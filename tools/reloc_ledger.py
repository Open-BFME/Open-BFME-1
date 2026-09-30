#!/usr/bin/env python3
"""Typed relocation ledger for retail's data, and the data item partition.

Retail has no .reloc and no PDB, so no single table says which dwords of
.rdata/.data are pointers. A pointer scan is not that table: it misses
pointers that are not dword-aligned or not absolute, and it reads integers
that happen to look like addresses as pointers. This tool assembles the
ledger from evidence that PROVES each row, types every row, and keeps what a
scan alone suggests in a separate review queue that nothing links from.

  python3 tools/reloc_ledger.py                 # ~5 min, BUILD_POOL workers (<= 4)
  python3 tools/reloc_ledger.py --objects-root build/wt_link   # another checkout's objects

Provenance (one row per site; the strongest evidence wins):

  compiler       a relocation in one of our objects. A code section is placed
                 by its matched ledger row and must equal retail outside its
                 relocation fields; each DIR32 then reads its target from
                 retail's bytes at the site (build.py's resolve copies DIR32
                 from retail the same way). The target's own section is thereby
                 placed: a data section placed at a retail address and equal
                 to retail there contributes its relocations too (fixed point,
                 as component_link.Placement does for one component).
  dump-analysis  build/dump_relocs/relocs.csv (tools/dump_relocs.py) rows
                 whose target is data: typed by disassembly of the dump body.
  structure      a field of a structure whose format is fixed and whose
                 address is proven by a reference: MSVC EH FuncInfo (magic
                 0x19930520) and the unwind / try-block / handler tables it
                 points at, ThrowInfo / CatchableTypeArray / CatchableType,
                 and a type descriptor's type_info vftable pointer.
  vtable         a slot of a vftable whose start is proven by a vptr store
                 (`mov dword ptr [reg+d], imm32` in a matched body) or by a
                 compiled ??_7 symbol, while the slot points at a function
                 start (ledger row or Ghidra) and no other item starts.
  use-proven     code loads a dword from a data address and uses it as an
                 address (`call/jmp [X]`, or `mov reg, [X]` then reg is a
                 memory base, a call target or `this` for a call), or
                 `call/jmp [X + r*4]` indexes a table, or the CRT hands a
                 range to _initterm (every entry up to the next item start).
  proven-scalar  NOT a relocation: an in-image dword one of our matching object
                 sections holds with no relocation, typed as a number by
                 evidence other than our own source -- a prebuilt upstream
                 library member (`library-member`), the arithmetic-typed
                 declaration of the covering symbol in vendored upstream C source
                 (`vendored-declaration`, file hash recorded), or retail's direct
                 8/16-bit or x87 accesses covering every byte of the word with
                 every reference into the section such an access and nothing in
                 data pointing into it (`element-access`). proven_scalars.csv lists
                 them for tools/image_check.py.
  scan-candidate an aligned dword in a scaffold data item whose value lies in
                 the image and that no row above explains. NEVER linked; the
                 scaffold keeps it literal and lists it for review.

Rows whose site is in .text are references INTO data from code; rows whose
site is in data are pointers held by data (target anywhere in the image).

Data items: .rdata/.data/STLPORT_ are partitioned into object-defined
sections (placed and compared as above; `contradicted` when the bytes
differ), linker-built ranges (debug and export directories; .idata is the
import lane), and scaffold items split at every proven reference target,
every dir32_addresses.csv / exports.csv name and every vtable start. An item's
size is `proven` for an object section, a structure or a NUL-terminated string
referenced at its start; otherwise `inferred` (runs to the next boundary).

Outputs (build/reloc_ledger/): ledger.csv, items.csv, names.csv (the name
each caller spells, per address), placements.csv, review_scan.csv,
review_size.csv, review_types.csv, review_conflicts.csv, proven_scalars.csv,
call_targets.csv (where byte-verified code's calls to each undefined name go in
retail), summary.json.
"""
import argparse
import bisect
import collections
import concurrent.futures
import csv
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

OUT = ROOT / "build" / "reloc_ledger"
REVERSE = ROOT / "targets" / "game" / "reverse"
DIR32, DIR32NB, REL32 = 0x0006, 0x0007, 0x0014
KIND_NAME = {DIR32: "DIR32", DIR32NB: "DIR32NB", REL32: "REL32", 0: "SCALAR"}
CNT_CODE, UNINIT, LNK_INFO, LNK_REMOVE, COMDAT_FLAG, DISCARDABLE = 0x20, 0x80, 0x200, 0x800, 0x1000, 0x02000000
NRELOC_OVFL = 0x01000000
EXTERNAL, STATIC, WEAK_EXTERNAL = 2, 3, 105
DATA_SECTIONS = (".rdata", ".data", ".idata", "STLPORT_")
SCAFFOLD_SECTIONS = (".rdata", ".data", "STLPORT_")
EH_MAGIC = 0x19930520
PROVENANCE_RANK = {"compiler": 0, "structure": 1, "dump-analysis": 2, "vtable": 3, "use-proven": 4,
                   "proven-scalar": 5, "scan-candidate": 9}
NOT_A_RELOCATION = ("proven-scalar", "scan-candidate")  # rows the scaffold keeps literal
KIND_SCALAR = 0
# CRT absolutes no census object defines: libc's exsup.asm `__except_list equ 0` (the fs:[0] offset)
KNOWN_ABSOLUTE = {"__except_list": 0}
ANON = re.compile(r"\?A0x[0-9A-Fa-f]{8}")


# --------------------------------------------------------------------------- retail image

class Image:
    """Retail's sections by VA; the virtual-only tail of a section reads as zero."""

    def __init__(self, data=None):
        data = data if data is not None else build.EXE.read_bytes()
        self.data = data
        pe = struct.unpack_from("<I", data, 0x3C)[0]
        count = struct.unpack_from("<H", data, pe + 6)[0]
        optional = struct.unpack_from("<H", data, pe + 20)[0]
        self.base = struct.unpack_from("<I", data, pe + 24 + 28)[0]
        self.size = struct.unpack_from("<I", data, pe + 24 + 56)[0]
        dirs = pe + 24 + 96
        self.directories = [struct.unpack_from("<II", data, dirs + 8 * i) for i in range(16)]
        self.sections = []
        for i in range(count):
            o = pe + 24 + optional + 40 * i
            name = data[o:o + 8].rstrip(b"\0").decode("latin-1").strip()
            vsize, rva, rsize, rptr = struct.unpack_from("<IIII", data, o + 8)
            self.sections.append({"name": name, "va": self.base + rva, "end": self.base + rva + max(vsize, rsize),
                                  "raw_end": self.base + rva + min(vsize, rsize) if vsize else self.base + rva + rsize,
                                  "raw": rptr})
        self._starts = [s["va"] for s in self.sections]
        self.by_name = {s["name"]: s for s in self.sections}

    def section(self, va):
        i = bisect.bisect_right(self._starts, va) - 1
        if i >= 0 and va < self.sections[i]["end"]:
            return self.sections[i]["name"] or "?"
        return "header" if self.base <= va < self.base + self.size else None

    def in_image(self, va):
        return self.base + 0x1000 <= va < self.base + self.size

    def read(self, va, size):
        i = bisect.bisect_right(self._starts, va) - 1
        if i < 0 or va + size > self.sections[i]["end"]:
            return None
        s = self.sections[i]
        out = bytearray(size)
        raw_n = max(0, min(va + size, s["raw_end"]) - va)
        if raw_n:
            off = s["raw"] + va - s["va"]
            out[:raw_n] = self.data[off:off + raw_n]
        return bytes(out)

    def u32(self, va):
        raw = self.read(va, 4)
        return struct.unpack("<I", raw)[0] if raw else None

    def is_data(self, va):
        return self.section(va) in DATA_SECTIONS


# --------------------------------------------------------------------------- COFF

def parse_coff(data):
    """(sections, symbols): sections[n-1] = dict; symbols[index] = dict (aux records skipped)."""
    nsec, _, symtab, nsym, optional = struct.unpack_from("<HIIIH", data, 2)
    strings = symtab + 18 * nsym
    sections = []
    for i in range(nsec):
        o = 20 + optional + 40 * i
        raw_name = data[o:o + 8]
        if raw_name[:1] == b"/":
            idx = int(raw_name[1:].rstrip(b"\0"))
            name = data[strings + idx:data.index(b"\0", strings + idx)].decode("latin-1")
        else:
            name = raw_name.rstrip(b"\0").decode("latin-1")
        size, ptr, relptr = struct.unpack_from("<III", data, o + 16)
        nrel = struct.unpack_from("<H", data, o + 32)[0]
        flags = struct.unpack_from("<I", data, o + 36)[0]
        first = 0
        if flags & NRELOC_OVFL and nrel == 0xFFFF:
            # the real count (this entry included) is the first entry's address field
            nrel, first = struct.unpack_from("<I", data, relptr)[0], 1
        relocs = [struct.unpack_from("<IIH", data, relptr + 10 * r) for r in range(first, nrel)]
        sections.append({"number": i + 1, "name": name, "size": size, "flags": flags,
                         "body": data[ptr:ptr + size] if ptr and not flags & UNINIT else None,
                         "relocs": relocs, "align": (flags >> 20) & 0xF})
    symbols = {}
    index = 0
    while index < nsym:
        rec = data[symtab + 18 * index:symtab + 18 * index + 18]
        if rec[:4] == b"\0\0\0\0":
            off = struct.unpack_from("<I", rec, 4)[0]
            name = data[strings + off:data.index(b"\0", strings + off)].decode("latin-1")
        else:
            name = rec[:8].rstrip(b"\0").decode("latin-1")
        value, section, typ, storage, aux = struct.unpack_from("<IhHBB", rec, 8)
        symbols[index] = {"index": index, "name": name, "value": value, "section": section, "type": typ,
                          "storage": storage}
        index += 1 + aux
    return sections, symbols


def is_data_section(section):
    return (section["size"] > 0 and not section["flags"] & (CNT_CODE | LNK_INFO | LNK_REMOVE | DISCARDABLE)
            and not section["name"].startswith((".text", ".debug", ".drectve")))


def masked_equal(body, retail, relocs, lo=0):
    """body == retail outside relocation fields (offsets relative to lo)."""
    ours, theirs = bytearray(body), bytearray(retail)
    if len(ours) != len(theirs):
        return False
    for where, _, kind in relocs:
        o = where - lo
        width = 2 if kind == 0x000A else 4
        if 0 <= o < len(ours):
            ours[o:o + width] = theirs[o:o + width]
    return ours == theirs


def symbol_key(obj_name, sym):
    """The name a relocation's referent is known by across the whole program."""
    if sym["storage"] in (EXTERNAL, WEAK_EXTERNAL):
        return sym["name"]
    return f"{obj_name}!{sym['name']}"


# --------------------------------------------------------------------------- compiler phase (workers)

_IMAGE = None


def _image():
    global _IMAGE
    if _IMAGE is None:
        _IMAGE = Image()
    return _IMAGE


def _find_symbol(symbols, name):
    for s in symbols.values():
        if s["name"] == name and s["section"] > 0:
            return s
    normal = ANON.sub("?A0xHASH", name)
    found = [s for s in symbols.values() if s["section"] > 0 and ANON.sub("?A0xHASH", s["name"]) == normal]
    return found[0] if len(found) == 1 else None


def _dir32_fact(img, obj, sections, symbols, section, base, where, index, kind):
    """What retail's bytes at one relocation site say: a ledger row dict and
    (placement key, address) of the referent, or None when not a data fact."""
    target = symbols.get(index)
    if target is None or kind not in (DIR32, DIR32NB) or where + 4 > section["size"]:
        return None
    if target["section"] == -1:
        return None  # an absolute symbol (__except_list is fs:[0]): no image address
    site = base + where
    value = img.u32(site)
    if value is None:
        return None
    addend = struct.unpack_from("<i", section["body"], where)[0]
    va = (value if kind == DIR32 else img.base + value) & 0xFFFFFFFF
    sym_va = (va - addend) & 0xFFFFFFFF
    fact = {"site": site, "kind": kind, "target": va, "symbol": symbol_key(obj, target), "addend": addend,
            "sym_va": sym_va, "referent": target, "coff_type": target["type"]}
    if not (img.in_image(va) and img.in_image(sym_va)):
        # our object relocates a field retail holds as a literal (a vftable
        # store retail wrote as 0, a constant): a contradiction, never a row
        fact["literal"] = value
    return fact


def scan_code(task):
    """Worker: place an object's code sections by its ledger rows and read every
    DIR32 in the rows' bytes. Returns rows (sites in .text), placements and the
    object's data-section / defined-name tables."""
    path, anchors = task
    img = _image()
    obj = Path(path).name
    data = Path(path).read_bytes()
    sections, symbols = parse_coff(data)
    out = {"obj": obj, "rows": [], "literals": [], "places": [], "names": [], "calls": [], "mismatch": 0, "missing": 0, "rows_ok": 0,
           "data_sections": {}, "defined": []}
    for s in sections:
        if is_data_section(s):
            out["data_sections"][s["number"]] = (s["name"], s["size"], s["flags"], s["body"] is None)
    out["absolute"] = []
    for s in symbols.values():
        if s["storage"] == EXTERNAL and s["section"] > 0 and s["section"] in out["data_sections"]:
            out["defined"].append((s["name"], s["section"], s["value"], s["type"]))
        elif s["storage"] == EXTERNAL and s["section"] == -1:
            out["absolute"].append((s["name"], s["value"]))
    for name, rva, size in anchors:
        sym = _find_symbol(symbols, name)
        if sym is None:
            out["missing"] += 1
            continue
        section = sections[sym["section"] - 1]
        if section["body"] is None:
            out["missing"] += 1
            continue
        va = img.base + rva
        lo, hi = sym["value"], sym["value"] + size
        body = section["body"][lo:hi]
        retail = img.read(va, size)
        relocs = [(w, i, k) for w, i, k in section["relocs"] if lo <= w < hi]
        if retail is None or len(body) != size or not masked_equal(body, retail, relocs, lo):
            out["mismatch"] += 1
            continue
        out["rows_ok"] += 1
        base = va - lo
        for where, index, kind in relocs:
            referent = symbols.get(index)
            if kind == REL32 and referent is not None and referent["storage"] == EXTERNAL \
                    and referent["section"] == 0 and where + 4 <= hi:
                # where retail's own call goes: independent evidence for the name's address.
                # retail's rel32 = S + A - (P + 4), A the object's in-place addend: the
                # destination is P + 4 + rel32, the symbol's address that minus A
                disp = struct.unpack("<i", img.read(base + where, 4))[0]
                addend = struct.unpack_from("<i", section["body"], where)[0]
                destination = (base + where + 4 + disp) & 0xFFFFFFFF
                out["calls"].append((referent["name"], (destination - addend) & 0xFFFFFFFF, destination))
            fact = _dir32_fact(img, obj, sections, symbols, section, base, where, index, kind)
            if fact is None:
                continue
            referent = fact.pop("referent")
            fact["origin"] = f"{obj}:{name}"
            if "literal" in fact:
                out["literals"].append(fact)
                continue
            if img.is_data(fact["target"]) or img.is_data(fact["sym_va"]):
                out["rows"].append(fact)
            _place(out, sections, referent, fact["sym_va"], f"{name}+{where - lo:#x}")
    return out


def _place(out, sections, referent, sym_va, evidence):
    if referent["section"] > 0:
        target_section = sections[referent["section"] - 1]
        if is_data_section(target_section):
            out["places"].append((referent["section"], sym_va - referent["value"], evidence))
    elif referent["storage"] == EXTERNAL and referent["section"] == 0:
        out["names"].append((referent["name"], sym_va, evidence))


def scan_data(task):
    """Worker: compare an object's placed data sections with retail and read
    the relocations of the ones that match."""
    path, placed = task
    img = _image()
    obj = Path(path).name
    sections, symbols = parse_coff(Path(path).read_bytes())
    out = {"obj": obj, "rows": [], "literals": [], "places": [], "names": [], "verdicts": [], "unrelocated": []}
    for number, base in placed.items():
        section = sections[number - 1]
        size = section["size"]
        retail = img.read(base, size)
        if retail is None:
            out["verdicts"].append((number, base, "outside-image"))
            continue
        if section["body"] is None:
            # uninitialised: retail must hold zeros there (or lie in the virtual tail)
            out["verdicts"].append((number, base, "verified" if not any(retail) else "contradicted"))
            continue
        if not masked_equal(section["body"], retail, section["relocs"]):
            out["verdicts"].append((number, base, "contradicted"))
            continue
        out["verdicts"].append((number, base, "verified"))
        # in-image dwords the compiler did NOT relocate: numbers in our source,
        # but only typed evidence says retail's element is a number too
        covered = set()
        for where, _, kind in section["relocs"]:
            covered.update(range(where, where + (2 if kind == 0x000A else 4)))
        members = sorted((x["value"], x["name"]) for x in symbols.values()
                         if x["section"] == number and x["storage"] in (EXTERNAL, STATIC)
                         and x["name"] and not x["name"].startswith("."))

        def covering(off, members=members):
            i = bisect.bisect_right(members, (off, chr(0x10FFFF))) - 1
            return (members[i][1], members[i][0]) if i >= 0 else None
        for off in range(0, size - 3):
            if any(off + k in covered for k in range(4)):
                continue
            value = struct.unpack_from("<I", retail, off)[0]
            if img.in_image(value):
                out["unrelocated"].append((number, base, size, base + off, value, covering(off)))
        for where, index, kind in section["relocs"]:
            fact = _dir32_fact(img, obj, sections, symbols, section, base, where, index, kind)
            if fact is None:
                continue
            referent = fact.pop("referent")
            fact["origin"] = f"{obj}:{section['name']}#{number}"
            fact["section_no"] = number
            if "literal" in fact:
                out["literals"].append(fact)
                continue
            out["rows"].append(fact)
            _place(out, sections, referent, fact["sym_va"], f"{section['name']}#{number}+{where:#x}")
    return out


# --------------------------------------------------------------------------- compiler phase (driver)

def object_anchors(rows):
    """{object path: [(object symbol, rva, size)]} for every matched row's object. A
    funclet or gen-alias row anchors nothing (its bytes are another row's), but
    its object is still read: the names it defines are not scaffold names."""
    anchors = collections.defaultdict(list)
    for row in rows:
        try:
            obj = build.row_object(row)
        except SystemExit:
            continue
        if "gen-funclet" in (row.get("notes") or "") or "gen-alias" in (row.get("notes") or ""):
            anchors[str(obj)]
            continue
        anchors[str(obj)].append((build.ledger_object_symbol(row), int(row["target_rva"], 16),
                                  int(row["target_size"])))
    return anchors


def compiler_phase(objects, anchors, workers, log=print):
    """Rows, section verdicts and name addresses from every object."""
    rows, verdicts, literals, unrelocated = [], {}, [], []
    absolute = {}                                # name -> value of an absolute COFF symbol
    calls = collections.defaultdict(collections.Counter)  # undefined external -> retail call targets
    names = collections.defaultdict(dict)        # name -> {va: evidence}
    placed = collections.defaultdict(dict)       # obj path -> {section: base}
    why = {}
    conflicted = set()
    conflicts = []
    defined = collections.defaultdict(list)      # name -> [(obj path, section, value, type)]
    data_sections = {}                           # obj path -> {section: (name, size, flags, uninit)}
    by_name = {Path(p).name: p for p in objects}
    stats = collections.Counter()

    def absorb(result):
        path = by_name[result["obj"]]
        for fact in result["rows"]:
            if "section_no" in fact:
                fact["okey"] = (path, fact.pop("section_no"))
        rows.extend(result["rows"])
        literals.extend(result["literals"])
        for number, base, evidence in result["places"]:
            old = placed[path].get(number)
            if old is None:
                placed[path][number] = base
                why[(path, number)] = evidence
                new_places.add(path)
            elif old != base:
                conflicted.add((path, number))
                conflicts.append(("section", f"{result['obj']}#{number}", f"{old:#010x}", f"{base:#010x}", evidence))
        for name, va, evidence in result["names"]:
            names[name].setdefault(va, evidence)

    new_places = set()
    with concurrent.futures.ProcessPoolExecutor(workers) as pool:
        tasks = [(p, anchors.get(p, [])) for p in objects]
        for result in pool.map(scan_code, tasks, chunksize=32):
            path = by_name[result["obj"]]
            data_sections[path] = result["data_sections"]
            for name, number, value, typ in result["defined"]:
                defined[name].append((path, number, value, typ))
            absolute.update(result["absolute"])
            for name, symbol_va, destination in result["calls"]:
                calls[name][(symbol_va, destination)] += 1
            for key in ("mismatch", "missing", "rows_ok"):
                stats["code_" + key] += result[key]
            absorb(result)
        log(f"reloc_ledger: code phase: {stats['code_rows_ok']:,} rows compared equal, "
            f"{stats['code_mismatch']:,} differ, {stats['code_missing']:,} not found; {len(rows):,} data references")
        done = collections.defaultdict(set)
        for round_no in range(1, 20):
            # a defined name with one address places every object's copy of it
            for name, vas in names.items():
                if len(vas) != 1 or name not in defined:
                    continue
                va = next(iter(vas))
                for path, number, value, _ in defined[name]:
                    old = placed[path].get(number)
                    if old is None:
                        placed[path][number] = va - value
                        why[(path, number)] = f"name {name} ({names[name][va]})"
                        new_places.add(path)
                    elif old != va - value:
                        conflicted.add((path, number))
                        conflicts.append(("section", f"{Path(path).name}#{number}", f"{old:#010x}",
                                          f"{va - value:#010x}", f"name {name}"))
            work = []
            for path in sorted(new_places):
                todo = {n: b for n, b in placed[path].items() if n not in done[path] and (path, n) not in conflicted}
                if todo:
                    work.append((path, todo))
                    done[path].update(todo)
            new_places.clear()
            if not work:
                break
            for result in pool.map(scan_data, work, chunksize=16):
                path = by_name[result["obj"]]
                for number, base, verdict in result["verdicts"]:
                    verdicts[(path, number)] = (base, verdict)
                for number, base, size, va, value, symbol in result["unrelocated"]:
                    unrelocated.append(((path, number), base, size, va, value, symbol))
                absorb(result)
            log(f"reloc_ledger: data round {round_no}: {len(work):,} objects, {len(verdicts):,} sections judged, "
                f"{len(rows):,} rows")
    # a reference to an absolute symbol (__except_list = fs:[0]) holds its value, not an address
    before = len(literals)
    literals = [f for f in literals if {**KNOWN_ABSOLUTE, **absolute}.get(f["symbol"]) != f["literal"]]
    stats["absolute_symbol_references"] = before - len(literals)
    # a section placed at two addresses is not retail's layout: its verdict and rows go
    for key in conflicted:
        verdicts[key] = (placed[key[0]][key[1]], "conflict")
    before = len(rows)
    rows = [r for r in rows if r.get("okey") not in conflicted]
    stats["rows_dropped_conflict"] = before - len(rows)
    for name, vas in names.items():
        if len(vas) > 1:
            conflicts.append(("name", name, " ".join(f"{v:#010x}" for v in sorted(vas)), "",
                              "; ".join(vas[v] for v in sorted(vas))[:300]))
    return {"calls": calls, "unrelocated": unrelocated, "literals": literals, "why": why, "rows": rows, "verdicts": verdicts, "names": names, "conflicts": conflicts, "defined": defined,
            "data_sections": data_sections, "stats": stats}


# --------------------------------------------------------------------------- code uses (workers)

_MD = None


def _md():
    global _MD
    if _MD is None:
        from capstone import CS_ARCH_X86, CS_MODE_32, Cs
        _MD = Cs(CS_ARCH_X86, CS_MODE_32)
        _MD.detail = True
    return _MD


def scan_uses(chunk):
    """Worker: linear sweep of matched bodies for uses that prove a data dword
    is an address. Returns [(what, rule, data va, site va)] where `what` is
    ptr (the dword at va is an address), table (va starts an array of them) or
    vptr (va may start a vftable: an imm32 stored through a register)."""
    from capstone.x86 import X86_OP_IMM, X86_OP_MEM, X86_OP_REG, X86_REG_ECX, X86_REG_INVALID
    img = _image()
    md = _md()
    found = []
    for va, size in chunk:
        body = img.read(va, size)
        if body is None:
            continue
        insns = list(md.disasm(body, va))
        for i, insn in enumerate(insns):
            ops = insn.operands
            mnem = insn.mnemonic
            if mnem in ("call", "jmp") and len(ops) == 1 and ops[0].type == X86_OP_MEM:
                m = ops[0].mem
                if m.base == X86_REG_INVALID and m.segment == 0:
                    x = m.disp & 0xFFFFFFFF
                    if m.index == X86_REG_INVALID:
                        found.append(("ptr", mnem + "-mem", x, insn.address))
                    elif m.scale == 4:
                        found.append(("table", mnem + "-table", x, insn.address))
                continue
            if (mnem == "mov" and len(ops) == 2 and ops[0].type == X86_OP_MEM and ops[1].type == X86_OP_IMM
                    and ops[0].size == 4 and ops[0].mem.base != X86_REG_INVALID and insn.imm_size == 4):
                found.append(("vptr", "vptr-store", ops[1].imm & 0xFFFFFFFF, insn.address))
                continue
            if not (mnem == "mov" and len(ops) == 2 and ops[0].type == X86_OP_REG and ops[1].type == X86_OP_MEM
                    and ops[1].size == 4):
                continue
            m = ops[1].mem
            if m.base != X86_REG_INVALID or m.segment != 0:
                continue
            if m.index != X86_REG_INVALID and m.scale != 4:
                continue
            reg = ops[0].reg
            use = None
            for nxt in insns[i + 1:i + 9]:
                if any(op.type == X86_OP_MEM and op.mem.base == reg for op in nxt.operands):
                    use = "deref"
                elif nxt.mnemonic in ("call", "jmp") and nxt.operands and nxt.operands[0].type == X86_OP_REG \
                        and nxt.operands[0].reg == reg:
                    use = "call-reg"
                elif nxt.mnemonic == "call" and reg == X86_REG_ECX:
                    use = "this-call"
                if use:
                    break
                _, written = nxt.regs_access()
                if reg in written or nxt.mnemonic.startswith(("j", "ret", "call")):
                    break
            if use:
                what = "ptr" if m.index == X86_REG_INVALID else "table"
                found.append((what, f"load-{use}" if what == "ptr" else f"load-table-{use}",
                              m.disp & 0xFFFFFFFF, insn.address))
    return found


# --------------------------------------------------------------------------- structures

def looks_string(img, va, limit=4096):
    """Length including the terminator of a printable ASCII or UTF-16LE string at va, else 0."""
    name = img.section(va)
    if name not in img.by_name:
        return 0
    raw = img.read(va, min(limit, img.by_name[name]["end"] - va))
    if not raw:
        return 0
    # UTF-16 first: "w\0i\0" would otherwise read as the one-character ASCII string "w"
    n = 0
    while n + 1 < len(raw) and raw[n + 1] == 0 and (0x20 <= raw[n] < 0x7F or raw[n] in (9, 10, 13)):
        n += 2
    if n >= 4 and n + 1 < len(raw) and raw[n] == 0 and raw[n + 1] == 0:
        return n + 2
    end = raw.find(b"\0")
    if end >= 1 and all(0x20 <= c < 0x7F or c in (9, 10, 13) for c in raw[:end]):
        return end + 1
    return 0


class Structures:
    """Walk the fixed-format MSVC structures reachable from proven addresses.

    Each walk validates every field before emitting anything; a structure
    that fails validation emits nothing (its dwords stay scan candidates)."""

    def __init__(self, img):
        self.img = img
        self.rows = []        # (site, target, rule)
        self.items = {}       # start -> (size, kind)
        self.seen = set()

    def text(self, va):
        return self.img.section(va) == ".text"

    def rdata(self, va):
        return self.img.section(va) == ".rdata"

    def u32s(self, va, n):
        raw = self.img.read(va, 4 * n)
        return struct.unpack(f"<{n}I", raw) if raw else None

    def funcinfo(self, va):
        if va in self.seen:
            return True
        f = self.u32s(va, 7)
        if not f or f[0] != EH_MAGIC:
            return False
        _, max_state, p_unwind, n_try, p_try, n_ip, p_ip = f
        if not (0 <= max_state < 4096 and 0 <= n_try < 1024 and n_ip == 0 and p_ip == 0):
            return False
        if (max_state and not self.rdata(p_unwind)) or (not max_state and p_unwind):
            return False
        if (n_try and not self.rdata(p_try)) or (not n_try and p_try):
            return False
        unwind = self.u32s(p_unwind, 2 * max_state) if max_state else ()
        if max_state and not unwind:
            return False
        for k in range(max_state):
            to_state = struct.unpack("<i", struct.pack("<I", unwind[2 * k]))[0]
            action = unwind[2 * k + 1]
            if not (-1 <= to_state < max_state) or (action and not self.text(action)):
                return False
        tries = self.u32s(p_try, 5 * n_try) if n_try else ()
        if n_try and not tries:
            return False
        handlers = []
        for k in range(n_try):
            low, high, catch_high, n_catch, p_handlers = tries[5 * k:5 * k + 5]
            if not (low <= high < catch_high <= max_state and 0 < n_catch < 64 and self.rdata(p_handlers)):
                return False
            hs = self.u32s(p_handlers, 4 * n_catch)
            if not hs:
                return False
            for c in range(n_catch):
                adjectives, p_type, _, handler = hs[4 * c:4 * c + 4]
                if adjectives > 0xFF or not self.text(handler) or (p_type and not self.typedesc(p_type, dry=True)):
                    return False
            handlers.append((p_handlers, n_catch, hs))
        self.seen.add(va)
        self.items[va] = (28, "eh-funcinfo")
        if max_state:
            self.rows.append((va + 8, p_unwind, "eh-funcinfo"))
            self.items.setdefault(p_unwind, (8 * max_state, "eh-unwindmap"))
            for k in range(max_state):
                if unwind[2 * k + 1]:
                    self.rows.append((p_unwind + 8 * k + 4, unwind[2 * k + 1], "eh-unwind-action"))
        if n_try:
            self.rows.append((va + 16, p_try, "eh-funcinfo"))
            self.items.setdefault(p_try, (20 * n_try, "eh-tryblockmap"))
            for k in range(n_try):
                self.rows.append((p_try + 20 * k + 16, tries[5 * k + 4], "eh-tryblock"))
        for p_handlers, n_catch, hs in handlers:
            self.items.setdefault(p_handlers, (16 * n_catch, "eh-handlers"))
            for c in range(n_catch):
                if hs[4 * c + 1]:
                    self.rows.append((p_handlers + 16 * c + 4, hs[4 * c + 1], "eh-handler-type"))
                    self.typedesc(hs[4 * c + 1])
                self.rows.append((p_handlers + 16 * c + 12, hs[4 * c + 3], "eh-handler"))
        return True

    def typedesc(self, va, dry=False):
        """A type descriptor: type_info vftable pointer, a zero `spare`, `.?A...` name."""
        if self.img.section(va) not in (".data", ".rdata"):
            return False
        f = self.u32s(va, 2)
        if not f or not self.rdata(f[0]) or f[1]:
            return False
        n = looks_string(self.img, va + 8, 1024)
        if self.img.read(va + 8, 1) != b"." or not n:
            return False
        if not dry and va not in self.items:
            self.items[va] = (8 + n, "rtti-typedescriptor")
            self.rows.append((va, f[0], "rtti-typedescriptor"))
        return True

    def fieldparse(self, va, is_code_ptr):
        """An INI FieldParse table (INI.h: token, parse, userData, offset; 16 bytes
        each) ending in an entry whose token is 0: at least two entries, every
        token a string, every parse function code, every offset below 64 KB."""
        entries = []
        at = va
        while len(entries) < 4096:
            f = self.u32s(at, 4)
            if not f:
                return False
            token, parse, user, offset = f
            if token == 0:
                if parse or offset:
                    return False
                break
            if self.img.section(token) not in (".rdata", ".data") or looks_string(self.img, token) < 2:
                return False
            if not is_code_ptr(parse) or offset >= 0x10000:
                return False
            entries.append((at, f))
            at += 16
        if len(entries) < 2:
            return False
        self.items[va] = (at + 16 - va, "ini-fieldparse")
        for where, (token, parse, user, _) in entries:
            self.rows.append((where, token, "ini-fieldparse"))
            self.rows.append((where + 4, parse, "ini-fieldparse"))
            if self.img.in_image(user):
                self.rows.append((where + 8, user, "ini-fieldparse"))
        return True

    def throwinfo(self, va):
        if self.img.section(va) != ".rdata":
            return False
        f = self.u32s(va, 4)
        if not f:
            return False
        attributes, unwind, compat, p_cta = f
        if attributes > 0xF or compat or (unwind and not self.text(unwind)) or not self.rdata(p_cta):
            return False
        cta = self.u32s(p_cta, 1)
        if not cta or not 0 < cta[0] < 32:
            return False
        cts = self.u32s(p_cta + 4, cta[0])
        if not cts:
            return False
        bodies = []
        for ct in cts:
            g = self.u32s(ct, 7) if self.rdata(ct) else None
            if not g or g[0] > 0xFF or not self.typedesc(g[1], dry=True) or (g[6] and not self.text(g[6])):
                return False
            bodies.append((ct, g))
        self.items.setdefault(va, (16, "eh-throwinfo"))
        if unwind:
            self.rows.append((va + 4, unwind, "eh-throwinfo"))
        self.rows.append((va + 12, p_cta, "eh-throwinfo"))
        self.items.setdefault(p_cta, (4 + 4 * cta[0], "eh-catchabletypearray"))
        for k, (ct, g) in enumerate(bodies):
            self.rows.append((p_cta + 4 + 4 * k, ct, "eh-catchabletypearray"))
            self.items.setdefault(ct, (28, "eh-catchabletype"))
            self.rows.append((ct + 4, g[1], "eh-catchabletype"))
            self.typedesc(g[1])
            if g[6]:
                self.rows.append((ct + 24, g[6], "eh-catchabletype"))
        return True


# --------------------------------------------------------------------------- names and types

SCALAR = {"H": 4, "I": 4, "J": 4, "K": 4, "M": 4, "F": 2, "G": 2, "D": 1, "C": 1, "E": 1, "N": 8, "O": 8,
          "_N": 1, "_J": 8, "_K": 8, "_W": 2}
MANGLED_DATA = re.compile(r"^(\?[^@?][^@]*@(?:[^@]+@)*@)([23])(.+)$")


def mangled_identity(name):
    """(qualified name, storage+type code) of a mangled global/static data name, or None."""
    m = MANGLED_DATA.match(name)
    return (m.group(1), m.group(2) + m.group(3)) if m else None


def mangled_scalar_size(name):
    """Bytes a mangled data name declares when its type is an arithmetic scalar or
    enum, else None. P/Q (pointer OR array: `T x[]` mangles like `T* x`) and
    class types declare no size a name alone can bound."""
    ident = mangled_identity(name)
    if ident is None:
        return None
    t = ident[1][1:]
    if t.startswith("W4"):
        return 4
    return SCALAR.get(t[:2] if t.startswith("_") else t[:1])


def g_name(va):
    return f"g_{va:08X}"


# --------------------------------------------------------------------------- the ledger

class Ledger:
    """One row per relocation site; the strongest provenance wins a site."""

    def __init__(self, img):
        self.img = img
        self.rows = {}
        self.clashes = []

    def add(self, site, kind, target, provenance, rule, confidence, symbol="", addend=0, origin="", sym_va=None):
        row = {"site": site, "kind": kind, "target": target & 0xFFFFFFFF, "symbol": symbol, "addend": addend,
               "provenance": provenance, "rule": rule, "confidence": confidence, "origin": origin,
               "sym_va": (target - addend) & 0xFFFFFFFF if sym_va is None else sym_va}
        old = self.rows.get(site)
        if old is None:
            self.rows[site] = row
            return True
        if old["target"] != row["target"] or old["kind"] != row["kind"]:
            if provenance != "scan-candidate" and old["provenance"] != "scan-candidate":
                self.clashes.append((site, old, row))
        if PROVENANCE_RANK[provenance] < PROVENANCE_RANK[old["provenance"]]:
            self.rows[site] = row
            return True
        if not old["symbol"] and symbol and old["target"] == row["target"]:
            old["symbol"], old["addend"] = symbol, addend
        return False


def load_dump_rows(path, img):
    """dump_relocs.py rows whose target is data: [(site, kind, target, symbol, addend, rule, evidence, body)]."""
    out = []
    if not path.exists():
        return out
    with path.open(newline="", encoding="utf-8") as handle:
        for row in csv.DictReader(handle):
            target = int(row["target"], 16)
            if not img.is_data(target):
                continue
            addend = int(row["addend"], 16) if not row["addend"].startswith("-") else -int(row["addend"][1:], 16)
            out.append((int(row["site_va"], 16), DIR32 if row["kind"] == "DIR32" else REL32, target,
                        row["symbol"], addend, row["rule"], row["evidence"], row["body"]))
    return out


DUMP_CONFIDENCE = {"mem-abs": "exact", "mem-sib": "exact", "jumptable": "exact", "jumptable-external": "exact",
                   "mem-based": "high"}
IMM_HIGH = ("start:dir32", "start:export", "start:vtable", "start:iat", "string", "deref", "this-call", "fnptrs",
            "start:row")


def dump_confidence(rule, evidence):
    if rule in DUMP_CONFIDENCE:
        return DUMP_CONFIDENCE[rule]
    return "high" if evidence.split(";")[0] in IMM_HIGH else "medium"


def read_csv_rows(path):
    with path.open(newline="", encoding="utf-8") as handle:
        return list(csv.DictReader(handle))


STARTUP_TABLES = ROOT / "build" / "startup" / "retail_tables.json"


def linker_ranges(img, startup=STARTUP_TABLES):
    """[(start, end, label)] the linker writes itself: debug and export directories,
    and the CRT initializer tables it assembles from every input's .CRT$X?? /
    .rtc$??? sections, from ___xc_a to ___xc_z inclusive (tools/startup_tables.py
    retail, which reads each delimiter at its genuine library relocation)."""
    out = []
    if startup is not None and Path(startup).exists():
        for table, t in json.loads(Path(startup).read_text(encoding="utf-8")).items():
            if t.get("begin") is not None:
                begin, end = int(str(t["begin"]), 0), int(str(t["end"]), 0)
                out.append((begin, end + 4, f"crt-table-{table}"))
    rva, size = img.directories[0]
    if size:
        out.append((img.base + rva, img.base + rva + size, "export-directory"))
    rva, size = img.directories[6]
    if size:
        out.append((img.base + rva, img.base + rva + size, "debug-directory"))
        for k in range(size // 28):
            entry = img.read(img.base + rva + 28 * k, 28)
            data_size, data_rva = struct.unpack_from("<II", entry, 16)
            if data_rva and data_size:
                out.append((img.base + data_rva, img.base + data_rva + data_size, "debug-data"))
    return out


# --------------------------------------------------------------------------- C++ file scope

_LITERALS = re.compile(r'//[^\n]*|/\*.*?\*/|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'', re.S)


def blank_literals(text):
    """Comments and string/char literals replaced by blanks (newlines kept, quotes
    kept for strings), and `#if 0` ... `#endif` regions dropped, so braces and
    semicolons in the result are code."""
    def blank(m):
        s = m.group(0)
        if s.startswith('"'):
            return '"' + " " * (len(s) - 2) + '"'
        return re.sub(r"[^\n]", " ", s)
    text = _LITERALS.sub(blank, text)
    out, depth = [], 0
    for line in text.split("\n"):
        directive = line.strip()
        if depth:
            if re.match(r"#\s*if", directive):
                depth += 1
            elif re.match(r"#\s*endif", directive):
                depth -= 1
            elif depth == 1 and re.match(r"#\s*(else|elif)", directive):
                depth = 0
            out.append("")
            continue
        if re.match(r"#\s*if\s+0\b", directive):
            depth = 1
            out.append("")
            continue
        out.append(line)
    return "\n".join(out)


def file_scope_lines(text):
    """[(1-based line, stripped line)] of the lines that START at file or namespace
    scope (not inside a function, class, enum or initializer body); None when the
    braces do not balance, so no scope can be trusted."""
    code = blank_literals(text)
    stack, starts, last = [], [], 0
    lines = code.split("\n")
    position = 0
    for number, line in enumerate(lines, 1):
        if all(kind == "namespace" for kind in stack):
            starts.append((number, line.strip()))
        for offset, char in enumerate(line):
            at = position + offset
            if char in ";{}":
                if char == "{":
                    prefix = code[last:at]
                    namespace = re.search(r'\bnamespace\b[\w\s]*$', prefix) or re.search(r'\bextern\s*""\s*$', prefix)
                    stack.append("namespace" if namespace else "body")
                elif char == "}":
                    if not stack:
                        return None
                    stack.pop()
                last = at + 1
        position += len(line) + 1
    return starts if not stack else None


def file_scope_definitions(text, qualified):
    """[(line, text)] of file/namespace-scope definitions of `qualified` (a
    declarator with an initializer or a plain `;`, not extern/typedef/a function)."""
    starts = file_scope_lines(text)
    if starts is None:
        return None
    pattern = re.compile(r"^(?!extern\b|typedef\b|return\b|using\b)[A-Za-z_][\w:<>,\s\*&]*[\s\*&]"
                         + re.escape(qualified) + r"\s*(\[[^\]]*\]\s*)*(=|;)")
    return [(number, line) for number, line in starts if pattern.match(line)]


# --------------------------------------------------------------------------- partition

class Partition:
    """Object-defined, linker-built and scaffold extents of retail's data sections."""

    def __init__(self, img, comp, structures, ledger, vtable_starts, names_at):
        self.img = img
        self.structures = structures
        self.vtable_starts = vtable_starts
        self.review = []
        sections = []
        for (path, number), (base, verdict) in comp["verdicts"].items():
            if verdict not in ("verified", "contradicted"):
                continue
            name, size, flags, uninit = comp["data_sections"][path][number]
            home = img.section(base)
            if home not in SCAFFOLD_SECTIONS or img.section(base + size - 1) != home:
                self.review.append(("object-section-outside-data", f"{Path(path).name}#{number}", base, size, home))
                continue
            sections.append((base, base + size, Path(path).name, number, name, verdict, uninit))
        sections.sort()
        self.object_sections = sections
        # union of object extents; partial overlaps are two objects claiming one retail byte range
        merged = []
        for start, end, obj, number, name, verdict, uninit in sections:
            if merged and start < merged[-1][1]:
                if (start, end) != (merged[-1][0], merged[-1][1]) and start != merged[-1][0]:
                    self.review.append(("object-sections-overlap", f"{obj}#{number}", start, end - start,
                                        f"{merged[-1][0]:#010x}+{merged[-1][1] - merged[-1][0]:#x}"))
                merged[-1][1] = max(merged[-1][1], end)
            else:
                merged.append([start, end])
        self.object_spans = merged
        self._span_starts = [s for s, _ in merged]
        self.linker = linker_ranges(img)
        covered = sorted([(s, e, "object") for s, e in merged] + [(s, e, lab) for s, e, lab in self.linker])
        self.gaps = []
        for name in SCAFFOLD_SECTIONS:
            sec = img.by_name.get(name)
            if sec is None:
                continue
            cursor = sec["va"]
            for s, e, _ in covered:
                if e <= cursor or s >= sec["end"]:
                    continue
                if s > cursor:
                    self.gaps.append((cursor, s, name))
                cursor = max(cursor, e)
            if cursor < sec["end"]:
                self.gaps.append((cursor, sec["end"], name))
        # the virtual-only tail of a section is uninitialised: split gaps there
        split = []
        for s, e, name in self.gaps:
            raw_end = img.by_name[name]["raw_end"]
            if s < raw_end < e:
                split += [(s, raw_end, name), (raw_end, e, name)]
            else:
                split.append((s, e, name))
        self.gaps = split
        self._gap_starts = [g[0] for g in self.gaps]
        self.bounds = set(g[0] for g in self.gaps)
        for va in names_at:
            self.bound(va)
        for start, (size, _) in structures.items.items():
            self.bound(start)
            self.bound(start + size)
        for va in vtable_starts:
            self.bound(va)
        for row in ledger.rows.values():
            self.row_bounds(row)
        self._sorted = sorted(self.bounds)
        # a vftable runs to the next vftable or structure, not to every referenced slot
        self.vtable_stops = sorted(set(vtable_starts) | {s for s in structures.items}
                                   | {s + n for s, (n, _) in structures.items.items()})

    def gap_of(self, va):
        i = bisect.bisect_right(self._gap_starts, va) - 1
        if i >= 0 and va < self.gaps[i][1]:
            return self.gaps[i]
        return None

    def object_owner(self, va):
        i = bisect.bisect_right(self._span_starts, va) - 1
        if i >= 0 and va < self.object_spans[i][1]:
            return self.object_spans[i]
        return None

    def bound(self, va):
        gap = self.gap_of(va)
        if gap is not None:
            self.bounds.add(va)
            n = looks_string(self.img, va) if self.img.section(va) in (".rdata", ".data") else 0
            if n and va + n < gap[1]:
                self.bounds.add(va + n)

    def row_bounds(self, row):
        if row["provenance"] in NOT_A_RELOCATION:
            return
        for va in (row["sym_va"], row["target"]):
            if self.img.is_data(va):
                self.bound(va)

    def run_of(self, start, test, allow_zero=False, stops=None):
        """Dword sites from start while test(value) holds, inside one gap and up to
        the next boundary (the next of `stops` when given)."""
        gap = self.gap_of(start)
        if gap is None:
            return []
        points = self._sorted if stops is None else stops
        i = bisect.bisect_right(points, start)
        stop = min(gap[1], points[i] if i < len(points) else gap[1])
        out, va = [], start
        while va + 4 <= stop:
            value = self.img.u32(va)
            if value == 0 and allow_zero:
                va += 4
                continue
            if not test(value):
                break
            out.append(va)
            va += 4
        return out

    def vtable_run(self, start, is_code_ptr):
        """Scaffold slot sites of the vftable at start: dwords that point at code, up to
        the next vftable or structure. A slot inside an object section is the
        compiler's; the walk continues past it, since an object may define a
        shorter copy of the table than retail's."""
        section = self.img.section(start)
        i = bisect.bisect_right(self.vtable_stops, start)
        stop = self.vtable_stops[i] if i < len(self.vtable_stops) else self.img.by_name[section]["end"]
        out, va = [], start
        while va + 4 <= stop and self.img.section(va) == section and is_code_ptr(self.img.u32(va)):
            if self.gap_of(va) is not None:
                out.append(va)
            va += 4
        return out

    def finish(self, ledger):
        for row in ledger.rows.values():
            self.row_bounds(row)
        self._sorted = sorted(self.bounds)
        items = []
        for gs, ge, name in self.gaps:
            lo = bisect.bisect_left(self._sorted, gs)
            hi = bisect.bisect_left(self._sorted, ge)
            points = self._sorted[lo:hi]
            for k, start in enumerate(points):
                end = points[k + 1] if k + 1 < len(points) else ge
                items.append(self.describe(start, end, name))
        for base, end, obj, number, sname, verdict, uninit in self.object_sections:
            items.append({"start": base, "end": end, "section": self.img.section(base), "source": "object",
                          "kind": sname + ("(bss)" if uninit else ""), "proof": "object-section",
                          "verdict": verdict, "origin": f"{obj}#{number}"})
        for s, e, lab in self.linker:
            items.append({"start": s, "end": e, "section": self.img.section(s), "source": "linker", "kind": lab,
                          "proof": "directory", "verdict": "", "origin": ""})
        items.sort(key=lambda it: (it["start"], it["source"] != "scaffold"))
        self.items = items
        self.scaffold = [it for it in items if it["source"] == "scaffold"]
        self._item_starts = [it["start"] for it in self.scaffold]

    def describe(self, start, end, name):
        img = self.img
        size = end - start
        item = {"start": start, "end": end, "section": name, "source": "scaffold", "verdict": "", "origin": ""}
        if start >= img.by_name[name]["raw_end"]:
            item.update(kind="bss", proof="uninitialised")
            return item
        s = self.structures.items.get(start)
        if s is not None:
            item.update(kind=s[1], proof="structure" if s[0] == size else "structure-split")
            return item
        n = looks_string(img, start) if name in (".rdata", ".data") else 0
        if n == size:
            item.update(kind="string", proof="string-terminator")
            return item
        if start in self.vtable_starts:
            item.update(kind="vftable", proof="inferred")
            return item
        raw = img.read(start, size)
        item.update(kind="zero" if not any(raw) else "data", proof="inferred")
        return item

    def scaffold_item(self, va):
        i = bisect.bisect_right(self._item_starts, va) - 1
        if i >= 0 and va < self.scaffold[i]["end"]:
            return self.scaffold[i]
        return None

    def covered_sites(self, ledger):
        cover = set()
        for row in ledger.rows.values():
            if row["provenance"] != "scan-candidate" and self.gap_of(row["site"]) is not None:
                # a proven scalar covers its dword too: it is settled, not a candidate
                cover.update(range(row["site"], row["site"] + 4))
        return cover

    def scan_candidates(self, ledger, evidence):
        """[(va, value, aligned, evidence)]: every in-image dword (any alignment) in an
        initialised scaffold item that overlaps no proven field."""
        cover = self.covered_sites(ledger)
        out = []
        for start, end, name in self.gaps:
            if start >= self.img.by_name[name]["raw_end"]:
                continue
            raw = self.img.read(start, end - start)
            for off in range(0, len(raw) - 3):
                value = struct.unpack_from("<I", raw, off)[0]
                va = start + off
                if self.img.in_image(value) and not any(v in cover for v in range(va, va + 4)):
                    it = self.scaffold_item(va)
                    why = "inside-string" if it["proof"] == "string-terminator" else evidence(value, raw[off:off + 4])
                    out.append((va, value, va % 4 == 0, why))
        return out


# --------------------------------------------------------------------------- names

class Namer:
    """Every name a caller spells for a data address, who defines it, and the
    symbol a relocation to an address links against."""

    def __init__(self, img, part, comp, dump_rows, ledger):
        import dump_relocs
        self.img = img
        self.part = part
        self.ctx = dump_relocs.load_context()
        self.object_defined = collections.defaultdict(set)     # va -> names objects define there
        self.object_names = set(comp["defined"])
        placed = {}
        for (path, number), (base, verdict) in comp["verdicts"].items():
            if verdict in ("verified", "contradicted"):
                placed[(path, number)] = base
        self.object_at = {}                                     # name -> va
        homes = collections.defaultdict(set)
        for name, defs in comp["defined"].items():
            for path, number, value, _ in defs:
                if (path, number) in placed:
                    homes[name].add(placed[(path, number)] + value)
        # a name our objects place at two retail addresses (retail kept two copies
        # the link cannot tell apart) labels neither
        self.object_multi_home = {n: sorted(v) for n, v in homes.items() if len(v) > 1}
        for name, vas in homes.items():
            if len(vas) == 1:
                va = next(iter(vas))
                self.object_defined[va].add(name)
                self.object_at[name] = va
        self._object_label_vas = sorted(self.object_defined)
        # names callers spell, by source
        self.callers = collections.defaultdict(lambda: collections.defaultdict(set))  # name -> va -> {source}
        for name, vas in comp["names"].items():
            for va in vas:
                if img.is_data(va):
                    self.callers[name][va].add("compiler")
        for row in read_csv_rows(REVERSE / "dir32_addresses.csv"):
            va = int(row["va"], 16)
            if img.is_data(va):
                self.callers[row["name"]][va].add("dir32")
        for row in read_csv_rows(REVERSE / "exports.csv"):
            if row["kind"] == "data" and row["rva"].startswith("0x"):
                va = img.base + int(row["rva"], 16)
                if img.is_data(va):
                    self.callers[row["name"]][va].add("export")
        for site, kind, target, symbol, addend, rule, evidence, body in dump_rows:
            self.callers[symbol][target - addend].add("dump")
        self.conflicts = {n: sorted(v) for n, v in self.callers.items() if len(v) > 1}
        self.at = collections.defaultdict(set)                   # va -> caller names (one address only)
        for name, vas in self.callers.items():
            if len(vas) == 1:
                self.at[next(iter(vas))].add(name)
        self.primary, self.aliases, self.alias_targets, self.unaliasable = {}, {}, {}, []

    def assign(self):
        """One definition per scaffold item; every other name becomes an alias."""
        for it in self.part.scaffold:
            va = it["start"]
            wanted = sorted(n for n in self.at.get(va, ()) if n not in self.object_names and not n.startswith("__imp_"))
            real = [n for n in wanted if not n.startswith("g_")]
            primary = real[0] if len(real) == 1 else g_name(va)
            it["label"] = primary
            it["names"] = len(wanted)
            self.primary[va] = primary
            for n in wanted:
                if n != primary:
                    self.aliases[n] = primary
        for va, names in sorted(self.at.items()):
            if self.part.object_owner(va) is None:
                continue
            here = sorted(self.object_defined.get(va, ()))
            for n in sorted(names):
                if n in self.object_names or n.startswith("__imp_"):
                    continue
                if here:
                    self.aliases[n] = here[0]
                else:
                    self.unaliasable.append((n, va))

    def link_name(self, target):
        """(symbol, addend, class) a relocation to target links against."""
        section = self.img.section(target)
        if section in (".text", ".idata"):
            symbol, addend, cls, _ = self.ctx.owner(target)
            return symbol, addend, cls
        it = self.part.scaffold_item(target)
        if it is not None:
            return it["label"], target - it["start"], "scaffold"
        span = self.part.object_owner(target)
        if span is not None:
            i = bisect.bisect_right(self._object_label_vas, target) - 1
            if i >= 0 and self._object_label_vas[i] >= span[0]:
                va = self._object_label_vas[i]
                return sorted(self.object_defined[va])[0], target - va, "object"
            return "", 0, "object-static"
        return "", 0, "linker" if section in SCAFFOLD_SECTIONS else (section or "outside")


# --------------------------------------------------------------------------- type review

def type_review(namer, comp, ledger, part):
    """Data names used with inconsistent types or sizes."""
    out = []
    by_identity = collections.defaultdict(set)
    for name in set(namer.callers) | set(comp["defined"]):
        ident = mangled_identity(name)
        if ident:
            by_identity[ident[0]].add(name)
    for ident, names in sorted(by_identity.items()):
        if len(names) > 1:
            vas = sorted({v for n in names for v in namer.callers.get(n, {})} |
                         {namer.object_at[n] for n in names if n in namer.object_at})
            out.append(("same-name-different-type", " ".join(sorted(names)), " ".join(f"{v:#010x}" for v in vas),
                        f"{len(names)} type encodings"))
    for va, names in sorted(namer.at.items()):
        sizes = {n: mangled_scalar_size(n) for n in names | namer.object_defined.get(va, set())}
        known = {n: s for n, s in sizes.items() if s is not None}
        if len(set(known.values())) > 1:
            out.append(("one-address-different-scalar-sizes", " ".join(sorted(known)), f"{va:#010x}",
                        " ".join(f"{n}={s}" for n, s in sorted(known.items()))))
        it = part.scaffold_item(va)
        if it is not None and it["proof"] == "structure" and it["start"] == va:
            for n, s in sorted(known.items()):
                if s != it["end"] - it["start"]:
                    out.append(("declared-scalar-but-structure", n, f"{va:#010x}",
                                f"declares {s} bytes; retail holds a {it['kind']} of {it['end'] - it['start']}"))
    for row in ledger.rows.values():
        if row["provenance"] != "compiler" or not row["symbol"] or "!" in row["symbol"]:
            continue
        s = mangled_scalar_size(row["symbol"])
        if s is not None and row["addend"] >= s:
            out.append(("access-past-declared-size", row["symbol"], f"{row['sym_va']:#010x}",
                        f"declares {s} bytes; referenced at +{row['addend']:#x} from {row['origin']}"))
    sizes = collections.defaultdict(set)
    for name, defs in comp["defined"].items():
        for path, number, value, _ in defs:
            info = comp["data_sections"][path][number]
            if info[2] & COMDAT_FLAG:
                sizes[name].add(info[1] - value)
    for name, found in sorted(sizes.items()):
        if len(found) > 1:
            out.append(("comdat-copies-differ-in-size", name, f"{namer.object_at.get(name, 0):#010x}",
                        " ".join(str(x) for x in sorted(found))))
    for f in comp["rows"]:
        if f.get("coff_type") == 0x20 and img_is_data_global(f["sym_va"]):
            out.append(("function-declared-data", f["symbol"], f"{f['sym_va']:#010x}", f["origin"]))
    return out


def img_is_data_global(va):
    return _image().section(va) in SCAFFOLD_SECTIONS


# --------------------------------------------------------------------------- proven scalars

class AccessReader:
    """The instruction holding a relocation site, by linear sweep of its ledger body."""

    def __init__(self, img, bodies):
        self.img = img
        self.starts = sorted(bodies)
        self.bodies = bodies
        self.cache = {}

    def insn_at(self, site):
        i = bisect.bisect_right(self.starts, site) - 1
        if i < 0 or site >= self.starts[i] + self.bodies[self.starts[i]]:
            return None
        start = self.starts[i]
        if start not in self.cache:
            body = self.img.read(start, self.bodies[start]) or b""
            self.cache[start] = list(_md().disasm(body, start))
        for insn in self.cache[start]:
            if insn.address <= site < insn.address + insn.size:
                return insn
        return None


def vendored_objects(rows):
    """{object path: tag} for objects whose ledger rows name exactly one upstream
    library (`vendored=<lib>-<ver>`), a prebuilt library member included. Rows
    with no tag do not disqualify (EA-patched Lua keeps some untagged); the tag
    is only a gate -- a vendored-declaration still needs the declaration read
    from the source file itself."""
    tags = collections.defaultdict(set)
    for row in rows:
        try:
            obj = str(build.row_object(row))
        except SystemExit:
            continue
        m = re.search(r"vendored=([^;,\s]+)", row.get("notes") or "")
        tags[obj].add(m.group(1) if m else None)
    return {obj: next(iter(t - {None})) for obj, t in tags.items() if len(t - {None}) == 1}


def element_access(insn, site):
    """(True, how, (start, width, direct)) when the instruction reads or writes
    the item through a memory operand whose disp32 is the site and whose element
    is not a 4-byte integer (8/16-bit integer or x87 float); `direct` is False
    when a base or index register moves the access; else (False, why, None)."""
    from capstone.x86 import X86_OP_MEM, X86_REG_INVALID
    if insn is None:
        return False, "site not inside a decoded ledger body", None
    if insn.disp_size != 4 or insn.address + insn.disp_offset != site:
        return False, f"`{insn.mnemonic} {insn.op_str}` takes the address (not a memory operand)", None
    mem = [op for op in insn.operands if op.type == X86_OP_MEM]
    if not mem:
        return False, f"`{insn.mnemonic} {insn.op_str}` has no memory operand", None
    size, m = mem[0].size, mem[0].mem
    span = (m.disp & 0xFFFFFFFF, size, m.base == X86_REG_INVALID and m.index == X86_REG_INVALID)
    if insn.mnemonic.startswith("f") and size in (4, 8, 10):
        return True, f"x87 {size}-byte float `{insn.mnemonic}`", span
    if size in (1, 2) and insn.mnemonic != "lea":
        return True, f"{8 * size}-bit `{insn.mnemonic}`", span
    return False, f"`{insn.mnemonic} {insn.op_str}` accesses {size} bytes", None


SCALAR_WORDS = frozenset(("char", "short", "int", "long", "float", "double", "signed", "unsigned", "__int8",
                          "__int16", "__int32", "__int64", "const", "volatile", "static", "extern", "local"))
QUALIFIERS = frozenset(("const", "volatile", "static", "extern", "local", "signed", "unsigned"))
C_COMMENT = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)
BASE_SIZES = (("__int64", 8), ("double", 8), ("__int8", 1), ("char", 1), ("__int16", 2), ("short", 2),
              ("__int32", 4), ("long", 4), ("float", 4), ("int", 4))


_PREPROCESSED = {}


def preprocess(source):
    """The source as MSVC 7.1 preprocesses it with its own build flags (cl -E),
    or None when that is not possible. Pack pragmas survive preprocessing."""
    source = Path(source)
    if source in _PREPROCESSED:
        return _PREPROCESSED[source]
    text = None
    try:
        rel = source.resolve().relative_to(ROOT.resolve())
    except ValueError:
        rel = None
    if rel is not None and source.suffix.lower() in (".c", ".cpp"):
        command, env = build.compiler_command(ROOT / rel, ROOT / "build" / "reloc_ledger" / "probe.obj")
        flags = [a for a in command if not a.startswith("-Fo")]
        flags[flags.index("-c")] = "-E"
        proc = subprocess.run(flags, capture_output=True, text=True, errors="replace", env=env, cwd=str(ROOT))
        if proc.returncode == 0 and proc.stdout.strip():
            zp = [a for a in flags if re.fullmatch(r"[-/]Zp\d*", a)]
            pack = int(zp[-1][3:] or 1) if zp else 8
            text = f"#pragma pack(from-flags {pack})\n" + proc.stdout
    _PREPROCESSED[source] = text
    return text


class CTypes:
    """Just enough of C's type system to lay out an upstream declaration:
    arithmetic types, typedefs, structs of them, pointers (4 bytes) and arrays,
    read from the translation unit as MSVC preprocesses it (cl -E, the build's
    own flags). A struct is laid out under the #pragma pack state in force at
    its definition (push/pop/set replayed from the preprocessed text, the /Zp
    flag as the default): each member aligned to min(its alignment, pack). A
    source that cannot be preprocessed, an unreadable pragma or
    __declspec(align) leaves structs unproven. Anything it cannot read makes
    the answer None (unproven), never a guess."""

    def __init__(self, source, preprocessed=None):
        if preprocessed is None:
            preprocessed = preprocess(source)
        self.exact = preprocessed is not None
        if self.exact:
            self.text = self.source = C_COMMENT.sub(" ", preprocessed)
        else:
            texts = []
            for path in sorted(source.parent.glob("*.h")) + [source]:
                try:
                    texts.append(C_COMMENT.sub(" ", path.read_text(encoding="latin-1")))
                except OSError:
                    continue
            self.text = "\n".join(texts)
            self.source = C_COMMENT.sub(" ", source.read_text(encoding="latin-1")) if source.is_file() else ""
        self.default_pack = 8
        m = re.match(r"#pragma pack\(from-flags (\d+)\)", self.text.lstrip())
        if m:
            self.default_pack = int(m.group(1))
        self.pragmas = [(m.start(), m.group(1)) for m in re.finditer(r"#\s*pragma\s+pack\s*\(([^)]*)\)", self.text)
                        if not m.group(1).startswith("from-flags")]

    def pack_at(self, pos):
        """MSVC's #pragma pack state at text offset `pos` (push/pop with ids and
        values, reset, set), or None when a directive cannot be read."""
        current, stack = self.default_pack, []
        for at, args in self.pragmas:
            if at >= pos:
                break
            parts = [a.strip() for a in args.split(",") if a.strip()]
            if not parts:
                current = self.default_pack
            elif parts[0].isdigit() and len(parts) == 1:
                current = int(parts[0])
            elif parts[0] == "show":
                continue
            elif parts[0] == "push":
                ident = next((x for x in parts[1:] if not x.isdigit()), None)
                stack.append((ident, current))
                value = next((x for x in parts[1:] if x.isdigit()), None)
                if value:
                    current = int(value)
            elif parts[0] == "pop":
                ident = next((x for x in parts[1:] if not x.isdigit()), None)
                value = next((x for x in parts[1:] if x.isdigit()), None)
                if ident:
                    while stack and stack[-1][0] != ident:
                        stack.pop()
                    if not stack:
                        return None
                if not stack:
                    return None
                current = stack.pop()[1]
                if value:
                    current = int(value)
            else:
                return None
        return current if current in (1, 2, 4, 8, 16) else None

    def layout(self, words, depth=0):
        """(size, align, [(offset, size, 'scalar'|'pointer')]) of a type given as words."""
        if depth > 6:
            return None
        words = [w for w in words if w not in QUALIFIERS or w in ("signed", "unsigned")]
        rest = [w for w in words if w not in ("signed", "unsigned")]
        if not rest and words:
            return 4, 4, [(0, 4, "scalar")]
        if rest and rest[0] == "struct" and len(rest) == 2:
            return self.struct(rest[1], depth)
        if rest and rest[0] == "enum":
            return 4, 4, [(0, 4, "scalar")]  # MSVC 7.1: an enum is an int
        if all(w in SCALAR_WORDS for w in rest):
            for name, size in BASE_SIZES:
                if name in rest:
                    return size, size, [(0, size, "scalar")]
            return None
        if len(rest) != 1:
            return None
        m = re.search(r"typedef\s+([\w \t]+?)[ \t]+(\**)\s*" + re.escape(rest[0]) + r"\s*;", self.text)
        if m:
            if m.group(2):
                return 4, 4, [(0, 4, "pointer")]
            return self.layout(m.group(1).split(), depth + 1)
        if re.search(r"typedef[^;]*\(\s*\*\s*" + re.escape(rest[0]) + r"\s*\)", self.text):
            return 4, 4, [(0, 4, "pointer")]  # a function-pointer typedef
        if (re.search(r"typedef\s+enum\s*\w*\s*\{[^{}]*\}\s*" + re.escape(rest[0]) + r"\s*;", self.text)
                or re.search(r"\benum\s+" + re.escape(rest[0]) + r"\s*\{", self.text)):
            return 4, 4, [(0, 4, "scalar")]
        m = re.search(r"typedef\s+struct\s*\w*\s*\{([^{}]*)\}\s*" + re.escape(rest[0]) + r"\s*;", self.text)
        if m:
            return self.members(m.group(1), depth, m.start())
        return None

    def struct(self, tag, depth):
        m = re.search(r"struct\s+" + re.escape(tag) + r"\s*\{([^{}]*)\}", self.text)
        return self.members(m.group(1), depth, m.start()) if m else None

    def members(self, body, depth, pos):
        """A struct body laid out under the pack state in force where it is
        defined; None when that state is unknown (no preprocessed unit, an
        unreadable pragma) or the body asks for __declspec(align)."""
        pack = self.pack_at(pos) if self.exact else None
        if pack is None or re.search(r"__declspec\s*\(\s*align", body):
            return None
        return self._members(body, depth, pack)

    def _members(self, body, depth, pack=8):
        fields, offset, align = [], 0, 1
        for decl in (d.strip() for d in body.split(";")):
            if not decl:
                continue
            m = re.fullmatch(r"([\w \t]+?)[ \t]+(\**)\s*(\w+)\s*((?:\[\s*\d+\s*\]\s*)*)", decl)
            if not m:
                return None
            count = 1
            for n in re.findall(r"\d+", m.group(4)):
                count *= int(n)
            inner = (4, 4, [(0, 4, "pointer")]) if m.group(2) else self.layout(m.group(1).split(), depth + 1)
            if inner is None:
                return None
            size, a, sub = inner
            a = min(a, pack)  # MSVC: a member aligns to the smaller of its own and the pack
            offset = (offset + a - 1) // a * a
            for k in range(count):
                fields += [(offset + k * size + o, s, kind) for o, s, kind in sub]
            offset += size * count
            align = max(align, a)
        return (offset + align - 1) // align * align, align, fields

    def declaration(self, cname):
        """(declared type text, element layout) of the one initialised definition
        of `cname` in the source file, or None."""
        found = re.findall(r"(?:^|[;{}])\s*([A-Za-z_][\w \t]*?)[ \t]+(\**)\s*" + re.escape(cname)
                           + r"\s*((?:\[[^\]]*\]\s*)*)=", self.source, flags=re.M)
        if len(found) != 1:
            return None
        if found[0][1]:
            return found[0][0].strip() + " *", (4, 4, [(0, 4, "pointer")])
        element = self.layout(found[0][0].split())
        return (found[0][0].strip(), element) if element else None


def declared_size(source, cname, types=None):
    """(bytes, declaration) the one file-scope definition of `cname` in `source`
    declares -- its element type's size times every array dimension, each a
    number after preprocessing -- or None (no single definition, an unsized or
    symbolic dimension, a type it cannot lay out)."""
    types = types or CTypes(Path(source))
    defs = file_scope_definitions(types.source, cname)
    if not defs or len(defs) != 1:
        return None
    m = re.match(r"^(?:static\s+)?([A-Za-z_][\w \t]*?)[ \t]+(\**)\s*" + re.escape(cname)
                 + r"\s*((?:\[[^\]]*\]\s*)*)(=|;)", defs[0][1])
    if not m:
        return None
    count = 1
    for dim in re.findall(r"\[([^\]]*)\]", m.group(3)):
        if not dim.strip().isdigit():
            return None
        count *= int(dim.strip())
    element = (4, 4, []) if m.group(2) else types.layout(m.group(1).split())
    if element is None:
        return None
    return element[0] * count, defs[0][1]


def upstream_declaration(source, cname):
    """(declared type, element layout) of `cname` in an upstream source, or None."""
    return CTypes(source).declaration(cname) if source.is_file() else None


def scalar_bytes(layout, offset):
    """True when every byte of the dword at `offset` (from the array start) falls in
    an arithmetic field or padding of the element layout, never in a pointer."""
    size, _, fields = layout
    for b in range(offset, offset + 4):
        o = b % size
        if any(kind == "pointer" and f <= o < f + s for f, s, kind in fields):
            return False
    return True


def c_name(symbol):
    """The C identifier a data symbol spells: `_name` (C) or `?name@@...` at global
    scope (C++); None for anything else (string literals, scoped names)."""
    if symbol.startswith("?"):
        m = re.match(r"\?(\w+)@@", symbol)
        return m.group(1) if m else None
    if symbol.startswith(("$", ".")):
        return None
    return symbol[1:] if symbol.startswith("_") else symbol


def prove_scalars(img, comp, L, rows, bodies, objects_root=None):
    """proven-scalar rows for the in-image dwords our objects' matching data
    sections hold WITHOUT a relocation, word by word. A word is a number when:

      library-member        the section is a prebuilt upstream library member
                            (its own relocation table has none there); the
                            member's sha256 is recorded
      vendored-declaration  every row of the object is vendored upstream code
                            and the source file in the repo (sha256 recorded)
                            holds the one initialised definition of the symbol
                            covering the word, and every byte of the word falls
                            in an arithmetic field (or padding) of its element
                            type as laid out from that source (typedefs and
                            structs resolved; anything unreadable is unproven)
      element-access        every retail reference into the section is an
                            8/16-bit integer or x87 float access, nothing in
                            data points into it, and direct (unindexed)
                            accesses cover every byte of the word

    Anything else stays unproven. Returns (counts, disagreements)."""
    import hashlib
    vendored = vendored_objects(rows)
    sources = {}
    for row in rows:
        try:
            sources.setdefault(str(build.row_object(row)), row["source"])
        except SystemExit:
            continue
    if objects_root:
        vendored = {str(remap(k, objects_root)): v for k, v in vendored.items()}
        sources = {str(remap(k, objects_root)): v for k, v in sources.items()}
    reader = AccessReader(img, bodies)
    by_section = collections.defaultdict(list)
    for entry in comp["unrelocated"]:
        key, base, size, va, value = entry[:5]
        symbol = entry[5] if len(entry) > 5 else None
        by_section[(key, base, size)].append((va, value, symbol))
    refs = sorted((r["site"], r["sym_va"], r["target"]) for r in L.rows.values()
                  if r["provenance"] not in NOT_A_RELOCATION)
    targets = collections.defaultdict(list)   # referenced address -> sites
    for site, sym_va, target in refs:
        targets[sym_va].append(site)
        if target != sym_va:
            targets[target].append(site)
    target_keys = sorted(targets)
    digests, types = {}, {}

    def sha(path):
        if path not in digests:
            digests[path] = hashlib.sha256(Path(path).read_bytes()).hexdigest()[:16]
        return digests[path]

    verdicts, disagreements = collections.Counter(), []
    for (key, base, size), words in sorted(by_section.items()):
        path, _ = key
        if comp["verdicts"].get(key, (0, ""))[1] != "verified":
            continue
        source = sources.get(path, "")
        tag = vendored.get(path)
        lo, hi = bisect.bisect_left(target_keys, base), bisect.bisect_left(target_keys, base + size)
        sites = sorted({s for t in target_keys[lo:hi] for s in targets[t]})
        covered, access_why = set(), None if sites else "no retail reference found"
        for site in sites:
            if img.section(site) != ".text":
                if not base <= site < base + size:
                    access_why = f"data at {site:#010x} points into it"
                    break
                continue
            ok, how, span = element_access(reader.insn_at(site), site)
            if not ok:
                access_why = f"{site:#010x}: {how}"
                break
            if span[2]:
                covered.update(range(span[0], span[0] + span[1]))
        for va, value, symbol in words:
            evidence = None
            if tag and source.lower().endswith(".lib"):
                evidence = ("library-member", f"{tag}: prebuilt member {Path(path).name} sha256 {sha(path)} "
                                              "carries no relocation there")
            elif tag and symbol and c_name(symbol[0]):
                src = ROOT / source
                cname = c_name(symbol[0])
                if src not in types:
                    types[src] = CTypes(src) if src.is_file() else None
                decl = types[src].declaration(cname) if types[src] else None
                if decl is not None and scalar_bytes(decl[1], va - (base + symbol[1])):
                    evidence = ("vendored-declaration", f"{tag}: {source} sha256 {sha(src)} declares "
                                                        f"`{decl[0]} {cname}`; +{va - base - symbol[1]:#x} lies in "
                                                        "arithmetic fields of its element")
            if evidence is None and access_why is None and all(b in covered for b in range(va, va + 4)):
                evidence = ("element-access", f"{len(sites)} reference(s) into the section, each an 8/16-bit "
                                              "or x87 element access; direct accesses cover every byte")
            if evidence is None:
                verdicts["unproven"] += 1
                continue
            if L.add(va, KIND_SCALAR, value, "proven-scalar", evidence[0], "high", origin=evidence[1]):
                verdicts[evidence[0]] += 1
            elif L.rows[va]["provenance"] == "proven-scalar":
                verdicts["same-word-another-copy"] += 1  # a second object's copy of the section
            else:
                old = L.rows[va]
                verdicts["pointer-row-disagrees"] += 1
                disagreements.append((va, value, evidence[0], old["provenance"], old["rule"], path))
    return verdicts, disagreements


# --------------------------------------------------------------------------- driver

def remap(path, objects_root):
    return Path(objects_root) / Path(path).resolve().relative_to(ROOT.resolve())


def run(args, log=print):
    img = _image()
    ledger_rows = [r for r in build.load_function_rows() if r["target_rva"].startswith("0x")]
    bodies = {}
    for r in ledger_rows:
        va = img.base + int(r["target_rva"], 16)
        bodies[va] = max(int(r["target_size"]), bodies.get(va, 0))
    code_starts = set(bodies)
    for r in read_csv_rows(REVERSE / "ghidra_functions.csv"):
        code_starts.add(img.base + int(r["rva"], 16))

    def is_code_ptr(v):
        """A function start, or an incremental-link stub (E9 rel32) that jumps to one."""
        if v in code_starts:
            return True
        head = img.read(v, 5) if img.section(v) == ".text" else None
        return bool(head) and head[0] == 0xE9 and (
            (v + 5 + struct.unpack_from("<i", head, 1)[0]) & 0xFFFFFFFF) in code_starts
    workers = max(1, min(int(os.environ.get("BUILD_POOL", "4")), 4))
    anchors = {}
    for path, rows in object_anchors(ledger_rows).items():
        real = remap(path, args.objects_root) if args.objects_root else Path(path)
        if real.exists():
            anchors[str(real)] = rows
    if args.objects_rsp:
        # exactly the objects a census links (repo-relative paths, one per line)
        root = args.objects_root or ROOT
        listed = [str(Path(root) / line.strip().strip('"'))
                  for line in args.objects_rsp.read_text(encoding="utf-8").splitlines() if line.strip()]
        anchors = {p: anchors.get(p, []) for p in listed if Path(p).exists()}
    objects = sorted(anchors)
    log(f"reloc_ledger: {len(objects):,} objects, {sum(len(v) for v in anchors.values()):,} anchored rows")
    comp = compiler_phase(objects, anchors, workers, log)
    L = Ledger(img)
    for f in comp["rows"]:
        where = "data-dir32" if img.is_data(f["site"]) else "code-dir32"
        L.add(f["site"], f["kind"], f["target"], "compiler", where, "exact", f["symbol"], f["addend"],
              f["origin"], f["sym_va"])
    dump_rows = load_dump_rows(args.dump_relocs / "relocs.csv", img)
    if not dump_rows:
        log(f"reloc_ledger: no dump relocations under {args.dump_relocs} (run tools/dump_relocs.py --all)")
    for site, kind, target, symbol, addend, rule, evidence, body in dump_rows:
        L.add(site, kind, target, "dump-analysis", rule, dump_confidence(rule, evidence), symbol, addend, body)
    chunks, chunk, size = [], [], 0
    for va in sorted(bodies):
        chunk.append((va, bodies[va]))
        size += bodies[va]
        if size > 200_000:
            chunks.append(chunk)
            chunk, size = [], 0
    if chunk:
        chunks.append(chunk)
    uses = []
    with concurrent.futures.ProcessPoolExecutor(workers) as pool:
        for found in pool.map(scan_uses, chunks):
            uses.extend(found)
    log(f"reloc_ledger: {len(uses):,} candidate uses in {len(bodies):,} bodies")
    vtable_starts, tables, use_bad = {}, {}, []
    for what, rule, x, site in sorted(uses, key=lambda u: (u[2], u[3])):
        if not img.is_data(x) or img.section(x) == ".idata":
            continue
        if what == "ptr":
            value = img.u32(x)
            if value is None:
                continue
            if img.in_image(value):
                L.add(x, DIR32, value, "use-proven", rule, "high", origin=f"{site:#010x}")
            elif value:
                use_bad.append((x, value, rule, site))
        elif what == "table":
            tables.setdefault(x, (rule, site))
        elif what == "vptr" and img.section(x) == ".rdata" and is_code_ptr(img.u32(x)):
            vtable_starts.setdefault(x, site)
    S = Structures(img)
    seeds = {r["sym_va"] for r in L.rows.values()} | {r["target"] for r in L.rows.values()}
    for va in sorted(seeds):
        if img.section(va) == ".rdata":
            S.funcinfo(va) or S.throwinfo(va)
    code_refs = {r["sym_va"] for r in L.rows.values() if img.section(r["site"]) == ".text"}
    for va in sorted(code_refs):
        if img.section(va) in (".rdata", ".data") and va not in S.items:
            S.fieldparse(va, is_code_ptr)
    for site, target, rule in S.rows:
        L.add(site, DIR32, target, "structure", rule, "high")
    log(f"reloc_ledger: {len(S.items):,} structures, {len(S.rows):,} structure pointers, "
        f"{len(vtable_starts):,} vftable starts, {len(tables):,} indexed tables")
    names_at = set()
    for name, vas in comp["names"].items():
        names_at |= set(vas)
    for row in read_csv_rows(REVERSE / "dir32_addresses.csv"):
        names_at.add(int(row["va"], 16))
    for row in read_csv_rows(REVERSE / "exports.csv"):
        if row["kind"] == "data" and row["rva"].startswith("0x"):
            names_at.add(img.base + int(row["rva"], 16))
    part = Partition(img, comp, S, L, vtable_starts, names_at)
    for start in sorted(vtable_starts):
        for va in part.vtable_run(start, is_code_ptr):
            L.add(va, DIR32, img.u32(va), "vtable", "vftable-slot", "high", origin=f"{vtable_starts[start]:#010x}")
    for start, (rule, site) in sorted(tables.items()):
        if part.object_owner(start) is not None:
            continue
        code_table = rule.startswith(("call", "jmp"))
        test = is_code_ptr if code_table else img.in_image
        for va in part.run_of(start, test, allow_zero=not code_table):
            L.add(va, DIR32, img.u32(va), "use-proven", "table-" + rule, "medium", origin=f"{site:#010x}")
    summary_extra = {}
    scalars, disagreements = prove_scalars(img, comp, L, ledger_rows, bodies, args.objects_root)
    comp["scalar_disagreements"] = disagreements
    log(f"reloc_ledger: object-section in-image dwords without a relocation: {dict(scalars)}")
    part.finish(L)
    def evidence(value, raw):
        if is_code_ptr(value):
            return "code-start"
        if raw[1] == raw[3] == 0 and 0x20 <= raw[0] < 0x7F and 0x20 <= raw[2] < 0x7F:
            return "utf16-text"
        if all(0x20 <= c < 0x7F for c in raw[:3]) and raw[3] == 0:
            return "ascii-text"
        if (img.section(value) in (".rdata", ".data") and looks_string(img, value) >= 2
                and (img.read(value - 1, 1) == b"\0" or value % 4 == 0)):
            return "string-start"
        if value in part.bounds:
            return "item-start"
        return "interior"

    unaligned = 0
    for va, value, aligned, why in part.scan_candidates(L, evidence):
        L.add(va, DIR32, value, "scan-candidate", "aligned-scan" if aligned else "unaligned-scan", "none",
              origin=why)
        unaligned += not aligned
    namer = Namer(img, part, comp, dump_rows, L)
    namer.assign()
    for row in L.rows.values():
        if row["provenance"] == "proven-scalar":
            row["link_symbol"], row["link_addend"], row["link_class"] = "", 0, "scalar"
            continue
        row["link_symbol"], row["link_addend"], row["link_class"] = namer.link_name(row["target"])
    settle = collections.Counter()
    for row in L.rows.values():
        if img.section(row["site"]) not in SCAFFOLD_SECTIONS or row["provenance"] == "compiler":
            continue
        if row["provenance"] == "proven-scalar":
            settle["scalar"] += 1
        elif row["provenance"] == "scan-candidate":
            settle["unproven-scaffold-aligned" if row["rule"] == "aligned-scan" else "unproven-scaffold-unaligned"] += 1
        else:
            settle["pointer"] += 1
    settle["unproven-object-section"] = scalars.get("unproven", 0)
    summary_extra["candidate_words"] = dict(settle)
    summary_extra["object_unrelocated_in_image_dwords"] = dict(scalars)
    types = type_review(namer, comp, L, part)
    return write_outputs(args.out, img, L, part, namer, comp, S, use_bad, unaligned, types, log, summary_extra)


# --------------------------------------------------------------------------- outputs

LEDGER_FIELDS = ["site_section", "site_va", "kind", "target_va", "target_section", "symbol", "addend", "sym_va",
                 "provenance", "rule", "confidence", "link_symbol", "link_addend", "link_class", "origin"]
ITEM_FIELDS = ["start", "end", "size", "section", "source", "kind", "proof", "verdict", "label", "names", "origin"]


def hx(v):
    return f"0x{v & 0xFFFFFFFF:08X}"


def sx(v):
    return f"{v:#x}" if v >= 0 else f"-{-v:#x}"


def write_csv(path, fields, rows):
    with path.open("w", newline="", encoding="utf-8") as handle:
        w = csv.writer(handle, lineterminator="\n")
        w.writerow(fields)
        w.writerows(rows)


def write_outputs(out, img, L, part, namer, comp, S, use_bad, unaligned, types, log=print, extra=None):
    out.mkdir(parents=True, exist_ok=True)
    rows = sorted(L.rows.values(), key=lambda r: r["site"])
    write_csv(out / "ledger.csv", LEDGER_FIELDS, (
        [img.section(r["site"]), hx(r["site"]), KIND_NAME[r["kind"]], hx(r["target"]), img.section(r["target"]) or "",
         r["symbol"], sx(r["addend"]), hx(r["sym_va"]), r["provenance"], r["rule"], r["confidence"],
         r["link_symbol"], sx(r["link_addend"]), r["link_class"], r["origin"]] for r in rows))
    write_csv(out / "items.csv", ITEM_FIELDS, (
        [hx(it["start"]), hx(it["end"]), it["end"] - it["start"], it["section"], it["source"], it["kind"],
         it["proof"], it["verdict"], it.get("label", ""), it.get("names", ""), it["origin"]] for it in part.items))
    name_rows = []
    for name, vas in sorted(namer.callers.items()):
        for va, sources in sorted(vas.items()):
            if name in namer.conflicts:
                role = "conflict"
            elif name in namer.object_names:
                role = "object" if namer.object_at.get(name) == va else "object-elsewhere"
            elif namer.primary.get(va) == name:
                role = "scaffold"
            elif name in namer.aliases:
                role = "alias"
            elif name.startswith("__imp_"):
                role = "import"
            else:
                role = "unplaced"
            name_rows.append([hx(va), name, "+".join(sorted(sources)), role, namer.aliases.get(name, "")])
    write_csv(out / "names.csv", ["va", "name", "sources", "role", "alias_of"], name_rows)
    write_csv(out / "review_scan.csv", ["site_va", "value", "value_section", "alignment", "evidence", "item",
                                        "item_kind", "item_label"], (
        [hx(r["site"]), hx(r["target"]), img.section(r["target"]) or "", r["rule"].split("-")[0], r["origin"],
         hx(part.scaffold_item(r["site"])["start"]), part.scaffold_item(r["site"])["kind"],
         part.scaffold_item(r["site"]).get("label", "")] for r in rows if r["provenance"] == "scan-candidate"))
    write_csv(out / "call_targets.csv", ["name", "symbol_va", "destination_va", "sites"], (
        [name, hx(symbol_va), hx(destination), n] for name, targets in sorted(comp["calls"].items())
        for (symbol_va, destination), n in sorted(targets.items())))
    write_csv(out / "proven_scalars.csv", ["va", "value", "rule", "evidence"], (
        [hx(r["site"]), hx(r["target"]), r["rule"], r["origin"]] for r in rows if r["provenance"] == "proven-scalar"))
    write_csv(out / "review_size.csv", ["start", "size", "section", "kind", "proof", "label"], (
        [hx(it["start"]), it["end"] - it["start"], it["section"], it["kind"], it["proof"], it.get("label", "")]
        for it in part.scaffold if it["proof"] in ("inferred", "structure-split")))
    write_csv(out / "review_types.csv", ["check", "names", "va", "detail"], types)
    conflicts, seen_sections = [], collections.Counter()
    for c in comp["conflicts"]:
        if c[0] == "section":
            seen_sections[c[1]] += 1
            if seen_sections[c[1]] > 1:
                continue
            conflicts.append(list(c))
        else:
            first = int(c[2].split()[0], 16)
            conflicts.append(["name-data" if img.is_data(first) else "name-code"] + list(c[1:]))
    conflicts += [["site-clash", hx(site), f"{old['provenance']}:{hx(old['target'])}",
                   f"{new['provenance']}:{hx(new['target'])}", f"{old['origin']} | {new['origin']}"]
                  for site, old, new in L.clashes]
    conflicts += [["literal-where-object-relocates", hx(f["site"]), hx(f["literal"]), f["symbol"], f["origin"]]
                  for f in comp["literals"]]
    conflicts += [["scalar-evidence-vs-pointer-row", hx(va), hx(value), f"{ev} vs {prov}:{rule}", Path(obj).name]
                  for va, value, ev, prov, rule, obj in comp.get("scalar_disagreements", [])]
    conflicts += [["use-loads-non-address", hx(x), hx(v), rule, hx(site)] for x, v, rule, site in use_bad]
    conflicts += [["unaliasable-name", hx(va), n, "", "caller name inside an object section with no external label"]
                  for n, va in namer.unaliasable]
    conflicts += [["object-name-two-homes", hx(vas[0]), n, " ".join(hx(v) for v in vas[1:]),
                   "our objects place one name at several retail copies"]
                  for n, vas in sorted(namer.object_multi_home.items())]
    conflicts += [[kind, hx(start), f"{size:#x}", obj, str(detail)] for kind, obj, start, size, detail in part.review]
    write_csv(out / "review_conflicts.csv", ["check", "a", "b", "c", "detail"], conflicts)

    prov = collections.Counter(r["provenance"] for r in rows)
    by_site = collections.Counter((r["provenance"], "code" if img.section(r["site"]) == ".text" else "data")
                                  for r in rows)
    items = collections.Counter()
    item_bytes = collections.Counter()
    for it in part.items:
        key = f"{it['source']}:{it['proof']}"
        items[key] += 1
        item_bytes[key] += it["end"] - it["start"]
    summary = {
        "ledger_rows": len(rows),
        "by_provenance": dict(prov),
        "by_provenance_site": {f"{p}/{s}": n for (p, s), n in sorted(by_site.items())},
        "by_rule": dict(collections.Counter(f"{r['provenance']}:{r['rule']}" for r in rows)),
        "link_class": dict(collections.Counter(r["link_class"] for r in rows if r["provenance"] != "scan-candidate")),
        "compiler": dict(comp["stats"]),
        "object_sections": dict(collections.Counter(v for _, v in comp["verdicts"].values())),
        "items": dict(items), "item_bytes": dict(item_bytes),
        "scaffold_items": len(part.scaffold),
        "scaffold_bytes": sum(it["end"] - it["start"] for it in part.scaffold),
        "structures": dict(collections.Counter(k for _, k in S.items.values())),
        "unaligned_in_image_dwords_in_scaffold": unaligned,
        "scan_evidence": dict(collections.Counter(f"{r['rule']}:{r['origin']}" for r in rows
                                                  if r["provenance"] == "scan-candidate")),
        "names": {"caller_names": len(namer.callers), "conflicting": len(namer.conflicts),
                  "scaffold_primary": len(namer.primary), "aliases": len(namer.aliases),
                  "unaliasable": len(namer.unaliasable), "object_multi_home": len(namer.object_multi_home)},
        "review": dict(collections.Counter(c[0] for c in conflicts)),
        "types": dict(collections.Counter(t[0] for t in types)),
    }
    summary.update(extra or {})
    (out / "summary.json").write_text(json.dumps(summary, indent=1, sort_keys=True), encoding="utf-8")
    log(json.dumps(summary, indent=1, sort_keys=True))
    return 0


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--objects-root", type=Path, default=None,
                    help="read row objects from this checkout (same relative paths); default: this tree")
    ap.add_argument("--dump-relocs", type=Path, default=ROOT / "build" / "dump_relocs",
                    help="tools/dump_relocs.py --all output directory")
    ap.add_argument("--objects-rsp", type=Path, default=None,
                    help="read exactly these objects (a link_census objects.rsp); default: every matched row's")
    ap.add_argument("--out", type=Path, default=OUT)
    args = ap.parse_args(argv)
    return run(args)


if __name__ == "__main__":
    sys.exit(main())
