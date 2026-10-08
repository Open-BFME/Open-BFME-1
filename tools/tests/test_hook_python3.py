#!/usr/bin/env python3
"""A hook that cannot run Python must say so, not report a corrupt ledger.

On Windows `python3` is often the Microsoft Store shortcut: it prints "Python
was not found" and exits 9009. post-merge read that as a failed check_csv.py
and told a new contributor their clean ledger was corrupt. .githooks/python3.sh
falls back to `py -3` and otherwise names the real problem.
"""
import os
import re
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


def union_merge(tmp_path, py):
    """Merge two branches that both append to a merge=union ledger, through the
    driver tools/setup_hooks.sh registers, with python3 the Store shortcut."""
    repo, env = clone_with_hooks(tmp_path, py)
    shutil.copy(ROOT / "tools/merge_rows.py", repo / "tools/merge_rows.py")
    (repo / ".gitattributes").write_text("ledger.csv merge=union\n")
    driver = re.search(r'merge\.union\.driver "([^"]+)"', (ROOT / "tools/setup_hooks.sh").read_text()).group(1)
    env.update(GIT_AUTHOR_NAME="t", GIT_COMMITTER_NAME="t", GIT_AUTHOR_EMAIL="", GIT_COMMITTER_EMAIL="")

    def git(*args):
        return subprocess.run(["git", "-c", f"merge.union.driver={driver}", *args], cwd=repo, env=env,
                              capture_output=True, text=True)
    ledger = repo / "ledger.csv"
    ledger.write_text("a\nb\n")
    git("add", ".")
    git("commit", "-qm", "base")
    git("checkout", "-qb", "side")
    ledger.write_text("a\nb\nside\n")
    git("commit", "-qam", "side")
    git("checkout", "-q", "-")
    ledger.write_text("a\nb\nmain\n")
    git("commit", "-qam", "main")
    return git("merge", "-q", "--no-edit", "side"), ledger


def test_union_driver_runs_through_py_launcher(tmp_path):
    launcher = f'#!/bin/sh\n[ "$1" = -3 ] || exit 1\nshift\nexec "{sys.executable}" "$@"\n'
    run, ledger = union_merge(tmp_path, launcher)
    assert run.returncode == 0, run.stdout + run.stderr
    assert ledger.read_text().splitlines() == ["a", "b", "main", "side"]


def test_union_driver_without_python_names_it(tmp_path):
    run, _ = union_merge(tmp_path, "#!/bin/sh\nexit 1\n")
    assert run.returncode != 0
    assert "no working Python 3" in run.stdout + run.stderr, run.stdout + run.stderr
