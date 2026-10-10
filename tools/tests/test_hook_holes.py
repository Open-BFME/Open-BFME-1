"""Hook holes ported from Open-BFME-2's gate hardening (eca813ee88 and its review).

Each case runs the real hook in a throwaway repository; the checkers are stubs and
build.sh records what it was asked to verify and the compiler state it saw.

- pre-commit took its early exit for a commit staging only data_rows.csv, or only
  a claimed .cc/.cxx/.asm source: nothing was byte-verified.
- pre-commit passed a caller's BUILD_RECOMPILE_ONLY, CL and _CL_ to the build.
- `git diff | grep -q` under pipefail: grep exits at its match, a long diff dies of
  SIGPIPE, the pipeline fails, and the lessons ban (pre-commit) or the ledger
  re-check (post-commit) silently did not run.
- pre-push read an unreadable data_rows.csv as "no data rows", and compared an
  outgoing source with HEAD rather than with the pushed commit.
"""
import re
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
HOOKS = TOOLS.parent / ".githooks"
sys.path.insert(0, str(TOOLS))
import bash_path  # noqa: E402

STUBS = ("check_case_collisions", "conversion_gate", "name_regression", "name_oracle", "name_history",
         "eol_guard", "retired_guard", "doc_budget", "ea_name_guard", "name_lane", "link_debt", "target_hooks",
         "layout_migration", "check_csv", "pin_consistency", "b_pin_check", "identity_guard", "adopt_header",
         "one_identity", "gate_baseline", "class_gate", "ledger_guard", "ilt_guard", "alias_guard",
         "hatch_counters", "tu_ownership", "header_dependents", "find_declared_unmatched")
# LF only, like the real selector (Sol round 1: a CRLF stub fed `game/D.cpp\r` to the hook on Windows)
DELTA_STUB = ('import pathlib, sys\n'
              'sys.stdin.read() if "-" in sys.argv else None\n'
              'sys.stdout.reconfigure(newline="\\n")\n'
              'p = pathlib.Path("delta.txt")\n'
              'sys.stdout.write(p.read_text() if p.exists() else "")\n')
# check_csv's orphan rule, the part these cases need: a tracked game/*.cpp that no
# matched function or data row in the INDEX claims is refused.
CHECK_CSV_STUB = '''import csv, io, subprocess, sys
def staged(path):
    shown = subprocess.run(["git", "show", ":" + path], capture_output=True, text=True)
    return list(csv.DictReader(io.StringIO(shown.stdout))) if shown.returncode == 0 else []
claimed = {r["source"] for p in ("targets/game/reverse/functions.csv", "targets/game/reverse/data_rows.csv")
           for r in staged(p) if r.get("status") == "matched"}
tracked = subprocess.run(["git", "ls-files", "game"], capture_output=True, text=True, check=True).stdout.split()
orphans = [p for p in tracked if p.endswith(".cpp") and p not in claimed]
if orphans:
    print("orphaned:", *orphans, file=sys.stderr)
    raise SystemExit(1)
# and its tombstone rule: a deleted_rows.csv entry may not name a matched row
matched = {r["name"] for r in staged("targets/game/reverse/functions.csv") if r.get("status") == "matched"}
tombstoned = sorted(matched & {r["name"] for r in staged("targets/game/reverse/deleted_rows.csv")})
if tombstoned:
    print("tombstoned but matched:", *tombstoned, file=sys.stderr)
    raise SystemExit(1)
'''
# The real checks' answers to the questions these cases ask: a baseline that is gone
# refuses (pin_consistency.read_baseline), a DIR32 line no ledger backs refuses
# (dir32_record_guard.problems), a removed debt line whose row still fails refuses
# (repair_queue verify-removed, run from HEAD).
PIN_STUB = '''import pathlib, sys
if not pathlib.Path("targets/game/reverse/pin_consistency_baseline.csv").exists():
    print("pin_consistency: baseline is missing", file=sys.stderr)
    raise SystemExit(1)
'''
DIR32_STUB = '''import subprocess, sys
staged = subprocess.run(["git", "show", ":targets/game/reverse/dir32_addresses.csv"], capture_output=True, text=True)
if staged.returncode or "Unproved" in staged.stdout:
    print("dir32_record_guard: unproved line", file=sys.stderr)
    raise SystemExit(1)
'''
REPAIR_STUB = '''import pathlib, sys
if pathlib.Path("still-failing").exists():
    print("repair_queue: a removed debt line's row still fails", file=sys.stderr)
    raise SystemExit(1)
'''
PIN_BASELINE = "targets/game/reverse/pin_consistency_baseline.csv"
BODY_BASELINE = "targets/game/reverse/body_guard_baseline.csv"
FULL_BASELINE = "targets/game/reverse/full_gate_baseline.txt"
DIR32 = "targets/game/reverse/dir32_addresses.csv"
DELETED_ROWS = "targets/game/reverse/deleted_rows.csv"
BUILD_SH = ('#!/usr/bin/env bash\nprintf \'%s\\n\' "$@" >> built\n'
            'printf \'%s|%s|%s\\n\' "${BUILD_RECOMPILE_ONLY-unset}" "${CL-unset}" "${_CL_-unset}" >> built_env\n')
FUNCTIONS = "targets/game/reverse/functions.csv"
DATA_ROWS = "targets/game/reverse/data_rows.csv"
FN_HEAD = "name,export_rva,target_rva,target_size,source,status,notes\n"
DR_HEAD = "name,rva,size,source,status,notes\n"


def git(root, *args):
    return subprocess.run(["git", *args], cwd=root, check=True, capture_output=True, text=True).stdout.strip()


def write(root, path, text):
    target = root / path
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_bytes(text.encode("utf-8"))


@pytest.fixture
def repo(tmp_path):
    root = tmp_path / "repo"
    root.mkdir()
    git(root, "init", "-q")
    git(root, "config", "user.name", "Fixture")
    git(root, "config", "user.email", "fixture@example.invalid")
    git(root, "config", "core.autocrlf", "false")
    for tool in STUBS:
        write(root, f"tools/{tool}.py", "import sys\nsys.stdin.read() if '-' in sys.argv else None\n")
    write(root, "tools/delta_sources.py", DELTA_STUB)
    write(root, "tools/check_csv.py", CHECK_CSV_STUB)
    write(root, "tools/pin_consistency.py", PIN_STUB)
    write(root, "tools/dir32_record_guard.py", DIR32_STUB)
    write(root, "tools/body_guard.py", "")
    write(root, "tools/repair_queue.py", REPAIR_STUB)
    write(root, "build.sh", BUILD_SH)
    (root / "build.sh").chmod(0o755)
    write(root, FUNCTIONS, FN_HEAD
          + "?a@@YAXXZ,,0x00001000,16,game/masm/A.asm,matched,\n"
          + "?c@@YAXXZ,,0x00001010,16,game/lib/C.cc,matched,\n")
    write(root, DATA_ROWS, DR_HEAD + "g_d,0x00A00000,4,game/D.cpp,matched,\n")
    write(root, PIN_BASELINE, "symbol,bodies\n?p@@YAXXZ,1000\n?q@@YAXXZ,2000\n")
    write(root, BODY_BASELINE, "rva,check\n0x00001000,size\n")
    write(root, FULL_BASELINE, "# red rows\nstrnul 0x00001000 ?a@@YAXXZ\n")
    write(root, DIR32, "name,va\n?g_d@@3HA,0x00E00000\n")
    write(root, DELETED_ROWS, "name,target_rva,reason\n")
    for path in ("game/masm/A.asm", "game/lib/C.cc", "game/lib/U.cxx", "game/D.cpp"):
        write(root, path, "; v1\n")
    write(root, ".gitignore", "built\nbuilt_env\ndelta.txt\nstill-failing\nrechecked\n")
    git(root, "add", "-A")
    git(root, "commit", "-qm", "base")
    return root


def run(root, hook, env=None, stdin=None, args=()):
    try:
        bash = bash_path.bash()
    except RuntimeError:
        pytest.skip("Bash is required to exercise hooks")
    return subprocess.run([bash, str(HOOKS / hook), *args], cwd=root, input=stdin, capture_output=True,
                          text=True, encoding="utf-8", errors="replace",
                          env={**bash_path.env(), **(env or {})}, timeout=600)


def lines(root, name):
    path = root / name
    return path.read_text(encoding="utf-8").splitlines() if path.exists() else []


def test_a_data_rows_only_commit_is_byte_verified(repo):
    write(repo, DATA_ROWS, DR_HEAD + "g_d,0x00A00000,4,game/D.cpp,matched,\n"
                                     "g_e,0x00A00004,4,game/D.cpp,matched,\n")
    write(repo, "delta.txt", "source:game/D.cpp\n")
    git(repo, "add", DATA_ROWS)
    result = run(repo, "pre-commit")
    assert result.returncode == 0, result.stderr[-2000:]
    assert lines(repo, "built") == ["source:game/D.cpp"]


@pytest.mark.parametrize("path", ["game/masm/A.asm", "game/lib/C.cc"])
def test_a_claimed_non_cpp_source_edit_is_byte_verified(repo, path):
    write(repo, path, "; v2\n")
    write(repo, "game/lib/U.cxx", "; v2\n")            # unclaimed: filtered, not built
    git(repo, "add", path, "game/lib/U.cxx")
    result = run(repo, "pre-commit")
    assert result.returncode == 0, result.stderr[-2000:]
    assert lines(repo, "built") == [path]


def test_compiler_state_a_caller_exported_never_reaches_the_build(repo):
    write(repo, "game/masm/A.asm", "; v2\n")
    git(repo, "add", "game/masm/A.asm")
    result = run(repo, "pre-commit", env={"BUILD_RECOMPILE_ONLY": "1", "CL": "/Od", "_CL_": "/X"})
    assert result.returncode == 0, result.stderr[-2000:]
    assert lines(repo, "built_env") == ["unset|unset|unset"]


def test_a_staged_data_rows_edit_with_unstaged_edits_is_refused(repo):
    write(repo, DATA_ROWS, DR_HEAD + "g_d,0x00A00000,4,game/D.cpp,matched,\ng_e,0x00A00004,4,game/D.cpp,matched,\n")
    git(repo, "add", DATA_ROWS)
    write(repo, DATA_ROWS, DR_HEAD + "g_d,0x00A00000,4,game/D.cpp,matched,\n")
    result = run(repo, "pre-commit")
    assert result.returncode == 1
    assert f"unstaged edits in: {DATA_ROWS}" in result.stderr
    assert not lines(repo, "built")


@pytest.mark.parametrize("operation", ["delete", "rename"])
def test_deleting_or_renaming_data_rows_reaches_the_ledger_check(repo, operation):
    # Sol round 1: the ACMRT listing omits a deletion and names only a rename's
    # destination, so either took the early exit and orphaned game/D.cpp unseen
    if operation == "delete":
        git(repo, "rm", "-q", DATA_ROWS)
    else:
        git(repo, "mv", DATA_ROWS, DATA_ROWS.replace("data_rows", "data_rows_saved"))
    result = run(repo, "pre-commit")
    assert result.returncode == 1
    assert "orphaned: game/D.cpp" in result.stderr and "ledger integrity" in result.stderr


def test_removing_a_data_row_ledger_with_its_source_passes(repo):
    git(repo, "rm", "-q", DATA_ROWS, "game/D.cpp")
    result = run(repo, "pre-commit")
    assert result.returncode == 0, result.stderr[-2000:]


def remove(repo, path, operation):
    if operation == "delete":
        git(repo, "rm", "-q", path)
    else:
        git(repo, "mv", path, path.replace(".csv", "_saved.csv").replace(".txt", "_saved.txt"))


@pytest.mark.parametrize("operation", ["delete", "rename"])
def test_deleting_or_renaming_the_pin_baseline_is_refused(repo, operation):
    # Sol round 2: the deleted side never set baseline_changed, so the commit took the
    # early exit and a required baseline went missing for every later gate
    remove(repo, PIN_BASELINE, operation)
    result = run(repo, "pre-commit")
    assert result.returncode == 1 and "baseline is missing" in result.stderr


def test_shrinking_the_pin_baseline_passes(repo):
    write(repo, PIN_BASELINE, "symbol,bodies\n?p@@YAXXZ,1000\n")
    git(repo, "add", PIN_BASELINE)
    result = run(repo, "pre-commit")
    assert result.returncode == 0, result.stderr[-2000:]


@pytest.mark.parametrize("name,refused", [("?Unproved@@3HA", True), ("?g_e@@3HA", False)])
def test_a_dir32_only_change_reaches_its_guard(repo, name, refused):
    # Sol round 2: dir32_record_changed was set but never kept the commit from the early exit
    write(repo, DIR32, f"name,va\n?g_d@@3HA,0x00E00000\n{name},0x00E00004\n")
    git(repo, "add", DIR32)
    result = run(repo, "pre-commit")
    assert (result.returncode == 1 and "unproved line" in result.stderr) if refused \
        else result.returncode == 0, result.stderr[-2000:]


@pytest.mark.parametrize("baseline,emptied", [(BODY_BASELINE, "rva,check\n"), (FULL_BASELINE, "# red rows\n")])
@pytest.mark.parametrize("operation", ["shrink", "delete", "rename"])
@pytest.mark.parametrize("repaired", [False, True])
def test_a_debt_baseline_change_reverifies_the_removed_debt(repo, baseline, emptied, operation, repaired):
    # Sol rounds 2-3: a body_guard or full-gate baseline change took the early exit (and
    # verify-removed ran only for the body baseline), so removing a debt line claimed a
    # repair nothing rebuilt
    if not repaired:
        write(repo, "still-failing", "")
    if operation == "shrink":
        write(repo, baseline, emptied)
        git(repo, "add", baseline)
    else:
        remove(repo, baseline, operation)
    result = run(repo, "pre-commit")
    if repaired:
        assert result.returncode == 0, result.stderr[-2000:]
    else:
        assert result.returncode == 1 and "still fails" in result.stderr


def test_a_tombstone_naming_a_matched_row_is_refused(repo):
    # Sol round 2: deleted_rows.csv set no flag, so check_csv never judged a tombstone
    write(repo, DELETED_ROWS, "name,target_rva,reason\n?a@@YAXXZ,0x00001000,dup\n")
    git(repo, "add", DELETED_ROWS)
    result = run(repo, "pre-commit")
    assert result.returncode == 1 and "tombstoned but matched: ?a@@YAXXZ" in result.stderr


def test_retiring_a_row_with_its_tombstone_passes(repo):
    write(repo, DELETED_ROWS, "name,target_rva,reason\n?a@@YAXXZ,0x00001000,dup\n")
    write(repo, FUNCTIONS, FN_HEAD + "?c@@YAXXZ,,0x00001010,16,game/lib/C.cc,matched,\n")
    git(repo, "add", DELETED_ROWS, FUNCTIONS)
    result = run(repo, "pre-commit")
    assert result.returncode == 0, result.stderr[-2000:]


def test_post_commit_rechecks_a_data_rows_only_commit(repo):
    # Sol round 2: the post-commit predicate left data_rows.csv out, so a cherry-picked
    # data-row commit was never rechecked
    write(repo, "tools/ledger_after_rewrite.py", "import pathlib\npathlib.Path('rechecked').write_text('y')\n")
    git(repo, "add", "tools/ledger_after_rewrite.py")
    git(repo, "commit", "-qm", "recording recheck")
    write(repo, DATA_ROWS, DR_HEAD + "g_d,0x00A00000,4,game/D.cpp,matched,\ng_e,0x00A00004,4,game/D.cpp,matched,\n")
    git(repo, "add", DATA_ROWS)
    git(repo, "commit", "-qm", "data rows only")
    result = run(repo, "post-commit")
    assert result.returncode == 0, result.stderr[-2000:]
    assert (repo / "rechecked").exists()


def message_repo(tmp_path, guard=None):
    root = tmp_path / "msgrepo"
    root.mkdir()
    git(root, "init", "-q")
    git(root, "config", "user.name", "Fixture")
    git(root, "config", "user.email", "fixture@example.invalid")
    if guard is not None:
        write(root, "tools/dir32_record_guard.py", guard)
        git(root, "add", "-A")
        git(root, "commit", "-qm", "guard")
    message = tmp_path / "msg"
    message.write_text("A message\n", encoding="utf-8")
    return root, message


def test_commit_msg_refuses_a_listed_guard_it_cannot_read(tmp_path):
    # Sol round 2: a failed `cat-file -e` (here, the blob quarantined) read as "no guard"
    root, message = message_repo(tmp_path, "import sys  # --commit-msg\nsys.exit(0)\n")
    blob = git(root, "rev-parse", "HEAD:tools/dir32_record_guard.py")
    loose = root / ".git" / "objects" / blob[:2] / blob[2:]
    loose.chmod(0o644)
    loose.rename(tmp_path / "quarantined")
    result = run(root, "commit-msg", args=(str(message),))
    assert result.returncode == 1 and "cannot be read" in result.stderr


@pytest.mark.parametrize("state", ["absent guard", "unborn HEAD"])
def test_commit_msg_passes_without_a_guard(tmp_path, state):
    if state == "absent guard":
        root, message = message_repo(tmp_path)
        write(root, "README", "x\n")
        git(root, "add", "README")
        git(root, "commit", "-qm", "no guard")
    else:
        root, message = message_repo(tmp_path)
    result = run(root, "commit-msg", args=(str(message),))
    assert result.returncode == 0, result.stderr[-2000:]


def many(root, count=4000):
    # sorted after docs/ and targets/, ~70 bytes a line: far past a 64 KiB pipe buffer
    for i in range(count):
        write(root, f"zz/a_long_directory_name_for_the_pipe_buffer/file_{i:05d}.txt", "x\n")


@pytest.mark.parametrize("name", ["docs/lessons.md", "Docs/Lessons.md"])
def test_the_lessons_ban_fires_however_long_the_staged_list(repo, name):
    many(repo)
    write(repo, name, "# lessons\n")
    git(repo, "add", "-A")
    result = run(repo, "pre-commit")
    assert result.returncode == 1
    assert "docs/lessons.md was deleted deliberately" in result.stderr


def test_post_commit_rechecks_the_ledger_however_long_the_commit(repo):
    write(repo, "tools/ledger_after_rewrite.py", "import pathlib\npathlib.Path('rechecked').write_text('y')\n")
    many(repo)
    write(repo, FUNCTIONS, FN_HEAD + "?a@@YAXXZ,,0x00001000,16,game/masm/A.asm,matched,\n")
    git(repo, "add", "-A")
    git(repo, "-c", "core.hooksPath=/dev/null", "commit", "-qm", "long")
    result = run(repo, "post-commit")
    assert result.returncode == 0, result.stderr[-2000:]
    assert (repo / "rechecked").exists()


def selector_script():
    text = (HOOKS / "pre-push").read_text(encoding="utf-8")
    m = re.search(r'python3 - "\$base" "\$local_sha" > "\$edited_out" <<\'PY\' \\\n[^\n]*\n(.*?)\nPY\n', text, re.S)
    assert m, "the edited-claimed-sources selector script was not found in .githooks/pre-push"
    return m.group(1)


def test_pre_push_refuses_an_unreadable_data_rows_ledger(repo):
    base = git(repo, "rev-parse", "HEAD")
    write(repo, "game/D.cpp", "; v2\n")
    git(repo, "add", "game/D.cpp")
    # present in the tree but unreadable: a gitlink whose commit is not here
    git(repo, "update-index", "--force-remove", DATA_ROWS)
    git(repo, "update-index", "--add", "--cacheinfo", f"160000,{'1' * 40},{DATA_ROWS}")
    git(repo, "commit", "-qm", "unreadable data rows")
    rev = git(repo, "rev-parse", "HEAD")
    done = subprocess.run([sys.executable, "-", base, rev], input=selector_script(), cwd=repo,
                          capture_output=True, text=True)
    assert done.returncode != 0 and "game/D.cpp" not in done.stdout


def test_pre_push_selects_a_data_only_source_when_data_rows_is_readable(repo):
    base = git(repo, "rev-parse", "HEAD")
    write(repo, "game/D.cpp", "; v2\n")
    git(repo, "commit", "-qam", "edit the data-only source")
    done = subprocess.run([sys.executable, "-", base, git(repo, "rev-parse", "HEAD")], input=selector_script(),
                          cwd=repo, capture_output=True, text=True, check=True)
    assert done.stdout.split() == ["game/D.cpp"]


def padded_guard(root):
    """The real dir32_record_guard.py followed by ~200 KB of comments: grep finds
    `--commit-msg` near the top and exits while `git show` still has far more than
    a pipe buffer to write."""
    text = (TOOLS / "dir32_record_guard.py").read_text(encoding="utf-8")
    pad = "".join(f"# padding line {i:05d} keeps git show writing after grep has matched\n" for i in range(3000))
    write(root, "tools/dir32_record_guard.py", text + pad)


@pytest.mark.parametrize("retire", [False, True])
def test_commit_msg_runs_the_dir32_guard_however_long_it_is(tmp_path, retire):
    # Sol round 1: `git show HEAD:guard | grep -q --commit-msg` died of SIGPIPE on a
    # long guard, and a deletion without its trailer went through 5/5 times
    import dir32_record_guard as guard
    old, new, va = "?g_wrong@@3HA", "?TheRight@@3HA", 0x012ED5D4
    root = tmp_path / "repo"
    root.mkdir()
    git(root, "init", "-q")
    git(root, "config", "user.name", "Fixture")
    git(root, "config", "user.email", "fixture@example.invalid")
    git(root, "config", "core.autocrlf", "false")
    write(root, "targets/game/reverse/dir32_addresses.csv", f"name,va\n{old},0x{va:08X}\n?TheKept@@3HA,0x01300000\n")
    write(root, DATA_ROWS, "name,address,address_kind,size,section,source,status,evidence,model\n"
                           f"{new},0x{va:08X},va,4,.data,game/a.cpp,matched,x,m\n")
    write(root, FUNCTIONS, FN_HEAD)
    write(root, "game/a.cpp", "int TheRight;\n")
    padded_guard(root)
    git(root, "add", "-A")
    git(root, "commit", "-qm", "base")
    write(root, "targets/game/reverse/dir32_addresses.csv", "name,va\n?TheKept@@3HA,0x01300000\n")
    git(root, "add", "targets/game/reverse/dir32_addresses.csv")
    message = tmp_path / "msg"
    message.write_text("Drop a line\n" + (f"\n{guard.trailer(old, va, new)}\n" if retire else ""), encoding="utf-8")
    result = run(root, "commit-msg", args=(str(message),))
    if retire:
        assert result.returncode == 0, result.stderr[-2000:]
    else:
        assert result.returncode == 1 and "dir32_addresses.csv line deleted" in result.stderr


def test_pre_push_binds_sources_and_compiler_state_to_the_pushed_commit():
    text = (HOOKS / "pre-push").read_text(encoding="utf-8")
    assert 'git diff --quiet HEAD -- "$s"' not in text
    assert 'git diff --quiet "$local_sha" -- "$s"' in text
    assert re.search(r"^unset BUILD_RECOMPILE_ONLY CL _CL_$", text, re.M)
