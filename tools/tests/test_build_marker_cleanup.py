"""A full build clears the markers dead builds left behind, on every host.

The cleanup asked `os.kill(pid, 0)` and cleared a marker on ProcessLookupError.
On Windows that call raises a plain OSError for a dead pid, so no marker was
ever cleared there and tools/object_cache.py kept answering "unknown".
build.pid_alive asks the kernel on Windows and keeps the signal test elsewhere.
"""
import os
import subprocess
import sys
import time
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build

DEAD = 999999


def test_three_answers():
    assert build.pid_alive(os.getpid()) is True
    assert build.pid_alive(DEAD) is False


def test_a_process_that_has_exited_is_dead():
    child = subprocess.Popen([sys.executable, "-c", "pass"])
    child.wait()
    time.sleep(0.2)
    # Popen still holds the handle on Windows, so the pid is not reused yet and
    # the kernel reports an exit code instead of STILL_ACTIVE.
    assert build.pid_alive(child.pid) is False


def test_full_build_clears_dead_markers_and_keeps_live_ones(monkeypatch, tmp_path):
    monkeypatch.setattr(build, "INFLIGHT_DIR", tmp_path)
    monkeypatch.setattr(build, "main", lambda argv: None)
    live = subprocess.Popen([sys.executable, "-c", "import time; time.sleep(30)"])
    try:
        (tmp_path / str(DEAD)).write_text("dead build\n")
        (tmp_path / str(live.pid)).write_text("a build running beside this one\n")
        (tmp_path / "notes.txt").write_text("not a marker\n")
        build.run_marked([])
        assert not (tmp_path / str(DEAD)).exists()
        assert (tmp_path / str(live.pid)).exists()
        assert (tmp_path / "notes.txt").exists()
        assert not (tmp_path / str(os.getpid())).exists(), "own marker is removed on the way out"
    finally:
        live.kill()
        live.wait()


def test_a_scoped_build_clears_nothing(monkeypatch, tmp_path):
    monkeypatch.setattr(build, "INFLIGHT_DIR", tmp_path)
    monkeypatch.setattr(build, "main", lambda argv: None)
    (tmp_path / str(DEAD)).write_text("dead build\n")
    build.run_marked(["Code/Some.cpp"])
    assert (tmp_path / str(DEAD)).exists()
