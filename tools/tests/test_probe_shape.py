"""probe's shape score: register choice and constants do not count as structure."""
import sys
from pathlib import Path
from types import SimpleNamespace

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import probe  # noqa: E402


def ins(address, mnemonic, op_str):
    return SimpleNamespace(address=address, mnemonic=mnemonic, op_str=op_str)


def test_register_and_slot_choice_is_not_structure():
    retail = [ins(0, "mov", "ebx, dword ptr [esp + 0x18]"), ins(4, "call", "0x401000"), ins(9, "ret", "")]
    ours = [ins(0, "mov", "ebp, dword ptr [esp + 0x14]"), ins(4, "call", "0x402000"), ins(9, "ret", "")]
    score, opcodes = probe.shape_compare(retail, ours)
    assert score == 1.0
    assert [op[0] for op in opcodes] == ["equal"]


def test_a_missing_call_is_structure():
    retail = [ins(0, "push", "esi"), ins(1, "call", "0x401000"), ins(6, "ret", "")]
    ours = [ins(0, "push", "esi"), ins(1, "ret", "")]
    score, opcodes = probe.shape_compare(retail, ours)
    assert score < 1.0
    assert any(op[0] != "equal" for op in opcodes)


def test_esp_is_not_normalised_away():
    assert probe.shape_text(ins(0, "add", "esp, 8")) == "add esp, N"
    assert probe.shape_text(ins(0, "add", "ecx, 8")) == "add R, N"
