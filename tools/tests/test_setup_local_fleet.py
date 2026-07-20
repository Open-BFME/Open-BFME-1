#!/usr/bin/env python3
"""Stdlib integration test for tools/setup_local_fleet.py."""
import json
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
TOOL = ROOT / "tools" / "setup_local_fleet.py"


def run(*args, cwd=None):
    return subprocess.run(args, cwd=cwd, check=True, text=True,
                          capture_output=True).stdout.strip()


def main():
    with tempfile.TemporaryDirectory(dir=ROOT / "build") as tmp:
        tmp = Path(tmp)
        source, fleet = tmp / "source", tmp / "fleet"
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
                    "--root", str(fleet), "--workers", "2", "--pool", "5",
                    "--origin", origin)
        second = run(sys.executable, str(TOOL), "--source", str(source),
                     "--root", str(fleet), "--workers", "2", "--pool", "5",
                     "--origin", origin)
        assert first and second

        manifest = json.loads((fleet / "fleet.json").read_text())
        assert [w["slot"] for w in manifest["workers"]] == [1, 2, 3, 4, 5]
        assert [w["role"] for w in manifest["workers"]] == [
            "writer-primary", "writer", "writer", "scout", "scout"]
        for slot, repo in ((1, source), (2, fleet / "writer-2"),
                           (3, fleet / "writer-3")):
            gitdir = Path(run("git", "-C", str(repo), "rev-parse",
                              "--path-format=absolute", "--git-dir"))
            config = json.loads((gitdir / "openbfme-worker.json").read_text())
            assert (config["slot"], config["pool"]) == (slot, 5)
            assert run("git", "-C", str(repo), "remote", "get-url", "origin") == origin
            assert run("git", "-C", str(repo), "config", "pull.rebase") == "true"
    print("PASS local fleet: idempotent setup, isolated writers, deterministic slots")


if __name__ == "__main__":
    main()
