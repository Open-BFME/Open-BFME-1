"""red_rows.py's verdict, proven in both directions.

A reporter that cannot go red is worse than none: it would publish "0 red rows"
over the exact wall it exists to find. So the gate's exit code, its output and
whether it rewrote targets/game/reverse/reloc_names.csv are all knobs here, and the compile
wall that exits 2 without ever reaching byte comparison has to land on a
different verdict than a clean run.
"""
import importlib.util
import sys
from pathlib import Path
from types import SimpleNamespace

TOOLS = Path(__file__).resolve().parents[1]


def _load(name):
    spec = importlib.util.spec_from_file_location(name, TOOLS / f"{name}.py")
    module = importlib.util.module_from_spec(spec)
    sys.modules[name] = module
    spec.loader.exec_module(module)
    return module


red_rows = _load("red_rows")


def test_windows_runner_invokes_build_sh_through_bash(monkeypatch):
    seen = {}

    monkeypatch.setattr(red_rows.os, "name", "nt")
    monkeypatch.setattr(red_rows.shutil, "which", lambda name: "C:/Git/bin/bash.exe")

    def run(command, **kwargs):
        seen["command"] = command
        seen["kwargs"] = kwargs
        return SimpleNamespace(returncode=0, stdout="")

    monkeypatch.setattr(red_rows.subprocess, "run", run)
    assert red_rows.run_gate() == (0, "")
    assert seen["command"] == ["C:/Git/bin/bash.exe", str(red_rows.ROOT / "build.sh")]

GREEN = """Compile: 0 of 264 TU(s) (deps-cache: 264 current)
Functions: OK 5127/5127 matched across 311 source file(s)
Reloc names: 903 anonymous function(s) named from byte-true call sites
"""

TWO_RED = """Compile: 0 of 264 TU(s) (deps-cache: 264 current)
  FAIL ??_G?$SList@VTagBlockIndex@@@@UAEPAXI@Z (game/Libraries/Source/WWVegas/WWLib/tagblock.cpp)
    target:   56 8B F1 E8 4D FF FF FF
    compiled: 57 8B F9 E8 4D FF FF FF
  FAIL ?resetIdleScan@TurretAI@@QAEXXZ (game/GameEngine/Source/Common/TurretAI.cpp)
    unresolved call(s): _theGameLogic (add to targets/game/reverse/symbols.csv)
    target:   8B 44 24 04 CC CC
    compiled: 8B 44 24 08 90 90
Functions: FAIL 2/5127
2 function(s) failed byte comparison
"""

COMPILE_WALL = """Compile: 3 of 264 TU(s) (deps-cache: 261 current)
compile failed: game/GameEngine/Source/Common/TurretAI.cpp
TurretAI.cpp(41) : error C2065: 'theGameLogic' : undeclared identifier
"""


class Gate:
    """One gate run, with its output, exit code and reloc rewrite as knobs."""

    def __init__(self, tmp_path, monkeypatch, *, output, code=0, rewrites_reloc=False):
        self.reloc = tmp_path / "reloc_names.csv"
        self.reloc.write_text("name,target_rva,target_size,source,notes\n",
                              encoding="utf-8")

        def gate():
            if rewrites_reloc:
                self.reloc.write_text(
                    "name,target_rva,target_size,source,notes\n"
                    "?named@@YAXXZ,0x00401000,16,game/a.cpp,reloc-derived\n",
                    encoding="utf-8")
            return code, output

        monkeypatch.setattr(red_rows, "RELOC_NAMES", self.reloc)
        monkeypatch.setattr(red_rows, "run_gate", gate)


def test_every_failing_row_is_named_and_no_byte_dump_is_echoed(tmp_path, monkeypatch, capsys):
    Gate(tmp_path, monkeypatch, output=TWO_RED, code=1)

    assert red_rows.main() != 0, "red rows must not exit 0"

    out = capsys.readouterr().out
    assert "??_G?$SList@VTagBlockIndex@@@@UAEPAXI@Z" in out
    assert "?resetIdleScan@TurretAI@@QAEXXZ" in out
    assert "2 red row(s)" in out
    assert "target:" not in out and "compiled:" not in out
    assert "8B 44 24" not in out, "byte dumps belong in the gate, not the report"


def test_a_gate_that_died_before_byte_comparison_is_not_zero_red_rows(tmp_path, monkeypatch, capsys):
    """cl.exe returns 2 and the gate never compares a single byte."""
    Gate(tmp_path, monkeypatch, output=COMPILE_WALL, code=2)

    assert red_rows.main() != 0

    captured = capsys.readouterr()
    assert "before it reached byte comparison" in captured.out
    assert "gate exit 2" in captured.out
    assert "0 red rows" not in captured.out, "an unrun comparison is not a green one"
    assert "error C2065" in captured.err, "the reason it died is the whole point"


def test_a_clean_gate_is_zero_red_rows(tmp_path, monkeypatch, capsys):
    Gate(tmp_path, monkeypatch, output=GREEN, code=0)

    assert red_rows.main() == 0

    out = capsys.readouterr().out
    assert "0 red rows" in out
    assert "RED " not in out
    assert "targets/game/reverse/reloc_names.csv: unchanged" in out


def test_a_rewritten_reloc_file_is_reported(tmp_path, monkeypatch, capsys):
    """A green run leaves a 450 KB diff behind; nobody may commit it unaware."""
    Gate(tmp_path, monkeypatch, output=GREEN, code=0, rewrites_reloc=True)

    assert red_rows.main() == 0

    assert "REWRITTEN by this run" in capsys.readouterr().out
