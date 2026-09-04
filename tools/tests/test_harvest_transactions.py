"""Exercise publication against isolated real Git repositories, never the fleet."""
import os
from pathlib import Path
import shutil
import subprocess
import sys

import pytest

TOOLS = Path(__file__).resolve().parents[1]


def git(repo, *args):
    return subprocess.check_output(["git", "-C", str(repo), *args], text=True).strip()


@pytest.fixture
def repository(tmp_path):
    root = tmp_path / "repo"
    root.mkdir()
    git(root, "init", "-b", "master")
    git(root, "config", "user.name", "Test")
    git(root, "config", "user.email", "test@example.invalid")
    for name in ("tools/fleet", "reverse", "Code", "build"):
        (root / name).mkdir(parents=True)
    shutil.copy2(TOOLS / "fleet/harvest.py", root / "tools/fleet/harvest.py")
    shutil.copy2(TOOLS / "portable_lock.py", root / "tools/portable_lock.py")
    (root / "tools/fleet/ledger_prep.py").write_text("# no repairs needed in this fixture\n")
    (root / "tools/check_csv.py").write_text(
        "from pathlib import Path\nimport sys\n"
        "root = Path(__file__).resolve().parents[1]\n"
        "sys.exit(1 if (root / 'BAD').exists() else 0)\n")
    for path in ("tools/dedup_csv.py", "tools/fleet/dedup_keepfirst.py"):
        (root / path).write_text("# bad fixture cannot be mechanically repaired\n")
    (root / "reverse/functions.csv").write_text(
        "name,export_rva,target_rva,target_size,source,status,notes\n"
        "foo,,0x1000,8,Code/foo.cpp,matched,\n")
    (root / "reverse/symbols.csv").write_text("name,address,notes\n")
    (root / "reverse/re_attempts.log").write_text("")
    (root / "Code/foo.cpp").write_text("int foo(){return 1;}\n")
    (root / ".gitignore").write_text("build/\nreverse/.*.lock\nhooks/\n")
    git(root, "add", "--", "tools", "reverse", "Code", ".gitignore")
    git(root, "commit", "-m", "fixture")
    remote = tmp_path / "remote.git"
    git(tmp_path, "clone", "--bare", str(root), str(remote))
    git(root, "remote", "add", "origin", str(remote))
    git(root, "fetch", "origin")
    return root, remote


def harvest(root):
    return subprocess.run([sys.executable, "tools/fleet/harvest.py", "test harvest"],
                          cwd=root, capture_output=True, text=True, timeout=45)


def test_rebased_worktree_validator_blocks_publication(repository, tmp_path):
    root, remote = repository
    publisher = tmp_path / "publisher"
    git(tmp_path, "clone", str(remote), str(publisher))
    git(publisher, "config", "user.name", "Test")
    git(publisher, "config", "user.email", "test@example.invalid")
    (publisher / "BAD").write_text("must be caught in rebased worktree")
    git(publisher, "add", "BAD")
    git(publisher, "commit", "-m", "remote validation failure")
    git(publisher, "push", "origin", "master")
    before = git(remote, "rev-parse", "master")
    (root / "Code/foo.cpp").write_text("int foo(){return 2;}\n")
    result = harvest(root)
    assert result.returncode != 0, result.stdout + result.stderr
    assert "rebased ledgers fail check_csv" in result.stderr
    assert git(remote, "rev-parse", "master") == before


def test_network_does_not_hold_landing_lock_and_late_work_survives(repository):
    root, remote = repository
    hooks = root / "hooks"
    hooks.mkdir()
    helper = hooks / "late_worker.py"
    helper.write_text(
        "import sys\nfrom pathlib import Path\n"
        f"root = Path({str(root)!r})\n"
        "sys.path.insert(0, str(root / 'tools'))\nimport portable_lock\n"
        "with (root / 'reverse/.add_match.lock').open('a+') as h:\n"
        "    portable_lock.lock(h, exclusive=True)\n"
        "    (root / 'reverse/re_attempts.log').write_text('late worker evidence\\n')\n"
        "    portable_lock.unlock(h)\n")
    hook = hooks / "pre-push"
    hook.write_text(f'#!/bin/sh\n"{Path(sys.executable).as_posix()}" "{helper.as_posix()}"\n', newline="\n")
    hook.chmod(0o755)
    git(root, "config", "core.hooksPath", str(hooks))
    (root / "Code/foo.cpp").write_text("int foo(){return 2;}\n")
    (root / "Code/unrelated.cpp").write_text("unfinished unrelated source")
    result = harvest(root)
    assert result.returncode == 0, result.stdout + result.stderr
    assert "synchronization deferred" in result.stdout
    assert (root / "reverse/re_attempts.log").read_text() == "late worker evidence\n"
    assert git(remote, "show", "master:Code/foo.cpp") == "int foo(){return 2;}"
    assert "Code/unrelated.cpp" not in git(remote, "ls-tree", "-r", "--name-only", "master")


def test_preexisting_index_is_not_consumed(repository):
    root, _ = repository
    (root / "private.txt").write_text("another writer")
    git(root, "add", "private.txt")
    result = harvest(root)
    assert result.returncode != 0
    assert "existing staged work" in result.stderr
    assert git(root, "diff", "--cached", "--name-only") == "private.txt"


def test_uncommitted_shared_dependency_cannot_contaminate_verification(repository):
    root, remote = repository
    before = git(remote, "rev-parse", "master")
    (root / "Code/local.h").write_text("// unfinished dependency")
    result = harvest(root)
    assert result.returncode != 0
    assert "changed shared dependencies" in result.stderr
    assert git(remote, "rev-parse", "master") == before
