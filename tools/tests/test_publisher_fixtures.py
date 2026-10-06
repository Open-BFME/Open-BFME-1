"""The publisher's exploit-fixture sets: well formed, and generated fresh."""
import json
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS / "publisher_fixtures"))
import make_fixtures  # noqa: E402

CASES = sorted((TOOLS / "publisher_fixtures").glob("*/cases.json"))


def test_there_is_a_fixture_set_for_this_repository():
    assert CASES


@pytest.mark.parametrize("path", CASES, ids=[p.parent.name for p in CASES])
def test_each_set_has_exploits_and_benign_controls(path):
    cases = json.loads(path.read_text(encoding="utf-8"))
    names = [c["name"] for c in cases]
    assert len(names) == len(set(names))
    kinds = [c["expect"] for c in cases]
    assert set(kinds) == {"reject", "pass"} and kinds.count("reject") >= 3
    for case in cases:
        assert case["why"] and case["message"] and case["edits"]
        for edit in case["edits"]:
            assert edit["path"] and not edit["path"].startswith(("/", ".."))
            assert sum(k in edit for k in ("write", "append", "old")) == 1
            assert ("old" in edit) == ("new" in edit)
    # a self-weakening case: the candidate edits the checker it would be judged by
    assert any(e["path"].startswith(("tools/", ".githooks/")) for c in cases if c["expect"] == "reject"
               for e in c["edits"])
    assert (path.parent / "ledger.sh").exists()


def test_the_generator_builds_patches_and_refuses_stale_cases(tmp_path):
    repo = tmp_path / "repo"
    run = lambda *a: subprocess.run(["git", *a], cwd=repo, check=True, capture_output=True)  # noqa: E731
    repo.mkdir()
    run("init", "-q")
    (repo / "a.txt").write_text("one\n")
    run("add", "a.txt")
    run("-c", "user.name=t", "-c", "user.email=", "commit", "-qm", "base")
    cases = tmp_path / "cases.json"
    cases.write_text(json.dumps([
        {"name": "edit", "expect": "reject", "why": "w", "message": "m",
         "edits": [{"path": "a.txt", "old": "one", "new": "two"}, {"path": "b/new.txt", "write": "x"}]},
        {"name": "control", "expect": "pass", "why": "w", "message": "m",
         "edits": [{"path": "a.txt", "append": "more\n"}]}]))
    manifest = make_fixtures.build(cases, tmp_path / "out", repo=repo)
    assert [m["expect"] for m in manifest] == ["reject", "pass"]
    patch = (tmp_path / "out" / "edit.patch").read_text()
    assert "+two" in patch and "b/new.txt" in patch
    assert json.loads((tmp_path / "out" / "fixtures.json").read_text()) == manifest
    stale = tmp_path / "stale.json"
    stale.write_text(json.dumps([{"name": "s", "expect": "reject", "why": "w", "message": "m",
                                  "edits": [{"path": "a.txt", "old": "gone", "new": "x"}]}]))
    with pytest.raises(RuntimeError, match="no longer contains"):
        make_fixtures.build(stale, tmp_path / "out2", repo=repo)
