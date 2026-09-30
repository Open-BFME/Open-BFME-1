#!/usr/bin/env python3
"""Data scaffold: COFF objects defining every retail data item no source object defines.

Reads build/reloc_ledger/ (tools/reloc_ledger.py) and writes, under
build/data_scaffold/:

  obj/scaffold_NNN.obj  one COFF section per contiguous run of scaffold items
                        (.rdata$S, .data$S, STLPORT_, uninitialised .bss$S), holding
                        retail's bytes, a public label at every item start (the
                        name callers spell, else g_<VA>) and a DIR32 relocation at
                        every ledger site in it whose provenance is not
                        scan-candidate. Scan candidates stay literal.
  obj/aliases.obj       weak externals (SEARCH_ALIAS) for every other name a
                        caller spells at a scaffold item, or at an object-defined
                        label: labelled aliases, one definition per address.
  symbols.csv           every scaffold symbol: va, role, item kind, size proof,
                        the sources of its name. SCAFFOLDING, never progress.
  verify.json           the checks below.

Verification:
  retail   each section resolved with every symbol at its retail address
           equals retail's bytes (uninitialised sections: retail holds zeros).
  shifted  every symbol moved by its own offset (each scaffold section moves
           as one), every relocation field decodes to its target's moved
           address, no other byte changes, and no in-image dword is left
           outside a relocation field except the ledger's scan candidates.
  link     (--link-check) link.exe 7.1 links the scaffold objects, the alias
           object and a stub defining every other external, at base
           0x10000000, no /FORCE; the linked bytes are checked the same way.
  trial    (--trial-link) the census objects (link_census.py objects.rsp,
           gen_asm dumps swapped for tools/dump_relocs.py objects) + scaffold +
           aliases, no /FORCE: every unresolved and duplicate name, classified.
           Holds the census lock (build/wt_link.census-lock) while linking.

  python3 tools/data_scaffold.py                     # emit + verify (retail, shifted)
  python3 tools/data_scaffold.py --link-check        # + link.exe at a moved base
  python3 tools/data_scaffold.py --trial-link --census-rsp build/census_objects.rsp
"""
import argparse
import bisect
import collections
import csv
import json
import re
import struct
import subprocess
import sys
import time
import zlib
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402
import reloc_ledger as RL  # noqa: E402

OUT = ROOT / "build" / "data_scaffold"
LEDGER = ROOT / "build" / "reloc_ledger"
DIR32 = 0x0006
EXTERNAL, STATIC, WEAK_EXTERNAL = 2, 3, 105
NRELOC_OVFL = 0x01000000
SECTION_FLAGS = {".rdata": 0x40000040, ".data": 0xC0000040, "STLPORT_": 0xC0000040}
BSS_FLAGS = 0xC0000080
SECTION_NAMES = {".rdata": ".rdata$S", ".data": ".data$S", "STLPORT_": "STLPORT_"}
SECTIONS_PER_OBJECT = 2000
LINK_BASE = 0x10000000
LOCK_WAIT = 2 * 3600  # seconds to wait for another census link to release the lock
MAX_ALIGN = 16


def align_flags(va):
    align = 1
    while align < MAX_ALIGN and va % (align * 2) == 0:
        align *= 2
    return (align.bit_length()) << 20  # IMAGE_SCN_ALIGN_{1,2,4,8,16}BYTES = 1..5 << 20


def parse_int(text):
    return -int(text[1:], 16) if text.startswith("-") else int(text, 16)


# --------------------------------------------------------------------------- inputs

def load(ledger_dir):
    items = [r for r in RL.read_csv_rows(ledger_dir / "items.csv") if r["source"] == "scaffold"]
    for it in items:
        it["start"], it["end"] = int(it["start"], 16), int(it["end"], 16)
    relocs = collections.defaultdict(list)   # site -> row
    scan = set()
    with (ledger_dir / "ledger.csv").open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            if row["site_section"] not in RL.SCAFFOLD_SECTIONS:
                continue
            site = int(row["site_va"], 16)
            if row["provenance"] in RL.NOT_A_RELOCATION:
                scan.add(site)  # stays literal: listed, never a relocation
                continue
            relocs[site] = row
    names = RL.read_csv_rows(ledger_dir / "names.csv")
    return items, relocs, scan, names


def blocks_of(items):
    """Maximal runs of contiguous scaffold items in one section, split where
    the virtual-only (uninitialised) tail begins."""
    blocks = []
    for it in sorted(items, key=lambda i: i["start"]):
        bss = it["proof"] == "uninitialised"
        if blocks and blocks[-1]["end"] == it["start"] and blocks[-1]["section"] == it["section"] \
                and blocks[-1]["bss"] == bss:
            blocks[-1]["items"].append(it)
            blocks[-1]["end"] = it["end"]
        else:
            blocks.append({"start": it["start"], "end": it["end"], "section": it["section"], "bss": bss,
                           "items": [it]})
    return blocks


# --------------------------------------------------------------------------- COFF writer

class Coff:
    def __init__(self):
        self.sections = []   # dicts: name, flags, data (bytes or None), size, relocs [(off, symbol index)]
        self.symbols = []    # (name, value, section number, storage, aux bytes or None)
        self.index = {}
        self.strings = bytearray(4)

    def symbol(self, name, value=0, section=0, storage=EXTERNAL):
        if name in self.index and section == 0:
            return self.index[name]
        if name in self.index:
            raise ValueError(f"symbol {name} defined twice in one object")
        self.index[name] = len(self.symbols)
        self.symbols.append((name, value, section, storage))
        return self.index[name]

    def define(self, name, value, section):
        """Define a name, promoting an earlier undefined reference."""
        if name in self.index:
            i = self.index[name]
            if self.symbols[i][2] != 0:
                raise ValueError(f"symbol {name} defined twice in one object")
            self.symbols[i] = (name, value, section, EXTERNAL)
            return i
        return self.symbol(name, value, section)

    def add_section(self, name, flags, data, size):
        self.sections.append({"name": name, "flags": flags, "data": data, "size": size, "relocs": []})
        return len(self.sections)

    def _name(self, text):
        raw = text.encode("latin-1")
        if len(raw) <= 8:
            return raw.ljust(8, b"\0")
        offset = len(self.strings)
        self.strings += raw + b"\0"
        return struct.pack("<II", 0, offset)

    def write(self, path):
        head = 20 + 40 * len(self.sections)
        body = bytearray()
        headers = bytearray()
        for s in self.sections:
            raw_ptr = head + len(body) if s["data"] is not None else 0
            if s["data"] is not None:
                body += s["data"]
            relocs = s["relocs"]
            flags = s["flags"]
            nrel = len(relocs)
            rel_ptr = head + len(body) if nrel else 0
            if nrel >= 0xFFFF:
                flags |= NRELOC_OVFL
                body += struct.pack("<IIH", nrel + 1, 0, 0)
                count_field = 0xFFFF
            else:
                count_field = nrel
            for off, sym in relocs:
                body += struct.pack("<IIH", off, sym, DIR32)
            name = s["name"].encode("latin-1")
            if len(name) > 8:
                offset = len(self.strings)
                self.strings += name + b"\0"
                name = f"/{offset}".encode("ascii")
            headers += name.ljust(8, b"\0") + struct.pack(
                "<IIIIIIHHI", 0, 0, s["size"], raw_ptr if s["data"] is not None else 0, rel_ptr, 0,
                count_field, 0, flags)
        table = bytearray()
        for name, value, section, storage in self.symbols:
            table += self._name(name) + struct.pack("<IhHBB", value, section, 0, storage, 0)
        symtab = head + len(body)
        struct.pack_into("<I", self.strings, 0, len(self.strings))
        header = struct.pack("<HHIIIHH", 0x14C, len(self.sections), 0, symtab, len(self.symbols), 0, 0)
        path.write_bytes(header + bytes(headers) + bytes(body) + bytes(table) + bytes(self.strings))


def alias_object(table, path):
    """Weak externals with IMAGE_WEAK_EXTERN_SEARCH_ALIAS (link_census.alias_object's record)."""
    targets = sorted(set(table.values()))
    strings = bytearray(4)

    def field(text):
        raw = text.encode("latin-1")
        if len(raw) <= 8:
            return raw.ljust(8, b"\0")
        offset = len(strings)
        strings.extend(raw + b"\0")
        return struct.pack("<II", 0, offset)

    symbols, index = bytearray(), {}
    for target in targets:
        index[target] = len(symbols) // 18
        symbols += field(target) + struct.pack("<IhHBB", 0, 0, 0, EXTERNAL, 0)
    for alias, target in sorted(table.items()):
        symbols += field(alias) + struct.pack("<IhHBB", 0, 0, 0, WEAK_EXTERNAL, 1)
        symbols += struct.pack("<II", index[target], 3) + b"\0" * 10
    struct.pack_into("<I", strings, 0, len(strings))
    header = struct.pack("<HHIIIHH", 0x14C, 0, 0, 20, len(symbols) // 18, 0, 0)
    path.write_bytes(header + bytes(symbols) + bytes(strings))


# --------------------------------------------------------------------------- emission

def emit(img, items, relocs, names, out):
    """Write the scaffold objects; returns (objects, manifest rows, sections, aliases, problems)."""
    blocks = blocks_of(items)
    labels = {}                                   # name -> va (scaffold definitions)
    for it in items:
        labels[it["label"]] = it["start"]
    # aliases: every other caller name at a scaffold item or an object label
    aliases, manifest, problems = {}, [], collections.Counter()
    by_va = collections.defaultdict(list)
    for row in names:
        by_va[int(row["va"], 16)].append(row)
        if row["role"] == "alias" and row["alias_of"]:
            aliases[row["name"]] = row["alias_of"]
    (out / "obj").mkdir(parents=True, exist_ok=True)
    for old in (out / "obj").glob("scaffold_*.obj"):
        old.unlink()
    objects, sections, unlinkable = [], [], set()
    for k in range(0, len(blocks), SECTIONS_PER_OBJECT):
        coff = Coff()
        for block in blocks[k:k + SECTIONS_PER_OBJECT]:
            size = block["end"] - block["start"]
            if block["bss"]:
                number = coff.add_section(".bss$S", BSS_FLAGS | align_flags(block["start"]), None, size)
            else:
                data = img.read(block["start"], size)
                number = coff.add_section(SECTION_NAMES[block["section"]],
                                          SECTION_FLAGS[block["section"]] | align_flags(block["start"]),
                                          bytearray(data), size)
            section = coff.sections[number - 1]
            section["va"] = block["start"]
            for it in block["items"]:
                coff.define(it["label"], it["start"] - block["start"], number)
                manifest.append([f"0x{it['start']:08X}", it["label"], "definition", it["kind"], it["proof"],
                                 it["end"] - it["start"], "+".join(sorted({s for r in by_va.get(it["start"], [])
                                                                          for s in r["sources"].split("+")}))
                                 or "address"])
            if block["bss"]:
                sections.append(section)
                continue
            for site in sorted(s for s in relocs if block["start"] <= s < block["end"] - 3):
                row = relocs[site]
                symbol = row["link_symbol"]
                if not symbol:
                    problems[f"unlinkable:{row['link_class']}"] += 1
                    unlinkable.add(site)
                    continue
                off = site - block["start"]
                struct.pack_into("<i", section["data"], off, parse_int(row["link_addend"]))
                section["relocs"].append((off, coff.symbol(symbol)))
            section["data"] = bytes(section["data"])
            sections.append(section)
        path = out / "obj" / f"scaffold_{k // SECTIONS_PER_OBJECT:03d}.obj"
        coff.write(path)
        objects.append(path)
    for alias, target in sorted(aliases.items()):
        manifest.append([f"0x{labels.get(target, 0):08X}", alias, "alias", "", "", "", f"alias of {target}"])
    alias_object(aliases, out / "obj" / "aliases.obj")
    with (out / "symbols.csv").open("w", newline="", encoding="utf-8") as handle:
        w = csv.writer(handle, lineterminator="\n")
        w.writerow(["va", "name", "role", "kind", "size_proof", "size", "name_sources"])
        w.writerows(sorted(manifest))
    return objects, labels, aliases, problems, unlinkable


# --------------------------------------------------------------------------- verification

def shift_of(name):
    return 0x1000 + (zlib.crc32(name.encode("latin-1")) % 0xFF00) * 0x10


def read_scaffold(objects):
    """[(section dict, [(off, symbol name, addend)], {label: offset})] from the written objects."""
    out = []
    for path in objects:
        sections, symbols = RL.parse_coff(path.read_bytes())
        labels = collections.defaultdict(dict)
        for s in symbols.values():
            if s["section"] > 0:
                labels[s["section"]][s["name"]] = s["value"]
        for sec in sections:
            relocs = []
            for where, index, kind in sec["relocs"]:
                addend = struct.unpack_from("<i", sec["body"], where)[0]
                relocs.append((where, symbols[index]["name"], addend))
            out.append((sec, relocs, labels[sec["number"]]))
    return out


def verify(img, objects, ledger_rows, scan, labels, unlinkable=frozenset()):
    """retail and shifted placements, per section; returns a summary dict."""
    parsed = read_scaffold(objects)
    retail_of = dict(labels)
    clash = collections.Counter()
    for row in ledger_rows.values():
        if not row["link_symbol"]:
            continue
        va = (int(row["target_va"], 16) - parse_int(row["link_addend"])) & 0xFFFFFFFF
        if retail_of.setdefault(row["link_symbol"], va) != va:
            clash[row["link_symbol"]] += 1
    section_base = {}
    for sec, relocs, lab in parsed:
        name, off = next(iter(sorted(lab.items(), key=lambda kv: kv[1])))
        section_base[id(sec)] = labels[name] - off
    result = collections.Counter()
    failures = []
    for sec, relocs, lab in parsed:
        base = section_base[id(sec)]
        retail = img.read(base, sec["size"])
        if sec["body"] is None:
            result["sections_bss"] += 1
            if any(retail):
                failures.append(f"{base:#010x}: uninitialised section but retail holds non-zero bytes")
            continue
        result["sections"] += 1
        result["relocations"] += len(relocs)
        # (i) retail placement
        got = bytearray(sec["body"])
        for where, symbol, addend in relocs:
            struct.pack_into("<I", got, where, (retail_of[symbol] + addend) & 0xFFFFFFFF)
        if bytes(got) != retail:
            diff = next(i for i in range(len(got)) if got[i] != retail[i])
            failures.append(f"{base:#010x}+{diff:#x}: retail placement differs")
            result["retail_differs"] += 1
        # (ii) every symbol moved; this section moves by the shift of its first label
        moved_self = shift_of(min(lab, key=lab.get))
        local = {n: labels[n] + moved_self for n in lab}
        moved = bytearray(sec["body"])
        fields = set()
        for where, symbol, addend in relocs:
            fields.update(range(where, where + 4))
            target = local.get(symbol, retail_of[symbol] + shift_of(symbol))
            struct.pack_into("<I", moved, where, (target + addend) & 0xFFFFFFFF)
            if (target + addend) & 0xFFFFFFFF == struct.unpack_from("<I", retail, where)[0]:
                failures.append(f"{base + where:#010x}: field did not move ({symbol})")
                result["field_not_moved"] += 1
        literal = 0
        for off in range(0, len(moved) - 3):
            if off in fields or off + 1 in fields or off + 2 in fields or off + 3 in fields:
                continue
            if moved[off] != retail[off]:
                result["byte_changed"] += 1
            value = struct.unpack_from("<I", moved, off)[0]
            if img.in_image(value) and any(base + off + k in unlinkable for k in range(-3, 4)):
                result["unlinkable_literals"] += 1
            elif img.in_image(value) and base + off not in scan:
                literal += 1
                if literal <= 3:
                    failures.append(f"{base + off:#010x}: in-image literal {value:#010x} left, not a listed candidate")
        result["unlisted_literals"] += literal
        result["listed_literals"] += sum(1 for s in scan if base <= s < base + len(moved) - 3)
    result["symbol_address_clashes"] = len(clash)
    return dict(result), failures


# --------------------------------------------------------------------------- link.exe checks

def stub_object(names, path):
    strings, symbols = bytearray(4), bytearray()
    for i, name in enumerate(sorted(names)):
        raw = name.encode("latin-1")
        field = raw.ljust(8, b"\0") if len(raw) <= 8 else struct.pack("<II", 0, len(strings))
        if len(raw) > 8:
            strings.extend(raw + b"\0")
        symbols += field + struct.pack("<IhHBB", 16 * i, 1, 0, EXTERNAL, 0)
    struct.pack_into("<I", strings, 0, len(strings))
    body = b"\xcc" * (16 * max(1, len(names)))
    table = 20 + 40 + len(body)
    header = struct.pack("<HHIIIHH", 0x14C, 1, 0, table, len(symbols) // 18, 0, 0)
    section = b".text$zz" + struct.pack("<IIIIIIHHI", 0, 0, len(body), 60, 0, 0, 0, 0, 0x60500020)
    path.write_bytes(header + section + body + bytes(symbols) + bytes(strings))


def linker():
    root = build.vc71_root()
    return root / "Vc7" / "bin" / "link.exe", build.compiler_environment(root, None)


def link_check(img, objects, labels, aliases, scan, out):
    """Link the scaffold alone at LINK_BASE and check every linked section."""
    import pefile
    work = out / "link"
    work.mkdir(parents=True, exist_ok=True)
    defined, referenced = set(), set()
    for path in objects:
        _, symbols = RL.parse_coff(path.read_bytes())
        for s in symbols.values():
            if s["storage"] == EXTERNAL:
                (defined if s["section"] > 0 else referenced).add(s["name"])
    externs = (referenced | set(aliases.values())) - defined
    stub_object(externs | {"_stub_entry"}, work / "stub.obj")
    exe, mapfile = work / "scaffold.exe", work / "scaffold.map"
    link, env = linker()
    cmd = [str(link), "/NOLOGO", "/NODEFAULTLIB", "/INCREMENTAL:NO", "/MACHINE:X86", "/SUBSYSTEM:CONSOLE",
           "/FIXED", f"/BASE:{LINK_BASE:#x}", "/OPT:NOREF", "/ENTRY:stub_entry", f"/MAP:{mapfile}", f"/OUT:{exe}",
           *[str(p) for p in objects], str(out / "obj" / "aliases.obj"), str(work / "stub.obj")]
    proc = subprocess.run(cmd, capture_output=True, text=True, errors="replace", env=env)
    (work / "link.log").write_text(proc.stdout + proc.stderr, encoding="utf-8")
    if proc.returncode != 0:
        return {"linked": False, "exit": proc.returncode, "log": (proc.stdout + proc.stderr)[-2000:]}, []
    linked = {}
    for line in mapfile.read_text(errors="replace").splitlines():
        parts = line.split()
        if len(parts) >= 3 and re.fullmatch(r"[0-9a-f]{4}:[0-9a-f]{8}", parts[0]) \
                and re.fullmatch(r"[0-9a-f]{8}", parts[2]):
            linked.setdefault(parts[1], int(parts[2], 16))
    pe = pefile.PE(str(exe))
    image = pe.get_memory_mapped_image()
    result, failures = collections.Counter(), []
    for alias, target in aliases.items():
        if alias in linked and target in linked and linked[alias] != linked[target]:
            failures.append(f"alias {alias} linked at {linked[alias]:#x}, target {target} at {linked[target]:#x}")
            result["alias_mismatch"] += 1
    for sec, relocs, lab in read_scaffold(objects):
        first = min(lab, key=lab.get)
        if first not in linked:
            result["section_missing_from_map"] += 1
            continue
        place = linked[first] - lab[first]
        base = labels[first] - lab[first]
        got = image[place - LINK_BASE:place - LINK_BASE + sec["size"]]
        retail = img.read(base, sec["size"])
        if place == base:
            failures.append(f"{base:#010x}: linked at its retail address")
        fields = set()
        for where, symbol, addend in relocs:
            fields.update(range(where, where + 4))
            want = (linked[symbol] + addend) & 0xFFFFFFFF
            if struct.unpack_from("<I", got, where)[0] != want:
                result["field_wrong"] += 1
                if result["field_wrong"] <= 5:
                    failures.append(f"{base + where:#010x}: {symbol}+{addend:#x} linked wrong")
        bad = sum(1 for i in range(len(retail)) if i not in fields and got[i] != retail[i])
        result["byte_differs"] += bad
        result["sections"] += 1
        result["fields"] += len(relocs)
    result["linked"] = True
    return dict(result), failures


# --------------------------------------------------------------------------- trial whole-program link



def census_lock_path():
    """build/wt_link.census-lock of the MAIN checkout (daily_census.sh's lock)."""
    common = subprocess.run(["git", "rev-parse", "--path-format=absolute", "--git-common-dir"], cwd=ROOT,
                            capture_output=True, text=True).stdout.strip()
    main = Path(common).parent if common else ROOT
    return main / "build" / "wt_link.census-lock"


def retail_libraries(out):
    """The libraries retail's imports come from: msvcrt.lib (MSVCR71 and the CRT's
    static members, crtexew.obj's _WinMainCRTStartup among them), the toolchain's
    import library for every other DLL in retail's import table, and for a DLL
    the toolchain lacks one generated from retail's own import names and hints
    (tools/loader_lanes.py). Plus retail's resources as a .res. Returns
    (paths, report)."""
    import loader_lanes
    root = build.vc71_root() / "Vc7"
    folders = [root / "lib", root / "PlatformSDK" / "Lib"]
    shipped = {}
    for folder in folders:
        for path in sorted(folder.iterdir()):
            if path.suffix.lower() == ".lib":
                shipped.setdefault(path.stem.lower(), path)
    retail = loader_lanes.facts(loader_lanes.load(build.EXE))
    gen = out / "import_libs"
    gen.mkdir(parents=True, exist_ok=True)
    paths, report = [shipped["msvcrt"]], {"msvcr71.dll": "toolchain msvcrt.lib"}
    for imp in retail["imports"]:
        stem = imp["dll"].rsplit(".", 1)[0].lower()
        if stem == "msvcr71":
            continue
        lib = shipped.get("vfw32" if stem == "avifil32" else stem)
        if lib is not None:
            report[imp["dll"]] = f"toolchain {lib.name}"
        else:
            lib = loader_lanes.write_import_lib(imp["dll"], imp["names"], imp["hints"], gen / f"{stem}.lib")
            report[imp["dll"]] = f"generated from retail's {len(imp['names'])} imports"
        if lib not in paths:
            paths.append(lib)
    res = out / "retail.res"
    res.write_bytes(loader_lanes.res_bytes(loader_lanes.resource_leaves(loader_lanes.load(build.EXE))))
    paths.append(res)
    report["resources"] = "retail .rsrc as retail.res"
    return paths, report


def verify_original_dump(img, source, obj, ctx=None):
    """Whether a dump source's OWN object is relocatable: current for its source,
    every ledger row's body equal to retail outside relocation fields, and every
    operand of its reached code that holds an in-image address (a branch leaving
    the body, a disp32, an imm32) covered by a relocation. Bound to the exact
    source and object by sha256. {"ok": bool, "why": str, ...}"""
    import hashlib
    import dump_relocs
    import link_census
    verdict = {"source": source.relative_to(ROOT).as_posix() if source.is_relative_to(ROOT) else str(source),
               "ok": False}
    if not obj.exists() or not source.exists():
        return {**verdict, "why": "object or source missing"}
    verdict["source_sha256"] = hashlib.sha256(source.read_bytes()).hexdigest()
    verdict["object_sha256"] = hashlib.sha256(obj.read_bytes()).hexdigest()
    if not link_census.object_current(source, obj):
        return {**verdict, "why": "object is not current for its source"}
    rel_source = verdict["source"]
    rows = [r for r in build.load_function_rows() if r["source"] == rel_source and r["target_rva"].startswith("0x")]
    if not rows:
        return {**verdict, "why": "no matched ledger row names this source"}
    sections, symbols = RL.parse_coff(obj.read_bytes())
    for row in rows:
        name = build.ledger_object_symbol(row)
        sym = next((x for x in symbols.values() if x["name"] == name and x["section"] > 0), None)
        if sym is None:
            return {**verdict, "why": f"{name} not defined in the object"}
        sec = sections[sym["section"] - 1]
        size, va = int(row["target_size"]), img.base + int(row["target_rva"], 16)
        lo = sym["value"]
        body = (sec["body"] or b"")[lo:lo + size]
        relocs = [(w - lo, k) for w, _, k in sec["relocs"] if lo <= w < lo + size]
        retail = img.read(va, size)
        if retail is None or len(body) != size or not RL.masked_equal(body, retail, [(w, 0, k) for w, k in relocs]):
            return {**verdict, "why": f"{name} differs from retail outside relocation fields"}
        fields = {w for w, _ in relocs}
        result = dump_relocs.analyze(retail, va, ctx)
        for problem, off, text in result["problems"]:
            if problem != "falls-off-end":
                return {**verdict, "why": f"{name}+{off:#x} {problem} {text}".strip()}
        for ref in result["refs"]:
            inside = va <= ref.value < va + size
            needs = (ref.kind == "branch" and not inside) or (ref.kind != "branch" and img.in_image(ref.value))
            if needs and ref.off not in fields:
                return {**verdict, "why": f"{name}+{ref.insn_off:#x} `{ref.text}` holds {ref.value:#010x} "
                                          "with no relocation"}
    return {**verdict, "ok": True, "why": f"{len(rows)} body(ies) equal retail; every in-image operand relocated"}


def dump_sources():
    """{census object path (repo-relative): .asm source} for every dump source."""
    return {build.row_object(row).resolve().relative_to(ROOT.resolve()).as_posix(): row["source"]
            for row in build.load_function_rows()
            if row["source"].lower().endswith(".asm") and row["target_rva"].startswith("0x")}


def dump_objects():
    """{census object path (repo-relative): dump_relocs object} for every .asm dump source."""
    out = {}
    for row in build.load_function_rows():
        if not row["source"].lower().endswith(".asm") or not row["target_rva"].startswith("0x"):
            continue
        stem = re.sub(r"[^A-Za-z0-9_]+", "_", Path(row["source"]).with_suffix("").as_posix())
        relobj = ROOT / "build" / "dump_relocs" / "obj" / f"{stem}.obj"
        census = build.row_object(row).resolve().relative_to(ROOT.resolve()).as_posix()
        out[census] = relobj
    return out


UNRESOLVED = re.compile(r'error LNK20(?:01|19): unresolved external symbol (?:"[^"]*" \((\S+)\)|(\S+))')
DUPLICATE = re.compile(r'^(\S+\.obj) : (?:error LNK2005|warning LNK4006): (?:"[^"]*" \((\S+)\)|(\S+)) '
                       r'already defined in (\S+\.obj)')
REFERRER = re.compile(r"^(\S+\.obj) : error LNK20(?:01|19)")


def trial_link(img, objects, rsp, out, log=print, code=True, libraries=True):
    swap = dump_objects()
    census = [line.strip().strip('"') for line in rsp.read_text(encoding="utf-8").splitlines() if line.strip()]
    linked, swapped, kept, rejected = [], 0, [], []
    sources = dump_sources()
    for rel in census:
        path = swap.get(rel)
        if path is not None and path.exists():
            linked.append(path)
            swapped += 1
            continue
        if path is not None:
            # dump_relocs wrote no relocatable object for this dump source: its own
            # object links only if it proves relocatable itself
            verdict = verify_original_dump(img, ROOT / sources[rel], ROOT / rel)
            (kept if verdict["ok"] else rejected).append({"object": rel, **verdict})
            if not verdict["ok"]:
                continue
        linked.append(ROOT / rel)
    linked = list(dict.fromkeys(linked))
    work = out / "trial"
    work.mkdir(parents=True, exist_ok=True)
    counts = {}
    if code:
        import code_scaffold
        rows = [r for r in build.load_function_rows() if r["target_rva"].startswith("0x")]
        eh_targets = {int(r["target_va"], 16) for r in RL.read_csv_rows(LEDGER / "ledger.csv")
                      if r["rule"] in code_scaffold.EH_RULES}
        census_set = {p.resolve() for p in linked}
        funclet_swaps, funclets, fcounts, refused = code_scaffold.funclet_labels(img, rows, census_set, out,
                                                                                 eh_targets, log)
        linked = [funclet_swaps.get(p.resolve(), p) for p in linked]
        dumped, dump_objs, dcounts = code_scaffold.funclet_dumps(img, refused, out, log)
        funclets.update(dumped)
        linked += dump_objs
        defined, referenced = code_scaffold.object_externals(linked + objects + [out / "obj" / "aliases.obj"])
        data_aliases = {r["name"] for r in RL.read_csv_rows(out / "symbols.csv") if r["role"] == "alias"}
        table, why = code_scaffold.code_aliases(img, rows, referenced - defined, defined, funclets, data_aliases)
        alias_object(table, out / "obj" / "code_aliases.obj")
        with (out / "code_aliases.csv").open("w", newline="", encoding="utf-8") as handle:
            w = csv.writer(handle, lineterminator="\n")
            w.writerow(["alias", "defined_as"])
            w.writerows(sorted(table.items()))
        linked.append(out / "obj" / "code_aliases.obj")
        counts = {"funclet_labels": dict(fcounts), "funclet_bodies_from_retail": dict(dcounts), "code_aliases": len(table), "code_alias_kinds": dict(why),
                  "undefined_before_code_aliases": len(referenced - defined)}
        log(json.dumps(counts))
    linked += objects + [out / "obj" / "aliases.obj"]
    listfile = work / "objects.rsp"
    listfile.write_text("\n".join(f'"{p}"' for p in linked) + "\n", encoding="utf-8")
    link, env = linker()
    extra = []
    if libraries:
        libs, lib_report = retail_libraries(out)
        extra = [str(p) for p in libs] + ["/SAFESEH:NO"]
        counts["libraries"] = lib_report
        log(json.dumps(lib_report))
    cmd = [str(link), "/NOLOGO", "/NODEFAULTLIB", "/INCREMENTAL:NO", "/MACHINE:X86", "/SUBSYSTEM:WINDOWS",
           "/ENTRY:WinMainCRTStartup", f"/OUT:{work / 'trial.exe'}", f"/MAP:{work / 'trial.map'}", f"@{listfile}",
           *extra]
    lock = census_lock_path()
    deadline = time.time() + LOCK_WAIT
    while True:
        try:
            lock.mkdir()
            break
        except FileExistsError:
            if time.time() > deadline:
                raise SystemExit(f"data_scaffold: {lock} held for {LOCK_WAIT // 60} min; not linking")
            time.sleep(30)
    try:
        started = time.time()
        proc = subprocess.run(cmd, capture_output=True, text=True, errors="replace", env=env)
        seconds = time.time() - started
    finally:
        lock.rmdir()
    text = proc.stdout + proc.stderr
    (work / "trial.log").write_text(text, encoding="utf-8")
    meta = {"when": time.strftime("%Y-%m-%d %H:%M"), "objects": len(linked), "dump_objects_swapped": swapped,
            "original_dump_objects_kept": kept, "original_dump_objects_rejected": rejected,
            "complete": not rejected, "seconds": round(seconds), "exit": proc.returncode, **counts}
    (work / "trial_meta.json").write_text(json.dumps(meta), encoding="utf-8")
    return classify_trial(img, objects, text, meta, work, log)


def classify_trial(img, objects, text, meta, work, log=print):
    """Unresolved and duplicate names of a trial link log, classified."""
    import link_census
    rows = [r for r in build.load_function_rows() if r["target_rva"].startswith("0x")]
    classes, detail, dup_kinds, dups = link_census.classify(text, rows)
    scaffold_names = set()
    for path in objects:
        _, symbols = RL.parse_coff(path.read_bytes())
        scaffold_names |= {s["name"] for s in symbols.values() if s["storage"] == EXTERNAL and s["section"] > 0}
    # why the scaffold left a name undefined: its role in the ledger's names.csv,
    # else the extent that holds its address
    roles = {}
    for row in RL.read_csv_rows(LEDGER / "names.csv"):
        roles.setdefault(row["name"], row["role"])
    spans = sorted((int(r["start"], 16), int(r["end"], 16), r["source"])
                   for r in RL.read_csv_rows(LEDGER / "items.csv") if r["source"] != "scaffold")
    starts = [s for s, _, _ in spans]
    code_link = {}
    for row in RL.read_csv_rows(LEDGER / "ledger.csv"):
        if row["link_symbol"].startswith("g_") and row["target_section"] == ".text":
            code_link.setdefault(row["link_symbol"], row["link_class"])

    def holder(va):
        i = bisect.bisect_right(starts, va) - 1
        return spans[i][2] if i >= 0 and va < spans[i][1] else "none"

    refined = collections.Counter()
    for name, entry in detail.items():
        kind = entry["kind"]
        m = re.fullmatch(r"g_([0-9A-F]{8})", name)
        if m:
            va = int(m.group(1), 16)
            section = (img.section(va) or "outside").strip(".")
            if section == "text":
                why = code_link.get(name, "dump-reference")
            elif section in ("rdata", "data"):
                why = "inside-" + holder(va)
            else:
                why = section
            kind = f"g_{section}:{why}"
        elif kind == "unpinned" and name in RL.KNOWN_ABSOLUTE:
            kind = "crt-absolute"
        elif kind == "data":
            kind = "data:" + roles.get(name, "not-a-data-address")
        refined[kind] += 1
        entry["kind"] = kind
    dup_refined = collections.Counter()
    for name, objs in dups.items():
        involved = any(Path(o).name.startswith(("scaffold_", "aliases")) for o in objs)
        dup_refined[("scaffold-" if involved else "") + ("data" if name in scaffold_names else "other")] += 1
    fatal = sorted(set(re.findall(r"fatal error (LNK\d+)", text)))
    refs = collections.Counter()
    for line in text.splitlines():
        found = UNRESOLVED.search(line)
        if found and REFERRER.match(line):
            refs[found.group(1) or found.group(2)] += 1
    summary = {**meta, "fatal": fatal, "unresolved": sum(refined.values()), "unresolved_classes": dict(refined),
               "duplicates": len(dups), "duplicate_classes": dict(dup_refined),
               "duplicate_classes_census": dict(dup_kinds),
               "unpinned_residue": residue([n for n, e in detail.items() if e["kind"] == "unpinned"], refs)}
    (work / "trial.json").write_text(json.dumps({**summary, "unresolved_detail": detail, "duplicate_detail": dups},
                                                indent=1), encoding="utf-8")
    write_queue(work.parent / "queue.csv", text, detail, rows, img)
    log(json.dumps(summary, indent=1))
    return summary


def qualified(name):
    """The part of a name that survives a signature change: `?f@C@@` of a mangled
    name, the bare identifier of a C one."""
    if name.startswith("?"):
        i = name.find("@@")
        return name[:i + 2] if i > 0 else name
    return re.sub(r"@\d+$", "", name.lstrip("_"))


def write_queue(path, text, detail, rows, img):
    """queue.csv: one row per unresolved name -- class, cause group, referring
    objects, a suggested owner row and the evidence for it. A suggestion is a
    lead, never an identity: `address` rows come from a pin or an address-derived
    name, `same-qualified-name` rows only share the name up to the signature."""
    referrers = collections.defaultdict(list)
    for line in text.splitlines():
        found = UNRESOLVED.search(line)
        ref = REFERRER.match(line)
        if found and ref:
            referrers[found.group(1) or found.group(2)].append(Path(ref.group(1)).name)
    pinned = {}
    with (ROOT / "targets/game/reverse/symbols.csv").open(newline="", encoding="utf-8") as handle:
        for row in csv.reader(handle):
            if len(row) >= 2 and row[1].startswith("0x"):
                pinned.setdefault(row[0], int(row[1], 16))
    dir32 = {}
    for row in RL.read_csv_rows(build.DIR32_ADDRESSES):
        dir32.setdefault(row["name"], int(row["va"], 16))
    roles = {}
    if (LEDGER / "names.csv").exists():
        for row in RL.read_csv_rows(LEDGER / "names.csv"):
            roles.setdefault(row["name"], row["role"])
    at = collections.defaultdict(list)
    by_qualified = collections.defaultdict(list)
    for row in rows:
        at[int(row["target_rva"], 16)].append(row)
        by_qualified[qualified(row["name"])].append(row)
    import code_scaffold
    calls = code_scaffold.call_targets(img, LEDGER / "call_targets.csv")
    out = []
    for name, entry in sorted(detail.items()):
        kind = entry["kind"]
        cause = next(c for c, rx in RESIDUE_CAUSES if rx.search(name)) if kind == "unpinned" else kind
        suggestion, evidence = "", ""
        m = re.fullmatch(r"g_([0-9A-F]{8})", name)
        rva, how = (int(m.group(1), 16) - img.base, "address-derived name") if m else (None, "")
        if not m and name in pinned:
            rva, how = code_scaffold.resolve_pin(name, pinned[name], lambda r: bool(at.get(r)), dir32, calls)
            if rva is None:
                readings = " or ".join(f"0x{r:08X}" for r in code_scaffold.pin_readings(pinned[name]))
                out.append([name, entry["kind"], cause, len(referrers.get(name, [])),
                            " ".join(sorted(set(referrers.get(name, [])))[:5]), "",
                            f"symbols.csv pin 0x{pinned[name]:08X}: {how} (RVA {readings})"])
                continue
            words = {"rva": "RVA", "va": "VA", "dir32": "the dir32 address",
                     "call-target": "where verified calls land"}
            how = "symbols.csv pin read as " + " and ".join(words[h] for h in how.split("+"))
        if rva is not None:
            owners = [r for r in at.get(rva, []) if not r["name"].startswith("?j_")] or at.get(rva, [])
            if owners:
                suggestion = owners[0]["name"]
                evidence = f"address 0x{rva:08X} ({how}); row source {owners[0]['source']}"
            else:
                evidence = f"address 0x{rva:08X} has no ledger row"
        elif name in dir32:
            va = dir32[name]
            owners = at.get(va - img.base, [])
            suggestion = owners[0]["name"] if owners else ""
            evidence = f"dir32_addresses.csv 0x{va:08X} ({img.section(va) or 'outside'}); " \
                       f"ledger names.csv role {roles.get(name, 'none')}"
        else:
            same = [r for r in by_qualified.get(qualified(name), []) if r["name"] != name]
            if same:
                suggestion = same[0]["name"]
                evidence = f"same-qualified-name at {same[0]['target_rva']} ({len(same)} row(s)); signature differs"
        refs = referrers.get(name, [])
        out.append([name, kind, cause, len(refs), " ".join(sorted(set(refs))[:5]), suggestion, evidence])
    out.sort(key=lambda r: (-r[3], r[0]))
    with path.open("w", newline="", encoding="utf-8") as handle:
        w = csv.writer(handle, lineterminator="\n")
        w.writerow(["name", "class", "cause", "referring_objects", "referrers_first5", "suggested_owner_row",
                    "evidence"])
        w.writerows(out)


RESIDUE_CAUSES = (
    ("crt", re.compile(r"^_[^?]|^__|^\?\?[23]@YAPAXI@Z$|^\?\?[23]@YAXPAX@Z$")),
    ("vtable/rtti", re.compile(r"^\?\?_[7R]")),
    ("invented Bfme*/Rva*/Gen* name", re.compile(r"Bfme|BFME|bfme|Rva[0-9A-Fa-f]{8}|Gen_?[0-9A-Fa-f]{8}|Rva[0-9A-F]")),
    ("ctor/dtor (private class copies)", re.compile(r"^\?\?[01]|^\?\?_[DEG]")),
    ("operator", re.compile(r"^\?\?[2-9A-Z]|^\?\?_[0-9A-Z]")),
    ("static/global data", re.compile(r"^\?[^?].*@@[23]")),
    ("other method or function", re.compile(r".")),
)


def residue(names, refs, top=12):
    """Unpinned names grouped by cause, with the most-referenced first (references =
    referring objects in the link log)."""
    groups = collections.defaultdict(list)
    for name in names:
        cause = next(c for c, rx in RESIDUE_CAUSES if rx.search(name))
        groups[cause].append(name)
    out = {}
    for cause, members in sorted(groups.items(), key=lambda kv: -len(kv[1])):
        ranked = sorted(members, key=lambda n: (-refs.get(n, 0), n))
        out[cause] = {"names": len(members), "references": sum(refs.get(n, 0) for n in members),
                      "top": [[n, refs.get(n, 0)] for n in ranked[:top]]}
    return out


# --------------------------------------------------------------------------- driver

def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--ledger", type=Path, default=LEDGER, help="tools/reloc_ledger.py output directory")
    ap.add_argument("--out", type=Path, default=OUT)
    ap.add_argument("--link-check", action="store_true", help="also link the scaffold alone at a moved base")
    ap.add_argument("--trial-link", action="store_true", help="also link the whole program without /FORCE")
    ap.add_argument("--no-code-scaffold", action="store_true",
                    help="trial link without funclet labels and code aliases (tools/code_scaffold.py)")
    ap.add_argument("--no-libraries", action="store_true",
                    help="trial link without msvcrt.lib, the import libraries and retail's .res")
    ap.add_argument("--reclassify", action="store_true", help="classify the last trial link's log again")
    ap.add_argument("--census-rsp", type=Path, default=ROOT / "build" / "link_census" / "objects.rsp",
                    help="the census's object list (repo-relative paths)")
    args = ap.parse_args(argv)
    img = RL.Image()
    items, relocs, scan, names = load(args.ledger)
    args.out.mkdir(parents=True, exist_ok=True)
    objects, labels, aliases, problems, unlinkable = emit(img, items, relocs, names, args.out)
    checks, failures = verify(img, objects, relocs, scan, labels, unlinkable)
    report = {"objects": len(objects), "items": len(items), "labels": len(labels), "aliases": len(aliases),
              "bytes": sum(it["end"] - it["start"] for it in items),
              "bss_bytes": sum(it["end"] - it["start"] for it in items if it["proof"] == "uninitialised"),
              "unlinkable": dict(problems), "verify": checks, "failures": failures[:50]}
    if args.link_check:
        report["link_check"], link_failures = link_check(img, objects, labels, aliases, scan, args.out)
        report["link_failures"] = link_failures[:50]
    if args.trial_link:
        report["trial"] = trial_link(img, objects, args.census_rsp, args.out, code=not args.no_code_scaffold,
                                     libraries=not args.no_libraries)
    elif args.reclassify:
        work = args.out / "trial"
        report["trial"] = classify_trial(img, objects, (work / "trial.log").read_text(encoding="utf-8"),
                                         json.loads((work / "trial_meta.json").read_text(encoding="utf-8")), work)
    (args.out / "verify.json").write_text(json.dumps(report, indent=1), encoding="utf-8")
    if report.get("trial") and not report["trial"].get("complete", True):
        print("data_scaffold: trial INCOMPLETE -- a dump source's object was rejected (not relocatable)")
        return 1
    print(json.dumps({k: v for k, v in report.items() if k != "failures"}, indent=1))
    bad = checks.get("retail_differs", 0) or checks.get("field_not_moved", 0) or checks.get("byte_changed", 0) \
        or checks.get("unlisted_literals", 0) or (args.link_check and not report["link_check"].get("linked"))
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
