#!/usr/bin/env python3
"""Import binding: make a TU's imports link against retail's real import table.

The byte gate masks every DIR32 operand, so `call [__imp__Anything]` matches
retail whatever the declaration is called. A strict link is not so kind: the
import libraries define exactly one `__imp_` name per imported function, and
defining a function's own name in a TU collides with the call stub the same
import-library member carries. Measured on the 2026-09-30 trial link: 491
unresolved `__imp_` names.

Every `__imp_` reference an object emits falls in one class:

  correct      an import library defines it, retail imports that function, and
               any witness (dir32_addresses.csv, a symbols.csv pin, an Rva token
               in the name) agrees on the IAT slot
  alias        no import library defines it for a retail import, but a witness
               puts it on exactly one retail IAT slot: WRONG-NAME (same DLL) or
               WRONG-DLL (the spelling belongs to another DLL's import).
               Repairable: spell the slot's real import
  wrong-slot   a real import name whose witness is a different slot: the
               source calls the wrong function. Never rewritten here
  not-iat      the witness address is not an IAT slot (a function-pointer
               global declared dllimport). Not an import; out of scope
  conflict     witnesses disagree. Refused
  invented     no import and no witness. Refused: nothing proves which slot
               it means, and aliasing it to a similar name is a guess
  owned-iat    a source-defined import-address cell whose native name or DIR32
               witness proves a retail IAT slot. Refused: the native import
               library must provide the cell; STATIC cells need a DIR32 witness

and a definition in one of our objects of a name that an import library also
defines as the call stub of a retail import is a DUPLICATE THUNK: it links only
under /FORCE. Its address-owned name is `?j_XXXXXXXX@@YAXXZ` (AGENTS.md) when
the body is the 6-byte `jmp [slot]`, else `RvaXXXXXXXX_<name>`.

  python3 tools/import_binding.py measure [--objects RSP] [--json OUT]
  python3 tools/import_binding.py next [--objects RSP]    # one repairable TU and its plan
  python3 tools/import_binding.py apply <source>          # rewrite its import declarations
  python3 tools/import_binding.py check <source>          # rebuild, bind, strict link; PASS/FAIL + receipt

`check` compiles the TU with build.py (the scoped byte gate), then requires
of the fresh object: no alias/invented/conflict/wrong-slot import and no
duplicate thunk; every DIR32 site of every matched row that reads an
`__imp_` name reads, in retail, the IAT slot of that name's real import; and
a link with no /FORCE, /NODEFAULTLIB, against the retail import libraries
(data_scaffold.retail_libraries) plus labelled link-only stubs for every
non-import external, succeeds and imports only what retail imports, from the
same DLL. Stubs never define an `__imp_` name or an import library's call
stub, so an import can only be resolved by the real library. Receipt:
build/import_binding/<build.py object stem>/receipt.json.
"""
import argparse
import collections
import csv
import hashlib
import json
import os
import re
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402

OUT = ROOT / "build" / "import_binding"
BASE = 0x400000
DIR32 = 0x0006
EXTERNAL, STATIC, WEAK_EXTERNAL = 2, 3, 105
RVA_TOKEN = re.compile(r"Rva([0-9A-Fa-f]{8})")
DECL = re.compile(r'(?m)^[ \t]*[^;{}\n/"]*(?:"C"[^;{}\n/"]*)?__declspec\s*\(\s*dllimport\s*\)[^;{}]*;')
NOT_CODE = re.compile(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\\n])*"|' + r"'(?:\\.|[^'\\\n])*'", re.S)
GENERATED = ("game/gen_asm/", "game/gen_small/")


def editable(source):
    """False for a generated source: AGENTS.md forbids hand edits under game/gen_asm and game/gen_small."""
    return bool(source) and not source.replace("\\", "/").startswith(GENERATED)


def sub_code(old, new, text):
    """Rename the identifier `old` to `new` outside comments and literals."""
    pattern = re.compile(rf"\b{re.escape(old)}\b")
    out, at = [], 0
    for m in NOT_CODE.finditer(text):
        out.append(pattern.sub(new, text[at:m.start()]))
        out.append(m.group(0))
        at = m.end()
    out.append(pattern.sub(new, text[at:]))
    return "".join(out)


def in_code(old, text):
    return sub_code(old, "@", text) != text


# ---------------------------------------------------------------- retail facts
def retail_slots():
    """{slot rva: (dll lower, imported name)} from retail's import directory."""
    import link_census
    return {slot: (dll.lower(), name) for dll, name, slot in link_census._retail_import_entries()}


def short_imports(path):
    """[(symbol, dll lower, imported name, type)] for every short import object
    of an import library (type 0 code, 1 data, 2 const). The imported name
    follows the name type, as link_census.library_import_thunks reads it."""
    data, at, out = path.read_bytes(), 8, []
    while at + 60 <= len(data):
        try:
            size = int(data[at + 48:at + 58].decode("ascii").strip())
        except ValueError:
            break
        body = data[at + 60:at + 60 + size]
        if body[:4] == b"\0\0\xff\xff" and len(body) > 20:
            kind = struct.unpack_from("<H", body, 18)[0]
            end = body.index(b"\0", 20)
            symbol = body[20:end].decode("latin-1")
            dll = body[end + 1:body.index(b"\0", end + 1)].decode("latin-1").lower()
            name_type = (kind >> 2) & 7
            if name_type == 1:
                name = symbol
            elif name_type == 2:
                name = symbol[1:] if symbol[:1] in "?@_" else symbol
            else:
                bare = re.sub(r"@\d+$", "", symbol[1:] if symbol.startswith("_") else symbol)
                name = bare.split("@")[0] if name_type == 3 else bare
            out.append((symbol, dll, name, kind & 3))
        at += 60 + size + (size & 1)
    return out


def weak_aliases(path):
    """{alias: target} for the weak externals of an archive's members.
    oldnames.lib is one: `__imp__stricmp` -> `__imp___stricmp`. Every /MD
    object names it as a default library (.drectve /DEFAULTLIB:OLDNAMES), so
    the real link resolves these; a /NODEFAULTLIB link must list it."""
    data, at, out = path.read_bytes(), 8, {}
    while at + 60 <= len(data):
        size = int(data[at + 48:at + 58].decode("ascii").strip())
        body = data[at + 60:at + 60 + size]
        if len(body) > 20 and body[:4] != b"\0\0\xff\xff" and data[at:at + 2] not in (b"/ ", b"//"):
            try:
                table, _ = struct.unpack_from("<II", body, 8)
                symbols = coff_symbols(body)
            except (struct.error, ValueError):
                symbols = []
            index = {i: name for i, name, _, _, _ in symbols}
            for i, name, _, storage, _ in symbols:
                if storage == WEAK_EXTERNAL:
                    tag = struct.unpack_from("<I", body, table + 18 * (i + 1))[0]
                    out[name] = index.get(tag)
        at += 60 + size + (size & 1)
    return out


def oldnames():
    return build.vc71_root() / "Vc7" / "lib" / "oldnames.lib"


def libraries():
    """Retail's import libraries, as the trial whole-program link uses them,
    plus oldnames.lib (a default library of every /MD object). Generated once
    (data_scaffold.retail_libraries runs lib.exe) and reused: seats run in
    parallel, and regenerating a library another process is linking races."""
    listing = OUT / "libraries.txt"
    if listing.exists():
        paths = [Path(line) for line in listing.read_text(encoding="utf-8").splitlines() if line]
        if all(p.exists() for p in paths):
            return paths + [oldnames()]
    import data_scaffold
    paths, _ = data_scaffold.retail_libraries(OUT)
    paths = [p for p in paths if p.suffix.lower() == ".lib"]
    listing.write_text("".join(f"{p}\n" for p in paths), encoding="utf-8")
    return paths + [oldnames()]


class Imports:
    """What the real import libraries provide, bound to retail's slots."""

    def __init__(self, slots, libs):
        self.slots = slots                          # rva -> (dll, name)
        self.by_import = {v: k for k, v in slots.items()}
        imported = set(slots.values())
        self.imp = {}                               # __imp_X -> (dll, name), retail-imported only
        self.foreign = {}                           # __imp_X a library defines but retail does not import
        self.thunk = {}                             # call stub X -> (dll, name), retail-imported only
        self.canonical = collections.defaultdict(set)   # (dll, name) -> {__imp_X}
        aliases = {}
        for lib in libs:
            if lib == oldnames():
                aliases.update(weak_aliases(lib))
                continue
            for symbol, dll, name, kind in short_imports(lib):
                key = (dll, name)
                if key in imported:
                    self.imp["__imp_" + symbol] = key
                    self.canonical[key].add("__imp_" + symbol)
                    if kind == 0:
                        self.thunk[symbol] = key
                else:
                    self.foreign.setdefault("__imp_" + symbol, key)
        # oldnames: the alias resolves to its target's import; it is never the
        # canonical spelling, and its plain alias is not a call stub definition.
        self.oldnames = {a: t for a, t in aliases.items() if t in self.imp and a not in self.imp}
        for alias, target in self.oldnames.items():
            self.imp[alias] = self.imp[target]

    def spelling(self, slot):
        """The one `__imp_` name the libraries define for a retail slot, or None."""
        names = self.canonical.get(self.slots.get(slot), set())
        return next(iter(names)) if len(names) == 1 else None


# ---------------------------------------------------------------- witnesses
def witnesses(root=ROOT):
    """{__imp_ name: {(source, slot-or-address rva)}} from dir32_addresses.csv
    (VA, recorded by the full gate from matched rows' retail operands) and
    symbols.csv pins (RVA)."""
    found = collections.defaultdict(set)
    with (root / "targets/game/reverse/dir32_addresses.csv").open(newline="", encoding="utf-8") as fh:
        for row in csv.DictReader(fh):
            if row["name"].startswith("__imp_"):
                found[row["name"]].add(("dir32", int(row["va"], 16) - BASE))
    with (root / "targets/game/reverse/symbols.csv").open(newline="", encoding="utf-8") as fh:
        for row in csv.DictReader(fh):
            if row["name"].startswith("__imp_"):
                found[row["name"]].add(("pin", int(row["address"], 16)))
    return found


def name_token(symbol, slots):
    """An Rva token in the name, when it reads as a slot as a VA or an RVA."""
    hits = set()
    for token in RVA_TOKEN.findall(symbol):
        value = int(token, 16)
        for rva in (value - BASE, value):
            if rva in slots:
                hits.add(rva)
    return hits


def site_witnesses(obj, rows):
    """{__imp_ name: {rva}}: for every matched row this object compiles, each
    DIR32 site reading an `__imp_` name gives retail's operand minus the
    compiled addend -- the address retail reads there (build.dir32_references,
    for an explicit object). The strongest witness: the matched body itself."""
    found = collections.defaultdict(set)
    for row in rows:
        size = int(row["target_size"])
        try:
            body, relocs = build.read_object_symbol_bytes(obj, build.ledger_object_symbol(row), size)
        except (ValueError, KeyError, OSError):
            continue
        target = build.read_target_bytes(int(row["target_rva"], 16), size)
        for off, rtype, sym in relocs:
            if rtype == DIR32 and sym.startswith("__imp_") and off + 4 <= min(size, len(body), len(target)):
                va = (struct.unpack_from("<I", target, off)[0] - struct.unpack_from("<I", body, off)[0]) & 0xFFFFFFFF
                found[sym].add(va - BASE)
    return found


def site_counts(obj, rows):
    """{__imp_ name: DIR32 sites inside matched bodies}."""
    counts = collections.Counter()
    for row in rows:
        size = int(row["target_size"])
        try:
            _, relocs = build.read_object_symbol_bytes(obj, build.ledger_object_symbol(row), size)
        except (ValueError, KeyError, OSError):
            continue
        counts.update(sym for off, rtype, sym in relocs
                      if rtype == DIR32 and sym.startswith("__imp_") and off + 4 <= size)
    return counts


def reloc_counts(obj):
    """{__imp_ name: DIR32 sites anywhere in the object}."""
    import reloc_ledger
    sections, symbols = reloc_ledger.parse_coff(obj.read_bytes())
    names = {i: s["name"] for i, s in symbols.items()}
    counts = collections.Counter()
    for section in sections:
        for _, index, rtype in section["relocs"]:
            if rtype == DIR32 and names.get(index, "").startswith("__imp_"):
                counts[names[index]] += 1
    return counts


def classify(symbol, imports, found, sites=None):
    """(class, detail, slot or None) for one `__imp_` name. `sites` are this
    object's own site witnesses (site_witnesses)."""
    slots = imports.slots
    addresses = {rva for _, rva in found.get(symbol, ())}
    site = set((sites or {}).get(symbol, ()))
    pins_as_va = {rva - BASE for kind, rva in found.get(symbol, ()) if kind == "pin" and rva - BASE in slots}
    # A pin written as a VA (0x0135945C for slot 0x00F5945C) is the same slot.
    addresses = {a for a in addresses if a in slots or a - BASE not in slots} | pins_as_va
    addresses |= name_token(symbol, slots) | site
    in_iat = {a for a in addresses if a in slots}
    if symbol in imports.imp:
        real = imports.by_import[imports.imp[symbol]]
        if not addresses or addresses == {real}:
            return "correct", imports.imp[symbol], real
        return "wrong-slot", f"{symbol} imports {imports.imp[symbol]} at {real:#x}; witness {sorted(map(hex, addresses))}", real
    if len(addresses) > 1:
        return "conflict", f"witnesses {sorted(map(hex, addresses))}", None
    if not addresses:
        return "invented", "no import library defines it and nothing witnesses a slot", None
    (slot,) = addresses
    if slot not in in_iat:
        return "not-iat", f"witness {slot:#x} is not a retail IAT slot", None
    dll, name = slots[slot]
    other = imports.foreign.get(symbol)
    bare = symbol[len("__imp_"):]
    bare = re.sub(r"@\d+$", "", bare[1:] if bare.startswith("_") else bare)
    elsewhere = {d for (d, n) in imports.by_import if n == bare and d != dll}
    kind = "alias:wrong-dll" if (other and other[0] != dll) or elsewhere else "alias:wrong-name"
    return kind, f"{dll}!{name}", slot


# ---------------------------------------------------------------- objects
def coff_symbols(data):
    table, count = struct.unpack_from("<II", data, 8)
    strings = table + 18 * count
    out, index = [], 0
    while index < count:
        record = data[table + 18 * index:table + 18 * index + 18]
        if record[:4] == b"\0\0\0\0":
            offset = struct.unpack_from("<I", record, 4)[0]
            name = data[strings + offset:data.index(b"\0", strings + offset)]
        else:
            name = record[:8].rstrip(b"\0")
        value, section, _, storage, aux = struct.unpack_from("<IhHBB", record, 8)
        out.append((index, name.decode("latin-1"), section, storage, value))
        index += 1 + aux
    return out


def external_symbols(records):
    """(undefined, defined) external names; COMMON and ABS are definitions."""
    undefined, defined = set(), set()
    for _, name, section, storage, value in records:
        if storage != EXTERNAL:
            continue
        if section == 0 and value == 0:
            undefined.add(name)
        elif section > 0 or section == -1 or (section == 0 and value > 0):
            defined.add(name)
    return undefined - defined, defined


def object_facts(path):
    """(undefined __imp_ names, defined external names) of one object."""
    data = path.read_bytes()
    if data[:2] != b"\x4c\x01":
        return set(), set()
    undefined, defined = external_symbols(coff_symbols(data))
    return {name for name in undefined if name.startswith("__imp_")}, defined


def static_iat_symbols(path):
    """Defined local __imp_ names, separate from the external-provider API."""
    data = path.read_bytes()
    if data[:2] != b"\x4c\x01":
        return set()
    return {name for _, name, section, storage, _ in coff_symbols(data)
            if storage == STATIC and (section > 0 or section == -1) and name.startswith("__imp_")}


def owned_iat_cells(defined, imports, found, sites, static_defined=()):
    """Source-owned cells proven to denote retail IAT slots. Call only for a
    known source object: import-library members legitimately define cells.
    Pins and name tokens alone do not prove an owned global is an IAT cell.
    Local STATIC cells require an object-local DIR32 witness: the recorded
    global name table has no source provenance for local symbols."""
    cells = {}
    for symbol in sorted(defined | set(static_defined)):
        if not symbol.startswith("__imp_"):
            continue
        slots = set(sites.get(symbol, ()))
        if symbol in defined:
            slots.update(rva for kind, rva in found.get(symbol, ()) if kind == "dir32")
            if symbol in imports.imp:
                slots.add(imports.by_import[imports.imp[symbol]])
        slots.intersection_update(imports.slots)
        if slots:
            cells[symbol] = sorted(slots)
    return cells


def owned_iat_problem(symbol, slots):
    return (f"{symbol}: source object defines a retail import-address cell "
            f"({', '.join(map(hex, slots))}); it must remain undefined for the native import library")


def weak_import_records(obj):
    """Actually relocated source weak imports, with validated direct auxiliaries."""
    try:
        data = obj.read_bytes()
        if data[:2] != b"\x4c\x01":
            return {}
        candidates = {index for index, name, _, storage, _ in coff_symbols(data)
                      if storage == WEAK_EXTERNAL and name.startswith("__imp_")}
        if not candidates:
            return {}
        import link_census
        import reloc_ledger
        records = {r["index"]: r for r in link_census._coff_symbols(data)}
        sections, _ = reloc_ledger.parse_coff(data)
        used = {index for section in sections for _, index, _ in section["relocs"]} & candidates
        table, _ = struct.unpack_from("<II", data, 8)
        routes = {}
        for index in sorted(used):
            record = records[index]
            symbol = record["name"]
            if record["section"] != 0 or record["value"] != 0 or record["aux"] != 1:
                raise Refused(f"{symbol}: malformed weak import record")
            tag, search = struct.unpack_from("<II", data, table + 18 * (index + 1))
            default = records.get(tag)
            if search not in (1, 2, 3) or default is None or tag == index:
                raise Refused(f"{symbol}: invalid weak import auxiliary/default/search")
            if default["storage"] != EXTERNAL or not -1 <= default["section"] <= len(sections):
                raise Refused(f"{symbol}: unsupported weak import default (weak chains remain unproved)")
            routes[symbol] = {"index": index, "tag": tag, "search": search,
                              "default": {k: default[k] for k in ("name", "storage", "section", "value")},
                              "object_sha256": hashlib.sha256(data).hexdigest()}
        if routes and obj.read_bytes() != data:
            raise Refused("source weak import object changed during inspection")
        return routes
    except (OSError, ValueError, KeyError, IndexError, struct.error) as exc:
        raise Refused(f"cannot inspect source weak imports: {exc}") from exc


def weak_import_routes(obj, imports, sites):
    """Defaults are route metadata; only library or matched-site evidence names
    the expected native import. Unrelocated declarations claim no IAT route."""
    records = weak_import_records(obj)
    if not records:
        return {}
    try:
        actual_sites = sites() if callable(sites) else sites
    except (OSError, ValueError, KeyError, IndexError, struct.error) as exc:
        raise Refused(f"cannot inspect source weak import sites: {exc}") from exc
    routes = {}
    for symbol, record in records.items():
        actual = set(actual_sites.get(symbol, ()))
        if symbol in imports.imp:
            expected = imports.imp[symbol]
            slot = imports.by_import[expected]
            if actual and actual != {slot}:
                raise Refused(f"{symbol}: weak import has conflicting matched DIR32 sites")
            origin = "library"
        else:
            if actual and not (actual & imports.slots.keys()):
                continue  # A source-local non-IAT function-pointer route.
            if len(actual) != 1 or next(iter(actual)) not in imports.slots:
                raise Refused(f"{symbol}: weak import has no single object-local retail IAT witness")
            slot = next(iter(actual))
            expected, origin = imports.slots[slot], "matched DIR32"
        routes[symbol] = {**record, "expected": expected, "slot": slot, "expected_from": origin}
    if routes and any(hashlib.sha256(obj.read_bytes()).hexdigest() != r["object_sha256"] for r in routes.values()):
        raise Refused("source weak import object changed during route inspection")
    return routes


def file_digest(path):
    """Hash inputs incrementally, including the matched-row ledger."""
    digest = hashlib.sha256()
    with Path(path).open("rb") as handle:
        for block in iter(lambda: handle.read(1024 * 1024), b""):
            digest.update(block)
    return digest.hexdigest()


def weak_selection_inputs(source, obj):
    """Inputs whose unchanged bytes bind the pending native weak-import proof."""
    libs = libraries()
    paths = [obj, ROOT / source, build.EXE, build.FUNCTIONS, *libs]
    try:
        return libs, {str(path): file_digest(path) for path in paths}
    except OSError as exc:
        raise Refused(f"weak import proof input unavailable: {exc}") from exc


def weak_selected_proof(obj, imports, routes, work, libs, inputs):
    """Audit each required weak primary against this link's MAP and PE IAT.
    Missing primaries never borrow the auxiliary default's selected address."""
    import selected_import_audit as audit
    import pefile
    paths = [work / "after.dll", work / "after.map"]
    native = None
    try:
        if str(obj) not in inputs:
            raise Refused("weak import proof lacks this source object's identity")
        before = {**inputs, **{str(path): file_digest(path) for path in paths}}
        if any(file_digest(path) != digest for path, digest in inputs.items()):
            raise Refused("weak import proof input changed during link")
        library_cells, _ = audit.oracle(imports.slots, libs)
        native = pefile.PE(str(paths[0]), fast_load=True)
        native.parse_data_directories(directories=[pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_IMPORT"]])
        selected = audit.map_symbols(paths[1].read_text(encoding="latin-1").splitlines())
        slots = audit.pe_slots(native)
        bindings = []
        for symbol, route in routes.items():
            expected = tuple(route["expected"])
            if route["expected_from"] == "library":
                identities = library_cells.get(symbol, set())
                if identities != {expected}:
                    bindings.append({"symbol": symbol, "expected": list(expected), "proved": False,
                                     "reason": "fresh library identity is missing, ambiguous, or differs from the required import"})
                    continue
            else:
                identities = {expected} if any(expected in values for values in library_cells.values()) else set()
            bindings.append(audit.audit_binding(symbol, {symbol: identities}, {}, selected, slots, None))
        after = {path: file_digest(path) for path in before}
        if before != after:
            raise Refused("weak import proof input changed during audit")
        return {"input_sha256": before, "input_hash_equality": True, "bindings": bindings}
    except (OSError, ValueError, KeyError, IndexError, struct.error, pefile.PEFormatError) as exc:
        raise Refused(f"weak import selected proof unavailable: {exc}") from exc
    finally:
        if native is not None:
            native.close()


def read_rsp(path):
    return [Path(line.strip().strip('"')) for line in Path(path).read_text(encoding="utf-8").splitlines()
            if line.strip()]


def census_objects():
    """This checkout's object for every matched row's source (built or not)."""
    seen = {}
    for row in build.load_function_rows():
        if not row["source"].lower().endswith(build.LIB_SUFFIX):
            seen.setdefault(build.row_object(row), row["source"])
    return seen


def source_of_objects():
    """{object file name: source} for every matched row's C/C++ source."""
    sources = {r["source"] for r in build.load_function_rows() if not r["source"].lower().endswith(build.LIB_SUFFIX)}
    return {build.obj_path(ROOT / source).name: source for source in sorted(sources)}


def rows_by_object():
    """{object file name: [matched rows]} for every C/C++ source."""
    by_source = collections.defaultdict(list)
    for row in build.load_function_rows():
        if not row["source"].lower().endswith(build.LIB_SUFFIX) and row["target_rva"].startswith("0x"):
            by_source[row["source"]].append(row)
    return {build.obj_path(ROOT / source).name: rows for source, rows in by_source.items()}


def measure(objects, imports, found):
    """Per-class counts over every reference and every distinct name. A name
    is classified per object when that object's matched bodies witness it."""
    names = {}
    refs = collections.Counter()
    per_object = {}
    dup = []
    seen = collections.defaultdict(set)
    detail = {}
    by_object = rows_by_object()
    source_objects = {path.resolve() for path in census_objects()}
    for path in objects:
        if not path.exists():
            continue
        source_owned = path.resolve() in source_objects
        routes = weak_import_routes(path, imports, lambda: site_witnesses(path, by_object.get(path.name, ()))) if source_owned else {}
        undefined, defined = object_facts(path)
        classes = {}
        sites = None
        for symbol in undefined:
            if symbol not in names:
                names[symbol] = classify(symbol, imports, found)
            verdict = names[symbol]
            if verdict[0] != "correct" or found.get(symbol) is None:
                if sites is None:
                    sites = site_witnesses(path, by_object.get(path.name, ()))
                if symbol in sites:
                    verdict = classify(symbol, imports, found, sites)
            classes[symbol] = verdict[0]
            refs[verdict[0]] += 1
            seen[verdict[0]].add(symbol)
            if verdict[0] != names[symbol][0]:
                detail[symbol + " @ " + path.name] = list(verdict)
        static_defined = static_iat_symbols(path) if source_owned else set()
        if source_owned and (static_defined or any(s.startswith("__imp_") for s in defined)):
            if sites is None:
                sites = site_witnesses(path, by_object.get(path.name, ()))
            for symbol, slots in owned_iat_cells(defined, imports, found, sites, static_defined).items():
                classes[symbol] = "owned-iat"
                refs["owned-iat"] += 1
                seen["owned-iat"].add(symbol)
                detail[symbol + " @ " + path.name] = ["owned-iat", owned_iat_problem(symbol, slots), None]
        if source_owned:
            for symbol, route in routes.items():
                classes[symbol] = "unproved-weak-import"
                refs["unproved-weak-import"] += 1
                seen["unproved-weak-import"].add(symbol)
                detail[symbol + " @ " + path.name] = ["unproved-weak-import", route, route["slot"]]
        thunks = sorted(defined & imports.thunk.keys())
        for t in thunks:
            dup.append((path.name, t))
            refs["duplicate-thunk"] += 1
        if classes or thunks:
            per_object[path.name] = {"imports": classes, "duplicate_thunks": thunks}
    distinct = {c: len(v) for c, v in seen.items()}
    distinct["duplicate-thunk"] = len({t for _, t in dup})
    return {"references": dict(refs), "distinct": distinct, "names": {k: list(v) for k, v in names.items()},
            "per_object_verdicts": detail, "objects": per_object}


def load_context():
    return Imports(retail_slots(), libraries()), witnesses()


def cmd_measure(args):
    imports, found = load_context()
    objects = read_rsp(args.objects) if args.objects else list(census_objects())
    try:
        result = measure(objects, imports, found)
    except Refused as why:
        print(f"import_binding: REFUSED measurement: {why}")
        return 1
    bad_objects = sum(1 for o in result["objects"].values()
                      if o["duplicate_thunks"] or any(c != "correct" for c in o["imports"].values()))
    result["objects_scanned"] = sum(1 for o in objects if o.exists())
    result["objects_with_defects"] = bad_objects
    print(f"import_binding: {result['objects_scanned']:,} objects, {bad_objects:,} with an import defect")
    for label in ("references", "distinct"):
        print(f"  {label}: " + ", ".join(f"{k} {v:,}" for k, v in sorted(result[label].items())))
    out = Path(args.json) if args.json else OUT / "measure.json"
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text(json.dumps(result, indent=1, sort_keys=True), encoding="utf-8")
    print(f"  -> {out}")
    return 0


# ---------------------------------------------------------------- one TU
REPAIRABLE = ("alias:wrong-name", "alias:wrong-dll")
JMP_IAT = b"\xff\x25"


class Refused(Exception):
    """Fail closed: the TU is not repaired, and why."""


def canonical_source(source):
    """Use the compiler's source identity for rows, evidence and receipts."""
    try:
        return build.resolved(ROOT / source.replace("\\", "/")).relative_to(ROOT).as_posix()
    except ValueError:
        raise Refused(f"{source}: source path is outside this checkout") from None


def identifier(symbol):
    """(C/C++ identifier, 'C' or 'C++') a function symbol (no __imp_) spells.
    Only plain global functions: a scoped C++ name or a fastcall one is refused."""
    if symbol.startswith("?"):
        m = re.fullmatch(r"\?([A-Za-z_]\w*)@@[YZ].*", symbol)
        if not m:
            raise Refused(f"{symbol}: not a plain global C++ function")
        return m.group(1), "C++"
    m = re.fullmatch(r"_([A-Za-z_]\w*?)(?:@\d+)?", symbol)
    if not m:
        raise Refused(f"{symbol}: not a __cdecl/__stdcall C name")
    return m.group(1), "C"


def tu_rows(source):
    return [r for r in build.load_function_rows() if r["source"] == source and r["target_rva"].startswith("0x")]


def plan(source, obj, imports, found):
    """[(kind, symbol, detail)] the TU needs, or Refused. kind: 'bind'
    (symbol -> canonical __imp_ name, identifiers) or 'own' (a duplicate thunk
    definition -> its address-owned name)."""
    rows = tu_rows(source)
    routes = weak_import_routes(obj, imports, lambda: site_witnesses(obj, rows))
    if routes:
        raise Refused("; ".join(f"{symbol}: weak import route requires selected native IAT proof; cannot rewrite automatically"
                                for symbol in routes))
    undefined, defined = object_facts(obj)
    sites = site_witnesses(obj, rows)
    steps, refused = [], []
    refused.extend(owned_iat_problem(symbol, slots)
                   for symbol, slots in owned_iat_cells(defined, imports, found, sites, static_iat_symbols(obj)).items())
    for symbol in sorted(undefined):
        kind, detail, slot = classify(symbol, imports, found, sites)
        if kind == "correct":
            continue
        if kind == "wrong-slot":
            # A real import name read through another slot: rebind only when the
            # TU's own matched bodies witness one IAT slot at EVERY site that
            # reads the name, so no unverified call is redirected.
            witnessed = sites.get(symbol, set())
            if len(witnessed) == 1 and next(iter(witnessed)) in imports.slots and site_counts(obj, rows).get(symbol) == reloc_counts(obj).get(symbol):
                kind, slot = "alias:wrong-name", next(iter(witnessed))
                detail = "{}!{}".format(*imports.slots[slot])
        if kind not in REPAIRABLE:
            refused.append(f"{symbol}: {kind} ({detail})")
            continue
        target = imports.spelling(slot)
        if target is None:
            refused.append(f"{symbol}: slot {slot:#x} has no single import-library spelling")
            continue
        try:
            old, _ = identifier(symbol[len("__imp_"):])
            new, linkage = identifier(target[len("__imp_"):])
        except Refused as why:
            refused.append(str(why))
            continue
        steps.append(("bind", symbol, {"to": target, "slot": slot, "import": detail,
                                       "old": old, "new": new, "linkage": linkage}))
    for symbol in sorted(defined & imports.thunk.keys()):
        owners = [r for r in rows if build.ledger_object_symbol(r) == symbol]
        if len(owners) != 1:
            refused.append(f"{symbol}: duplicate thunk with {len(owners)} ledger rows in this TU")
            continue
        row = owners[0]
        rva, size = int(row["target_rva"], 16), int(row["target_size"])
        body = build.read_target_bytes(rva, size)
        slot = imports.by_import[imports.thunk[symbol]]
        if size != 6 or body[:2] != JMP_IAT or struct.unpack_from("<I", body, 2)[0] - BASE != slot:
            refused.append(f"{symbol}: row at {rva:#010x} is not retail's `jmp [{slot + BASE:#010x}]` stub")
            continue
        old, _ = identifier(symbol)
        steps.append(("own", symbol, {"rva": rva, "slot": slot, "old": old,
                                      "new": f"Rva{rva:08X}_{old.lstrip('_')}", "row": row["name"]}))
    if refused:
        raise Refused("; ".join(refused))
    return steps


def rewrite(text, steps, keep_declarations=True, c_source=False):
    """The TU text with each step applied. 'own' first: the definition's
    identifier becomes address-owned (C++ linkage, like its Rva siblings);
    then each 'bind' renames the identifier to the real import's and gives its
    dllimport declaration the import's linkage (or drops that declaration so a
    header's declaration is used, keep_declarations=False)."""
    for kind, _, d in steps:
        if kind != "own":
            continue
        if not in_code(d["old"], text):
            raise Refused(f"{d['old']} does not occur in the source")
        # the owned definition takes C++ linkage: drop `extern "C"` on its line only
        pattern = re.compile(rf'(?m)^([ \t]*)extern[ \t]+"C"[ \t]+([^;{{}}(\n]*\b{re.escape(d["old"])}[ \t]*\()')
        text = pattern.sub(r"\1\2", text)
        text = sub_code(d["old"], d["new"], text)
    for kind, _, d in steps:
        if kind != "bind":
            continue
        old, new = d["old"], d["new"]
        if not in_code(old, text):
            raise Refused(f"{old} does not occur in the source (declared by a header?)")

        def fix(match):
            decl = match.group(0)
            if not in_code(old, decl):
                return decl
            if not keep_declarations:
                return ""
            decl = sub_code(old, new, decl)
            if c_source:
                return decl
            has_c = re.search(r'extern\s+"C"', decl)
            if d["linkage"] == "C" and not has_c:
                lead = re.match(r"\s*", decl).group(0)
                decl = lead + 'extern "C" ' + decl[len(lead):]
            elif d["linkage"] == "C++" and has_c:
                decl = re.sub(r'extern\s+"C"\s*', "", decl, count=1)
            return decl
        text = DECL.sub(fix, text)
        text = sub_code(old, new, text)
    return text


def work_dir(source):
    return OUT / build.obj_path(ROOT / source).stem


def fresh_object(source):
    """Compile the TU to its build.py object; (object, error text)."""
    obj = build.obj_path(ROOT / source)
    obj.parent.mkdir(parents=True, exist_ok=True)
    ok, text, _ = build.try_compile_source(ROOT / source, obj)
    return (obj if ok else None), (text or "")


def verify_object(source, obj, imports, found, steps, weak_proof=None):
    """[problem] for the rebuilt object: every import correct and witnessed
    as its retail slot where a matched body reads it, no source-owned IAT cell
    or duplicate thunk, and each owned name defined."""
    problems = []
    rows = tu_rows(source)
    routes = weak_import_routes(obj, imports, lambda: site_witnesses(obj, rows))
    bindings = {r["symbol"]: r for r in (weak_proof or {}).get("bindings", ())}
    for symbol, route in routes.items():
        proof = bindings.get(symbol, {})
        if ((weak_proof or {}).get("input_hash_equality") is not True or not proof.get("proved")
                or (weak_proof or {}).get("input_sha256", {}).get(str(obj)) != route["object_sha256"]
                or tuple(proof.get("expected", ())) != tuple(route["expected"])):
            problems.append(f"{symbol}: unproved weak import route ({proof.get('reason', 'no selected native IAT proof')})")
    undefined, defined = object_facts(obj)
    sites = site_witnesses(obj, rows)
    problems.extend(owned_iat_problem(symbol, slots)
                    for symbol, slots in owned_iat_cells(defined, imports, found, sites, static_iat_symbols(obj)).items())
    for symbol in sorted(undefined):
        kind, detail, slot = classify(symbol, imports, found, sites)
        if kind != "correct":
            problems.append(f"{symbol}: still {kind} ({detail})")
    for symbol in sorted(defined & imports.thunk.keys()):
        problems.append(f"{symbol}: still defines an import library's call stub")
    for kind, symbol, d in steps:
        if kind == "bind" and d["to"] not in undefined and symbol in undefined:
            problems.append(f"{symbol}: not rebound to {d['to']}")
        if kind == "own" and not any(re.search(rf"\b{d['new']}\b", n) for n in defined):
            problems.append(f"{d['new']}: not defined")
    return problems


def strict_link(obj, imports, work, label):
    """Link the object alone with no /FORCE and /NODEFAULTLIB against the
    retail import libraries and oldnames.lib. Labelled link-only stubs define
    every other external; never an `__imp_` name or a library's call stub, so
    an import resolves through the real library or not at all.
    (ok, output, linked imports)."""
    import link_census
    import provider_repair
    libs = libraries()
    # The libraries provide only retail imports: an import's `__imp_` slot and
    # call stub (and oldnames' spelling of one). Everything else, CRT statics
    # included, is a labelled stub: a static member would drag in imports of
    # its own (operator delete[] -> MSVCR71's operator delete), which is the
    # CRT's closure, not this TU's. Where two import libraries define the same
    # `__imp_` name (WSock32.Lib and WS2_32.Lib: htonl, send), the library of
    # the DLL retail imports it from goes first.
    provided = set(imports.thunk)
    provided |= {a for a, t in weak_aliases(oldnames()).items() if t in imports.thunk}
    order = {"wsock32.lib": 0}
    libs = sorted(libs, key=lambda p: order.get(p.name.lower(), 1))
    records = coff_symbols(obj.read_bytes())
    undefined, _ = external_symbols(records)
    stubbed = {n for n in undefined if not n.startswith("__imp_") and n not in provided}
    work.mkdir(parents=True, exist_ok=True)
    stubs = link_census.stub_object(stubbed, work / f"{label}_stubs.obj")
    out = work / f"{label}.dll"
    r = provider_repair._link(["/DLL", "/NOENTRY", "/OPT:NOREF", "/SAFESEH:NO", f"/OUT:{out}",
                               f"/MAP:{work / (label + '.map')}", obj, stubs, *libs])
    text = (r.stdout or "") + (r.stderr or "")
    linked = []
    if r.returncode == 0:
        import pefile
        pe = pefile.PE(str(out), fast_load=True)
        pe.parse_data_directories(directories=[pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_IMPORT"]])
        for dll in getattr(pe, "DIRECTORY_ENTRY_IMPORT", ()):
            for entry in dll.imports:
                linked.append((dll.dll.decode("latin-1").lower(), entry.name.decode("latin-1") if entry.name else None))
        pe.close()
    return r.returncode == 0, text.strip()[-1500:], linked, sorted(stubbed)


def link_verdict(ok, linked, imports):
    """Problems with a strict link's imports: each must be a retail import from the same DLL."""
    retail = set(imports.slots.values())
    if not ok:
        return ["strict link failed"]
    return [f"links {dll}!{name}, which retail does not import" for dll, name in linked if (dll, name) not in retail]


EVIDENCE = ROOT / "targets/game/reverse/identity_evidence"
LEDGER = ROOT / "targets/game/reverse/functions.csv"
CORRECTIONS = ROOT / "targets/game/reverse/name_corrections.json"


def rehome_row(source, obj, symbol, d, imports, model):
    """Repoint the duplicate thunk's ledger row to its address-owned name with
    add_match (identity correction, evidence file written first). None or why not."""
    _, defined = object_facts(obj)
    owned = [n for n in defined if re.fullmatch(rf"\?{d['new']}@@Y.*|_{d['new']}(@\d+)?", n)]
    if len(owned) != 1:
        return f"{d['new']}: {len(owned)} definitions in the object"
    dll, name = imports.thunk[symbol]
    rva, slot = d["rva"], d["slot"]
    evidence = EVIDENCE / f"{rva:08x}-import-stub.md"
    evidence.write_text(
        f"# 0x{rva:08X} is the import stub for {dll}!{name}, owned by address\n\n"
        f"Retail's six bytes at 0x{rva:08X} are `FF 25 {slot + BASE:08X}`, `jmp [IAT]` through the\n"
        f"slot retail's import directory assigns to {dll}!{name} (RVA 0x{slot:08X}).\n"
        f"The import library's short import object for that function defines both\n"
        f"`__imp_{symbol}` and the call stub `{symbol}`, so a TU that also defines `{symbol}`\n"
        f"links only under /FORCE (LNK2005 in a strict link).\n\n"
        f"The row keeps the bytes under the address-owned name `{owned[0]}` and\n"
        f"its body calls the real import `{imports.spelling(slot)}`;\n"
        f"`{symbol}` stays the import library's own name. Proven by\n"
        f"`python3 tools/import_binding.py check {source}` (strict link, no /FORCE).\n",
        encoding="utf-8", newline="\n")
    r = subprocess.run([sys.executable, str(ROOT / "tools" / "add_match.py"), owned[0], f"0x{rva:08X}", "6", source,
                        "--replace-rva", f"0x{rva:08X}", "--correct-identity", d["row"],
                        "--identity-evidence", evidence.relative_to(ROOT).as_posix(), "--model", model,
                        "--notes", f"{dll} {name} import stub FF 25 [0x{slot + BASE:08X}]; address-owned so the "
                                   f"import library's {symbol} stub links (import_binding)"],
                       cwd=ROOT, capture_output=True, text=True, errors="replace")
    if r.returncode:
        evidence.unlink()
        return f"add_match refused {owned[0]}: " + (r.stdout + r.stderr).strip()[-600:]
    return None


def record_name_correction(source, d):
    """name_regression reads `_CIacos -> Rva009F7256_CIacos` as a descriptive
    name lost; it is the documented identity correction, so record it exactly
    (the file's before/after blobs), citing the evidence rehome_row wrote."""
    import name_regression as nr
    before = nr.git(ROOT, "show", f"HEAD:{source}")
    after = (ROOT / source).read_bytes().decode("utf-8", "replace").replace("\r\n", "\n")
    path = ROOT / nr.CORRECTIONS
    raw = path.read_bytes()  # mixed line endings: append in place, never re-serialise
    entry = {"old_path": source, "new_path": source, "old_name": d["old"], "new_name": d["new"],
                    "before_sha256": nr.digest(before), "after_sha256": nr.digest(after),
                    "evidence": f"targets/game/reverse/identity_evidence/{d['rva']:08x}-import-stub.md",
                    "reason": f"{d['old']} is the import library's own call stub for this import; the TU's "
                              f"definition of the same name collides with it (LNK2005), so the body at "
                              f"0x{d['rva']:08X} keeps its bytes under an address-owned name."}
    end = raw.rstrip().rfind(b"]")
    body = json.dumps(entry, indent=1, ensure_ascii=False).replace("\n", "\n ")
    raw = raw[:end].rstrip() + b",\n " + body.encode("utf-8") + b"\n" + raw[end:]
    json.loads(raw)
    path.write_bytes(raw)


def cmd_apply(args):
    source = canonical_source(args.source)
    imports, found = load_context()
    work = work_dir(source)
    work.mkdir(parents=True, exist_ok=True)
    path = ROOT / source
    original = path.read_bytes()
    obj, err = fresh_object(source)
    if obj is None:
        print(f"import_binding: FAIL {source} does not compile as it stands\n{err}")
        return 1
    (work / "before.obj").write_bytes(obj.read_bytes())
    try:
        steps = plan(source, obj, imports, found)
    except Refused as why:
        (work / "refused.txt").write_text(str(why) + "\n", encoding="utf-8")
        print(f"import_binding: REFUSED {source}: {why}")
        return 1
    if not steps:
        print(f"import_binding: {source}: nothing to repair")
        return 0
    (work / "before.src").write_bytes(original)
    (work / "plan.json").write_text(json.dumps(steps, indent=1), encoding="utf-8")
    if any(kind == "own" for kind, _, _ in steps) and not args.model:
        print("import_binding: REFUSED: a duplicate thunk re-homes a ledger row; pass --model (or set BFME_MODEL)")
        return 1
    ledger_before, corrections_before = LEDGER.read_bytes(), CORRECTIONS.read_bytes()
    text = original.decode("latin-1")
    newline = "\r\n" if "\r\n" in text else "\n"
    c_source = path.suffix.lower() == ".c"
    last = None
    for keep in (True, False):
        try:
            candidate = rewrite(text, steps, keep_declarations=keep, c_source=c_source)
        except Refused as why:
            last = str(why)
            break
        if newline == "\r\n":  # keep the file's line endings byte for byte
            candidate = candidate.replace("\r\n", "\n").replace("\n", "\r\n")
        path.write_bytes(candidate.encode("latin-1"))
        obj, err = fresh_object(source)
        if obj is None:
            last = "compile failed: " + " | ".join(l for l in err.splitlines() if "error" in l)[:600]
            continue
        problems = verify_object(source, obj, imports, found, steps)
        if not problems:
            for kind, symbol, d in steps:
                if kind == "own":
                    problem = rehome_row(source, obj, symbol, d, imports, args.model)
                    if problem:
                        problems.append(problem)
                        break
                    record_name_correction(source, d)
        if problems:
            LEDGER.write_bytes(ledger_before)
            CORRECTIONS.write_bytes(corrections_before)
        if not problems:
            print(f"import_binding: applied {len(steps)} step(s) to {source} "
                  f"({'declarations kept' if keep else 'header declarations used'}); now run check")
            for kind, symbol, d in steps:
                print(f"  {kind}: {symbol} -> {d.get('to') or d['new']}")
            return 0
        last = "; ".join(problems)
    path.write_bytes(original)
    fresh_object(source)
    (work / "refused.txt").write_text(f"no rewrite binds it: {last}\n", encoding="utf-8")
    print(f"import_binding: REFUSED {source}: no rewrite binds it ({last}); source restored")
    return 1


def cmd_check(args):
    source = canonical_source(args.source)
    imports, found = load_context()
    work = work_dir(source)
    work.mkdir(parents=True, exist_ok=True)
    steps = json.loads((work / "plan.json").read_text(encoding="utf-8")) if (work / "plan.json").exists() else []
    receipt = {"source": source, "steps": steps}
    gate = subprocess.run([sys.executable, str(ROOT / "tools" / "build.py"), source], cwd=ROOT,
                          capture_output=True, text=True, errors="replace")
    receipt["byte_gate"] = {"exit": gate.returncode, "tail": gate.stdout.strip().splitlines()[-6:]}
    failures = [] if gate.returncode == 0 else [f"byte gate exit {gate.returncode}"]
    obj = build.obj_path(ROOT / source)
    owned_steps = [s for s in steps if s[0] == "own"]
    routes, weak_proof, preparation_error = {}, None, None
    try:
        records = weak_import_records(obj)
        witness_inputs = {str(path): file_digest(path) for path in (build.EXE, build.FUNCTIONS)} if records else {}
        routes = weak_import_routes(obj, imports, lambda: site_witnesses(obj, tu_rows(source)))
        if any(file_digest(path) != digest for path, digest in witness_inputs.items()):
            raise Refused("weak import witness inputs changed during route inspection")
        if any(file_digest(obj) != record["object_sha256"] for record in records.values()):
            raise Refused("source weak import object changed before link")
        if routes:
            libs, inputs = weak_selection_inputs(source, obj)
            if any(inputs[path] != digest for path, digest in witness_inputs.items()):
                raise Refused("weak import witness inputs changed before link")
            if any(inputs[str(obj)] != route["object_sha256"] for route in routes.values()):
                raise Refused("source weak import object changed before link")
            # These are this source's disposable outputs, not historical controls.
            for path in (work / "after.dll", work / "after.map"):
                path.unlink(missing_ok=True)
        else:
            failures += verify_object(source, obj, imports, found, owned_steps)
    except (OSError, Refused) as why:
        preparation_error = str(why)
        failures.append(preparation_error)
    if preparation_error is None:
        ok, text, linked, stubbed = strict_link(obj, imports, work, "after")
    else:
        ok, text, linked, stubbed = False, "not run: " + preparation_error, [], []
    receipt["strict_link"] = {"ok": ok, "output": text, "imports": linked, "stubbed_non_imports": len(stubbed)}
    failures += link_verdict(ok, linked, imports)
    if routes:
        try:
            if ok:
                weak_proof = weak_selected_proof(obj, imports, routes, work, libs, inputs)
            else:
                weak_proof = {"input_hash_equality": False, "bindings": []}
            failures += verify_object(source, obj, imports, found, owned_steps, weak_proof=weak_proof)
        except Refused as why:
            failures.append(str(why))
            weak_proof = {"input_hash_equality": False, "bindings": [], "error": str(why)}
        receipt["weak_import_routes"] = routes
        receipt["weak_import_proof"] = weak_proof
    before = work / "before.obj"
    if before.exists():  # the control: the unrepaired object must NOT link strictly
        bok, btext, _, _ = strict_link(before, imports, work, "before")
        try:
            control_problems = verify_object(source, before, imports, found, [])
        except Refused as why:
            control_problems = [str(why)]
        receipt["before_strict_link"] = {"ok": bok, "output": btext, "binding_problems": control_problems}
    if weak_proof and weak_proof.get("input_hash_equality"):
        try:
            if any(file_digest(path) != digest
                   for path, digest in weak_proof["input_sha256"].items()):
                raise Refused("weak import proof input changed before receipt")
        except (OSError, Refused) as why:
            failures.append(str(why))
            weak_proof["input_hash_equality"] = False
    receipt["pass"] = not failures
    receipt["failures"] = failures
    (work / "receipt.json").write_text(json.dumps(receipt, indent=1), encoding="utf-8")
    print(f"import_binding: {'PASS' if not failures else 'FAIL'} {source}")
    for line in failures:
        print(f"  {line}")
    if receipt.get("before_strict_link"):
        control = receipt["before_strict_link"]
        misbound = len(control["binding_problems"])
        print(f"  control: unrepaired object {'links' if control['ok'] else 'fails'} strictly"
              + (f", {misbound} import binding problem(s)" if misbound else ""))
    print(f"  receipt: {work / 'receipt.json'}")
    return 0 if not failures else 1


def cmd_next(args):
    """One TU whose every import defect is repairable, from a measure run."""
    measured = json.loads(Path(args.measure).read_text(encoding="utf-8"))
    sources = source_of_objects()
    done = {p.parent.name for pattern in ("*/receipt.json", "*/refused.txt") for p in OUT.glob(pattern)}
    for name, facts in sorted(measured["objects"].items()):
        kinds = set(facts["imports"].values()) - {"correct"}
        if not (kinds or facts["duplicate_thunks"]) or not kinds <= set(REPAIRABLE):
            continue
        source = sources.get(name)
        if source is None or work_dir(source).name in done or not editable(source):
            continue
        print(source)
        for symbol, kind in sorted(facts["imports"].items()):
            if kind != "correct":
                print(f"  {kind}: {symbol}")
        for symbol in facts["duplicate_thunks"]:
            print(f"  duplicate-thunk: {symbol}")
        print(f"  python3 tools/import_binding.py apply {source} && python3 tools/import_binding.py check {source}")
        return 0
    print("import_binding: no repairable TU left in", args.measure)
    return 1


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    sub = parser.add_subparsers(dest="command", required=True)
    p = sub.add_parser("measure")
    p.add_argument("--objects", help="a link response file of objects (default: this checkout's census objects)")
    p.add_argument("--json")
    p.set_defaults(func=cmd_measure)
    p = sub.add_parser("next")
    p.add_argument("--measure", default=str(OUT / "measure.json"))
    p.set_defaults(func=cmd_next)
    for name, func in (("apply", cmd_apply), ("check", cmd_check)):
        p = sub.add_parser(name)
        p.add_argument("source")
        p.add_argument("--model", default=os.environ.get("BFME_MODEL", ""))
        p.set_defaults(func=func)
    args = parser.parse_args(argv)
    try:
        return args.func(args)
    except Refused as why:
        print(f"import_binding: REFUSED: {why}")
        return 1


if __name__ == "__main__":
    sys.exit(main())
