#!/usr/bin/env python3
"""Which sources sit in a directory their own class keeps nothing else in.

WHY THIS EXISTS. 14,718 real sources against the original's 1,421, and 6,892 of
them sit directly in Code/GameEngine/Source/Common/ -- AI state machines, W3D
drawable modules, script-engine bodies, all in one flat directory because the
conversion lane writes a new TU wherever it happens to be standing. Nobody can
navigate that, and no amount of renaming inside those files fixes it.

WHY MOVING AND NOT MERGING. Merging them into one TU per class is the obvious
answer and it is mostly blocked: 95 of 146 marker clusters hold a
__declspec(naked)/__emit donor that must be converted first, and of the 51 that
do not, only 6 have donors that agree on their `// cl:` line -- that line is the
TU's entire compile environment, so donors that disagree resolve different
headers and stop reproducing retail. Total reach of the merge lane is 9 files.
Moving has none of those constraints: the `// cl:` line travels with the file and
14,615 of 14,734 sources (99%) carry no relative include, so nothing resolves
differently afterwards. Measured, a move is byte-neutral.

THE RULE. A file is queued only when it declares exactly ONE owning class and
that class demonstrably lives somewhere else: the ZH reference has a file for it,
or the class already keeps two or more bodies in another existing directory. The
destination is never invented and the queue never guesses.

    python3 tools/placement_queue.py            # write the queue, print a summary
    python3 tools/placement_queue.py --by-dir   # where files would leave and land

See docs/placement_lane.md for the traps this lane has already paid for.
"""
import argparse
import collections
import csv
import glob
import os
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
ZH = "reference/CnC_Generals_Zero_Hour/GeneralsMD/Code"
AREAS = ("Code/GameEngine", "Code/Libraries", "Code/GameEngineDevice")
QUEUE = "reverse/placement_queue.tsv"
# The flat root of Common/ holds 6,892 files because the conversion lane writes
# new TUs there by default. A class whose bodies mostly sit in the dumping ground
# is not evidence that the dumping ground is where they belong, so it is never a
# destination inferred from sibling counts. ZH naming it explicitly still counts:
# some classes really do live in Common/.
DUMPING_GROUND = "Code/GameEngine/Source/Common"

# ?method@Class@@... and ??0Class@@ / ??1Class@@ for constructors and destructors.
METHOD = re.compile(r"^\?([A-Za-z_]\w*)@([A-Za-z_]\w*)@@")
STRUCTOR = re.compile(r"^\?\?[01]([A-Za-z_]\w*)@@")
# A move rewrites no text, so only a RELATIVE include can resolve differently
# afterwards. 119 files carry one; they stay where they are.
RELATIVE_INCLUDE = re.compile(r'^\s*#include\s+"(?:\.\./|\./)', re.M)


def owning_class(mangled):
    hit = METHOD.match(mangled or "")
    if hit:
        return hit.group(2)
    hit = STRUCTOR.match(mangled or "")
    return hit.group(1) if hit else None


def survey(root):
    """(file -> its one owning class, class -> Counter of directories it lives in)."""
    owners = collections.defaultdict(set)
    homes = collections.defaultdict(collections.Counter)
    with open(root / "reverse/functions.csv", newline="") as fh:
        for row in csv.DictReader(fh):
            if row.get("status") != "matched":
                continue
            source = row.get("source") or ""
            if not source.startswith(AREAS) or source.startswith("Code/gen"):
                continue
            cls = owning_class(row.get("name"))
            if not cls:
                continue
            owners[source].add(cls)
            homes[cls][os.path.dirname(source)] += 1
    single = {s: next(iter(c)) for s, c in owners.items() if len(c) == 1}
    return single, homes


def zh_directories(root):
    """class name -> the directory ZH keeps that class's source in."""
    out = {}
    for path in glob.glob(str(root / ZH) + "/**/*.cpp", recursive=True):
        rel = os.path.relpath(path, root)
        out.setdefault(os.path.basename(rel)[:-4].lower(), os.path.dirname(rel))
    return out


def destination(root, source, cls, homes, zh):
    """Where that file belongs, or None when the evidence does not say."""
    here = os.path.dirname(source)
    zh_dir = zh.get(cls.lower())
    if zh_dir:
        candidate = zh_dir.replace(ZH, "Code", 1)
        if candidate != here and (root / candidate).is_dir():
            return candidate
    # Otherwise: where this class already keeps most of its bodies. Two or more,
    # because one sibling elsewhere is as likely to be the misplaced file.
    ranked = [(d, n) for d, n in homes[cls].most_common()
              if d != here and n >= 2 and d != DUMPING_GROUND]
    for d, _ in ranked:
        if (root / d).is_dir():
            return d
    return None


def build(root):
    single, homes = survey(root)
    zh = zh_directories(root)
    queue, skipped = [], collections.Counter()
    for source, cls in sorted(single.items()):
        dest = destination(root, source, cls, homes, zh)
        if not dest:
            skipped["no destination the evidence supports"] += 1
            continue
        target = os.path.join(dest, os.path.basename(source))
        if (root / target).exists():
            skipped["a file of that name is already there"] += 1
            continue
        try:
            text = (root / source).read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        if RELATIVE_INCLUDE.search(text):
            skipped["carries a relative include"] += 1
            continue
        queue.append((source, target, cls))
    return queue, skipped


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--by-dir", action="store_true", help="summarise by directory")
    args = ap.parse_args()

    queue, skipped = build(ROOT)
    (ROOT / QUEUE).write_text(
        "".join(f"{s}\t{d}\t{c}\n" for s, d, c in queue), encoding="utf-8")
    print(f"{QUEUE}: {len(queue):,} file(s) queued")
    for reason, n in skipped.most_common():
        print(f"  skipped {n:>6,}  {reason}")
    if args.by_dir:
        out = collections.Counter(os.path.dirname(s) for s, _, _ in queue)
        into = collections.Counter(os.path.dirname(d) for _, d, _ in queue)
        print("\nleaving:")
        for d, n in out.most_common(8):
            print(f"  {n:>5}  {d}")
        print("landing:")
        for d, n in into.most_common(8):
            print(f"  {n:>5}  {d}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
