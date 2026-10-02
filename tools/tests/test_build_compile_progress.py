"""A long compile prints progress now and then; a short one stays quiet."""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build


def _clock(monkeypatch):
    now = [1000.0]
    monkeypatch.setattr(build.time, "monotonic", lambda: now[0])
    return now


def test_large_compile_reports_start_interval_and_end(monkeypatch, capsys):
    now = _clock(monkeypatch)
    tick = build._compile_progress(250)
    for done in range(1, 251):
        now[0] += 3          # 750 s in all: two interval lines, then the last
        tick()
    lines = capsys.readouterr().out.splitlines()
    assert lines == ["Compile progress: 0/250 TU(s) in 0s",
                     "Compile progress: 100/250 TU(s) in 300s",
                     "Compile progress: 200/250 TU(s) in 600s",
                     "Compile progress: 250/250 TU(s) in 750s"]


def test_small_compile_prints_nothing(monkeypatch, capsys):
    now = _clock(monkeypatch)
    tick = build._compile_progress(build.PROGRESS_MIN_TUS - 1)
    for _ in range(build.PROGRESS_MIN_TUS - 1):
        now[0] += 600
        tick()
    assert capsys.readouterr().out == ""
