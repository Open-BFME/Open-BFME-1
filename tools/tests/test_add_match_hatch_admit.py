"""add_match admits a verified row's object-symbol= in the escape-hatch register only
when it names a compiler label (`_$E8`, `$L12`, `__ehhandler$...`); an alias to a
real function, or one typed into functions.csv by hand, stays refused growth."""
import os
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import add_match  # noqa: E402
import hatch_counters  # noqa: E402

LEDGER = "targets/game/reverse/functions.csv"
HEADER = "name,export_rva,target_rva,target_size,source,status,notes\n"


def git(root, *args):
    env = dict(os.environ, GIT_AUTHOR_NAME="t", GIT_COMMITTER_NAME="t", GIT_AUTHOR_EMAIL="",
               GIT_COMMITTER_EMAIL="")
    got = subprocess.run(["git", "-C", str(root), *args], capture_output=True, text=True, env=env)
    assert got.returncode == 0, got.stderr
    return got.stdout


@pytest.mark.parametrize("notes, admitted", [
    ("object-symbol=_$E8; native PointGroup initializer", True),
    ("object-symbol=$L4571", True),
    ("x;object-symbol=__ehhandler$?f@@YAXXZ;y", True),
    ("object-symbol=?realName@Thing@@QAEXXZ", False),
    ("object-symbol=_$E8junk more", False),
    ("plain notes", False),
])
def test_compiler_label_pattern(notes, admitted):
    assert bool(add_match.COMPILER_LABEL.search(notes)) is admitted


@pytest.fixture
def tree(tmp_path, monkeypatch):
    (tmp_path / LEDGER).parent.mkdir(parents=True)
    (tmp_path / LEDGER).write_text(HEADER, newline="\n")
    git(tmp_path, "init", "-q")
    git(tmp_path, "config", "core.autocrlf", "false")
    monkeypatch.setattr(hatch_counters, "ROOT", tmp_path)
    git(tmp_path, "add", ".")
    hatch_counters.write(hatch_counters.tree_scan(), mode="enforce")
    git(tmp_path, "add", ".")
    git(tmp_path, "commit", "-qm", "init")
    monkeypatch.chdir(tmp_path)
    return tmp_path


def append_and_admit(root, row, rva, notes):
    before = (root / LEDGER).read_bytes()
    (root / LEDGER).write_bytes(before + row.encode() + b"\n")
    add_match.admit_compiler_label_alias(root, notes, rva, before)


def gate(root):
    git(root, "add", ".")
    errors, _, hard = hatch_counters.check_staged()
    return errors + hard


def test_verified_compiler_label_rows_pass_and_others_are_refused(tree):
    append_and_admit(tree, "?d_1@@YAXXZ,,0x00C6DE20,26,game/a.cpp,matched,object-symbol=_$E8", 0xC6DE20,
                     "object-symbol=_$E8")
    append_and_admit(tree, "?d_2@@YAXXZ,,0x00C70890,20,game/b.cpp,matched,object-symbol=_$E2", 0xC70890,
                     "object-symbol=_$E2")
    assert gate(tree) == []                      # two tool admissions in one commit
    append_and_admit(tree, "?alias@@YAXXZ,,0x00001000,5,game/c.cpp,matched,object-symbol=?real@@YAXXZ",
                     0x1000, "object-symbol=?real@@YAXXZ")
    problems = gate(tree)
    assert problems and all("0x00001000" in p for p in problems)
