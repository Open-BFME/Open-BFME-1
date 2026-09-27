"""Detour ABI/replay checks only; these do not claim a gameplay result."""
import os
import shutil
import struct
import subprocess
import sys
import tempfile
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
capstone = pytest.importorskip("capstone")
import modbuild
from cave import PE

pytestmark = pytest.mark.skipif(
    not modbuild.BASELINE.exists() or shutil.which("wine") is None,
    reason="retail baseline and Wine required")


@pytest.fixture(scope="module")
def built():
    supplied = os.environ.get("BFME_MELEEPROBE_TEST_EXE")
    if supplied:
        yield PE(supplied)
        return
    with tempfile.TemporaryDirectory() as tmp:
        out = Path(tmp) / "meleeprobe.exe"
        result = subprocess.run(
            [sys.executable, str(ROOT / "tools/modbuild.py"), "--only", "052-meleeprobe", "-o", str(out)],
            cwd=ROOT, capture_output=True, text=True)
        assert result.returncode == 0, result.stdout + result.stderr
        yield PE(out)


def test_instrument_is_unshipped_and_shares_the_four_fix_sites():
    assert "052-meleeprobe" not in modbuild.FEATURES
    assert "053-melee-retry" not in modbuild.FEATURES
    assert modbuild.UNSHIPPED["053-melee-retry"][0] is modbuild.build_meleeprobe
    assert modbuild.UNSHIPPED["052-meleeprobe"][0] is modbuild.build_meleeprobe
    hooks = {rva: (entry, args) for rva, entry, args, _ in modbuild.MELEEPROBE_HOOKS}
    assert hooks[0x175979] == ("meleeprobe_enter_before", ("ebp", "esi", "ebx"))
    assert hooks[0x17597E] == ("meleeprobe_enter_after", ("eax",))
    assert hooks[0x175AF0] == ("meleeprobe_update_before", ("ebx", "edi", "ebp"))
    assert hooks[0x175AF5] == ("meleeprobe_update_after", ("eax",))
    assert hooks[0x175A0F] == ("meleeprobe_begin", ("ebp", "esi", "ebx"))
    assert hooks[0x175B34] == ("meleeprobe_update_target", ("ebx", "edi", "ebp"))
    assert hooks[0x175B26] == ("meleeprobe_not_ready", ("ebx", "edi", "ebp", "esi"))
    assert hooks[0x175B16] == ("meleeprobe_ready", ("ebx", "edi", "ebp", "esi"))
    assert hooks[0x238D10] == ("meleeprobe_plan_enter", ("stack:0", "stack:2", "stack:5", "stack:6"))
    assert hooks[0x244455] == ("meleeprobe_plan_complete", ("eax", "edi", "esi"))
    assert hooks[0x3DF331] == ("meleeprobe_cell_begin", ("ebx", "edx"))
    assert hooks[0x3DF390] == ("meleeprobe_cell_data", ("esi",))
    assert hooks[0x667238] == hooks[0x6671A1] == ("meleeprobe_chat", ("esi", "eax", "ebp"))
    assert hooks[0x277780] == ("meleeprobe_command", ("ecx", "stack:0"))


def test_probe_refuses_a_previously_patched_fix_site():
    pe = PE(modbuild.BASELINE)
    pe.write(0x175979, b"\xe9\0\0\0\0")
    with pytest.raises(SystemExit, match="cannot stack"):
        modbuild.build_meleeprobe(pe, ROOT / "mods/features/052-meleeprobe")


@pytest.mark.parametrize("hook", modbuild.MELEEPROBE_HOOKS)
def test_each_detour_preserves_registers_replays_instructions_and_resumes(built, hook):
    rva, _, args, expected_hex = hook
    original = PE(modbuild.BASELINE)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    expected = bytes.fromhex(expected_hex)
    assert original.read(rva, len(expected)) == expected
    patched = built.read(rva, 5)
    assert patched[0] == 0xE9
    shim = rva + 5 + struct.unpack("<i", patched[1:])[0]
    instructions = list(md.disasm(built.read(shim, 96), built.image_base + shim))
    assert [ins.mnemonic for ins in instructions[:3]] == ["pushal", "pushfd", "cld"]
    for pushed, (ins, register) in enumerate(zip(instructions[3:], reversed(args))):
        if register.startswith("stack:"):
            offset = 36 + pushed * 4 + 4 + int(register.split(":")[1]) * 4
            register = f"dword ptr [esp + {offset:#x}]"
        assert (ins.mnemonic, ins.op_str) == ("push", register)
    call_index = 3 + len(args)
    assert instructions[call_index].mnemonic == "call"
    assert [(i.mnemonic, i.op_str) for i in instructions[call_index + 1:call_index + 4]] == [
        ("add", "esp, " + (hex(len(args) * 4) if len(args) * 4 >= 10 else str(len(args) * 4))),
        ("popfd", ""), ("popal", "")]
    stolen = list(md.disasm(expected, original.image_base + rva))
    replay = instructions[call_index + 4:call_index + 4 + len(stolen)]
    assert [(i.mnemonic, i.op_str) for i in replay] == [(i.mnemonic, i.op_str) for i in stolen]
    back = instructions[call_index + 4 + len(stolen)]
    assert back.mnemonic == "jmp"
    assert int(back.op_str, 16) == original.image_base + rva + len(expected)


def test_predicate_restoration_leaves_retail_test_and_branch(built):
    original = PE(modbuild.BASELINE)
    for rva in (0x17597E, 0x175AF5):
        assert original.read(rva, 5) == bytes.fromhex("83c40884c0")
        assert built.read(rva + 5, 2) == original.read(rva + 5, 2)
        assert built.read(rva + 5, 1) == b"\x74"
