"""The real review picker rechecks a bounded advisory shortlist."""
from pathlib import Path
import sys
import threading
import time
import uuid

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools/fleet"))
import eligibility  # noqa: E402
import fleet_cgroup  # noqa: E402
import fleet_run  # noqa: E402
import pick_review  # noqa: E402
import portable_lock  # noqa: E402
import re_log  # noqa: E402


HEADER = "name,export_rva,target_rva,target_size,source,status,notes\n"


def row(rva, size=100, source="Code/masm_dumps/test.asm"):
    return f"?d_{rva:08x}@@YAXXZ,,0x{rva:08x},{size},{source},matched,\n"


def seed(tmp_path, monkeypatch, scores):
    reverse = tmp_path / "reverse"
    attempts = reverse / "attempts"
    attempts.mkdir(parents=True)
    (tmp_path / "build/fleet_logs").mkdir(parents=True)
    monkeypatch.setattr(re_log, "RE_ATTEMPTS", reverse / "re_attempts.log")
    (reverse / "functions.csv").write_text(HEADER + "".join(row(rva) for rva in scores))
    (reverse / "re_attempts.log").write_text("".join(
        f"?d_{rva:08x}@@YAXXZ\t0x{rva:08x}\t100\tpartial\tbanked\n"
        for rva in scores))
    for rva, score in scores.items():
        (attempts / f"0x{rva:08x}.cpp").write_text(
            f"// ?d_{rva:08x}@@YAXXZ\n"
            f"// partial score={score:.2f} date=2026-09-23\n"
            "void candidate() {}\n")
    return reverse


def test_review_rechecks_landed_and_resized_bodies(tmp_path, monkeypatch):
    reverse = seed(tmp_path, monkeypatch, {0x1000: .94, 0x2000: .93, 0x3000: .92})
    prepared = pick_review.prepare(.5, .95, tmp_path)
    assert [c[2] for c in prepared] == ["0x00001000", "0x00002000", "0x00003000"]
    (reverse / "functions.csv").write_text(
        HEADER + row(0x1000, source="Code/landed.cpp") + row(0x2000, size=101)
        + row(0x3000))
    assert pick_review.finalize(prepared, 2, .5, .95, tmp_path, dry=True) == [
        "0x00003000"]


def test_review_rechecks_score_verdict_and_stash(tmp_path, monkeypatch):
    reverse = seed(tmp_path, monkeypatch, {
        0x1000: .94, 0x2000: .93, 0x3000: .92, 0x4000: .91, 0x5000: .90})
    prepared = pick_review.prepare(.5, .95, tmp_path)
    attempts = reverse / "attempts"
    for rva, score in ((0x1000, .49), (0x2000, .96)):
        (attempts / f"0x{rva:08x}.cpp").write_text(
            f"// ?d_{rva:08x}@@YAXXZ\n"
            f"// partial score={score:.2f} date=2026-09-23\n"
            "void candidate() {}\n")
    with (reverse / "re_attempts.log").open("a") as log:
        log.write("?d_00003000@@YAXXZ\t0x00003000\t100\tno-match\trefuted\n")
    (attempts / "0x00004000.cpp").unlink()
    assert pick_review.finalize(prepared, 2, .5, .95, tmp_path, dry=True) == [
        "0x00005000"]


def test_review_rechecks_a_resolved_latest_verdict(tmp_path, monkeypatch):
    reverse = seed(tmp_path, monkeypatch, {0x1000: .94, 0x2000: .93})
    prepared = pick_review.prepare(.5, .95, tmp_path)
    with (reverse / "re_attempts.log").open("a") as log:
        log.write("?d_00001000@@YAXXZ\t0x00001000\t100\tsolved\tresolved elsewhere\n")
    assert pick_review.finalize(prepared, 1, .5, .95, tmp_path, dry=True) == [
        "0x00002000"]


def test_review_tie_break_preserves_size_then_rva_order(tmp_path, monkeypatch):
    reverse = seed(tmp_path, monkeypatch, {0x1000: .90, 0x2000: .90, 0x3000: .90})
    (reverse / "functions.csv").write_text(
        HEADER + row(0x1000) + row(0x2000, size=120) + row(0x3000))
    prepared = pick_review.prepare(.5, .95, tmp_path)
    assert [c[2] for c in prepared] == [
        "0x00002000", "0x00003000", "0x00001000"]
    assert pick_review.finalize(prepared, 2, .5, .95, tmp_path, dry=True) == [
        "0x00002000", "0x00003000"]


def test_review_rechecks_claim_and_recent_touch(tmp_path, monkeypatch):
    seed(tmp_path, monkeypatch, {0x1000: .94, 0x2000: .93, 0x3000: .92})
    prepared = pick_review.prepare(.5, .95, tmp_path)
    fleet_run.claim(tmp_path, "other-run", [("0x00001000", 100)])
    run = tmp_path / "build/fleet_runs/older"
    run.mkdir(parents=True)
    (run / "record.json").write_text(
        '{"start": ' + str(time.time())
        + ', "status": "finished", "targets": [["0x00002000", 100]]}')
    assert pick_review.finalize(prepared, 2, .5, .95, tmp_path, dry=True) == [
        "0x00003000"]


def test_review_preparation_runs_before_acquiring_the_picker_lock(tmp_path, monkeypatch):
    seed(tmp_path, monkeypatch, {0x1000: .94})
    entered, proceed = threading.Event(), threading.Event()
    original_stash = eligibility.stash

    def observed_stash(rva):
        entered.set()
        assert proceed.wait(3)
        return original_stash(rva)

    monkeypatch.setattr(eligibility, "stash", observed_stash)
    handle = (tmp_path / "build/.fleet_claims.lock").open("a+b")
    portable_lock.lock(handle, exclusive=True)
    result = []
    worker = threading.Thread(target=lambda: result.extend(
        pick_review.prepare(.5, .95, tmp_path)))
    try:
        worker.start()
        assert entered.wait(3), "whole-pool preparation waited on the shared lock"
    finally:
        proceed.set()
        portable_lock.unlock(handle)
        handle.close()
        worker.join(timeout=3)
    assert not worker.is_alive()
    assert [c[2] for c in result] == ["0x00001000"]


def test_review_exhausted_shortlist_does_not_spin_or_log(tmp_path, monkeypatch):
    scores = {0x1000 * i: .94 - i / 1000 for i in range(1, 34)}
    reverse = seed(tmp_path, monkeypatch, scores)
    prepared = pick_review.prepare(.5, .95, tmp_path)
    assert len(prepared) == 33
    stale = {int(c[2], 16) for c in prepared[:32]}
    (reverse / "functions.csv").write_text(HEADER + "".join(
        row(rva, source="Code/landed.cpp" if rva in stale
            else "Code/masm_dumps/test.asm") for rva in scores))
    assert pick_review.finalize(prepared, 1, .5, .95, tmp_path) == []
    assert not (tmp_path / "build/fleet_logs/seats.log").exists()
    assert [c[2] for c in pick_review.prepare(.5, .95, tmp_path)] == [
        f"0x{next(rva for rva in scores if rva not in stale):08x}"]


def test_review_final_check_detects_an_unrelated_torn_ledger_row(tmp_path, monkeypatch):
    reverse = seed(tmp_path, monkeypatch, {0x1000: .94})
    prepared = pick_review.prepare(.5, .95, tmp_path)
    with (reverse / "functions.csv").open("a") as ledger:
        ledger.write("?d_00009000@@YAXXZ,,0x00009000\n")
    with pytest.raises(eligibility.LedgerUnreadable):
        pick_review.finalize(prepared, 1, .5, .95, tmp_path, dry=True)


def test_two_advisory_picks_still_need_an_atomic_claim(tmp_path, monkeypatch):
    seed(tmp_path, monkeypatch, {0x1000: .94})
    prepared = pick_review.prepare(.5, .95, tmp_path)
    for _ in range(2):
        assert pick_review.finalize(prepared, 1, .5, .95, tmp_path, dry=True) == [
            "0x00001000"]
    fleet_run.claim(tmp_path, "first", [("0x00001000", 100)])
    with pytest.raises(fleet_run.ClaimConflict):
        fleet_run.claim(tmp_path, "second", [("0x00001000", 100)])


def test_two_advisory_picks_still_need_one_live_atomic_runner_claim(tmp_path, monkeypatch):
    try:
        unit = fleet_cgroup.CgroupV2Unit.create("test-" + uuid.uuid4().hex)
    except fleet_cgroup.ContainmentUnavailable as error:
        pytest.skip(f"host does not delegate writable cgroup-v2 units: {error}")
    assert unit.remove()
    seed(tmp_path, monkeypatch, {0x1000: .94})
    prepared = pick_review.prepare(.5, .95, tmp_path)
    assert pick_review.finalize(prepared, 1, .5, .95, tmp_path, dry=True) == [
        "0x00001000"]
    assert pick_review.finalize(prepared, 1, .5, .95, tmp_path, dry=True) == [
        "0x00001000"]
    brief = tmp_path / "brief.txt"
    brief.write_text("TARGETS:\n- 0x00001000 100B body\n")
    marker = tmp_path / "worker-started"
    errors = []

    def run_owner():
        try:
            fleet_run.execute(
                tmp_path, brief, tmp_path / "owner.log", "test", "A",
                [sys.executable, "-c", "from pathlib import Path; import time; "
                 f"Path({str(marker)!r}).touch(); time.sleep(1)"])
        except BaseException as error:
            errors.append(error)

    owner = threading.Thread(target=run_owner)
    owner.start()
    try:
        deadline = time.monotonic() + 5
        while not marker.exists() and time.monotonic() < deadline:
            time.sleep(.01)
        assert marker.exists(), errors
        with pytest.raises(fleet_run.ClaimConflict):
            fleet_run.claim(tmp_path, "second", [("0x00001000", 100)])
    finally:
        owner.join(timeout=5)
    assert not owner.is_alive()
    assert not errors
