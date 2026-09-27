"""Check the focused AC mod's attack-view and melee predicate detours."""
import os
import struct
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
capstone = pytest.importorskip("capstone")
from cave import PE
import modbuild


def test_focused_ac_image_preserves_view_search_and_melee_calls():
    image = os.environ.get("BFME_AC_ATTACK_VIEW_TEST_EXE")
    if not image:
        pytest.skip("supply BFME_AC_ATTACK_VIEW_TEST_EXE")
    built, retail = PE(image), PE(modbuild.BASELINE)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)

    for rva, _, args in modbuild.checked_structure_melee_hooks(retail):
        assert built.read(rva, 1) == b"\xe9"
        patch = built.read(rva, 5)
        shim = rva + 5 + struct.unpack("<i", patch[1:])[0]
        instructions = list(md.disasm(built.read(shim, 96), built.image_base + shim))
        assert [ins.mnemonic for ins in instructions[:3]] == ["pushal", "pushfd", "cld"]
        assert [ins.op_str for ins in instructions[3:3 + len(args)]] == list(reversed(args))

    for rva, _, args, expected_hex in modbuild.TARGET_VIEW_GOAL_HOOKS:
        expected = bytes.fromhex(expected_hex)
        assert retail.read(rva, len(expected)) == expected
        patch = built.read(rva, 5)
        assert patch[0] == 0xE9
        shim = rva + 5 + struct.unpack("<i", patch[1:])[0]
        instructions = list(md.disasm(built.read(shim, 64), built.image_base + shim))
        assert [i.mnemonic for i in instructions[:3]] == ["pushal", "pushfd", "cld"]
        assert instructions[3].op_str.startswith("dword ptr [esp +")
        assert [i.op_str for i in instructions[4:6]] == ["eax", "ecx"]
        assert [(i.mnemonic, i.op_str) for i in instructions[7:11]] == [
            ("add", "esp, 0xc"), ("mov", "dword ptr [esp + 0x1c], eax"),
            ("popfd", ""), ("popal", "")]
        assert instructions[11].op_str == "ecx, ecx"
        assert int(instructions[12].op_str, 16) == (
            built.image_base + rva + 4 + int.from_bytes(expected[3:4], "little", signed=True))
        assert int(instructions[14].op_str, 16) == built.image_base + rva + len(expected)
