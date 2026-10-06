"""TU map, skeleton composition and the ownership invariants, on throwaway trees.

Positive controls are commits the old hooks let through and these rules must
refuse (a second row for an owned address, a row moved into the wrong file, a
second body of an owned function, a private copy of a registered class).
Negative controls are the edits the fleet makes every hour and that must keep
passing (an edit in place, a move into the approved TU, an inline helper, a
copy the author allowed explicitly).
"""
import importlib.util
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
HEADER = "name,export_rva,target_rva,target_size,source,status,notes\n"


def _load(name):
    if name not in sys.modules:
        spec = importlib.util.spec_from_file_location(name, TOOLS / f"{name}.py")
        module = importlib.util.module_from_spec(spec)
        sys.modules[name] = module
        spec.loader.exec_module(module)
    return sys.modules[name]


tu_map = _load("tu_map")
tu_skeleton = _load("tu_skeleton")
tu_ownership = _load("tu_ownership")


def row(name, rva, size, source, status="matched", notes=""):
    return f"{name},,0x{rva:08X},{size},{source},{status},{notes}\n"


# ---------------------------------------------------------------- tu_map
@pytest.fixture
def mapped(tmp_path):
    zh = tmp_path / "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code"
    (zh / "GameEngine/Source/Die").mkdir(parents=True)
    (zh / "GameEngine/Source/Die/FooDie.cpp").write_text(
        "void FooDie::onDie(int)\n{\n}\nFooDie::FooDie(Thing *t)\n{\n}\n")
    (zh / "GameEngine/Source/Die/BarDie.cpp").write_text("void BarDie::onDie(int)\n{\n}\n")
    rev = tmp_path / "reverse"
    rev.mkdir()
    d = "Code/GameEngine/Source/Die"
    (rev / "functions.csv").write_text(HEADER + "".join([
        row("??0FooDie@@QAE@PAVThing@@@Z", 0x1000, 16, f"{d}/FooDieCtor.cpp"),        # S/Z anchor
        row("?rva00001010@Rva00001010@@QAEXXZ", 0x1010, 16, f"{d}/Rva1010.cpp"),     # bracketed (C)
        row("?onDie@FooDie@@UAEXH@Z", 0x1020, 16, f"{d}/FooDieOnDie.cpp"),           # Z anchor
        row("??_GFooDie@@UAEPAXI@Z", 0x9000, 16, f"{d}/FooDieDel.cpp"),             # COMDAT far away
        row("?onDie@BarDie@@UAEXH@Z", 0x20000, 16, f"{d}/BarDieOnDie.cpp"),
        row("?helper@Lone@@QAEXXZ", 0x40000, 16, f"{d}/Lone.cpp"),                  # N only
        row("?other@Lone@@QAEXXZ", 0x40010, 16, f"{d}/LoneOther.cpp"),
    ]))
    (rev / "ghidra_functions.csv").write_text("rva,size,name\n0x1030,8,FUN_1030\n0x1040,8,FUN_1040\n")
    (rev / "string_xrefs.tsv").write_text("C:\\bfme2\\Code\\GameEngine\\Source\\Die\\BarDie.cpp\t0x20004\n")
    out = tu_map.build(tu_map.Layout(tmp_path))
    return {int(r["rva"], 16): r for r in out}


def test_anchored_and_contiguous_rows_are_approved(mapped):
    foo = "Code/GameEngine/Source/Die/FooDie.cpp"
    assert mapped[0x1000]["tu"] == foo and mapped[0x1000]["confidence"] == "approved"
    assert mapped[0x1020]["by"] == "Z" and mapped[0x1020]["confidence"] == "approved"
    assert mapped[0x1010]["by"] == "C" and mapped[0x1010]["confidence"] == "approved"
    assert mapped[0x20000]["by"] == "F" and mapped[0x20000]["tu"].endswith("Die/BarDie.cpp")


def test_header_inline_comdat_far_from_its_class_is_displaced(mapped):
    assert mapped[0x9000]["confidence"] == "displaced" and mapped[0x9000]["tu"] == ""


def test_naming_convention_alone_is_only_proposed(mapped):
    assert mapped[0x40000]["confidence"] == "proposed"
    assert mapped[0x40000]["tu"] == "Code/GameEngine/Source/Die/Lone.cpp"


def test_unledgered_retail_function_between_anchors_gets_no_ledger_source(mapped):
    assert 0x1030 not in mapped or mapped[0x1030]["kind"] == "code-unledgered"


def test_map_is_deterministic(tmp_path, mapped):
    layout = tu_map.Layout(tmp_path)
    assert tu_map.render(tu_map.build(layout)) == tu_map.render(tu_map.build(layout))


def test_noncontiguous_tu_is_not_approved(tmp_path):
    zh = tmp_path / "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/X"
    zh.mkdir(parents=True)
    (zh / "A.cpp").write_text("void A::f()\n{\n}\nvoid A::g()\n{\n}\n")
    (zh / "B.cpp").write_text("void B::f()\n{\n}\n")
    (tmp_path / "reverse").mkdir()
    (tmp_path / "reverse/functions.csv").write_text(HEADER + "".join([
        row("?f@A@@QAEXXZ", 0x1000, 16, "Code/X/Af.cpp"),
        row("?f@B@@QAEXXZ", 0x2000, 16, "Code/X/Bf.cpp"),     # B's anchor inside A's span
        row("?g@A@@QAEXXZ", 0x3800, 16, "Code/X/Ag.cpp"),
    ]))
    out = {int(r["rva"], 16): r for r in tu_map.build(tu_map.Layout(tmp_path))}
    assert out[0x1000]["confidence"] == "proposed" and "noncontiguous" in out[0x1000]["evidence"]


# ---------------------------------------------------------------- skeleton
def test_chunks_keep_comments_and_ignore_braces_in_literals():
    text = ('#include "a.h"\n// lead comment\nstruct S { int a; };\n'
            'const char *s = "}{";\nint f()\n{\n    return \'}\';  // }\n}\n')
    got = tu_skeleton.chunks(text)
    kinds = [k for k, _ in got]
    assert kinds == ["pp", "decl", "decl", "def"]
    assert "// lead comment" in got[1][1]
    assert got[3][1].strip().endswith("}") and "return '}'" in got[3][1]


def test_compose_dedupes_declarations_and_marks_placeholders():
    sk = [({"rva": "0x00001000", "size": "16", "by": "Z"},
           {"name": "?f@A@@", "source": "a.cpp", "status": "matched"}),
          ({"rva": "0x00001010", "size": "8", "by": "C"}, None),
          ({"rva": "0x00001020", "size": "16", "by": "Z"},
           {"name": "?g@A@@", "source": "b.cpp", "status": "matched"})]
    texts = {"a.cpp": "// cl: /O1\n#include \"x.h\"\nclass A { public: void f(); void g(); };\nvoid A::f() {}\n",
             "b.cpp": "// cl: /O1\n#include \"x.h\"\nclass A { public: void f(); void g(); };\nvoid A::g() {}\n"}
    out = tu_skeleton.compose("T.cpp", sk, ["a.cpp", "b.cpp"], texts, ["/O1"], "first")
    assert out.startswith("// cl: /O1\n")
    assert out.count('#include "x.h"') == 1 and out.count("class A") == 1
    assert out.index("void A::f()") < out.index("0x00001010") < out.index("void A::g()")
    assert "tu-skeleton: 0x00001010 8B (unledgered) -- unmatched, no code, never credited" in out


def test_repoint_moves_only_absorbed_donor_rows_and_keeps_terminators():
    raw = HEADER + row("a", 0x10, 4, "Code/x/A.cpp").replace("\n", "\r\n") + row("b", 0x20, 4, "Code/x/B.cpp")
    new, moved = tu_skeleton.repoint(raw, {"Code/x/A.cpp"}, "Code/x/T.cpp")
    assert moved == 1 and ",Code/x/T.cpp," in new and ",Code/x/B.cpp," in new
    assert new.count("\r\n") == 1 and len(new) == len(raw)


# ---------------------------------------------------------------- ownership
def git(repo, *args):
    subprocess.run(["git", *args], cwd=repo, check=True, capture_output=True)


@pytest.fixture
def repo(tmp_path, monkeypatch):
    git(tmp_path, "init", "-q")
    git(tmp_path, "config", "user.name", "t")
    git(tmp_path, "config", "user.email", "t@t")
    rev = tmp_path / "reverse"
    rev.mkdir()
    d = tmp_path / "Code/X"
    d.mkdir(parents=True)
    (d / "Foo.cpp").write_text("void Foo::f()\n{\n}\n")
    (d / "Shared.h").write_text("class Reg\n{\npublic:\n    int a;\n    float b;\n};\n")
    (rev / "functions.csv").write_text(HEADER + row("?f@Foo@@QAEXXZ", 0x1000, 16, "Code/X/Foo.cpp")
                                       + row("?g@Foo@@QAEXXZ", 0x1010, 16, "Code/X/FooG.cpp"))
    (rev / "tu_map.csv").write_text(
        "rva,size,kind,tu,confidence,by,evidence,source\n"
        "0x00001000,16,code,Code/X/Foo.cpp,approved,Z,,Code/X/Foo.cpp\n"
        "0x00001010,16,code,Code/X/Foo.cpp,approved,C,,Code/X/FooG.cpp\n"
        "0x00001020,16,code-unledgered,Code/X/Foo.cpp,approved,C,,\n")
    (rev / "canonical_classes.csv").write_text("class,header,notes\nReg,Code/X/Shared.h,test\n")
    (d / "FooG.cpp").write_text("void Foo::g()\n{\n}\n")
    git(tmp_path, "add", "-A")
    git(tmp_path, "commit", "-qm", "base")
    monkeypatch.setattr(tu_ownership, "ROOT", tmp_path)
    monkeypatch.setattr(tu_ownership, "LAYOUT", tu_map.Layout(tmp_path))
    monkeypatch.setattr(tu_ownership, "_FP", None)
    return tmp_path


def staged(repo):
    git(repo, "add", "-A")
    return {rule for rule, _ in tu_ownership.check("HEAD", None)}


def ledger_add(repo, text):
    p = repo / "reverse/functions.csv"
    p.write_text(p.read_text() + text)


def test_a1_second_row_for_owned_address_is_refused(repo):
    ledger_add(repo, row("?f2@Foo@@QAEXXZ", 0x1000, 16, "Code/X/Other.cpp"))
    assert "A1" in staged(repo)


def test_a2_move_to_wrong_file_is_refused_and_move_into_tu_passes(repo):
    p = repo / "reverse/functions.csv"
    p.write_text(p.read_text().replace(",Code/X/FooG.cpp,", ",Code/X/Elsewhere.cpp,"))
    assert staged(repo) == {"A2"}
    p.write_text(p.read_text().replace(",Code/X/Elsewhere.cpp,", ",Code/X/Foo.cpp,"))
    assert staged(repo) == set()


def test_a3_new_row_outside_approved_tu(repo):
    ledger_add(repo, row("?h@Foo@@QAEXXZ", 0x1020, 16, "Code/X/FooH.cpp"))
    assert staged(repo) == {"A3"}


def test_a3_new_row_in_its_tu_passes(repo):
    ledger_add(repo, row("?h@Foo@@QAEXXZ", 0x1020, 16, "Code/X/Foo.cpp"))
    assert staged(repo) == set()


def test_edit_in_place_passes(repo):
    p = repo / "reverse/functions.csv"
    p.write_text(p.read_text().replace("FooG.cpp,matched,", "FooG.cpp,matched,note"))
    assert staged(repo) == set()


def test_a4_second_body_is_refused_but_inline_helper_passes(repo):
    (repo / "Code/X/Bar.cpp").write_text("inline void Foo::f()\n{\n}\n")
    assert staged(repo) == set()
    (repo / "Code/X/Bar.cpp").write_text("void Foo::f()\n{\n}\n")
    assert staged(repo) == {"A4"}


def test_b1_private_copy_of_registered_class(repo):
    (repo / "Code/X/Baz.cpp").write_text("class Reg\n{\npublic:\n    int a;\n    float b;\n};\n")
    assert staged(repo) == {"B1"}
    (repo / "Code/X/Baz.cpp").write_text("// class-gate: allow Reg byte-proved view\n"
                                         "class Reg\n{\npublic:\n    int a;\n    float b;\n};\n")
    assert staged(repo) == set()


def test_b2_fingerprint_is_diagnostic_only(repo):
    (repo / "Code/X/Qux.cpp").write_text("class Rva00001234\n{\npublic:\n    int x;\n    float y;\n};\n")
    git(repo, "add", "-A")
    found = tu_ownership.check("HEAD", None)
    assert [r for r, _ in found] == ["B2"]
    assert tu_ownership.report(found, shadow=False) == 0
