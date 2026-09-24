"""A ledger that cannot be read whole is an error, never an empty ledger.

Every picker builds on eligibility.load_rows, and an empty answer looks
exactly like a drained pool.
"""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import eligibility

HEADER = "name,export_rva,target_rva,target_size,source,status,notes\r\n"
ROW = "?f@@YAXXZ,0x00001000,0x00001000,16,Code/a.cpp,matched,\r\n"


def test_a_whole_ledger_loads(tmp_path):
    ledger = tmp_path / "functions.csv"
    ledger.write_text(HEADER + ROW + ROW, newline="")
    assert len(eligibility.load_rows(ledger, wait=0)) == 2


def test_a_ledger_with_no_rows_is_empty_and_not_an_error(tmp_path):
    ledger = tmp_path / "functions.csv"
    ledger.write_text(HEADER, newline="")
    assert eligibility.load_rows(ledger, wait=0) == []


def test_a_short_row_is_named_by_line(tmp_path):
    ledger = tmp_path / "functions.csv"
    ledger.write_text(HEADER + ROW + "?g@@YAXXZ,0x00002000,0x0000", newline="")
    with pytest.raises(eligibility.LedgerUnreadable, match="line 3"):
        eligibility.load_rows(ledger, wait=0)


def test_a_missing_ledger_is_an_error(tmp_path):
    with pytest.raises(eligibility.LedgerUnreadable, match="functions.csv"):
        eligibility.load_rows(tmp_path / "functions.csv", wait=0)


def test_bounded_ledger_load_still_rejects_an_unselected_torn_row(tmp_path):
    ledger = tmp_path / "functions.csv"
    ledger.write_text(HEADER + ROW + "?g@@YAXXZ,0x00002000,0x00002000", newline="")
    with pytest.raises(eligibility.LedgerUnreadable, match="line 3"):
        eligibility.load_rows(ledger, wait=0, rvas={0x1000})
    ledger.write_text(HEADER + ROW + ROW.replace("0x00001000", "0x00002000"), newline="")
    got = eligibility.load_rows(ledger, wait=0, rvas={0x1000})
    assert [row["target_rva"] for row in got] == ["0x00001000"]
