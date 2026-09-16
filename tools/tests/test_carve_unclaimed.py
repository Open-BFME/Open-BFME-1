#!/usr/bin/env python3
"""Synthetic and integration contracts for the carved anonymous lane."""
import csv
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

import boundary_validator  # noqa: E402
import carve_unclaimed as carve  # noqa: E402
import eligibility  # noqa: E402
import next_work  # noqa: E402


def validator(data, sizes=None):
    sizes = sizes or {}
    return boundary_validator.BoundaryValidator(lambda r, n: data[r:r + n], sizes)


def test_splitter_uses_callers_and_ret_int3_tail():
    data = bytearray(0x1040)
    data[0x1000:0x1005] = b"\x90\xc3\xcc\xcc\xcc"
    data[0x1010:0x1015] = b"\x90\xc3\xcc\xcc\xcc"
    rows = carve.split_candidates(
        data, [(0x1000, 0x1020)], calls={0x1000: [0x0F00, 0x0F10],
                                         0x1010: [0x0F20]},
        validator=validator(data))
    assert [(r["target_rva"], int(r["target_size"]), r["callers"])
            for r in rows] == [("0x00001000", 2, "2"),
                                ("0x00001010", 2, "1")]
    assert all(r["end_evidence"] == "ret+int3" for r in rows)


def test_splitter_rejects_overlapping_positive_extents():
    data = bytearray(0x1040)
    data[0x1000:0x1008] = b"\x90\xc3\xcc\xcc\xcc\x90\xc3\xcc"
    data[0x1004:0x1008] = b"\x90\xc3\xcc\xcc"
    rows = carve.split_candidates(
        data, [(0x1000, 0x1010)],
        ghidra_sizes={0x1000: 8, 0x1004: 4},
        validator=validator(data, {0x1000: 8, 0x1004: 4}))
    assert [r["target_rva"] for r in rows] == ["0x00001004"]


def test_shrink_on_land_excludes_newly_claimed_gap():
    data = bytearray(0x1030)
    data[0x1000:0x1005] = b"\x90\xc3\xcc\xcc\xcc"
    assert carve.split_candidates(
        data, [(0x1000, 0x1020)], calls={0x1000: [0x0F00]},
        validator=validator(data))
    assert carve.split_candidates(
        data, [(0x1005, 0x1020)], calls={0x1000: [0x0F00]},
        validator=validator(data)) == []


def test_carved_rows_shape_and_filter_stale_overlap(tmp_path):
    path = tmp_path / "carved.csv"
    with path.open("w", newline="") as fh:
        writer = csv.DictWriter(fh, fieldnames=carve.HEADER)
        writer.writeheader()
        writer.writerow({"rva": "0x1000", "size": "2", "start_evidence": "rel32-call/jmp",
                         "callers": "2", "end_evidence": "ret+int3", "ghidra": ""})
        writer.writerow({"rva": "0x2000", "size": "2", "start_evidence": "ghidra-start",
                         "callers": "0", "end_evidence": "ghidra-size", "ghidra": "FUN_2000"})
    rows = eligibility.carved_rows(path, rows=[{"target_rva": "0x1000",
                                                "target_size": "2"}])
    assert [r["target_rva"] for r in rows] == ["0x00002000"]
    assert rows[0]["status"] == "carved"
    assert rows[0]["source"] == "reverse/carved.csv"
    assert rows[0]["callers"] == "0"


def test_carved_ranking_uses_expected_bytes(monkeypatch):
    rows = [
        {"name": "?d_00001000@@YAXXZ", "target_rva": "0x1000", "target_size": "400",
         "source": "reverse/carved.csv", "status": "carved", "callers": "0",
         "start_evidence": "ghidra-start", "end_evidence": "ghidra-size", "ghidra": ""},
        {"name": "?d_00002000@@YAXXZ", "target_rva": "0x2000", "target_size": "300",
         "source": "reverse/carved.csv", "status": "carved", "callers": "3",
         "start_evidence": "rel32-call/jmp", "end_evidence": "ret+int3", "ghidra": ""},
    ]
    monkeypatch.setattr(eligibility, "open_dumps", lambda **kwargs: rows)
    monkeypatch.setattr(eligibility, "boundary_suspect", lambda *args: False)
    got = next_work.carved_candidates()
    assert [c["target_rva"] for c in got] == ["0x2000", "0x1000"]
    assert got[0]["warmth"] == 6


def test_progress_does_not_import_carver():
    text = (ROOT / "tools" / "progress.py").read_text(encoding="utf-8")
    assert "carve_unclaimed" not in text
