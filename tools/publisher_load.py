#!/usr/bin/env python3
"""How many builders does the publisher (tools/publisher.py) need?

Two measurements of the SAME Publisher code (scheduler, speculative pipeline,
bisect, receipts):

  simulate   A virtual clock and a virtual repository: arrivals are Poisson
             at --rate units/h from three operators (61/25/14% shares, the
             BFME2 split); a batch's gate takes gate_fixed + gate_per_unit *
             units seconds (+-jitter), and is red when it holds a bad unit
             (--red of arrivals). Hours of traffic in seconds; sweep builders.
  loadtest   Real git on local bare clones and real builder processes; the
             gate sleeps the same formula divided by --scale. Git, process
             and overlay overheads are NOT scaled, so it is pessimistic by
             roughly scale x those overheads.

Both print sustained units/h after a warm-up, latency p50/p95 (enqueue to
landed), queue depth, gates run and builder utilization.

  python3 tools/publisher_load.py simulate [--builders 1,2,3,4,6] [--rate 300] [--hours 8]
  python3 tools/publisher_load.py loadtest --workdir DIR [--builders 3] [--minutes 60] [--scale 6]
  python3 tools/publisher_load.py history --out F.json [--ref origin/master] [--days 7]
  python3 tools/publisher_load.py simulate --footprints F.json ...   # replay real footprints

`history` reads every non-merge commit of the last --days: its paths, the
ledger rows it changes (row_ledgers) and the files that #include what it
touches, and reports how often a commit overlaps another within +-15/30 min
under row scope and under whole-file scope. `--footprints` replays those
footprints in order as the simulated arrivals.
"""
import argparse
import hashlib
import json
import math
import random
import subprocess
import sys
import tempfile
import threading
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import publisher as pub  # noqa: E402

SHARES = (("opA", 0.61), ("opB", 0.25), ("opC", 0.14))


class VirtualRepo:
    def __init__(self):
        self.tip = "h0"
        self.parent = {"h0": None}
        self.bad = {"h0": frozenset()}
        self.is_bad = lambda unit: False
        self.composed = 0
        self.headers = {}                   # ledger path -> header line
        self.graph = ({}, set())            # include graph, as GitRepo.includers()

    def head(self):
        return self.tip

    def compose(self, base, patches):
        units = [u for u, _ in patches]
        tip = hashlib.sha1(("|".join([base, *units])).encode()).hexdigest()[:16]
        self.parent[tip] = base
        self.bad[tip] = self.bad[base] | {u for u in units if self.is_bad(u)}
        self.composed += 1
        return tip, None

    def tree(self, tip):
        return f"T{tip}"

    def inputs_digest(self, head, scope):
        return "static"

    def ledger_header(self, path):
        return self.headers.get(path)

    def includers(self):
        return self.graph

    def is_ancestor(self, older, newer, limit=100000):
        while newer is not None and limit:
            if newer == older:
                return True
            newer, limit = self.parent.get(newer), limit - 1
        return False

    def publish(self, tip):
        if self.is_ancestor(self.tip, tip):
            self.tip = tip
            return True
        return False


class VirtualExecutor:
    """Registered builders (one slot each) on a virtual clock; receipts are
    signed with each builder's own key. `liars` {builder: verdict} makes a
    builder report that verdict whatever the truth."""

    def __init__(self, n, clock, repo, key, duration, blame=lambda units: [], builders=None):
        self.clock, self.repo, self.duration = clock, repo, duration
        self.builders = builders or {f"v{i}": dict(operator="local", key=key) for i in range(n)}
        self.n = len(self.builders)
        self.blame = blame
        self.liars = {}
        self.quarantined = lambda: {}
        self.waiting, self.running = [], []
        self.busy_seconds, self._last = 0.0, 0.0

    def operator_of(self, builder):
        return (self.builders.get(builder) or {}).get("operator")

    def builder_of(self, job):
        return job.get("builder")

    def _eligible(self, builder, job):
        return (self.operator_of(builder) not in job["exclude"] and builder not in job["avoid"]
                and builder not in self.quarantined())

    def _advance(self):
        now = self.clock()
        self.busy_seconds += len(self.running) * (now - self._last)
        self._last = now
        for job in [j for j in self.running if j["done"] <= now]:
            self.running.remove(job)
            bad = bool(self.repo.bad[job["tip"]])
            verdict = self.liars.get(job["builder"]) or ("red" if bad else "green")
            job["result"] = pub.signed(self.builders[job["builder"]]["key"], dict(
                v=2, tip=job["tip"], base=job["base"], tree=self.repo.tree(job["tip"]),
                checker=job["digest"], toolchain={}, exit=int(verdict == "red"), result=None,
                blame=self.blame(job["units"]) if bad else [], builder=job["builder"],
                verdict=verdict))
        busy = {j["builder"] for j in self.running}
        for job in list(self.waiting):
            builder = next((b for b in self.builders if b not in busy and self._eligible(b, job)), None)
            if builder is None:
                continue
            self.waiting.remove(job)
            job["builder"], job["done"] = builder, now + self.duration(len(job["units"]))
            self.running.append(job)
            busy.add(builder)

    def submit(self, base, tip, digest, units, spec=None, exclude_operators=(), avoid=()):
        job = dict(base=base, tip=tip, digest=digest, units=list(units), result=None, done=None,
                   exclude=set(exclude_operators), avoid=set(avoid), builder=None)
        if not any(self._eligible(b, job) for b in self.builders):
            return None
        self.waiting.append(job)
        self._advance()
        return job

    def poll(self, job):
        self._advance()
        return job["result"]

    def cancel(self, job):
        self._advance()
        for queue in (self.waiting, self.running):
            if job in queue:
                queue.remove(job)

    def busy(self):
        return len(self.running)

    def next_time(self):
        return min((j["done"] for j in self.running), default=math.inf)

    def wait(self, seconds):
        pass


class VirtualWorld:
    """A Publisher on a virtual clock, repository and builder pool. Tests and
    `simulate` drive it with arrivals: (time, operator, bad, envelope extras)."""

    def __init__(self, root, builders=3, operators=None, gate_fixed=60, gate_per_unit=20,
                 jitter=0.2, blame=0.0, seed=1, **cfg):
        self.rng = random.Random(seed)
        self.root = Path(root)
        self.root.mkdir(parents=True, exist_ok=True)
        ops = {}
        for name, op in (operators or {n: {} for n, _ in SHARES}).items():
            pub.new_key(self.root / "operators" / f"{name}.key")
            ops[name] = dict(dict(rate=1000, burst=40), **op, key_file=f"operators/{name}.key")
        registry = {}                         # builders spread over three host operators
        for i in range(builders):
            pub.new_key(self.root / "builders" / f"v{i}.key")
            registry[f"v{i}"] = dict(operator=f"host{'ABC'[i % 3]}", key_file=f"builders/v{i}.key")
        pub.write_json(self.root / "config.json", dict(dict(builders_registry=registry), **cfg,
                                                       target="virtual", builders=builders,
                                                       operators=ops))
        pub.new_key(self.root / "receipt.key")
        pub.write_json(self.root / "checkers.json", {"current": "sim", "history": []})
        self.now = [0.0]
        self.state = pub.State(self.root)
        self.repo = VirtualRepo()
        rng = self.rng
        duration = lambda n: (gate_fixed + gate_per_unit * n) * rng.uniform(1 - jitter, 1 + jitter)  # noqa: E731
        self.ex = VirtualExecutor(builders, lambda: self.now[0], self.repo, self.state.receipt_key,
                                  duration, builders={
                                      b: dict(operator=e["operator"], key=self.state.builder_key(b))
                                      for b, e in self.state.registry().items()})
        self.ex.quarantined = self.state.quarantined
        self.p = pub.Publisher(self.state, repo=self.repo, executor=self.ex,
                               clock=lambda: self.now[0])
        self.repo.is_bad = lambda u: self.p.queue.get(u, {}).get("sim_bad", False)
        # the gate names a bad unit's path with probability `blame`
        self.ex.blame = lambda units: [path for u in units if self.repo.is_bad(u) and rng.random() < blame
                                       for path in self.p.queue.get(u, {}).get("paths", ())]
        self.keys = {name: self.state.operator_key(name) for name in ops}
        self.serial = 0
        self.depth = []

    def submit(self, operator, bad=False, paths=None, rows=None, **extra):
        """A unit touching `paths` and, in row ledgers, the rows `rows`
        ({path: [keys]}); its scope defaults to exactly that (row tokens)."""
        self.serial += 1
        i = self.serial
        rows = rows or {}
        paths = list(paths or ([] if rows else [f"u{i}"]))
        body = "".join(f"diff --git a/{p} b/{p}\n+{i}\n" for p in paths if p not in rows)
        for path, keys in rows.items():
            body += f"diff --git a/{path} b/{path}\n" + "".join(
                f"+{self._row(path, k)}\n" for k in keys)
        patch = (f"From {i:040x} Mon Sep 17 00:00:00 2001\nunit {i}\n" + body).encode()
        extra.setdefault("scope", dict(allow=pub.scope_from_diff(
            patch, self.state.cfg["row_ledgers"], self.repo.ledger_header)))
        envelope = pub.signed(self.keys[operator], dict(
            v=1, operator=operator, sim_bad=bad, patch_sha256=hashlib.sha256(patch).hexdigest(),
            **extra))
        unit, reason = self.p.accept(envelope, patch)
        assert unit, reason
        return unit

    def _row(self, path, key):
        """A ledger line whose key column holds `key` (line ledgers: the key)."""
        import csv
        import io
        header = self.repo.ledger_header(path)
        column = pub.row_ledger(path, self.state.cfg["row_ledgers"])
        if not header or not column:
            return key
        names = next(csv.reader([header]))
        cells = [""] * len(names)
        cells[names.index(column)] = key
        line = io.StringIO()
        csv.writer(line, lineterminator="").writerow(cells)
        return line.getvalue()

    def run(self, arrivals, end):
        """arrivals: sorted [(t, operator, bad, extras)]; runs to time `end`."""
        i = 0
        for _ in range(50):
            if not self.p.step():
                break
        for _ in range(10 ** 7):
            nxt = min(arrivals[i][0] if i < len(arrivals) else math.inf, self.ex.next_time())
            if nxt == math.inf or nxt > end:
                break
            self.now[0] = max(self.now[0], nxt)
            while i < len(arrivals) and arrivals[i][0] <= self.now[0]:
                _, name, bad, extra = arrivals[i]
                self.submit(name, bad, **dict(extra))
                i += 1
            for _ in range(50):
                if not self.p.step():
                    break
            self.depth.append((self.now[0], len(self.p.queue)))
        self.now[0] = max(self.now[0], end)
        self.ex._advance()

    def events(self):
        return [json.loads(line) for line in (self.root / "events.jsonl").read_text().splitlines()]


def history(repo, ref="origin/master", days=7):
    """Footprints of the last `days` of non-merge commits: [{t, paths, rows}],
    plus ledger headers and the include graph at `ref`."""
    cfg = pub.DEFAULTS
    log = pub.out("log", f"--since={int(days * 24)}.hours", "--no-merges", "--format=%H %ct", ref, cwd=repo)
    headers, prints = {}, []

    def header_of(path):
        if path not in headers:
            got = pub.git("show", f"{ref}:{path}", cwd=repo, check=False)
            headers[path] = (got.stdout.split(b"\n", 1)[0].rstrip(b"\r").decode(errors="replace")
                             if got.returncode == 0 else None)
        return headers[path]
    for line in reversed(log.splitlines()):
        sha, stamp = line.split()
        diff = pub.git("show", "--format=", "--no-renames", "-U0", "--no-ext-diff", sha,
                       cwd=repo).stdout
        prints.append(dict(sha=sha[:10], t=int(stamp), paths=pub.patch_paths(diff),
                           rows=pub.ledger_rows(diff, cfg["row_ledgers"], header_of)))
    by_name, macro = pub.scan_includes(repo, ref, cfg["include_globs"])
    return dict(ref=pub.out("rev-parse", ref, cwd=repo), days=days, footprints=prints,
                headers={k: v for k, v in headers.items() if v},
                graph=[{k: sorted(v) for k, v in by_name.items()}, sorted(macro)])


def _record(fp, graph, row_scope=True):
    cfg = pub.DEFAULTS
    if not row_scope:                         # the whole-file rule of the previous commit
        return dict(scope=dict(allow=fp["paths"]), paths=fp["paths"], rows={}, reach=[])
    allow = []
    for path in fp["paths"]:
        keys = fp["rows"].get(path)
        allow += [f"{path}#{k}" for k in keys] if keys and "*" not in keys else [path]
    return dict(scope=dict(allow=allow), paths=fp["paths"], rows=fp["rows"],
                reach=pub.reach_of(fp["paths"], graph, cfg))


def collisions(data, windows=(15, 30)):
    """Share of commits overlapping at least one other commit within +-W min."""
    graph = ({k: set(v) for k, v in data["graph"][0].items()}, set(data["graph"][1]))
    prints = [fp for fp in data["footprints"] if fp["paths"]]
    report = dict(commits=len(prints))
    for row_scope in (True, False):
        recs = [_record(fp, graph, row_scope) for fp in prints]
        for w in windows:
            hit, j0 = 0, 0
            for i, fp in enumerate(prints):
                while prints[j0]["t"] < fp["t"] - w * 60:
                    j0 += 1
                j = j0
                while j < len(prints) and prints[j]["t"] <= fp["t"] + w * 60:
                    if j != i and pub.scopes_overlap(recs[i], recs[j]):
                        hit += 1
                        break
                    j += 1
            report[f"{'row' if row_scope else 'whole_file'}_overlap_{w}min"] = round(hit / len(prints), 3)
    report["touch_functions_csv"] = round(sum(
        any(p.endswith("functions.csv") for p in fp["paths"]) for fp in prints) / len(prints), 3)
    report["header_reach_wide"] = sum(1 for r in [_record(fp, graph) for fp in prints]
                                      if r["reach"] == ["*"])
    return report


def simulate(builders=3, rate=300, hours=8, red=0.03, gate_fixed=60, gate_per_unit=20, jitter=0.2,
             max_batch=20, seed=1, warmup=1.0, workdir=None, blame=0.0, target=0.1,
             shared=0.0, footprints=None, row_scope=True):
    """Poisson arrivals from the three operators; returns measurements."""
    world = VirtualWorld(workdir or tempfile.mkdtemp(prefix="pubsim-"), builders,
                         gate_fixed=gate_fixed, gate_per_unit=gate_per_unit, jitter=jitter,
                         blame=blame, seed=seed, max_batch=max_batch, target_red_batch=target,
                         **({} if row_scope else {"row_ledgers": {}}))
    rng = world.rng
    prints = None
    if footprints:                            # replay real commits as the arrivals
        world.repo.headers = dict(footprints["headers"])
        world.repo.graph = ({k: set(v) for k, v in footprints["graph"][0].items()},
                            set(footprints["graph"][1]))
        prints = [fp for fp in footprints["footprints"] if fp["paths"]]
    end = hours * 3600.0
    arrivals, t = [], 0.0
    while t < end:
        t += rng.expovariate(rate / 3600.0)
        r, acc = rng.random(), 0.0
        for name, share in SHARES:
            acc += share
            if r <= acc:
                break
        # `shared`: share of units that also touch one shared ledger (serialized)
        extra = {"paths": [f"s{len(arrivals)}", "functions.csv"]} if rng.random() < shared else {}
        if prints:
            fp = prints[len(arrivals) % len(prints)]
            extra = {"paths": fp["paths"], "rows": fp["rows"] if row_scope else {}}
        arrivals.append((t, name, rng.random() < red, extra))
    world.run(arrivals, end)
    p, ex, root = world.p, world.ex, world.root
    depth_samples = world.depth
    depth_max = max((d for _, d in depth_samples), default=0)
    events = [json.loads(line) for line in (root / "events.jsonl").read_text().splitlines()]
    landed = [e for e in events if e["ev"] == "landed" and e["t"] >= warmup * 3600]
    by_op = {}
    for e in events:
        if e["ev"] == "landed":
            by_op.setdefault(e["operator"], []).append(e["wait"])
    waits = [e["wait"] for e in landed]
    span = max(1e-9, (end - warmup * 3600) / 3600)
    late = [d for t_, d in depth_samples if t_ >= end - 3600]
    return dict(builders=builders, rate=rate, red=red, hours=hours, blame=blame, target=target,
                shared=shared, footprints=len(prints or ()), row_scope=row_scope,
                sustained_per_h=round(len(landed) / span, 1),
                latency_p50_min=round((pub.percentile(waits, 0.5) or 0) / 60, 1),
                latency_p95_min=round((pub.percentile(waits, 0.95) or 0) / 60, 1),
                queue_end=len(p.queue), queue_max=depth_max,
                queue_last_hour_mean=round(sum(late) / max(1, len(late)), 1),
                rejected=sum(1 for e in events if e["ev"] == "rejected"),
                gates=p.stats["gates"], red_batches=p.stats["red_batches"],
                utilization=round(ex.busy_seconds / (builders * end), 2),
                p95_wait_min_by_operator={k: round((pub.percentile(v, 0.95) or 0) / 60, 1)
                                          for k, v in sorted(by_op.items())})


# ---- real git -------------------------------------------------------------
GATE = """#!/bin/bash
# load-test gate: sleeps like a real gate, red when the change adds a bad* file
n=$(git diff --name-only "$LANDING_BASE" "$LANDING_TIP" | wc -l)
python3 -c "import time; time.sleep(({fixed} + {per_unit} * $n) / {scale})"
bad=$(git diff --name-only "$LANDING_BASE" "$LANDING_TIP" | grep '^bad' || true)
if [ -n "$bad" ]; then
    echo "$bad" | sed 's/^/PUBLISHER-BLAME: /'; exit 1
fi
"""


def _git(cwd, *args, input_bytes=None):
    return pub.git(*args, cwd=cwd, input_bytes=input_bytes).stdout.decode().strip()


def _state(root, builders, max_batch, rates):
    root = Path(root)
    root.mkdir(parents=True, exist_ok=True)
    ops = {}
    for name, _ in SHARES:
        pub.new_key(root / "operators" / f"{name}.key")
        ops[name] = dict(key_file=f"operators/{name}.key", rate=rates.get(name, 1000), burst=40)
    return ops


def loadtest(workdir, builders=3, rate=300, minutes=60, scale=6.0, red=0.03, gate_fixed=60,
             gate_per_unit=20, max_batch=20, seed=1, target=0.25):
    rng = random.Random(seed)
    root = Path(workdir).resolve()
    root.mkdir(parents=True, exist_ok=True)
    origin, seat, state_dir = root / "origin.git", root / "seat", root / "state"
    _git(root, "init", "-q", "--bare", str(origin))
    _git(root, "init", "-q", str(seat))
    for k, v in (("user.name", "seat"), ("user.email", ""), ("core.hooksPath", "no-hooks")):
        _git(seat, "config", k, v)
    (seat / "checker").mkdir()
    (seat / "checker" / "gate.sh").write_text(
        GATE.format(fixed=gate_fixed, per_unit=gate_per_unit, scale=scale), newline="\n")
    (seat / "a.txt").write_text("base\n")
    _git(seat, "add", "-A")
    _git(seat, "commit", "-q", "-m", "base")
    _git(seat, "push", "-q", str(origin), "HEAD:refs/heads/master")
    base = _git(seat, "rev-parse", "HEAD")
    expected = int(rate * minutes / 60 * 1.3) + 10
    patches = root / "patches"
    patches.mkdir()
    bad_flags = []
    for n in range(expected):                     # independent units: one new file each
        bad = rng.random() < red
        bad_flags.append(bad)
        _git(seat, "checkout", "-q", "--detach", base)
        name = f"{'bad' if bad else 'u'}{n:05d}.txt"
        (seat / name).write_text(f"{n}\n")
        _git(seat, "add", name)
        _git(seat, "commit", "-q", "-m", f"unit {n}")
        (patches / f"{n:05d}.patch").write_bytes(
            pub.git("format-patch", "-1", "--stdout", cwd=seat).stdout)
    inbox = root / "inbox"
    ops = _state(state_dir, builders, max_batch, {})
    pub.write_json(state_dir / "config.json", dict(
        target=str(origin), builders=builders, max_batch=max_batch, operators=ops,
        inbox=str(inbox), checker_paths=["checker"], gate="bash checker/gate.sh",
        poll_seconds=0.5, clean_keep=[], target_red_batch=target, ledger_cmd="git ls-files",
        reverify_share=0.0, reverify_red=False))     # one host: throughput, not re-verification
    pub.new_key(state_dir / "receipt.key")
    fixtures, manifest = root / "fixtures", []    # promotion needs an exploit and a control
    fixtures.mkdir()
    for name, expect in (("bad_fixture", "reject"), ("fine_fixture", "pass")):
        _git(seat, "checkout", "-q", "--detach", base)
        (seat / f"{name}.txt").write_text("x\n")
        _git(seat, "add", f"{name}.txt")
        _git(seat, "commit", "-q", "-m", name)
        (fixtures / f"{name}.patch").write_bytes(pub.git("format-patch", "-1", "--stdout", cwd=seat).stdout)
        manifest.append(dict(patch=f"{name}.patch", expect=expect))
    (fixtures / "fixtures.json").write_text(json.dumps(manifest))
    ok, report = pub.promote(state_dir, base, fixtures)
    assert ok, report
    state = pub.State(state_dir)
    publisher = pub.Publisher(state)
    keys = {name: state.operator_key(name) for name, _ in SHARES}
    stop = threading.Event()
    real = minutes * 60 / scale
    started = time.time()

    def arrive():
        t, n = 0.0, 0
        while n < expected and not stop.is_set():
            t += rng.expovariate(rate * scale / 3600.0)
            delay = started + t - time.time()
            if delay > 0:
                time.sleep(delay)
            if time.time() - started > real:
                return
            r, acc = rng.random(), 0.0
            for name, share in SHARES:
                acc += share
                if r <= acc:
                    break
            patch = (patches / f"{n:05d}.patch").read_bytes()
            unit = hashlib.sha256(patch).hexdigest()[:20]
            envelope = pub.signed(keys[name], dict(v=1, operator=name, time=time.time(),
                                                   patch_sha256=hashlib.sha256(patch).hexdigest(),
                                                   scope=dict(allow=pub.patch_paths(patch))))
            inbox.mkdir(exist_ok=True)
            (inbox / f"{unit}.patch").write_bytes(patch)
            pub.write_json(inbox / f"{unit}.env.json", envelope)
            n += 1
    feeder = threading.Thread(target=arrive, daemon=True)
    feeder.start()
    drainer = threading.Thread(target=pub.drain, args=(publisher,), kwargs=dict(stop=stop),
                               daemon=True)
    drainer.start()
    depth = []
    while time.time() - started < real:
        time.sleep(2)
        depth.append(len(publisher.queue))
    stop.set()
    drainer.join(timeout=120)
    events = [json.loads(line) for line in (state_dir / "events.jsonl").read_text().splitlines()]
    warm = started + real / 6
    landed = [e for e in events if e["ev"] == "landed" and e["t"] >= warm]
    waits = [e["wait"] * scale for e in landed]
    span_h = (real - real / 6) * scale / 3600
    master = _git(origin, "rev-list", "--count", "master")
    return dict(builders=builders, rate=rate, scale=scale, sim_minutes=minutes,
                submitted=sum(1 for e in events if e["ev"] == "enqueue"),
                landed_total=sum(1 for e in events if e["ev"] == "landed"),
                rejected=sum(1 for e in events if e["ev"] == "rejected"),
                sustained_per_h=round(len(landed) / span_h, 1),
                latency_p50_min=round((pub.percentile(waits, 0.5) or 0) / 60, 1),
                latency_p95_min=round((pub.percentile(waits, 0.95) or 0) / 60, 1),
                queue_end=len(publisher.queue), queue_max=max(depth or [0]),
                gates=publisher.stats["gates"], red_batches=publisher.stats["red_batches"],
                master_commits=int(master), foreign=sum(1 for e in events if e["ev"] == "foreign_push"),
                receipts_refused=sum(1 for e in events if e["ev"] == "receipt_refused"))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = ap.add_subparsers(dest="action", required=True)
    s = sub.add_parser("simulate")
    s.add_argument("--builders", default="1,2,3,4,6")
    s.add_argument("--rate", type=float, default=300)
    s.add_argument("--hours", type=float, default=8)
    s.add_argument("--red", default="0.01,0.03,0.10")
    s.add_argument("--gate-fixed", type=float, default=60)
    s.add_argument("--gate-per-unit", type=float, default=20)
    s.add_argument("--max-batch", type=int, default=20)
    s.add_argument("--blame", type=float, default=0.0, help="share of red gates naming the culprit")
    s.add_argument("--target", type=float, default=0.1, help="target_red_batch")
    s.add_argument("--shared", type=float, default=0.0,
                   help="share of units that also touch functions.csv")
    s.add_argument("--footprints", help="history JSON: replay real commit footprints")
    s.add_argument("--whole-file", action="store_true", help="whole-file ledger scope (no rows)")
    h = sub.add_parser("history")
    h.add_argument("--out", required=True)
    h.add_argument("--repo", default=".")
    h.add_argument("--ref", default="origin/master")
    h.add_argument("--days", type=float, default=7)
    lt = sub.add_parser("loadtest")
    lt.add_argument("--workdir", required=True)
    lt.add_argument("--builders", type=int, default=3)
    lt.add_argument("--rate", type=float, default=300)
    lt.add_argument("--minutes", type=float, default=60)
    lt.add_argument("--scale", type=float, default=6)
    lt.add_argument("--red", type=float, default=0.03)
    lt.add_argument("--target", type=float, default=0.25, help="target_red_batch (gate emits blame)")
    args = ap.parse_args(argv)
    if args.action == "history":
        data = history(args.repo, args.ref, args.days)
        pub.write_json(Path(args.out), data)
        print(json.dumps(collisions(data), indent=1))
        return 0
    if args.action == "simulate":
        prints = json.loads(Path(args.footprints).read_text()) if args.footprints else None
        for red in map(float, args.red.split(",")):
            for n in map(int, args.builders.split(",")):
                with tempfile.TemporaryDirectory(prefix="pubsim-") as tmp:
                    print(json.dumps(simulate(n, args.rate, args.hours, red, args.gate_fixed,
                                              args.gate_per_unit, max_batch=args.max_batch,
                                              workdir=tmp, blame=args.blame,
                                              target=args.target, shared=args.shared,
                                              footprints=prints,
                                              row_scope=not args.whole_file)), flush=True)
        return 0
    print(json.dumps(loadtest(args.workdir, args.builders, args.rate, args.minutes, args.scale,
                              args.red, target=args.target), indent=1))
    return 0


if __name__ == "__main__":
    sys.exit(main())
