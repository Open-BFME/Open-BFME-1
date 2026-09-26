"""A target-bound worker cannot reach legacy game operations by accident."""
import os
from pathlib import Path
import subprocess
import sys

import pytest


TOOLS = Path(__file__).resolve().parents[1]
LEGACY = ("build", "add_match", "re_log", "probe", "check_csv", "next_work",
          "brief", "callees")


def environment(**bindings):
    env = {key: value for key, value in os.environ.items()
           if key not in {"BFME_TARGET", "BFME_TARGET_SHA256"}}
    env.update(bindings)
    return env


@pytest.mark.parametrize("tool", LEGACY)
@pytest.mark.parametrize("bindings", [
    {"BFME_TARGET": "worldbuilder", "BFME_TARGET_SHA256": "a" * 64},
    {"BFME_TARGET": "unknown"},
    {"BFME_TARGET": ""},
    {"BFME_TARGET_SHA256": "a" * 64},
])
def test_bound_cli_refuses_before_imports_reads_or_writes(tmp_path, tool, bindings):
    # No game files or dependencies exist here: rejection must precede their use.
    for name in (tool, "target_guard"):
        (tmp_path / (name + ".py")).write_bytes((TOOLS / (name + ".py")).read_bytes())
    result = subprocess.run([sys.executable, "-B", str(tmp_path / (tool + ".py")),
                             "record", "missing-symbol"], cwd=tmp_path,
                            env=environment(**bindings), capture_output=True, text=True)
    assert result.returncode != 0
    assert f"{tool}.py: legacy BFME1-only command refused" in result.stderr
    assert "python3 tools/worldbuilder.py --help" in result.stderr
    assert "Traceback" not in result.stderr
    assert set(path.name for path in tmp_path.iterdir()) == {tool + ".py", "target_guard.py"}


def test_bound_worker_can_import_build_and_target_helpers(tmp_path):
    code = ("import sys; sys.path.insert(0, sys.argv[1]); "
            "import build, target_verify; "
            "assert callable(build.compiler_command); "
            "assert callable(build.read_object_symbol_bytes); "
            "assert callable(target_verify.verify)")
    result = subprocess.run([sys.executable, "-B", "-c", code, str(TOOLS)], cwd=tmp_path,
                            env=environment(BFME_TARGET="worldbuilder",
                                            BFME_TARGET_SHA256="a" * 64),
                            capture_output=True, text=True)
    assert result.returncode == 0, result.stderr
    assert not list(tmp_path.iterdir())


@pytest.mark.parametrize("selector", [["--target", "worldbuilder"], ["--target=unknown"]])
def test_legacy_build_cannot_interpret_explicit_target_as_game_selector(tmp_path, selector):
    for name in ("build", "target_guard"):
        (tmp_path / (name + ".py")).write_bytes((TOOLS / (name + ".py")).read_bytes())
    result = subprocess.run([sys.executable, "-B", str(tmp_path / "build.py"), *selector],
                            cwd=tmp_path, env=environment(), capture_output=True, text=True)
    assert result.returncode != 0
    assert "--target is unsupported" in result.stderr
    assert "Traceback" not in result.stderr


@pytest.mark.parametrize("tool", ["add_match", "probe", "check_csv", "next_work", "brief", "callees"])
def test_unbound_legacy_argument_parser_is_unchanged(tmp_path, tool):
    result = subprocess.run([sys.executable, "-B", str(TOOLS / (tool + ".py")), "--help"],
                            cwd=tmp_path, env=environment(), capture_output=True, text=True)
    assert result.returncode == 0, result.stderr
    assert "usage:" in result.stdout
    assert "command refused" not in result.stderr
