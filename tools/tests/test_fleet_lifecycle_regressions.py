"""The runner owns only launched brief targets; ownerless log picks are legacy."""
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import time

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import eligibility  # noqa: E402
import fleet_run  # noqa: E402
from fleet.reconcile_legacy import reconcile  # noqa: E402


def ledger(root, *targets):
    reverse = root / "reverse"
    reverse.mkdir(exist_ok=True)
    rows = ["name,export_rva,target_rva,target_size,source,status,notes"]
    rows.extend(f"?d_{rva:08X}@@YAXXZ,,0x{rva:08X},{size},Code/gen_asm/test.asm,matched,"
                for rva, size in targets)
    (reverse / "functions.csv").write_text("\n".join(rows) + "\n")


def brief(root, *targets):
    path = root / "brief.txt"
    path.write_text("TARGETS:\n" + "".join(f"- 0x{rva:08X} {size}B body\n"
                                             for rva, size in targets))
    return path


def log(root, content):
    path = root / "build/fleet_logs/seats.log"
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(content)
    return path


def test_failed_and_filtered_selections_never_own_rvas(tmp_path):
    ledger(tmp_path, (0x1000, 8), (0x2000, 8), (0x3000, 8))
    log(tmp_path, "01:00 seat pick selected 0x00001000 0x00002000 0x00003000\n")
    # A brief generator may fail or filter two of three selected RVAs. There
    # is no reservation to strand in either case.
    assert eligibility.busy_rvas(tmp_path) == set()
    with pytest.raises(ValueError):
        fleet_run.execute(tmp_path, brief(tmp_path), tmp_path / "empty.log", "test", "1",
                          [sys.executable, "-c", "pass"])
    assert eligibility.busy_rvas(tmp_path) == set()
    path = brief(tmp_path, (0x1000, 8))
    assert fleet_run.execute(tmp_path, path, tmp_path / "work.log", "test", "1",
                             [sys.executable, "-c", "pass"]) == 0
    record = json.loads(next((tmp_path / "build/fleet_runs").glob("*/record.json")).read_text())
    assert record["targets"] == [["0x00001000", 8]]
    assert eligibility.busy_rvas(tmp_path) == set()
    assert eligibility.recent_run_rvas(root=tmp_path) == set()


def test_multi_target_completion_releases_all_and_cools_only_touched(tmp_path):
    ledger(tmp_path, (0x1000, 8), (0x2000, 8))
    command = [sys.executable, "-c",
               f"import sys; sys.path.insert(0, {str(Path(fleet_run.__file__).parent)!r}); "
               "import fleet_run; fleet_run.mark_touched(0x1000)"]
    assert fleet_run.execute(tmp_path, brief(tmp_path, (0x1000, 8), (0x2000, 8)),
                             tmp_path / "work.log", "test", "1", command) == 0
    assert fleet_run.active_rvas(tmp_path) == set()
    assert eligibility.recent_run_rvas(root=tmp_path) == {"0x00001000"}
    with fleet_run.connect(tmp_path) as db:
        assert db.execute("SELECT rva FROM claims").fetchall() == []


def test_stale_brief_and_claim_conflict_never_launch(tmp_path):
    ledger(tmp_path, (0x1000, 8))
    path = brief(tmp_path, (0x1000, 8))
    started = tmp_path / "started"
    command = [sys.executable, "-c", f"from pathlib import Path; Path({str(started)!r}).touch()"]
    fleet_run.claim(tmp_path, "newer", [("0x00001000", 8)])
    with pytest.raises(fleet_run.ClaimConflict):
        fleet_run.execute(tmp_path, path, tmp_path / "conflict.log", "test", "1", command)
    fleet_run.release(tmp_path, "older", "late cleanup")
    assert fleet_run.active_rvas(tmp_path) == {"0x00001000"}
    assert not started.exists()
    fleet_run.release(tmp_path, "newer", "test")
    ledger(tmp_path)  # another worker landed it after brief creation
    with pytest.raises(fleet_run.StaleBrief):
        fleet_run.execute(tmp_path, path, tmp_path / "stale.log", "test", "1", command)
    assert not started.exists()
    assert fleet_run.active_rvas(tmp_path) == set()


def test_concurrent_runner_processes_launch_only_one_owner(tmp_path):
    ledger(tmp_path, (0x1000, 8))
    path = brief(tmp_path, (0x1000, 8))
    launched = tmp_path / "launched.txt"
    runner = tmp_path / "runner.py"
    runner.write_text(
        "import sys\n"
        f"sys.path.insert(0, {str(Path(fleet_run.__file__).parent)!r})\n"
        "import fleet_run\n"
        "from pathlib import Path\n"
        "root = Path(sys.argv[1])\n"
        "try:\n"
        "  fleet_run.execute(root, root/'brief.txt', root/(sys.argv[2]+'.log'), 'test', sys.argv[2], "
        f"[sys.executable, '-c', \"from pathlib import Path; import time; Path({str(launched)!r}).open('a').write('x\\\\n'); time.sleep(1)\"])\n"
        "except fleet_run.ClaimConflict:\n"
        "  sys.exit(75)\n")
    jobs = [subprocess.Popen([sys.executable, str(runner), str(tmp_path), str(i)],
                             stdout=subprocess.DEVNULL, stderr=subprocess.PIPE)
            for i in range(2)]
    results = [job.communicate(timeout=20) for job in jobs]
    assert sorted(job.returncode for job in jobs) == [0, 75], results
    assert launched.read_text().count("x") == 1
    assert fleet_run.active_rvas(tmp_path) == set()


def test_legacy_cutover_is_dry_run_guarded_and_detects_old_restart(tmp_path):
    # Production initializes durable coordination before old log events are
    # reconciled. A historical log with no DB now requires explicit cutover.
    fleet_run.connect(tmp_path).close()
    path = log(tmp_path, "01:00 seat pick -> 0x00001000 0x00002000\n"
                     "01:01 seat luna1 -> 0x00001000\n"
                     "01:02 seat luna1 done 0x00001000\n")
    assert eligibility.busy_rvas(tmp_path) == {"0x00002000"}
    before = path.read_bytes()
    report = reconcile(tmp_path)
    assert report["outstanding"] == ["0x00002000"]
    assert path.read_bytes() == before
    with pytest.raises(ValueError):
        reconcile(tmp_path, apply=True, stopped_fleet=True, expected_sha="wrong")
    fleet_run.claim(tmp_path, "live", [("0x00003000", 8)])
    with pytest.raises(RuntimeError):
        reconcile(tmp_path, apply=True, stopped_fleet=True, expected_sha=report["log_sha256"])
    fleet_run.release(tmp_path, "live", "test")
    with pytest.raises(ValueError):
        reconcile(tmp_path, apply=True, expected_sha=report["log_sha256"])
    assert reconcile(tmp_path, apply=True, stopped_fleet=True,
                     expected_sha=report["log_sha256"])["applied"]
    assert eligibility.busy_rvas(tmp_path) == set()
    assert reconcile(tmp_path)["outstanding"] == []
    with path.open("a") as stream:
        stream.write("01:03 seat pick -> 0x00004000\n")
    assert eligibility.busy_rvas(tmp_path) == {"0x00004000"}


def test_ambiguous_legacy_and_expired_unknown_pid_stay_busy(tmp_path):
    with fleet_run.connect(tmp_path) as db:
        db.execute("INSERT INTO claims (rva,run,started) VALUES ('0x00001000','unknown',0)")
    fleet_run.claim(tmp_path, "expired-unknown", [("0x00002000", 8)], pid=None, lease=-1)
    assert fleet_run.active_rvas(tmp_path) == {"0x00001000", "0x00002000"}


def test_supervisor_crash_keeps_expired_nonterminal_run_busy(tmp_path):
    if os.name != "posix":
        pytest.skip("this process-tree fixture uses fork and setsid")
    ledger(tmp_path, (0x1000, 8))
    brief_path = brief(tmp_path, (0x1000, 8))
    direct_pid_path = tmp_path / "direct.pid"
    descendant_pid_path = tmp_path / "descendant.pid"
    worker_code = (
        "import os,sys,time\n"
        "direct,descendant=sys.argv[1:]\n"
        "open(direct,'w').write(str(os.getpid()))\n"
        "pid=os.fork()\n"
        "if pid == 0:\n"
        " os.setsid()\n"
        " for fd in (0,1,2):\n"
        "  try: os.close(fd)\n"
        "  except OSError: pass\n"
        " with open(descendant,'w') as f:\n"
        "  f.write(str(os.getpid())); f.flush(); os.fsync(f.fileno())\n"
        " time.sleep(30)\n"
        " os._exit(0)\n"
        "time.sleep(2)\n"
    )
    runner_path = tmp_path / "runner.py"
    runner_path.write_text(
        "import sys\nfrom pathlib import Path\n"
        f"sys.path.insert(0, {str(Path(fleet_run.__file__).parent)!r})\n"
        "import fleet_run\n"
        f"root=Path({str(tmp_path)!r})\n"
        f"fleet_run.execute(root, {str(brief_path)!r}, root/'worker.log', 'test', 'crash', "
        f"[sys.executable, '-c', {worker_code!r}, {str(direct_pid_path)!r}, "
        f"{str(descendant_pid_path)!r}])\n",
        encoding="utf-8",
    )
    supervisor = subprocess.Popen([sys.executable, str(runner_path)], cwd=tmp_path,
                                  stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    direct_pid = descendant_pid = None
    try:
        deadline = time.monotonic() + 10
        while time.monotonic() < deadline and not (direct_pid_path.exists()
                                                   and descendant_pid_path.exists()):
            time.sleep(.02)
        assert direct_pid_path.exists() and descendant_pid_path.exists()
        direct_pid = int(direct_pid_path.read_text(encoding="ascii"))
        descendant_pid = int(descendant_pid_path.read_text(encoding="ascii"))

        # Wait until set_pid commits before killing the supervisor.
        deadline = time.monotonic() + 5
        while time.monotonic() < deadline:
            with fleet_run.connect(tmp_path) as db:
                owner = db.execute("SELECT run,pid FROM claims WHERE rva='0x00001000'").fetchone()
            if owner and owner[1] == direct_pid:
                run = owner[0]
                break
            time.sleep(.02)
        else:
            raise AssertionError("runner did not persist the worker PID")

        supervisor.kill()
        supervisor.wait(timeout=5)
        deadline = time.monotonic() + 8
        while fleet_run.pid_alive(direct_pid) and time.monotonic() < deadline:
            time.sleep(.02)
        assert not fleet_run.pid_alive(direct_pid)
        assert fleet_run.pid_alive(descendant_pid)

        with fleet_run.connect(tmp_path) as db:
            db.execute("UPDATE claims SET expires=? WHERE run=?", (time.time() - 1, run))
            db.commit()
        assert eligibility.busy_rvas(tmp_path) == {"0x00001000"}
        with pytest.raises(fleet_run.ClaimConflict):
            fleet_run.claim(tmp_path, "replacement", [("0x00001000", 8)])
    finally:
        if supervisor.poll() is None:
            supervisor.kill()
            supervisor.wait(timeout=5)
        if direct_pid and fleet_run.pid_alive(direct_pid):
            try:
                os.kill(direct_pid, 9)
            except ProcessLookupError:
                pass
        if descendant_pid:
            try:
                os.kill(descendant_pid, 9)
            except ProcessLookupError:
                pass


def test_pid_recording_refuses_lost_or_partial_ownership(tmp_path):
    fleet_run.claim(tmp_path, "owner", [("0x00001000", 8), ("0x00002000", 8)])
    with pytest.raises(fleet_run.ClaimConflict):
        fleet_run.set_pid(tmp_path, "owner", 12345, expected=3)
    with fleet_run.connect(tmp_path) as db:
        assert db.execute("SELECT pid FROM claims WHERE run='owner'").fetchall() == [(None,), (None,)]
    fleet_run.release(tmp_path, "owner", "test")
    with pytest.raises(fleet_run.ClaimConflict):
        fleet_run.set_pid(tmp_path, "owner", 12345, expected=2)


def test_dry_run_does_not_create_coordination_state(tmp_path):
    assert reconcile(tmp_path)["outstanding"] == []
    assert not (tmp_path / "build").exists()


def test_surviving_process_group_keeps_claim_after_direct_child_exits(tmp_path, monkeypatch):
    ledger(tmp_path, (0x1000, 8))
    monkeypatch.setattr(fleet_run, "surviving_group", lambda child: True)
    assert fleet_run.execute(tmp_path, brief(tmp_path, (0x1000, 8)), tmp_path / "work.log",
                             "test", "1", [sys.executable, "-c", "pass"]) == 0
    with fleet_run.connect(tmp_path) as db:
        assert db.execute("SELECT pid FROM claims").fetchone() == (None,)
    assert fleet_run.active_rvas(tmp_path) == {"0x00001000"}
    record = json.loads(next((tmp_path / "build/fleet_runs").glob("*/record.json")).read_text())
    assert record["surviving_group"] is True


def test_file_picker_selection_is_advisory_and_live_run_excludes_file(tmp_path):
    ledger(tmp_path, (0x1000, 8))
    path = log(tmp_path, "")
    script = Path(fleet_run.__file__).parent / "fleet/pick_file.py"
    env = dict(os.environ, PYTHONPATH=str(Path(fleet_run.__file__).parent))
    def pick():
        return subprocess.run([sys.executable, str(script), "1"], cwd=tmp_path,
                              env=env, capture_output=True, text=True, check=True).stdout.strip()
    assert pick() == "Code/gen_asm/test.asm"
    assert pick() == "Code/gen_asm/test.asm"
    assert "seat pick selected" in path.read_text()
    assert eligibility.busy_rvas(tmp_path) == set()
    fleet_run.claim(tmp_path, "live", [("0x00001000", 8)])
    assert pick() == ""
    fleet_run.release(tmp_path, "live", "test")
    assert pick() == "Code/gen_asm/test.asm"


def test_unblock_launcher_routes_through_runner_and_preserves_exit(tmp_path):
    subprocess.run(["git", "init", "-q", str(tmp_path)], check=True)
    source = Path(fleet_run.__file__).parent / "fleet/launch_unblock.sh"
    target = tmp_path / "tools/fleet/launch_unblock.sh"
    target.parent.mkdir(parents=True)
    shutil.copy2(source, target)
    (tmp_path / "build/fleet_logs").mkdir(parents=True)
    (tmp_path / "brief.txt").write_text("TARGETS:\n- 0x00001000 8B body\n")
    stub = tmp_path / "tools/fleet_run.py"
    stub.write_text("import json,sys\nfrom pathlib import Path\n"
                    "Path('build/runner_args.json').write_text(json.dumps(sys.argv[1:]))\n"
                    "sys.exit(7)\n")
    result = subprocess.run(["bash", str(target), "review", "brief.txt"],
                            cwd=tmp_path, capture_output=True, text=True)
    assert result.returncode == 7, result.stderr
    args = json.loads((tmp_path / "build/runner_args.json").read_text())
    assert args[:6] == ["--brief", "brief.txt", "--log", "build/fleet_logs/seat_unblock_review.log",
                        "--engine", "lunablock"]
    assert "--" in args and args[-1] == "-"
    events = (tmp_path / "build/fleet_logs/seats.log").read_text()
    assert "unblock assigned review" in events and "unblock finished review exit=7" in events
