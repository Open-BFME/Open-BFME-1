"""pre-commit with more staged sources than one Windows command line can hold.

Windows caps a native command line at 32,767 characters. The hook passed every staged
source to `find_declared_unmatched.py --staged` as arguments, so past roughly 400
sources Bash failed with "Argument list too long" and the commit died before anything
was checked. The list now goes to the tool on stdin (--paths-from -). Each case runs the
real hook in a throwaway repository: find_declared_unmatched.py is the real tool, the
other checkers are stubs, and build.sh records what it was asked to verify.
"""
import shutil
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import bash_path  # noqa: E402

COUNT = 1500
STUBS = ("check_case_collisions", "conversion_gate", "name_regression", "name_oracle", "name_history",
         "eol_guard", "retired_guard", "doc_budget", "ea_name_guard", "name_lane", "link_debt", "target_hooks",
         "layout_migration", "check_csv", "pin_consistency", "b_pin_check", "delta_sources",
         "identity_guard", "adopt_header", "one_identity", "gate_baseline", "class_gate", "ledger_guard",
         "ilt_guard", "alias_guard", "hatch_counters", "tu_ownership", "header_dependents")
# find_declared_unmatched imports this one helper from build.py.
BUILD_STUB = '''import re


def ledger_object_symbol(row):
    match = re.search(r"(?:^|;)object-symbol=([^;]+)", row.get("notes", ""))
    return match.group(1) if match else row["name"]
'''


def git(root, *args):
    subprocess.run(["git", *args], cwd=root, check=True, capture_output=True)


def source(i):
    # 1,500 of these are ~115,000 characters.
    return f"game/GameEngine/Source/GameLogic/Object/Update/SyntheticUpdateModule{i:04d}.cpp"


def write(root, path, text):
    target = root / path
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_bytes(text.encode("utf-8"))


def make_repo(root, count):
    root.mkdir()
    git(root, "init", "-q")
    git(root, "config", "user.name", "Fixture")
    git(root, "config", "user.email", "fixture@example.invalid")
    git(root, "config", "core.autocrlf", "false")
    for tool in STUBS:
        write(root, f"tools/{tool}.py", "raise SystemExit(0)\n")
    write(root, "tools/build.py", BUILD_STUB)
    shutil.copyfile(TOOLS / "find_declared_unmatched.py", root / "tools/find_declared_unmatched.py")
    write(root, "build.sh", "#!/usr/bin/env bash\nprintf '%s\\n' \"$@\" >> built\n")
    (root / "build.sh").chmod(0o755)
    write(root, "targets/game/reverse/functions.csv",
          "name,export_rva,target_rva,target_size,source,status,notes\n"
          + "".join(f"?f@C{i:04d}@@QAEXXZ,,0x{0x1000 + 16 * i:08X},16,{source(i)},matched,\n"
                    for i in range(count)))
    write(root, ".gitignore", "built\n")
    git(root, "add", "-A")
    git(root, "commit", "-qm", "base")
    for i in range(count):
        write(root, source(i), f"struct C{i:04d} {{ void f(); }};\nvoid C{i:04d}::f() {{}}\n")
    return root


def run_hook(root, stage=True):
    try:
        bash = bash_path.bash()
    except RuntimeError:
        pytest.skip("Bash is required to exercise hooks")
    if stage:
        git(root, "add", "game")
    return subprocess.run([bash, str(TOOLS.parent / ".githooks" / "pre-commit")], cwd=root,
                          capture_output=True, text=True, encoding="utf-8", errors="replace",
                          env=bash_path.env(), timeout=1200)


def built(root):
    path = root / "built"
    return path.read_text(encoding="utf-8").splitlines() if path.exists() else []


def test_clean_commit_of_1500_sources_passes_and_verifies_every_source(tmp_path):
    root = make_repo(tmp_path / "repo", COUNT)
    result = run_hook(root)
    assert result.returncode == 0, result.stderr[-3000:]
    assert "Argument list too long" not in result.stderr
    assert f"PRE-COMMIT OK (ledger integrity + {COUNT} verification selector(s) checked)" in result.stdout
    assert sorted(built(root)) == sorted(map(source, range(COUNT)))


def test_an_undeclared_definition_among_1500_sources_is_refused_and_named(tmp_path):
    root = make_repo(tmp_path / "repo", COUNT)
    bad = source(750)
    write(root, bad, "struct C0750 { void f(); void g(); };\nvoid C0750::f() {}\nvoid C0750::g() {}\n")
    result = run_hook(root)
    assert result.returncode == 1
    assert "Argument list too long" not in result.stderr
    assert "staged sources define functions the ledger does not declare" in result.stderr
    report = result.stdout.replace("\\", "/")  # the tool prints native paths
    assert f"{bad}: C0750::g" in report
    assert "C0749::f" not in report
    assert not built(root)


def run_tool(root, args, stdin=None):
    return subprocess.run([sys.executable, "tools/find_declared_unmatched.py", *args], cwd=root,
                          input=stdin, capture_output=True)


@pytest.mark.parametrize("separator", [b"\0", b"\n", b"\r\n"])
def test_paths_from_stdin_reports_exactly_what_arguments_do(tmp_path, separator):
    root = make_repo(tmp_path / "repo", 40)
    write(root, source(3), "struct C0003 { void f(); void g(); };\nvoid C0003::f() {}\nvoid C0003::g() {}\n")
    orphan = "game/GameEngine/Source/Orphan.cpp"
    write(root, orphan, "struct O { void o(); };\nvoid O::o() {}\n")
    git(root, "add", "game")
    paths = [source(i) for i in range(40)] + [orphan]
    by_argv = run_tool(root, ["--fail", "--staged", *paths])
    by_stdin = run_tool(root, ["--fail", "--staged", "--paths-from", "-"],
                        stdin=separator.join(p.encode() for p in paths) + separator)
    assert by_argv.returncode == by_stdin.returncode == 1
    assert by_stdin.stdout == by_argv.stdout
    assert b"Orphan.cpp: ZERO matched" in by_stdin.stdout and b"C0003::g" in by_stdin.stdout


def test_an_empty_paths_from_list_inspects_nothing(tmp_path):
    root = make_repo(tmp_path / "repo", 3)
    done = run_tool(root, ["--fail", "--staged", "--paths-from", "-"], stdin=b"")
    assert done.returncode == 0
    assert done.stdout.strip() == b"All defined functions are already matched."


def test_a_staged_source_with_unstaged_edits_is_refused(tmp_path):
    root = make_repo(tmp_path / "repo", 20)
    git(root, "add", "game")
    write(root, source(7), "// not what was staged\n")
    result = run_hook(root, stage=False)
    assert result.returncode == 1
    assert f"unstaged edits in: {source(7)}" in result.stderr
    assert source(8) not in result.stderr
    assert not built(root)
