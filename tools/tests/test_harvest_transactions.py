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
    # harvest.py imports fleet_run (in-flight leases) and re_log (quarantine
    # verdicts) and runs retired_guard; without them every test here died on
    # ModuleNotFoundError before reaching what it meant to test
    shutil.copy2(TOOLS / "fleet_run.py", root / "tools/fleet_run.py")
    shutil.copy2(TOOLS / "fleet_cgroup.py", root / "tools/fleet_cgroup.py")
    (root / "tools/re_log.py").write_text(
        "import sys\nfrom pathlib import Path\n"
        "if sys.argv[1:2] == ['record']:\n"
        "    with (Path(__file__).resolve().parents[1] / 'reverse/re_attempts.log').open('a') as h:\n"
        "        h.write(' '.join(sys.argv[2:]) + chr(10))\n")
    (root / "tools/retired_guard.py").write_text("# nothing is retired in this fixture\n")
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
    # a changed cited source is staged only once it byte-verifies on its own
    (root / "build.sh").write_text('echo "Functions: OK"\n', newline="\n")
    (root / ".gitignore").write_text("build/\nbuild.sh\nreverse/.*.lock\nhooks/\n")
    git(root, "add", "--", "tools", "reverse", "Code", ".gitignore")
    git(root, "commit", "-m", "fixture")
    remote = tmp_path / "remote.git"
    git(tmp_path, "clone", "--bare", str(root), str(remote))
    git(root, "remote", "add", "origin", str(remote))
    git(root, "fetch", "origin")
    return root, remote


def harvest(root):
    # the fixture's remote is a bare directory: `gh api` cannot fast-forward it
    return subprocess.run([sys.executable, "tools/fleet/harvest.py", "test harvest"],
                          cwd=root, capture_output=True, text=True, timeout=45,
                          env=dict(os.environ, HARVEST_NO_GH="1"))


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


def test_own_leftover_index_is_recovered_not_refused(repository):
    """A harvest that died between staging and commit left its index behind;
    every later pass refused it as another writer's (2026-09-18, three days)."""
    root, remote = repository
    (root / "reverse/re_attempts.log").write_text("late evidence\n")
    git(root, "add", "reverse/re_attempts.log")
    (root / "build/.harvest_staged").write_text("1234")
    result = harvest(root)
    assert result.returncode == 0, result.stdout + result.stderr
    assert "unstaging the leftovers" in result.stdout
    assert "late evidence" in git(remote, "show", "master:reverse/re_attempts.log")
    assert not (root / "build/.harvest_staged").exists()


def test_source_outside_the_official_tree_is_quarantined_not_fatal(repository):
    root, remote = repository
    (root / "Code/stlport").mkdir()
    (root / "Code/stlport/bad.cpp").write_text("int bad(){return 2;}\n")
    (root / "Code/GameEngine").mkdir()
    (root / "Code/GameEngine/good.cpp").write_text("int good(){return 3;}\n")
    with (root / "reverse/functions.csv").open("a") as ledger:
        ledger.write("bad,,0x2000,8,Code/stlport/bad.cpp,matched,\n"
                     "good,,0x3000,8,Code/GameEngine/good.cpp,matched,\n")
    result = harvest(root)
    assert result.returncode == 0, result.stdout + result.stderr
    pushed = git(remote, "show", "master:reverse/functions.csv")
    assert "good.cpp" in pushed and "bad.cpp" not in pushed
    assert (root / "build/quarantine/Code/stlport/bad.cpp").exists()
    assert "placement" in (root / "reverse/re_attempts.log").read_text()


def test_hands_needed_exit_writes_an_alarm_line(repository):
    root, _ = repository
    (root / "private.txt").write_text("another writer")
    git(root, "add", "private.txt")
    assert harvest(root).returncode != 0
    assert "another writer" in (root / "build/fleet_logs/harvest_alarm.log").read_text()
