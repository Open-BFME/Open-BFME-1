"""A drifted COFF offset must never become a copyable retail callee pin."""
from pathlib import Path
import sys

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import decode_calls


@pytest.mark.parametrize("opcode,offset,kind", [
    ("e8", 1, "call"), ("e9", 1, "jmp"),
    ("0f85", 2, "jne"), ("0f8e", 2, "jle"),
])
def test_real_branches_align_despite_different_displacements(opcode, offset, kind):
    compiled = bytes.fromhex(opcode + "00000000c3")
    retail = bytes.fromhex(opcode + "f0ffffffc3")
    assert decode_calls.aligned_rel32_site(
        offset, decode_calls.rel32_operands(compiled),
        decode_calls.rel32_operands(retail)) == (kind, None)


@pytest.mark.parametrize("body", [
    "b8e8112233c3",       # E8 inside MOV EAX, imm32
    "b8e9112233c3",       # E9 inside MOV EAX, imm32
    "b80f851122c3",       # 0F 85 inside MOV's immediate
    "9a123456783300c3",   # far absolute CALL, not rel32
    "ea123456783300c3",   # far absolute JMP, not rel32
    "ff1500104000c3",     # indirect CALL through absolute memory
    "ffe0",              # register JMP
    "e8010203",          # truncated relative operand
    "7502c3",            # short branch, not REL32
])
def test_operand_bytes_and_non_rel32_branches_are_not_sites(body):
    assert decode_calls.rel32_operands(bytes.fromhex(body)) == {}


@pytest.mark.parametrize("compiled,retail,offset,why", [
    ("e800000000c3", "b800000000c3", 1, "retail offset"),
    ("b800000000c3", "e800000000c3", 1, "object relocation"),
    ("e800000000c3", "e900000000c3", 1, "kinds differ"),
    ("90e800000000c3", "0f8500000000c3", 2, "boundaries or kinds"),
    ("e800000000c3", "e800000000c3", -1, "object relocation"),
    ("e800000000c3", "e800000000c3", 20, "object relocation"),
])
def test_layout_mismatches_are_explained(compiled, retail, offset, why):
    kind, reason = decode_calls.aligned_rel32_site(
        offset, decode_calls.rel32_operands(bytes.fromhex(compiled)),
        decode_calls.rel32_operands(bytes.fromhex(retail)))
    assert kind is None
    assert why in reason


def run_main(monkeypatch, tmp_path, compiled, retail, relocs):
    source = tmp_path / "game" / "foo.cpp"
    source.parent.mkdir()
    source.write_text("void foo() {}\n")
    monkeypatch.setattr(decode_calls.build, "ROOT", tmp_path)
    monkeypatch.setattr(decode_calls.build, "obj_path", lambda _: tmp_path / "foo.obj")
    monkeypatch.setattr(decode_calls.build, "compile_source", lambda *args: None)
    monkeypatch.setattr(decode_calls.build, "load_all_function_rows", lambda: [{
        "name": "?foo@@YAXXZ", "target_rva": "0x1000",
        "target_size": str(len(retail)), "source": "game/foo.cpp", "status": "matched",
    }])
    monkeypatch.setattr(decode_calls.build, "load_symbol_map", lambda: {})
    monkeypatch.setattr(decode_calls.build, "build_call_thunks", lambda: {})
    monkeypatch.setattr(decode_calls.build, "read_object_symbol_bytes",
                        lambda *args: (compiled, relocs))
    monkeypatch.setattr(decode_calls.build, "read_target_bytes", lambda *args: retail)
    monkeypatch.setattr(decode_calls, "load_ghidra", lambda _: ({}, []))
    monkeypatch.setattr(decode_calls, "load_exports", lambda _: {})
    monkeypatch.setattr(sys, "argv", ["decode_calls.py", "game/foo.cpp"])
    decode_calls.main()


def test_main_suppresses_bogus_pin_but_preserves_aligned_call(
        monkeypatch, tmp_path, capsys):
    # The first object CALL became retail MOV; the second still lines up.
    compiled = bytes.fromhex("e800000000e800000000c3")
    retail = bytes.fromhex("b811223344e8f0ffffffc3")
    with pytest.raises(SystemExit) as error:
        run_main(monkeypatch, tmp_path, compiled, retail, [
            (1, 0x14, "?bogus@@YAXXZ"), (6, 0x14, "?valid@@YAXXZ"),
        ])
    assert error.value.code == 1
    output = capsys.readouterr().out
    assert "NO PIN CANDIDATE" in output
    assert "pin: ?bogus" not in output
    assert "pin: ?valid@@YAXXZ,0x00000FFA" in output
    assert "1 unaligned site(s) suppressed" in output
    assert "byte match alone does not prove" in output


def test_main_reports_relocation_beyond_retail_extent(monkeypatch, tmp_path, capsys):
    with pytest.raises(SystemExit) as error:
        run_main(monkeypatch, tmp_path, bytes.fromhex("90e800000000c3"), b"\xc3",
                 [(2, 0x14, "?beyond@@YAXXZ")])
    assert error.value.code == 1
    output = capsys.readouterr().out
    assert "1 REL32 site(s), 1 unresolved" in output
    assert "pin:" not in output
    assert "retail offset" in output


def test_main_aligned_tail_call_succeeds(monkeypatch, tmp_path, capsys):
    run_main(monkeypatch, tmp_path, bytes.fromhex("e900000000"),
             bytes.fromhex("e910000000"), [(1, 0x14, "?tail@@YAXXZ")])
    assert "jmp -> 0x00001015" in capsys.readouterr().out
