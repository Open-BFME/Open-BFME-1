"""add_data_match admits a verified row's address-spelled global (`?g_Va012BA084@@3GA`
-> `g_Va012BA084`) in the escape-hatch register, and only that token: another
address global typed into the same file by hand stays refused growth."""
import os
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import add_data_match  # noqa: E402
import hatch_counters  # noqa: E402

SOURCE = "game/a.cpp"


def git(root, *args):
    env = dict(os.environ, GIT_AUTHOR_NAME="t", GIT_COMMITTER_NAME="t", GIT_AUTHOR_EMAIL="",
               GIT_COMMITTER_EMAIL="")
    got = subprocess.run(["git", "-C", str(root), *args], capture_output=True, text=True, env=env)
    assert got.returncode == 0, got.stderr
    return got.stdout


@pytest.mark.parametrize("name, token", [
    ("?g_Va012BA084@@3GA", "g_Va012BA084"),
    ("_g_VA00123456", "g_VA00123456"),
    ("?OurLanguage@@3W4LanguageID@@A", None),
])
def test_address_token(name, token):
    assert add_data_match.address_token(name) == token


@pytest.fixture
def tree(tmp_path, monkeypatch):
    (tmp_path / SOURCE).parent.mkdir(parents=True)
    (tmp_path / SOURCE).write_text("int x;\n", newline="\n")
    git(tmp_path, "init", "-q")
    git(tmp_path, "config", "core.autocrlf", "false")
    monkeypatch.setattr(hatch_counters, "ROOT", tmp_path)
    git(tmp_path, "add", ".")
    hatch_counters.write(hatch_counters.tree_scan(), mode="enforce")
    git(tmp_path, "add", ".")
    git(tmp_path, "commit", "-qm", "init")
    monkeypatch.chdir(tmp_path)
    return tmp_path


def gate(root):
    git(root, "add", ".")
    errors, _, hard = hatch_counters.check_staged()
    return errors + hard


def test_the_tool_row_passes_and_a_hand_written_one_is_refused(tree):
    (tree / SOURCE).write_text("int x;\nunsigned short g_Va012BA084;\n", newline="\n")
    add_data_match.admit_address_global(SOURCE, "?g_Va012BA084@@3GA")
    assert gate(tree) == []
    git(tree, "commit", "-qm", "tool row")
    (tree / SOURCE).write_text("int x;\nunsigned short g_Va012BA084;\nint g_Va012BA090;\n",
                               newline="\n")
    add_data_match.admit_address_global(SOURCE, "?OurLanguage@@3W4LanguageID@@A")
    problems = gate(tree)
    assert problems and all("g_Va012BA090" in p for p in problems)
