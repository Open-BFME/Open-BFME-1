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


def test_acquisition_hooks_preserve_selection_and_dispatch(images):
    built, original = images
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    for rva, _, args, expected_hex in (
        modbuild.TARGET_ACQUIRE_HOOKS + modbuild.TARGET_CANDIDATE_HOOKS
        + modbuild.TARGET_FIRST_HOOKS
    ):
        expected = bytes.fromhex(expected_hex)
        assert original.read(rva, len(expected)) == expected
        patch = built.read(rva, 5)
        assert patch[0] == 0xE9
        shim = rva + 5 + struct.unpack("<i", patch[1:])[0]
        instructions = list(md.disasm(built.read(shim, 96), built.image_base + shim))
        assert [i.mnemonic for i in instructions[:3]] == ["pushal", "pushfd", "cld"]
        for pushed, (ins, arg) in enumerate(zip(instructions[3:], reversed(args))):
            if arg.startswith("stack_offset:"):
                offset = 36 + 4 * pushed + int(arg.split(":", 1)[1], 0)
                arg = f"dword ptr [esp + {offset:#x}]"
            assert (ins.mnemonic, ins.op_str) == ("push", arg)
        call = 3 + len(args)
        assert instructions[call].mnemonic == "call"
        assert [i.mnemonic for i in instructions[call + 1:call + 4]] == [
            "add", "popfd", "popal"]
        stolen = list(md.disasm(expected, original.image_base + rva))
        replay = instructions[call + 4:call + 4 + len(stolen)]
        assert [(i.mnemonic, i.op_str) for i in replay] == [
            (i.mnemonic, i.op_str) for i in stolen]
        back = instructions[call + 4 + len(stolen)]
        assert back.mnemonic == "jmp"
        assert int(back.op_str, 16) == original.image_base + rva + len(expected)


def test_acquisition_hooks_do_not_erase_native_branch_targets(images):
    _, original = images
    start, size = 0x1CBDC0, 924
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    spans = [(original.image_base + rva, original.image_base + rva + len(bytes.fromhex(expected)))
             for rva, _, _, expected in modbuild.TARGET_ACQUIRE_HOOKS
             + modbuild.TARGET_CANDIDATE_HOOKS + modbuild.TARGET_FIRST_HOOKS
             if start <= rva < start + size]
    for ins in md.disasm(original.read(start, size), original.image_base + start):
        if not ins.group(capstone.CS_GRP_JUMP):
            continue
        if not ins.operands or ins.operands[0].type != capstone.x86_const.X86_OP_IMM:
            continue
        destination = ins.operands[0].imm
        for hook_start, hook_end in spans:
            assert not hook_start < destination < hook_end, (
                f"native branch at {ins.address:#x} enters hook {hook_start:#x} "
                f"at {destination:#x}")


def test_attack_view_goal_hooks_restore_ecx_and_replay_native_branches(images):
    built, original = images
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    for rva, _, args, expected_hex in modbuild.TARGET_VIEW_GOAL_HOOKS:
        expected = bytes.fromhex(expected_hex)
        assert original.read(rva, len(expected)) == expected
        patch = built.read(rva, 5)
        assert patch[0] == 0xE9
        shim = rva + 5 + struct.unpack("<i", patch[1:])[0]
        instructions = list(md.disasm(built.read(shim, 96), built.image_base + shim))
        assert [i.mnemonic for i in instructions[:3]] == ["pushal", "pushfd", "cld"]
        assert instructions[3].op_str.startswith("dword ptr [esp +")
        assert [i.op_str for i in instructions[4:6]] == ["eax", "ecx"]
        assert instructions[6].mnemonic == "call"
        assert [(i.mnemonic, i.op_str) for i in instructions[7:11]] == [
            ("add", "esp, 0xc"), ("mov", "dword ptr [esp + 0x1c], eax"),
            ("popfd", ""), ("popal", "")]
        assert [(i.mnemonic, i.op_str) for i in instructions[11:13]] == [
            ("test", "ecx, ecx"),
            ("jne" if rva in (0x3E4BE5, 0x3E4C5B) else "je",
             hex(built.image_base + rva + 4 + int.from_bytes(expected[3:4], "little", signed=True)))
        ]
        assert instructions[14].mnemonic == "jmp"
        assert int(instructions[14].op_str, 16) == built.image_base + rva + len(expected)


def test_attack_view_hooks_do_not_erase_native_branch_targets(images):
    _, original = images
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    spans = [(original.image_base + rva, original.image_base + rva + len(bytes.fromhex(expected)))
             for rva, _, _, expected in modbuild.TARGET_VIEW_GOAL_HOOKS]
    for start, size in ((0x3E4330, 672), (0x3E49F0, 753)):
        for ins in md.disasm(original.read(start, size), original.image_base + start):
            if not ins.group(capstone.CS_GRP_JUMP):
                continue
            if not ins.operands or ins.operands[0].type != capstone.x86_const.X86_OP_IMM:
                continue
            destination = ins.operands[0].imm
            for hook_start, hook_end in spans:
                assert not hook_start < destination < hook_end, (
                    f"native branch at {ins.address:#x} enters hook {hook_start:#x} "
                    f"at {destination:#x}")
