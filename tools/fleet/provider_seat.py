#!/usr/bin/env python3
"""One pass of the `provider` fleet lane: serve, repair, check, hand off or abandon.

The lane is a script, not a model session: tools/provider_repair.py decides.
  next     serves and claims ONE link-selection conflict (census index)
  apply    removes the competing legacy definition(s)
  check    byte gate + objdiff + strict harness: PASS or FAIL, with a receipt
  hand off PASS: commit exactly the edited competitor sources (hooks run) and
           ENQUEUE that commit with the landing service; the seat never races
           master. The unit carries the claim lease, the check to run again
           on the rebased tree (`provider_repair.py check`, with this pass's
           brief and before-snapshot attached) and the model. The landing
           drainer (`landing_service.py drain`) rebases, gates, re-checks and
           publishes it under the publish window, and releases the claim
           only once the landing is on origin/master.
  abandon  FAIL (or a commit the hooks refuse): restore, record a blocked
           verdict, release the claim

WHY NOT RACE. Measured 2026-09-30 (build/wt_measure/.../pass3.log): a pass
for ??0BezierSegment@@QAE@XZ PASSED, then lost the push race 5 times in a
row -- every rebase brought an upstream game-source change, forcing a
multi-minute re-check while master moved again. One drainer landing a batch
under the window pays the gate once.

The seat works in its OWN worktree (build/wt_provider_seat<N>, detached on
origin/master), never the shared fleet checkout. The census index is read
from the main checkout (build/link_census/link_index.pkl).

Exit: 0 handed to the landing queue, 1 failed and abandoned (or dropped for
want of a lease), 3 nothing to serve. seat.sh counts 1 toward the dry-streak
pause.

  python3 tools/fleet/provider_seat.py --seat 1 [--worktree DIR] [--index PKL]
"""
import argparse
import hashlib
import json
import os
import re
import shlex
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

QUEUED, FAILED, NOTHING = 0, 1, 3
MASTER = "refs/remotes/origin/master"


def run(cmd, cwd, check=False):
    got = subprocess.run(cmd, cwd=cwd, capture_output=True, text=True, errors="replace")
    if check and got.returncode:
        raise RuntimeError(f"{' '.join(map(str, cmd))}: {got.stderr.strip()[-500:]}")
    return got


def git(cwd, *args, check=False):
    return run(["git", *args], cwd, check)


def model():
    value = os.environ.get("BFME_MODEL", "")
    return value if re.fullmatch(r"[A-Za-z0-9._/-]{1,60}", value) else "script/provider_repair"


def log(msg):
    print(f"provider_seat: {msg}", flush=True)


def landing():
    """This host's landing queue (tools/landing_service.py, state build/landing)."""
    import landing_service
    return landing_service.Service()


def worktree(path, main=ROOT):
    """The seat's own detached worktree on a fresh origin/master."""
    path = Path(path)
    if not (path / ".git").exists():
        git(main, "fetch", "-q", "origin", "master", check=True)
        git(main, "worktree", "add", "-q", "--detach", str(path), "FETCH_HEAD", check=True)
    git(path, "fetch", "-q", "origin", "master", check=True)
    # This worktree holds only this seat's work; a leftover is a crashed pass.
    git(path, "rebase", "--abort")
    git(path, "reset", "-q", "--hard", check=True)
    # origin/master, never FETCH_HEAD: every claims fetch rewrites FETCH_HEAD
    git(path, "checkout", "-q", "--detach", MASTER, check=True)
    return path


def tool(wt, *args):
    return run([sys.executable, str(Path(wt) / "tools" / "provider_repair.py"), *args], wt)


def abandon(wt, facts, reason, sources=()):
    if sources:
        git(wt, "reset", "-q", "--", *sources)          # unstage, so checkout restores HEAD's copy
    got = tool(wt, "abandon", facts["symbol"], "--model", model(), "--reason", reason[:300])
    log(f"abandoned {facts['symbol']} ({reason[:160]}): exit {got.returncode}")


def lease_of(wt, rva):
    import claims
    return claims.current_lease(int(rva, 16), root=wt)


def hand_off(wt, facts, work_dir):
    sources = sorted({c["source"] for c in facts["competitors"]})
    rva = f"0x{int(facts['rva'], 16):08X}"
    lease = lease_of(wt, facts["rva"])
    if not lease:
        # fail closed: without our lease nothing proves the body is still
        # ours. Not a verdict on the body: restore and hand off nothing.
        git(wt, "checkout", "--", *sources)
        log(f"dropped {facts['symbol']}: this checkout holds no claim lease for it")
        return FAILED
    receipt = Path(work_dir) / "receipt.json"
    try:
        gate = json.loads(receipt.read_text(encoding="utf-8"))["steps"]["gate"]["result"]
    except (OSError, ValueError, KeyError):
        gate = "?"
    digest = hashlib.sha256(receipt.read_bytes()).hexdigest() if receipt.exists() else "?"
    message = (f"provider: select retail {facts['symbol']} at {rva}\n\n"
               f"tools/provider_repair.py check PASS; {gate}\n"
               f"removed the competing definition from: {', '.join(sources)}\n"
               f"owner: {facts['owner']['source']}\n"
               f"seat receipt sha256: {digest} (the landing service checks again on the "
               f"rebased tree)\n\n"
               f"Model: {model()}\n"
               f"Claim-Lease: {rva}={lease}\n")
    git(wt, "add", "--", *sources, check=True)
    committed = subprocess.run(["git", "commit", "-q", "-F", "-"], cwd=wt, input=message,
                               capture_output=True, text=True)
    if committed.returncode:
        abandon(wt, facts, "commit refused by hooks: " + (committed.stderr or committed.stdout)[-300:],
                sources)
        return FAILED
    queued = Path(wt) / "build" / "provider_seat" / "queued"
    queued.mkdir(parents=True, exist_ok=True)
    patch = queued / f"{rva}.patch"
    patch.write_bytes(subprocess.run(["git", "format-patch", "-1", "--stdout", "HEAD"], cwd=wt,
                                     capture_output=True, check=True).stdout)
    rel = f"build/provider_repair/{rva}"
    unit = landing().enqueue(patch, {
        "claims": {rva: lease},
        "verify": f"{shlex.quote(sys.executable)} tools/provider_repair.py check "
                  f"{shlex.quote(facts['symbol'])}",
        "attach": {rel: str(Path(work_dir).resolve())},
        "model": model(), "source": "provider_seat", "symbol": facts["symbol"]})
    # the unit is the landing service's now; this worktree goes back to master
    git(wt, "reset", "-q", "--hard", MASTER)
    log(f"queued {facts['symbol']} as landing unit {unit} (claim kept until it lands)")
    return QUEUED


def once(wt, index=None):
    served = tool(wt, "next", "--model", model(), *(["--index", str(index)] if index else []))
    if served.returncode:
        log(served.stdout.strip().splitlines()[-1] if served.stdout.strip() else "nothing to serve")
        return NOTHING
    brief = re.search(r"^\s*brief\s+(\S.*)$", served.stdout, re.MULTILINE)
    if not brief:
        log("next printed no brief path")
        return NOTHING
    brief_path = Path(wt) / brief.group(1).strip()
    facts = json.loads(brief_path.read_text(encoding="utf-8"))
    log(f"serving {facts['symbol']} at {facts['rva']}")
    applied = tool(wt, "apply", facts["symbol"])
    if applied.returncode:
        abandon(wt, facts, "apply failed: " + (applied.stderr or applied.stdout)[-300:])
        return FAILED
    checked = tool(wt, "check", facts["symbol"])
    if checked.returncode:
        abandon(wt, facts, "check FAIL: " + checked.stdout.strip().splitlines()[-1][:300]
                if checked.stdout.strip() else "check FAIL")
        return FAILED
    return hand_off(wt, facts, brief_path.parent)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--seat", default="1")
    ap.add_argument("--worktree")
    ap.add_argument("--index", default=str(ROOT / "build" / "link_census" / "link_index.pkl"))
    args = ap.parse_args(argv)
    wt = worktree(args.worktree or ROOT / "build" / f"wt_provider_seat{args.seat}")
    index = Path(args.index)
    return once(wt, index if index.exists() else None)


if __name__ == "__main__":
    sys.exit(main())
