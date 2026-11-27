"""A single-body scaffold conversion is a two-ledger transaction.

functions.csv uses git's union merge driver, so deleting its generated row is
not durable by itself: a branch forked before the conversion can silently put
the row back. add_match --replace-rva must tombstone that exact synthetic
identity, and a failed byte gate must restore the tombstone with everything
else it touched.
"""
import csv
import io
import subprocess
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import add_match

def fake_run(gate):
    """subprocess.run double: the verify build returns GATE; git calls (gate_writers.stamp,
    which passes capture_output=True since 58db922b43) get a captured failure, so no stamp
    file is written outside the fixture."""
    def run(command, **kwargs):
        if command and command[0] == "git":
            run.git.append(list(command[1:]))
            return SimpleNamespace(returncode=1, stdout=b"", stderr=b"")
        assert set(kwargs) == {"cwd", "env"}, kwargs
        return SimpleNamespace(returncode=gate)
    run.git = []
    return run


STAMP_CALL = ["rev-parse", "--git-path", "bfme-gate-writers"]


def stamp_reached():
    """True when add_match reached gate_writers.stamp (its first git call) under fake_run."""
    return STAMP_CALL in add_match.subprocess.run.git



HEADER = "name,export_rva,target_rva,target_size,source,status,notes"
DUMP = (
    "?d_00abcd00@@YAXXZ,,0x00ABCD00,32,game/gen_asm/d_00abcd00.asm,matched,"
    "gen-dump;ghidra=FUN_00eacd00"
)
REAL = "?realBody@Thing@@QAEXXZ"
SOURCE_REL = "game/GameEngine/Source/Common/Thing.cpp"


def arrange(tmp_path, monkeypatch, *, gate, target_rva="0x00ABCD00", size="32",
            extra_args=(), scaffold=DUMP, replace_rva="0x00ABCD00"):
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
        fake_run(gate))
    monkeypatch.setattr(sys, "argv", [
        "add_match.py", REAL, target_rva, size, SOURCE_REL,
        "--replace-rva", replace_rva, "--root", str(tmp_path),
        *extra_args,
    ])
    return functions, deleted, source


def test_replace_rva_tombstones_the_superseded_scaffold(tmp_path, monkeypatch):
    functions, deleted, _source = arrange(tmp_path, monkeypatch, gate=0)

    add_match.main()

    assert stamp_reached()                  # a verified relabel stamps gate_writers
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
        fake_run(0))
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


# Vendored rows (approved by the project lead 2026-10-15): --correct-identity may
# retire a matched vendored=<lib> row only with evidence naming its RVA and both names.
VRVA = "0x00069C80"
VENDORED_OLD = "?swap@?$vector@PAX@_STL@@QAEXAAV12@@Z"
VENDORED = DUMP.replace("?d_00abcd00@@YAXXZ", VENDORED_OLD).replace(
    "game/gen_asm/d_00abcd00.asm", "game/gen_small/zhstl_001.cpp").replace(
    "gen-dump;ghidra=FUN_00eacd00", "vendored=cnc-zh;zhstl").replace(
    "0x00ABCD00", VRVA)
VENDORED_PROOF = "targets/game/reverse/identity_evidence/0x00069c80-vendored.md"
GOOD_PROOF = f"Retail 0x00069C80 is {REAL}, not {VENDORED_OLD}: matched caller.\n"


def arrange_vendored(tmp_path, monkeypatch, scaffold=VENDORED, proof_text=GOOD_PROOF,
                     with_evidence=True):
    extra = ("--correct-identity", VENDORED_OLD)
    if with_evidence:
        extra += ("--identity-evidence", VENDORED_PROOF)
    functions, deleted, source = arrange(tmp_path, monkeypatch, gate=0, target_rva=VRVA, replace_rva=VRVA,
                                         scaffold=scaffold, extra_args=extra)
    proof = tmp_path / VENDORED_PROOF
    proof.parent.mkdir(parents=True)
    proof.write_text(proof_text)
    return functions, deleted, source


def assert_refused(functions, deleted, source):
    before = functions.read_bytes(), deleted.read_bytes(), source.read_bytes()
    with pytest.raises(SystemExit):
        add_match.main()
    assert (functions.read_bytes(), deleted.read_bytes(), source.read_bytes()) == before


def test_vendored_correction_with_evidence_is_accepted(tmp_path, monkeypatch):
    functions, deleted, _ = arrange_vendored(tmp_path, monkeypatch)
    add_match.main()
    ledger = functions.read_text()
    assert VENDORED_OLD not in ledger
    assert "identity-correction=" + VENDORED_PROOF in ledger
    assert ledger.count("0x00069C80") == 1
    tombstone = list(csv.reader(io.StringIO(deleted.read_text())))[-1]
    assert tombstone[0] == VENDORED_OLD
    assert REAL in tombstone[2]


def test_vendored_correction_without_evidence_is_refused(tmp_path, monkeypatch):
    assert_refused(*arrange_vendored(tmp_path, monkeypatch, with_evidence=False))


@pytest.mark.parametrize("text", [
    f"{REAL} replaces {VENDORED_OLD}.\n",                       # no RVA
    f"0x00069C90 is {REAL}, not {VENDORED_OLD}.\n",             # wrong RVA
    f"0x00069C80 is {REAL}.\n",                                 # no old name
    f"0x00069C80 is not {VENDORED_OLD}.\n",                     # no new name
])
def test_vendored_correction_with_weak_evidence_is_refused(tmp_path, monkeypatch, text):
    assert_refused(*arrange_vendored(tmp_path, monkeypatch, proof_text=text))


def test_unmatched_vendored_row_is_refused(tmp_path, monkeypatch):
    unmatched = VENDORED.replace(",matched,", ",unmatched,")
    assert_refused(*arrange_vendored(tmp_path, monkeypatch, scaffold=unmatched))


@pytest.mark.parametrize("notes", [
    "gen-thunk;gap;target=0x00066C70",
    "zhstl;source=vendored=cnc-zh",
])
def test_non_vendored_gen_row_still_refused_with_good_evidence(tmp_path, monkeypatch, notes):
    gen = VENDORED.replace("vendored=cnc-zh;zhstl", notes)
    assert_refused(*arrange_vendored(tmp_path, monkeypatch, scaffold=gen))


def test_vendored_tombstone_cites_evidence_and_prior_notes(tmp_path, monkeypatch):
    _, deleted, _ = arrange_vendored(tmp_path, monkeypatch)
    add_match.main()
    tombstone = list(csv.reader(io.StringIO(deleted.read_text())))[-1]
    assert "Identity evidence: " + VENDORED_PROOF in tombstone[2]
    assert "Prior notes: vendored=cnc-zh;zhstl" in tombstone[2]


@pytest.mark.parametrize("text", [
    f"0x00069c80 is {REAL.upper()}, not {VENDORED_OLD.upper()}.\n",   # case-folded names
    f"0x00069C801 is {REAL}, not {VENDORED_OLD}.\n",                    # RVA superstring
    f"0x00069C80 is x{REAL}, not {VENDORED_OLD}.\n",                    # name inside a token
    f"0x00069C80 is {REAL}, not {VENDORED_OLD}X.\n",                    # name prefix only
])
def test_vendored_evidence_must_name_exact_tokens(tmp_path, monkeypatch, text):
    assert_refused(*arrange_vendored(tmp_path, monkeypatch, proof_text=text))


def test_vendored_evidence_hex_case_is_free(tmp_path, monkeypatch):
    text = f"`0x00069c80` is `{REAL}`, not `{VENDORED_OLD}`.\n"
    arrange_vendored(tmp_path, monkeypatch, proof_text=text)
    add_match.main()


@pytest.mark.parametrize("new_name", [" ", "", "\t", f"{REAL} x"])
def test_blank_or_spaced_new_name_refused(tmp_path, monkeypatch, new_name):
    files = arrange_vendored(tmp_path, monkeypatch,
                             proof_text=f"0x00069C80 {VENDORED_OLD} {new_name}\n")
    sys.argv[1] = new_name
    assert_refused(*files)


@pytest.mark.parametrize("rva", ["0x009F9B82", "0x00A00000", "0x00AD5401"])
def test_vendored_row_in_paused_d3dx_region_refused(tmp_path, monkeypatch, rva):
    row = VENDORED.replace(VRVA, rva)
    extra = ("--correct-identity", VENDORED_OLD, "--identity-evidence", VENDORED_PROOF)
    files = arrange(tmp_path, monkeypatch, gate=0, target_rva=rva, replace_rva=rva, scaffold=row,
                    extra_args=extra)
    proof = tmp_path / VENDORED_PROOF
    proof.parent.mkdir(parents=True)
    proof.write_text(f"{rva} is {REAL}, not {VENDORED_OLD}.\n")
    assert_refused(*files)


# A renamed real parent and its existing compiler-label cleanup must be one
# verified ledger state. The fake byte gate tests the transaction only; the
# original/native proof remains an independent admission requirement.
PARENT_OLD = "?oldParent@@YAXXZ"
CHILD = "?existingCleanup@@YAXXZ"
CHILD_RVA = "0x00ABCE00"


def arrange_parent_correction(tmp_path, monkeypatch, *, notes=None, status="matched",
                              child_source=SOURCE_REL, parent_source=SOURCE_REL,
                              size="158", rva="0x00ABCD00", extra_args=()):
    proof_rel = "targets/game/reverse/identity_evidence/parent.md"
    parent = (f"{PARENT_OLD},,0x00ABCD00,158,{parent_source},matched,authored")
    files = arrange(tmp_path, monkeypatch, gate=0, scaffold=parent, size=size,
                    target_rva=rva, extra_args=("--correct-identity", PARENT_OLD,
                                              "--identity-evidence", proof_rel, *extra_args))
    proof = tmp_path / proof_rel
    proof.parent.mkdir(parents=True)
    proof.write_text(f"The original same body proves {PARENT_OLD} -> {REAL}.\n")
    if notes is None:
        notes = f"authored cleanup;gen-funclet;parent={PARENT_OLD};object-symbol=$L878;keep this prose"
    functions, _deleted, _source = files
    functions.write_bytes(functions.read_bytes() +
        f"{CHILD},,{CHILD_RVA},11,{child_source},{status},{notes}\r\n".encode())
    monkeypatch.delenv("BFME_RUN_DIR", raising=False)
    monkeypatch.setenv("BFME_CLAIMS", "off")
    return files


def ledger_rows(functions):
    return list(csv.DictReader(io.StringIO(functions.read_text(encoding="utf-8"))))


@pytest.mark.parametrize("gate", [0, 1])
def test_same_source_parent_and_158b_11b_child_are_verified_atomically(
        tmp_path, monkeypatch, gate):
    real_run = subprocess.run
    functions, deleted, source = arrange_parent_correction(tmp_path, monkeypatch)
    # Git is real, isolated and local. Only the C++ byte verifier is doubled.
    real_run(["git", "init", "-q", str(tmp_path)], check=True)
    before = functions.read_bytes(), deleted.read_bytes(), source.read_bytes()
    seen = []

    def verify(command, **kwargs):
        if command[0] == "git":
            return real_run(command, **kwargs)
        assert kwargs["cwd"] == tmp_path
        assert command[-1] == SOURCE_REL  # whole-source verification, not one row
        assert kwargs["env"]["ADDMATCH_BOUNDARY_NAME"] == REAL
        rows = ledger_rows(functions)
        parent = next(r for r in rows if r["name"] == REAL)
        child = next(r for r in rows if r["name"] == CHILD)
        assert parent["target_size"] == "158"
        assert child["target_size"] == "11" and child["target_rva"] == CHILD_RVA
        assert f"parent={REAL}" in child["notes"].split(";")
        assert "object-symbol=$L878" in child["notes"].split(";")
        assert PARENT_OLD not in [r["name"] for r in rows]
        assert "keep this prose" in child["notes"]
        seen.append(True)
        return SimpleNamespace(returncode=gate)

    monkeypatch.setattr(add_match.subprocess, "run", verify)
    if gate:
        with pytest.raises(SystemExit):
            add_match.main()
        assert (functions.read_bytes(), deleted.read_bytes(), source.read_bytes()) == before
    else:
        add_match.main()
        assert f"parent={REAL}" in next(r for r in ledger_rows(functions) if r["name"] == CHILD)["notes"]
    assert seen == [True]


def test_parent_retarget_preserves_all_other_bytes_and_mixed_terminators(tmp_path, monkeypatch):
    functions, _deleted, _source = arrange_parent_correction(tmp_path, monkeypatch)
    raw = functions.read_bytes()
    records = add_match.ledger_io.split_records(raw)
    # Exact marker with no object-symbol is also a native $L-named funclet.
    extra = (f"$L901,,0x00ABCF00,8,{SOURCE_REL},matched,gen-funclet;parent={PARENT_OLD};Begründung\n"
             f"?other@@YAXXZ,,0x00ABD000,4,game/Other.cpp,matched,foreign;parent={PARENT_OLD}\r\n").encode()
    functions.write_bytes(records[0][0] + b"\r\n" + records[1][0] + b"\r\r\n" +
                          records[2][0] + b"\n" + extra)
    before = functions.read_bytes()
    add_match.main()
    expected_kept = b"".join(payload.replace(f"parent={PARENT_OLD}".encode(), f"parent={REAL}".encode()) + term
        if add_match.ledger_key(add_match.ledger_io.fields(payload)) in {(CHILD, 0x00ABCE00), ("$L901", 0x00ABCF00)}
        else payload + term
        for payload, term in add_match.ledger_io.split_records(before)
        if add_match.ledger_key(add_match.ledger_io.fields(payload)) != (PARENT_OLD, 0x00ABCD00))
    assert functions.read_bytes().startswith(expected_kept)
    assert len(ledger_rows(functions)) == 4


@pytest.mark.parametrize("notes,status,child_source", [
    (f"gen-funclet;parent={PARENT_OLD}suffix;object-symbol=$L878", "matched", SOURCE_REL),
    (f"gen-funclet;prose parent={PARENT_OLD};object-symbol=$L878", "matched", SOURCE_REL),
    (f"gen-funclet;parent={PARENT_OLD.lower()};object-symbol=$L878", "matched", SOURCE_REL),
    (f"gen-funclet; parent={PARENT_OLD};object-symbol=$L878", "matched", SOURCE_REL),
    (f"gen-funclet;parent={PARENT_OLD} ;object-symbol=$L878", "matched", SOURCE_REL),
    (f"not-gen-funclet;parent={PARENT_OLD};object-symbol=$L878", "matched", SOURCE_REL),
    (f"gen-funclet;parent={PARENT_OLD};object-symbol=?realFunction@@YAXXZ", "matched", SOURCE_REL),
    (f"gen-funclet;parent={PARENT_OLD};object-symbol=$L878", "dump", SOURCE_REL),
    (f"gen-funclet;parent={PARENT_OLD};object-symbol=$L878", "matched", "game/Foreign.cpp"),
])
def test_parent_retarget_never_rewrites_unrelated_or_nonfunclet_metadata(
        tmp_path, monkeypatch, notes, status, child_source):
    functions, _deleted, _source = arrange_parent_correction(
        tmp_path, monkeypatch, notes=notes, status=status, child_source=child_source)
    child_before = next(payload + term for payload, term in add_match.ledger_io.split_records(functions.read_bytes())
                        if add_match.ledger_key(add_match.ledger_io.fields(payload)) == (CHILD, 0x00ABCE00))
    add_match.main()
    assert child_before in functions.read_bytes()


@pytest.mark.parametrize("notes", [
    f"gen-funclet;parent={PARENT_OLD};parent=?another@@YAXXZ;object-symbol=$L878",
    f"gen-funclet;parent={PARENT_OLD};parent={PARENT_OLD};object-symbol=$L878",
    f"gen-funclet;parent={PARENT_OLD};object-symbol=$L878;object-symbol=$L879",
])
def test_ambiguous_funclet_tokens_refuse_before_any_write(tmp_path, monkeypatch, capsys, notes):
    files = arrange_parent_correction(tmp_path, monkeypatch, notes=notes)
    before = tuple(p.read_bytes() for p in files)
    with pytest.raises(SystemExit) as error:
        add_match.main()
    assert error.value.code == 1
    assert "ambiguous funclet" in capsys.readouterr().err
    assert tuple(p.read_bytes() for p in files) == before
    assert not stamp_reached()


@pytest.mark.parametrize("kind", ["parent", "child", "quoted"])
def test_ambiguous_or_nonlossless_parent_rows_cannot_be_selected(tmp_path, monkeypatch, kind):
    files = arrange_parent_correction(tmp_path, monkeypatch)
    functions = files[0]
    if kind == "parent":
        functions.write_bytes(functions.read_bytes() +
            f"{PARENT_OLD},,0x00ABD100,4,{SOURCE_REL},matched,second old owner\r\n".encode())
    elif kind == "child":
        child = next(payload + term for payload, term in add_match.ledger_io.split_records(functions.read_bytes())
                     if add_match.ledger_key(add_match.ledger_io.fields(payload)) == (CHILD, 0x00ABCE00))
        functions.write_bytes(functions.read_bytes() + child)
    else:
        functions.write_bytes(functions.read_bytes().replace(
            b"matched,authored cleanup;", b'matched,"authored cleanup;').replace(
            b"keep this prose\r\n", b'keep this prose"\r\n'))
    before = tuple(p.read_bytes() for p in files)
    with pytest.raises(SystemExit):
        add_match.main()
    assert tuple(p.read_bytes() for p in files) == before


@pytest.mark.parametrize("size,rva,parent_source,extra", [
    ("159", "0x00ABCD00", SOURCE_REL, ("--boundary-evidence", "larger proven body")),
    ("174", "0x00ABCCF0", SOURCE_REL, ("--boundary-evidence", "contained old row")),
    ("158", "0x00ABCD00", "game/Old.cpp", ()),
])
def test_parent_retarget_does_not_expand_to_changed_range_or_source(
        tmp_path, monkeypatch, size, rva, parent_source, extra):
    functions, _deleted, _source = arrange_parent_correction(
        tmp_path, monkeypatch, size=size, rva=rva, parent_source=parent_source, extra_args=extra)
    child_before = next(r for r in ledger_rows(functions) if r["name"] == CHILD)
    add_match.main()  # Existing ordinary route; fake gate makes no C++ claim.
    assert next(r for r in ledger_rows(functions) if r["name"] == CHILD) == child_before


def test_parent_retarget_refuses_no_verify_without_mutation(tmp_path, monkeypatch, capsys):
    files = arrange_parent_correction(tmp_path, monkeypatch, extra_args=("--no-verify",))
    before = tuple(p.read_bytes() for p in files)
    with pytest.raises(SystemExit) as error:
        add_match.main()
    assert error.value.code == 1
    assert "--no-verify" in capsys.readouterr().err
    assert tuple(p.read_bytes() for p in files) == before


@pytest.mark.parametrize("error", [KeyboardInterrupt, OSError])
def test_parent_retarget_interrupted_verifier_restores_complete_snapshots(tmp_path, monkeypatch, error):
    files = arrange_parent_correction(tmp_path, monkeypatch)
    before = tuple(p.read_bytes() for p in files)

    def interrupted(command, **kwargs):
        if command[0] == "git":
            return SimpleNamespace(returncode=1, stdout=b"", stderr=b"")
        assert f"parent={REAL}" in next(r for r in ledger_rows(files[0]) if r["name"] == CHILD)["notes"]
        raise error()

    monkeypatch.setattr(add_match.subprocess, "run", interrupted)
    with pytest.raises(error):
        add_match.main()
    assert tuple(p.read_bytes() for p in files) == before
