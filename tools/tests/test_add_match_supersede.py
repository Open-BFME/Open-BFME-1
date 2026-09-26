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
    "?d_00abcd00@@YAXXZ,,0x00ABCD00,32,game/gen_asm/d_00abcd00.asm,matched,"
    "gen-dump;ghidra=FUN_00eacd00"
)
REAL = "?realBody@Thing@@QAEXXZ"
SOURCE_REL = "game/GameEngine/Source/Common/Thing.cpp"


def arrange(tmp_path, monkeypatch, *, gate, target_rva="0x00ABCD00", size="32",
            extra_args=(), scaffold=DUMP):
    reverse = tmp_path / "targets/game/reverse"
    reverse.mkdir(parents=True)
    source = tmp_path / SOURCE_REL
    source.parent.mkdir(parents=True)
    source.write_bytes(
        f"// {REAL} present-unmatched\r\nvoid realBody() {{}}\r\n".encode("utf-8"))
    functions = reverse / "functions.csv"
    functions.write_bytes(f"{HEADER}\r\n{scaffold}\r\n".encode("utf-8"))
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


@pytest.mark.parametrize("gate", [0, 1])
def test_tgrid_replacement_keeps_transaction_and_tombstone(tmp_path, monkeypatch, gate):
    scaffold = DUMP.replace("game/gen_asm/d_00abcd00.asm", "game/gen_small/tgrid_109.cpp").replace(
        "gen-dump;ghidra=FUN_00eacd00", "gen-tgrid;template=vec_p16cd")
    functions, deleted, source = arrange(tmp_path, monkeypatch, gate=gate, scaffold=scaffold)
    before = functions.read_bytes(), deleted.read_bytes(), source.read_bytes()
    if gate:
        with pytest.raises(SystemExit):
            add_match.main()
        assert (functions.read_bytes(), deleted.read_bytes(), source.read_bytes()) == before
    else:
        add_match.main()
        assert REAL in functions.read_text()
        tombstone = list(csv.reader(io.StringIO(deleted.read_text())))[-1]
        assert "gen-tgrid scaffold placeholder" in tombstone[2]
        assert "same 32-byte range" in tombstone[2]


@pytest.mark.parametrize("gate", [0, 1])
@pytest.mark.parametrize("source_path", ["game/gen_small/fam_001.cpp",
                                        "game/gen_small/fun_002.cpp"])
def test_gen_shim_replacement_keeps_transaction_and_tombstone(
        tmp_path, monkeypatch, gate, source_path):
    scaffold = DUMP.replace("game/gen_asm/d_00abcd00.asm", source_path).replace(
        "gen-dump;ghidra=FUN_00eacd00", "gen-shim;family=f265_b7a8aa")
    functions, deleted, source = arrange(tmp_path, monkeypatch, gate=gate, scaffold=scaffold)
    before = functions.read_bytes(), deleted.read_bytes(), source.read_bytes()
    if gate:
        with pytest.raises(SystemExit):
            add_match.main()
        assert (functions.read_bytes(), deleted.read_bytes(), source.read_bytes()) == before
    else:
        add_match.main()
        assert REAL in functions.read_text()
        tombstone = list(csv.reader(io.StringIO(deleted.read_text())))[-1]
        assert "gen-shim scaffold placeholder" in tombstone[2]
        assert "same 32-byte range" in tombstone[2]


@pytest.mark.parametrize("gate", [0, 1])
def test_real_identity_correction_requires_proof_and_is_transactional(
        tmp_path, monkeypatch, gate):
    old_name = "?apply@Rva00ABCD00@@QAEXXZ"
    old = DUMP.replace("?d_00abcd00@@YAXXZ", old_name).replace(
        "game/gen_asm/d_00abcd00.asm", "game/GameEngine/Old.cpp").replace(
        "gen-dump;ghidra=FUN_00eacd00", "authored")
    proof_rel = "targets/game/reverse/identity_evidence/0x00abcd00.md"
    functions, deleted, source = arrange(
        tmp_path, monkeypatch, gate=gate, scaffold=old,
        extra_args=("--correct-identity", old_name,
                    "--identity-evidence", proof_rel))
    proof = tmp_path / proof_rel
    proof.parent.mkdir(parents=True)
    proof.write_text("Matched caller and vtable prove the constructor.\n")
    before = functions.read_bytes(), deleted.read_bytes(), source.read_bytes()
    if gate:
        with pytest.raises(SystemExit):
            add_match.main()
        assert (functions.read_bytes(), deleted.read_bytes(), source.read_bytes()) == before
    else:
        add_match.main()
        ledger = functions.read_text()
        assert old_name not in ledger
        assert "identity-correction=" + proof_rel in ledger
        tombstone = list(csv.reader(io.StringIO(deleted.read_text())))[-1]
        assert tombstone[0] == old_name
        assert REAL in tombstone[2]


def test_real_identity_correction_rejects_wrong_old_name(tmp_path, monkeypatch):
    old = DUMP.replace("game/gen_asm/d_00abcd00.asm", "game/GameEngine/Old.cpp").replace(
        "gen-dump;ghidra=FUN_00eacd00", "authored")
    proof_rel = "targets/game/reverse/identity_evidence/0x00abcd00.md"
    functions, deleted, source = arrange(
        tmp_path, monkeypatch, gate=0, scaffold=old,
        extra_args=("--correct-identity", "?wrong@@YAXXZ",
                    "--identity-evidence", proof_rel))
    proof = tmp_path / proof_rel
    proof.parent.mkdir(parents=True)
    proof.write_text("Evidence.\n")
    before = functions.read_bytes(), deleted.read_bytes(), source.read_bytes()
    with pytest.raises(SystemExit):
        add_match.main()
    assert (functions.read_bytes(), deleted.read_bytes(), source.read_bytes()) == before


def test_real_identity_correction_rejects_missing_evidence(tmp_path, monkeypatch):
    old_name = "?apply@Rva00ABCD00@@QAEXXZ"
    old = DUMP.replace("?d_00abcd00@@YAXXZ", old_name).replace(
        "game/gen_asm/d_00abcd00.asm", "game/GameEngine/Old.cpp").replace(
        "gen-dump;ghidra=FUN_00eacd00", "authored")
    functions, deleted, source = arrange(
        tmp_path, monkeypatch, gate=0, scaffold=old,
        extra_args=("--correct-identity", old_name,
                    "--identity-evidence", "targets/game/reverse/identity_evidence/missing.md"))
    before = functions.read_bytes(), deleted.read_bytes(), source.read_bytes()
    with pytest.raises(SystemExit):
        add_match.main()
    assert (functions.read_bytes(), deleted.read_bytes(), source.read_bytes()) == before


@pytest.mark.parametrize("notes,path", [
    ("gen-tgrid;template=vec_p16cd", "game/Real.cpp"),
    ("gen-tgrid-other", "game/gen_small/tgrid_109.cpp"),
    ("gen-uw;parent=0x00123456", "game/gen_small/uw_gen_001.cpp"),
    ("authored", "game/gen_small/tgrid_109.cpp"),
    ("gen-shim;family=f265_b7a8aa", "game/Real.cpp"),
    ("gen-shim-other", "game/gen_small/fam_001.cpp"),
    ("gen-alias;family=f265_b7a8aa", "game/gen_small/fam_001.cpp"),
    ("gen-alias;object-symbol=?m@Gen_00383090@@QAEHXZ", "game/gen_small/fun_002.cpp"),
])
def test_tgrid_support_does_not_admit_real_or_unwind_claims(
        tmp_path, monkeypatch, notes, path):
    scaffold = DUMP.replace("game/gen_asm/d_00abcd00.asm", path).replace(
        "gen-dump;ghidra=FUN_00eacd00", notes)
    functions, deleted, source = arrange(tmp_path, monkeypatch, gate=0, scaffold=scaffold)
    before = functions.read_bytes(), deleted.read_bytes(), source.read_bytes()
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
    reverse = tmp_path / "targets/game/reverse"
    reverse.mkdir(parents=True)
    old_source = tmp_path / "game" / "Old.cpp"
    old_source.parent.mkdir()
    old_source.write_text("void oldBody() {}\n", encoding="utf-8")
    new_source = tmp_path / "game" / "New.cpp"
    new_source.write_text("void newBody() {}\n", encoding="utf-8")
    functions = reverse / "functions.csv"
    functions.write_bytes(
        (f"{HEADER}\r\n{REAL},,0x00ABCD00,32,game/Old.cpp,matched,old claim\r\n")
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
        "add_match.py", REAL, new_rva, "32", "game/New.cpp",
        "--replace-existing", "--root", str(tmp_path),
    ])

    add_match.main()

    tombstones = list(csv.reader(io.StringIO(deleted.read_text(encoding="utf-8"))))[1:]
    assert bool(tombstones) is expect_tombstone
    if expect_tombstone:
        assert tombstones[0][:2] == [REAL, "0x00ABCD00"]
        assert "0x00ABCE00/32B" in tombstones[0][2]


def test_replace_existing_completes_a_truncated_lift_name(tmp_path, monkeypatch):
    # 36 named __emit lifts carry decorations like ?init@ShellGameLoadScreen@@;
    # the converter passes the full mangled name and must still find the row.
    lift = ("?realBody@Thing@@,,0x00ABCD00,32,game/GameEngine/Source/Common/ThingThunk.cpp,"
            "matched,object-symbol=_bfme_Thing_realBody")
    functions, deleted, _source = arrange(tmp_path, monkeypatch, gate=0, scaffold=lift)
    monkeypatch.setattr(sys, "argv", [
        "add_match.py", REAL, "0x00ABCD00", "32", SOURCE_REL,
        "--replace-existing", "--root", str(tmp_path)])
    add_match.main()
    ledger = functions.read_text(encoding="utf-8")
    assert f"{REAL},," in ledger and "?realBody@Thing@@,," not in ledger
    assert "completes-decoration=?realBody@Thing@@" in ledger
    tombstone = list(csv.reader(io.StringIO(deleted.read_text(encoding="utf-8"))))[-1]
    assert tombstone[:2] == ["?realBody@Thing@@", "0x00ABCD00"]


def test_replace_existing_does_not_complete_a_name_at_another_address(tmp_path, monkeypatch):
    lift = ("?realBody@Thing@@,,0x00ABCE00,32,game/GameEngine/Source/Common/ThingThunk.cpp,"
            "matched,")
    arrange(tmp_path, monkeypatch, gate=0, scaffold=lift)
    monkeypatch.setattr(sys, "argv", [
        "add_match.py", REAL, "0x00ABCD00", "32", SOURCE_REL,
        "--replace-existing", "--root", str(tmp_path)])
    with pytest.raises(SystemExit):
        add_match.main()
