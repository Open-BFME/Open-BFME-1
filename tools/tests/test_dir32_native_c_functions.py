"""Native C callbacks need matched code ownership, not a C++ name suffix or pin."""
from pathlib import Path
import sys

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import body_guard
import build
import ilt_oracle

BASE, BODY, ILT, WRONG = 0x400000, 0x1700, 0x1200, 0x1900


def check(monkeypatch, symbol, *, rows=(), address=BODY, pins=None, data=None, recorded=None):
    monkeypatch.setattr(build, "_dir32_guard_rows", lambda: list(rows))
    monkeypatch.setattr(body_guard, "_text_follow", lambda rva: BODY if rva == ILT else rva)
    monkeypatch.setattr(body_guard, "_row_sizes", lambda: {})
    monkeypatch.setattr(ilt_oracle, "retail_ilt", lambda exe: (BASE + ILT, [BODY]))
    return build.unrecorded_dir32_problem(symbol, BASE + address,
                                          (recorded or {}, data or {}),
                                          pins if pins is not None else {symbol: [BODY]})


def row(symbol, *, address=BODY, source="game/Callback.c", status="matched", notes=""):
    return symbol, address, source, status, notes


@pytest.mark.parametrize("symbol", ["_callback", "_callback@4", "@callback@4"])
@pytest.mark.parametrize("address", [BODY, ILT])
def test_native_c_callback_uses_its_matched_body_or_verified_ilt(monkeypatch, symbol, address):
    assert check(monkeypatch, symbol, rows=[row(symbol)], address=address) is None


def test_native_c_callback_cannot_use_an_additive_pin_for_another_body(monkeypatch):
    assert "places elsewhere" in check(monkeypatch, "_callback", rows=[row("_callback")],
                                       address=WRONG, pins={"_callback": [BODY, WRONG]})


@pytest.mark.parametrize("symbol", ["_global", "_global@4", "_globalZ", "__real@00000000", "_callback"])
def test_a_pin_without_a_matched_native_function_is_not_code_ownership(monkeypatch, symbol):
    assert check(monkeypatch, symbol) is not None


@pytest.mark.parametrize("changes", [
    {"status": "unmatched"},
    {"source": "game/gen_small/fun_000.cpp"},
    {"source": "game/gen_asm/d_00001700.asm"},
    {"notes": "object-symbol=_other"},
])
def test_native_c_callback_requires_a_real_row_linking_under_its_own_name(monkeypatch, changes):
    assert check(monkeypatch, "_callback", rows=[row("_callback", **changes)]) is not None


def test_another_rows_object_symbol_cannot_invent_a_native_c_identity(monkeypatch):
    assert check(monkeypatch, "_callback", rows=[row("?dup_00001700@@YAXXZ", notes="object-symbol=_callback")]) is not None


def test_ambiguous_native_function_placements_fail(monkeypatch):
    assert check(monkeypatch, "_callback", rows=[row("_callback"), row("_callback", address=WRONG)]) is not None


def test_native_function_rejects_conflicting_data_ownership(monkeypatch):
    assert check(monkeypatch, "_callback", rows=[row("_callback")], data={"_datum": BASE + BODY}) is not None
    assert check(monkeypatch, "_callback", rows=[row("_callback")], data={"_callback": BASE + WRONG}) is not None
    assert check(monkeypatch, "_callback", rows=[row("_callback")],
                 recorded={BASE + BODY: {"_other"}}) is not None


def test_equal_bytes_or_an_unaligned_jump_do_not_create_a_native_c_identity(monkeypatch):
    monkeypatch.setattr(body_guard, "callee_twin", lambda *args: True)
    assert check(monkeypatch, "_callback", rows=[row("_callback")], address=WRONG) is not None
    assert check(monkeypatch, "_callback", rows=[row("_callback")], address=ILT + 1) is not None


def test_existing_cpp_ilt_function_handling_stays_exact(monkeypatch):
    symbol = "??1Callback@@QAE@XZ"
    assert check(monkeypatch, symbol, address=ILT) is None
    assert "places elsewhere" in check(monkeypatch, symbol, address=WRONG)


def test_legitimate_c_data_still_requires_its_own_exact_data_placement(monkeypatch):
    assert check(monkeypatch, "_datum", data={"_datum": BASE + BODY}) is None
    assert check(monkeypatch, "_datum", data={"_datum": BASE + WRONG}) is not None
