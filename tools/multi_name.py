"""Classify every address that two or more row names claim.

A shared address is usually honest: retail's linker folds identical COMDATs, so
one body legitimately answers to several names. But it is also how a whole class
of defect hides, because the offsets AGREE -- the GameWindow setters read as
perfectly matched while every Color and BorderColor row sat one field along.
Nothing that reads offsets can see that; only asking whether the claimants COULD
be one body can.

THE TEST IS STRUCTURAL, AND THE TWO OBVIOUS FORMS OF IT DO NOT WORK. Both were
tried on the live ledger before this settled:

  * comparing the claimants' relocation TARGET NAMES flags 367 of 1,041 and is
    useless -- two classes' constructors name different vftables, and a vftable
    store is a masked DIR32 the byte comparison never looks at, so this flags
    every template and module family in the tree;
  * comparing only REL32 call-target names gives 225 and still over-flags: one
    function under a C and a C++ decoration (?png_handle_IHDR@D3DX@@ against
    _png_handle_IHDR@12) and per-instantiation template symbols resolve to
    different names for the same call.

What works is structure rather than names. Mask every relocation site to zero in
both bodies, then compare the remaining bytes AND the (offset, type) list. Two
ICF-folded bodies ARE the same bytes, so their relocation sites must coincide
however differently our objects happen to name the targets. On the live ledger
that gives 965 real folds, 65 all-placeholder groups, and 11 addresses whose
claimants cannot be one body -- five of them GameWindow, four of those unknown
before this ran.

An unreadable object is REPORTED, never skipped. A sweep that silently drops the
rows it could not load reports "consistent" for a symbol whose contradiction it
failed to read, which is how a whitelist once got 18 unreviewed entries.
"""
import collections
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build as B  # noqa: E402

PLACEHOLDER = re.compile(
    r"^(\?d_[0-9a-f]+@|\?j_[0-9a-f]+@|\?dup_[0-9a-f]+@|\?a_[0-9a-f]+@"
    r"|tg_|dup_|Gen_|gen_|\?gen_|uw_)")

FOLD = "identical masked bytes and reloc sites - a real fold"
DIFFER = "DIFFERENT BODIES - cannot share an address"
ODD_MEMBER = ("one member of a LARGE group compiles differently here - "
              "evidence about that member, not about the group")
PLACEHOLDERS = "all-placeholder"
UNREADABLE = "unreadable object - NOT a clean result"

# Above this many names, "the bodies differ" stops being a claim about the group.
# Forty names on one nine-byte constructor is an ICF group the linker really
# built; one member of it compiling differently HERE points at our compile of
# that member long before it points at thirty-nine wrong rows. Reported apart so
# a large group is not read as a large defect.
LARGE_GROUP = 3


def is_placeholder(name):
    return bool(PLACEHOLDER.match(name)) or "Shim" in name or "Gen_t_" in name


def same_class_different_methods(names):
    """The GameWindow shape: one class, several method names. Not a verdict on
    its own -- getClassMemoryPool and getModuleNameKey share a body legitimately
    -- but it is the label worth carrying beside a DIFFER verdict."""
    bits = []
    for n in names:
        m = re.match(r"^\?([A-Za-z_0-9]+)@([A-Za-z_0-9]+)@@", n)
        if not m:
            return False
        bits.append((m.group(2), m.group(1)))
    return len({c for c, _ in bits}) == 1 and len({f for _, f in bits}) > 1


def shape(row, size, read=None):
    """(reloc sites, bytes with every reloc site zeroed), or None if unreadable.

    Zeroing the sites is the whole point: a body's identity for folding purposes
    is what the compiler emitted BETWEEN its relocations, because the linker
    patches the rest."""
    read = read or _read
    got = read(row, size)
    if got is None:
        return None
    body, relocs = got
    masked = bytearray(body[:size])
    for off, _kind, _sym in relocs:
        if 0 <= off < size:
            width = min(4, size - off)
            masked[off:off + width] = b"\0" * width
    sites = tuple(sorted((off, kind) for off, kind, _ in relocs if off < size))
    return sites, bytes(masked)


def _read(row, size):
    try:
        obj = B.require_row_object(row)
        return B.read_object_symbol_bytes(obj, B.ledger_object_symbol(row), size)
    except BaseException:      # noqa: BLE001 - surfaced as UNREADABLE, not swallowed
        return None


def groups(rows):
    by = collections.defaultdict(list)
    for row in rows:
        by[(int(row["target_rva"], 16), row["target_size"])].append(row)
    return {k: v for k, v in by.items() if len({r["name"] for r in v}) > 1}


def classify(rows, read=None):
    """Yield (rva, size, names, verdict, same_family) for every shared address."""
    for (rva, size), rs in sorted(groups(rows).items()):
        names = sorted({r["name"] for r in rs})
        family = same_class_different_methods(names)
        if all(is_placeholder(n) for n in names):
            yield rva, int(size), names, PLACEHOLDERS, family
            continue
        seen = {}
        for row in rs:
            if row["name"] not in seen:
                seen[row["name"]] = shape(row, int(size), read)
        shapes = list(seen.values())
        if any(s is None for s in shapes):
            yield rva, int(size), names, UNREADABLE, family
        elif len(set(shapes)) == 1:
            yield rva, int(size), names, FOLD, family
        elif len(names) > LARGE_GROUP:
            yield rva, int(size), names, ODD_MEMBER, family
        else:
            yield rva, int(size), names, DIFFER, family


def main(argv):
    rows = [r for r in B.load_function_rows() if r["status"] == "matched"]
    tally = collections.Counter()
    flagged = []
    for rva, size, names, verdict, family in classify(rows):
        tally[verdict] += 1
        if verdict in (DIFFER, UNREADABLE, ODD_MEMBER):
            flagged.append((size, rva, names, verdict, family))
    print("matched rows; addresses claimed by 2+ names: %d" % sum(tally.values()))
    for verdict, n in tally.most_common():
        print("  %5d  %s" % (n, verdict))
    if not flagged:
        return 0
    print("\nworth reading, largest first:")
    for size, rva, names, verdict, family in sorted(flagged, reverse=True):
        tag = " [same class, different methods]" if family else ""
        print("0x%08X %6dB  %s%s" % (rva, size, verdict, tag))
        for name in names:
            print("      %s" % name[:96])
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
