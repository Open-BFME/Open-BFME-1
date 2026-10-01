"""A native archive/table/initializer must prove each retired import route."""
import csv
import io
import struct
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import add_match
import archive_import
import build
import reloc_ledger

PUBLIC = "_Native@24"
TABLE = "?nativeTable@@3PAHA"
INIT = "?nativeInit@@YAPAXXZ"
OLD = "?ji_00001000@@YAXXZ"
SOURCE = "inputs/vendor/fixture/native.lib"
NOTES = "vendored=fixture-1;member=native.obj"
PROOF = "targets/game/reverse/identity_evidence/native.md"
HEADER = "name,export_rva,target_rva,target_size,source,status,notes"


def coff(sections, symbols):
    """Minimal ordinary i386 object, read by the real COFF parser."""
    strings = bytearray(b"\0\0\0\0")
    symdata = bytearray()
    for name, section, typ, storage in symbols:
        encoded = name.encode()
        if len(encoded) <= 8:
            label = encoded.ljust(8, b"\0")
        else:
            label = struct.pack("<II", 0, len(strings))
            strings.extend(encoded + b"\0")
        symdata.extend(label + struct.pack("<IhHBB", 0, section, typ, storage, 0))
    struct.pack_into("<I", strings, 0, len(strings))
    off = 20 + 40 * len(sections)
    headers, payload = bytearray(), bytearray()
    for name, body, relocs, flags in sections:
        ptr = off
        payload.extend(body)
        off += len(body)
        relptr = off if relocs else 0
        for where, index, kind in relocs:
            payload.extend(struct.pack("<IIH", where, index, kind))
            off += 10
        headers.extend(name.encode().ljust(8, b"\0") + struct.pack(
            "<IIIIIIHHI", 0, 0, len(body), ptr, relptr, 0, len(relocs), 0, flags))
    return struct.pack("<HHIIIHH", 0x14C, len(sections), 0, off, len(symbols), 0, 0) + headers + payload + symdata + strings


def archive(member):
    label = "native.obj/".ljust(16)
    header = (label + "0".ljust(12) + "0".ljust(6) + "0".ljust(6)
              + "100644".ljust(8) + str(len(member)).ljust(10) + "`\n").encode()
    return b"!<arch>\n" + header + member + (b"\n" if len(member) % 2 else b"")


@pytest.fixture
def route(tmp_path, monkeypatch):
    init = b"\x55\x8b\xec\x90\x90\x5d\xc2\x18\x00"
    sections = [[".text", b"\xff\x25\x04\0\0\0", [(2, 1, 6)], 0x60001020],
                [".data", b"\0" * 8, [(4, 2, 6)], 0xC0000040],
                [".text", init, [], 0x60001020]]
    symbols = [[PUBLIC, 1, 0x20, 2], [TABLE, 2, 0, 2], [INIT, 3, 0x20, 2]]
    old = {"name": OLD, "rva": 0x1000, "size": 6, "source": "game/gen_small/imports_000.cpp",
           "status": "matched", "notes": "gen-import;slot=0x00402004;target=thunk_FUN_00403000"}
    owned = {"name": INIT, "rva": 0x3000, "size": len(init), "source": SOURCE,
             "status": "matched", "notes": NOTES}
    memory = {0x401000: b"\xff\x25\x04\x20\x40\0",
              0x402004: struct.pack("<I", 0x403000), 0x403000: init}
    class Image:
        base = 0x400000
        def read(self, va, size):
            value = memory.get(va)
            return value[:size] if value is not None else None
        def u32(self, va):
            return struct.unpack("<I", self.read(va, 4))[0]
    monkeypatch.setattr(reloc_ledger, "Image", lambda raw: Image())
    path = tmp_path / SOURCE
    path.parent.mkdir(parents=True)
    reverse = tmp_path / "targets/game/reverse"
    reverse.mkdir(parents=True)
    (reverse / "dir32_addresses.csv").write_text(f"name,va\n{TABLE},0x00402000\n")
    baseline = tmp_path / build.EXE.relative_to(build.ROOT)
    baseline.parent.mkdir(parents=True)
    baseline.write_bytes(b"fixture baseline")
    monkeypatch.setattr(build, "ROOT", tmp_path)
    monkeypatch.setattr(build, "EXE", baseline)
    monkeypatch.setattr(build, "DIR32_ADDRESSES", reverse / "dir32_addresses.csv")
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size: Image().read(0x400000 + rva, size))
    def write():
        path.write_bytes(archive(coff(sections, symbols)))
    write()
    return SimpleNamespace(root=tmp_path, old=old, rows=[old, owned], sections=sections,
                           symbols=symbols, memory=memory, path=path, write=write)


def verify(route, **overrides):
    args = dict(root=route.root, old=route.old, name=PUBLIC, source=SOURCE,
                notes=NOTES, rows=route.rows)
    args.update(overrides)
    return archive_import.verify(**args)


def test_real_archive_member_route_verifies_without_writing(route):
    before = route.path.read_bytes()
    verify(route)
    assert route.path.read_bytes() == before


@pytest.mark.parametrize("field,value", [("status", "partial"), ("size", 5),
    ("source", "game/Thing.cpp"), ("source", "game/gen_small/fun_000.cpp"),
    ("name", "?ji_00001001@@YAXXZ"), ("notes", "gen-import conversion;slot=0x00402004"),
    ("notes", "gen-import;slot=0x00402008")])
def test_rejects_nonexact_old_import_identity(route, field, value):
    route.old[field] = value
    with pytest.raises(ValueError):
        verify(route)


@pytest.mark.parametrize("notes", ["", "vendored=fixture-1", "member=native.obj",
    "vendored=wrong;member=native.obj", "vendored=fixture-1;member=wrong.obj",
    NOTES + ";member=native.obj", NOTES + ";object-symbol=" + PUBLIC,
    NOTES + ";object-symbol=a;object-symbol=b"])
def test_rejects_unowned_or_indirect_archive_metadata(route, notes):
    with pytest.raises(ValueError):
        verify(route, notes=notes)


@pytest.mark.parametrize("change", ["opcode", "extent", "offset", "kind", "extra_reloc",
    "private", "not_function", "missing_table", "table_code", "table_bounds",
    "missing_init", "init_kind", "unknown_init", "init_target", "init_bytes", "init_addend"])
def test_rejects_broken_native_route_witness(route, change):
    if change == "opcode": route.sections[0][1] = b"\xff\x15\x04\0\0\0"
    elif change == "extent": route.sections[0][1] += b"\x90"
    elif change == "offset": route.sections[0][2] = [(1, 1, 6)]
    elif change == "kind": route.sections[0][2] = [(2, 1, 20)]
    elif change == "extra_reloc": route.sections[0][2].append((0, 1, 6))
    elif change == "private": route.symbols[0][3] = 3
    elif change == "not_function": route.symbols[0][2] = 0
    elif change == "missing_table": route.symbols[1][1] = 0
    elif change == "table_code": route.sections[1][3] = 0x60001020
    elif change == "table_bounds": route.sections[0][1] = b"\xff\x25\x08\0\0\0"
    elif change == "missing_init": route.sections[1][2] = []
    elif change == "init_kind": route.sections[1][2] = [(4, 2, 20)]
    elif change == "unknown_init": route.rows = [route.old]
    elif change == "init_target": route.memory[0x402004] = struct.pack("<I", 0x403001)
    elif change == "init_bytes": route.sections[2][1] = b"\x90" * 9
    elif change == "init_addend": route.sections[1][1] = b"\0" * 4 + struct.pack("<I", 1)
    route.write()
    with pytest.raises(ValueError):
        verify(route)


def test_rejects_wrong_recorded_table_home(route):
    (route.root / "targets/game/reverse/dir32_addresses.csv").write_text(
        f"name,va\n{TABLE},0x00402001\n")
    with pytest.raises(ValueError, match="home"):
        verify(route)


def transaction(route, monkeypatch, gate=0, extra=()):
    reverse = route.root / "targets/game/reverse"
    fields = lambda row: [row["name"], "", f"0x{row['rva']:08X}", str(row["size"]),
                          row["source"], row["status"], row["notes"]]
    data = io.StringIO(newline="")
    writer = csv.writer(data, lineterminator="\r\n")
    writer.writerow(HEADER.split(","))
    writer.writerows(fields(row) for row in route.rows)
    functions, deleted = reverse / "functions.csv", reverse / "deleted_rows.csv"
    functions.write_bytes(data.getvalue().encode())
    deleted.write_bytes(b"name,target_rva,reason\n")
    proof = route.root / PROOF
    proof.parent.mkdir(parents=True)
    proof.write_text("Independent route identity proof.")
    (route.root / "build.sh").write_text("#!/bin/sh\nexit 0\n")
    monkeypatch.setattr(add_match.subprocess, "run", lambda command, *, cwd, env:
                        SimpleNamespace(returncode=gate))
    monkeypatch.setattr(sys, "argv", ["add_match.py", PUBLIC, "0x00001000", "6", SOURCE,
        "--root", str(route.root), "--replace-rva", "0x00001000",
        "--replace-archive-import", OLD, "--identity-evidence", PROOF,
        "--notes", NOTES, *extra])
    return functions, deleted


@pytest.mark.parametrize("gate", [0, 1])
def test_archive_replacement_preserves_transaction_and_binary_member(route, monkeypatch, gate):
    functions, deleted = transaction(route, monkeypatch, gate)
    before = functions.read_bytes(), deleted.read_bytes(), route.path.read_bytes()
    if gate:
        with pytest.raises(SystemExit): add_match.main()
        assert before == (functions.read_bytes(), deleted.read_bytes(), route.path.read_bytes())
    else:
        add_match.main()
        assert OLD not in functions.read_text()
        assert PUBLIC in functions.read_text()
        assert OLD in deleted.read_text()
        assert route.path.read_bytes() == before[2]


@pytest.mark.parametrize("extra", [("--no-verify",), ("--boundary-evidence", "wrong extent"),
    ("--replace-existing",), ("--correct-identity", OLD)])
def test_archive_mode_rejects_bypass_flags_without_writes(route, monkeypatch, extra):
    functions, deleted = transaction(route, monkeypatch, extra=extra)
    before = functions.read_bytes(), deleted.read_bytes(), route.path.read_bytes()
    with pytest.raises(SystemExit): add_match.main()
    assert before == (functions.read_bytes(), deleted.read_bytes(), route.path.read_bytes())


def test_ordinary_scaffold_policy_still_rejects_generated_import(route):
    assert not add_match.replaceable_scaffold(route.old)


@pytest.mark.parametrize("field,value", [("target", "0x00001001"), ("size", "7"),
                                        ("old", "?ji_00001001@@YAXXZ")])
def test_cli_rejects_extent_or_identity_change_without_writes(route, monkeypatch, field, value):
    functions, deleted = transaction(route, monkeypatch)
    positions = {"target": 2, "size": 3, "old": sys.argv.index("--replace-archive-import") + 1}
    sys.argv[positions[field]] = value
    before = functions.read_bytes(), deleted.read_bytes(), route.path.read_bytes()
    with pytest.raises(SystemExit): add_match.main()
    assert before == (functions.read_bytes(), deleted.read_bytes(), route.path.read_bytes())


def test_rejects_noncanonical_archive_function_name(route):
    with pytest.raises(ValueError, match="external archive function"):
        verify(route, name="_Other@24")


def test_rejects_nonvendor_archive(route):
    source = "build/native.lib"
    path = route.root / source
    path.parent.mkdir()
    path.write_bytes(route.path.read_bytes())
    with pytest.raises(ValueError, match="inputs/vendor"):
        verify(route, source=source)


def test_cli_interruption_restores_ledgers_and_archive(route, monkeypatch):
    functions, deleted = transaction(route, monkeypatch)
    before = functions.read_bytes(), deleted.read_bytes(), route.path.read_bytes()
    monkeypatch.setattr(add_match.subprocess, "run",
                        lambda *args, **kwargs: (_ for _ in ()).throw(KeyboardInterrupt()))
    with pytest.raises(KeyboardInterrupt): add_match.main()
    assert before == (functions.read_bytes(), deleted.read_bytes(), route.path.read_bytes())


def runtime_row(route, monkeypatch):
    transaction(route, monkeypatch)
    add_match.main()
    rows = list(csv.DictReader((route.root / "targets/game/reverse/functions.csv").open()))
    return next(row for row in rows if row["name"] == PUBLIC)


def test_runtime_gate_reverifies_native_route_and_keeps_raw_metrics(route, monkeypatch):
    row = runtime_row(route, monkeypatch)
    obj = route.root / "native.obj"
    obj.write_bytes(coff(route.sections, route.symbols))
    patch = build.compile_function(row, {}, obj)
    assert patch["bytes"] == route.memory[0x401000]
    assert patch["masked"] is True and patch["concrete"] == 2
    assert patch["independently_bound"] == 4 and patch["structural_route"]
    monkeypatch.setattr(build, "load_symbol_map", lambda: {})
    monkeypatch.setattr(build, "compile_rows", lambda rows, sources: {})
    monkeypatch.setattr(build, "row_object", lambda row: obj)
    monkeypatch.setattr(build, "write_reloc_names", lambda patches: None)
    assert len(build.verify_functions(selected_rows=[row])) == 1


def test_ordinary_thin_library_row_still_fails_actual_runtime_gate(route, monkeypatch):
    row = runtime_row(route, monkeypatch)
    row["notes"] = NOTES
    obj = route.root / "native.obj"
    obj.write_bytes(coff(route.sections, route.symbols))
    patch = build.compile_function(row, {}, obj)
    assert patch["masked"] and patch["concrete"] == 2 and not patch["structural_route"]
    monkeypatch.setattr(build, "load_symbol_map", lambda: {})
    monkeypatch.setattr(build, "compile_rows", lambda rows, sources: {})
    monkeypatch.setattr(build, "row_object", lambda row: obj)
    with pytest.raises(SystemExit):
        build.verify_functions(selected_rows=[row])


@pytest.mark.parametrize("change", ["archive_hash", "member_hash", "evidence", "table", "initializer"])
def test_runtime_verify_row_refuses_changed_proof(route, monkeypatch, change):
    row = runtime_row(route, monkeypatch)
    if change == "archive_hash":
        route.path.write_bytes(route.path.read_bytes() + b"drift")
    elif change == "member_hash":
        row["notes"] = row["notes"].replace("archive-import-member-sha256=", "wrong-token=")
    elif change == "evidence":
        (route.root / PROOF).unlink()
    elif change == "table":
        (route.root / "targets/game/reverse/dir32_addresses.csv").write_text(
            f"name,va\n{TABLE},0x00402008\n")
    elif change == "initializer":
        route.memory[0x403000] = b"\x90" * 9
    with pytest.raises(ValueError): archive_import.verify_row(route.root, row)


def test_runtime_gate_rejects_tampered_extracted_object(route, monkeypatch):
    row = runtime_row(route, monkeypatch)
    route.sections[0][1] = b"\xff\x15\x04\0\0\0"
    obj = route.root / "wrong.obj"
    obj.write_bytes(coff(route.sections, route.symbols))
    with pytest.raises(ValueError, match="extracted archive thunk"):
        build.compile_function(row, {}, obj)


def test_initializer_must_retain_library_minimum_concrete_bytes(route):
    route.sections[2][2] = [(2, 0, 20)]
    route.write()
    with pytest.raises(ValueError, match="too few independently compared"):
        verify(route)


def initializer_table_operand(route):
    body = b'\x55\x8b\xec\xff\x15\x04\0\0\0\x90\x90\x90\x5d\xc2\x18\0'
    route.sections[2][1] = body
    route.sections[2][2] = [(5, 1, reloc_ledger.DIR32)]
    route.rows[1]['size'] = len(body)
    route.memory[0x403000] = body[:5] + struct.pack('<I', 0x402004) + body[9:]
    route.write()


def test_runtime_rejects_equal_opcode_initializer_with_wrong_table_addend(route, monkeypatch):
    initializer_table_operand(route)
    row = runtime_row(route, monkeypatch)
    assert archive_import.verify_row(route.root, row)
    # Same opcodes/extent/ABI and same relocated mask; a distinct table field.
    body = route.sections[2][1]
    route.sections[2][1] = body[:5] + struct.pack('<I', 0) + body[9:]
    route.write()
    with pytest.raises(ValueError, match='initializer relocation operand'):
        archive_import.verify_row(route.root, row)


@pytest.mark.parametrize('change', ['unknown_home', 'unsupported', 'wrong_retail'])
def test_initializer_operand_proof_fails_closed(route, change):
    initializer_table_operand(route)
    if change == 'unknown_home':
        route.symbols.append(['?unknown@@3HA', 0, 0, 2])
        route.sections[2][2] = [(5, 3, reloc_ledger.DIR32)]
    elif change == 'unsupported':
        route.sections[2][2] = [(5, 1, reloc_ledger.DIR32NB)]
    else:
        original = route.memory[0x403000]
        route.memory[0x403000] = original[:5] + struct.pack('<I', 0x402000) + original[9:]
    route.write()
    with pytest.raises(ValueError):
        verify(route)


def test_initializer_rel32_requires_actual_owned_archive_definition(route):
    body = b'\x55\x8b\xec\xe8\0\0\0\0\x90\x90\x90\x90\x5d\xc2\x18\0'
    route.sections[2][1] = body
    route.sections[2][2] = [(4, 3, reloc_ledger.REL32)]
    route.sections.append(['.text', b'\x90' * 8 + b'\xc3', [], 0x60001020])
    route.symbols.append(['_Destination@4', 4, 0x20, 2])
    route.rows[1]['size'] = len(body)
    route.rows.append(dict(route.rows[1], name='_Destination@4', rva=0x4000, size=9))
    route.memory[0x403000] = body[:4] + struct.pack('<i', 0x404000 - 0x403008) + body[8:]
    route.write()
    assert verify(route)
    route.symbols[3][1] = 0
    route.write()
    with pytest.raises(ValueError, match='actual archive definition'):
        verify(route)


def test_archive_hash_and_member_parse_use_one_frozen_payload(route, monkeypatch):
    original = Path.read_bytes
    reads = []
    def read(path):
        if path == route.path:
            reads.append(path)
        return original(path)
    monkeypatch.setattr(Path, 'read_bytes', read)
    assert verify(route)
    assert len(reads) == 1


@pytest.mark.parametrize('where', [1, 2, 3, 4, 5, 6, 7])
def test_dispatch_cell_rejects_additional_intersecting_relocations(route, where):
    route.sections[1][2].append((where, 2, reloc_ledger.DIR32))
    route.write()
    with pytest.raises(ValueError, match='sole nonoverlapping'):
        verify(route)


def test_dispatch_cell_rejects_unknown_relocation_width(route):
    route.sections[1][2].append((3, 2, 0xFFFF))
    route.write()
    with pytest.raises(ValueError, match='unsupported relocation width'):
        verify(route)


def test_initializer_rel32_rejects_duplicate_definition_in_other_archive_member(route, monkeypatch):
    # Establish the positive direct REL32 fixture from the existing test.
    body = b'\x55\x8b\xec\xe8\0\0\0\0\x90\x90\x90\x90\x5d\xc2\x18\0'
    route.sections[2][1] = body
    route.sections[2][2] = [(4, 3, reloc_ledger.REL32)]
    route.sections.append(['.text', b'\x90' * 8 + b'\xc3', [], 0x60001020])
    route.symbols.append(['_Destination@4', 4, 0x20, 2])
    route.rows[1]['size'] = len(body)
    route.rows.append(dict(route.rows[1], name='_Destination@4', rva=0x4000, size=9))
    route.memory[0x403000] = body[:4] + struct.pack('<i', 0x404000 - 0x403008) + body[8:]
    route.write()
    assert verify(route)
    row = runtime_row(route, monkeypatch)
    duplicate = archive(coff([['.text', b'\xc3', [], 0x60001020]],
                             [['_Destination@4', 1, 0x20, 2]]))
    duplicate = duplicate.replace(b'native.obj/     ', b'other.obj/      ', 1)
    route.path.write_bytes(route.path.read_bytes() + duplicate[8:])
    with pytest.raises(ValueError, match='actual archive definition'):
        archive_import.verify_row(route.root, row)


def cache_route(route, monkeypatch):
    import json
    import verification_cache as cache
    row = runtime_row(route, monkeypatch)
    obj = route.root / 'native.obj'
    obj.write_bytes(coff(route.sections, route.symbols))
    build._deps_sidecar(obj).write_text(json.dumps({'deps': {}}))
    monkeypatch.setattr(build, 'row_object', lambda _: obj)
    monkeypatch.setattr(build, 'compiler_command', lambda *_: ([], {}))
    monkeypatch.setattr(build, 'load_symbol_map', lambda: {})
    monkeypatch.setattr(cache, 'ROOT', route.root)
    monkeypatch.setattr(cache, 'CACHE', route.root / 'cache')
    monkeypatch.setattr(cache, '_rules_receipt', lambda *_: [['fixture', 'rules']])
    monkeypatch.setattr(cache, '_live_build_marker', lambda: None)
    return cache, row, obj


def test_actual_archive_route_publication_record_and_fresh_cache_hit(route, monkeypatch):
    import json
    cache, row, obj = cache_route(route, monkeypatch)
    payload = cache._payload(row, {}, {})
    assert payload['verification']['raw_concrete'] == 2
    assert payload['verification']['independently_bound'] == 4
    assert len(payload['verification']['archive_sha256']) == 64
    assert len(payload['verification']['member_sha256']) == 64
    manifest = route.root / 'manifest.json'
    manifest.write_text(json.dumps({'version': cache.VERSION, 'commit': 'fixture', 'rows': [row]}))
    monkeypatch.setattr(cache, 'exact_worktree', lambda _: None)
    # Fixture image supplies only route bytes, not unrelated strings/constants.
    for check in ('verify_baseline', 'verify_string_refs', 'verify_constant_refs',
                  'verify_dir32_addresses', 'verify_dir32_consistency'):
        monkeypatch.setattr(build, check, lambda *a, **kw: None)
    cache.record(manifest)
    key = cache._key(payload)
    entry = cache._load_entry(key)
    assert cache._entry_is_valid(entry, cache._payload(row, {}, {}))
    entry['payload']['verification']['independently_bound'] = 0
    cache._entry_path(key).write_text(json.dumps(entry))
    assert cache._load_entry(key) is None
    route.path.write_bytes(route.path.read_bytes() + b'archive drift')
    assert cache._payload(row, {}, {}) is None


def test_publication_cache_rejects_ordinary_thin_member(route, monkeypatch):
    import json
    cache, row, obj = cache_route(route, monkeypatch)
    row['notes'] = NOTES
    assert cache._payload(row, {}, {}) is None
    manifest = route.root / 'manifest.json'
    manifest.write_text(json.dumps({'version': cache.VERSION, 'commit': 'fixture', 'rows': [row]}))
    monkeypatch.setattr(cache, 'exact_worktree', lambda _: None)
    for check in ('verify_baseline', 'verify_string_refs', 'verify_constant_refs',
                  'verify_dir32_addresses', 'verify_dir32_consistency'):
        monkeypatch.setattr(build, check, lambda *a, **kw: None)
    with pytest.raises(RuntimeError, match='post-verification evidence failed'):
        cache.record(manifest)


@pytest.mark.parametrize('change', ['missing_route', 'incomplete_route', 'wrong_bound',
                                  'wrong_raw', 'wrong_resolved', 'wrong_reloc', 'malformed_reloc', 'wrong_hash'])
def test_shared_eligibility_rejects_corrupted_structural_dictionary(route, monkeypatch, change):
    row = runtime_row(route, monkeypatch)
    obj = route.root / 'native.obj'
    obj.write_bytes(coff(route.sections, route.symbols))
    patch = build.compile_function(row, {}, obj)
    assert build.verified_patch_eligible(patch, patch['target'])
    if change == 'missing_route': patch['structural_route'] = None
    elif change == 'incomplete_route': patch['structural_route'] = {'verified': True}
    elif change == 'wrong_bound': patch['independently_bound'] = 3
    elif change == 'wrong_raw': patch['structural_route']['raw'] = b'\x90' * 6
    elif change == 'wrong_resolved': patch['structural_route']['bytes'] = b'\x90' * 6
    elif change == 'wrong_reloc': patch['relocs'] = []
    elif change == 'malformed_reloc': patch['structural_route']['relocs'] = [None]
    elif change == 'wrong_hash': patch['structural_route']['archive_sha256'] = 'invalid'
    assert not build.verified_patch_eligible(patch, patch['target'])
