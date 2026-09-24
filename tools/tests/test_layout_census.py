"""layout_census reads TU-local class bodies without a compiler, then asks one."""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import layout_census


BODY = """
class Object
{
public:
	virtual void unused00() = 0;
	virtual Drawable *getDrawable() const = 0;
	Weapon *getCurrentWeapon(WeaponSlotType *slot);
	void inlineBody() { if (m_id) { m_id = 0; } }

	char m_pad00[0x38 - 4];
	Coord3D m_position;
	Int m_a, *m_b, m_c[4];
	UnsignedInt m_bits : 3;
	static Int s_count;
	enum { SLOT_COUNT = 4 };
	ObjectID m_id;
};
"""


def test_find_class_returns_base_list_and_body():
    head, body = layout_census.find_class("int x;\nclass Object : public Thing\n{\n int m_a;\n};\n", "Object")
    assert head == "class Object : public Thing"
    assert "m_a" in body


def test_find_class_ignores_forward_declarations():
    assert layout_census.find_class("class Object;\nstruct Other { int x; };\n", "Object") is None


def test_parse_members_splits_data_virtuals_and_methods():
    _head, body = layout_census.find_class(layout_census.strip_comments(BODY), "Object")
    data, virtuals, methods = layout_census.parse_members(body)
    assert [name for name, _ in data] == ["m_pad00", "m_position", "m_a", "m_b", "m_c", "m_id"]
    assert dict(data)["m_c"] == "Int [4]"
    assert dict(data)["m_b"] == "Int *"
    assert virtuals == ["virtual void unused00() = 0", "virtual Drawable *getDrawable() const = 0"]
    assert methods[0] == "Weapon *getCurrentWeapon(WeaponSlotType *slot)"
    assert methods[1] == "void inlineBody()"


def test_probe_values_parse_vc71_out_of_line_arguments():
    text = ("x.cpp(9) : error C2079: 'layout_census_4' uses undefined struct 'LayoutCensusValue<N>'\n"
            "        with\n        [\n            N=56\n        ]\n")
    assert {m.group(1): int(m.group(2)) for m in layout_census.VALUE.finditer(text)} == {"layout_census_4": 56}


def test_named_skips_opaque_byte_pads():
    record = {"members": [
        {"name": "m_pad", "type": "unsigned char [0x70]", "offset": 4, "size": 0x70},
        {"name": "m_id", "type": "ObjectID", "offset": 0x74, "size": 4},
    ]}
    assert [m["name"] for m in layout_census.named(record)] == ["m_id"]
    assert layout_census.kind("ObjectID", 4) == layout_census.kind("unsigned int", 4) == "int32"
    assert layout_census.kind("const ThingTemplate *", 4) == "ptr"
