"""Relocation masks must never invent retail instructions in probe output."""
from pathlib import Path
import sys

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import probe


def layout(instructions):
    return [(ins.address, ins.size, ins.mnemonic) for ins in instructions]


@pytest.mark.parametrize("retail,compiled,relocs", [
    # The object's CALL operand mask covers retail's CALL opcode.
    ("90 e8 11 22 33 44 c3", "e8 00 00 00 00 90 c3", [(1, 0x14, "_call")]),
    # Same instruction start, but a MOV immediate is not a LEA displacement.
    ("8d 40 04 90 90 c3", "b8 00 00 00 00 c3", [(1, 6, "_global")]),
    # A displacement follows a SIB byte; do not assume address operands begin at +1.
    ("90 8b 84 24 11 22 33 44 c3", "8b 84 24 00 00 00 00 90 c3", [(3, 6, "_global")]),
])
def test_shifted_relocations_preserve_actual_instruction_stream(retail, compiled, relocs):
    retail, compiled = bytes.fromhex(retail), bytes.fromhex(compiled)
    rr, oo, rn, on, rb, ob, unmapped = probe.diagnostic_streams(retail, compiled, relocs)
    assert unmapped == relocs
    assert layout(rr) == layout(probe.disasm(retail)) == layout(rn)
    assert layout(oo) == layout(probe.disasm(compiled)) == layout(on)
    assert rb == retail and ob == compiled
    assert [(i.mnemonic, i.op_str) for i in rr] != [
        (i.mnemonic, i.op_str) for i in probe.disasm(probe.masked(retail, relocs))]


@pytest.mark.parametrize("retail,compiled,relocs", [
    ("e8 11 22 33 44 c3", "e8 00 00 00 00 c3", [(1, 0x14, "_call")]),
    ("8b 84 24 11 22 33 44 c3", "8b 84 24 00 00 00 00 c3", [(3, 6, "_global")]),
])
def test_corresponding_address_operands_can_be_normalized(retail, compiled, relocs):
    retail, compiled = bytes.fromhex(retail), bytes.fromhex(compiled)
    rr, oo, rn, on, rb, ob, unmapped = probe.diagnostic_streams(retail, compiled, relocs)
    assert not unmapped
    assert rb == ob
    assert layout(rr) == layout(rn)
    assert layout(oo) == layout(on)
    assert bytes(rr[0].bytes) == retail[:rr[0].size]
    assert probe.classify(rn, on, rb, ob) == "exact"


def test_literal_difference_is_retained_beside_a_valid_relocation():
    retail = bytes.fromhex("e8 11 22 33 44 b8 01 00 00 00 c3")
    compiled = bytes.fromhex("e8 00 00 00 00 b8 02 00 00 00 c3")
    _, _, rn, on, rb, ob, unmapped = probe.diagnostic_streams(retail, compiled, [(1, 0x14, "_call")])
    assert not unmapped
    assert probe.classify(rn, on, rb, ob) == "operand-change"


def test_cli_displays_real_instructions_after_shifted_call(tmp_path, monkeypatch, capsys):
    import experiment_store
    retail = bytes.fromhex("90 e8 11 22 33 44 c3")
    compiled = bytes.fromhex("e8 00 00 00 00 90 c3")
    image = tmp_path / "retail.exe"
    image.write_bytes(retail)
    monkeypatch.setattr(probe.build, "EXE", image)
    monkeypatch.setattr(probe.build, "pe_sections", lambda _: [])
    monkeypatch.setattr(probe.build, "rva_to_file_offset", lambda *_: 0)
    monkeypatch.setattr(probe.build, "read_object_symbol_bytes",
                        lambda *_: (compiled, [(1, 0x14, "_call")]))
    monkeypatch.setattr(experiment_store, "compile_cached", lambda _: (tmp_path / "test.obj", False))
    monkeypatch.setattr(experiment_store, "record_result", lambda *_: {"seen_before": 0})
    monkeypatch.setattr(sys, "argv", ["probe.py", str(tmp_path / "test.cpp"), "_f", "0x1000", "--size", "7"])
    probe.main()
    output = capsys.readouterr().out
    assert "candidate relocation-layout-drift" in output
    assert "0001 e8 11 22 33 44" in output
    assert "call 0x44332217" in output
