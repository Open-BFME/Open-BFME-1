"""A corrected identity must retain its bytes and retire its old ledger key."""

import csv
import io
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import correct_match_identity as C  # noqa: E402

OLD = "?bfmeGet1270@BfmeA1270@@QAEXPAUBfmeVec1270@@0@Z"
NEW = "?findFarthestEdgePoint@TerrainLogic@@UBE?AUCoord3D@@PBU2@@Z"
SOURCE = "game/GameEngine/Source/Common/BfmeConv1270.cpp"
EVIDENCE = "targets/game/reverse/identity_farthest_edge_001a38b0.md"
HEADER = b"name,export_rva,target_rva,target_size,source,status,notes\r\n"
OLD_ROW = f"{OLD},,0x001A38B0,151,{SOURCE},matched,".encode()
OTHER = b"?other@@YAXXZ,,0x001A4000,10,game/other.cpp,matched,\n"


@pytest.fixture
def repo(tmp_path):
    (tmp_path / "targets/game/reverse").mkdir(parents=True)
    (tmp_path / "tools").mkdir()
    (tmp_path / SOURCE).parent.mkdir(parents=True)
    (tmp_path / SOURCE).write_text("void body() {}\n")
    (tmp_path / EVIDENCE).write_text("vtable slot and native ABI evidence\n")
    (tmp_path / "build.sh").write_text("#!/bin/sh\nexit 0\n")
    (tmp_path / "targets/game/reverse/functions.csv").write_bytes(HEADER + OLD_ROW + b"\r\r\n" + OTHER)
    (tmp_path / "targets/game/reverse/deleted_rows.csv").write_bytes(b"name,target_rva,reason\r\n")
    return tmp_path


def test_rename_preserves_mixed_terminators_and_records_tombstone(repo, monkeypatch):
    calls = []

    def passed(command, **kwargs):
        calls.append((command, kwargs))
        return SimpleNamespace(returncode=0)

    monkeypatch.setattr(C.subprocess, "run", passed)
    C.correct(repo, OLD, NEW, 0x001A38B0, 151, SOURCE, EVIDENCE)

    changed = (repo / "targets/game/reverse/functions.csv").read_bytes()
    assert OLD_ROW not in changed
    assert changed.startswith(HEADER)
    assert b"\r\r\n" + OTHER in changed
    assert (NEW + ",,0x001A38B0,151," + SOURCE + ",matched,object-symbol=" + OLD).encode() in changed
    assert ("identity-evidence=" + EVIDENCE).encode() in changed
    deleted = list(csv.reader(io.StringIO(
        (repo / "targets/game/reverse/deleted_rows.csv").read_text())))[-1]
    assert deleted[:2] == [OLD, "0x001A38B0"]
    assert NEW in deleted[2]
    assert len(calls) == 2
    assert calls[0][1]["env"]["ADDMATCH_BOUNDARY_NAME"] == NEW


def test_failed_byte_gate_restores_both_ledgers(repo, monkeypatch):
    functions = repo / "targets/game/reverse/functions.csv"
    deleted = repo / "targets/game/reverse/deleted_rows.csv"
    before = functions.read_bytes(), deleted.read_bytes()
    monkeypatch.setattr(C.subprocess, "run",
                        lambda *_args, **_kwargs: SimpleNamespace(returncode=1))

    with pytest.raises(SystemExit, match="scoped byte gate failed"):
        C.correct(repo, OLD, NEW, 0x001A38B0, 151, SOURCE, EVIDENCE)

    assert (functions.read_bytes(), deleted.read_bytes()) == before


def test_refuses_to_replace_a_scaffold(repo):
    functions = repo / "targets/game/reverse/functions.csv"
    before = functions.read_bytes()
    functions.write_bytes(before.replace(b"matched,\r\r\n", b"matched,gen-dump\r\r\n"))
    with pytest.raises(SystemExit, match="add_match --replace-rva"):
        C.correct(repo, OLD, NEW, 0x001A38B0, 151, SOURCE, EVIDENCE)
    assert b"gen-dump" in functions.read_bytes()


def test_preserves_existing_note_and_refuses_claimed_new_name(repo, monkeypatch):
    functions = repo / "targets/game/reverse/functions.csv"
    before = functions.read_bytes()
    functions.write_bytes(before.replace(OLD_ROW, OLD_ROW + b"earlier-proof"))
    monkeypatch.setattr(C.subprocess, "run",
                        lambda *_args, **_kwargs: SimpleNamespace(returncode=0))
    C.correct(repo, OLD, NEW, 0x001A38B0, 151, SOURCE, EVIDENCE)
    assert (b"matched,earlier-proof;object-symbol=" + OLD.encode()) in functions.read_bytes()

    changed = functions.read_bytes().replace(OTHER, (
        OLD + ",,0x001A4000,10,game/other.cpp,matched,\n").encode())
    functions.write_bytes(changed)
    with pytest.raises(SystemExit, match="new name is already claimed"):
        C.correct(repo, NEW, OLD, 0x001A38B0, 151, SOURCE, EVIDENCE)


def test_preserves_quoted_note(repo, monkeypatch):
    functions = repo / "targets/game/reverse/functions.csv"
    functions.write_bytes(functions.read_bytes().replace(
        OLD_ROW, OLD_ROW + b'"note, with comma"'))
    monkeypatch.setattr(C.subprocess, "run",
                        lambda *_args, **_kwargs: SimpleNamespace(returncode=0))
    C.correct(repo, OLD, NEW, 0x001A38B0, 151, SOURCE, EVIDENCE)
    rows = list(csv.reader(io.StringIO(functions.read_text())))
    changed = next(row for row in rows if row[0] == NEW)
    assert changed[6].startswith("note, with comma;object-symbol=" + OLD)
