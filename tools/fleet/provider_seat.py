#!/usr/bin/env python3
"""One pass of the `provider` fleet lane: serve, repair, check, land or abandon.

The lane is a script, not a model session: tools/provider_repair.py decides.
  next     serves and claims ONE link-selection conflict (census index)
  apply    removes the competing legacy definition(s)
  check    byte gate + objdiff + strict harness: PASS or FAIL, with a receipt
  land     PASS: commit exactly the edited competitor sources (hooks run),
           rebase; if the rebase changed any receipt input or any other
           verification input (ledgers, headers, inputs/, tools/, hooks),
           run `check` AGAIN on the rebased tree (FAIL: retract and
           abandon) and re-commit with the NEW receipt's digest; right
           before each push re-validate that digest and the lease (lost:
           retract, publish nothing); push, confirm by ancestry, release
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


# Upstream changes that can alter what `check` proved even when none of the
# receipt's input files changed: headers, the reference/shim tree, the
# toolchain, and the tools that compile and judge.
# An upstream change needs no second `check` only if it is prose or banked
# evidence. Everything else -- ledgers (functions.csv, symbols.csv and every other file
# under targets/), headers, inputs/, tools/, hooks, build scripts -- is a
# verification input (review 2026-09-30: a symbols.csv change after check
# landed with one check; then an upstream .cpp that a checked .cpp #includes
# landed with one check, so no game source is exempt). Unknown means recheck.
HARMLESS_PREFIXES = ("docs/", "targets/game/reverse/attempts/")
HARMLESS_FILES = ("README.md", "AGENTS.md", "targets/game/reverse/re_attempts.log")


def recheck_reasons(wt, old_base, new_base):
    """Upstream paths between the checked base and the new one that the
    check could have read."""
    if old_base == new_base:
        return []
    changed = git(wt, "diff", "--name-only", old_base, new_base).stdout.split()
    out = []
    for path in changed:
        if path in HARMLESS_FILES or path.startswith(HARMLESS_PREFIXES):
            continue
        out.append(path)
    return out


def receipt_inputs(receipt_path):
    try:
        return json.loads(Path(receipt_path).read_text(encoding="utf-8")).get("inputs") or {}
    except (OSError, ValueError):
        return {}


def stale(wt, receipt_path, old_base, new_base):
    """Why the receipt no longer describes the tree about to be published, or
    None: every recorded input hash must match the file as it is now, and no
    verification input may have changed upstream since the checked base."""
    if not Path(receipt_path).exists():
        return "no readable receipt"
    inputs = receipt_inputs(receipt_path)
    if not inputs:
        return "the receipt records no input hashes"
    for path, digest in sorted(inputs.items()):
        try:
            now = hashlib.sha256((Path(wt) / path).read_bytes()).hexdigest()
        except OSError:
            return f"{path} is gone"
        if now != digest:
            return f"{path} changed since check"
    changed = recheck_reasons(wt, old_base, new_base)
    if changed:
        return f"upstream changed {changed[0]}" + (f" (+{len(changed) - 1})" if len(changed) > 1 else "")
    return None


def retract(wt, facts, sources, reason, record=True):
    """Undo our unpublished commit, then abandon (or just restore)."""
    git(wt, "reset", "-q", "--soft", "HEAD~1")
    git(wt, "reset", "-q", "--", *sources)
    if record:
        abandon(wt, facts, reason)
    else:
        git(wt, "checkout", "--", *sources)
        log(f"dropped {facts['symbol']}: {reason}")


def digest(receipt_path):
    try:
        return hashlib.sha256(Path(receipt_path).read_bytes()).hexdigest()
    except OSError:
        return None


def compose(facts, sources, lease, receipt_path):
    """The commit message: the receipt summary and the digest of the receipt
    file AS IT IS NOW (recomposed after every re-check)."""
    rva = f"0x{int(facts['rva'], 16):08X}"
    try:
        gate = json.loads(Path(receipt_path).read_text(encoding="utf-8")).get(
            "steps", {}).get("gate", {}).get("result", "?")
    except (OSError, ValueError):
        gate = "?"
    return (f"provider: select retail {facts['symbol']} at {rva}\n\n"
            f"tools/provider_repair.py check PASS; {gate}\n"
            f"removed the competing definition from: {', '.join(sources)}\n"
            f"owner: {facts['owner']['source']}\n"
            f"receipt sha256: {digest(receipt_path)}\n\n"
            f"Model: {model()}\n"
            f"Claim-Lease: {rva}={lease}\n")


def published_digest(wt):
    found = re.search(r"^receipt sha256: ([0-9a-f]{64})$",
                      git(wt, "log", "-1", "--format=%B").stdout, re.MULTILINE)
    return found.group(1) if found else None


def commit(wt, message, amend=False):
    return subprocess.run(["git", "commit", "-q", *(["--amend"] if amend else []), "-F", "-"],
                          cwd=wt, input=message, capture_output=True, text=True)


def land(wt, facts, receipt_path):
    sources = sorted({c["source"] for c in facts["competitors"]})
    rva = f"0x{int(facts['rva'], 16):08X}"
    lease = lease_of(wt, facts["rva"])
    if not lease:
        # fail closed: without our lease nothing proves the body is still
        # ours. Not a verdict on the body (someone else may own it now):
        # restore the sources and publish nothing.
        git(wt, "checkout", "--", *sources)
        log(f"dropped {facts['symbol']}: this checkout holds no claim lease for it")
        return FAILED
    git(wt, "add", "--", *sources, check=True)
    committed = commit(wt, compose(facts, sources, lease, receipt_path))
    if committed.returncode:
        abandon(wt, facts, "commit refused by hooks: " + (committed.stderr or committed.stdout)[-300:],
                sources)
        return FAILED
    checked_base = git(wt, "rev-parse", "HEAD~1").stdout.strip()   # the tree `check` judged
    sha = git(wt, "rev-parse", "HEAD").stdout.strip()
    for attempt in range(PUSH_ATTEMPTS):
        pulled = git(wt, "pull", "-q", "--rebase", "origin", "master")
        if pulled.returncode:
            git(wt, "rebase", "--abort")
            break
        base = git(wt, "rev-parse", "HEAD~1").stdout.strip()
        # The rebase may have brought changes the check never saw (review
        # 2026-09-30: an owner-source change, then a symbols.csv change,
        # landed on a stale receipt).
        why = stale(wt, receipt_path, checked_base, base)
        if why:
            log(f"rebased onto {base[:10]}: {why}; checking again")
            again = tool(wt, "check", facts["symbol"])
            if again.returncode:
                retract(wt, facts, sources, f"check FAIL after rebase ({why}): "
                        + (again.stdout.strip().splitlines() or ["?"])[-1][:240])
                return FAILED
            checked_base = base
            amended = commit(wt, compose(facts, sources, lease, receipt_path), amend=True)
            if amended.returncode:
                retract(wt, facts, sources, "re-commit refused by hooks: "
                        + (amended.stderr or amended.stdout)[-240:])
                return FAILED
        sha = git(wt, "rev-parse", "HEAD").stdout.strip()
        # Immediately before the push: the message names THIS receipt, and the
        # receipt still describes this exact tree.
        if published_digest(wt) != digest(receipt_path) or stale(wt, receipt_path, checked_base, base):
            retract(wt, facts, sources, "receipt does not match the commit about to be pushed",
                    record=False)
            return FAILED
        # fail closed if the claim was lost while we checked or rebased
        import claims
        try:
            held = claims.lease_holder(int(facts["rva"], 16), lease, root=wt)
        except claims.ClaimsUnavailable:
            held = None
        if not held:
            retract(wt, facts, sources, "claim lease lost before publication", record=False)
            return FAILED
        if git(wt, "push", "-q", "origin", "HEAD:master").returncode == 0:
            git(wt, "fetch", "-q", "origin", "master")
            if git(wt, "merge-base", "--is-ancestor", sha, MASTER).returncode == 0:
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
    git(wt, "fetch", "-q", "origin", "master")
    git(wt, "reset", "-q", "--hard", MASTER)
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
