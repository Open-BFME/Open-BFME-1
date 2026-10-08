#!/usr/bin/env python3
"""Stdlib integration test for tools/setup_local_fleet.py."""
import json
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
TOOL = ROOT / "tools" / "setup_local_fleet.py"


def run(*args, cwd=None):
    return subprocess.run(args, cwd=cwd, check=True, text=True,
                          capture_output=True).stdout.strip()


def test_setup_is_idempotent_and_isolates_writers(tmp_path):
    source, fleet = tmp_path / "source", tmp_path / "fleet"
    source.mkdir()
    run("git", "init", "-b", "codex/test", cwd=source)
    run("git", "config", "user.name", "Fleet Test", cwd=source)
    run("git", "config", "user.email", "fleet@example.invalid", cwd=source)
    run("git", "remote", "add", "origin", "https://example.invalid/old.git",
        cwd=source)
    (source / "README").write_text("fixture\n", encoding="utf-8")
    run("git", "add", "README", cwd=source)
    run("git", "commit", "-m", "fixture", cwd=source)

    origin = "https://example.invalid/Open-BFME.git"
    first = run(sys.executable, str(TOOL), "--source", str(source),
                "--root", str(fleet), "--workers", "2",
                "--origin", origin)

    repos = (source, fleet / "writer-2", fleet / "writer-3")
    for repo in repos:
        gitdir = Path(run("git", "-C", str(repo), "rev-parse",
                          "--path-format=absolute", "--git-dir"))
        (gitdir / "openbfme-worker.json").write_text(
            '{"slot": 1, "pool": 5}\n', encoding="utf-8")

    second = run(sys.executable, str(TOOL), "--source", str(source),
                 "--root", str(fleet), "--workers", "2",
                 "--origin", origin)
    assert first and second

    manifest = json.loads((fleet / "fleet.json").read_text())
    assert [w["role"] for w in manifest["workers"]] == [
        "primary", "writer", "writer"]
    assert [w["path"] for w in manifest["workers"]] == [str(r) for r in repos]
    assert all("slot" not in w and "pool" not in w for w in manifest["workers"])
    for repo in repos:
        gitdir = Path(run("git", "-C", str(repo), "rev-parse",
                          "--path-format=absolute", "--git-dir"))
        assert not (gitdir / "openbfme-worker.json").exists()
        assert run("git", "-C", str(repo), "remote", "get-url", "origin") == origin
        assert run("git", "-C", str(repo), "config", "pull.rebase") == "true"
        assert run("git", "-C", str(repo), "config", "merge.union.driver") == \
            "sh .githooks/run-python3 tools/merge_rows.py %O %A %B %P"
