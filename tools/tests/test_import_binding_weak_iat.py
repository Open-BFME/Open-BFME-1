"""Pure weak-IAT regressions; fixture bytes never invoke a compiler or linker.

COFF auxiliaries, relocations, import archives, PE imports and MAP records are
parsed normally. Only the external byte gate and native link are substituted
in the command integration tests. Fixture selection is not a native result.
"""
import hashlib
import json
import struct
from types import SimpleNamespace

import pytest

from test_import_binding import (
    FakeImports, SLOT_ACOS, SLOT_CEIL, build, ib, matched_caller,
    source_checkout, write_coff,
)


CANONICAL = "__imp__ceil"
OLDNAME = "__imp__acos_old"
ALIAS = "__imp__UnknownAlias"
NATIVE_IAT = ib.BASE + 0x3060
NATIVE_DATA = ib.BASE + 0x3100
NATIVE_THUNK = ib.BASE + 0x1010


def _coff_bytes(symbols, relocated=1):
    """Two genuine COFF sections; symbols include their raw auxiliary bytes."""
    body = b"\xff\x15\0\0\0\0\xc3"
    raw = 100
    data_at = raw + len(body)
    reloc_at = data_at + 4
    nreloc = int(relocated is not None)
    table_at = reloc_at + 10 * nreloc
    strings = bytearray(b"\0" * 4)
    records = bytearray()
    count = 0
    for symbol in symbols:
        encoded = symbol["name"].encode("ascii")
        if len(encoded) <= 8:
            name = encoded.ljust(8, b"\0")
        else:
            name = struct.pack("<II", 0, len(strings))
            strings += encoded + b"\0"
        aux = symbol.get("aux", [])
        records += struct.pack("<8sIhHBB", name, symbol.get("value", 0),
                               symbol.get("section", 0), symbol.get("type", 0),
                               symbol.get("storage", ib.EXTERNAL), len(aux))
        records += b"".join(aux)
        count += 1 + len(aux)
    struct.pack_into("<I", strings, 0, len(strings))
    header = struct.pack("<HHIIIHH", 0x14C, 2, 0, table_at, count, 0, 0)
    text = struct.pack("<8sIIIIIIHHI", b".text", 0, 0, len(body), raw,
                       reloc_at if nreloc else 0, 0, nreloc, 0, 0x60000020)
    data = struct.pack("<8sIIIIIIHHI", b".data", 0, 0, 4, data_at, 0, 0, 0, 0, 0xC0000040)
    relocation = struct.pack("<IIH", 2, relocated, ib.DIR32) if nreloc else b""
    return header + text + data + body + b"\0" * 4 + relocation + records + strings


def weak_coff_bytes(symbol=CANONICAL, *, search=3, tag=None, aux_count=1,
                    section=0, value=0, default_name="_LocalSlot",
                    default_storage=ib.EXTERNAL, default_section=2,
                    default_value=0, default_type=0, relocated=True):
    """Raw indices: caller=0, weak=1, weak aux=2, direct default=3."""
    if tag is None:
        tag = 2 + aux_count
    auxiliary = struct.pack("<II", tag, search) + bytes(10)
    default_aux = [struct.pack("<II", 0, 2) + bytes(10)] if default_storage == ib.WEAK_EXTERNAL else []
    symbols = [
        {"name": "_caller", "section": 1, "type": 0x20},
        {"name": symbol, "section": section, "value": value,
         "storage": ib.WEAK_EXTERNAL, "aux": [auxiliary] * aux_count},
        {"name": default_name, "section": default_section, "value": default_value,
         "storage": default_storage, "type": default_type, "aux": default_aux},
    ]
    return _coff_bytes(symbols, relocated=1 if relocated else None)


def write_weak_coff(path, symbol=CANONICAL, **kwargs):
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(weak_coff_bytes(symbol, **kwargs))
    return path


def witness(monkeypatch, slot=SLOT_CEIL):
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size:
                        b"\xff\x15" + struct.pack("<I", ib.BASE + slot) + b"\xc3")


def source_weak(source_checkout, monkeypatch, symbol=CANONICAL, slot=SLOT_CEIL, **kwargs):
    root, rows = source_checkout
    rows(matched_caller())
    witness(monkeypatch, slot)
    return write_weak_coff(build.obj_path(root / "game/x.cpp"), symbol, **kwargs)


@pytest.mark.parametrize("search", [1, 2, 3])
@pytest.mark.parametrize("storage,section,value", [
    (ib.EXTERNAL, 2, 0), (ib.EXTERNAL, 0, 4), (ib.EXTERNAL, -1, NATIVE_DATA),
])
def test_relocated_weak_iat_keeps_direct_data_default_metadata(tmp_path, search, storage, section, value):
    obj = write_weak_coff(tmp_path / "x.obj", search=search, default_storage=storage,
                          default_section=section, default_value=value)
    routes = ib.weak_import_routes(obj, FakeImports(), {})
    assert routes == {CANONICAL: {
        "index": 1, "tag": 3, "search": search,
        "default": {"name": "_LocalSlot", "storage": storage, "section": section, "value": value},
        "expected": ("msvcr71.dll", "ceil"), "slot": SLOT_CEIL, "expected_from": "library",
        "object_sha256": hashlib.sha256(obj.read_bytes()).hexdigest(),
    }}
    # Weak declarations remain separate from the external-provider API.
    undefined, defined = ib.object_facts(obj)
    assert undefined == set() and CANONICAL not in defined


def test_source_oldnames_weak_identity_comes_from_library_not_default(tmp_path):
    obj = write_weak_coff(tmp_path / "x.obj", OLDNAME,
                          default_name="__imp___CIacos", default_section=0)
    route = ib.weak_import_routes(obj, FakeImports(), {})[OLDNAME]
    assert route["expected"] == ("msvcr71.dll", "_CIacos")
    assert route["expected_from"] == "library" and route["slot"] == SLOT_ACOS
    assert ib.object_facts(obj)[0] == {"__imp___CIacos"}


def test_unknown_weak_alias_needs_actual_single_iat_site(source_checkout, monkeypatch):
    obj = source_weak(source_checkout, monkeypatch, ALIAS)
    sites = ib.site_witnesses(obj, ib.tu_rows("game/x.cpp"))
    assert sites == {ALIAS: {SLOT_CEIL}}
    route = ib.weak_import_routes(obj, FakeImports(), sites)[ALIAS]
    assert route["expected_from"] == "matched DIR32"
    assert (route["expected"], route["slot"]) == (("msvcr71.dll", "ceil"), SLOT_CEIL)


def test_unknown_weak_addend_witness_names_base_iat_slot(source_checkout, monkeypatch):
    obj = source_weak(source_checkout, monkeypatch, ALIAS)
    data = bytearray(obj.read_bytes())
    struct.pack_into("<I", data, 102, 4)  # .text raw offset100, DIR32 operand+2.
    obj.write_bytes(data)
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size:
                        b"\xff\x15" + struct.pack("<I", ib.BASE + SLOT_CEIL + 4) + b"\xc3")
    body, _ = build.read_object_symbol_bytes(obj, "_caller", 7)
    assert struct.unpack_from("<I", body, 2)[0] == 4
    sites = ib.site_witnesses(obj, ib.tu_rows("game/x.cpp"))
    assert sites == {ALIAS: {SLOT_CEIL}}
    route = ib.weak_import_routes(obj, FakeImports(), sites)[ALIAS]
    assert route["slot"] == SLOT_CEIL and route["expected_from"] == "matched DIR32"
    assert route["expected"] == ("msvcr71.dll", "ceil")


@pytest.mark.parametrize("sites", [{}, {ALIAS: {SLOT_ACOS, SLOT_CEIL}}, {ALIAS: {SLOT_CEIL, 0xF37830}}])
def test_unknown_weak_alias_cannot_borrow_default_identity(tmp_path, sites):
    obj = write_weak_coff(tmp_path / "x.obj", ALIAS, default_name=CANONICAL, default_section=0)
    with pytest.raises(ib.Refused):
        ib.weak_import_routes(obj, FakeImports(), sites)


def test_unknown_weak_alias_cannot_borrow_pin_or_address_token(source_checkout, monkeypatch):
    root, _ = source_checkout
    symbol = "__imp__Rva01359394LocalSlot"
    obj = write_weak_coff(root / "x.obj", symbol)
    found = {symbol: {("pin", SLOT_CEIL), ("dir32", SLOT_CEIL)}}
    with pytest.raises(ib.Refused):
        ib.plan("game/x.cpp", obj, FakeImports(), found)
    with pytest.raises(ib.Refused):
        ib.verify_object("game/x.cpp", obj, FakeImports(), found, [])


def test_unknown_weak_non_iat_pointer_is_out_of_scope(source_checkout, monkeypatch):
    obj = source_weak(source_checkout, monkeypatch, ALIAS, slot=0xF37830)
    sites = ib.site_witnesses(obj, ib.tu_rows("game/x.cpp"))
    assert sites == {ALIAS: {0xF37830}}
    assert ib.weak_import_routes(obj, FakeImports(), sites) == {}
    assert ib.plan("game/x.cpp", obj, FakeImports(), {}) == []
    assert ib.verify_object("game/x.cpp", obj, FakeImports(), {}, []) == []


@pytest.mark.parametrize("slot", [SLOT_ACOS, 0xF37830])
def test_canonical_weak_conflicting_actual_site_is_refused(source_checkout, monkeypatch, slot):
    obj = source_weak(source_checkout, monkeypatch, slot=slot)
    with pytest.raises(ib.Refused):
        ib.weak_import_routes(obj, FakeImports(), ib.site_witnesses(obj, ib.tu_rows("game/x.cpp")))
    with pytest.raises(ib.Refused):
        ib.verify_object("game/x.cpp", obj, FakeImports(), {}, [])


@pytest.mark.parametrize("options", [
    {"aux_count": 0}, {"aux_count": 2}, {"tag": 1}, {"tag": 2}, {"tag": 99},
    {"search": 0}, {"search": 4}, {"search": 99},
    {"section": 2}, {"value": 4}, {"default_storage": ib.WEAK_EXTERNAL},
    {"default_storage": ib.STATIC, "default_section": 2},
    {"default_storage": ib.STATIC, "default_section": 0},
    {"default_section": -2}, {"default_section": 3}, {"default_storage": 6},
])
def test_malformed_or_unsupported_relocated_weak_route_is_refused(tmp_path, options):
    obj = write_weak_coff(tmp_path / "x.obj", **options)
    with pytest.raises(ib.Refused):
        ib.weak_import_routes(obj, FakeImports(), {})


@pytest.mark.parametrize("data", [b"\x4c\x01", weak_coff_bytes()[:129]])
def test_truncated_weak_coff_is_refused(tmp_path, data):
    obj = tmp_path / "x.obj"
    obj.write_bytes(data)
    with pytest.raises(ib.Refused):
        ib.weak_import_routes(obj, FakeImports(), {})


def test_weak_object_must_stay_equal_during_site_inspection(tmp_path):
    obj = write_weak_coff(tmp_path / "x.obj")

    def changed_sites():
        obj.write_bytes(weak_coff_bytes(search=2))
        return {}

    with pytest.raises(ib.Refused):
        ib.weak_import_routes(obj, FakeImports(), changed_sites)


@pytest.mark.parametrize("options", [{}, {"aux_count": 0}, {"search": 99}, {"tag": 2}])
def test_unrelocated_weak_declarations_do_not_require_selection(source_checkout, options):
    root, _ = source_checkout
    obj = write_weak_coff(root / "x.obj", relocated=False, **options)
    assert ib.weak_import_routes(obj, FakeImports(), {}) == {}
    assert ib.plan("game/x.cpp", obj, FakeImports(), {}) == []
    assert ib.verify_object("game/x.cpp", obj, FakeImports(), {}, []) == []


def test_relocated_non_import_weak_symbol_stays_out_of_iat_scope(tmp_path):
    obj = write_weak_coff(tmp_path / "x.obj", "_WeakCallback")

    def unexpected_sites():
        raise AssertionError("non-import weak references do not need retail IAT sites")

    assert ib.weak_import_routes(obj, FakeImports(), unexpected_sites) == {}


@pytest.mark.parametrize("symbol,slot", [(CANONICAL, SLOT_CEIL), (OLDNAME, SLOT_ACOS), (ALIAS, SLOT_CEIL)])
def test_plan_and_default_verify_refuse_unproved_weak_import(source_checkout, monkeypatch, symbol, slot):
    obj = source_weak(source_checkout, monkeypatch, symbol, slot)
    with pytest.raises(ib.Refused):
        ib.plan("game/x.cpp", obj, FakeImports(), {})
    problems = ib.verify_object("game/x.cpp", obj, FakeImports(), {}, [])
    assert problems and any(symbol in problem for problem in problems)
    assert not any("source object defines a retail import-address cell" in problem for problem in problems)


def test_measure_weak_route_only_for_exact_known_source_object(source_checkout, monkeypatch):
    root, _ = source_checkout
    obj = source_weak(source_checkout, monkeypatch, OLDNAME, SLOT_ACOS,
                      default_name="__imp___CIacos", default_section=0)
    member = write_weak_coff(root / "archive_members" / obj.name, OLDNAME,
                             default_name="__imp___CIacos", default_section=0)
    imports = FakeImports()
    result = ib.measure([obj], imports, {})
    assert result["objects"][obj.name]["imports"][OLDNAME] == "unproved-weak-import"
    assert result["references"]["unproved-weak-import"] == 1
    assert result["distinct"]["unproved-weak-import"] == 1
    archived = ib.measure([member], imports, {})
    assert "unproved-weak-import" not in archived["references"]
    assert archived["objects"][member.name]["imports"] == {"__imp___CIacos": "correct"}


def test_measure_unknown_non_iat_weak_route_stays_out_of_scope(source_checkout, monkeypatch):
    obj = source_weak(source_checkout, monkeypatch, ALIAS, slot=0xF37830)
    assert ib.measure([obj], FakeImports(), {})["objects"] == {}


def _archive_bytes(members):
    archive = bytearray(b"!<arch>\n")
    for index, body in enumerate(members):
        header = (f"member{index}/".encode().ljust(16) + b"0".ljust(12)
                  + b"0".ljust(6) + b"0".ljust(6) + b"0".ljust(8))
        archive += header + str(len(body)).encode().ljust(10) + b"`\n" + body
        if len(body) & 1:
            archive += b"\n"
    return bytes(archive)


def _short_import(symbol, dll, name_type=2):
    names = symbol.encode() + b"\0" + dll.encode() + b"\0"
    return struct.pack("<HHHHIIHH", 0, 0xFFFF, 0, 0x14C, 0, len(names), 0, name_type << 2) + names


def pe_bytes(name="ceil", dll="MSVCR71.dll", *, has_import=True, ordinal=False):
    """A PE32 with a real named IAT, zero data, and a callable FF25 thunk."""
    data = bytearray(0x800)
    data[:2] = b"MZ"
    struct.pack_into("<I", data, 0x3C, 0x80)
    data[0x80:0x84] = b"PE\0\0"
    struct.pack_into("<HHIIIHH", data, 0x84, 0x14C, 2, 0, 0, 0, 0xE0, 0x210F)
    optional = 0x98
    struct.pack_into("<H", data, optional, 0x10B)
    struct.pack_into("<I", data, optional + 28, ib.BASE)
    struct.pack_into("<II", data, optional + 32, 0x1000, 0x200)
    struct.pack_into("<II", data, optional + 56, 0x4000, 0x200)
    struct.pack_into("<I", data, optional + 92, 16)
    if has_import:
        struct.pack_into("<II", data, optional + 104, 0x3000, 40)
        struct.pack_into("<II", data, optional + 192, 0x3060, 8)
    sections = optional + 0xE0
    struct.pack_into("<8sIIIIIIHHI", data, sections, b".text", 0x200, 0x1000, 0x200, 0x200,
                     0, 0, 0, 0, 0x60000020)
    struct.pack_into("<8sIIIIIIHHI", data, sections + 40, b".idata", 0x200, 0x3000, 0x200, 0x400,
                     0, 0, 0, 0, 0xC0000040)
    struct.pack_into("<2sI", data, 0x210, b"\xff\x25", NATIVE_IAT)
    if has_import:
        struct.pack_into("<IIIII", data, 0x400, 0x3040, 0, 0, 0x3080, 0x3060)
        entry = 0x80000001 if ordinal else 0x30A0
        struct.pack_into("<II", data, 0x440, entry, 0)
        struct.pack_into("<II", data, 0x460, entry, 0)
        dll_bytes = dll.encode() + b"\0"
        data[0x480:0x480 + len(dll_bytes)] = dll_bytes
        name_bytes = b"\0\0" + name.encode() + b"\0"
        data[0x4A0:0x4A0 + len(name_bytes)] = name_bytes
    return bytes(data)


def map_line(symbol=CANONICAL, address=NATIVE_IAT, owner="fixture.obj"):
    return f" 0002:00000060 {symbol} {address:08X} {owner}\n"


@pytest.fixture
def selection_context(source_checkout, monkeypatch):
    root, rows = source_checkout
    source = root / "game/x.cpp"
    source.parent.mkdir(parents=True)
    source.write_text("// pure source fixture\n", encoding="ascii")
    retail = root / "retail.exe"
    retail.write_bytes(pe_bytes())
    monkeypatch.setattr(build, "EXE", retail)
    native_lib = root / "native.lib"
    native_lib.write_bytes(_archive_bytes([
        _short_import("_ceil", "MSVCR71.dll"),
        _short_import("__CIacos", "MSVCR71.dll"),
    ]))
    aliases = root / "oldnames.lib"
    aliases.write_bytes(_archive_bytes([
        weak_coff_bytes(OLDNAME, default_name="__imp___CIacos", default_section=0, relocated=False),
    ]))
    libs = [native_lib, aliases]
    monkeypatch.setattr(ib, "libraries", lambda: libs)
    rows(matched_caller())
    witness(monkeypatch)
    obj = write_weak_coff(build.obj_path(source))
    work = ib.work_dir("game/x.cpp")
    work.mkdir(parents=True)
    (work / "after.dll").write_bytes(pe_bytes())
    (work / "after.map").write_text(map_line(), encoding="ascii")
    return SimpleNamespace(root=root, source=source, obj=obj, work=work, libs=libs, imports=FakeImports())


def selected_proof(context):
    sites = ib.site_witnesses(context.obj, ib.tu_rows("game/x.cpp"))
    routes = ib.weak_import_routes(context.obj, context.imports, sites)
    libs, inputs = ib.weak_selection_inputs("game/x.cpp", context.obj)
    return ib.weak_selected_proof(context.obj, context.imports, routes, context.work, libs, inputs)


def test_selection_inputs_bind_object_source_baseline_and_libraries(selection_context):
    context = selection_context
    libs, inputs = ib.weak_selection_inputs("game/x.cpp", context.obj)
    assert libs == context.libs
    paths = [context.obj, context.source, build.EXE, build.FUNCTIONS, *libs]
    assert inputs == {str(path): hashlib.sha256(path.read_bytes()).hexdigest() for path in paths}


@pytest.mark.parametrize("search", [1, 2, 3])
def test_selected_actual_native_iat_proves_weak_primary_with_data_default(selection_context, search):
    context = selection_context
    write_weak_coff(context.obj, search=search)
    proof = selected_proof(context)
    assert proof["input_hash_equality"] is True
    (binding,) = proof["bindings"]
    assert binding["proved"] is True
    assert binding["symbol"] == CANONICAL and binding["route"] == "actual IAT slot"
    assert binding["selected_va"] == binding["slot_va"] == f"0x{NATIVE_IAT:08X}"
    assert binding["actual"] == [["msvcr71.dll", "ceil"]]
    assert ib.verify_object("game/x.cpp", context.obj, context.imports, {}, [], weak_proof=proof) == []


def test_selected_source_oldnames_weak_alias_is_supported(selection_context, monkeypatch):
    context = selection_context
    witness(monkeypatch, SLOT_ACOS)
    write_weak_coff(context.obj, OLDNAME, default_name="__imp___CIacos", default_section=0)
    (context.work / "after.dll").write_bytes(pe_bytes(name="_CIacos"))
    (context.work / "after.map").write_text(map_line(OLDNAME), encoding="ascii")
    proof = selected_proof(context)
    assert proof["bindings"][0]["proved"] is True
    assert proof["bindings"][0]["expected"] == ["msvcr71.dll", "_CIacos"]
    assert ib.verify_object("game/x.cpp", context.obj, context.imports, {}, [], weak_proof=proof) == []


def test_selected_unknown_alias_uses_actual_matched_iat_identity(selection_context):
    context = selection_context
    write_weak_coff(context.obj, ALIAS)
    (context.work / "after.map").write_text(map_line(ALIAS), encoding="ascii")
    proof = selected_proof(context)
    assert proof["bindings"][0]["proved"] is True
    assert proof["bindings"][0]["symbol"] == ALIAS
    assert ib.verify_object("game/x.cpp", context.obj, context.imports, {}, [], weak_proof=proof) == []


@pytest.mark.parametrize("symbol", [CANONICAL, ALIAS])
def test_selected_weak_identity_requires_fresh_real_library_evidence(selection_context, symbol):
    context = selection_context
    write_weak_coff(context.obj, symbol)
    (context.work / "after.map").write_text(map_line(symbol), encoding="ascii")
    context.libs[0].write_bytes(_archive_bytes([_short_import("__CIacos", "MSVCR71.dll")]))
    proof = selected_proof(context)
    assert proof["bindings"][0]["proved"] is False
    assert ib.verify_object("game/x.cpp", context.obj, context.imports, {}, [], weak_proof=proof)


def test_selected_weak_library_identity_ambiguity_is_not_filtered_away(selection_context):
    context = selection_context
    context.libs[0].write_bytes(_archive_bytes([
        _short_import("_ceil", "MSVCR71.dll"), _short_import("_ceil", "OTHER.dll"),
    ]))
    proof = selected_proof(context)
    assert proof["bindings"][0]["proved"] is False
    assert "ambiguous" in proof["bindings"][0]["reason"]


def test_selected_fresh_library_identity_cannot_replace_route_expected_identity(selection_context):
    context = selection_context
    context.imports.slots[0xF59600] = ("other.dll", "ceil")
    context.libs[0].write_bytes(_archive_bytes([_short_import("_ceil", "OTHER.dll")]))
    (context.work / "after.dll").write_bytes(pe_bytes(dll="OTHER.dll"))
    proof = selected_proof(context)
    assert proof["bindings"][0]["proved"] is False
    assert ib.verify_object("game/x.cpp", context.obj, context.imports, {}, [], weak_proof=proof)


@pytest.mark.parametrize("case", [
    "empty imports", "wrong name", "wrong DLL", "ordinal", "wrong slot",
    "thunk instead of IAT", "empty MAP", "default only MAP", "ambiguous MAP", "ambiguous owner",
])
def test_selected_weak_route_requires_exact_primary_map_and_native_iat(selection_context, case):
    context = selection_context
    image, selected = pe_bytes(), map_line()
    if case == "empty imports":
        image = pe_bytes(has_import=False)
    elif case == "wrong name":
        image = pe_bytes(name="floor")
    elif case == "wrong DLL":
        image = pe_bytes(dll="OTHER.dll")
    elif case == "ordinal":
        image = pe_bytes(ordinal=True)
    elif case == "wrong slot":
        selected = map_line(address=NATIVE_DATA)
    elif case == "thunk instead of IAT":
        selected = map_line(address=NATIVE_THUNK)
    elif case == "empty MAP":
        selected = ""
    elif case == "default only MAP":
        selected = map_line("_LocalSlot")
    elif case == "ambiguous MAP":
        selected += map_line(address=NATIVE_DATA)
    elif case == "ambiguous owner":
        selected += map_line(owner="other.obj")
    (context.work / "after.dll").write_bytes(image)
    (context.work / "after.map").write_text(selected, encoding="ascii")
    proof = selected_proof(context)
    (binding,) = proof["bindings"]
    assert binding["symbol"] == CANONICAL and binding["proved"] is False
    assert ib.verify_object("game/x.cpp", context.obj, context.imports, {}, [], weak_proof=proof)


@pytest.mark.parametrize("name", ["after.dll", "after.map"])
def test_selection_missing_current_link_artifact_is_refused(selection_context, name):
    (selection_context.work / name).unlink()
    with pytest.raises(ib.Refused):
        selected_proof(selection_context)


def test_selected_invalid_pe_is_refused(selection_context):
    (selection_context.work / "after.dll").write_bytes(b"MZ")
    with pytest.raises(ib.Refused):
        selected_proof(selection_context)


@pytest.mark.parametrize("which", ["object", "source", "baseline", "ledger", "library"])
def test_selected_weak_proof_refuses_changed_prelink_input(selection_context, which):
    context = selection_context
    routes = ib.weak_import_routes(context.obj, context.imports, {})
    libs, inputs = ib.weak_selection_inputs("game/x.cpp", context.obj)
    path = {"object": context.obj, "source": context.source, "ledger": build.FUNCTIONS,
            "baseline": build.EXE, "library": libs[0]}[which]
    path.write_bytes(path.read_bytes() + b"changed")
    with pytest.raises(ib.Refused):
        ib.weak_selected_proof(context.obj, context.imports, routes, context.work, libs, inputs)


@pytest.mark.parametrize("which", ["library", "ledger", "MAP", "PE"])
def test_selected_weak_proof_refuses_input_mutation_during_audit(selection_context, monkeypatch, which):
    import selected_import_audit as audit

    context = selection_context
    real_oracle = audit.oracle
    path = {"library": context.libs[0], "ledger": build.FUNCTIONS, "MAP": context.work / "after.map",
            "PE": context.work / "after.dll"}[which]

    def changed_oracle(slots, libs):
        result = real_oracle(slots, libs)
        path.write_bytes(path.read_bytes() + b"changed")
        return result

    monkeypatch.setattr(audit, "oracle", changed_oracle)
    with pytest.raises(ib.Refused):
        selected_proof(context)


@pytest.mark.parametrize("case", ["wrong expected", "wrong object hash", "empty bindings", "missing hash equality"])
def test_verify_cannot_reuse_incomplete_or_other_identity_proof(selection_context, case):
    context = selection_context
    proof = selected_proof(context)
    assert proof["bindings"][0]["proved"] is True
    if case == "wrong expected":
        proof["bindings"][0]["expected"] = ["msvcr71.dll", "_CIacos"]
    elif case == "wrong object hash":
        proof["input_sha256"][str(context.obj)] = "0" * 64
    elif case == "empty bindings":
        proof["bindings"] = []
    else:
        proof.pop("input_hash_equality")
    assert ib.verify_object("game/x.cpp", context.obj, context.imports, {}, [], weak_proof=proof)


@pytest.mark.parametrize("proof", [
    {"input_hash_equality": False, "bindings": []},
    {"input_hash_equality": True, "bindings": []},
    {"input_hash_equality": True, "bindings": [{"symbol": "__imp__other", "proved": True}]},
    {"input_hash_equality": True, "bindings": [{"symbol": CANONICAL, "proved": False}]},
])
def test_verify_weak_proof_requires_each_explicit_binding(source_checkout, monkeypatch, proof):
    obj = source_weak(source_checkout, monkeypatch)
    assert ib.verify_object("game/x.cpp", obj, FakeImports(), {}, [], weak_proof=proof)


@pytest.mark.parametrize("case,expected_exit", [
    ("alias data default", 1), ("library primary IAT", 0), ("empty imports", 1),
    ("wrong selected slot", 1), ("missing primary MAP", 1),
])
def test_check_pure_integration_audits_selected_weak_iat(selection_context, monkeypatch, case, expected_exit):
    """Real source/COFF/library/MAP/PE evidence, explicitly substituted link."""
    context = selection_context
    write_weak_coff(context.obj, search=2 if case == "library primary IAT" else 3)
    image, selected = pe_bytes(), map_line()
    if case == "alias data default":
        image, selected = pe_bytes(has_import=False), map_line(address=NATIVE_DATA)
    elif case == "empty imports":
        image = pe_bytes(has_import=False)
    elif case == "wrong selected slot":
        selected = map_line(address=NATIVE_DATA)
    elif case == "missing primary MAP":
        selected = map_line("_LocalSlot")
    monkeypatch.setattr(ib, "load_context", lambda: (context.imports, {}))
    monkeypatch.setattr(ib.subprocess, "run", lambda *args, **kwargs:
                        SimpleNamespace(returncode=0, stdout="pure byte gate fixture\n"))
    calls = []

    def linked(obj, imports, work, label):
        calls.append((obj, label))
        assert not (work / "after.dll").exists() and not (work / "after.map").exists()
        (work / f"{label}.dll").write_bytes(image)
        (work / f"{label}.map").write_text(selected, encoding="ascii")
        return True, "pure selected link fixture", [], []

    monkeypatch.setattr(ib, "strict_link", linked)
    assert ib.cmd_check(SimpleNamespace(source="game/x.cpp")) == expected_exit
    receipt = json.loads((context.work / "receipt.json").read_text())
    assert calls == [(context.obj, "after")]
    assert receipt["byte_gate"]["exit"] == 0 and receipt["strict_link"]["ok"]
    assert receipt["strict_link"]["imports"] == []
    assert receipt["pass"] is (expected_exit == 0)
    assert bool(receipt["failures"]) is (expected_exit != 0)
    assert ib.link_verdict(True, [], context.imports) == []


def test_check_link_success_cannot_reuse_stale_selected_outputs(selection_context, monkeypatch):
    context = selection_context
    sibling = context.root / "build/import_binding/other_source"
    sibling.mkdir(parents=True)
    (sibling / "after.dll").write_bytes(b"another source's DLL")
    (sibling / "after.map").write_bytes(b"another source's MAP")
    monkeypatch.setattr(ib, "load_context", lambda: (context.imports, {}))
    monkeypatch.setattr(ib.subprocess, "run", lambda *args, **kwargs:
                        SimpleNamespace(returncode=0, stdout="pure byte gate fixture\n"))
    monkeypatch.setattr(ib, "strict_link", lambda *args: (True, "pure link emits no files", [], []))
    assert ib.cmd_check(SimpleNamespace(source="game/x.cpp")) == 1
    receipt = json.loads((context.work / "receipt.json").read_text())
    assert receipt["strict_link"]["ok"] and receipt["pass"] is False
    assert not (context.work / "after.dll").exists() and not (context.work / "after.map").exists()
    assert (sibling / "after.dll").read_bytes() == b"another source's DLL"
    assert (sibling / "after.map").read_bytes() == b"another source's MAP"


def test_check_weak_object_cannot_change_between_inspection_and_snapshot(selection_context, monkeypatch):
    context = selection_context
    real_inputs = ib.weak_selection_inputs
    monkeypatch.setattr(ib, "load_context", lambda: (context.imports, {}))
    monkeypatch.setattr(ib.subprocess, "run", lambda *args, **kwargs:
                        SimpleNamespace(returncode=0, stdout="pure byte gate fixture\n"))

    def changed_inputs(source, obj):
        write_weak_coff(obj, search=2)
        return real_inputs(source, obj)

    def unexpected(*args):
        raise AssertionError("changed source object must be refused before linking")

    monkeypatch.setattr(ib, "weak_selection_inputs", changed_inputs)
    monkeypatch.setattr(ib, "strict_link", unexpected)
    assert ib.cmd_check(SimpleNamespace(source="game/x.cpp")) == 1
    assert json.loads((context.work / "receipt.json").read_text())["pass"] is False


@pytest.mark.parametrize("which", ["baseline", "ledger"])
def test_check_witness_inputs_cannot_change_during_route_derivation(selection_context, monkeypatch, which):
    """Derive real routes, then change a previously captured witness input."""
    context = selection_context
    real_routes = ib.weak_import_routes
    path = {"baseline": build.EXE, "ledger": build.FUNCTIONS}[which]
    inspected = []
    monkeypatch.setattr(ib, "load_context", lambda: (context.imports, {}))
    monkeypatch.setattr(ib.subprocess, "run", lambda *args, **kwargs:
                        SimpleNamespace(returncode=0, stdout="pure byte gate fixture\n"))

    def changed_routes(*args, **kwargs):
        routes = real_routes(*args, **kwargs)
        assert CANONICAL in routes
        if not inspected:
            path.write_bytes(path.read_bytes() + b"\n")
        inspected.append(routes)
        return routes

    def unexpected(*args):
        raise AssertionError("changed witness inputs must be refused before linking")

    monkeypatch.setattr(ib, "weak_import_routes", changed_routes)
    monkeypatch.setattr(ib, "strict_link", unexpected)
    assert ib.cmd_check(SimpleNamespace(source="game/x.cpp")) == 1
    receipt = json.loads((context.work / "receipt.json").read_text())
    assert inspected and receipt["pass"] is False
    assert receipt["strict_link"]["ok"] is False
    assert any("witness inputs changed during route inspection" in problem for problem in receipt["failures"])


@pytest.mark.parametrize("which", ["source", "ledger", "baseline"])
def test_check_final_receipt_rejects_input_change_after_verified_proof(selection_context, monkeypatch, which):
    """Verify real selected IAT evidence, then change input before receipt."""
    context = selection_context
    real_verify = ib.verify_object
    path = {"source": context.source, "ledger": build.FUNCTIONS, "baseline": build.EXE}[which]
    verified = []
    linked_calls = []
    monkeypatch.setattr(ib, "load_context", lambda: (context.imports, {}))
    monkeypatch.setattr(ib.subprocess, "run", lambda *args, **kwargs:
                        SimpleNamespace(returncode=0, stdout="pure byte gate fixture\n"))

    def linked(obj, imports, work, label):
        linked_calls.append((obj, label))
        (work / f"{label}.dll").write_bytes(pe_bytes())
        (work / f"{label}.map").write_text(map_line(), encoding="ascii")
        return True, "pure selected link fixture", [], []

    def changed_after_verify(*args, **kwargs):
        problems = real_verify(*args, **kwargs)
        proof = kwargs.get("weak_proof")
        if proof is not None:
            assert problems == []
            assert proof["input_hash_equality"] is True
            assert proof["bindings"][0]["symbol"] == CANONICAL
            assert proof["bindings"][0]["proved"] is True
            verified.append(True)
            path.write_bytes(path.read_bytes() + b"\n")
        return problems

    monkeypatch.setattr(ib, "strict_link", linked)
    monkeypatch.setattr(ib, "verify_object", changed_after_verify)
    assert ib.cmd_check(SimpleNamespace(source="game/x.cpp")) == 1
    receipt = json.loads((context.work / "receipt.json").read_text())
    assert linked_calls == [(context.obj, "after")] and verified == [True]
    assert receipt["strict_link"]["ok"] is True and receipt["pass"] is False
    assert receipt["weak_import_proof"]["input_hash_equality"] is False
    assert receipt["weak_import_proof"]["bindings"][0]["proved"] is True
    assert any("weak import proof input changed before receipt" in problem for problem in receipt["failures"])


@pytest.mark.parametrize("options", [{"aux_count": 0}, {"tag": 2}, {"search": 4}])
def test_check_malformed_weak_auxiliary_fails_without_linking(selection_context, monkeypatch, options):
    context = selection_context
    write_weak_coff(context.obj, **options)
    monkeypatch.setattr(ib, "load_context", lambda: (context.imports, {}))
    monkeypatch.setattr(ib.subprocess, "run", lambda *args, **kwargs:
                        SimpleNamespace(returncode=0, stdout="pure byte gate fixture\n"))

    def unexpected(*args):
        raise AssertionError("malformed source weak auxiliary must be refused before linking")

    monkeypatch.setattr(ib, "strict_link", unexpected)
    assert ib.cmd_check(SimpleNamespace(source="game/x.cpp")) == 1
    assert json.loads((context.work / "receipt.json").read_text())["pass"] is False


def test_first_check_preparation_refusal_creates_failure_receipt(selection_context, monkeypatch):
    context = selection_context
    (context.work / "after.dll").unlink()
    (context.work / "after.map").unlink()
    context.work.rmdir()
    write_weak_coff(context.obj, aux_count=0)
    monkeypatch.setattr(ib, "load_context", lambda: (context.imports, {}))
    monkeypatch.setattr(ib.subprocess, "run", lambda *args, **kwargs:
                        SimpleNamespace(returncode=0, stdout="pure byte gate fixture\n"))

    def unexpected(*args):
        raise AssertionError("malformed source weak auxiliary must be refused before linking")

    monkeypatch.setattr(ib, "strict_link", unexpected)
    assert ib.cmd_check(SimpleNamespace(source="game/x.cpp")) == 1
    receipt = json.loads((context.work / "receipt.json").read_text())
    assert receipt["pass"] is False and receipt["failures"]
    assert receipt["strict_link"]["ok"] is False


def test_apply_refuses_weak_route_without_rewriting_source(selection_context, monkeypatch):
    context = selection_context
    original = context.source.read_bytes()
    monkeypatch.setattr(ib, "load_context", lambda: (context.imports, {}))
    monkeypatch.setattr(ib, "fresh_object", lambda source: (context.obj, "pure compile fixture"))
    assert ib.cmd_apply(SimpleNamespace(source="game/x.cpp", model=None)) == 1
    assert context.source.read_bytes() == original
    assert (context.work / "refused.txt").exists()
    assert not (context.work / "plan.json").exists()


def test_normal_true_undefined_import_does_not_request_weak_adapter(selection_context, monkeypatch):
    context = selection_context
    write_coff(context.obj, CANONICAL)
    monkeypatch.setattr(ib, "load_context", lambda: (context.imports, {}))
    monkeypatch.setattr(ib.subprocess, "run", lambda *args, **kwargs:
                        SimpleNamespace(returncode=0, stdout="pure byte gate fixture\n"))
    monkeypatch.setattr(ib, "strict_link", lambda *args: (True, "pure link fixture", [], []))

    def unexpected(*args, **kwargs):
        raise AssertionError("normal undefined imports do not require weak selected proof")

    monkeypatch.setattr(ib, "weak_selection_inputs", unexpected)
    monkeypatch.setattr(ib, "weak_selected_proof", unexpected)
    assert ib.cmd_check(SimpleNamespace(source="game/x.cpp")) == 0
