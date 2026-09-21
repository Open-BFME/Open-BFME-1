"""An address is a number, however the ledger spells it.

functions.csv carries three spellings of target_rva: the canonical 0x0015B830,
lower-case hex, and short forms such as 0x1005. The duplicate check keyed on
the text, so the same claim under two spellings passed; the "claims two
addresses" check could not see it either, because the numbers are equal. The
stash check looked a bank up by the row's text in lower case, so a short
spelling never met its canonical 0x%08x file name.
"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import check_csv  # noqa: E402

SRC = "Code/GameEngine/Source/Common/System/GameMemory.cpp"


def problems_for(*rows):
    raw = check_csv.FUNCTIONS_HEADER + "\r\n" + "".join(row + "\r\n" for row in rows)
    out = []
    check_csv.check_functions(raw.encode(), out, {SRC}, {})
    return out


def test_same_claim_under_two_spellings_is_a_duplicate():
    found = problems_for(f"?f@@YAXXZ,,0x0015B830,16,{SRC},matched,",
                         f"?f@@YAXXZ,,0x0015b830,16,{SRC},matched,")
    assert any("exact duplicate row" in p for p in found), found


def test_short_spelling_is_the_same_address():
    found = problems_for(f"?f@@YAXXZ,,0x00001005,5,{SRC},matched,",
                         f"?f@@YAXXZ,,0x1005,5,{SRC},matched,")
    assert any("exact duplicate row" in p for p in found), found


def test_distinct_claims_stay_clean():
    assert not problems_for(f"?f@@YAXXZ,,0x0015B830,16,{SRC},matched,",
                            f"?g@@YAXXZ,,0x0015b840,16,{SRC},matched,")


def test_stash_lookup_meets_a_short_spelled_row(monkeypatch):
    stash = "reverse/attempts/0x00001005.cpp"
    ledger = (check_csv.FUNCTIONS_HEADER + "\r\n" + f"?f@@YAXXZ,,0x1005,5,{SRC},matched,\r\n").encode()
    blobs = {check_csv.ROOT / stash: b"// ?f@@YAXXZ\n// partial score=0.50 date=2026-09-21\nvoid f() {}\n",
             check_csv.ROOT / SRC: b"void f() {}\n"}
    monkeypatch.setattr(check_csv, "read_blobs", lambda paths, spec: {p: blobs[p] for p in paths})
    found = []
    check_csv.check_attempts(None, found, functions_raw=ledger, sources_ok={stash, SRC})
    assert any("already has real C++" in p for p in found), found
