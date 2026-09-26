"""Exercise target hook selection and snapshot checks in real isolated Git repos."""
import csv
import importlib.util
import io
import json
import os
from pathlib import Path
import shutil
import subprocess
import sys

import pytest


TOOLS = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location("target_hooks", TOOLS / "target_hooks.py")
H = importlib.util.module_from_spec(spec)
spec.loader.exec_module(H)
SOURCE = "Code/Tools/WorldBuilder/src/Example.cpp"
SHARED = "Code/GameEngine/Shared.cpp"


def git(root, *args):
    return subprocess.run(["git", *args], cwd=root, check=True, capture_output=True, text=True).stdout.strip()


def put(root, path, content):
    dest = root / path
    dest.parent.mkdir(parents=True, exist_ok=True)
    dest.write_text(content, encoding="utf-8")


def ledger(root, sources):
    out = io.StringIO()
    writer = csv.DictWriter(out, fieldnames=sorted(H.REQUIRED))
    writer.writeheader()
    for index, source in enumerate(sources):
        writer.writerow(dict(name=f"?function{index}@@YAXXZ", target_rva=hex(0x1000 + index * 32),
                             target_size="16", status="matched", source=source,
                             profile="editor-size", evidence="export", model="fixture"))
    put(root, H.LEDGER, out.getvalue())


@pytest.fixture
def repo(tmp_path):
    git(tmp_path, "init", "-q")
    git(tmp_path, "config", "user.name", "Fixture")
    git(tmp_path, "config", "user.email", "fixture@example.invalid")
    for path in H.CHECKERS:
        put(tmp_path, path, "raise SystemExit(0)\n")
    shutil.copyfile(TOOLS / "target_hooks.py", tmp_path / "tools/target_hooks.py")
    put(tmp_path, "tools/worldbuilder.py", '''import csv, pathlib, sys
root = pathlib.Path('.')
with open('calls', 'a') as out: out.write(sys.argv[1] + '\\n')
rows = list(csv.DictReader(open('reverse/worldbuilder/functions.csv')))
claimed = {row['source'] for row in rows}
import subprocess
owned = {path for path in subprocess.check_output(['git', 'ls-files'], text=True).splitlines()
         if path.startswith(('Code/Tools/WorldBuilder/', 'targets/worldbuilder/Code/')) and path.endswith('.cpp')}
if owned - claimed:
    raise SystemExit('unclaimed target source')
if any('BAD' in pathlib.Path(path).read_text() for path in claimed):
    raise SystemExit('byte verification failed')
''')
    put(tmp_path, H.CONFIG, json.dumps({"image": {"path": "image.exe"}}))
    put(tmp_path, "image.exe", "fixture binary")
    put(tmp_path, "reverse/functions.csv", "source,status\n")
    ledger(tmp_path, [])
    git(tmp_path, "add", "tools", "targets", "reverse", "image.exe")
    git(tmp_path, "commit", "-qm", "fixture foundation")
    return tmp_path


def add_source(repo, source=SOURCE, shared=False):
    put(repo, source, "void function() {}\n")
    ledger(repo, [source])
    paths = [source, H.LEDGER]
    if shared:
        put(repo, "reverse/functions.csv", f"source,status\n{source},matched\n")
        paths.append("reverse/functions.csv")
    git(repo, "add", *paths)


def calls(repo):
    return (repo / "calls").read_text().splitlines() if (repo / "calls").exists() else []


def test_worldbuilder_source_is_verified_and_excluded_from_game(repo):
    add_source(repo)
    out = repo / "exclusive"
    assert H.run(repo, ":", "HEAD", out)
    assert calls(repo) == ["check", "verify"]
    assert out.read_text().splitlines() == [SOURCE]


def test_shared_source_remains_in_both_targets(repo):
    add_source(repo, SHARED, shared=True)
    out = repo / "exclusive"
    assert H.run(repo, ":", "HEAD", out)
    assert calls(repo) == ["check", "verify"]
    assert not out.read_text()


def test_staged_source_with_unstaged_edits_fails_before_compilation(repo):
    add_source(repo)
    put(repo, SOURCE, "BAD unstaged body\n")
    with pytest.raises(H.HookError, match="staged index"):
        H.run(repo, ":", "HEAD")
    assert not calls(repo)


def test_unrelated_dirty_game_source_is_not_verified(repo):
    put(repo, SHARED, "game source\n")
    git(repo, "add", SHARED)
    git(repo, "commit", "-qm", "game source fixture")
    put(repo, SHARED, "BAD unrelated game body\n")
    add_source(repo)
    assert H.run(repo, ":", "HEAD")
    assert calls(repo) == ["check", "verify"]


def test_shared_header_change_triggers_worldbuilder(repo):
    put(repo, "Code/GameEngine/shared.h", "struct Shared {};\n")
    git(repo, "add", "Code/GameEngine/shared.h")
    assert H.run(repo, ":", "HEAD")
    assert calls(repo) == ["check", "verify"]


def test_dirty_verifier_cannot_approve_staged_code(repo):
    add_source(repo)
    put(repo, "tools/worldbuilder.py", "raise SystemExit(0)\n")
    with pytest.raises(H.HookError, match="tools/worldbuilder.py"):
        H.run(repo, ":", "HEAD")
    assert not calls(repo)


def test_unclaimed_source_cannot_take_the_game_hook_early_exit(repo):
    put(repo, SOURCE, "void unclaimed() {}\n")
    git(repo, "add", SOURCE)
    with pytest.raises(H.HookError, match="Unclaimed"):
        H.run(repo, ":", "HEAD")
    assert not calls(repo)


def test_bad_bytes_block_publishing(repo):
    add_source(repo)
    put(repo, SOURCE, "BAD body\n")
    git(repo, "add", SOURCE)
    with pytest.raises(subprocess.CalledProcessError):
        H.run(repo, ":", "HEAD")


def test_outgoing_commit_must_be_checked_out(repo):
    base = git(repo, "rev-parse", "HEAD")
    add_source(repo)
    git(repo, "commit", "-qm", "target body")
    outgoing = git(repo, "rev-parse", "HEAD")
    put(repo, "other.txt", "later\n")
    git(repo, "add", "other.txt")
    git(repo, "commit", "-qm", "later commit")
    with pytest.raises(H.HookError, match="HEAD"):
        H.run(repo, outgoing, base)
    assert not calls(repo)


def test_outgoing_dirty_source_fails_before_compilation(repo):
    base = git(repo, "rev-parse", "HEAD")
    add_source(repo)
    git(repo, "commit", "-qm", "target body")
    put(repo, SOURCE, "BAD local body\n")
    with pytest.raises(H.HookError, match="differ"):
        H.run(repo, "HEAD", base)
    assert not calls(repo)


def test_unknown_remote_base_still_verifies_target(repo):
    add_source(repo)
    git(repo, "commit", "-qm", "target body")
    assert H.run(repo, "HEAD")
    assert calls(repo) == ["check", "verify"]


def test_malformed_membership_cannot_exempt_game_source(repo):
    put(repo, H.LEDGER, "source,status\nCode/GameEngine/Bad.cpp,matched\n")
    git(repo, "add", H.LEDGER)
    with pytest.raises(H.HookError, match="schema"):
        H.run(repo, ":", "HEAD", repo / "exclusive")
    assert not (repo / "exclusive").exists()


def test_new_source_must_be_staged_with_its_ledger(repo):
    add_source(repo)
    git(repo, "reset", "-q", "HEAD", "--", SOURCE)
    with pytest.raises(H.HookError, match="absent from snapshot"):
        H.run(repo, ":", "HEAD")


def test_game_only_change_does_not_run_worldbuilder(repo):
    put(repo, SHARED, "void game() {}\n")
    git(repo, "add", SHARED)
    assert not H.run(repo, ":", "HEAD")
    assert not calls(repo)


def test_untracked_header_cannot_influence_compilation(repo):
    add_source(repo)
    put(repo, "Code/GameEngine/untracked.h", "struct Untracked {};\n")
    with pytest.raises(H.HookError, match="Untracked"):
        H.run(repo, ":", "HEAD")
    assert not calls(repo)


def hook_fixture(repo):
    for name in ("check_case_collisions", "conversion_gate", "name_regression", "name_oracle",
                 "name_history", "eol_guard", "retired_guard", "check_csv", "pin_consistency",
                 "one_identity", "b_pin_check", "identity_guard", "adopt_header", "delta_sources"):
        put(repo, "tools/" + name + ".py", "raise SystemExit(0)\n")
    put(repo, "tools/find_declared_unmatched.py", "open('game-parser', 'w').write('called')\n")
    put(repo, "build.sh", "#!/usr/bin/env bash\nprintf '%s\\n' \"$@\" > game-build\n")
    (repo / "build.sh").chmod(0o755)
    git(repo, "add", "tools", "build.sh")
    git(repo, "commit", "-qm", "hook fixture")


def invoke_hook(repo, hook, base=None):
    bash = shutil.which("bash")
    if not bash:
        pytest.skip("Bash is required to exercise hooks")
    head = git(repo, "rev-parse", "HEAD")
    refs = f"refs/heads/main {head} refs/heads/main {base}\n" if hook == "pre-push" else ""
    return subprocess.run([bash, str(TOOLS.parent / ".githooks" / hook)], cwd=repo,
                          input=refs, capture_output=True, text=True)


def test_real_precommit_verifies_editor_before_game_early_exit(repo):
    hook_fixture(repo)
    add_source(repo)
    result = invoke_hook(repo, "pre-commit")
    assert result.returncode == 0, result.stderr
    assert calls(repo) == ["check", "verify"]
    assert not (repo / "game-parser").exists()
    assert not (repo / "game-build").exists()


def test_real_precommit_verifies_shared_source_in_both_targets(repo):
    hook_fixture(repo)
    add_source(repo, SHARED, shared=True)
    result = invoke_hook(repo, "pre-commit")
    assert result.returncode == 0, result.stderr
    assert calls(repo) == ["check", "verify"]
    assert (repo / "game-parser").exists()
    assert SHARED in (repo / "game-build").read_text()


def test_real_precommit_refuses_unclaimed_editor_source(repo):
    hook_fixture(repo)
    put(repo, SOURCE, "void unclaimed() {}\n")
    git(repo, "add", SOURCE)
    result = invoke_hook(repo, "pre-commit")
    assert result.returncode != 0
    assert "WorldBuilder target verification" in result.stderr
    assert not (repo / "game-build").exists()


def test_real_prepush_verifies_worldbuilder_only_commit(repo):
    hook_fixture(repo)
    base = git(repo, "rev-parse", "HEAD")
    add_source(repo)
    git(repo, "commit", "-qm", "editor body")
    result = invoke_hook(repo, "pre-push", base)
    assert result.returncode == 0, result.stderr
    assert calls(repo) == ["check", "verify"]
    assert not (repo / "game-build").exists()


def test_imported_checker_dependency_is_snapshot_bound(repo):
    put(repo, "tools/compiler_helper.py", "flags = 'good'\n")
    put(repo, "tools/coffar.py", "import compiler_helper\n")
    git(repo, "add", "tools/compiler_helper.py", "tools/coffar.py")
    git(repo, "commit", "-qm", "compiler helper fixture")
    add_source(repo)
    put(repo, "tools/compiler_helper.py", "flags = 'BAD unstaged flags'\n")
    with pytest.raises(H.HookError, match="compiler_helper"):
        H.run(repo, ":", "HEAD")
    assert not calls(repo)


def test_worker_target_is_cleared_only_inside_publication_hook(repo, monkeypatch):
    hook_fixture(repo)
    guard = "import os\nassert 'BFME_TARGET' not in os.environ\nassert 'BFME_TARGET_SHA256' not in os.environ\n"
    put(repo, "tools/check_csv.py", guard)
    git(repo, "add", "tools/check_csv.py")
    git(repo, "commit", "-qm", "guard fixture")
    add_source(repo, SHARED, shared=True)
    monkeypatch.setenv("BFME_TARGET", "worldbuilder")
    monkeypatch.setenv("BFME_TARGET_SHA256", "worker hash")
    result = invoke_hook(repo, "pre-commit")
    assert result.returncode == 0, result.stderr
    assert os.environ["BFME_TARGET"] == "worldbuilder"
    assert calls(repo) == ["check", "verify"]
    assert SHARED in (repo / "game-build").read_text()


def test_game_source_scan_exempts_only_validated_target_membership(tmp_path, monkeypatch, capsys):
    monkeypatch.syspath_prepend(str(TOOLS))
    import build
    import target_hooks
    put(tmp_path, SOURCE, "void editor() {}\n")
    put(tmp_path, SHARED, "void shared() {}\n")
    monkeypatch.setattr(build, "ROOT", tmp_path)
    monkeypatch.setattr(build, "load_function_rows", lambda: [
        {"source": SHARED, "name": "?shared@@YAXXZ"}])
    checked = []
    def validated(root):
        checked.append(root)
        return {SOURCE, SHARED}
    monkeypatch.setattr(target_hooks, "validated_worldbuilder_sources", validated)
    build.verify_source_claims()
    assert checked == [tmp_path]
    assert "1 sources" in capsys.readouterr().out
    put(tmp_path, "Code/GameEngine/unclaimed.cpp", "void unclaimed() {}\n")
    with pytest.raises(SystemExit):
        build.verify_source_claims()
    assert "ZERO matched rows" in capsys.readouterr().out


def test_game_source_scan_cannot_use_invalid_target_claims(tmp_path, monkeypatch):
    monkeypatch.syspath_prepend(str(TOOLS))
    import build
    import target_hooks
    put(tmp_path, SOURCE, "void editor() {}\n")
    monkeypatch.setattr(build, "ROOT", tmp_path)
    monkeypatch.setattr(build, "load_function_rows", lambda: [])
    def invalid(root):
        raise ValueError("invalid target identity")
    monkeypatch.setattr(target_hooks, "validated_worldbuilder_sources", invalid)
    with pytest.raises(ValueError, match="identity"):
        build.verify_source_claims()


@pytest.mark.parametrize("suffix", ["cpp", "c", "cc", "cxx", "asm", "s"])
def test_other_worker_untracked_translation_unit_does_not_block_landing(repo, suffix):
    add_source(repo)
    put(repo, f"Code/Tools/WorldBuilder/src/OtherWorker.{suffix}", "unfinished work\n")
    assert H.run(repo, ":", "HEAD")
    assert calls(repo) == ["check", "verify"]


@pytest.mark.parametrize("suffix", ["cpp", "c", "cc", "cxx", "asm", "s"])
def test_staged_unclaimed_translation_unit_is_rejected_from_snapshot(repo, suffix):
    add_source(repo)
    path = f"targets/worldbuilder/Code/GameEngine/Unclaimed.{suffix}"
    put(repo, path, "unfinished work\n")
    git(repo, "add", path)
    with pytest.raises(H.HookError, match="Unclaimed"):
        H.run(repo, ":", "HEAD")
    assert not calls(repo)


def test_dirty_donor_source_is_rejected_before_identity_verification(repo):
    donor = H.DONOR_ROOT + "src/WorldBuilderView.cpp"
    put(repo, donor, "donor identity evidence\n")
    git(repo, "add", donor)
    git(repo, "commit", "-qm", "donor fixture")
    add_source(repo)
    put(repo, donor, "uncommitted donor identity change\n")
    with pytest.raises(H.HookError, match="WorldBuilderView.cpp"):
        H.run(repo, ":", "HEAD")
    assert not calls(repo)


def test_additional_manifest_donor_is_a_snapshot_dependency(repo):
    donor = "reference/NewDonor/Editor.cpp"
    put(repo, donor, "donor identity evidence\n")
    put(repo, "reverse/worldbuilder/provenance.json", json.dumps({"donor": {"files": [{"path": donor}]}}))
    git(repo, "add", donor, "reverse/worldbuilder/provenance.json")
    git(repo, "commit", "-qm", "additional donor fixture")
    add_source(repo)
    put(repo, donor, "uncommitted identity change\n")
    with pytest.raises(H.HookError, match="Editor.cpp"):
        H.run(repo, ":", "HEAD")
    assert not calls(repo)


@pytest.mark.parametrize("path", ["targets/worldbuilder/references.json", "targets/worldbuilder/dependencies/mfc71.csv",
                                  "reverse/worldbuilder/provenance.json"])
def test_reference_and_dependency_metadata_are_snapshot_bound(repo, path):
    put(repo, path, "{}\n")
    git(repo, "add", path)
    git(repo, "commit", "-qm", "metadata fixture")
    add_source(repo)
    put(repo, path, '{"unstaged": true}\n')
    with pytest.raises(H.HookError, match="differ"):
        H.run(repo, ":", "HEAD")
    assert not calls(repo)


def test_staged_donor_only_change_rechecks_worldbuilder_identity(repo):
    donor = H.DONOR_ROOT + "src/WorldBuilderView.cpp"
    put(repo, donor, "donor identity evidence\n")
    git(repo, "add", donor)
    git(repo, "commit", "-qm", "donor fixture")
    put(repo, donor, "changed donor identity evidence\n")
    git(repo, "add", donor)
    assert H.run(repo, ":", "HEAD")
    assert calls(repo) == ["check", "verify"]
