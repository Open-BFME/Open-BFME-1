"""The offset model, and the four cases it must REFUSE rather than approximate.

This checker asserts an offset for a member the source never states, then compares
the name at that offset against the ZH<->retail witness. Every wrong offset it
computes becomes a false finding on somebody else's commit, and it runs in the
pre-commit hook of a repository taking 30-50 commits an hour. So the interesting
tests here are not the arithmetic -- they are the refusals, because a model that
guesses past what it knows fails loudly in the fixtures and silently in production.

The arithmetic itself has a better test than any fixture: 5,285 member declarations
in the tree already state their own offset, and `--selfcheck` reproduces 99.5% of
them. That is what guards SIZES and the alignment rule; these fixtures guard the
decisions --selfcheck cannot see, because a refused struct never reaches it.
"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import name_oracle as N


def members(src, has_base=False):
    """Run the walker over one declaration and return (names->offsets, refusal)."""
    brace = src.index("{")
    rows, refused = N.outer_members(src, brace, has_base)
    return {r[0]: r[1] for r in rows}, refused


def test_offsets_follow_declaration_order_and_alignment():
    got, refused = members("""struct S {
\tchar m_flag;
\tint m_count;
\tchar m_tag;
\tdouble m_when;
};""")
    assert refused is None
    # 0, then int aligns to 4, then char at 8, then double aligns to 16 (/Zp8 caps
    # alignment at 8, and 9 rounded up to 8 is 16).
    assert got == {"m_flag": 0, "m_count": 4, "m_tag": 8, "m_when": 16}


def test_pointer_is_four_bytes_and_array_spans_multiply():
    got, refused = members("""struct S {
\tchar m_head[0x10 - 0x00];
\tS *m_next;
\tint m_rows[3];
};""")
    assert refused is None
    assert got == {"m_head": 0, "m_next": 0x10, "m_rows": 0x14}


def test_virtual_class_starts_after_the_vptr():
    """The off-by-four cluster that took the model from 90.5% to 99.5%."""
    got, refused = members("""class S {
\tvirtual void step(void);
\tint m_first;
};""")
    assert refused is None
    assert got == {"m_first": 4}


def test_refuses_a_base_class():
    """Members start at sizeof(base), which nothing here knows."""
    _, refused = members("struct S : public Other {\n\tint m_a;\n};", has_base=True)
    assert refused == "base class of unknown size"


def test_refuses_an_unsizeable_type():
    _, refused = members("struct S {\n\tAsciiString m_name;\n\tint m_after;\n};")
    assert refused.startswith("unsizeable type")


def test_refuses_a_declaration_that_windows_into_a_larger_class():
    """`GlobalData::m_bfmeOn` states +0x1278 as its FIRST member: the declaration is a
    slice of a bigger class, so every offset in it is relative to something unknown."""
    _, refused = members("struct S {\n\tint m_mid;\t// +0x1278\n};")
    assert refused == "declaration windows into a larger class"


def test_annotation_that_contradicts_the_model_disqualifies_the_struct():
    """The file wins, and the struct is dropped rather than half-trusted. This is what
    keeps the 25 known packed-struct residuals from becoming 25 false findings."""
    _, refused = members("struct S {\n\tint m_a;\t// +0x0\n\tchar m_b;\t// +0x8\n};")
    assert refused == "annotation contradicts the computed layout"


def test_agreeing_annotations_are_kept_and_reported():
    rows, refused = N.outer_members(
        "struct S {\n\tint m_a;\t// +0x0\n\tint m_b;\t// +0x4\n};", 9, False)
    assert refused is None
    assert [(r[0], r[1], r[3]) for r in rows] == [("m_a", 0, 0), ("m_b", 4, 4)]


def test_nested_struct_offsets_never_leak_into_the_outer_type():
    """GeometryInfo's inner BfmeShape::m_height was scored against GeometryInfo+0x04
    and reported a correct file as a defect, at a 22% false rate."""
    got, refused = members("""struct Outer {
\tstruct Inner
\t{
\t\tint m_height;
\t};
\tint m_first;
};""")
    assert refused is None
    assert got == {"m_first": 0}


def test_placeholder_shapes_are_told_apart_from_real_names():
    """--todo is free work with the answer attached; --check is a question for a
    human. Misfiling one as the other buries the easy wins under the hard ones."""
    for name in ("m_a", "m_unk20", "m_pad0c", "m_slot1c", "m_bfme0C", "m_int54", "m_unmodelled_000"):
        assert N.PLACEHOLDER.match(name), name
    for name in ("m_priority", "m_shouldFade", "m_currentState", "m_boundingCircleRadius"):
        assert not N.PLACEHOLDER.match(name), name
