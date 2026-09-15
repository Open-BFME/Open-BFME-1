#!/usr/bin/env python3
"""data_coverage classifies data extents by their bytes and never touches
progress.py's headline (it is a separate tool with its own denominator)."""
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import data_coverage as dc  # noqa: E402

TEXT_LO, TEXT_HI = 0x401000, 0x401000 + 0x1000


def ptrs(*values):
    return b"".join(struct.pack("<I", v) for v in values)


def test_string_runs_ascii_and_utf16():
    assert dc.is_string_run(b"Lang\\%s\\Lotr.csf\x00junk")
    assert dc.is_string_run("Hello".encode("utf-16-le") + b"\x00\x00")
    assert not dc.is_string_run(b"\x01\x02\x03\x00")
    assert not dc.is_string_run(b"ab\x00")


def test_code_pointer_table_needs_two_text_pointers():
    assert dc.is_code_pointer_table(ptrs(0x401010, 0x401020, 0x12345678), TEXT_LO, TEXT_HI)
    assert not dc.is_code_pointer_table(ptrs(0x401010, 0x12345678), TEXT_LO, TEXT_HI)


def test_extent_classification_by_composition():
    strings = b"".join(w.encode() + b"\x00" for w in ["GRAYSCALE", "SOLID", "_mode", "Data/%s/Movies/"] * 3)
    assert dc.classify_extent(b"xy" + strings, TEXT_LO, TEXT_HI) == "string"
    table = ptrs(*([0x401010, 0x401040] * 10))
    assert dc.classify_extent(table, TEXT_LO, TEXT_HI) == "code-pointer-table"
    assert dc.classify_extent(b"\x00" * 200 + b"\x01", TEXT_LO, TEXT_HI) == "zero-initialised"
    assert dc.classify_extent(b"\x10" * 8, TEXT_LO, TEXT_HI) == "small-constant"
    assert dc.classify_extent(bytes(range(1, 200)), TEXT_LO, TEXT_HI) == "global"


def test_extents_split_at_references_and_cap():
    refs = {0x1000, 0x1010, 0x1100, 0x5000}
    got = dc.split_extents(refs, 0x1000, 0x2000)
    assert got == [(0x1000, 0x1010), (0x1010, 0x1100), (0x1100, 0x2000)]
    dc_max = dc.MAX_EXTENT
    assert dc.split_extents({0x1000}, 0x1000, 0x1000 + dc_max * 3) == [(0x1000, 0x1000 + dc_max)]


def test_scan_pointers_reports_sites():
    raw = b"\x90\x90" + ptrs(0xC80000) + b"\x90" + ptrs(0xC80000) + ptrs(0x123)
    hits = dc.scan_pointers(raw, 0x401000, 0xC73000, 0xF58000)
    assert hits == {0xC80000: [0x401002, 0x401007]}


def test_progress_does_not_import_data_coverage():
    text = (ROOT / "tools" / "progress.py").read_text(encoding="utf-8")
    assert "data_coverage" not in text
