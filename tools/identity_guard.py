#!/usr/bin/env python3
"""Fail when a byte-verified row starts naming the wrong function.

The byte gate cannot see this class: a pin naming the wrong function still
byte-matches, so a green build proves nothing about identity. Five detectors
find it, and before this guard existed they ran only when somebody remembered
them -- which made them reports rather than checks.

Four are fast enough for the commit hook and run here.
null_reloc.py takes ~70s and runs in the full gate instead; see tools/build.py.

Counts only ever go DOWN. Raising a baseline to go green is the same prohibited
move as raising ORPHAN_BASELINE or appending to pin_consistency_baseline.csv:
it converts a found defect into a permanent one. Lower a number when you fix
something, and say what you fixed in the commit message.
"""
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
BASELINE = ROOT / "targets/game/reverse" / "identity_baseline.txt"

# An ANCHOR is a line the tool prints unconditionally, so its presence proves the
# output is still the format the count pattern was written against. multi_name
# tallies its verdicts and prints only the categories that occurred, so a
# category that falls to zero loses its line entirely: without an anchor there
# is no way to tell "clean" from "the format moved", and guessing either way is
# wrong. A check whose anchor is None must always print its own line.
#
# The SOURCE says what the number is made of, and it decides whether the number
# can be believed right now. OBJECTS means the detector reads this tree's
# compiled .obj files. An interrupted ./build.sh leaves objects built from a
# state that no longer exists, and the detector then compares stale bytes and
# reports a defect that is not in the ledger at all -- that is a real incident,
# not a hypothesis: a killed full build produced multi_name.different findings
# at 0x00042D1B and 0x002136E0 that vanished the moment the two translation
# units were rebuilt, after one of them had already been reported upstream as a
# red tree. IMAGE means the detector reads retail's own bytes and the ledger,
# which no local build state can spoil.
#
# DETAIL is the verdict text the tool prints above the rows it flagged, which is
# what lets an object-derived failure ask about THOSE objects instead of the
# tree. Tree-wide staleness is the normal state of a warm clone -- 338 of 3,984
# present objects here, right after a fetch -- so a tree-level answer would fire
# almost every run and become the next thing everyone learns to skip, which is
# the failure being fixed rather than a fix for it. Scoped to the rows in the
# finding, it is a verdict about that finding.
# (label, tool, count regex, anchor regex or None, source, detail text or None)
OBJECTS, IMAGE = "objects", "image"
CHECKS = [
    ("multi_name.family",
     "multi_name.py",
     re.compile(r"^\s+(\d+)\s+FOLDS HERE but the names are one family member apart", re.M),
     re.compile(r"^matched rows; addresses claimed by 2\+ names: \d+", re.M),
     OBJECTS,
     "FOLDS HERE but the names are one family member apart"),
    ("multi_name.different",
     "multi_name.py",
     re.compile(r"^\s+(\d+)\s+DIFFERENT BODIES - cannot share an address", re.M),
     re.compile(r"^matched rows; addresses claimed by 2\+ names: \d+", re.M),
     OBJECTS,
     "DIFFERENT BODIES - cannot share an address"),
    # Sizes come from the ledger, so no build state reaches this one.
    ("size_outlier.indicted",
     "size_outlier.py",
     re.compile(r"none same-method or same-class=(\d+)"),
     None,
     IMAGE,
     None),
    # multi_name cannot reach this one: the constructors it clears as a
    # structural fold ARE one shape, because build.py masks the vftable operand
    # that separates them. ctor_vtable reads that operand instead.
    ("ctor_vtable.contradicted",
     "ctor_vtable.py",
     re.compile(r"^\s+(\d+)\s+the vtable it installs names a DIFFERENT class", re.M),
     re.compile(r"^matched constructor rows with a plain class name: \d+", re.M),
     IMAGE,
     None),
    # Retail has no identical-COMDAT folding, so a second real name on a body is
    # an over-claim however well the bytes match. Counts names, not addresses.
    ("one_identity.surplus",
     "one_identity.py",
     re.compile(r"^surplus names beyond one per body: (\d+)$", re.M),
     None,
     IMAGE,
     None),
    # A coverage floor, not a defect count: a body the sweep cannot read is one
    # it reports clean without looking. Same lesson as null_reloc.max_unreadable.
    ("ctor_vtable.unreadable",
     "ctor_vtable.py",
     re.compile(r"^\s+(\d+)\s+body could not be read - NOT a clean result", re.M),
     re.compile(r"^matched constructor rows with a plain class name: \d+", re.M),
     IMAGE,
     None),
]
SOURCE = {c[0]: c[4] for c in CHECKS}
DETAIL = {c[0]: c[5] for c in CHECKS}
TOOL = {c[0]: c[1] for c in CHECKS}


def read_baseline():
    if not BASELINE.exists():
        sys.exit(f"identity_guard: {BASELINE.relative_to(ROOT)} is missing. It is not "
                 f"self-seeding -- an auto-written baseline is an unreviewed free pass.")
    out = {}
    for line in BASELINE.read_text(encoding="utf-8").splitlines():
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        key, _, value = line.partition("=")
        out[key.strip()] = int(value)
    return out


def measure():
    cache, found = {}, {}
    for label, tool, pattern, anchor, _source, _detail in CHECKS:
        if tool not in cache:
            done = subprocess.run([sys.executable, str(ROOT / "tools" / tool)],
                                  capture_output=True, text=True, cwd=ROOT)
            if done.returncode != 0:
                sys.exit(f"identity_guard: {tool} failed:\n{done.stderr.strip()}")
            cache[tool] = done.stdout
        match = pattern.search(cache[tool])
        if match is None:
            # A silent zero here would read as "clean" -- the exact failure this
            # whole family of checks exists to catch. Read zero only when the
            # anchor proves the tool did print its tally and this category
            # simply did not occur in it.
            if anchor is None or not anchor.search(cache[tool]):
                sys.exit(f"identity_guard: could not find the {label} count in "
                         f"{tool}'s output, and its anchor line is missing too. "
                         f"The tool's format changed; fix the pattern rather "
                         f"than assuming zero.")
            found[label] = 0
            continue
        found[label] = int(match.group(1))
    return found, cache


def flagged_names(output, detail):
    """Symbol names the detector printed under `detail`, in report order.

    The report puts the verdict on a line starting at column 0 with the address
    and follows it with the rows, indented. Names may be elided, so these are
    prefixes; object_cache.sources_for_names matches on that basis.
    """
    names, collecting = [], False
    for line in output.splitlines():
        if line[:2] == "0x":
            collecting = detail in line
            continue
        if collecting:
            stripped = line.strip()
            if stripped.startswith("?"):
                names.append(stripped)
            else:
                collecting = False
    return names


def object_verdict(worse, outputs):
    """(verdict, [line]) from tools/object_cache.py about the objects behind
    these findings, or None when nothing object-derived regressed."""
    keys = sorted(k for k in worse if SOURCE[k] == OBJECTS)
    if not keys:
        return None
    import object_cache as OC
    # An interrupted build is decisive for the WHOLE tree and does not depend on
    # reading anything out of the report: a killed run can have left any object
    # half-written. Ask that first, so the answer does not hinge on parsing.
    dead, live, unreadable = OC.markers()
    if dead:
        return OC.DIRTY, [f"a build here was interrupted (marker left by pid "
                          f"{', '.join(map(str, dead[:4]))}); any object in this tree "
                          f"can be from a partial run, and a half-written one is "
                          f"exactly as fresh as a whole one"]
    names = []
    for key in keys:
        names += flagged_names(outputs[TOOL[key]], DETAIL[key])
    # No names parsed means the report's format moved. Asking about the whole
    # tree would answer a different question and almost always say "stale", so
    # say what happened instead of quietly widening the question.
    if not names:
        return OC.UNKNOWN, [f"could not read the flagged rows out of "
                            f"{', '.join(sorted({TOOL[k] for k in keys}))}'s report, "
                            f"so the objects behind this finding were not checked"]
    sources = OC.sources_for_names(names)
    verdict, reasons = OC.status(sources or None)
    return verdict, [f"objects behind the flagged rows ({len(sources)} source(s)): "
                     + reasons[0]] + reasons[1:]


def main():
    baseline, (found, outputs) = read_baseline(), measure()
    worse = {k: (found[k], baseline[k]) for k in found
             if k in baseline and found[k] > baseline[k]}
    missing = [k for k in found if k not in baseline]
    if missing:
        sys.exit(f"identity_guard: no baseline for {', '.join(sorted(missing))}")
    if worse:
        print("identity_guard: FAIL — a row that byte-matches now names the wrong function",
              file=sys.stderr)
        for key, (now, was) in sorted(worse.items()):
            print(f"    {key}: {was} -> {now}", file=sys.stderr)
        print("    Run the detector named by the key to see which rows. The byte "
              "gate cannot catch this class; that is why this check exists.",
              file=sys.stderr)
        keys = sorted(k for k in worse if SOURCE[k] == OBJECTS)
        if keys:
            print(f"    {', '.join(keys)} compares THIS TREE'S COMPILED OBJECTS, not "
                  f"retail, so the objects behind the flagged rows decide whether this "
                  f"is a defect or an artifact. Asking tools/object_cache.py:",
                  file=sys.stderr)
            try:
                answer = object_verdict(worse, outputs)
            except Exception as exc:                      # noqa: BLE001
                # Loudly, not silently: a bookkeeping failure must not be
                # mistaken for "the objects are fine".
                print(f"    object_cache could not answer ({type(exc).__name__}: "
                      f"{exc}). Treat this finding as UNVERIFIED and rebuild the "
                      f"sources holding the flagged rows before reporting it.",
                      file=sys.stderr)
            else:
                verdict, lines = answer
                print(f"    -> {verdict.upper()}", file=sys.stderr)
                for line in lines:
                    print(f"       {line}", file=sys.stderr)
                if verdict == "dirty":
                    print("    Those objects do not describe this tree, so this finding "
                          "is NOT evidence of a ledger defect. Rebuild the sources above "
                          "and re-run before reporting a regression.", file=sys.stderr)
                elif verdict == "unknown":
                    print("    The objects behind this finding could not be vouched for, "
                          "so it is unverified either way. Rebuild those sources and "
                          "re-run.", file=sys.stderr)
                else:
                    print("    Those objects match their sources and no build was "
                          "interrupted, so this finding IS about the ledger. Treat it as "
                          "a real regression.", file=sys.stderr)
        raise SystemExit(1)
    # A drop is good news that still fails, the way pin_consistency fails on a
    # baseline row that no longer describes a violation: a baseline left above
    # the truth is head-room the next defect slips into unnoticed.
    better = {k: (found[k], baseline[k]) for k in found if found[k] < baseline[k]}
    if better:
        print("identity_guard: FIXED — now lower the baseline in this same commit",
              file=sys.stderr)
        for key, (now, was) in sorted(better.items()):
            print(f"    {key} = {now}    (was {was})", file=sys.stderr)
        raise SystemExit(1)
    print(f"identity_guard: OK ({sum(found.values())} known identity suspects, none new)")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
