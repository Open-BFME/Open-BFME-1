import hashlib
import json
import os
from pathlib import Path
import signal
import sqlite3
import subprocess
import sys
import time
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import worldbuilder_fleet as fleet


@pytest.fixture
def context(tmp_path, monkeypatch):
    monkeypatch.delenv("BFME_TARGET", raising=False)
    monkeypatch.delenv("BFME_TARGET_SHA256", raising=False)
    subprocess.run(["git", "init", "-q", str(tmp_path)], check=True)
    subprocess.run(["git", "-c", "user.name=Test", "-c", "user.email=test@example.invalid",
                    "commit", "-q", "--allow-empty", "-m", "fixture"], cwd=tmp_path, check=True)
    target = SimpleNamespace(root=tmp_path, build_root=tmp_path / "build/worldbuilder",
                             expected_sha256="a" * 64, target_id="worldbuilder",
                             verify_hash=lambda: b"target")
    packets = [{"id": "view-grid", "source": "Code/Tools/WorldBuilder/src/WorldBuilderView.cpp",
                "packet_sha256": "b" * 64},
               {"id": "view-texture", "source": "Code/Tools/WorldBuilder/src/WorldBuilderView.cpp",
                "packet_sha256": "c" * 64},
               {"id": "frame-brush", "source": "Code/Tools/WorldBuilder/src/MainFrm.cpp",
                "packet_sha256": "d" * 64}]
    monkeypatch.setitem(sys.modules, "worldbuilder", SimpleNamespace(open_candidates=lambda _t: packets))
    return target, packets


def active(target):
    db = fleet.database(target)
    try:
        return list(db.execute("SELECT source,run_id FROM claims"))
    finally:
        db.close()


def test_claim_owns_family_and_conflicts_with_another_body(context):
    target, _ = context
    brief = fleet.claim(target, "view-grid", "first")
    assert len(brief["candidates"]) == 2
    with pytest.raises(sqlite3.IntegrityError):
        fleet.claim(target, "view-texture", "second")
    assert len(active(target)) == 1
    fleet.claim(target, "frame-brush", "third")
    assert len(active(target)) == 2


def test_stale_packet_does_not_claim_or_create_run(context):
    target, _ = context
    with pytest.raises(ValueError, match="stale packet"):
        fleet.claim(target, "view-grid", "stale", "f" * 64)
    assert not active(target)
    assert not fleet.run_path(target, "stale").exists()


def test_wrong_binary_fails_before_any_write(context):
    target, _ = context
    def changed():
        raise ValueError("SHA-256 mismatch")
    target.verify_hash = changed
    with pytest.raises(ValueError, match="SHA-256"):
        fleet.claim(target, "view-grid", "wrong-image")
    assert not target.build_root.exists()


def test_shared_game_source_is_not_editable_by_pilot(context):
    target, packets = context
    packets[0]["source"] = "Code/GameEngine/Common/Shared.cpp"
    with pytest.raises(ValueError, match="shared engine donors are read-only"):
        fleet.claim(target, "view-grid", "shared")
    assert not target.build_root.exists()


def test_completed_run_is_immutable_and_claim_can_be_released(context):
    target, _ = context
    fleet.claim(target, "view-grid", "once")
    brief = (fleet.run_path(target, "once") / "brief.json").read_bytes()
    fleet.release(target, "once", "worker completed")
    assert not active(target)
    with pytest.raises(FileExistsError):
        fleet.claim(target, "view-grid", "once")
    assert not active(target)
    assert (fleet.run_path(target, "once") / "brief.json").read_bytes() == brief


@pytest.mark.skipif(os.name != "posix", reason="run requires POSIX process groups")
def test_failed_worker_records_exit_code_and_releases(context):
    target, _ = context
    result = fleet.run(target, "view-grid", "failure", [sys.executable, "-c", "print('diagnostic');raise SystemExit(7)"])
    assert result["exit_code"] == 7
    assert not active(target)
    directory = fleet.run_path(target, "failure")
    assert "diagnostic" in (directory / "worker.log").read_text()
    assert json.loads((directory / "result.json").read_text())["exit_code"] == 7


@pytest.mark.skipif(os.name != "posix", reason="run requires POSIX process groups")
def test_missing_worker_command_records_failure_and_releases(context):
    target, _ = context
    with pytest.raises(FileNotFoundError):
        fleet.run(target, "view-grid", "missing", [str(target.root / "absent-executable")])
    assert not active(target)
    result = json.loads((fleet.run_path(target, "missing") / "result.json").read_text())
    assert "FileNotFoundError" in result["error"]


@pytest.mark.skipif(os.name != "posix", reason="run requires POSIX process groups")
def test_worker_receives_exact_target_context(context):
    target, _ = context
    result = fleet.run(target, "view-grid", "context", [sys.executable, "-c",
          "import os;print(os.environ['BFME_TARGET']);print(os.environ['BFME_TARGET_SHA256']);print(os.environ['BFME_RUN_ID'])"])
    assert result["exit_code"] == 0
    assert (fleet.run_path(target, "context") / "worker.log").read_text().splitlines() == ["worldbuilder", "a" * 64, "context"]


def test_distinct_git_worktrees_share_source_claims(context, tmp_path):
    target, _ = context
    other_root = tmp_path / "other-worktree"
    subprocess.run(["git", "worktree", "add", "-q", "-b", "other", str(other_root)],
                   cwd=target.root, check=True)
    other = SimpleNamespace(**dict(vars(target), root=other_root,
                                   build_root=other_root / "build/worldbuilder"))
    fleet.claim(target, "view-grid", "first-worktree")
    with pytest.raises(sqlite3.IntegrityError):
        fleet.claim(other, "view-texture", "second-worktree")
    assert active(other) == active(target)
    with pytest.raises(ValueError, match="release it from that worktree"):
        fleet.release(other, "first-worktree", "wrong checkout")
    assert not fleet.run_path(other, "first-worktree").exists()
    assert not (fleet.run_path(target, "first-worktree") / "release.json").exists()
    fleet.claim(other, "frame-brush", "other-source")
    assert len(active(target)) == 2
    fleet.release(target, "first-worktree", "operator completed first source")
    fleet.release(other, "other-source", "operator completed other source")


@pytest.mark.parametrize("key,value", [("BFME_TARGET", "game"), ("BFME_TARGET_SHA256", "f" * 64)])
def test_wrong_caller_target_fails_before_writes(context, monkeypatch, key, value):
    target, _ = context
    monkeypatch.setenv(key, value)
    with pytest.raises(ValueError, match=key):
        fleet.run(target, "view-grid", "wrong-environment", [sys.executable, "-c", "pass"])
    assert not target.build_root.exists()
    assert not (target.root / ".git/fleet").exists()


def test_windows_requires_external_supervision_before_claiming(context, monkeypatch):
    target, _ = context
    monkeypatch.setattr(sys, "platform", "win32")
    with pytest.raises(ValueError, match="externally supervised"):
        fleet.run(target, "view-grid", "windows", [sys.executable, "-c", "pass"])
    assert not target.build_root.exists()
    assert not (target.root / ".git/fleet").exists()


@pytest.mark.skipif(os.name != "posix", reason="run requires POSIX process groups")
def test_exited_worker_descendants_stop_before_release(context, monkeypatch):
    target, _ = context
    release = fleet.release
    def checked_release(actual, run_id, reason):
        process = json.loads((fleet.run_path(actual, run_id) / "process.json").read_text())
        assert not fleet.group_running(process["pid"])
        release(actual, run_id, reason)
    monkeypatch.setattr(fleet, "release", checked_release)
    command = [sys.executable, "-c",
               "import subprocess,sys;subprocess.Popen([sys.executable,'-c','import time;time.sleep(60)'])"]
    result = fleet.run(target, "view-grid", "descendant", command)
    assert result["exit_code"] == 0
    assert not active(target)


@pytest.mark.skipif(os.name != "posix", reason="run requires POSIX process groups")
def test_process_metadata_failure_stops_worker_before_release(context, monkeypatch):
    target, _ = context
    write = Path.write_text
    def fail_process_metadata(path, *args, **kwargs):
        if path.name == "process.json":
            raise OSError("cannot write process metadata")
        return write(path, *args, **kwargs)
    monkeypatch.setattr(Path, "write_text", fail_process_metadata)
    with pytest.raises(OSError, match="process metadata"):
        fleet.run(target, "view-grid", "metadata-failure",
                  [sys.executable, "-c", "import time;time.sleep(60)"])
    result = json.loads((fleet.run_path(target, "metadata-failure") / "result.json").read_text())
    assert not fleet.group_running(result["pid"])
    assert not active(target)


def launch_supervised_worker(target, packets, run_id):
    marker = target.root / (run_id + "-child-ready")
    worker = ("import pathlib,subprocess,sys,time;"
              "subprocess.Popen([sys.executable,'-c','import time;time.sleep(60)']);"
              f"pathlib.Path({str(marker)!r}).touch();time.sleep(60)")
    wrapper = (f"import sys;sys.path.insert(0,{str(Path(fleet.__file__).parent)!r});"
               "from pathlib import Path;from types import SimpleNamespace;"
               "import worldbuilder_fleet as f;"
               f"target=SimpleNamespace(root=Path({str(target.root)!r}),"
               f"build_root=Path({str(target.build_root)!r}),"
               f"target_id='worldbuilder',expected_sha256={'a' * 64!r},verify_hash=lambda:b'target');"
               f"sys.modules['worldbuilder']=SimpleNamespace(open_candidates=lambda t:{packets!r});"
               f"f.run(target,'view-grid',{run_id!r},[sys.executable,'-c',{worker!r}])")
    process = subprocess.Popen([sys.executable, "-c", wrapper], stdout=subprocess.PIPE,
                               stderr=subprocess.PIPE, text=True)
    deadline = time.monotonic() + 10
    while not marker.exists() and process.poll() is None and time.monotonic() < deadline:
        time.sleep(0.02)
    if not marker.exists():
        process.kill()
        _, stderr = process.communicate()
        pytest.fail(f"supervised worker failed to start: {stderr}")
    return process


@pytest.mark.skipif(os.name != "posix", reason="run requires POSIX process groups")
@pytest.mark.parametrize("signum", [signal.SIGTERM, getattr(signal, "SIGKILL", 9)])
def test_signal_cleanup_and_uncatchable_crash_retention(context, signum):
    target, packets = context
    run_id = "signal-" + str(signum)
    process = launch_supervised_worker(target, packets, run_id)
    directory = fleet.run_path(target, run_id)
    worker_pid = json.loads((directory / "process.json").read_text())["pid"]
    try:
        process.send_signal(signum)
        process.communicate(timeout=15)
        if signum == signal.SIGTERM:
            assert not fleet.group_running(worker_pid)
            assert not active(target)
            result = json.loads((directory / "result.json").read_text())
            assert "WorkerInterrupted" in result["error"]
        else:
            assert fleet.group_running(worker_pid)
            assert active(target)
            assert not (directory / "release.json").exists()
    finally:
        if process.poll() is None:
            process.kill()
            process.communicate()
        try:
            os.killpg(worker_pid, signal.SIGKILL)
        except ProcessLookupError:
            pass
        if active(target):
            fleet.release(target, run_id, "operator killed the abandoned worker process group")


@pytest.mark.skipif(os.name != "posix", reason="run requires POSIX process groups")
def test_uncertain_cleanup_retains_claim(context, monkeypatch):
    target, _ = context
    stop = fleet.stop_worker_group
    def uncertain(process):
        stop(process)
        raise ValueError("cannot establish worker liveness")
    monkeypatch.setattr(fleet, "stop_worker_group", uncertain)
    with pytest.raises(ValueError, match="worker liveness"):
        fleet.run(target, "view-grid", "uncertain", [sys.executable, "-c", "pass"])
    assert active(target)
    result = json.loads((fleet.run_path(target, "uncertain") / "result.json").read_text())
    assert "worker liveness" in result["cleanup_error"]
    fleet.release(target, "uncertain", "operator independently confirmed worker stopped")


@pytest.mark.parametrize("run_id", ["../outside", "/absolute", "", "x/y"])
def test_run_path_cannot_escape(context, run_id):
    target, _ = context
    with pytest.raises(ValueError):
        fleet.run_path(target, run_id)
