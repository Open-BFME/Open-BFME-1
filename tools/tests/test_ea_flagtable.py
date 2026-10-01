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


GD = 0x012ED5C8
GUARDED_WIN = (("if", (("cmp", ("gd",), ("const", 0)), "je"), (("return", ("const", 1), 0),),
                (("store", 0x29, "byte", ("const", 1)), ("return", ("const", 1), 0))),)


def test_effects_ignore_register_allocation_and_refuse_unmodelled_code():
    # game: mov eax,[gd]; test; je; mov byte [eax+0x29],1; mov eax,1; ret
    game = image(bytes.fromhex("a1c8d52e0185c07404c6402901b801000000c3"))
    # WorldBuilder: the same handler as xor eax,eax / inc eax, with its own GlobalData pointer
    wb = image(bytes.fromhex("a1304b460185c07404c6402901" "33c040c3"))
    assert F.effects(game, 0, GD) == GUARDED_WIN
    assert F.effects(wb, 0, 0x01464B30) == GUARDED_WIN
    assert F.effects(image(bytes.fromhex("a1c8d52e01ffd0c3")), 0, GD) is None   # call eax
    assert F.effects(image(bytes.fromhex("a1c8d52e0185c074fec3")), 0, GD) is None   # je to itself: a loop


def test_effects_keep_branch_conditions_but_not_block_layout():
    # cmp eax,0 sets test eax,eax's flags; jne over a ret to the store is the same handler
    cmp_form = image(bytes.fromhex("a1c8d52e0183f8007404c6402901b801000000c3"))
    jne_form = image(bytes.fromhex("a1c8d52e0185c07506b801000000c3c6402901b801000000c3"))
    assert F.effects(cmp_form, 0, GD) == F.effects(jne_form, 0, GD) == GUARDED_WIN
    # jne where je stood stores only when GlobalData is null: a different handler
    inverted = image(bytes.fromhex("a1c8d52e0185c07504c6402901b801000000c3"))
    assert F.effects(inverted, 0, GD) not in (None, GUARDED_WIN)
    # a guard on a different value is a different handler too
    count = image(bytes.fromhex("a1c8d52e01837c240801" "7e04c6402901b801000000c3"))
    assert F.effects(count, 0, GD) not in (None, GUARDED_WIN)


def test_effects_name_the_global_an_or_writes():
    or_mem = F.effects(image(bytes.fromhex("830da06f2a0104b801000000c3")), 0, GD)
    or_reg = F.effects(image(bytes.fromhex("a1a06f2a0183c804a3a06f2a01b801000000c3")), 0, GD)
    elsewhere = F.effects(image(bytes.fromhex("830da46f2a0104b801000000c3")), 0, GD)
    flag_word = ("global", 0x012A6FA0)
    assert or_mem == or_reg == (("set", flag_word, "dword", ("bitor", ("load", flag_word, "dword"), ("const", 4))),
                                ("return", ("const", 1), 0))
    assert elsewhere != or_mem
    # a WorldBuilder global matches a game one only where a shared flag writes both
    wb_or = F.effects(image(bytes.fromhex("830d10bc3b0104b801000000c3")), 0, 0x01464B30)
    assert F.rename(wb_or, {}) != or_mem
    mapping = {}
    F.unify(or_mem, wb_or, mapping)
    assert mapping == {0x013BBC10: 0x012A6FA0} and F.rename(wb_or, mapping) == or_mem


def test_an_ambiguous_match_names_nothing():
    store = lambda off: (("store", off, "byte", ("const", 1)), ("return", ("const", 1), 0))
    a, b, c = store(1), store(2), store(3)
    trees = {"-twoBodies": a, "-twoHandlers": b, "-twin": b, "-unique": c, "-returnOnly": (("return", ("const", 1), 0),)}
    index = {a: {0x10, 0x20}, b: {0x30}, c: {0x40}, trees["-returnOnly"]: {0x50}}
    matched, notes = F.pair(trees, ["-twoBodies", "-twoHandlers", "-unique", "-returnOnly"], index)
    assert matched == {"-unique": 0x40}
    assert any("-twoBodies" in n and "0x00000010" in n and "0x00000020" in n for n in notes)
    assert any("-twoHandlers" in n and "-twin" in n for n in notes)


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
