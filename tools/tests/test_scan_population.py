"""What a recipe engine may SCAN over, and what still blocks it.

`land_batch` supersedes a lone gen-dump row of the exact same extent and nothing
else (tools/tests/test_land_supersede.py). The scan side has to offer that same
set: narrower and whole ranges stay invisible to every engine, wider and the
engine emits a body over ground another row holds and the wave aborts at land
time.

The two ways the set drifted from validate_rows' both live here. Keying it on
`Code/gen_asm/` withheld the 349 dumps in `Code/gen_small/dumps_000.cpp`, and
hiding a dump from `owned` also hid any UNMATCHED row sharing its address, which
the matched-only overlap index cannot see either.
"""
import collections
import importlib.util
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

HEADER = "name,export_rva,target_rva,target_size,source,status,notes"
GEN_ASM_DUMP = ("?d_00abcd00@@YAXXZ,,0x00ABCD00,32,Code/gen_asm/d_00abcd00.asm,"
                "matched,gen-dump;ghidra=FUN_00eacd00")
GEN_SMALL_DUMP = ("?d_00abce00@@YAXXZ,,0x00ABCE00,48,Code/gen_small/dumps_000.cpp,"
                  "matched,gen-dump;ghidra=FUN_00eace00")
REAL = ("?realBody@Thing@@QAEXXZ,,0x00ABCF00,64,"
        "Code/GameEngine/Source/Common/Thing.cpp,matched,")
# A hypothesis about an address, not proof the ground is spoken for -- and it
# sits on top of the gen_asm dump.
HYPOTHESIS = ("?guess@Thing@@QAEXXZ,,0x00ABCD00,32,"
              "Code/GameEngine/Source/Common/Thing.cpp,unmatched,")

ASM_RVA, ASM_SIZE = 0x00ABCD00, 32
SMALL_RVA, SMALL_SIZE = 0x00ABCE00, 48


def _module(name):
    """The live module under `name`; sibling test files re-exec these."""
    if name not in sys.modules:
        spec = importlib.util.spec_from_file_location(name, TOOLS / f"{name}.py")
        module = importlib.util.module_from_spec(spec)
        sys.modules[name] = module
        spec.loader.exec_module(module)
    return sys.modules[name]


@pytest.fixture
def gen_small(tmp_path, monkeypatch):
    """gen_small reading a scratch ledger, ledger rows chosen per test."""
    module = _module("gen_small")
    ledger = tmp_path / "functions.csv"

    def with_rows(*rows):
        ledger.write_text(HEADER + "\r\n" + "".join(row + "\r\n" for row in rows),
                          encoding="utf-8")
        return module

    monkeypatch.setattr(module.B, "FUNCTIONS", ledger)
    module.with_rows = with_rows
    return with_rows


# --------------------------------------------------------------------------
# dump_boundaries: which dumps a scan may see through
# --------------------------------------------------------------------------

def test_a_dump_outside_gen_asm_is_offered_the_same_way(gen_small):
    """land_batch supersedes it, so the scan has to be able to reach it."""
    boundaries = gen_small(GEN_ASM_DUMP, GEN_SMALL_DUMP, REAL).dump_boundaries()
    assert boundaries == {ASM_RVA: (ASM_SIZE, "?d_00abcd00@@YAXXZ"),
                          SMALL_RVA: (SMALL_SIZE, "?d_00abce00@@YAXXZ")}


def test_a_real_row_is_never_offered(gen_small):
    assert 0x00ABCF00 not in gen_small(GEN_ASM_DUMP, REAL).dump_boundaries()


def test_an_unmatched_dump_row_is_not_a_proven_boundary(gen_small):
    """validate_rows would take it over; the scan will not scan at its width.

    The value of a dump boundary here is that its extent is verified. An
    unmatched row is a hypothesis about an address, and a candidate scanned at
    an unverified width costs the whole wave rather than the one site.
    """
    unmatched_dump = GEN_ASM_DUMP.replace(",matched,", ",unmatched,")
    assert gen_small(unmatched_dump, GEN_SMALL_DUMP).dump_boundaries() == {
        SMALL_RVA: (SMALL_SIZE, "?d_00abce00@@YAXXZ")}


def test_a_second_row_at_the_address_withdraws_the_boundary(gen_small):
    """An unmatched row shares the dump's rva: opaque to `owned`, invisible to
    the matched-range index, and fatal to the wave at land time."""
    boundaries = gen_small(GEN_ASM_DUMP, HYPOTHESIS, GEN_SMALL_DUMP).dump_boundaries()
    assert ASM_RVA not in boundaries
    assert SMALL_RVA in boundaries, "the uncontested dump still is"


# --------------------------------------------------------------------------
# scan_population: the two inventories have to agree
# --------------------------------------------------------------------------

def test_a_dump_the_inventory_never_saw_becomes_scannable(gen_small):
    """12,816 dump ranges have no ghidra entry at all; that was the whole point."""
    module = gen_small(GEN_ASM_DUMP)
    population = module.scan_population([(0x00B00000, 16, "FUN_00b00000")],
                                        module.dump_boundaries())
    assert population == [(ASM_RVA, ASM_SIZE, "?d_00abcd00@@YAXXZ"),
                          (0x00B00000, 16, "FUN_00b00000")]


def test_the_inventory_and_the_dump_must_agree_on_the_extent(gen_small):
    """A verified range booked at two widths is a reconciliation, not a choice."""
    module = gen_small(GEN_ASM_DUMP)
    with pytest.raises(module.FormatError) as exc:
        module.scan_population([(ASM_RVA, ASM_SIZE + 16, "FUN_00eacd00")],
                               module.dump_boundaries())
    assert f"0x{ASM_RVA:08X}" in str(exc.value)
    assert f"ghidra={ASM_SIZE + 16}B" in str(exc.value)
    assert f"dump={ASM_SIZE}B" in str(exc.value)


def test_an_agreeing_entry_is_not_a_dispute(gen_small):
    module = gen_small(GEN_ASM_DUMP)
    assert module.scan_population([(ASM_RVA, ASM_SIZE, "FUN_00eacd00")],
                                  module.dump_boundaries()) == [
        (ASM_RVA, ASM_SIZE, "?d_00abcd00@@YAXXZ")]


# --------------------------------------------------------------------------
# tg_scan: transparency is exact-range, and only over the dump
# --------------------------------------------------------------------------

RVA, SIZE = 0x00401000, 32
BODY = bytes(range(SIZE))


def scan(monkeypatch, owned, ledger_rows, transparent, entry_size=SIZE):
    module = _module("gen_small")
    monkeypatch.setattr(module.B, "read_target_bytes", lambda rva, size: BODY[:size])
    pattern = module.TgPattern("?probe@@YAXXZ", None, None, SIZE, BODY, (), "a")
    index = module.overlap_index(ledger_rows)
    return module.tg_scan({pattern.symbol: pattern}, [(RVA, entry_size, "site")],
                          set(), owned, index, transparent)


def row(name, rva, size, status="matched"):
    return {"name": name, "rva": rva, "size": size, "status": status}


DUMP_ROW = row("?d_00401000@@YAXXZ", RVA, SIZE)
TRANSPARENT = {RVA: (SIZE, "?d_00401000@@YAXXZ")}


def test_open_ground_is_scanned(monkeypatch):
    assert RVA in scan(monkeypatch, {}, [], {})


def test_an_exact_range_dump_is_seen_through(monkeypatch):
    assert RVA in scan(monkeypatch, {RVA: "Code/gen_asm/x.asm"}, [DUMP_ROW], TRANSPARENT)


def test_the_same_dump_blocks_when_no_boundary_is_offered(monkeypatch):
    assert RVA not in scan(monkeypatch, {RVA: "Code/gen_asm/x.asm"}, [DUMP_ROW], {})


def test_a_dump_of_another_extent_is_not_seen_through(monkeypatch):
    """Same start, different size: validate_rows calls that a boundary dispute."""
    assert RVA not in scan(monkeypatch, {RVA: "Code/gen_asm/x.asm"},
                           [row("?d_00401000@@YAXXZ", RVA, SIZE + 4)],
                           {RVA: (SIZE + 4, "?d_00401000@@YAXXZ")})


@pytest.mark.parametrize("other", [
    row("?real@@YAXXZ", RVA, SIZE),               # exactly the same range
    row("?big@@YAXXZ", RVA - 16, SIZE + 64),      # contains it
    row("?tail@@YAXXZ", RVA + SIZE - 8, 64),      # overlaps its tail
])
def test_a_matched_row_over_the_range_still_blocks(monkeypatch, other):
    """Transparency skips ONE name in the overlap index: the dump's own."""
    assert RVA not in scan(monkeypatch, {RVA: "Code/gen_asm/x.asm"},
                           [DUMP_ROW, other], TRANSPARENT)


def test_the_two_halves_agree_on_what_is_supersedable(gen_small, monkeypatch):
    """dump_boundaries offers a range; validate_rows accepts that same range.

    Asserted against the live pair rather than a hand-built dict, because the
    scan drifting wider than the landing transaction is what a wave dies of.
    """
    module = gen_small(GEN_ASM_DUMP, GEN_SMALL_DUMP, REAL)
    ledger = module.parse_ledger(module.B.FUNCTIONS.read_bytes())
    for rva, (size, name) in sorted(module.dump_boundaries().items()):
        body = module.format_row(f"?taken_{rva:08x}@@YAXXZ", rva, size,
                                 "Code/GameEngine/Source/Common/Thing.cpp", "")
        _append, _landed, retract = module.validate_rows([body], ledger)
        assert [owner["name"] for owner, *_ in retract] == [name]
