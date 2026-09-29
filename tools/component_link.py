#!/usr/bin/env python3
"""Link one vendored component with a test driver, run it, and account for it.

The byte gates prove one function at a time; the census links everything under
/FORCE. This checks one small component end to end: the objects the census
links for its matched rows (build.row_object, compiled by build.py's own
command and proven current by link_census.object_current), plus a driver in
tools/tests/component_link/, linked by MSVC 7.1 link.exe with /NODEFAULTLIB and an
explicit msvcrt.lib + kernel32.lib. No /FORCE, no /ALTERNATENAME, no alias
object, no weak externals: an unresolved or duplicate name fails the link.

  python3 tools/component_link.py zlib      # also: lzhl, lua

It prints and checks:
  externals   every name the component references that its own objects do
              not define, where the map says it resolved, and whether retail
              imports it (link_census.excused). The driver may not define one
              unless the component lists it as a labelled test double.
  selected    the object the map took each component definition from; a COMDAT
              whose copies differ across the linked objects; any duplicate.
  retail      each section of each component object placed at its retail
              address -- code from its ledger row, everything else DERIVED from
              the relocations retail's own code carries (a static table has no
              name in retail, but the instruction that reads it holds its
              address) -- then compared byte for byte outside relocation
              fields. Two derivations that disagree are a conflict; an import
              reached through a slot other than retail's is a conflict too.
  run         the driver's PASS/FAIL lines (zlib: plus Python's zlib inflating
              our streams and ours inflating Python's).

Exit status is non-zero on any unresolved, duplicate, differing COMDAT,
driver-defined dependency, stale object, byte mismatch, conflict or test
failure. Artifacts: build/component_link/<component>/.
"""
import argparse
import collections
import csv
import os
import re
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402
import link_census  # noqa: E402

HERE = ROOT / "tools" / "tests" / "component_link"  # fixtures: the placement hook allows sources there
OUT = ROOT / "build" / "component_link"
BASE = 0x400000
DIR32, DIR32NB, REL32 = 0x0006, 0x0007, 0x0014
EXTERNAL, STATIC, WEAK_EXTERNAL = 2, 3, 105
SKIP_FLAGS = 0x00000800 | 0x00000200 | 0x02000000  # LNK_REMOVE | LNK_INFO | DISCARDABLE (.drectve, .debug$*)
UNINITIALIZED = 0x00000080
JMP_INDIRECT = bytes([0xFF, 0x25])  # an import thunk: jmp [IAT slot]

COMPONENTS = {
    "zlib": {
        "sources": ["game/Libraries/Source/Compression/ZLib/"],
        "driver": "zlib_harness.c",
        "include": ["game/Libraries/Source/Compression/ZLib"],
        "doubles": {},
    },
    "lzhl": {
        # mem_ops.cpp: retail's LZHL `new`/`delete` call the game's own operators
        # (0x881F30/0x881EB0), not MSVCR71's, so they are part of the closure.
        "sources": ["game/Libraries/Source/Compression/LZHCompress/CompLibSource/",
                    "game/Libraries/Source/Compression/LZHCompress/NoxCompress.cpp",
                    "game/Libraries/Source/WWVegas/WWLib/mem_ops.cpp"],
        "driver": "lzhl_harness.cpp",
        "include": [],
        "doubles": {
            "___gameMemAllocPtr": "retail 0x0130E9B4, set at run time by the game's memory manager; "
                                  "the driver points it at malloc",
            "___gameMemFreePtr": "retail 0x0130E9AC, likewise; the driver points it at free",
        },
    },
    "lua": {
        "sources": ["game/Libraries/Source/Lua/"],
        "driver": "lua_harness.cpp",
        "include": ["game/Libraries/Source/Lua"],
        # name -> why the driver defines it (reported as a TEST DOUBLE, never as resolved)
        "doubles": {
            "?bfmeLogMsg574@@YAXPBD@Z": "luaB_print's game logger; retail's body is only the gen_asm "
                                        "dump ?d_002e5090, so the driver records the text instead",
        },
    },
}


def rows_for(sources):
    """Matched ledger rows whose source starts with one of `sources`, streamed."""
    out = []
    with (ROOT / "targets/game/reverse/functions.csv").open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            if row.get("status") == "matched" and (row.get("target_rva") or "").startswith("0x") \
                    and any(row["source"].startswith(s) for s in sources):
                out.append(row)
    return out


def rel(path):
    return Path(path).resolve().relative_to(ROOT.resolve()).as_posix()


def ensure_objects(rows):
    """[object] for the rows, compiled by build.py's command when missing or stale."""
    objs, stale = [], []
    for row in rows:
        obj = build.row_object(row)
        if obj in objs:
            continue
        objs.append(obj)
        source = ROOT / row["source"]
        if not obj.exists() or not link_census.object_current(source, obj):
            build.compile_source(source, obj)
            if not link_census.object_current(source, obj):
                stale.append(obj.name)
    return objs, stale


# ---------------------------------------------------------------- COFF reading

def coff(obj):
    data = obj.read_bytes()
    count, _, table, nsyms, optional = struct.unpack_from("<HIIIH", data, 2)
    sections = []
    for index in range(count):
        at = 20 + optional + index * 40
        name = data[at:at + 8].rstrip(b"\0").decode("latin-1")
        size, pointer, relocs = struct.unpack_from("<III", data, at + 16)
        nrelocs = struct.unpack_from("<H", data, at + 32)[0]
        flags = struct.unpack_from("<I", data, at + 36)[0]
        body = data[pointer:pointer + size] if pointer and not flags & UNINITIALIZED else None
        fixups = [struct.unpack_from("<IIH", data, r) for r in range(relocs, relocs + 10 * nrelocs, 10)]
        sections.append({"number": index + 1, "name": name, "size": size, "flags": flags,
                         "body": body, "relocs": fixups})
    symbols = {s["index"]: s for s in link_census._coff_symbols(data)}
    return sections, symbols


def section_members(symbols, number):
    """Named symbols in a section, by offset (external and static)."""
    named = [s for s in symbols.values() if s["section"] == number and s["storage"] in (EXTERNAL, STATIC)
             and not s["name"].startswith((".", "$"))]
    return [s["name"] for s in sorted(named, key=lambda s: (s["value"], s["storage"] != EXTERNAL))]


def section_label(sections, symbols, number):
    members = section_members(symbols, number)
    return members[0] if members else sections[number - 1]["name"]


# ------------------------------------------------------- retail placement check

class Placement:
    """Place every section of the component's objects at its retail address.

    Anchors: a symbol whose ledger row gives an RVA (functions), or a
    dir32_addresses.csv data name. Propagation: a relocation in a placed
    section, read against retail's bytes there, gives the retail address of
    its target, so the target's section is placed too (fixed point).
    """

    def __init__(self, objs, rows):
        self.image, self.pe = build.exe_image()
        self.objs = {obj.name: coff(obj) for obj in objs}
        self.base = {}          # (obj, section) -> retail rva
        self.why = {}           # (obj, section) -> evidence text
        self.conflicts = []
        self.imports = []       # (obj, name, retail slot rva used, expected slots)
        self.defined = {}       # external name -> (obj, section, value)
        for name, (sections, symbols) in self.objs.items():
            for s in symbols.values():
                if s["storage"] == EXTERNAL and s["section"] > 0:
                    self.defined.setdefault(s["name"], (name, s["section"], s["value"]))
        # A row anchors a symbol of ITS object only: two TUs' statics share
        # names (_read_number in liolib.c and llex.c). A gen-alias row claims a
        # second address for another row's body; it names no symbol here.
        self.anchor_obj = collections.defaultdict(lambda: collections.defaultdict(set))
        self.aliases = []
        for row in rows:
            if "gen-alias" in (row.get("notes") or ""):
                self.aliases.append(row)
                continue
            for key in {row["name"], build.ledger_object_symbol(row)}:
                self.anchor_obj[build.row_object(row).name][key].add(int(row["target_rva"], 16))
        self.anchor_ext = collections.defaultdict(set)  # an external COMDAT: every object's copy is one symbol
        for names in self.anchor_obj.values():
            for key, rvas in names.items():
                self.anchor_ext[key] |= rvas
        self.anchors = collections.defaultdict(set)  # external names: dir32 data, other sources' rows
        with (ROOT / "targets/game/reverse/dir32_addresses.csv").open(newline="", encoding="utf-8") as handle:
            for row in csv.DictReader(handle):
                self.anchors[row["name"]].add(int(row["va"], 16) - BASE)
        self.slots = collections.defaultdict(set)
        for name, slot in link_census.retail_import_slots():
            self.slots[name].add(slot)
        self.outside = collections.defaultdict(set)  # external name -> retail addresses its references reach
        wanted = {s["name"] for _, symbols in self.objs.values() for s in symbols.values()
                  if s["storage"] == EXTERNAL and s["section"] == 0 and s["name"] not in self.defined}
        self.ledger_rows = collections.defaultdict(list)
        with (ROOT / "targets/game/reverse/functions.csv").open(newline="", encoding="utf-8") as handle:
            for row in csv.DictReader(handle):
                if row["name"] in wanted and (row.get("target_rva") or "").startswith("0x"):
                    self.anchors[row["name"]].add(int(row["target_rva"], 16))
                    self.ledger_rows[row["name"]].append(row)

    def read(self, rva, size):
        try:
            offset = build.rva_to_file_offset(self.pe, rva)
        except ValueError:
            return None
        chunk = self.image[offset:offset + size]
        return chunk if len(chunk) == size else None

    def place(self, key, rva, evidence):
        if key in self.base:
            if self.base[key] != rva:
                self.conflicts.append(f"{key[0]} section {key[1]}: 0x{self.base[key]:08X} ({self.why[key]}) "
                                      f"vs 0x{rva:08X} ({evidence})")
            return False
        self.base[key] = rva
        self.why[key] = evidence
        return True

    def run(self):
        queue = []
        for name, (sections, symbols) in self.objs.items():
            for s in symbols.values():
                if s["section"] <= 0 or s["storage"] not in (EXTERNAL, STATIC):
                    continue
                known = self.anchor_obj[name].get(s["name"])
                if not known and s["storage"] == EXTERNAL:
                    known = self.anchor_ext.get(s["name"]) or self.anchors.get(s["name"])
                if known:
                    for rva in sorted(known):
                        key = (name, s["section"])
                        if self.place(key, rva - s["value"], f"ledger {s['name']}"):
                            queue.append(key)
        while queue:
            obj, number = queue.pop()
            sections, symbols = self.objs[obj]
            section = sections[number - 1]
            if section["body"] is None:
                continue
            start = self.base[(obj, number)]
            retail = self.read(start, section["size"])
            if retail is None or self.masked_diff(section, retail):
                continue  # a section that is not retail's says nothing about where its targets are
            for where, index, kind in section["relocs"]:
                target = symbols.get(index)
                if target is None or kind not in (DIR32, DIR32NB, REL32) or where + 4 > section["size"]:
                    continue
                addend = struct.unpack_from("<i", section["body"], where)[0]
                value = struct.unpack_from("<i", retail, where)[0]
                if kind == DIR32:
                    address = (value - addend - BASE) & 0xFFFFFFFF
                elif kind == DIR32NB:
                    address = (value - addend) & 0xFFFFFFFF
                else:
                    address = (start + where + 4 + value - addend) & 0xFFFFFFFF
                evidence = f"{section_label(sections, symbols, number)}+0x{where:X} in retail"
                if target["section"] > 0:
                    key, offset = (obj, target["section"]), target["value"]
                elif target["storage"] == EXTERNAL and target["name"] in self.defined:
                    owner, sec, offset = self.defined[target["name"]]
                    key = (owner, sec)
                else:
                    key = None
                if key is not None:
                    address = self.through_stub(key, address)
                elif target["name"].startswith("__imp_"):
                    bare = target["name"][len("__imp_"):]
                    # the C name first: __imp__exit is exit's slot, not _exit's
                    expected = self.slots.get(link_census._undecorate(bare)) or self.slots.get(bare) or set()
                    self.imports.append((obj, target["name"], address, expected))
                    continue
                else:
                    self.outside[target["name"]].add(address)
                    known = self.anchors.get(target["name"])
                    if known and address not in known:
                        self.conflicts.append(f"{evidence}: {target['name']} at 0x{address:08X}, "
                                              f"ledger says {sorted(hex(a) for a in known)}")
                    continue
                if self.place(key, address - offset, evidence):
                    queue.append(key)

    def through_stub(self, key, address):
        """Retail was linked incrementally: a call or a function pointer may
        name an ILT jump stub (`jmp body`) rather than the body. Follow it when
        the target is code that does not itself start with a jmp."""
        section = self.objs[key[0]][0][key[1] - 1]
        head = self.read(address, 5)
        starts_jmp = bool(section["body"]) and section["body"][0] == 0xE9
        if section["name"].startswith(".text") and head and head[0] == 0xE9 and not starts_jmp:
            return (address + 5 + struct.unpack_from("<i", head, 1)[0]) & 0xFFFFFFFF
        return address

    @staticmethod
    def masked_diff(section, retail):
        """Offsets where the section differs from retail outside relocation fields."""
        ours, theirs = bytearray(section["body"]), bytearray(retail)
        for where, _, kind in section["relocs"]:
            width = 2 if kind == 0x000A else 4
            ours[where:where + width] = theirs[where:where + width]
        return [i for i in range(len(ours)) if ours[i] != theirs[i]]

    def find_content(self, body):
        """Retail RVAs outside .text holding exactly these bytes."""
        found = []
        for sec in self.pe:
            if sec["name"] in (".rdata", ".data"):
                data = self.image[sec["raw_pointer"]:sec["raw_pointer"] + sec["size"]]
                at = data.find(body)
                while at >= 0 and len(found) < 3:
                    found.append(sec["rva"] + at)
                    at = data.find(body, at + 1)
        return found

    def compare(self):
        """[(obj, label, section name, size, rva or None, verdict)] for every section."""
        results = []
        for obj, (sections, symbols) in self.objs.items():
            for section in sections:
                if section["flags"] & SKIP_FLAGS or section["size"] == 0:
                    continue
                key = (obj, section["number"])
                label = section_label(sections, symbols, section["number"])
                rva = self.base.get(key)
                if rva is None:
                    verdict = "unplaced"
                    if section["body"] is not None and not section["relocs"] and section["size"] >= 8                             and not section["name"].startswith(".text"):
                        hits = self.find_content(section["body"])
                        if len(hits) == 1:
                            rva, verdict = hits[0], "content only (no reference places it)"
                elif section["body"] is None:
                    verdict = "bss (placed, no bytes)"
                else:
                    retail = self.read(rva, section["size"])
                    if retail is None:
                        verdict = "outside retail's raw data"
                    else:
                        diff = self.masked_diff(section, retail)
                        verdict = "match" if not diff else f"MISMATCH ({len(diff)} bytes, first +0x{diff[0]:X})"
                results.append((obj, label, section["name"], section["size"], rva, verdict,
                                section_members(symbols, section["number"])))
        return results


# ------------------------------------------------------------------ link + run

def toolchain():
    root = build.vc71_root()
    return root, build.compiler_environment(root)


def compile_driver(component, spec, out):
    root, env = toolchain()
    source = HERE / spec["driver"]
    obj = out / (source.stem + ".obj")
    command = [str(root / "Vc7" / "bin" / "cl.exe"), "-nologo", "-c", "-O2", "-MD", "-W3",
               *[f"-I{inc}" for inc in spec["include"]], f"-Fo{rel(obj)}", rel(source)]
    if sys.platform != "win32":
        command.insert(0, "wine")
    result = subprocess.run(command, capture_output=True, text=True, errors="replace", env=env, cwd=ROOT)
    if result.returncode:
        raise SystemExit(f"driver compile failed:\n{result.stdout}{result.stderr}")
    return obj


def link(objs, driver, out):
    root, env = toolchain()
    libs = [root / "Vc7" / "lib" / "msvcrt.lib", root / "Vc7" / "lib" / "kernel32.lib"]
    exe, mapfile = out / "component.exe", out / "component.map"
    command = [str(root / "Vc7" / "bin" / "link.exe"), "/NOLOGO", "/NODEFAULTLIB", "/INCREMENTAL:NO",
               "/MACHINE:X86", "/SUBSYSTEM:CONSOLE", "/VERBOSE", f"/MAP:{rel(mapfile)}", f"/OUT:{rel(exe)}",
               rel(driver), *[rel(o) for o in objs], *[str(lib) for lib in libs]]
    assert not any(a.upper().startswith(("/FORCE", "/ALTERNATENAME")) for a in command)
    if sys.platform != "win32":
        command.insert(0, "wine")
    result = subprocess.run(command, capture_output=True, text=True, errors="replace", env=env, cwd=ROOT)
    log = result.stdout + result.stderr
    (out / "link.log").write_text(log, encoding="utf-8")
    return result.returncode, log, exe, mapfile


def map_publics(mapfile, statics=False):
    """{symbol: [lib:object, ...]} from the map's publics, or with `statics`
    its static symbols too (a TU's static shares a name with another TU's
    external: lbaselib.c's luaB_print)."""
    found = collections.defaultdict(list)
    for line in mapfile.read_text(errors="replace").splitlines():
        if line.strip() == "Static symbols" and not statics:
            break
        parts = line.split()
        if len(parts) >= 4 and re.fullmatch(r"[0-9a-f]{4}:[0-9a-f]{8}", parts[0]) \
                and re.fullmatch(r"[0-9a-f]{8}", parts[2]):
            found[parts[1]].append(parts[-1])
    return found


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    parser.add_argument("component", choices=sorted(COMPONENTS))
    args = parser.parse_args(argv)
    spec = COMPONENTS[args.component]
    out = OUT / args.component
    out.mkdir(parents=True, exist_ok=True)
    failures = []

    rows = rows_for(spec["sources"])
    objs, stale = ensure_objects(rows)
    print(f"component {args.component}: {len(rows)} matched rows in {len(objs)} objects")
    for name in stale:
        failures.append(f"stale object {name}")

    # What the component needs from outside itself, from the objects.
    facts = {obj.name: link_census.object_facts(obj, truth=_NoTruth()) for obj in objs}
    defines = set()
    for copies, strong, _ in facts.values():
        defines |= set(strong) | {name for name, *_ in copies}
    needs = collections.defaultdict(set)
    for obj, (_, _, undefined) in facts.items():
        for name in undefined:
            if name not in defines:
                needs[name].add(obj)

    driver = compile_driver(args.component, spec, out)
    code, log, exe, mapfile = link(objs, driver, out)
    for line in log.splitlines():
        if re.search(r"error LNK|warning LNK", line):
            failures.append(f"link: {line.strip()}")
    if code or not exe.exists():
        failures.append(f"link.exe exited {code}")
        for line in failures:
            print("FAIL", line)
        return 1
    publics, in_image = map_publics(mapfile), map_publics(mapfile, statics=True)
    _, driver_defines, _ = link_census.object_facts(driver, truth=_NoTruth())

    placement = Placement(objs, rows)
    placement.run()
    runtime = link_census.library_symbols(build.vc71_root() / "Vc7" / "lib" / "msvcrt.lib")
    stubs, imported = link_census.import_stubs(), link_census.retail_imports()
    print(f"\nexternals ({len(needs)}): name -> where the link resolved it; retail imports it?")
    for name in sorted(needs):
        where = publics.get(name) or publics.get(name.replace("__imp_", "", 1)) or ["not in image (unreferenced)"]
        from_driver = name in driver_defines
        ok = link_census.excused(name, runtime, imported, stubs)
        note = "yes" if ok else "NO"
        if from_driver:
            if name in spec["doubles"]:
                note = f"TEST DOUBLE in driver: {spec['doubles'][name]}"
            else:
                failures.append(f"{name} is defined by the driver, not the component or the CRT")
                note = "DRIVER-DEFINED"
        elif not ok:
            failures.append(f"{name}: retail does not import it")
        reached = placement.outside.get(name)
        if reached:
            shown = []
            for address in sorted(reached):
                head = placement.read(address, 5) or b""
                stub = head[:1] == b"\xe9"
                body = (address + 5 + struct.unpack_from("<i", head, 1)[0]) & 0xFFFFFFFF if stub else None
                shown.append(f"0x{address:08X}" + (f" (jmp 0x{body:08X})" if stub else ""))
            note += f"; retail calls {', '.join(shown)}"
        print(f"  {name:<40} {','.join(sorted(set(where))):<34} {note}   (from {', '.join(sorted(needs[name]))})")
    print("  import-library resolutions whose retail call target is a body, not an import thunk:")
    divergent = 0
    for name in sorted(needs):
        where = publics.get(name) or []
        reached = placement.outside.get(name)
        if name.startswith("__imp_") or not reached or not any(".dll" in w.lower() for w in where):
            continue
        bodies = [a for a in sorted(reached) if (placement.read(a, 2) or b"") != JMP_INDIRECT]
        if bodies:
            divergent += 1
            rows_at = placement.ledger_rows.get(name, [])
            owner = ", ".join(f"{r['source']}" for r in rows_at) or "no ledger row"
            line = (f"{name}: linked from {','.join(where)}, retail calls a body at "
                    f"{', '.join(f'0x{a:08X}' for a in bodies)} ({owner})")
            print("    DIVERGENT", line)
            failures.append(line)
    if not divergent:
        print("    none")

    print("\nselected definitions:")
    names = {obj.name: obj.stem for obj in objs}
    elsewhere, shared = [], collections.defaultdict(set)
    for obj, (copies, strong, _) in facts.items():
        for name in strong:
            where = publics.get(name)
            if where and not any(Path(w).name == obj for w in where):
                elsewhere.append(f"{name}: defined in {obj}, map took {where}")
        for name, *_ in copies:
            shared[name].add(obj)
    driver_comdats = {name for name, *_ in link_census.comdat_bodies(driver)}
    strong_total = sum(len(s) for _, s, _ in facts.values())
    print(f"  {strong_total} exclusive definitions; {strong_total - len(elsewhere)} taken from their own object")
    for line in elsewhere:
        print("  ELSEWHERE", line)
        failures.append(line)
    multi = {n: o for n, o in shared.items() if len(o) > 1 or n in driver_comdats}
    print(f"  {len(shared)} COMDAT symbols; {len(multi)} with more than one copy in the link "
          f"(the map names the copy kept):")
    for name in sorted(multi):
        copies = sorted(multi[name]) + (["<driver>"] if name in driver_comdats else [])
        print(f"    {name[:60]:<60} kept {','.join(publics.get(name, ['?']))}  of {len(copies)}")
    conflicts = link_census.comdat_conflicts(objs + [driver])
    print(f"  COMDATs with differing copies across the linked objects: {len(conflicts)}")
    for name, copies in sorted(conflicts.items()):
        print(f"    {name}: {copies}")
        failures.append(f"differing COMDAT {name}")
    strong_by = collections.Counter(n for _, s, _ in facts.values() for n in s)
    dupes = [n for n, c in strong_by.items() if c > 1]
    print(f"  duplicate strong definitions: {len(dupes)}")
    failures += [f"duplicate {n}" for n in dupes]

    results = placement.compare()
    counts = collections.Counter(r[5].split(" ")[0] for r in results)
    print(f"\nretail placement: {len(results)} sections; {dict(counts)}")
    code = [r for r in results if r[2].startswith(".text")]
    print(f"  code: {len(code)} sections, {sum(r[5] == 'match' for r in code)} match retail (at a ledger "
          f"address or one retail's own references give) with every relocation landing where retail's does")
    print(f"  data ({len(results) - len(code)} sections):")
    for obj, label, sname, size, rva, verdict, members in results:
        if verdict == "unplaced":
            # No retail evidence places it. Harmless only if the link dropped it
            # (an inline COMDAT retail never emitted out of line, a scaffold).
            kept = [m for m in members if m in in_image]
            verdict = "unplaced, IN THE IMAGE" if kept else "unplaced, not in the image"
            if kept:
                failures.append(f"{obj} {label}: linked into the image but no retail evidence places it")
        if not sname.startswith(".text") or not verdict.startswith("match"):
            where = f"0x{rva:08X}" if rva is not None else "-"
            print(f"    {Path(obj).stem.split('_')[-1]:<22} {sname:<8} {size:>6} {where:>11} {verdict:<26} "
                  f"{', '.join(members)[:160] or label}")
        if verdict.startswith("MISMATCH") or verdict.startswith("outside"):
            failures.append(f"{obj} {label}: {verdict}")
    for obj, name, address, expected in placement.imports:
        if address not in expected:
            failures.append(f"{obj}: {name} read through 0x{address:08X}, retail's slots {sorted(map(hex, expected))}")
    print(f"  imports read through retail's own IAT slot: "
          f"{sum(a in e for *_, a, e in placement.imports)} of {len(placement.imports)} references")
    placed_at = {rva: set(section_members(placement.objs[o][1], n)) for (o, n), rva in placement.base.items()}
    orphans = [r for r in placement.aliases
               if build.ledger_object_symbol(r) not in placed_at.get(int(r["target_rva"], 16), ())]
    if orphans:  # reported, not failed: the ledger's claim, not the link's
        print(f"  gen-alias rows giving a component body a second retail address "
              f"(a real link emits one copy; those addresses get none): "
              + ", ".join(f"{r['target_rva']}={build.ledger_object_symbol(r)}" for r in orphans))
    for line in placement.conflicts:
        print("  CONFLICT", line)
        failures.append(f"placement conflict: {line}")

    print("\nrun:")
    failures += run(args.component, exe, out)
    print()
    for line in failures:
        print("FAIL", line)
    print(f"component {args.component}: {'FAIL' if failures else 'PASS'} ({len(failures)} failure(s))")
    return 1 if failures else 0


class _NoTruth:
    """object_facts wants a retail judge for COMDAT copies; Placement does that here."""
    def verdict(self, *args):
        return None


def run(component, exe, out):
    import zlib
    failures = []
    env = dict(os.environ)
    root = build.vc71_root()
    env["PATH"] = os.pathsep.join([str(root.parents[1]), env.get("PATH", "")])  # msvcr71.dll
    if component == "zlib":
        raw = bytes((i * 31 + (i >> 7)) & 0xFF for i in range(200000)) + b"gondor calls for aid " * 3000
        (out / "py.raw").write_bytes(raw)
        (out / "py.z").write_bytes(zlib.compress(raw, 9))
    command = [str(exe), str(out)]
    if sys.platform != "win32":
        command.insert(0, "wine")
    result = subprocess.run(command, capture_output=True, text=True, errors="replace", env=env, timeout=300)
    print(result.stdout.rstrip())
    if result.returncode:
        failures.append(f"driver exited {result.returncode} {result.stderr.strip()}")
    if component == "zlib":
        for name in ("text", "random"):
            try:
                ok = zlib.decompress((out / f"{name}.z").read_bytes()) == (out / f"{name}.raw").read_bytes()
            except (OSError, zlib.error) as error:
                ok = False
                print(f"  {name}.z: {error}")
            print(f"{'PASS' if ok else 'FAIL'} Python's zlib inflates our {name}.z to the original")
            if not ok:
                failures.append(f"Python cross-check {name}.z")
    return failures


if __name__ == "__main__":
    sys.exit(main())
