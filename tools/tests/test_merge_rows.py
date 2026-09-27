"""The ledger merge driver registered as git's `union` (tools/merge_rows.py)."""
import subprocess
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import merge_rows as M  # noqa: E402

H = b"name,target_rva\n"


def sides(tmp_path, base, ours, theirs):
    paths = [tmp_path / n for n in ("base", "ours", "theirs")]
    for path, data in zip(paths, (base, ours, theirs)):
        path.write_bytes(data)
    return [str(p) for p in paths]


def plain_union(tmp_path, *three):
    base, ours, theirs = sides(tmp_path, *three)
    return subprocess.run(["git", "merge-file", "-p", "--union", ours, base, theirs],
                          check=True, capture_output=True).stdout


def driver(tmp_path, *three):
    base, ours, theirs = sides(tmp_path, *three)
    assert M.main([base, ours, theirs, "functions.csv"]) == 0
    return Path(ours).read_bytes()


def test_a_row_upstream_retracted_stays_gone_beside_your_edit(tmp_path):
    three = (H + b"R,1\nS,2\n", H + b"S,2\n", H + b"R,1\nS,3\n")
    assert plain_union(tmp_path, *three) == H + b"S,2\nR,1\nS,3\n"
    assert driver(tmp_path, *three) == H + b"S,3\n"


def test_neighbouring_edits_keep_only_the_new_rows(tmp_path):
    three = (H + b"X,1\nY,2\n", H + b"X,9\nY,2\n", H + b"X,1\nY,8\n")
    assert plain_union(tmp_path, *three) == H + b"X,9\nY,2\nX,1\nY,8\n"
    assert driver(tmp_path, *three) == H + b"X,9\nY,8\n"


def test_a_row_both_sides_added_is_kept_once(tmp_path):
    three = (H, H + b"N,5\nP,6\n", H + b"Q,7\nN,5\n")
    assert plain_union(tmp_path, *three) == H + b"N,5\nP,6\nQ,7\nN,5\n"
    assert driver(tmp_path, *three) == H + b"N,5\nP,6\nQ,7\n"


def test_a_row_both_sides_edited_keeps_both_versions_for_check_csv(tmp_path):
    three = (H + b"S,2\n", H + b"S,3\n", H + b"S,4\n")
    assert driver(tmp_path, *three) == plain_union(tmp_path, *three) == H + b"S,3\nS,4\n"


def test_terminators_survive_and_an_lf_copy_is_not_a_second_row(tmp_path):
    c = b"name,target_rva\r\n"
    three = (c + b"A,1\r\r\nB,2\r\n",
             c + b"A,1\r\r\nB,2\r\nC,3\r\n",
             c + b"A,1\r\r\nB,2\nD,4\n")
    assert plain_union(tmp_path, *three) == c + b"A,1\r\r\nB,2\r\nC,3\r\nB,2\nD,4\n"
    assert driver(tmp_path, *three) == c + b"A,1\r\r\nB,2\r\nC,3\r\nD,4\n"


def test_a_failed_union_leaves_a_conflict(tmp_path):
    base, ours, theirs = sides(tmp_path, H, H, H)
    Path(base).unlink()
    assert M.main([base, ours, theirs, "functions.csv"]) == 1


def test_a_rebase_uses_the_driver_registered_as_union(tmp_path):
    def git(*args):
        return subprocess.run(["git", *args], cwd=tmp_path, check=True, capture_output=True, text=True)
    git("init", "-q", "-b", "master")
    git("config", "user.email", "t@example.com")
    git("config", "user.name", "t")
    git("config", "merge.union.driver", f'"{sys.executable}" "{TOOLS / "merge_rows.py"}" %O %A %B %P')
    (tmp_path / ".gitattributes").write_text("functions.csv merge=union\n")
    ledger = tmp_path / "functions.csv"
    ledger.write_bytes(H + b"R,1\nS,2\n")
    git("add", ".")
    git("commit", "-qm", "base")
    git("checkout", "-qb", "mine")
    ledger.write_bytes(H + b"R,1\nS,3\n")
    git("commit", "-qam", "edit S")
    git("checkout", "-q", "master")
    ledger.write_bytes(H + b"S,2\n")
    git("commit", "-qam", "retract R")
    git("checkout", "-q", "mine")
    rebase = git("rebase", "master")
    assert ledger.read_bytes() == H + b"S,3\n"
    assert "dropped 2 line(s)" in rebase.stderr
