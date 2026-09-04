"""Candidate boundaries must be instructions, never opcode-looking operands."""
import sys
from pathlib import Path

import capstone
import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import family_scan


@pytest.mark.parametrize("hex_bytes", [
    "90 c3",                 # ret
    "90 c2 04 00",           # ret 4 (thiscall/stdcall cleanup)
    "90 e9 01 00 00 00",     # direct near tail jump
    "90 eb 01",              # direct short tail jump
    "90 ff e0",              # register tail jump
    "90 ff 60 04",           # memory tail jump with displacement
    "90 ff 25 78 56 34 12",  # import tail jump
])
def test_accepts_decoded_terminal_instruction(hex_bytes):
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    assert family_scan.ends_in_return_or_jump(bytes.fromhex(hex_bytes), md)


@pytest.mark.parametrize("hex_bytes", [
    "", "90",               # no terminal instruction
    "b8 00 00 00 c3",        # mov immediate ends in ret opcode
    "b8 00 00 ff 00",        # penultimate FF is an immediate, not a jump
    "90 75 00",              # conditional branch still has fallthrough
    "c3 0f",                 # valid return followed by truncated instruction
    "c2 04",                 # truncated ret imm16
    "90 e9 01 00",           # truncated near jump
    "90 e8 00 00 00 00",     # call is not a terminal jump
])
def test_rejects_false_or_incomplete_terminal(hex_bytes):
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    assert not family_scan.ends_in_return_or_jump(bytes.fromhex(hex_bytes), md)


@pytest.mark.parametrize("mode", ["exact", "disp", "operand", "mnemonic"])
def test_cli_exposes_ret_cleanup_family_in_every_mode(monkeypatch, capsys, mode):
    body = bytes.fromhex("8b 44 24 04 89 01 c2 04 00")
    rows = [("first", 0x1000, len(body)), ("second", 0x2000, len(body))]
    monkeypatch.setattr(family_scan, "candidates", lambda *args: iter(rows))
    monkeypatch.setattr(family_scan, "load_real_pins", lambda: set())
    monkeypatch.setattr(family_scan, "load_attempted", lambda: (set(), set()))
    monkeypatch.setattr(family_scan.build, "read_target_bytes", lambda *args: body + b"\xcc")
    monkeypatch.setattr(sys, "argv", ["family_scan.py", "--" + mode])
    family_scan.main()
    out = capsys.readouterr().out
    assert "bodies scanned: 2" in out
    assert "unattempted rows reachable: 2" in out


def test_one_bad_boundary_does_not_retire_other_shape_siblings(monkeypatch, capsys):
    body = bytes.fromhex("8b 44 24 04 89 01 c2 04 00")
    rows = [("first", 0x1000, len(body)), ("second", 0x2000, len(body)), ("third", 0x3000, len(body))]
    monkeypatch.setattr(family_scan, "candidates", lambda *args: iter(rows))
    monkeypatch.setattr(family_scan, "load_real_pins", lambda: set())
    monkeypatch.setattr(family_scan, "load_attempted", lambda: ({0x1000}, {0x1000}))
    monkeypatch.setattr(family_scan.build, "read_target_bytes", lambda *args: body + b"\xcc")
    monkeypatch.setattr(sys, "argv", ["family_scan.py", "--operand"])
    family_scan.main()
    assert "unattempted rows reachable: 2" in capsys.readouterr().out
