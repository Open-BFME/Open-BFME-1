"""header_dependents: a header change reaches exactly the sources that can include it, and
every doubt widens the set or falls back to the full gate."""
import shutil
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import bash_path  # noqa: E402
import header_dependents as H  # noqa: E402


def git(root, *args):
    subprocess.run(["git", *args], cwd=root, check=True, capture_output=True)


@pytest.fixture
def repo(tmp_path, monkeypatch):
    git(tmp_path, "init", "-q")
    git(tmp_path, "config", "user.name", "Fixture")
    git(tmp_path, "config", "user.email", "fixture@example.invalid")
    monkeypatch.setattr(H, "ROOT", tmp_path)
    return tmp_path


def put(root, path, text):
    target = root / path
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_text(text)
    git(root, "add", "--", path)


def ledger(root, *sources):
    put(root, "targets/game/reverse/functions.csv",
        "name,export_rva,target_rva,target_size,source,status,notes\n"
        + "".join(f"?f{i}@@YAXXZ,,0x{0x1000 + i:08X},4,{s},matched,x\n" for i, s in enumerate(sources)))


def run(root, capsys, *args):
    code = H.main(list(args))
    out = capsys.readouterr()
    return code, [line for line in out.out.splitlines() if line]


def base(repo):
    put(repo, "game/Inc/Low.h", "int low;\n")
    put(repo, "game/Inc/Mid.h", '#include "../Inc/LOW.H"\n')
    put(repo, "game/A.cpp", '#include "Inc/Mid.h"\nvoid a() {}\n')
    put(repo, "game/B.cpp", "void b() {}\n")
    put(repo, "game/C.cpp", "// cl: /FIForced.h\nvoid c() {}\n")
    put(repo, "game/Forced.h", "int forced;\n")
    ledger(repo, "game/A.cpp", "game/B.cpp", "game/C.cpp")
    git(repo, "commit", "-qm", "base")


def test_transitive_case_insensitive_include(repo, capsys):
    base(repo)
    put(repo, "game/Inc/Low.h", "int low2;\n")
    assert run(repo, capsys, "--staged") == (0, ["game/A.cpp"])


def test_forced_include_counts(repo, capsys):
    base(repo)
    put(repo, "game/Forced.h", "int forced2;\n")
    assert run(repo, capsys, "--staged") == (0, ["game/C.cpp"])


def test_deleted_header_still_finds_its_includers(repo, capsys):
    base(repo)
    git(repo, "rm", "-q", "game/Inc/Low.h")
    assert run(repo, capsys, "--staged") == (0, ["game/A.cpp"])


def test_new_unincluded_header_reaches_nothing(repo, capsys):
    base(repo)
    put(repo, "game/Inc/Unused.h", "int unused;\n")
    assert run(repo, capsys, "--staged") == (0, [])


def test_macro_include_counts_as_including_everything(repo, capsys):
    base(repo)
    put(repo, "game/D.cpp", "#define H \"x.h\"\n#include H\nvoid d() {}\n")
    ledger(repo, "game/A.cpp", "game/B.cpp", "game/C.cpp", "game/D.cpp")
    git(repo, "commit", "-qm", "macro")
    put(repo, "game/Inc/Low.h", "int low3;\n")
    assert run(repo, capsys, "--staged") == (0, ["game/A.cpp", "game/D.cpp"])


def test_toolchain_or_vendor_change_needs_the_full_gate(repo, capsys):
    base(repo)
    put(repo, "inputs/vendor/stlport/stl/_vector.h", "x\n")
    assert run(repo, capsys, "--staged")[0] == 2


def test_limit_falls_back_to_the_full_gate(repo, capsys):
    base(repo)
    put(repo, "game/Inc/Low.h", "int low4;\n")
    assert run(repo, capsys, "--staged", "--limit", "0")[0] == 2


def test_mod_headers_are_not_game_dependencies(repo, capsys):
    base(repo)
    put(repo, "mods/features/x/feature.h", "int mod;\n")
    assert run(repo, capsys, "--staged") == (0, [])


def included_base(repo):
    put(repo, "game/Net/Inc.cpp", "void inc() {}\n")
    put(repo, "game/Net/Host.cpp", '#include "Inc.cpp"\nvoid host() {}\n')
    put(repo, "game/Lib/Outer.cpp", '#include "../Net/Host.cpp"\n')
    put(repo, "game/Lib/henc.tbl", "1, 2, 3,\n")
    put(repo, "game/Lib/Huff.inl", '#include "henc.tbl"\n')
    put(repo, "game/Lib/Huff.cpp", '#include "Huff.inl"\nvoid huff() {}\n')
    ledger(repo, "game/Net/Inc.cpp", "game/Net/Host.cpp", "game/Lib/Outer.cpp", "game/Lib/Huff.cpp")
    git(repo, "commit", "-qm", "base")


def test_an_included_source_reaches_its_includers_through_sources(repo, capsys):
    included_base(repo)
    put(repo, "game/Net/Inc.cpp", "void inc2() {}\n")
    assert run(repo, capsys, "--staged") == (0, ["game/Lib/Outer.cpp", "game/Net/Host.cpp"])


def test_an_included_table_reaches_through_a_header(repo, capsys):
    included_base(repo)
    put(repo, "game/Lib/henc.tbl", "4, 5, 6,\n")
    assert run(repo, capsys, "--staged") == (0, ["game/Lib/Huff.cpp"])


def test_a_renamed_included_source_still_reaches_the_old_includers(repo, capsys):
    included_base(repo)
    git(repo, "mv", "game/Net/Inc.cpp", "game/Net/Moved.cpp")
    assert run(repo, capsys, "--staged") == (0, ["game/Lib/Outer.cpp", "game/Net/Host.cpp"])


def test_a_source_nothing_includes_skips_the_graph(repo, capsys, monkeypatch):
    included_base(repo)
    monkeypatch.setattr(H, "graph", lambda: pytest.fail("graph built for an unincluded source"))
    put(repo, "game/Lib/Huff.cpp", '#include "Huff.inl"\nvoid huff2() {}\n')
    assert run(repo, capsys, "--staged") == (0, [])


def test_an_included_vendored_file_needs_the_full_gate(repo, capsys):
    included_base(repo)
    put(repo, "game/Alloc.cpp", "#include <stl/_alloc.c>\n")
    git(repo, "commit", "-qm", "alloc")
    put(repo, "inputs/vendor/stlport/stl/_alloc.c", "x\n")
    assert run(repo, capsys, "--staged")[0] == 2


STUBS = ("check_case_collisions", "conversion_gate", "name_regression", "name_oracle", "name_history",
         "eol_guard", "retired_guard", "doc_budget", "ea_name_guard", "link_debt", "target_hooks",
         "layout_migration", "check_csv", "pin_consistency", "b_pin_check", "find_declared_unmatched",
         "delta_sources", "identity_guard", "adopt_header", "one_identity", "gate_baseline")


@pytest.fixture
def hook_repo(repo):
    """The real hooks with every other checker stubbed; build.sh records what it verifies."""
    for tool in STUBS:
        put(repo, f"tools/{tool}.py", "raise SystemExit(0)\n")
    shutil.copyfile(TOOLS / "header_dependents.py", repo / "tools/header_dependents.py")
    put(repo, "build.sh", "#!/usr/bin/env bash\nprintf '%s\\n' \"$@\" >> built\n")
    (repo / "build.sh").chmod(0o755)
    git(repo, "add", "tools", "build.sh")
    included_base(repo)
    return repo


def hook(repo, name, refs=""):
    try:
        bash = bash_path.bash()
    except RuntimeError:
        pytest.skip("Bash is required to exercise hooks")
    return subprocess.run([bash, str(TOOLS.parent / ".githooks" / name)], cwd=repo, input=refs,
                          capture_output=True, text=True, env=bash_path.env())


def head(repo):
    return subprocess.run(["git", "rev-parse", "HEAD"], cwd=repo, capture_output=True,
                          text=True, check=True).stdout.strip()


def test_pre_commit_verifies_the_includers_of_a_staged_source(hook_repo):
    put(hook_repo, "game/Net/Inc.cpp", "void inc2() {}\n")
    result = hook(hook_repo, "pre-commit")
    assert result.returncode == 0, result.stderr
    assert "scoped gate over 2 dependent source(s)" in result.stderr
    assert (hook_repo / "built").read_text().splitlines()[:2] == ["game/Lib/Outer.cpp", "game/Net/Host.cpp"]


def test_pre_commit_refuses_unstaged_edits_in_an_included_table(hook_repo):
    put(hook_repo, "game/Lib/henc.tbl", "4, 5, 6,\n")
    (hook_repo / "game/Lib/henc.tbl").write_text("7, 8, 9,\n")
    result = hook(hook_repo, "pre-commit")
    assert result.returncode != 0
    assert "unstaged edits in game/Lib/henc.tbl" in result.stderr
    assert not (hook_repo / "built").exists()


def test_pre_push_verifies_the_includer_of_a_pushed_table(hook_repo):
    base_sha = head(hook_repo)
    put(hook_repo, "game/Lib/henc.tbl", "4, 5, 6,\n")
    git(hook_repo, "commit", "-qm", "table")
    result = hook(hook_repo, "pre-push", f"refs/heads/main {head(hook_repo)} refs/heads/main {base_sha}\n")
    assert result.returncode == 0, result.stderr
    assert (hook_repo / "built").read_text().splitlines() == ["game/Lib/Huff.cpp"]


def test_a_crash_fails_the_commit_instead_of_passing_it(hook_repo):
    put(hook_repo, "tools/header_dependents.py", "raise SystemExit(1)\n")
    git(hook_repo, "commit", "-qm", "broken tool")
    put(hook_repo, "game/Net/Inc.cpp", "void inc2() {}\n")
    result = hook(hook_repo, "pre-commit")
    assert result.returncode != 0
    assert "header_dependents (see above)" in result.stderr
    assert not (hook_repo / "built").exists()
