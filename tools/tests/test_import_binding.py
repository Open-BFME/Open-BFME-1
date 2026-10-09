"""import_binding: classification, source rewriting, and fail-closed refusals."""
import csv
import json
import shutil
import struct
import sys
from pathlib import Path
from types import SimpleNamespace

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
    write_coff(tmp_path / "x.obj", "__imp__ceil")
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
    write_coff(tmp_path / "x.obj", "__imp__ceil")
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


OWNERSHIP = [(2, 0), (0, 4), (-1, SLOT_CEIL + ib.BASE)]


def write_coff(path, symbol, section=0, value=0, storage=ib.EXTERNAL, data_name=b".data"):
    """Real x86 COFF: _caller reads the named cell through one DIR32 site."""
    body = b"\xff\x15\0\0\0\0\xc3"
    raw, data, reloc = 100, 107, 111
    table = reloc + 10
    header = struct.pack("<HHIIIHH", 0x14C, 2, 0, table, 2, 0, 0)
    text_section = struct.pack("<8sIIIIIIHHI", b".text", 0, 0, len(body), raw, reloc, 0, 1, 0, 0x60000020)
    data_section = struct.pack("<8sIIIIIIHHI", data_name, 0, 0, 4, data, 0, 0, 0, 0, 0xC0000040)
    caller = struct.pack("<8sIhHBB", b"_caller", 0, 1, 0x20, ib.EXTERNAL, 0)
    cell = struct.pack("<8sIhHBB", struct.pack("<II", 0, 4), value, section, 0, storage, 0)
    name = symbol.encode("ascii") + b"\0"
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(header + text_section + data_section + body + b"\0" * 4
                     + struct.pack("<IIH", 2, 1, ib.DIR32) + caller + cell
                     + struct.pack("<I", 4 + len(name)) + name)
    return path


@pytest.fixture
def source_checkout(monkeypatch, tmp_path):
    """A small ledger with real source/object path metadata, no native tools."""
    monkeypatch.setattr(ib, "ROOT", tmp_path)
    monkeypatch.setattr(ib, "OUT", tmp_path / "build/import_binding")
    monkeypatch.setattr(build, "ROOT", tmp_path)
    monkeypatch.setattr(build, "BUILD_DIR", tmp_path / "build/match")
    ledger = tmp_path / "functions.csv"
    monkeypatch.setattr(build, "FUNCTIONS", ledger)
    monkeypatch.setattr(build, "_FUNCTION_ROWS_CACHE", {})

    def rows(*entries):
        with ledger.open("w", newline="", encoding="utf-8") as handle:
            writer = csv.DictWriter(handle, fieldnames=["name", "target_rva", "target_size", "status", "source", "notes"])
            writer.writeheader()
            writer.writerows(entries)

    rows()
    return tmp_path, rows


def matched_caller(source="game/x.cpp"):
    return {"name": "_caller", "target_rva": "0x00001000", "target_size": "7",
            "status": "matched", "source": source, "notes": ""}


@pytest.mark.parametrize("section,value", OWNERSHIP)
def test_object_facts_distinguishes_owned_external_cells(tmp_path, section, value):
    obj = write_coff(tmp_path / "x.obj", "__imp__ceil", section, value)
    assert ib.object_facts(obj) == (set(), {"_caller", "__imp__ceil"})


@pytest.mark.parametrize("section,value,storage", [(0, 0, ib.EXTERNAL), (-2, 0, ib.EXTERNAL),
                                                  (2, 0, ib.STATIC), (0, 4, ib.WEAK_EXTERNAL)])
def test_object_facts_preserves_storage_and_undefined_rules(tmp_path, section, value, storage):
    obj = write_coff(tmp_path / "x.obj", "__imp__ceil", section, value, storage)
    undefined = {"__imp__ceil"} if (section, value, storage) == (0, 0, ib.EXTERNAL) else set()
    assert ib.object_facts(obj) == (undefined, {"_caller"})


@pytest.mark.parametrize("section,value", OWNERSHIP)
@pytest.mark.parametrize("symbol", ["__imp__ceil", "__imp__acos_old"])
def test_source_owned_canonical_and_oldnames_cells_are_refused(source_checkout, section, value, symbol):
    root, _ = source_checkout
    obj = write_coff(root / "x.obj", symbol, section, value, data_name=b".idata$5")
    with pytest.raises(ib.Refused, match="source object defines a retail import-address cell"):
        ib.plan("game/x.cpp", obj, FakeImports(), {})
    (problem,) = ib.verify_object("game/x.cpp", obj, FakeImports(), {}, [])
    assert symbol in problem and "must remain undefined" in problem


@pytest.mark.parametrize("symbol", ["__imp__ceil", "__imp__acos_old"])
def test_real_undefined_import_remains_positive(source_checkout, symbol):
    root, _ = source_checkout
    obj = write_coff(root / "x.obj", symbol)
    assert ib.object_facts(obj)[0] == {symbol}
    assert ib.plan("game/x.cpp", obj, FakeImports(), {}) == []
    assert ib.verify_object("game/x.cpp", obj, FakeImports(), {}, []) == []


@pytest.mark.parametrize("section,value", OWNERSHIP)
def test_owned_alias_is_rejected_by_actual_matched_dir32_site(source_checkout, monkeypatch, section, value):
    root, rows = source_checkout
    rows(matched_caller())
    symbol = "__imp__CIacosIat"
    obj = write_coff(root / "x.obj", symbol, section, value)
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size: b"\xff\x15" + struct.pack("<I", ib.BASE + SLOT_ACOS) + b"\xc3")
    assert ib.site_witnesses(obj, ib.tu_rows("game/x.cpp")) == {symbol: {SLOT_ACOS}}
    with pytest.raises(ib.Refused, match="source object defines a retail import-address cell"):
        ib.plan("game/x.cpp", obj, FakeImports(), {})
    assert "0xf59230" in ib.verify_object("game/x.cpp", obj, FakeImports(), {}, [])[0]


def test_owned_alias_requires_native_cell_evidence(source_checkout):
    root, _ = source_checkout
    symbol = "__imp__CIacosIat"
    obj = write_coff(root / "x.obj", symbol, 0, 4)
    imports = FakeImports()
    found = {symbol: {("dir32", SLOT_ACOS), ("pin", SLOT_CEIL)}}
    assert ib.verify_object("game/x.cpp", obj, imports, found, [])
    # Neither an unsupported spelling, a pin nor a token proves owned IAT data.
    for name, evidence in [(symbol, {}), (symbol, {symbol: {("pin", SLOT_ACOS)}}),
                           ("__imp__Rva01358F30Sleep@4", {}),
                           (symbol, {symbol: {("dir32", 0xF37830)}})]:
        write_coff(obj, name, 0, 4)
        assert ib.plan("game/x.cpp", obj, imports, evidence) == []
        assert ib.verify_object("game/x.cpp", obj, imports, evidence, []) == []
    # Conflicting native site witnesses still prove a source-owned IAT cell.
    assert ib.owned_iat_cells({symbol}, imports, {}, {symbol: {SLOT_ACOS, SLOT_CEIL}}) == {symbol: [SLOT_ACOS, SLOT_CEIL]}


def test_owned_non_iat_function_pointer_stays_out_of_scope(source_checkout, monkeypatch):
    root, rows = source_checkout
    rows(matched_caller())
    symbol = "__imp__LocalCallback"
    obj = write_coff(root / "x.obj", symbol, 2)
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size: b"\xff\x15" + struct.pack("<I", ib.BASE + 0xF37830) + b"\xc3")
    assert ib.site_witnesses(obj, ib.tu_rows("game/x.cpp")) == {symbol: {0xF37830}}
    assert ib.plan("game/x.cpp", obj, FakeImports(), {}) == []
    assert ib.verify_object("game/x.cpp", obj, FakeImports(), {}, []) == []


@pytest.mark.parametrize("symbol", ["__imp__ceil", "__imp__CIacosIat"])
def test_static_source_cell_needs_actual_object_dir32_evidence(source_checkout, monkeypatch, symbol):
    root, rows = source_checkout
    rows(matched_caller())
    obj = write_coff(build.obj_path(root / "game/x.cpp"), symbol, 2, 0, ib.STATIC)
    imports = FakeImports()
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size: b"\xff\x15" + struct.pack("<I", ib.BASE + SLOT_CEIL) + b"\xc3")
    assert ib.object_facts(obj) == (set(), {"_caller"})  # external-provider API stays unchanged
    assert ib.static_iat_symbols(obj) == {symbol}
    assert ib.site_witnesses(obj, ib.tu_rows("game/x.cpp")) == {symbol: {SLOT_CEIL}}
    with pytest.raises(ib.Refused, match="source object defines a retail import-address cell"):
        ib.plan("game/x.cpp", obj, imports, {})
    assert ib.verify_object("game/x.cpp", obj, imports, {}, [])
    assert ib.measure([obj], imports, {})["objects"][obj.name]["imports"] == {symbol: "owned-iat"}
    # A global name table cannot identify this TU's local STATIC symbol.
    rows()
    for evidence in ({}, {symbol: {("pin", SLOT_CEIL)}}, {symbol: {("dir32", SLOT_CEIL)}}):
        assert ib.plan("game/x.cpp", obj, imports, evidence) == []
        assert ib.verify_object("game/x.cpp", obj, imports, evidence, []) == []


@pytest.mark.parametrize("symbol", ["__imp__ceil", "__imp__Rva01358F30Sleep@4"])
def test_static_non_iat_or_unwitnessed_token_stays_out_of_scope(source_checkout, monkeypatch, symbol):
    root, rows = source_checkout
    rows(matched_caller())
    obj = write_coff(build.obj_path(root / "game/x.cpp"), symbol, 2, 0, ib.STATIC)
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size: b"\xff\x15" + struct.pack("<I", ib.BASE + 0xF37830) + b"\xc3")
    assert ib.site_witnesses(obj, ib.tu_rows("game/x.cpp")) == {symbol: {0xF37830}}
    # Another TU's same-name native DIR32 fact is not evidence for this local.
    found = {symbol: {("dir32", SLOT_CEIL)}}
    assert ib.plan("game/x.cpp", obj, FakeImports(), found) == []
    assert ib.verify_object("game/x.cpp", obj, FakeImports(), found, []) == []
    assert ib.measure([obj], FakeImports(), found)["objects"] == {}
    rows()
    assert ib.verify_object("game/x.cpp", obj, FakeImports(), {}, []) == []


@pytest.mark.parametrize("section,value", OWNERSHIP)
def test_owned_plain_native_thunk_is_still_rejected(source_checkout, section, value):
    root, _ = source_checkout
    obj = write_coff(root / "x.obj", "_ceil", section, value)
    assert ib.verify_object("game/x.cpp", obj, FakeImports(), {}, []) == ["_ceil: still defines an import library's call stub"]


@pytest.mark.parametrize("section,value", OWNERSHIP)
def test_measure_reports_only_exact_known_source_owned_cells(source_checkout, monkeypatch, section, value):
    root, rows = source_checkout
    rows(matched_caller())
    source = write_coff(build.obj_path(root / "game/x.cpp"), "__imp__ceil", section, value)
    member = write_coff(root / "archive_members" / source.name, "__imp__ceil", section, value, data_name=b".idata$5")
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size: b"\xff\x15" + struct.pack("<I", ib.BASE + SLOT_CEIL) + b"\xc3")
    imports = FakeImports()
    result = ib.measure([member, source], imports, {})
    assert result["objects"][source.name]["imports"] == {"__imp__ceil": "owned-iat"}
    assert result["references"] == {"owned-iat": 1}
    assert ib.measure([member], imports, {})["objects"] == {}
    # No owned verdict may poison classification of a real undefined import.
    undefined = write_coff(root / "undefined.obj", "__imp__ceil")
    result = ib.measure([source, undefined], imports, {})
    assert result["references"] == {"owned-iat": 1, "correct": 1}


@pytest.mark.parametrize("section,value", OWNERSHIP)
def test_check_pure_integration_refuses_owned_cell_despite_link_success(source_checkout, monkeypatch, section, value):
    """Actual COFF/ledger parsing; external byte gate and native link are fixtures."""
    root, _ = source_checkout
    obj = write_coff(build.obj_path(root / "game/x.cpp"), "__imp__ceil", section, value)
    work = ib.work_dir("game/x.cpp")
    work.mkdir(parents=True)
    monkeypatch.setattr(ib, "load_context", lambda: (FakeImports(), {}))
    monkeypatch.setattr(ib.subprocess, "run", lambda *a, **k: SimpleNamespace(returncode=0, stdout="byte fixture\n"))
    calls = []

    def linked(actual_obj, imports, actual_work, label):
        calls.append(actual_obj)
        return True, "pure link fixture", [], []

    monkeypatch.setattr(ib, "strict_link", linked)
    assert ib.cmd_check(SimpleNamespace(source="game/x.cpp")) == 1
    receipt = json.loads((work / "receipt.json").read_text())
    assert calls == [obj]
    assert receipt["byte_gate"]["exit"] == 0 and receipt["strict_link"]["ok"]
    assert receipt["strict_link"]["imports"] == [] and receipt["pass"] is False
    assert "source object defines a retail import-address cell" in receipt["failures"][0]
    assert ib.link_verdict(True, [], FakeImports()) == []  # legal for a TU with no imports


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


def test_link_verdict_accepts_a_name_retail_imports_from_another_dll():
    """WSock32.Lib and WS2_32.Lib both define _recvfrom@24; retail imports it
    from WS2_32. The TU cannot pick the DLL, so that is no TU failure (re_attempts 58765)."""
    imports = FakeImports()
    imports.slots = {**imports.slots, 0x958CBC: ("ws2_32.dll", "recvfrom"),
                     0x959718: ("wsock32.dll", "htonl")}
    linked = [("wsock32.dll", "recvfrom"), ("wsock32.dll", "htonl")]
    assert ib.link_verdict(True, linked, imports) == []
    # A name retail imports from no DLL is still refused.
    assert ib.link_verdict(True, [("wsock32.dll", "WSAAsyncSelect")], imports) == [
        "links wsock32.dll!WSAAsyncSelect, which retail does not import"]
