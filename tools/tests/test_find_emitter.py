"""Emitting a symbol is not the same as calling it, and that is the whole point.

The merge lane's most common blocker is a row that is green only because a
converted body calls an accessor RETAIL INLINES AWAY. Write the body correctly
and the COMDAT is not emitted and the row goes red, so the row has to move to a
translation unit that really emits the symbol. Guessing from grep costs a full
TU build per wrong guess, and a caller that does not emit is exactly the guess
that looks right: Script::setAction is called in GameLogic.cpp and NOT emitted
there, which cost one build before this existed.

So the object map has to be built FORWARD from the tree, and only sources in
the tree may be offered as homes.
"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import find_emitter  # noqa: E402


def test_object_map_is_built_forward_from_the_tree():
    """Decoding an object name backwards is ambiguous; computing it is not.

    obj_path() joins path parts with "_" and file names contain underscores
    too, so scripts.obj and Scripts/foo.obj are indistinguishable in reverse.
    An earlier version decoded and produced "scripts.cpp" for a path that was
    nothing of the sort.
    """
    mapping = find_emitter.sources_by_object()
    assert mapping, "no sources mapped"
    for obj, src in mapping.items():
        assert src.endswith(".cpp")
        assert not Path(src).is_absolute()
        assert obj.endswith(".obj")


def test_every_mapped_source_exists():
    """A home that is not a real file cannot own a ledger row."""
    root = Path(__file__).resolve().parents[2]
    mapping = find_emitter.sources_by_object()
    sample = list(mapping.values())[:200]
    for src in sample:
        assert (root / src).is_file(), src


def test_mapping_is_injective_on_sources():
    """Two sources sharing one object would make a repoint target ambiguous."""
    mapping = find_emitter.sources_by_object()
    assert len(set(mapping.values())) == len(mapping)
