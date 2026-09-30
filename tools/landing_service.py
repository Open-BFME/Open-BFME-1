#!/usr/bin/env python3
"""The landing service: ONE publisher for master (design + prototype).

WHY. A hundred seats each run `pull --rebase; push`, and each push runs the
push gate against a master that moves every minute. Measured 2026-09-17: a
direct push lost 6 of 6 races while its ~35 s hook ran; the harvest pipeline
(tools/fleet/harvest.py) survives only by pushing a scratch branch and
fast-forwarding master through the GitHub API. Every seat pays the gate, most
pay it several times, and a green hook proves a snapshot that is not the one
master ends up at. Claims have the mirror problem: a worker knows its commit
verified, never that it landed (claims.release_landed).

DESIGN. Seats stop pushing to master. They hand in finished units; one
service lands them.
  UNIT      One `git format-patch` mbox (a commit keeps its message, author
            and trailers), stored by the sha256 of its bytes, so the same
            unit enqueued twice is one unit (idempotent). Optional metadata:
            the claim tokens it was built under ({rva: sha}, tools/claims.py),
            model/run/host as recorded, never trusted.
  QUEUE     A directory: queue/<id>.patch + <id>.json. Terminal states move
            the metadata to landed/ or rejected/ with the reason. Nothing is
            deleted, so a crash never loses a unit and a replay is harmless.
  BATCH     Take up to N queued units in arrival order. Rebase ONCE: reset a
            private worktree to the fetched origin/master (the snapshot) and
            `git am -3` the batch. A unit that does not apply is rejected
            (`conflict`) and the rest continue.
  FENCE     A unit carrying claim tokens is rejected (`claim-lost`) when
            origin no longer holds one (claims.holds): its worker's lease
            expired and someone else owns the body now.
  GATE      Run the gate ONCE per batch on the exact batch tip: by default the
            repository's own .githooks/pre-push fed the ref line for
            snapshot..tip (protected_paths, conversion_gate, check_csv,
            identity, byte-verify of every affected selector), so the
            service proves exactly what a push would.
  BISECT    A red batch is split in halves; each half is re-gated on top of
            the units already accepted (bisect() below), so one bad unit
            costs O(log n) gates and never sinks its neighbours.
  PUBLISH   Push the gated tip to master. The push hook runs again; the
            verification cache (tools/verification_cache.py) makes the
            repeat cheap. If master moved, re-fetch and redo the batch on the
            new snapshot: a receipt is only ever for the snapshot it names.
  RECEIPT   receipts/<id>.json per landed unit: unit id, snapshot sha, batch
            tip sha, the landed commit sha, tree sha, gate command and exit,
            batch size, bisect depth, host, time. The landed sha is what
            `claims.py release --landed SHA` takes.
  RECOVERY  state.json records the phase (verifying/publishing) with the
            snapshot and tip before each step. On start, a `publishing` tip
            that is an ancestor of origin/master is recorded as landed;
            anything else returns to the queue.

AUTHENTICATION IS NOT SOLVED. model=, run= and host= in a receipt are values
a worker process could have set. Proposal: fleet_run signs a run receipt
(run id, host, the model parsed from the command it launched, brief sha,
touched rvas) with a per-host key the worker cannot read (a separate OS user,
or a signing daemon outside the cgroup), and pushes it to refs/receipts/<run>;
the service accepts a unit's model/run only when a verifying signature
covers that run and its touched rvas include the unit's rows.

STATUS. Prototype: queue, bisect, am-based batching, fencing, gate, publish,
receipts and recovery are implemented and tested on fixture repositories
(tools/tests/test_landing_service.py). It does not yet run anywhere; seats
still push directly. Next: run it beside the harvest loop on one host with
--gate defaulted to pre-push, then point fleet seats at `enqueue`.

  python3 tools/landing_service.py enqueue <patch-file | commit> [--claim 0xRVA=TOKEN ...]
  python3 tools/landing_service.py status
  python3 tools/landing_service.py run-once [--max-batch 20] [--gate CMD] [--no-publish]
"""
import argparse
import datetime
import hashlib
import json
import os
import socket
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
STATE = ROOT / "build" / "landing"
DEFAULT_GATE = ('printf "refs/heads/master %s refs/heads/master %s\\n" "$LANDING_TIP" "$LANDING_BASE" '
                '| bash .githooks/pre-push origin origin')


def git(*args, cwd, check=True, input_bytes=None, timeout=600):
    got = subprocess.run(["git", *args], cwd=cwd, capture_output=True, input=input_bytes,
                         timeout=timeout)
    if check and got.returncode:
        raise RuntimeError(f"git {' '.join(args)}: {got.stderr.decode(errors='replace').strip()}")
    return got


def out(*args, cwd):
    return git(*args, cwd=cwd).stdout.decode().strip()


def bisect(units, verify, accepted=()):
    """(good, bad): the largest arrival-ordered subset that gates green.

    `verify(prefix)` answers whether accepted+prefix is green on the
    snapshot. A green batch costs one call; each bad unit adds about
    2*log2(n) calls, and good units after a bad one are kept."""
    units, accepted = list(units), list(accepted)
    if not units:
        return [], []
    if verify(accepted + units):
        return units, []
    if len(units) == 1:
        return [], units
    mid = len(units) // 2
    left_good, left_bad = bisect(units[:mid], verify, accepted)
    right_good, right_bad = bisect(units[mid:], verify, accepted + left_good)
    return left_good + right_good, left_bad + right_bad


class Service:
    def __init__(self, repo=ROOT, state=None, remote="origin", branch="master", gate=DEFAULT_GATE,
                 fence=None):
        self.repo = Path(repo)
        self.state = Path(state) if state else STATE
        self.remote, self.branch, self.gate = remote, branch, gate
        self.fence = fence or self.claims_fence
        for sub in ("queue", "landed", "rejected", "receipts"):
            (self.state / sub).mkdir(parents=True, exist_ok=True)
        self.work = self.state / "wt"
        self.gates_run = 0

    # ---- queue ----------------------------------------------------------
    def enqueue(self, patch, meta=None):
        """Store a unit; returns its id. The same bytes are one unit, whatever
        its state: re-enqueueing a landed or rejected unit changes nothing."""
        data = Path(patch).read_bytes() if Path(patch).exists() else git(
            "format-patch", "-1", "--stdout", patch, cwd=self.repo).stdout
        unit = hashlib.sha256(data).hexdigest()[:20]
        if any((self.state / d / f"{unit}.json").exists() for d in ("queue", "landed", "rejected")):
            return unit
        (self.state / "queue" / f"{unit}.patch").write_bytes(data)
        record = dict(meta or {}, id=unit, enqueued=time.time())
        self._write(self.state / "queue" / f"{unit}.json", record)
        return unit

    def queued(self):
        items = [json.loads(p.read_text(encoding="utf-8")) for p in (self.state / "queue").glob("*.json")]
        return sorted(items, key=lambda r: (r.get("enqueued", 0), r["id"]))

    def _write(self, path, data):
        tmp = path.with_suffix(".tmp")
        tmp.write_text(json.dumps(data, indent=1, sort_keys=True), encoding="utf-8")
        os.replace(tmp, path)

    def _finish(self, unit, where, **extra):
        record = json.loads((self.state / "queue" / f"{unit}.json").read_text(encoding="utf-8"))
        record.update(extra, finished=time.time())
        self._write(self.state / where / f"{unit}.json", record)
        (self.state / "queue" / f"{unit}.json").unlink()
        return record

    def _phase(self, **data):
        self._write(self.state / "state.json", data)

    # ---- git ------------------------------------------------------------
    def snapshot(self):
        git("fetch", "-q", "--no-tags", self.remote, self.branch, cwd=self.repo, timeout=900)
        return out("rev-parse", "FETCH_HEAD", cwd=self.repo)

    def _worktree(self, base):
        if not (self.work / ".git").exists():
            git("worktree", "add", "-q", "--detach", str(self.work), base, cwd=self.repo)
        git("am", "--abort", cwd=self.work, check=False)
        git("reset", "-q", "--hard", base, cwd=self.work)
        git("clean", "-qfd", cwd=self.work)

    def _apply(self, base, units):
        """Tip after applying `units` on `base`, or (None, unit) for the first
        unit that does not apply."""
        self._worktree(base)
        for unit in units:
            patch = self.state / "queue" / f"{unit}.patch"
            if git("am", "-q", "-3", "--keep-cr", str(patch), cwd=self.work, check=False).returncode:
                git("am", "--abort", cwd=self.work, check=False)
                return None, unit
        return out("rev-parse", "HEAD", cwd=self.work), None

    def _gate(self, base, tip):
        self.gates_run += 1
        env = dict(os.environ, LANDING_BASE=base, LANDING_TIP=tip)
        got = subprocess.run(["bash", "-c", self.gate], cwd=self.work, env=env,
                             capture_output=True, timeout=6 * 3600)
        return got.returncode

    def claims_fence(self, record):
        tokens = record.get("claims") or {}
        if not tokens:
            return True
        sys.path.insert(0, str(ROOT / "tools"))
        import claims
        return all(claims.holds(int(rva, 16), token, root=self.repo) for rva, token in tokens.items())

    # ---- one pass -------------------------------------------------------
    def recover(self):
        path = self.state / "state.json"
        if not path.exists():
            return
        data = json.loads(path.read_text(encoding="utf-8"))
        if data.get("phase") == "publishing":
            tip = self.snapshot()
            landed = git("merge-base", "--is-ancestor", data["tip"], tip, cwd=self.repo,
                         check=False).returncode == 0
            if landed:
                self._receipts(data["units"], data["base"], data["tip"], data.get("gate_exit", 0),
                               note="recovered after a crash")
        path.unlink()

    def run_once(self, max_batch=20, publish=True, attempts=3):
        """Land up to `max_batch` queued units. Returns {landed, rejected}."""
        self.recover()
        records = {r["id"]: r for r in self.queued()[:max_batch]}
        result = {"landed": [], "rejected": []}
        for unit, record in list(records.items()):
            if not self.fence(record):
                self._finish(unit, "rejected", reason="claim-lost")
                result["rejected"].append(unit)
                del records[unit]
        for _ in range(attempts):
            if not records:
                return result
            base = self.snapshot()
            self._phase(phase="verifying", base=base, units=list(records))
            order = list(records)
            while True:                          # drop units that do not apply at all
                tip, bad = self._apply(base, order)
                if not bad:
                    break
                self._finish(bad, "rejected", reason="conflict", snapshot=base)
                result["rejected"].append(bad)
                order.remove(bad)
                del records[bad]
            if not order:
                return result
            gate_exit = {}

            def verify(prefix):
                tip, bad = self._apply(base, prefix)
                if bad:
                    return False
                code = self._gate(base, tip)
                gate_exit[tuple(prefix)] = code
                return code == 0
            good, bad = bisect(order, verify)
            for unit in bad:
                self._finish(unit, "rejected", reason="gate", snapshot=base)
                result["rejected"].append(unit)
                del records[unit]
            if not good:
                return result
            tip, _ = self._apply(base, good)
            if not publish:
                return dict(result, would_land=good, tip=tip)
            self._phase(phase="publishing", base=base, tip=tip, units=good, gate_exit=0)
            pushed = git("push", "-q", self.remote, f"{tip}:refs/heads/{self.branch}",
                         cwd=self.work, check=False)
            if pushed.returncode == 0:
                self._receipts(good, base, tip, 0)
                (self.state / "state.json").unlink()
                result["landed"] += good
                for unit in good:
                    del records[unit]
                return result
            (self.state / "state.json").unlink()   # master moved: redo on the new snapshot
        return result

    def _receipts(self, units, base, tip, gate_exit, note=""):
        commits = out("rev-list", "--reverse", f"{base}..{tip}", cwd=self.repo).split()
        tree = out("rev-parse", f"{tip}^{{tree}}", cwd=self.repo)
        for unit, commit in zip(units, commits):
            receipt = dict(unit=unit, snapshot=base, batch_tip=tip, commit=commit, tree=tree,
                           gate=self.gate, gate_exit=gate_exit, batch=len(units),
                           host=socket.gethostname(), note=note,
                           time=datetime.datetime.now(datetime.timezone.utc).isoformat())
            self._write(self.state / "receipts" / f"{unit}.json", receipt)
            if (self.state / "queue" / f"{unit}.json").exists():
                self._finish(unit, "landed", commit=commit, snapshot=base)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = ap.add_subparsers(dest="action", required=True)
    en = sub.add_parser("enqueue")
    en.add_argument("units", nargs="+", help="format-patch files or commits")
    en.add_argument("--claim", action="append", default=[], metavar="0xRVA=TOKEN")
    sub.add_parser("status")
    run = sub.add_parser("run-once")
    run.add_argument("--max-batch", type=int, default=20)
    run.add_argument("--gate", default=DEFAULT_GATE)
    run.add_argument("--no-publish", action="store_true")
    args = ap.parse_args(argv)
    service = Service(gate=getattr(args, "gate", DEFAULT_GATE))
    if args.action == "enqueue":
        meta = {"claims": dict(c.split("=", 1) for c in args.claim)} if args.claim else {}
        for unit in args.units:
            print(service.enqueue(unit, meta))
        return 0
    if args.action == "status":
        for sub_dir in ("queue", "landed", "rejected"):
            print(f"{sub_dir}: {len(list((service.state / sub_dir).glob('*.json')))}")
        return 0
    print(json.dumps(service.run_once(args.max_batch, publish=not args.no_publish), indent=1))
    return 0


if __name__ == "__main__":
    sys.exit(main())
