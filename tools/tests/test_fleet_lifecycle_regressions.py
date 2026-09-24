"""The runner owns only launched brief targets; ownerless log picks are legacy."""
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import time
import uuid

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import eligibility  # noqa: E402
import fleet_cgroup  # noqa: E402
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


def require_cgroup_v2():
    try:
        unit = fleet_cgroup.CgroupV2Unit.create("test-" + uuid.uuid4().hex)
    except fleet_cgroup.ContainmentUnavailable as error:
        pytest.skip(f"host does not delegate writable cgroup-v2 units: {error}")
    assert unit.remove()


def release_legacy_after_stop(root, run, reason="test operator stop"):
    report = fleet_run.coordination_status(root)
    return fleet_run.release(root, run, reason, stopped_fleet=True,
                             expected_state_sha=report["snapshot_sha256"])


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
    release_legacy_after_stop(tmp_path, "newer")
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
    release_legacy_after_stop(tmp_path, "live")
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
    require_cgroup_v2()
    if os.name != "posix":
        pytest.skip("this detached-descendant fixture uses POSIX process startup")
    ledger(tmp_path, (0x1000, 8))
    brief_path = brief(tmp_path, (0x1000, 8))
    descendant_pid_path = tmp_path / "descendant.pid"
    child_code = (
        "import os,time; "
        f"open({str(descendant_pid_path)!r},'w').write(str(os.getpid())); "
        "time.sleep(30)"
    )
    worker_code = (
        "import subprocess,sys\n"
        f"child_code={child_code!r}\n"
        "subprocess.Popen([sys.executable,'-c',child_code],start_new_session=True,"
        "stdin=subprocess.DEVNULL,stdout=subprocess.DEVNULL,stderr=subprocess.DEVNULL)\n"
    )
    runner_path = tmp_path / "runner.py"
    runner_path.write_text(
        "import sys\nfrom pathlib import Path\n"
        f"sys.path.insert(0, {str(Path(fleet_run.__file__).parent)!r})\n"
        "import fleet_run\n"
        f"root=Path({str(tmp_path)!r})\n"
        f"fleet_run.execute(root, {str(brief_path)!r}, root/'worker.log', 'test', 'crash', "
        f"[sys.executable, '-c', {worker_code!r}, {str(descendant_pid_path)!r}])\n",
        encoding="utf-8",
    )
    supervisor = subprocess.Popen([sys.executable, str(runner_path)], cwd=tmp_path,
                                  stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    direct_pid = descendant_pid = None
    try:
        deadline = time.monotonic() + 10
        while time.monotonic() < deadline and not descendant_pid_path.exists():
            time.sleep(.02)
        assert descendant_pid_path.exists()
        descendant_pid = int(descendant_pid_path.read_text(encoding="ascii"))

        # Wait until the PID and containment unit are committed; then kill the
        # supervisor while it waits for its detached child to finish.
        deadline = time.monotonic() + 5
        while time.monotonic() < deadline:
            with fleet_run.connect(tmp_path) as db:
                owner = db.execute(
                    "SELECT run,pid,cgroup_path FROM claims WHERE rva='0x00001000'").fetchone()
            if owner and owner[1] and owner[2]:
                run, direct_pid, cgroup_path = owner
                break
            time.sleep(.02)
        else:
            raise AssertionError("runner did not persist the worker PID and cgroup")

        deadline = time.monotonic() + 5
        while fleet_run.pid_alive(direct_pid) and time.monotonic() < deadline:
            time.sleep(.02)
        assert not fleet_run.pid_alive(direct_pid)
        assert fleet_run.cgroup_state(cgroup_path, run) is True

        supervisor.kill()
        supervisor.wait(timeout=5)
        assert fleet_run.pid_alive(descendant_pid)

        with fleet_run.connect(tmp_path) as db:
            db.execute("UPDATE claims SET expires=? WHERE run=?", (time.time() - 1, run))
            db.commit()
        assert eligibility.busy_rvas(tmp_path) == {"0x00001000"}
        with pytest.raises(fleet_run.ClaimConflict):
            fleet_run.claim(tmp_path, "replacement", [("0x00001000", 8)])

        os.kill(descendant_pid, 9)
        deadline = time.monotonic() + 8
        while time.monotonic() < deadline and fleet_run.cgroup_state(cgroup_path, run) is not False:
            time.sleep(.02)
        assert fleet_run.cgroup_state(cgroup_path, run) is False
        assert fleet_run.active_rvas(tmp_path) == set()
        fleet_run.claim(tmp_path, "replacement", [("0x00001000", 8)])
        release_legacy_after_stop(tmp_path, "replacement")
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
        if "cgroup_path" in locals() and fleet_run.cgroup_state(cgroup_path, run) is False:
            fleet_cgroup.remove_empty_cgroup(
                cgroup_path, Path(cgroup_path).name.removeprefix("bfme-fleet-"))


def test_crash_after_popen_before_attach_leaves_only_inert_bootstrap(tmp_path):
    if not sys.platform.startswith("linux"):
        pytest.skip("the blocked bootstrap is Linux-only")
    ledger(tmp_path, (0x1000, 8))
    run = "gap-" + uuid.uuid4().hex
    try:
        unit = fleet_cgroup.CgroupV2Unit.create(run)
    except fleet_cgroup.ContainmentUnavailable as error:
        pytest.skip(f"host does not delegate writable cgroup-v2 units: {error}")
    fleet_run.connect(tmp_path).close()
    run_dir = tmp_path / "build/fleet_runs" / run
    run_dir.mkdir(parents=True)
    (run_dir / "record.json").write_text(
        json.dumps({"id": run, "status": "starting", "targets": [["0x00001000", 8]],
                    "cgroup_path": str(unit.path), "cgroup_empty_verified": False,
                    "touch_tracking": True, "launch_phase": "preexec"}),
        encoding="utf-8")
    fleet_run.claim(tmp_path, run, [("0x00001000", 8)], lease=60,
                    cgroup_path=str(unit.path))
    marker = tmp_path / "must-not-execute"
    child_pid_file = tmp_path / "bootstrap.pid"
    script = tmp_path / "crash-before-attach.py"
    target_code = f"from pathlib import Path; Path({str(marker)!r}).touch()"
    script.write_text(
        "import os,subprocess,sys\n"
        f"sys.path.insert(0, {str(Path(fleet_run.__file__).parent)!r})\n"
        "from fleet_cgroup import BlockedBootstrap\n"
        f"worker=BlockedBootstrap([sys.executable,'-c',{target_code!r}],{str(tmp_path)!r},"
        "dict(os.environ),subprocess.DEVNULL,subprocess.DEVNULL,subprocess.DEVNULL)\n"
        f"open({str(child_pid_file)!r},'w').write(str(worker.child.pid))\n"
        "os._exit(0)\n",
        encoding="utf-8",
    )
    supervisor = subprocess.Popen([sys.executable, str(script)], cwd=tmp_path,
                                  stdout=subprocess.DEVNULL, stderr=subprocess.PIPE)
    bootstrap_pid = None
    try:
        supervisor.communicate(timeout=10)
        assert supervisor.returncode == 0
        bootstrap_pid = int(child_pid_file.read_text(encoding="ascii"))
        deadline = time.monotonic() + 5
        while fleet_run.pid_alive(bootstrap_pid) and time.monotonic() < deadline:
            time.sleep(.02)
        time.sleep(.1)
        assert not marker.exists()
        assert unit.populated() is False
        # The persisted claim remains busy during its lease even though this
        # pre-attach bootstrap could never execute the workload.
        assert fleet_run.active_rvas(tmp_path) == {"0x00001000"}
        with fleet_run.connect(tmp_path) as db:
            db.execute("UPDATE claims SET expires=? WHERE run=?", (time.time() - 1, run))
            db.commit()
        assert fleet_run.active_rvas(tmp_path) == set()
        fleet_run.claim(tmp_path, "after-inert-bootstrap", [("0x00001000", 8)])
        release_legacy_after_stop(tmp_path, "after-inert-bootstrap")
    finally:
        if supervisor.poll() is None:
            supervisor.kill()
            supervisor.wait(timeout=5)
        if bootstrap_pid and fleet_run.pid_alive(bootstrap_pid):
            try:
                os.kill(bootstrap_pid, 9)
            except ProcessLookupError:
                pass
        if unit.populated() is True:
            unit.kill()
            unit.wait_empty(timeout=5)
        if unit.populated() is False:
            unit.remove()


def test_fast_nonzero_exit_waits_for_detached_late_touch(tmp_path):
    require_cgroup_v2()
    ledger(tmp_path, (0x1000, 8), (0x2000, 8))
    descendant_code = (
        "import sys,time; time.sleep(.25); "
        f"sys.path.insert(0, {str(Path(fleet_run.__file__).parent)!r}); "
        "import fleet_run; fleet_run.mark_touched(0x1000)"
    )
    direct_code = (
        "import subprocess,sys; "
        f"subprocess.Popen([sys.executable,'-c',{descendant_code!r}],"
        "start_new_session=True,stdin=subprocess.DEVNULL,stdout=subprocess.DEVNULL,"
        "stderr=subprocess.DEVNULL); sys.exit(7)"
    )
    result = fleet_run.execute(tmp_path,
                               brief(tmp_path, (0x1000, 8), (0x2000, 8)),
                               tmp_path / "work.log", "test", "late-touch",
                               [sys.executable, "-c", direct_code])
    assert result == 7
    record = json.loads(next((tmp_path / "build/fleet_runs").glob("*/record.json")).read_text())
    assert record["status"] == "finished"
    assert record["touched"] == ["0x00001000"]
    assert record["cgroup_empty_verified"] is True
    assert fleet_run.active_rvas(tmp_path) == set()
    assert eligibility.recent_run_rvas(root=tmp_path) == {"0x00001000"}


def test_cgroup_timeout_kills_detached_descendant(tmp_path):
    require_cgroup_v2()
    ledger(tmp_path, (0x1000, 8))
    descendant_pid_path = tmp_path / "timeout-descendant.pid"
    descendant_code = (
        "import os,time; "
        f"open({str(descendant_pid_path)!r},'w').write(str(os.getpid())); "
        "time.sleep(60)"
    )
    direct_code = (
        "import subprocess,sys,time; "
        f"subprocess.Popen([sys.executable,'-c',{descendant_code!r}],"
        "start_new_session=True,stdin=subprocess.DEVNULL,stdout=subprocess.DEVNULL,"
        "stderr=subprocess.DEVNULL); time.sleep(60)"
    )
    result = fleet_run.execute(tmp_path, brief(tmp_path, (0x1000, 8)),
                               tmp_path / "work.log", "test", "timeout",
                               ["timeout", "1s", sys.executable, "-c", direct_code])
    assert result != 0
    assert descendant_pid_path.exists()
    record = json.loads(next((tmp_path / "build/fleet_runs").glob("*/record.json")).read_text())
    assert record["timed_out"] is True
    assert record["cgroup_empty_verified"] is True
    assert fleet_run.active_rvas(tmp_path) == set()


def test_containment_unavailable_fails_before_worker_or_claim(tmp_path, monkeypatch):
    ledger(tmp_path, (0x1000, 8))
    path = brief(tmp_path, (0x1000, 8))
    started = tmp_path / "worker-started"

    def unavailable(run):
        raise fleet_cgroup.ContainmentUnavailable("test no delegated cgroup")

    monkeypatch.setattr(fleet_cgroup.CgroupV2Unit, "create", unavailable)
    with pytest.raises(fleet_cgroup.ContainmentUnavailable, match="no delegated cgroup"):
        fleet_run.execute(tmp_path, path, tmp_path / "pointer", "test", "1",
                          [sys.executable, "-c", f"open({str(started)!r},'w').write('x')"])
    assert not started.exists()
    assert not (tmp_path / "pointer").exists()
    assert list((tmp_path / "build/fleet_runs").glob("*/record.json")) == []
    assert fleet_run.active_rvas(tmp_path) == set()


def test_bootstrap_sanitizes_startup_environment_until_cgroup_attach(tmp_path, monkeypatch):
    require_cgroup_v2()
    if not sys.platform.startswith("linux"):
        pytest.skip("the blocked bootstrap is Linux-only")
    ledger(tmp_path, (0x1000, 8))
    site_dir = tmp_path / "worker-site"
    site_dir.mkdir()
    marker = tmp_path / "sitecustomize-ran"
    (site_dir / "sitecustomize.py").write_text(
        f"from pathlib import Path; Path({str(marker)!r}).touch()\n", encoding="utf-8")
    monkeypatch.setenv("PYTHONPATH", str(site_dir))
    monkeypatch.setenv("LD_PRELOAD", str(tmp_path / "must-not-load-in-bootstrap.so"))

    original_attach = fleet_cgroup.CgroupV2Unit.attach
    real_popen = subprocess.Popen
    bootstrap_envs = []

    def observe_popen(args, *positional, **kwargs):
        if args and args[0] == sys.executable and "-I" in args:
            bootstrap_envs.append(kwargs.get("env"))
        return real_popen(args, *positional, **kwargs)

    def check_before_gate(unit, pid, timeout=5.0):
        assert not marker.exists(), "worker-controlled Python startup ran before cgroup attach"
        result = original_attach(unit, pid, timeout)
        assert not marker.exists(), "worker-controlled startup ran before the release gate"
        return result

    monkeypatch.setattr(fleet_cgroup.subprocess, "Popen", observe_popen)
    monkeypatch.setattr(fleet_cgroup.CgroupV2Unit, "attach", check_before_gate)
    assert fleet_run.execute(tmp_path, brief(tmp_path, (0x1000, 8)),
                             tmp_path / "worker.log", "test", "startup-env",
                             [sys.executable, "-c", "pass"]) == 0
    assert bootstrap_envs == [{}]
    assert marker.exists(), "the post-gate worker did not receive its original PYTHONPATH"


def test_missing_worker_executable_releases_empty_claim_without_ghost(tmp_path):
    ledger(tmp_path, (0x1000, 8))
    with pytest.raises(FileNotFoundError, match="worker executable not found"):
        fleet_run.execute(tmp_path, brief(tmp_path, (0x1000, 8)),
                          tmp_path / "worker.log", "test", "missing-executable",
                          ["no-such-fleet-worker-executable", "arg"])
    assert fleet_run.active_rvas(tmp_path) == set()
    with fleet_run.connect(tmp_path) as db:
        assert db.execute("SELECT rva FROM claims").fetchall() == []
    record = json.loads(next((tmp_path / "build/fleet_runs").glob("*/record.json")).read_text())
    assert record["status"] == "failed"
    assert record["cgroup_empty_verified"] is True


def test_pid_recording_refuses_lost_or_partial_ownership(tmp_path):
    fleet_run.claim(tmp_path, "owner", [("0x00001000", 8), ("0x00002000", 8)])
    with pytest.raises(fleet_run.ClaimConflict):
        fleet_run.set_pid(tmp_path, "owner", 12345, expected=3)
    with fleet_run.connect(tmp_path) as db:
        assert db.execute("SELECT pid FROM claims WHERE run='owner'").fetchall() == [(None,), (None,)]
    release_legacy_after_stop(tmp_path, "owner")
    with pytest.raises(fleet_run.ClaimConflict):
        fleet_run.set_pid(tmp_path, "owner", 12345, expected=2)


def test_dry_run_does_not_create_coordination_state(tmp_path):
    assert reconcile(tmp_path)["outstanding"] == []
    assert not (tmp_path / "build").exists()


def test_unreadable_cgroup_keeps_claim_and_blocks_named_release(tmp_path, monkeypatch):
    run = "unknown-unit"
    cgroup_path = f"/unknown/bfme-fleet-{run}"
    fleet_run.claim(tmp_path, run, [("0x00001000", 8)],
                    pid=12345, lease=-1, cgroup_path=cgroup_path)
    record = tmp_path / "build/fleet_runs" / run
    record.mkdir(parents=True)
    (record / "record.json").write_text(json.dumps({
        "id": run, "status": "running", "pid": 12345,
        "cgroup_path": cgroup_path,
    }), encoding="utf-8")
    monkeypatch.setattr(fleet_run, "cgroup_state", lambda path, run=None: None)
    assert fleet_run.active_rvas(tmp_path) == {"0x00001000"}
    with pytest.raises(fleet_run.ClaimConflict, match="populated or unknown"):
        fleet_run.release(tmp_path, "unknown-unit", "test")
    assert fleet_run.active_rvas(tmp_path) == {"0x00001000"}


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
    release_legacy_after_stop(tmp_path, "live")
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
