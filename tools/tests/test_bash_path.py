"""bash_path: Git for Windows' own bash on Windows, never WSL's, and PATH order kept for stubs."""
import os
from pathlib import Path
import sys

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import bash_path  # noqa: E402


def touch(path):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(b"")
    return path


def test_elsewhere_the_plain_bash(tmp_path):
    assert bash_path._find("posix", "/usr/bin/git", str(tmp_path)) == "bash"


def test_windows_prefers_the_git_on_path(tmp_path):
    git = touch(tmp_path / "Portable Git/cmd/git.exe")
    wanted = touch(tmp_path / "Portable Git/usr/bin/bash.exe")
    touch(tmp_path / "Program Files/Git/usr/bin/bash.exe")
    assert bash_path._find("nt", str(git), str(tmp_path / "Program Files")) == str(wanted)


def test_windows_git_from_mingw64_finds_its_root(tmp_path):
    git = touch(tmp_path / "Git/mingw64/bin/git.exe")
    wanted = touch(tmp_path / "Git/usr/bin/bash.exe")
    assert bash_path._find("nt", str(git), str(tmp_path / "none")) == str(wanted)


def test_windows_falls_back_to_program_files(tmp_path):
    wanted = touch(tmp_path / "Program Files/Git/usr/bin/bash.exe")
    assert bash_path._find("nt", None, str(tmp_path / "Program Files")) == str(wanted)


def test_windows_without_git_bash_refuses_rather_than_reach_wsl(tmp_path):
    touch(tmp_path / "Windows/System32/bash.exe")
    with pytest.raises(RuntimeError, match="usr/bin/bash.exe not found"):
        bash_path._find("nt", None, str(tmp_path / "Program Files"))


def test_env_puts_git_before_the_host_path_and_behind_the_callers_stubs(tmp_path, monkeypatch):
    root = tmp_path / "Git"
    git = [str(root / "mingw64/bin"), str(root / "usr/bin")]
    monkeypatch.setattr(bash_path.os, "name", "nt")
    monkeypatch.setattr(bash_path, "bash", lambda: str(root / "usr/bin/bash.exe"))
    monkeypatch.setenv("PATH", os.pathsep.join(["system32", "host", git[1]]))
    base = {"PATH": os.pathsep.join(["stubs", "system32", "host", git[1]]), "KEEP": "1"}
    result = bash_path.env(base)
    assert result["PATH"].split(os.pathsep) == ["stubs", *git, "system32", "host"]
    assert result["KEEP"] == "1" and base["PATH"].startswith("stubs")
    assert bash_path.env(result)["PATH"] == result["PATH"]
    assert bash_path.env()["PATH"].split(os.pathsep) == [*git, "system32", "host"]


def test_env_elsewhere_is_an_unchanged_copy(monkeypatch):
    monkeypatch.setattr(bash_path.os, "name", "posix")
    base = {"PATH": "/stubs:/usr/bin"}
    result = bash_path.env(base)
    assert result == base and result is not base
