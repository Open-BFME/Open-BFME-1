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
            the claims it was built under ({rva: LEASE id}, tools/claims.py
            ClaimResult.leases -- the lease survives heartbeat renewals, the
            token does not, so queued metadata never goes stale by rotation),
            model/run/host as recorded, never trusted.
  QUEUE     A directory: queue/<id>.patch + <id>.json. Terminal states move
            the metadata to landed/ or rejected/ with the reason. Nothing is
            deleted, so a crash never loses a unit and a replay is harmless.
  BATCH     Take up to N queued units in arrival order. Rebase ONCE: reset a
            private worktree to the fetched origin/master (the snapshot) and
            `git am -3` the batch. A unit that does not apply is rejected
            (`conflict`) and the rest continue.
  FENCE     Twice. Before the batch, and again right before publication
            (a claim can be lost DURING a 17-minute gate), a unit whose lease
            origin no longer holds is rejected (`claim-lost`) and the batch
            is re-gated without it. The publication itself is one `git push
            --atomic` that updates master AND leases every unit's claim ref
            at its current token (--force-with-lease), so a takeover between
            that last read and the push rejects the whole push.
  GATE      Run the gate ONCE per batch on the exact batch tip: by default the
            repository's own .githooks/pre-push fed the ref line for
            snapshot..tip (protected_paths, conversion_gate, check_csv,
            identity, byte-verify of every affected selector), so the
            service proves exactly what a push would.
  BISECT    A red batch is split in halves; each half is re-gated on top of
            the units already accepted (bisect() below), so one bad unit
            costs O(log n) gates and never sinks its neighbours.
  PUBLISH   Push the EXACT commit object the gate verified (kept under
            refs/landing/verified), never a re-application: `git am` again
            makes a new commit with a new committer time. The push hook runs
            again; the verification cache makes the repeat cheap. If master
            moved, re-fetch and redo the batch on the new snapshot: a receipt
            is only ever for the snapshot it names.
  RECEIPT   receipts/<id>.json per landed unit: unit id, snapshot, the
            verified-and-published tip, the unit's commit, the tip's tree
            (every tracked source, header, config, tool, baseline, library
            and toolchain file) plus the subtree hash of each of those
            groups, the gate command, exit and log sha256, a manifest
            (sha256 per file) of the objects/images/maps the gate wrote, and
            the python/git versions and host. The landed sha is what
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

STATUS. Prototype: queue, bisect, am-based batching, two-point fencing with
an atomic leased push, exact-tip publication, receipts and recovery are
tested on fixture repositories (tools/tests/test_landing_service.py,
including the 2026-09-29 audit reproductions). It does not run anywhere yet;
seats still push directly.

  python3 tools/landing_service.py enqueue <patch-file | commit> [--claim 0xRVA=LEASE ...]
  python3 tools/landing_service.py status
  python3 tools/landing_service.py run-once [--max-batch 20] [--gate CMD] [--no-publish]
"""
import argparse
import datetime
import hashlib
import json
import os
import platform
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


# what a receipt names by subtree hash, beside the whole tree
VERIFIED_INPUTS = ("game", "inputs/reference", "inputs/toolchains", "inputs/baselines", "tools",
                   ".githooks", "targets/game/reverse", "build.sh", "build.cmd")
ARTIFACTS = (".obj", ".lib", ".exe", ".dll", ".map", ".pdb")


class LostClaim(RuntimeError):
    """A unit's claim is no longer its worker's."""


class Service:
    def __init__(self, repo=ROOT, state=None, remote="origin", branch="master", gate=DEFAULT_GATE,
                 fence=None, leases=None):
        self.repo = Path(repo)
        self.state = Path(state) if state else STATE
        self.remote, self.branch, self.gate = remote, branch, gate
        self.fence = fence or self.claims_fence
        self.leases = leases or self.claim_leases
        for sub in ("queue", "landed", "rejected", "receipts", "logs"):
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
        """Exit code of the gate on the worktree at `tip`; its output is kept
        in logs/<tip>.log for the receipt."""
        self.gates_run += 1
        env = dict(os.environ, LANDING_BASE=base, LANDING_TIP=tip)
        got = subprocess.run(["bash", "-c", self.gate], cwd=self.work, env=env,
                             stdout=subprocess.PIPE, stderr=subprocess.STDOUT, timeout=6 * 3600)
        (self.state / "logs" / f"{tip}.log").write_bytes(got.stdout or b"")
        return got.returncode

    def _artifacts(self, since):
        """{path: sha256} of build products the gate wrote in the worktree."""
        found = {}
        for path in sorted(self.work.rglob("*")):
            if path.suffix.lower() in ARTIFACTS and ".git" not in path.parts and path.is_file():
                if path.stat().st_mtime >= since - 1:
                    found[path.relative_to(self.work).as_posix()] = hashlib.sha256(
                        path.read_bytes()).hexdigest()
        return found

    def claims_fence(self, record):
        """True while origin still holds every claim the unit names."""
        return self.claim_leases(record) is not None

    def claim_leases(self, record):
        """{claim ref: current token} for the unit's claims, None if any is
        lost or expired. Accepts lease ids and (older units) tokens."""
        named = record.get("claims") or {}
        if not named:
            return {}
        sys.path.insert(0, str(ROOT / "tools"))
        import claims
        current = {}
        for rva, lease in named.items():
            token = claims.lease_holder(int(rva, 16), lease, root=self.repo)
            if not token:
                return None
            current[claims.ref_of(int(rva, 16))] = token
        return current

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
                self._receipts(data["units"], data["base"], data["tip"], data.get("verified") or {},
                               note="recovered after a crash")
        path.unlink()

    def _reject(self, result, records, unit, reason, **extra):
        self._finish(unit, "rejected", reason=reason, **extra)
        result["rejected"].append(unit)
        records.pop(unit, None)

    def run_once(self, max_batch=20, publish=True, attempts=3):
        """Land up to `max_batch` queued units. Returns {landed, rejected}."""
        self.recover()
        records = {r["id"]: r for r in self.queued()[:max_batch]}
        result = {"landed": [], "rejected": []}
        for unit, record in list(records.items()):
            if not self.fence(record):
                self._reject(result, records, unit, "claim-lost")
        for _ in range(attempts + len(records)):
            if not records:
                return result
            base = self.snapshot()
            self._phase(phase="verifying", base=base, units=list(records))
            order = list(records)
            while True:                          # drop units that do not apply at all
                tip, bad = self._apply(base, order)
                if not bad:
                    break
                self._reject(result, records, bad, "conflict", snapshot=base)
                order.remove(bad)
            if not order:
                return result
            verified = {}

            def verify(prefix):
                tip, bad = self._apply(base, prefix)
                if bad:
                    return False
                started = time.time()
                code = self._gate(base, tip)
                if code == 0:
                    verified[tuple(prefix)] = dict(tip=tip, started=started,
                                                   artifacts=self._artifacts(started))
                return code == 0
            good, bad = bisect(order, verify)
            for unit in bad:
                self._reject(result, records, unit, "gate", snapshot=base)
            if not good:
                return result
            if tuple(good) not in verified and not verify(good):
                continue                        # not reproducible as a whole: retry the pass
            evidence = verified[tuple(good)]
            tip = evidence["tip"]
            # keep the verified object alive; publication pushes THIS sha
            git("update-ref", "refs/landing/verified", tip, cwd=self.repo)
            if not publish:
                return dict(result, would_land=good, tip=tip)
            # fence again: a claim can be lost while the gate runs
            lost = [u for u in good if not self.fence(records[u])]
            leases = {}
            for unit in good:
                if unit in lost:
                    continue
                held = self.leases(records[unit])
                if held is None:
                    lost.append(unit)
                else:
                    leases.update(held)
            if lost:
                for unit in lost:
                    self._reject(result, records, unit, "claim-lost", snapshot=base)
                continue                        # re-gate without them
            self._phase(phase="publishing", base=base, tip=tip, units=good, verified=evidence)
            spec = [f"--force-with-lease={ref}:{token}" for ref, token in sorted(leases.items())]
            refs = [f"{token}:{ref}" for ref, token in sorted(leases.items())]
            pushed = git("push", "-q", "--atomic", *spec, self.remote,
                         f"{tip}:refs/heads/{self.branch}", *refs, cwd=self.work, check=False)
            (self.state / "state.json").unlink()
            if pushed.returncode == 0:
                self._receipts(good, base, tip, evidence)
                result["landed"] += good
                for unit in good:
                    del records[unit]
                return result
            # master moved or a claim changed under the lease: re-read, redo
        return result

    def _receipts(self, units, base, tip, evidence, note=""):
        commits = out("rev-list", "--reverse", f"{base}..{tip}", cwd=self.repo).split()
        tree = out("rev-parse", f"{tip}^{{tree}}", cwd=self.repo)
        inputs = {}
        for path in VERIFIED_INPUTS:
            got = git("rev-parse", f"{tip}:{path}", cwd=self.repo, check=False)
            if got.returncode == 0:
                inputs[path] = got.stdout.decode().strip()
        log = self.state / "logs" / f"{tip}.log"
        artifacts = evidence.get("artifacts") or {}
        manifest = json.dumps(artifacts, sort_keys=True).encode()
        (self.state / "receipts" / f"{tip}.artifacts.json").write_bytes(manifest)
        versions = dict(python=platform.python_version(),
                        git=out("--version", cwd=self.repo))
        for unit, commit in zip(units, commits):
            receipt = dict(unit=unit, snapshot=base, batch_tip=tip, commit=commit, tree=tree,
                           inputs=inputs, gate=self.gate, gate_exit=0,
                           gate_log_sha256=hashlib.sha256(log.read_bytes()).hexdigest()
                           if log.exists() else None,
                           artifacts=len(artifacts),
                           artifacts_sha256=hashlib.sha256(manifest).hexdigest(),
                           batch=len(units), host=socket.gethostname(), note=note,
                           versions=versions,
                           time=datetime.datetime.now(datetime.timezone.utc).isoformat())
            self._write(self.state / "receipts" / f"{unit}.json", receipt)
            if (self.state / "queue" / f"{unit}.json").exists():
                self._finish(unit, "landed", commit=commit, snapshot=base)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = ap.add_subparsers(dest="action", required=True)
    en = sub.add_parser("enqueue")
    en.add_argument("units", nargs="+", help="format-patch files or commits")
    en.add_argument("--claim", action="append", default=[], metavar="0xRVA=LEASE",
                    help="a claim the unit was built under: its lease id (claims.ClaimResult.leases)")
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
