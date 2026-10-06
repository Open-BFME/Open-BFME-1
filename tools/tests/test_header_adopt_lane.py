"""header_adopt_lane: source surgery, header generation, failure taxonomy and the closure check."""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import header_adopt_lane as lane  # noqa: E402

UNIT = """// cl: /O2
typedef float Real;
// struct Coord3D { int fake; };
struct Coord3D
{
    Real x, y, z;
    void zero() { x = y = z = 0.0f; }
};
template <class T>
class StringBase { T *p; };
class AsciiString : public StringBase<char> { char *m_data; };
void use(Coord3D *c) { c->zero(); }
"""

CONTRACT = {"class": "Coord3D", "key": "struct", "key_by": "bytes", "size": 12, "size_by": "zh", "bases": [],
            "fields": [{"offset": o, "size": 4, "kind": "f4", "type": "float", "name": n}
                       for o, n in ((0, "x"), (4, "y"), (8, "z"))]}


def test_swap_strips_the_view_and_includes_the_header_where_it_stood():
    out = lane.swap(UNIT, ["Coord3D"], "../Lib/Coord3D.h")
    assert "Real x, y, z;" not in out
    assert out.index('#include "../Lib/Coord3D.h"') < out.index("void use")
    assert "// struct Coord3D { int fake; };" in out          # a commented-out head is not a view
    assert lane.swap("void f();\n", ["Coord3D"], "x.h") is None


def test_dependency_views_go_with_the_class():
    out = lane.swap(UNIT, ["AsciiString", "StringBase"], "ascii_string.h")
    assert "StringBase" not in out.split("void use")[0].split('#include "ascii_string.h"')[1]
    assert "template <class T>" not in out
    assert out.count('#include "ascii_string.h"') == 1


def test_generated_header_spells_the_contract():
    text = lane.generate(CONTRACT, "data", {})
    assert "struct Coord3D {" in text and "float x;" in text and "float z;" in text
    assert "Coord3D() {}" not in text
    assert "Coord3D() {}" in lane.generate(CONTRACT, "data+ctor", {})


def test_failure_taxonomy():
    assert lane.failure_class("x.cpp(3) : error C2039: 'zero' : is not a member") == "C2039 missing member"
    assert lane.failure_class("x.cpp(3) : error C2371: 'Bool' : redefinition") == "C2371"
    assert lane.failure_class("Functions: FAIL ?f@@YAXXZ") == "bytes/callee identity"


def test_closure_diff_flags_lost_rows(tmp_path):
    head = "name,retail_rva,closed_strict\n"
    before, same, lost = tmp_path / "a.csv", tmp_path / "b.csv", tmp_path / "c.csv"
    before.write_text(head + "?f@@YAXXZ,0x00401000,1\n?g@@YAXXZ,0x00401010,0\n")
    same.write_text(head + "?f@@YAXXZ,0x00401000,1\n?g@@YAXXZ,0x00401010,1\n")
    lost.write_text(head + "?f@@YAXXZ,0x00401000,0\n?g@@YAXXZ,0x00401010,1\n")
    assert lane.closure_diff(before, same) == 0      # negative control: closure only grew
    assert lane.closure_diff(before, lost) == 1      # positive control: a closed row was lost
