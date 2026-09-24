"""A missing claims database must never turn a live fleet into an empty one."""
import json
import os
from pathlib import Path
import sqlite3
import subprocess
import sys

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import fleet_run  # noqa: E402
import eligibility  # noqa: E402
from fleet.reconcile_legacy import reconcile  # noqa: E402


RVA = "0x00001000"


def record(root, run, *, status="running", pid=None):
    directory = root / "build/fleet_runs" / run
    directory.mkdir(parents=True)
    data = {"status": status, "targets": [[RVA, 8]]}
    if pid is not None:
        data["pid"] = pid
    path = directory / "record.json"
    path.write_text(json.dumps(data), encoding="utf-8")
    return path


def test_lost_database_does_not_erase_live_ownership(tmp_path):
    fleet_run.claim(tmp_path, "original", [(RVA, 8)], pid=os.getpid(), lease=3600)
    record(tmp_path, "original", pid=os.getpid())
    database = tmp_path / "build/fleet_runs.sqlite"
    assert fleet_run.active_rvas(tmp_path) == {RVA}
    database.unlink()

    with pytest.raises(fleet_run.CoordinationUnavailable):
        fleet_run.active_rvas(tmp_path)
    with pytest.raises(fleet_run.CoordinationUnavailable):
        eligibility.busy_rvas(tmp_path)
    with pytest.raises(fleet_run.CoordinationUnavailable):
        fleet_run.claim(tmp_path, "replacement", [(RVA, 8)])
    assert not database.exists(), "a read or rejected claim must not recreate an empty database"


def test_replaced_database_does_not_match_old_coordination_marker(tmp_path):
    fleet_run.claim(tmp_path, "original", [(RVA, 8)], pid=os.getpid(), lease=3600)
    record(tmp_path, "original", pid=os.getpid())
    database = tmp_path / "build/fleet_runs.sqlite"
    database.unlink()
    sqlite3.connect(database).close()

    with pytest.raises(fleet_run.CoordinationUnavailable):
        fleet_run.active_rvas(tmp_path)
    with pytest.raises(fleet_run.CoordinationUnavailable):
        fleet_run.claim(tmp_path, "replacement", [(RVA, 8)])


def test_historical_first_use_requires_guarded_initialization(tmp_path):
    old = tmp_path / "build/fleet_logs/seats.log"
    old.parent.mkdir(parents=True)
    old.write_text("01:00 seat pick -> 0x00001000\n", encoding="utf-8")
    before = old.read_bytes()
    report = fleet_run.coordination_status(tmp_path)
    assert report["state"] == "requires_review"
    assert not (tmp_path / "build/fleet_runs.sqlite").exists()
    assert not fleet_run.coordination_marker(tmp_path).exists()

    with pytest.raises(ValueError):
        fleet_run.initialize_coordination(tmp_path, expected_sha=report["snapshot_sha256"])
    with pytest.raises(ValueError):
        fleet_run.initialize_coordination(tmp_path, stopped_fleet=True, expected_sha="wrong")
    assert old.read_bytes() == before
    assert not fleet_run.coordination_marker(tmp_path).exists()

    result = fleet_run.initialize_coordination(
        tmp_path, stopped_fleet=True, expected_sha=report["snapshot_sha256"])
    assert result["state"] == "ready"
    assert old.read_bytes() == before
    fleet_run.claim(tmp_path, "new-run", [(RVA, 8)])
    assert fleet_run.active_rvas(tmp_path) == {RVA}


def test_run_record_without_database_requires_restore(tmp_path):
    record(tmp_path, "old-run", status="finished")
    report = fleet_run.coordination_status(tmp_path)
    assert report["state"] == "missing"
    with pytest.raises(fleet_run.CoordinationUnavailable):
        fleet_run.initialize_coordination(
            tmp_path, stopped_fleet=True, expected_sha=report["snapshot_sha256"])
    assert not (tmp_path / "build/fleet_runs.sqlite").exists()


def test_malformed_record_cgroup_path_reports_unknown_not_crash(tmp_path):
    path = record(tmp_path, "odd-run", status="running")
    data = json.loads(path.read_text(encoding="utf-8"))
    data["cgroup_path"] = {"unexpected": "object"}
    path.write_text(json.dumps(data), encoding="utf-8")

    report = fleet_run.coordination_status(tmp_path)
    assert report["cgroup_units"] == {"empty": 0, "populated": 0, "unknown": 1}


def test_guarded_initialization_refuses_live_recorded_pid(tmp_path):
    fleet_run.claim(tmp_path, "live-run", [(RVA, 8)], pid=os.getpid(), lease=3600)
    record(tmp_path, "live-run", pid=os.getpid())
    fleet_run.coordination_marker(tmp_path).unlink()
    report = fleet_run.coordination_status(tmp_path)
    with pytest.raises(fleet_run.CoordinationUnavailable):
        fleet_run.initialize_coordination(
            tmp_path, stopped_fleet=True, expected_sha=report["snapshot_sha256"])
    assert not fleet_run.coordination_marker(tmp_path).exists()


def test_guarded_initialization_refuses_live_claim_without_record(tmp_path):
    fleet_run.claim(tmp_path, "live-run", [(RVA, 8)], pid=os.getpid(), lease=3600)
    fleet_run.coordination_marker(tmp_path).unlink()
    report = fleet_run.coordination_status(tmp_path)
    with pytest.raises(fleet_run.CoordinationUnavailable, match="claimed worker"):
        fleet_run.initialize_coordination(
            tmp_path, stopped_fleet=True, expected_sha=report["snapshot_sha256"])
    assert not fleet_run.coordination_marker(tmp_path).exists()


def test_guarded_initialization_refuses_unknown_nonterminal_run(tmp_path):
    fleet_run.connect(tmp_path).close()
    fleet_run.coordination_marker(tmp_path).unlink()
    record(tmp_path, "starting-run", status="starting")
    report = fleet_run.coordination_status(tmp_path)
    with pytest.raises(fleet_run.CoordinationUnavailable, match="nonterminal run has no PID"):
        fleet_run.initialize_coordination(
            tmp_path, stopped_fleet=True, expected_sha=report["snapshot_sha256"])
    assert not fleet_run.coordination_marker(tmp_path).exists()


def test_legacy_cutover_cannot_treat_missing_database_as_zero_claims(tmp_path):
    fleet_run.claim(tmp_path, "original", [(RVA, 8)], pid=os.getpid(), lease=3600)
    record(tmp_path, "original", pid=os.getpid())
    (tmp_path / "build/fleet_runs.sqlite").unlink()

    report = reconcile(tmp_path)
    assert report["coordination"]["state"] == "missing"
    with pytest.raises(fleet_run.CoordinationUnavailable):
        reconcile(tmp_path, apply=True, stopped_fleet=True,
                  expected_sha=report["log_sha256"])
    assert not (tmp_path / "build/fleet_legacy_cutover.json").exists()


def test_first_use_from_two_processes_shares_one_database(tmp_path):
    script = (
        "import sys\n"
        "from pathlib import Path\n"
        f"sys.path.insert(0, {str(Path(fleet_run.__file__).parent)!r})\n"
        "import fleet_run\n"
        "fleet_run.claim(Path(sys.argv[1]), sys.argv[2], "
        "[(sys.argv[3], 8)], pid=None, lease=3600)\n"
    )
    jobs = [subprocess.Popen([sys.executable, "-c", script, str(tmp_path),
                              "first" if n == 0 else "second", f"0x{0x1000 + n:08x}"],
                             stdout=subprocess.PIPE, stderr=subprocess.PIPE)
            for n in range(2)]
    results = [job.communicate(timeout=20) for job in jobs]
    assert all(job.returncode == 0 for job in jobs), results
    assert fleet_run.active_rvas(tmp_path) == {"0x00001000", "0x00001001"}


def test_corrupt_marker_keeps_claims_busy(tmp_path):
    fleet_run.claim(tmp_path, "original", [(RVA, 8)], pid=os.getpid(), lease=3600)
    fleet_run.coordination_marker(tmp_path).write_text("{}", encoding="utf-8")
    with pytest.raises(fleet_run.CoordinationUnavailable):
        fleet_run.active_rvas(tmp_path)


def test_initialized_database_missing_release_schema_is_not_repaired(tmp_path):
    fleet_run.claim(tmp_path, "original", [(RVA, 8)], pid=os.getpid(), lease=3600)
    database = tmp_path / "build/fleet_runs.sqlite"
    with sqlite3.connect(database) as db:
        db.execute("DROP TABLE releases")
    assert fleet_run.coordination_status(tmp_path)["state"] == "inconsistent"
    with pytest.raises(fleet_run.CoordinationUnavailable):
        fleet_run.claim(tmp_path, "replacement", [(RVA, 8)])
    with sqlite3.connect(database) as db:
        assert not db.execute("SELECT name FROM sqlite_master WHERE name='releases'").fetchone()


def test_unmarked_database_with_invalid_identity_cannot_reseed_marker(tmp_path):
    fleet_run.connect(tmp_path).close()
    marker = fleet_run.coordination_marker(tmp_path)
    marker.unlink()
    with sqlite3.connect(tmp_path / "build/fleet_runs.sqlite") as db:
        db.execute("UPDATE fleet_coordination SET id='invalid'")
    with pytest.raises(fleet_run.CoordinationUnavailable):
        fleet_run.connect(tmp_path)
    assert not marker.exists()


def test_old_release_history_requires_guarded_migration(tmp_path):
    database = tmp_path / "build/fleet_runs.sqlite"
    database.parent.mkdir(parents=True)
    with sqlite3.connect(database) as db:
        db.execute("CREATE TABLE claims (rva TEXT PRIMARY KEY, run TEXT, started REAL)")
        db.execute("CREATE TABLE releases (run TEXT, at REAL, reason TEXT)")
        db.execute("INSERT INTO releases VALUES ('old-run', 1, 'worker exited')")
    with pytest.raises(fleet_run.CoordinationUnavailable):
        fleet_run.connect(tmp_path)
    report = fleet_run.coordination_status(tmp_path)
    assert report["state"] == "requires_review"
    assert report["claim_count"] == 0
    assert report["release_count"] == 1
    result = fleet_run.initialize_coordination(
        tmp_path, stopped_fleet=True, expected_sha=report["snapshot_sha256"])
    assert result["state"] == "ready"
    with sqlite3.connect(database) as db:
        assert db.execute("SELECT count(*) FROM releases").fetchone()[0] == 1


def test_migrated_legacy_claim_with_unknown_pid_stays_busy(tmp_path):
    database = tmp_path / "build/fleet_runs.sqlite"
    database.parent.mkdir(parents=True)
    with sqlite3.connect(database) as db:
        db.execute("CREATE TABLE claims (rva TEXT PRIMARY KEY, run TEXT, started REAL)")
        db.execute("CREATE TABLE releases (run TEXT, at REAL, reason TEXT)")
        db.execute("INSERT INTO claims VALUES (?, 'old-run', 1)", (RVA,))
    record(tmp_path, "old-run", status="finished")
    report = fleet_run.coordination_status(tmp_path)
    assert report["state"] == "requires_review"
    result = fleet_run.initialize_coordination(
        tmp_path, stopped_fleet=True, expected_sha=report["snapshot_sha256"])
    assert result["state"] == "ready"
    assert fleet_run.active_rvas(tmp_path) == {RVA}
    with pytest.raises(fleet_run.ClaimConflict):
        fleet_run.claim(tmp_path, "replacement", [(RVA, 8)])


def test_invalid_pid_cannot_name_a_process_group_or_expire_claim(tmp_path, monkeypatch):
    record(tmp_path, "old-run", status="finished")
    monkeypatch.setattr(fleet_run.os, "kill", lambda *args: pytest.fail("invalid PID queried"))
    for pid in (None, 0, -1, "123", True):
        assert fleet_run.pid_alive(pid)
        assert not fleet_run.lease_dead(None, pid, root=tmp_path, run="old-run")


def test_changed_cutover_snapshot_requires_new_review(tmp_path):
    log = tmp_path / "build/fleet_logs/seats.log"
    log.parent.mkdir(parents=True)
    log.write_text("01:00 seat pick -> 0x00001000\n", encoding="utf-8")
    report = fleet_run.coordination_status(tmp_path)
    log.write_text(log.read_text() + "01:01 seat pick -> 0x00002000\n", encoding="utf-8")
    with pytest.raises(ValueError, match="state changed"):
        fleet_run.initialize_coordination(
            tmp_path, stopped_fleet=True, expected_sha=report["snapshot_sha256"])
    assert not fleet_run.coordination_marker(tmp_path).exists()


def test_marked_legacy_schema_requires_guarded_cgroup_migration(tmp_path):
    fleet_run.claim(tmp_path, "legacy-owner", [(RVA, 8)], pid=None, lease=3600)
    database = tmp_path / "build/fleet_runs.sqlite"
    with sqlite3.connect(database) as db:
        db.execute("ALTER TABLE claims DROP COLUMN cgroup_path")

    report = fleet_run.coordination_status(tmp_path)
    assert report["state"] == "requires_cgroup_migration"
    assert report["cgroup_schema"] == "missing"
    with sqlite3.connect(database) as db:
        assert "cgroup_path" not in {row[1] for row in db.execute("PRAGMA table_info(claims)")}
    with pytest.raises(fleet_run.CoordinationUnavailable, match="guarded cgroup schema migration"):
        fleet_run.active_rvas(tmp_path)
    with pytest.raises(ValueError):
        fleet_run.initialize_coordination(tmp_path, expected_sha=report["snapshot_sha256"])

    result = fleet_run.initialize_coordination(
        tmp_path, stopped_fleet=True, expected_sha=report["snapshot_sha256"])
    assert result["state"] == "ready"
    assert result["cgroup_schema"] == "present"
    with sqlite3.connect(database) as db:
        assert db.execute("SELECT cgroup_path FROM claims WHERE run='legacy-owner'").fetchone() == (None,)
    assert fleet_run.active_rvas(tmp_path) == {RVA}
    with pytest.raises(fleet_run.ClaimConflict):
        fleet_run.claim(tmp_path, "replacement", [(RVA, 8)])


def test_marked_cgroup_migration_does_not_repair_other_missing_columns(tmp_path):
    fleet_run.claim(tmp_path, "legacy-owner", [(RVA, 8)], pid=None, lease=3600)
    database = tmp_path / "build/fleet_runs.sqlite"
    with sqlite3.connect(database) as db:
        db.execute("ALTER TABLE claims DROP COLUMN cgroup_path")
        db.execute("ALTER TABLE claims DROP COLUMN expires")

    report = fleet_run.coordination_status(tmp_path)
    assert report["state"] == "inconsistent"
    with pytest.raises(fleet_run.CoordinationUnavailable):
        fleet_run.initialize_coordination(
            tmp_path, stopped_fleet=True, expected_sha=report["snapshot_sha256"])
    with sqlite3.connect(database) as db:
        columns = {row[1] for row in db.execute("PRAGMA table_info(claims)")}
    assert "cgroup_path" not in columns
    assert "expires" not in columns


def test_first_picker_diagnostic_with_file_stem_allows_fresh_runner(tmp_path):
    log = tmp_path / "build/fleet_logs/seats.log"
    log.parent.mkdir(parents=True)
    log.write_text("01:00 seat pick selected W3DModelDraw\n", encoding="utf-8")
    fleet_run.claim(tmp_path, "first", [(RVA, 8)], pid=None, lease=3600)
    assert fleet_run.active_rvas(tmp_path) == {RVA}
