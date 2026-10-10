"""ledger_guard: the byte gate must read the ledgers being committed or pushed."""
import re
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import ledger_guard as G  # noqa: E402

LEDGER = G.LEDGERS[0]
ROW = "?f@@YAXXZ,,0x00401000,4,{src},matched,x\n"
HEAD = "name,export_rva,target_rva,target_size,source,status,notes\n"


def git(root, *args):
    return subprocess.run(["git", *args], cwd=root, check=True, capture_output=True, text=True).stdout


@pytest.fixture
def repo(tmp_path, monkeypatch):
    git(tmp_path, "init", "-q")
    git(tmp_path, "config", "user.name", "Fixture")
    git(tmp_path, "config", "user.email", "fixture@example.invalid")
    for path, text in ((LEDGER, HEAD + ROW.format(src="Unit.cpp")), (G.LEDGERS[1], "name,rva\n"),
                       ("Unit.cpp", "struct Coord2D { float x, y; };\nvoid f(Coord2D *) {}\n")):
        (tmp_path / path).parent.mkdir(parents=True, exist_ok=True)
        (tmp_path / path).write_text(text)
    git(tmp_path, "add", "-A")
    git(tmp_path, "commit", "-qm", "base")
    monkeypatch.setattr(G, "ROOT", tmp_path)
    return tmp_path


def rename_row(repo):
    """The 2026-10-06 shape: the unit's view changes class-key, its row is renamed U->V."""
    (repo / "Unit.cpp").write_text('#include "Coord2D.h"\nvoid f(Coord2D *) {}\n')
    git(repo, "add", "Unit.cpp")
    (repo / LEDGER).write_text(HEAD + ROW.format(src="Unit.cpp").replace("?f@@", "?f@@V"))


def test_unstaged_ledger_rename_is_refused_at_commit(repo, capsys):
    rename_row(repo)                                  # positive control: passed the old hook
    assert G.main(["--staged"]) == 1
    assert LEDGER in capsys.readouterr().err


def test_staged_ledger_and_clean_trees_pass(repo):
    assert G.main(["--staged"]) == 0                  # nothing changed
    rename_row(repo)
    git(repo, "add", LEDGER)
    assert G.main(["--staged"]) == 0                  # rename staged with its unit
    (repo / "Other.cpp").write_text("int g;\n")       # unrelated unstaged edit
    assert G.main(["--staged"]) == 0


def test_push_refuses_a_ledger_that_is_not_the_pushed_commits(repo):
    head = git(repo, "rev-parse", "HEAD").strip()
    assert G.main(["--commit", head]) == 0
    rename_row(repo)
    assert G.main(["--commit", head]) == 1            # unstaged
    git(repo, "add", LEDGER)
    assert G.main(["--commit", head]) == 1            # staged but not in the pushed commit
    git(repo, "commit", "-qm", "rename")
    assert G.main(["--commit", git(repo, "rev-parse", "HEAD").strip()]) == 0


def test_an_unstaged_data_row_is_refused_at_commit_and_push(repo):
    # Open-BFME-2 36a0bdc042: build.py proves data rows from the working-tree data_rows.csv
    data = G.LEDGERS[2]
    (repo / data).write_text("name,rva,size,source,status,notes\ng,0x00A00000,4,Unit.cpp,matched,\n")
    git(repo, "add", data)
    git(repo, "commit", "-qm", "data row")
    head = git(repo, "rev-parse", "HEAD").strip()
    (repo / data).write_text("name,rva,size,source,status,notes\ng,0x00A00004,4,Unit.cpp,matched,\n")
    assert G.main(["--staged"]) == 1
    assert G.main(["--commit", head]) == 1
    git(repo, "add", data)
    assert G.main(["--staged"]) == 0 and G.main(["--commit", head]) == 1


@pytest.mark.parametrize("hook,call", [("pre-commit", "ledger_guard.py --staged"),
                                       ("pre-push", 'ledger_guard.py --commit "$local_sha"')])
def test_hooks_guard_before_any_build(hook, call):
    text = (TOOLS.parent / ".githooks" / hook).read_text(encoding="utf-8")
    assert call in text
    first_build = re.search(r"BUILD_POOL=", text)
    assert first_build and text.index(call) < first_build.start()
