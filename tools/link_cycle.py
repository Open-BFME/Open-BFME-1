#!/usr/bin/env python3
"""Link the tree at retail's addresses and measure every matched row in the image.

BFME1 port of Open-BFME-2's tools/link_cycle.py (same phases, same series,
same receipt), with BFME1's binding rules:

  - Retail was linked /INCREMENTAL: a call or a vtable slot encodes the ILT
    thunk (`jmp body`, 0x1000..0x5B000, or a `?j_` row), never the body.
    This link is /INCREMENTAL:NO (/ORDER forbids an ILT), so a reference
    to the body counts when retail's thunk jumps there (`ilt_routes`).
    Across the measurement, distinct bodies or distinct thunks must not
    collapse to one linked target. Taking both a thunk and its body's address
    also preserves their observable inequality.
  - No ICF in retail (/OPT:NOICF here too); distinct retail bodies cannot
    share a provider through byte-twin equivalence.
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
     __imp_ name an object references; proved source-owned native thunks retain
     only their library IAT cells. Shipped /MD runtime archives supply CRT statics
     and legacy aliases; /OPT:NOICF. Unresolved names get 4-byte
     data stubs, duplicate definitions need /FORCE; both are counted.
  4. Measure (per ledger row, every failing relocation, not the first):
     - a unit counts only when the /MAP shows the link selected its own copy
       of the head symbol (`not-selected` otherwise: /FORCE kept another);
     - code references translate through verified ledger extents or fillers
       and must equal retail's target; unrelocated direct branches create
       closure edges too;
     - an __ehhandler$ thunk counts as its owner function's (owner + offset)
       only when the row is that owner and the FuncInfo, unwind and try maps
       equal retail's, with verified providers for the handler, funclets
       and catch descriptors (including their dependency closures);
     - data references must map 1:1, and the linked datum's bytes must equal
       retail's at the referenced address; a datum whose name is pinned in
       symbols.csv must sit at its pin (the `pinned` series also fails
       unpinned data). Pointers INSIDE a datum are references too: code
       pointers translate, data pointers must map 1:1, reach a real datum
       (not a stub) and agree with its pin, and that datum is checked the
       same way, to any depth (`data-ptr-*` failures). Whole-datum mappings
       preserve identity and offsets; literal image pointers fail closed;
     - imports match on (dll, name or ordinal). Retail's duplicate IAT slots
       of one import are one datum only for references that read through the
       slot (call/jmp/push/mov [slot]) on both sides; a reference that can
       observe the slot itself keeps the 1:1 rule.
     Closed-strict: the closure graph holds units, datums and
     EH thunks; a node is ok when self-strict AND shift-verified (5), and a
     row closes when its unit reaches only ok nodes. A filler, a stub or a
     node the graph does not hold is never a leaf. Credit = unique retail
     bytes of placed, closed-strict rows in progress.py's recovered source
     lanes; fillers, stubs, generated rows, dumps and prebuilt libraries never count.
     A byte-verified prebuilt library is a legitimate dependency, with its
     own series, even though its bytes are not recovered source credit.
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
     object store; a snapshot needs the host-key launcher for bundle authority.
     Runs record checkout cleanliness at start and end; readers also require ancestry,
     integrity, matching rules and freshness before granting authority.
     BFME1's rule tuple includes a profile and implementation digest; it is
     distinct from BFME2 link-cycle-2. Dirty diagnostics need --allow-dirty.
     The finalized source closure graph is serialized without asking another
     verdict. Its digest, all ledger/evidence inputs, decoder versions and
     canonical per-object identities are bound by the receipt. Instance tags
     bind exact receipt bytes; core/canonical core compare reproducible content.
     measurements/<tag>/ retains each receipt, graph, status and provenance;
     --measure-only writes a separate non-authoritative diagnostic directory.

  python3 tools/link_cycle.py [--build] [--max-iter 6] [--shift-base 0x10000000]
  python3 tools/link_cycle.py --snapshot HEAD --build [--reuse-quarantine --reuse-stubs]
  python3 tools/link_cycle.py --measure-only     # re-measure the last links (never authoritative)

Outputs in build/link_cycle/: link_status.csv (one row per matched ledger
row), closure_graph.json.gz, fold_list.csv, provenance.json, receipt.json,
receipt.json.identity.json, measurements/, base.map/.exe/.log, shft.*. Diagnostic:
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
# snapshot); snapshots execute their own tools and bind those dependencies.
ROOT = Path(os.environ.get("LINK_CYCLE_ROOT") or Path(__file__).resolve().parents[1]).resolve()
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402
import link_census as census  # noqa: E402
import link_cycle_context as context  # noqa: E402
import cycle_source  # noqa: E402
import census_receipts  # noqa: E402
import progress  # noqa: E402
import retail_relocs  # noqa: E402

OUT = ROOT / "build" / "link_cycle"
COMPILE_INPUTS = "compile_inputs.json"
BASE = 0x400000
SHIFT_BASE = 0x10000000
# BFME1 has one text group; funclets stay beside their functions.
REGIONS = [(0x1000, ".text")]           # BFME1: funclets sit beside their functions
ILT = (0x1000, 0x5B000)                  # retail's ILT: rel32 jumps only (no .reloc site below 0x5B000)
REVERSE = ROOT / "targets" / "game" / "reverse"
ABSOLUTE = {"__except_list": 0}          # exsup.asm: __except_list equ 0 (an FS: offset)
RULES = context.RULES
text_bytes = context.text_bytes
text_sha256 = context.text_sha256
measure_env = context.measure_env
COMDAT, EXTERNAL, STATIC, WEAK = 0x1000, 2, 3, 105
REL32, DIR32 = 0x14, 6


# ---------------------------------------------------------------- COFF
class Sec:
    __slots__ = ("idx", "name", "size", "ptr", "flags", "relocs", "sel")


class Sym:
    __slots__ = ("i", "name", "value", "sec", "cls")


def parse_coff(data):
    """(sections, {raw index: Sym}) of an i386 COFF object."""
    build.validate_coff(data)
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


def row_kind(row, naked=False):
    notes = row.get("notes", "")
    for k in ("gen-funclet", "gen-import", "gen-alias"):
        if k in notes:
            return k
    src = row.get("source", "")
    lane = progress.source_lane(src, notes, naked)
    if src.startswith(("game/gen_asm/", "game/gen_small/")) or lane == "generated":
        return "generated"
    if lane == "dump":
        return "asm"
    return "real" if lane in progress.DECOMPILED_LANES else lane


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
    conversion_gate rule C1 keeps their sources raw `db`. Dumpness is the
    gen-dump note (build.is_scaffold_row); only dumps that dump_relocs.py
    rebuilt have a relocatable object to swap in."""
    swap = {}
    for row in rows:
        if build.is_scaffold_row(row):
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
            except (ValueError, IndexError, struct.error) as error:
                raise SystemExit(f"link_cycle: invalid COFF object {p}: {error}; "
                                 "delete it and rerun with --build") from None
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
    matched = {(r["name"], r["target_rva"]): (int(r.get("target_size") or 0), r["source"]) for r in rows}
    texts = {}
    for source in {r["source"] for r in rows if Path(r["source"]).suffix.lower() in progress.CPP_SUFFIXES}:
        path = ROOT / source
        if path.is_file():
            text = path.read_text(encoding="utf-8", errors="replace")
            if "_asm" in text or "naked" in text or "_emit" in text:
                texts[source] = text
    naked = progress.naked_cpp_rows(matched, texts)
    units, keyed = [], {}
    stat = collections.Counter()
    for r in rows:
        rva, size = int(r["target_rva"], 16), int(r.get("target_size") or 0)
        p = row_obj(r)
        sym = (re.search(r"(?:^|;)object-symbol=([^;]+)", r.get("notes", "")) or [None, r["name"]])[1]
        rec = {"name": r["name"], "sym": sym, "rva": rva, "size": size,
               "kind": row_kind(r, (r["name"], r["target_rva"]) in naked), "source": r["source"],
               "provenance": progress.source_lane(r["source"], r.get("notes", ""),
                                                   (r["name"], r["target_rva"]) in naked)}
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


def native_import_thunks(rows, objs, retail, imports, entries):
    """Source-owned FF25 providers proved at their own ledgered retail IAT slots."""
    expected = {(name if name.startswith("?") else "_" + name): (dll, import_name(name))
                for dll, names in entries.items() for name in names}
    owners = collections.defaultdict(list)
    for row in rows:
        owners[(str(row_obj(row)), build.ledger_object_symbol(row))].append(row)
    proved, refused = set(), set()
    for path in objs.paths:
        obj = objs.get(path)
        if obj is None:
            continue
        secs, syms, raw = obj
        for y in syms.values():
            if y.cls != EXTERNAL or y.name not in expected:
                continue
            if y.sec <= 0:
                if y.sec == -1 or y.value:
                    refused.add(y.name)
                continue
            rows_at = owners.get((str(path), y.name), [])
            if len(rows_at) != 1 or row_kind(rows_at[0]) != "real" or int(rows_at[0]["target_size"]) != 6:
                refused.add(y.name)
                continue
            sec = secs[y.sec - 1]
            code = raw[sec.ptr + y.value:sec.ptr + y.value + 6]
            relocs = [(off - y.value, syms[index].name, kind) for off, index, kind in sec.relocs
                      if y.value <= off < y.value + 6]
            rva = int(rows_at[0]["target_rva"], 16)
            original = retail[rva:rva + 6]
            if (y.value + 6 > sec.size or not sec.flags & 0x20
                    or code != b"\xff\x25" + bytes(4) or relocs != [(2, "__imp_" + y.name, DIR32)]
                    or len(original) != 6 or original[:2] != b"\xff\x25"):
                refused.add(y.name)
                continue
            slot = struct.unpack_from("<I", original, 2)[0] - BASE
            if imports.get(slot) != expected[y.name]:
                refused.add(y.name)
                continue
            proved.add(y.name)
    return proved - refused


def runtime_libraries():
    """/NODEFAULTLIB must not discard the shipped /MD CRT statics and aliases."""
    directory = build.vc71_root() / "Vc7" / "lib"
    return [directory / "msvcrt.lib", directory / "oldnames.lib"]


def undecorate_stdcall_imports(path):
    """/DEF keeps @N in the DLL name; UNDECORATE keeps it only on the COFF symbol."""
    data = bytearray(path.read_bytes())
    at = 8
    while at + 60 <= len(data):
        size = int(data[at + 48:at + 58].decode("ascii").strip())
        start = at + 60
        if size >= 20 and data[start:start + 4] == b"\0\0\xff\xff":
            end = data.index(0, start + 20, start + size)
            symbol = bytes(data[start + 20:end]).decode("latin-1")
            kind = struct.unpack_from("<H", data, start + 18)[0]
            if re.fullmatch(r"_[^?@]+@\d+", symbol) and (kind >> 2) & 7 == 2:
                struct.pack_into("<H", data, start + 18, (kind & ~0x1C) | (3 << 2))
        at += 60 + size + (size & 1)
    path.write_bytes(data)


def make_import_libs(entries, outdir, native_thunks=()):
    root = build.vc71_root()
    libs = []
    for dll, names in sorted(entries.items()):
        stem = re.sub(r"\W", "_", dll.rsplit(".", 1)[0].lower())
        d = outdir / f"imp_{stem}.def"
        # CODE also defines a callable thunk; only a proved native owner may replace it.
        exports = [f"  {n}" + (" DATA" if (n if n.startswith("?") else "_" + n) in native_thunks else "") + "\n"
                   for n in names]
        d.write_text(f"LIBRARY {dll}\nEXPORTS\n" + "".join(exports), encoding="latin-1")
        lib = outdir / f"imp_{stem}.lib"
        cmd = [str(root / "Vc7/bin/lib.exe"), "/NOLOGO", "/MACHINE:X86", f"/DEF:{d}", f"/OUT:{lib}"]
        if sys.platform != "win32":
            cmd.insert(0, "wine")   # as link() runs link.exe: the toolchain's .exe files are not host executables
        res = subprocess.run(cmd, capture_output=True, text=True, errors="replace", env=build.compiler_environment(root))
        if res.returncode or not lib.exists():
            raise SystemExit(f"link_cycle: lib.exe failed for {dll}:\n{res.stdout}{res.stderr}")
        undecorate_stdcall_imports(lib)
        libs.append(lib)
    return libs


def zz_objects(objs, placed, ordered_names, zzdir):
    """Private copies with every unplaced code section renamed .text$zz, so unplaced
    code lands after retail's last group instead of inside it. Every link input
    is a private short-named copy in zzdir (o00000.obj): creating a hard link
    changes the already-consumed source object's inode generation.
    link.exe 7.1 cannot open a path past MAX_PATH, and object names run
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
        if not q.exists() or os.path.samefile(p, q) or q.read_bytes() != d:
            q.unlink(missing_ok=True)              # retire old hard links without writing through them
            q.write_bytes(bytes(d))
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
    # under wine an absolute POSIX path (/home/...) reads as a link.exe option and the input is
    # ignored (LNK4044): name each input relative to the link's working directory, outdir
    rsp.write_text("\n".join(f'"{p if sys.platform == "win32" else os.path.relpath(p, outdir)}"' for p in inputs)
                   + "\n", encoding="latin-1")
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


def funcinfo(m, a, base):
    def extent(at, size):
        if at < 0 or size < 0 or at + size > len(m):
            raise ValueError("EH table outside image")
    extent(a, 24)
    magic, maxst, pu, ntry, ptry, _ = struct.unpack_from("<IiIIII", m, a)
    if not 0 <= maxst <= 400 or ntry > 50 or (maxst and not pu) or (ntry and not ptry):
        raise ValueError("unsupported EH table extent")
    if maxst:
        extent(pu - base, maxst * 8)
    if ntry:
        extent(ptry - base, ntry * 20)
    un = [struct.unpack_from("<iI", m, pu - base + 8 * i) for i in range(maxst)]
    tr = []
    for i in range(ntry):
        lo, hi, ch, nc, ph = struct.unpack_from("<iiiiI", m, ptry - base + 20 * i)
        if not 0 <= nc <= 20 or (nc and not ph):
            raise ValueError("unsupported catch table extent")
        if nc:
            extent(ph - base, nc * 16)
        tr.append((lo, hi, ch, nc, [struct.unpack_from("<IIiI", m, ph - base + 16 * j) for j in range(nc)]))
    return magic, maxst, ntry, un, tr


def eh_verdict(I, lt, R, rt, lbase, rbase, translate=None, reference=None):
    """None when the linked __ehhandler$ thunk at lt and retail's at rt (mov eax,
    FuncInfo; jmp handler) carry equal EH data; else the first difference."""
    # Both 10-byte thunks must lie in their image: a retail target past its bytes
    # raised IndexError and lost the whole Open-BFME-1 bf7709aa22 run, and a
    # negative offset would silently read from the image's end.
    if not (0 <= lt <= len(I) - 10 and 0 <= rt <= len(R) - 10):
        return "thunk outside the image"
    if I[lt] != 0xB8 or R[rt] != 0xB8 or I[lt + 5] != 0xE9 or R[rt + 5] != 0xE9:
        return "thunk shape differs"
    def proven(la, ra, *, direct=False, data=False):
        if reference is not None:
            return reference(la, ra, direct=direct, data=data)
        # Address translation alone proves no provider bytes or dependencies.
        return False

    lh = lt + 10 + struct.unpack_from("<i", I, lt + 6)[0]
    rh = rt + 10 + struct.unpack_from("<i", R, rt + 6)[0]
    if not proven(lh, rh):
        return "handler target unverified"
    try:
        a = funcinfo(I, u32(I, lt + 1) - lbase, lbase)
        b = funcinfo(R, u32(R, rt + 1) - rbase, rbase)
    except (struct.error, IndexError, ValueError):
        return "FuncInfo unparsable"
    if a[:3] != b[:3]:
        return "FuncInfo header differs"
    if [x[0] for x in a[3]] != [x[0] for x in b[3]]:
        return "unwind map differs"
    if any((x[1] == 0) != (y[1] == 0) for x, y in zip(a[3], b[3])):
        return "unwind action presence differs"
    if not all(proven(x[1] - lbase, y[1] - rbase)
               for x, y in zip(a[3], b[3]) if x[1] and y[1]):
        return "unwind funclet unverified"
    if [t[:4] for t in a[4]] != [t[:4] for t in b[4]]:
        return "try map differs"
    for t, v in zip(a[4], b[4]):
        if [(h[0], h[2]) for h in t[4]] != [(h[0], h[2]) for h in v[4]]:
            return "catch map differs"
        if any((h[1] == 0) != (g[1] == 0) or (h[1] and not proven(h[1] - lbase, g[1] - rbase, data=True))
               for h, g in zip(t[4], v[4])):
            return "catch type unverified"
        if not all(h[3] and g[3] and proven(h[3] - lbase, g[3] - rbase)
                   for h, g in zip(t[4], v[4])):
            return "catch funclet unverified"
    return None


def hardcoded_operands(code, va, masked, lo, hi, starts=frozenset(), entries=(0,)):
    """Offsets of 32-bit displacement/immediate operands in `code` (at `va`)
    holding an absolute address in [lo, hi) or in `starts` that no relocation
    covers: they cannot follow a rebase. Relative branch targets are not
    operands here. The caller passes retail's data VAs and row starts: a
    source hard-codes retail's addresses, and a whole-image range would also
    take ASCII tags (push 0x696E74, "int") for addresses."""
    if _CSD is None:
        return []
    out = []
    for ins in code_flow(code, va, entries)[0]:
        at = ins.address - va
        for off, size in ((ins.disp_offset, ins.disp_size), (ins.imm_offset, ins.imm_size)):
            if size != 4 or not off or ins.mnemonic == "call" or ins.mnemonic.startswith("j"):
                continue
            k = at + off
            v = u32(code, k)
            if (lo <= v < hi or v in starts) and not any(j in masked for j in range(k, k + 4)):
                out.append(k)
    return out


def code_flow(code, va, entries=(0,)):
    """Reachable instructions and fallthrough beyond an extent. Decode branch
    destinations separately so inline data cannot hide a later direct call."""
    if _CSD is None:
        return [], False, False
    work, seen, covered, fallthrough = list(entries), {}, set(), False
    while work:
        at = work.pop()
        if at in seen:
            continue
        ins = next(_CSD.disasm(bytes(code[at:at + 15]), va + at, count=1), None)
        if ins is None or any(k in covered for k in range(at, at + ins.size)):
            return list(seen.values()), False, fallthrough
        seen[at] = ins
        covered.update(range(at, at + ins.size))
        branch = ins.mnemonic == "call" or ins.mnemonic.startswith(("j", "loop"))
        if branch and ins.operands and ins.operands[0].type == capstone.x86.X86_OP_IMM:
            target = ins.operands[0].imm - va
            if 0 <= target < len(code):
                work.append(target)
        if ins.mnemonic == "jmp" or ins.mnemonic.startswith(("ret", "iret")) or ins.mnemonic in ("int3", "ud2", "hlt"):
            continue
        end = at + ins.size
        if end < len(code):
            work.append(end)
        else:
            fallthrough = True
    return list(seen.values()), True, fallthrough


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
                # Only ledger extents are checked by run(). The rest of a
                # COFF section (helpers, gaps, tails) has no verified provider.
                for r in u["rows"]:
                    if 0 <= r["off"] < r["off"] + r["size"] <= u["size"]:
                        items.append((la + r["off"], la + r["off"] + r["size"], r["rva"], ("unit", u["id"])))
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
        self.code_targets = collections.defaultdict(set)
        self.pointer_links = collections.defaultdict(set)
        self.code_entries = collections.defaultdict(lambda: {0})
        self.code_pointers = collections.defaultdict(set)
        self.code_users = collections.defaultdict(dict)
        self.code_pointer_users = collections.defaultdict(dict)
        self.eh_nodes = {}
        self.datum_conflicts = set()
        self.retail_sites = None

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

    def storage_ref(self, lt, rt, width, owner, *, indexed=False, pointer_words=False):
        """Memory in .text is storage; verified rows supply bytes, not entries."""
        # BFME1 docs/matching.md requires all consumed storage bytes. A
        # function's verified extent does not bound an unknown byte index.
        # Same-section compiler tables retain body_guard's typed table rule.
        if indexed and not (pointer_words and owner.startswith('$')):
            return "code-storage-range-unknown:" + owner, set()
        edges, end = set(), lt + max(width, 1)
        at = lt
        while at < end:
            tr, item = self.T(at)
            # docs/matching.md checks relocation targets; BFME1 ledger extents
            # are the only code coverage we have verified, never their gaps.
            if tr != rt + at - lt or item is None:
                return "code-storage-unverified:" + owner, set()
            i = bisect.bisect_right(self.istarts, at) - 1
            if indexed:
                # An unknown effective range observes the whole containing
                # storage extent; no integer/index analysis is needed.
                end = max(end, self.items[i][1])
                indexed = False
            if item[0] == "unit":
                unit = self.units[item[1]]
                obj = self.objs.get(Path(unit["obj"]))
                sec = obj[0][unit["sec"] - 1]
                for site, si, ty in sec.relocs:
                    slot = unit["linked"] + site
                    if (ty == DIR32 and obj[1].get(si) is not None and obj[1][si].name not in ABSOLUTE
                            and lt < slot + 4 and slot < end and (lt, end - lt) != (slot, 4)
                            and not (pointer_words and width == 4 and (slot - lt) % 4 == 0)):
                        # docs/matching.md masks whole symbolic DIR32 words,
                        # not raw bytes of relocated instruction operands.
                        return "code-storage-raw-relocation:" + owner, set()
            edges.add(item)
            at = min(end, self.items[i][1])
        return None, edges

    def pointer_word(self, linked, retail):
        """Whether storage contains a symbolic pointer, independently of its use."""
        if linked in self.limports:
            return True
        if self.retail_sites is not None:
            i = bisect.bisect_left(self.retail_sites, retail)
            if i < len(self.retail_sites) and self.retail_sites[i] == retail:
                return True
        _, item = self.T(linked)
        if item and item[0] == 'unit':
            unit = self.units[item[1]]
            obj = self.objs.get(Path(unit['obj']))
            sec, offset = obj[0][unit['sec'] - 1], linked - unit['linked']
        else:
            sym = self.sym_at(linked)
            found = self.objs.lookup(sym[2], sym[1]) if sym else None
            if not found or found[1].sec <= 0:
                return False
            obj, y = found
            sec, offset = obj[0][y.sec - 1], y.value + linked - sym[0]
        return any(site == offset and ty == DIR32 and obj[1].get(si) is not None
                   and obj[1][si].name not in ABSOLUTE for site, si, ty in sec.relocs)

    def argument_range(self, instructions, origin, lt, rt):
        """Known fixed API accesses, only for an unambiguous push/call window.

        This is a consumer range, never a retail sizeof assertion. In particular
        CoCreateInstance reads two 16-byte GUIDs; inventory padding is irrelevant
        (BFME1 data_rows.py:443). No register/index value is evaluated here.
        """
        x = capstone.x86
        ordered = sorted(instructions, key=lambda ins: ins.address)
        pos = next(i for i, ins in enumerate(ordered) if ins is origin)
        after, pushes = [], 0
        end = origin.address + origin.size
        for ins in ordered[pos + 1:]:
            if ins.address != end:
                return []
            after.append(ins)
            end += ins.size
            if ins.mnemonic == 'call':
                break
            if ins.mnemonic.startswith(('j', 'loop', 'ret')) or ins.mnemonic in ('pop', 'enter', 'leave'):
                return []
            if ins.mnemonic == 'push':
                pushes += 1
            else:
                _, writes = ins.regs_access()
                if any(_CSD.reg_name(n) == 'esp' for n in writes) or any(
                        op.type == x.X86_OP_MEM and op.access & capstone.CS_AC_WRITE
                        and _CSD.reg_name(op.mem.base) == 'esp' for op in ins.operands):
                    return []
        if not after or after[-1].mnemonic != 'call':
            return []
        # An alternate entry after the push destroys argument position proof.
        if any(ins.mnemonic.startswith(('j', 'loop')) and ins.operands
               and ins.operands[0].type == x.X86_OP_IMM
               and origin.address < ins.operands[0].imm < end for ins in ordered):
            return []
        call = after[-1]
        op = call.operands[0]
        if op.type == x.X86_OP_MEM and not op.mem.base and not op.mem.index:
            imported = self.limports.get(op.mem.disp - self.lbase)
            if imported == ('ole32.dll', 'CoCreateInstance') and pushes in (0, 3):
                return [(lt, rt, 16, False)]
            if imported == ('msvcr71.dll', 'puts') and pushes == 0:
                # BFME1 body_guard.py:145: puts consumes through the literal's
                # NUL, with no post-NUL padding or later stack lifetime.
                nul = bytes(self.R).find(b'\0', rt, rt + 65536)
                if nul >= rt:
                    return [(lt, rt, nul + 1 - rt, False)]
        elif op.type == x.X86_OP_IMM:
            target = op.imm - self.lbase
            sym = self.sym_at(target)
            if sym and sym[0] == target and sym[1] == '_bfmeAppend' and pushes == 1:
                # BFME1 body_guard._static_content's literal rule: a format
                # consumer observes through NUL, not alignment after it.
                nul = bytes(self.R).find(b'\0', rt, rt + 65536)
                if nul >= rt:
                    return [(lt, rt, nul + 1 - rt, False)]
        return []

    def callee_pops(self, instructions, o, sec, off, L):
        """Stack cleanup proved by BFME1 ABI evidence or callee decoration."""
        import callee_protos
        x = capstone.x86
        relocations = {site: o[1].get(si) for site, si, ty in sec.relocs if ty in (DIR32, REL32)}
        result = {}
        for ins in instructions:
            if ins.mnemonic != 'call' or not ins.operands:
                continue
            op = ins.operands[0]
            if op.type == x.X86_OP_IMM:
                target, operand = op.imm - self.lbase, ins.imm_offset
                retail = self.translate(target)
                if retail is not None:
                    evidence = callee_protos.load().get(self.ilt_body(retail), {})
                    rets = evidence.get('ret_bytes', '').split()
                    if len(rets) == 1 and rets[0].isdigit():
                        result[ins.address] = int(rets[0])
            elif op.type == x.X86_OP_MEM and not op.mem.base and not op.mem.index:
                target, operand = op.mem.disp - self.lbase, ins.disp_offset
                if target not in self.limports:
                    continue
            else:
                continue  # register-indirect calls establish no callee ABI
            symbol = relocations.get(off + ins.address - self.lbase - L + operand)
            names = [symbol.name] if symbol else []
            names += [name for name, _ in self.syms_at(target)]
            pops = set()
            for name in names:
                decorated = re.fullmatch(r'(?:__imp_)?_[^@]+@(\d+)', name)
                if decorated:
                    pops.add(int(decorated[1]))
                elif name.startswith('?'):
                    declared = callee_protos.declared(name)
                    if declared and declared[0] in ('__stdcall', '__thiscall'):
                        pops.add(4 * declared[1])
            if ins.address in result:
                pops.add(result[ins.address])
            if len(pops) == 1 and 0 <= next(iter(pops)) <= 65535 and next(iter(pops)) % 4 == 0:
                result[ins.address] = pops.pop()
            else:
                result.pop(ins.address, None)
        return result

    def bounded_byte_map(self, instructions, ins, L, rva, size, o, secno, off):
        """Only cmp/ja; movzx byte-map; jmp dword-table, with no bypass entry.

        The complete map and every selected slot must belong to verified code
        storage. Slot identities use BFME1 body_guard's same-section rule.
        """
        import body_guard
        x = capstone.x86
        ordered = sorted(instructions, key=lambda i: i.address)
        n = next((n for n, i in enumerate(ordered) if i.address == ins.address), -1)
        if n < 2 or n + 1 >= len(ordered):
            return None
        cmp, branch, load, jump = ordered[n-2:n+2]
        if (cmp.mnemonic != 'cmp' or branch.mnemonic != 'ja' or load.mnemonic != 'movzx'
                or jump.mnemonic != 'jmp' or any(a.address + a.size != b.address
                    for a, b in zip((cmp, branch, load), (branch, load, jump)))
                or len(cmp.operands) != 2 or len(load.operands) != 2 or len(jump.operands) != 1):
            return None
        index, bound = cmp.operands
        dest, byte = load.operands
        table = jump.operands[0]
        if (index.type != x.X86_OP_REG or index.size != 4 or bound.type != x.X86_OP_IMM
                or not 0 <= bound.imm < size or dest.type != x.X86_OP_REG or dest.size != 4
                or byte.type != x.X86_OP_MEM or byte.size != 1
                or byte.mem.base != index.reg or byte.mem.index
                or table.type != x.X86_OP_MEM or table.size != 4 or table.mem.base
                or table.mem.index != dest.reg or table.mem.scale != 4):
            return None
        lo, hi = cmp.address, jump.address + jump.size
        if any(lo < self.lbase + L + entry < hi for entry in self.code_entries[L]):
            return None
        if any(i.operands and i.operands[0].type == x.X86_OP_IMM
               and (i.mnemonic == 'call' or i.mnemonic.startswith(('j', 'loop')))
               and lo < i.operands[0].imm < hi for i in instructions):
            return None
        start, slots = byte.mem.disp - self.lbase, table.mem.disp - self.lbase
        count = bound.imm + 1
        if not L <= start < start + count <= L + size:
            return None
        values = bytes(self.I[start:start+count])
        if values != bytes(self.R[rva+start-L:rva+start-L+count]):
            return None
        end = slots + 4 * (max(values) + 1)
        if not L <= slots < end <= L + size or max(slots, start) < min(end, start + count):
            return None
        sec, syms, raw = o[0][secno - 1], o[1], o[2]
        relocations = {site: (syms.get(si), ty) for site, si, ty in sec.relocs}
        # Both storage bases must be compiler-local same-section relocations.
        for instruction, address in ((load, start), (jump, slots)):
            site = off + instruction.address - self.lbase - L + instruction.disp_offset
            symbol, ty = relocations.get(site, (None, None))
            if (ty != DIR32 or symbol is None or symbol.sec != secno or symbol.cls != STATIC
                    or not symbol.name.startswith('$') or address != L + symbol.value - off + u32(raw, sec.ptr + site)):
                return None
        for at in range(slots, end, 4):
            site = off + at - L
            symbol, ty = relocations.get(site, (None, None))
            if ty != DIR32 or symbol is None or symbol.sec != secno or not symbol.name.startswith('$'):
                return None
            addend = u32(raw, sec.ptr + site)
            target = self.lbase + L + symbol.value - off + addend
            expected = body_guard.ltable_address(rva, off, symbol.value, addend, self.rbase)
            if (u32(self.I, at) != target or u32(self.R, rva + at - L) != expected
                    or not self.lbase + L <= target < self.lbase + min(start, slots)
                    or lo < target < hi):
                return None
        return count

    def address_uses(self, instructions, origin, register, lt, rt, indexed=False, opaque=False, callee_pops=None):
        """Conservative register provenance, not execution or index evaluation.

        Walk the reachable CFG with address tags and constant displacements.
        Ambiguous joins/loops lose provenance and fail closed. Registers used
        as indices remain unknown; no symbolic/numeric equivalence is inferred.
        """
        x = capstone.x86
        def reg(n):
            name = _CSD.reg_name(n)
            for family in (('eax', 'ax', 'al', 'ah'), ('ebx', 'bx', 'bl', 'bh'),
                           ('ecx', 'cx', 'cl', 'ch'), ('edx', 'dx', 'dl', 'dh'),
                           ('esi', 'si'), ('edi', 'di'), ('ebp', 'bp'), ('esp', 'sp')):
                if name in family:
                    return family[0]
            return name

        by_address = {i.address: i for i in instructions}
        def register_mask(n):
            name = _CSD.reg_name(n)
            if name in ('ah', 'bh', 'ch', 'dh'):
                return 2
            if name in ('al', 'bl', 'cl', 'dl'):
                return 1
            if name in ('ax', 'bx', 'cx', 'dx', 'si', 'di', 'bp', 'sp'):
                return 3
            return 15

        def partial_bits_read(origin, written):
            """Ordinary register liveness, without evaluating instruction values.

            A partial overwrite need not observe the old address. Refuse only
            if its remaining representation bytes reach a read/unknown flow.
            """
            target = reg(written)
            pending = [(origin.address + origin.size, 15 & ~register_mask(written))]
            visited = {}
            while pending:
                at, mask = pending.pop()
                if not mask or mask & ~visited.get(at, 0) == 0:
                    continue
                mask |= visited.get(at, 0)
                visited[at] = mask
                ins = by_address.get(at)
                if ins is None:
                    return True
                reads, writes = ins.regs_access()
                if any(reg(n) == target and register_mask(n) & mask for n in reads):
                    return True
                if ins.mnemonic.startswith(('ret', 'iret')):
                    if target == 'eax':
                        return True
                    continue
                if ins.mnemonic == 'call' and target in ('eax', 'ecx', 'edx'):
                    return True  # caller-clobbered register/argument flow is unknown
                for n in writes:
                    if reg(n) == target:
                        mask &= ~register_mask(n)
                if ins.mnemonic in ('int3', 'ud2', 'hlt'):
                    continue
                if ins.mnemonic.startswith(('j', 'loop')):
                    if not ins.operands or ins.operands[0].type != x.X86_OP_IMM:
                        return bool(mask)
                    pending.append((ins.operands[0].imm, mask))
                    if ins.mnemonic == 'jmp':
                        continue
                pending.append((at + ins.size, mask))
            return False

        work = [(origin.address + origin.size, {register if isinstance(register, str) else reg(register): (None if opaque else 0, indexed)})]
        seen, uses, escapes, bad = {}, set(), False, False
        while work:
            at, state = work.pop()
            if not state:
                continue
            previous = seen.get(at)
            if previous is not None:
                if {n for n in previous if n.startswith('stack:')} != {n for n in state if n.startswith('stack:')}:
                    # docs/matching.md: an inconsistent stack frame at a join
                    # loses the storage provenance; never grow guessed aliases.
                    bad = True
                    continue
                if any(previous[n] != tag for n, tag in state.items() if n in previous):
                    # BFME1 docs/matching.md requires proven target/content;
                    # conflicting address offsets at a join lose that proof.
                    bad = True
                    continue
                joined = dict(previous)
                joined.update(state)
                if joined == previous:
                    continue
                state = joined
            if len(state) > 4 * len(instructions):
                # docs/matching.md: unbounded/unknown stack flow establishes
                # no consumed range. Refuse rather than execute the loop.
                bad = True
                continue
            # A tag absent on another path is unrelated to this origin, not a
            # conflicting pointer value. Keep may-address tags monotonically;
            # overwritten registers are removed using Capstone's write set.
            seen[at] = dict(state)
            ins = by_address.get(at)
            if ins is None:
                escapes = True
                continue
            ops, mn = ins.operands, ins.mnemonic
            memory_regs, used_regs = set(), set()
            for op in ops:
                if op.type == x.X86_OP_MEM:
                    tags = [(reg(n), state[reg(n)], scale) for n, scale in
                            ((op.mem.base, 1), (op.mem.index, op.mem.scale)) if n and reg(n) in state]
                    memory_regs.update(t[0] for t in tags)
                    if not tags or mn == 'lea':
                        continue
                    if len(tags) != 1 or tags[0][2] != 1:
                        # docs/matching.md permits symbolic addresses, not
                        # multiplication/addition of two relocated addresses.
                        bad = True
                        continue
                    name, (delta, indexed), _ = tags[0]
                    if delta is None:
                        # BFME1 docs/matching.md requires a proven target and
                        # range; a loaded pointer's unknown flow proves neither.
                        bad = True
                        continue
                    other = [n for n in (op.mem.base, op.mem.index) if n and reg(n) != name]
                    indexed |= bool(other) or mn in ('bt', 'bts', 'btr', 'btc') and len(ops) > 1 and ops[1].type == x.X86_OP_REG
                    indexed |= mn.startswith(('rep', 'lods', 'stos', 'movs', 'scas', 'cmps'))
                    uses.add((lt + delta + op.mem.disp, rt + delta + op.mem.disp, op.size, indexed))
                elif (op.type == x.X86_OP_REG and op.access & capstone.CS_AC_READ
                      and reg(op.reg) in state):
                    used_regs.add(reg(op.reg))
            reads, writes = ins.regs_access()
            for op in ops:
                if op.type == x.X86_OP_MEM and reg(op.mem.base) == 'esp' and not op.mem.index:
                    for name in state:
                        if not name.startswith('stack:'):
                            continue
                        slot = int(name[6:])
                        if op.mem.disp < slot + 4 and slot < op.mem.disp + op.size and (
                                (op.mem.disp, op.size) != (slot, 4) or mn == 'lea'):
                            # BFME1 docs/matching.md permits whole pointer
                            # copies, not partial representation reads/writes
                            # or untracked aliases of copied pointer storage.
                            bad = True
            if any(op.type == x.X86_OP_REG and op.access & capstone.CS_AC_WRITE
                   and op.size < 4 and reg(op.reg) in state and partial_bits_read(ins, op.reg) for op in ops):
                # docs/matching.md permits whole symbolic pointer words;
                # reading address bytes left by a partial overwrite does not
                # preserve that exception. Dead overwritten bytes observe none.
                bad = True
            read_tags = {reg(n) for n in reads if reg(n) in state}
            # Implicit string operands are exposed by Capstone as memory;
            # anything else implicit has an unknown observation/flow.
            implicit = read_tags - memory_regs - used_regs
            if implicit and not mn.startswith('ret'):
                # docs/matching.md: unproved symbolic address observations
                # cannot receive relocation equivalence credit.
                bad = True
            new = dict(state)
            for n in writes:
                new.pop(reg(n), None)
            if mn.startswith(('rep', 'lods', 'stos', 'movs', 'scas', 'cmps')):
                for n in writes:
                    name = reg(n)
                    if name in state and name in memory_regs:
                        # BFME1 matching.md requires subsequent storage ranges
                        # too. Implicit string advancement has unknown offset;
                        # keep its provenance opaque instead of dropping it.
                        new[name] = (None, False)
            def stack_slot(op):
                if op.type == x.X86_OP_MEM and reg(op.mem.base) == 'esp' and not op.mem.index:
                    return 'stack:' + str(op.mem.disp)
                return None
            if mn == 'mov' and len(ops) == 2 and stack_slot(ops[1]) in state:
                if ops[0].type == x.X86_OP_REG and ops[0].size == ops[1].size == 4:
                    new[reg(ops[0].reg)] = state[stack_slot(ops[1])]
                else:
                    # docs/matching.md only permits whole pointer copies.
                    bad = True
            elif mn == 'mov' and len(ops) == 2 and ops[1].type == x.X86_OP_REG and reg(ops[1].reg) in state:
                tag = state[reg(ops[1].reg)]
                if ops[0].type == x.X86_OP_REG and ops[0].size == ops[1].size == 4:
                    new[reg(ops[0].reg)] = tag
                elif stack_slot(ops[0]) and ops[0].size == 4:
                    new[stack_slot(ops[0])] = tag
                elif ops[0].type == x.X86_OP_MEM and ops[0].size == 4:
                    # docs/matching.md symbolic pointers need a pointer context;
                    # an untyped destination cannot prove numeric preservation.
                    bad = True
                else:
                    # BFME1 matching.md's whole symbolic dword exception
                    # does not cover a truncated/non-pointer representation.
                    bad = True
            elif mn == 'lea' and len(ops) == 2 and ops[1].type == x.X86_OP_MEM:
                mem = ops[1].mem
                tags = [(reg(n), state[reg(n)], scale) for n, scale in
                        ((mem.base, 1), (mem.index, mem.scale)) if n and reg(n) in state]
                if tags:
                    if len(tags) != 1 or tags[0][2] != 1:
                        # BFME1 matching.md symbolic target consistency does
                        # not prove numeric address multiplication.
                        bad = True
                    else:
                        name, (delta, indexed), _ = tags[0]
                        if delta is None:
                            # docs/matching.md: unknown pointer flow is not
                            # evidence for numeric address arithmetic.
                            bad = True
                            continue
                        other = any(n and reg(n) != name for n in (mem.base, mem.index))
                        new[reg(ops[0].reg)] = (delta + mem.disp, indexed or other)
            elif mn in ('add', 'sub', 'inc', 'dec') and ops and ops[0].type == x.X86_OP_REG and reg(ops[0].reg) in state:
                name = reg(ops[0].reg)
                delta, indexed = state[name]
                if delta is None:
                    # docs/matching.md: numeric use of a loaded pointer has
                    # no value-equivalence proof; refuse rather than execute it.
                    bad = True
                    continue
                if mn in ('inc', 'dec'):
                    delta += 1 if mn == 'inc' else -1
                elif ops[1].type == x.X86_OP_IMM:
                    delta += ops[1].imm * (1 if mn == 'add' else -1)
                elif mn == 'add' and ops[1].type == x.X86_OP_REG and reg(ops[1].reg) not in state:
                    indexed = True
                else:
                    # docs/matching.md proves pointer rebasing only, not
                    # arbitrary arithmetic on relocated addresses.
                    bad = True
                new[name] = (delta, indexed)
            elif mn == 'push' and used_regs:
                pass  # Keep the whole pointer in its fixed stack slot below.
            elif mn == 'pop' and ops and ops[0].type == x.X86_OP_REG and 'stack:0' in state:
                new[reg(ops[0].reg)] = state['stack:0']
                new.pop('stack:0', None)
            elif mn.startswith('ret'):
                escapes |= 'eax' in state and state['eax'][0] is not None  # returned original address
                if 'eax' in state and state['eax'][0] not in (0, None):
                    # docs/matching.md only permits constant/index address
                    # adjustment for a proven memory use, not numeric returns.
                    bad = True
            elif used_regs and not (mn in ('mov', 'movzx', 'movsx') and len(ops) > 1 and ops[1].type == x.X86_OP_MEM
                                    and not any(n in used_regs for n in read_tags - memory_regs)):
                if mn not in ('call', 'jmp'):
                    # docs/matching.md's symbolic DIR32 exception does not
                    # preserve and/or/xor/shift/integer compare/multiply.
                    bad = True
                else:
                    escapes = True
            if (mn == 'mov' and len(ops) == 2 and ops[0].type == x.X86_OP_REG
                    and ops[1].type == x.X86_OP_MEM and ops[1].size == 4):
                mem = ops[1].mem
                tag = state.get(reg(mem.base)) if mem.base and not mem.index else None
                if tag and tag[0] is not None and not tag[1] and self.pointer_word(
                        lt + tag[0] + mem.disp, rt + tag[0] + mem.disp):
                    new[reg(ops[0].reg)] = (None, False)
            if mn == 'call':
                escapes |= bool(read_tags) or any(n.startswith('stack:') for n in state)
                # We cannot follow an unknown callee's register effects.
                for n in ('eax', 'ecx', 'edx'):
                    new.pop(n, None)
                popped = (callee_pops or {}).get(ins.address, 0)
                # The callee discards these arguments. Rebase surviving locals
                # before a branch join or a later load can reuse their tags.
                if popped:
                    new = {('stack:' + str(int(n[6:]) - popped) if n.startswith('stack:') else n): tag
                           for n, tag in new.items() if not n.startswith('stack:') or int(n[6:]) + 4 > popped}
            if mn == 'mov' and len(ops) == 2 and stack_slot(ops[0]) and not (
                    ops[1].type == x.X86_OP_REG and reg(ops[1].reg) in state):
                new.pop(stack_slot(ops[0]), None)
            stack_change = 4 if mn == 'push' else -4 if mn == 'pop' else 0
            if mn in ('add', 'sub') and len(ops) == 2 and ops[0].type == x.X86_OP_REG and reg(ops[0].reg) == 'esp':
                if ops[1].type == x.X86_OP_IMM:
                    stack_change = ops[1].imm * (-1 if mn == 'add' else 1)
                elif any(n.startswith('stack:') for n in state):
                    # BFME1 target/content rule: unknown stack flow loses
                    # the address provenance required for subsequent loads.
                    bad = True
            if stack_change:
                new = {('stack:' + str(int(n[6:]) + stack_change) if n.startswith('stack:') else n): tag
                       for n, tag in new.items()}
            if mn == 'push':
                new.pop('stack:0', None)  # the push overwrites the complete word
                if ops and ops[0].type == x.X86_OP_REG and reg(ops[0].reg) in state:
                    new['stack:0'] = state[reg(ops[0].reg)]
            if mn.startswith(('ret', 'iret')) or mn in ('int3', 'ud2', 'hlt'):
                continue
            if mn.startswith(('j', 'loop')):
                if ops and ops[0].type == x.X86_OP_IMM:
                    work.append((ops[0].imm, new))
                elif new:
                    escapes = True
                if mn == 'jmp':
                    continue
            work.append((at + ins.size, new))
        return sorted(uses), escapes, bad

    def relocs(self, L, rva, size, o, secno, off, owner, failures=None):
        """Check every relocation of [off, off+size) of section `secno` of object o
        linked at L against retail at rva. Returns (failures, edges, masked
        offsets, data references [(lt, rt, target name, Sym, object, addend,
        access)], relocations [(offset, type, absolute?)] for the shifted check)."""
        I, R = self.I, self.R
        secs, syms, raw = o
        sec = secs[secno - 1]
        if not (0 <= off <= off + size <= sec.size and 0 <= L <= L + size <= len(I)
                and 0 <= rva <= rva + size <= len(R)):
            return ["code-extent"], set(), set(), [], []
        got, want = I[L:L + size], R[rva:rva + size]
        fails, edges, masked, data, rels = failures if failures is not None else [], set(), set(), [], []
        instructions, decoded, fallthrough = code_flow(got, L + self.lbase, self.code_entries[L])
        pops = self.callee_pops(instructions, o, sec, off, L)
        def address_uses(*args, **kwargs):
            return self.address_uses(*args, **kwargs, callee_pops=pops)
        # Internal direct branches are already traversed here; only entries
        # discovered outside this traversal need to schedule another pass.
        direct_calls = {ins.address - L - self.lbase + ins.imm_offset for ins in instructions
                        if ins.mnemonic == "call" and ins.operands
                        and ins.operands[0].type == capstone.x86.X86_OP_IMM}
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
            addend = u32(raw, sec.ptr + va) if sec.ptr else 0
            width, indexed, memory, pointer_words = 0, False, False, False
            for ins in instructions:
                if ty == DIR32 and ins.address - L - self.lbase + ins.disp_offset == fo and ins.mnemonic != "lea":
                    for operand in ins.operands:
                        if operand.type == capstone.x86.X86_OP_MEM:
                            memory = True
                            width = max(width, operand.size)
                            indexed |= bool(operand.mem.index or operand.mem.base)
                            pointer_words |= (ins.mnemonic in ("mov", "push", "jmp", "call") and operand.size == 4
                                              and not operand.mem.base and operand.mem.scale == 4)
                    if indexed and self.lsec(lt) == '.text':
                        bounded = self.bounded_byte_map(instructions, ins, L, rva, size, o, secno, off)
                        if bounded is not None:
                            width, indexed = bounded, False
                    # x86 bit strings use a register offset beyond the nominal
                    # operand width. BFME1's whole datum rule covers that use.
                    indexed |= ins.mnemonic in ("bt", "bts", "btr", "btc") and any(
                        op.type == capstone.x86.X86_OP_REG for op in ins.operands[1:])
            uses, escapes, numeric = [], False, False
            for ins in instructions:
                if (ty == DIR32 and ins.address - L - self.lbase + ins.imm_offset == fo
                        and ins.mnemonic == "push"):
                    uses = self.argument_range(instructions, ins, lt, rt)
                    if not uses:
                        uses, escapes, numeric = address_uses(instructions, ins, "stack:0", lt, rt)
                elif (ty == DIR32 and ins.address - L - self.lbase + ins.imm_offset == fo
                        and ins.mnemonic == "mov" and ins.operands[0].type == capstone.x86.X86_OP_REG):
                    uses, escapes, numeric = address_uses(instructions, ins, ins.operands[0].reg, lt, rt)
                    numeric |= ins.operands[0].size != 4
                elif (ty == DIR32 and ins.address - L - self.lbase + ins.imm_offset == fo
                      and ins.mnemonic == "add" and ins.operands[0].type == capstone.x86.X86_OP_REG):
                    uses, escapes, numeric = address_uses(instructions, ins, ins.operands[0].reg, lt, rt, indexed=True)
                elif (ty == DIR32 and ins.address - L - self.lbase + ins.disp_offset == fo
                      and ins.mnemonic == "lea" and ins.operands[0].type == capstone.x86.X86_OP_REG):
                    mem = ins.operands[1].mem
                    uses, escapes, numeric = address_uses(instructions, ins, ins.operands[0].reg, lt, rt,
                                                              indexed=bool(mem.base or mem.index))
                elif (ty == DIR32 and ins.address - L - self.lbase + ins.imm_offset == fo
                      and ins.mnemonic == "mov" and ins.operands[0].type == capstone.x86.X86_OP_MEM):
                    mem = ins.operands[0].mem
                    if _CSD.reg_name(mem.base) == "esp" and not mem.index:
                        uses, escapes, numeric = address_uses(instructions, ins, "stack:" + str(mem.disp), lt, rt)
                    else:
                        # docs/matching.md requires a known pointer context,
                        # not an arbitrary integer destination for an address.
                        numeric = True
                elif ty == DIR32 and ins.address - L - self.lbase + ins.imm_offset == fo:
                    # BFME1 symbolic DIR32 permission does not cover integer
                    # arithmetic/compare using a relocated immediate operand.
                    numeric = True
            if memory and width == 4:
                d = self.datum(lt, tn, y, o, addend) if lt not in self.limports else None
                symbolic = self.pointer_word(lt, rt) if not indexed else bool(d and d[4] is not None and any(
                    d[5] <= site < d[5] + d[1] and ty == DIR32 for site, _, ty in d[4].relocs))
                if symbolic:
                    for ins in instructions:
                        if ins.address - L - self.lbase + ins.disp_offset != fo:
                            continue
                        if ins.mnemonic not in ("mov", "push", "call", "jmp"):
                            # BFME1 docs/matching.md rebases symbolic pointers;
                            # integer operations directly on their storage do
                            # not preserve the values those operations observe.
                            numeric = True
                        elif ins.mnemonic == "mov" and ins.operands[0].type == capstone.x86.X86_OP_REG:
                            a, b = (u32(I, lt) - self.lbase, u32(R, rt) - self.rbase) if not indexed else (0, 0)
                            pointer_uses, lost, bad = address_uses(instructions, ins, ins.operands[0].reg,
                                                                      a, b, opaque=indexed)
                            numeric |= bad
                            if not indexed and self.lsec(a) == ".text":
                                for aa, bb, z, unknown in pointer_uses:
                                    f, ee = self.storage_ref(aa, bb, z, tn, indexed=unknown)
                                    if f:
                                        fails.append(f)
                                    edges.update(ee)
                                if lost and pointer_uses:
                                    # docs/matching.md target content must
                                    # cover the entire reached storage use.
                                    fails.append(f"code-address-flow-unknown:{tn}")
            if numeric:
                # BFME1 docs/matching.md permits symbolic target rebasing;
                # numeric observations require byte/value equality, not identity.
                fails.append(f"address-numeric-use:{tn}")
            if self.ltext[0] <= lt < self.ltext[0] + self.ltext[1]:
                if uses:
                    for a, b, z, unknown in uses:
                        f, storage_edges = self.storage_ref(a, b, z, tn, indexed=unknown)
                        if f:
                            fails.append(f)
                        edges.update(storage_edges)
                if escapes and uses:
                    # docs/matching.md requires all consumed .text bytes;
                    # an escaped address has no fully established access range.
                    fails.append(f"code-address-flow-unknown:{tn}")
                if memory:
                    if y is not None and y.sec == secno:
                        import body_guard
                        # Reuse BFME1's ltable rule, including storage bases.
                        expected = body_guard.ltable_address(rva, off, y.value, addend, self.rbase)
                        if rv != expected:
                            fails.append(f"code-storage-ltable:{tn}")
                    if (y is not None and y.sec == secno and y.cls == STATIC and tn.startswith("$")
                            and (self.T(lt)[1] is None or self.T(lt)[1][0] == "fill")):
                        # body_guard's same-section ltable/tail rule also
                        # permits storage after the ledger's code extent. Its
                        # complete symbol extent is a datum: content, shifted
                        # words and every stored code destination are checked
                        # by the existing data traversal, never by decoding it.
                        data.append((lt, rt, tn, y, o, addend, "addr", width, indexed, ([], False), pointer_words))
                    else:
                        f, storage_edges = self.storage_ref(lt, rt, width, tn, indexed=indexed, pointer_words=pointer_words)
                        if f:
                            fails.append(f)
                        edges.update(storage_edges)
                else:
                    direct = ty == REL32 and fo in direct_calls
                    f, e = self.code_ref(lt, rt, tn, owner, direct=direct, pointer=ty == DIR32, fails=fails,
                                         entry=not direct or not L <= lt < L + size)
                    if f:
                        fails.append(f)
                    elif e:
                        edges.add(e)
            else:
                access = "read" if ty == DIR32 and read_through(got, fo) and read_through(want, fo) else "addr"
                # docs/matching.md DIR32 consistency and body_guard's static
                # rule check the whole containing datum, also for addresses
                # carried in registers, string ops and unknown scaled indices.
                data.append((lt, rt, tn, y, o, addend, access, width, indexed, (uses, escapes), pointer_words))
        # docs/matching.md: DIR32 slots may differ only with symbolic
        # evidence. Retail HIGHLOW sites in code need that evidence too.
        if self.retail_sites is not None:
            symbolic = {fo for fo, ty, absolute in rels if ty == DIR32 and not absolute}
            for site in self.retail_sites[bisect.bisect_left(self.retail_sites, rva):
                                          bisect.bisect_left(self.retail_sites, rva + size)]:
                if site - rva not in symbolic:
                    fails.append("code-unrelocated-pointer")
        nd = nonreloc_diffs(got, want, masked)
        if nd:
            fails.append(f"bytes:{nd}")
        # Same-section and literal rel32 branches need no COFF relocation.
        # Their targets still belong to the source dependency closure.
        if _CSD is None:
            fails.append("code-decoder-missing")
        else:
            if not decoded:
                fails.append("code-decode-incomplete")
            if fallthrough:
                f, e = self.code_ref(L + size, rva + size, "fallthrough", owner, pointer=False, fails=fails)
                if f:
                    fails.append(f)
                elif e:
                    edges.add(e)
            for ins in instructions:
                if ins.mnemonic != "call" and not ins.mnemonic.startswith(("j", "loop")):
                    continue
                if not ins.operands or ins.operands[0].type != capstone.x86.X86_OP_IMM:
                    continue
                fo = ins.address - L - self.lbase + ins.imm_offset
                if any(k in masked for k in range(fo, fo + ins.imm_size)):
                    continue
                lt = ins.operands[0].imm - self.lbase
                rt = rva + (lt - L)  # identical unrelocated displacement
                f, e = self.code_ref(lt, rt, "direct-branch", owner, direct=ins.mnemonic == "call",
                                     pointer=False, fails=fails, entry=not L <= lt < L + size)
                if f:
                    fails.append(f)
                elif e:
                    edges.add(e)
        return fails, edges, masked, data, rels

    def ilt_body(self, rt):
        """The body a retail ILT thunk (or `?j_` row) at rt jumps to; rt itself otherwise."""
        for _ in range(3):
            if (0 <= rt <= len(self.R) - 5
                    and (ILT[0] <= rt < ILT[1] or rt in self.thunk_rows) and self.R[rt] == 0xE9):
                rt = (rt + 5 + struct.unpack_from("<i", self.R, rt + 1)[0]) & 0xFFFFFFFF
            else:
                break
        return rt

    def code_identity(self, lt, rt, *, pointer=False, fails=None):
        """Preserve observable pointer equality and inequality measurement-wide."""
        # BFME1 build_call_thunks/load_symbol_map permit multiple ILT call
        # routes. docs/matching.md's DIR32 consistency concerns taken addresses;
        # route-only calls must not constrain observable pointer identity.
        # Even direct calls cannot merge distinct retail bodies (AGENTS.md:
        # retail has no ICF). Only thunk routes to the same body are exempt.
        self.code_targets[lt].add(self.ilt_body(rt))
        if fails is not None:
            self.code_users[lt][id(fails)] = fails
        if not pointer:
            return
        self.code_pointers[lt].add(rt)
        self.pointer_links[rt].add(lt)
        if fails is not None:
            self.code_pointer_users[lt][id(fails)] = fails

    def code_collapses(self):
        bad = {lt for axis in (self.code_targets, self.code_pointers)
               for lt, targets in axis.items() if len(targets) > 1}
        for links in self.pointer_links.values():
            if len(links) > 1:
                bad.update(links)
        return bad

    def schedule_entry(self, lt):
        # BFME1's verified extents cover dependencies at every reached entry,
        # including switch/EH table pointers, not merely the nominal row start.
        i = bisect.bisect_right(self.istarts, lt) - 1
        if i >= 0 and self.items[i][0] <= lt < self.items[i][1] and self.items[i][3][0] == "unit":
            self.code_entries[self.items[i][0]].add(lt - self.items[i][0])

    def settle_code_identities(self):
        body_bad = {lt for lt, targets in self.code_targets.items() if len(targets) > 1}
        for lt in sorted(self.code_collapses()):
            # Pointer conflicts affect taken-address uses. BFME1 permits
            # direct call routes independently of observable pointer identity.
            users = dict(self.code_users[lt]) if lt in body_bad else {}
            users.update(self.code_pointer_users[lt])
            for fails in users.values():
                why = f"code-identity-collapse:0x{lt:08X}"
                if why not in fails:
                    fails.append(why)

    def code_ref(self, lt, rt, tn, owner, *, direct=False, pointer=True, fails=None, entry=True):
        tr, item = self.T(lt)
        if tr is not None:
            if entry:
                self.schedule_entry(lt)
            self.code_identity(lt, rt, pointer=pointer and not direct, fails=fails)
        if tr is not None and tr == rt:
            return None, item
        if tr is not None and self.ilt_body(rt) == tr:
            self.ilt_routes["call" if direct else "pointer"] += 1
            return None, item
        s = self.sym_at(lt)
        if s and s[0] == lt and s[1].startswith("__ehhandler$"):
            if s[1][len("__ehhandler$"):] != owner:
                self.eh["foreign thunk"] += 1
                return f"eh-foreign:{tn}", None
            node = self.eh_nodes.setdefault(s[0], {"fails": [], "edges": set(), "refs": []})

            def reference(la, ra, *, direct=False, data=False):
                if data:
                    sym = self.sym_at(la)
                    found = self.objs.lookup(sym[2], sym[1]) if sym else None
                    if not found:
                        return False
                    o, y = found
                    node["refs"].append((la, ra, sym[1], y, o, la - sym[0], "addr"))
                    return True
                # EH helper bodies need a verified provider, including all
                # of that provider's code/data dependencies and shifted bytes.
                tr, edge = self.T(la)
                if tr is not None:
                    self.schedule_entry(la)
                    self.code_identity(la, ra, pointer=not direct, fails=node["fails"])
                if tr is None or (tr != ra and self.ilt_body(ra) != tr):
                    return False
                node["edges"].add(edge)
                return True

            v = eh_verdict(self.I, s[0], self.R, rt - (lt - s[0]), self.lbase, self.rbase,
                           self.translate, reference)
            if v:
                node["fails"].append(v)
            self.eh[v or "verified"] += 1
            return (f"eh:{v}", None) if v else (None, ("eh", s[0]))
        # BFME1 retail has no ICF: equal bodies at distinct retail addresses
        # retain distinct identities, including when the provider is a dump.
        if tr is None:
            return f"code-unmapped:{tn}", None
        return f"code-wrong:{tn}", None

    def object_name(self, o):
        """Lower-case basename of a parsed object (the map's Lib:Object spelling)."""
        names = getattr(self, "_onames", None)
        if names is None or id(o) not in names:
            names = self._onames = {id(v): Path(p).name.lower() for p, v in self.objs.cache.items() if v}
            # zz objects retain the original map owner through by_base.
            owners = set(self.pubobj.values())
            for base, path in getattr(self.objs, "by_base", {}).items():
                obj = self.objs.cache.get(Path(path))
                if obj is not None and base in owners:
                    names[id(obj)] = base
        return names.get(id(o))

    def datum(self, lt, tn, y, o, addend):
        """The datum a data reference reaches, from the relocation's own target:
        (linked start of the datum, its size, offset of lt in it, defining object,
        section, section offset of the datum, linked address of the named symbol).
        A public the referencing object defines counts as its own only when the
        map says the link selected that object's copy.

        A signed DIR32 displacement does not change the named datum. For
        register/index uses we verify that datum in full; fixed accesses are
        checked separately against its bounds. Section-symbol relocations use
        their addend to identify the actual containing symbol."""
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
                size = self.communal(tn)
                return (S, size, lt - S, o, None, 0, S) if S <= lt < S + size else None
            if S is None or not found:
                return None
            o, ys = found
            sec, P, base = o[0][ys.sec - 1], ys.value + (lt - S), ys.value
        anchor = P if tn == sec.name else base
        if not 0 <= anchor < sec.size:
            return None
        vals = self.objs.defined(o)[1].get(sec.idx, [])
        i = bisect.bisect_right(vals, anchor) - 1
        v0 = vals[i] if i >= 0 else 0
        v1 = vals[i + 1] if i + 1 < len(vals) else sec.size
        if tn.startswith("$SG") and sec.ptr:
            # BFME1 body_guard.py:145 excludes post-NUL alignment padding.
            blob = o[2][sec.ptr + v0:sec.ptr + v1]
            nul = blob.find(b"\0", max(0, P - v0))
            if nul >= 0:
                v1 = v0 + nul + 1
            if v0 <= P < v1:
                v0 = P  # body_guard compares the suffix; S retains symbol identity
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

    def retail_datum_size(self, start, fallback, name):
        """Independent retail size; allocation/inventory partitions prove none.

        data_rows.symbol_size (tools/data_rows.py:443) makes allocation an
        upper bound only. Never promote the candidate's extent to retail size.
        """
        if not hasattr(self, "retail_ledger"):
            extents = {}
            ledger = ROOT / "targets/game/reverse/data_rows.csv"
            if ledger.exists():
                with ledger.open(newline="", encoding="utf-8") as stream:
                    for row in csv.DictReader(stream):
                        if row.get("status") == "matched":
                            address = int(row["address"], 16)
                            address -= self.rbase if row["address_kind"] == "va" else 0
                            extents[address] = int(row["size"])
            self.retail_ledger = extents
            self.retail_ledger_starts = sorted(extents)
        i = bisect.bisect_right(self.retail_ledger_starts, start) - 1
        if i >= 0:
            address = self.retail_ledger_starts[i]
            if address <= start < address + self.retail_ledger[address]:
                return self.retail_ledger[address] if address == start else None
        import reloc_ledger
        scalar = reloc_ledger.mangled_scalar_size(name)
        if scalar is not None:
            return scalar
        if name.startswith("??_C@"):
            try:
                return len(build.string_literal_bytes(name, memoryview(self.R)[start:]))
            except ValueError:
                # body_guard._static_content requires the complete literal.
                return None
        if name.startswith("$SG"):
            # body_guard.py:145: the literal ends at NUL, padding is exempt.
            nul = bytes(self.R).find(b"\0", start, start + fallback)
            return nul + 1 - start if nul >= start else None
        return None

    def datum_sources(self, o, name, rva):
        """Retain the defining TU even for failed, data-only providers."""
        if not hasattr(self, "provider_sources"):
            sources = self.provider_sources = collections.defaultdict(set)
            for unit in self.units:
                for row in unit["rows"]:
                    sources[Path(unit["obj"]).name.lower()].add(row["source"])
            rows = [row for unit in self.units for row in unit["rows"]]
            if ROOT == census.ROOT:
                # BFME1 admits whole data TUs, not only the anchor's symbol.
                for path, source in census._object_sources(rows).items():
                    sources[Path(path).name.lower()].add(source.relative_to(ROOT).as_posix())
            ledger = ROOT / "targets/game/reverse/data_rows.csv"
            if ledger.exists():
                with ledger.open(newline="", encoding="utf-8") as stream:
                    for row in csv.DictReader(stream):
                        if row.get("status") == "matched" and row.get("source"):
                            sources[("datum", row["name"])].add(row["source"])
                            if row["name"] in self.pubobj:
                                sources[self.pubobj[row["name"]]].add(row["source"])
        return sorted(self.provider_sources.get(self.object_name(o), set()) |
                      self.provider_sources.get(("datum", name), set()))

    def include_proofs(self, sources):
        """BFME1 build deps sidecars and census receipts witness include inputs."""
        proofs = {}
        for source in sources:
            if Path(source).suffix.lower() in progress.LIB_SUFFIXES:
                continue  # a prebuilt member has no TU include search
            path = build.row_object({"source": source})
            side = Path(path).with_suffix(".deps.json")
            if side.is_file():
                meta = json.loads(side.read_text(encoding="utf-8"))
                proofs[source] = {k: meta[k] for k in ("deps", "search_roots", "inventory") if k in meta}
            elif source in getattr(self, "compile_includes", {}):
                proofs[source] = self.compile_includes[source]
        return proofs

    def scan_datum(self, key, sec, value, name, o):
        """A datum node: its bytes against retail's (relocated words masked), code
        pointers translated through the unit or filler holding them, data pointers
        kept as references (judged once every reference is known)."""
        start, rstart, size = key
        node = {"name": name, "sources": self.datum_sources(o, name, rstart),
                "fails": [], "edges": set(), "refs": [], "rels": [], "masked": set()}
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
                f, item = self.code_ref(lt, rt, tn, "", fails=node["fails"])
                if f:
                    node["fails"].append(f"data-codeptr:{name}")
                else:
                    node["edges"].add(item)
            else:
                addend = u32(raw, sec.ptr + va) if sec.ptr else 0
                node["refs"].append((lt, rt, tn, y, o, addend, "addr"))
        if nonreloc_diffs(got, want, masked):
            node["fails"].append(f"data-content:{name}")
        # Retail's retained HIGHLOW list distinguishes pointers from numbers
        # and strings. Without that evidence, a possible image pointer fails
        # closed. Inspect unaligned words too (packed structs are valid).
        sites = self.retail_sites
        offsets = (range(max(0, size - 3)) if sites is None else
                   (v - rstart for v in sites[bisect.bisect_left(sites, rstart):
                                              bisect.bisect_left(sites, rstart + size)]))
        rsecs = getattr(self, "rsecs", self.isecs)
        relocated = {fo for fo, ty, _ in node["rels"] if ty == DIR32}
        for fo in offsets:
            if fo in relocated:
                continue
            if fo + 4 > size:
                node["fails"].append(f"data-pointer-straddle:{name}")
                break
            lv, rv = u32(got, fo), u32(want, fo)
            ra = rv - self.rbase
            rinside = (rsecs.name_at(ra) != "outside" if hasattr(rsecs, "name_at") else
                       any(a <= ra < a + z for a, z in rsecs.values()))
            if (sites is not None or self.lsec(lv - self.lbase) != "outside" or rinside):
                node["fails"].append(f"data-unrelocated-pointer:{name}")
                break
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
                start, rstart, _ = r[1]
                # Interior references must agree on the identity and offset
                # of the whole datum, not merely on each accessed address.
                self.fwd[start].add(rstart)
                self.back[rstart].add(start)
                if ref[2].startswith('$SG'):
                    symbol, retail_symbol = r[2], ref[1] - (ref[0] - r[2])
                    self.fwd[symbol].add(retail_symbol)
                    self.back[retail_symbol].add(symbol)
                node = self.dnodes[r[1]]
                if not node.get("seen"):
                    node["seen"] = True
                    work.extend(node["refs"])
        # Overlapping extents must preserve the same displacement in both
        # directions; otherwise distinct storage has been merged or split.
        for axis in (0, 1):
            group, end, deltas = [], -1, set()
            for key in sorted(self.dnodes, key=lambda k: k[axis]):
                if key[axis] >= end:
                    if len(deltas) > 1:
                        self.datum_conflicts.update(group)
                    group, end, deltas = [], -1, set()
                group.append(key)
                end = max(end, key[axis] + key[2])
                deltas.add(key[1] - key[0])
            if len(deltas) > 1:
                self.datum_conflicts.update(group)

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
            # BFME1's import equivalence proves one 32-bit IAT slot, not
            # adjacent slots or a range selected by an unbounded index.
            if len(ref) > 7 and (ref[7] > 4 or ref[8]):
                fails.append(f"data-access-extent:{tn}")
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
        start, rstart, size = kind[1]
        if tn.startswith('$SG') and S != start:
            fails += self.one_to_one(S, rt - (lt - S), tn)
        width = ref[7] if len(ref) > 7 else 0
        indexed = ref[8] if len(ref) > 8 else False
        # BFME1 data_rows.py:443: allocation only bounds size. Fixed
        # accesses may use verified bytes; unknown ranges need retail evidence.
        required = self.retail_datum_size(rstart, size, tn)
        uses, escapes = ref[9] if len(ref) > 9 else ([], not width or indexed)
        if width:
            uses = [(lt, rt, width, indexed)] + uses
        if not width and not uses:
            escapes = True
        if ((escapes or any(u[3] for u in uses)) and
                (required is None or required > size)) or any(
                not u[3] and not 0 <= u[0] - start <= size - u[2] for u in uses):
            # docs/matching.md target content rule; an unproven retail domain
            # cannot be supplied by a candidate allocation or inventory gap.
            fails.append(f"data-access-extent:{tn}")
        node = self.dnodes[kind[1]]
        for a, _, z, unknown in uses:
            for fo, ty, absolute in node["rels"]:
                if not absolute and (unknown or a < start + fo + 4 and start + fo < a + z):
                    if (unknown or (a, z) != (start + fo, 4)) and not (
                            unknown and len(ref) > 10 and ref[10] and z == 4 and (start + fo - a) % 4 == 0):
                        # docs/matching.md permits symbolic whole DIR32 words,
                        # not observations of their rebased representation.
                        fails.append(f"data-raw-relocation:{tn}")
                        break
        fails += self.one_to_one(start, rstart, tn) if (start, rstart) != (lt, rt) else []
        if kind[1] in self.datum_conflicts:
            fails.append(f"data-identity:{tn}")
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
                rec["scanned_entries"] = frozenset(self.code_entries[L])
                f, e, m, data, rels = self.relocs(L, r["rva"], r["size"], o, u["sec"], r["off"], r["sym"])
                rec["fails"], rec["edges"], rec["masked"], rec["rels"] = f, e, m, rels
                for ref in data:
                    self.pending.append((rec, ref))
        self.collect_twins()
        scanned = {id(rec): rec.get("scanned_entries", frozenset({0})) for rec in out}
        while True:
            self.discover([ref for _, ref in self.pending] + [ref for b in self.twin_body.values() for ref in b[2]]
                          + [ref for node in self.eh_nodes.values() for ref in node["refs"]])
            changed = False
            for rec in out:
                if not rec["measured"]:
                    continue
                L, r, u = rec["linked"], rec["row"], rec["unit"]
                entries = frozenset(self.code_entries[L])
                if entries == scanned[id(rec)]:
                    continue
                scanned[id(rec)] = entries
                changed = True
                f, e, mask, data, rels = self.relocs(L, r["rva"], r["size"], self.objs.get(u["obj"]),
                                                   u["sec"], r["off"], r["sym"], failures=rec["fails"])
                # Register the same failure list on every traversal, so late
                # identity conflicts invalidate all uses before closure.
                rec["edges"].update(e)
                rec["masked"].update(mask)
                for ref in data:
                    self.pending.append((rec, ref))
            if not changed:
                break
        self.settle_code_identities()
        self.judge_datums()
        for node in self.eh_nodes.values():
            for ref in node["refs"]:
                f, e, _ = self.ref_with_datum(ref)
                node["fails"] += f
                node["edges"] |= e
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
        """Retain rejected diagnostics; BFME1 never grants ICF twin credit."""
        self.twins = {key: (False, "bfme1-no-icf") for key in self.twins}
        self.twin_edges = {}

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
    return subprocess.run(["git", *args], capture_output=True, text=True, cwd=cwd or ROOT, check=True).stdout.strip()


def tool_digest():
    return context.digest(context.tool_dependencies(ROOT, __file__))


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


CANON_RULES = "coff-canon-1"
ANON_NS = re.compile(rb"\?A0x[0-9a-f]{8}")
ANON_CANON = b"?A0x########"
ASSOCIATIVE = 5


def canonical_identity(o):
    """object_identity up to what two compiles of one TU in two trees may vary in
    (VC7.1: research lc-repro-bfme2), and nothing else:
      - the anonymous namespace's hash `?A0x<8 hex>` (it follows the path or the
        compile). Renamed only when the object holds exactly one such hash, in
        names and section bytes alike; an object holding two keeps them raw;
      - section numbering: a section is named by what the linker binds it by: a
        COMDAT by its leader symbol (adjustor thunks come out permuted), an
        associative COMDAT by its parent, any other by its name and its rank
        among same-named sections (their relative order is kept: it is link order);
      - symbol table order: a relocation names its target (a section by that key,
        a symbol by name, class and definition), not its table index, and the
        relocations of a section are sorted by site.
    Everything else is bound: every section's flags, size, bytes and relocation
    (site, type, target), the COMDAT selection and parent, and every symbol's
    name, value, section, type and class, a weak external's default. The time
    stamp and debug records stay out, as in object_identity."""
    secs, syms, raw = o
    symptr = struct.unpack_from("<I", raw, 8)[0]
    live = [s for s in secs if not s.name.startswith(".debug$")]
    found = set(ANON_NS.findall("\0".join(y.name for y in syms.values()).encode("latin-1")))
    for s in live:
        if s.ptr:
            found.update(ANON_NS.findall(raw[s.ptr:s.ptr + s.size]))
    anon = found.pop() if len(found) == 1 else None

    def rn(name):
        return name.replace(anon.decode(), ANON_CANON.decode()) if anon else name

    def aux(i):
        o = symptr + 18 * i
        return raw[o + 18:o + 18 + 18 * raw[o + 17]]
    secdef, leader, sel, parent = set(), {}, {}, {}
    for i in sorted(syms):
        y = syms[i]
        if not 0 < y.sec <= len(secs):
            continue
        s = secs[y.sec - 1]
        a = aux(i)
        if y.cls == STATIC and y.value == 0 and y.name == s.name and len(a) >= 18 and y.sec not in sel:
            secdef.add(i)
            sel[y.sec] = a[14]
            parent[y.sec] = struct.unpack_from("<H", a, 12)[0] if a[14] == ASSOCIATIVE else 0
        elif s.flags & COMDAT and y.sec not in leader:
            leader[y.sec] = rn(y.name)
    base, keys = {}, {}

    def stem(k, seen=()):
        if k not in base:
            s = secs[k - 1]
            if not s.flags & COMDAT:
                base[k] = ("sec", s.name)
            elif sel.get(k) == ASSOCIATIVE and 0 < parent[k] <= len(secs) and k not in seen:
                base[k] = ("assoc", stem(parent[k], seen + (k,)), s.name)
            else:
                base[k] = ("comdat", leader.get(k), s.name)
        return base[k]
    rank = collections.Counter()
    for s in secs:
        b = stem(s.idx)
        keys[s.idx] = b + (rank[b],)
        rank[b] += 1

    def where(sec):
        return keys[sec] if 0 < sec <= len(secs) else sec

    def ref(i):
        y = syms.get(i)
        if y is None:
            return ("raw", i)
        if i in secdef:
            return ("S", keys[y.sec])
        return ("D", rn(y.name), y.cls, where(y.sec), y.value)
    srecs = []
    for s in live:
        body = raw[s.ptr:s.ptr + s.size] if s.ptr else b""
        if anon:
            body = body.replace(anon, ANON_CANON)
        srecs.append(repr((keys[s.idx], s.flags, s.size, hashlib.sha256(body).hexdigest(), sel.get(s.idx),
                           where(parent[s.idx]) if parent.get(s.idx) else None,
                           sorted(((va, ty, ref(si)) for va, si, ty in s.relocs), key=repr))))
    yrecs = []
    for i, y in syms.items():
        typ = struct.unpack_from("<H", raw, symptr + 18 * i + 14)[0]
        a = aux(i)
        weak = (ref(struct.unpack_from("<I", a, 0)[0]), struct.unpack_from("<I", a, 4)[0]) \
            if y.cls == WEAK and len(a) >= 8 else None
        yrecs.append(repr((rn(y.name), y.value, where(y.sec), typ, y.cls, i in secdef, weak)))
    h = hashlib.sha256(CANON_RULES.encode())
    for r in sorted(srecs) + ["--"] + sorted(yrecs):
        h.update(r.encode("latin-1", "backslashreplace") + b"\n")
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
SNAPSHOT_BUILD = "empty-export/1"


def snapshot_build_dir(top, *, empty=False):
    """The build tree belongs to the run, never to the archived commit/cache."""
    path = Path(top) / "build"
    if path.is_symlink() or (path.exists() and not path.is_dir()):
        raise SystemExit("link_cycle: snapshot build/ must be a local directory")
    if empty and path.exists() and any(path.iterdir()):
        raise SystemExit("link_cycle: launcher requires an empty snapshot build/ directory")
    path.mkdir(exist_ok=True)
    return path


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
        if (meta.get("commit") != sha or meta.get("build_origin") != SNAPSHOT_BUILD
                or tree_manifest(dest) != meta.get("tree_manifest")):
            raise SystemExit(f"link_cycle: snapshot {dest} no longer matches its marker; delete it and re-export")
        snapshot_build_dir(dest, empty=bool(os.environ.get("BFME_CYCLE_EXPECTED_SEMANTIC")))
        cycle_source.reject_bytecode(dest)
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
            # Exclude the ENTIRE top-level build tree before extraction: even
            # tracked symlinks/hardlinks must never import an external cache.
            for member in tar:
                relative = Path(into).relative_to(tmp) / member.name
                if relative.parts and relative.parts[0] == "build":
                    continue
                tar.extract(member, into, filter="data")
        if proc.wait():
            raise SystemExit(f"link_cycle: git archive {commit} in {repo} failed")
    extract(ROOT, sha, tmp)
    subs = {}
    for line in git("ls-tree", "-r", sha).splitlines():
        mode, kind, obj, path = line.split(None, 3)
        if mode == "160000":
            if Path(path).parts[0] == "build":
                continue
            if subprocess.run(["git", "-C", str(ROOT / path), "cat-file", "-e", obj + "^{commit}"],
                              capture_output=True).returncode:
                raise SystemExit(f"link_cycle: submodule {path} lacks its pinned commit {obj}")
            (tmp / path).mkdir(parents=True, exist_ok=True)
            extract(ROOT / path, obj, tmp / path)
            subs[path] = obj
    cycle_source.reject_bytecode(tmp)
    snapshot_build_dir(tmp, empty=True)
    # The launcher binds the exported tools before even the shim helper runs.
    expected = os.environ.get("BFME_CYCLE_EXPECTED_SEMANTIC")
    if expected and context.digest({n: text_sha256(tmp / "tools" / n) for n in context.MEASUREMENT_FILES}) != expected:
        raise SystemExit("link_cycle: snapshot tools differ from launcher preflight")
    # the tree's own generated inputs (case-redirect shims on a case-sensitive host), before the marker
    subprocess.run(cycle_source.command(tmp / "tools", "import gen_case_shims; gen_case_shims.ensure_case_shims()"),
                   cwd=tmp, check=True, env=dict(os.environ))
    cycle_source.reject_bytecode(tmp)
    snapshot_build_dir(tmp, empty=True)
    return finish_snapshot(tmp, dest, sha, subs, round(time.time() - t))


def finish_snapshot(tmp, dest, sha, subs, seconds):
    """Write the marker of a complete extraction (tmp; moved to dest if they
    differ). Without its marker a directory is an unfinished export."""
    meta = {"commit": sha, "submodules": subs, "tree_manifest": tree_manifest(tmp),
            "build_origin": SNAPSHOT_BUILD,
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
    expected = os.environ.get("BFME_CYCLE_EXPECTED_SEMANTIC")
    semantic = context.digest({n: text_sha256(snap / "tools" / n) for n in context.MEASUREMENT_FILES})
    if expected and semantic != expected:
        raise SystemExit("link_cycle: snapshot tools differ from launcher preflight")
    env = dict(os.environ, LINK_CYCLE_ROOT=str(snap), BFME_OBJSTORE="off",
               GIT_CEILING_DIRECTORIES=str(snap.parent))
    return subprocess.run(cycle_source.script_command(snap / "tools/link_cycle.py", *rest), env=env, cwd=snap).returncode


def input_state(allow_dirty=False, *, final=False):
    """What a receipt binds, taken when the cycle STARTS and re-proved at its end:
    the commit (a snapshot's marker, else HEAD and the dirty diff), this tool,
    the toolchain, retail and the ledgers."""
    mark = ROOT / SNAPSHOT_MARK
    if mark.exists():
        meta = json.loads(mark.read_text())
        commit = {"commit": meta["commit"], "submodules": meta["submodules"], "snapshot": True,
                  "tree_manifest": tree_manifest(ROOT), "dirty": False}
        if commit["tree_manifest"] != meta["tree_manifest"]:
            raise SystemExit("link_cycle: the snapshot tree differs from its marker; refusing to measure it")
    else:
        diff = subprocess.run(["git", "diff", "--binary", "HEAD"], capture_output=True, cwd=ROOT, check=True).stdout
        untracked = subprocess.run(["git", "ls-files", "--others", "--exclude-standard", "-z"],
                                   capture_output=True, cwd=ROOT, check=True).stdout
        untracked_hashes = {os.fsdecode(n): sha256(ROOT / os.fsdecode(n)) for n in untracked.split(b"\0") if n}
        commit = {"commit": git("rev-parse", "HEAD"), "snapshot": False,
                  "untracked_sha256": digest_of(untracked_hashes),
                  "submodules": git("submodule", "status", "--recursive"),
                  "dirty": bool(git("status", "--porcelain", "--untracked-files=normal")),
                  "diff_sha256": hashlib.sha256(diff).hexdigest()}
    if commit.get("dirty") and not allow_dirty and not final:
        raise SystemExit("link_cycle: dirty tree; use --allow-dirty for an explicitly non-authoritative diagnostic")
    dependencies = context.tool_dependencies(ROOT, __file__)
    target = context.target_identity(build.EXE)
    if target["image_base"] != BASE or target["machine"] != 0x14C:
        raise SystemExit("link_cycle: target is not the configured i386 BFME1 image base")
    root = build.vc71_root()
    return dict(commit, allow_dirty=bool(allow_dirty), rule_identity=context.rule_identity(dependencies),
                tool_dependencies=dependencies, tool_digest=context.digest(dependencies),
                measure_env=measure_env(), target=target, retail_sha256=target["sha256"],
                toolchain_sha256={n: sha256(root / "Vc7/bin" / n) for n in ("link.exe", "cl.exe", "lib.exe")},
                runtime_libraries_sha256={p.relative_to(root).as_posix(): sha256(p) for p in runtime_libraries()},
                inputs=context.input_hashes(ROOT))


def cycle_input_receipts(out):
    """Load only this cycle's bound witness, never the census's receipts."""
    path = Path(out) / "receipt.json"
    if not path.exists():
        return None
    receipt = json.loads(path.read_text())
    if not receipt.get("compile_input_run"):
        return None
    proof = Path(out) / COMPILE_INPUTS
    if not proof.is_file() or sha256(proof) != receipt.get("compile_inputs_sha256"):
        raise SystemExit("link_cycle: corrupt compile input receipts; rerun with --build")
    receipts = census_receipts.Receipts.load(proof, receipt["compile_input_run"])
    if receipts is None:
        raise SystemExit("link_cycle: invalid compile input receipts; rerun with --build")
    return receipts


def compile_cycle_rows(rows, sources, out):
    receipts = census_receipts.Receipts(Path(out) / COMPILE_INPUTS)
    receipts.path.unlink(missing_ok=True)
    failed = []
    try:
        source_outputs = build.compile_rows(rows, sources, input_proof=receipts)
        census._refresh_missing_search_root_receipts(rows, source_outputs, receipts)
    except SystemExit as error:
        # A successful uncacheable TU is still proven by its witnessed compile.
        source_map = {build.obj_path(Path(s)): Path(s) for s in sources
                      if Path(s).suffix.lower() != build.LIB_SUFFIX}
        stale = census.stale_objects(list(source_map), source_map, receipts=receipts)
        failed = sorted(source_map[p].relative_to(ROOT).as_posix() for p in stale)
        if not failed:
            raise
        print(f"link_cycle: {len(failed)} TU(s) failed to compile ({error}): {failed[:5]}", flush=True)
    finally:
        receipts.save()
    return receipts, failed


def compile_input_binding(receipts):
    return ({"compile_input_run": receipts.run, "compile_input_root": str(ROOT.resolve()),
             "compile_input_root_spellings": census_receipts.root_spellings(ROOT),
             "compile_inputs_sha256": sha256(receipts.path),
             "compile_inputs_semantic_sha256": digest_of(compile_input_semantics(receipts.entries))}
            if receipts is not None else {})


def compile_input_semantics(entries, root=None, spellings=None):
    """Content proof, excluding run IDs, inode generations and export locations.

    Exact witness bytes remain bound by the instance receipt and manifest.
    Object content is independently bound by the provenance's COFF identities.
    """
    root = str(Path(root or ROOT).resolve())

    def normalize(value):
        if isinstance(value, str):
            return census_receipts.canonical_text(value, root, spellings)
        if isinstance(value, list):
            return [normalize(v) for v in value]
        if isinstance(value, dict):
            return {normalize(k): normalize(v) for k, v in value.items()}
        return value

    result = {}
    for obj, entry in entries.items():
        inputs = {k: v for k, v in entry["input"].items()
                  if k not in ("generations", "preprocessed", "signature")}
        inputs["preprocessed_canon"] = entry["input"].get("preprocessed_canon", entry["input"]["preprocessed"])
        signature = entry["input"]["signature"]
        inputs["signature"] = {k: v for k, v in signature.items()
                               if k != "fingerprint" or "environment" not in signature}
        result[obj] = {"source": entry["source"], "command": entry["command"], "input": inputs}
    return normalize(result)


def provenance(rows, present, objs, out, *, receipts=None):
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
    currency, why = {}, {}
    stale = census.stale_objects(present, sources, why, receipts=receipts, proofs=currency)
    if stale:
        raise SystemExit(f"link_cycle: {len(stale)} object(s) are not current for their sources (stale cache), "
                         f"{census.describe_stale(stale, why)}; run with --build")
    prov, tampered = {}, []
    for p in present:
        rel = Path(p).relative_to(ROOT).as_posix()
        o = objs.get(p)
        rec = {"object": object_identity(o) if o else None, "object_canon": canonical_identity(o) if o else None}
        src = sources.get(p)
        if src is not None and Path(src).suffix.lower() != build.LIB_SUFFIX:
            rec["proof"] = currency[p]
            side = Path(p).with_suffix(".deps.json")
            rec.update(source=Path(src).relative_to(ROOT).as_posix(), source_sha256=sha256(src),
                       deps_sha256=sha256(side) if side.exists() else None)
            if rec["proof"] == "receipt":
                ref = str(Path(p).resolve())
                entry = receipts.entries[ref]
                rec.update(receipt_ref=ref, receipt_sha256=digest_of(entry), object_sha256=sha256(p),
                           witness_semantic_sha256=digest_of(compile_input_semantics({ref: entry})))
        prov[rel] = rec
        old = before.get(rel)
        if (old and rec.get("proof") == "deps" and rec.get("deps_sha256")
                and old.get("deps_sha256") == rec["deps_sha256"]
                and old.get("source_sha256") == rec["source_sha256"]
                and (old.get("object") != rec["object"] or
                     (old.get("object_canon") is not None and old["object_canon"] != rec["object_canon"]))):
            tampered.append(rel)
    if tampered:
        raise SystemExit(f"link_cycle: {len(tampered)} object(s) changed with no compile behind the change, "
                         f"e.g. {tampered[:5]}; delete them (and their .deps.json) and run with --build")
    content = json.dumps(prov, indent=0, sort_keys=True)
    if not path.exists() or path.read_text(encoding="utf-8") != content:
        path.write_text(content, encoding="utf-8")
    return (sha256(path), dict(sorted(collections.Counter(r.get("proof", "no source") for r in prov.values()).items())),
            canonical_digests(prov))


def canonical_digests(prov):
    """The objects' and the provenance's digests by canonical_identity: what two
    builders of one tree agree on (object_identity also binds the compile's
    anonymous-namespace hash and section and symbol numbering)."""
    h = hashlib.sha256(CANON_RULES.encode())
    for rel in sorted(prov):
        h.update(f"{rel}\0{prov[rel].get('object_canon') or '-'}".encode())
    stable = {rel: {k: v for k, v in rec.items()
                    if k not in ("receipt_ref", "receipt_sha256", "object_sha256")
                    and not (rec.get("proof") == "receipt" and k == "deps_sha256")}
              for rel, rec in prov.items()}
    canon = {rel: {k: v for k, v in rec.items() if k != "object"} for rel, rec in stable.items()}
    return {"canon_rules": CANON_RULES, "objects_canon_digest": h.hexdigest(),
            "provenance_semantic_sha256": digest_of(stable),
            "provenance_canon_sha256": digest_of(canon)}


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


def record_run_evidence(receipt, start, end, args, *, remeasure=False):
    """Bind both checkout observations and diagnostic switches before core stamping."""
    keys = ("commit", "snapshot", "dirty", "diff_sha256", "untracked_sha256", "submodules", "tree_manifest")
    receipt["checkout_start"] = {k: start[k] for k in keys if k in start}
    receipt["checkout_end"] = {k: end[k] for k in keys if k in end}
    receipt["run_options"] = {k: bool(getattr(args, k, False)) for k in context.RUN_OPTIONS}
    receipt["run_options"].update(snapshot=bool(start.get("snapshot")), remeasure=remeasure,
                                  measure_only=remeasure or bool(getattr(args, "measure_only", False)))
    if os.environ.get(cycle_source.AUDIT_ENV):
        receipt["executed_modules"] = cycle_source.audit_modules(os.environ[cycle_source.AUDIT_ENV],
                                                                require_complete=False)
        receipt["runtime_modules"] = cycle_source.audit_modules(os.environ[cycle_source.AUDIT_ENV],
                                                               require_complete=False, runtime=True)
    receipt["authoritative"] = context.run_authority_failure(receipt) is None


def receipt_core(receipt):
    """The reproducible part of a receipt: what a cold and a cached run of the same
    inputs must agree on. Times, dates, link history and the warm-start path are
    left out; the instance tag additionally binds exact receipt bytes."""
    keep = ("checkout_start", "checkout_end", "run_options", "diagnostic",
            "rule_identity", "executed_modules", "runtime_modules", "runtime_evidence", "allow_dirty", "tool_dependencies", "measure_env", "target", "settings",
            "untracked_sha256", "closure_graph_sha256", "rules", "commit", "submodules", "snapshot", "dirty", "diff_sha256", "tool_digest",
            "retail_sha256", "toolchain_sha256", "runtime_libraries_sha256", "inputs", "objects_digest", "provenance_sha256", "objects",
            "objects_missing", "compile_failed", "currency_proofs", "quarantine_sha256", "stubs_sha256",
            "compile_inputs_semantic_sha256",
            "not_ordered", "not_ordered_bytes", "analyze",
            "scaffold", "final_link", "series")
    core = {k: receipt[k] for k in keep if k in receipt}
    if "provenance_semantic_sha256" in receipt:
        core["provenance_sha256"] = receipt["provenance_semantic_sha256"]
    return core


def receipt_canon_core(receipt):
    """receipt_core with the objects and the provenance bound by canonical_identity
    (canonical_digests) in place of object_identity: two builders of one commit
    compare `core_canon_sha256`; `core_sha256` stays the same-builder identity.
    None for a receipt written before the canonical digests existed."""
    if "objects_canon_digest" not in receipt:
        return None
    core = receipt_core(receipt)
    core.pop("objects_digest", None)
    core.pop("provenance_sha256", None)
    core.update({k: receipt[k] for k in ("canon_rules", "objects_canon_digest", "provenance_canon_sha256")})
    return core


def stamp_cores(receipt):
    receipt["core_sha256"] = digest_of(receipt_core(receipt))
    canon = receipt_canon_core(receipt)
    if canon is not None:
        receipt["core_canon_sha256"] = digest_of(canon)


def write_receipt(out, receipt, name="receipt.json"):
    """Finalize once; tag binds exact bytes, while cores exclude instance timing.

    The per-instance receipt archive is write-once. receipt.json is a convenience
    pointer to the latest run, not its immutable identity or publication proof.
    """
    stamp_cores(receipt)
    receipt["measured_end_ns"] = time.time_ns()
    raw = (json.dumps(receipt, sort_keys=True, indent=1) + "\n").encode()
    sha = hashlib.sha256(raw).hexdigest()
    tag = f"{receipt['commit'][:12]}-{receipt['measured_end_ns']}-{sha[:16]}"
    archive = Path(out) / "measurements" / tag
    archive.mkdir(parents=True, exist_ok=False)
    # Retain the small measurement substrate with the identity so reruns cannot
    # orphan an archived receipt by replacing the latest graph/status/provenance.
    import shutil
    expected = {CLOSURE_GRAPH: receipt.get("closure_graph_sha256"),
                "link_status.csv": receipt.get("series", {}).get("link_status_sha256"),
                "provenance.json": receipt.get("provenance_sha256"),
                COMPILE_INPUTS: receipt.get("compile_inputs_sha256")}
    for member, want in expected.items():
        source = Path(out) / member
        if source.exists():
            shutil.copyfile(source, archive / member)
        if want and (not (archive / member).exists() or sha256(archive / member) != want):
            raise SystemExit(f"link_cycle: {member} moved before archival; no receipt finalized")
    (archive / "receipt.json").write_bytes(raw)
    identity = {"tag": tag, "receipt_sha256": sha, "commit": receipt["commit"],
                "measured_end_ns": receipt["measured_end_ns"], "core_sha256": receipt["core_sha256"],
                "core_canon_sha256": receipt.get("core_canon_sha256")}
    (archive / "identity.json").write_text(json.dumps(identity, sort_keys=True) + "\n")
    (Path(out) / name).write_bytes(raw)
    (Path(out) / (name + ".identity.json")).write_text(json.dumps(identity, sort_keys=True) + "\n")
    return identity


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
    cycle_source.input_epoch(ROOT, prepare=True)
    getattr(census, "refuse_unsupported_ledgers", lambda: None)()
    start = input_state(getattr(args, "allow_dirty", False))                      # bound at START, re-proved before recording
    rows = census.ledger()
    compile_failed = []
    receipts = None
    if args.build:
        t = time.time()
        os.environ.setdefault("BUILD_POOL", str(max(1, (os.cpu_count() or 2) - 2)))
        build.ensure_case_shims()
        sources = census.compile_sources(rows)
        receipts, compile_failed = compile_cycle_rows(rows, sources, out)
        times["compile"] = round(time.time() - t)
    else:
        receipts = cycle_input_receipts(out)
    compile_inputs = compile_input_binding(receipts)
    t = time.time()
    present, missing = census.objects(rows)
    failed_objs = {build.obj_path(ROOT / s) for s in compile_failed}
    if failed_objs:
        missing = list(missing) + [p for p in present if p in failed_objs]
        present = [p for p in present if p not in failed_objs]
    if not args.raw_dumps:
        SWAP.update(load_swap(rows))
        present = list(dict.fromkeys(SWAP.get(p.resolve(), p) for p in present))
    cycle_source.input_epoch(ROOT, outputs=out)
    objs = Objects(present)
    units, astat = analyze(rows, objs)
    obj_digest = objects_digest(objs, present)
    prov_digest, proofs, canon = provenance(rows, present, objs, out, receipts=receipts)
    times["provenance"] = round(time.time() - t)
    pe_r, R, rsecs, rimp = pe_view(build.EXE)
    text0, textsz = rsecs[".text"]
    pins, byaddr = load_pins()
    with (REVERSE / "ghidra_functions.csv").open(newline="") as f:
        ghidra = [int(r["rva"], 16) for r in csv.DictReader(f)]
    cuts = [a for a in ghidra + list(byaddr) if text0 <= a < text0 + textsz]
    retail_imports = globals()["retail_imports"]()
    entries, imp_missing = import_def_entries(undefined_imports(objs), retail_imports)
    native_thunks = native_import_thunks(rows, objs, R, rimp, entries)
    libs = make_import_libs(entries, out, native_thunks) + runtime_libraries()
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
        # The shifted link runs alongside on Windows; under Wine two concurrent link.exe runs
        # exit 0 without writing their /MAP, so there it runs after the base link.
        pool = None
        try:
            concurrent_shift = args.shift_base and sys.platform == "win32"
            if concurrent_shift:   # used when this iteration converges
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
                if not shift.cancel():   # already running: let it finish before the next link
                    shift.result()
                shift = None
            quarantine |= set(culprits)
            save_cache(qfile, obj_digest, sorted(quarantine))
        finally:
            if pool is not None:
                pool.shutdown(wait=True)
    save_cache(qfile, obj_digest, sorted(quarantine))
    if shift:
        shift_res = shift.result()
    elif args.shift_base:   # under Wine, only the final iteration's layout is linked shifted
        shift_res = link(SHIFT_TAG, inputs, order, entry, args.shift_base, out)
    else:
        shift_res = None
    times["link"] = round(time.time() - t_link)

    t = time.time()
    cycle_source.input_epoch(ROOT)
    res = measure(out, units, chunks, objs, R, rsecs, rimp, pins, shift_res is not None, args.shift_base)
    times["measure"] = round(time.time() - t)
    receipt = dict(start, **canon, **compile_inputs, tool="link_cycle", rules=RULES,
                   settings={"shift_base": args.shift_base, "raw_dumps": args.raw_dumps},
                   closure_graph_sha256=res["closure_graph_sha256"],
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
    end = input_state(getattr(args, "allow_dirty", False), final=True)
    moved = sorted(k for k in start if start[k] != end.get(k))
    current_objs = Objects(present)
    if objects_digest(current_objs, present) != obj_digest:
        moved.append("objects_digest")
    end_prov, end_proofs, end_canon = provenance(rows, present, current_objs, out, receipts=receipts)
    if (end_prov, end_proofs, end_canon) != (prov_digest, proofs, canon):
        moved.append("provenance")
    if compile_input_binding(receipts) != compile_inputs:
        moved.append("compile_inputs")
    if getattr(sys, "_bfme_cycle_io", None) is not None:
        try:
            cycle_source.consumed_inputs(ROOT)
        except ValueError as error:
            moved.append(str(error))
    record_run_evidence(receipt, start, end, args)
    receipt["authoritative"] = receipt["authoritative"] and not moved
    times["total"] = round(time.time() - t_all)
    receipt["seconds"] = times
    stamp_cores(receipt)
    if moved:
        receipt["moved_during_run"] = moved
        (out / "receipt.rejected.json").write_text(json.dumps(receipt, indent=1), encoding="utf-8")
        raise SystemExit(f"link_cycle: inputs moved during the run ({', '.join(moved)}); no receipt recorded")
    write_receipt(out, receipt)
    print(json.dumps(res, indent=1))
    print(f"link_cycle: receipt {out / 'receipt.json'} core {receipt['core_sha256'][:16]}; wall {times}")
    return receipt


def measure(out, units, chunks, objs, R, rsecs, rimp, pins, have_shift, shift_base, artifact_out=None):
    artifact_out = Path(artifact_out or out)
    artifact_out.mkdir(parents=True, exist_ok=True)
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
    m.rsecs = rsecs
    m.compile_includes = {}
    # A real BFME1 image must have its retained relocation evidence; the
    # loader raises rather than silently dropping a missing/truncated table.
    m.retail_sites = retail_relocs.site_rvas() if R[:2] == b"MZ" else None
    recs = m.run()
    proof_file = out / COMPILE_INPUTS
    if proof_file.exists():
        # Fresh census receipts contain the actual opened paths even when a
        # reusable deps sidecar cannot be written. Retain their content witness.
        proof_doc = json.loads(proof_file.read_text(encoding="utf-8"))
        measured_sources = ({row["source"] for unit in units for row in unit["rows"]} |
                            {source for node in m.dnodes.values() for source in node["sources"]})
        inventory_cache = {}
        for entry in proof_doc.get("entries", {}).values():
            original = entry["source"].replace("\\", "/")
            for source in measured_sources:
                if not original.endswith("/" + source):
                    continue
                prefix = original[:-len(source)]
                deps = {p[len(prefix):] if p.startswith(prefix) else p: h
                        for p, h in entry["input"]["files"].items()}
                # Quoted include precedence also observes source/header
                # directories; command /I roots are inventoried by build.
                command = entry.get("command", [])
                roots = build._include_search_roots(ROOT / source, command, {})
                if roots is not None:
                    search_roots = [build._root_key(root) for root in roots]
                    inventory = build._inventory_for_roots(roots, inventory_cache)
                    m.compile_includes[source] = dict(deps=deps, search_roots=search_roots, inventory=inventory)
    text0, raw_textsz = rsecs[".text"]
    # BFME1 progress.real_split/real_code_denominator exclude all retail CC
    # bytes. Bind the same intervals for graph gains and receipt-only diffs.
    m.padding = [[text0 + hit.start(), text0 + hit.end()]
                 for hit in re.finditer(b"\xcc+", bytes(R[text0:text0 + raw_textsz]))]
    textsz = raw_textsz - sum(b - a for a, b in m.padding)
    sh = Shifted(out, I, isecs, rsecs, have_shift, shift_base, {BASE + r["row"]["rva"] for r in recs})
    hard = {}
    for rec in recs:
        if rec["measured"]:
            why = sh.code(rec["linked"], rec["row"]["size"], rec["masked"], rec["rels"],
                          entries=m.code_entries[rec["linked"]])
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
                node = m.eh_nodes[e[1]]
                ok[e] = not node["fails"] and not sh.eh(e[1])
                edges[e] |= node["edges"]
    # a dump (generated/asm unit) is retail bytes re-encoded, not source: in the
    # source closure an edge into one closes nothing, like a filler
    dump_units = {u["id"] for u in units if any(r.get("provenance") in ("generated", "dump") or r["kind"] in ("generated", "asm")
                                                        for r in u["rows"])}
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
    fold = artifact_out / "fold_list.csv"
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
    status = artifact_out / "link_status.csv"
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
            span = context.credit_spans(r["rva"], r["size"], m.padding)
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
                    series[(k, name, "bytes")] += unique_bytes(span)
                    spans[(k, name)].extend(span)
    res = {}
    for (k, name), sp in sorted(spans.items()):
        res.setdefault(k, {})[name] = {"rows": series[(k, name, "rows")], "bytes": series[(k, name, "bytes")],
                                       "unique_bytes": unique_bytes(sp),
                                       "pct_text": round(100 * unique_bytes(sp) / max(1, textsz), 2)}
    reasons = collections.Counter()
    rbytes = collections.Counter()
    for rec in recs:
        if rec["row"]["kind"] == "real" and rec["placed"]:
            fails = rec["fails"] + (["shift"] if id(rec) in hard else [])
            for c in {f.split(":")[0] for f in fails}:
                reasons[c] += 1
                rbytes[c] += unique_bytes(context.credit_spans(rec["row"]["rva"], rec["row"]["size"], m.padding))
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
    res["padding"] = m.padding
    res["link_status_sha256"] = sha256(status)
    res["data_back"] = {"address_kind": "rva", "collisions": [
        {"retail_rva": rt, "linked_rvas": sorted(ls)} for rt, ls in sorted(m.back.items()) if len(ls) > 1]}
    m.source_includes = m.include_proofs({r["source"] for u in units for r in u["rows"]} |
                                        {s for node in m.dnodes.values() for s in node["sources"]})
    graph = closure_graph_doc(m, recs, hard, ok, src_edges)
    write_closure_graph(artifact_out / CLOSURE_GRAPH, graph)
    res["closure_graph_sha256"] = sha256(artifact_out / CLOSURE_GRAPH)
    return res


CLOSURE_GRAPH = "closure_graph.json.gz"
CLOSURE_GRAPH_SCHEMA = context.GRAPH_SCHEMA


def node_key(n):
    """A closure node as text: its kind and its numbers, nested keys flattened."""
    def flat(v):
        for x in v:
            if isinstance(x, tuple):
                yield from flat(x)
            else:
                yield str(x)
    return ":".join(flat(n))


def closure_graph_doc(m, recs, hard, ok, edges):
    """The closure graph measure() judged, as plain sorted values: every node with its
    verdict and what it is, every edge, and each ledger row with its unit node, placed and
    self_strict. It READS the finished measure and asks nothing: no shift check runs here
    (a twin or datum that failed with no failure of its own failed its shift check; one
    with failures of its own was never asked), so no verdict or counter can move."""
    nodes = {}
    rows = []
    for rec in recs:
        r, u = rec["row"], rec["unit"]
        n = ("unit", u["id"])
        d = nodes.setdefault(node_key(n), {"kind": "unit", "ok": bool(ok[n]), "name": u.get("head") or r["name"],
                                           "rva": r["rva"], "source": r["source"], "provenance": [], "failures": set()})
        d["rva"] = min(d["rva"], r["rva"])
        d["name"] = min(d["name"], u.get("head") or r["name"])
        d["source"] = min(d["source"], r["source"])
        # AGENTS.md generated/vendored claims and progress.source_lane:
        # provenance is independent of functional gen-funclet/import/alias kind.
        d["provenance"] = sorted(set(d["provenance"]) | {r.get("provenance", r["kind"])})
        d["failures"].update(rec["fails"])
        if id(rec) in hard:
            d["failures"].add(f"shift:{hard[id(rec)]}")
        if not rec["measured"]:
            d["failures"].add("unmeasured")
        rows.append([r["name"], r["kind"], r["source"], r["rva"], r["size"], node_key(n), int(bool(rec["placed"])),
                     int(bool(rec["measured"] and not rec["fails"]))])
    for n, v in ok.items():
        kind, key = n[0], node_key(n)
        if kind == "unit":
            continue
        d = nodes[key] = {"kind": kind, "ok": bool(v), "failures": set()}
        if kind == "twin":
            good, why = m.twins[(n[1], n[2])]
            sym = m.sym_at(n[1])
            d.update(rva=n[2], linked=n[1], name=sym[1] if sym else "", object=sym[2] if sym else "")
            d["failures"].update((getattr(m, "twin_fails", {}).get((n[1], n[2])) or [why]) if not good else ([] if v else ["shift"]))
        elif kind == "datum":
            node = m.dnodes[n[1]]
            d.update(rva=n[1][1], linked=n[1][0], size=n[1][2], name=node["name"], sources=node["sources"])
            d["failures"].update(node["fails"] or ([] if v else ["shift"]))
        elif kind == "eh":
            d["failures"].update(m.eh_nodes[n[1]]["fails"] or ([] if v else ["shift"]))
        elif not v:
            d["failures"].add("shift")
    for d in nodes.values():
        d["failures"] = sorted(d["failures"])
    return {"schema": CLOSURE_GRAPH_SCHEMA, "bad_targets": list(context.BAD_TARGETS), "rules": RULES,
            "padding": m.padding, "include_proofs": m.source_includes,
            "nodes": dict(sorted(nodes.items())),
            "edges": {node_key(n): sorted(node_key(t) for t in ts) for n, ts in sorted(edges.items(), key=lambda kv:
                                                                                      node_key(kv[0])) if ts},
            "rows": sorted(rows, key=lambda r: (r[3], r[0], r[2], r[1], r[4], r[5], r[6], r[7]))}


def write_closure_graph(path, doc):
    """closure_graph.json.gz: canonical JSON (sorted keys), gzip with no name and mtime 0, so
    the same measure writes the same bytes."""
    import gzip
    data = json.dumps(doc, sort_keys=True, separators=(",", ":")).encode("utf-8")
    with open(path, "wb") as raw:
        with gzip.GzipFile(filename="", mode="wb", fileobj=raw, compresslevel=6, mtime=0) as gz:
            gz.write(data)


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

    def code(self, at, size, masked, rels, entries=(0,)):
        """None, or why code at `at` does not follow a rebase: a hard-coded retail
        data VA or row start no relocation covers, or a shifted-link difference."""
        if hardcoded_operands(self.I[at:at + size], at + BASE, masked, self.lo, self.hi, self.starts, entries):
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
        except (struct.error, IndexError, ValueError):
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
    ap.add_argument("--allow-dirty", action="store_true", help="record a dirty diagnostic (never authoritative)")
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
    receipts = cycle_input_receipts(out)
    compile_inputs = compile_input_binding(receipts)
    start = input_state(getattr(args, "allow_dirty", False))
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
    diagnostic = out / "remeasured" / str(time.time_ns())
    diagnostic.mkdir(parents=True)
    if receipts is not None:
        import shutil
        shutil.copyfile(receipts.path, diagnostic / COMPILE_INPUTS)
    obj_digest = objects_digest(objs, present)
    prov_digest, proofs, canon = provenance(rows, present, objs, diagnostic, receipts=receipts)
    res = measure(out, units, chunks, objs, R, rsecs, rimp, pins, True, args.shift_base, artifact_out=diagnostic)
    print(json.dumps(res, indent=1))
    path = out / "receipt.json"
    receipt = dict(start, **canon, **compile_inputs, tool="link_cycle", rules=RULES, authoritative=False,
                   source_receipt_sha256=sha256(path) if path.exists() else None,
                   diagnostic="remeasured, link input currency not proven", series=res,
                   objects_digest=obj_digest, provenance_sha256=prov_digest, currency_proofs=proofs,
                   closure_graph_sha256=res["closure_graph_sha256"],
                   settings={"shift_base": args.shift_base, "raw_dumps": args.raw_dumps},
                   seconds={"measure": round(time.time() - t)})
    current_objs = Objects(present)
    end_prov = provenance(rows, present, current_objs, diagnostic, receipts=receipts)
    end = input_state(getattr(args, "allow_dirty", False), final=True)
    record_run_evidence(receipt, start, end, args, remeasure=True)
    if (start != end
            or objects_digest(current_objs, present) != obj_digest
            or compile_input_binding(receipts) != compile_inputs
            or end_prov != (prov_digest, proofs, canon)):
        raise SystemExit("link_cycle: inputs moved during diagnostic remeasurement")
    write_receipt(diagnostic, receipt)
    return 0


if __name__ == "__main__":
    sys.exit(main())
