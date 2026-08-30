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
however differently our objects happen to name the targets.

STRUCTURE IS NOT ENOUGH ON ITS OWN, and the GameWindow setters are why. Our
header is short by a field there, so `winSetEnabledColor` compiles to exactly
retail's `winSetEnabledImage` -- two names on one address, structurally
identical HERE, and both green. No byte comparison can see that. What can is the
NAMES: two accessors one family member apart (same class, same token count,
differing in one position). That is the FAMILY verdict, and it is a candidate
list rather than a verdict on the ledger -- it is the only test here that
reasons from names.

FAMILY IS NOT PROOF, AND AABTreeClass IS WHY. Cast_AABox_Recursive,
Cast_OBBox_Recursive and Intersect_OBBox_Recursive share one body at 0x0096B100
and legitimately do: they differ only in the type of the test object, every
method they call on it folded too, and the calls are REL32s the comparison
masks. So the flag depends on WHERE the difference would have to appear. The
GameWindow families differ in which FIELD they write, and a field offset is a
literal in the instruction stream -- it cannot fold, so identical compared bytes
prove a defect. The AABTree families differ in a TYPE, and everything the type
contributed is inside the masked relocations, so identical compared bytes prove
nothing. Each FAMILY line reports which case it is by asking whether the
claimants name the same relocation targets. It does not change the verdict:
clearing a candidate automatically is how a real defect gets filed as noise.

Different target NAMES do not settle it either way, and the next step is the
same for both outcomes: resolve each name to an ADDRESS. AABTreeClass folds
because all three of its differing calls land on one address -- the callees
folded first, so the callers became identical. A family whose differing
relocations resolve to DIFFERENT addresses cannot be one body at all, whatever
the compared bytes say, because the linked bodies would not match.

On the live ledger: 958 real folds, 65 all-placeholder, 9 family conflicts,
2 addresses whose claimants cannot be one body, and 4 large groups with one odd
member. Both GameWindow draw-data families rest on ALL 37 of their bytes -- full
byte evidence and still wrong, which is the whole reason the name test exists.

EVERY VERDICT PRINTS HOW MANY BYTES IT RESTS ON, because masking makes a cheap
verdict and an expensive one look identical. A body whose every byte is a
relocation site compares equal to ANY target of its length -- it is not a match,
it is an absence of evidence -- and the build's funclet healer paid for that
lesson with a data table of four label pointers that tied with a real funclet.
No group here rests on zero bytes, so the verdicts stand as computed; 44 of the
958 folds rest on three bytes or fewer, which is a 5-byte `E9` jump agreeing
with another 5-byte `E9` jump on the opcode alone. That is a different claim
from 600 bytes agreeing, and until this column it printed the same.

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
FAMILY = ("FOLDS HERE but the names are one family member apart - "
          "what a shared layout error looks like")
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


def tokens(name):
    """(class, method tokens) for a plain `?method@Class@@...` name, else None."""
    m = re.match(r"^\?([A-Za-z_0-9]+)@([A-Za-z_0-9]+)@@", name)
    if not m:
        return None
    method, cls = m.group(1), m.group(2)
    words = [w for w in re.split(
        r"_|(?<=[a-z0-9])(?=[A-Z])|(?<=[A-Z])(?=[A-Z][a-z])", method) if w]
    return cls, tuple(words)


def accessor_siblings(names):
    """True when two names are one family member apart: same class, same token
    count, differing in exactly ONE position.

    `winSetEnabledColor` and `winSetEnabledImage` differ only at the last word,
    so they are the same operation on two different fields and CANNOT be one
    body. `getClassMemoryPool` and `getModuleNameKey` differ everywhere and are
    simply two functions that happen to share one, which the linker is entitled
    to do -- that pair is the reason this is a one-token test rather than any
    name difference."""
    parsed = [tokens(n) for n in names]
    for i, a in enumerate(parsed):
        for b in parsed[i + 1:]:
            if a is None or b is None or a[0] != b[0]:
                continue
            x, y = a[1], b[1]
            if len(x) == len(y) >= 2 and sum(p != q for p, q in zip(x, y)) == 1:
                return True
    return False


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


Group = collections.namedtuple(
    "Group", "rva size names verdict family surviving masked_split")


def surviving(sites, size):
    """How many of `size` bytes masking left for the comparison to see.

    Callers report it beside the verdict rather than acting on it: it is the
    difference between "these agree on 600 bytes" and "these agree on the E9
    opcode", which the verdict string alone cannot express.
    """
    covered = set()
    for offset, _kind in sites:
        if 0 <= offset < size:
            covered.update(range(offset, min(offset + 4, size)))
    return size - len(covered)


def probe(row, size, read=None):
    """(shape, relocation targets by site), or None if unreadable.

    The shape decides identity; the targets never do -- they are what the
    comparison could not see, and reporting them is how a reader knows whether
    an agreement had anywhere left to disagree.
    """
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
    targets = tuple(sorted((off, sym) for off, _kind, sym in relocs if off < size))
    return (sites, bytes(masked)), targets


def shape(row, size, read=None):
    """(reloc sites, bytes with every reloc site zeroed), or None if unreadable.

    Zeroing the sites is the whole point: a body's identity for folding purposes
    is what the compiler emitted BETWEEN its relocations, because the linker
    patches the rest."""
    got = probe(row, size, read)
    return None if got is None else got[0]


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
    """Yield a Group for every address two or more names claim."""
    for (rva, size), rs in sorted(groups(rows).items()):
        size = int(size)
        names = sorted({r["name"] for r in rs})
        family = same_class_different_methods(names)
        if all(is_placeholder(n) for n in names):
            yield Group(rva, size, names, PLACEHOLDERS, family, None, False)
            continue
        seen = {}
        for row in rs:
            if row["name"] not in seen:
                seen[row["name"]] = probe(row, size, read)
        shapes = [None if p is None else p[0] for p in seen.values()]
        # Whether the claimants name DIFFERENT relocation targets. If they do,
        # the only thing telling them apart sits in the bytes the comparison
        # blanked, so identical shapes are not evidence that they are one body.
        # If they do not, identical shapes are the whole story.
        split = len({p[1] for p in seen.values() if p is not None}) > 1
        # The weakest claimant sets what the verdict rests on: an agreement is
        # only as good as the fewest bytes either side left unmasked.
        left = min((surviving(s[0], size) for s in shapes if s is not None),
                   default=None)
        if any(s is None for s in shapes):
            yield Group(rva, size, names, UNREADABLE, family, left, split)
        elif len(set(shapes)) == 1:
            # Structurally these CAN be one body -- but if the names are one
            # family member apart they cannot be, whatever our compile says.
            # Two setters of different fields producing identical bytes here is
            # the signature of a class that is short by a field: the GameWindow
            # setters read as perfectly matched while every Color row sat on the
            # Image body. Only reported for small groups; a forty-name ICF group
            # of trivial accessors will always contain some one-token pair.
            if len(names) <= LARGE_GROUP and accessor_siblings(names):
                yield Group(rva, size, names, FAMILY, family, left, split)
            else:
                yield Group(rva, size, names, FOLD, family, left, split)
        elif len(names) > LARGE_GROUP:
            yield Group(rva, size, names, ODD_MEMBER, family, left, split)
        else:
            yield Group(rva, size, names, DIFFER, family, left, split)


def main(argv):
    rows = [r for r in B.load_function_rows() if r["status"] == "matched"]
    tally = collections.Counter()
    thin = collections.Counter()
    flagged = []
    for g in classify(rows):
        tally[g.verdict] += 1
        if g.surviving is not None and g.surviving < 4:
            thin[g.verdict] += 1
        if g.verdict in (DIFFER, UNREADABLE, ODD_MEMBER, FAMILY):
            flagged.append(g)
    print("matched rows; addresses claimed by 2+ names: %d" % sum(tally.values()))
    for verdict, n in tally.most_common():
        print("  %5d  %s" % (n, verdict))
    for verdict, n in thin.most_common():
        print("  of those, %d rest on fewer than 4 unmasked bytes: %s" % (n, verdict))
    if not flagged:
        return 0
    print("\nworth reading, largest first:")
    for g in sorted(flagged, key=lambda g: (g.size, g.rva), reverse=True):
        tag = " [same class, different methods]" if g.family else ""
        rests = "n/a" if g.surviving is None else "%d/%d" % (g.surviving, g.size)
        print("0x%08X %6dB  rests on %-9s %s%s"
              % (g.rva, g.size, rests, g.verdict, tag))
        if g.verdict == FAMILY:
            print("      %s" % ("the claimants name different relocation targets, so what "
                                "separates them was masked - undecidable here"
                                if g.masked_split else
                                "the claimants name the SAME relocation targets, so a "
                                "difference would have to show in the compared bytes"))
        for name in g.names:
            print("      %s" % name[:96])
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
