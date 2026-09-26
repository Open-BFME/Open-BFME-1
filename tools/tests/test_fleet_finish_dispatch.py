"""The real finish picker rechecks stale advisory work before dispatch."""
from pathlib import Path
import sys
import threading

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools/fleet"))
import eligibility  # noqa: E402
import pick_finish  # noqa: E402
import portable_lock  # noqa: E402


def row(rva, size=100, source="game/masm_dumps/body.asm"):
    return f"?d_{rva:08x}@@YAXXZ,,0x{rva:08x},{size},{source},matched,\n"


def fixture(tmp_path, monkeypatch, busy=None):
    (tmp_path / "targets/game/reverse").mkdir(parents=True)
    (tmp_path / "build/fleet_logs").mkdir(parents=True)
    ledger = tmp_path / "targets/game/reverse/functions.csv"
    header = "name,export_rva,target_rva,target_size,source,status,notes\n"
    stash = {}
    for rva in (0x1000, 0x2000, 0x3000):
        path = tmp_path / f"{rva:x}.cpp"
        path.write_text(f"// ?d_{rva:08x}@@YAXXZ\n// partial score=0.99\nvoid f() {{}}\n")
        stash[rva] = (path, 0.99 - (rva // 0x1000) / 100)
    monkeypatch.setattr(eligibility, "stash", lambda rva: stash.get(rva))
    if busy is None:
        busy = {"0x00001000"}
    monkeypatch.setattr(eligibility, "busy_rvas", lambda root: set(busy))
    monkeypatch.setattr(eligibility, "recent_run_rvas", lambda hours, root: set())
    return ledger, header, stash


def test_finish_rechecks_landed_busy_and_changed_size_targets(tmp_path, monkeypatch):
    ledger, header, stash = fixture(tmp_path, monkeypatch)
    # 0x2000 landed after the expensive probe; 0x3000 changed boundary size.
    ledger.write_text(header + row(0x1000) + row(0x2000, source="game/real.cpp")
                      + row(0x3000, size=120))
    prepared = [(stash[rva][1], 100, f"0x{rva:08x}", stash[rva][0])
                for rva in (0x1000, 0x2000, 0x3000)]
    assert pick_finish.finalize(prepared, {}, 2, 0.9, 0, 0, tmp_path) == []
    assert not (tmp_path / "build/fleet_logs/seats.log").exists()


def test_finish_uses_next_valid_candidate_once_and_does_not_spin(tmp_path, monkeypatch):
    ledger, header, stash = fixture(tmp_path, monkeypatch)
    ledger.write_text(header + row(0x1000) + row(0x2000) + row(0x3000))
    prepared = [(stash[rva][1], 100, f"0x{rva:08x}", stash[rva][0])
                for rva in (0x1000, 0x2000, 0x3000)]
    assert pick_finish.finalize(prepared, {}, 2, 0.9, 0, 0, tmp_path) == [
        "0x00002000", "0x00003000"]
    assert "selected 0x00002000 0x00003000" in (
        tmp_path / "build/fleet_logs/seats.log").read_text()


def test_finish_waits_for_lock_then_uses_current_claims(tmp_path, monkeypatch):
    busy = set()
    ledger, header, stash = fixture(tmp_path, monkeypatch, busy)
    ledger.write_text(header + row(0x1000) + row(0x2000))
    prepared = [(stash[rva][1], 100, f"0x{rva:08x}", stash[rva][0])
                for rva in (0x1000, 0x2000)]
    entering = threading.Event()
    result = []
    original_lock = pick_finish.lock

    def signal_lock(handle, **kwargs):
        entering.set()
        return original_lock(handle, **kwargs)

    monkeypatch.setattr(pick_finish, "lock", signal_lock)
    handle = (tmp_path / "build/.fleet_claims.lock").open("a+b")
    portable_lock.lock(handle, exclusive=True)
    worker = threading.Thread(target=lambda: result.extend(
        pick_finish.finalize(prepared, {}, 1, 0.9, 0, 0, tmp_path)))
    try:
        worker.start()
        assert entering.wait(3)
        assert worker.is_alive()
        busy.add("0x00001000")
    finally:
        portable_lock.unlock(handle)
        handle.close()
        worker.join(timeout=3)
    assert not worker.is_alive()
    assert result == ["0x00002000"]
