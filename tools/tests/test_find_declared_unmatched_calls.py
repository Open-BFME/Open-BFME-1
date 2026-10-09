#!/usr/bin/env python3
"""A qualified call split over lines is not a definition.

re_attempts.log 0x00366970: `_STL::_Construct(&p->m_value,` / `value);` inside
Rva00366970Store::append has the `Qualified::name(` shape and no ';' on its
first line, so the checker reported a definition of _STL::_Construct and
refused the commit.
"""
import importlib.util
import sys
from pathlib import Path

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
_spec = importlib.util.spec_from_file_location(
    "fdu_calls_under_test", TOOLS / "find_declared_unmatched.py")
fdu = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(fdu)


def names(text):
    return [(cls, method) for _line, cls, method, _note in fdu.iter_definitions(text)]


def test_multiline_qualified_call_is_not_a_definition():
    text = """
void Rva00366970Store::append(const Rva00366890Element *p, const AsciiString &a)
{
\t_STL::_Construct(&m_last->m_name,
\t\ta);
\tif (Owner::check(a,
\t\t\tp) && x)
\t\treturn;
}
"""
    assert names(text) == [("Rva00366970Store", "append")]


def test_multiline_definitions_are_still_definitions():
    text = """
// ?run@Owner@@QAEXHH@Z
void Owner::run(int a,
\t\tint b) const
{
}
Owner::Owner(int a,
\t\tint b)
\t: m_a(a)
{
}
template Value &Map::operator[](
\tconst Key &key);
"""
    assert names(text) == [("Owner", "run"), ("Owner", "Owner"), ("Map", "operator[]")]
    assert list(fdu.iter_definitions(text))[0][3] == "?run@Owner@@QAEXHH@Z"


def test_annotation_above_a_call_does_not_bind_to_the_next_definition():
    text = """
// ?_Init@PointGroupClass@@ present-unmatched
PointGroupClass::_Init(a,
\tb);
void Owner::run()
{
}
"""
    assert list(fdu.iter_definitions(text)) == [(5, "Owner", "run", None)]
