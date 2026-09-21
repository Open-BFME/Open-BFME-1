"""Relocation masks must never invent retail instructions in probe output."""
from pathlib import Path
import sys

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import probe


def layout(instructions):
    return [(ins.address, ins.size, ins.mnemonic) for ins in instructions]


def test_extent_warns_when_size_cuts_stack_cleanup():
    # The 262570 dump's old end split ADD ESP before its RET 4.
    body = bytes.fromhex("5f 5e 5b 81 c4 98 00 00 00 c2 04 00 cc cc cc")
    warning = probe.extent_warning(body, 6)
    assert "end +0x6 cuts decoded instruction +0x3: add esp, 0x98" in warning
    assert "size was NOT adjusted" in warning


@pytest.mark.parametrize("body,size", [
    ("c2 04 00 cc cc cc", 3),  # complete RET 4
    ("e9 00 00 00 00 cc cc cc", 5),  # complete tail jump
    ("b8 c3 cc cc cc c3", 5),  # RET/padding bytes inside an immediate
    ("81 c4 98", 3),  # insufficient lookahead is not positive evidence
])
def test_extent_does_not_infer_boundaries_from_opcodes(body, size):
    assert probe.extent_warning(bytes.fromhex(body), size) is None


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


BODY = bytes.fromhex("8b 44 24 04 85 c0 74 03 c2 04 00 33 c0 c2 04 00")


def test_short_extent_hint_names_a_size_that_stops_before_the_end():
    hint = probe.short_extent_hint(BODY + bytes.fromhex("cc cc cc cc"), 13, BODY, [])
    assert "size 13 stops 3 byte(s) before the end" in hint
    assert "--replace-rva" in hint


def test_short_extent_hint_ignores_relocation_slots():
    compiled = bytes.fromhex("e8 00 00 00 00 c2 04 00")
    retail = bytes.fromhex("e8 11 22 33 44 c2 04 00")
    assert probe.short_extent_hint(retail, 5, compiled, [(1, 0x14, "_call")])


@pytest.mark.parametrize("following,size", [
    (BODY, 16),  # the size already covers the body
    (BODY[:13] + bytes.fromhex("c2 08 00"), 13),  # the tail differs from retail
    (BODY[:14], 13),  # retail ends before the compiled body does
])
def test_short_extent_hint_stays_silent_without_full_equality(following, size):
    assert probe.short_extent_hint(following, size, BODY, []) is None
