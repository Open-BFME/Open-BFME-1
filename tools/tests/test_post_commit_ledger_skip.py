"""post-commit re-checks the ledger only for commits pre-commit did not verify.

pre-commit records the tree it verified (check_csv --staged and b_pin_check
--staged both ran on it); post-commit skips ledger_after_rewrite.py only when
the new commit's tree is exactly that tree. Cherry-picks, rebases and
--no-verify commits never carry a matching record, so they are still checked.
"""
import os
from pathlib import Path
import shutil
import subprocess

HOOK = Path(__file__).resolve().parents[2] / ".githooks" / "post-commit"


def git(repo, *args):
    return subprocess.run(["git", *args], cwd=repo, check=True, capture_output=True, text=True).stdout.strip()


def repo(tmp_path):
    root = tmp_path / "r"
    (root / "tools").mkdir(parents=True)
    (root / "targets/game/reverse").mkdir(parents=True)
    git(root, "init", "-q", "-b", "master")
    git(root, "config", "user.name", "t"); git(root, "config", "user.email", "t@t")
    (root / "tools/ledger_after_rewrite.py").write_text(
        "import sys\nopen('ran.txt','a').write(sys.argv[1] + '\\n')\n")
    (root / ".gitignore").write_text("ran.txt\n")
    (root / "targets/game/reverse/functions.csv").write_text("name\n")
    git(root, "add", "-A"); git(root, "commit", "-q", "-m", "base")
    return root


def commit_ledger_change(root, text):
    (root / "targets/game/reverse/functions.csv").write_text(text)
    git(root, "add", "-A"); git(root, "commit", "-q", "--no-verify", "-m", "change")


def run_hook(root):
    env = {k: v for k, v in os.environ.items() if not k.startswith("GIT_")}
    subprocess.run(["bash", str(HOOK)], cwd=root, check=True, env=env)
    ran = root / "ran.txt"
    return ran.read_text().splitlines() if ran.exists() else []


def record(root, tree):
    (root / git(root, "rev-parse", "--git-path", "bfme-ledger-verified-tree")).write_text(tree + "\n")


def test_unverified_commit_is_rechecked(tmp_path):
    root = repo(tmp_path)
    commit_ledger_change(root, "name\nrow\n")
    assert run_hook(root) == ["post-commit"]


def test_commit_of_the_verified_tree_is_not_rechecked(tmp_path):
    root = repo(tmp_path)
    commit_ledger_change(root, "name\nrow\n")
    record(root, git(root, "rev-parse", "HEAD^{tree}"))
    assert run_hook(root) == []
    # the record is consumed: a later commit is checked again
    assert not (root / git(root, "rev-parse", "--git-path", "bfme-ledger-verified-tree")).exists()


def test_record_of_another_tree_does_not_skip(tmp_path):
    root = repo(tmp_path)
    record(root, git(root, "rev-parse", "HEAD^{tree}"))  # the base tree, then a different commit
    commit_ledger_change(root, "name\nother\n")
    assert run_hook(root) == ["post-commit"]


def test_pre_commit_records_only_after_both_ledger_checks():
    # the record must be written at the final OK and only when b_pin_check ran
    text = (HOOK.parent / "pre-commit").read_text()
    cleared = text.index('rm -f "$receipt"')
    snapshot = text.index('checked_tree="$(git write-tree')
    write = text.index('mv -f "$receipt.tmp.$$" "$receipt"')
    # stale receipts go first; the tree is captured before the reused checks read it
    # (the layout-migration path runs its own checks earlier and exits without a receipt)
    assert cleared < snapshot < text.rindex("python3 tools/check_csv.py --staged || fail \"ledger integrity")
    assert text.index("b_pin_ran=1") < write
    assert write < text.index('echo "PRE-COMMIT OK (ledger integrity')
