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
    """AsciiString and Coord3D are in the table now (read from their headers); a type
    that is genuinely unknown still stops the walk rather than being approximated."""
    _, refused = members("struct S {\n\tSomeUnknownThing m_name;\n\tint m_after;\n};")
    assert refused.startswith("unsizeable type")


def test_refuses_a_union():
    """Union members overlay; this model sums them. PathfindCellInfo produced nine
    wrong offsets the moment ICoord2D became sizeable and stopped hiding the struct."""
    _, refused = members(
        "struct S {\n\tunion { int m_a; char m_b; };\n\tint m_after;\n};")
    assert refused == "contains a union"


def test_header_read_sizes_place_the_members_after_them():
    """AsciiString is one `Header *m_data` (string_base.h:80); Coord3D is three Reals
    but aligns to 4, so its size must not be mistaken for its alignment."""
    got, refused = members(
        "struct S {\n\tAsciiString m_name;\n\tCoord3D m_where;\n\tchar m_tag;\n};")
    assert refused is None
    assert got == {"m_name": 0, "m_where": 4, "m_tag": 16}


def test_new_header_sizes_place_the_members_after_them():
    """Rva0036CA00Str is one pointer; BfmeNetAddress is UnsignedInt+UnsignedShort
    padded to 8; BfmeSubObject is char[4] aligning to 1; Matrix3D is Vector4[3];
    AudioEventRTS is 0x70; FieldParse is four pointer/Int fields."""
    got, refused = members("""struct S {
	Rva0036CA00Str m_name;
	BfmeNetAddress m_addr;
	BfmeSubObject m_sub;
	char m_tag;
	Matrix3D m_xform;
	AudioEventRTS m_sound;
	FieldParse m_parse;
};""")
    assert refused is None
    assert got == {
        "m_name": 0,
        "m_addr": 4,
        "m_sub": 12,
        "m_tag": 16,
        "m_xform": 20,
        "m_sound": 68,
        "m_parse": 0x70 + 68,
    }


def test_static_members_do_not_occupy_instance_space():
    """static const FieldParse tables blocked 22 structs. Static members are not
    in the instance layout, so they are skipped rather than sized -- sizing them
    would push every following member, the same class of bug as summing a union."""
    got, refused = members("""struct S {
	int m_key;
	static const FieldParse m_fieldParseTable[];
	int m_after;
};""")
    assert refused is None
    assert got == {"m_key": 0, "m_after": 4}


def test_template_parameter_and_bitset_stay_unsizeable():
    """T is a template parameter; _STL::bitset<NUMBITS> depends on one. Inventing
    a number would shift every following member of 200+ structs."""
    _, refused_t = members("struct S {\n\tT m_item;\n\tint m_after;\n};")
    assert refused_t.startswith("unsizeable type")
    _, refused_bits = members(
        "struct S {\n\t_STL::bitset<NUMBITS> m_bits;\n\tint m_after;\n};")
    assert refused_bits.startswith("unsizeable type")


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


def test_a_member_reports_its_size_so_a_span_can_be_told_from_a_field():
    """`char m_unknown[0x54]` starting where s_GlobalDataFieldParseTable starts is not
    that field -- it is unknown SPACE beginning there. --todo must not offer to rename
    it, or a 0x54-byte pad acquires the name of the 4-byte pointer at its front."""
    rows, refused = N.outer_members(
        "struct S {\n\tchar m_unknown[0x54];\n\tint m_after;\n};", 9, False)
    assert refused is None
    assert [(r[0], r[1], r[4], r[5]) for r in rows] == [
        ("m_unknown", 0, 0x54, True), ("m_after", 0x54, 4, False)]


def test_scan_can_be_pointed_at_alternate_file_contents():
    """The introduced-vs-inherited gate works by running the identical walk against
    HEAD's version of each staged file. An inherited placeholder is somebody else's
    backlog and must never fail a commit; only what this diff ADDS does."""
    path = N.ROOT / "Code/GameEngine/Source/__fixture__.cpp"
    body = "struct Anything {\n\tint m_unk04;\n};\n"
    tally, todo, conflicts = N.scan([str(path)], False, texts={path: body})
    # No witness knows `Anything`, so nothing is claimed either way -- what this
    # asserts is that the override is honoured and no disk read is attempted.
    assert not conflicts and not todo
    assert tally["members computed"] == 1
