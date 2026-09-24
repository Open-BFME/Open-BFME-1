"""Instruction boundaries and placeholder identities must not invent contracts."""
import csv
import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import callees
import pin_consistency


def test_ledger_aliases_show_compiled_body_without_claiming_alias_identity(monkeypatch, tmp_path):
    reverse = tmp_path / "reverse"
    reverse.mkdir()
    with (reverse / "functions.csv").open("w", newline="") as fh:
        writer = csv.DictWriter(fh, fieldnames=["name", "target_rva", "notes"])
        writer.writeheader()
        writer.writerows([
            {"name": "StringBaseCopy", "target_rva": "0x00887B60", "notes": ""},
            {"name": "BuddyInfoCopy", "target_rva": "0x00887B60",
             "notes": "object-symbol=StringBaseCopy;C++ alias"},
            {"name": "GameSpyGroupRoomCopy", "target_rva": "0x00887B60",
             "notes": "object-symbol=StringBaseCopy;C++ alias"},
        ])
    monkeypatch.setattr(callees.build, "ROOT", tmp_path)

    shown = callees.ledger_names()[0x00887B60]
    assert "StringBaseCopy" in shown
    assert "object symbol" in shown
    assert "3 ledger names" in shown
    assert "GameSpyGroupRoomCopy" not in shown


def test_distinct_object_symbols_at_same_rva_are_reported_ambiguous(monkeypatch, tmp_path):
    reverse = tmp_path / "reverse"
    reverse.mkdir()
    with (reverse / "functions.csv").open("w", newline="") as fh:
        writer = csv.DictWriter(fh, fieldnames=["name", "target_rva", "notes"])
        writer.writeheader()
        writer.writerows([
            {"name": "FirstBody", "target_rva": "0x0033A580", "notes": ""},
            {"name": "SecondBody", "target_rva": "0x0033A580", "notes": ""},
        ])
    monkeypatch.setattr(callees.build, "ROOT", tmp_path)

    shown = callees.ledger_names()[0x0033A580]
    assert "AMBIGUOUS" in shown
    assert "FirstBody" not in shown and "SecondBody" not in shown


def install_body(monkeypatch, body):
    monkeypatch.setattr(callees.build, "read_target_bytes", lambda *_: body)
    monkeypatch.setattr(callees, "read", lambda *_: b"\x90")


def test_e8_inside_mov_immediate_is_not_a_call(monkeypatch):
    # mov eax,0x5e8; add al,al; ret. A raw E8 scan invents target 0x100b.
    install_body(monkeypatch, bytes.fromhex("b8 e8 05 00 00 00 c0 c3"))
    assert not callees.call_targets(0x1000, 8)


@pytest.mark.parametrize("target", [0x1800, 0x3000])
def test_real_direct_calls_preserve_signed_displacements_and_counts(monkeypatch, target):
    start = 0x2000
    body = b"\xe8" + struct.pack("<i", target - start - 5)
    body += b"\xe8" + struct.pack("<i", target - start - 10) + b"\xc3"
    install_body(monkeypatch, body)
    assert callees.call_targets(start, len(body)) == {target: 2}


@pytest.mark.parametrize("body", ["e8 01 02", "ff 15 00 30 00 00 c3"])
def test_truncated_and_indirect_calls_are_not_direct_targets(monkeypatch, body):
    raw = bytes.fromhex(body)
    install_body(monkeypatch, raw)
    assert not callees.call_targets(0x2000, len(raw))


def test_unmapped_target_is_excluded(monkeypatch):
    install_body(monkeypatch, bytes.fromhex("e8 fb 0f 00 00 c3"))
    monkeypatch.setattr(callees, "read", lambda *_: None)
    assert not callees.call_targets(0x2000, 6)


def test_placeholder_name_is_not_reported_as_a_typed_contract(monkeypatch, capsys):
    monkeypatch.setattr(callees, "ledger_names", lambda: {0x3000: "?j_00003000@@YAXXZ"})
    monkeypatch.setattr(callees, "call_targets", lambda *_: {0x3000: 1})
    monkeypatch.setattr(callees, "read", lambda *_: b"\x90" * 5)
    monkeypatch.setattr(callees, "import_calls", lambda *_: {})
    monkeypatch.setattr(callees, "decoded_extent", lambda *_: 6)
    monkeypatch.setattr(sys, "argv", ["callees.py", "0x2000", "6"])
    assert callees.main() == 0
    output = capsys.readouterr().out
    assert "0 unnamed in function ledger" in output
    assert "not ABI proof" in output
    assert "WRONG" not in output


def test_import_calls_use_pe_names_and_ignore_unknown_slots(monkeypatch):
    body = bytes.fromhex("ff 15 00 30 00 00 ff 15 00 30 00 00 ff 15 00 40 00 00 c3")
    install_body(monkeypatch, body)
    monkeypatch.setattr(pin_consistency, "import_table",
                        lambda: {0x3000: ("mss32.dll", "_AIL_open_stream@12")})
    assert callees.import_calls(0x2000, len(body)) == {
        (0x3000, "mss32.dll", "_AIL_open_stream@12"): 2}


@pytest.mark.parametrize("body", ["b8 ff 15 00 30 90 c3", "ff 15 00 30", "ff d0 c3"])
def test_import_inventory_respects_boundaries_and_absolute_operand(monkeypatch, body):
    raw = bytes.fromhex(body)
    install_body(monkeypatch, raw)
    monkeypatch.setattr(pin_consistency, "import_table", lambda: {0x3000: ("x.dll", "f")})
    assert not callees.import_calls(0x2000, len(raw))


def run_main(monkeypatch, body):
    install_body(monkeypatch, body)
    monkeypatch.setattr(callees, "ledger_names", lambda: {})
    monkeypatch.setattr(callees, "import_calls", lambda *_: {})
    monkeypatch.setattr(sys, "argv", ["callees.py", "0x2000", str(len(body))])
    return callees.main()


def test_a_fully_decoded_body_has_no_warning(monkeypatch, capsys):
    body = bytes.fromhex("e8") + struct.pack("<i", 0x100) + bytes.fromhex("c3")
    assert run_main(monkeypatch, body) == 0
    assert "INCOMPLETE" not in capsys.readouterr().out


def test_decoding_that_stops_early_is_reported(monkeypatch, capsys):
    # call; two undecodable bytes; a second call the linear decode never reaches
    body = (bytes.fromhex("e8") + struct.pack("<i", 0x100) + bytes.fromhex("0f04")
            + bytes.fromhex("e8") + struct.pack("<i", 0x200) + bytes.fromhex("c3"))
    install_body(monkeypatch, body)
    assert callees.decoded_extent(0x2000, len(body)) == 5
    assert run_main(monkeypatch, body) == 3
    output = capsys.readouterr().out
    assert "INCOMPLETE INVENTORY" in output and "+0x5 of 0xD" in output
