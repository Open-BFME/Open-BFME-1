import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import one_identity as oi  # noqa: E402


def row(name, rva, size=7):
    return {"name": name, "target_rva": f"0x{rva:08X}", "target_size": str(size), "status": "matched"}


def test_placeholders_do_not_count_as_real_names():
    rows = [row("?getA@C@@QAEHXZ", 0x100), row("?dup_00000100@@YAXXZ", 0x100),
            row("?getB@D@@QAEHXZ", 0x200), row("?getC@E@@QAEHXZ", 0x200)]
    names = oi.real_names_by_address(rows)
    assert names[0x100] == {"?getA@C@@QAEHXZ"}
    assert names[0x200] == {"?getB@D@@QAEHXZ", "?getC@E@@QAEHXZ"}


def test_surplus_counts_every_real_name_beyond_the_first_per_body():
    rows = [row("?a@C@@QAEHXZ", 0x100), row("?b@C@@QAEHXZ", 0x100), row("?c@C@@QAEHXZ", 0x100),
            row("?d@C@@QAEHXZ", 0x200), row("?dup_00000200@@YAXXZ", 0x200)]
    assert oi.surplus(rows) == 2


def test_link_table_stops_at_the_first_non_jump_and_groups_entries_by_body():
    base = 0x1000
    text = bytearray(b"\xcc" * 5)
    for target in (0x2000, 0x3000, 0x2000):
        here = base + len(text)
        text += b"\xe9" + struct.pack("<i", target - (here + 5))
    text += b"\xcc" * 8
    end, entries = oi.link_table(bytes(text), base)
    assert end == base + 5 + 15
    assert entries[0x2000] == [0x1005, 0x100F]
    assert entries[0x3000] == [0x100A]


def test_folding_evidence_counts_identical_separate_bodies_and_skips_rel32():
    base = 0x1000
    getter = bytes.fromhex("8b4104c3")
    call = bytes.fromhex("e800000000c3")
    text = getter + getter + getter[:3] + b"\xc2" + call + call
    rows = [row("?end@?$vector@H@_STL@@QAEPAHXZ", base, 4),
            row("?end@?$vector@M@_STL@@QAEPAMXZ", base + 4, 4),
            row("?get@C@@QAEHXZ", base + 8, 4),
            row("?f@@YAXXZ", base + 12, 6), row("?g@@YAXXZ", base + 18, 6)]
    patterns, bodies, template, (widest, rvas) = oi.folding_evidence(rows, text, base, base)
    assert (patterns, bodies, template) == (1, 2, 2)
    assert widest == getter and sorted(rvas) == [base, base + 4]
