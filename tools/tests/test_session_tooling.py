"""Seat yield by run id, the line-ending guard, and lift class homes."""
import json
import subprocess
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
sys.path.insert(0, str(TOOLS / "fleet"))

import eol_guard  # noqa: E402
import session_yield  # noqa: E402


def _run(tmp_path, run_id, engine, seat, start, status="finished"):
    d = tmp_path / "runs" / run_id
    d.mkdir(parents=True)
    (d / "record.json").write_text(json.dumps(
        {"id": run_id, "engine": engine, "seat": seat, "start": start, "status": status}))


def test_latest_finished_run_of_the_seat(tmp_path):
    _run(tmp_path, "a", "luna", "3", 1)
    _run(tmp_path, "b", "luna", "3", 2)
    _run(tmp_path, "c", "luna", "3", 3, status="aborted")
    _run(tmp_path, "d", "luna", "4", 4)
    assert session_yield.latest_run("luna", "3", tmp_path / "runs")["id"] == "b"


def test_yield_counts_landings_banks_and_verdicts_of_one_run(tmp_path):
    functions = tmp_path / "functions.csv"
    functions.write_text("h\n?a@@YAXXZ,,0x1,4,Code/A.cpp,matched,x run=r1\n"
                         "?b@@YAXXZ,,0x2,4,Code/B.cpp,matched,x run=r2\n")
    log = tmp_path / "re_attempts.log"
    log.write_text("s\t0x3\t4\tblocked\tt=20 run=r1\n"
                   "s\t0x4\t4\tpartial\tt=40 stash=x run=r1\n"
                   "s\t0x5\t4\tblocked\tt=20 run=r9\n")
    assert session_yield.run_yield("r1", functions, log) == (1, 1, 2)
    assert session_yield.run_yield("r9", functions, log) == (0, 0, 1)


def test_eol_guard_flags_a_line_ending_rewrite(tmp_path, monkeypatch):
    def git(*args):
        subprocess.run(["git", *args], cwd=tmp_path, check=True, capture_output=True)
    git("init", "-q")
    git("config", "core.autocrlf", "false")
    git("config", "user.name", "t")
    git("config", "user.email", "t@example.invalid")
    source = tmp_path / "Mixed.cpp"
    source.write_bytes(b"".join(b"line %d\r\n" % i for i in range(80)) + b"tail\n")
    git("add", "Mixed.cpp")
    git("commit", "-qm", "base")
    monkeypatch.setattr(eol_guard, "ROOT", tmp_path)
    source.write_bytes(b"".join(b"line %d\n" % i for i in range(80)) + b"tail\nnew\n")
    git("add", "Mixed.cpp")
    found = eol_guard.rewrites()
    assert found and found[0][0] == "Mixed.cpp" and found[0][2] == 1
    monkeypatch.delenv("BFME_EOL_REWRITE", raising=False)
    assert eol_guard.main([]) == 1
    monkeypatch.setenv("BFME_EOL_REWRITE", "1")
    assert eol_guard.main([]) == 0


def test_eol_guard_passes_a_real_edit(tmp_path, monkeypatch):
    def git(*args):
        subprocess.run(["git", *args], cwd=tmp_path, check=True, capture_output=True)
    git("init", "-q")
    git("config", "core.autocrlf", "false")
    git("config", "user.name", "t")
    git("config", "user.email", "t@example.invalid")
    source = tmp_path / "A.cpp"
    source.write_bytes(b"".join(b"line %d\r\n" % i for i in range(80)))
    git("add", "A.cpp")
    git("commit", "-qm", "base")
    monkeypatch.setattr(eol_guard, "ROOT", tmp_path)
    source.write_bytes(b"".join(b"edit %d\r\n" % i for i in range(80)))
    git("add", "A.cpp")
    assert eol_guard.rewrites() == []


def test_class_of_member_ctor_dtor_and_free_names():
    import pytest
    lift_lane = pytest.importorskip("lift_lane")
    assert lift_lane.class_of("?init@ShellGameLoadScreen@@") == "ShellGameLoadScreen"
    assert lift_lane.class_of("??0Object@@QAE@XZ") == "Object"
    assert lift_lane.class_of("??1ControlBar@@UAE@XZ") == "ControlBar"
    assert lift_lane.class_of("??_GFoo@@UAEPAXI@Z") == "Foo"
    assert lift_lane.class_of("?freeFunction@@YAXXZ") is None
