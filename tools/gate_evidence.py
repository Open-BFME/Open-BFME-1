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
so a receipt shows them), the gate kind (`full` or `scoped`) and the Python
version. A `full` record also satisfies a `scoped` check.

WHERE. `<git common dir>/bfme-gate-evidence/<tree>.<kind>.json`: shared by
the worktrees of one clone, never pushed, never trusted from another host.

OPT-IN. `check` only ever answers yes when BFME_REUSE_GATE_EVIDENCE=1 (the
landing service sets it for its own publishing push). Without it every push
gates exactly as before. Like any local file this can be forged by someone
who could equally push with --no-verify; it is a cache, not an attestation.

  python3 tools/gate_evidence.py record --commit SHA --kind full|scoped
  python3 tools/gate_evidence.py check  --commit SHA --kind full|scoped   # exit 0: reuse
"""
import argparse
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


def _path(tree, kind, root=None):
    common = _git("rev-parse", "--git-common-dir", root=root)
    base = Path(common) if Path(common).is_absolute() else Path(root or ROOT) / common
    return base / "bfme-gate-evidence" / f"{tree}.{kind}.json"


def record(commit, kind, root=None):
    facts = key(commit, root)
    if not facts:
        raise SystemExit(f"gate_evidence: unknown commit {commit}")
    path = _path(facts["tree"], kind, root)
    path.parent.mkdir(parents=True, exist_ok=True)
    data = dict(facts, kind=kind, commit=_git("rev-parse", commit, root=root),
                host=socket.gethostname(), time=int(time.time()))
    tmp = path.with_suffix(f".{os.getpid()}.tmp")
    tmp.write_text(json.dumps(data, indent=1, sort_keys=True), encoding="utf-8")
    os.replace(tmp, path)
    return path


def reusable(commit, kind, root=None):
    """(True, why) when a matching record exists and reuse is enabled."""
    if os.environ.get(ENABLE) != "1":
        return False, f"{ENABLE} is not set"
    facts = key(commit, root)
    if not facts:
        return False, f"unknown commit {commit}"
    for have in ([kind, "full"] if kind == "scoped" else [kind]):
        path = _path(facts["tree"], have, root)
        try:
            data = json.loads(path.read_text(encoding="utf-8"))
        except (OSError, ValueError):
            continue
        if all(data.get(k) == v for k, v in facts.items()):
            return True, f"{have} gate passed on tree {facts['tree'][:10]} at {data.get('commit', '?')[:10]}"
    return False, "no matching record"


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("action", choices=["record", "check"])
    ap.add_argument("--commit", required=True)
    ap.add_argument("--kind", choices=["full", "scoped"], required=True)
    args = ap.parse_args(argv)
    if args.action == "record":
        print(record(args.commit, args.kind))
        return 0
    ok, why = reusable(args.commit, args.kind)
    print(f"gate_evidence: {'REUSING' if ok else 'not reusing'}: {why}", file=sys.stderr)
    return 0 if ok else 1


if __name__ == "__main__":
    sys.exit(main())
