"""The duplicate-row hint must name the repair that is actually allowed.

check_csv used to answer every duplicate with `Fix: python3 tools/dedup_csv.py`.
That renormalises both ledgers (~157k lines) and conflicts with every branch in
flight, so docs/lessons.md has told agents three separate times to ignore the
hint -- and agents kept following it, because the tool is what they read.
"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import check_csv  # noqa: E402

SRC = "Code/GameEngine/Source/Common/System/GameMemory.cpp"
ROW = f"?dup@@YAXXZ,,0x00401000,16,{SRC},matched,\r\n"


def _problems(raw, checker):
    out = []
    checker(raw.encode(), out, {SRC}) if checker is check_csv.check_functions \
        else checker(raw.encode(), out)
    return out


def _hits(problems, needle):
    return [p for p in problems if needle in p]


def test_functions_duplicate_names_ledger_io_not_dedup():
    raw = f"{check_csv.FUNCTIONS_HEADER}\r\n{ROW}{ROW}"
    dups = _hits(_problems(raw, check_csv.check_functions), "exact duplicate row")
    assert dups, "a byte-identical repeated row must be reported"
    assert all("ledger_io" in p for p in dups), dups
    assert not any("Fix: python3 tools/dedup_csv.py" in p for p in dups), dups


def test_functions_duplicate_says_block_not_line():
    """Union merge duplicates contiguous blocks; a fixer expecting one line stops early."""
    raw = f"{check_csv.FUNCTIONS_HEADER}\r\n{ROW}{ROW}"
    dups = _hits(_problems(raw, check_csv.check_functions), "exact duplicate row")
    assert all("block" in p for p in dups), dups


def test_symbols_duplicate_names_ledger_io_not_dedup():
    row = "?sym@@3HA,0x00401000,\r\n"
    raw = f"{check_csv.SYMBOLS_HEADER}\r\n{row}{row}"
    dups = _hits(_problems(raw, check_csv.check_symbols), "exact duplicate row")
    assert dups, "a byte-identical repeated pin must be reported"
    assert all("ledger_io" in p for p in dups), dups
    assert not any("Fix: python3 tools/dedup_csv.py" in p for p in dups), dups


def test_repeated_header_is_a_merge_duplicate_not_a_normalisation():
    raw = (f"{check_csv.FUNCTIONS_HEADER}\r\n{ROW}"
           f"{check_csv.FUNCTIONS_HEADER}\r\n{ROW}")
    hdr = _hits(_problems(raw, check_csv.check_functions), "header appears")
    assert hdr, "a union-merged second header must be reported"
    assert all("ledger_io" in p for p in hdr), hdr


def test_whole_file_terminator_damage_still_points_at_dedup():
    """dedup_csv remains the right tool for its real job -- don't over-correct."""
    src = Path(check_csv.__file__).read_text()
    assert "Restore from git and use binary-safe edits (tools/dedup_csv.py" in src
