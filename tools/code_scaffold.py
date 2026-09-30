#!/usr/bin/env python3
"""Code-side link scaffolding for the trial whole-program link (tools/data_scaffold.py --trial-link).

Two kinds of labelled scaffolding, both build products under
build/data_scaffold/, never progress, never an edit to a tracked source or
object:

  funclet labels  A gen-funclet row's body is a TU-local `$Lnnnn` label: no
                  other object can name it, so a retail EH unwind map (in the
                  data scaffold or a relocatable dump) that points at it cannot
                  link. A COPY of the census object gets one appended external
                  symbol `g_<VA>` at the label's section offset: the name the
                  ledger and dump_relocs already spell for that address. The
                  label is accepted only when its bytes equal retail's at the
                  row outside relocation fields (build.holds_funclet), taken
                  from the row's pin or, if the pin was renumbered, the one
                  `$L` of the parent's group that holds the funclet. Each label
                  records whether a retail EH table (ledger structure row)
                  expects that address. Section bytes, relocations and every
                  existing symbol index are untouched.
  code aliases    One weak external (SEARCH_ALIAS) per undefined name that has
                  a retail address -- a symbols.csv pin (route= first) or an
                  address-derived g_<VA> in .text -- pointing at the EXTERNAL
                  symbol the object of the row at that address defines
                  (object-symbol= notes, anonymous-namespace hash normalised),
                  or at the funclet label above. An ILT stub address (a ?j_ row)
                  is followed to its target body. One definition per address:
                  authored game/ C++ first, then by name (link_census's rule).
"""
import collections
import csv
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402
import link_census  # noqa: E402
import reloc_ledger as RL  # noqa: E402

EXTERNAL, STATIC = 2, 3
ANON = re.compile(r"\?A0x[0-9A-Fa-f]{8}")
LABEL = re.compile(r"\$L\d+")
EH_RULES = ("eh-unwind-action", "eh-handler", "eh-tryblock", "eh-throwinfo", "eh-catchabletype")


def g_name(va):
    return f"g_{va:08X}"


def append_symbols(data, new):
    """COFF bytes with external symbols [(name, value, section)] appended to the
    symbol table (existing indices, sections and relocations unchanged)."""
    symtab, nsym = struct.unpack_from("<II", data, 8)
    strings_at = symtab + 18 * nsym
    strings = bytearray(data[strings_at:])
    records = bytearray()
    for name, value, section in new:
        raw = name.encode("latin-1")
        if len(raw) <= 8:
            field = raw.ljust(8, b"\0")
        else:
            field = struct.pack("<II", 0, len(strings))
            strings += raw + b"\0"
        records += field + struct.pack("<IhHBB", value, section, 0x20, EXTERNAL, 0)
    struct.pack_into("<I", strings, 0, len(strings))
    out = bytearray(data[:strings_at]) + records + strings
    struct.pack_into("<I", out, 12, nsym + len(new))
    return bytes(out)


def _held(sections, sym, target):
    """build.holds_funclet on a parsed symbol: its bytes equal target outside relocation fields."""
    sec = sections[sym["section"] - 1]
    if sec["body"] is None:
        return False
    lo = sym["value"]
    body = sec["body"][lo:lo + len(target)]
    relocs = [(w - lo, k, "") for w, _, k in sec["relocs"] if lo <= w < lo + len(target)]
    return build.holds_funclet(body, relocs, target)


def find_funclet(sections, symbols, row, target):
    """(symbol, how) of the row's funclet label in a parsed object, or (None, reason)."""
    by_name = {s["name"]: s for s in symbols.values() if s["section"] > 0}
    pin = build.ledger_object_symbol(row)
    sym = by_name.get(pin)
    if sym is not None and _held(sections, sym, target):
        return sym, "pin"
    parent = re.search(r"(?:^|;)parent=([^;]+)", row.get("notes", ""))
    if not parent:
        return None, "pin-does-not-hold" if sym is not None else "pin-missing"
    group = {s["section"] for s in symbols.values()
             if s["name"] in (f"__ehhandler${parent.group(1)}", parent.group(1)) and s["section"] > 0}
    hits = [s for s in symbols.values() if s["section"] in group and LABEL.fullmatch(s["name"])
            and _held(sections, s, target)]
    if len(hits) == 1:
        return hits[0], "parent-group"
    return None, f"parent-group-{len(hits)}-hits"


IMAGE_BASE = 0x400000


def pin_readings(value):
    """The RVAs a symbols.csv address can mean: most pins are RVAs, some are
    written as VAs (pin_consistency.verify_dir32_pins reads both the same way)."""
    return [value] + ([value - IMAGE_BASE] if value >= IMAGE_BASE else [])


def resolve_pin(name, value, has_owner, dir32=None, calls=None):
    """(rva, how) for a pin, or (None, reason). `has_owner(rva)` must say whether a
    LEDGER ROW lives there (export availability is a separate, later question).
    Independent evidence -- where byte-verified code's calls to the name land
    in retail (call_targets.csv, an ILT stub followed to its body) and the
    address matched references give it (dir32_addresses.csv) -- must agree with
    each other and with an owned reading; any contradiction, or two owned
    readings no evidence separates, is reported, never resolved by picking."""
    owned = [r for r in pin_readings(value) if has_owner(r)]
    if not owned:
        return None, "no-owner"
    evidence = {}
    called = set((calls or {}).get(name, ()))
    if called:
        evidence["call-target"] = called
    if dir32 is not None and name in dir32:
        evidence["dir32"] = {dir32[name] - IMAGE_BASE}
    supported = set(owned)
    for how, rvas in evidence.items():
        supported &= rvas
    if evidence and not supported:
        return None, "evidence-contradicts-pin"
    if len(supported) == 1:
        rva = next(iter(supported))
        how = "+".join(sorted(evidence)) if evidence else ("rva" if rva == value else "va")
        return rva, how
    return None, "ambiguous-va-rva"


def call_targets(img, path=None):
    """{name: {rva}} where byte-verified code's calls to each name land in retail,
    each ILT stub (E9 rel32) also standing for the body it jumps to."""
    path = path or ROOT / "build" / "reloc_ledger" / "call_targets.csv"
    out = collections.defaultdict(set)
    if not Path(path).exists():
        return out
    for row in RL.read_csv_rows(path):
        va = int(row["symbol_va"], 16)  # the symbol's address: destination minus the addend
        out[row["name"]].add(va - img.base)
        head = img.read(va, 5) if img.section(va) == ".text" else None
        if head and head[0] == 0xE9:
            out[row["name"]].add((va + 5 + struct.unpack_from("<i", head, 1)[0] - img.base) & 0xFFFFFFFF)
    return out


def funclet_labels(img, rows, census, out, eh_targets, log=print):
    """Patched copies of the census objects holding gen-funclet rows.

    Returns ({census object: patched copy}, {va: g_ name}, manifest rows, counts)."""
    by_obj = collections.defaultdict(list)
    for row in rows:
        if "gen-funclet" not in (row.get("notes") or "") or not row["target_rva"].startswith("0x"):
            continue
        obj = build.row_object(row)
        if obj.resolve() in census:
            by_obj[obj].append(row)
    dest = out / "funclet_obj"
    dest.mkdir(parents=True, exist_ok=True)
    swaps, labels, manifest, counts, refused = {}, {}, [], collections.Counter(), []
    for obj, obj_rows in sorted(by_obj.items()):
        data = obj.read_bytes()
        sections, symbols = RL.parse_coff(data)
        defined = {s["name"] for s in symbols.values() if s["section"] > 0 and s["storage"] == EXTERNAL}
        found = []
        for row in sorted(obj_rows, key=lambda r: r["target_rva"]):
            va = img.base + int(row["target_rva"], 16)
            target = img.read(va, int(row["target_size"]))
            sym, how = find_funclet(sections, symbols, row, target)
            if sym is None or g_name(va) in defined:
                how = how if sym is None else "name-taken"
                counts["to-dump:" + how] += 1
                manifest.append([f"0x{va:08X}", "", obj.name, build.ledger_object_symbol(row), "", "", how,
                                 va in eh_targets])
                refused.append(row)
                continue
            found.append((va, sym, how, row))
        # one compiled body standing for several retail funclets (a generator's
        # representative, equal outside relocation fields) names none of them:
        # each gets its own relocatable body from retail's bytes instead
        shared = collections.Counter((sym["section"], sym["value"]) for _, sym, _, _ in found)
        new = []
        for va, sym, how, row in found:
            if shared[(sym["section"], sym["value"])] > 1:
                counts["to-dump:shared-label"] += 1
                manifest.append([f"0x{va:08X}", "", obj.name, sym["name"], sym["section"], f"{sym['value']:#x}",
                                 f"shared-by-{shared[(sym['section'], sym['value'])]}", va in eh_targets])
                refused.append(row)
                continue
            name = g_name(va)
            new.append((name, sym["value"], sym["section"]))
            labels[va] = name
            counts["labelled"] += 1
            counts["eh-expected" if va in eh_targets else "not-in-an-eh-table"] += 1
            manifest.append([f"0x{va:08X}", name, obj.name, sym["name"], sym["section"], f"{sym['value']:#x}",
                             how, va in eh_targets])
        if new:
            copy = dest / obj.name
            copy.write_bytes(append_symbols(data, new))
            swaps[obj.resolve()] = copy
    with (out / "funclet_labels.csv").open("w", newline="", encoding="utf-8") as handle:
        w = csv.writer(handle, lineterminator="\n")
        w.writerow(["va", "label", "object", "local_symbol", "section", "offset", "found_by", "eh_table_expects"])
        w.writerows(sorted(manifest))
    log(f"code_scaffold: funclet labels {dict(counts)} in {len(swaps):,} object copies")
    return swaps, labels, counts, refused


FUNCLETS_PER_OBJECT = 500


def funclet_dumps(img, rows, out, log=print):
    """Relocatable bodies `g_<VA>` from retail's bytes for funclets no compiled label
    can name, through tools/dump_relocs.py's classifier, emitter and verifier
    (retail placement equals retail; every reference moves at a shifted one).
    Returns ({va: name}, [object paths], counts)."""
    import dump_relocs
    ctx = dump_relocs.load_context()
    dump_relocs.OUT = out / "funclet_dumps"
    (dump_relocs.OUT / "asm").mkdir(parents=True, exist_ok=True)
    (dump_relocs.OUT / "obj").mkdir(parents=True, exist_ok=True)
    for old in (dump_relocs.OUT / "obj").glob("*.obj"):
        old.unlink()
    ordered = sorted(rows, key=lambda r: int(r["target_rva"], 16))
    names, objects, counts = {}, [], collections.Counter()
    for k in range(0, len(ordered), FUNCLETS_PER_OBJECT):
        source = f"funclet_dumps/part_{k // FUNCLETS_PER_OBJECT:03d}.asm"
        items = []
        for row in ordered[k:k + FUNCLETS_PER_OBJECT]:
            va = img.base + int(row["target_rva"], 16)
            size = int(row["target_size"])
            retail = img.read(va, size)
            summary = {"symbol": g_name(va), "ambiguous": 0, "unreached": 0, "_hard": [], "status": "",
                       "reasons": ""}
            c = dump_relocs.classify(retail, va, ctx, g_name(va))
            c["analysis"]["ambiguous_sites"] = {a[0] for a in c["ambiguous"]}
            if c["failures"] or c["tables"]:
                counts["refused:" + ";".join(sorted({f[0] for f in c["failures"]}) or ["table"])] += 1
                continue
            summary["ambiguous"] = len(c["ambiguous"])
            items.append((g_name(va), va, retail, c["relocs"], c["analysis"], summary, False))
        if not items:
            continue
        dump_relocs.finish_source(source, items, ctx)
        stem = re.sub(r"[^A-Za-z0-9_]+", "_", Path(source).with_suffix("").as_posix())
        obj = dump_relocs.OUT / "obj" / f"{stem}.obj"
        for name, va, *_, summary, _ in items:
            status = summary["status"] or "failed"
            counts[status] += 1
            if status in ("exact", "ambiguous") and obj.exists():
                names[va] = name
        if obj.exists():
            objects.append(obj)
    log(f"code_scaffold: funclet bodies from retail bytes {dict(counts)} in {len(objects)} objects")
    return names, objects, counts


def object_externals(paths):
    """(defined, referenced) external names over COFF objects."""
    defined, referenced = set(), set()
    for path in paths:
        for s in build.read_object_symbols(Path(path).read_bytes()):
            if s["storage"] == EXTERNAL and s["name"]:
                (defined if s["section"] > 0 else referenced).add(s["name"])
            elif s["storage"] == 105 and s["name"]:
                defined.add(s["name"])  # a weak external resolves itself (or fails on its own)
    return defined, referenced


def code_aliases(img, rows, undefined, defined, funclets, skip=frozenset(), dir32=None, calls=None):
    """{undefined name: defining name} for names with a retail code address."""
    if dir32 is None:
        dir32 = {r["name"]: int(r["va"], 16) for r in RL.read_csv_rows(build.DIR32_ADDRESSES)}
    if calls is None:
        calls = call_targets(img)
    routes = {}
    pinned = link_census.pins(routes)
    by_address = collections.defaultdict(list)
    stubs = {}
    for row in rows:
        address = int(row["target_rva"], 16)
        if row["name"].startswith("?j_"):
            target = link_census._thunk_target(row.get("notes"))
            if target is not None:
                stubs.setdefault(address, target)
        else:
            by_address[address].append(row)
    # a name that is the object symbol of exactly one ledger address (dump_relocs
    # spells a row's target by its object symbol, `$Lnnnn` funclet pins included)
    homes = collections.defaultdict(set)
    for row in rows:
        homes[build.ledger_object_symbol(row)].add(int(row["target_rva"], 16))
    exported = {}

    def object_name(row):
        va = img.base + int(row["target_rva"], 16)
        if "gen-funclet" in (row.get("notes") or ""):
            return funclets.get(va)
        obj = build.row_object(row)
        if obj not in exported:
            try:
                exported[obj] = {s["name"] for s in build.read_object_symbols(obj.read_bytes())
                                 if s["section"] > 0 and s["storage"] == EXTERNAL}
            except OSError:
                exported[obj] = set()
        wanted = build.ledger_object_symbol(row)
        if wanted in exported[obj]:
            return wanted
        normal = ANON.sub("?A0xHASH", wanted)
        found = [n for n in exported[obj] if ANON.sub("?A0xHASH", n) == normal]
        return found[0] if len(found) == 1 else None

    def defining(address, depth=0):
        owners = by_address.get(address)
        if owners:
            ranked = sorted(owners, key=lambda r: (not (r["source"].startswith("game/") and not r["source"].startswith(
                ("game/gen_small/", "game/gen_asm/"))), r["name"]))
            for row in ranked:
                name = object_name(row)
                if name and name in defined:
                    return name
            return None
        if depth < 2 and address in stubs:
            return defining(stubs[address], depth + 1)
        return None

    table, why = {}, collections.Counter()
    for name in sorted(undefined):
        if name in skip:
            continue
        m = re.fullmatch(r"g_([0-9A-F]{8})", name)
        if m:
            va = int(m.group(1), 16)
            if img.section(va) != ".text":
                continue
            address = va - img.base
            kind = "g_text"
        else:
            address, kind = routes.get(name), "pinned"
            if address is None and name in pinned:
                address, how = resolve_pin(name, pinned[name],
                                           lambda rva: bool(by_address.get(rva)) or rva in stubs, dir32, calls)
                if address is None:
                    why["pinned:" + how] += 1
                    continue
            if address is None and len(homes.get(name, ())) == 1:
                address, kind = next(iter(homes[name])), "row-symbol"
            if address is None:
                continue
        target = defining(address)
        if target and target != name:
            table[name] = target
            why[kind + (":via-ilt" if address in stubs else "")] += 1
        else:
            why[kind + ":no-exported-definer"] += 1
    return table, why
