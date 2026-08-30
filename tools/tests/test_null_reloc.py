"""null_reloc finds rows whose relocated store lands where retail wrote nothing.

The tests that matter are the two the obvious implementation gets wrong: the SEH
prologue relocates against absolute zero and must NOT be flagged, and a row that
cannot be read must be counted rather than dropped into the clean bucket.
"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import null_reloc  # noqa: E402


def _row(name, rva="0x00001000", size="9", source="a.cpp"):
    return {"name": name, "export_rva": "", "target_rva": rva, "target_size": size,
            "source": source, "status": "matched", "notes": ""}


def _readers(bodies, targets):
    def read(row, size):
        got = bodies[row["name"]]
        if got is None:
            raise ValueError("no object for %s" % row["name"])
        return got
    return read, lambda rva, size: targets[rva][:size]


CTOR = b"\x8b\xc1\xc7\x00\x00\x00\x00\x00\xc3"


def test_a_vftable_store_over_all_zero_retail_bytes_is_flagged():
    """The live shape. Our constructor stores its own vftable through a DIR32;
    retail stores a literal zero. Masking blanks exactly those four bytes on both
    sides, so the row verifies while being on the wrong body."""
    rows = [_row("??0MemoryPoolObject@@QAE@XZ")]
    read, retail = _readers(
        {"??0MemoryPoolObject@@QAE@XZ": (CTOR, [(4, 0x0006, "??_7MemoryPoolObject@@6B@")])},
        {0x1000: CTOR})
    got, = null_reloc.scan(rows, read, retail)
    assert got.offset == 4
    assert got.symbol == "??_7MemoryPoolObject@@6B@"


def test_a_pointer_actually_present_in_retail_is_not_flagged():
    rows = [_row("??0Real@@QAE@XZ")]
    linked = b"\x8b\xc1\xc7\x00\x28\x37\x07\x01\xc3"
    read, retail = _readers(
        {"??0Real@@QAE@XZ": (CTOR, [(4, 0x0006, "??_7Real@@6B@")])},
        {0x1000: linked})
    assert list(null_reloc.scan(rows, read, retail)) == []


def test_the_seh_prologue_relocates_against_absolute_zero_and_is_exempt():
    """`mov eax, fs:[__except_list]` genuinely targets absolute 0. It opens every
    try-block in the tree, so without this exemption it buries every real hit."""
    body = b"\x64\xa1\x00\x00\x00\x00\x50\x90\x90"
    rows = [_row("?f@@YAXXZ")]
    read, retail = _readers(
        {"?f@@YAXXZ": (body, [(2, 0x0006, "__except_list")])},
        {0x1000: body})
    assert list(null_reloc.scan(rows, read, retail)) == []


def test_a_rel32_over_zero_bytes_is_not_this_defect():
    """Only DIR32 carries an absolute address. A REL32 displacement of zero is an
    ordinary self-relative call to the next instruction."""
    body = b"\x8b\xc1\xe8\x00\x00\x00\x00\x90\xc3"
    rows = [_row("?g@@YAXXZ")]
    read, retail = _readers(
        {"?g@@YAXXZ": (body, [(3, 0x0014, "?callee@@YAXXZ")])},
        {0x1000: body})
    assert list(null_reloc.scan(rows, read, retail)) == []


def test_a_site_running_past_the_body_is_not_read_off_the_end():
    rows = [_row("?h@@YAXXZ", size="6")]
    read, retail = _readers(
        {"?h@@YAXXZ": (b"\x90" * 6, [(4, 0x0006, "??_7X@@6B@")])},
        {0x1000: b"\x00" * 6})
    assert list(null_reloc.scan(rows, read, retail)) == []


def test_an_unreadable_row_is_counted_not_dropped():
    """A sweep that silently skips what it could not load reports 'clean' for the
    row whose contradiction it failed to read."""
    rows = [_row("?broken@@YAXXZ")]
    read, retail = _readers({"?broken@@YAXXZ": None}, {0x1000: CTOR})
    assert list(null_reloc.scan(rows, read, retail)) == []
    assert null_reloc.scan.unreadable == ["?broken@@YAXXZ"]


def test_one_finding_per_row_even_with_several_null_sites():
    body = b"\x8b\xc1\xc7\x00\x00\x00\x00\x00\xc7\x40\x04\x00\x00\x00\x00\xc3"
    rows = [_row("?two@@YAXXZ", size="16")]
    read, retail = _readers(
        {"?two@@YAXXZ": (body, [(4, 0x0006, "??_7A@@6B@"), (11, 0x0006, "??_7B@@6B@")])},
        {0x1000: body})
    got = list(null_reloc.scan(rows, read, retail))
    assert len(got) == 1 and got[0].offset == 4, "the first site is enough to condemn it"
