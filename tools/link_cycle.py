#!/usr/bin/env python3
"""Link the tree at retail's addresses and measure every matched row in the image.

BFME1 port of Open-BFME-2's tools/link_cycle.py (same phases, same series,
same receipt), with BFME1's binding rules:

  - Retail was linked /INCREMENTAL: a call or a vtable slot encodes the ILT
    thunk (`jmp body`, 0x1000..0x5B000, or a `?j_` row), never the body.
    This link is /INCREMENTAL:NO (/ORDER forbids an ILT), so a reference that
    lands on the body counts when retail's thunk jumps to that body
    (`ilt_routes`); one that lands on the thunk's own unit counts directly.
  - No ICF in retail (/OPT:NOICF here too); the twin rule stays, as the
    diagnostic it was in BFME2, and certifies nothing it cannot prove.
  - One .text group: BFME1 places EH funclets next to their functions, so a
    filler never carries a $x/$yc/$yd group name.
  - Dumps (game/gen_asm/, game/masm_dumps/, other .asm) and generated rows are
    their own kinds (`generated`, `asm`): measured like any row, never credit,
    and in the source closure an edge into one is not a leaf (like a filler).
    tools/dump_apply.py makes their own references symbolic; a dump still in
    raw `db` fails the shifted check wherever it reaches out.
  - Import libraries come from targets/game/reverse/imports.csv (retail's table).

link_census.py asks "does the tree link?". This tool asks "where does each
matched row land in a real link, and is it wired the way retail is?". It is the
productionised /ORDER pilot (research 14), with the link-setup and measurement
fixes of research 29, 31 and the round-2 review:

  1. Collect the object of every matched row (link_census.objects; --build
     compiles stale ones first). Each object section holding matched rows is a
     unit; a unit is ordered at its retail start when its COMDAT head can be
     named in /ORDER and its section group and alignment allow it.
  2. Every retail .text byte no ordered unit covers becomes a retail-byte
     filler COMDAT, so ordered units land at their retail RVAs. Unplaced code
     moves to .text$zz (private object copies) so it cannot push retail's
     groups. A unit whose linked footprint differs from its retail extent is
     quarantined and the link repeats until no order item drifts.
  3. Link setup: __except_list is an absolute 0 (the CRT's definition);
     import libraries are generated from retail's own import table for every
     __imp_ name an object references; /OPT:NOICF. Unresolved names get 4-byte
     data stubs, duplicate definitions need /FORCE; both are counted.
  4. Measure (per ledger row, every failing relocation, not the first):
     - a unit counts only when the /MAP shows the link selected its own copy
       of the head symbol (`not-selected` otherwise: /FORCE kept another);
     - code references translate through the unit or filler that holds the
       linked target and must equal retail's target;
     - an __ehhandler$ thunk counts as its owner function's (owner + offset)
       only when the row is that owner and the FuncInfo, unwind and try maps
       and funclet bodies equal retail's;
     - an other-name copy is an ICF twin only from the fold list this tool
       builds: the definition the /MAP says the link put there (at its own
       offset in its section), retail's row size within its extent, equal
       non-relocation bytes, every relocation resolving to retail's target;
     - data references must map 1:1, and the linked datum's bytes must equal
       retail's at the referenced address; a datum whose name is pinned in
       symbols.csv must sit at its pin (the `pinned` series also fails
       unpinned data). Pointers INSIDE a datum are references too: code
       pointers translate, data pointers must map 1:1, reach a real datum
       (not a stub) and agree with its pin, and that datum is checked the
       same way, to any depth (`data-ptr-*` failures);
     - imports match on (dll, name or ordinal). Retail's duplicate IAT slots
       of one import are one datum only for references that read through the
       slot (call/jmp/push/mov [slot]) on both sides; a reference that can
       observe the slot itself keeps the 1:1 rule.
     Closed-strict: the closure graph holds units, certified twins, datums and
     EH thunks; a node is ok when self-strict AND shift-verified (5), and a
     row closes when its unit reaches only ok nodes. A filler, a stub or a
     node the graph does not hold is never a leaf. Credit = unique retail
     bytes of placed, closed-strict authored rows; fillers, stubs and aliases
     never count.
  5. A second link at a shifted base (default 0x10000000) with the same
     inputs. The layout must be identical; in every node's bytes (rows'
     code, twins, datums, EH FuncInfo and its maps) non-relocation bytes must
     not move and every DIR32 must move by exactly the delta; code may hold no
     unrelocated retail data VA or row start. A failure takes the node's whole
     dependent closure out of credit. No shifted link: nothing is credited.
  6. A receipt (build/link_cycle/receipt.json) binds, as taken at the START
     and re-proved at the end (else receipt.rejected.json and exit 1): the
     commit (or a snapshot's commit and tree digest), this tool's digest,
     toolchain, retail, the ledgers, the objects' identity digest and the
     per-TU provenance (provenance.json: source, sha256, dependency record,
     object identity; an object not current for its source is refused).
     `core_sha256` digests the reproducible part: a cold and a cached run of
     the same inputs must give the same core. Warm-start caches (quarantine,
     stubs) are reused only for the objects they were computed from.
     `--snapshot REV` measures an immutable export of REV (git archive with
     submodules) in its own directory, with its own outputs and no shared
     object store; only such a receipt is `authoritative`.

  python3 tools/link_cycle.py [--build] [--max-iter 6] [--shift-base 0x10000000]
  python3 tools/link_cycle.py --snapshot HEAD --build [--reuse-quarantine --reuse-stubs]
  python3 tools/link_cycle.py --measure-only     # re-measure the last links (never authoritative)

Outputs in build/link_cycle/: link_status.csv (one row per matched ledger
row), fold_list.csv, provenance.json, receipt.json, base.map/.exe/.log, shift.*. Diagnostic:
the image is not expected to run.
"""
import argparse
import bisect
import collections
import concurrent.futures
import csv
import hashlib
import json
import os
import re
import struct
import subprocess
import sys
import tempfile
import time
from pathlib import Path

# LINK_CYCLE_ROOT: the tree to measure (run_in_snapshot points it at an exported
# snapshot); this file stays the measuring tool and is digested as such.
ROOT = Path(os.environ.get("LINK_CYCLE_ROOT") or Path(__file__).resolve().parents[1]).resolve()
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402
import link_census as census  # noqa: E402

OUT = ROOT / "build" / "link_cycle"
BASE = 0x400000
SHIFT_BASE = 0x10000000
# retail .text is four groups: .text | .text$x (EH funclets) | .text$yc (dynamic
# initializers) | .text$yd (atexit dtors). /ORDER sorts only within a group, so
# a filler carries its region's group name. Boundaries: retail BFME2 1.06.
REGIONS = [(0x1000, ".text")]           # BFME1: funclets sit beside their functions
ILT = (0x1000, 0x5B000)                  # retail's ILT: rel32 jumps only (no .reloc site below 0x5B000)
REVERSE = ROOT / "targets" / "game" / "reverse"
ABSOLUTE = {"__except_list": 0}          # exsup.asm: __except_list equ 0 (an FS: offset)
TOOL_FILES = ("link_cycle.py", "link_census.py", "build.py", "dump_apply.py", "dump_relocs.py")
COMDAT, EXTERNAL, STATIC, WEAK = 0x1000, 2, 3, 105
REL32, DIR32 = 0x14, 6


# ---------------------------------------------------------------- COFF
class Sec:
    __slots__ = ("idx", "name", "size", "ptr", "flags", "relocs", "sel")


class Sym:
    __slots__ = ("i", "name", "value", "sec", "cls")


def parse_coff(data):
    """(sections, {raw index: Sym}) of an i386 COFF object."""
    _, nsec, _, symptr, nsym, opt, _ = struct.unpack_from("<HHIIIHH", data, 0)
    strtab = symptr + nsym * 18

    def text(raw):
        if raw[:4] == b"\0\0\0\0":
            off = strtab + struct.unpack_from("<I", raw, 4)[0]
            return data[off:data.index(b"\0", off)].decode("latin-1")
        return raw.rstrip(b"\0").decode("latin-1")
    secs = []
    for k in range(nsec):
        o = 20 + opt + 40 * k
        s = Sec()
        s.idx = k + 1
        nm = data[o:o + 8].rstrip(b"\0").decode("latin-1")
        if nm.startswith("/"):
            off = strtab + int(nm[1:])
            nm = data[off:data.index(b"\0", off)].decode("latin-1")
        s.name = nm
        s.size, s.ptr, rptr = struct.unpack_from("<III", data, o + 16)
        nrel = struct.unpack_from("<H", data, o + 32)[0]
        s.flags = struct.unpack_from("<I", data, o + 36)[0]
        s.relocs = [struct.unpack_from("<IIH", data, rptr + 10 * r) for r in range(nrel)]
        s.sel = 0
        secs.append(s)
    syms, i = {}, 0
    while i < nsym:
        o = symptr + 18 * i
        y = Sym()
        y.i, y.name = i, text(data[o:o + 8])
        y.value, y.sec, _, y.cls, naux = struct.unpack_from("<IhHBB", data, o + 8)
        syms[i] = y
        if y.cls == STATIC and naux and 0 < y.sec <= nsec and y.value == 0:
            s = secs[y.sec - 1]
            if s.flags & COMDAT and s.name == y.name:
                s.sel = struct.unpack_from("<B", data, o + 18 + 14)[0]
        i += 1 + naux
    return secs, syms


def write_coff(path, sections, symbols):
    """sections [(name, flags, body, comdat_sel)], symbols [(name, secno, value, cls)];
    secno -1 = absolute."""
    strings = bytearray(4)

    def field(n):
        raw = n.encode("latin-1")
        if len(raw) <= 8:
            return raw.ljust(8, b"\0")
        o = len(strings)
        strings.extend(raw + b"\0")
        return struct.pack("<II", 0, o)
    symtab = bytearray()
    for k, (name, flags, body, sel) in enumerate(sections, 1):
        if sel:
            symtab += field(name) + struct.pack("<IhHBB", 0, k, 0, STATIC, 1)
            symtab += struct.pack("<IHHIHBBH", len(body), 0, 0, 0, 0, sel, 0, 0)
    for name, sec, val, cls in symbols:
        symtab += field(name) + struct.pack("<IhHBB", val, sec, 0x20 if sec > 0 else 0, cls, 0)
    hdr_end = 20 + 40 * len(sections)
    shdr, bodies = bytearray(), bytearray()
    for name, flags, body, sel in sections:
        ptr = hdr_end + len(bodies) if body else 0
        shdr += name.encode().ljust(8, b"\0") + struct.pack("<IIIIIIHHI", 0, 0, len(body), ptr, 0, 0, 0, 0, flags)
        bodies += body
    strings[0:4] = struct.pack("<I", len(strings))
    path.write_bytes(struct.pack("<HHIIIHH", 0x14C, len(sections), 0, hdr_end + len(bodies), len(symtab) // 18, 0, 0)
                     + shdr + bodies + symtab + strings)
    return path


def region(a):
    g = REGIONS[0][1]
    for s, n in REGIONS:
        if a >= s:
            g = n
    return g


def align_of(flags):
    n = (flags >> 20) & 0xF
    return 1 << (n - 1) if n else 16


def order_name(name):
    """link.exe 7.1 /ORDER drops one leading underscore of each entry."""
    return name[1:] if name.startswith("_") else name


def row_kind(row):
    notes = row.get("notes", "")
    for k in ("gen-funclet", "gen-import", "gen-alias"):
        if k in notes:
            return k
    src = row.get("source", "")
    if src.startswith(("game/gen_asm/", "game/gen_small/")):
        return "generated"
    if src.lower().endswith(".asm"):
        return "asm"
    return "real"


def group_of(secname):
    """The image section group a COFF code section joins: .text$d0055e510 (a
    MASM dump segment) joins .text; $x/$yc/$yd are groups of their own."""
    head, _, tail = secname.partition("$")
    return secname if tail in ("x", "yc", "yd") else head


def retail_imports():
    """{imported name: {dll, lower case}} from retail's import table."""
    found = collections.defaultdict(set)
    with (REVERSE / "imports.csv").open(newline="", encoding="utf-8") as f:
        for r in csv.DictReader(f):
            if r["name"]:
                found[r["name"]].add(r["dll"].lower())
    return dict(found)


# ---------------------------------------------------------------- analyze
SWAP = {}   # census object -> tools/dump_relocs.py relocatable object (game/gen_asm/ dumps)


def row_obj(row):
    p = build.row_object(row)
    return SWAP.get(p.resolve(), p)


def load_swap(rows):
    """game/gen_asm/ dumps link as tools/dump_relocs.py's relocatable objects
    (build/dump_relocs/obj/), the way data_scaffold.py's trial link does:
    conversion_gate rule C1 keeps their sources raw `db`."""
    swap = {}
    for row in rows:
        if row["source"].startswith("game/gen_asm/"):
            stem = re.sub(r"[^A-Za-z0-9_]+", "_", Path(row["source"]).with_suffix("").as_posix())
            relobj = ROOT / "build" / "dump_relocs" / "obj" / f"{stem}.obj"
            if relobj.exists():
                swap[build.row_object(row).resolve()] = relobj
    return swap


class Objects:
    """Parsed link objects, cached; lower-case basename -> path for map lookups."""
    def __init__(self, paths):
        self.paths = list(paths)
        self.by_base = {p.name.lower(): p for p in self.paths}
        self.cache, self.index = {}, {}

    def get(self, p):
        """(sections, symbols, raw bytes) of an object; None when it is missing."""
        p = Path(p)
        if p not in self.cache:
            try:
                data = p.read_bytes()
                self.cache[p] = parse_coff(data) + (data,)
            except FileNotFoundError:
                self.cache[p] = None
        return self.cache[p]

    def defined(self, o):
        """{name: Sym} defined in object o, and {section: sorted symbol offsets}."""
        key = id(o)
        if key not in self.index:
            secs, syms, _ = o
            names, vals = {}, collections.defaultdict(set)
            for y in syms.values():
                if 0 < y.sec <= len(secs):
                    names.setdefault(y.name, y)
                    vals[y.sec].add(y.value)
            self.index[key] = (names, {k: sorted(v) for k, v in vals.items()})
        return self.index[key]

    def lookup(self, objbase, name):
        """(object, Sym) for `name` defined by the object a map line names."""
        p = self.by_base.get(objbase.lower())
        o = self.get(p) if p else None
        y = self.defined(o)[0].get(name) if o else None
        return (o, y) if y else None


def analyze(rows, objs):
    """Units: one per object section holding >= 1 matched row."""
    units, keyed = [], {}
    stat = collections.Counter()
    for r in rows:
        rva, size = int(r["target_rva"], 16), int(r.get("target_size") or 0)
        p = row_obj(r)
        sym = (re.search(r"(?:^|;)object-symbol=([^;]+)", r.get("notes", "")) or [None, r["name"]])[1]
        rec = {"name": r["name"], "sym": sym, "rva": rva, "size": size, "kind": row_kind(r), "source": r["source"]}
        o = objs.get(p)
        y = None
        if o is not None:
            secs, syms, _ = o
            y = next((s for s in syms.values() if s.name == sym and s.sec > 0 and s.cls in (2, 3, 6)), None)
        if y is None:
            stat["no object" if o is None else "symbol not in object"] += 1
            units.append({"obj": str(p), "sec": 0, "rows": [dict(rec, off=0)], "why": "no object" if o is None
                          else "symbol not in object", "starts": [rva], "head": None, "size": 0})
            continue
        s = secs[y.sec - 1]
        key = (str(p), y.sec)
        u = keyed.get(key)
        if u is None:
            u = keyed[key] = {"obj": str(p), "sec": y.sec, "secname": s.name, "size": s.size,
                              "comdat": bool(s.flags & COMDAT), "flags": s.flags, "rows": [], "starts": set()}
            units.append(u)
        u["rows"].append(dict(rec, off=y.value))
        u["starts"].add(rva - y.value)
    for u in keyed.values():
        secs, syms, _ = objs.get(u["obj"])
        heads = [y for y in syms.values() if y.sec == u["sec"] and y.cls in (2, 3) and y.value == 0
                 and y.name != u["secname"]]
        u["head"] = heads[0].name if heads else None
        u["head_cls"] = heads[0].cls if heads else None
        u["starts"] = sorted(u["starts"])
    for k, u in enumerate(units):
        u["id"] = k
    return units, stat


# ---------------------------------------------------------------- plan
def plan_order(units, quarantine, text0, textsz):
    """(placed units in retail order, Counter reasons, Counter bytes). Sets u['why']."""
    reasons, rbytes, cand = collections.Counter(), collections.Counter(), []

    def refuse(u, why):
        u["why"] = why
        reasons[why] += 1
        rbytes[why] += sum(r["size"] for r in u["rows"])
    for u in units:
        u.pop("placed", None)
        if u.get("sec", 0) == 0:
            refuse(u, u["why"])
            continue
        u["why"] = None
        if not u["secname"].startswith(".text"):
            refuse(u, "not code (%s)" % u["secname"])
        elif len(u["starts"]) == 1 and region(u["starts"][0]) != group_of(u["secname"]):
            refuse(u, "section group mismatch: compiled %s, retail %s" % (u["secname"], region(u["starts"][0])))
        elif not u["comdat"]:
            refuse(u, "not COMDAT")
        elif u["head"] is None:
            refuse(u, "no head symbol")
        elif u["head_cls"] != EXTERNAL:
            refuse(u, "static COMDAT")
        elif len(u["starts"]) != 1:
            refuse(u, "rows disagree on section start")
        elif not text0 <= u["starts"][0] < text0 + textsz:
            refuse(u, "start outside .text")
        elif u["starts"][0] % align_of(u["flags"]):
            refuse(u, "retail start violates section alignment")
        elif u["head"] in quarantine:
            refuse(u, "quarantined: linked footprint != retail extent")
        else:
            cand.append(u)
    cand.sort(key=lambda u: (u["starts"][0], u["obj"]))
    placed, seen, end = [], set(), 0
    for u in cand:
        s = u["starts"][0]
        if s < end:
            refuse(u, "overlaps previous unit")
        elif u["head"] in seen:
            refuse(u, "head already ordered (duplicate COMDAT)")
        else:
            seen.add(u["head"])
            u["placed"] = True
            placed.append(u)
            end = s + u["size"]
    return placed, reasons, rbytes


def filler_chunks(placed, cuts, text0, textsz):
    """[(start, end)] of every .text byte no placed unit covers, split at `cuts`."""
    cuts = sorted(set(cuts) | {s for s, _ in REGIONS})
    chunks, cur = [], text0
    for s, e in [(u["starts"][0], u["starts"][0] + u["size"]) for u in placed] + [(text0 + textsz,) * 2]:
        if s > cur:
            i = bisect.bisect_right(cuts, cur)
            pts = [cur] + cuts[i:bisect.bisect_left(cuts, s)] + [s]
            chunks += [(a, b) for a, b in zip(pts, pts[1:]) if b > a]
        cur = max(cur, e)
    return chunks


def fill_name(a):
    return "_fill_%08X" % a


def drift_culprits(items, linked):
    """Order items [(retail start, name, kind)] whose linked distance to the next
    item differs from retail's: the unit that grew or shrank is quarantined (a
    filler 'growing' means the next unit's alignment padded it)."""
    items = sorted(items)
    bad, missing = set(), 0
    for (r0, n0, k0), (r1, n1, k1) in zip(items, items[1:]):
        if n0 not in linked or n1 not in linked:
            missing += 1
            continue
        if linked[n1] - linked[n0] != r1 - r0:
            bad.add(n0 if k0 == "unit" else n1 if k1 == "unit" else n0)
    return sorted(b for b in bad if not b.startswith("_fill_")), missing


# ---------------------------------------------------------------- link inputs
def undefined_imports(objs):
    names = set()
    for p in objs.paths:
        o = objs.get(p)
        if o:
            names |= {y.name for y in o[1].values() if y.sec == 0 and y.cls == EXTERNAL and y.name.startswith("__imp_")}
    return names


def import_def_entries(imp_names, retail_imports):
    """{dll: [def entry]} for every referenced __imp_ name retail imports; and the
    names retail does not import (left to stubs)."""
    by_dll, missing = collections.defaultdict(set), []
    for n in sorted(imp_names):
        rest = n[len("__imp_"):]
        if rest.startswith("?"):
            base, entry = rest, rest
        elif rest.startswith("_"):
            entry = rest[1:]
            base = re.sub(r"@\d+$", "", entry)
        else:
            missing.append(n)
            continue
        dlls = retail_imports.get(base)
        if not dlls:
            missing.append(n)
            continue
        by_dll[sorted(dlls)[0]].add(entry)
    return {d: sorted(e) for d, e in by_dll.items()}, missing


def import_name(name):
    """An imported function's name without the stdcall @N lib.exe /DEF keeps on it
    (its import objects use IMPORT_NAME_NOPREFIX; retail's are undecorated)."""
    return re.sub(r"@\d+$", "", name)


def import_key(dll, name, ordinal=None):
    """An import's identity: (dll, name) or (dll, '#ordinal'); the dll lower case,
    the name without lib.exe's stdcall @N."""
    if isinstance(name, bytes):
        name = name.decode("latin-1")
    return dll.lower(), import_name(name) if name else "#%d" % (ordinal or 0)


def read_through(code, fo):
    """True when the dword at fo is the memory operand of an instruction that only
    reads the slot: call/jmp/push [m32] (FF /2 /4 /6), mov r32,[m32] (8B, mod 00
    rm 101) or mov eax,[m32] (A1). Such a reference cannot observe which of two
    slots holding the same import it reads; any other use (an address taken, a
    store, a data pointer) can."""
    if fo >= 2 and code[fo - 1] & 0xC7 == 0x05:
        op, reg = code[fo - 2], (code[fo - 1] >> 3) & 7
        if op == 0x8B or (op == 0xFF and reg in (2, 4, 6)):
            return True
    return fo >= 1 and code[fo - 1] == 0xA1 and not (fo >= 2 and code[fo - 2] in (0x8B, 0x8D, 0xFF, 0x89, 0xC7))


def make_import_libs(entries, outdir):
    root = build.vc71_root()
    libs = []
    for dll, names in sorted(entries.items()):
        stem = re.sub(r"\W", "_", dll.rsplit(".", 1)[0].lower())
        d = outdir / f"imp_{stem}.def"
        d.write_text(f"LIBRARY {dll}\nEXPORTS\n" + "".join(f"  {n}\n" for n in names), encoding="latin-1")
        lib = outdir / f"imp_{stem}.lib"
        res = subprocess.run([str(root / "Vc7/bin/lib.exe"), "/NOLOGO", "/MACHINE:X86", f"/DEF:{d}", f"/OUT:{lib}"],
                             capture_output=True, text=True, errors="replace", env=build.compiler_environment(root))
        if res.returncode or not lib.exists():
            raise SystemExit(f"link_cycle: lib.exe failed for {dll}:\n{res.stdout}{res.stderr}")
        libs.append(lib)
    return libs


def zz_objects(objs, placed, ordered_names, zzdir):
    """Private copies with every unplaced code section renamed .text$zz, so unplaced
    code lands after retail's last group instead of inside it. Every link input
    is a short name in zzdir (o00000.obj: such a copy, else a hard link to the
    object): link.exe 7.1 cannot open a path past MAX_PATH, and object names run
    to 150 characters. zzdir/names.json maps the names back (read_map)."""
    zzdir.mkdir(parents=True, exist_ok=True)
    placed_secs = {(u["obj"], u["sec"]) for u in placed}
    out, renamed, names, modified = [], 0, {}, []
    for k, p in enumerate(objs.paths):
        secs, syms, raw = objs.get(p)
        d = bytearray(raw)
        opt = struct.unpack_from("<H", d, 16)[0]
        heads = {}
        for y in sorted(syms.values(), key=lambda y: y.i):
            if y.sec > 0 and y.cls in (2, 3) and y.name != secs[y.sec - 1].name and y.sec not in heads:
                heads[y.sec] = y.name if y.cls == EXTERNAL else None
        hit = False
        for s in secs:
            if not s.name.startswith(".text") or (str(p), s.idx) in placed_secs:
                continue
            if s.flags & COMDAT and heads.get(s.idx) in ordered_names:
                continue
            struct.pack_into("8s", d, 20 + opt + 40 * (s.idx - 1), b".text$zz")
            hit = True
            renamed += 1
        q = zzdir / ("o%05d.obj" % k)
        names[q.name] = Path(p).name.lower()
        if hit:
            modified.append(q.name)
            if not q.exists() or q.read_bytes() != d:
                q.unlink(missing_ok=True)          # never write through a hard link to the object
                q.write_bytes(bytes(d))
        elif not (q.exists() and os.path.samefile(p, q)):
            q.unlink(missing_ok=True)
            try:
                os.link(p, q)
            except OSError:
                import shutil
                shutil.copyfile(p, q)
        out.append(q)
    (zzdir / "names.json").write_text(json.dumps({"names": names, "modified": modified}))
    return out, renamed


def zz_names(out):
    """({short link name: object basename}, [short names of modified copies])."""
    try:
        d = json.loads((out / "zzobj" / "names.json").read_text())
        return d["names"], d["modified"]
    except (OSError, ValueError, KeyError):
        return {}, []


# link.exe records the output file name inside the image, so the shifted link's name must be
# exactly as long as the base link's, or .rdata differs by the length difference and every node
# fails the shifted-layout check.
BASE_TAG = "base"
SHIFT_TAG = "shft"
assert len(SHIFT_TAG) == len(BASE_TAG)


def link(tag, inputs, order, entry, base, outdir):
    rsp = outdir / f"{tag}.rsp"
    rsp.write_text("\n".join(f'"{p}"' for p in inputs) + "\n", encoding="latin-1")
    root = build.vc71_root()
    cmd = [str(root / "Vc7/bin/link.exe"), "/NOLOGO", "/FORCE", "/NODEFAULTLIB", "/INCREMENTAL:NO", "/MACHINE:X86",
           "/SUBSYSTEM:WINDOWS", "/FIXED", f"/BASE:0x{base:X}", "/OPT:NOREF", "/OPT:NOICF",
           "/ENTRY:" + order_name(entry), f"/ORDER:@{order}", f"/MAP:{outdir / (tag + '.map')}",
           f"/OUT:{outdir / (tag + '.exe')}", f"@{rsp}"]
    if sys.platform != "win32":
        cmd.insert(0, "wine")
    for p in (outdir / (tag + ".map"), outdir / (tag + ".exe")):
        p.unlink(missing_ok=True)
    t = time.time()
    res = subprocess.run(cmd, capture_output=True, text=True, errors="replace",
                         env=build.compiler_environment(root), cwd=outdir)
    log = res.stdout + res.stderr
    (outdir / (tag + ".log")).write_text(log, encoding="utf-8")
    print(f"link_cycle: link {tag} base 0x{base:X} exit {res.returncode} {time.time() - t:.0f}s", flush=True)
    return log, res.returncode, time.time() - t


UNRES = re.compile(r'unresolved external symbol (?:"[^"]*" \((\S+)\)|(\S+))')
DUP = re.compile(r'warning LNK4006: (?:"[^"]*" \((\S+)\)|(\S+)) already defined')


def diagnostics(log):
    return {"codes": dict(collections.Counter(re.findall(r"(?:error|warning) (LNK\d+)", log))),
            "unresolved": sorted({a or b for a, b in UNRES.findall(log)}),
            "duplicates": sorted({a or b for a, b in DUP.findall(log)})}


# ---------------------------------------------------------------- map
MAPLINE = re.compile(r"^\s*([0-9a-f]{4}):([0-9a-f]{8})\s+(\S+)\s+([0-9a-f]{8})\s+(?:f\s+)?(?:i\s+)?(\S+)\s*$")


def read_map(text, base, names=None):
    """(publics {name: rva}, statics {(name, objbase): rva}, sorted [(rva, name, objbase)],
    {public: objbase})."""
    pub, stat, allsyms, static, pubobj = {}, {}, [], False, {}
    for line in text.splitlines():
        if "Static symbols" in line:
            static = True
        m = MAPLINE.match(line)
        if not m or m.group(1) == "0000":
            continue
        va = int(m.group(4), 16) - base
        ob = m.group(5).split(":")[-1].lower()
        ob = (names or {}).get(ob, ob)
        if static:
            stat.setdefault((m.group(3), ob), va)
        else:
            pub.setdefault(m.group(3), va)
            pubobj.setdefault(m.group(3), ob)
        allsyms.append((va, m.group(3), ob))
    allsyms.sort()
    return pub, stat, allsyms, pubobj


# ---------------------------------------------------------------- measure helpers
def u32(m, a):
    return struct.unpack_from("<I", m, a)[0]


def nonreloc_diffs(got, want, masked):
    return sum(1 for k in range(len(want)) if k not in masked and (k >= len(got) or got[k] != want[k]))


def pin_matches(pin, rva, base=BASE):
    """symbols.csv pins data both as RVAs and as VAs (138 VA, 30 RVA on
    2026-10-05). A retail datum's RVA (>= .rdata) and any datum's VA lie in
    disjoint bands, so either spelling of the same address is accepted."""
    return pin == rva or pin == rva + base


def unique_bytes(spans):
    """Bytes covered by the union of [start, end) spans."""
    total, cur = 0, -1
    for s, e in sorted(spans):
        if e > cur:
            total += e - max(s, cur)
            cur = e
    return total


def greatest_closure(ok, edges, bad_targets=("fill", "stub"), unknown_closes=False):
    """Nodes that are ok and reach only ok nodes (cycles optimistic). An edge to a
    node kind in `bad_targets` (fillers, stubs), or to a node `ok` does not hold
    (unless `unknown_closes`, the pilot's rule), closes nothing: it is not a leaf."""
    closed = {n for n in ok if ok[n]}
    for n in list(closed):
        if any(t[0] in bad_targets or (t not in ok and not unknown_closes) for t in edges.get(n, ())):
            closed.discard(n)
    rev = collections.defaultdict(set)
    for n, ts in edges.items():
        for t in ts:
            rev[t].add(n)
    work = [n for n in ok if n not in closed]
    while work:
        t = work.pop()
        for n in rev.get(t, ()):
            if n in closed:
                closed.discard(n)
                work.append(n)
    return closed


try:
    import capstone
    _CS = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    _CSD = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    _CSD.detail = True
except ImportError:  # pragma: no cover
    _CS = _CSD = None


def _norm(ins):
    return ins.mnemonic + " " + re.sub(r"0x[0-9a-f]{6,8}", "ADDR", ins.op_str)


def funclet_equal(I, la, R, ra, lbase, rbase, translate=None):
    """Funclet bodies equal up to the first ret/jmp, address operands masked; a
    direct call/jmp target must translate to retail's when it is mapped."""
    a = list(_CS.disasm(bytes(I[la:la + 64]), la + lbase))
    b = list(_CS.disasm(bytes(R[ra:ra + 64]), ra + rbase))
    for x, y in zip(a, b):
        if _norm(x) != _norm(y):
            return False
        if translate and x.mnemonic in ("call", "jmp") and x.op_str.startswith("0x") and y.op_str.startswith("0x"):
            t = translate(int(x.op_str, 16) - lbase)
            if t is not None and t != int(y.op_str, 16) - rbase:
                return False
        if x.mnemonic in ("jmp", "ret"):
            return True
    return len(a) == len(b)


def funcinfo(m, a, base):
    magic, maxst, pu, ntry, ptry, _ = struct.unpack_from("<IiIIII", m, a)
    un = [struct.unpack_from("<iI", m, pu - base + 8 * i) for i in range(max(0, min(maxst, 400)))] if pu else []
    tr = []
    for i in range(min(ntry, 50)):
        lo, hi, ch, nc, ph = struct.unpack_from("<iiiiI", m, ptry - base + 20 * i)
        tr.append((lo, hi, ch, nc, [struct.unpack_from("<IIiI", m, ph - base + 16 * j) for j in range(min(nc, 20))]))
    return magic, maxst, ntry, un, tr


def eh_verdict(I, lt, R, rt, lbase, rbase, translate=None):
    """None when the linked __ehhandler$ thunk at lt and retail's at rt (mov eax,
    FuncInfo; jmp handler) carry equal EH data; else the first difference."""
    if I[lt] != 0xB8 or R[rt] != 0xB8 or I[lt + 5] != 0xE9 or R[rt + 5] != 0xE9:
        return "thunk shape differs"
    try:
        a = funcinfo(I, u32(I, lt + 1) - lbase, lbase)
        b = funcinfo(R, u32(R, rt + 1) - rbase, rbase)
    except (struct.error, IndexError):
        return "FuncInfo unparsable"
    if a[:3] != b[:3]:
        return "FuncInfo header differs"
    if [x[0] for x in a[3]] != [x[0] for x in b[3]]:
        return "unwind map differs"
    if any((x[1] == 0) != (y[1] == 0) for x, y in zip(a[3], b[3])):
        return "unwind action presence differs"
    if not all(funclet_equal(I, x[1] - lbase, R, y[1] - rbase, lbase, rbase, translate)
               for x, y in zip(a[3], b[3]) if x[1] and y[1]):
        return "unwind funclet differs"
    if [t[:4] for t in a[4]] != [t[:4] for t in b[4]]:
        return "try map differs"
    for t, v in zip(a[4], b[4]):
        if [(h[0], h[2]) for h in t[4]] != [(h[0], h[2]) for h in v[4]]:
            return "catch map differs"
        if not all(funclet_equal(I, h[3] - lbase, R, g[3] - rbase, lbase, rbase, translate)
                   for h, g in zip(t[4], v[4])):
            return "catch funclet differs"
    return None


def hardcoded_operands(code, va, masked, lo, hi, starts=frozenset()):
    """Offsets of 32-bit displacement/immediate operands in `code` (at `va`)
    holding an absolute address in [lo, hi) or in `starts` that no relocation
    covers: they cannot follow a rebase. Relative branch targets are not
    operands here. The caller passes retail's data VAs and row starts: a
    source hard-codes retail's addresses, and a whole-image range would also
    take ASCII tags (push 0x696E74, "int") for addresses."""
    if _CSD is None:
        return []
    out = []
    for ins in _CSD.disasm(bytes(code), va):
        at = ins.address - va
        for off, size in ((ins.disp_offset, ins.disp_size), (ins.imm_offset, ins.imm_size)):
            if size != 4 or not off or ins.mnemonic == "call" or ins.mnemonic.startswith("j"):
                continue
            k = at + off
            v = u32(code, k)
            if (lo <= v < hi or v in starts) and not any(j in masked for j in range(k, k + 4)):
                out.append(k)
    return out


# ---------------------------------------------------------------- measure
class Measure:
    def __init__(self, units, chunks, mapped, I, R, isecs, rimports, limports, pins, objs, ledger_starts,
                 lbase=BASE, rbase=BASE):
        self.units, self.I, self.R, self.isecs = units, I, R, isecs
        self.pins, self.objs, self.ledger_starts = pins, objs, ledger_starts
        self.lbase, self.rbase = lbase, rbase
        self.rimports, self.limports = rimports, limports
        self.pub, self.stat, self.allsyms, self.pubobj = mapped
        self.avas = [s[0] for s in self.allsyms]
        self.ltext = isecs.get(".text", (0, 0))
        items = []
        for u in units:
            if u.get("head") is None:
                continue
            ob = Path(u["obj"]).name.lower()
            la = self.pub.get(u["head"]) if u["head_cls"] == EXTERNAL else self.stat.get((u["head"], ob))
            u.pop("not_selected", None)
            if la is not None and u["head_cls"] == EXTERNAL and self.pubobj.get(u["head"]) != ob:
                # /FORCE kept another object's copy of this name: the unit's own bytes are not in the image
                u["not_selected"] = self.pubobj.get(u["head"])
                la = None
            u["linked"] = la
            if la is not None and len(u["starts"]) == 1:
                items.append((la, la + u["size"], u["starts"][0], ("unit", u["id"])))
        for a, b in chunks:
            la = self.pub.get(fill_name(a))
            if la is not None:
                items.append((la, la + b - a, a, ("fill", a)))
        items.sort()
        self.items, self.istarts = items, [t[0] for t in items]
        self.thunk_rows = {r["rva"] for u in units for r in u["rows"] if r["name"].startswith("?j_")}
        self._init_state()

    def _init_state(self):
        self.fwd, self.back = collections.defaultdict(set), collections.defaultdict(set)
        self.twins, self.eh = {}, collections.Counter()
        self.resolved, self.dnodes, self.twin_edges, self.twin_rels, self.twin_body = {}, {}, {}, {}, {}
        self.import_equiv = 0       # read-through references kept by the (dll, name) rule, not 1:1
        self.ilt_routes = collections.Counter()

    def T(self, a):
        i = bisect.bisect_right(self.istarts, a) - 1
        if i >= 0 and self.items[i][0] <= a < self.items[i][1]:
            return self.items[i][2] + a - self.items[i][0], self.items[i][3]
        return None, None

    def translate(self, a):
        return self.T(a)[0]

    def sym_at(self, a):
        i = bisect.bisect_right(self.avas, a) - 1
        if i < 0:
            return None
        va, name, ob = self.allsyms[i]
        j = i + 1
        while j < len(self.allsyms) and self.allsyms[j][0] == va:
            j += 1
        return va, name, ob, self.allsyms[j][0] if j < len(self.allsyms) else va + 1

    def syms_at(self, a):
        """Every map symbol at exactly a: [(name, objbase)]."""
        i = bisect.bisect_left(self.avas, a)
        out = []
        while i < len(self.allsyms) and self.allsyms[i][0] == a:
            out.append(self.allsyms[i][1:])
            i += 1
        return out

    def lsec(self, a):
        if hasattr(self.isecs, "name_at"):
            return self.isecs.name_at(a)
        return next((n for n, (s, z) in self.isecs.items() if s <= a < s + max(z, 1)), "outside")

    def relocs(self, L, rva, size, o, secno, off, owner):
        """Check every relocation of [off, off+size) of section `secno` of object o
        linked at L against retail at rva. Returns (failures, edges, masked
        offsets, data references [(lt, rt, target name, Sym, object, addend,
        access)], relocations [(offset, type, absolute?)] for the shifted check)."""
        I, R = self.I, self.R
        secs, syms, raw = o
        sec = secs[secno - 1]
        got, want = I[L:L + size], R[rva:rva + size]
        fails, edges, masked, data, rels = [], set(), set(), [], []
        for va, si, ty in sec.relocs:
            if not off <= va < off + size:
                continue
            fo = va - off
            masked.update(range(fo, min(fo + 4, size)))
            y = syms.get(si)
            tn = y.name if y else "?"
            if ty not in (DIR32, REL32):
                fails.append(f"rtype:{ty}")
                continue
            if fo + 4 > size:
                fails.append(f"straddle:{tn}")
                continue
            rels.append((fo, ty, tn in ABSOLUTE))
            lv, rv = u32(got, fo), u32(want, fo)
            if tn in ABSOLUTE:
                if ty != DIR32 or lv != rv:
                    fails.append(f"abs:{tn}")
                continue
            if ty == REL32:
                lt, rt = (L + fo + 4 + lv) & 0xFFFFFFFF, (rva + fo + 4 + rv) & 0xFFFFFFFF
            else:
                lt, rt = (lv - self.lbase) & 0xFFFFFFFF, (rv - self.rbase) & 0xFFFFFFFF
            if self.ltext[0] <= lt < self.ltext[0] + self.ltext[1]:
                f, e = self.code_ref(lt, rt, tn, owner)
                if f:
                    fails.append(f)
                elif e:
                    edges.add(e)
            else:
                addend = u32(raw, sec.ptr + va) if sec.ptr else 0
                access = "read" if ty == DIR32 and read_through(got, fo) and read_through(want, fo) else "addr"
                data.append((lt, rt, tn, y, o, addend, access))
        nd = nonreloc_diffs(got, want, masked)
        if nd:
            fails.append(f"bytes:{nd}")
        return fails, edges, masked, data, rels

    def ilt_body(self, rt):
        """The body a retail ILT thunk (or `?j_` row) at rt jumps to; rt itself otherwise."""
        for _ in range(3):
            if (ILT[0] <= rt < ILT[1] or rt in self.thunk_rows) and self.R[rt] == 0xE9:
                rt = (rt + 5 + struct.unpack_from("<i", self.R, rt + 1)[0]) & 0xFFFFFFFF
            else:
                break
        return rt

    def code_ref(self, lt, rt, tn, owner):
        tr, item = self.T(lt)
        if tr is not None and tr == rt:
            return None, item
        if tr is not None and self.ilt_body(rt) == tr:
            self.ilt_routes["call"] += 1      # retail bound at the thunk, this link at its body
            return None, item
        s = self.sym_at(lt)
        if s and s[1].startswith("__ehhandler$"):
            if s[1][len("__ehhandler$"):] != owner:
                self.eh["foreign thunk"] += 1
                return f"eh-foreign:{tn}", None
            v = eh_verdict(self.I, s[0], self.R, rt - (lt - s[0]), self.lbase, self.rbase, self.translate)
            self.eh[v or "verified"] += 1
            return (f"eh:{v}", None) if v else (None, ("eh", s[0]))
        if s and s[0] == lt and rt in self.ledger_starts:
            self.twins.setdefault((lt, rt), None)
            return None, ("twin", lt, rt)          # judged in settle_twins; a rejected twin fails the row
        if tr is None:
            return f"code-unmapped:{tn}", None
        return f"code-wrong:{tn}", None

    def object_name(self, o):
        """Lower-case basename of a parsed object (the map's Lib:Object spelling)."""
        names = getattr(self, "_onames", None)
        if names is None or id(o) not in names:
            names = self._onames = {id(v): Path(p).name.lower() for p, v in self.objs.cache.items() if v}
        return names.get(id(o))

    def datum(self, lt, tn, y, o, addend):
        """The datum a data reference reaches, from the relocation's own target:
        (linked start of the datum, its size, offset of lt in it, defining object,
        section, section offset of the datum, linked address of the named symbol).
        A public the referencing object defines counts as its own only when the
        map says the link selected that object's copy.

        A DIR32 addend is a signed displacement (MSVC folds `table[i - 1]` into
        [reg*4 + table-4], stored addend -4); read unsigned it put lt about 4 GB
        into the section. A displacement before the named symbol stays unresolved
        (data-unmapped): an indexed read through it reaches the symbol's own datum
        and a direct one the bytes before it, and judging either alone would credit
        the other unchecked. Judging both is a follow-up; until then nothing is
        credited there. (Displacements past the symbol's datum are judged by the
        datum holding lt, as before.)"""
        if addend & 0x80000000:
            addend -= 1 << 32
        local = y is not None and y.sec > 0
        if local and y.cls == EXTERNAL and tn in self.pubobj and self.object_name(o) is not None:
            local = self.pubobj[tn] == self.object_name(o)
        if local:                                    # defined in the referencing object
            sec, P, S = o[0][y.sec - 1], y.value + addend, lt - addend
            base = y.value
        else:                                        # defined elsewhere: the map names its object
            S, ob = self.pub.get(tn), self.pubobj.get(tn)
            found = self.objs.lookup(ob, tn) if ob else None
            if S is not None and not found:
                # an /alternatename alias: the map gives it the address and object of the
                # name it stands for; take that definition's datum
                i = bisect.bisect_left(self.avas, S)
                while not found and i < len(self.allsyms) and self.allsyms[i][0] == S:
                    found = self.objs.lookup(self.allsyms[i][2], self.allsyms[i][1])
                    i += 1
            if S is not None and not found and self.communal(tn):
                # an uninitialized global: a COMMON record sizes it (the linker takes the
                # largest), and the map names an object that does not define it
                return None if lt < S else (S, self.communal(tn), lt - S, o, None, 0, S)
            if S is None or not found:
                return None
            o, ys = found
            sec, P, base = o[0][ys.sec - 1], ys.value + (lt - S), ys.value
        if P < base:
            return None
        vals = self.objs.defined(o)[1].get(sec.idx, [])
        q = min(P, sec.size - 1)
        i = bisect.bisect_right(vals, q) - 1
        v0 = vals[i] if i >= 0 else 0
        v1 = vals[i + 1] if i + 1 < len(vals) else sec.size
        return lt - (P - v0), v1 - v0, P - v0, o, sec, v0, S

    def communal(self, name):
        """Size of a COMMON global across every parsed link object (0: none)."""
        if getattr(self, "commons", None) is None:
            self.commons = {}
            for o in list(self.objs.cache.values()):
                for z in (o[1].values() if o else ()):
                    if z.sec == 0 and z.cls == EXTERNAL and z.value > 0:
                        self.commons[z.name] = max(self.commons.get(z.name, 0), z.value)
        return self.commons.get(name, 0)

    # ---- data: every datum reachable through data pointers is a node of the closure
    def resolve(self, ref):
        """What a data reference reaches: ('stub' | 'outside' | 'import' | 'unmapped',)
        or ('datum', key, linked address of the named symbol). Memoised; a new
        datum is scanned for its own pointers."""
        lt, rt, tn, y, o, addend = ref[:6]
        mk = (lt, rt, tn, id(o), addend)
        r = self.resolved.get(mk)
        if r is not None:
            return r
        sec = self.lsec(lt)
        if sec == ".stubd":
            r = ("stub",)
        elif sec == "outside":
            r = ("outside",)
        elif lt in self.limports:
            r = ("import",)
        else:
            d = self.datum(lt, tn, y, o, addend)
            if d is None:
                r = ("unmapped",)
            else:
                start, size, k, do, dsec, v0, S = d
                key = (start, rt - k, size)
                r = ("datum", key, S)
                if key not in self.dnodes:
                    self.dnodes[key] = self.scan_datum(key, dsec, v0, tn, do)
        self.resolved[mk] = r
        return r

    def scan_datum(self, key, sec, value, name, o):
        """A datum node: its bytes against retail's (relocated words masked), code
        pointers translated through the unit or filler holding them, data pointers
        kept as references (judged once every reference is known)."""
        start, rstart, size = key
        node = {"name": name, "fails": [], "edges": set(), "refs": [], "rels": [], "masked": set()}
        if size <= 0 or rstart < 0 or rstart + size > len(self.R) or start < 0 or start + size > len(self.I):
            node["fails"].append(f"data-extent:{name}")
            return node
        got, want = self.I[start:start + size], self.R[rstart:rstart + size]
        masked = node["masked"]
        syms = o[1] if o else {}
        raw = o[2] if o else b""
        for va, si, ty in (sec.relocs if sec is not None else ()):
            fo = va - value
            if not 0 <= fo < size:
                continue
            masked.update(range(fo, min(fo + 4, size)))
            y = syms.get(si)
            tn = y.name if y else "?"
            if ty != DIR32 or fo + 4 > size:
                node["fails"].append(f"data-rtype:{name}")
                continue
            node["rels"].append((fo, ty, tn in ABSOLUTE))
            lt = (u32(got, fo) - self.lbase) & 0xFFFFFFFF
            rt = (u32(want, fo) - self.rbase) & 0xFFFFFFFF
            if self.ltext[0] <= lt < self.ltext[0] + self.ltext[1]:
                tr, item = self.T(lt)
                if tr is not None and tr != rt and self.ilt_body(rt) == tr:
                    self.ilt_routes["pointer"] += 1     # retail's slot holds the ILT thunk
                    node["edges"].add(item)
                elif tr != rt:
                    node["fails"].append(f"data-codeptr:{name}")
                else:
                    node["edges"].add(item)
            else:
                addend = u32(raw, sec.ptr + va) if sec.ptr else 0
                node["refs"].append((lt, rt, tn, y, o, addend, "addr"))
        if nonreloc_diffs(got, want, masked):
            node["fails"].append(f"data-content:{name}")
        return node

    def discover(self, refs):
        """Register refs, and every data pointer reachable from their datums, in the
        1:1 maps."""
        work = list(refs)
        while work:
            ref = work.pop()
            self.fwd[ref[0]].add(ref[1])
            self.back[ref[1]].add(ref[0])
            r = self.resolve(ref)
            if r[0] == "datum":
                node = self.dnodes[r[1]]
                if not node.get("seen"):
                    node["seen"] = True
                    work.extend(node["refs"])

    def one_to_one(self, lt, rt, tn):
        out = []
        if len(self.fwd[lt]) != 1:
            out.append(f"data-fwd:{tn}")
        if len(self.back[rt]) != 1:
            out.append(f"data-back:{tn}")
        return out

    def ref_check(self, ref):
        """(failures, edges, pinned?) of one data reference: the 1:1 map, what it
        reaches, the pin. Imports match on (dll, name or ordinal). A slot read
        through (call/jmp/push/mov [slot] on both sides) cannot observe which of
        retail's duplicate slots of one import it reads, so there one import is one
        datum; a reference that can observe the slot (address taken, data pointer)
        keeps the 1:1 rule."""
        lt, rt, tn = ref[:3]
        access = ref[6] if len(ref) > 6 else "addr"
        kind = self.resolve(ref)
        fails = []
        if kind[0] == "import":
            want = self.rimports.get(rt)
            same = want is not None and want == self.limports[lt]
            if not same:
                fails.append(f"import-mismatch:{tn}")
            strict = self.one_to_one(lt, rt, tn)
            if access != "read" or not same:
                fails += strict
            elif strict:
                self.import_equiv += 1
            return fails, set(), True
        fails += self.one_to_one(lt, rt, tn)
        if kind[0] != "datum":
            what = {"stub": "data-stub", "outside": "data-outside-image", "unmapped": "data-unmapped"}[kind[0]]
            return fails + [f"{what}:{tn}"], set(), False
        S = kind[2]
        pinned = tn in self.pins
        if pinned and not pin_matches(self.pins[tn], rt - (lt - S), self.rbase):
            fails.append(f"data-pin:{tn}")
        return fails, {("datum", kind[1])}, pinned

    def judge_datums(self):
        """Each datum's own failures: content, code pointers and every data pointer
        it holds (1:1, reaching a real datum, its pin; failures read data-ptr-*).
        Its edges: code units and the datums it points to, so the closure runs
        through data."""
        for node in self.dnodes.values():
            if node.get("judged"):
                continue
            node["judged"] = True
            for ref in node["refs"]:
                f, e, _ = self.ref_check(ref)
                node["fails"] += ["data-ptr-" + x.split("data-", 1)[-1] for x in f]
                node["edges"] |= e

    def ref_with_datum(self, ref):
        """ref_check plus the reached datum's own failures: a row is self-strict only
        when the data it touches directly is right, pointers included."""
        fails, edges, pinned = self.ref_check(ref)
        kind = self.resolve(ref)
        if kind[0] == "datum":
            fails = fails + self.dnodes[kind[1]]["fails"]
        return fails, edges, pinned

    def data_ref(self, lt, rt, tn, y, o, addend, access="addr"):
        """One reference judged on its own (tests): discover, judge, check."""
        ref = (lt, rt, tn, y, o, addend, access)
        self.discover([ref])
        self.judge_datums()
        return self.ref_with_datum(ref)

    def run(self):
        """Per ledger row: dict with failures, edges, placement."""
        out = []
        self.pending = []
        for u in self.units:
            la = u.get("linked")
            o = self.objs.get(u["obj"]) if la is not None else None
            for r in u["rows"]:
                rec = {"row": r, "unit": u, "linked": None, "placed": 0, "fails": [], "edges": set(),
                       "unpinned": 0, "masked": set(), "rels": [], "measured": False}
                out.append(rec)
                if u.get("not_selected") is not None:
                    rec["fails"].append(f"not-selected:{u['not_selected']}")
                if la is None or not o:
                    continue
                L = la + r["off"]
                rec["linked"], rec["placed"], rec["measured"] = L, int(L == r["rva"]), True
                f, e, m, data, rels = self.relocs(L, r["rva"], r["size"], o, u["sec"], r["off"], r["sym"])
                rec["fails"], rec["edges"], rec["masked"], rec["rels"] = f, e, m, rels
                for ref in data:
                    self.pending.append((rec, ref))
        self.collect_twins()
        self.discover([ref for _, ref in self.pending] + [ref for b in self.twin_body.values() for ref in b[2]])
        self.judge_datums()
        for rec, ref in self.pending:
            f, e, pinned = self.ref_with_datum(ref)
            rec["fails"] += f
            rec["edges"] |= e
            rec["unpinned"] += 0 if pinned else 1
        self.settle_twins()
        for rec in out:
            for e in list(rec["edges"]):
                if e[0] == "twin" and not self.twins.get((e[1], e[2]), (False,))[0]:
                    rec["fails"].append(f"twin-rejected:{self.twins.get((e[1], e[2]), (0, 'unjudged'))[1]}")
        return out

    def selected_copy(self, lt, size):
        """(object, Sym, None) of the definition the link put at lt, from the /MAP:
        the object that contributed the function there, whose extent in its section
        (to the next symbol or the section end; trailing int3/nop padding optional)
        holds retail's row size. Else (None, None, why)."""
        why = "no map definition"
        for name, ob in self.syms_at(lt):
            found = self.objs.lookup(ob, name)
            if not found:
                continue
            o, ys = found
            sec = o[0][ys.sec - 1]
            if not sec.name.startswith(".text"):
                continue
            vals = self.objs.defined(o)[1].get(ys.sec, [])
            i = bisect.bisect_right(vals, ys.value)
            end = vals[i] if i < len(vals) else sec.size
            body = bytes(o[2][sec.ptr + ys.value:sec.ptr + end]) if sec.ptr else b""
            trim = len(body.rstrip(b"\xcc\x90")) if sec.ptr else end - ys.value
            if trim <= size <= end - ys.value:
                return o, ys, None
            why = "extent differs"
        return None, None, why

    def collect_twins(self):
        """Candidate ICF twins: a linked function start reached where retail calls a
        ledger row start. The body judged is the copy the /MAP says the link kept."""
        work = list(self.twins)
        body = self.twin_body
        while work:
            lt, rt = work.pop()
            if (lt, rt) in body:
                continue
            size = self.ledger_starts[rt]
            o, ys, why = self.selected_copy(lt, size)
            if o is None:
                body[(lt, rt)] = ([why], set(), [], [])
                continue
            f, e, _, data, rels = self.relocs(lt, rt, size, o, ys.sec, ys.value, ys.name)
            body[(lt, rt)] = (f, e, data, rels)
            for x in e:
                if x[0] == "twin" and (x[1], x[2]) not in body:
                    self.twins.setdefault((x[1], x[2]), None)
                    work.append((x[1], x[2]))

    def settle_twins(self):
        """Certify twins: equal bytes, every relocation (code, and data with its
        datum's own failures) resolving to retail's target, twins of twins
        included."""
        body, ok, edges = self.twin_body, {}, {}
        for key, (f, e, data, rels) in body.items():
            fails, es = list(f), set(e)
            for ref in data:
                rf, redges, _ = self.ref_with_datum(ref)
                fails += rf
                es |= redges
            ok[key], edges[key] = fails, es
            self.twin_rels[key] = rels
        good = {k for k, v in ok.items() if not v}
        changed = True
        while changed:
            changed = False
            for k in list(good):
                if any(x[0] == "twin" and (x[1], x[2]) not in good for x in edges[k]):
                    good.discard(k)
                    ok[k] = ["calls a rejected twin"]
                    changed = True
        self.twin_edges = edges
        for k in body:
            self.twins[k] = (k in good, (ok[k] or ["certified"])[0].split(":")[0])

    def judge_twins(self):
        """collect_twins, their data, settle_twins in one call (tests)."""
        self.collect_twins()
        self.discover([ref for b in self.twin_body.values() for ref in b[2]])
        self.judge_datums()
        self.settle_twins()


# ---------------------------------------------------------------- cycle
def sha256(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for b in iter(lambda: f.read(1 << 20), b""):
            h.update(b)
    return h.hexdigest()


def git(*args, cwd=None):
    return subprocess.run(["git", *args], capture_output=True, text=True, cwd=cwd or ROOT).stdout.strip()


def tool_digest():
    """This file as run, plus the tree's build and census modules it imports."""
    h = hashlib.sha256()
    h.update(b"link_cycle.py\0" + Path(__file__).read_bytes())
    for n in TOOL_FILES[1:]:
        h.update(n.encode() + b"\0" + (ROOT / "tools" / n).read_bytes())
    return h.hexdigest()


def object_identity(o):
    """A COFF object's content without the compile's time stamp and debug records
    (they hold the build directory): section names, flags, bytes and
    relocations, and the symbol table."""
    secs, syms, raw = o
    h = hashlib.sha256()
    for s in secs:
        if s.name.startswith(".debug$"):
            continue
        h.update(f"{s.name}\0{s.flags:x}\0{s.size}\0".encode("latin-1"))
        h.update(raw[s.ptr:s.ptr + s.size] if s.ptr else b"")
        h.update(repr(s.relocs).encode())
    for k in sorted(syms):
        y = syms[k]
        h.update(f"{y.name}\0{y.value}\0{y.sec}\0{y.cls}\n".encode("latin-1"))
    return h.hexdigest()


def objects_digest(objs, paths):
    """One digest of every link input object's identity, by path under ROOT."""
    h = hashlib.sha256()
    for p in sorted(paths, key=lambda p: Path(p).as_posix()):
        o = objs.get(p)
        h.update(Path(p).relative_to(ROOT).as_posix().encode() + b"\0" + (object_identity(o) if o else "-").encode())
    return h.hexdigest()


def tree_manifest(top):
    """sha256 over (path, size, mtime) of every file under a snapshot, its build/
    and marker excluded. The content is `git archive` of the marker's commits;
    the manifest proves nothing wrote to the tree since (hashing 61k files is
    I/O-bound: 10+ minutes on a scanned Windows host, a stat walk ~10 s)."""
    h = hashlib.sha256()
    top = Path(top)
    files = []
    for d, dirs, names in os.walk(top):
        rel = Path(d).relative_to(top)
        if rel == Path("."):
            dirs[:] = [x for x in dirs if x != "build"]
        for n in names:
            if rel != Path(".") or n != SNAPSHOT_MARK:
                st = os.stat(os.path.join(d, n))
                files.append(f"{(rel / n).as_posix()}\0{st.st_size}\0{st.st_mtime_ns}\n")
    for f in sorted(files):
        h.update(f.encode("utf-8", "surrogateescape"))
    return h.hexdigest()


SNAPSHOT_MARK = "SNAPSHOT.json"


def export_snapshot(rev, parent):
    """An immutable copy of the tree at `rev`: `git archive` of the commit and of
    every submodule at the commit its gitlink pins, extracted to parent/<sha12>.
    The marker records the commit, the submodule commits and the tree
    manifest every run in it re-proves. An existing snapshot is reused only
    when its manifest still holds."""
    import tarfile
    sha = git("rev-parse", "--verify", rev + "^{commit}")
    if not re.fullmatch(r"[0-9a-f]{40}", sha):
        raise SystemExit(f"link_cycle: {rev!r} is not a commit")
    dest = Path(parent).resolve() / sha[:10]
    if len(str(dest)) > len(str(ROOT)):
        # cl.exe 7.1 opens includes by unnormalised path (`dir\..\..\x.h`) under MAX_PATH:
        # a root deeper than the tree that builds today fails TUs the tree compiles
        print(f"link_cycle: warning: snapshot path {dest} is {len(str(dest)) - len(str(ROOT))} characters "
              f"longer than {ROOT}; a TU near MAX_PATH there will not compile (counted in objects_missing)",
              flush=True)
    mark = dest / SNAPSHOT_MARK
    if mark.exists():
        meta = json.loads(mark.read_text())
        if meta.get("commit") != sha or tree_manifest(dest) != meta.get("tree_manifest"):
            raise SystemExit(f"link_cycle: snapshot {dest} no longer matches its marker; delete it and re-export")
        return dest
    tmp = dest                         # extracted in place; the marker, written last, makes it complete
    if tmp.exists():
        import shutil
        shutil.rmtree(tmp)
    tmp.mkdir(parents=True)
    t = time.time()

    def extract(repo, commit, into):
        proc = subprocess.Popen(["git", "-C", str(repo), "archive", "--format=tar", commit], stdout=subprocess.PIPE)
        with tarfile.open(fileobj=proc.stdout, mode="r|") as tar:
            tar.extractall(into, filter="tar")
        if proc.wait():
            raise SystemExit(f"link_cycle: git archive {commit} in {repo} failed")
    extract(ROOT, sha, tmp)
    subs = {}
    for line in git("ls-tree", "-r", sha).splitlines():
        mode, kind, obj, path = line.split(None, 3)
        if mode == "160000":
            if subprocess.run(["git", "-C", str(ROOT / path), "cat-file", "-e", obj + "^{commit}"],
                              capture_output=True).returncode:
                raise SystemExit(f"link_cycle: submodule {path} lacks its pinned commit {obj}")
            (tmp / path).mkdir(parents=True, exist_ok=True)
            extract(ROOT / path, obj, tmp / path)
            subs[path] = obj
    # the tree's own generated inputs (case-redirect shims on a case-sensitive host), before the marker
    subprocess.run([sys.executable, "-c", "import sys; sys.path.insert(0, 'tools'); import gen_case_shims; "
                    "gen_case_shims.ensure_case_shims()"], cwd=tmp, check=True,
                   env=dict(os.environ, PYTHONDONTWRITEBYTECODE="1"))
    return finish_snapshot(tmp, dest, sha, subs, round(time.time() - t))


def finish_snapshot(tmp, dest, sha, subs, seconds):
    """Write the marker of a complete extraction (tmp; moved to dest if they
    differ). Without its marker a directory is an unfinished export."""
    meta = {"commit": sha, "submodules": subs, "tree_manifest": tree_manifest(tmp),
            "exported_utc": time.strftime("%Y-%m-%d %H:%M:%S", time.gmtime()), "export_seconds": seconds}
    (tmp / SNAPSHOT_MARK).write_text(json.dumps(meta, indent=1))
    if tmp != dest:
        tmp.rename(dest)
    print(f"link_cycle: snapshot {sha[:12]} exported in {seconds}s", flush=True)
    return dest


def run_in_snapshot(args, argv):
    """Export (or reuse) the snapshot, then run this tool on it in a child whose
    ROOT is the snapshot: its objects, links and receipt live in the snapshot's
    own build/, no shared object store, no git repository above it."""
    snap = export_snapshot(args.snapshot, args.snapshot_dir)
    drop, skip = {"--snapshot", "--snapshot-dir", "--out"}, False
    rest = []
    for a in argv:
        if skip:
            skip = False
            continue
        if a.split("=", 1)[0] in drop:
            skip = "=" not in a
            continue
        rest.append(a)
    env = dict(os.environ, LINK_CYCLE_ROOT=str(snap), BFME_OBJSTORE="off", PYTHONDONTWRITEBYTECODE="1",
               GIT_CEILING_DIRECTORIES=str(snap.parent))
    return subprocess.run([sys.executable, str(Path(__file__).resolve()), *rest], env=env, cwd=snap).returncode


def input_state():
    """What a receipt binds, taken when the cycle STARTS and re-proved at its end:
    the commit (a snapshot's marker, else HEAD and the dirty diff), this tool,
    the toolchain, retail and the ledgers."""
    mark = ROOT / SNAPSHOT_MARK
    if mark.exists():
        meta = json.loads(mark.read_text())
        commit = {"commit": meta["commit"], "submodules": meta["submodules"], "snapshot": True,
                  "tree_manifest": tree_manifest(ROOT)}
        if commit["tree_manifest"] != meta["tree_manifest"]:
            raise SystemExit("link_cycle: the snapshot tree differs from its marker; refusing to measure it")
    else:
        diff = subprocess.run(["git", "diff", "HEAD"], capture_output=True, cwd=ROOT).stdout
        commit = {"commit": git("rev-parse", "HEAD"), "snapshot": False,
                  "dirty": bool(git("status", "--porcelain", "--untracked-files=no")),
                  "diff_sha256": hashlib.sha256(diff).hexdigest()}
    root = build.vc71_root()
    return dict(commit, tool_digest=tool_digest(), retail_sha256=sha256(build.EXE),
                toolchain_sha256={n: sha256(root / "Vc7/bin" / n) for n in ("link.exe", "cl.exe", "lib.exe")},
                inputs={"functions_csv": sha256(REVERSE / "functions.csv"),
                        "symbols_csv": sha256(REVERSE / "symbols.csv"),
                        "ghidra_functions_csv": sha256(REVERSE / "ghidra_functions.csv")})


def provenance(rows, present, objs, out):
    """Per-TU provenance of every link input: source, its sha256, the compile's
    dependency record (command fingerprint, header digests) and the object's
    identity. Refuses an object its source no longer produces (a stale cache),
    and one whose bytes changed while its compile record did not since the last
    cycle's provenance (an object no compile wrote: the dependency record does
    not hash the object itself)."""
    sources = census._object_sources(rows)
    path = out / "provenance.json"
    try:
        before = json.loads(path.read_text(encoding="utf-8"))
    except (OSError, ValueError):
        before = {}
    inventory, stale, prov, tampered = {}, [], {}, []
    for p in present:
        rel = Path(p).relative_to(ROOT).as_posix()
        o = objs.get(p)
        rec = {"object": object_identity(o) if o else None}
        src = sources.get(p)
        if src is not None and Path(src).suffix.lower() != build.LIB_SUFFIX:
            if build.compile_is_current(src, p, inventory_cache=inventory):
                rec["proof"] = "inventory"
            elif build.compile_is_current(src, p):
                # the compile could not inventory its include search (macro or parent-traversing
                # includes): source, command and every recorded header still prove it
                rec["proof"] = "deps"
            else:
                stale.append(rel)
            side = Path(p).with_suffix(".deps.json")
            rec.update(source=Path(src).relative_to(ROOT).as_posix(), source_sha256=sha256(src),
                       deps_sha256=sha256(side) if side.exists() else None)
        prov[rel] = rec
        old = before.get(rel)
        if (old and rec.get("deps_sha256") and old.get("deps_sha256") == rec["deps_sha256"]
                and old.get("source_sha256") == rec["source_sha256"] and old.get("object") != rec["object"]):
            tampered.append(rel)
    if stale:
        raise SystemExit(f"link_cycle: {len(stale)} object(s) are not current for their sources (stale cache), "
                         f"e.g. {stale[:5]}; run with --build")
    if tampered:
        raise SystemExit(f"link_cycle: {len(tampered)} object(s) changed with no compile behind the change, "
                         f"e.g. {tampered[:5]}; delete them (and their .deps.json) and run with --build")
    path.write_text(json.dumps(prov, indent=0, sort_keys=True), encoding="utf-8")
    return sha256(path), dict(sorted(collections.Counter(r.get("proof", "no source") for r in prov.values()).items()))


def cache_file(path, stamp, allow_stale):
    """A warm-start cache (quarantine, stubs) is reused only for the objects it
    was computed from; (value or None, whether a stale one was taken)."""
    if not path.exists():
        return None, False
    data = json.loads(path.read_text())
    if not isinstance(data, dict) or "objects_digest" not in data:
        print(f"link_cycle: {path.name} carries no objects digest; ignored", flush=True)
        return None, False
    if data["objects_digest"] == stamp:
        return data["value"], False
    if allow_stale:
        return data["value"], True
    print(f"link_cycle: {path.name} was computed for other objects; ignored (a cold start)", flush=True)
    return None, False


def save_cache(path, stamp, value):
    path.write_text(json.dumps({"objects_digest": stamp, "value": value}))


def receipt_core(receipt):
    """The reproducible part of a receipt: what a cold and a cached run of the same
    inputs must agree on. Times, dates, link history and the warm-start path are
    left out; the core's sha256 is the receipt's identity."""
    keep = ("rules", "commit", "submodules", "snapshot", "dirty", "diff_sha256", "tool_digest",
            "retail_sha256", "toolchain_sha256", "inputs", "objects_digest", "provenance_sha256", "objects",
            "objects_missing", "compile_failed", "currency_proofs", "quarantine_sha256", "stubs_sha256",
            "not_ordered", "not_ordered_bytes", "analyze",
            "scaffold", "final_link", "series")
    return {k: receipt[k] for k in keep if k in receipt}


def digest_of(value):
    return hashlib.sha256(json.dumps(value, sort_keys=True).encode()).hexdigest()


def load_pins():
    pins, byaddr = {}, collections.defaultdict(list)
    with (REVERSE / "symbols.csv").open(newline="", encoding="utf-8") as f:
        for r in csv.DictReader(f):
            if r["address"].startswith("0x") and r["name"] not in pins:
                a = int(r["address"], 16)
                pins[r["name"]] = a
                byaddr[a].append(r["name"])
    return pins, byaddr


class SectionList(dict):
    """{name: (rva, size)} of an image's sections (the first of a repeated name),
    keeping every section for address lookups: link.exe can emit two .data."""
    def __init__(self, entries):
        super().__init__()
        self.all = list(entries)
        for n, a, z in self.all:
            self.setdefault(n, (a, z))

    def name_at(self, a):
        return next((n for n, s, z in self.all if s <= a < s + max(z, 1)), "outside")


def pe_view(path):
    import pefile
    pe = pefile.PE(str(path), fast_load=True)
    secs = SectionList((s.Name.rstrip(b"\0").decode("latin-1"), s.VirtualAddress, s.Misc_VirtualSize)
                       for s in pe.sections)
    pe.parse_data_directories(directories=[pefile.DIRECTORY_ENTRY["IMAGE_DIRECTORY_ENTRY_IMPORT"]])
    imps = {}
    for dll in getattr(pe, "DIRECTORY_ENTRY_IMPORT", []):
        for e in dll.imports:
            imps[e.address - pe.OPTIONAL_HEADER.ImageBase] = import_key(dll.dll.decode("latin-1"), e.name, e.ordinal)
    return pe, pe.get_memory_mapped_image(), secs, imps


def cycle(args):
    t_all = time.time()
    times = {}
    out = Path(args.out)
    out.mkdir(parents=True, exist_ok=True)
    getattr(census, "refuse_unsupported_ledgers", lambda: None)()
    start = input_state()                      # bound at START, re-proved before recording
    rows = census.ledger()
    compile_failed = []
    if args.build:
        t = time.time()
        os.environ.setdefault("BUILD_POOL", str(max(1, (os.cpu_count() or 2) - 2)))
        build.ensure_case_shims()
        sources = census.compile_sources(rows)
        try:
            build.compile_rows(rows, sources)
        except SystemExit as e:
            # every other TU still compiled (the pool drains); a failed TU's object, old or
            # absent, is left out of the link and named in the receipt
            compile_failed = sorted(Path(s).relative_to(ROOT).as_posix() for s in sources
                                    if Path(s).suffix.lower() != build.LIB_SUFFIX
                                    and not build.compile_is_current(Path(s), build.obj_path(Path(s))))
            print(f"link_cycle: {len(compile_failed)} TU(s) failed to compile ({e}): {compile_failed[:5]}",
                  flush=True)
        times["compile"] = round(time.time() - t)
    t = time.time()
    present, missing = census.objects(rows)
    failed_objs = {build.obj_path(ROOT / s) for s in compile_failed}
    if failed_objs:
        missing = list(missing) + [p for p in present if p in failed_objs]
        present = [p for p in present if p not in failed_objs]
    if not args.raw_dumps:
        SWAP.update(load_swap(rows))
        present = list(dict.fromkeys(SWAP.get(p.resolve(), p) for p in present))
    objs = Objects(present)
    units, astat = analyze(rows, objs)
    obj_digest = objects_digest(objs, present)
    prov_digest, proofs = provenance(rows, present, objs, out)
    times["provenance"] = round(time.time() - t)
    pe_r, R, rsecs, rimp = pe_view(build.EXE)
    text0, textsz = rsecs[".text"]
    pins, byaddr = load_pins()
    with (REVERSE / "ghidra_functions.csv").open(newline="") as f:
        ghidra = [int(r["rva"], 16) for r in csv.DictReader(f)]
    cuts = [a for a in ghidra + list(byaddr) if text0 <= a < text0 + textsz]
    retail_imports = globals()["retail_imports"]()
    entries, imp_missing = import_def_entries(undefined_imports(objs), retail_imports)
    libs = make_import_libs(entries, out)
    absobj = write_coff(out / "absolute.obj", [], [(n, -1, v, EXTERNAL) for n, v in ABSOLUTE.items()])
    times["analyze"] = round(time.time() - t)
    print(f"link_cycle: {len(rows):,} rows, {len(units):,} units, {len(present):,} objects "
          f"({len(missing):,} missing), import entries {sum(map(len, entries.values())):,}", flush=True)

    qfile, sfile = out / "quarantine.json", out / "stubs.json"
    quarantine, stale_q = cache_file(qfile, obj_digest, args.allow_stale_cache) if args.reuse_quarantine else (None, False)
    stubs, stale_s = cache_file(sfile, obj_digest, args.allow_stale_cache) if args.reuse_stubs else (None, False)
    warm = {"quarantine": quarantine is not None, "stubs": stubs is not None, "stale": stale_q or stale_s}
    quarantine = set(quarantine or ())
    iters, history = 0, []
    raw = R[text0:text0 + textsz]
    t_link = time.time()
    while True:
        iters += 1
        placed, reasons, rbytes = plan_order(units, quarantine, text0, textsz)
        chunks = filler_chunks(placed, cuts, text0, textsz)
        fill_objs = []
        for k in range(0, len(chunks), 15000):
            part = chunks[k:k + 15000]
            fill_objs.append(write_coff(out / ("fill%02d.obj" % (k // 15000)),
                                        [(region(a), 0x60101020, bytes(raw[a - text0:b - text0]), 2) for a, b in part],
                                        [(fill_name(a), j, 0, EXTERNAL) for j, (a, b) in enumerate(part, 1)]))
        items = sorted([(u["starts"][0], u["head"], "unit") for u in placed] + [(a, fill_name(a), "fill") for a, b in chunks])
        order = out / "order.txt"
        order.write_text("\n".join(order_name(n) for _, n, _ in items) + "\n", encoding="latin-1")
        at = {a: n for a, n, _ in items}
        aliases = {n: at[a] for n, a in pins.items() if a in at and at[a] != n and not n.startswith("??_E")}
        census.alias_object(aliases, out / "alias.obj")
        linkobjs, renamed = zz_objects(objs, placed, {n for _, n, _ in items}, out / "zzobj")
        base_inputs = fill_objs + linkobjs + libs + [absobj, out / "alias.obj"]
        entry = placed[0]["head"]
        if stubs is None:
            log1, _, secs1 = link("pass1", base_inputs, order, entry, BASE, out)
            d1 = diagnostics(log1)
            exported = set()
            for p in linkobjs:
                b = p.read_bytes()
                if b"EXPORT:" in b:
                    exported |= {m.decode("latin-1") for m in re.findall(rb"/EXPORT:(\S+)", b)}
            stubs = sorted(set(d1["unresolved"]) - exported - set(ABSOLUTE))
            save_cache(sfile, obj_digest, stubs)
            history.append({"link": "pass1", "secs": round(secs1), "unresolved": len(d1["unresolved"]),
                            "codes": d1["codes"]})
        write_coff(out / "stubs.obj", [(".stubd", 0xC0300040, bytes(4 * max(1, len(stubs))), 0)],
                   [(n, 1, 4 * i, EXTERNAL) for i, n in enumerate(stubs)])
        inputs = base_inputs + [out / "stubs.obj"]
        shift = None
        if args.shift_base:   # the shifted link runs alongside; it is used when this iteration converges
            pool = concurrent.futures.ThreadPoolExecutor(1)
            shift = pool.submit(link, SHIFT_TAG, inputs, order, entry, args.shift_base, out)
        log, code, secs = link(BASE_TAG, inputs, order, entry, BASE, out)
        d = diagnostics(log)
        if not (out / "base.map").exists():
            raise SystemExit(f"link_cycle: the base link wrote no map (exit {code}): {log[:2000]}")
        mapped = read_map((out / "base.map").read_text(encoding="latin-1"), BASE, zz_names(out)[0])
        culprits, nmiss = drift_culprits(items, mapped[0])
        history.append({"link": f"iter{iters}", "secs": round(secs), "exit": code, "placed_units": len(placed),
                        "drift": len(culprits), "missing_names": nmiss, "new_unresolved": len(d["unresolved"])})
        print(f"link_cycle: iteration {iters}: {len(placed):,} units ordered, {len(culprits):,} drift culprits, "
              f"{len(d['unresolved'])} new unresolved", flush=True)
        if d["unresolved"]:
            stubs = sorted(set(stubs) | set(d["unresolved"]))
            save_cache(sfile, obj_digest, stubs)
        if (not culprits and not d["unresolved"]) or iters >= args.max_iter:
            break
        if shift:
            shift.cancel()
            shift.result()
        quarantine |= set(culprits)
        save_cache(qfile, obj_digest, sorted(quarantine))
    save_cache(qfile, obj_digest, sorted(quarantine))
    shift_res = shift.result() if shift else None
    times["link"] = round(time.time() - t_link)

    t = time.time()
    res = measure(out, units, chunks, objs, R, rsecs, rimp, pins, shift_res is not None, args.shift_base)
    times["measure"] = round(time.time() - t)
    receipt = dict(start, tool="link_cycle", rules="link-cycle-2",
                   date_utc=time.strftime("%Y-%m-%d %H:%M:%S", time.gmtime()),
                   objects_digest=obj_digest, provenance_sha256=prov_digest, objects=len(present),
                   objects_missing=len(missing), compile_failed=compile_failed, currency_proofs=proofs,
                   warm_start=warm, dump_objects_swapped=len(set(SWAP.values())),
                   quarantine_sha256=digest_of(sorted(quarantine)), stubs_sha256=digest_of(sorted(stubs)),
                   links=history, iterations=iters, quarantined_units=len(quarantine),
                   not_ordered=dict(sorted(reasons.items())), not_ordered_bytes=dict(sorted(rbytes.items())),
                   analyze=dict(sorted(astat.items())),
                   scaffold={"filler_chunks": len(chunks), "filler_bytes": sum(b - a for a, b in chunks),
                             "stubs": len(stubs), "aliases": len(aliases), "zz_sections": renamed,
                             "import_entries": sum(map(len, entries.values())),
                             "imports_not_in_retail": len(imp_missing)},
                   final_link={"exit": code, "codes": dict(sorted(d["codes"].items())),
                               "force_duplicates": len(diagnostics(log)["duplicates"]),
                               "force_duplicate_diagnostics": d["codes"].get("LNK4006", 0)},
                   series=res)
    # re-prove the start: the same commit/tree, tool, toolchain, retail, ledgers and objects
    end = input_state()
    moved = sorted(k for k in start if start[k] != end.get(k))
    if objects_digest(Objects(present), present) != obj_digest:
        moved.append("objects_digest")
    receipt["authoritative"] = bool(start.get("snapshot")) and not moved and not warm["stale"] and not compile_failed
    times["total"] = round(time.time() - t_all)
    receipt["seconds"] = times
    receipt["core_sha256"] = digest_of(receipt_core(receipt))
    if moved:
        receipt["moved_during_run"] = moved
        (out / "receipt.rejected.json").write_text(json.dumps(receipt, indent=1), encoding="utf-8")
        raise SystemExit(f"link_cycle: inputs moved during the run ({', '.join(moved)}); no receipt recorded")
    (out / "receipt.json").write_text(json.dumps(receipt, indent=1), encoding="utf-8")
    print(json.dumps(res, indent=1))
    print(f"link_cycle: receipt {out / 'receipt.json'} core {receipt['core_sha256'][:16]}; wall {times}")
    return receipt


def measure(out, units, chunks, objs, R, rsecs, rimp, pins, have_shift, shift_base):
    pe, I, isecs, limp = pe_view(out / (BASE_TAG + ".exe"))
    names, modified = zz_names(out)
    mapped = read_map((out / "base.map").read_text(encoding="latin-1"), BASE, names)
    ledger_starts = {}
    for u in units:
        for r in u["rows"]:
            ledger_starts[r["rva"]] = max(ledger_starts.get(r["rva"], 0), r["size"])
    # the linked image's code pointers live in the map's object basenames: index zz copies too
    for q in modified:                 # a renamed copy is the bytes the link read
        objs.by_base[names[q]] = out / "zzobj" / q
    m = Measure(units, chunks, mapped, I, R, isecs, rimp, limp, pins, objs, ledger_starts)
    recs = m.run()
    textsz = rsecs[".text"][1]
    sh = Shifted(out, I, isecs, rsecs, have_shift, shift_base, {BASE + r["row"]["rva"] for r in recs})
    hard = {}
    for rec in recs:
        if rec["measured"]:
            why = sh.code(rec["linked"], rec["row"]["size"], rec["masked"], rec["rels"])
            if why:
                hard[id(rec)] = why
    # The closure graph. Nodes: units, certified twins, datums (through data
    # pointers), EH thunks. A node is ok when it is self-strict AND its every
    # relocation moved with the base in the shifted link (sh); a failing node
    # takes everything that reaches it out of the closure. Edges to fillers or
    # stubs, or to nodes the graph does not hold, close nothing.
    ok, edges = {}, collections.defaultdict(set)
    for rec in recs:
        n = ("unit", rec["unit"]["id"])
        ok[n] = ok.get(n, True) and rec["measured"] and not rec["fails"] and id(rec) not in hard
        edges[n] |= rec["edges"]
    for k, (good, _) in m.twins.items():
        n = ("twin", k[0], k[1])
        ok[n] = good and not sh.code(k[0], ledger_starts[k[1]], {j for fo, _, _ in m.twin_rels.get(k, ())
                                                                   for j in range(fo, fo + 4)},
                                     m.twin_rels.get(k, ()))
        edges[n] |= m.twin_edges.get(k, set())
    for key, node in m.dnodes.items():
        n = ("datum", key)
        ok[n] = not node["fails"] and not sh.data(key, node)
        edges[n] |= node["edges"]
    for es in list(edges.values()):
        for e in es:
            if e[0] == "eh" and e not in ok:
                ok[e] = not sh.eh(e[1])
    # a dump (generated/asm unit) is retail bytes re-encoded, not source: in the
    # source closure an edge into one closes nothing, like a filler
    dump_units = {u["id"] for u in units if u["rows"] and u["rows"][0]["kind"] in ("generated", "asm")}
    src_edges = {n: {("dump", e[1]) if e[0] == "unit" and e[1] in dump_units else e for e in es}
                 for n, es in edges.items()}
    closed = greatest_closure(ok, src_edges, bad_targets=("fill", "stub", "dump"))
    closed_dumps_ok = greatest_closure(ok, edges)
    # the pilot's rule, for comparison: code edges only, fillers are leaves, no shift
    pilot_ok = {n: v for n, v in ok.items() if n[0] == "unit"}
    for rec in recs:
        n = ("unit", rec["unit"]["id"])
        pilot_ok[n] = pilot_ok.get(n, True) and rec["measured"] and not rec["fails"]
    pilot_edges = {n: {e for e in es if e[0] == "unit"} for n, es in edges.items() if n[0] == "unit"}
    closed_pilot = greatest_closure(pilot_ok, pilot_edges, bad_targets=(), unknown_closes=True)
    fold = out / "fold_list.csv"
    with fold.open("w", newline="", encoding="utf-8") as f:
        w = csv.writer(f)
        w.writerow(["linked_rva", "retail_rva", "symbol", "object", "verdict"])
        for (lt, rt), (good, why) in sorted(m.twins.items()):
            s = m.sym_at(lt)
            w.writerow(["0x%08X" % lt, "0x%08X" % rt, s[1], s[2], why])
    cols = ["name", "kind", "source", "retail_rva", "size", "linked_rva", "placed", "placement_reason", "self_strict",
            "closed_strict", "closed_strict_dumps_ok", "closed_strict_pilot_rule", "pinned_strict", "byte_equal", "hardcoded", "failure_count",
            "failures"]
    series = collections.Counter()
    spans = collections.defaultdict(list)
    status = out / "link_status.csv"
    with status.open("w", newline="", encoding="utf-8") as f:
        w = csv.writer(f)
        w.writerow(cols)
        for rec in sorted(recs, key=lambda r: (r["row"]["rva"], r["row"]["name"])):
            r, u = rec["row"], rec["unit"]
            n = ("unit", u["id"])
            st = int(rec["measured"] and not rec["fails"])
            L = rec["linked"]
            be = int(rec["placed"] and I[r["rva"]:r["rva"] + r["size"]] == R[r["rva"]:r["rva"] + r["size"]])
            fails = rec["fails"] + ([f"shift:{hard[id(rec)]}"] if id(rec) in hard else [])
            reason = u.get("why") or ("copy not selected" if u.get("not_selected") is not None else "")
            row = {"name": r["name"], "kind": r["kind"], "source": r["source"], "retail_rva": "0x%08X" % r["rva"],
                   "size": r["size"], "linked_rva": "" if L is None else "0x%08X" % L, "placed": rec["placed"],
                   "placement_reason": reason, "self_strict": st,
                   "closed_strict": int(st and n in closed), "closed_strict_dumps_ok": int(st and n in closed_dumps_ok),
                   "closed_strict_pilot_rule": int(st and n in closed_pilot),
                   "pinned_strict": int(st and not rec["unpinned"]), "byte_equal": be,
                   "hardcoded": int(id(rec) in hard), "failure_count": len(fails),
                   "failures": ";".join(f"{k}x{v}" if v > 1 else k for k, v in collections.Counter(fails).items())}
            w.writerow([row[c] for c in cols])
            k = r["kind"]
            span = (r["rva"], r["rva"] + r["size"])
            flags = {"all": 1, "placed": rec["placed"], "self_strict_any": st, "placed_self_strict": rec["placed"] and st,
                     "placed_pinned_strict": rec["placed"] and row["pinned_strict"],
                     "placed_closed_strict": rec["placed"] and row["closed_strict"],
                     "placed_closed_strict_dumps_ok": rec["placed"] and row["closed_strict_dumps_ok"],
                     "placed_closed_strict_pilot_rule": rec["placed"] and row["closed_strict_pilot_rule"],
                     "placed_byte_equal": be, "placed_self_strict_hardcoded": rec["placed"] and st and row["hardcoded"],
                     "placed_self_strict_shift_safe": rec["placed"] and st and not row["hardcoded"]}
            for name, v in flags.items():
                if v:
                    series[(k, name, "rows")] += 1
                    series[(k, name, "bytes")] += r["size"]
                    spans[(k, name)].append(span)
    res = {}
    for (k, name), sp in sorted(spans.items()):
        res.setdefault(k, {})[name] = {"rows": series[(k, name, "rows")], "bytes": series[(k, name, "bytes")],
                                       "unique_bytes": unique_bytes(sp),
                                       "pct_text": round(100 * unique_bytes(sp) / textsz, 2)}
    reasons = collections.Counter()
    rbytes = collections.Counter()
    for rec in recs:
        if rec["row"]["kind"] == "real" and rec["placed"]:
            fails = rec["fails"] + (["shift"] if id(rec) in hard else [])
            for c in {f.split(":")[0] for f in fails}:
                reasons[c] += 1
                rbytes[c] += rec["row"]["size"]
    res["credit_unique_bytes"] = res.get("real", {}).get("placed_closed_strict", {}).get("unique_bytes", 0)
    res["placed_failure_classes"] = {c: [reasons[c], rbytes[c]] for c, _ in sorted(reasons.items(),
                                                                                    key=lambda kv: (-kv[1], kv[0]))}
    res["twins"] = dict(sorted(collections.Counter(v[1] for v in m.twins.values()).items()))
    res["eh_thunks"] = dict(sorted(m.eh.items()))
    res["imports_read_through_equivalent"] = m.import_equiv
    kinds = collections.Counter()
    for n, v in ok.items():
        kinds[(n[0], "ok" if v else "failed")] += 1
        kinds[(n[0], "closed" if n in closed else "open")] += 1
    res["closure_nodes"] = {f"{a}_{b}": c for (a, b), c in sorted(kinds.items())}
    res["shift"] = sh.summary()
    res["ilt_routes"] = dict(sorted(m.ilt_routes.items()))
    res["retail_text_bytes"] = textsz
    res["link_status_sha256"] = sha256(status)
    return res


class Shifted:
    """The shifted link's verdicts. Same inputs at another base: the layout must be
    identical, every non-relocation byte equal, and every relocated word must move
    by exactly the base delta (DIR32; REL32 and absolutes do not move). Checked
    for rows' code, twins, every datum of the closure and EH tables. Without a
    shifted link every check fails: the base adjustment is unverified."""

    def __init__(self, out, I, isecs, rsecs, have_shift, shift_base, starts):
        self.I, self.delta, self.base_s = I, (shift_base or 0) - BASE, shift_base
        self.lo, self.hi = BASE + rsecs[".rdata"][0], BASE + max(s + z for _, s, z in rsecs.all)
        self.starts = starts
        self.S, self.why = None, "no shifted link"
        self.failed = collections.Counter()
        if have_shift and shift_base and (out / (SHIFT_TAG + ".exe")).exists():
            _, S, ssecs, _ = pe_view(out / (SHIFT_TAG + ".exe"))
            if [(n, a, z) for n, a, z in ssecs.all] != [(n, a, z) for n, a, z in getattr(isecs, "all", ())]:
                self.why = "shifted layout differs"
            else:
                self.S, self.why = S, None

    def _note(self, kind, why):
        if why:
            self.failed[(kind, why)] += 1
        return why

    def words(self, at, size, masked, rels):
        S, I = self.S, self.I
        for k in range(size):
            if k not in masked and I[at + k] != S[at + k]:
                return "byte moved"
        for fo, ty, absolute in rels:
            d = (u32(S, at + fo) - u32(I, at + fo)) & 0xFFFFFFFF
            if d != (0 if absolute or ty == REL32 else self.delta & 0xFFFFFFFF):
                return "relocation not adjusted"
        return None

    def code(self, at, size, masked, rels):
        """None, or why code at `at` does not follow a rebase: a hard-coded retail
        data VA or row start no relocation covers, or a shifted-link difference."""
        if hardcoded_operands(self.I[at:at + size], at + BASE, masked, self.lo, self.hi, self.starts):
            return self._note("code", "hardcoded address")
        if self.S is None:
            return self._note("code", self.why)
        return self._note("code", self.words(at, size, masked, rels))

    def data(self, key, node):
        if self.S is None:
            return self._note("datum", self.why)
        start, _, size = key
        if size <= 0 or start < 0 or start + size > len(self.I):
            return None                                   # already failed as data-extent
        return self._note("datum", self.words(start, size, node.get("masked", set()), node.get("rels", ())))

    def eh(self, lt):
        """The thunk's FuncInfo, unwind/try maps and handler addresses all moved by
        the delta (their own entries compared through eh_verdict at the base)."""
        if self.S is None:
            return self._note("eh", self.why)
        I, S = self.I, self.S
        try:
            if u32(S, lt + 1) - u32(I, lt + 1) != self.delta or u32(S, lt + 6) != u32(I, lt + 6):
                return self._note("eh", "thunk not adjusted")
            fi = u32(I, lt + 1) - BASE
            if eh_tables(I, fi, BASE) != eh_tables(S, fi, self.base_s):
                return self._note("eh", "FuncInfo not adjusted")
        except (struct.error, IndexError):
            return self._note("eh", "FuncInfo unparsable")
        return None

    def summary(self):
        out = {"checked": self.S is not None, "why_unchecked": self.why, "delta": self.delta}
        out["failed"] = {f"{k}:{w}": c for (k, w), c in sorted(self.failed.items())}
        return out


def eh_tables(m, fi, base):
    """funcinfo() with every image address made base-relative (0 stays 0)."""
    magic, maxst, ntry, un, tr = funcinfo(m, fi, base)

    def rel(v):
        return v - base if v else 0
    return (magic, maxst, ntry, [(s, rel(a)) for s, a in un],
            [(lo, hi, ch, nc, [(h0, rel(h1), h2, rel(h3)) for h0, h1, h2, h3 in hs]) for lo, hi, ch, nc, hs in tr])


def main(argv=None):
    argv = sys.argv[1:] if argv is None else argv
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--build", action="store_true", help="compile stale objects first (BUILD_POOL = cores - 2)")
    ap.add_argument("--max-iter", type=int, default=6, help="links in the quarantine loop (default 6)")
    ap.add_argument("--shift-base", type=lambda s: int(s, 0), default=SHIFT_BASE,
                    help="second link's base (0 = none, and nothing is credited; default 0x10000000)")
    ap.add_argument("--reuse-quarantine", action="store_true",
                    help="start from the last cycle's quarantine list (only if computed for the same objects)")
    ap.add_argument("--reuse-stubs", action="store_true",
                    help="skip pass 1, reuse the last cycle's stub names (only if computed for the same objects)")
    ap.add_argument("--allow-stale-cache", action="store_true",
                    help="reuse quarantine/stubs computed for other objects (the receipt is then not authoritative)")
    ap.add_argument("--snapshot", metavar="REV",
                    help="measure an immutable export of REV (git archive incl. submodules), not the worktree")
    ap.add_argument("--snapshot-dir", default=os.environ.get("LINK_CYCLE_SNAPSHOTS") or
                    str(Path(tempfile.gettempdir()) / "lcs"),
                    help="where snapshots live, one directory per commit with its outputs in build/; "
                         "no deeper than this tree (MAX_PATH)")
    ap.add_argument("--measure-only", action="store_true", help="re-measure the last links (no link)")
    ap.add_argument("--raw-dumps", action="store_true",
                    help="link game/gen_asm/ dumps as committed (raw db) instead of dump_relocs objects")
    ap.add_argument("--out", default=str(OUT))
    args = ap.parse_args(argv)
    if args.snapshot:
        return run_in_snapshot(args, argv)
    if args.measure_only:
        return remeasure(args)
    cycle(args)
    return 0


def remeasure(args):
    out = Path(args.out)
    rows = census.ledger()
    present, _ = census.objects(rows)
    if not args.raw_dumps:
        SWAP.update(load_swap(rows))
        present = list(dict.fromkeys(SWAP.get(p.resolve(), p) for p in present))
    objs = Objects(present)
    units, _ = analyze(rows, objs)
    _, R, rsecs, rimp = pe_view(build.EXE)
    text0, textsz = rsecs[".text"]
    pins, byaddr = load_pins()
    q = json.loads((out / "quarantine.json").read_text()) if (out / "quarantine.json").exists() else []
    quarantine = set(q["value"] if isinstance(q, dict) else q)
    with (REVERSE / "ghidra_functions.csv").open(newline="") as f:
        ghidra = [int(r["rva"], 16) for r in csv.DictReader(f)]
    placed, _, _ = plan_order(units, quarantine, text0, textsz)
    chunks = filler_chunks(placed, [a for a in ghidra + list(byaddr) if text0 <= a < text0 + textsz], text0, textsz)
    t = time.time()
    res = measure(out, units, chunks, objs, R, rsecs, rimp, pins, True, args.shift_base)
    print(json.dumps(res, indent=1))
    path = out / "receipt.json"
    if path.exists():   # the links are the receipt's; the measure, its digest and series are replaced
        receipt = json.loads(path.read_text(encoding="utf-8"))
        receipt.update(series=res, tool_digest=tool_digest(), rules="link-cycle-2", authoritative=False,
                       remeasured_utc=time.strftime("%Y-%m-%d %H:%M:%S", time.gmtime()))
        receipt.setdefault("seconds", {})["measure"] = round(time.time() - t)
        receipt["core_sha256"] = digest_of(receipt_core(receipt))
        path.write_text(json.dumps(receipt, indent=1), encoding="utf-8")
    return 0


if __name__ == "__main__":
    sys.exit(main())
