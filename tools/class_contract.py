#!/usr/bin/env python3
"""The ABI contract of one class, decided from evidence in a fixed rule order.

WHY. A canonical header is only as good as the claims it freezes: sizeof,
every field's offset, width and name, the class-key (which the mangled names
of every ledger row spell: `U` struct, `V` class), the bases and the virtual
slots. The private views disagree on spelling almost always and on layout
rarely, so the question is never "which view is right" but "which evidence
settles this one attribute". This tool answers it per attribute, in the
order research 11 fixed, stopping at the first rule that decides:

  1. bytes        what byte-matched code proves: an attribute every compiled
                  view agrees on, and the class-key the ledger's matched names
                  mangle (each row's name is verified by the gate);
  2. retail-access  widths of `this`-relative reads and writes in the retail
                  bodies of the class's own member functions (capstone), and
                  BFME1's ZH<->retail field witnesses (bfme_layouts.json);
  3. retail-vtable  vftable stores in retail constructors and the slots that
                  vtables.tsv lists for that table;
  4. zh           the Zero Hour header's own layout (compiled, -Z7), names and
                  class-key;
  5. majority     of the views, for names only.

An attribute still tied after all five is a queue item, never a guess. The
contract is written next to the canonical header (reverse/class_contracts/)
so the evidence a header was generated from is reviewable and re-checkable.

    python3 tools/class_contract.py --class Coord3D            summary
    python3 tools/class_contract.py --class Coord3D --write    freeze the contract
"""
import argparse
import collections
import concurrent.futures as cf
import csv
import json
import os
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import class_layouts  # noqa: E402

if (ROOT / "reverse" / "functions.csv").exists():                    # Open-BFME-2
    REVERSE, CODE = ROOT / "reverse", ("Code/",)
else:                                                                 # Open-BFME-1
    REVERSE, CODE = ROOT / "targets" / "game" / "reverse", ("game/",)
LEDGER = REVERSE / "functions.csv"
CONTRACTS = REVERSE / "class_contracts"
GENERATED = ("Code/gen_asm/", "Code/gen_small/", "game/gen_small/", "game/gen_asm/")
PRIMK = {"float": "f4", "double": "f8", "int": "i4", "uint": "i4", "long": "i4", "ulong": "i4", "short": "i2",
         "ushort": "i2", "char": "i1", "uchar": "i1", "bool": "i1", "int64": "i8", "uint64": "i8", "enum": "i4",
         "wchar": "i2", "int8": "i1", "uint8": "i1"}
PAD = re.compile(r"^(m_)?(pad|_pad|unk|gap|reserved)", re.I)


# ---------------------------------------------------------------- evidence: views

def ledger_rows():
    with LEDGER.open(newline="", encoding="utf-8") as handle:
        return [r for r in csv.DictReader(handle) if r["status"] == "matched"]


def census(name, rows=None):
    """Ledger sources (authored) that declare their own body for `name`."""
    sources = sorted({r["source"] for r in (rows or ledger_rows())
                      if r["source"].lower().endswith((".cpp", ".c")) and not r["source"].startswith(GENERATED)})
    head = re.compile(r"^[ \t]*(?:class|struct)[ \t]+(?:__declspec\([^)]*\)\s+)?" + re.escape(name) + r"\s*(?::[^{;]*)?\{", re.M)
    out = []
    for source in sources:
        try:
            text = (ROOT / source).read_text(encoding="latin-1")
        except OSError:
            continue
        if head.search(text) and name in class_layouts.class_bodies(text):
            out.append(source)
    return out


def views(name, sources, jobs=8):
    """{source: layout or {'error': ...}} for the private views of `name`."""
    builder = class_layouts.build_module()

    def one(source):
        try:
            got = class_layouts.private_views(source, builder, {name})
            return source, got.get(name) or {"error": "no CodeView record"}, got
        except RuntimeError as exc:
            return source, {"error": str(exc)}, {}
    out, every = {}, {}
    with cf.ThreadPoolExecutor(jobs) as pool:
        for source, layout, got in pool.map(one, sources):
            out[source], every[source] = layout, got
    return out, every


def kind(type_name):
    if type_name.endswith("*"):
        return "P"
    if "[" in type_name:
        return "A"
    return PRIMK.get(type_name, "S:" + type_name)


def flatten(layout, every, base=0, depth=0):
    """[(offset, size, kind, name, type)] with known bases expanded and pads dropped."""
    out = []
    if layout.get("vfptr") and not layout.get("bases"):
        out.append((base, 4, "VPTR", "__vfptr", "void*"))
    for base_name, offset in layout.get("bases", []):
        if base_name in every and depth < 6:
            out += flatten(every[base_name], every, base + max(offset, 0), depth + 1)
    for offset, field, type_name, size in layout.get("fields", []):
        if PAD.match(field) or (type_name.startswith(("char[", "uchar[")) and field.startswith(("pad", "_", "m_pad"))):
            continue
        out.append((base + offset, size, kind(type_name), field, type_name))
    return out


# ---------------------------------------------------------------- evidence: retail

def thiscall_rows(name, rows):
    member = re.compile(r"^\?(\w+)@" + re.escape(name) + r"@@[AIQ][AB]E")
    ctor = re.compile(r"^\?\?0" + re.escape(name) + r"@@[AIQ]AE")
    return ([r for r in rows if member.match(r["name"])], [r for r in rows if ctor.match(r["name"])])


def retail_access(name, rows, builder):
    """{offset: Counter(width)} from `this`-relative operands in retail member bodies."""
    import capstone
    from capstone import x86
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    members, _ = thiscall_rows(name, rows)
    seen = collections.defaultdict(collections.Counter)
    for row in members[:400]:
        try:
            code = builder.read_target_bytes(int(row["target_rva"], 16), int(row["target_size"], 0))
        except Exception:
            continue
        this = {x86.X86_REG_ECX}
        for insn in md.disasm(code, 0):
            ops = insn.operands
            for op in ops:
                if op.type == x86.X86_OP_MEM and op.mem.base in this and op.mem.index == 0 and 0 <= op.mem.disp < 0x10000:
                    seen[op.mem.disp][op.size] += 1
            if insn.mnemonic == "mov" and len(ops) == 2 and ops[0].type == x86.X86_OP_REG and ops[1].type == x86.X86_OP_REG \
                    and ops[1].reg in this:
                this.add(ops[0].reg)
                continue
            written = insn.regs_access()[1]
            this -= set(written)
            if insn.mnemonic == "call":
                this -= {x86.X86_REG_ECX, x86.X86_REG_EAX, x86.X86_REG_EDX}
            if not this or insn.mnemonic in ("ret", "jmp"):
                break
    return {off: dict(c) for off, c in sorted(seen.items())}


def witnesses(name):
    """{offset: votes} from BFME1's ZH<->retail aligned field witnesses."""
    path = REVERSE / "bfme_layouts.json"
    if not path.exists():
        return {}
    out = {}
    for entry in json.loads(path.read_text(encoding="utf-8")):
        if entry.get("owner") == name and entry.get("bfme") is not None and entry.get("confidence", 0) >= 0.9:
            out[int(entry["bfme"])] = entry.get("votes")
    return out


def retail_vtable(name, rows, builder):
    """vftable RVAs stored at [this+0] by retail constructors, with their vtables.tsv slots."""
    import capstone
    from capstone import x86
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    base = getattr(builder, "IMAGE_BASE", 0x400000)
    _, ctors = thiscall_rows(name, rows)
    tables = collections.Counter()
    for row in ctors:
        try:
            code = builder.read_target_bytes(int(row["target_rva"], 16), int(row["target_size"], 0))
        except Exception:
            continue
        for insn in md.disasm(code, 0):
            ops = insn.operands
            if insn.mnemonic == "mov" and len(ops) == 2 and ops[0].type == x86.X86_OP_MEM and ops[0].mem.disp == 0 \
                    and ops[1].type == x86.X86_OP_IMM and ops[1].imm > base:
                tables[ops[1].imm - base] += 1
    slots = collections.defaultdict(dict)
    path = REVERSE / "vtables.tsv"
    if tables and path.exists():
        with path.open(newline="", encoding="utf-8") as handle:
            for row in csv.DictReader(handle, delimiter="\t"):
                rva = int(row["vtable_rva"], 16)
                if rva in tables:
                    slots[rva][int(row["slot"])] = row["func_name"]
    return {"%#x" % rva: {"stores": count, "slots": slots.get(rva, {})} for rva, count in tables.items()}


def ledger_key(name, rows):
    """Counter of the class-key the matched ledger names mangle: U = struct, V = class."""
    marks = collections.Counter()
    for row in rows:
        for found in re.finditer(r"([UV])" + re.escape(name) + r"@@", row["name"]):
            marks["struct" if found.group(1) == "U" else "class"] += 1
    return marks


def zh_layout(name, builder):
    """The Zero Hour header's layout of `name`, compiled with the ZH flags; None if absent."""
    zh_root = getattr(builder, "ZH_REFERENCE_ROOT", None)
    if zh_root is None or not Path(zh_root).exists():
        return None
    head = re.compile(r"^(?:class|struct)\s+" + re.escape(name) + r"\b[^;]*\{", re.M)
    header = None
    for path in sorted(Path(zh_root).rglob("*.h")):
        try:
            if head.search(path.read_text(encoding="latin-1")):
                header = path
                break
        except OSError:
            continue
    if header is None:
        return None
    shown = header.as_posix()
    shown = shown[shown.find("CnC_Generals_Zero_Hour"):]
    probe = class_layouts.CACHE / f"zh_{name}.cpp"
    probe.parent.mkdir(parents=True, exist_ok=True)
    # The header alone first: PreRTS.h drags in STLport, which these flags do not set up.
    every, failure = None, None
    for prelude in ("", '#include "PreRTS.h"\n'):
        probe.write_text(f'{prelude}#include "{header.as_posix()}"\n'
                         f"int zh_probe({name} *p) {{ return sizeof(*p); }}\n", encoding="utf-8")
        try:
            every = class_layouts.compile_layouts(probe.relative_to(ROOT), builder, True, list(builder._ZH_FLAGS))
            break
        except (RuntimeError, AttributeError) as exc:
            failure = str(exc)[:300]
    if every is None:
        return {"header": shown, "error": failure}
    layout = every.get(name)
    if not layout or layout.get("fwd"):
        return {"header": shown, "error": "no CodeView record"}
    return {"header": shown, "layout": layout, "every": every}


# ---------------------------------------------------------------- decision

def decide(name, sources=None, jobs=8, sample=None):
    builder = class_layouts.build_module()
    rows = ledger_rows()
    sources = sources or census(name, rows)
    if sample and len(sources) > sample:
        import random
        sources = sorted(random.Random(20261006).sample(sources, sample))
    got, every = views(name, sources, jobs)
    good = {s: L for s, L in got.items() if "error" not in L}
    flat = {s: flatten(L, every[s]) for s, L in good.items()}
    zh = zh_layout(name, builder)
    zh_flat = flatten(zh["layout"], zh["every"]) if zh and "layout" in zh else []
    zh_at = {o: (s, k, n, t) for o, s, k, n, t in zh_flat}
    access = retail_access(name, rows, builder)
    witness = witnesses(name)
    vtables = retail_vtable(name, rows, builder)
    queue, fields = [], []

    candidates = collections.defaultdict(collections.Counter)
    names = collections.defaultdict(collections.Counter)
    types = collections.defaultdict(collections.Counter)
    for source, items in flat.items():
        for offset, size, k, field, type_name in items:
            candidates[offset][(size, k)] += 1
            names[offset][field] += 1
            types[(offset, size, k)][type_name] += 1
    # A field past the majority sizeof that only a minority of views declares is
    # that view's own claim (a pad-as-members view, a different type wearing the
    # name): recorded, never frozen into the contract. The unit's gate decides it.
    major_size = collections.Counter(L["size"] for L in good.values()).most_common(1)[0][0] if good else 0
    outliers = []
    for offset in sorted(candidates):
        votes = candidates[offset]
        if offset >= major_size and 2 * sum(votes.values()) < len(flat):
            outliers.append({"offset": offset, "views": sum(votes.values()),
                             "sources": sorted(s for s, items in flat.items() if any(o == offset for o, *_ in items))})
            continue
        rule, pick = None, None
        if len(votes) == 1:
            rule, pick = "bytes", next(iter(votes))
        else:
            widths = access.get(offset, {})
            fits = [c for c in votes if c[0] in widths and len(widths) == 1]
            if len(fits) == 1:
                rule, pick = "retail-access", fits[0]
            elif offset in zh_at and (zh_at[offset][0], zh_at[offset][1]) in votes:
                rule, pick = "zh", (zh_at[offset][0], zh_at[offset][1])
            else:
                top = votes.most_common(2)
                if top[0][1] > top[1][1]:
                    rule, pick = "majority", top[0][0]
                else:
                    queue.append({"class": name, "attribute": f"field@{offset:#x}", "candidates":
                                  {f"{s}:{k}": n for (s, k), n in votes.items()}})
                    continue
        if offset in zh_at:
            label, label_rule = zh_at[offset][2], "zh"
        else:
            top = names[offset].most_common(2)
            label, label_rule = top[0][0], "majority" if len(top) < 2 or top[0][1] > top[1][1] else "tie"
            if label_rule == "tie":
                queue.append({"class": name, "attribute": f"name@{offset:#x}", "candidates": dict(names[offset])})
        type_name = types[(offset, *pick)].most_common(1)[0][0]
        if offset in zh_at and (zh_at[offset][0], zh_at[offset][1]) == pick:
            type_name = zh_at[offset][3]
        fields.append({"offset": offset, "size": pick[0], "kind": pick[1], "type": type_name, "name": label,
                       "decided_by": rule, "name_by": label_rule, "views": sum(votes.values()),
                       "retail_widths": access.get(offset, {}), "witness": witness.get(offset)})
    # A field that straddles another decided field is a layout conflict, whatever the votes say.
    spans = [(f["offset"], f["offset"] + f["size"]) for f in fields if f["size"]]
    for f in fields:
        if any(a < f["offset"] < b for a, b in spans):
            queue.append({"class": name, "attribute": f"straddle@{f['offset']:#x}", "candidates": {}})

    sizes = collections.Counter(L["size"] for L in good.values())
    end = max((f["offset"] + f["size"] for f in fields), default=0)
    if zh and "layout" in zh and zh["layout"]["size"] >= end and zh["layout"]["size"] in sizes:
        size, size_rule = zh["layout"]["size"], "zh"
    else:
        fitting = collections.Counter({s: n for s, n in sizes.items() if s >= end})
        top = fitting.most_common(2)
        size, size_rule = (top[0][0], "majority") if top and (len(top) < 2 or top[0][1] > top[1][1]) else (end, "tie")
        if size_rule == "tie":
            queue.append({"class": name, "attribute": "size", "candidates": dict(sizes)})

    keys = ledger_key(name, rows)
    if keys and (len(keys) == 1 or keys.most_common(2)[0][1] > keys.most_common(2)[1][1]):
        key, key_rule = keys.most_common(1)[0][0], "bytes"
    elif zh and "layout" in zh:
        key, key_rule = zh["layout"]["key"], "zh"
    else:
        view_keys = collections.Counter(L["key"] for L in good.values())
        key, key_rule = view_keys.most_common(1)[0][0] if view_keys else "struct", "majority"

    zh_bases = [b for b, _ in zh["layout"]["bases"]] if zh and "layout" in zh else None
    base_votes = collections.Counter(tuple(b for b, _ in L.get("bases", [])) for L in good.values())
    if zh_bases is not None and tuple(zh_bases) in base_votes:
        bases, base_rule = zh_bases, "zh"
    else:
        bases, base_rule = (list(base_votes.most_common(1)[0][0]) if base_votes else []), "majority"

    slot_votes = collections.defaultdict(collections.Counter)
    for L in good.values():
        for slot, member in L.get("vslots", {}).items():
            slot_votes[int(slot)][member] += 1
    retail_slots = max((len(v["slots"]) for v in vtables.values()), default=None)
    zh_slots = {int(k): v for k, v in zh["layout"].get("vslots", {}).items()} if zh and "layout" in zh else {}
    vslots = {}
    for slot, votes in sorted(slot_votes.items()):
        if retail_slots is not None and slot >= retail_slots:
            queue.append({"class": name, "attribute": f"slot{slot}", "candidates": dict(votes),
                          "why": f"beyond the retail vftable's {retail_slots} slots"})
            continue
        if len(votes) == 1:
            vslots[slot] = (next(iter(votes)), "bytes")
        elif zh_slots.get(slot) in votes:
            vslots[slot] = (zh_slots[slot], "zh")
        else:
            top = votes.most_common(2)
            if top[0][1] > top[1][1]:
                vslots[slot] = (top[0][0], "majority")
            else:
                queue.append({"class": name, "attribute": f"slot{slot}", "candidates": dict(votes)})

    return {
        "class": name, "key": key, "key_by": key_rule, "ledger_keys": dict(keys), "size": size, "size_by": size_rule,
        "bases": bases, "bases_by": base_rule, "fields": fields,
        "vslots": {str(k): {"member": m, "decided_by": r} for k, (m, r) in vslots.items()},
        "evidence": {"views": len(good), "view_errors": len(got) - len(good), "census": len(sources),
                     "view_sizes": dict(sizes), "zh": {k: v for k, v in (zh or {}).items() if k in ("header", "error")},
                     "retail_member_rows": len(thiscall_rows(name, rows)[0]),
                     "retail_access": {"%#x" % k: v for k, v in access.items()},
                     "witness_offsets": sorted(witness), "retail_vtables": vtables},
        "queue": queue,
        "outliers": outliers,
        "sources": sorted(good),
    }


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--class", dest="name", required=True)
    parser.add_argument("--sample", type=int, help="decide from a seeded sample of N views")
    parser.add_argument("--jobs", type=int, default=max(2, (os.cpu_count() or 4) - 4))
    parser.add_argument("--write", action="store_true", help=f"write {CONTRACTS.relative_to(ROOT).as_posix()}/NAME.json")
    args = parser.parse_args(argv)
    contract = decide(args.name, jobs=args.jobs, sample=args.sample)
    if args.write:
        CONTRACTS.mkdir(parents=True, exist_ok=True)
        frozen = {k: v for k, v in contract.items() if k != "sources"}
        (CONTRACTS / f"{args.name}.json").write_text(json.dumps(frozen, indent=1, sort_keys=True) + "\n", encoding="utf-8")
    ev = contract["evidence"]
    print(f"{args.name}: {contract['key']} ({contract['key_by']}), sizeof {contract['size']} ({contract['size_by']}), "
          f"bases {contract['bases']} ({contract['bases_by']}); {ev['views']} views, {ev['view_errors']} uncompiled, "
          f"zh {ev['zh'].get('header', '-')}")
    for f in contract["fields"]:
        print(f"  +{f['offset']:#05x} {f['size']} {f['type']:<12} {f['name']:<16} {f['decided_by']}/{f['name_by']}"
              f"  views={f['views']} retail={f['retail_widths']} witness={f['witness']}")
    for slot, v in contract["vslots"].items():
        print(f"  slot {slot}: {v['member']} ({v['decided_by']})")
    for item in contract["queue"]:
        print(f"  QUEUE {item['attribute']}: {item.get('candidates')} {item.get('why', '')}")
    return 1 if contract["queue"] else 0


if __name__ == "__main__":
    sys.exit(main())
