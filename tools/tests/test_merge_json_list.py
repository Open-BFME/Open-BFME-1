"""The JSON-list merge driver for name_corrections.json (tools/merge_json_list.py)."""
import json
import subprocess
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import merge_json_list as M  # noqa: E402


def e(n):
    return {"old_name": f"old{n}", "new_name": f"new{n}"}


def test_both_sides_appending_keeps_both_in_order():
    assert M.merge([e(1)], [e(1), e(2)], [e(1), e(3)]) == [e(1), e(2), e(3)]


def test_a_deletion_on_either_side_survives():
    assert M.merge([e(1), e(2)], [e(1), e(2), e(4)], [e(2)]) == [e(2), e(4)]
    assert M.merge([e(1), e(2)], [e(2)], [e(1), e(2), e(3)]) == [e(2), e(3)]


def test_the_same_entry_added_twice_is_kept_once():
    assert M.merge([], [e(5)], [e(5)]) == [e(5)]


def test_driver_keeps_ours_layout_and_refuses_non_lists(tmp_path):
    base, ours, theirs = (tmp_path / n for n in ("base", "ours", "theirs"))
    base.write_bytes(b"[]\r\n")
    ours.write_bytes(json.dumps([e(1)], indent=1).replace("\n", "\r\n").encode() + b"\r\n")
    theirs.write_bytes(b'[{"old_name": "old2", "new_name": "new2"}]')
    assert M.main([str(base), str(ours), str(theirs)]) == 0
    raw = ours.read_bytes()
    assert json.loads(raw) == [e(1), e(2)] and raw.startswith(b"[\r\n {")
    theirs.write_bytes(b'{"not": "a list"}')
    assert M.main([str(base), str(ours), str(theirs)]) == 1


def test_git_uses_the_driver_for_concurrent_appends(tmp_path):
    def git(*args):
        return subprocess.run(["git", *args], cwd=tmp_path, check=True, capture_output=True, text=True).stdout
    git("init", "-q", "-b", "master")
    git("config", "user.email", "t@example.com")
    git("config", "user.name", "t")
    git("config", "merge.jsonlist.driver", f'"{sys.executable}" "{TOOLS / "merge_json_list.py"}" %O %A %B')
    (tmp_path / ".gitattributes").write_text("c.json merge=jsonlist\n")
    (tmp_path / "c.json").write_text(json.dumps([e(1)], indent=1) + "\n")
    git("add", ".")
    git("commit", "-qm", "base")
    git("checkout", "-qb", "side")
    (tmp_path / "c.json").write_text(json.dumps([e(1), e(3)], indent=1) + "\n")
    git("commit", "-qam", "side")
    git("checkout", "-q", "master")
    (tmp_path / "c.json").write_text(json.dumps([e(1), e(2)], indent=1) + "\n")
    git("commit", "-qam", "master")
    git("merge", "-q", "side", "-m", "merge")
    assert json.loads((tmp_path / "c.json").read_text()) == [e(1), e(2), e(3)]
