"""land_batch superseding a Code/gen_asm/ byte dump with a real body.

A dump is retail's own bytes under a synthetic name: it holds a boundary and
carries no identity, so the body that recovers the identity has to be able to
take the range over. Before this, land_batch raised on the dump row's rva and
check_csv rejected the pair as an over-claim, so no generated body could land
over a dump at all.

The two dangerous edges are here too: a dump whose extent only partly matches
must stay a loud conflict (the boundary itself is in dispute), and a failed gate
must put the dump row AND its tombstone back exactly as they were.
"""
import importlib.util
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
HEADER = "name,export_rva,target_rva,target_size,source,status,notes"
DELETED_HEADER = "name,target_rva,reason"


def _load(name):
    spec = importlib.util.spec_from_file_location(name, TOOLS / f"{name}.py")
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


gen_small = _load("gen_small")

DUMP = "?d_00abcd00@@YAXXZ,,0x00ABCD00,32,Code/gen_asm/d_00abcd00.asm,matched,gen-dump;ghidra=FUN_00eacd00"
# The gen-dump note is what makes a row a dump, not the directory: 349 of them
# live in Code/gen_small/dumps_000.cpp.
GEN_SMALL_DUMP = DUMP.replace("Code/gen_asm/d_00abcd00.asm", "Code/gen_small/dumps_000.cpp")
REAL = "?realBody@Thing@@QAEXXZ,,0x00ABCD00,32,Code/GameEngine/Source/Common/Thing.cpp,matched,"


class Ledgers:
    """The three files land_batch writes, plus a gate whose verdict is a knob."""

    def __init__(self, tmp_path, monkeypatch, *, ledger_rows, gate=0):
        self.functions = tmp_path / "functions.csv"
        self.symbols = tmp_path / "symbols.csv"
        self.deleted = tmp_path / "deleted_rows.csv"
        self.functions.write_text(
            HEADER + "\r\n" + "".join(r + "\r\n" for r in ledger_rows), encoding="utf-8")
        self.symbols.write_text("name,address,notes\n", encoding="utf-8")
        self.deleted.write_text(DELETED_HEADER + "\n", encoding="utf-8")
        monkeypatch.setattr(gen_small.B, "FUNCTIONS", self.functions)
        monkeypatch.setattr(gen_small.B, "SYMBOLS", self.symbols)
        monkeypatch.setattr(gen_small, "DELETED", self.deleted)
        monkeypatch.setattr(gen_small, "LOCK_FILE", tmp_path / "lock")
        monkeypatch.setattr(gen_small, "run", lambda command, label: gate)

    def snapshot(self):
        return (self.functions.read_bytes(), self.symbols.read_bytes(),
                self.deleted.read_bytes())

    @property
    def rows(self):
        return self.functions.read_text(encoding="utf-8")


def test_exact_dump_row_is_superseded_and_tombstoned(tmp_path, monkeypatch):
    led = Ledgers(tmp_path, monkeypatch, ledger_rows=[DUMP])

    gen_small.land_batch([REAL], [], ["Code/GameEngine/Source/Common/Thing.cpp"])

    assert "?d_00abcd00@@YAXXZ" not in led.rows, "the dump row must be retracted"
    assert REAL in led.rows
    tombstone = led.deleted.read_text(encoding="utf-8")
    assert "?d_00abcd00@@YAXXZ,0x00ABCD00," in tombstone
    assert "?realBody@Thing@@QAEXXZ" in tombstone, "the tombstone names its successor"


def test_wrong_extent_at_the_same_rva_is_a_loud_conflict(tmp_path, monkeypatch):
    """Same start, different size: the boundary is in dispute, not the identity."""
    led = Ledgers(tmp_path, monkeypatch, ledger_rows=[DUMP])
    before = led.snapshot()
    wider = REAL.replace(",32,", ",48,")

    with pytest.raises(gen_small.FormatError) as exc:
        gen_small.land_batch([wider], [], ["Code/GameEngine/Source/Common/Thing.cpp"])

    assert "?realBody@Thing@@QAEXXZ" in str(exc.value)
    assert "?d_00abcd00@@YAXXZ" in str(exc.value), "both rows must be named"
    assert led.snapshot() == before


def test_partial_overlap_with_a_dump_is_a_loud_conflict(tmp_path, monkeypatch):
    """A body starting inside a dump is a boundary disagreement, never a takeover."""
    led = Ledgers(tmp_path, monkeypatch, ledger_rows=[DUMP])
    before = led.snapshot()
    shifted = REAL.replace(",0x00ABCD00,32,", ",0x00ABCD10,32,")

    with pytest.raises(gen_small.FormatError) as exc:
        gen_small.land_batch([shifted], [], ["Code/GameEngine/Source/Common/Thing.cpp"])

    assert "?realBody@Thing@@QAEXXZ" in str(exc.value)
    assert "?d_00abcd00@@YAXXZ" in str(exc.value), "both rows must be named"
    assert led.snapshot() == before


@pytest.mark.parametrize("source,notes", [
    ("Code/GameEngine/Source/Common/Other.cpp", ""),
    ("Code/gen_small/thunks_037.cpp", "gen-thunk;target=FUN_00eacd00"),
])
def test_only_a_dump_may_be_superseded(tmp_path, monkeypatch, source, notes):
    """Real sources and gen_small thunk placeholders both stay untouchable: only
    a row whose notes say gen-dump is bytes-without-identity."""
    incumbent = DUMP.replace("Code/gen_asm/d_00abcd00.asm", source).replace(
        "gen-dump;ghidra=FUN_00eacd00", notes)
    led = Ledgers(tmp_path, monkeypatch, ledger_rows=[incumbent])
    before = led.snapshot()

    with pytest.raises(gen_small.FormatError):
        gen_small.land_batch([REAL], [], ["Code/GameEngine/Source/Common/Thing.cpp"])

    assert led.snapshot() == before


def test_a_dump_outside_gen_asm_is_superseded_the_same_way(tmp_path, monkeypatch):
    """The 349-row case the old path check refused: notes say dump, path does not.

    Keying the supersede on Code/gen_asm/ left every one of those addresses
    unconvertible — the real body could not take a range no real body owned.
    """
    led = Ledgers(tmp_path, monkeypatch, ledger_rows=[GEN_SMALL_DUMP])

    gen_small.land_batch([REAL], [], ["Code/GameEngine/Source/Common/Thing.cpp"])

    assert "?d_00abcd00@@YAXXZ" not in led.rows, "the dump row must be retracted"
    assert REAL in led.rows
    assert "?d_00abcd00@@YAXXZ,0x00ABCD00," in led.deleted.read_text(encoding="utf-8")


def test_failed_gate_restores_the_dump_row_and_the_tombstone(tmp_path, monkeypatch):
    led = Ledgers(tmp_path, monkeypatch, ledger_rows=[DUMP], gate=1)
    before = led.snapshot()

    with pytest.raises(SystemExit):
        gen_small.land_batch([REAL], [], ["Code/GameEngine/Source/Common/Thing.cpp"])

    assert led.snapshot() == before, "a red gate leaves nothing behind, tombstone included"
