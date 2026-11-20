"""Source-owned callable imports: raw COFF/archive fixtures and native controls.

Pure tests substitute only compile currency and retail fixture bytes. Native
tests compile a disposable checkout with VC7.1 and real baseline/library inputs;
they are neither a production ledger admission nor a game/runtime test.
"""
import csv
import hashlib
import json
import os
from pathlib import Path
import struct
import subprocess
import sys
from types import SimpleNamespace
import uuid

import pytest

import build
import data_scaffold
import import_binding as ib


NAME = "_OwnedExample"
IAT = "__imp_" + NAME
SLOT = 0x3000
RVA = 0x1000
IDENTITY = ("test.dll", "OwnedExample")
FIELDS = ["name", "target_rva", "target_size", "status", "source", "notes"]


def archive(*members, omitted=()):
    def framed(name, body):
        head = (name.ljust(16) + "0".ljust(12) + "0".ljust(6)
                + "0".ljust(6) + "100666".ljust(8) + str(len(body)).ljust(10) + "`\n")
        return head.encode("ascii") + body + (b"\n" if len(body) & 1 else b"")
    publics = []
    for i, member in enumerate(members):
        if member[:4] == b"\0\0\xff\xff":
            name = member[20:member.index(0, 20)]
            if struct.unpack_from("<H", member, 18)[0] & 3 == 0 and name.decode() not in omitted:
                publics.append((name, i))
            if (b"__imp_" + name).decode() not in omitted:
                publics.append((b"__imp_" + name, i))
    strings = b"".join(n + b"\0" for n, i in publics)
    first_size = 4 + 4 * len(publics) + len(strings)
    second_size = 8 + 4 * len(members) + 2 * len(publics) + len(strings)
    at = 8 + len(framed("/", bytes(first_size))) + len(framed("/", bytes(second_size)))
    offsets = []
    for i, member in enumerate(members):
        offsets.append(at)
        at += len(framed(f"m{i}.obj/", member))
    first = (struct.pack(">I", len(publics))
             + b"".join(struct.pack(">I", offsets[i]) for n, i in publics) + strings)
    ordered = sorted(publics)
    second = (struct.pack("<I", len(members)) + b"".join(struct.pack("<I", o) for o in offsets)
              + struct.pack("<I", len(publics))
              + b"".join(struct.pack("<H", i + 1) for n, i in ordered)
              + b"".join(n + b"\0" for n, i in ordered))
    return (b"!<arch>\n" + framed("/", first) + framed("/", second)
            + b"".join(framed(f"m{i}.obj/", body) for i, body in enumerate(members)))


def short_import(name=NAME, dll="TEST.dll", *, kind=0, hint=37, machine=0x14C, name_type=2):
    payload = name.encode("ascii") + b"\0" + dll.encode("ascii") + b"\0"
    return struct.pack("<HHHHIIHH", 0, 0xFFFF, 0, machine, 123, len(payload), hint,
                       kind | (name_type << 2)) + payload


def write_thunk(path, *, name=NAME, iat=IAT, body=b"\xff\x25" + bytes(4),
                flags=0x60000020, function_type=0x20, storage=2,
                relocations=None, cell_section=0, cell_storage=2, cell_value=0):
    if relocations is None:
        relocations = [(2, 1, ib.DIR32)]
    strings = bytearray(4)
    def named(value):
        data = value.encode("ascii")
        if len(data) <= 8:
            return data.ljust(8, b"\0")
        result = struct.pack("<II", 0, len(strings))
        strings.extend(data + b"\0")
        return result
    symbol_data = (named(name) + struct.pack("<IhHBB", 0, 1, function_type, storage, 0)
                   + named(iat) + struct.pack("<IhHBB", cell_value, cell_section, 0, cell_storage, 0))
    struct.pack_into("<I", strings, 0, len(strings))
    raw, reloc = 60, 60 + len(body)
    table = reloc + 10 * len(relocations)
    header = struct.pack("<HHIIIHH", 0x14C, 1, 0, table, 2, 0, 0)
    section = struct.pack("<8sIIIIIIHHI", b".text", 0, 0, len(body), raw,
                          reloc if relocations else 0, 0, len(relocations), 0, flags)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(header + section + body
                     + b"".join(struct.pack("<IIH", *r) for r in relocations) + symbol_data + strings)
    return path


def write_rows(path, *rows):
    with path.open("w", newline="", encoding="utf-8") as fh:
        writer = csv.DictWriter(fh, fieldnames=FIELDS)
        writer.writeheader()
        writer.writerows(rows)


@pytest.fixture
def owner(monkeypatch, tmp_path):
    monkeypatch.setattr(ib, "ROOT", tmp_path)
    monkeypatch.setattr(ib, "OUT", tmp_path / "build/import_binding")
    monkeypatch.setattr(build, "ROOT", tmp_path)
    monkeypatch.setattr(build, "BUILD_DIR", tmp_path / "build/match")
    monkeypatch.setattr(data_scaffold, "ROOT", tmp_path)
    monkeypatch.setattr(build, "FUNCTIONS", tmp_path / "functions.csv")
    monkeypatch.setattr(build, "_FUNCTION_ROWS_CACHE", {})
    monkeypatch.setattr(build, "EXE", tmp_path / "retail.bin")
    build.EXE.write_bytes(b"retail fixture")
    src = tmp_path / "game/Owner.cpp"
    src.parent.mkdir()
    src.write_text('extern "C" { extern int (*_imp__OwnedExample)(int);\n'
                   'int OwnedExample(int value) { return _imp__OwnedExample(value); } }\n')
    row = dict(name=NAME, target_rva=hex(RVA), target_size="6", status="matched",
               source="game/Owner.cpp", notes="")
    write_rows(build.FUNCTIONS, row)
    obj = write_thunk(build.obj_path(src))
    build._deps_sidecar(obj).write_text("{}")
    monkeypatch.setattr(build, "compile_is_current", lambda *a, **kw: True)
    monkeypatch.setattr(build, "_compile_receipt_preflight", lambda *a: ({"deps": {}}, True, False, []))
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size:
                        (b"\xff\x25" + struct.pack("<I", ib.BASE + SLOT))[:size])
    monkeypatch.setattr(ib, "retail_slots", lambda: {SLOT: IDENTITY})
    lib = tmp_path / "original.lib"
    lib.write_bytes(archive(short_import()))
    imports = ib.Imports(ib.retail_slots(), [lib])
    return SimpleNamespace(root=tmp_path, source=src, relative=row["source"], row=row,
                           obj=obj, lib=lib, imports=imports)


def proof(owner):
    return ib.source_owned_thunks(owner.relative, owner.obj, owner.imports)


def test_exact_current_authored_owner_preserves_public_name_and_code_facts(owner):
    found = proof(owner)
    assert set(found) == {NAME}
    assert found[NAME]["expected"] == list(IDENTITY)
    assert found[NAME]["slot"] == SLOT
    assert owner.imports.thunk == {NAME: IDENTITY}
    assert ib.plan(owner.relative, owner.obj, owner.imports, {}) == []
    assert ib.verify_object(owner.relative, owner.obj, owner.imports, {}, []) == []
    result = ib.measure([owner.obj], owner.imports, {})
    assert result["references"] == {"correct": 1, "source-owned-thunk": 1}
    assert result["objects"][owner.obj.name]["duplicate_thunks"] == []
    assert result["objects"][owner.obj.name]["source_owned_thunks"] == [NAME]


@pytest.mark.parametrize("kwargs", [
    {"flags": 0xC0000040}, {"flags": 0x40000020}, {"function_type": 0}, {"storage": 3},
    {"body": b"\xff\x25" + bytes(4) + b"\xc3"},
    {"body": b"\xff\x25\x01\0\0\0"}, {"iat": "__imp__Other"},
    {"relocations": []}, {"relocations": [(2, 1, 0x14)]},
    {"relocations": [(2, 1, ib.DIR32), (0, 1, ib.DIR32)]},
    {"cell_section": 1}, {"cell_section": -1, "cell_value": ib.BASE + SLOT},
    {"cell_value": 4}, {"cell_storage": 105},
])
def test_raw_prefix_data_alias_extra_body_and_non_native_iat_remain_unproved(owner, kwargs):
    write_thunk(owner.obj, **kwargs)
    assert proof(owner) == {}
    assert NAME in owner.imports.thunk
    if kwargs.get("storage") == 3:
        # A private STATIC function is not an external duplicate, and cannot
        # remove the native public CODE provider from the link.
        return
    if kwargs.get("cell_storage") == 105:
        with pytest.raises(ib.Refused, match="malformed weak"):
            ib.verify_object(owner.relative, owner.obj, owner.imports, {}, [])
        return
    # A source-defined cell keeps its independent existing refusal too.
    assert any("call stub" in p or "import-address cell" in p
               for p in ib.verify_object(owner.relative, owner.obj, owner.imports, {}, []))


@pytest.mark.parametrize("change", ["stale", "alias", "generated-note", "dump-note", "no-row", "second-row",
                                     "asm", "raw-emit", "token-paste", "wrong-path", "wrong-iat", "wrong-dll"])
def test_ownership_needs_current_unaliased_authored_row_and_independent_identity(owner, monkeypatch, change):
    if change == "stale":
        monkeypatch.setattr(build, "compile_is_current", lambda *a, **kw: False)
    elif change == "alias":
        owner.row["notes"] = "object-symbol=" + NAME
        owner.row["name"] = "?InventedAlias@@YAXXZ"
    elif change == "generated-note":
        owner.row["notes"] = "gen-thunk"
    elif change == "dump-note":
        owner.row["notes"] = "gen-dump"
    elif change == "no-row":
        write_rows(build.FUNCTIONS)
    elif change == "second-row":
        write_rows(build.FUNCTIONS, owner.row, owner.row)
    elif change in ("asm", "raw-emit", "token-paste"):
        owner.source.write_text({"asm": "__asm { jmp eax }", "raw-emit": "__emit 0xff;", "token-paste": "#define X __a ## sm"}[change])
    elif change == "wrong-path":
        other = owner.obj.with_name("unregistered.obj")
        other.write_bytes(owner.obj.read_bytes())
        owner.obj = other
    elif change == "wrong-iat":
        monkeypatch.setattr(ib, "retail_slots", lambda: {SLOT + 4: IDENTITY})
    elif change == "wrong-dll":
        owner.lib.write_bytes(archive(short_import(dll="OTHER.dll")))
    if change in ("alias", "generated-note", "dump-note"):
        write_rows(build.FUNCTIONS, owner.row)
    assert proof(owner) == {}


def test_foreign_alternative_for_same_symbol_is_not_a_library_vote(owner):
    other = owner.root / "other.lib"
    other.write_bytes(archive(short_import(dll="OTHER.dll")))
    imports = ib.Imports(ib.retail_slots(), [owner.lib, other])
    assert ib.source_owned_thunks(owner.relative, owner.obj, imports) == {}


@pytest.mark.parametrize("missing", [NAME, IAT])
def test_native_code_property_requires_actual_callable_and_iat_archive_providers(owner, missing):
    owner.lib.write_bytes(archive(short_import(), omitted={missing}))
    assert owner.imports.thunk == {NAME: IDENTITY}  # raw headers remain truthful
    assert proof(owner) == {}  # an unindexed header is not a native provider
    assert "call stub" in ib.verify_object(owner.relative, owner.obj, owner.imports, {}, [])[-1]


def test_source_or_library_mutation_during_proof_cannot_get_ownership(owner, monkeypatch):
    original = ib.file_digest
    calls = 0
    def changed(path):
        nonlocal calls
        value = original(path)
        if Path(path) == owner.lib:
            calls += 1
            if calls > 1:
                return "0" * 64
        return value
    monkeypatch.setattr(ib, "file_digest", changed)
    assert proof(owner) == {}


@pytest.mark.parametrize("text", ["__asm { jmp eax }", "#define ASSEMBLER __a ## sm"])
def test_header_asm_or_token_paste_cannot_hide_authored_source_provenance(owner, monkeypatch, text):
    header = owner.root / "native.h"
    header.write_text(text)
    monkeypatch.setattr(build, "_compile_receipt_preflight", lambda *a:
                        ({"deps": {str(header): ib.file_digest(header)}}, True, False, []))
    assert proof(owner) == {}


def fake_librarian(monkeypatch):
    """Pure projection fixture; native tests below use the actual lib.exe."""
    commands = []
    def run(cmd, cwd, **kwargs):
        commands.append(cmd)
        target = Path(cwd) / next(a[len("/OUT:"):] for a in cmd if a.startswith("/OUT:"))
        from coffar import read_archive
        target.write_bytes(archive(*(b for n, b in read_archive(Path(cwd) / cmd[-1]))))
        return SimpleNamespace(returncode=0, stdout="", stderr="")
    monkeypatch.setattr(ib.subprocess, "run", run)
    return commands


def test_projection_changes_only_proved_code_entry_keeps_other_members_and_original(owner, monkeypatch):
    unowned = short_import("_Other", "TEST.dll", hint=71)
    data = short_import("_Data", "TEST.dll", kind=1)
    constant = short_import("_Constant", "TEST.dll", kind=2)
    static = b"an unrelated native static member"
    owner.lib.write_bytes(archive(short_import(), unowned, data, constant, static))
    original = owner.lib.read_bytes()
    commands = fake_librarian(monkeypatch)
    libs, context = ib.scoped_import_libraries([owner.lib], [owner.obj], owner.root / "build/private-libs")
    assert len(commands) == 1 and set(context["owners"]) == {NAME}
    assert owner.lib.read_bytes() == original
    assert libs[0] != owner.lib and libs[0].is_relative_to(owner.root / "build")
    projected = libs[0].read_bytes()
    raw = libs[0].with_name(libs[0].stem + ".raw.lib").read_bytes()
    assert sum(a != b for a, b in zip(original, raw)) == 1
    assert len(original) == len(raw)
    assert ib.short_imports(libs[0]) == [
        (NAME, *IDENTITY, 1), ("_Other", "test.dll", "Other", 0),
        ("_Data", "test.dll", "Data", 1), ("_Constant", "test.dll", "Constant", 2)]
    assert static in projected and unowned in projected and data in projected and constant in projected
    assert context["archive_proofs"][0]["both_provider_indexes_preserved"]
    assert owner.imports.thunk == {NAME: IDENTITY}


def test_name_set_and_nonparticipating_source_do_not_enable_projection(owner, monkeypatch):
    def forbidden(*a, **kw):
        raise AssertionError("native librarian must not run without a proved participating owner")
    monkeypatch.setattr(ib.subprocess, "run", forbidden)
    for objects in ([], [NAME], [owner.obj.with_name("copied.obj")]):
        libs, context = ib.scoped_import_libraries([owner.lib], objects, owner.root / "build/private-libs")
        assert libs == [owner.lib] and context["owners"] == {}


@pytest.mark.parametrize("machine,name_type", [(0x8664, 2), (0x14C, 0), (0x14C, 4)])
def test_projection_refuses_unsupported_short_import_header(owner, monkeypatch, machine, name_type):
    owner.lib.write_bytes(archive(short_import(machine=machine, name_type=name_type)))
    fake_librarian(monkeypatch)
    assert proof(owner) == {}
    libs, context = ib.scoped_import_libraries([owner.lib], [owner.obj], owner.root / "build/private-libs")
    assert libs == [owner.lib] and context["owners"] == {}


def test_projection_cannot_overwrite_original_directory(owner, monkeypatch):
    fake_librarian(monkeypatch)
    original = owner.lib.read_bytes()
    with pytest.raises(ib.Refused, match="disposable"):
        ib.scoped_import_libraries([owner.lib], [owner.obj], owner.root)
    assert owner.lib.read_bytes() == original


@pytest.mark.parametrize("damage", ["member", "stale-index"])
def test_rebuilt_archive_cannot_change_members_or_keep_stale_callable_index(owner, monkeypatch, damage):
    original = owner.lib.read_bytes()
    def damaged(cmd, cwd, **kwargs):
        from coffar import read_archive
        raw = Path(cwd) / cmd[-1]
        target = Path(cwd) / next(a[len("/OUT:"):] for a in cmd if a.startswith("/OUT:"))
        if damage == "stale-index":
            target.write_bytes(raw.read_bytes())
        else:
            members = [bytearray(b) for n, b in read_archive(raw)]
            members[0][8] ^= 1  # native short-import timestamp: identity strings alone miss it
            target.write_bytes(archive(*(bytes(b) for b in members)))
        return SimpleNamespace(returncode=0, stdout="", stderr="")
    monkeypatch.setattr(ib.subprocess, "run", damaged)
    with pytest.raises(ib.Refused, match="member|index"):
        ib.scoped_import_libraries([owner.lib], [owner.obj], owner.root / "build/private-libs")
    assert owner.lib.read_bytes() == original


NATIVE = os.name == "nt" and (build.DEFAULT_VC71_ROOT / "Vc7/bin/link.exe").exists()
NATIVE_ROOT = build.ROOT / "build/agent-thing-bfme1-20261120/source-owned-native"


@pytest.fixture
def native_owner(monkeypatch):
    """A real compiler receipt and normal private ledger, no byte-gate mocks."""
    root = NATIVE_ROOT / uuid.uuid4().hex[:8]
    root.mkdir(parents=True, exist_ok=True)
    # Keep actual original baseline/toolchain paths; only this fixture checkout,
    # normal object directory and ledger are private.
    monkeypatch.setattr(ib, "ROOT", root)
    monkeypatch.setattr(ib, "OUT", root / "build/import_binding")
    monkeypatch.setattr(build, "ROOT", root)
    monkeypatch.setattr(build, "BUILD_DIR", root / "build/match")
    monkeypatch.setattr(data_scaffold, "ROOT", root)
    monkeypatch.setattr(build, "FUNCTIONS", root / "functions.csv")
    monkeypatch.setattr(build, "_FUNCTION_ROWS_CACHE", {})
    # Public typed source is kept inline so this regression is self-contained.
    definitions = [
        ("ControlFp.cpp", "__controlfp", 0x9F7DF2, 6,
         '// cl: /O1 /G7 /Ob1 /MD /D_CRTIMP=\n#include <float.h>\nextern "C" {\n'
         'extern unsigned int (__cdecl *_imp___controlfp)(unsigned int, unsigned int);\n'
         'unsigned int __cdecl _controlfp(unsigned int value, unsigned int mask) {\n'
         'return _imp___controlfp(value, mask); } }\n'),
        ("DllOnExitImport.cpp", "___dllonexit", 0x9F7EE0, 6,
         '// cl: /O2 /G7 /Oy /Ob1 /MD\n#include <stdlib.h>\n'
         'typedef void (__cdecl *Callback)();\nextern "C" {\n'
         'extern _onexit_t (__cdecl *_imp____dllonexit)(_onexit_t, Callback **, Callback **);\n'
         '_onexit_t __cdecl __dllonexit(_onexit_t f, Callback **b, Callback **e) {\n'
         'return _imp____dllonexit(f, b, e); } }\n'),
        ("DefaultPrecision.cpp", "__setdefaultprecision", 0x9F7F98, 18,
         '// cl: /O1 /Ob1 /MD /D_CRTIMP=\n#include <float.h>\n'
         'extern "C" void __cdecl _setdefaultprecision() { _controlfp(_PC_53, _MCW_PC); }\n'),
        ("AtexitThunk.c", "__onexit", 0x9F6E00, 38,
         '// cl: /DNDEBUG /MD /O1\n#include <stdlib.h>\n'
         'typedef void (__cdecl *Callback)(void);\nCallback *__onexitbegin;\nCallback *__onexitend;\n'
         'extern _onexit_t (__cdecl *_imp___onexit)(_onexit_t);\n'
         '_onexit_t __cdecl __dllonexit(_onexit_t, Callback **, Callback **);\n'
         '_onexit_t __cdecl _onexit(_onexit_t f) {\n'
         'if (__onexitbegin == (Callback *)-1) return _imp___onexit(f);\n'
         'return __dllonexit(f, &__onexitbegin, &__onexitend); }\n'
         'int __cdecl atexit(Callback f) { return (_onexit((_onexit_t)f) == 0) ? -1 : 0; }\n'),
    ]
    rows, objects = [], []
    for filename, name, rva, size, text in definitions:
        source = root / "game" / filename
        source.parent.mkdir(exist_ok=True)
        source.write_text(text)
    for filename, name, rva, size, text in definitions:
        source = root / "game" / filename
        output = build.obj_path(source)
        output.parent.mkdir(parents=True, exist_ok=True)
        build.compile_source(source, output)
        assert build.compile_is_current(source, output)
        rows.append(dict(name=name, target_rva=hex(rva), target_size=str(size), status="matched",
                         source=source.relative_to(root).as_posix(), notes=""))
        objects.append(output)
    assert all(build.compile_is_current(root / row["source"], obj) for row, obj in zip(rows, objects))
    import link_census
    globals = {r["name"]: r for r in link_census._coff_symbols(objects[3].read_bytes())
               if r["name"] in ("___onexitbegin", "___onexitend")}
    assert set(globals) == {"___onexitbegin", "___onexitend"}
    assert all(r["storage"] == 2 and r["section"] == 0 and r["value"] == 4 for r in globals.values())
    rows.append(dict(name="_atexit", target_rva="0x9F6E26", target_size="18", status="matched",
                     source="game/AtexitThunk.c", notes=""))
    write_rows(build.FUNCTIONS, *rows)
    symbols = {r["name"]: [int(r["target_rva"], 16)] for r in rows}
    for row in rows:
        verified = build.compile_function(row, symbols, build.obj_path(root / row["source"]))
        assert verified["bytes"] == verified["target"] and not verified["masked"] and not verified["unresolved"]
    lib = build.vc71_root() / "Vc7/lib/msvcrt.lib"
    oldnames = build.vc71_root() / "Vc7/lib/oldnames.lib"
    return SimpleNamespace(root=root, rows=rows, objects=objects, libs=[lib,
        build.vc71_root() / "Vc7/lib/libc.lib", build.vc71_root() / "Vc7/lib/kernel32.lib", oldnames])


@pytest.mark.skipif(not NATIVE, reason="needs real MSVC 7.1 on Windows")
def test_native_original_duplicate_then_scoped_iat_only_selected_cpp_and_exact_import(native_owner):
    fixture = native_owner
    import provider_repair
    import selected_import_audit as audit
    import pefile
    originals = {str(p): ib.file_digest(p) for p in fixture.libs}
    work = fixture.root / "build/link"
    work.mkdir(parents=True, exist_ok=True)
    def link(label, libs, objects=fixture.objects):
        image, mapping = work / (label + ".dll"), work / (label + ".map")
        result = provider_repair._link(["/DLL", "/NOENTRY", "/OPT:NOREF", "/OPT:NOICF", "/SAFESEH:NO",
                                        "/NODEFAULTLIB", "/INCLUDE:__CIacos", "/OUT:" + str(image), "/MAP:" + str(mapping),
                                        *objects, *libs])
        return result, image, mapping
    before, _, _ = link("original-code-control", fixture.libs)
    assert before.returncode != 0
    assert "LNK2005" in before.stdout + before.stderr
    libs, context = ib.scoped_import_libraries(fixture.libs, fixture.objects, work / "private-iat")
    assert set(context["owners"]) == {r["name"] for r in fixture.rows if r["target_size"] == "6"}
    after, image, mapping = link("source-owned", libs)
    assert after.returncode == 0, after.stdout + after.stderr
    verified = ib.source_owned_selected_proof(context, mapping, image)
    assert verified["input_hash_equality"] and len(verified["bindings"]) == 2
    assert all(b["proved"] and b["iat_binding"]["proved"] for b in verified["bindings"])
    assert {str(p): ib.file_digest(p) for p in fixture.libs} == originals
    assert all(name in ib.Imports(ib.retail_slots(), fixture.libs).thunk for name in context["owners"])
    selected = audit.map_symbols(mapping.read_text(encoding="latin-1").splitlines())
    cells, thunks = audit.oracle(ib.retail_slots(), libs)
    pe = pefile.PE(str(image))
    try:
        unowned = audit.audit_binding("__CIacos", cells, thunks, selected, audit.pe_slots(pe),
                                       audit.virtual_reader(pe), audit.executable_reader(pe))
    finally:
        pe.close()
    assert unowned["proved"], unowned
    assert "__CIacos" in thunks  # native CODE provider still resolves an unowned callable
    assert next(t for n, d, e, t in ib.short_imports(libs[0]) if n == "__onexit") == 1
    # Exercise the normal data scaffold library-selection path, not a custom
    # closure-only library builder. Resources and all other native imports stay.
    scaffold_libs, scaffold_report = data_scaffold.retail_libraries(fixture.root / "build/scaffold", objects=fixture.objects)
    scaffold_context = scaffold_report["source_owned_callable_imports"]
    scaffold_link, scaffold_image, scaffold_map = link("normal-scaffold", [*scaffold_libs, fixture.libs[-1]])
    assert scaffold_link.returncode == 0, scaffold_link.stdout + scaffold_link.stderr
    scaffold_proof = ib.source_owned_selected_proof(scaffold_context, scaffold_map, scaffold_image)
    assert all(b["proved"] for b in scaffold_proof["bindings"])
    # The ordinary no-context catalog still exposes original CODE imports.
    catalog, catalog_report = data_scaffold.retail_libraries(fixture.root / "build/scaffold-default")
    assert "source_owned_callable_imports" not in catalog_report
    assert catalog[0] == fixture.libs[0]
    # Exercise the ordinary scoped import checker as well. Only the private
    # fixture's original library catalog is selected; native linking/proof run.
    monkeypatch = pytest.MonkeyPatch()
    try:
        monkeypatch.setattr(ib, "libraries", lambda: fixture.libs)
        imports = ib.Imports(ib.retail_slots(), fixture.libs)
        for index in range(2):
            row, obj = fixture.rows[index], fixture.objects[index]
            assert ib.verify_object(row["source"], obj, imports, {}, []) == []
            ok, log, linked, stubs = ib.strict_link(obj, imports, work / "normal-check", f"owner{index}")
            assert ok, log
            assert ib.link_verdict(ok, linked, imports) == []
            assert (work / "normal-check" / f"owner{index}_source_owned.json").exists()
    finally:
        monkeypatch.undo()
    (work / "native-receipt.json").write_text(json.dumps({
        "scope": "Private fixture checkout; five strict authored rows plus original CRT COMMONs; no production admission or execution",
        "original_code_control": {"exit": before.returncode, "log": before.stdout + before.stderr},
        "iat_only_candidate": {"exit": after.returncode, "log": after.stdout + after.stderr},
        "original_libraries_unchanged": originals, "projection": context,
        "selected_import_proof": verified, "unowned_code_control": unowned,
        "normal_scaffold_proof": scaffold_proof}, indent=2))
    (NATIVE_ROOT / "latest-receipt.txt").write_text(str(work / "native-receipt.json"))
    # A forged public MAP owner cannot borrow the valid native import binding.
    wrong = work / "wrong-owner.map"
    text = mapping.read_text(encoding="latin-1")
    text = text.replace(fixture.objects[0].name, "wrong-owner.obj")
    wrong.write_text(text, encoding="latin-1")
    with pytest.raises(ib.Refused, match="MAP"):
        ib.source_owned_selected_proof(context, wrong, image)
    # A stale source cannot borrow an earlier valid selected-provider receipt.
    source = fixture.root / fixture.rows[0]["source"]
    original_source = source.read_bytes()
    try:
        source.write_text(source.read_text() + "\n// changed after native proof\n")
        with pytest.raises(ib.Refused, match="changed|current"):
            ib.source_owned_selected_proof(context, mapping, image)
    finally:
        source.write_bytes(original_source)
    # Preserve replayable positive evidence after the destructive negative.
    replayed = ib.source_owned_selected_proof(context, mapping, image)
    receipt = json.loads((work / "native-receipt.json").read_text())
    receipt["negative_controls"] = {"wrong_map_refused": True, "stale_source_refused": True,
                                    "source_restored": True}
    receipt["post_negative_replay"] = replayed
    (work / "native-receipt.json").write_text(json.dumps(receipt, indent=2))


# Translation phase 2 joins physical lines before comments are recognized.
# These are valid ways to spell the same refused asm/intrinsic/paste tokens.
@pytest.mark.parametrize("in_header", [False, True])
@pytest.mark.parametrize("text", [
    "__a\\\nsm { jmp eax }",
    "__declspec(na\\\nked) int f();",
    "__em\\\nit 0xff;",
    "#define ASSEMBLER __a #\\\n# sm",
])
def test_spliced_source_or_header_cannot_hide_assembly_or_token_paste(owner, monkeypatch, in_header, text):
    if in_header:
        header = owner.root / "spliced.h"
        header.write_text(text)
        monkeypatch.setattr(build, "_compile_receipt_preflight", lambda *a:
                            ({"deps": {str(header): ib.file_digest(header)}}, True, False, []))
    else:
        owner.source.write_text(text)
    assert proof(owner) == {}


@pytest.mark.parametrize("ending", ["\r\n", "\r"])
def test_non_lf_physical_lines_cannot_hide_assembly(owner, ending):
    owner.source.write_bytes(("__a\\" + ending + "sm { jmp eax }").encode("ascii"))
    assert proof(owner) == {}


def test_spliced_line_comment_is_elided_after_line_joining(owner):
    original = owner.source.read_text()
    owner.source.write_text(original + "\n// This comment continues \\\n__asm __emit naked ##\n")
    assert set(proof(owner)) == {NAME}


@pytest.mark.skipif(not NATIVE, reason="needs real MSVC 7.1 on Windows")
def test_native_spliced_naked_asm_never_acquires_authored_callable_ownership(native_owner):
    fixture = native_owner
    row, obj = fixture.rows[0], fixture.objects[0]
    source = fixture.root / row["source"]
    original = source.read_bytes()
    imports = ib.Imports(ib.retail_slots(), fixture.libs)
    try:
        objects = []
        for naked, assembler in [("naked", "__asm"), ("na\\\nked", "__a\\\nsm")]:
            text = ('// cl: /O1 /G7 /Ob1 /MD /D_CRTIMP=\n#include <float.h>\nextern "C" {\n'
                    'extern unsigned int (__cdecl *_imp___controlfp)(unsigned int, unsigned int);\n'
                    '__declspec(' + naked + ') unsigned int __cdecl _controlfp(unsigned int value, unsigned int mask) {\n'
                    + assembler + ' { jmp dword ptr [_imp___controlfp] }\n}\n}\n')
            source.write_text(text)
            build.compile_source(source, obj)
            assert build.compile_is_current(source, obj)
            compared = build.compile_function(row, {}, obj)
            assert compared["bytes"] == compared["target"] and not compared["masked"] and not compared["unresolved"]
            objects.append(obj.read_bytes())
            assert ib.source_owned_thunks(row["source"], obj, imports) == {}
        assert objects[0] == objects[1]
    finally:
        source.write_bytes(original)
        build.compile_source(source, obj)


@pytest.mark.parametrize("collision", ["iat000.lib", "iat000.raw.lib"])
def test_projection_outputs_cannot_replace_frozen_input_libraries(owner, monkeypatch, collision):
    work = owner.root / "build/colliding-outputs"
    work.mkdir(parents=True)
    original = work / collision
    original.write_bytes(owner.lib.read_bytes())
    before = original.read_bytes()
    commands = fake_librarian(monkeypatch)
    with pytest.raises(ib.Refused, match="input"):
        ib.scoped_import_libraries([original], [owner.obj], work)
    assert original.read_bytes() == before
    assert commands == []  # The refusal precedes unlink/write/native lib.exe.
