"""Reuse ledger and source reads without mixing working, index, or ref states."""
import contextlib
import io
import sys
from pathlib import Path

import pytest


ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import check_csv


MODES = (None, "", "REF")
ARGS = {None: (), "": ("--staged",), "REF": ("--ref", "REF")}


@pytest.fixture
def fake_state(tmp_path, monkeypatch):
    monkeypatch.setattr(check_csv, "ROOT", tmp_path)
    monkeypatch.setattr(check_csv, "FUNCTIONS", tmp_path / "reverse/functions.csv")
    monkeypatch.setattr(check_csv, "SYMBOLS", tmp_path / "reverse/symbols.csv")
    monkeypatch.setattr(check_csv, "DELETED", tmp_path / "reverse/deleted_rows.csv")

    source_by_mode = {
        None: "Code/worktree_dump.asm",
        "": "Code/index_dump.asm",
        "REF": "Code/ref_dump.asm",
    }
    count_by_mode = {None: 1, "": 2, "REF": 3}
    attempt = "reverse/attempts/0x00001000.cpp"
    states = {}
    for mode, count in count_by_mode.items():
        source = source_by_mode[mode]
        rows = [
            f"?d_00001000@@YAXXZ,,0x00001000,1,{source},matched,gen-dump\r\n"
        ]
        rows += [
            f"?u_{n:08x}@@YAXXZ,,0x{n:08X},0,{source},unmatched,\r\n"
            for n in range(0x1001, 0x1001 + count - 1)
        ]
        functions = (
            check_csv.FUNCTIONS_HEADER + "\r\n" + "".join(rows)
        ).encode()
        states[mode] = {
            "functions": functions,
            "sources": {source, attempt, f"Code/gen_small/{mode or 'worktree'}.cpp"},
        }

    symbols = (check_csv.SYMBOLS_HEADER + "\r\n").encode()
    deleted = b"name,target_rva,reason\r\n"
    calls = {"known": [], "ledger": [], "blobs": []}
    current_mode = {"value": None}
    attempt_body = {"value": b"// fn\n// partial score=0.9 date=2026-09-12\n"}

    def known_sources(mode):
        calls["known"].append(mode)
        return set(states[mode]["sources"])

    def read_ledger(path, mode):
        calls["ledger"].append((path.name, mode))
        if path.name == "functions.csv":
            if mode == "HEAD":
                mode = current_mode["value"]
            return states[mode]["functions"]
        if path.name == "symbols.csv":
            return symbols
        if path.name == "deleted_rows.csv":
            return deleted
        raise AssertionError(path)

    def read_blobs(paths, mode):
        paths = list(paths)
        calls["blobs"].append((tuple(str(path) for path in paths), mode))
        return {path: attempt_body["value"] for path in paths}

    monkeypatch.setattr(check_csv, "known_sources", known_sources)
    monkeypatch.setattr(check_csv, "read_ledger", read_ledger)
    monkeypatch.setattr(check_csv, "read_blobs", read_blobs)
    monkeypatch.setattr(check_csv, "ORPHAN_BASELINE", 6)

    return {
        "states": states,
        "calls": calls,
        "current_mode": current_mode,
        "attempt_body": attempt_body,
    }


def run_main(state, mode):
    state["current_mode"]["value"] = mode
    old_argv = sys.argv
    sys.argv = ["check_csv.py", *ARGS[mode]]
    stdout, stderr = io.StringIO(), io.StringIO()
    try:
        with contextlib.redirect_stdout(stdout), contextlib.redirect_stderr(stderr):
            try:
                result = check_csv.main()
            except SystemExit as exc:
                result = exc.code
    finally:
        sys.argv = old_argv
    return result, stdout.getvalue(), stderr.getvalue()


def test_main_uses_one_mode_correct_membership_scan(fake_state):
    for mode in MODES:
        fake_state["calls"]["known"].clear()
        fake_state["calls"]["ledger"].clear()
        result, output, error = run_main(fake_state, mode)
        assert result is None, error
        expected_rows = {None: 1, "": 2, "REF": 3}[mode]
        assert f"functions.csv {expected_rows} rows" in output
        assert fake_state["calls"]["known"] == [mode]
        function_reads = [x for x in fake_state["calls"]["ledger"]
                          if x[0] == "functions.csv"]
        assert len(function_reads) == (2 if mode == "" else 1)


def test_invalid_attempt_is_a_failure(fake_state):
    fake_state["attempt_body"]["value"] = b"// fn\n// malformed score\n"
    result, _output, error = run_main(fake_state, None)
    assert result == 1
    assert "unreadable score" in error
    assert fake_state["calls"]["known"] == [None]


def test_staged_mode_keeps_separate_head_ledger_read(fake_state):
    result, _output, error = run_main(fake_state, "")
    assert result is None, error
    ledger = fake_state["calls"]["ledger"]
    assert ledger.count(("functions.csv", "HEAD")) == 1
    assert ledger.count(("functions.csv", "")) == 1


def test_standalone_helpers_keep_state_specific_fallbacks(fake_state):
    for mode in MODES:
        fake_state["calls"]["known"].clear()
        fake_state["calls"]["ledger"].clear()
        problems = []
        assert check_csv.check_attempts(mode, problems) == 1
        assert problems == []
        assert fake_state["calls"]["known"] == [mode]
        assert ("functions.csv", mode) in fake_state["calls"]["ledger"]

        fake_state["calls"]["known"].clear()
        fake_state["calls"]["ledger"].clear()
        problems = []
        assert check_csv.check_orphans(mode, problems) == 0
        assert problems == []
        assert fake_state["calls"]["known"] == [mode]
        assert ("functions.csv", mode) in fake_state["calls"]["ledger"]
