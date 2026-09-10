"""The constant-return lane only consumes exact live dump scaffolds.

The input is deliberately ledger-shaped rather than a text-section byte scan:
the boundary and the ownership policy are part of what makes taking over a dump
safe.  Catch/Unwind rows and overlaps stay visible as exclusions.
"""
import importlib.util
import sys
from pathlib import Path

import pytest


TOOLS = Path(__file__).resolve().parents[1]


def _load():
    spec = importlib.util.spec_from_file_location("gen_small_getter_test", TOOLS / "gen_small.py")
    module = importlib.util.module_from_spec(spec)
    sys.modules[spec.name] = module
    spec.loader.exec_module(module)
    return module


gen_small = _load()


def _row(rva, *, source="Code/gen_asm/dump.asm", size=6,
         notes="gen-dump;ghidra=FUN_00000000", name=None, status="matched"):
    return {
        "name": name or f"?d_{rva:08x}@@YAXXZ",
        "target_rva": f"0x{rva:08X}",
        "target_size": str(size),
        "source": source,
        "status": status,
        "notes": notes,
    }


def test_population_is_exact_sorted_and_policy_filtered():
    body = bytes.fromhex("b878563412c3")
    rows = [
        _row(0x300),
        _row(0x100, notes="gen-dump;ghidra=Catch@00100100"),
        _row(0x200, notes="gen-dump;ghidra=Unwind@00100200"),
        _row(0x400),
        _row(0x402, source="Code/GameEngine/Source/Common/Real.cpp", size=4,
             notes="", name="?real@Thing@@YAXXZ"),
        _row(0x500, source="Code/GameEngine/Source/Common/Real.cpp", notes=""),
        _row(0x550, source="Code/gen_small/dumps_000.cpp"),
        _row(0x600, size=5),
        _row(0x700),
    ]
    images = {rva: body for rva in (0x100, 0x200, 0x300, 0x400, 0x500, 0x550)}
    images[0x600] = bytes.fromhex("b878563412")
    images[0x700] = bytes.fromhex("b878563412c2")

    def read(rva, size):
        return images.get(rva, b"")[:size]

    eligible, excluded = gen_small.getter_population(rows, read)
    assert [item[0] for item in eligible] == [0x300, 0x550]
    assert [(rva, reason) for rva, reason, _ in excluded] == [
        (0x100, "eh-funclet"),
        (0x200, "eh-funclet"),
        (0x400, "overlap=?real@Thing@@YAXXZ"),
    ]


def test_rendering_is_deterministic_and_uses_synthetic_method_names():
    bodies = {
        0x300: bytes.fromhex("b878563412c3"),
        0x350: bytes.fromhex("b8efbeaddec3"),
    }
    rows = [_row(0x350), _row(0x300)]

    def read(rva, size):
        return bodies[rva][:size]

    eligible, _ = gen_small.getter_population(rows, read)
    source = gen_small.render_getters(eligible, batch=3)
    reversed_source = gen_small.render_getters(
        gen_small.getter_population(list(reversed(rows)), read)[0], batch=3)
    assert source == reversed_source
    assert "gen-getters --batch 3" in source
    assert source.index("Gen_00000300") < source.index("Gen_00000350")
    assert "struct Gen_00000300 { unsigned m(); };" in source
    assert "unsigned Gen_00000300::m() { return 0x12345678u; }" in source


def test_funclet_exclusion_is_unconditional():
    row = _row(0x100, notes="gen-dump;ghidra=Catch@00100100")
    with pytest.raises(TypeError):
        gen_small.getter_population(
            [row], lambda rva, size: bytes.fromhex("b878563412c3"), include_eh=True)
    eligible, excluded = gen_small.getter_population(
        [row], lambda rva, size: bytes.fromhex("b878563412c3"))
    assert eligible == []
    assert excluded == [(0x100, "eh-funclet", 6)]


def test_batches_are_numbered_and_landed_batch_reuse_is_refused():
    source, pending = gen_small.getter_paths(7)
    assert source.as_posix().endswith("Code/gen_small/getters_007.cpp")
    assert pending.as_posix().endswith("build/gen_small/getters_007.json")

    owner = _row(0x100, source="Code/gen_small/getters_000.cpp")
    with pytest.raises(gen_small.FormatError, match=r"--batch 1"):
        gen_small.ensure_getter_batch_available(
            "Code/gen_small/getters_000.cpp", [owner], 1, 0)
    gen_small.ensure_getter_batch_available(
        "Code/gen_small/getters_000.cpp", [owner], 0, 0)
