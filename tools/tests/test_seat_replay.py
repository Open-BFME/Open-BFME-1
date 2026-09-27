"""Replaying a seat's own delta onto a moved master (tools/fleet/seat_replay.py)."""
import subprocess
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
sys.path.insert(0, str(TOOLS / "fleet"))

import seat_replay as R  # noqa: E402

SHARED = "{}\n" + "".join(f"line{i}\n" for i in range(8)) + "{}\n"
HEAD = b"name,export_rva,target_rva,target_size,source,status,notes\r\n"


def test_record_delta_is_the_seat_change_only():
    before = HEAD + b"?d_1@@YAXXZ,,0x1,8,d.asm,matched,\r\r\n" + b"?x@@YAXXZ,,0x9,4,x.cpp,matched,\r\n"
    after = HEAD + b"?x@@YAXXZ,,0x9,4,x.cpp,matched,\r\n" + b"?real@@YAXXZ,,0x1,8,r.cpp,matched,\r\n"
    removed, added = R.record_delta(before, after)
    assert dict(removed) == {b"?d_1@@YAXXZ,,0x1,8,d.asm,matched,": 1}
    assert added == [(b"?real@@YAXXZ,,0x1,8,r.cpp,matched,", b"\r\n")]


def test_apply_keeps_master_rows_and_their_terminators():
    master = (HEAD + b"?up@@YAXXZ,,0x5,4,u.cpp,matched,\r\r\n" + b"?d_1@@YAXXZ,,0x1,8,d.asm,matched,\r\r\n"
              + b"?new_upstream@@YAXXZ,,0x7,4,n.cpp,matched,\n")
    removed, added = R.record_delta(HEAD + b"?d_1@@YAXXZ,,0x1,8,d.asm,matched,\r\r\n",
                                    HEAD + b"?real@@YAXXZ,,0x1,8,r.cpp,matched,\r\n")
    out = R.apply_records(master, removed, added)
    assert out == (HEAD + b"?up@@YAXXZ,,0x5,4,u.cpp,matched,\r\r\n"
                   + b"?new_upstream@@YAXXZ,,0x7,4,n.cpp,matched,\n"
                   + b"?real@@YAXXZ,,0x1,8,r.cpp,matched,\r\n")


def test_a_row_master_already_has_is_not_appended_twice():
    master = HEAD + b"?real@@YAXXZ,,0x1,8,r.cpp,matched,\r\n"
    out = R.apply_records(master, {}, [(b"?real@@YAXXZ,,0x1,8,r.cpp,matched,", b"\r\n")])
    assert out == master


def _git(cwd, *args):
    return subprocess.run(["git", *args], cwd=cwd, check=True, capture_output=True, text=True).stdout


def test_seat_delta_and_apply_on_a_moved_master(tmp_path):
    repo = tmp_path / "repo"
    repo.mkdir()
    _git(repo, "init", "-q", "-b", "master")
    _git(repo, "config", "user.email", "t@example.com")
    _git(repo, "config", "user.name", "t")
    # the real ledger blobs carry their CRs, so git never converts them
    _git(repo, "config", "core.autocrlf", "false")
    ledger = repo / "targets/game/reverse/functions.csv"
    ledger.parent.mkdir(parents=True)
    ledger.write_bytes(HEAD + b"?d_1@@YAXXZ,,0x1,8,d.asm,matched,\r\n")
    (repo / "shared.cpp").write_text(SHARED.format("a", "c"))
    _git(repo, "add", ".")
    _git(repo, "commit", "-qm", "base")
    base = _git(repo, "rev-parse", "HEAD").strip()
    # the seat: replaces the dump row, adds a source, edits line 1 of shared.cpp
    ledger.write_bytes(HEAD + b"?real@@YAXXZ,,0x1,8,r.cpp,matched,\r\n")
    (repo / "r.cpp").write_text("void real() {}\n")
    (repo / "shared.cpp").write_text(SHARED.format("A", "c"))
    _git(repo, "add", ".")
    _git(repo, "commit", "-qm", "seat")
    seat = _git(repo, "rev-parse", "HEAD").strip()
    # master moved: another row appended, last line of shared.cpp edited
    _git(repo, "checkout", "-q", base)
    ledger.write_bytes(HEAD + b"?d_1@@YAXXZ,,0x1,8,d.asm,matched,\r\n" + b"?up@@YAXXZ,,0x5,4,u.cpp,matched,\r\n")
    (repo / "shared.cpp").write_text(SHARED.format("a", "C"))
    _git(repo, "commit", "-qam", "master moved")
    delta = R.seat_delta(repo, seat)
    assert R.apply_delta(repo, delta) is None
    assert ledger.read_bytes() == (HEAD + b"?up@@YAXXZ,,0x5,4,u.cpp,matched,\r\n"
                                   + b"?real@@YAXXZ,,0x1,8,r.cpp,matched,\r\n")
    assert (repo / "r.cpp").read_text() == "void real() {}\n"
    assert (repo / "shared.cpp").read_text() == SHARED.format("A", "C")
