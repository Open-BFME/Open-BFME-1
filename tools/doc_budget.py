#!/usr/bin/env python3
"""Stop the instructions every agent loads from growing back.

docs/lessons.md grew 7.4x in thirty days under two written bans, and AGENTS.md
went from 524 to 3,094 words in eight weeks; only a hook has ever held a doc.
Both git hooks run this:

  * AGENTS.md stays at or under AGENTS_CAP words: every Codex session loads it.
  * A change may not add net words to AGENTS.md, README.md and docs/ taken
    together: to add a sentence, cut one. CATALOGS are exempt because agents
    look things up in them rather than read them.
  * A mod README stays at or under MOD_README_CAP words; players read those.

  python3 tools/doc_budget.py --staged       # commit hook: index against HEAD
  python3 tools/doc_budget.py --range A B    # push hook: B against A
"""
import argparse
import fnmatch
import subprocess
import sys

AGENTS_CAP = 1450
MOD_README_CAP = 500
BUDGETED = ("AGENTS.md", "README.md", "docs/*.md")
CATALOGS = frozenset(("docs/shape_levers.md", "docs/ini_schema.md",
                      "docs/opencode_router.md", "docs/throughput-tools.md"))
MOD_READMES = ("mods/README.md", "mods/features/*/README.md")


def budgeted(path):
    return path not in CATALOGS and any(fnmatch.fnmatchcase(path, p) for p in BUDGETED)


def mod_readme(path):
    return any(fnmatch.fnmatchcase(path, p) for p in MOD_READMES)


def problems(changed, before, after):
    """changed: paths the change touches. before/after: {path: words} for those
    paths, with a path absent where the file does not exist."""
    found = []
    if "AGENTS.md" in changed and after.get("AGENTS.md", 0) > AGENTS_CAP:
        found.append(f"AGENTS.md is {after['AGENTS.md']} words; the cap is {AGENTS_CAP}. "
                     "Cut before you add: every Codex session loads all of it.")
    grown = sum(after.get(p, 0) - before.get(p, 0) for p in changed if budgeted(p))
    if grown > 0:
        found.append(f"this adds {grown} net words to AGENTS.md, README.md and docs/. Cut as many "
                     "elsewhere in them, or put the fact where it is enforced: a tool's error "
                     "message, the commit message, or a comment next to the code it is about.")
    for path in sorted(changed):
        if mod_readme(path) and after.get(path, 0) > MOD_README_CAP:
            found.append(f"{path} is {after[path]} words; a mod README may have at most "
                         f"{MOD_README_CAP}.")
    return found


def git(*args):
    return subprocess.run(("git",) + args, capture_output=True, text=True, check=True).stdout


def counts(ref, paths):
    """Word counts at ref (":" is the index) for the paths that exist there."""
    listing = git("ls-files") if ref == ":" else git("ls-tree", "-r", "--name-only", ref)
    present = set(listing.splitlines())
    prefix = ":" if ref == ":" else f"{ref}:"
    return {p: len(git("show", prefix + p).split()) for p in paths if p in present}


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    mode = ap.add_mutually_exclusive_group(required=True)
    mode.add_argument("--staged", action="store_true")
    mode.add_argument("--range", nargs=2, metavar=("OLD", "NEW"))
    a = ap.parse_args()
    if a.staged:
        # A merge commit's index carries upstream's doc edits, each already
        # checked when it was committed; the push hook checks the whole range.
        if subprocess.run(("git", "rev-parse", "-q", "--verify", "MERGE_HEAD"),
                          capture_output=True).returncode == 0:
            return 0
        old, new = "HEAD", ":"
        diff = git("diff", "--cached", "--no-renames", "--name-only", "HEAD")
    else:
        old, new = a.range
        diff = git("diff", "--no-renames", "--name-only", old, new)
    changed = [p for p in diff.splitlines() if budgeted(p) or mod_readme(p)]
    if not changed:
        return 0
    found = problems(changed, counts(old, changed), counts(new, changed))
    for line in found:
        print(f"doc_budget: {line}", file=sys.stderr)
    return 1 if found else 0


if __name__ == "__main__":
    sys.exit(main())
