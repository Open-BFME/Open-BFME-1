"""link_debt: new hard-coded image addresses fail; renames and removals pass."""
import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_debt as L  # noqa: E402


def git(root, *args):
    subprocess.run(["git", *args], cwd=root, check=True, capture_output=True)


@pytest.fixture
def repo(tmp_path, monkeypatch):
    git(tmp_path, "init", "-q")
    git(tmp_path, "config", "user.name", "Fixture")
    git(tmp_path, "config", "user.email", "fixture@example.invalid")
    monkeypatch.setattr(L, "ROOT", tmp_path)
    return tmp_path


def put(root, path, text):
    target = root / path
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_text(text)
    git(root, "add", "--", path)


LITERAL = "int f() { return *(int *)0x012ED5C8; }\n"
NAMED = "extern int g_012ED5C8;\nint f() { return g_012ED5C8; }\n"


def test_new_literal_fails(repo):
    put(repo, "game/A.cpp", NAMED)
    git(repo, "commit", "-qm", "base")
    put(repo, "game/A.cpp", LITERAL)
    assert L.staged() == 1


def test_replacing_a_literal_passes(repo):
    put(repo, "game/A.cpp", LITERAL)
    git(repo, "commit", "-qm", "base")
    put(repo, "game/A.cpp", NAMED)
    assert L.staged() == 0


def test_moving_a_file_keeps_its_count(repo):
    put(repo, "game/A.cpp", LITERAL)
    git(repo, "commit", "-qm", "base")
    git(repo, "mv", "game/A.cpp", "game/B.cpp")
    assert L.staged() == 0


def test_new_literal_cannot_hide_behind_removal_in_another_file(repo):
    put(repo, "game/A.cpp", LITERAL)
    put(repo, "game/B.cpp", NAMED)
    git(repo, "commit", "-qm", "base")
    put(repo, "game/A.cpp", NAMED)
    put(repo, "game/B.cpp", LITERAL)
    assert L.staged() == 1


def test_new_address_cannot_replace_an_old_one_in_the_same_file(repo):
    put(repo, "game/A.cpp", LITERAL)
    git(repo, "commit", "-qm", "base")
    put(repo, "game/A.cpp", LITERAL.replace("0x012ED5C8", "0x012ED5CC"))
    assert L.staged() == 1


def test_moving_literal_into_watched_tree_fails(repo):
    put(repo, "scratch/A.cpp", LITERAL)
    git(repo, "commit", "-qm", "base")
    (repo / "game").mkdir(exist_ok=True)
    git(repo, "mv", "scratch/A.cpp", "game/A.cpp")
    assert L.staged() == 1


def test_generated_roots_are_not_watched(repo):
    put(repo, "game/A.cpp", NAMED)
    git(repo, "commit", "-qm", "base")
    put(repo, "game/gen_small/x.cpp", LITERAL)
    assert L.staged() == 0


def test_same_address_with_different_hex_format_is_allowed(repo):
    put(repo, "game/A.cpp", LITERAL)
    git(repo, "commit", "-qm", "base")
    put(repo, "game/A.cpp", LITERAL.replace("0x012ED5C8", "0x12ed5c8"))
    assert L.staged() == 0


def test_masks_and_comments_are_not_addresses():
    assert L.literals("if (x & 0x80000000) {}  // *(int *)0x012ED5C8\n") == []


def test_addresses_catch_every_form_of_an_image_address():
    text = """
    *(unsigned *)this = 0x0113C340;          // vftable stored as an integer
    m_vptr = 0x0111ff78u;
    float f = BFME_AT(float, 0x01076C24);
    return reinterpret_cast<void (*)()>(0x0043c9cf);
    """
    assert L.addresses(text) == ["0x0113C340", "0x0111ff78u", "0x01076C24", "0x0043c9cf"]


def test_addresses_skip_flags_masks_sizes_comments_and_strings():
    text = """
    m_flags |= 0x1000100;      // two bits: a flag word
    unsigned m = v & 0xffffff; // one repeated digit: a mask
    size_t n = 0x00401000;     // low 12 bits clear
    const char *s = "0x0113C340";
    /* 0x0113C340 */
    int small = 0x3FC;
    """
    assert L.addresses(text) == []
