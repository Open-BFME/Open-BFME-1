#!/usr/bin/env python3
"""ea_flagtable: Zero Hour's table, the effects model, the CSV merge and the guard's free names."""
import sys
from pathlib import Path
from types import SimpleNamespace as NS

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import ea_flagtable as F  # noqa: E402
import ea_name_guard as guard  # noqa: E402


def image(code):
    return NS(base=0x400000, mem=bytes(code), imports={})


def test_a_flag_two_if_branches_pair_differently_names_nothing(tmp_path):
    src = tmp_path / "CommandLine.cpp"
    src.write_text('\t{ "-win", parseWin },\n#if A\n\t{ "-q", parseA },\n#else\n\t{ "-q", parseB },\n#endif\n'
                   '\t{ "-win", parseWin },\n')
    assert F.zh_handlers(src) == {"-win": "parseWin"}


def test_effects_ignore_register_allocation_and_refuse_unmodelled_code():
    # game: mov eax,[gd]; test; je; mov byte [eax+0x29],1; mov eax,1; ret
    game = image(bytes.fromhex("a1c8d52e0185c07404c6402901b801000000c3"))
    # WorldBuilder: the same handler as xor eax,eax / inc eax, with its own GlobalData pointer
    wb = image(bytes.fromhex("a1304b460185c07404c6402901" "33c040c3"))
    want = (("store", 0x29, "byte", ("const", 1)), ("return", ("const", 1)))
    assert F.effects(game, 0, 0x012ED5C8) == want
    assert F.effects(wb, 0, 0x01464B30) == want
    assert F.effects(image(bytes.fromhex("a1c8d52e01ffd0c3")), 0, 0x012ED5C8) is None   # call eax


def test_merge_replaces_flagtable_rows_and_a_label_name_at_their_address():
    row = lambda rva, kind, value, route, basis="": dict(rva=rva, kind=kind, value=value, route=route, basis=basis)
    existing = [row("0x00000010", "file", "A.cpp", "wb1"), row("0x00000010", "name", "A::f", "chain", "aligned"),
                row("0x00000020", "name", "parseOld", "flagtable", "strong")]
    got = F.merge(existing, [(0x10, "parseNew", "game table")])
    assert got == [row("0x00000010", "file", "A.cpp", "wb1"), row("0x00000010", "name", "parseNew", "flagtable", "strong")]


def test_guard_accepts_ea_free_function_name_and_refuses_another():
    ea = {0x609C0: ("parseWin", "flagtable", "strong")}
    ok = {"name": "?parseWin@@YAHQAPADH@Z", "target_rva": "0x000609C0", "notes": ""}
    bad = dict(ok, name="?parseWindowed@@YAHQAPADH@Z")
    assert guard.problems([ok], {}, ea, {}) == []
    assert len(guard.problems([bad], {}, ea, {}, zh={})) == 1
