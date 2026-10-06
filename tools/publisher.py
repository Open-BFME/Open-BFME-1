#!/usr/bin/env python3
"""The publisher: the only writer of the target branch; it writes receipted tips.

WHY. tools/landing_service.py batches, bisects and recovers exact tips, but
(audit 2026-10, sol61): its default gate runs the CANDIDATE's own
.githooks/pre-push, so a unit that weakens the hook approves itself; a unit's
`verify` command runs with the service's environment and credentials; the
drainer sleeps ten minutes after every pass (67-120 commits/h against BFME2
peaks of 271/h); and worker identity is whatever the worker wrote. This file
replaces it. It imports nothing from the repository it serves, so BFME2
copies it unchanged; everything repository-specific is in the state's
config.json.

PIECES.
  CHECKER    A pinned bundle: the files under `checker_paths` (tools/,
             .githooks/, build scripts) at one PROMOTED commit, extracted to
             state/checkers/<digest>/ and re-hashed before every use. The
             candidate's own copies never run: the builder overlays the
             bundle onto the candidate worktree and marks the overlaid paths
             skip-worktree, so `git diff`/`status` inside the gate still see
             the candidate's tree. `promote` is the only way to change the
             bundle: every exploit fixture must get its expected verdict, and
             the full-ledger output (`ledger_cmd`) of the old and new bundle
             on the current head must agree, or each differing line must be
             listed in --accept-diff.
  BUILDER    `build` is its own process with a scrubbed environment (no
             tokens, no credential helper, no global/system git config, HOME
             in its scratch dir), in a clone with NO remote that borrows the
             publisher's objects (--shared). It runs the configured gate with
             the pinned checker and writes a receipt: tip, base, tip tree,
             checker digest, toolchain hashes, verdict, log hash, signed with
             HMAC-SHA256 (state/receipt.key). A unit cannot bring a command:
             a check a unit needs belongs in the checker.
  PUBLISHER  Fast-forwards the branch (never forces) only to a tip whose
             receipt verifies, is green, names the current checker and names
             EXACTLY the current head as base. Batches are speculative: with N
             builders, batch k is composed on batch k-1's tip and gated at the
             same time. A red batch splits in halves (bisect); batches stacked
             on it go back to the queue. Composition is deterministic (fixed
             committer, committer date = author date), so the same units on
             the same base give the same tip SHA: after a crash its receipt is
             reused and nothing is re-gated. A publication is journalled; on
             start, a journalled tip already on the branch settles as landed.
             The drainer never sleeps after a batch; it waits at most
             `poll_seconds` for a builder or a submission.
  FAIRNESS   An operator is the key that signed the submission (config
             `operators`), never the commit author. Each has a token bucket
             (`rate` units/h, `burst`). A batch takes reserved `infra_slots`
             for infrastructure units, then round-robin from operators
             holding tokens, then fills leftover room (work-conserving) except
             from operators in the slow lane (more than `red_slow_lane` of
             their last 20 gated units red). Units sharing a `bundle` land or
             fail together; `after` orders a unit behind others. Waiting
             raises priority by one per `aging_minutes`, and a prerequisite
             inherits the priority of everything waiting on it, so zero-credit
             prerequisite work is not starved. A `wide` unit is gated alone.
  SUBMIT     Operators call `submit` instead of `git push`: the range becomes
             a format-patch unit plus an envelope signed with the operator's
             key, written to an inbox directory or pushed to
             refs/submit/<operator>/<id> on a submission remote.
             tools/publisher_pre_push.sh turns a push to master into a submit.
  METRICS    state/events.jsonl; `status` prints queue depth per operator,
             oldest wait, landed in the last hour, latency p50/p95, builders.

LIMITS. Builders run as the publisher's OS user unless config
`builder_prefix` runs them as another (e.g. ["sudo", "-u", "builder"]): env
scrubbing keeps tokens out of the gate, only a separate user keeps the
receipt key and the OS credential store out of reach. Only an admin ruleset
restricting the branch to the bot stops a direct or API push; the publisher
detects one (event `foreign_push`) and re-bases its pipeline. Runbook:
docs/throughput-tools.md, "Publisher".

  python3 tools/publisher.py init --state DIR --target URL [--set key=json ...]
  python3 tools/publisher.py operator --state DIR NAME [--rate 60 --burst 20 --infra]
  python3 tools/publisher.py promote --state DIR COMMIT [--fixtures DIR] [--accept-diff FILE]
  python3 tools/publisher.py submit --operator NAME --key-file F (--inbox DIR | --remote URL) [RANGE]
  python3 tools/publisher.py drain --state DIR [--once]
  python3 tools/publisher.py status --state DIR
"""
import argparse
import collections
import hashlib
import hmac
import io
import json
import math
import os
import re
import shutil
import socket
import subprocess
import sys
import tarfile
import threading
import time
import uuid
from pathlib import Path

DEFAULTS = dict(
    branch="master", submit_remote=None, inbox=None,
    checker_paths=["tools", ".githooks"], toolchain_paths=[],
    gate='bash .githooks/pre-push', ledger_cmd=None, gate_timeout=6 * 3600,
    builders=2, max_batch=20, poll_seconds=2.0, builder_prefix=[], clean_keep=["build/"],
    push_options=[], operators={}, infra_slots=2, aging_minutes=30.0, red_slow_lane=0.2,
    target_red_batch=0.1, min_batch=2, fair=True,
)
COMMITTER = "publisher"
# what the builder process and the gate may inherit; everything else (tokens,
# SSH agent, GIT_* overrides, credential helpers) is dropped
SAFE_ENV = ("PATH", "PATHEXT", "SYSTEMROOT", "SystemRoot", "WINDIR", "COMSPEC", "TEMP", "TMP",
            "LANG", "LC_ALL", "TZ", "NUMBER_OF_PROCESSORS", "PROCESSOR_ARCHITECTURE", "OS",
            "MSYSTEM", "PYTHONIOENCODING", "PYTHONUTF8")


class Crash(BaseException):
    """Raised by a test's crash point: the process dies there."""


# ---- small helpers ----------------------------------------------------------
def git(*args, cwd, check=True, env=None, input_bytes=None, timeout=900):
    got = subprocess.run(["git", *args], cwd=cwd, capture_output=True, input=input_bytes,
                         env=env, timeout=timeout)
    if check and got.returncode:
        raise RuntimeError(f"git {' '.join(map(str, args))}: "
                           f"{got.stderr.decode(errors='replace').strip()}")
    return got


def out(*args, cwd, env=None):
    return git(*args, cwd=cwd, env=env).stdout.decode().strip()


def canonical(obj):
    return json.dumps(obj, sort_keys=True, separators=(",", ":")).encode()


def sign(key, obj):
    body = {k: v for k, v in obj.items() if k != "mac"}
    return hmac.new(key, canonical(body), hashlib.sha256).hexdigest()


def signed(key, obj):
    return dict(obj, mac=sign(key, obj))


def verify_mac(key, obj):
    return bool(obj.get("mac")) and hmac.compare_digest(obj["mac"], sign(key, obj))


def read_key(path):
    return bytes.fromhex(Path(path).read_text(encoding="ascii").strip())


def new_key(path):
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(os.urandom(32).hex() + "\n", encoding="ascii")
    return path


def write_json(path, data):
    tmp = Path(f"{path}.{os.getpid()}.{threading.get_ident()}.tmp")
    tmp.write_text(json.dumps(data, indent=1, sort_keys=True), encoding="utf-8")
    os.replace(tmp, path)


def read_json(path, default=None):
    try:
        return json.loads(Path(path).read_text(encoding="utf-8"))
    except FileNotFoundError:
        return default


def tree_digest(root):
    """sha256 over (relative path, sha256 of bytes) of every file under root."""
    root = Path(root)
    h = hashlib.sha256()
    for path in sorted(p for p in root.rglob("*") if p.is_file()):
        h.update(path.relative_to(root).as_posix().encode() + b"\0")
        h.update(hashlib.sha256(path.read_bytes()).hexdigest().encode() + b"\n")
    return h.hexdigest()


def scrubbed_env(home, **extra):
    env = {k: os.environ[k] for k in SAFE_ENV if k in os.environ}
    Path(home).mkdir(parents=True, exist_ok=True)
    env.update(HOME=str(home), USERPROFILE=str(home), GIT_CONFIG_NOSYSTEM="1",
               GIT_CONFIG_GLOBAL=os.devnull, GIT_TERMINAL_PROMPT="0", GCM_INTERACTIVE="never",
               GIT_ASKPASS="", SSH_ASKPASS="", GIT_SSH_COMMAND="false")
    env.update({k: str(v) for k, v in extra.items()})
    return env


def percentile(values, q):
    values = sorted(values)
    if not values:
        return None
    return values[min(len(values) - 1, int(round(q * (len(values) - 1))))]


# ---- configuration and state ------------------------------------------------
class State:
    def __init__(self, root):
        self.root = Path(root)
        for sub in ("queue", "landed", "rejected", "inbox-rejected", "receipts", "logs",
                    "checkers", "builders"):
            (self.root / sub).mkdir(parents=True, exist_ok=True)
        self.cfg = dict(DEFAULTS, **(read_json(self.root / "config.json", {}) or {}))
        self.receipt_key_path = self.root / "receipt.key"

    @property
    def receipt_key(self):
        return read_key(self.receipt_key_path)

    def operator_key(self, name):
        op = self.cfg["operators"].get(name)
        if not op:
            return None
        path = Path(op["key_file"])
        return read_key(path if path.is_absolute() else self.root / path)

    def event(self, name, t=None, **data):
        record = dict(data, ev=name, t=round(time.time() if t is None else t, 3))
        with (self.root / "events.jsonl").open("a", encoding="utf-8") as handle:
            handle.write(json.dumps(record) + "\n")


# ---- the pinned checker -----------------------------------------------------
class Checkers:
    """Bundles by digest, and which one is promoted (state/checkers.json)."""

    def __init__(self, state):
        self.state = state
        self.index_path = state.root / "checkers.json"

    def index(self):
        return read_json(self.index_path, {"current": None, "history": []})

    def current(self):
        return self.index()["current"]

    def path(self, digest):
        """The bundle directory, after checking its bytes still hash to digest."""
        where = self.state.root / "checkers" / digest
        if not where.is_dir() or tree_digest(where) != digest:
            raise RuntimeError(f"checker bundle {digest[:12]} is missing or was modified")
        return where

    def materialize(self, repo, commit):
        """Extract checker_paths at `commit`; returns its digest."""
        paths = [p for p in self.state.cfg["checker_paths"]
                 if git("cat-file", "-e", f"{commit}:{p}", cwd=repo, check=False).returncode == 0]
        if not paths:
            raise RuntimeError(f"{commit} has none of checker_paths {self.state.cfg['checker_paths']}")
        tmp = self.state.root / "checkers" / f"tmp-{uuid.uuid4().hex}"
        data = git("archive", "--format=tar", commit, "--", *paths, cwd=repo).stdout
        with tarfile.open(fileobj=io.BytesIO(data)) as tar:
            try:
                tar.extractall(tmp, filter="data")
            except TypeError:                   # Python < 3.11.4: no extraction filters
                tar.extractall(tmp)
        digest = tree_digest(tmp)
        final = self.state.root / "checkers" / digest
        if final.exists():
            shutil.rmtree(tmp)
        else:
            os.replace(tmp, final)
        return digest

    def record(self, digest, commit, evidence):
        index = self.index()
        index["history"].append(dict(evidence, digest=digest, commit=commit, promoted=time.time(),
                                     previous=index["current"]))
        index["current"] = digest
        write_json(self.index_path, index)


# ---- the isolated builder ---------------------------------------------------
class Builder:
    """One build slot: a remote-less clone borrowing the publisher's objects."""

    def __init__(self, state, name):
        self.state, self.name = state, name
        self.dir = state.root / "builders" / name
        self.work = self.dir / "wt"
        self.env = scrubbed_env(self.dir / "home")

    def _git(self, *args, **kw):
        return git(*args, cwd=self.work, env=self.env, **kw)

    def checkout(self, tip, digest):
        source = self.state.root / "repo"
        if not (self.work / ".git").exists():
            git("clone", "-q", "--shared", "--no-checkout", str(source), str(self.work),
                cwd=self.dir, env=self.env)
            self._git("remote", "remove", "origin")     # nothing to push to, by construction
        (self.work / ".git" / "index").unlink(missing_ok=True)   # drops old skip-worktree bits
        self._git("update-ref", "--no-deref", "HEAD", tip)
        self._git("reset", "-q", "--hard", tip)
        keep = [a for k in self.state.cfg["clean_keep"] for a in ("-e", k)]
        self._git("clean", "-qfdx", *keep)
        bundle = Checkers(self.state).path(digest)
        paths = self.state.cfg["checker_paths"]
        for rel in paths:
            target = self.work / rel
            if target.is_dir() and not target.is_symlink():
                shutil.rmtree(target)
            elif target.exists() or target.is_symlink():
                target.unlink()
            src = bundle / rel
            if src.is_dir():
                shutil.copytree(src, target)
            elif src.is_file():
                target.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(src, target)
        tracked = self._git("ls-files", "-z", "--", *paths).stdout
        if tracked:
            self._git("update-index", "-z", "--skip-worktree", "--stdin", input_bytes=tracked)
        (self.work / ".git" / "info").mkdir(exist_ok=True)
        (self.work / ".git" / "info" / "exclude").write_text(
            "".join(f"/{p.strip('/')}\n" for p in paths), encoding="utf-8")
        return bundle

    def toolchain(self, tip):
        found = {}
        for rel in self.state.cfg["toolchain_paths"]:
            got = self._git("rev-parse", f"{tip}:{rel}", check=False)
            found[rel] = got.stdout.decode().strip() if got.returncode == 0 else None
        found["python"] = hashlib.sha256(Path(sys.executable).read_bytes()).hexdigest()
        found["git"] = out("--version", cwd=self.dir)
        return found

    def run(self, base, tip, digest, command=None, timeout=None):
        """(exit code, output) of `command` (default: the gate) at `tip`."""
        bundle = self.checkout(tip, digest)
        env = dict(self.env, LANDING_BASE=base, LANDING_TIP=tip, CHECKER_DIR=bundle.as_posix(),
                   CHECKER_DIGEST=digest)
        try:
            got = subprocess.run(["bash", "-c", command or self.state.cfg["gate"]], cwd=self.work,
                                 env=env, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                                 timeout=timeout or self.state.cfg["gate_timeout"])
            code, output = got.returncode, got.stdout or b""
        except subprocess.TimeoutExpired as error:
            code, output = 124, (error.stdout or b"") + b"\n[publisher] gate timed out\n"
        Checkers(self.state).path(digest)       # the bundle was not touched meanwhile
        return code, output

    def build(self, base, tip, digest):
        started = time.time()
        code, output = self.run(base, tip, digest)
        log = self.state.root / "logs" / f"{tip}.{digest[:12]}.log"
        log.write_bytes(output)
        receipt = dict(v=1, tip=tip, base=base, tree=out("rev-parse", f"{tip}^{{tree}}", cwd=self.work),
                       checker=digest, toolchain=self.toolchain(tip),
                       verdict="green" if code == 0 else "red", exit=code,
                       log_sha256=hashlib.sha256(output).hexdigest(), builder=self.name,
                       blame=sorted(set(m.decode(errors="replace").strip() for m in re.findall(
                           rb"^PUBLISHER-BLAME: (.+)$", output, re.MULTILINE)))[:200],
                       host=socket.gethostname(), started=started,
                       seconds=round(time.time() - started, 2))
        receipt = signed(self.state.receipt_key, receipt)
        write_json(receipt_path(self.state, tip, base, digest), receipt)
        return receipt


def receipt_path(state, tip, base, digest):
    return state.root / "receipts" / f"{tip}.{base[:16]}.{digest[:16]}.json"


def kill_tree(proc):
    """Kill a build and its gate: an orphaned gate would keep writing into the
    slot's worktree while the slot's next build runs there."""
    if os.name == "nt":
        subprocess.run(["taskkill", "/T", "/F", "/PID", str(proc.pid)], capture_output=True)
    else:
        import signal
        try:
            os.killpg(proc.pid, signal.SIGKILL)
        except ProcessLookupError:
            pass


class ProcessExecutor:
    """Runs each build as a separate `publisher.py build` process (scrubbed
    environment, optional builder_prefix) on one of N slots."""

    def __init__(self, state):
        self.state = state
        self.n = int(state.cfg["builders"])
        self.free = collections.deque(f"b{i}" for i in range(self.n))
        self.waiting = collections.deque()
        self.lock = threading.Lock()
        self.wake = threading.Event()

    def submit(self, base, tip, digest, units):
        job = dict(base=base, tip=tip, digest=digest, units=list(units), result=None, proc=None,
                   cancelled=False, slot=None)
        with self.lock:
            self.waiting.append(job)
        self._start()
        return job

    def _start(self):
        with self.lock:
            while self.free and self.waiting:
                job = self.waiting.popleft()
                job["slot"] = self.free.popleft()
                threading.Thread(target=self._run, args=(job,), daemon=True).start()

    def _run(self, job):
        argv = [*self.state.cfg["builder_prefix"], sys.executable, str(Path(__file__).resolve()),
                "build", "--state", str(self.state.root), "--slot", job["slot"],
                "--base", job["base"], "--tip", job["tip"], "--checker", job["digest"]]
        env = scrubbed_env(self.state.root / "builders" / job["slot"] / "home")
        try:
            with self.lock:
                if job["cancelled"]:
                    return
                job["proc"] = subprocess.Popen(argv, env=env, stdout=subprocess.PIPE,
                                               stderr=subprocess.STDOUT,
                                               start_new_session=os.name != "nt")
            text = job["proc"].communicate()[0].decode(errors="replace")
            if not job["cancelled"]:
                got = read_json(receipt_path(self.state, job["tip"], job["base"], job["digest"]))
                job["result"] = got or dict(verdict="error", error=text[-2000:])
        finally:
            with self.lock:
                self.free.append(job["slot"])
            self.wake.set()
            self._start()

    def poll(self, job):
        return job["result"]

    def cancel(self, job):
        with self.lock:
            job["cancelled"] = True
            if job in self.waiting:
                self.waiting.remove(job)
            proc = job["proc"]
        if proc and proc.poll() is None:
            kill_tree(proc)

    def busy(self):
        return self.n - len(self.free)

    def wait(self, seconds):
        self.wake.wait(seconds)
        self.wake.clear()


# ---- the target repository --------------------------------------------------
class GitRepo:
    """The publisher's private clone: the only place with push credentials."""

    def __init__(self, state):
        self.state = state
        self.dir = state.root / "repo"
        self.target, self.branch = state.cfg["target"], state.cfg["branch"]
        if not (self.dir / ".git").exists():
            git("init", "-q", str(self.dir), cwd=state.root)
            git("config", "gc.auto", "0", cwd=self.dir)    # builders borrow these objects
            git("remote", "add", "target", self.target, cwd=self.dir)
        self.env = dict(os.environ, GIT_COMMITTER_NAME=COMMITTER, GIT_COMMITTER_EMAIL="",
                        GIT_AUTHOR_NAME=COMMITTER, GIT_AUTHOR_EMAIL="")

    def head(self):
        got = out("ls-remote", self.target, f"refs/heads/{self.branch}", cwd=self.dir).split()
        sha = got[0] if got else None
        if sha and git("cat-file", "-e", f"{sha}^{{commit}}", cwd=self.dir, check=False).returncode:
            git("fetch", "-q", "--no-tags", "target",
                f"+refs/heads/{self.branch}:refs/publisher/head", cwd=self.dir)
        return sha

    def compose(self, base, patches):
        """(tip, None) after `git am` of every patch on base, or (None, unit id)."""
        git("am", "--abort", cwd=self.dir, check=False)
        git("checkout", "-q", "-f", "--detach", base, cwd=self.dir)
        git("clean", "-qfd", cwd=self.dir)
        for unit, patch in patches:
            got = git("-c", f"user.name={COMMITTER}", "-c", "user.email=", "am", "-q", "-3",
                      "--keep-cr", "--committer-date-is-author-date", str(patch),
                      cwd=self.dir, env=self.env, check=False)
            if got.returncode:
                git("am", "--abort", cwd=self.dir, check=False)
                return None, unit
        tip = out("rev-parse", "HEAD", cwd=self.dir)
        git("update-ref", f"refs/publisher/tips/{tip}", tip, cwd=self.dir)   # keep it reachable
        return tip, None

    def tree(self, tip):
        return out("rev-parse", f"{tip}^{{tree}}", cwd=self.dir)

    def is_ancestor(self, older, newer):
        return git("merge-base", "--is-ancestor", older, newer, cwd=self.dir,
                   check=False).returncode == 0

    def publish(self, tip):
        """Fast-forward only: a plain push, never forced."""
        opts = [f"--push-option={o}" for o in self.state.cfg["push_options"]]
        got = git("push", "-q", *opts, "target", f"{tip}:refs/heads/{self.branch}", cwd=self.dir,
                  check=False)
        return got.returncode == 0


# ---- scheduling ------------------------------------------------------------
class Scheduler:
    """Token buckets, bundles, dependencies, aging, infra reservation."""

    def __init__(self, state, clock):
        self.state, self.clock = state, clock
        self.buckets = read_json(state.root / "buckets.json", {}) or {}
        self.outcomes = {k: collections.deque(v, maxlen=20)
                         for k, v in (read_json(state.root / "outcomes.json", {}) or {}).items()}
        self.recent = collections.deque((v for d in self.outcomes.values() for v in d), maxlen=300)

    def _op(self, name):
        return self.state.cfg["operators"].get(name, {})

    def refill(self, now):
        for name, op in self.state.cfg["operators"].items():
            tokens, last = self.buckets.get(name, (float(op.get("burst", 20)), now))
            tokens = min(float(op.get("burst", 20)),
                         tokens + self.rate(name) * max(0.0, now - last) / 3600.0)
            self.buckets[name] = (tokens, now)

    def rate(self, name):
        rate = float(self._op(name).get("rate", 60))
        return rate / 2 if self.slow(name) else rate

    def slow(self, name):
        seen = self.outcomes.get(name) or ()
        return len(seen) >= 5 and seen.count("red") / len(seen) > self.state.cfg["red_slow_lane"]

    def outcome(self, operator, verdict):
        self.outcomes.setdefault(operator, collections.deque(maxlen=20)).append(verdict)
        self.recent.append(verdict)

    def save(self):
        write_json(self.state.root / "buckets.json", self.buckets)
        write_json(self.state.root / "outcomes.json", {k: list(v) for k, v in self.outcomes.items()})

    def pick(self, records, exclude, landed, room, now):
        """(items, rejections). items: lists of unit ids, dependencies first;
        rejections: [(unit, reason)] for units whose prerequisites failed."""
        self.refill(now)
        recs = {u: r for u, r in records.items() if u not in exclude}
        rejections = [(u, "dependency-rejected") for u, r in recs.items()
                      if any(self.state_of(d) == "rejected" for d in r.get("after") or ())]
        for u, _ in rejections:
            recs.pop(u)
        groups = collections.OrderedDict()
        for u, r in sorted(recs.items(), key=lambda kv: (kv[1]["enqueued"], kv[0])):
            key = (r["operator"], r["bundle"]) if r.get("bundle") else ("", u)
            groups.setdefault(key, []).append(u)
        item_of = {u: key for key, us in groups.items() for u in us}
        aging = max(1e-9, float(self.state.cfg["aging_minutes"]) * 60)
        prio = {key: max(min(10.0, float(recs[u].get("priority") or 0)) +
                         (now - recs[u]["enqueued"]) / aging for u in us)
                for key, us in groups.items()}
        deps = {key: {item_of[d] for u in us for d in recs[u].get("after") or ()
                      if d in item_of and item_of[d] != key} for key, us in groups.items()}
        for _ in range(len(groups)):            # a prerequisite inherits its dependents' priority
            changed = False
            for key, needs in deps.items():
                for need in needs:
                    if prio[need] < prio[key]:
                        prio[need], changed = prio[key], True
            if not changed:
                break
        done_units = set(exclude) | set(landed)

        def ready(key, chosen):
            for u in groups[key]:
                for d in recs[u].get("after") or ():
                    if d not in done_units and d not in chosen and item_of.get(d) != key:
                        return False
            return True

        chosen, items, left = set(), [], room
        order = sorted(groups, key=lambda k: (-prio[k], recs[groups[k][0]]["enqueued"]))

        def take(key):
            nonlocal left
            items.append(list(groups[key]))
            chosen.update(groups[key])
            left -= len(groups[key])

        candidates = [k for k in order if ready(k, chosen)]
        if candidates and any(recs[u].get("kind") == "wide" for u in groups[candidates[0]]):
            return [list(groups[candidates[0]])], rejections   # a wide unit is gated alone
        wide = {k for k in order if any(recs[u].get("kind") == "wide" for u in groups[k])}
        infra = 0
        for key in order:                      # 1. reserved infrastructure slots
            size = len(groups[key])
            if (key in wide or any(recs[u].get("kind") != "infra" for u in groups[key])
                    or infra + size > self.state.cfg["infra_slots"] or size > left
                    or not ready(key, chosen)):
                continue
            take(key)
            infra += size
        fair = self.state.cfg.get("fair", True)       # False: arrival/priority order only
        progress = fair
        while progress and left > 0:          # 2. round-robin among operators holding tokens
            progress = False
            ops = []
            for key in order:
                op = recs[groups[key][0]]["operator"]
                if op not in ops:
                    ops.append(op)
            for op in ops:
                key = next((k for k in order if k not in wide and groups[k][0] not in chosen
                            and recs[groups[k][0]]["operator"] == op and ready(k, chosen)), None)
                if key is None:
                    continue
                size = len(groups[key])
                tokens, stamp = self.buckets.get(op, (0.0, now))
                if size <= left and tokens >= size:     # one item per operator per round
                    self.buckets[op] = (tokens - size, stamp)
                    take(key)
                    progress = True
        for key in order:                     # 3. work-conserving fill, slow lane excluded
            if left <= 0:
                break
            op = recs[groups[key][0]]["operator"]
            if (key in wide or groups[key][0] in chosen or (fair and self.slow(op))
                    or len(groups[key]) > left or not ready(key, chosen)):
                continue
            take(key)
        return items, rejections

    def state_of(self, unit):
        for where in ("rejected", "landed"):
            if (self.state.root / where / f"{unit}.json").exists():
                return where
        return None


# ---- the publisher ---------------------------------------------------------
class Batch:
    def __init__(self, items, base, tip):
        self.items, self.base, self.tip = items, base, tip
        self.job = None
        self.receipt = None
        self.probe = False

    @property
    def units(self):
        return [u for item in self.items for u in item]


class Publisher:
    def __init__(self, state, repo=None, executor=None, clock=time.time, crash_at=(), offline=False):
        self.state = state if isinstance(state, State) else State(state)
        self.cfg = self.state.cfg
        self.clock = clock
        self.repo = repo or GitRepo(self.state)
        self.executor = executor or ProcessExecutor(self.state)
        self.checkers = Checkers(self.state)
        self.sched = Scheduler(self.state, clock)
        self.crash_at = set(crash_at)
        self.inflight = []
        self.queue = {}
        for path in (self.state.root / "queue").glob("*.json"):
            record = read_json(path)
            self.queue[record["id"]] = record
        self.landed = {p.stem for p in (self.state.root / "landed").glob("*.json")}
        self.published = set()
        self.heads = set()                  # every head seen: a red lone item there is red
        self.pause_until = 0.0
        self.head = None
        self.stats = dict(gates=0, reused=0, batches=0, red_batches=0)
        self.lat = collections.deque(maxlen=5000)       # (landed time, latency seconds)
        if not offline:
            self.recover()

    def _crash(self, point):
        if point in self.crash_at:
            raise Crash(point)

    def event(self, name, **data):
        self.state.event(name, t=self.clock(), **data)

    # ---- submissions ----------------------------------------------------
    def accept(self, envelope, patch):
        """Queue a signed submission; returns (unit id, None) or (None, reason)."""
        op = envelope.get("operator")
        key = self.state.operator_key(op) if isinstance(op, str) else None
        if key is None:
            return None, "unknown-operator"
        if not verify_mac(key, envelope) or hashlib.sha256(patch).hexdigest() != envelope.get("patch_sha256"):
            return None, "bad-signature"
        unit = hashlib.sha256(patch).hexdigest()[:20]
        if unit in self.queue or self.sched.state_of(unit):
            return unit, None                       # the same bytes are one unit
        kind = envelope.get("kind") or "normal"
        if kind == "infra" and not self.cfg["operators"][op].get("infra"):
            kind = "normal"                          # only infra-flagged operators get the reserve
        record = dict(id=unit, operator=op, kind=kind if kind in ("normal", "infra", "wide") else "normal",
                      after=[str(a) for a in envelope.get("after") or ()],
                      bundle=envelope.get("bundle"), priority=envelope.get("priority") or 0,
                      submitted=envelope.get("time"), enqueued=self.clock(),
                      commits=patch.count(b"\nFrom ") + patch.startswith(b"From "),
                      paths=sorted({m.decode(errors="replace") for m in
                                    re.findall(rb"^diff --git a/\S+ b/(\S+)$", patch, re.MULTILINE)}),
                      sim_bad=bool(envelope.get("sim_bad")))
        (self.state.root / "queue" / f"{unit}.patch").write_bytes(patch)
        write_json(self.state.root / "queue" / f"{unit}.json", record)
        self.queue[unit] = record
        self.event("enqueue", unit=unit, operator=op, kind=record["kind"])
        return unit, None

    def ingest(self):
        inbox = self.cfg.get("inbox")
        if inbox and Path(inbox).is_dir():
            for env_path in sorted(Path(inbox).glob("*.env.json")):
                patch_path = env_path.with_name(env_path.name[:-len(".env.json")] + ".patch")
                if not patch_path.exists():
                    continue
                self._ingest_one(read_json(env_path), patch_path.read_bytes(), env_path.name)
                env_path.unlink()
                patch_path.unlink()
        remote = self.cfg.get("submit_remote")
        if remote and isinstance(self.repo, GitRepo):
            listing = out("ls-remote", remote, "refs/submit/*", cwd=self.repo.dir).splitlines()
            for line in listing:
                sha, ref = line.split()
                git("fetch", "-q", "--no-tags", remote, f"+{ref}:refs/publisher/in", cwd=self.repo.dir)
                env = git("show", f"{sha}:envelope.json", cwd=self.repo.dir, check=False)
                patch = git("show", f"{sha}:unit.patch", cwd=self.repo.dir, check=False)
                if env.returncode or patch.returncode:
                    self.event("inbox_rejected", ref=ref, reason="malformed")
                else:
                    self._ingest_one(json.loads(env.stdout), patch.stdout, ref)
                git("push", "-q", remote, f":{ref}", cwd=self.repo.dir, check=False)

    def _ingest_one(self, envelope, patch, name):
        unit, reason = self.accept(envelope or {}, patch)
        if reason:
            write_json(self.state.root / "inbox-rejected" / f"{uuid.uuid4().hex}.json",
                       dict(source=name, reason=reason, operator=(envelope or {}).get("operator")))
            self.event("inbox_rejected", source=name, reason=reason)

    # ---- settlement -----------------------------------------------------
    def _finish(self, unit, where, **extra):
        record = self.queue.pop(unit, None) or read_json(self.state.root / "queue" / f"{unit}.json")
        if record is None:
            return
        now = self.clock()
        record.update(extra, finished=now)
        write_json(self.state.root / where / f"{unit}.json", record)
        (self.state.root / "queue" / f"{unit}.json").unlink(missing_ok=True)
        if where == "landed":
            self.landed.add(unit)
            self.lat.append((now, now - record["enqueued"]))
        verdict = "green" if where == "landed" else "red" if extra.get("reason") == "gate" else None
        if verdict:
            self.sched.outcome(record["operator"], verdict)
        self.event(where, unit=unit, operator=record["operator"], reason=extra.get("reason"),
                   wait=round(now - record["enqueued"], 1))

    def recover(self):
        """Settle a journalled publication left by a crash."""
        if (self.state.root / "journal.json").exists():
            self._settle(note="recovered after a crash")

    def _settle(self, note=""):
        journal = read_json(self.state.root / "journal.json")
        head = self.repo.head()
        if not head:
            raise RuntimeError("target branch unreadable; publication journal kept")
        ok = self.repo.is_ancestor(journal["tip"], head)
        if ok:
            receipt = read_json(journal["receipt"]) if journal.get("receipt") else None
            for unit in journal["units"]:
                if unit in self.queue:
                    self._finish(unit, "landed", tip=journal["tip"], base=journal["base"],
                                 checker=journal["checker"], receipt=journal.get("receipt"),
                                 receipt_mac=(receipt or {}).get("mac"), note=note)
            self.published.add(journal["tip"])
            self.event("published", tip=journal["tip"], base=journal["base"],
                       units=len(journal["units"]), note=note)
        (self.state.root / "journal.json").unlink()
        # a push by anyone else after ours still shows up as foreign in step()
        self.head = journal["tip"] if ok else head
        self.heads.add(self.head)
        self.sched.save()
        return ok

    def verify_receipt(self, receipt, batch, head):
        if not receipt or not verify_mac(self.state.receipt_key, receipt):
            return "bad-mac"
        if receipt["tip"] != batch.tip or receipt["base"] != batch.base:
            return "wrong-tip-or-base"
        if receipt["base"] != head:
            return "base-is-not-head"
        if receipt["checker"] != self.checkers.current():
            return "stale-checker"
        if receipt["verdict"] != "green":
            return "red"
        if receipt["tree"] != self.repo.tree(batch.tip) or not self.repo.is_ancestor(head, batch.tip):
            return "tree-or-ancestry"
        return None

    def _publish(self, batch):
        head = self.repo.head()
        why = self.verify_receipt(batch.receipt, batch, head)
        if why:
            self.event("receipt_refused", tip=batch.tip, reason=why)
            return False
        path = receipt_path(self.state, batch.tip, batch.base, batch.receipt["checker"])
        write_json(self.state.root / "journal.json",
                   dict(phase="publishing", base=batch.base, tip=batch.tip, units=batch.units,
                        checker=batch.receipt["checker"], receipt=str(path)))
        self._crash("before_push")
        self.repo.publish(batch.tip)
        self._crash("after_push")
        return self._settle()

    # ---- the pipeline ---------------------------------------------------
    def _flush(self, start=0):
        for batch in self.inflight[start:]:
            if batch.job is not None:
                self.executor.cancel(batch.job)
        del self.inflight[start:]

    def _dispatch(self, batch, digest):
        self.stats["batches"] += 1
        path = receipt_path(self.state, batch.tip, batch.base, digest)
        cached = read_json(path)
        if cached and verify_mac(self.state.receipt_key, cached):
            batch.receipt = cached                  # exact tip already gated: reuse
            self.stats["reused"] += 1
        else:
            self.stats["gates"] += 1
            batch.job = self.executor.submit(batch.base, batch.tip, digest, batch.units)
        self.inflight.append(batch)
        self.event("batch", tip=batch.tip, base=batch.base, units=len(batch.units),
                   reused=batch.receipt is not None, depth=len(self.inflight))

    def _compose(self, base, items, final):
        """A Batch of `items` on `base`; a unit that does not apply is rejected
        when base is the head (`final`), otherwise deferred to a later pass."""
        items = [list(i) for i in items]
        while items:
            patches = [(u, self.state.root / "queue" / f"{u}.patch") for i in items for u in i]
            tip, bad = self.repo.compose(base, patches)
            if not bad:
                return Batch(items, base, tip), []
            item = next(i for i in items if bad in i)
            items.remove(item)
            if not final:
                return None, item               # may be the speculative base's fault
            for u in item:
                self._finish(u, "rejected", reason="conflict", base=base)
        return None, []

    def step(self):
        """One non-blocking turn. Returns True when something changed.

        The pipeline is a list of batches; each is based on the head or on
        another batch's tip. A batch based on the head with a receipt is
        settled in list order: green publishes (the batch stacked on it is now
        on the head), red splits. A batch whose base is neither the head nor a
        tip still in the list is an orphan and goes back to the queue."""
        changed = False
        self.ingest()
        digest = self.checkers.current()
        if not digest:
            return False
        head = self.repo.head()
        if head != self.head:
            if self.head is not None and head not in self.published:
                self.event("foreign_push", head=head, expected=self.head)
            self._flush(0)
            self.head = head
            changed = True
        self.heads.add(head)
        while True:
            acted = False
            for batch in self.inflight:
                if batch.receipt is None and batch.job is not None:
                    batch.receipt = self.executor.poll(batch.job)
            for batch in list(self.inflight):
                # a lone item red on a real head is red: rejecting never publishes
                got = batch.receipt or {}
                if (got.get("verdict") == "red" and len(batch.items) == 1
                        and batch.base in self.heads and got.get("checker") == digest):
                    self._drop(batch)
                    self.stats["red_batches"] += 1
                    for u in batch.items[0]:
                        self._finish(u, "rejected", reason="gate", base=batch.base, tip=batch.tip,
                                     bundle_red=len(batch.items[0]) > 1)
                    acted = True
            for batch in self.inflight:
                if batch.base != self.head:
                    continue
                if batch.receipt is None:
                    break                            # settle in order: wait for it
                acted = True
                self._drop(batch)
                verdict = batch.receipt.get("verdict")
                if verdict == "error":                # no receipt: back off, then regate
                    self.event("builder_error", tip=batch.tip, error=batch.receipt.get("error"))
                    self.pause_until = self.clock() + 30
                elif batch.receipt.get("checker") != digest:
                    pass                              # promoted meanwhile: its units regate
                elif verdict == "green":
                    if not self._publish(batch):
                        self._flush(0)
                        self.pause_until = self.clock() + 30
                else:
                    self.stats["red_batches"] += 1
                    self._split(batch, digest)
                break
            acted |= self._prune()
            if not acted:
                break
            changed = True
        changed |= self._fill(digest)
        self.sched.save()
        return changed

    def _drop(self, batch):
        if batch in self.inflight:
            self.inflight.remove(batch)
        if batch.job is not None and batch.receipt is None:
            self.executor.cancel(batch.job)

    def _prune(self):
        """Drop orphans (their units stay queued); True when any was dropped."""
        dropped = False
        while True:
            tips = {b.tip for b in self.inflight}
            orphans = [b for b in self.inflight if b.base != self.head and b.base not in tips]
            if not orphans:
                return dropped
            for batch in orphans:
                self._drop(batch)
            dropped = True

    def _split(self, batch, digest):
        """A red batch on the head. If the gate blamed paths (PUBLISHER-BLAME
        lines) that some but not all items touch, the rest is regated on the
        head and each suspect is probed alone; otherwise a k-way split over
        the builders, stacked, so the parts before the first red one land."""
        if len(batch.items) == 1:
            for u in batch.items[0]:
                self._finish(u, "rejected", reason="gate", base=batch.base, tip=batch.tip)
            return
        blame = set(batch.receipt.get("blame") or ())
        suspects = [it for it in batch.items if blame and any(
            p in blame for u in it for p in self.queue.get(u, {}).get("paths") or ())]
        if suspects and len(suspects) < len(batch.items):
            rest, _ = self._compose(self.head, [it for it in batch.items if it not in suspects], True)
            if rest:
                self._dispatch(rest, digest)
            for item in suspects:
                probe, _ = self._compose(self.head, [item], final=True)
                if probe:
                    probe.probe = True
                    self._dispatch(probe, digest)
            return
        k = max(2, min(len(batch.items), int(self.cfg["builders"])))
        size = -(-len(batch.items) // k)
        base = self.head
        for at in range(0, len(batch.items), size):
            part, _ = self._compose(base, batch.items[at:at + size], final=base == self.head)
            if not part:
                break
            self._dispatch(part, digest)
            base = part.tip

    def _fill(self, digest):
        """Keep `builders` batches in flight, each stacked on the last
        non-probe batch (nothing stacks on a probe or a wide unit)."""
        changed, skip = False, set()
        if self.clock() < self.pause_until:
            return False
        while len(self.inflight) < int(self.cfg["builders"]) and self.queue:
            chain = [b for b in self.inflight if not b.probe]
            if chain and any(self.queue.get(u, {}).get("kind") == "wide" for u in chain[-1].units):
                break
            base = chain[-1].tip if chain else self.head
            taken = {u for b in self.inflight for u in b.units} | skip
            items, rejections = self.sched.pick(self.queue, taken, self.landed,
                                                self.batch_size(), self.clock())
            for unit, reason in rejections:
                self._finish(unit, "rejected", reason=reason)
                changed = True
            if not items:
                break
            batch, deferred = self._compose(base, items, final=base == self.head)
            skip.update(deferred)
            if batch is None:
                changed = True
                continue
            self._dispatch(batch, digest)
            changed = True
        return changed

    def batch_size(self):
        """Units per new batch: the largest n with P(batch red) <= target_red_batch
        at the observed per-unit red rate (prior 2% over 50 units), so a run of
        red units shrinks batches instead of drowning the pipeline in bisects."""
        seen = list(self.sched.recent)
        rate = (seen.count("red") + 1.0) / (len(seen) + 50.0)
        target = float(self.cfg["target_red_batch"])
        n = int(math.log(1 - target) / math.log(1 - rate)) if rate < 1 else 1
        return max(int(self.cfg["min_batch"]), min(int(self.cfg["max_batch"]), n))

    # ---- reporting ------------------------------------------------------
    def status(self):
        now = self.clock()
        depth = collections.Counter(r["operator"] for r in self.queue.values())
        recent = [lat for t, lat in self.lat if now - t <= 3600]
        oldest = min((r["enqueued"] for r in self.queue.values()), default=None)
        return dict(queue=len(self.queue), per_operator=dict(depth),
                    oldest_wait_s=round(now - oldest, 1) if oldest else 0,
                    landed_last_hour=len(recent),
                    latency_p50_s=percentile(recent, 0.5), latency_p95_s=percentile(recent, 0.95),
                    inflight=len(self.inflight), builders_busy=self.executor.busy(),
                    checker=self.checkers.current(), **self.stats,
                    slow_lane=sorted(op for op in self.cfg["operators"] if self.sched.slow(op)))


def drain(publisher, once=False, stop=None):
    """Continuous: no sleep after a batch; wait at most poll_seconds for a
    builder to finish or a submission to arrive."""
    while not (stop and stop.is_set()):
        try:
            changed = publisher.step()
        except Crash:
            raise
        except Exception as error:  # noqa: BLE001 -- logged, the loop keeps the queue moving
            publisher.event("error", error=str(error))
            print(json.dumps({"error": str(error)}), file=sys.stderr, flush=True)
            changed = False
        if once and not publisher.inflight:
            return publisher.status()
        if not changed:
            publisher.executor.wait(float(publisher.cfg["poll_seconds"]))
    return publisher.status()


# ---- submission (operator side) --------------------------------------------
def make_unit(repo, rev):
    if ".." in rev:
        return git("format-patch", "--stdout", rev, cwd=repo).stdout
    return git("format-patch", "-1", "--stdout", rev, cwd=repo).stdout


def submit(repo, operator, key_file, rev="@{u}..HEAD", inbox=None, remote=None, kind="normal",
           after=(), bundle=None, priority=0, extra=None):
    """Hand a unit to the publisher; returns its id. Operator side only: it
    needs the operator's key, never the publisher's credentials."""
    patch = make_unit(repo, rev)
    if not patch.strip():
        raise RuntimeError(f"nothing to submit in {rev}")
    envelope = dict(v=1, operator=operator, patch_sha256=hashlib.sha256(patch).hexdigest(),
                    kind=kind, after=list(after), bundle=bundle, priority=priority,
                    time=time.time(), nonce=uuid.uuid4().hex, **(extra or {}))
    envelope = signed(read_key(key_file), envelope)
    unit = hashlib.sha256(patch).hexdigest()[:20]
    if inbox:
        inbox = Path(inbox)
        inbox.mkdir(parents=True, exist_ok=True)
        (inbox / f"{unit}.patch").write_bytes(patch)
        write_json(inbox / f"{unit}.env.json", envelope)    # last: the publisher keys on it
    if remote:
        blobs = {}
        for name, data in (("envelope.json", canonical(envelope)), ("unit.patch", patch)):
            blobs[name] = git("hash-object", "-w", "--stdin", cwd=repo,
                              input_bytes=data).stdout.decode().strip()
        tree = git("mktree", cwd=repo, input_bytes="".join(
            f"100644 blob {sha}\t{name}\n" for name, sha in sorted(blobs.items())).encode()
        ).stdout.decode().strip()
        env = dict(os.environ, GIT_AUTHOR_NAME=operator, GIT_AUTHOR_EMAIL="",
                   GIT_COMMITTER_NAME=operator, GIT_COMMITTER_EMAIL="")
        commit = out("commit-tree", tree, "-m", f"submit {unit}", cwd=repo, env=env)
        git("push", "-q", "--no-verify", remote, f"{commit}:refs/submit/{operator}/{unit}", cwd=repo)
    return unit


# ---- promotion (admin side) ------------------------------------------------
def promote(state, commit, fixtures=None, accept_diff=None, repo=None):
    """Make the checker at `commit` current. Returns (ok, report dict)."""
    state = state if isinstance(state, State) else State(state)
    repo = repo or GitRepo(state)
    head = repo.head()
    if git("cat-file", "-e", f"{commit}^{{commit}}", cwd=repo.dir, check=False).returncode:
        git("fetch", "-q", "--no-tags", "target", "+refs/heads/*:refs/publisher/target/*",
            cwd=repo.dir)
    digest = Checkers(state).materialize(repo.dir, commit)
    old = Checkers(state).current()
    builder = Builder(state, "promote")
    report = dict(digest=digest, commit=commit, head=head, fixtures=[], ledger=None)
    ok = True
    manifest = read_json(Path(fixtures) / "fixtures.json", []) if fixtures else []
    for fixture in manifest:           # [{"patch": "x.patch", "expect": "reject"|"pass"}]
        tip, bad = repo.compose(head, [("fixture", Path(fixtures) / fixture["patch"])])
        if bad:
            verdict = "does-not-apply"
        else:
            code, _ = builder.run(head, tip, digest)
            verdict = "pass" if code == 0 else "reject"
        good = verdict == fixture["expect"]
        ok &= good
        report["fixtures"].append(dict(fixture, got=verdict, ok=good))
    if state.cfg.get("ledger_cmd"):
        outputs = {}
        for name, which in (("old", old), ("new", digest)):
            if which:
                code, text = builder.run(head, head, which, command=state.cfg["ledger_cmd"])
                outputs[name] = set(text.decode(errors="replace").splitlines())
        added = sorted(outputs["new"] - outputs.get("old", outputs["new"]))
        removed = sorted(outputs.get("old", outputs["new"]) - outputs["new"])
        diff = [f"+ {line}" for line in added] + [f"- {line}" for line in removed]
        accepted = set(Path(accept_diff).read_text(encoding="utf-8").splitlines()) if accept_diff else set()
        unaccepted = [line for line in diff if line not in accepted]
        report["ledger"] = dict(added=len(added), removed=len(removed), unaccepted=unaccepted[:50],
                                diff_sha256=hashlib.sha256("\n".join(diff).encode()).hexdigest())
        ok &= not unaccepted
    if ok:
        Checkers(state).record(digest, commit, report)
        state.event("promoted", digest=digest, commit=commit)
    return ok, report


# ---- command line ----------------------------------------------------------
def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = ap.add_subparsers(dest="action", required=True)
    p = sub.add_parser("init")
    p.add_argument("--state", required=True)
    p.add_argument("--target", required=True)
    p.add_argument("--set", action="append", default=[], metavar="KEY=JSON")
    p = sub.add_parser("operator", help="add an operator; writes its key file")
    p.add_argument("--state", required=True)
    p.add_argument("name")
    p.add_argument("--rate", type=float, default=60)
    p.add_argument("--burst", type=float, default=20)
    p.add_argument("--infra", action="store_true")
    p = sub.add_parser("promote")
    p.add_argument("--state", required=True)
    p.add_argument("commit")
    p.add_argument("--fixtures")
    p.add_argument("--accept-diff")
    p = sub.add_parser("submit")
    p.add_argument("rev", nargs="?", default="@{u}..HEAD")
    p.add_argument("--operator", required=True)
    p.add_argument("--key-file", required=True)
    p.add_argument("--inbox")
    p.add_argument("--remote")
    p.add_argument("--kind", default="normal", choices=("normal", "infra", "wide"))
    p.add_argument("--after", action="append", default=[])
    p.add_argument("--bundle")
    p.add_argument("--priority", type=float, default=0)
    p = sub.add_parser("build", help="(internal) one isolated build; run by the executor")
    for flag in ("--state", "--slot", "--base", "--tip", "--checker"):
        p.add_argument(flag, required=True)
    p = sub.add_parser("drain")
    p.add_argument("--state", required=True)
    p.add_argument("--once", action="store_true")
    p = sub.add_parser("status")
    p.add_argument("--state", required=True)
    args = ap.parse_args(argv)

    if args.action == "init":
        root = Path(args.state)
        root.mkdir(parents=True, exist_ok=True)
        cfg = read_json(root / "config.json", {}) or {}
        cfg["target"] = args.target
        for item in args.set:
            k, v = item.split("=", 1)
            cfg[k] = json.loads(v)
        write_json(root / "config.json", cfg)
        if not (root / "receipt.key").exists():
            new_key(root / "receipt.key")
        State(root)
        return 0
    if args.action == "operator":
        root = Path(args.state)
        cfg = read_json(root / "config.json", {})
        key = new_key(root / "operators" / f"{args.name}.key")
        cfg.setdefault("operators", {})[args.name] = dict(key_file=f"operators/{args.name}.key",
                                                          rate=args.rate, burst=args.burst,
                                                          infra=args.infra)
        write_json(root / "config.json", cfg)
        print(key)              # hand THIS file to the operator's fleet host, nothing else
        return 0
    if args.action == "promote":
        ok, report = promote(args.state, args.commit, args.fixtures, args.accept_diff)
        print(json.dumps(report, indent=1))
        return 0 if ok else 1
    if args.action == "submit":
        print(submit(Path.cwd(), args.operator, args.key_file, args.rev, args.inbox, args.remote,
                     args.kind, args.after, args.bundle, args.priority))
        return 0
    if args.action == "build":
        receipt = Builder(State(args.state), args.slot).build(args.base, args.tip, args.checker)
        print(receipt["verdict"])
        return 0
    if args.action == "drain":
        print(json.dumps(drain(Publisher(args.state), once=args.once), indent=1))
        return 0
    if args.action == "status":
        state = State(args.state)
        pub = Publisher(state, repo=_OfflineRepo(), executor=ProcessExecutor(state), offline=True)
        print(json.dumps(pub.status(), indent=1))
        return 0
    return 2


class _OfflineRepo:
    """`status` reads local state only; it never talks to the target."""
    def head(self):
        return None


if __name__ == "__main__":
    sys.exit(main())
