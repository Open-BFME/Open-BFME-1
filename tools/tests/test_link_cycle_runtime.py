"""BFME1 CRT/import setup controls; donor evidence: BFME2 runtime-link-20261017."""
import hashlib
import os
from pathlib import Path
import shutil
import struct
import subprocess
import sys

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_cycle as lc
from test_link_cycle_identity import TEXT, emit

ENTRIES = {"kernel32.dll": ["Sleep@4"]}
SLOT, RVA = 0x3000, 0x1000


def thunk_object(path, *, code=b"\xff\x25" + bytes(4), target="__imp__Sleep@4", refs=()):
    sections = [{"name": ".text", "flags": TEXT, "body": code,
                 "relocs": [(2, target, lc.DIR32)]}]
    if refs:
        sections.append({"name": ".data", "flags": 0xC0300040, "body": bytes(4 * len(refs)),
                         "relocs": [(4 * i, name, lc.DIR32) for i, name in enumerate(refs)]})
    path.write_bytes(emit(sections, [{"name": "_Sleep@4", "sec": 0}, {"name": target}]
                          + [{"name": name} for name in refs]))
    return path


def thunk_row(path, **changes):
    return dict({"name": "_Sleep@4", "target_rva": f"0x{RVA:08X}", "target_size": "6",
                 "source": "game/NativeSleep.cpp", "notes": "", "object": path}, **changes)


def native_proof(rows, paths, monkeypatch, *, identity=("kernel32.dll", "Sleep"), original=None):
    monkeypatch.setattr(lc, "row_obj", lambda row: row["object"])
    retail = bytearray(0x4000)
    retail[RVA:RVA + 6] = original if original is not None else b"\xff\x25" + struct.pack("<I", lc.BASE + SLOT)
    return lc.native_import_thunks(rows, lc.Objects(paths), retail, {SLOT: identity}, ENTRIES)


def test_native_import_thunks_require_the_actual_retail_import(tmp_path, monkeypatch):
    obj = thunk_object(tmp_path / "native.obj")
    assert native_proof([thunk_row(obj)], [obj], monkeypatch) == {"_Sleep@4"}
    for identity in (("user32.dll", "Sleep"), ("kernel32.dll", "SleepEx")):
        assert native_proof([thunk_row(obj)], [obj], monkeypatch, identity=identity) == set()
    for original in (b"\xff\x25" + struct.pack("<I", lc.BASE + SLOT + 4), b"\x90" * 6):
        assert native_proof([thunk_row(obj)], [obj], monkeypatch, original=original) == set()


@pytest.mark.parametrize("change", [{"target_size": "5"}, {"notes": "gen-import"},
                                    {"name": "_Other@4"}])
def test_native_import_thunks_require_their_own_source_extent(tmp_path, monkeypatch, change):
    obj = thunk_object(tmp_path / "native.obj")
    assert native_proof([thunk_row(obj, **change)], [obj], monkeypatch) == set()


@pytest.mark.parametrize("code,target", [(b"\xff\x25\x04\0\0\0", "__imp__Sleep@4"),
                                         (b"\xff\x25" + bytes(4), "__imp__SleepEx@8"),
                                         (b"\xe9" + bytes(5), "__imp__Sleep@4")])
def test_native_import_thunks_reject_addends_and_wrong_providers(tmp_path, monkeypatch, code, target):
    obj = thunk_object(tmp_path / "native.obj", code=code, target=target)
    assert native_proof([thunk_row(obj)], [obj], monkeypatch) == set()


def test_native_import_thunks_do_not_hide_unproved_competing_definitions(tmp_path, monkeypatch):
    obj = thunk_object(tmp_path / "native.obj")
    other = thunk_object(tmp_path / "unrowed.obj")
    assert native_proof([thunk_row(obj)], [obj, other], monkeypatch) == set()
    assert native_proof([thunk_row(obj), thunk_row(obj)], [obj], monkeypatch) == set()
    assert native_proof([thunk_row(obj), thunk_row(other)], [obj, other], monkeypatch) == {"_Sleep@4"}
    for section in (0, -1):
        common = lc.write_coff(tmp_path / "non-code.obj", [], [("_Sleep@4", section, 4, lc.EXTERNAL)])
        assert native_proof([thunk_row(obj)], [obj, common], monkeypatch) == set()


def test_runtime_libraries_are_shipped_md_providers(tmp_path, monkeypatch):
    monkeypatch.setattr(lc.build, "vc71_root", lambda: tmp_path)
    assert lc.runtime_libraries() == [tmp_path / "Vc7/lib/msvcrt.lib", tmp_path / "Vc7/lib/oldnames.lib"]


def test_import_libraries_only_omit_thunks_with_proved_owners(tmp_path, monkeypatch):
    def run(command, **kwargs):
        Path(next(arg[5:] for arg in command if arg.startswith("/OUT:"))).write_bytes(b"!<arch>\n")
        return subprocess.CompletedProcess(command, 0, "", "")
    monkeypatch.setattr(lc.subprocess, "run", run)
    monkeypatch.setattr(lc.build, "vc71_root", lambda: tmp_path)
    monkeypatch.setattr(lc.build, "compiler_environment", lambda root: {})
    lc.make_import_libs({"test.dll": ["Foo@4", "_bar", "?cpp@@YAXXZ", "Unowned@0"]}, tmp_path,
                        {"_Foo@4", "__bar", "?cpp@@YAXXZ"})
    assert (tmp_path / "imp_test.def").read_text() == (
        "LIBRARY test.dll\nEXPORTS\n  Foo@4 DATA\n  _bar DATA\n  ?cpp@@YAXXZ DATA\n  Unowned@0\n")


def test_stdcall_import_rewrite_preserves_offsets_and_data_type(tmp_path):
    def member(symbol, kind):
        payload = struct.pack("<HHHHIIHH", 0, 0xffff, 0, 0x14c, 0,
                              len(symbol) + 1 + len("test.dll") + 1, 0, kind)
        payload += symbol.encode() + b"\0test.dll\0"
        header = b"test.dll/".ljust(16) + b"0".ljust(12) + b"0".ljust(6) * 2
        header += b"0".ljust(8) + str(len(payload)).encode().ljust(10) + b"`\n"
        return header + payload + (b"\n" if len(payload) & 1 else b"")
    raw = b"!<arch>\n" + member("_Foo@4", (2 << 2) | 1)
    raw += member("_Bar@8", 2 << 2) + member("?cpp@@YAXXZ", 1 << 2)
    path = tmp_path / "imports.lib"
    path.write_bytes(raw)
    lc.undecorate_stdcall_imports(path)
    changed = path.read_bytes()
    differences = [i for i, (a, b) in enumerate(zip(raw, changed)) if a != b]
    assert len(changed) == len(raw) and len(differences) == 2
    assert all(raw[i] ^ changed[i] == 4 for i in differences)
    assert struct.unpack_from("<H", changed, 8 + 60 + 18)[0] == (3 << 2) | 1
    lc.undecorate_stdcall_imports(path)
    assert path.read_bytes() == changed


def test_native_thunk_and_crt_statics_link_without_force_at_both_bases(tmp_path, monkeypatch):
    if sys.platform != "win32" and not shutil.which("wine"):
        pytest.skip("requires the committed MSVC/Wine toolchain")
    import pefile
    refs = ["__fltused", "___security_cookie", "__except_handler3", "_strcmpi"]
    obj = thunk_object(tmp_path / "probe.obj", refs=refs)
    root = lc.build.vc71_root()
    original = {path: hashlib.sha256(path.read_bytes()).hexdigest() for path in lc.runtime_libraries()}
    retail_imports = {(dll.lower(), name) for dll, name, _ in lc.census._retail_import_entries()}

    def link(libs, label, base=lc.BASE):
        target = tmp_path / (label + ".dll")
        command = [str(root / "Vc7/bin/link.exe"), "/NOLOGO", "/DLL", "/NOENTRY", "/NODEFAULTLIB",
                   "/MACHINE:X86", "/OPT:NOREF", "/OPT:NOICF", f"/BASE:{base}", "/OUT:" + target.name,
                   "/MAP:" + label + ".map", obj.name]
        command += [os.path.relpath(path, tmp_path) for path in libs]
        if sys.platform != "win32":
            command.insert(0, "wine")
        result = subprocess.run(command, cwd=tmp_path, env=lc.build.compiler_environment(root),
                                capture_output=True, text=True, errors="replace")
        (tmp_path / (label + ".log")).write_text(result.stdout + result.stderr)
        assert not any(arg.upper().startswith(("/FORCE", "/ALTERNATENAME")) for arg in command)
        return result, target

    before = tmp_path / "before"
    before.mkdir()
    code_libs = lc.make_import_libs(ENTRIES, before)
    result, _ = link(code_libs, "missing-runtime-and-duplicate")
    assert result.returncode != 0
    assert "LNK2005" in result.stdout and "__fltused" in result.stdout
    result, _ = link(code_libs + lc.runtime_libraries(), "duplicate-with-runtime")
    assert result.returncode != 0 and "LNK2005" in result.stdout
    assert "unresolved external symbol __fltused" not in result.stdout

    after = tmp_path / "after"
    after.mkdir()
    proved = native_proof([thunk_row(obj)], [obj], monkeypatch)
    assert proved == {"_Sleep@4"}
    iat_libs = lc.make_import_libs(ENTRIES, after, proved)
    result, _ = link(iat_libs, "missing-runtime")
    assert result.returncode != 0 and "__fltused" in result.stdout and "LNK2005" not in result.stdout
    images = []
    for label, base in (("native-base", lc.BASE), ("shifted-base", lc.SHIFT_BASE)):
        result, target = link(iat_libs + lc.runtime_libraries(), label, base)
        assert result.returncode == 0, result.stdout + result.stderr
        assert "LNK2005" not in result.stdout and "LNK4006" not in result.stdout
        image = pefile.PE(str(target))
        assert image.OPTIONAL_HEADER.ImageBase == base
        assert any(d.dll.lower() == b"kernel32.dll" and any(i.name == b"Sleep" for i in d.imports)
                   for d in image.DIRECTORY_ENTRY_IMPORT)
        selected_imports = {(d.dll.decode("latin-1").lower(), i.name.decode("latin-1"))
                            for d in image.DIRECTORY_ENTRY_IMPORT for i in d.imports}
        assert selected_imports <= retail_imports
        assert ("kernel32.dll", "Sleep@4") not in selected_imports
        images.append(image)
    first, shifted = images
    assert [(s.Name, s.VirtualAddress, s.Misc_VirtualSize) for s in first.sections] == [
        (s.Name, s.VirtualAddress, s.Misc_VirtualSize) for s in shifted.sections]
    a, b = first.get_memory_mapped_image(), shifted.get_memory_mapped_image()
    delta = lc.SHIFT_BASE - lc.BASE
    covered = set()
    for block in first.DIRECTORY_ENTRY_BASERELOC:
        for entry in block.entries:
            if entry.type == pefile.RELOCATION_TYPE["IMAGE_REL_BASED_HIGHLOW"]:
                assert struct.unpack_from("<I", b, entry.rva)[0] == struct.unpack_from("<I", a, entry.rva)[0] + delta
                covered.update(range(entry.rva, entry.rva + 4))
    for section in first.sections:
        if section.Name.rstrip(b"\0") not in (b".text", b".data"):
            continue
        for rva in range(section.VirtualAddress, section.VirtualAddress + section.Misc_VirtualSize):
            if rva not in covered:
                assert a[rva] == b[rva]
    assert original == {path: hashlib.sha256(path.read_bytes()).hexdigest() for path in original}
