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
            --atomic` that updates master AND rewrites every unit's claim ref
            (lease and owner kept, `published` recorded; claims.publication)
            with --force-with-lease at the token just read. Because each
            claim ref is a real update, the server checks every old value in
            the same transaction: a takeover at any point before it, even
            inside the push's own pre-push hook, rejects the whole push.
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
            snapshot, tip and verification evidence before each step, and is
            removed only after receipts and queue settlement are written. On
            start (and after every push, whatever it reported), a
            `publishing` tip that is an ancestor of origin/master is recorded
            as landed with its receipts; anything else returns to the queue.

LESSONS FROM THE 2026-09-30 LANDING WINDOW (a header-wide stack published by
hand while master was frozen):
  SSH       A push whose pre-push hook runs ~15 minutes lost its SSH
            connection after "PRE-PUSH OK" (broken pipe) because the
            connection sat idle through the hook. The service pushes with
            ServerAliveInterval set (SSH_KEEPALIVE below; an existing
            GIT_SSH_COMMAND is left alone). HTTPS remotes are unaffected.
  TRACKED   The full gate regenerates targets/game/reverse/reloc_names.csv
            (tools/build.py), and the push hook's post-gate snapshot check
            refuses a tree whose tracked files the gate changed. So a gate
            that writes tracked files cannot verify the tip it runs on.
            Preferred fix: the gate writes generated tables under build/ and
            a separate, reviewed commit updates the tracked copy. Until
            then the service must not publish a tip the gate dirtied: it
            either (a) commits the regenerated file on top and gates THAT
            tip again (twice the gate time), or (b) refuses the batch with
            the dirty list. Publishing the pre-gate tip with a stale table
            would contradict the receipt. Not implemented yet: today the
            push hook refuses such a push, which is (b) after the fact.

AUTHENTICATION IS NOT SOLVED. model=, run= and host= in a receipt are values
a worker process could have set. Proposal: fleet_run signs a run receipt
(run id, host, the model parsed from the command it launched, brief sha,
touched rvas) with a per-host key the worker cannot read (a separate OS user,
or a signing daemon outside the cgroup), and pushes it to refs/receipts/<run>;
the service accepts a unit's model/run only when a verifying signature
covers that run and its touched rvas include the unit's rows.

WINDOW. For header-wide units `run-once --window` holds refs/landing/window
(tools/publish_window.py) for the pass; every pre-push hook refuses pushes to
master while someone else holds it, so the gated tip still fast-forwards,
and the publishing push reuses this host's gate evidence for the identical
tree (tools/gate_evidence.py, BFME_REUSE_GATE_EVIDENCE=1) instead of a second
17-minute gate. Cooperative only: see publish_window.py.

STATUS. Prototype: queue, bisect, am-based batching, two-point fencing with
an atomic leased push, exact-tip publication, receipts and recovery are
tested on fixture repositories (tools/tests/test_landing_service.py,
including the 2026-09-29 audit reproductions). It does not run anywhere yet;
seats still push directly.

  python3 tools/landing_service.py enqueue <patch-file | commit> [--claim 0xRVA=LEASE ...]
  python3 tools/landing_service.py status
  python3 tools/landing_service.py enqueue A..B          # a multi-commit (header-wide) unit
  python3 tools/landing_service.py drain [--interval 10] [--once] [--seed-cache DIR]
  python3 tools/landing_service.py run-once [--max-batch 20] [--gate CMD] [--no-publish] [--window]
"""
import argparse
import datetime
import hashlib
import json
import os
import platform
import re
import shutil
import socket
import subprocess
import sys
import threading
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
STATE = ROOT / "build" / "landing"
# keep an SSH push alive through a long pre-push hook (see LESSONS above)
SSH_KEEPALIVE = "ssh -o ServerAliveInterval=30 -o ServerAliveCountMax=60"
DEFAULT_GATE = ('printf "refs/heads/master %s refs/heads/master %s\\n" "$LANDING_TIP" "$LANDING_BASE" '
                '| bash .githooks/pre-push origin origin')


def git(*args, cwd, check=True, input_bytes=None, timeout=600):
    env = dict(os.environ)
    env.setdefault("GIT_SSH_COMMAND", SSH_KEEPALIVE)
    got = subprocess.run(["git", *args], cwd=cwd, capture_output=True, input=input_bytes,
                         timeout=timeout, env=env)
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
        if Path(patch).exists():
            data = Path(patch).read_bytes()
        elif ".." in str(patch):
            # a multi-commit unit (a header-wide stack): the whole range, applied
            # and gated as one; `git am` takes the mbox of several patches
            data = git("format-patch", "--stdout", str(patch), cwd=self.repo).stdout
        else:
            data = git("format-patch", "-1", "--stdout", patch, cwd=self.repo).stdout
        commits = len(re.findall(rb"^From [0-9a-f]{40} ", data, re.MULTILINE)) or 1
        unit = hashlib.sha256(data).hexdigest()[:20]
        if any((self.state / d / f"{unit}.json").exists() for d in ("queue", "landed", "rejected")):
            return unit
        (self.state / "queue" / f"{unit}.patch").write_bytes(data)
        record = dict(meta or {}, id=unit, enqueued=time.time(), commits=commits)
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

    def _unit_checks(self, base, tip, units):
        """A unit may carry its own check (`verify`, a command run in the
        service worktree at the batch tip) with the files it needs
        (`attach`: {worktree-relative dest: source dir}); provider_seat hands
        in `provider_repair.py check` with its brief and before-snapshot, so
        the provider verdict is re-derived on the exact rebased tree. The
        first failure fails the batch, and bisect isolates the unit."""
        for record in units:
            if not record.get("verify"):
                continue
            for dest, src in (record.get("attach") or {}).items():
                target = self.work / dest
                if target.exists():
                    shutil.rmtree(target)
                shutil.copytree(src, target)
            env = dict(os.environ, LANDING_BASE=base, LANDING_TIP=tip)
            got = subprocess.run(["bash", "-c", record["verify"]], cwd=self.work, env=env,
                                 stdout=subprocess.PIPE, stderr=subprocess.STDOUT, timeout=6 * 3600)
            with (self.state / "logs" / f"{tip}.log").open("ab") as handle:
                handle.write(f"\n--- unit {record['id']}: {record['verify']}\n".encode() + got.stdout)
            if got.returncode:
                return got.returncode
        return 0

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
    def recover(self, note=""):
        """Settle a journalled publication: if its tip is on the branch, write
        the receipts and move the units to landed/, THEN drop the journal (a
        failure before that leaves it for the next start). Returns the units
        it recorded as landed."""
        path = self.state / "state.json"
        if not path.exists():
            return []
        data = json.loads(path.read_text(encoding="utf-8"))
        done = []
        if data.get("phase") == "publishing":
            tip = self.snapshot()
            if git("merge-base", "--is-ancestor", data["tip"], tip, cwd=self.repo,
                   check=False).returncode == 0:
                self._receipts(data["units"], data["base"], data["tip"], data.get("verified") or {},
                               note=note)
                done = list(data["units"])
                self._release(data.get("claims") or {})
        path.unlink()
        return done

    def _release(self, published):
        """The landing is on the branch: delete each claim ref we rewrote at
        publication, compare-and-swap on the exact commit we wrote, so a
        claim anyone took since is untouched. A failed delete just expires."""
        for ref, sha in sorted(published.items()):
            git("push", "-q", f"--force-with-lease={ref}:{sha}", self.remote, f":{ref}",
                cwd=self.repo, check=False)

    def _reject(self, result, records, unit, reason, **extra):
        self._finish(unit, "rejected", reason=reason, **extra)
        result["rejected"].append(unit)
        records.pop(unit, None)

    def run_once(self, max_batch=20, publish=True, attempts=3, window=False, window_minutes=None,
                 max_hold=300):
        """Land up to `max_batch` queued units. Returns {landed, rejected}.

        window=True holds the cooperative publish window (publish_window.py)
        for the pass: master is quiet while the batch is gated, so the
        verified tip still fast-forwards afterwards, and the publishing push
        reuses this host's gate evidence for the identical tree. The window
        is a short lease (publish_window.LEASE_MINUTES) renewed every third
        of it while the pass works, closed in `finally` on success or
        failure; no new pass starts after `max_hold` seconds of holding
        (the rest stays queued), and the hold time is in the result."""
        if not window:
            return self._run_once(max_batch, publish, attempts)
        import publish_window
        minutes = window_minutes or publish_window.LEASE_MINUTES
        opened = time.time()
        nonce = publish_window.open_window(minutes, purpose="landing_service batch",
                                           remote=self.remote, root=self.repo)
        saved = {k: os.environ.get(k) for k in (publish_window.TOKEN_ENV, "BFME_REUSE_GATE_EVIDENCE")}
        os.environ[publish_window.TOKEN_ENV] = nonce
        os.environ["BFME_REUSE_GATE_EVIDENCE"] = "1"
        done = threading.Event()
        lost = []

        def renew():
            while not done.wait(minutes * 60 / 3):
                if publish_window.renew_window(nonce, minutes, remote=self.remote, root=self.repo) is None:
                    lost.append(time.time())
                    return
        renewer = threading.Thread(target=renew, daemon=True)
        renewer.start()
        result = {}
        try:
            result = self._run_once(max_batch, publish, attempts, deadline=opened + max_hold)
            return result
        finally:
            done.set()
            renewer.join(timeout=30)
            for k, v in saved.items():
                if v is None:
                    os.environ.pop(k, None)
                else:
                    os.environ[k] = v
            publish_window.close_window(nonce, remote=self.remote, root=self.repo)
            held = round(time.time() - opened, 1)
            result.update(window=nonce, window_held_seconds=held,
                          **({"window_lost": True} if lost else {}))
            with (self.state / "windows.log").open("a", encoding="utf-8") as handle:
                handle.write(json.dumps({"nonce": nonce, "opened": int(opened), "held": held,
                                         "landed": len(result.get("landed", [])),
                                         "rejected": len(result.get("rejected", [])),
                                         "lost": bool(lost)}) + "\n")

    def _run_once(self, max_batch=20, publish=True, attempts=3, deadline=None):
        recovered = self.recover(note="recovered after a crash")
        records = {r["id"]: r for r in self.queued()[:max_batch]}
        result = {"landed": recovered, "rejected": []}
        for unit, record in list(records.items()):
            if not self.fence(record):
                self._reject(result, records, unit, "claim-lost")
        for _ in range(attempts + len(records)):
            if not records:
                return result
            if deadline and time.time() > deadline:
                return dict(result, deferred=sorted(records))   # stays queued for the next window
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
                    code = self._unit_checks(base, tip, [records[u] for u in prefix])
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
            # Each claim ref is REWRITTEN (lease kept, publication recorded) with
            # an expected-token lease in the same --atomic push as master: a
            # no-op refspec is only checked against the ref advertisement, so
            # a takeover after it still published (review 2026-09-30). A real
            # update makes the server check every old value in one transaction.
            import claims
            spec = [f"--force-with-lease={ref}:{token}" for ref, token in sorted(leases.items())]
            published = {ref: claims.publication(token, tip, root=self.repo)
                         for ref, token in sorted(leases.items())}
            refs = [f"{sha}:{ref}" for ref, sha in published.items()]
            # The journal outlives the push until receipts and queue
            # settlement are written; recover() finishes an interrupted one.
            self._phase(phase="publishing", base=base, tip=tip, units=good, verified=evidence,
                        claims=published)
            git("push", "-q", "--atomic", *spec, self.remote,
                f"{tip}:refs/heads/{self.branch}", *refs, cwd=self.work, check=False)
            landed = self.recover()
            if landed:
                result["landed"] += landed
                for unit in landed:
                    records.pop(unit, None)
                return result
            # master moved or a claim changed under the lease: re-read, redo
        return result

    def _commits_of(self, unit):
        for where in ("queue", "landed", "rejected"):
            path = self.state / where / f"{unit}.json"
            if path.exists():
                return int(json.loads(path.read_text(encoding="utf-8")).get("commits", 1))
        return 1

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
        spans, at = [], 0
        for unit in units:
            count = self._commits_of(unit)
            spans.append((unit, commits[at:at + count]))
            at += count
        for unit, own in spans:
            commit = own[-1] if own else None
            receipt = dict(unit=unit, snapshot=base, batch_tip=tip, commit=commit, commits=own,
                           tree=tree,
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
    en.add_argument("units", nargs="+", help="format-patch files, commits, or A..B ranges (one unit each)")
    en.add_argument("--claim", action="append", default=[], metavar="0xRVA=LEASE",
                    help="a claim the unit was built under: its lease id (claims.ClaimResult.leases)")
    sub.add_parser("status")
    run = sub.add_parser("run-once")
    run.add_argument("--max-batch", type=int, default=20)
    run.add_argument("--gate", default=DEFAULT_GATE)
    run.add_argument("--no-publish", action="store_true")
    run.add_argument("--window", action="store_true",
                     help="hold the cooperative publish window for the pass (header-wide units)")
    drain = sub.add_parser("drain", help="land the queue under the window, now and every N minutes")
    drain.add_argument("--interval", type=float, default=10, help="minutes between passes")
    drain.add_argument("--once", action="store_true", help="one pass, then exit")
    drain.add_argument("--max-batch", type=int, default=20)
    drain.add_argument("--gate", default=DEFAULT_GATE)
    drain.add_argument("--seed-cache", metavar="DIR",
                       help="a warm build/match to copy into the service worktree once")
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
    if args.action == "drain":
        return drain(service, args.interval, args.once, args.max_batch, args.seed_cache)
    print(json.dumps(service.run_once(args.max_batch, publish=not args.no_publish,
                                      window=args.window), indent=1))
    return 0


def drain(service, interval=10, once=False, max_batch=20, seed=None):
    """The landing drainer: whenever the queue is non-empty, one windowed
    pass lands up to `max_batch` units with ONE gate. The service worktree
    (state/wt) persists between passes, so its object cache stays warm;
    `seed` copies a warm build/match into it the first time."""
    while True:
        if service.queued():
            if seed and not (service.work / "build" / "match").exists():
                base = service.snapshot()
                service._worktree(base)
                shutil.copytree(seed, service.work / "build" / "match")
            started = time.time()
            try:
                result = service.run_once(max_batch, window=True)   # short lease, renewed, closed
            except Exception as error:  # noqa: BLE001 -- a held window is closed by run_once
                result = {"error": str(error)}
            print(json.dumps(dict(result, seconds=round(time.time() - started, 1))), flush=True)
        if once:
            return 0
        time.sleep(interval * 60)


if __name__ == "__main__":
    sys.exit(main())
