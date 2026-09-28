"""header_dependents: a header change reaches exactly the sources that can include it, and
every doubt widens the set or falls back to the full gate."""
import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
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
