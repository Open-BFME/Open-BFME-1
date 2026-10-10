#!/usr/bin/env python3
"""Fail if any two tracked paths differ only in case, or a control path is not
lowercase.

Such a pair cannot coexist in a Windows/macOS working tree (case-insensitive
filesystems): git checks out one and silently drops the other, breaking the build
and emitting a "paths have collided" warning on clone. This guard runs in the
pre-commit hook so a colliding path can never reach master. Alternate-case sweep
shims are generated at build time (see gen_case_shims.py) and git-ignored, so they
are not tracked and never trip this check.

Control paths are the ones the hooks and tools read by exact spelling: the root,
the ledger trees (Open-BFME-2 reverse/, Open-BFME-1 targets/ and inputs/baselines/),
tools/, .githooks/ and .github/. Tracked under another case -- reverse/Data_Rows.csv,
reverse/Gate_Baseline.txt, or a whole Reverse/ directory -- a case-insensitive
file system still serves the file to the build under its canonical name while
every exact git lookup misses it, so each gate that selects through it verifies
nothing and a baseline edited under the variant escapes its shrink-only check
(GPT-6.1-Sol, converged data gate review, rounds 7-9). Every control path is
spelled in lowercase -- the convention both trees already follow -- so a control
path with an upper-case letter is refused, whether or not any base holds the file.
One file serves both repositories and protects both namespaces in each. Not
control: Markdown documents and LICENSE, and the evidence trees in NOT_CONTROL
(banked attempts, attempt evidence, per-class contracts named after C++ classes,
Open-BFME-1's identity evidence named by upper-case address, the vendored wibo
bundle). An exempt tree is exempt only under its own spelling.

The documents read by exact name keep that name: AGENTS.md and README.md at the
root, docs/ with a lower-case .md suffix, and the mod READMEs.

  python3 tools/check_case_collisions.py             # the index (pre-commit)
  python3 tools/check_case_collisions.py --ref SHA   # a commit's tree (pre-push)
"""
import argparse
import collections
import subprocess
import sys

# Both repositories' namespaces, always: the rules never depend on what the checkout
# holds (an empty untracked targets/game/reverse/ once switched Open-BFME-2 to the
# Open-BFME-1 rules and reverse/Data_Rows.csv passed -- GPT-6.1-Sol). Open-BFME-2:
# reverse/. Open-BFME-1: targets/ (both targets) and the baseline manifests and images
# under inputs/baselines/ that build.py and the WorldBuilder target open by name.
CONTROL_TREES = ("reverse/", "targets/", "inputs/baselines/", "tools/", ".githooks/", ".github/")
NOT_CONTROL = (
    "reverse/attempts/", "reverse/attempt_support/", "reverse/class_contracts/",             # BFME2
    "targets/game/reverse/attempts/", "targets/game/reverse/attempt_support/",              # BFME1
    "targets/game/reverse/attempt_history/", "targets/game/reverse/class_contracts/",
    "targets/game/reverse/identity_evidence/", "targets/worldbuilder/reverse/attempts/",
    "tools/compat/wibo/",                  # a vendored bundle; its README checks these names
)
# Root documents read by exact name (doc_budget, the README badge writers).
CANONICAL = {"agents.md": "AGENTS.md", "readme.md": "README.md"}


def tracked_paths(ref=None):
    cmd = ["git", "ls-files", "-z"] if ref is None else ["git", "ls-tree", "-r", "-z", "--name-only", ref]
    out = subprocess.run(cmd, capture_output=True, check=True).stdout.decode("utf-8", errors="surrogateescape")
    return [p for p in out.split("\0") if p]


def find_collisions(paths):
    by_lower = collections.defaultdict(list)
    for p in paths:
        by_lower[p.lower()].append(p)
    return [sorted(group) for group in by_lower.values() if len(group) > 1]


def control(path):
    """Whether the hooks or tools may read `path` by its exact spelling."""
    low = path.lower()
    # the exempt trees by their own (lowercase) spelling only: under Reverse/attempts/
    # or reverse/Attempts/ a tool selecting reverse/attempts/ would skip the file
    # (GPT-6.1-Sol, round 10); mixed-case names inside the real trees stay allowed
    if path.startswith(NOT_CONTROL) or low.endswith(".md") or low == "license":
        return False
    return "/" not in path or low.startswith(CONTROL_TREES)


def wanted(path):
    """The spelling `path` must have, or None when any spelling will do."""
    low = path.lower()
    if "/" not in path and low in CANONICAL:
        return CANONICAL[low]
    # Open-BFME-1 doc_budget caps mod READMEs (mods/README.md, mods/features/*/README.md)
    # by exact name; a feature's own name is free
    parts = low.split("/")
    if low == "mods/readme.md":
        return "mods/README.md"
    # at any depth: doc_budget matches with fnmatchcase, whose * also spans "/"
    if len(parts) >= 4 and parts[:2] == ["mods", "features"] and parts[-1] == "readme.md":
        return "mods/features/" + "/".join(path.split("/")[2:-1]) + "/README.md"
    if low.startswith("docs/") and (not path.startswith("docs/") or (low.endswith(".md") and not path.endswith(".md"))):
        return "docs/" + path[5:-3] + ".md" if low.endswith(".md") else "docs/" + path[5:]
    return low if control(path) else None


def miscased(paths):
    """Paths not spelled the way the hooks and tools read them."""
    return sorted(p for p in paths if wanted(p) not in (None, p))


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--ref", help="check this commit's tree instead of the index")
    args = parser.parse_args(argv)
    paths = tracked_paths(args.ref)
    collisions = find_collisions(paths)
    wrong = miscased(paths)
    if collisions:
        print("case-only path collision (breaks Windows/macOS checkout):", file=sys.stderr)
        for group in sorted(collisions):
            print("  " + "  <->  ".join(group), file=sys.stderr)
        print(
            "rename one path so they differ by more than case, or (for a dual-case "
            "include shim) make one canonical and generate the other via "
            "tools/gen_case_shims.py.",
            file=sys.stderr,
        )
    if wrong:
        trees = ", ".join(t.rstrip("/") + "/" for t in CONTROL_TREES)
        print(f"a control path (the root, {trees}) or a document read by name is not spelled as "
              "the hooks read it, so they would verify nothing through it:", file=sys.stderr)
        for p in wrong:
            print(f"  {p}  ->  rename to {wanted(p)}", file=sys.stderr)
    return 1 if collisions or wrong else 0


if __name__ == "__main__":
    sys.exit(main())
