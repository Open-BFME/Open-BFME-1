"""load_symbol_map resolves a ledger row's object-symbol= name to that row.

A row whose source emits its body under an object-symbol= name (F4 drain,
re_attempts 59002/59046/59065/59164/59324) is the same body: a caller
compiled against the emitted name calls the ledger row, and the byte
comparison still decides.
"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build  # noqa: E402


def _map(monkeypatch, rows, thunks=None):
    monkeypatch.setattr(build, "load_all_function_rows", lambda: [dict(r) for r in rows])
    monkeypatch.setattr(build, "build_call_thunks", lambda: dict(thunks or {}))
    monkeypatch.setattr(build, "SYMBOLS", Path("/nonexistent/symbols.csv"))
    return build.load_symbol_map()


ROW = {"name": "?dup_003a5370@@YAXXZ", "target_rva": "0x003A5370",
       "notes": "object-symbol=?erase@?$vector@UNugget@@@_STL@@QAEPAUNugget@@PAU3@0@Z"}


def test_object_symbol_name_resolves_to_its_row(monkeypatch):
    found = _map(monkeypatch, [ROW], {0x3A5370: [0x12345]})
    assert found["?erase@?$vector@UNugget@@@_STL@@QAEPAUNugget@@PAU3@0@Z"] == [0x12345, 0x3A5370]
    assert found["?dup_003a5370@@YAXXZ"] == [0x12345, 0x3A5370]


def test_funclet_label_is_not_a_global_alias(monkeypatch):
    row = dict(ROW, name="?$L1@parent@@", notes="object-symbol=$L1234")
    assert "$L1234" not in _map(monkeypatch, [row])


def test_ledger_name_keeps_only_its_own_address(monkeypatch):
    real = {"name": ROW["notes"].split("=", 1)[1], "target_rva": "0x00500000", "notes": ""}
    found = _map(monkeypatch, [ROW, real])
    assert found[real["name"]] == [0x500000]


def test_name_emitted_by_two_rows_is_not_aliased(monkeypatch):
    other = dict(ROW, name="?dup_003a6000@@YAXXZ", target_rva="0x003A6000")
    found = _map(monkeypatch, [ROW, other])
    assert ROW["notes"].split("=", 1)[1] not in found


def test_row_without_object_symbol_adds_nothing(monkeypatch):
    row = {"name": "?f@@YAXXZ", "target_rva": "0x00001000", "notes": "gen-thunk"}
    assert _map(monkeypatch, [row]) == {"?f@@YAXXZ": [0x1000]}
