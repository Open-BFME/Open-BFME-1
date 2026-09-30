"""import_binding: classification, source rewriting, and fail-closed refusals."""
import shutil
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build  # noqa: E402
import import_binding as ib  # noqa: E402

SLOT_ACOS, SLOT_CEIL, SLOT_SLEEP = 0xF59230, 0xF59394, 0xF58F30


class FakeImports(ib.Imports):
    """msvcrt.lib/kernel32.lib in miniature, without reading an archive."""

    def __init__(self):
        self.slots = {SLOT_ACOS: ("msvcr71.dll", "_CIacos"), SLOT_CEIL: ("msvcr71.dll", "ceil"),
                      SLOT_SLEEP: ("kernel32.dll", "Sleep")}
        self.by_import = {v: k for k, v in self.slots.items()}
        self.imp = {"__imp___CIacos": self.slots[SLOT_ACOS], "__imp__ceil": self.slots[SLOT_CEIL],
                    "__imp__Sleep@4": self.slots[SLOT_SLEEP]}
        self.canonical = {v: {k} for k, v in self.imp.items()}
        self.thunk = {k[len("__imp_"):]: v for k, v in self.imp.items()}
        self.foreign = {"__imp__htons@4": ("ws2_32.dll", "htons")}
        self.oldnames = {"__imp__acos_old": "__imp___CIacos"}
        self.imp["__imp__acos_old"] = self.slots[SLOT_ACOS]


def test_real_import_is_correct():
    imports = FakeImports()
    assert ib.classify("__imp__ceil", imports, {})[0] == "correct"
    assert ib.classify("__imp__ceil", imports, {}, {"__imp__ceil": {SLOT_CEIL}})[0] == "correct"
    assert ib.classify("__imp__acos_old", imports, {})[0] == "correct"  # oldnames.lib resolves it


def test_invented_import_is_refused_not_aliased():
    """No library defines it and nothing witnesses a slot: never guess a similar name."""
    imports = FakeImports()
    kind, _, slot = ib.classify("__imp__CIacosIat", imports, {})
    assert (kind, slot) == ("invented", None)


def test_alias_needs_a_witness_and_binds_to_its_slot():
    imports = FakeImports()
    kind, detail, slot = ib.classify("__imp__CIacosIat", imports, {}, {"__imp__CIacosIat": {SLOT_ACOS}})
    assert (kind, detail, slot) == ("alias:wrong-name", "msvcr71.dll!_CIacos", SLOT_ACOS)
    assert imports.spelling(slot) == "__imp___CIacos"
    # a pin written as a VA is the same slot; an Rva token in the name too
    assert ib.classify("__imp__bfmeMathVE", imports, {"__imp__bfmeMathVE": {("pin", SLOT_CEIL + ib.BASE)}})[2] == SLOT_CEIL
    assert ib.classify("__imp__Rva01358F30Sleep@4", imports, {})[2] == SLOT_SLEEP


def test_disagreeing_or_non_iat_witnesses_are_refused():
    imports = FakeImports()
    both = {"__imp__x": {("dir32", SLOT_CEIL), ("pin", SLOT_ACOS)}}
    assert ib.classify("__imp__x", imports, both)[0] == "conflict"
    assert ib.classify("__imp__x", imports, {"__imp__x": {("pin", 0xF37830)}})[0] == "not-iat"
    # a real import read through another slot calls the wrong function
    assert ib.classify("__imp__ceil", imports, {}, {"__imp__ceil": {SLOT_ACOS}})[0] == "wrong-slot"


def test_wrong_dll_alias():
    imports = FakeImports()
    imports.slots[0xF59600] = ("wsock32.dll", "ntohs")
    imports.by_import[("wsock32.dll", "ntohs")] = 0xF59600
    assert ib.classify("__imp__htons@4", imports, {}, {"__imp__htons@4": {0xF59600}})[0] == "alias:wrong-dll"


def test_identifier_refuses_scoped_names():
    assert ib.identifier("?bfmeMathVE@@YANN@Z") == ("bfmeMathVE", "C++")
    assert ib.identifier("_Sleep@4") == ("Sleep", "C")
    assert ib.identifier("__CIacos") == ("_CIacos", "C")
    with pytest.raises(ib.Refused):
        ib.identifier("?deallocate@__new_alloc@_STL@@SAXPAXI@Z")
    with pytest.raises(ib.Refused):
        ib.identifier("@fast@8")


FORWARDER = """// IAT slot: _CIacos 0x01359230; CIacosIat is the alias.
extern "C" __declspec(dllimport) void __cdecl CIacosIat(void);
__declspec(dllimport) double bfmeMathVE(double x);

// _CIacos forwards on the x87 stack.
extern "C" void __cdecl _CIacos(void) { CIacosIat(); }
double up(double v) { const char *s = "bfmeMathVE"; return bfmeMathVE(v); }
"""

STEPS = [("own", "__CIacos", {"old": "_CIacos", "new": "Rva009F7256_CIacos"}),
         ("bind", "__imp__CIacosIat", {"old": "CIacosIat", "new": "_CIacos", "linkage": "C"}),
         ("bind", "__imp_?bfmeMathVE@@YANN@Z", {"old": "bfmeMathVE", "new": "ceil", "linkage": "C"})]


def test_rewrite_binds_owns_and_leaves_comments_and_literals():
    out = ib.rewrite(FORWARDER, STEPS)
    assert 'extern "C" __declspec(dllimport) void __cdecl _CIacos(void);' in out
    assert 'extern "C" __declspec(dllimport) double ceil(double x);' in out
    assert "void __cdecl Rva009F7256_CIacos(void) { _CIacos(); }" in out
    assert 'extern "C" void __cdecl Rva009F7256' not in out  # owned body is C++, like its Rva siblings
    assert "// IAT slot: _CIacos 0x01359230; CIacosIat is the alias." in out
    assert "// _CIacos forwards on the x87 stack." in out
    assert '"bfmeMathVE"' in out and "return ceil(v);" in out


def test_rewrite_can_drop_declarations_for_a_header():
    out = ib.rewrite(FORWARDER, STEPS, keep_declarations=False)
    assert "dllimport" not in out and "return ceil(v);" in out


def test_rewrite_refuses_a_name_the_source_does_not_spell():
    with pytest.raises(ib.Refused):
        ib.rewrite("int f() { return g(); }\n", [("bind", "__imp__x", {"old": "x", "new": "y", "linkage": "C"})])


def test_plan_refuses_any_unrepairable_import(monkeypatch, tmp_path):
    """One invented import in the TU refuses the whole TU: nothing is rewritten."""
    imports = FakeImports()
    monkeypatch.setattr(ib, "tu_rows", lambda source: [])
    monkeypatch.setattr(ib, "object_facts", lambda obj: ({"__imp__CIacosIat", "__imp__Invented"}, set()))
    monkeypatch.setattr(ib, "site_witnesses", lambda obj, rows: {"__imp__CIacosIat": {SLOT_ACOS}})
    with pytest.raises(ib.Refused, match="__imp__Invented: invented"):
        ib.plan("game/x.cpp", tmp_path / "x.obj", imports, {})
    monkeypatch.setattr(ib, "object_facts", lambda obj: ({"__imp__CIacosIat"}, set()))
    (step,) = ib.plan("game/x.cpp", tmp_path / "x.obj", imports, {})
    assert step[0] == "bind" and step[2]["to"] == "__imp___CIacos" and step[2]["new"] == "_CIacos"


def test_plan_refuses_a_duplicate_thunk_whose_row_is_not_the_stub(monkeypatch, tmp_path):
    imports = FakeImports()
    row = {"name": "__CIacos", "target_rva": "0x009F7256", "target_size": "6", "notes": "", "source": "game/x.cpp"}
    monkeypatch.setattr(ib, "tu_rows", lambda source: [row])
    monkeypatch.setattr(ib, "object_facts", lambda obj: (set(), {"__CIacos"}))
    monkeypatch.setattr(ib, "site_witnesses", lambda obj, rows: {})
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size: b"\xff\x25" + (SLOT_ACOS + ib.BASE).to_bytes(4, "little"))
    (step,) = ib.plan("game/x.cpp", tmp_path / "x.obj", imports, {})
    assert step[0] == "own" and step[2]["new"] == "Rva009F7256_CIacos"
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size: b"\xff\x25" + (SLOT_CEIL + ib.BASE).to_bytes(4, "little"))
    with pytest.raises(ib.Refused, match="not retail's"):
        ib.plan("game/x.cpp", tmp_path / "x.obj", imports, {})


TOOLCHAIN = (build.DEFAULT_VC71_ROOT / "Vc7" / "bin" / "link.exe").exists() and sys.platform == "win32"


@pytest.mark.skipif(not TOOLCHAIN, reason="needs MSVC 7.1 on Windows")
def test_strict_link_refuses_an_invented_import_and_accepts_the_real_one():
    """The real libraries decide: an invented __imp_ name fails LNK2019, never a stub."""
    tmp_path = ib.OUT / "test_strict_link"  # cl.exe sources must sit under the checkout
    tmp_path.mkdir(parents=True, exist_ok=True)
    imports = ib.Imports(ib.retail_slots(), ib.libraries())
    for label, decl, ok in (("invented", "CIacosIat", False), ("real", "_CIacos", True)):
        src = tmp_path / f"{label}.cpp"
        src.write_text(f'extern "C" __declspec(dllimport) void __cdecl {decl}(void);\n'
                       f"void __cdecl Rva009F7256_CIacos(void) {{ {decl}(); }}\n", encoding="ascii")
        obj = tmp_path / f"{label}.obj"
        compiled, text, _ = build.try_compile_source(src, obj)
        assert compiled, text
        linked, output, found, _ = ib.strict_link(obj, imports, tmp_path / label, label)
        assert linked is ok, output
        assert ib.link_verdict(linked, found, imports) == ([] if ok else ["strict link failed"])
    shutil.rmtree(tmp_path, ignore_errors=True)
