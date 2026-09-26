"""Real-process tests for the Linux fleet containment primitive."""
import json
import os
from pathlib import Path
import signal
import subprocess
import sys
import time
import uuid
from unittest.mock import patch

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
from fleet_cgroup import (  # noqa: E402
    BlockedBootstrap,
    BootstrapError,
    CgroupStateUnavailable,
    CgroupV2Unit,
    ContainmentUnavailable,
    cgroup_populated,
    remove_empty_cgroup,
)


def new_unit():
    try:
        return CgroupV2Unit.create("test-" + uuid.uuid4().hex)
    except ContainmentUnavailable as error:
        pytest.skip(f"host does not delegate writable cgroup-v2 units: {error}")


def test_bootstrap_cannot_exec_until_assigned_and_detached_descendant_keeps_unit(tmp_path):
    unit = new_unit()
    marker = tmp_path / "executed"
    descendant_pid = tmp_path / "descendant.pid"
    descendant_code = (
        "import os,sys,time; "
        f"open({str(descendant_pid)!r}, 'w').write(str(os.getpid())); "
        "time.sleep(.5)"
    )
    worker_code = (
        "import subprocess,sys; "
        f"subprocess.Popen([sys.executable, '-c', {descendant_code!r}], "
        "start_new_session=True, stdin=subprocess.DEVNULL, stdout=subprocess.DEVNULL, "
        "stderr=subprocess.DEVNULL); "
        f"open({str(marker)!r}, 'w').write('started'); "
        "sys.exit(7)"
    )
    bootstrap = None
    try:
        bootstrap = BlockedBootstrap([sys.executable, "-c", worker_code], str(tmp_path),
                                    dict(os.environ), subprocess.DEVNULL,
                                    subprocess.PIPE, subprocess.STDOUT)
        assert not marker.exists()
        assert unit.populated() is False
        unit.attach(bootstrap.child.pid)
        assert unit.populated() is True
        bootstrap.release()
        code = bootstrap.child.wait(timeout=5)
        assert code == 7
        assert marker.read_text() == "started"
        assert descendant_pid.exists()
        # The direct process is gone, but the setsid child remains in this unit.
        assert unit.populated() is True
        with pytest.raises(BootstrapError, match="refusing to abort a released worker"):
            bootstrap.abort()
        assert unit.populated() is True
        unit.wait_empty(timeout=8)
        assert unit.populated() is False
    finally:
        if bootstrap is not None and bootstrap._gate_write is not None:
            bootstrap.abort()
        if unit.populated() is True:
            unit.kill()
            unit.wait_empty(timeout=8)
        assert unit.remove()


def test_cgroup_kill_terminates_a_detached_tree(tmp_path):
    unit = new_unit()
    descendant_pid = tmp_path / "descendant.pid"
    descendant_code = (
        "import os,sys,time; "
        f"open({str(descendant_pid)!r}, 'w').write(str(os.getpid())); "
        "time.sleep(60)"
    )
    worker_code = (
        "import subprocess,sys,time; "
        f"subprocess.Popen([sys.executable, '-c', {descendant_code!r}], "
        "start_new_session=True, stdin=subprocess.DEVNULL, stdout=subprocess.DEVNULL, "
        "stderr=subprocess.DEVNULL); time.sleep(60)"
    )
    bootstrap = None
    timer = None
    try:
        bootstrap = BlockedBootstrap([sys.executable, "-c", worker_code], str(tmp_path),
                                    dict(os.environ), subprocess.DEVNULL,
                                    subprocess.DEVNULL, subprocess.DEVNULL)
        unit.attach(bootstrap.child.pid)
        bootstrap.release()
        deadline = time.monotonic() + 5
        while not descendant_pid.exists() and time.monotonic() < deadline:
            time.sleep(.01)
        assert descendant_pid.exists()
        timer = __import__("threading").Timer(.2, unit.kill)
        timer.start()
        bootstrap.child.wait(timeout=8)
        unit.wait_empty(timeout=8)
        assert unit.populated() is False
    finally:
        if timer is not None:
            timer.cancel()
            timer.join(timeout=2)
        if bootstrap is not None and bootstrap._gate_write is not None:
            bootstrap.abort()
        if unit.populated() is True:
            unit.kill()
            unit.wait_empty(timeout=8)
        assert unit.remove()


def test_persisted_unit_stays_observable_after_supervisor_crash(tmp_path):
    if not sys.platform.startswith("linux"):
        pytest.skip("cgroup-v2 process fixture is Linux-only")
    # The supervisor below creates its own unit; probe first so a Linux host
    # without cgroup-v2 delegation (GitHub runners) skips instead of failing.
    assert new_unit().remove()
    metadata = tmp_path / "run.json"
    descendant_pid_file = tmp_path / "descendant.pid"
    supervisor = tmp_path / "supervisor.py"
    descendant_code = (
        "import os,sys,time; "
        f"open({str(descendant_pid_file)!r}, 'w').write(str(os.getpid())); "
        "time.sleep(30)"
    )
    direct_code = (
        "import subprocess,sys; "
        f"subprocess.Popen([sys.executable, '-c', {descendant_code!r}], "
        "start_new_session=True, stdin=subprocess.DEVNULL, stdout=subprocess.DEVNULL, "
        "stderr=subprocess.DEVNULL)"
    )
    supervisor.write_text(
        "import json,os,subprocess,sys,time,uuid\n"
        f"sys.path.insert(0, {str(TOOLS)!r})\n"
        "from fleet_cgroup import BlockedBootstrap,CgroupV2Unit\n"
        f"unit=CgroupV2Unit.create('test-'+uuid.uuid4().hex)\n"
        f"worker=BlockedBootstrap([sys.executable,'-c',{direct_code!r}],{str(tmp_path)!r},"
        "dict(os.environ),subprocess.DEVNULL,subprocess.DEVNULL,subprocess.DEVNULL)\n"
        "unit.attach(worker.child.pid)\n"
        f"open({str(metadata)!r},'w').write(json.dumps({{'path':str(unit.path),'pid':worker.child.pid}}))\n"
        "worker.release()\n"
        "worker.child.wait()\n"
        "unit.wait_empty()\n",
        encoding="utf-8",
    )
    proc = subprocess.Popen([sys.executable, str(supervisor)], stdout=subprocess.DEVNULL,
                            stderr=subprocess.PIPE)
    path = None
    descendant_pid = None
    try:
        deadline = time.monotonic() + 10
        while time.monotonic() < deadline and not metadata.exists():
            if proc.poll() is not None:
                raise AssertionError(f"supervisor exited early: {proc.stderr.read().decode(errors='replace')}")
            time.sleep(.02)
        assert metadata.exists()
        state = json.loads(metadata.read_text(encoding="utf-8"))
        path = state["path"]
        direct_pid = state["pid"]
        deadline = time.monotonic() + 5
        while time.monotonic() < deadline and not descendant_pid_file.exists():
            time.sleep(.02)
        assert descendant_pid_file.exists()
        descendant_pid = int(descendant_pid_file.read_text(encoding="ascii"))
        deadline = time.monotonic() + 5
        while time.monotonic() < deadline:
            try:
                os.kill(direct_pid, 0)
                alive = True
            except ProcessLookupError:
                alive = False
            if not alive and cgroup_populated(path) is True:
                break
            time.sleep(.02)
        assert cgroup_populated(path) is True
        proc.kill()
        proc.wait(timeout=5)
        assert cgroup_populated(path) is True
    finally:
        if proc.poll() is None:
            proc.kill()
            proc.wait(timeout=5)
        if descendant_pid:
            try:
                os.kill(descendant_pid, signal.SIGKILL)
            except ProcessLookupError:
                pass
        if path and cgroup_populated(path) is True:
            unit = CgroupV2Unit.from_path(path)
            unit.wait_empty(timeout=8)
            run = Path(path).name.removeprefix("bfme-fleet-")
            assert remove_empty_cgroup(path, run)


def test_empty_cgroup_cleanup_fails_closed_for_unknown_state(tmp_path):
    fake = tmp_path / "not-a-cgroup"
    fake.mkdir()
    assert cgroup_populated(fake) is None
    assert not remove_empty_cgroup(fake, "test")
    with pytest.raises(CgroupStateUnavailable):
        CgroupV2Unit.from_path(fake)


def test_empty_cleanup_is_bound_to_the_named_run(tmp_path):
    unit = new_unit()
    run = unit.path.name.removeprefix("bfme-fleet-")
    try:
        assert not remove_empty_cgroup(unit.path, run + "-other")
        assert unit.path.exists()
        observer = CgroupV2Unit.from_path(unit.path)
        with pytest.raises(CgroupStateUnavailable, match="creating supervisor"):
            observer.remove()
        assert remove_empty_cgroup(unit.path, run)
    finally:
        if unit.path.exists():
            assert unit.remove()


def test_release_write_failure_is_not_misclassified_as_blocked(tmp_path):
    if not sys.platform.startswith("linux"):
        pytest.skip("BlockedBootstrap is Linux-only (it refuses to start elsewhere)")
    marker = tmp_path / "executed"
    bootstrap = BlockedBootstrap(
        [sys.executable, "-c", f"open({str(marker)!r}, 'w').write('yes')"],
        str(tmp_path), dict(os.environ), subprocess.DEVNULL,
        subprocess.DEVNULL, subprocess.DEVNULL)
    try:
        with patch("fleet_cgroup.os.write", side_effect=OSError("injected write failure")):
            with pytest.raises(OSError, match="injected write failure"):
                bootstrap.release()
        assert bootstrap._released
        with pytest.raises(BootstrapError, match="refusing to abort a released worker"):
            bootstrap.abort()
        assert bootstrap.child.wait(timeout=5) == 125
        assert not marker.exists()
    finally:
        if bootstrap._gate_write is not None:
            bootstrap.abort()
