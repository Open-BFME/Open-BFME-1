#!/usr/bin/env python3
"""The four shapes a rebase inflicts on a merge=union ledger, and the repair.

Every one of these was seen on master during a single session on 2026-09-07;
symbols.csv arrived DOUBLED three separate times. A rebase runs no hook, so
nothing else catches any of it -- the damage surfaces later as a push the gate
refuses, at which point the cause is many commits behind.
"""
import importlib.util
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

spec = importlib.util.spec_from_file_location("ledger_repair", TOOLS / "ledger_repair.py")
ledger_repair = importlib.util.module_from_spec(spec)
spec.loader.exec_module(ledger_repair)

import ledger_io

FN_HEADER = b"name,demangled,target_rva,size,source,status,notes\r\n"
SY_HEADER = b"name,address,notes\r\n"


@pytest.fixture
def ledger(tmp_path, monkeypatch):
    """A throwaway repo root with the three ledger files and a game/ tree."""
    (tmp_path / "targets/game/reverse").mkdir(parents=True)
    (tmp_path / "game").mkdir()
    (tmp_path / "targets/game/reverse" / "deleted_rows.csv").write_bytes(b"name,target_rva,reason\r\n")
    monkeypatch.setattr(ledger_repair, "ROOT", tmp_path)
    monkeypatch.chdir(tmp_path)
    return tmp_path


def write(root, functions=b"", symbols=b""):
    (root / "targets/game/reverse" / "functions.csv").write_bytes(FN_HEADER + functions)
    (root / "targets/game/reverse" / "symbols.csv").write_bytes(SY_HEADER + symbols)


def rows(path):
    return [ledger_io.fields(p) for i, (p, _t)
            in enumerate(ledger_io.split_records(path.read_bytes())) if i]


def test_an_exact_duplicate_record_is_dropped_keeping_the_first(ledger):
    row = b"?a@@YAXXZ,0x00001000,note\r\n"
    write(ledger, symbols=row + row)
    ledger_repair.repair()
    assert len(rows(ledger / "targets/game/reverse" / "symbols.csv")) == 1


def test_a_row_naming_a_source_that_no_longer_exists_yields_to_one_that_does(ledger):
    (ledger / "game" / "Live.cpp").write_text("")
    write(ledger, functions=(
        b"?a@@YAXXZ,,0x00001000,8,game/Gone.cpp,matched,\r\n"
        b"?a@@YAXXZ,,0x00001000,8,game/Live.cpp,matched,\r\n"))
    ledger_repair.repair()
    kept = rows(ledger / "targets/game/reverse" / "functions.csv")
    assert [f[4] for f in kept] == ["game/Live.cpp"]


def test_a_tombstoned_row_that_came_back_is_dropped_again(ledger):
    (ledger / "targets/game/reverse" / "deleted_rows.csv").write_bytes(
        b"name,target_rva,reason\r\n?phantom@@YAXXZ,0x00002000,never shipped\r\n")
    (ledger / "game" / "Live.cpp").write_text("")
    write(ledger, functions=(
        b"?phantom@@YAXXZ,,0x00002000,8,game/Live.cpp,matched,\r\n"
        b"?real@@YAXXZ,,0x00003000,8,game/Live.cpp,matched,\r\n"))
    kept = None
    ledger_repair.repair()
    kept = rows(ledger / "targets/game/reverse" / "functions.csv")
    assert [f[0] for f in kept] == ["?real@@YAXXZ"]


def test_a_lone_lf_in_a_crlf_symbols_file_is_normalised(ledger):
    """The union driver treats a differently-terminated line as a DISTINCT line
    and re-adds it on every rebase; that is how 4,172 pins became 8,784."""
    write(ledger, symbols=b"?a@@YAXXZ,0x00001000,a\r\n?b@@YAXXZ,0x00002000,b\n")
    ledger_repair.repair()
    raw = (ledger / "targets/game/reverse" / "symbols.csv").read_bytes()
    assert raw.count(b"\r\n") == 3 and raw.count(b"\n") == 3


def test_functions_csv_keeps_its_mixed_terminators(ledger):
    """functions.csv legitimately mixes all three, so normalising it would
    rewrite the whole file and make every row look edited to conversion_gate."""
    (ledger / "game" / "Live.cpp").write_text("")
    write(ledger, functions=(
        b"?a@@YAXXZ,,0x00001000,8,game/Live.cpp,matched,\r\n"
        b"?b@@YAXXZ,,0x00002000,8,game/Live.cpp,matched,\n"))
    ledger_repair.repair()
    raw = (ledger / "targets/game/reverse" / "functions.csv").read_bytes()
    assert b",matched,\n" in raw and b",matched,\r\n" in raw
