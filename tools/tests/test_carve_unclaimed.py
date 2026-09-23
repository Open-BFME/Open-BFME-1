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
    # Two call targets two bytes apart: the first has no decoded terminal
    # before the second positive start, so it is not served; the second is.
    data = bytearray(0x1040)
    data[0x1000:0x1008] = bytes([0x90, 0x90, 0x90, 0x90, 0xC3, 0xCC, 0xCC, 0xCC])
    rows = carve.split_candidates(
        data, [(0x1000, 0x1010)], calls={0x1000: [0x0F00], 0x1002: [0x0F10]},
        validator=validator(data))
    assert [(r["target_rva"], int(r["target_size"])) for r in rows] == [("0x00001002", 3)]


def test_splitter_rejects_tail_before_reachable_cleanup():
    # A claimed EH funclet begins at 0x1004.  The parent has a backward jmp
    # immediately before that fence, but its conditional branch reaches the
    # epilogue at 0x1008.  Four bytes are not a complete parent body.
    data = bytearray(0x1020)
    data[0x1000:0x100c] = bytes([
        0x75, 0x06,       # jne 0x1008
        0xeb, 0xfc,       # jmp 0x1000
        0x90, 0x90, 0x90, 0x90,
        0xc3, 0xcc, 0xcc, 0xcc,
    ])
    rows = carve.split_candidates(
        data, [(0x1000, 0x1004)], calls={0x1000: [0x0f00]},
        validator=validator(data))
    assert rows == []


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
        writer.writerow({"rva": "0x3000", "size": "8", "start_evidence": "ghidra-start",
                         "callers": "0", "end_evidence": "jmp-tail", "ghidra": "Unwind@3000"})
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


def test_carved_attempts_follow_boundary_after_name_recovery(monkeypatch):
    row = {"name": "?d_00001000@@YAXXZ", "target_rva": "0x1000",
           "target_size": "120", "source": "reverse/carved.csv",
           "status": "carved", "callers": "1"}
    monkeypatch.setattr(eligibility, "open_dumps", lambda **kwargs: [row])
    monkeypatch.setattr(eligibility, "boundary_suspect", lambda *args: False)
    monkeypatch.setattr(eligibility, "latest_verdicts",
                        lambda: {0x1000: "blocked"})
    monkeypatch.setattr(eligibility, "attempt_counts",
                        lambda: {0x1000: 6})
    candidate = next_work.carved_candidates()[0]
    assert candidate["deferred_attempts"] == 6
    assert next_work.drop_logged([candidate])[0][0]["deferred_attempts"] == 6


def test_progress_does_not_import_carver():
    text = (ROOT / "tools" / "progress.py").read_text(encoding="utf-8")
    assert "carve_unclaimed" not in text


def test_ghidra_size_never_sets_the_end():
    # Ghidra says 2 bytes; the decoded body is nop, nop, ret then int3: 3 bytes.
    data = bytearray(0x1040)
    data[0x1000:0x1006] = bytes([0x90, 0x90, 0xC3, 0xCC, 0xCC, 0xCC])
    rows = carve.split_candidates(
        data, [(0x1000, 0x1020)], ghidra_sizes={0x1000: 2},
        validator=validator(data, {0x1000: 2}))
    assert [(r["target_rva"], int(r["target_size"]), r["end_evidence"])
            for r in rows] == [("0x00001000", 3, "ret+int3")]
    # Ghidra start with no decoded terminal before the fence: not served.
    data2 = bytearray(0x1040)
    data2[0x1000:0x1006] = bytes([0x90, 0x90, 0x90, 0xCC, 0xCC, 0xCC])
    rows2 = carve.split_candidates(
        data2, [(0x1000, 0x1020)], ghidra_sizes={0x1000: 3},
        validator=validator(data2, {0x1000: 3}))
    assert rows2 == []
