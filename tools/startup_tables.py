#!/usr/bin/env python3
"""Retail's CRT initializer tables, and whether a link reproduces them.

msvcrt.lib's _WinMainCRTStartup (crtexew.obj, ledgered at the PE entry) runs
_initterm over [___xi_a, ___xi_z) and [___xc_a, ___xc_z); __RTC_Initialize and
__RTC_Terminate (RunTmChk.lib initsect.obj) walk [___rtc_iaa, ___rtc_izz) and
[___rtc_taa, ___rtc_tzz). The DLL CRT runs no .CRT$XP/XT table from the exe.
The linker builds each range from every input's `.CRT$X..` / `.rtc$...`
sections: grouped by the name after '$' in sort order and, within one name, in
link order (tools/tests/test_startup_tables.py links objects to prove it). So
the order retail runs its initializers in is a fact about retail's link order,
and a relink reproduces it only if its inputs come in a compatible order.

  retail   every delimiter read from its genuine library relocation at the
           ledgered row (retail's bytes at the site), then every slot: target,
           the ledger row owning it (exact start, enclosing, none) and the
           row's kind, retail's nonzero runs, and the ledger sources whose
           entries are not contiguous (split_sources: no single object can
           supply them in retail's order).
  objects  --rsp FILE [--objects-root DIR]: every .CRT$/.rtc$ section of every
           object in link order, each entry's retail address and how it was
           found (`ledger`: the object's own row by object symbol, else a
           unique external row or pin; `bytes`: the one unclaimed retail table
           target its code fits, relocations the ledger places included), and
           the tables the linker will build from them.
  image    --exe FILE --map FILE [--rsp FILE]: the tables a finished link
           built, each entry mapped back through the map's publics/statics to
           the same keys (with --rsp, also through the objects' placements).

`objects` and `image` compare against retail: missing, extra, unresolved and
out-of-order entries (those outside a longest common ordered subsequence).
Zero slots are reported, not compared: _initterm skips them. The verdict is
`match` only when all four lists are empty. Outputs go to build/startup/.
"""
import argparse
import bisect
import collections
import csv
import json
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402
from coffar import read_archive  # noqa: E402
from reloc_ledger import parse_coff  # noqa: E402

OUT = ROOT / "build" / "startup"
SYMBOLS = ROOT / "targets" / "game" / "reverse" / "symbols.csv"
DIR32, REL32 = 0x0006, 0x0014
JMP = bytes([0xE9])
EXTERNAL, STATIC = 2, 3
# table -> (row holding the delimiter relocations, begin symbol, end symbol)
TABLES = {
    "XI": ("_WinMainCRTStartup", "___xi_a", "___xi_z"),
    "XC": ("_WinMainCRTStartup", "___xc_a", "___xc_z"),
    "RTC_I": ("__RTC_Initialize", "___rtc_iaa", "___rtc_izz"),
    "RTC_T": ("__RTC_Terminate", "___rtc_taa", "___rtc_tzz"),
}
# COFF section name prefix -> table its entries land in
SECTION_TABLE = (("$XI", "XI"), ("$XC", "XC"), ("$IA", "RTC_I"), ("$IM", "RTC_I"), ("$IZ", "RTC_I"),
                 ("$TA", "RTC_T"), ("$TM", "RTC_T"), ("$TZ", "RTC_T"))


def table_of(section_name):
    """Table a .CRT$/.rtc$ section contributes to, or None."""
    low = section_name.lower()
    if not low.startswith((".crt$", ".rtc$")):
        return None
    tail = section_name[section_name.index("$"):].upper()
    for prefix, table in SECTION_TABLE:
        if tail.startswith(prefix.upper()) and (prefix.startswith("$X") == low.startswith(".crt$")):
            return table
    return None


def linker_order(contributions):
    """The order link.exe lays grouped sections out: by full section name, and
    within one name by input position (Python's sort is stable)."""
    return sorted(contributions, key=lambda c: c["section"])


# --------------------------------------------------------------------------- retail

class Retail:
    def __init__(self, exe=build.EXE):
        import pefile
        pe = pefile.PE(str(exe), fast_load=True)
        self.base = pe.OPTIONAL_HEADER.ImageBase
        self.image = pe.get_memory_mapped_image()

    def u32(self, rva):
        return struct.unpack_from("<I", self.image, rva)[0]


def matched_rows():
    return [r for r in build.load_function_rows() if r["target_rva"].startswith("0x")]


def row_kind(row):
    notes, source = row.get("notes") or "", row["source"]
    if "vendored=" in notes:
        return "vendored"
    m = re.search(r"(?:^|;)\s*(gen-[a-z]+)", notes)
    if m:
        return m.group(1)
    if source.lower().endswith(".asm"):
        return "masm-dump"
    return "source"


class Owners:
    """Ledger row at or around an address."""

    def __init__(self, rows):
        self.rows = sorted(rows, key=lambda r: int(r["target_rva"], 16))
        self.starts = [int(r["target_rva"], 16) for r in self.rows]

    def at(self, rva):
        i = bisect.bisect_right(self.starts, rva) - 1
        while i >= 0 and self.starts[i] == rva and i > 0 and self.starts[i - 1] == rva:
            i -= 1
        if i < 0:
            return "unclaimed", None
        row = self.rows[i]
        start, size = self.starts[i], int(row["target_size"] or 0)
        if start == rva:
            return "exact", row
        if rva < start + size:
            return "inside", row
        return "unclaimed", None


def delimiters(retail, rows):
    """{symbol: va} for every table delimiter, read at its relocation site in retail.

    Each comes from the genuine library member of the ledgered row whose object
    symbol TABLES names: its DIR32 relocation against the delimiter, read at
    the row's retail address."""
    holders = {build.ledger_object_symbol(r): r for r in rows if r["source"].lower().endswith(".lib")}
    out = {}
    for holder, begin, end in TABLES.values():
        row = holders.get(holder)
        if row is None:
            continue
        sections, symbols = parse_coff(dict(read_archive(ROOT / row["source"]))[build.ledger_member(row)])
        defined = [s for s in symbols.values() if s["name"] == holder and s["section"] > 0]
        if len(defined) != 1:
            continue
        sec = sections[defined[0]["section"] - 1]
        rva = int(row["target_rva"], 16) - defined[0]["value"]
        for where, index, kind in sec["relocs"]:
            name = symbols[index]["name"]
            if kind == DIR32 and name in (begin, end):
                out[name] = retail.u32(rva + where)
    return out


def retail_tables(retail, rows):
    owners = Owners(rows)
    delim = delimiters(retail, rows)
    tables = {}
    for table, (_, begin, end) in TABLES.items():
        if begin not in delim or end not in delim:
            tables[table] = {"begin": None, "end": None, "slots": 0, "entries": [], "runs": [],
                             "note": f"delimiters not found (row {TABLES[table][0]} absent or not a library member)"}
            continue
        lo, hi = delim[begin], delim[end]
        entries, runs, run = [], [], None
        for va in range(lo, hi, 4):
            target = retail.u32(va - retail.base)
            if target == 0:
                run = None
                continue
            rva = target - retail.base
            how, row = owners.at(rva)
            entries.append({"slot": va, "target": target, "rva": rva, "owner": how,
                            "row": row["name"] if row else "", "kind": row_kind(row) if row else "unclaimed",
                            "source": row["source"] if row else ""})
            if run is None:
                run = {"start": va, "count": 0}
                runs.append(run)
            run["count"] += 1
        tables[table] = {"begin": lo, "end": hi, "slots": (hi - lo) // 4, "entries": entries, "runs": runs}
    return tables


# --------------------------------------------------------------------------- objects

def object_key(path):
    """The name a map and an object list share for an object: its file name."""
    return re.split(r"[\\/:]", str(path))[-1].lower()


class Resolver:
    """(object, symbol) -> retail rva, from the ledger, the pins and the DIR32 table.

    Code pins in symbols.csv are RVAs, data pins VAs; a pin above the image's
    code VA range is taken as a VA, one inside .text's RVA range as an RVA, and
    one in between (a data RVA or a code VA) is not used. dir32_addresses.csv
    (data, VA) is the verified name for data referents."""

    CODE_END_RVA = 0xC73000
    BASE = 0x400000

    def __init__(self, rows, pins_path=SYMBOLS, dir32_path=build.DIR32_ADDRESSES):
        self.local = {}
        external = collections.defaultdict(set)
        for row in rows:
            try:
                obj = object_key(build.row_object(row))
            except SystemExit:
                continue
            rva = int(row["target_rva"], 16)
            self.local[(obj, build.ledger_object_symbol(row))] = rva
            external[row["name"]].add(rva)
        extra = collections.defaultdict(set)
        for path, column in ((pins_path, "address"), (dir32_path, "va")):
            if not (path and Path(path).exists()):
                continue
            with open(path, encoding="utf-8", newline="") as handle:
                for pin in csv.DictReader(handle):
                    if pin["name"] in external or not pin[column].startswith("0x"):
                        continue
                    value = int(pin[column], 16)
                    if column == "va" or value >= self.BASE + self.CODE_END_RVA:
                        extra[pin["name"]].add(value - self.BASE)
                    elif value < self.CODE_END_RVA:
                        extra[pin["name"]].add(value)
        self.external = {}
        for table in (external, extra):
            for name, rvas in table.items():
                if len(rvas) == 1 and name not in self.external:
                    self.external[name] = next(iter(rvas))

    def __call__(self, obj, name, storage):
        rva = self.local.get((obj, name))
        if rva is None and storage != STATIC:
            rva = self.external.get(name)
        return rva


def entry_body(sections, symbols, sym, resolver, obj, depth=2):
    """The code an initializer entry points at: bytes from the symbol to its
    section's end, and its relocations as (offset, kind, retail rva or None,
    addend, nested body). A referent the ledger cannot place but this object
    defines in another code section carries its own body (to `depth`), so
    body_fits can check what retail's field reaches."""
    if sym["section"] <= 0:
        return None
    sec = sections[sym["section"] - 1]
    if not sec["body"] or not sec["flags"] & 0x20:
        return None
    lo = sym["value"]
    relocs = []
    for where, index, kind in sec["relocs"]:
        if where < lo or kind not in (DIR32, REL32):
            continue
        ref = symbols[index]
        rva = resolver(obj, ref["name"], ref["storage"]) if ref["section"] != sym["section"] else None
        nested = None
        if rva is None and depth > 0 and ref["section"] > 0 and ref["section"] != sym["section"]:
            nested = entry_body(sections, symbols, ref, resolver, obj, depth - 1)
        addend = struct.unpack_from("<i", sec["body"], where)[0]
        relocs.append((where - lo, kind, rva, addend, nested))
    return {"bytes": sec["body"][lo:], "relocs": relocs}


def object_contributions(paths, resolver, unreadable=None):
    """[{object, section, table, entries: [{symbol, storage, rva, via}]}] in link
    order. An object that cannot be read or parsed is appended to `unreadable`
    (the comparison then cannot say `match`), never treated as empty."""
    out = []
    for position, path in enumerate(paths):
        try:
            data = Path(path).read_bytes()
        except OSError as exc:
            if unreadable is None:
                raise
            unreadable.append(f"{path}: {exc.strerror}")
            continue
        if b"$X" not in data and b"rtc$" not in data:
            continue
        try:
            sections, symbols = parse_coff(data)
        except (struct.error, ValueError) as exc:
            if unreadable is None:
                raise
            unreadable.append(f"{path}: {exc}")
            continue
        obj = object_key(path)
        for sec in sections:
            table = table_of(sec["name"])
            if table is None or sec["flags"] & 0x800:
                continue
            slots = [None] * (sec["size"] // 4)
            for where, index, kind in sec["relocs"]:
                if kind == DIR32 and where % 4 == 0 and where // 4 < len(slots):
                    sym = symbols[index]
                    rva = resolver(obj, sym["name"], sym["storage"])
                    slots[where // 4] = {"symbol": sym["name"], "storage": sym["storage"], "rva": rva,
                                         "via": "ledger" if rva is not None else None,
                                         "body": entry_body(sections, symbols, sym, resolver, obj)}
            out.append({"position": position, "object": obj, "section": sec["name"], "table": table,
                        "entries": [s for s in slots if s is not None], "zero_slots": slots.count(None)})
    return out


def through_ilt(retail, rva):
    """rva, or where the incremental-link jmp at rva goes."""
    if retail.image[rva:rva + 1] == JMP:
        return (rva + 5 + struct.unpack_from("<i", retail.image, rva + 1)[0]) & 0xFFFFFFFF
    return rva


def body_fits(retail, rva, body):
    """Retail's code at rva equals the body outside its relocation fields; every
    relocation whose referent the ledger places reaches it (directly or via an
    incremental-link jmp), and every one carrying a nested body reaches code
    that body fits."""
    code = body["bytes"]
    if rva < 0 or rva + len(code) > len(retail.image):
        return False
    here = bytearray(retail.image[rva:rva + len(code)])
    mine = bytearray(code)
    for off, kind, target, addend, nested in body["relocs"]:
        if off + 4 > len(mine):
            return False
        mine[off:off + 4] = here[off:off + 4]
        if target is None and nested is None:
            continue
        value = struct.unpack_from("<I", here, off)[0]
        if kind == DIR32:
            reached = (value - retail.base - addend) & 0xFFFFFFFF
        else:
            reached = (rva + off + 4 + struct.unpack_from("<i", here, off)[0]) & 0xFFFFFFFF
        if target is not None:
            if target not in (reached, through_ilt(retail, reached)):
                return False
        elif not body_fits(retail, through_ilt(retail, reached), nested):
            return False
    return mine == here


def place_by_bytes(contributions, retail, tables):
    """Resolve entries the ledger cannot name by the retail initializer whose
    code they are: the one retail table target, not taken by a ledger entry,
    that the entry's body fits (body_fits), and that no other entry resolves to
    the same way. Anything else stays unresolved, with its candidate count."""
    fits_of = {}
    for c in contributions:
        want = [e["rva"] for e in tables.get(c["table"], {}).get("entries", [])]
        taken = {e["rva"] for cc in contributions if cc["table"] == c["table"] for e in cc["entries"]
                 if e["via"] == "ledger"}
        for e in c["entries"]:
            if e["rva"] is None and e.get("body"):
                fits = [r for r in dict.fromkeys(want) if r not in taken and body_fits(retail, r, e["body"])]
                e["candidates"] = len(fits)
                if len(fits) == 1:
                    fits_of[id(e)] = (c["table"], fits[0])
    claims = collections.Counter(fits_of.values())
    for c in contributions:
        for e in c["entries"]:
            hit = fits_of.get(id(e))
            if hit and claims[hit] == 1:
                e["rva"], e["via"] = hit[1], "bytes"
            elif hit:
                e["contested"] = claims[hit]
            e.pop("body", None)
    return contributions


def read_rsp(rsp, objects_root=None):
    paths = []
    for line in Path(rsp).read_text(encoding="utf-8").splitlines():
        line = line.strip().strip('"')
        if not line or line.startswith("/"):
            continue
        p = Path(line)
        if not p.is_absolute():
            p = (Path(objects_root) if objects_root else ROOT) / p
        paths.append(p)
    return paths


def predicted_tables(contributions):
    tables = collections.defaultdict(list)
    for c in linker_order(contributions):
        for e in c["entries"]:
            tables[c["table"]].append({**e, "object": c["object"], "section": c["section"]})
    return dict(tables)


# --------------------------------------------------------------------------- image

MAP_GROUP = re.compile(r"^\s*([0-9a-fA-F]{4}):([0-9a-fA-F]{8})\s+([0-9a-fA-F]{8})H\s+(\S+)\s+(DATA|CODE)\s*$")
# the object column can hold spaces (build/match names encode the source path)
MAP_SYMBOL = re.compile(r"^\s*([0-9a-fA-F]{4}):([0-9a-fA-F]{8})\s+(\S+)\s+([0-9a-fA-F]{8})\s+(?:f\s+)?(?:i\s+)?(\S.*?)\s*$")


def linked_tables(exe, mapfile, resolver):
    """Entries of every CRT/RTC group in a linked image, mapped back to retail."""
    import pefile
    pe = pefile.PE(str(exe), fast_load=True)
    base = pe.OPTIONAL_HEADER.ImageBase
    image = pe.get_memory_mapped_image()
    groups, names = [], collections.defaultdict(list)
    statics = False
    with open(mapfile, encoding="latin-1") as handle:
        for line in handle:
            if line.startswith(" Static symbols"):
                statics = True
            m = MAP_GROUP.match(line)
            if m and table_of(m.group(4)):
                sec = int(m.group(1), 16)
                va = base + pe.sections[sec - 1].VirtualAddress + int(m.group(2), 16)
                groups.append({"section": m.group(4), "table": table_of(m.group(4)), "va": va,
                               "size": int(m.group(3), 16)})
                continue
            m = MAP_SYMBOL.match(line)
            if m and m.group(1) != "0000":
                names[int(m.group(4), 16)].append((m.group(3), object_key(m.group(5)), statics))
    tables = collections.defaultdict(list)
    zero = collections.Counter()
    for g in sorted(groups, key=lambda g: g["va"]):
        for va in range(g["va"], g["va"] + g["size"], 4):
            target = struct.unpack_from("<I", image, va - base)[0]
            if target == 0:
                zero[g["table"]] += 1
                continue
            rva, symbol, obj = None, "", ""
            for name, o, is_static in names.get(target, []):
                rva = resolver(o, name, STATIC if is_static else EXTERNAL)
                symbol, obj = name, o
                if rva is not None:
                    break
            tables[g["table"]].append({"symbol": symbol, "object": obj, "rva": rva, "section": g["section"],
                                       "linked": target})
    return dict(tables), dict(zero)


# --------------------------------------------------------------------------- compare

def ordered_common(a, b):
    """Indices of `b` in a longest subsequence ordered the same way in `a`
    (patience LIS over positions of b's items in a; items are unique)."""
    pos = {v: i for i, v in enumerate(a)}
    seq = [(pos[v], j) for j, v in enumerate(b) if v in pos]
    tails, back, prev = [], [], [None] * len(seq)
    for k, (p, _) in enumerate(seq):
        i = bisect.bisect_left(tails, p)
        if i == len(tails):
            tails.append(p)
            back.append(k)
        else:
            tails[i], back[i] = p, k
        prev[k] = back[i - 1] if i else None
    keep, k = set(), back[-1] if back else None
    while k is not None:
        keep.add(seq[k][1])
        k = prev[k]
    return keep


def compare(retail, linked):
    """Per table: missing, extra, unresolved, surplus copies, out_of_order, verdict.

    Counts are compared as multisets (retail's RTC tables repeat one target once
    per /RTC object); order over each target's first occurrence."""
    report = {}
    for table in sorted(set(retail) | set(linked)):
        entries = retail.get(table, {}).get("entries", [])
        want = [e["rva"] for e in entries]
        got = linked.get(table, [])
        unresolved = [e for e in got if e["rva"] is None]
        got_rvas = [e["rva"] for e in got if e["rva"] is not None]
        want_n, got_n = collections.Counter(want), collections.Counter(got_rvas)
        missing = [e for e in entries if e["rva"] not in got_n]
        extra = [e for e in got if e["rva"] is not None and e["rva"] not in want_n]
        surplus = {f"0x{v:08X}": [want_n[v], n] for v, n in got_n.items() if v in want_n and n != want_n[v]}
        wanted = list(dict.fromkeys(want))
        common = [v for v in dict.fromkeys(got_rvas) if v in want_n]
        keep = ordered_common(wanted, common)
        out_of_order = [common[j] for j in range(len(common)) if j not in keep]
        bad = missing or extra or unresolved or out_of_order or surplus
        report[table] = {"retail_count": len(want), "linked_count": len(got), "common": len(common),
                         "missing": missing, "extra": extra, "unresolved": unresolved,
                         "count_differs": surplus, "out_of_order": out_of_order,
                         "verdict": "mismatch" if bad else "match"}
    return report


# --------------------------------------------------------------------------- driver

def hexify(obj):
    if isinstance(obj, dict):
        return {k: (f"0x{v:08X}" if k in ("slot", "target", "rva", "begin", "end", "start", "linked", "va")
                    and isinstance(v, int) else hexify(v)) for k, v in obj.items()}
    if isinstance(obj, list):
        return [f"0x{v:08X}" if isinstance(v, int) else hexify(v) for v in obj]
    return obj


def write_retail(tables, out):
    out.mkdir(parents=True, exist_ok=True)
    (out / "retail_tables.json").write_text(json.dumps(hexify(tables), indent=1), encoding="utf-8")
    split = {t: split_sources(v["entries"]) for t, v in tables.items() if v["entries"]}
    (out / "retail_split_sources.json").write_text(json.dumps(split, indent=1), encoding="utf-8")
    with open(out / "retail_initializers.csv", "w", newline="", encoding="utf-8") as handle:
        w = csv.writer(handle)
        w.writerow(["table", "index", "slot", "target_rva", "owner", "kind", "row", "source"])
        for table, t in tables.items():
            for i, e in enumerate(t["entries"]):
                w.writerow([table, i, f"0x{e['slot']:08X}", f"0x{e['rva']:08X}", e["owner"], e["kind"], e["row"],
                            e["source"]])


def split_sources(entries):
    """{source: [(first index, length)]} for every ledger source whose entries
    sit in more than one run of the retail table. One object's .CRT$XCU is one
    contiguous contribution, so a source split this way cannot compile to the
    object that supplied these entries: it gathers several retail objects'
    initializers (or one of its rows names the wrong body)."""
    runs = []
    for i, e in enumerate(entries):
        src = e["source"] if e["kind"] == "source" else None
        if runs and runs[-1][0] == src:
            runs[-1][2] += 1
        else:
            runs.append([src, i, 1])
    places = collections.defaultdict(list)
    for src, first, length in runs:
        if src:
            places[src].append((first, length))
    return {src: spots for src, spots in places.items() if len(spots) > 1}


def summarize_retail(tables):
    lines = []
    for table, t in tables.items():
        if t["begin"] is None:
            lines.append(f"{table}: {t['note']}")
            continue
        kinds = collections.Counter(f"{e['owner']}/{e['kind']}" for e in t["entries"])
        lines.append(f"{table}: VA 0x{t['begin']:08X}..0x{t['end']:08X} {t['slots']} slots, "
                     f"{len(t['entries'])} nonzero in {len(t['runs'])} runs; " + ", ".join(
                         f"{k} {n}" for k, n in kinds.most_common())
                     + f"; {len(split_sources(t['entries']))} source(s) split across runs")
    return lines


def summarize_compare(report):
    return [f"{table}: {r['verdict']} -- retail {r['retail_count']}, linked {r['linked_count']}, common {r['common']}, "
            f"missing {len(r['missing'])}, extra {len(r['extra'])}, unresolved {len(r['unresolved'])}, "
            f"count differs {len(r['count_differs'])}, out of order {len(r['out_of_order'])}"
            for table, r in report.items()]


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("mode", choices=("retail", "objects", "image"))
    ap.add_argument("--rsp", type=Path, help="objects: link-order object list")
    ap.add_argument("--objects-root", type=Path, help="objects: directory the rsp paths are relative to")
    ap.add_argument("--exe", type=Path)
    ap.add_argument("--map", type=Path)
    ap.add_argument("--out", type=Path, default=OUT)
    args = ap.parse_args(argv)
    rows = matched_rows()
    retail = Retail()
    tables = retail_tables(retail, rows)
    write_retail(tables, args.out)
    for line in summarize_retail(tables):
        print(line)
    if args.mode == "retail":
        return 0
    resolver = Resolver(rows)
    if args.mode == "objects":
        if not args.rsp:
            ap.error("objects needs --rsp")
        unreadable = []
        contributions = place_by_bytes(object_contributions(read_rsp(args.rsp, args.objects_root), resolver,
                                                            unreadable), retail, tables)
        linked = predicted_tables(contributions)
        extra = {"contributions": contributions, "unreadable": unreadable}
    else:
        if not (args.exe and args.map):
            ap.error("image needs --exe and --map")
        if args.rsp:
            # the objects' own placements (ledger or bytes) name the statics a
            # map shows only by (object, name)
            unreadable = []
            placed = {(c["object"], e["symbol"]): e["rva"] for c in place_by_bytes(object_contributions(
                read_rsp(args.rsp, args.objects_root), resolver, unreadable), retail, tables) for e in c["entries"]}
            base_resolver = resolver

            def resolver(obj, name, storage):  # noqa: F811
                rva = placed.get((obj, name))
                return rva if rva is not None else base_resolver(obj, name, storage)
        linked, zero = linked_tables(args.exe, args.map, resolver)
        extra = {"zero_slots": zero, "unreadable": unreadable if args.rsp else []}
    report = compare(tables, linked)
    name = f"compare_{args.mode}.json"
    (args.out / name).write_text(json.dumps(hexify({"report": report, "linked": linked, **extra}), indent=1),
                                 encoding="utf-8")
    for line in summarize_compare(report):
        print(line)
    if extra["unreadable"]:
        print(f"{len(extra['unreadable'])} object(s) could not be read; no table can be called a match")
        return 1
    return 0 if all(r["verdict"] == "match" for r in report.values()) else 1


if __name__ == "__main__":
    sys.exit(main())
