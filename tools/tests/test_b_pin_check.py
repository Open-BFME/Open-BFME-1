"""Every b_<rva>() a compiled source calls keeps its ?b_<rva>@@YAXXZ pin.

The failure this pins down: a8ad18240f replaced ?b_0053dfc0@@YAXXZ with the
target's real name, j_0002efbe lost its target, and every compiler-free check
passed.
"""
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import b_pin_check  # noqa: E402

THUNK = "void b_0053dfc0();\nvoid j_0002efbe() { b_0053dfc0(); }\n"
FUNCTIONS = ("name,export_rva,target_rva,target_size,source,status,notes\r\n"
             "?j_0002efbe@@YAXXZ,,0x0002EFBE,5,game/gen_small/gthunks_052.cpp,matched,gen-thunk\r\n")
PIN = "?b_0053dfc0@@YAXXZ,0x0053DFC0,gen-thunk body\r\n"
REAL = "?acceptJoinGame@LANAPI@@QAEXXZ,0x0053DFC0,real name\r\n"


@pytest.fixture
def repo(tmp_path, monkeypatch):
    def git(*args):
        subprocess.run(["git", *args], cwd=tmp_path, check=True, capture_output=True)
    git("init", "-q")
    git("config", "user.name", "t")
    git("config", "user.email", "t@example.invalid")
    git("config", "core.autocrlf", "false")
    (tmp_path / "game/gen_small").mkdir(parents=True)
    (tmp_path / "targets/game/reverse").mkdir(parents=True)
    (tmp_path / "game/gen_small/gthunks_052.cpp").write_text(THUNK)
    (tmp_path / "targets/game/reverse/functions.csv").write_text(FUNCTIONS, newline="")
    monkeypatch.setattr(b_pin_check, "ROOT", tmp_path)

    def commit(pins):
        (tmp_path / "targets/game/reverse/symbols.csv").write_text("name,rva,notes\r\n" + pins, newline="")
        git("add", "-A")
        git("commit", "-qm", "x")
        return subprocess.run(["git", "rev-parse", "HEAD"], cwd=tmp_path,
                              capture_output=True, text=True, check=True).stdout.strip()
    return commit


def test_the_b_pin_beside_the_real_name_passes(repo):
    sha = repo(PIN + REAL)
    assert b_pin_check.problems(sha) == []
    assert b_pin_check.problems(None) == []
    assert b_pin_check.problems(":") == []


def test_replacing_the_b_pin_with_the_real_name_fails(repo):
    sha = repo(REAL)
    found = b_pin_check.problems(sha)
    assert len(found) == 1 and "b_0053dfc0" in found[0] and "gthunks_052.cpp" in found[0]


def test_a_b_pin_at_the_wrong_address_fails(repo):
    sha = repo("?b_0053dfc0@@YAXXZ,0x0053DFD0,typo\r\n")
    found = b_pin_check.problems(sha)
    assert any("not the 0x0053DFC0" in line for line in found)


def test_a_source_no_row_compiles_is_ignored(repo, tmp_path):
    (tmp_path / "game/gen_small/orphan.cpp").write_text("void b_00123456();\nvoid f() { b_00123456(); }\n")
    sha = repo(PIN)
    assert b_pin_check.problems(sha) == []
