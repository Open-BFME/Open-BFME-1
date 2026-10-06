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
  SCOPE      Every unit declares the path globs it may touch (`scope.allow`,
             optional `scope.forbid`; `**` crosses directories). No path is
             exempt: shared ledgers (functions.csv, symbols.csv,
             data_rows.csv, baselines), headers, build files, tools/ and
             .githooks/ are scope like any other. Two units whose scopes
             overlap (a path one touches is inside the other's scope, or the
             same glob) are never in flight together: the later one waits,
             it is not rejected. Row ledgers (`row_ledgers`: functions.csv
             by target_rva, symbols.csv by name, data_rows.csv by address,
             other union-merged ledgers by whole line) are scoped by row:
             `targets/game/reverse/functions.csv#0x00401000` allows and
             overlaps that row only; a plain path allows the whole file.
             A unit's rows are read from its diff with the ledger's header.
             A unit touching a file that others #include (by file name,
             transitively, as header_dependents.py does; `#include MACRO`
             counts as including everything) also overlaps every unit that
             touches one of those includers. After the rebase each unit's own diff must
             stay inside its scope, or it is rejected with the offending
             paths (`out-of-scope`).
  RETRIES    A gate-red unit is fingerprinted: its +/- lines outside
             `ledger_paths` plus its target (its non-ledger scope globs).
             After `retry_limit` (3) equivalent failures for one target, an
             equivalent submission is refused (`retry-limit`) until the
             target's inputs change: the blobs its scope covers at the head,
             or the promoted checker.
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
  python3 tools/publisher.py submit --operator NAME --key-file F (--inbox DIR | --remote URL)
          (--scope GLOB ... [--forbid GLOB ...] | --scope-from-diff) [RANGE]
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
    scope_required=True, serialize_scopes=True, retry_limit=3,
    builders_registry={}, stage_remote=None, reverify_share=0.1, reverify_red=True,
    reverify_high_risk=True,
    high_risk=["**/*.h", "**/*.hpp", "**/*.hh", "**/*.hxx", "**/*.inl", "**/*.inc",
               "**/*baseline*", "**/*_known_red.txt", "**/*whitelist*", "**/gen_asm/**",
               "**/gen_small/**"],
    row_ledgers={"**/functions.csv": "target_rva", "**/symbols.csv": "name",
                 "**/data_rows.csv": "address", "**/deleted_rows.csv": "",
                 "**/name_votes.csv": "", "**/name_agreed.csv": "", "**/re_attempts.log": "",
                 "**/attempts.jsonl": ""},
    include_globs=["*.h", "*.hpp", "*.hh", "*.hxx", "*.inl", "*.inc", "*.cpp", "*.c", "*.cc",
                   "*.cxx", "*.def", "*.tbl"],
    include_scan_seconds=120, reach_limit=3000,
    # STLport's `#include _STLP_NATIVE_HEADER(x)` redirects reach only toolchain
    # headers; header_dependents sends STLport changes to the full gate anyway
    macro_include_ignore=["**/stlport/**"],
    ledger_paths=["**/functions.csv", "**/symbols.csv", "**/data_rows.csv", "**/*baseline*",
                  "**/*_known_red.txt", "**/*whitelist*"],
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


_GLOBS = {}


def glob_match(path, pattern):
    """fnmatch for repository paths: `*` and `?` stay inside one directory,
    `**` crosses directories (`a/**/b` also matches `a/b`)."""
    rx = _GLOBS.get(pattern)
    if rx is None:
        out, i = [], 0
        while i < len(pattern):
            if pattern.startswith("**/", i):
                out.append("(?:.*/)?")
                i += 3
            elif pattern.startswith("**", i):
                out.append(".*")
                i += 2
            elif pattern[i] == "*":
                out.append("[^/]*")
                i += 1
            elif pattern[i] == "?":
                out.append("[^/]")
                i += 1
            else:
                out.append(re.escape(pattern[i]))
                i += 1
        rx = _GLOBS[pattern] = re.compile("".join(out) + r"\Z")
    return rx.match(path) is not None


def _entry(entry):
    """'path-glob' -> (glob, None); 'path-glob#KEY' -> (glob, KEY)."""
    glob, _, key = entry.partition("#")
    return glob, (key or None)


def _forbidden(scope, path, key):
    return any(glob_match(path, g) and (k is None or k == key)
               for g, k in map(_entry, scope.get("forbid") or ()))


def in_scope(path, scope, key=None):
    """May a unit with `scope` change `path` (row `key` of a row ledger; None
    = the whole file)? A row token allows only its own row."""
    return (any(glob_match(path, g) and (k is None or (key is not None and k == key))
                for g, k in map(_entry, scope.get("allow") or ()))
            and not _forbidden(scope, path, key))


def scope_touches(scope, path, key=None):
    """Could a unit with `scope` touch what (path, key) touches? key None means
    the whole file, which every row token of that file touches."""
    return (any(glob_match(path, g) and (k is None or key is None or k == key)
                for g, k in map(_entry, scope.get("allow") or ()))
            and not _forbidden(scope, path, key))


def footprint(record):
    """{(path, row key or None)} a unit's diff touches."""
    rows = record.get("rows") or {}
    items = set()
    for path in record.get("paths") or ():
        keys = rows.get(path)
        if keys and "*" not in keys:
            items.update((path, k) for k in keys)
        else:
            items.add((path, None))
    return items


def scopes_overlap(a, b):
    """Records a, b (scope, paths, rows, reach) may not be in flight together."""
    sa, sb = a.get("scope"), b.get("scope")
    if not sa or not sb:
        return True                         # an unscoped unit may touch anything
    if set(sa["allow"]) & set(sb["allow"]):
        return True
    fa, fb = footprint(a), footprint(b)
    literal = lambda s: {_entry(g) for g in s["allow"] if not set(_entry(g)[0]) & set("*?[")}  # noqa: E731
    ra, rb = set(a.get("reach") or ()), set(b.get("reach") or ())
    plain = lambda f: {p for p, k in f if k is None}  # noqa: E731
    if ("*" in ra and (plain(fb) or rb)) or ("*" in rb and (plain(fa) or ra)):
        return True                         # a header included nearly everywhere
    if ra & (rb | plain(fb)) or rb & plain(fa):
        return True                         # one edits what the other's TUs include
    return (any(scope_touches(sb, p, k) for p, k in fa | literal(sa) | {(r, None) for r in ra})
            or any(scope_touches(sa, p, k) for p, k in fb | literal(sb) | {(r, None) for r in rb}))


def row_ledger(path, ledgers):
    """The key column of a row ledger ('' = the whole line), None otherwise."""
    for glob, column in ledgers.items():
        if glob_match(path, glob):
            return column
    return None


def _norm_key(value):
    value = value.strip()
    try:
        if value.lower().startswith("0x"):
            return f"0x{int(value, 16):08X}"
    except ValueError:
        pass
    return value


def ledger_rows(diff, ledgers, header_of=None):
    """{ledger path: {row keys}} that a diff adds, changes or deletes. A key is
    the ledger's key column (RVAs normalised), or 'L<hash>' of the whole line
    for line ledgers and rows it cannot read; '*' = the header changed."""
    import csv
    rows, path, column, header = {}, None, None, None
    for raw in diff.split(b"\n"):
        got = re.match(rb"^diff --git a/\S+ b/(\S+)$", raw)
        if got:
            path = got.group(1).decode(errors="replace")
            column = row_ledger(path, ledgers)
            header = header_of(path) if (column and header_of) else None
            continue
        if re.match(rb"^From [0-9a-f]{40} ", raw) or raw == b"-- ":
            path = column = header = None       # the next commit's message, or the signature
            continue
        if column is None or raw[:1] not in (b"+", b"-") or raw.startswith((b"+++ ", b"--- ")):
            continue
        text = raw[1:].rstrip(b"\r").decode(errors="replace")
        keys = rows.setdefault(path, set())
        if header is not None and text == header:
            keys.add("*")
            continue
        key = None
        if column and header:
            names = next(csv.reader([header]))
            if column in names:
                try:
                    cells = next(csv.reader([text]))
                    if len(cells) > names.index(column) and cells[names.index(column)].strip():
                        key = _norm_key(cells[names.index(column)])
                except (csv.Error, StopIteration):
                    key = None
        keys.add(key or "L" + hashlib.sha1(text.encode()).hexdigest()[:12])
    return {p: sorted(k) for p, k in rows.items()}


def scan_includes(cwd, rev, globs):
    """({included file name, lower case: {paths}}, {paths with `#include MACRO`})
    of every #include in `rev`, read with one git grep."""
    by_name, macro = {}, set()
    got = git("grep", "-I", "-i", "-E", r"^[[:space:]]*#[[:space:]]*include", rev, "--", *globs,
              cwd=cwd, check=False, timeout=600)
    for line in got.stdout.decode(errors="replace").splitlines():
        _, path, text = (line.split(":", 2) + ["", ""])[:3]
        hit = re.search(r'include\s*[<"]([^>"]+)[>"]', text, re.IGNORECASE)
        if hit:
            by_name.setdefault(hit.group(1).replace("\\", "/").rsplit("/", 1)[-1].lower(),
                               set()).add(path)
        elif re.search(r"include\s*[A-Za-z_]", text):
            macro.add(path)
    return by_name, macro


def reach_of(paths, graph, cfg):
    """Every file that #includes one of `paths`, transitively by file name;
    ['*'] past reach_limit."""
    by_name, macro = graph
    macro = {m for m in macro if not any(glob_match(m, g) for g in cfg["macro_include_ignore"])}
    frontier = {p.rsplit("/", 1)[-1].lower() for p in paths
                if row_ledger(p, cfg["row_ledgers"]) is None}
    if not any(name in by_name for name in frontier):
        return []
    seen, names = set(), set()
    while frontier:
        name = frontier.pop()
        names.add(name)
        # a file with `#include MACRO` may include anything (header_dependents' rule)
        for path in set(by_name.get(name, ())) | macro:
            if path not in seen:
                seen.add(path)
                base = path.rsplit("/", 1)[-1].lower()
                if base not in names:
                    frontier.add(base)
        if len(seen) > int(cfg["reach_limit"]):
            return ["*"]
    return sorted(seen - set(paths))


def scope_from_diff(diff, ledgers, header_of=None):
    """The exact scope of a diff: its paths, row ledgers as row tokens."""
    rows = ledger_rows(diff, ledgers, header_of)
    out = []
    for path in patch_paths(diff):
        keys = rows.get(path)
        if keys and "*" not in keys:
            out += [f"{path}#{k}" for k in keys]
        else:
            out.append(path)
    return out


def patch_paths(patch):
    return sorted({m.decode(errors="replace") for m in
                   re.findall(rb"^diff --git a/\S+ b/(\S+)$", patch, re.MULTILINE)} |
                  {m.decode(errors="replace") for m in
                   re.findall(rb"^diff --git a/(\S+) b/\S+$", patch, re.MULTILINE)})


def target_globs(scope, ledger):
    """A unit's target: its scope without whole-file ledger globs (row tokens
    stay: they name the rows it is about)."""
    return [g for g in (scope or {}).get("allow") or ()
            if "#" in g or not any(glob_match(g, l) for l in ledger)]


def approach(patch, scope, ledger):
    """(target, fingerprint) of a unit: the target is its scope without ledger
    globs; the fingerprint hashes its +/- lines outside ledger files (no
    headers, messages, hashes or line numbers) with the target."""
    target = hashlib.sha256(canonical(sorted(target_globs(scope, ledger)))).hexdigest()[:16]
    lines, keep = [], False
    for line in patch.split(b"\n"):
        line = line.rstrip(b"\r")
        got = re.match(rb"^diff --git a/\S+ b/(\S+)$", line)
        if got:
            path = got.group(1).decode(errors="replace")
            keep = not any(glob_match(path, l) for l in ledger)
            if keep:
                lines.append(b"F " + got.group(1))
        elif re.match(rb"^From [0-9a-f]{40} ", line) or line == b"-- ":
            keep = False                        # next commit's headers, or the signature
        elif keep and line[:1] in (b"+", b"-") and not line.startswith((b"+++ ", b"--- ")):
            lines.append(line.rstrip())
    return target, hashlib.sha256(b"\n".join(lines) + b"\0" + target.encode()).hexdigest()[:24]


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

    def key_path(self, path):
        path = Path(path)
        return path if path.is_absolute() else self.root / path

    def registry(self):
        """{builder id: {operator, key_file, command?, home?, builder_key?, slots?}}.
        Without `builders_registry`, `builders` local builders of operator
        "local" (fine for one host; re-verification needs a second operator)."""
        registry = dict(self.cfg.get("builders_registry") or {})
        if not registry:
            for i in range(int(self.cfg["builders"])):
                key = self.root / "builders" / f"local{i}.key"
                if not key.exists():
                    new_key(key)
                registry[f"local{i}"] = dict(operator="local", key_file=str(key))
        return registry

    def builder_key(self, builder):
        entry = self.registry().get(builder) if isinstance(builder, str) else None
        return read_key(self.key_path(entry["key_file"])) if entry else None

    def quarantined(self):
        return read_json(self.root / "quarantine.json", {}) or {}

    def quarantine(self, builder, reason, **evidence):
        found = self.quarantined()
        if builder and builder not in found:
            found[builder] = dict(evidence, reason=reason, time=time.time())
            write_json(self.root / "quarantine.json", found)
            self.event("builder_quarantined", builder=builder, reason=reason)

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
        # byte-exact blobs whatever the host's core.autocrlf: the digest must
        # come out the same on every builder
        _extract(git("-c", "core.autocrlf=false", "archive", "--format=tar", commit, "--", *paths,
                     cwd=repo).stdout, tmp)
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
def _extract(data, dest):
    with tarfile.open(fileobj=io.BytesIO(data)) as tar:
        try:
            tar.extractall(dest, filter="data")
        except TypeError:                       # Python < 3.11.4: no extraction filters
            tar.extractall(dest)


class Builder:
    """One build slot on one host. It knows only its home, its id and its own
    registered key; the job (source URL, refs, checker digest, gate) comes
    from the publisher. Its clone has no remote; a local source lends its
    objects (alternates), a remote one is fetched. The checker bundle is
    extracted from the promoted commit and must hash to the digest."""

    def __init__(self, home, builder_id, key):
        self.home, self.id, self.key = Path(home), builder_id, key
        self.home.mkdir(parents=True, exist_ok=True)
        self.work = self.home / "wt"
        self.env = scrubbed_env(self.home / "home")

    def _git(self, *args, **kw):
        return git(*args, cwd=self.work, env=self.env, **kw)

    def fetch(self, source, refs):
        if not (self.work / ".git").exists():
            self.work.mkdir(parents=True, exist_ok=True)
            git("init", "-q", str(self.work), cwd=self.home, env=self.env)
            # the scrubbed environment drops the host's global config, and with
            # it core.longpaths: deep reference trees fail to check out on Windows
            self._git("config", "core.longpaths", "true")
        local = Path(source)
        if local.is_dir():                      # same host: borrow its objects, copy nothing
            objects = local / ".git" / "objects" if (local / ".git").is_dir() else local / "objects"
            (self.work / ".git" / "objects" / "info").mkdir(parents=True, exist_ok=True)
            # bytes: a text-mode write on Windows ends the path in \r, which git
            # rejects -- and then fetches (copies) every object instead
            (self.work / ".git" / "objects" / "info" / "alternates").write_bytes(
                objects.resolve().as_posix().encode() + b"\n")
        self._git("fetch", "-q", "--no-tags", str(source), *refs, timeout=3600)

    def bundle(self, job):
        digest = job["checker"]
        where = self.home / "checkers" / digest
        if where.is_dir() and tree_digest(where) == digest:
            return where
        self.fetch(job["source"], [f"+{job['checker_ref']}:refs/builder/checker"])
        have = [p for p in job["checker_paths"] if self._git(
            "cat-file", "-e", f"refs/builder/checker:{p}", check=False).returncode == 0]
        tmp = self.home / "checkers" / f"tmp-{uuid.uuid4().hex}"
        _extract(self._git("-c", "core.autocrlf=false", "archive", "--format=tar",
                           "refs/builder/checker", "--", *have).stdout, tmp)
        if tree_digest(tmp) != digest:
            shutil.rmtree(tmp)
            raise RuntimeError(f"{job['checker_ref']} does not hash to checker {digest[:12]}")
        if where.exists():
            shutil.rmtree(where)
        os.replace(tmp, where)
        return where

    def checkout(self, job):
        tip = job["tip"]
        self.fetch(job["source"], [f"+{job['tip_ref']}:refs/builder/tip"])
        if self._git("rev-parse", "refs/builder/tip").stdout.decode().strip() != tip:
            raise RuntimeError(f"{job['tip_ref']} is not {tip}")
        bundle = self.bundle(job)
        (self.work / ".git" / "index").unlink(missing_ok=True)   # drops old skip-worktree bits
        self._git("update-ref", "--no-deref", "HEAD", tip)
        self._git("reset", "-q", "--hard", tip)
        keep = [a for k in job.get("clean_keep") or () for a in ("-e", k)]
        self._git("clean", "-qfdx", *keep)
        paths = job["checker_paths"]
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

    def toolchain(self, job):
        found = {}
        for rel in job.get("toolchain_paths") or ():
            got = self._git("rev-parse", f"{job['tip']}:{rel}", check=False)
            found[rel] = got.stdout.decode().strip() if got.returncode == 0 else None
        found["python"] = hashlib.sha256(Path(sys.executable).read_bytes()).hexdigest()
        found["git"] = out("--version", cwd=self.home)
        return found

    def run(self, job, command=None):
        """(exit code, output) of `command` (default: the job's gate) at the tip."""
        bundle = self.checkout(job)
        env = dict(self.env, LANDING_BASE=job["base"], LANDING_TIP=job["tip"],
                   CHECKER_DIR=bundle.as_posix(), CHECKER_DIGEST=job["checker"])
        try:
            got = subprocess.run(["bash", "-c", command or job["gate"]], cwd=self.work, env=env,
                                 stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                                 timeout=float(job.get("gate_timeout") or 6 * 3600))
            code, output = got.returncode, got.stdout or b""
        except subprocess.TimeoutExpired as error:
            code, output = 124, (error.stdout or b"") + b"\n[publisher] gate timed out\n"
        if tree_digest(bundle) != job["checker"]:
            raise RuntimeError("the checker bundle changed during the gate")
        return code, output

    def build(self, job):
        """(signed receipt, gate output)."""
        started = time.time()
        code, output = self.run(job)
        result = re.findall(rb"^PUBLISHER-RESULT: (\S+)", output, re.MULTILINE)
        receipt = dict(v=2, tip=job["tip"], base=job["base"],
                       tree=self._git("rev-parse", f"{job['tip']}^{{tree}}").stdout.decode().strip(),
                       checker=job["checker"], toolchain=self.toolchain(job),
                       verdict="green" if code == 0 else "red", exit=code,
                       result=result[-1].decode() if result else None,
                       log_sha256=hashlib.sha256(output).hexdigest(), builder=self.id,
                       blame=sorted(set(m.decode(errors="replace").strip() for m in re.findall(
                           rb"^PUBLISHER-BLAME: (.+)$", output, re.MULTILINE)))[:200],
                       host=socket.gethostname(), started=started,
                       seconds=round(time.time() - started, 2))
        return signed(self.key, receipt), output


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


class PoolExecutor:
    """Runs builds on the registered builders (config `builders_registry`):
    each is `<command> builder-run --home H --id ID --key K` on its own host
    (a local process by default, `ssh host python3 .../publisher.py` for a
    remote one), with the job on stdin and the signed receipt on stdout.
    Quarantined builders get no jobs; a job may exclude operators, which is
    how re-verification lands on another operator's builder."""

    def __init__(self, state):
        self.state = state
        self.registry = state.registry()
        self.slots = [(bid, i) for bid, b in sorted(self.registry.items())
                      for i in range(int(b.get("slots", 1)))]
        self.n = len(self.slots)
        self.free = list(self.slots)
        self.waiting = collections.deque()
        self.lock = threading.Lock()
        self.wake = threading.Event()

    def operator_of(self, builder):
        return (self.registry.get(builder) or {}).get("operator")

    def builder_of(self, job):
        return job["slot"][0] if job and job.get("slot") else None

    def _eligible(self, slot, job):
        return (self.operator_of(slot[0]) not in job["exclude"] and slot[0] not in job["avoid"]
                and slot[0] not in self.state.quarantined())

    def submit(self, base, tip, digest, units, spec=None, exclude_operators=(), avoid=()):
        job = dict(base=base, tip=tip, digest=digest, units=list(units), spec=spec or {},
                   exclude=set(exclude_operators), avoid=set(avoid), result=None, proc=None,
                   cancelled=False, slot=None)
        if not any(self._eligible(slot, job) for slot in self.slots):
            return None                         # nobody may run it: the caller holds the batch
        with self.lock:
            self.waiting.append(job)
        self._start()
        return job

    def _start(self):
        with self.lock:
            for job in list(self.waiting):
                slot = next((sl for sl in self.free if self._eligible(sl, job)), None)
                if slot is None:
                    continue
                self.waiting.remove(job)
                self.free.remove(slot)
                job["slot"] = slot
                threading.Thread(target=self._run, args=(job,), daemon=True).start()

    def _run(self, job):
        bid, index = job["slot"]
        entry = self.registry[bid]
        command = entry.get("command") or [sys.executable, str(Path(__file__).resolve())]
        home = entry.get("home") or str(self.state.root / "builders" / bid)
        key = entry.get("builder_key") or str(self.state.key_path(entry["key_file"]))
        argv = [*command, "builder-run", "--home", f"{home}/slot{index}", "--id", bid, "--key", key]
        env = scrubbed_env(self.state.root / "builders" / bid / "env")
        try:
            with self.lock:
                if job["cancelled"]:
                    return
                job["proc"] = subprocess.Popen(argv, env=env, stdin=subprocess.PIPE,
                                               stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                                               start_new_session=os.name != "nt")
            got, err = job["proc"].communicate(canonical(job["spec"]))
            if job["cancelled"]:
                return
            try:
                answer = json.loads(got.decode(errors="replace").strip().splitlines()[-1])
                (self.state.root / "logs" / f"{job['tip']}.{bid}.log").write_text(
                    answer.get("log", ""), encoding="utf-8")
                job["result"] = answer["receipt"]
            except (ValueError, IndexError, KeyError):
                job["result"] = dict(verdict="error", builder=bid,
                                     error=(err or got).decode(errors="replace")[-2000:])
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


ProcessExecutor = PoolExecutor


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
        self._head = sha or getattr(self, "_head", None)
        if sha and git("cat-file", "-e", f"{sha}^{{commit}}", cwd=self.dir, check=False).returncode:
            git("fetch", "-q", "--no-tags", "target",
                f"+refs/heads/{self.branch}:refs/publisher/head", cwd=self.dir)
        return sha

    def compose(self, base, patches):
        """(tip, None) after `git am` of every patch on base, or (None, unit id)."""
        git("am", "--abort", cwd=self.dir, check=False)
        git("checkout", "-q", "-f", "--detach", base, cwd=self.dir)
        git("clean", "-qfd", cwd=self.dir)
        self.unit_paths, self.unit_diffs = {}, {}
        for unit, patch in patches:
            before = out("rev-parse", "HEAD", cwd=self.dir)
            got = git("-c", f"user.name={COMMITTER}", "-c", "user.email=", "am", "-q", "-3",
                      "--keep-cr", "--committer-date-is-author-date", str(patch),
                      cwd=self.dir, env=self.env, check=False)
            if got.returncode:
                git("am", "--abort", cwd=self.dir, check=False)
                return None, unit
            # the unit's own diff as rebased: what diff-vs-scope judges
            diff = git("diff", "--no-renames", "-U0", "--binary", before, "HEAD",
                       cwd=self.dir).stdout
            self.unit_diffs[unit] = diff
            self.unit_paths[unit] = patch_paths(diff)
        tip = out("rev-parse", "HEAD", cwd=self.dir)
        git("update-ref", f"refs/publisher/tips/{tip}", tip, cwd=self.dir)   # keep it reachable
        return tip, None

    def tree(self, tip):
        return out("rev-parse", f"{tip}^{{tree}}", cwd=self.dir)

    def job(self, base, tip, digest):
        """What a builder needs: where to fetch the tip and the checker, and
        the gate. A remote builder fetches from `stage_remote`, where the
        publisher stages both refs; a local one borrows this clone's objects."""
        cfg = self.state.cfg
        git("update-ref", f"refs/publisher/tips/{tip}", tip, cwd=self.dir)
        checker_ref = f"refs/publisher/checkers/{digest}"
        if git("rev-parse", "-q", "--verify", checker_ref, cwd=self.dir, check=False).returncode:
            history = Checkers(self.state).index()["history"]
            commit = next((h["commit"] for h in reversed(history) if h["digest"] == digest), None)
            if commit is None:
                raise RuntimeError(f"no promoted commit for checker {digest[:12]}")
            git("update-ref", checker_ref, commit, cwd=self.dir)
        source, tip_ref = str(self.dir), f"refs/publisher/tips/{tip}"
        if cfg.get("stage_remote"):
            staged = self.__dict__.setdefault("_staged", set())
            if tip not in staged:
                git("push", "-q", cfg["stage_remote"], f"{tip}:refs/publisher/candidates/{tip}",
                    f"{checker_ref}:{checker_ref}", cwd=self.dir)
                staged.add(tip)
            source, tip_ref = cfg["stage_remote"], f"refs/publisher/candidates/{tip}"
        return dict(source=source, tip_ref=tip_ref, tip=tip, base=base, checker=digest,
                    checker_ref=checker_ref, checker_paths=cfg["checker_paths"], gate=cfg["gate"],
                    toolchain_paths=cfg["toolchain_paths"], clean_keep=cfg["clean_keep"],
                    gate_timeout=cfg["gate_timeout"])

    def ledger_header(self, path):
        """First line of a ledger at the last head read (cached per path)."""
        cache = self.__dict__.setdefault("_headers", {})
        if not getattr(self, "_head", None):
            self.head()
        if path not in cache and getattr(self, "_head", None):
            got = git("show", f"{self._head}:{path}", cwd=self.dir, check=False)
            cache[path] = (got.stdout.split(b"\n", 1)[0].rstrip(b"\r").decode(errors="replace")
                           if got.returncode == 0 else None)
        return cache.get(path)

    def includers(self):
        """({included file name (lower case): {paths including it}}, {paths
        with a macro include}) at the last head; rescanned at most every
        include_scan_seconds (stale edges only under-serialize: every batch
        is still gated on its exact base)."""
        cached = getattr(self, "_includes", None)
        head = getattr(self, "_head", None) or self.head()
        if cached and (cached[0] == head or
                       time.time() - cached[1] < float(self.state.cfg["include_scan_seconds"])):
            return cached[2]
        graph = scan_includes(self.dir, head, self.state.cfg["include_globs"]) if head else ({}, set())
        self._includes = (head, time.time(), graph)
        return graph

    def inputs_digest(self, head, scope):
        """sha256 over the blobs at `head` that `scope` covers."""
        if getattr(self, "_listed", (None,))[0] != head:
            listing = out("ls-tree", "-r", "--full-tree", head, cwd=self.dir).splitlines()
            self._listed = (head, [line.split("\t", 1)[::-1] for line in listing])
        h = hashlib.sha256()
        for path, meta in self._listed[1]:
            if in_scope(path, scope):
                h.update(f"{path} {meta.split()[2]}\n".encode())
        return h.hexdigest()

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
        serialize = self.state.cfg.get("serialize_scopes", True)
        active = [records[u] for u in exclude if u in records]      # in flight now

        def clear(key):
            """No unit of `key` overlaps a unit in flight or already chosen."""
            if not serialize:
                return True
            others = active + [recs[u] for u in chosen]
            return not any(scopes_overlap(recs[u], o) for u in groups[key] for o in others)

        def ready(key, chosen):
            if not clear(key):
                return False
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
        self.checks, self.check_jobs = [], []     # re-verification receipts and jobs
        self.unavailable = False

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
        self.stats = dict(gates=0, reused=0, batches=0, red_batches=0, checks=0)
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
        scope = envelope.get("scope")
        if scope is not None:
            allow, forbid = scope.get("allow"), scope.get("forbid") or []
            if (not isinstance(allow, list) or not allow or not isinstance(forbid, list)
                    or any(not isinstance(g, str) or not g or g.startswith("/") or ".." in g.split("/")
                           for g in allow + forbid)):
                return None, "bad-scope"
            scope = dict(allow=list(allow), forbid=list(forbid))
        elif self.cfg.get("scope_required", True):
            return None, "no-scope"
        target, fingerprint = approach(patch, scope, self.cfg["ledger_paths"])
        if self._retry_refused(target, fingerprint, scope):
            return None, "retry-limit"
        kind = envelope.get("kind") or "normal"
        if kind == "infra" and not self.cfg["operators"][op].get("infra"):
            kind = "normal"                          # only infra-flagged operators get the reserve
        record = dict(id=unit, operator=op, kind=kind if kind in ("normal", "infra", "wide") else "normal",
                      after=[str(a) for a in envelope.get("after") or ()],
                      bundle=envelope.get("bundle"), priority=envelope.get("priority") or 0,
                      submitted=envelope.get("time"), enqueued=self.clock(),
                      commits=patch.count(b"\nFrom ") + patch.startswith(b"From "),
                      paths=patch_paths(patch), scope=scope, target=target,
                      fingerprint=fingerprint,
                      rows=ledger_rows(patch, self.cfg["row_ledgers"],
                                       getattr(self.repo, "ledger_header", None)),
                      reach=self._reach(patch_paths(patch)),
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
        if verdict == "red" and record.get("fingerprint"):
            self._retry_failed(record, extra.get("base"))
        self.event(where, unit=unit, operator=record["operator"], reason=extra.get("reason"),
                   wait=round(now - record["enqueued"], 1))

    def _reach(self, paths):
        if not hasattr(self.repo, "includers"):
            return []
        return reach_of(paths, self.repo.includers(), self.cfg)

    # ---- retry accounting -----------------------------------------------
    def _target_inputs(self, scope, head=None):
        """The checker plus the blobs the target's non-ledger globs cover at
        head; ledger files change on nearly every commit, so they are not
        inputs (row tokens name the target instead)."""
        head = head or self.head or self.repo.head()
        if not scope or not head or not hasattr(self.repo, "inputs_digest"):
            return None
        globs = [g for g in target_globs(scope, self.cfg["ledger_paths"]) if "#" not in g]
        digest = self.repo.inputs_digest(head, dict(allow=globs)) if globs else "-"
        return f"{self.checkers.current()}:{digest}"

    def _retry_failed(self, record, base):
        path = self.state.root / "retries.json"
        retries = read_json(path, {}) or {}
        inputs = self._target_inputs(record.get("scope"), base)
        entry = retries.get(record["target"])
        if not entry or entry.get("inputs") != inputs:
            entry = retries[record["target"]] = dict(inputs=inputs, failures={})
        entry["failures"][record["fingerprint"]] = entry["failures"].get(record["fingerprint"], 0) + 1
        write_json(path, retries)

    def _retry_refused(self, target, fingerprint, scope):
        entry = (read_json(self.state.root / "retries.json", {}) or {}).get(target)
        if not entry or entry["failures"].get(fingerprint, 0) < int(self.cfg["retry_limit"]):
            return False
        return entry.get("inputs") == self._target_inputs(scope)   # changed inputs: try again

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
        key = self.state.builder_key((receipt or {}).get("builder"))
        if not receipt or key is None or not verify_mac(key, receipt):
            return "bad-mac"
        if receipt["builder"] in self.state.quarantined():
            return "quarantined-builder"
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
        if not self.repo.publish(batch.tip):
            # the branch moved (another publisher won the compare-and-swap):
            # nothing is published, the batch is regated on the new head
            self.event("publish_refused", tip=batch.tip, base=batch.base)
        self._crash("after_push")
        return self._settle()

    # ---- the pipeline ---------------------------------------------------
    def _flush(self, start=0):
        for batch in self.inflight[start:]:
            if batch.job is not None:
                self.executor.cancel(batch.job)
            for job in batch.check_jobs:
                self.executor.cancel(job)
        del self.inflight[start:]

    def _dispatch(self, batch, digest):
        self.stats["batches"] += 1
        path = receipt_path(self.state, batch.tip, batch.base, digest)
        cached = read_json(path)
        if cached and self._authentic(cached, batch, digest):
            batch.receipt = cached                  # exact tip already gated: reuse
            self.stats["reused"] += 1
        else:
            self.stats["gates"] += 1
            batch.job = self.executor.submit(batch.base, batch.tip, digest, batch.units,
                                             self._spec(batch, digest))
        self.inflight.append(batch)
        self.event("batch", tip=batch.tip, base=batch.base, units=len(batch.units),
                   reused=batch.receipt is not None, depth=len(self.inflight))

    def _spec(self, batch, digest):
        return self.repo.job(batch.base, batch.tip, digest) if hasattr(self.repo, "job") else {}

    def _authentic(self, receipt, batch, digest, job=None):
        """Signed by the registered, unquarantined builder that ran it, for
        exactly this tip, base and checker."""
        builder = receipt.get("builder")
        key = self.state.builder_key(builder)
        return (key is not None and verify_mac(key, receipt)
                and builder not in self.state.quarantined()
                and (job is None or builder == self.executor.builder_of(job))
                and receipt.get("tip") == batch.tip and receipt.get("base") == batch.base
                and receipt.get("checker") == digest)

    def _poll(self, batch, digest):
        """Collect a batch's receipt; a forged or misattributed one
        quarantines the builder that returned it and the batch regates."""
        if batch.receipt is not None or batch.job is None:
            return
        got = self.executor.poll(batch.job)
        if got is None:
            return
        if got.get("verdict") != "error" and not self._authentic(got, batch, digest, batch.job):
            self.state.quarantine(self.executor.builder_of(batch.job), "receipt does not verify",
                                  tip=batch.tip, named=got.get("builder"))
            batch.job = self.executor.submit(batch.base, batch.tip, digest, batch.units,
                                             self._spec(batch, digest))
            return
        if got.get("verdict") != "error":
            write_json(receipt_path(self.state, batch.tip, batch.base, digest), got)
        batch.receipt = got

    def _high_risk(self, batch):
        globs = list(self.cfg["high_risk"]) + [g for p in self.cfg["checker_paths"]
                                               for g in (p, f"{p.rstrip('/')}/**")]
        return any(glob_match(path, g) for u in batch.units
                   for path in (self.queue.get(u) or {}).get("paths") or () for g in globs)

    def _needs_check(self, batch):
        verdict = batch.receipt.get("verdict")
        if verdict == "green":
            if self._high_risk(batch) and self.cfg.get("reverify_high_risk", True):
                return True
            draw = int(hashlib.sha256(f"check:{batch.tip}".encode()).hexdigest()[:8], 16) / 0xFFFFFFFF
            return draw < float(self.cfg["reverify_share"])
        return verdict == "red" and len(batch.items) == 1 and bool(self.cfg["reverify_red"])

    @staticmethod
    def _outcome(receipt):
        return (receipt.get("verdict"), receipt.get("tree"), receipt.get("checker"),
                receipt.get("result"))

    def _confirmed(self, batch, digest):
        """The verdict to act on, or None while re-verification is pending.

        A sampled or high-risk green, and a lone red, must be reproduced by a
        builder of a different operator; on disagreement a third operator's
        builder decides, and every builder outvoted is quarantined. With no
        eligible builder the batch is held (event reverify_unavailable)."""
        if not self._needs_check(batch):
            return batch.receipt.get("verdict")
        for job in list(batch.check_jobs):
            got = self.executor.poll(job)
            if got is None:
                continue
            batch.check_jobs.remove(job)
            if got.get("verdict") == "error":
                continue
            if not self._authentic(got, batch, digest, job):
                self.state.quarantine(self.executor.builder_of(job), "receipt does not verify",
                                      tip=batch.tip)
                continue
            batch.checks.append(got)
        receipts = [batch.receipt] + batch.checks
        votes = collections.Counter(self._outcome(r) for r in receipts)
        best, count = votes.most_common(1)[0]
        if count >= 2:
            for r in receipts:
                if self._outcome(r) != best:
                    self.state.quarantine(r.get("builder"), "receipt did not reproduce",
                                          tip=batch.tip, said=r.get("verdict"), majority=best[0])
            if self._outcome(batch.receipt) != best:
                batch.receipt = next(r for r in receipts if self._outcome(r) == best)
            return best[0]
        if batch.check_jobs:
            return None
        used = {self.executor.operator_of(r.get("builder")) for r in receipts}
        job = self.executor.submit(batch.base, batch.tip, digest, batch.units,
                                   self._spec(batch, digest), exclude_operators=used,
                                   avoid={r.get("builder") for r in receipts})
        if job is None:
            if not batch.unavailable:
                self.event("reverify_unavailable", tip=batch.tip, operators=sorted(map(str, used)))
                batch.unavailable = True
            return None
        batch.check_jobs.append(job)
        self.stats["checks"] += 1
        return None

    def capacity(self):
        return int(getattr(self.executor, "n", None) or self.cfg["builders"])

    def _compose(self, base, items, final):
        """A Batch of `items` on `base`; a unit that does not apply is rejected
        when base is the head (`final`), otherwise deferred to a later pass."""
        items = [list(i) for i in items]
        while items:
            patches = [(u, self.state.root / "queue" / f"{u}.patch") for i in items for u in i]
            tip, bad = self.repo.compose(base, patches)
            if not bad:
                outside = self._outside_scope([u for i in items for u in i])
                if not outside:
                    return Batch(items, base, tip), []
                for unit in outside:                    # the rebased diff left its scope
                    item = next((i for i in items if unit in i), None)
                    if item is None:
                        continue
                    items.remove(item)                  # a bundle fails as a whole
                    for u in item:
                        self._finish(u, "rejected", reason="out-of-scope",
                                     paths=outside.get(u, []), base=base)
                continue
            item = next(i for i in items if bad in i)
            items.remove(item)
            if not final:
                return None, item               # may be the speculative base's fault
            for u in item:
                self._finish(u, "rejected", reason="conflict", base=base)
        return None, []

    def _outside_scope(self, units):
        """{unit: [paths outside its scope]} for the last composition."""
        found = {}
        diffs = getattr(self.repo, "unit_diffs", None) or {}
        for unit in units:
            record = self.queue.get(unit) or {}
            if not record.get("scope"):
                continue
            if unit in diffs:                   # the unit's own diff as rebased
                paths = patch_paths(diffs[unit])
                rows = ledger_rows(diffs[unit], self.cfg["row_ledgers"],
                                   getattr(self.repo, "ledger_header", None))
            else:
                paths, rows = record.get("paths") or [], record.get("rows") or {}
            bad = []
            for path in paths:
                keys = rows.get(path)
                if keys and "*" not in keys:
                    bad += [f"{path}#{k}" for k in keys if not in_scope(path, record["scope"], k)]
                elif not in_scope(path, record["scope"]):
                    bad.append(path)
            if bad:
                found[unit] = sorted(bad)
        return found

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
                self._poll(batch, digest)
            for batch in list(self.inflight):
                # a lone item red on a real head is red (once reproduced):
                # rejecting never publishes
                got = batch.receipt or {}
                if (got.get("verdict") == "red" and len(batch.items) == 1
                        and batch.base in self.heads and got.get("checker") == digest
                        and self._confirmed(batch, digest) == "red"):
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
                verdict = batch.receipt.get("verdict")
                if verdict not in ("error", None) and batch.receipt.get("checker") == digest:
                    verdict = self._confirmed(batch, digest)
                    if verdict is None:
                        break                        # re-verification pending
                acted = True
                self._drop(batch)
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
        for job in batch.check_jobs:
            self.executor.cancel(job)
        batch.check_jobs = []

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
        k = max(2, min(len(batch.items), self.capacity()))
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
        while len(self.inflight) < self.capacity() and self.queue:
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
                    quarantined=sorted(self.state.quarantined()),
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
        # once: until nothing is in flight; a backoff (builder error, refused
        # push) with units still queued is waited out, not taken for idle
        if once and not publisher.inflight and not (
                publisher.queue and publisher.clock() < publisher.pause_until):
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
           after=(), bundle=None, priority=0, extra=None, scope=None, forbid=()):
    """Hand a unit to the publisher; returns its id. Operator side only: it
    needs the operator's key, never the publisher's credentials."""
    patch = make_unit(repo, rev)
    if not patch.strip():
        raise RuntimeError(f"nothing to submit in {rev}")
    if scope == "diff":                     # declare exactly the paths and rows it touches
        base = rev.split("..")[0] if ".." in rev else f"{rev}~1"

        def header_of(path):
            got = git("show", f"{base}:{path}", cwd=repo, check=False)
            return (got.stdout.split(b"\n", 1)[0].rstrip(b"\r").decode(errors="replace")
                    if got.returncode == 0 else None)
        scope = scope_from_diff(patch, DEFAULTS["row_ledgers"], header_of)
    envelope = dict(v=1, operator=operator, patch_sha256=hashlib.sha256(patch).hexdigest(),
                    kind=kind, after=list(after), bundle=bundle, priority=priority,
                    time=time.time(), nonce=uuid.uuid4().hex, **(extra or {}))
    if scope:
        envelope["scope"] = dict(allow=list(scope), forbid=list(forbid))
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
    """Make the checker at `commit` current. Returns (ok, report dict).

    Refused without a fixture set holding at least one exploit (`reject`) and
    one benign control (`pass`), and without `ledger_cmd`: a checker is never
    promoted on its own word."""
    state = state if isinstance(state, State) else State(state)
    manifest = read_json(Path(fixtures) / "fixtures.json", []) if fixtures else []
    kinds = {f.get("expect") for f in manifest}
    if not {"reject", "pass"} <= kinds:
        return False, dict(error="promotion needs fixtures.json with at least one exploit "
                                 "(expect: reject) and one benign control (expect: pass)")
    if not state.cfg.get("ledger_cmd"):
        return False, dict(error="promotion needs ledger_cmd (the full-ledger comparison)")
    repo = repo or GitRepo(state)
    head = repo.head()
    if git("cat-file", "-e", f"{commit}^{{commit}}", cwd=repo.dir, check=False).returncode:
        git("fetch", "-q", "--no-tags", "target", "+refs/heads/*:refs/publisher/target/*",
            cwd=repo.dir)
    digest = Checkers(state).materialize(repo.dir, commit)
    git("update-ref", f"refs/publisher/checkers/{digest}", commit, cwd=repo.dir)
    old = Checkers(state).current()
    builder = Builder(state.root / "builders" / "promote", "promote", b"promote")
    report = dict(digest=digest, commit=commit, head=head, fixtures=[], ledger=None)
    ok = True
    for fixture in manifest:           # [{"patch": "x.patch", "expect": "reject"|"pass", "why": ...}]
        tip, bad = repo.compose(head, [("fixture", Path(fixtures) / fixture["patch"])])
        if bad:
            verdict = "does-not-apply"
        else:
            code, _ = builder.run(repo.job(head, tip, digest))
            verdict = "pass" if code == 0 else "reject"
        good = verdict == fixture["expect"]
        ok &= good
        report["fixtures"].append(dict(fixture, got=verdict, ok=good))
    outputs = {}
    for name, which in (("old", old), ("new", digest)):
        if which:
            code, text = builder.run(repo.job(head, head, which), command=state.cfg["ledger_cmd"])
            outputs[name] = set(text.decode(errors="replace").splitlines())
    added = sorted(outputs["new"] - outputs.get("old", outputs["new"]))
    removed = sorted(outputs.get("old", outputs["new"]) - outputs["new"])
    diff = [f"+ {line}" for line in added] + [f"- {line}" for line in removed]
    accepted = set(Path(accept_diff).read_text(encoding="utf-8").splitlines()) if accept_diff else set()
    unaccepted = [line for line in diff if line not in accepted]
    report["ledger"] = dict(added=len(added), removed=len(removed), unaccepted=unaccepted[:50],
                            lines=len(outputs["new"]),
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
    p.add_argument("--scope", action="append", default=[], metavar="GLOB",
                   help="a path glob the unit may touch (repeat); ledgers and headers included")
    p.add_argument("--forbid", action="append", default=[], metavar="GLOB")
    p.add_argument("--scope-from-diff", action="store_true",
                   help="declare exactly the paths the range touches")
    p = sub.add_parser("builder", help="register a builder; writes its key file")
    p.add_argument("--state", required=True)
    p.add_argument("name")
    p.add_argument("--operator", required=True, help="who runs the host (re-verification "
                                                      "always uses another operator)")
    p.add_argument("--command", help='JSON argv that runs publisher.py on the host, e.g. '
                                     '["ssh","host","python3","/srv/bfme/tools/publisher.py"]')
    p.add_argument("--home", help="the builder's work directory on its host")
    p.add_argument("--builder-key", help="the key file's path on the builder host")
    p.add_argument("--slots", type=int, default=1)
    p = sub.add_parser("builder-run", help="(builder host) run one job from stdin, print the receipt")
    for flag in ("--home", "--id", "--key"):
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
        scope = "diff" if args.scope_from_diff else args.scope
        if not scope:
            ap.error("submit needs --scope GLOB ... or --scope-from-diff")
        print(submit(Path.cwd(), args.operator, args.key_file, args.rev, args.inbox, args.remote,
                     args.kind, args.after, args.bundle, args.priority, scope=scope,
                     forbid=args.forbid))
        return 0
    if args.action == "builder":
        root = Path(args.state)
        cfg = read_json(root / "config.json", {})
        key = new_key(root / "builders" / f"{args.name}.key")
        entry = dict(operator=args.operator, key_file=f"builders/{args.name}.key", slots=args.slots)
        if args.command:
            entry["command"] = json.loads(args.command)
        for field in ("home", "builder_key"):
            if getattr(args, field):
                entry[field] = getattr(args, field)
        cfg.setdefault("builders_registry", {})[args.name] = entry
        write_json(root / "config.json", cfg)
        print(key)              # install THIS file on the builder host only
        return 0
    if args.action == "builder-run":
        job = json.loads(sys.stdin.buffer.read())
        receipt, output = Builder(args.home, args.id, read_key(args.key)).build(job)
        print(json.dumps(dict(receipt=receipt, log=output.decode(errors="replace")[-200000:])))
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
