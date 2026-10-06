#!/usr/bin/env python3
"""ilt_repair: the access/const source edits and the ledger names they produce."""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import ilt_repair as R  # noqa: E402

DTOR = """class A
{
protected:
\tvirtual ~A();
private:
\tfriend void forceA();
};
"""


def test_sole_member_under_a_label_swaps_the_label():
    assert R.edit_member(DTOR, "A", None, "MAE", "UAE") == DTOR.replace("protected:", "public:")


def test_member_among_others_is_wrapped_and_access_restored():
    src = "struct B\n{\n\tint f();\n\tint g();\n};\nint B::f() { return 1; }\n"
    out = R.edit_member(src, "B", "f", "QAE", "IAE")
    assert out == "struct B\n{\nprotected:\n\tint f();\npublic:\n\tint g();\n};\nint B::f() { return 1; }\n"


def test_const_toggle_edits_declaration_and_out_of_line_definition():
    src = "class C\n{\npublic:\n\tint get(int x);\n};\nint C::get(int x) { return x; }\n"
    out = R.edit_member(src, "C", "get", "QAE", "QBE")
    assert out == "class C\n{\npublic:\n\tint get(int x) const;\n};\nint C::get(int x) const { return x; }\n"
    assert R.edit_member(out, "C", "get", "QBE", "QAE") == src


def test_unsupported_shapes_are_refused():
    assert R.edit_member(DTOR, "A", None, "QAE", "UAE") is None          # recorded access disagrees with source
    assert R.edit_member("class D { void f(); void f(int); };", "D", "f", "AAE", "QAE") is None   # overloads
    assert R.edit_member(DTOR, "A", "missing", "QAE", "IAE") is R.ABSENT
    assert R.edit_member(DTOR + DTOR, "A", None, "MAE", "UAE") is None   # two declarations of the class


def test_ledger_names_follow_the_edit():
    assert R.renamed("??_GA@@MAEPAXI@Z", "A", None, "MAE", "UAE") == "??_GA@@UAEPAXI@Z"
    assert R.renamed("??1A@@MAE@XZ", "A", None, "MAE", "UAE") == "??1A@@UAE@XZ"
    assert R.renamed("?get@C@@QAEHH@Z", "C", "get", "QAE", "QBE") == "?get@C@@QBEHH@Z"
    assert R.renamed("?get@CX@@QAEHH@Z", "C", "get", "QAE", "QBE") is None
    assert R.member_of("?get@C@@QAEHH@Z") == ("C", "get", "QAE")
    assert R.member_of("??_GA@@MAEPAXI@Z") == ("A", None, "MAE")


def test_reference_tokens():
    assert R.tokens("?b_000659e0@@YAXXZ") == ["b_000659e0"]
    assert R.tokens("??1Gen_dtor_00075d40@@UAE@XZ") == ["Gen_dtor_00075d40"]
    assert R.tokens("?f@C@@QAEXXZ") == ["f", "C"]
    assert R.tokens("??$f@H@@YAXXZ") is None
