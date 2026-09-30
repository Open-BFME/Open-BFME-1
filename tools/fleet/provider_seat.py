#!/usr/bin/env python3
"""One pass of the `provider` fleet lane: serve, repair, check, land or abandon.

The lane is a script, not a model session: tools/provider_repair.py decides.
  next     serves and claims ONE link-selection conflict (census index)
  apply    removes the competing legacy definition(s)
  check    byte gate + objdiff + strict harness: PASS or FAIL, with a receipt
  land     PASS: commit exactly the edited competitor sources (hooks run), push
           to master, confirm by ancestry, release the claim by its lease
  abandon  FAIL (or a commit the hooks refuse): restore, record a blocked
           verdict, release the claim
No add_match: the tool's own PASS/FAIL is the verdict.

The seat works in its OWN worktree (build/wt_provider_seat<N>, detached on
origin/master), never the shared fleet checkout: it commits and pushes, and
the other seats' in-flight edits must not ride along. The census index is
read from the main checkout (build/link_census/link_index.pkl).

Receipts: the commit message carries the model (BFME_MODEL, else
script/provider_repair), the check receipt's sha256, and a
`Claim-Lease: 0xRVA=<lease>` trailer so `claims.py release --landed SHA`
can release exactly this claim.

Exit: 0 landed, 1 failed and abandoned, 2 passed but could not be pushed
(patch saved under the worktree's build/provider_seat/unpushed/, claim left
to expire),
3 nothing to serve. seat.sh counts 1 and 2 toward the dry-streak pause.

  python3 tools/fleet/provider_seat.py --seat 1 [--worktree DIR] [--index PKL]
"""
import argparse
import hashlib
import json
import os
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

LANDED, FAILED, UNPUSHED, NOTHING = 0, 1, 2, 3
PUSH_ATTEMPTS = 5


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
    git(path, "checkout", "-q", "--detach", "FETCH_HEAD", check=True)
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


def land(wt, facts, receipt_path):
    sources = sorted({c["source"] for c in facts["competitors"]})
    receipt = Path(receipt_path).read_bytes() if Path(receipt_path).exists() else b""
    gate = (json.loads(receipt).get("steps", {}).get("gate", {}).get("result", "?")
            if receipt else "?")
    lease = lease_of(wt, facts["rva"])
    rva = f"0x{int(facts['rva'], 16):08X}"
    message = (f"provider: select retail {facts['symbol']} at {rva}\n\n"
               f"tools/provider_repair.py check PASS; {gate}\n"
               f"removed the competing definition from: {', '.join(sources)}\n"
               f"owner: {facts['owner']['source']}\n"
               f"receipt sha256: {hashlib.sha256(receipt).hexdigest()}\n\n"
               f"Model: {model()}\n"
               + (f"Claim-Lease: {rva}={lease}\n" if lease else ""))
    git(wt, "add", "--", *sources, check=True)
    committed = subprocess.run(["git", "commit", "-q", "-F", "-"], cwd=wt, input=message,
                               capture_output=True, text=True)
    if committed.returncode:
        abandon(wt, facts, "commit refused by hooks: " + (committed.stderr or committed.stdout)[-300:],
                sources)
        return FAILED
    sha = git(wt, "rev-parse", "HEAD").stdout.strip()
    for attempt in range(PUSH_ATTEMPTS):
        pulled = git(wt, "pull", "-q", "--rebase", "origin", "master")
        if pulled.returncode:
            git(wt, "rebase", "--abort")
            break
        sha = git(wt, "rev-parse", "HEAD").stdout.strip()
        if git(wt, "push", "-q", "origin", "HEAD:master").returncode == 0:
            git(wt, "fetch", "-q", "origin", "master")
            if git(wt, "merge-base", "--is-ancestor", sha, "FETCH_HEAD").returncode == 0:
                # the worktree's own claims.py: its checkout, its claims mirror
                released = run([sys.executable, str(Path(wt) / "tools" / "claims.py"), "release",
                                "--landed", sha], wt)
                log(f"landed {facts['symbol']} as {sha[:10]} (on origin/master); "
                    f"{released.stdout.strip()}")
                return LANDED
        log(f"push attempt {attempt + 1} for {sha[:10]} did not land; rebasing")
    saved = Path(wt) / "build" / "provider_seat" / "unpushed"
    saved.mkdir(parents=True, exist_ok=True)
    patch = saved / f"{rva}.patch"
    patch.write_bytes(subprocess.run(["git", "format-patch", "-1", "--stdout", sha], cwd=wt,
                                     capture_output=True).stdout)
    git(wt, "reset", "-q", "--hard", "FETCH_HEAD")
    log(f"{facts['symbol']} passed but could not be pushed; patch {patch}; claim left to expire")
    return UNPUSHED


def once(wt, index=None):
    served = tool(wt, "next", "--model", model(), *(["--index", str(index)] if index else []))
    if served.returncode:
        log(served.stdout.strip().splitlines()[-1] if served.stdout.strip() else "nothing to serve")
        return NOTHING
    brief = re.search(r"^\s*brief\s+(\S.*)$", served.stdout, re.MULTILINE)
    if not brief:
        log("next printed no brief path")
        return NOTHING
    facts = json.loads((Path(wt) / brief.group(1).strip()).read_text(encoding="utf-8"))
    log(f"serving {facts['symbol']} at {facts['rva']}")
    applied = tool(wt, "apply", facts["symbol"])
    if applied.returncode:
        abandon(wt, facts, "apply failed: " + (applied.stderr or applied.stdout)[-300:])
        return FAILED
    checked = tool(wt, "check", facts["symbol"])
    receipt = Path(wt) / "build" / "provider_repair" / f"0x{int(facts['rva'], 16):08X}" / "receipt.json"
    if checked.returncode:
        abandon(wt, facts, "check FAIL: " + checked.stdout.strip().splitlines()[-1][:300]
                if checked.stdout.strip() else "check FAIL")
        return FAILED
    return land(wt, facts, receipt)


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
