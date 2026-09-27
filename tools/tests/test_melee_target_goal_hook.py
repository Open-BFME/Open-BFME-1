"""Check the opt-in goal-ID replacement in a supplied, compiled 054 game image."""
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


@pytest.fixture(scope="module")
def images():
    supplied = os.environ.get("BFME_TARGET_GOAL_TEST_EXE")
    if not supplied:
        pytest.skip("supply the compiled 054 image in BFME_TARGET_GOAL_TEST_EXE")
    return PE(supplied), PE(modbuild.BASELINE)


def test_target_goal_hook_only_replaces_saved_eax_and_replays_original_load(images):
    built, original = images
    rva = 0x3DF445
    expected = bytes.fromhex("8b0d98082f01")
    assert original.read(rva, len(expected)) == expected
    patch = built.read(rva, 5)
    assert patch[0] == 0xE9
    shim = rva + 5 + struct.unpack("<i", patch[1:])[0]
    instructions = list(capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32).disasm(
        built.read(shim, 64), built.image_base + shim))
    assert [(i.mnemonic, i.op_str) for i in instructions[:6]] == [
        ("pushal", ""), ("pushfd", ""), ("cld", ""),
        ("push", "dword ptr [esp + 0x60]"), ("push", "esi"), ("push", "eax"),
    ]
    assert instructions[6].mnemonic == "call"
    assert [(i.mnemonic, i.op_str) for i in instructions[7:12]] == [
        ("add", "esp, 0xc"), ("mov", "dword ptr [esp + 0x20], eax"),
        ("popfd", ""), ("popal", ""), ("mov", "ecx, dword ptr [0x12f0898]"),
    ]
    assert instructions[12].mnemonic == "jmp"
    assert int(instructions[12].op_str, 16) == built.image_base + rva + len(expected)
    # The caller still looks up the returned ID through the native code path.
    assert built.read(rva + len(expected), 11) == original.read(rva + len(expected), 11)


def test_destination_guards_and_remaining_cell_checks_are_unchanged(images):
    built, original = images
    start, size = 0x3DF250, 648
    expected, patched = bytearray(original.read(start, size)), bytearray(built.read(start, size))
    for rva, length in ((0x3DF331, 9), (0x3DF390, 5), (0x3DF445, 6), (0x3DF4CC, 5)):
        offset = rva - start
        assert patched[offset] == 0xE9
        patched[offset:offset + length] = expected[offset:offset + length]
    assert patched == expected
