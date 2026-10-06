#!/usr/bin/env python3
"""Runs tools/publisher.py for one repository on a publisher host: ingest from
refs/submit/* on origin, isolated builders, receipts, metrics, health.

TARGET. The mode file on origin master (see tools/publisher_hook.py) picks it:
  shadow/off  the publisher writes branch `publisher-shadow` of a LOCAL bare
              mirror (state/mirror.git). Nothing is written to origin: the
              submission refs stay there (prune_origin=false) and results go
              to the mirror. Seats push to master directly meanwhile, so the
              shadow history drifts whenever a unit is red here or a commit
              lands without a submission; when the publisher is idle and the
              shadow tree differs from master's, the shadow branch is reset
              to master (`resync` in metrics). The checker follows master
              (auto-promotion, shadow only), so a red here is a disagreement
              with the gate seats ran. Scheduling is arrival order (fair=false),
              the order the units landed on master.
  enforce     the publisher fast-forwards origin master itself, deletes the
              refs/submit refs it ingested, and pushes its results to
              refs/publisher/results on origin (what `publisher_hook.py status`
              reads). Checker promotion is the admin's (`publisher.py promote`).
              Leaving enforce keeps origin as the target until the units queued
              under enforce have drained, so a rollback loses nothing.

FILES (state/). config.json and the rest are publisher.py's. service.json:
this file's settings. metrics.csv: one row per finished unit (latency,
verdict, red rate over the last 100 gated units, queue depth). queue.csv: one
row per minute. heartbeat.json: last loop. health-<date>.json: daily verdict.

  python3 tools/publisher_service.py setup --state-root DIR --name N --origin URL --source REPO
          [--commit REV] [--builders 8] [--gate-args '...'] [--checker-paths ...] [--set K=JSON]
  python3 tools/publisher_service.py run --state DIR [--no-pump] [--until-drained] [--max-seconds S]
  python3 tools/publisher_service.py supervise DIR...     (restarts each `run`; stop with `stop`)
  python3 tools/publisher_service.py stop DIR...
  python3 tools/publisher_service.py status --state DIR
  python3 tools/publisher_service.py health --state DIR [--hours 24]
  python3 tools/publisher_service.py replay --state DIR --source REPO [--count 30] [--rev origin/master]
"""
import argparse
import collections
import csv
import datetime
import json
import os
import re
import shutil
import subprocess
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import publisher as pub  # noqa: E402
from publisher_hook import AUTH, MODE_FILES, MODES, RESULTS_REF, unauth_key  # noqa: E402

SERVICE = dict(pump_seconds=10.0, prune_origin=False, results_seconds=30.0, auto_promote=True,
               unauth_rate=1000.0, unauth_burst=200.0, link=[], toolchain_source=None)
SHADOW_BRANCH = "publisher-shadow"
METRIC_FIELDS = ("time", "unit", "operator", "outcome", "reason", "latency_s", "queue_depth",
                 "inflight", "builders_busy", "red_rate_100", "target")
QUEUE_FIELDS = ("time", "target", "queue", "inflight", "builders_busy", "enqueued_total",
                "finished_total", "submit_refs_pending")
# go/no-go for stage B, over the health window
CRITERIA = dict(min_units=100, max_p95_s=1800, max_red_rate=0.03, max_conflict_rate=0.05,
                max_final_queue=40, min_uptime=0.95, max_errors=5)


def git(*args, cwd, check=True, timeout=600, input_bytes=None, env=None):
    return pub.git(*args, cwd=cwd, check=check, timeout=timeout, input_bytes=input_bytes, env=env)


def out(*args, cwd):
    return git(*args, cwd=cwd).stdout.decode().strip()


def now_iso(t=None):
    return datetime.datetime.fromtimestamp(t or time.time(), datetime.timezone.utc).strftime(
        "%Y-%m-%dT%H:%M:%SZ")


def git_dirs(source):
    """(object dir, common dir) of a local repository or worktree."""
    common = Path(out("rev-parse", "--path-format=absolute", "--git-common-dir", cwd=source))
    return common / "objects", common


def borrow(repo, *object_dirs):
    alt = Path(repo) / "objects" / "info" / "alternates"
    alt.parent.mkdir(parents=True, exist_ok=True)
    have = alt.read_text().splitlines() if alt.exists() else []
    alt.write_text("".join(f"{d}\n" for d in dict.fromkeys(have + [Path(d).as_posix()
                                                                   for d in object_dirs])),
                   newline="\n")             # git reads a CR as part of the path


# ---- setup ------------------------------------------------------------------
def setup(root, name, origin, source, commit="origin/master", builders=4, gate_args="",
          checker_paths=None, toolchain_paths=None, link=(), toolchain_source=None,
          build_pool=2, host_lock=None, extra=None):
    """One repository's publisher state under root/name, shadow target ready,
    checker at `commit` promoted, code pinned to `commit` in state/bin."""
    state = Path(root).resolve() / name
    state.mkdir(parents=True, exist_ok=True)
    source = str(Path(source).resolve())
    toolchain_source = toolchain_source and str(Path(toolchain_source).resolve())
    objects, _ = git_dirs(source)
    commit = out("rev-parse", f"{commit}^{{commit}}", cwd=source)
    master = out("rev-parse", "origin/master^{commit}", cwd=source)
    mirror = state / "mirror.git"
    if not (mirror / "HEAD").exists():
        git("init", "-q", "--bare", str(mirror), cwd=state)
        git("config", "gc.auto", "0", cwd=mirror)
    borrow(mirror, objects)
    git("update-ref", "refs/heads/master", master, cwd=mirror)
    if git("rev-parse", "-q", "--verify", f"refs/heads/{SHADOW_BRANCH}", cwd=mirror,
           check=False).returncode:
        git("update-ref", f"refs/heads/{SHADOW_BRANCH}", master, cwd=mirror)
    repo = state / "repo"
    if not (repo / ".git").exists():                 # pre-made so it borrows, not copies
        git("init", "-q", str(repo), cwd=state)
        git("config", "gc.auto", "0", cwd=repo)
        git("remote", "add", "target", str(mirror), cwd=repo)
    borrow(repo / ".git", mirror / "objects", objects)
    bin_dir = state / "bin"
    bin_dir.mkdir(exist_ok=True)
    for tool in ("publisher.py", "publisher_hook.py", "publisher_service.py", "publisher_gate.py"):
        data = git("show", f"{commit}:tools/{tool}", cwd=source).stdout
        (bin_dir / tool).write_bytes(data)
    lock = Path(host_lock or Path.home() / ".cache" / "open-bfme-build.lock")
    toolchains = state / "toolchains"
    gate = (f"BUILD_POOL={int(build_pool)} python3 tools/publisher_gate.py "
            f"--host-lock '{lock.as_posix()}'"
            + "".join(f" --link {rel}" for rel in link)
            + (f" --toolchains '{toolchains.as_posix()}'" if link else "")
            + (f" {gate_args}" if gate_args else ""))
    settings = dict(branch=SHADOW_BRANCH, inbox=str(state / "inbox"), builders=int(builders),
                    gate=gate, clean_keep=["build/"], fair=False,
                    checker_paths=checker_paths or ["tools", ".githooks"],
                    toolchain_paths=toolchain_paths or [], **(extra or {}))
    pub.main(["init", "--state", str(state), "--target", str(mirror),
              *[a for k, v in settings.items() for a in ("--set", f"{k}={json.dumps(v)}")]])
    svc = dict(SERVICE, **(pub.read_json(state / "service.json", {}) or {}))
    svc.update(name=name, origin=origin, mirror=str(mirror), shadow_target=str(mirror),
               link=list(link), toolchain_source=toolchain_source, target_mode="shadow")
    pub.write_json(state / "service.json", svc)
    service = Service(state, load=False)
    service.provision(commit)
    service.provision(master)
    ok, report = pub.promote(state, commit)
    if not ok:
        raise SystemExit(f"promotion of {commit} failed: {json.dumps(report)}")
    svc["promoted_tree"] = service.checker_tree(commit)
    pub.write_json(state / "service.json", svc)
    return state


# ---- the service ------------------------------------------------------------
class Service:
    def __init__(self, state, load=True):
        self.dir = Path(state).resolve()     # publisher.py hands git relative patch paths
        self.svc = dict(SERVICE, **pub.read_json(self.dir / "service.json"))
        self.mirror = Path(self.svc["mirror"])
        self.seen = set(pub.read_json(self.dir / "pump_seen.json", []) or [])
        saved = pub.read_json(self.dir / "service_state.json", {}) or {}
        self.offset = saved.get("offset", 0)
        self.counts = collections.Counter(saved.get("counts") or {})
        self.pending = 0
        self.red = collections.deque(maxlen=100)
        self.seq = int(time.time() * 1000)
        self.last = collections.defaultdict(float)
        self.pub = self._publisher() if load else None

    # -- helpers
    def save(self):
        pub.write_json(self.dir / "service.json", self.svc)

    def _publisher(self):
        return pub.Publisher(pub.State(self.dir))

    def master(self):
        return out("rev-parse", "refs/heads/master", cwd=self.mirror)

    def mode(self):
        for path in MODE_FILES:
            got = git("show", f"refs/heads/master:{path}", cwd=self.mirror, check=False)
            if got.returncode == 0:
                text = got.stdout.decode(errors="replace").strip()
                return text if text in MODES else "off"
        return "off"

    def checker_tree(self, commit):
        cfg = pub.State(self.dir).cfg
        return ",".join(git("rev-parse", f"{commit}:{p}", cwd=self.mirror, check=False)
                        .stdout.decode().strip() for p in cfg["checker_paths"])

    # -- origin: read (fetch); written only in enforce
    def fetch(self):
        git("fetch", "-q", "--no-tags", "--prune", self.svc["origin"],
            "+refs/heads/master:refs/heads/master", "+refs/submit/*:refs/submit-in/*",
            cwd=self.mirror, timeout=120)
        git("fetch", "-q", "--no-tags", str(self.mirror),
            "+refs/heads/master:refs/publisher/origin-master", cwd=self.dir / "repo")

    def pump(self):
        """refs/submit-in/* (fetched) -> inbox, in landing order; unauthenticated
        operators registered on first sight."""
        listing = out("for-each-ref", "--format=%(objectname) %(refname)", "refs/submit-in/",
                      cwd=self.mirror).splitlines()
        fresh, present = [], set()
        for line in listing:
            sha, ref = line.split()
            origin_ref = "refs/submit/" + ref[len("refs/submit-in/"):]
            present.add(origin_ref)
            if origin_ref in self.seen:
                continue
            env = git("show", f"{sha}:envelope.json", cwd=self.mirror, check=False)
            patch = git("show", f"{sha}:unit.patch", cwd=self.mirror, check=False)
            self.seen.add(origin_ref)
            if env.returncode or patch.returncode:
                self.pub.event("inbox_rejected", ref=origin_ref, reason="malformed")
                continue
            envelope = json.loads(env.stdout)
            fresh.append((self._order(envelope), origin_ref, envelope, patch.stdout))
        self.seen &= present                     # deleted on origin: forget
        self.pending = len(present - self.seen)
        cfg_path = self.dir / "config.json"
        cfg = pub.read_json(cfg_path)
        cfg.setdefault("operators", {})
        changed = False
        inbox = Path(cfg["inbox"])
        inbox.mkdir(parents=True, exist_ok=True)
        for _, origin_ref, envelope, patch in sorted(fresh, key=lambda f: f[0]):
            op = envelope.get("operator")
            if (envelope.get("auth") == AUTH and isinstance(op, str) and re.fullmatch(r"[a-z0-9-]{1,40}", op)
                    and op not in cfg["operators"]):
                key = self.dir / "operators" / f"{op}.key"
                key.parent.mkdir(exist_ok=True)
                key.write_text(unauth_key(op) + "\n", encoding="ascii")
                cfg["operators"][op] = dict(key_file=f"operators/{op}.key", auth=AUTH,
                                            rate=self.svc["unauth_rate"],
                                            burst=self.svc["unauth_burst"], infra=False)
                changed = True
            for sha in re.findall(rb"^\+Subproject commit ([0-9a-f]{40})$", patch, re.MULTILINE):
                self.provision(None, sha.decode())
            self.seq += 1
            name = f"{self.seq:015d}-{pub.hashlib.sha256(patch).hexdigest()[:20]}"
            (inbox / f"{name}.patch").write_bytes(patch)
            pub.write_json(inbox / f"{name}.env.json", envelope)
        if changed:
            pub.write_json(cfg_path, cfg)
            self.pub.state.cfg.update(operators=cfg["operators"])
        if fresh:
            pub.write_json(self.dir / "pump_seen.json", sorted(self.seen))
        if self.svc["target_mode"] == "enforce" or self.svc["prune_origin"]:
            gone = [r for r in sorted(self.seen)][:200]
            if gone and git("push", "-q", "--no-verify", self.svc["origin"],
                            *[f":{r}" for r in gone], cwd=self.mirror, check=False).returncode == 0:
                self.seen.difference_update(gone)
                pub.write_json(self.dir / "pump_seen.json", sorted(self.seen))
        return len(fresh)

    def _order(self, envelope):
        """Landing order on master (shadow: the submitted tip is on master);
        otherwise submission time."""
        tip = envelope.get("tip") or ""
        got = git("rev-list", "--count", tip, cwd=self.mirror, check=False) if tip else None
        return (int(got.stdout) if got is not None and got.returncode == 0 else 1 << 60,
                envelope.get("time") or 0)

    def provision(self, commit, sha=None):
        """Clone the gitlinks (`link`) at `commit` (or `sha`) into state/toolchains."""
        source = self.svc.get("toolchain_source")
        if not self.svc.get("link") or not source:
            return
        shas = [sha] if sha else []
        for rel in self.svc["link"] if commit else ():
            entry = out("ls-tree", commit, "--", rel, cwd=self.mirror)
            if entry.startswith("160000 "):
                shas.append(entry.split()[2])
        for sha in shas:
            dest = self.dir / "toolchains" / sha
            if (dest / ".git").exists():
                continue
            tmp = dest.with_name(sha + ".tmp")
            shutil.rmtree(tmp, ignore_errors=True)
            tmp.parent.mkdir(parents=True, exist_ok=True)
            git("clone", "-q", "--no-checkout", source, str(tmp), cwd=tmp.parent, timeout=3600)
            if git("cat-file", "-e", f"{sha}^{{commit}}", cwd=tmp, check=False).returncode:
                git("fetch", "-q", "origin", sha, cwd=tmp, check=False, timeout=3600)
            git("-c", "core.longpaths=true", "checkout", "-q", "--detach", sha, cwd=tmp, timeout=3600)
            os.replace(tmp, dest)
            self.pub and self.pub.event("toolchain_provisioned", sha=sha)

    # -- target selection
    def retarget(self, mode):
        want = "enforce" if mode == "enforce" else "shadow"
        have = self.svc["target_mode"]
        if have == "enforce" and want != "enforce" and self.pub.queue:
            want = "enforce"                    # units queued under enforce still land on origin
        if want == have:
            return
        cfg_path = self.dir / "config.json"
        cfg = pub.read_json(cfg_path)
        if want == "enforce":
            cfg.update(target=self.svc["origin"], branch="master", fair=True)
        else:
            cfg.update(target=self.svc["shadow_target"], branch=SHADOW_BRANCH, fair=False)
        pub.write_json(cfg_path, cfg)
        git("remote", "set-url", "target", cfg["target"], cwd=self.dir / "repo")
        self.pub._flush(0)
        self.svc["target_mode"] = want
        self.save()
        self.pub = self._publisher()
        self.pub.event("retarget", target=want, mode=mode)

    def auto_promote(self, master):
        if (not self.svc["auto_promote"] or self.svc["target_mode"] == "enforce"
                or git("cat-file", "-e", f"{master}:tools/publisher_gate.py", cwd=self.mirror,
                       check=False).returncode):
            return
        tree = self.checker_tree(master)
        if tree == self.svc.get("promoted_tree"):
            return
        ok, report = pub.promote(self.pub.state, master)
        self.svc["promoted_tree"] = tree
        self.save()
        self.pub.event("auto_promote", commit=master, ok=ok)

    def resync(self, master):
        """Shadow only: when idle, put the shadow branch back on master."""
        if (self.svc["target_mode"] == "enforce" or self.pub.queue or self.pub.inflight
                or self.pending or any(Path(self.pub.cfg["inbox"]).glob("*.env.json"))):
            return
        tip = out("rev-parse", f"refs/heads/{SHADOW_BRANCH}", cwd=self.mirror)
        if tip == master or out("rev-parse", f"{tip}^{{tree}}", cwd=self.mirror) == out(
                "rev-parse", f"{master}^{{tree}}", cwd=self.mirror):
            return
        git("update-ref", f"refs/heads/{SHADOW_BRANCH}", master, cwd=self.mirror)
        self.pub.event("resync", old=tip, new=master)

    # -- metrics
    def metrics(self):
        events = self.dir / "events.jsonl"
        if not events.exists():
            return []
        with events.open("rb") as handle:
            handle.seek(self.offset)
            data = handle.read()
        end = data.rfind(b"\n") + 1
        self.offset += end
        rows = []
        for line in data[:end].splitlines():
            ev = json.loads(line)
            self.counts[ev.get("ev")] += 1
            if ev.get("ev") not in ("landed", "rejected"):
                continue
            if ev["ev"] == "landed" or ev.get("reason") == "gate":
                self.red.append(ev["ev"] != "landed")
            rows.append(dict(time=now_iso(ev["t"]), unit=ev["unit"], operator=ev.get("operator"),
                             outcome=ev["ev"], reason=ev.get("reason") or "",
                             latency_s=ev.get("wait"), queue_depth=len(self.pub.queue),
                             inflight=len(self.pub.inflight),
                             builders_busy=self.pub.executor.busy(),
                             red_rate_100=round(sum(self.red) / len(self.red), 4) if self.red else 0,
                             target=self.svc["target_mode"]))
        if rows:
            append_csv(self.dir / "metrics.csv", METRIC_FIELDS, rows)
            self.results(rows)
        pub.write_json(self.dir / "service_state.json", dict(offset=self.offset, counts=self.counts))
        return rows

    def results(self, rows):
        path = self.dir / "results.jsonl"
        with path.open("a", encoding="utf-8") as handle:
            for r in rows:
                handle.write(json.dumps(dict(unit=r["unit"], outcome=r["outcome"],
                                             reason=r["reason"], t=r["time"])) + "\n")

    def publish_results(self):
        path = self.dir / "results.jsonl"
        if not path.exists():
            return
        lines = path.read_text(encoding="utf-8").splitlines()[-5000:]
        blob = git("hash-object", "-w", "--stdin", cwd=self.mirror,
            input_bytes=("\n".join(lines) + "\n").encode()).stdout.decode().strip()
        tree = git("mktree", cwd=self.mirror, input_bytes=f"100644 blob {blob}\tresults.jsonl\n"
                   .encode()).stdout.decode().strip()
        env = dict(os.environ, GIT_AUTHOR_NAME="publisher", GIT_AUTHOR_EMAIL="",
                   GIT_COMMITTER_NAME="publisher", GIT_COMMITTER_EMAIL="")
        commit = git("commit-tree", tree, "-m", "publisher results", cwd=self.mirror,
                     env=env).stdout.decode().strip()
        git("update-ref", RESULTS_REF, commit, cwd=self.mirror)
        if self.svc["target_mode"] == "enforce":
            git("push", "-q", "--no-verify", "--force", self.svc["origin"],
                f"{commit}:{RESULTS_REF}", cwd=self.mirror, check=False)

    def tick(self):
        st = self.pub.status()
        counts = self.counts
        append_csv(self.dir / "queue.csv", QUEUE_FIELDS, [dict(
            time=now_iso(), target=self.svc["target_mode"], queue=st["queue"],
            inflight=st["inflight"], builders_busy=st["builders_busy"],
            enqueued_total=counts["enqueue"], finished_total=counts["landed"] + counts["rejected"],
            submit_refs_pending=self.pending)])

    # -- the loop
    def hold(self):
        """One `run` per state: a second one (a supervisor restarted after its
        window closed, say) exits instead of racing the first."""
        self._lock = open(self.dir / "run.lock", "a+")
        try:
            if os.name == "nt":
                import msvcrt
                self._lock.seek(0)
                msvcrt.locking(self._lock.fileno(), msvcrt.LK_NBLCK, 1)
            else:
                import fcntl
                fcntl.flock(self._lock, fcntl.LOCK_EX | fcntl.LOCK_NB)
        except OSError:
            raise SystemExit(f"{self.dir}: another publisher_service run holds run.lock")

    def run(self, pump=True, until_drained=False, max_seconds=None, stop_file=None):
        self.hold()
        started = time.time()
        stop_file = stop_file or self.dir / "STOP"
        while not stop_file.exists():
            t = time.time()
            try:
                if pump and t - self.last["pump"] >= float(self.svc["pump_seconds"]):
                    self.last["pump"] = t
                    self.fetch()
                    master = self.master()
                    self.retarget(self.mode())
                    self.provision(master)
                    self.auto_promote(master)
                    self.pump()
                    self.resync(master)
                changed = self.pub.step()
                self.metrics()
                if t - self.last["results"] >= float(self.svc["results_seconds"]):
                    self.last["results"] = t
                    self.publish_results()
                if t - self.last["tick"] >= 60:
                    self.last["tick"] = t
                    self.tick()
                    self.daily()
                pub.write_json(self.dir / "heartbeat.json", dict(t=time.time(), pid=os.getpid(),
                                                                 **self.pub.status()))
            except Exception as error:  # noqa: BLE001 -- logged; the queue keeps moving
                self.pub.event("error", error=f"service: {error}")
                print(json.dumps({"error": str(error)}), file=sys.stderr, flush=True)
                changed = False
            if until_drained and not self.pub.queue and not self.pub.inflight and \
                    not any(Path(self.pub.cfg["inbox"]).glob("*.env.json")):
                break
            if max_seconds and time.time() - started > max_seconds:
                break
            if not changed:
                self.pub.executor.wait(float(self.pub.cfg["poll_seconds"]))
        self.pub._flush(0)                       # kill in-flight builds; receipts are reused
        self.metrics()
        self.publish_results()
        self._lock.close()
        return self.pub.status()

    def daily(self):
        day = time.strftime("%Y-%m-%d")
        path = self.dir / f"health-{day}.json"
        if not path.exists():
            pub.write_json(path, health(self.dir))


def append_csv(path, fields, rows):
    new = not path.exists()
    with path.open("a", newline="", encoding="utf-8") as handle:
        writer = csv.DictWriter(handle, fields)
        if new:
            writer.writeheader()
        writer.writerows(rows)


def read_csv(path):
    try:
        with open(path, newline="", encoding="utf-8") as handle:
            return list(csv.DictReader(handle))
    except FileNotFoundError:
        return []


def parse_t(text):
    return datetime.datetime.strptime(text, "%Y-%m-%dT%H:%M:%SZ").replace(
        tzinfo=datetime.timezone.utc).timestamp()


# ---- health -----------------------------------------------------------------
def health(state, hours=24.0, now=None, criteria=None):
    """Keeps up? p95? red rate? -> dict with checks and go (bool) for stage B."""
    state, now = Path(state).resolve(), now or time.time()
    crit = dict(CRITERIA, **(criteria or {}))
    since = now - hours * 3600
    units = [r for r in read_csv(state / "metrics.csv") if parse_t(r["time"]) >= since]
    ticks = [r for r in read_csv(state / "queue.csv") if parse_t(r["time"]) >= since]
    events = []
    if (state / "events.jsonl").exists():
        events = [e for e in map(json.loads, (state / "events.jsonl").read_text().splitlines())
                  if e.get("t", 0) >= since]
    lat = [float(r["latency_s"]) for r in units if r["latency_s"]]
    gated = [r for r in units if r["outcome"] == "landed" or r["reason"] == "gate"]
    red = sum(r["outcome"] == "rejected" for r in gated)
    conflicts = sum(r["reason"] == "conflict" for r in units)
    enq = sum(e["ev"] == "enqueue" for e in events)
    errors = sum(e["ev"] in ("error", "builder_error") for e in events)
    refused = sum(e["ev"] == "receipt_refused" and e.get("reason") != "base-is-not-head"
                  for e in events)
    depth = [int(r["queue"]) for r in ticks]
    quarter = max(1, len(depth) // 4)
    trend = (sum(depth[-quarter:]) / quarter - sum(depth[:quarter]) / quarter) if depth else 0
    hourly = collections.Counter(r["time"][:13] for r in units)
    checks = {
        "volume": (len(units) >= crit["min_units"], f"{len(units)} units finished (>= {crit['min_units']})"),
        "keeps_up": (bool(depth) and depth[-1] <= crit["max_final_queue"] and trend <= 10
                     and len(units) >= 0.95 * enq,
                     f"queue now {depth[-1] if depth else '?'} (<= {crit['max_final_queue']}), "
                     f"trend {trend:+.1f} (<= +10), finished {len(units)} of {enq} enqueued (>= 95%)"),
        "p95_latency": (bool(lat) and pub.percentile(lat, 0.95) <= crit["max_p95_s"],
                        f"p50 {pub.percentile(lat, 0.5)} s, p95 {pub.percentile(lat, 0.95)} s "
                        f"(<= {crit['max_p95_s']})"),
        "red_rate": (not gated or red / len(gated) <= crit["max_red_rate"],
                     f"{red}/{len(gated)} gated units red (<= {crit['max_red_rate']:.0%}); "
                     "every red one needs a look: in shadow it passed the seat's own hook"),
        "conflicts": (not units or conflicts / len(units) <= crit["max_conflict_rate"],
                      f"{conflicts}/{len(units)} did not apply (<= {crit['max_conflict_rate']:.0%})"),
        "uptime": (len(ticks) >= crit["min_uptime"] * hours * 60,
                   f"{len(ticks)} of {int(hours * 60)} minutes with a heartbeat row (>= {crit['min_uptime']:.0%})"),
        "errors": (errors <= crit["max_errors"] and refused == 0,
                   f"{errors} errors (<= {crit['max_errors']}), {refused} receipts refused (0)"),
    }
    return dict(time=now_iso(now), hours=hours, go=all(ok for ok, _ in checks.values()),
                checks={k: dict(ok=ok, detail=d) for k, (ok, d) in checks.items()},
                peak_hour=max(hourly.values(), default=0),
                resyncs=sum(e["ev"] == "resync" for e in events))


def status(state):
    state = Path(state).resolve()
    st = pub.State(state)
    p = pub.Publisher(st, repo=pub._OfflineRepo(), executor=pub.ProcessExecutor(st), offline=True)
    beat = pub.read_json(state / "heartbeat.json", {}) or {}
    svc = pub.read_json(state / "service.json", {}) or {}
    return dict(p.status(), target=svc.get("target_mode"), heartbeat_age_s=round(
        time.time() - beat["t"], 1) if beat else None, running_pid=beat.get("pid"),
        health_24h=health(state)["go"])


# ---- replay (measurement) ---------------------------------------------------
def replay(state, source, count=30, rev="origin/master", operator="replay"):
    """Queue the last `count` first-parent, non-merge commits of `rev` as units,
    in order, onto a shadow branch reset to the first one's parent."""
    state = Path(state).resolve()
    commits = out("rev-list", "--first-parent", f"-n{count * 2}", rev, cwd=source).split()
    picked = []
    for c in commits:
        parents = out("rev-list", "--parents", "-n1", c, cwd=source).split()[1:]
        if len(parents) != 1:
            break
        picked.append(c)
        if len(picked) == count:
            break
    picked.reverse()
    service = Service(state)
    cfg = pub.read_json(state / "config.json")
    cfg.setdefault("operators", {})
    key = state / "operators" / f"{operator}.key"
    key.parent.mkdir(exist_ok=True)
    key.write_text(unauth_key(operator) + "\n", encoding="ascii")
    cfg["operators"][operator] = dict(key_file=f"operators/{operator}.key", auth=AUTH,
                                      rate=1e6, burst=1e6, infra=False)
    pub.write_json(state / "config.json", cfg)
    first_parent = out("rev-parse", f"{picked[0]}^", cwd=source)
    git("update-ref", f"refs/heads/{SHADOW_BRANCH}", first_parent, cwd=service.mirror)
    inbox = Path(cfg["inbox"])
    inbox.mkdir(parents=True, exist_ok=True)
    for i, c in enumerate(picked):
        patch = git("format-patch", "-1", "--stdout", c, cwd=source).stdout
        envelope = pub.signed(bytes.fromhex(unauth_key(operator)), dict(
            v=1, operator=operator, patch_sha256=pub.hashlib.sha256(patch).hexdigest(), kind="normal",
            after=[], bundle=None, priority=0, time=time.time(), nonce=c, auth=AUTH,
            base=f"{c}^", tip=c, scope=dict(allow=pub.patch_paths(patch), forbid=[])))
        (inbox / f"{i:06d}-{c[:12]}.patch").write_bytes(patch)
        pub.write_json(inbox / f"{i:06d}-{c[:12]}.env.json", envelope)
    return picked


# ---- supervisor ---------------------------------------------------------------
def supervise(dirs):
    procs = {}
    for d in dirs:
        (Path(d) / "STOP").unlink(missing_ok=True)
    while True:
        alive = False
        for d in dirs:
            d = Path(d).resolve()
            proc = procs.get(d)
            if proc and proc.poll() is None:
                alive = True
                continue
            if (d / "STOP").exists():
                continue
            if proc:
                print(f"{now_iso()} {d.name}: exited {proc.returncode}; restarting in 30 s",
                      flush=True)
                time.sleep(30)
            log = (d / "service.log").open("a", encoding="utf-8")
            procs[d] = subprocess.Popen([sys.executable, str(d / "bin" / "publisher_service.py"),
                                         "run", "--state", str(d)], stdout=log,
                                        stderr=subprocess.STDOUT)
            print(f"{now_iso()} {d.name}: started pid {procs[d].pid}", flush=True)
            alive = True
        if not alive:
            return 0
        time.sleep(5)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = ap.add_subparsers(dest="action", required=True)
    p = sub.add_parser("setup")
    p.add_argument("--state-root", required=True)
    p.add_argument("--name", required=True)
    p.add_argument("--origin", required=True)
    p.add_argument("--source", required=True)
    p.add_argument("--commit", default="origin/master")
    p.add_argument("--builders", type=int, default=4)
    p.add_argument("--build-pool", type=int, default=2)
    p.add_argument("--gate-args", default="")
    p.add_argument("--checker-paths", nargs="+")
    p.add_argument("--toolchain-paths", nargs="+")
    p.add_argument("--link", action="append", default=[])
    p.add_argument("--toolchain-source")
    p.add_argument("--set", action="append", default=[], metavar="KEY=JSON",
                   help="any other publisher.py config key")
    p = sub.add_parser("run")
    p.add_argument("--state", required=True)
    p.add_argument("--no-pump", action="store_true")
    p.add_argument("--until-drained", action="store_true")
    p.add_argument("--max-seconds", type=float)
    p = sub.add_parser("supervise")
    p.add_argument("dirs", nargs="+")
    p = sub.add_parser("stop")
    p.add_argument("dirs", nargs="+")
    p = sub.add_parser("status")
    p.add_argument("--state", required=True)
    p = sub.add_parser("health")
    p.add_argument("--state", required=True)
    p.add_argument("--hours", type=float, default=24.0)
    p = sub.add_parser("replay")
    p.add_argument("--state", required=True)
    p.add_argument("--source", required=True)
    p.add_argument("--count", type=int, default=30)
    p.add_argument("--rev", default="origin/master")
    args = ap.parse_args(argv)
    if args.action == "setup":
        print(setup(args.state_root, args.name, args.origin, args.source, args.commit,
                    args.builders, args.gate_args, args.checker_paths, args.toolchain_paths,
                    args.link, args.toolchain_source, args.build_pool,
                    extra={k: json.loads(v) for k, v in (s.split("=", 1) for s in args.set)}))
        return 0
    if args.action == "run":
        print(json.dumps(Service(args.state).run(pump=not args.no_pump,
                                                 until_drained=args.until_drained,
                                                 max_seconds=args.max_seconds), indent=1))
        return 0
    if args.action == "supervise":
        return supervise(args.dirs)
    if args.action == "stop":
        for d in args.dirs:
            (Path(d) / "STOP").write_text(now_iso() + "\n")
        return 0
    if args.action == "status":
        print(json.dumps(status(args.state), indent=1))
        return 0
    if args.action == "health":
        report = health(args.state, args.hours)
        for name, check in report["checks"].items():
            print(f"{'PASS' if check['ok'] else 'FAIL'} {name}: {check['detail']}")
        print(f"STAGE-B {'GO' if report['go'] else 'NO-GO'} ({report['hours']} h window, "
              f"peak hour {report['peak_hour']} units, {report['resyncs']} resyncs)")
        return 0 if report["go"] else 1
    if args.action == "replay":
        for c in replay(args.state, args.source, args.count, args.rev):
            print(c)
        return 0
    return 2


if __name__ == "__main__":
    sys.exit(main())
