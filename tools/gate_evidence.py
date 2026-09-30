#!/usr/bin/env python3
"""Reusable evidence that a wide push gate passed on an exact tree.

WHY. A header-wide change runs a ~17 minute gate in pre-push. The landing
service gates a batch tip once (by running pre-push itself) and then pushes
that tip, which runs pre-push AGAIN on the identical tree: 17 more minutes,
long enough for master to move and the push to lose the race. This records
that the gate passed on a tree so the publishing push can reuse it.

KEY. The commit's tree hash (every tracked source, header, tool, hook,
ledger, baseline and toolchain file), the subtree hashes of
inputs/toolchains, inputs/baselines, tools and .githooks (named explicitly
so a receipt shows them), the gate kind and the Python version.

SCOPE. A `full` record covers any later gate of the same tree. A `scoped`
record also stores the exact dependent selectors it verified and the
destination base they were computed against, and covers a later scoped gate
only when every requested selector is among them: the same tip pushed onto
an OLDER base has more changed headers and a wider dependent set (review
2026-09-30: a narrow record let a wider gate be skipped).

WHERE. `<git common dir>/bfme-gate-evidence/<tree>.<kind>.json`: shared by
the worktrees of one clone, never pushed, never trusted from another host.

OPT-IN. `check` only ever answers yes when BFME_REUSE_GATE_EVIDENCE=1 (the
landing service sets it for its own publishing push). Without it every push
gates exactly as before. Like any local file this can be forged by someone
who could equally push with --no-verify; it is a cache, not an attestation.

  python3 tools/gate_evidence.py record --commit SHA --kind full
  python3 tools/gate_evidence.py record --commit SHA --kind scoped --base BASE --selectors-file F
  python3 tools/gate_evidence.py check  --commit SHA --kind ...  (same flags)   # exit 0: reuse
"""
import argparse
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
NAMED = ("inputs/toolchains", "inputs/baselines", "tools", ".githooks")
ENABLE = "BFME_REUSE_GATE_EVIDENCE"


def _git(*args, root=None):
    got = subprocess.run(["git", *args], cwd=root or ROOT, capture_output=True, text=True)
    return got.stdout.strip() if got.returncode == 0 else None


def key(commit, root=None):
    """The facts a record must match, or None when the commit is unknown."""
    tree = _git("rev-parse", f"{commit}^{{tree}}", root=root)
    if not tree:
        return None
    return {"tree": tree, "python": platform.python_version(),
            "subtrees": {p: _git("rev-parse", f"{commit}:{p}", root=root) for p in NAMED}}


def _dir(root=None):
    common = _git("rev-parse", "--git-common-dir", root=root)
    base = Path(common) if Path(common).is_absolute() else Path(root or ROOT) / common
    return base / "bfme-gate-evidence"


def _path(tree, kind, root=None, selectors=None):
    if kind == "scoped":
        digest = hashlib.sha256("\n".join(sorted(selectors or [])).encode()).hexdigest()[:16]
        return _dir(root) / f"{tree}.scoped.{digest}.json"
    return _dir(root) / f"{tree}.{kind}.json"


def record(commit, kind, root=None, selectors=None, base=None):
    facts = key(commit, root)
    if not facts:
        raise SystemExit(f"gate_evidence: unknown commit {commit}")
    if kind == "scoped" and not selectors:
        raise SystemExit("gate_evidence: a scoped record needs the selectors it verified")
    path = _path(facts["tree"], kind, root, selectors)
    path.parent.mkdir(parents=True, exist_ok=True)
    data = dict(facts, kind=kind, commit=_git("rev-parse", commit, root=root),
                selectors=sorted(selectors or []) if kind == "scoped" else None,
                base=base, host=socket.gethostname(), time=int(time.time()))
    tmp = path.with_suffix(f".{os.getpid()}.tmp")
    tmp.write_text(json.dumps(data, indent=1, sort_keys=True), encoding="utf-8")
    os.replace(tmp, path)
    return path


def reusable(commit, kind, root=None, selectors=None, base=None):
    """(True, why) when reuse is enabled and a record for this exact tree
    covers the requested scope: any `full` record, or a `scoped` record whose
    verified selectors include every requested one."""
    if os.environ.get(ENABLE) != "1":
        return False, f"{ENABLE} is not set"
    facts = key(commit, root)
    if not facts:
        return False, f"unknown commit {commit}"
    wanted = set(selectors or [])
    candidates = [_path(facts["tree"], "full", root)]
    if kind == "scoped":
        candidates += sorted(_dir(root).glob(f"{facts['tree']}.scoped.*.json"))
    for path in candidates:
        try:
            data = json.loads(path.read_text(encoding="utf-8"))
        except (OSError, ValueError):
            continue
        if not all(data.get(k) == v for k, v in facts.items()):
            continue
        if data.get("kind") == "full":
            return True, f"full gate passed on tree {facts['tree'][:10]} at {data.get('commit', '?')[:10]}"
        if data.get("kind") == "scoped" and wanted and wanted <= set(data.get("selectors") or []):
            return True, (f"scoped gate over {len(data['selectors'])} selector(s) (base "
                          f"{(data.get('base') or '?')[:10]}) covers these {len(wanted)}")
    return False, "no record covers this tree and scope"


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("action", choices=["record", "check"])
    ap.add_argument("--commit", required=True)
    ap.add_argument("--kind", choices=["full", "scoped"], required=True)
    ap.add_argument("--base", help="the destination base the scoped selectors were computed against")
    ap.add_argument("--selectors-file", help="one verified (or requested) selector per line")
    args = ap.parse_args(argv)
    selectors = None
    if args.selectors_file:
        selectors = [line.strip() for line in
                     Path(args.selectors_file).read_text(encoding="utf-8").splitlines() if line.strip()]
    if args.action == "record":
        print(record(args.commit, args.kind, selectors=selectors, base=args.base))
        return 0
    ok, why = reusable(args.commit, args.kind, selectors=selectors, base=args.base)
    print(f"gate_evidence: {'REUSING' if ok else 'not reusing'}: {why}", file=sys.stderr)
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
