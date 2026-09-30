"""add_match must not release a shared claim on LOCAL verification.

Until 2026-09-29 it called claims.release([rva], force=True) right after the
local byte gate, before the commit was pushed, so another worker could take
a body whose conversion was still unpublished (or about to be rejected). It
now queues the exact row, and the claim is released only once origin/master
holds it (claims.release_landed).
"""
import json
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import add_match  # noqa: E402
import claims  # noqa: E402

HEADER = "name,export_rva,target_rva,target_size,source,status,notes"
DUMP = "?d_00abcd00@@YAXXZ,,0x00ABCD00,32,game/gen_asm/d_00abcd00.asm,matched,gen-dump"
REAL = "?realBody@Thing@@QAEXXZ"
SOURCE_REL = "game/GameEngine/Source/Common/Thing.cpp"


@pytest.fixture
def landing(tmp_path, monkeypatch):
    reverse = tmp_path / "targets/game/reverse"
    reverse.mkdir(parents=True)
    source = tmp_path / SOURCE_REL
    source.parent.mkdir(parents=True)
    source.write_bytes(f"// {REAL} present-unmatched\r\nvoid realBody() {{}}\r\n".encode())
    (reverse / "functions.csv").write_bytes(f"{HEADER}\r\n{DUMP}\r\n".encode())
    (reverse / "deleted_rows.csv").write_bytes(b"name,target_rva,reason\n")
    (tmp_path / "build.sh").write_text("#!/bin/sh\nexit 0\n", encoding="utf-8")
    monkeypatch.setattr(add_match, "DEFAULT_ROOT", tmp_path)
    monkeypatch.setattr(add_match.subprocess, "run",
                        lambda command, *, cwd, env: SimpleNamespace(returncode=0))
    monkeypatch.setenv("BFME_CLAIM_OWNER", "worker-a")
    monkeypatch.delenv("BFME_CLAIMS", raising=False)

    def forbidden(*args, **kwargs):
        raise AssertionError("add_match released a claim before publication")
    monkeypatch.setattr(claims, "release", forbidden)
    monkeypatch.setattr(sys, "argv", [
        "add_match.py", REAL, "0x00ABCD00", "32", SOURCE_REL, "--replace-rva", "0x00ABCD00",
        "--root", str(tmp_path), "--model", "test-model"])
    return tmp_path


def test_local_verification_queues_instead_of_releasing(landing):
    add_match.main()
    queued = [json.loads(line) for line in
              (landing / claims.PENDING).read_text(encoding="utf-8").splitlines()]
    assert len(queued) == 1
    assert queued[0]["rva"] == "0x00ABCD00" and queued[0]["owner"] == "worker-a"
    assert queued[0]["row"].startswith(f"{REAL},,0x00ABCD00,32,{SOURCE_REL},matched,")


def test_claims_off_queues_nothing(landing, monkeypatch):
    monkeypatch.setenv("BFME_CLAIMS", "off")
    add_match.main()
    assert not (landing / claims.PENDING).exists()


def _landed_notes(root):
    rows = (root / "targets/game/reverse/functions.csv").read_text(encoding="utf-8").splitlines()
    return [r for r in rows if r.startswith(REAL)][0].split(",", 6)[6]


def test_the_receipt_records_host_run_and_a_disagreeing_launched_model(landing, monkeypatch):
    monkeypatch.setenv("BFME_HOST_TAG", "seat-host-7")
    monkeypatch.setenv("BFME_RUN_ID", "20260929T010203Z-abcdef012345")
    monkeypatch.setenv("BFME_MODEL", "gpt-6-astra")        # what fleet_run launched
    add_match.main()                                        # the worker typed test-model
    notes = _landed_notes(landing)
    assert "model=test-model" in notes
    assert "launched=gpt-6-astra" in notes
    assert "host=seat-host-7" in notes
    assert "run=20260929T010203Z-abcdef012345" in notes


def test_an_agreeing_model_adds_no_launched_tag(landing, monkeypatch):
    monkeypatch.setenv("BFME_HOST_TAG", "bad host!")
    monkeypatch.setenv("BFME_MODEL", "test-model")
    add_match.main()
    notes = _landed_notes(landing)
    assert "launched=" not in notes and "host=bad-host-" in notes
