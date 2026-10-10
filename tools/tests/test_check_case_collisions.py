"""check_case_collisions: case-only collisions, and control paths (the root, the
ledger trees, tools/, .githooks/, .github/) that are not lowercase -- in the index
and in a commit, whether or not any base holds the file (GPT-6.1-Sol, converged gate
rounds 7-9). One file for both repositories; it protects both namespaces in each, so
every case below runs the same in Open-BFME-1 and Open-BFME-2."""
import shutil
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import check_case_collisions as C  # noqa: E402

# Open-BFME-2's ledger tree, Open-BFME-1's two targets: named here, not read from the checker
LEDGER_TREES = ("reverse/", "targets/game/reverse/", "targets/worldbuilder/reverse/")


def up(path):
    """`path` with its first component spelled in another case."""
    head, _, rest = path.partition("/")
    return head.title() + "/" + rest


def git(root, *args):
    return subprocess.run(["git", *args], cwd=root, check=True, capture_output=True, text=True).stdout.strip()


def track(root, path, text="x\n"):
    """Stage `path` with its exact spelling, whatever the file system folds."""
    blob = root / "blob.tmp"
    blob.write_text(text, encoding="utf-8")
    sha = git(root, "hash-object", "-w", str(blob))
    git(root, "update-index", "--add", "--cacheinfo", f"100644,{sha},{path}")


def untrack(root, path):
    git(root, "update-index", "--force-remove", path)


@pytest.fixture
def repo(tmp_path, monkeypatch):
    git(tmp_path, "init", "-q")
    git(tmp_path, "config", "user.name", "T")
    git(tmp_path, "config", "user.email", "t@example.invalid")
    monkeypatch.chdir(tmp_path)
    return tmp_path


@pytest.mark.parametrize("rev", LEDGER_TREES)
@pytest.mark.parametrize("name", ["Data_Rows.csv", "Gate_Baseline.txt", "retail_inventory/Fold_List.csv"])
def test_a_ledger_path_not_in_lowercase_is_refused_with_or_without_a_base(repo, rev, name, capsys):
    for variant in (rev + name, up(rev + name.lower()), (rev + name).upper()):
        untrack_all = [p for p in C.tracked_paths()]
        for p in untrack_all:
            untrack(repo, p)
        track(repo, variant)                                  # no base holds it (round 9)
        assert C.miscased(C.tracked_paths()) == [variant]
        assert C.main([]) == 1 and f"rename to {variant.lower()}" in capsys.readouterr().err
    git(repo, "commit", "-qm", "variant")
    assert C.main(["--ref", "HEAD"]) == 1                     # the pushed commit's tree


@pytest.mark.parametrize("variant", ["TOOLS/x.py", ".githooks/Pre-Commit", "Build.sh",
                                     "inputs/baselines/bfme1/retail-1.03-unpacked/Manifest.JSON",
                                     "Inputs/baselines/bfme1/retail-1.03-unpacked/manifest.json",
                                     "targets/WorldBuilder/reverse/functions.csv"])
def test_a_tool_hook_root_or_baseline_path_not_in_lowercase_is_refused(repo, variant):
    track(repo, variant)
    assert C.main([]) == 1
    git(repo, "commit", "-qm", "variant")
    assert C.main(["--ref", "HEAD"]) == 1


@pytest.mark.parametrize("variant", [up("reverse/attempts/0x0048c16c.cpp"), "reverse/Attempts/0x0048c16c.cpp",
                                     "reverse/Attempt_Support/x/manifest.json",
                                     "reverse/Class_Contracts/Coord2D.json",
                                     up("targets/game/reverse/attempts/0x0048c16c.cpp"),
                                     "targets/game/reverse/Identity_Evidence/00161E20-x.json",
                                     "tools/Compat/wibo/LICENSE.wibo"])
def test_an_exempt_tree_spelled_in_another_case_is_control(repo, variant):
    """Round 10: the exemptions matched the lowercased path, so a stash under
    Reverse/attempts/ escaped check_csv's reverse/attempts/ selection."""
    track(repo, variant)
    assert C.main([]) == 1
    git(repo, "commit", "-qm", "variant tree")
    assert C.main(["--ref", "HEAD"]) == 1


@pytest.mark.parametrize("rev", LEDGER_TREES)
def test_a_register_created_deleted_and_recreated_in_another_case_is_refused(repo, rev):
    """Round 9: create the canonical register, delete it, recreate it under another
    case: the tip is what lands, and its spelling is refused whatever came before."""
    track(repo, rev + "gate_baseline.txt")
    git(repo, "commit", "-qm", "create")
    untrack(repo, rev + "gate_baseline.txt")
    git(repo, "commit", "-qm", "delete")
    track(repo, up(rev + "Gate_Baseline.txt"), "strnul 0x00001000 _f\n")
    git(repo, "commit", "-qm", "recreate")
    assert C.main(["--ref", "HEAD"]) == 1


@pytest.mark.parametrize("path", [
    "reverse/attempts/0x0048C16C.cpp", "reverse/attempts/0x0048c16c.cpp",     # c8128a7fe1's repair, both ways
    "reverse/attempt_support/0x00191c10/README.md", "reverse/attempt_support/coordinator/A-x/manifest.json",
    "reverse/class_contracts/Coord2D.json",                                   # named after C++ classes
    "targets/game/reverse/attempts/0x0048C16C.cpp", "targets/game/reverse/class_contracts/Coord2D.json",
    "targets/game/reverse/identity_evidence/00161E20-queued-team-contract.json",
    "targets/game/reverse/attempt_support/0x00163030-20260928-formB-early-return.inc",
    "tools/compat/wibo/LICENSE.wibo", "tools/compat/wibo/SHA256SUMS",
    "README.md", "AGENTS.md", "LICENSE", "tools/ghidra/README.md",            # documents
    "docs/README.md", "docs/progress.svg", "docs/doxygen/api/README.dox",
    "mods/README.md", "mods/features/043-ReplayCam/README.md", "mods/features/x/Patch.ASM",
    "mods/features/A/B/README.md", "mods/features/A/B/Payload.BIN",
    "Code/GameEngine/Source/Common/Foo.cpp", "game/GameEngine/Source/Foo.cpp",  # not a control tree
    "inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main.cpp",
    "reverse/data_rows.csv", "targets/game/reverse/data_rows.csv",            # control, lowercase
    "inputs/baselines/bfme1/retail-1.03-unpacked/manifest.json", "tools/check_case_collisions.py",
])
def test_lowercase_control_paths_and_non_control_paths_pass(repo, path):
    track(repo, path)
    assert C.main([]) == 0
    git(repo, "commit", "-qm", "ok")
    assert C.main(["--ref", "HEAD"]) == 0


@pytest.mark.parametrize("variant,want", [("Agents.md", "AGENTS.md"), ("readme.md", "README.md"),
                                          ("Docs/budget.md", "docs/budget.md"),
                                          ("docs/Budget.MD", "docs/Budget.md"),
                                          ("mods/readme.md", "mods/README.md"),
                                          ("Mods/README.md", "mods/README.md"),
                                          ("mods/features/example/Readme.MD", "mods/features/example/README.md"),
                                          ("mods/Features/Example/README.md", "mods/features/Example/README.md"),
                                          # nested: doc_budget's fnmatch * spans "/" (Sol, round 2)
                                          ("mods/features/a/b/readme.md", "mods/features/a/b/README.md"),
                                          ("Mods/features/a/b/README.md", "mods/features/a/b/README.md"),
                                          ("mods/Features/A/B/Readme.MD", "mods/features/A/B/README.md")])
def test_a_document_read_by_name_keeps_its_spelling(repo, variant, want, capsys):
    """doc_budget reads AGENTS.md, README.md, docs/*.md and the mod READMEs by exact
    name, and .md is otherwise exempt: Agents.md or mods/readme.md escaped its cap."""
    track(repo, variant)
    assert C.main([]) == 1 and f"rename to {want}" in capsys.readouterr().err
    git(repo, "commit", "-qm", "document")
    assert C.main(["--ref", "HEAD"]) == 1


@pytest.mark.parametrize("decoy", ["targets/game/reverse", "reverse", None])
@pytest.mark.parametrize("variant", ["reverse/Data_Rows.csv", "targets/WorldBuilder/reverse/functions.csv"])
def test_the_rules_never_depend_on_the_checkout(tmp_path, decoy, variant):
    """Round 1 of the shared file: an empty, untracked targets/game/reverse/ switched
    Open-BFME-2 to the Open-BFME-1 rules and reverse/Data_Rows.csv passed both hooks.
    Run the checker from inside a tree that holds a decoy layout directory, or none."""
    root = tmp_path / "tree"
    root.mkdir()
    git(root, "init", "-q")
    git(root, "config", "user.name", "T")
    git(root, "config", "user.email", "t@example.invalid")
    (root / "tools").mkdir()
    shutil.copyfile(TOOLS / "check_case_collisions.py", root / "tools" / "check_case_collisions.py")
    if decoy:
        (root / decoy).mkdir(parents=True)
    track(root, variant)
    run = lambda *a: subprocess.run([sys.executable, "tools/check_case_collisions.py", *a], cwd=root,
                                    capture_output=True, text=True)
    assert run().returncode == 1
    git(root, "commit", "-qm", "variant")
    assert run("--ref", "HEAD").returncode == 1


@pytest.mark.parametrize("pair", [("Code/a.cpp", "Code/A.cpp"),
                                  ("reverse/class_contracts/Coord2D.json", "reverse/class_contracts/coord2d.json")])
def test_a_case_only_collision_is_still_refused(repo, pair):
    for path in pair:
        track(repo, path)
    assert C.main([]) == 1
