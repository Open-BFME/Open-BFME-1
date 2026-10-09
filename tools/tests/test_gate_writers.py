"""tools/gate_writers.py: a gate-read ledger fact passes when its one writer stamped
it in this worktree's git dir, and a hand edit is refused."""
import os
import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import gate_writers as gw  # noqa: E402

DATA = "targets/game/reverse/data_rows.csv"
DATA_HEAD = "name,address,address_kind,size,section,source,status,evidence,model\n"
ROW_A = "?g_a@@3HA,0x01000000,va,4,.data,game/a.cpp,matched,old evidence,m\n"
ROW_B = "?g_b@@3HA,0x01000004,va,4,.data,game/a.cpp,matched,e,m\n"
EXTRA = {}


def git(root, *args):
    env = dict(os.environ, GIT_AUTHOR_NAME="t", GIT_COMMITTER_NAME="t", GIT_AUTHOR_EMAIL="t@t",
               GIT_COMMITTER_EMAIL="t@t")
    got = subprocess.run(["git", "-C", str(root), *args], capture_output=True, text=True, env=env)
    assert got.returncode == 0, got.stderr
    return got.stdout


@pytest.fixture
def repo(tmp_path, monkeypatch):
    files = {DATA: DATA_HEAD + ROW_A}
    files.update(EXTRA)
    for rel, text in files.items():
        (tmp_path / rel).parent.mkdir(parents=True, exist_ok=True)
        (tmp_path / rel).write_text(text, newline="\n")
    git(tmp_path, "init", "-q")
    git(tmp_path, "add", ".")
    git(tmp_path, "commit", "-qm", "init")
    monkeypatch.chdir(tmp_path)
    return tmp_path


def write(root, rel, text, tool_kind=None):
    before = (root / rel).read_bytes()
    (root / rel).write_text(text, newline="\n")
    if tool_kind:
        gw.stamp(tool_kind, before, (root / rel).read_bytes())
    git(root, "add", rel)


def test_a_tool_added_data_row_passes(repo):
    write(repo, DATA, DATA_HEAD + ROW_A + ROW_B, tool_kind="data_row")
    assert gw.staged_problems() == {}
    assert gw.main(["x", "--staged"]) == 0


def test_a_hand_added_or_moved_data_row_is_refused(repo, capsys):
    write(repo, DATA, DATA_HEAD + ROW_A + ROW_B)
    assert list(gw.staged_problems()) == ["data_row"]
    assert gw.main(["x", "--staged"]) == 1
    assert "tools/add_data_match.py" in capsys.readouterr().err
    write(repo, DATA, DATA_HEAD + ROW_A.replace("game/a.cpp", "game/b.cpp"))
    assert gw.staged_problems()["data_row"][0].endswith("game/b.cpp|matched")


def test_deleting_a_row_or_editing_its_evidence_is_not_refused(repo):
    write(repo, DATA, DATA_HEAD + ROW_A.replace("old evidence", "new evidence"))
    assert gw.staged_problems() == {}
    write(repo, DATA, DATA_HEAD)
    assert gw.staged_problems() == {}


def test_a_stamp_from_another_write_does_not_cover_this_one(repo):
    gw.stamp("data_row", DATA_HEAD, DATA_HEAD + ROW_B)
    write(repo, DATA, DATA_HEAD + ROW_A + ROW_B.replace("0x01000004", "0x01000008"))
    assert "data_row" in gw.staged_problems()


def test_merges_are_skipped(repo):
    write(repo, DATA, DATA_HEAD + ROW_A + ROW_B)
    head = git(repo, "rev-parse", "HEAD").strip()
    (repo / ".git" / "MERGE_HEAD").write_text(head + "\n")
    assert gw.main(["x", "--staged"]) == 0


def test_add_data_match_stamps_its_write():
    text = (Path(__file__).resolve().parents[1] / "add_data_match.py").read_text()
    assert 'gate_writers.stamp("data_row", existing, candidate)' in text
