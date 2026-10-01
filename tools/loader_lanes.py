#!/usr/bin/env python3
"""Loader lanes: what the Windows loader reads from an image, retail vs a link.

Each lane gets a status against retail: `matched`, `mismatched`, `partial`
(what was compared agrees, some part was not compared -- the report says
which) or `unknown` (no linked image given). Lanes:

  headers      optional-header fields the loader acts on (base, alignment,
               subsystem, stack/heap, characteristics, DLL characteristics)
  imports      DLL descriptor order and each DLL's function order; hints are
               listed but not judged (they come from whichever import library
               version is linked and only speed up the lookup)
  exports      names, ordinals (retail: sorted-name order, 1,818 names over
               1,820 ordinals) and the directory's module name; export
               TARGETS are not compared here, so equal names give `partial`
  resources    every (type, name, language) leaf, size and sha256
  stlport      the STLPORT_ section: presence, flags, dword count, nonzero
               dwords (its entries are pointers, so bytes are not compared)
  tls, load_config, base_relocs, delay_imports, bound_imports, com
               retail has none: a linked image must have none either.
               load_config also decides SafeSEH: with no load config there is
               no handler table. link.exe 7.1 adds msvcrt.lib's loadcfg.obj
               (72 bytes) when every input is SafeSEH-compatible, and not with
               /SAFESEH:NO or one input lacking @feat.00 (measured in
               tools/tests/test_loader_lanes.py); a relink passes /SAFESEH:NO
  debug        CodeView entry and PDB path (informational: never judged)

  python3 tools/loader_lanes.py                    # retail -> build/startup/loader_retail.json
  python3 tools/loader_lanes.py --exe linked.exe   # + per-lane verdicts -> loader_compare.json
  python3 tools/loader_lanes.py --write-res F.res  # retail .rsrc as a .res file link.exe accepts
  python3 tools/loader_lanes.py --write-import-libs DIR   # an import library per retail
                               # DLL the toolchain lacks (mss32, DINPUT8), retail's names/hints

The .res and .lib outputs are generated inputs for a relink, not progress.
"""
import argparse
import hashlib
import json
import shutil
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402

OUT = ROOT / "build" / "startup"
SDK_LIBS = [build.DEFAULT_VC71_ROOT / "Vc7" / "PlatformSDK" / "Lib", build.DEFAULT_VC71_ROOT / "Vc7" / "lib"] \
    if hasattr(build, "DEFAULT_VC71_ROOT") else []
HEADER_FIELDS = ("ImageBase", "SectionAlignment", "FileAlignment", "Subsystem", "MajorSubsystemVersion",
                 "MinorSubsystemVersion", "MajorOperatingSystemVersion", "SizeOfStackReserve",
                 "SizeOfStackCommit", "SizeOfHeapReserve", "SizeOfHeapCommit", "DllCharacteristics")
ABSENT_DIRS = {"tls": 9, "load_config": 10, "base_relocs": 5, "bound_imports": 11, "delay_imports": 13,
               "com": 14}


def load(path):
    import pefile
    return pefile.PE(str(path))


def facts(pe):
    """Everything the lanes compare, as plain data."""
    oh = pe.OPTIONAL_HEADER
    out = {"headers": {f: getattr(oh, f) for f in HEADER_FIELDS}}
    out["headers"]["Characteristics"] = pe.FILE_HEADER.Characteristics
    out["directories"] = {name: oh.DATA_DIRECTORY[i].Size for name, i in ABSENT_DIRS.items()}
    imports = []
    for entry in getattr(pe, "DIRECTORY_ENTRY_IMPORT", []):
        imports.append({"dll": entry.dll.decode("latin-1"),
                        "names": [(i.name.decode("latin-1") if i.name else f"#{i.ordinal}") for i in entry.imports],
                        "hints": [i.hint for i in entry.imports]})
    out["imports"] = imports
    exports = {"module": None, "symbols": [], "ordinal_slots": 0}
    if hasattr(pe, "DIRECTORY_ENTRY_EXPORT"):
        ex = pe.DIRECTORY_ENTRY_EXPORT
        exports["module"] = pe.get_string_at_rva(ex.struct.Name).decode("latin-1")
        exports["ordinal_slots"] = ex.struct.NumberOfFunctions
        exports["symbols"] = sorted(((s.name.decode("latin-1") if s.name else None, s.ordinal)
                                     for s in ex.symbols), key=lambda t: t[1])
    out["exports"] = exports
    leaves = []
    if hasattr(pe, "DIRECTORY_ENTRY_RESOURCE"):
        for t in pe.DIRECTORY_ENTRY_RESOURCE.entries:
            for n in t.directory.entries:
                for lang in n.directory.entries:
                    data = pe.get_data(lang.data.struct.OffsetToData, lang.data.struct.Size)
                    leaves.append({"type": t.id if t.id is not None else str(t.name),
                                   "name": n.id if n.id is not None else str(n.name), "lang": lang.id,
                                   "codepage": lang.data.struct.CodePage, "size": len(data),
                                   "sha256": hashlib.sha256(data).hexdigest()})
    out["resources"] = leaves
    stl = None
    for s in pe.sections:
        if s.Name.rstrip(b"\0").startswith(b"STLPORT"):
            body = s.get_data()[:s.Misc_VirtualSize]
            words = [struct.unpack_from("<I", body, o)[0] for o in range(0, len(body) - 3, 4)]
            stl = {"virtual_size": s.Misc_VirtualSize, "characteristics": s.Characteristics,
                   "nonzero_dwords": sum(1 for w in words if w)}
    out["stlport"] = stl
    debug = []
    for d in getattr(pe, "DIRECTORY_ENTRY_DEBUG", []):
        pdb = getattr(d.entry, "PdbFileName", b"") if d.entry else b""
        debug.append({"type": d.struct.Type, "pdb": pdb.rstrip(b"\0").decode("latin-1")})
    out["debug"] = debug
    return out


def compare(retail, linked):
    """{lane: {status, detail}}; `linked` None gives every lane `unknown`."""
    lanes = {}

    def put(lane, status, **detail):
        lanes[lane] = {"status": status, **detail}

    if linked is None:
        for lane in ("headers", "imports", "exports", "resources", "stlport", *ABSENT_DIRS, "debug"):
            put(lane, "unknown")
        return lanes
    diffs = {f: [retail["headers"][f], linked["headers"][f]] for f in retail["headers"]
             if retail["headers"][f] != linked["headers"][f]}
    put("headers", "matched" if not diffs else "mismatched", differences=diffs)

    r_dlls = [i["dll"].lower() for i in retail["imports"]]
    l_dlls = [i["dll"].lower() for i in linked["imports"]]
    per_dll = {}
    l_by = {i["dll"].lower(): i for i in linked["imports"]}
    for imp in retail["imports"]:
        other = l_by.get(imp["dll"].lower())
        if other is None:
            per_dll[imp["dll"]] = "absent"
        elif other["names"] != imp["names"]:
            missing = [n for n in imp["names"] if n not in other["names"]]
            extra = [n for n in other["names"] if n not in imp["names"]]
            per_dll[imp["dll"]] = {"missing": missing, "extra": extra,
                                   "order_only": not missing and not extra}
    extra_dlls = [d for d in l_dlls if d not in r_dlls]
    hint_diffs = sum(1 for imp in retail["imports"] if imp["dll"].lower() in l_by
                     and l_by[imp["dll"].lower()]["names"] == imp["names"]
                     and l_by[imp["dll"].lower()]["hints"] != imp["hints"])
    ok = r_dlls == l_dlls and not per_dll
    put("imports", "matched" if ok else "mismatched", dll_order_equal=r_dlls == l_dlls, retail_dlls=r_dlls,
        linked_dlls=l_dlls, extra_dlls=extra_dlls, per_dll=per_dll, dlls_with_hint_differences=hint_diffs)

    r_ex, l_ex = retail["exports"], linked["exports"]
    r_names = {n for n, _ in r_ex["symbols"]}
    l_names = {n for n, _ in l_ex["symbols"]}
    same = r_ex["symbols"] == l_ex["symbols"] and r_ex["module"] == l_ex["module"] \
        and r_ex["ordinal_slots"] == l_ex["ordinal_slots"]
    put("exports", "partial" if same else "mismatched", not_compared="export targets",
        retail_count=len(r_ex["symbols"]), linked_count=len(l_ex["symbols"]),
        missing=len(r_names - l_names), extra=len(l_names - r_names),
        missing_sample=sorted(r_names - l_names)[:20], module=[r_ex["module"], l_ex["module"]],
        ordinal_slots=[r_ex["ordinal_slots"], l_ex["ordinal_slots"]])

    put("resources", "matched" if retail["resources"] == linked["resources"] else "mismatched",
        retail=len(retail["resources"]), linked=len(linked["resources"]))

    rs, ls = retail["stlport"], linked["stlport"]
    if rs is None or ls is None:
        put("stlport", "matched" if rs == ls else "mismatched", retail=rs, linked=ls)
    else:
        same = rs["characteristics"] == ls["characteristics"] and rs["nonzero_dwords"] == ls["nonzero_dwords"]
        put("stlport", "partial" if same else "mismatched", not_compared="pointer targets", retail=rs, linked=ls)

    for lane in ABSENT_DIRS:
        r, l = retail["directories"][lane], linked["directories"][lane]
        put(lane, "matched" if r == l == 0 else ("mismatched" if r != l else "partial"), retail_size=r,
            linked_size=l)
    put("debug", "informational", retail=retail["debug"], linked=linked["debug"])
    return lanes


# --------------------------------------------------------------------------- generators

def resource_leaves(pe):
    """[(type, name, lang, data)] of the retail resource tree, numeric ids only."""
    leaves = []
    for t in pe.DIRECTORY_ENTRY_RESOURCE.entries:
        for n in t.directory.entries:
            for lang in n.directory.entries:
                if t.id is None or n.id is None:
                    raise SystemExit("loader_lanes: named resources are not supported by --write-res")
                leaves.append((t.id, n.id, lang.id, pe.get_data(lang.data.struct.OffsetToData,
                                                                 lang.data.struct.Size)))
    return leaves


def res_bytes(leaves):
    """A Win32 .res file: the empty header record, then one record per leaf
    (numeric type and name, MEMORYFLAGS 0x1010 as rc writes for icons)."""
    out = bytearray(struct.pack("<IIHHHHIHHII", 0, 0x20, 0xFFFF, 0, 0xFFFF, 0, 0, 0, 0, 0, 0))
    for typ, name, lang, data in leaves:
        header = struct.pack("<HHHH", 0xFFFF, typ, 0xFFFF, name) + struct.pack("<IHHII", 0, 0x1010, lang, 0, 0)
        out += struct.pack("<II", len(data), 8 + len(header)) + header + data
        out += b"\0" * (-len(out) % 4)
    return bytes(out)


def import_libraries():
    """Lower-case stems of every import library the toolchain ships."""
    root = build.vc71_root()
    stems = set()
    for folder in (root / "Vc7" / "PlatformSDK" / "Lib", root / "Vc7" / "lib"):
        if folder.exists():
            stems |= {p.stem.lower() for p in folder.iterdir() if p.suffix.lower() == ".lib"}
    return stems


# Retail imports these by an undecorated name; the symbol game code references
# carries the stdcall suffix from the SDK prototype.
IMPORT_SYMBOLS = {
    # dinput.h: HRESULT WINAPI DirectInput8Create(HINSTANCE, DWORD, REFIID, LPVOID *, LPUNKNOWN)
    "DirectInput8Create": "_DirectInput8Create@20",
}
NAME_TYPE_SHIFT, NAME_TYPE_MASK = 2, 0x1C
IMPORT_NAME, IMPORT_NOPREFIX, IMPORT_UNDECORATE = 1, 2, 3
NUL = bytes(1)


def import_symbol(name):
    """The C symbol (without __imp_) that imports retail's `name`."""
    if name in IMPORT_SYMBOLS:
        return IMPORT_SYMBOLS[name]
    return name if name.startswith("_") else "_" + name


def name_type(symbol, name):
    """The import-object name type under which the loader sees `name` for `symbol`."""
    if name == symbol:
        return IMPORT_NAME
    bare = symbol.lstrip("_?@")
    if name == bare:
        return IMPORT_NOPREFIX
    if name == bare.split("@")[0]:
        return IMPORT_UNDECORATE
    raise ValueError(f"no import name type turns {symbol} into {name}")


def write_import_lib(dll, names, hints, out):
    """An import library for `dll` whose objects import exactly `names` with
    retail's hints: lib.exe /DEF makes the short import objects, then each
    one's name type and hint are set to what retail's import table records."""
    import subprocess
    import tempfile
    root = build.vc71_root()
    env = build.compiler_environment(root, None)
    want = {import_symbol(n): (n, h) for n, h in zip(names, hints)}
    deffile = out.with_suffix(".def")
    lines = [f"LIBRARY {dll}", "EXPORTS"] + [f"    {s[1:]}" for s in want]
    deffile.write_text("\n".join(lines) + "\n", encoding="ascii")
    command = [str(root / "Vc7" / "bin" / "lib.exe"), "/NOLOGO", "/MACHINE:X86"]
    if sys.platform == "win32":
        command += [f"/DEF:{deffile.resolve()}", f"/OUT:{out.resolve()}"]
    else:
        wine = shutil.which("wine")
        if wine is None:
            raise SystemExit("wine not found. Install Wine to run MSVC 7.1 on this host.")
        command.insert(0, wine)
        command += [f"/DEF:{build.wine_path(deffile.resolve())}", f"/OUT:{build.wine_path(out.resolve())}"]
    out.unlink(missing_ok=True)
    # Wine services may retain standard handles after lib.exe exits. Regular
    # files let us wait for the direct child without waiting for pipe EOF.
    with tempfile.TemporaryFile() as stdout, tempfile.TemporaryFile() as stderr:
        proc = subprocess.run(command, stdout=stdout, stderr=stderr, env=env, cwd=ROOT)
        stdout.seek(0)
        stderr.seek(0)
        diagnostics = (stdout.read() + stderr.read()).decode("latin-1", errors="replace")
    if proc.returncode:
        raise SystemExit(f"lib.exe failed for {dll} (exit {proc.returncode}): {diagnostics}")
    if not out.is_file():
        raise SystemExit(f"{dll}: lib.exe succeeded without producing {out}: {diagnostics}")
    data = bytearray(out.read_bytes())
    if not data.startswith(b"!<arch>\n"):
        raise SystemExit(f"{dll}: lib.exe output is not an archive: {out}")
    offset, patched = 8, set()
    while offset + 60 <= len(data):
        size = int(data[offset + 48:offset + 58].decode("latin-1").strip())
        body = offset + 60
        sig1, sig2 = struct.unpack_from("<HH", data, body)
        if sig1 == 0 and sig2 == 0xFFFF:
            symbol = data[body + 20:data.index(NUL, body + 20)].decode("latin-1")
            if symbol in want:
                name, hint = want[symbol]
                kind = struct.unpack_from("<H", data, body + 18)[0]
                kind = (kind & ~NAME_TYPE_MASK) | (name_type(symbol, name) << NAME_TYPE_SHIFT)
                struct.pack_into("<HH", data, body + 16, hint, kind)
                patched.add(symbol)
        offset = body + size + (size & 1)
    if patched != set(want):
        raise SystemExit(f"{dll}: lib.exe made no import object for {sorted(set(want) - patched)}")
    out.write_bytes(bytes(data))
    return out


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--exe", type=Path, help="linked image to compare")
    ap.add_argument("--out", type=Path, default=OUT)
    ap.add_argument("--write-res", type=Path)
    ap.add_argument("--write-import-libs", type=Path)
    args = ap.parse_args(argv)
    args.out.mkdir(parents=True, exist_ok=True)
    retail_pe = load(build.EXE)
    retail = facts(retail_pe)
    (args.out / "loader_retail.json").write_text(json.dumps(retail, indent=1), encoding="utf-8")
    if args.write_res:
        args.write_res.write_bytes(res_bytes(resource_leaves(retail_pe)))
        print(f"wrote {args.write_res}")
    if args.write_import_libs:
        args.write_import_libs.mkdir(parents=True, exist_ok=True)
        have = import_libraries()
        for imp in retail["imports"]:
            stem = imp["dll"].rsplit(".", 1)[0].lower()
            # AVIFIL32 comes from vfw32.lib, MSVCR71 from msvcrt.lib
            if stem in have or (stem == "avifil32" and "vfw32" in have) or stem == "msvcr71":
                continue
            path = write_import_lib(imp["dll"], imp["names"], imp["hints"], args.write_import_libs / f"{stem}.lib")
            print(f"wrote {path} ({len(imp['names'])} imports)")
    linked = facts(load(args.exe)) if args.exe else None
    lanes = compare(retail, linked)
    (args.out / "loader_compare.json").write_text(json.dumps(lanes, indent=1), encoding="utf-8")
    for lane, verdict in lanes.items():
        print(f"{lane:14} {verdict['status']}")
    return 0 if all(v["status"] in ("matched", "informational") for v in lanes.values()) else 1


if __name__ == "__main__":
    sys.exit(main())
