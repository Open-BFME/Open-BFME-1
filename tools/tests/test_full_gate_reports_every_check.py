"""The full gate must run every check, then exit once.

This is a regression lock on a defect that cost the pin guard its entire
existence. tools/pin_consistency.py landed wired into the full gate at
616cbfc3e and was reported as live. It never ran. verify_dir32_consistency sat
four statements ahead of it with a live red on master, raised SystemExit(1), and
the process died there -- so the check built specifically to catch what a green
gate cannot had itself never executed in that gate, on any commit.

Nothing detected this for two days because a first-failure exit is invisible
from the outside: "the gate is red on DIR32" reads exactly the same whether the
later checks passed or never ran at all. Ordering is not a safety property.
Running is. So the property under test is not "the pin guard comes first" -- it
is "a red check cannot silence the checks behind it", which holds no matter how
anyone reorders main() later.
"""
import importlib
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))


def _modules():
    """The module objects main() will actually use, resolved at call time.

    Sibling test files load these by path and REBIND sys.modules["build"] and
    sys.modules["pin_consistency"] to fresh objects at import time. main() does
    `import pin_consistency` in its body, so it picks up whichever object won
    that race -- and stubbing a different one silently does nothing: the real
    guard ran, passed, and never touched the recorder, so these tests passed
    alone and failed in the suite. Resolving both here means the stub always
    lands on the object under test, whatever order pytest collects in.
    """
    return importlib.import_module("build"), importlib.import_module("pin_consistency")


def _stub_gate(monkeypatch, red=()):
    """Replace every check with a recorder; names in `red` fail like the real ones."""
    build, pin_consistency = _modules()
    null_reloc = importlib.import_module("null_reloc")
    calls = []

    def check(name, result=None):
        def run(*_args, **_kwargs):
            calls.append(name)
            if name in red:
                print(f"{name}: FAIL (stub)")
                raise SystemExit(1)
            return result
        return run

    monkeypatch.setattr(build, "ensure_case_shims", check("shims"))
    monkeypatch.setattr(build, "verify_baseline", check("baseline"))
    monkeypatch.setattr(build, "verify_functions", check("functions", ["patch"]))
    monkeypatch.setattr(build, "load_function_rows", lambda: [])
    monkeypatch.setattr(build, "verify_string_refs", check("string-refs"))
    monkeypatch.setattr(build, "verify_dir32_consistency", check("dir32"))
    monkeypatch.setattr(build, "verify_source_claims", check("source-claims"))
    monkeypatch.setattr(build, "verify_noop_patch", check("noop"))
    monkeypatch.setattr(pin_consistency, "verify", check("pins"))
    monkeypatch.setattr(null_reloc, "verify", check("null-relocs"))
    return calls, build


def test_a_red_check_cannot_silence_the_checks_behind_it(monkeypatch, capsys):
    """The exact shape of the live defect: DIR32 red, pin guard four statements
    later. The guard must still run, and the gate must still be red."""
    calls, build = _stub_gate(monkeypatch, red={"dir32"})

    with pytest.raises(SystemExit) as excinfo:
        build.main()

    assert excinfo.value.code == 1, "a red check must still fail the gate"
    assert "pins" in calls, (
        "the pin guard did not run behind a red DIR32 — this is the defect that "
        "made a landed guard a no-op on master for two days")
    for late in ("string-refs", "source-claims", "noop"):
        assert late in calls, f"{late} was skipped by an earlier failure"

    out = capsys.readouterr().out
    assert "FULL GATE: FAIL" in out and "dir32" in out, (
        "the summary must name which checks were red")


def test_every_red_check_is_named_not_just_the_first(monkeypatch, capsys):
    calls, build = _stub_gate(monkeypatch, red={"dir32", "pins", "source-claims"})

    with pytest.raises(SystemExit):
        build.main()

    out = capsys.readouterr().out
    assert "3 red" in out
    for name in ("dir32", "pin consistency", "source claims"):
        assert name in out, f"{name} missing from the summary"
    assert calls.count("noop") == 1, "checks after three failures still run"


def test_a_clean_gate_says_so_once(monkeypatch, capsys):
    calls, build = _stub_gate(monkeypatch)
    build.main()
    out = capsys.readouterr().out
    assert "FULL GATE: OK" in out
    assert "FAIL" not in out
    assert calls.count("pins") == 1


def test_an_unrunnable_noop_patch_fails_loudly_instead_of_being_skipped(
        monkeypatch, capsys):
    """verify_noop_patch needs the compiled patch set, so a failed
    verify_functions leaves it unrunnable. Silently skipping it would let the
    gate report every OTHER check green while one never ran -- the same class of
    lie this whole file exists to prevent."""
    calls, build = _stub_gate(monkeypatch, red={"functions"})

    with pytest.raises(SystemExit):
        build.main()

    assert "noop" not in calls, "the stub patch set was never produced"
    out = capsys.readouterr().out
    assert "No-op patch: FAIL not run" in out
    assert "no-op patch (unrunnable)" in out


def test_a_scoped_run_is_untouched(monkeypatch, capsys):
    """Only the full gate collects verdicts. The scoped path stays a fast fail:
    both hooks call it per file and it must exit on the first mismatch."""
    calls, build = _stub_gate(monkeypatch, red={"functions"})
    monkeypatch.setattr(build, "verify_functions", lambda *a, **k: (
        calls.append("functions"), (_ for _ in ()).throw(SystemExit(1)))[0])

    with pytest.raises(SystemExit):
        build.main(only=["game/whatever.cpp"])

    assert "string-refs" not in calls, "the scoped path must not keep going"
    assert "pins" not in calls, "the scoped path does not run the full-gate checks"
