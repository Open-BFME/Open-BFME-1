"""A single-body scaffold conversion is a two-ledger transaction.

functions.csv uses git's union merge driver, so deleting its generated row is
not durable by itself: a branch forked before the conversion can silently put
the row back. add_match --replace-rva must tombstone that exact synthetic
identity, and a failed byte gate must restore the tombstone with everything
else it touched.
"""
import csv
import io
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import add_match


HEADER = "name,export_rva,target_rva,target_size,source,status,notes"
DUMP = (
    "?d_00abcd00@@YAXXZ,,0x00ABCD00,32,Code/gen_asm/d_00abcd00.asm,matched,"
    "gen-dump;ghidra=FUN_00eacd00"
)
REAL = "?realBody@Thing@@QAEXXZ"
SOURCE_REL = "Code/GameEngine/Source/Common/Thing.cpp"


def arrange(tmp_path, monkeypatch, *, gate, target_rva="0x00ABCD00", size="32",
            extra_args=()):
    reverse = tmp_path / "reverse"
    reverse.mkdir()
    source = tmp_path / SOURCE_REL
    source.parent.mkdir(parents=True)
    source.write_bytes(
        f"// {REAL} present-unmatched\r\nvoid realBody() {{}}\r\n".encode("utf-8"))
    functions = reverse / "functions.csv"
    functions.write_bytes(f"{HEADER}\r\n{DUMP}\r\n".encode("utf-8"))
    deleted = reverse / "deleted_rows.csv"
    deleted.write_bytes(
        b'name,target_rva,reason\n?older@@YAXXZ,0x00123456,"existing, quoted reason"\n')
    build_sh = tmp_path / "build.sh"
    build_sh.write_text("#!/bin/sh\nexit 0\n", encoding="utf-8")
    build_sh.chmod(0o755)
    monkeypatch.setattr(
        add_match.subprocess, "run",
        lambda command, *, cwd, env: SimpleNamespace(returncode=gate))
    monkeypatch.setattr(sys, "argv", [
        "add_match.py", REAL, target_rva, size, SOURCE_REL,
        "--replace-rva", "0x00ABCD00", "--root", str(tmp_path),
        *extra_args,
    ])
    return functions, deleted, source


def test_replace_rva_tombstones_the_superseded_scaffold(tmp_path, monkeypatch):
    functions, deleted, _source = arrange(tmp_path, monkeypatch, gate=0)

    add_match.main()

    ledger = functions.read_text(encoding="utf-8")
    assert "?d_00abcd00@@YAXXZ" not in ledger
    assert REAL in ledger
    rows = list(csv.reader(io.StringIO(deleted.read_text(encoding="utf-8"))))
    tombstone = rows[-1]
    assert tombstone[:2] == ["?d_00abcd00@@YAXXZ", "0x00ABCD00"]
    assert REAL in tombstone[2]
    assert SOURCE_REL in tombstone[2]
    assert "same 32-byte range" in tombstone[2]


def test_red_gate_restores_both_ledgers_and_source_exactly(tmp_path, monkeypatch):
    functions, deleted, source = arrange(tmp_path, monkeypatch, gate=1)
    before = (functions.read_bytes(), deleted.read_bytes(), source.read_bytes())

    with pytest.raises(SystemExit):
        add_match.main()

    assert (functions.read_bytes(), deleted.read_bytes(), source.read_bytes()) == before


@pytest.mark.parametrize("target_rva,size", [
    ("0x00ABCD10", "32"),
    ("0x00ABCD00", "47"),
])
def test_range_mismatch_without_boundary_evidence_changes_nothing(
        tmp_path, monkeypatch, target_rva, size):
    functions, deleted, source = arrange(
        tmp_path, monkeypatch, gate=0, target_rva=target_rva, size=size)
    before = (functions.read_bytes(), deleted.read_bytes(), source.read_bytes())

    with pytest.raises(SystemExit):
        add_match.main()

    assert (functions.read_bytes(), deleted.read_bytes(), source.read_bytes()) == before


def test_proven_bad_extent_gets_an_explicit_correction_tombstone(tmp_path, monkeypatch):
    functions, deleted, _source = arrange(
        tmp_path, monkeypatch, gate=0, size="47",
        extra_args=("--boundary-evidence", "old extent ended mid-call; padding follows ret"))

    add_match.main()

    ledger = functions.read_text(encoding="utf-8")
    assert f",0x00ABCD00,47,{SOURCE_REL},matched," in ledger
    tombstone = list(csv.reader(io.StringIO(
        deleted.read_text(encoding="utf-8"))))[-1]
    assert "32-byte extent" in tombstone[2]
    assert "corrected 47-byte range" in tombstone[2]
    assert "ended mid-call" in tombstone[2]


def test_no_verify_tombstone_does_not_claim_byte_verification(tmp_path, monkeypatch):
    _functions, deleted, _source = arrange(
        tmp_path, monkeypatch, gate=0, extra_args=("--no-verify",))

    add_match.main()

    reason = list(csv.reader(io.StringIO(
        deleted.read_text(encoding="utf-8"))))[-1][2]
    assert "verification-deferred" in reason
    assert "byte-verified" not in reason


@pytest.mark.parametrize("new_rva,expect_tombstone", [
    ("0x00ABCD00", False),
    ("0x00ABCE00", True),
])
def test_replace_existing_tombstones_only_when_the_identity_key_moves(
        tmp_path, monkeypatch, new_rva, expect_tombstone):
    reverse = tmp_path / "reverse"
    reverse.mkdir()
    old_source = tmp_path / "Code" / "Old.cpp"
    old_source.parent.mkdir()
    old_source.write_text("void oldBody() {}\n", encoding="utf-8")
    new_source = tmp_path / "Code" / "New.cpp"
    new_source.write_text("void newBody() {}\n", encoding="utf-8")
    functions = reverse / "functions.csv"
    functions.write_bytes(
        (f"{HEADER}\r\n{REAL},,0x00ABCD00,32,Code/Old.cpp,matched,old claim\r\n")
        .encode("utf-8"))
    deleted = reverse / "deleted_rows.csv"
    deleted.write_bytes(b"name,target_rva,reason\n")
    build_sh = tmp_path / "build.sh"
    build_sh.write_text("#!/bin/sh\nexit 0\n", encoding="utf-8")
    build_sh.chmod(0o755)
    monkeypatch.setattr(
        add_match.subprocess, "run",
        lambda command, *, cwd, env: SimpleNamespace(returncode=0))
    monkeypatch.setattr(sys, "argv", [
        "add_match.py", REAL, new_rva, "32", "Code/New.cpp",
        "--replace-existing", "--root", str(tmp_path),
    ])

    add_match.main()

    tombstones = list(csv.reader(io.StringIO(deleted.read_text(encoding="utf-8"))))[1:]
    assert bool(tombstones) is expect_tombstone
    if expect_tombstone:
        assert tombstones[0][:2] == [REAL, "0x00ABCD00"]
        assert "0x00ABCE00/32B" in tombstones[0][2]
