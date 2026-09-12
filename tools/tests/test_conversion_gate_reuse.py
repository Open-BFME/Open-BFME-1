"""Shared conversion scans preserve standalone rules and ledger authority."""
import contextlib
import io
import subprocess
import sys
from pathlib import Path

import pytest


ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import conversion_gate as gate


def git(repo, *args):
    return subprocess.run(["git", "-C", str(repo), *args], check=True,
                          capture_output=True, text=True).stdout.strip()


def commit(repo, message):
    git(repo, "add", "--", "Code", "reverse", "tools")
    git(repo, "-c", "user.name=gate fixture", "-c",
        "user.email=gate@example.invalid", "commit", "-qm", message)
    return git(repo, "rev-parse", "HEAD")


def fixture_repo(tmp_path, kind):
    repo = tmp_path / kind
    repo.mkdir()
    git(repo, "init", "-q")
    (repo / "Code").mkdir()
    (repo / "reverse").mkdir()
    (repo / "reverse/functions.csv").write_text(
        "name,export_rva,target_rva,target_size,source,status,notes\n"
    )
    (repo / "tools").mkdir()
    (repo / "Code/Existing.cpp").write_text("int existing() { return 1; }\n")
    if kind == "asm-reversal":
        (repo / "Code/Game.cpp").write_text("int f() { return 1; }\n")
        (repo / "reverse/functions.csv").write_text(
            "name,export_rva,target_rva,target_size,source,status,notes\n"
            "?f@@YAXXZ,,0x00401000,4,Code/Game.cpp,matched,\n"
        )
    old = commit(repo, "old")

    if kind == "lift":
        (repo / "Code/Lift.cpp").write_text(
            "__declspec(naked) void f() { __asm { __emit 0xC3 } }\n"
        )
    elif kind == "gen-asm-valid":
        write_gen_asm(repo, "    db 0C3h\n")
    elif kind == "gen-asm-invalid":
        write_gen_asm(repo, "    mov eax, 1\n")
    elif kind == "gen-small":
        (repo / "Code/gen_small").mkdir()
        (repo / "Code/gen_small/retired.cpp").write_text(
            "__declspec(naked) void retired() { __asm { __emit 0xC3 } }\n"
        )
    elif kind == "asm-reversal":
        (repo / "Code/dump.asm").write_text("d_00401000 PROC\n    db 0C3h\nENDP\n")
        (repo / "reverse/functions.csv").write_text(
            "name,export_rva,target_rva,target_size,source,status,notes\n"
            "?f@@YAXXZ,,0x00401000,4,Code/dump.asm,matched,\n"
        )
    elif kind == "pure-tool":
        (repo / "tools/helper.py").write_text("VALUE = 1\n")
    elif kind == "c3":
        write_gen_asm(repo, "    db 0C3h\n")
        (repo / "reverse/functions.csv").write_text(
            "name,export_rva,target_rva,target_size,source,status,notes\n"
            "?d_00401000@@YAXXZ,,0x00401000,1,"
            "Code/gen_asm/d_00401000.asm,matched,gen-dump\n"
        )
        (repo / "Code/Existing.cpp").write_text("int existing() { return 2; }\n")
    else:
        raise AssertionError(kind)
    return repo, old, commit(repo, "new")


def write_gen_asm(repo, body):
    (repo / "Code/gen_asm").mkdir()
    (repo / "Code/gen_asm/d_00401000.asm").write_text(
        ".386\n.model flat\n_TEXT SEGMENT\n"
        "public ?d_00401000@@YAXXZ\n"
        "?d_00401000@@YAXXZ PROC\n"
        + body
        + "?d_00401000@@YAXXZ ENDP\n_TEXT ENDS\nEND\n"
    )


def run_gate(module, repo, old, new, monkeypatch):
    monkeypatch.chdir(repo)
    calls = []
    real_run = module.run

    def tracked_run(*argv):
        calls.append(argv)
        return real_run(*argv)

    monkeypatch.setattr(module, "run", tracked_run)
    old_argv = sys.argv
    sys.argv = ["conversion_gate.py", old, new]
    stdout, stderr = io.StringIO(), io.StringIO()
    try:
        with contextlib.redirect_stdout(stdout), contextlib.redirect_stderr(stderr):
            try:
                result = module.main()
            except SystemExit as exc:
                result = exc.code
    finally:
        sys.argv = old_argv
    return result, stdout.getvalue(), stderr.getvalue(), calls


@pytest.mark.parametrize("kind,expected", [
    ("lift", 1),
    ("gen-asm-valid", 0),
    ("gen-asm-invalid", 1),
    ("gen-small", 0),
    ("asm-reversal", 1),
    ("pure-tool", 0),
    ("c3", 1),
])
def test_reuse_preserves_gate_result_and_diagnostics(tmp_path, monkeypatch, kind, expected):
    repo, old, new = fixture_repo(tmp_path, kind)
    monkeypatch.chdir(repo)
    shared = gate.collect_diff_lines(old, new)
    assert gate.added_lift_lines(old, new, shared) == gate.added_lift_lines(old, new)
    assert gate.gen_asm_offences(old, new, shared) == gate.gen_asm_offences(old, new)
    after = run_gate(gate, repo, old, new, monkeypatch)
    assert bool(after[2]) == bool(expected)
    assert after[0] == expected
    diff_calls = [call for call in after[3] if call[:2] == ("git", "diff")]
    assert len(diff_calls) == 1
    blob_calls = [call for call in after[3] if call[:2] == ("git", "rev-parse")]
    assert len(blob_calls) == 2


def test_rule_b_keeps_ledger_blob_authority(tmp_path, monkeypatch):
    repo, old, new = fixture_repo(tmp_path, "asm-reversal")
    # Even if the shared textual diff were unavailable or unusual, Rule B must
    # decide ledger state from its authoritative object IDs.
    monkeypatch.setattr(gate, "collect_diff_lines", lambda *_args: [])
    result, _out, error, calls = run_gate(gate, repo, old, new, monkeypatch)
    assert result == 1, error
    assert len([call for call in calls if call[:2] == ("git", "rev-parse")]) == 2
