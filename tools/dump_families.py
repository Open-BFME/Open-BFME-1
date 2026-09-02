#!/usr/bin/env python3
"""Group dump rows into subsystem families by RARE shared callees and constants.

`family_scan.py` finds bodies that are the same function with different
constants. This is the other clustering: bodies that are DIFFERENT functions
from the same subsystem -- they call the same rare helpers, touch the same
globals, install the same vtables -- so one class model, one set of pins, or
one shim unlocks all of them. Vtable-only clustering misses free functions
(VP6, SSE filters, Lua, pathfinder callbacks); callees and constants do not.

Features per body (from the retail bytes, via capstone):
  * REL32 call/jmp targets, resolved to RVAs
  * DIR32 immediates/displacements that land in .rdata/.data (globals, vtables,
    string literals, jump tables)
Features shared by more than --common bodies (operator new, memcpy, ...) are
ignored. A family is one rare feature plus every dump body that uses it (no
transitive closure: chaining through shared helpers merged the whole game into
one 3,297-body hairball). Families overlap; each is an honest "pin or model this
one thing and these bodies share the unlock".

  python3 tools/dump_families.py                      # top families by bytes
  python3 tools/dump_families.py --out families.csv   # full listing
  python3 tools/dump_families.py --show 3             # members + shared features of family 3

Read-only.
"""
import argparse
import collections
import csv
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build

ROOT = Path(__file__).resolve().parents[1]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--common", type=int, default=50, help="ignore features shared by more than this many bodies")
    ap.add_argument("--min", type=int, default=4, help="minimum bodies sharing a feature to report it as a family")
    ap.add_argument("--out")
    ap.add_argument("--show", type=int)
    ap.add_argument("--top", type=int, default=25)
    a = ap.parse_args()

    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True

    image = open(build.EXE, "rb").read()
    secs = build.pe_sections(image)
    by = {s["name"]: (s["rva"], s["rva"] + s["size"]) for s in secs}
    tlo, thi = by[".text"]
    dlo = by[".rdata"][0]
    dhi = by[".data"][1]

    names = {}
    pin_names = {}
    for r in csv.reader(open(ROOT / "reverse/symbols.csv", newline="", encoding="utf-8", errors="replace")):
        if len(r) > 1 and r[1].startswith("0x"):
            try:
                v = int(r[1], 16)
            except ValueError:
                continue
            if not r[0].startswith(("?d_", "?b_", "?j_", "?dup_")):
                pin_names.setdefault(v, r[0])
    dump = []
    for r in csv.DictReader(open(ROOT / "reverse/functions.csv", newline="", encoding="utf-8", errors="replace")):
        try:
            rva = int(r["target_rva"], 16)
        except ValueError:
            continue
        names[rva] = r["name"]
        if r["source"].endswith((".asm", ".s")):
            dump.append((rva, int(r["target_size"] or 0), r["source"]))

    feats = {}
    for rva, size, src in dump:
        if size < 16:
            continue
        off = build.rva_to_file_offset(secs, rva)
        body = image[off: off + size]
        fs = set()
        for ins in md.disasm(body, rva):
            if ins.mnemonic in ("call", "jmp") and ins.operands and ins.operands[0].type == capstone.x86.X86_OP_IMM:
                t = ins.operands[0].imm
                if tlo <= t < thi and not (rva <= t < rva + size):
                    fs.add(("call", t))
            for op in ins.operands:
                v = None
                if op.type == capstone.x86.X86_OP_IMM:
                    v = op.imm
                elif op.type == capstone.x86.X86_OP_MEM and op.mem.base == 0 and op.mem.index == 0:
                    v = op.mem.disp
                if v is not None and v >= 0x400000 and dlo <= v - 0x400000 < dhi:
                    fs.add(("data", v))
        feats[rva] = fs

    freq = collections.Counter(f for fs in feats.values() for f in fs)
    rare = {f for f, c in freq.items() if 2 <= c <= a.common}
    index = collections.defaultdict(set)
    for rva, fs in feats.items():
        for f in fs & rare:
            index[f].add(rva)

    # One family per rare feature: every dump body that shares it. No transitive
    # closure -- chaining through shared helpers merges the whole game into one
    # hairball (3,297 bodies on the first run). Overlap between families is fine;
    # each is an honest "pin/model this one thing and these bodies share the unlock".
    sizes = {rva: s for rva, s, _ in dump}
    ranked = sorted(((sum(sizes[m] for m in ms), f, sorted(ms)) for f, ms in index.items() if len(ms) >= a.min), reverse=True)

    def shared_features(ms):
        c = collections.Counter(f for m in ms for f in feats[m] & rare)
        return [(f, n) for f, n in c.most_common(8) if n >= 2]

    def fname(f):
        kind, v = f
        if kind == "call":
            nm = pin_names.get(v) or names.get(v, "?")
            return f"call {nm[:55]} @{v:#x}"
        nm = pin_names.get(v) or pin_names.get(v - 0x400000) or ""
        return f"data {v:#x}" + (f" ({nm[:35]})" if nm else "")

    if a.show is not None:
        b, root, ms = ranked[a.show - 1]
        print(f"family {a.show}: {len(ms)} bodies, {b} bytes, anchored on {fname(root)}")
        for f, n in shared_features(ms):
            print(f"  shared by {n}: {fname(f)}")
        for m in sorted(ms, key=lambda v: sizes[v]):
            print(f"  0x{m:08X} {sizes[m]:5}B {names[m][:60]}")
        return

    print(f"dump bodies analysed: {len(feats)}; rare features: {len(rare)}; feature families ({a.min}+ bodies): {len(ranked)}")
    for i, (b, root, ms) in enumerate(ranked[:a.top], 1):
        print(f"{i:3}. {b:7} B {len(ms):4} bodies  anchor: {fname(root)}")
    if a.out:
        with open(a.out, "w", newline="") as f:
            w = csv.writer(f)
            w.writerow(["family", "bytes", "bodies", "rva", "size", "name", "shared_features"])
            for i, (b, root, ms) in enumerate(ranked, 1):
                sf = "; ".join(fname(f) for f, _ in shared_features(ms)[:4])
                for m in sorted(ms, key=lambda v: sizes[v]):
                    w.writerow([i, b, len(ms), f"0x{m:08x}", sizes[m], names[m], sf])
        print("wrote", a.out)


if __name__ == "__main__":
    main()
