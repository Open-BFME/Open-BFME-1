#!/usr/bin/env python3
"""A hook that cannot run Python must say so, not report a corrupt ledger.

On Windows `python3` is often the Microsoft Store shortcut: it prints "Python
was not found" and exits 9009. post-merge read that as a failed check_csv.py
and told a new contributor their clean ledger was corrupt. .githooks/python3.sh
falls back to `py -3` and otherwise names the real problem.
"""
import os
import shutil
import subprocess
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
BASH = shutil.which("bash")
pytestmark = pytest.mark.skipif(BASH is None or os.name == "nt", reason="needs a POSIX bash")

STORE_SHORTCUT = ('#!/bin/sh\n'
                  'echo "Python was not found; run without arguments to install from the Microsoft Store" >&2\n'
                  'exit 9009\n')


def clone_with_hooks(tmp_path, py):
    """The real hooks and a stub check_csv.py, with python3 the Store shortcut and `py` as given."""
    repo = tmp_path / "repo"
    (repo / "tools").mkdir(parents=True)
    shutil.copytree(ROOT / ".githooks", repo / ".githooks")
    (repo / "tools/check_csv.py").write_text('print("check_csv: OK")\n')
    subprocess.run(["git", "init", "-q", str(repo)], check=True)
    bin_dir = tmp_path / "bin"
    bin_dir.mkdir()
    for name, body in (("python3", STORE_SHORTCUT), ("py", py)):
        (bin_dir / name).write_text(body)
        (bin_dir / name).chmod(0o755)
    env = dict(os.environ, PATH=f"{bin_dir}{os.pathsep}{os.environ['PATH']}")
    return repo, env


def post_merge(repo, env):
    return subprocess.run([BASH, ".githooks/post-merge", "0"], cwd=repo, env=env,
                          capture_output=True, text=True)


def test_no_python_is_not_called_corruption(tmp_path):
    repo, env = clone_with_hooks(tmp_path, "#!/bin/sh\nexit 1\n")
    run = post_merge(repo, env)
    assert run.returncode == 1
    assert "LEDGER CORRUPT" not in run.stderr, run.stderr
    assert "NO WORKING PYTHON 3" in run.stderr and "checked NOTHING" in run.stderr, run.stderr


def test_py_launcher_stands_in_for_python3(tmp_path):
    launcher = f'#!/bin/sh\n[ "$1" = -3 ] || exit 1\nshift\nexec "{sys.executable}" "$@"\n'
    repo, env = clone_with_hooks(tmp_path, launcher)
    run = post_merge(repo, env)
    assert run.returncode == 0, run.stderr
    assert "check_csv: OK" in run.stdout, run.stdout + run.stderr
