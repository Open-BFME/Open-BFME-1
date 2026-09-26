"""Only a real placeholder row may be taken over with --replace-rva.

add_match and add_match_batch each carried a prefix copy of the marker test,
so a row of real C++ whose note begins "gen-dump conversion; ..." could be
retired as if it were a dump. The marker is the whole first token, exactly as
build.is_scaffold_row reads it.
"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import add_match


def row(notes, source="game/gen_asm/d_00401000.asm"):
    return {"notes": notes, "source": source}


def test_bare_markers_are_placeholders():
    assert add_match.replaceable_scaffold(row("gen-dump"))
    assert add_match.replaceable_scaffold(row("gen-dump;size=40"))
    assert add_match.replaceable_scaffold(row(" gen-thunk"))
    assert add_match.replaceable_scaffold(row("gen-thunk,target=0x00401000"))


def test_free_text_that_begins_with_a_marker_is_a_real_claim():
    real = "game/GameEngine/Source/Common/GenUwm008A4B20.cpp"
    assert not add_match.replaceable_scaffold(row("gen-dump conversion; 64-slot table", real))
    assert not add_match.replaceable_scaffold(row("gen-dump converted to address-derived name", real))
    assert not add_match.replaceable_scaffold(row("gen-thunked by hand", real))


def test_the_batch_tool_uses_the_same_marker():
    text = (Path(__file__).resolve().parents[1] / "add_match_batch.py").read_text(encoding="utf-8")
    assert "add_match.SCAFFOLD_NOTE.match" in text
    assert 'startswith(("gen-dump", "gen-thunk"))' not in text
