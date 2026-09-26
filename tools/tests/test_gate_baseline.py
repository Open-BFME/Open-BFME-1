#!/usr/bin/env python3
"""The full-gate baseline: new reds fail, known reds pass, the file only shrinks,
and a gate that never reached byte comparison proves nothing."""
import io
import sys
from contextlib import redirect_stdout, redirect_stderr
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import gate_baseline as gb  # noqa: E402

GATE_OK_SHAPE = """Compile: 3 of 3 TU(s)
  FAIL ?foo@@YAXXZ (game/GameEngine/Source/Common/Foo.cpp)
  FAIL ??1Bar@@QAE@XZ (game/Libraries/Source/WWVegas/WWLib/bar.cpp)
Functions: FAIL 2/100
DIR32 consistency: FAIL 3 NEW inconsistent symbol(s)
"""
GATE_DIED = """Compile: 1 of 3 TU(s)
compile failed: game/GameEngine/Source/Common/T3Atl.cpp
"""


def run(fn, *args):
    out, err = io.StringIO(), io.StringIO()
    with redirect_stdout(out), redirect_stderr(err):
        code = fn(*args)
    return code, out.getvalue()


def test_red_rows_parse_and_died_detection():
    assert gb.red_rows(GATE_OK_SHAPE) == [
        "??1Bar@@QAE@XZ (game/Libraries/Source/WWVegas/WWLib/bar.cpp)",
        "?foo@@YAXXZ (game/GameEngine/Source/Common/Foo.cpp)"]
    assert gb.red_rows(GATE_DIED) is None
    assert gb.red_rows("Functions: OK 5/5\n") == []


def test_check_passes_known_reds_and_fails_new_ones():
    baseline = gb.red_rows(GATE_OK_SHAPE)
    code, out = run(gb.check, GATE_OK_SHAPE, baseline)
    assert code == 0 and "0 NEW" in out
    worse = GATE_OK_SHAPE.replace("Functions:", "  FAIL ?new@@YAXXZ (game/X.cpp)\nFunctions:")
    code, out = run(gb.check, worse, baseline)
    assert code == 1 and "NEW RED ?new@@YAXXZ (game/X.cpp)" in out
    better = GATE_OK_SHAPE.replace("  FAIL ?foo@@YAXXZ (game/GameEngine/Source/Common/Foo.cpp)\n", "")
    code, out = run(gb.check, better, baseline)
    assert code == 0 and "now green" in out and "?foo@@YAXXZ" in out


def test_dead_gate_never_passes_or_records(tmp_path):
    code, _ = run(gb.check, GATE_DIED, [])
    assert code == 2
    code, _ = run(gb.check, GATE_DIED, None)
    assert code == 2


def test_no_baseline_is_strict():
    code, out = run(gb.check, GATE_OK_SHAPE, None)
    assert code == 1 and "no baseline recorded" in out
    code, _ = run(gb.check, "Functions: OK 5/5\n", None)
    assert code == 0


def test_baseline_round_trip(tmp_path):
    path = tmp_path / "b.txt"
    rows = gb.red_rows(GATE_OK_SHAPE)
    gb.write_baseline(rows, path)
    assert gb.load_baseline(path) == rows
    assert gb.parse_baseline("# comment\n\n a (b) \n") == ["a (b)"]


@pytest.mark.parametrize("exit_code", [0, 7])
def test_run_gate_forwards_output_before_child_exits_and_captures_everything(
        monkeypatch, tmp_path, exit_code):
    acknowledged = tmp_path / "progress-seen"

    class LiveOutput(io.StringIO):
        def flush(self):
            super().flush()
            if "Compile: started\n" in self.getvalue():
                acknowledged.touch()

    child = """
import pathlib, sys, time
print("Compile: started")
deadline = time.monotonic() + 2
while not pathlib.Path(sys.argv[1]).exists():
    if time.monotonic() > deadline:
        raise SystemExit("parent did not forward progress before completion")
    time.sleep(0.01)
print("compiler diagnostic", file=sys.stderr)
print("Functions: OK 1/1")
sys.stdout.write("final partial line")
sys.exit(int(sys.argv[2]))
"""
    monkeypatch.setattr(gb, "ROOT", tmp_path)
    monkeypatch.setattr(gb, "gate_command", lambda: [
        sys.executable, "-c", child, str(acknowledged), str(exit_code)])
    monkeypatch.delenv("PYTHONUNBUFFERED", raising=False)
    forwarded = LiveOutput()
    with redirect_stdout(forwarded):
        status, captured = gb.run_gate()

    assert status == exit_code
    assert acknowledged.exists()
    assert captured == forwarded.getvalue() == (
        "Compile: started\ncompiler diagnostic\nFunctions: OK 1/1\nfinal partial line")
