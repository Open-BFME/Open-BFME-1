"""Prose mentioning the marker phrase must not hard-fail the whole tree.

A note explaining the marker convention once contained `readable body of` in an
ordinary sentence. Every line holding the phrase had to parse as a marker, so
--list, --plan and --apply died tree-wide and every lane was blocked until the
prose was reworded. Narrowing what counts as an ATTEMPTED marker fixes that
without softening the failure a genuinely malformed marker must still produce.
"""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import merge_cluster  # noqa: E402


def _markers(tmp_path, text):
    f = tmp_path / "a.cpp"
    f.write_text(text)
    return merge_cluster.markers(f)


def test_well_formed_marker_is_read(tmp_path):
    got = _markers(tmp_path, "// readable body of ?foo@@YAXXZ: Code/Dest.cpp\n")
    assert got == [("?foo@@YAXXZ", "Code/Dest.cpp")]


def test_prose_mentioning_the_phrase_is_not_a_marker(tmp_path):
    """The exact shape that blocked every lane."""
    text = ("// My mis-anchoring note wrote the phrase `readable body of` in prose,\n"
            "// which merge_cluster scanned and hard-failed on.\n")
    assert _markers(tmp_path, text) == []


def test_prose_and_a_real_marker_coexist(tmp_path):
    text = ("// Explaining a `readable body of` marker in prose here.\n"
            "// readable body of ?bar@@YAXXZ: Code/Dest.cpp\n")
    assert _markers(tmp_path, text) == [("?bar@@YAXXZ", "Code/Dest.cpp")]


def test_malformed_marker_still_fails_loudly(tmp_path):
    """A dropped marker silently loses a body from its cluster -- keep failing."""
    with pytest.raises(SystemExit):
        _markers(tmp_path, "// readable body of ?baz@@YAXXZ -> Code/Dest.cpp\n")


def test_trailing_comment_marker_still_fails_loudly(tmp_path):
    """Marker position matters; a trailing one would never be applied."""
    with pytest.raises(SystemExit):
        _markers(tmp_path, "int x; // readable body of ?qux@@YAXXZ: Code/Dest.cpp\n")
