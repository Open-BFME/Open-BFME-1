#!/usr/bin/env python3
"""The full-gate baseline: new reds fail, known reds pass, the file only shrinks,
and a gate that never reached byte comparison proves nothing."""
import io
import sys
import threading
import time
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
FULL GATE: FAIL — 2 red: functions, dir32 consistency
"""
GATE_OK = "Functions: OK 5/5\n\nFULL GATE: OK \u2014 every check green\n"
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


def test_unchanged_function_failures_report_other_full_gate_failures():
    transcript = (GATE_OK_SHAPE +
                  "No-op patch: FAIL not run — verify_functions did not produce a patch set\n"
                  "FULL GATE: FAIL — 3 red: functions, dir32 consistency, no-op patch (unrunnable)\n")
    baseline = gb.red_rows(GATE_OK_SHAPE)
    code, out = run(gb.check, transcript, baseline)
    assert code == 0
    assert "function failure rows: 2 red now, 2 in baseline, 0 NEW" in out
    assert "does not establish that all checks passed" in out
    assert "raw FULL GATE: FAIL — 3 red: functions, dir32 consistency, no-op patch (unrunnable)" in out

    worse = transcript.replace("Functions:", "  FAIL ?new@@YAXXZ (game/X.cpp)\nFunctions:")
    code, out = run(gb.check, worse, baseline)
    assert code == 1
    assert "NEW RED ?new@@YAXXZ (game/X.cpp)" in out
    assert "raw FULL GATE: FAIL" in out


def test_dead_gate_never_passes_or_records(tmp_path):
    code, _ = run(gb.check, GATE_DIED, [])
    assert code == 2
    code, _ = run(gb.check, GATE_DIED, None)
    assert code == 2


def test_no_baseline_is_strict():
    code, out = run(gb.check, GATE_OK_SHAPE, None)
    assert code == 1 and "no baseline recorded" in out
    code, _ = run(gb.check, GATE_OK, None)
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


GATE_RED_DIR32 = GATE_OK_SHAPE + "\nFULL GATE: FAIL — 3 red: functions, dir32 consistency, no-op patch (unrunnable)\n"
DIR32_REPORT = "??_7A@@6B@\t0x1,0x2\n??_7B@@6B@\t0x3,0x4\n"
KNOWN_ROWS = ["??1Bar@@QAE@XZ (game/Libraries/Source/WWVegas/WWLib/bar.cpp)",
              "?foo@@YAXXZ (game/GameEngine/Source/Common/Foo.cpp)"]


def test_known_dir32_symbols_pass_and_a_new_one_fails():
    assert run(gb.check, GATE_RED_DIR32, KNOWN_ROWS, ["??_7A@@6B@", "??_7B@@6B@"], DIR32_REPORT)[0] == 0
    code, out = run(gb.check, GATE_RED_DIR32, KNOWN_ROWS, ["??_7A@@6B@"], DIR32_REPORT)
    assert code == 1 and "NEW DIR32 ??_7B@@6B@" in out


def test_a_fixed_dir32_symbol_is_named_for_removal():
    code, out = run(gb.check, GATE_RED_DIR32, KNOWN_ROWS, ["??_7A@@6B@", "??_7B@@6B@", "??_7C@@6B@"], DIR32_REPORT)
    assert code == 0 and "now consistent" in out and "??_7C@@6B@" in out


def test_red_dir32_without_its_report_fails_closed():
    code, out = run(gb.check, GATE_RED_DIR32, KNOWN_ROWS, [], None)
    assert code == 1 and "was not written" in out


def test_a_red_check_with_no_known_list_fails():
    gate = GATE_OK_SHAPE + "\nFULL GATE: FAIL — 2 red: functions, source claims\n"
    code, out = run(gb.check, gate, KNOWN_ROWS, [], None)
    assert code == 1 and "source claims" in out


def test_the_noop_patch_is_only_excused_while_functions_are_red():
    gate = "Functions: OK 5/5\n\nFULL GATE: FAIL — 1 red: no-op patch (unrunnable)\n"
    assert run(gb.check, gate, [], [], None)[0] == 1


def test_an_interrupted_gate_proves_nothing():
    # Byte comparison passed, then the run stopped before the later checks and the verdict.
    code, out = run(gb.check, "Compile: 3 of 3 TU(s)\nFunctions: OK 5/5\nDIR32 addresses: OK\n", [])
    assert code == 2 and "did not finish" in out
    code, _ = run(gb.check, GATE_OK_SHAPE.replace("FULL GATE", "FULL GATE?"), gb.red_rows(GATE_OK_SHAPE))
    assert code == 2


def test_exit_status_must_agree_with_the_verdict():
    assert run(gb.check, GATE_OK, [], None, None, 0)[0] == 0
    code, out = run(gb.check, GATE_OK, [], None, None, 1)       # OK transcript, failed process
    assert code == 2 and "exited 1" in out
    code, out = run(gb.check, GATE_OK_SHAPE, KNOWN_ROWS, None, None, 0)  # FAIL transcript, clean exit
    assert code == 2 and "exited 0" in out
    assert run(gb.check, GATE_OK_SHAPE, KNOWN_ROWS, None, None, 1)[0] == 0


def test_abnormal_exit_after_a_verdict_never_passes():
    # A killed or crashed gate can have printed a valid verdict first.
    for status in (137, 2, -9, 0xC000013A):
        code, out = run(gb.check, GATE_OK_SHAPE, KNOWN_ROWS, None, None, status)  # known-red FAIL
        assert code == 2 and "nothing is proven" in out
        assert run(gb.check, GATE_OK, [], None, None, status)[0] == 2


@pytest.mark.parametrize("exit_code, transcript, expected_check", [
    (0, GATE_OK, 0),
    (1, "  FAIL ?new@@YAXXZ (game/New.cpp)\nFunctions: FAIL 1/1\n"
        "FULL GATE: FAIL — 1 red: functions\n", 1),
    (7, GATE_OK, 2),
])
def test_run_gate_finishes_while_grandchild_holds_output(
        monkeypatch, tmp_path, exit_code, transcript, expected_check):
    ready = tmp_path / "grandchild-ready"
    release = tmp_path / "release-grandchild"
    done = tmp_path / "grandchild-done"
    grandchild = """
import pathlib, sys, time
ready, release, done = map(pathlib.Path, sys.argv[1:])
ready.touch()
deadline = time.monotonic() + 10
while not release.exists() and time.monotonic() < deadline:
    time.sleep(0.01)
done.touch()
"""
    child = """
import pathlib, subprocess, sys, time
subprocess.Popen([sys.executable, '-c', sys.argv[1], *sys.argv[2:5]])
deadline = time.monotonic() + 2
while not pathlib.Path(sys.argv[2]).exists():
    if time.monotonic() > deadline:
        raise SystemExit('grandchild did not start')
    time.sleep(0.01)
print('compiler diagnostic', file=sys.stderr)
sys.stdout.write(sys.argv[5])
sys.exit(int(sys.argv[6]))
"""
    monkeypatch.setattr(gb, "ROOT", tmp_path)
    monkeypatch.setattr(gb, "gate_command", lambda: [
        sys.executable, "-c", child, grandchild, str(ready), str(release),
        str(done), transcript, str(exit_code)])
    # Release the fixture even with the old EOF-dependent implementation, so
    # a regression fails this test promptly instead of hanging the test suite.
    watchdog = threading.Timer(3, release.touch)
    watchdog.start()
    forwarded = io.StringIO()
    started = time.monotonic()
    try:
        with redirect_stdout(forwarded):
            status, captured = gb.run_gate()
        assert time.monotonic() - started < 2
        assert ready.exists() and not release.exists() and not done.exists()
        assert status == exit_code
        assert captured == forwarded.getvalue() == "compiler diagnostic\n" + transcript
        assert run(gb.check, captured, [], None, None, status)[0] == expected_check
    finally:
        watchdog.cancel()
        release.touch()
        deadline = time.monotonic() + 2
        while not done.exists() and time.monotonic() < deadline:
            time.sleep(0.01)
    assert done.exists()
