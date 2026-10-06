"""conversion_gate rule C1: a game/gen_asm/ edit passes only as dump_apply's exact output.

The fixture repository holds one real dump source (its committed text from this
tree) so dump_apply.reproduce runs on real retail bytes and the real ledger.
"""
import subprocess
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import conversion_gate as gate  # noqa: E402
import dump_apply  # noqa: E402

SOURCE = "game/gen_asm/d_00138250.asm"   # 2 live bodies, calls through ?j_ thunks and data refs


def git(repo, *args):
    return subprocess.run(["git", "-C", str(repo), *args], check=True, capture_output=True).stdout


@pytest.fixture(scope="module")
def context():
    return dump_apply.Context()


@pytest.fixture(scope="module")
def original():
    """The unconverted dump as this tree last committed it (before Option A)."""
    raw = subprocess.run(["git", "-C", str(ROOT), "log", "--format=%H", "-1", "--", SOURCE],
                         capture_output=True, text=True, check=True).stdout.strip()
    text = git(ROOT, "show", f"{raw}:{SOURCE}")
    if dump_apply.HEADER.encode() in text:
        text = git(ROOT, "show", f"{raw}~1:{SOURCE}")
    assert dump_apply.HEADER.encode() not in text
    return text.replace(b"\r\n", b"\n")


@pytest.fixture(scope="module")
def converted(context, original):
    text, bodies = dump_apply.reproduce(SOURCE, original.decode("utf-8"), context)
    assert text is not None and bodies
    return text.encode("utf-8")


def repo_with(tmp_path, base, staged, path=SOURCE):
    """A repository whose HEAD holds `base` at path and whose index holds `staged`."""
    repo = tmp_path / "r"
    (repo / Path(path).parent).mkdir(parents=True)
    (repo / "targets/game/reverse").mkdir(parents=True)
    (repo / "targets/game/reverse/functions.csv").write_text(
        "name,export_rva,target_rva,target_size,source,status,notes\n")
    git(repo, "init", "-q")
    git(repo, "config", "core.autocrlf", "false")
    (repo / path).write_bytes(base)
    git(repo, "add", "-A")
    git(repo, "-c", "user.name=fixture", "-c", "user.email=f@example.invalid", "commit", "-qm", "base")
    (repo / path).write_bytes(staged)
    git(repo, "add", "-A")
    return repo


def offences(repo, monkeypatch, context):
    monkeypatch.chdir(repo)
    monkeypatch.setattr(gate, "_DUMP_APPLY", [context])
    return gate.gen_asm_offences("HEAD", ":")


def test_hand_edit_is_refused(tmp_path, monkeypatch, context, original):
    staged = original.replace(b"_TEXT ENDS", b"    mov eax, 1\n_TEXT ENDS", 1)
    found = offences(repo_with(tmp_path, original, staged), monkeypatch, context)
    assert found and all(f.startswith("C1 ") for f in found)


def test_tool_reproduced_conversion_is_accepted(tmp_path, monkeypatch, context, original, converted):
    assert offences(repo_with(tmp_path, original, converted), monkeypatch, context) == []


def test_tool_output_with_one_byte_changed_is_refused(tmp_path, monkeypatch, context, original, converted):
    # the changed byte sits in a line the generator grammar allows: only whole-file
    # reproduction can see it
    i = converted.index(b"    db 0") + len(b"    db 0")
    staged = converted[:i] + (b"1" if converted[i:i + 1] != b"1" else b"2") + converted[i + 1:]
    found = offences(repo_with(tmp_path, original, staged), monkeypatch, context)
    assert found and all(f.startswith("C1 ") for f in found)


def test_tool_output_from_a_different_base_is_refused(tmp_path, monkeypatch, context, original, converted):
    other_base = original.replace(b".model flat\n", b".model flat\n; a different base\n", 1)
    found = offences(repo_with(tmp_path, other_base, converted), monkeypatch, context)
    assert found and all(f.startswith("C1 ") for f in found)


def test_non_gen_asm_files_are_unaffected(tmp_path, monkeypatch, context):
    called = []
    monkeypatch.setattr(gate, "tool_reproduced", lambda *a: called.append(a) or False)
    base = b".386\n.model flat\n_TEXT SEGMENT\n_TEXT ENDS\nEND\n"
    staged = base.replace(b"_TEXT ENDS", b"    call ?f@@YAXXZ\n_TEXT ENDS")
    repo = repo_with(tmp_path, base, staged, path="game/masm_dumps/X.asm")
    assert offences(repo, monkeypatch, context) == [] and called == []
