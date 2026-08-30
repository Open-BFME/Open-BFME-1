"""Matched rows whose vftable store lands where retail wrote nothing.

Byte comparison masks every DIR32 site, and it decides WHICH bytes to mask from
the COMPILED side's relocation list. So a site that is a relocation for us and a
plain literal for retail is blanked on both sides and never compared at all --
the one field that distinguishes the two bodies is the one field nobody looks at.

That is how a constructor that stores its own vftable verifies against a
constructor that stores a literal zero. The two are the same length, the same
instructions, and differ only in the four bytes under the relocation:

    ours    8b c1  c7 00 <DIR32 ??_7X@@6B@>  c3     mov [eax], vftable
    retail  8b c1  c7 00  00 00 00 00        c3     mov [eax], 0

A linked absolute address is never zero, so all-zero retail bytes under one of
our DIR32 sites prove retail stored no pointer there. The row is on a body that
does not have the store our source emits, whatever the gate says.

THE ONE LEGITIMATE ZERO is `__except_list`. `mov eax, fs:[__except_list]` really
does relocate against absolute 0 -- it is the TIB offset, not a linked address --
and it opens every try-block in the tree, so it is excluded by name rather than
being allowed to bury the result.

On the live ledger: 160,612 matched rows scanned, 67 flagged, 15 of them carrying
an explicit `icf-owner=` that made the alias look sanctioned. They cluster on a
handful of zero-storing bodies -- 23 on 0x00087A50, 21 on 0x00061D90 -- while
retail holds 215 pointer-storing bodies of the 9-byte shape and 66 of the 18-byte
shape, each storing a DIFFERENT vftable. So the real constructors exist and are
individually distinguishable; these rows are simply not on them.

This finds the mismatch, never the fix. Re-homing needs the address of each
class's own `??_7X@@6B@`, and a body's name is settled by its CALL SITES -- not
by which candidate a masked comparison happens to accept.
"""
import collections
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build as B  # noqa: E402

DIR32 = 0x0006

# `mov eax, fs:[__except_list]`: a relocation against absolute 0 by definition.
ABSOLUTE_ZERO_SYMBOLS = frozenset(("__except_list", "___except_list"))

Finding = collections.namedtuple("Finding", "name rva size offset symbol source")


def _read(row, size):
    obj = B.require_row_object(row)
    return B.read_object_symbol_bytes(obj, B.ledger_object_symbol(row), size)


def _retail(rva, size):
    return B.read_target_bytes(rva, size)


def scan(rows, read=None, retail=None):
    """Yield a Finding per row, plus the count of rows that could not be read.

    A row that cannot be read is counted, never silently dropped: a sweep that
    quietly skips what it failed to load reports "clean" for the very rows whose
    contradiction it never saw.
    """
    read = read or _read
    retail = retail or _retail
    unreadable = []
    for row in rows:
        size = int(row["target_size"])
        if size < 4:
            continue
        rva = int(row["target_rva"], 16)
        try:
            body, relocs = read(row, size)
            target = retail(rva, size)
        except BaseException:      # noqa: BLE001 - reported, not swallowed
            unreadable.append(row["name"])
            continue
        for offset, kind, symbol in sorted(relocs):
            if kind != DIR32 or offset + 4 > size:
                continue
            if symbol in ABSOLUTE_ZERO_SYMBOLS:
                continue
            if target[offset:offset + 4] == b"\0\0\0\0":
                yield Finding(row["name"], rva, size, offset, symbol, row["source"])
                break
    scan.unreadable = unreadable


def main(argv):
    rows = [r for r in B.load_function_rows() if r["status"] == "matched"]
    findings = list(scan(rows))
    by_body = collections.defaultdict(list)
    for f in findings:
        by_body[(f.rva, f.size)].append(f)
    print("matched rows scanned: %d (%d unreadable)"
          % (len(rows), len(scan.unreadable)))
    print("rows whose DIR32 store lands on all-zero retail bytes: %d" % len(findings))
    print("distinct bodies they sit on: %d\n" % len(by_body))
    for (rva, size), group in sorted(by_body.items(), key=lambda kv: -len(kv[1])):
        print("0x%08X %4dB  %d row(s)  retail: %s"
              % (rva, size, len(group), _retail(rva, size).hex()))
        for f in sorted(group, key=lambda f: f.name):
            print("      +%-4d %-58s %s" % (f.offset, f.name[:58], f.symbol[:44]))
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
