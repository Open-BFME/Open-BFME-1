"""Anonymous advisory picks shrink when a carved boundary gets claimed."""
from pathlib import Path
import sys
import threading

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools/fleet"))
import eligibility  # noqa: E402
import pick_anon  # noqa: E402
import portable_lock  # noqa: E402


def fixture(tmp_path, monkeypatch, busy=()):
    (tmp_path / "reverse").mkdir()
    (tmp_path / "build/fleet_logs").mkdir(parents=True)
    (tmp_path / "reverse/functions.csv").write_text(
        "name,export_rva,target_rva,target_size,source,status,notes\n"
        "?f@@YAXXZ,,0x00000ff0,32,Code/landed.cpp,matched,\n"
        "?d_00002000@@YAXXZ,,0x00002000,400,Code/masm_dumps/body.asm,matched,\n")
    (tmp_path / "reverse/carved.csv").write_text(
        "rva,size,start_evidence,callers,end_evidence,ghidra\n"
        "0x00001000,400,rel32-call/jmp,2,ret+int3,\n")
    monkeypatch.setattr(eligibility, "busy_rvas", lambda root: set(busy))
    monkeypatch.setattr(eligibility, "recent_run_rvas", lambda hours, root: set())
    return [(10, 400, "0x00001000", None, 10),
            (9, 400, "0x00002000", None, 9)]


def test_new_ledger_overlap_removes_a_prepared_carved_target(tmp_path, monkeypatch):
    prepared = fixture(tmp_path, monkeypatch)
    assert pick_anon.finalize(prepared, 2, 300, 2500, tmp_path) == ["0x00002000"]
    assert "selected 0x00002000" in (tmp_path / "build/fleet_logs/seats.log").read_text()


def test_final_claim_check_skips_busy_target_without_creating_a_pick(tmp_path, monkeypatch):
    prepared = fixture(tmp_path, monkeypatch, {"0x00002000"})
    assert pick_anon.finalize(prepared, 2, 300, 2500, tmp_path) == []
    assert not (tmp_path / "build/fleet_logs/seats.log").exists()


def test_expensive_anonymous_preparation_runs_while_picker_lock_is_held(tmp_path, monkeypatch):
    fixture(tmp_path, monkeypatch)
    entering = threading.Event()
    release = threading.Event()
    result = []

    def score(rva, unlocked):
        entering.set()
        assert release.wait(3)
        return 1

    monkeypatch.setattr(pick_anon, "warmth", score)
    handle = (tmp_path / "build/.fleet_claims.lock").open("a+b")
    portable_lock.lock(handle, exclusive=True)
    worker = threading.Thread(target=lambda: result.extend(
        pick_anon.prepare(300, 2500, tmp_path)[0]))
    try:
        worker.start()
        assert entering.wait(3), "preparation blocked on the shared picker lock"
    finally:
        release.set()
        portable_lock.unlock(handle)
        handle.close()
        worker.join(timeout=3)
    assert not worker.is_alive()
    assert [c[2] for c in result] == ["0x00002000"]


def test_removed_unlock_cannot_authorize_an_unchanged_blind_repeat(tmp_path, monkeypatch):
    fixture(tmp_path, monkeypatch)
    (tmp_path / "reverse/re_attempts.log").write_text(
        "?d_00002000@@YAXXZ\t0x00002000\t400\tblocked\tt=20 first\n"
        "?d_00002000@@YAXXZ\t0x00002000\t400\tblocked\tt=20 second\n")
    prepared = [(4, 400, "0x00002000", None, 0)]  # warmth was only the unlock bonus
    unlocks = tmp_path / "reverse/unlocked.txt"
    unlocks.write_text("0x00002000 shared-pin\n")
    assert pick_anon.finalize(prepared, 1, 300, 2500, tmp_path, dry=True) == ["0x00002000"]
    unlocks.unlink()
    assert pick_anon.finalize(prepared, 1, 300, 2500, tmp_path, dry=True) == []
