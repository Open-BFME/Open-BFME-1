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
BLOCKED = "reverse/placement_blocked.tsv"
# The flat root of Common/ holds 6,892 files because the conversion lane writes
# new TUs there by default. A class whose bodies mostly sit in the dumping ground
# is not evidence that the dumping ground is where they belong, so it is never a
# destination inferred from sibling counts. ZH naming it explicitly still counts:
# some classes really do live in Common/.
DUMPING_GROUND = "Code/GameEngine/Source/Common"
LEGACY_DONOR_ROOTS = (
    DUMPING_GROUND,
    "Code/GameEngineDevice/Source/W3DDevice/Common",
)

# ?method@Class@@..., ??0Class@@ / ??1Class@@ constructors and destructors, and
# ??_GClass@@ / ??_EClass@@ deleting-destructor wrappers.
METHOD = re.compile(r"^\?([A-Za-z_]\w*)@([A-Za-z_]\w*)@@")
STRUCTOR = re.compile(r"^\?\?[01]([A-Za-z_]\w*)@@")
DELETING_DESTRUCTOR = re.compile(r"^\?\?_[EG]([A-Za-z_]\w*)@@")
# A move rewrites no text, so only an include that resolves against the file's OWN
# directory can break. That is not just `../` and `./`: a bare quoted name does it
# too, and MSVC searches the including file's directory first.
# ManTheWallsSpecialPowerDestructorThunk.cpp says
# `#include "SpecialPowerModuleDestructorThunk.cpp"` -- a sibling, by bare name --
# and moving it gave `fatal error C1083` after the batch had already been gated.
QUOTED_INCLUDE = re.compile(r'^\s*#include\s+"([^"]+)"', re.M)
BARE_INCLUDE = re.compile(r'^\s*#include\s+"([^"/]+\.c(?:pp)?)"', re.M)
CLASS_DECL = re.compile(r"^[ \t]*(?:class|struct)[ \t]+([A-Za-z_]\w*)\b[^;{]*\{", re.M)
NON_CODE = re.compile(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', re.S)
OUT_OF_LINE_DEFINITION = re.compile(
    r"\b(?P<class>[A-Za-z_]\w*)\s*::\s*~?[A-Za-z_]\w*\s*"
    r"\((?:[^();{}]|\([^();{}]*\))*\)\s*"
    r"(?:const\s*)?(?:throw\s*\([^)]*\)\s*)?"
    r"(?::[^;{}]*)?\{"
)


def out_of_line_classes(text):
    """Classes with member definitions in this source, excluding mere mentions."""
    code = NON_CODE.sub(" ", text)
    return {match.group("class") for match in OUT_OF_LINE_DEFINITION.finditer(code)}


def implements_class(text, name):
    """A matching filename alone does not establish class ownership.

    Common/System/Debug.cpp implements global logging functions, whereas the
    Debug class lives in the separate debug library. Require a class definition
    or an out-of-line member body, ignoring comments, strings and mere calls.
    This is conservative evidence collection, not a C++ parser.
    """
    code = NON_CODE.sub(" ", text)
    if any(m.group(1).lower() == name.lower() for m in CLASS_DECL.finditer(code)):
        return True
    return any(owner.lower() == name.lower() for owner in out_of_line_classes(text))


def owning_class(mangled):
    hit = METHOD.match(mangled or "")
    if hit:
        return hit.group(2)
    hit = STRUCTOR.match(mangled or "")
    return hit.group(1) if hit else None


def is_legacy_donor(directory):
    """Whether weak sibling counts may drain, but never nominate, this tree."""
    return any(directory == root or directory.startswith(root + "/")
               for root in LEGACY_DONOR_ROOTS)


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


def deleting_destructor_homes(root):
    """Class directories corroborated by exact deleting-destructor wrappers.

    These directories can expose a split family, but must not nominate a home on
    their own: doing that turned every generated wrapper into fresh queue work.
    """
    out = collections.defaultdict(set)
    with open(root / "reverse/functions.csv", newline="") as fh:
        for row in csv.DictReader(fh):
            if row.get("status") != "matched":
                continue
            source = row.get("source") or ""
            if not source.startswith(AREAS) or source.startswith("Code/gen"):
                continue
            hit = DELETING_DESTRUCTOR.match(row.get("name") or "")
            if hit:
                out[hit.group(1)].add(os.path.dirname(source))
    return out


def zh_directories(root):
    """class name -> the directory ZH keeps that class's source in."""
    out = {}
    secondary = collections.defaultdict(set)
    for path in glob.glob(str(root / ZH) + "/**/*.cpp", recursive=True):
        # Evidence and ledger paths use forward slashes on every host.
        rel = Path(path).relative_to(root).as_posix()
        name = Path(path).stem
        text = Path(path).read_text(encoding="utf-8", errors="replace")
        if implements_class(text, name):
            out.setdefault(name.lower(), os.path.dirname(rel))
        for owner in out_of_line_classes(text):
            secondary[owner.lower()].add(os.path.dirname(rel))
    # An official TU may own several classes: WorldHeightMap.cpp, for example,
    # also defines MapObject. Only accept secondary ownership when every actual
    # out-of-line definition agrees on one directory; calls and textual mentions
    # were removed before extraction and cannot nominate a destination.
    for owner, directories in secondary.items():
        if owner not in out and len(directories) == 1:
            out[owner] = next(iter(directories))
    return out


def zh_header_directories(root):
    """class name -> the ZH SOURCE directory implied by the header that declares it.

    The .cpp rule above only reaches a class ZH gave a file of its own name. Most
    did not get one: ZH declares 1,264 classes across its headers and keeps their
    bodies in the Source tree that mirrors Include/<Area>/<Sub>. That mirror is
    the evidence -- UpdateModule is declared in Include/GameLogic/Module, so its
    bodies belong in Source/GameLogic/Module, and 693 of ours are sitting in the
    flat Common/ instead. Worth 2,028 files the .cpp rule cannot see.
    """
    out = {}
    for path in glob.glob(str(root / ZH) + "/GameEngine/Include/**/*.h", recursive=True):
        here = Path(path).relative_to(root).parent.as_posix()
        mirror = here.replace("/Include/", "/Source/", 1)
        # The mirror has to be real IN ZH. Include/GameLogic/Module has no
        # Source/GameLogic/Module -- ZH keeps those bodies under Object/Update and
        # Object/Behavior -- so trusting the mirror blindly invented a directory
        # for 606 files and dragged 195 out of the one that already named them.
        if not (root / mirror).is_dir():
            continue
        for match in CLASS_DECL.finditer(
                Path(path).read_text(encoding="utf-8", errors="replace")):
            out.setdefault(match.group(1), mirror)
    return out


def destination(root, source, cls, homes, zh, zh_hdr, corroborating_homes=None):
    """Where that file belongs, or None when the evidence does not say."""
    here = os.path.dirname(source)

    # EVERY rule below stops at "already home". A rule that answers with the
    # current directory has said the file belongs here; treating that as a
    # non-answer and falling through to weaker evidence is what moved MapCache out
    # of GameClient -- where ZH's header puts it -- into a Common/RTS pile of nine,
    # and then proposed moving it back next rebuild. Fixed in one rule at a time,
    # it just relocated the oscillation; all three need it.
    def usable(candidate):
        # Never UP into a parent of where the file already is. ZH's header tree is
        # coarser than ours in places -- it declares AIUpdateInterface in
        # Include/GameLogic and we already keep it in Source/GameLogic/AI -- and
        # answering "GameLogic" there would drag 324 files out of a directory that
        # names them into one that does not. A file inside the destination subtree
        # is already home.
        return (candidate != here
                and not here.startswith(candidate + "/")
                and (root / candidate).is_dir())

    zh_dir = zh.get(cls.lower())
    if zh_dir:
        candidate = zh_dir.replace(ZH, "Code", 1)
        # ZH naming this very directory is the strongest evidence there is, and it
        # says the file is already home -- including in a deeper established
        # family -- so stop, do not fall through. Falling
        # through sent AssaultTransportAIUpdate.cpp from Object/Update/AIUpdate,
        # where ZH puts it, to GameLogic/AI on the strength of two siblings that
        # were themselves misplaced. Weak evidence must never outrank strong.
        if candidate == here or here.startswith(candidate + "/"):
            return None
        if usable(candidate):
            return candidate
    # Then the header that declares it. Never into the flat Common/ root: that is
    # the directory this lane exists to drain, and ZH's Common/ header saying
    # "Common" is not evidence that 6,892 files belong in one directory.
    hdr_dir = zh_hdr.get(cls)
    if hdr_dir:
        candidate = hdr_dir.replace(ZH, "Code", 1)
        if candidate == here or here.startswith(candidate + "/"):
            return None
        if candidate != DUMPING_GROUND and usable(candidate):
            # A header mirror proves the broad area, not that its root should
            # flatten a class already established in a deeper source family.
            # One established descendant refines that broad answer; two are an
            # ambiguity, not an invitation to pick the larger pile.
            descendants = [d for d, n in homes[cls].items()
                           if n >= 2 and d.startswith(candidate + "/")
                           and (root / d).is_dir()]
            if len(descendants) == 1 and homes[cls][candidate] < 2:
                return descendants[0]
            if descendants:
                return None
            return candidate
    # A module implementation and its FooModuleData are one source family. A
    # matched partner in the current directory is positive ownership evidence;
    # do not let a pile of potentially misplaced Foo rows pull the pair apart.
    suffix = "ModuleData"
    paired = cls[:-len(suffix)] if cls.endswith(suffix) else cls + suffix
    paired_homes = homes.get(paired, {})
    if len(paired_homes) == 1 and paired_homes.get(here, 0):
        return None
    # A deleting-destructor wrapper independently corroborates the current
    # directory.  When that directory also has a real family and another
    # directory has one, sibling counts cannot decide which family owns this
    # file: ranking the larger pile moved LivingWorldRegion and
    # BoneFXUpdateModuleData thunks away from their intentional homes.
    corroborated_here = (corroborating_homes or {}).get(cls, ())
    if (homes[cls][here] >= 2 and here in corroborated_here and any(
            count >= 2 and directory != here
            for directory, count in homes[cls].items())):
        return None
    # Otherwise: where this class already keeps most of its bodies. Two or more,
    # because one sibling elsewhere is as likely to be the misplaced file.
    # A second alternative directory makes the placement ambiguous even when one
    # pile is larger. Ranking that plurality let a stale identity-corrected TU
    # pull a destructor away from its independently recovered deleting wrapper.
    known_homes = set(homes[cls])
    if corroborating_homes:
        known_homes.update(corroborating_homes.get(cls, ()))
    alternatives = [d for d in known_homes
                    if d != here and not is_legacy_donor(d)
                    and (root / d).is_dir()]
    if len(alternatives) != 1:
        return None
    ranked = [(d, n) for d, n in homes[cls].most_common()
              if n >= 2 and not is_legacy_donor(d)]
    for d, _ in ranked:
        # The class already keeps two or more bodies HERE: the file is home, and
        # the search stops. Treating "here" as a non-answer and falling through to
        # the next-best directory is what made this rule oscillate -- five
        # BuddyThreadClass bodies in Common/RTS against two in
        # GameNetwork/GameSpy/Thread, and the queue kept proposing the minority.
        # Same defect as the ZH rule above; fixing one and not the other left
        # 147 files being volleyed between a class's two homes.
        if d == here:
            return None
        if usable(d):
            return d
    return None


def zh_keeps_source_here(root, source):
    """Whether ZH keeps this exact source at the same path below Code/."""
    relative = Path(source).relative_to("Code")
    return (root / ZH / relative).is_file()


def included_by_siblings(root):
    """Files some neighbour #includes by bare name -- they cannot be moved.

    The guard below asks what a file includes. This asks the other direction, and
    it is the one that bites: ManTheWallsSpecialPowerDestructorThunk.cpp and
    ProductionSpeedBonusDestructorThunk.cpp both say
    `#include "SpecialPowerModuleDestructorThunk.cpp"`, so moving THAT file broke
    two sources nobody had touched. The batch gate never saw it -- it builds what
    it moved, and what it moved compiled fine at its new home.
    """
    pinned = set()
    for path in glob.glob(str(root / "Code") + "/**/*.cpp", recursive=True):
        here = Path(path).relative_to(root).parent
        try:
            text = Path(path).read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        for name in BARE_INCLUDE.findall(text):
            target = (here / name).as_posix()
            if (root / target).exists():
                pinned.add(target)
    return pinned


def blocked_sources(root):
    """Sources a previous placement gate proved cannot move as they stand."""
    path = root / BLOCKED
    if not path.exists():
        return set()
    blocked = set()
    for number, line in enumerate(path.read_text(encoding="utf-8").splitlines(), 1):
        if not line:
            continue
        fields = line.split("\t")
        if len(fields) != 2 or not all(fields):
            raise ValueError(f"{BLOCKED}:{number}: expected source<TAB>reason")
        blocked.add(fields[0])
    return blocked


def build(root):
    single, homes = survey(root)
    corroborating_homes = deleting_destructor_homes(root)
    pinned = included_by_siblings(root)
    refused = blocked_sources(root)
    zh, zh_hdr = zh_directories(root), zh_header_directories(root)
    queue, skipped = [], collections.Counter()
    for source, cls in sorted(single.items()):
        if source in refused:
            skipped["a previous placement gate rejected the source"] += 1
            continue
        dest = destination(
            root, source, cls, homes, zh, zh_hdr, corroborating_homes
        )
        if not dest:
            skipped["no destination the evidence supports"] += 1
            continue
        # Included headers can emit inline methods whose class does not own the
        # TU. The reference keeping this exact source here is stronger evidence.
        if zh_keeps_source_here(root, source):
            skipped["ZH keeps this source at its current path"] += 1
            continue
        target = (Path(dest) / os.path.basename(source)).as_posix()
        if (root / target).exists():
            skipped["a file of that name is already there"] += 1
            continue
        try:
            text = (root / source).read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        here = os.path.dirname(source)
        if any((root / here / inc).exists()
               for inc in QUOTED_INCLUDE.findall(text)):
            skipped["quoted include resolves to a sibling"] += 1
            continue
        if source in pinned:
            skipped["a sibling includes it by bare name"] += 1
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
