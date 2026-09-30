"""Verifier/baseline edits need a Verifier-Change trailer; baselines only shrink."""
import shutil
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
REPO = TOOLS.parent
sys.path.insert(0, str(TOOLS))

import protected_paths as pp  # noqa: E402

GATE = "targets/game/reverse/full_gate_baseline.txt"
IDENT = "targets/game/reverse/identity_baseline.txt"
ORACLE = "targets/game/reverse/name_oracle_baseline.csv"


def git(cwd, *args, check=True):
    return subprocess.run(["git", *args], cwd=cwd, check=check, capture_output=True, text=True)


def write(repo, path, text):
    target = repo / path
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_text(text, encoding="utf-8")


def as_paths(files, named):
    """{path: text}; keyword spelling tools__build_py means tools/build.py."""
    out = dict(files or {})
    for key, text in named.items():
        stem, _, ext = key.replace("__", "/").rpartition("_")
        out[f"{stem}.{ext}"] = text
    return out


def commit(repo, message, files=None, **named):
    for path, text in as_paths(files, named).items():
        write(repo, path, text)
        git(repo, "add", path)
    git(repo, "commit", "-q", "--no-verify", "-m", message)
    return git(repo, "rev-parse", "HEAD").stdout.strip()


@pytest.fixture
def repo(tmp_path, monkeypatch):
    git(tmp_path, "init", "-q")
    git(tmp_path, "config", "user.name", "t")
    git(tmp_path, "config", "user.email", "t@example.com")
    git(tmp_path, "config", "core.hooksPath", "no-hooks")
    write(tmp_path, "tools/build.py", "x = 1\n")
    write(tmp_path, "game/a.cpp", "int a;\n")
    write(tmp_path, GATE, "# red rows\nfoo (a.cpp)\n")
    write(tmp_path, IDENT, "# counts\nmulti_name.family = 0\none_identity.surplus = 10\n")
    write(tmp_path, ORACLE, "finding,file,line,confidence,source\nA+0x4|m_a|m_b,game/a.cpp,3,1.00,w\n")
    write(tmp_path, "tools/name_oracle.py", "v = 1\n")
    git(tmp_path, "add", ".")
    git(tmp_path, "commit", "-q", "-m", "base")
    monkeypatch.chdir(tmp_path)
    return tmp_path


def staged(repo, message, files=None, **named):
    for path, text in as_paths(files, named).items():
        write(repo, path, text)
        git(repo, "add", path)
    msg = repo / "MSG"
    msg.write_text(message, encoding="utf-8")
    return pp.main(["--commit-msg", str(msg)])


def test_game_only_commit_needs_nothing(repo):
    assert staged(repo, "convert a", game__a_cpp="int a = 2;\n") == 0


def test_verifier_edit_needs_the_trailer(repo, capsys):
    assert staged(repo, "loosen", tools__build_py="x = 2\n") == 1
    err = capsys.readouterr().err
    assert "tools/build.py" in err and "Verifier-Change: MISSING" in err
    assert staged(repo, "mask reloc\n\nVerifier-Change: mask reloc type 7 in DIR32 compare\n") == 0
    assert "Verifier-Change: mask reloc type 7" in capsys.readouterr().err   # listed even when declared


def test_a_token_reason_or_a_comment_line_does_not_count(repo):
    assert staged(repo, "x\n\nVerifier-Change: ok\n", tools__build_py="x = 3\n") == 1
    assert staged(repo, "x\n# Verifier-Change: commented out reason\n") == 1


def test_a_baseline_may_not_grow_even_when_declared(repo, capsys):
    grown = "# red rows\nfoo (a.cpp)\nbar (b.cpp)\n"
    assert staged(repo, "x\n\nVerifier-Change: record a new red row please\n", {GATE: grown}) == 1
    assert "+ bar (b.cpp)" in capsys.readouterr().err
    git(repo, "reset", "-q")
    assert staged(repo, "x\n\nVerifier-Change: bar row fixed, shrink the list\n",
                  {GATE: "# red rows\n"}) == 0


def test_identity_counts_only_go_down(repo):
    up = "# counts\nmulti_name.family = 0\none_identity.surplus = 11\n"
    down = "# counts\nmulti_name.family = 0\none_identity.surplus = 9\n"
    why = "x\n\nVerifier-Change: identity surplus moved after a retire\n"
    assert staged(repo, why, {IDENT: up}) == 1
    git(repo, "reset", "-q")
    assert staged(repo, why, {IDENT: down}) == 0


def test_name_oracle_growth_needs_its_detector_changed_in_the_same_commit(repo):
    grown = ("finding,file,line,confidence,source\nA+0x4|m_a|m_b,game/a.cpp,3,1.00,w\n"
             "B+0x8|m_c|m_d,game/a.cpp,9,1.00,w\n")
    why = "x\n\nVerifier-Change: detector now reads nested structs\n"
    assert staged(repo, why, {ORACLE: grown}) == 1
    assert staged(repo, why, tools__name_oracle_py="v = 2\n") == 0


def test_range_judges_every_outgoing_commit(repo, capsys):
    base = git(repo, "rev-parse", "HEAD").stdout.strip()
    commit(repo, "game", game__a_cpp="int a = 5;\n")
    commit(repo, "declared\n\nVerifier-Change: new relocation kind handled\n", tools__build_py="x = 9\n")
    tip = git(repo, "rev-parse", "HEAD").stdout.strip()
    assert pp.main(["--range", base, tip]) == 0
    commit(repo, "sneaky", tools__build_py="x = 10\n")
    tip = git(repo, "rev-parse", "HEAD").stdout.strip()
    assert pp.main(["--range", base, tip]) == 1
    assert "sneaky" in capsys.readouterr().err


def test_range_catches_net_baseline_growth_and_merge_resolutions(repo):
    base = git(repo, "rev-parse", "HEAD").stdout.strip()
    commit(repo, "grow\n\nVerifier-Change: declared but still growth\n",
           {GATE: "# red rows\nfoo (a.cpp)\nnew (x.cpp)\n"})
    tip = git(repo, "rev-parse", "HEAD").stdout.strip()
    assert pp.main(["--range", base, tip]) == 1
    # a merge whose resolution edits a verifier is judged like a commit
    git(repo, "reset", "-q", "--hard", base)
    git(repo, "checkout", "-q", "-b", "side")
    commit(repo, "side", game__a_cpp="int a = 7;\n")
    git(repo, "checkout", "-q", "-")
    commit(repo, "main", game__b_cpp="int b;\n")
    git(repo, "merge", "-q", "--no-commit", "side")
    write(repo, "tools/build.py", "x = 'evil'\n")
    git(repo, "add", "tools/build.py")
    git(repo, "commit", "-q", "--no-verify", "-m", "merge side")
    tip = git(repo, "rev-parse", "HEAD").stdout.strip()
    assert pp.commit_paths(tip) == ["tools/build.py"]
    assert pp.main(["--range", base, tip]) == 1


def test_the_commit_msg_hook_runs_the_checker_as_of_head(repo):
    hooks = repo / "hooks"
    hooks.mkdir()
    shutil.copy(REPO / ".githooks" / "commit-msg", hooks / "commit-msg")
    (hooks / "commit-msg").chmod(0o755)
    write(repo, "tools/protected_paths.py", (TOOLS / "protected_paths.py").read_text(encoding="utf-8"))
    git(repo, "add", "tools/protected_paths.py")
    git(repo, "commit", "-q", "--no-verify", "-m", "checker\n\nVerifier-Change: install the checker")
    git(repo, "config", "core.hooksPath", str(hooks))
    write(repo, "tools/build.py", "x = 'loose'\n")
    git(repo, "add", "tools/build.py")
    refused = git(repo, "commit", "-q", "-m", "quietly loosen", check=False)
    assert refused.returncode != 0 and "Verifier-Change: MISSING" in refused.stderr
    # gutting the checker in the same commit does not help: HEAD's copy judges
    write(repo, "tools/protected_paths.py", "import sys\nsys.exit(0)\n")
    git(repo, "add", "tools/protected_paths.py")
    assert git(repo, "commit", "-q", "-m", "gut it", check=False).returncode != 0
    ok = git(repo, "commit", "-q", "-m", "declared\n\nVerifier-Change: retire the old checker for a test",
             check=False)
    assert ok.returncode == 0, ok.stderr


GROWN_ORACLE = ("finding,file,line,confidence,source\nA+0x4|m_a|m_b,game/a.cpp,3,1.00,w\n"
                "B+0x8|m_c|m_d,game/b.cpp,9,1.00,w\n")


def test_a_detector_edit_excuses_growth_only_in_its_own_commit(repo):
    # review 2026-09-29: pooled over the range, a detector edit in commit A
    # excused baseline growth in commit B.
    base = git(repo, "rev-parse", "HEAD").stdout.strip()
    commit(repo, "detector\n\nVerifier-Change: improve detector coverage",
           {"tools/name_oracle.py": "v = 2\n"})
    tip = commit(repo, "grow\n\nVerifier-Change: add exception without detector edit",
                 {ORACLE: GROWN_ORACLE})
    assert pp.check_range(base, tip) == 1
    git(repo, "reset", "-q", "--hard", base)
    tip = commit(repo, "both\n\nVerifier-Change: detector widened, baseline records it",
                 {"tools/name_oracle.py": "v = 3\n", ORACLE: GROWN_ORACLE})
    assert pp.check_range(base, tip) == 0


def test_a_deleted_count_cannot_come_back_raised(repo):
    base = git(repo, "rev-parse", "HEAD").stdout.strip()
    mid = commit(repo, "remove\n\nVerifier-Change: remove surplus count entry",
                 {IDENT: "multi_name.family = 0\n"})
    tip = commit(repo, "restore\n\nVerifier-Change: restore count entry",
                 {IDENT: "multi_name.family = 0\none_identity.surplus = 1000\n"})
    assert pp.check_range(mid, tip) == 1
    assert pp.check_range(base, mid) == 0
    # a brand-new key at zero is not growth
    git(repo, "reset", "-q", "--hard", base)
    tip = commit(repo, "new detector\n\nVerifier-Change: add a zero coverage floor",
                 {IDENT: "multi_name.family = 0\none_identity.surplus = 10\nnew.floor = 0\n"})
    assert pp.check_range(base, tip) == 0
