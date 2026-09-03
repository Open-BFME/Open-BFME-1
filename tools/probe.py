#!/usr/bin/env python3
"""Compile one TU, diff one symbol against retail, and name the wall.

Read-only: writes only its own scratch object under build/probe/, never touches
the ledgers or the lock. This is the inner loop of every conversion, packaged:

  python3 tools/probe.py Code/.../Foo.cpp "?bar@Foo@@QAEXXZ" 0x0048ACF0 [--size N] [--all]

Prints size, the non-relocation byte diffs, a side-by-side disassembly around
the first divergence, and a SYMPTOM -> LEVER line keyed to docs/shape_levers.md:

  sib-order            same instruction, base/index registers swapped
  register-mirror      same instruction stream, one or more registers renamed
  eh-transposition     `mov [esp+N],esp` and `mov ecx,esp` in swapped order
  adjacent-swap        two adjacent instructions in swapped order
  length-delta         instruction streams diverge in length (shape/CSE/inline)
  exact                byte-identical outside relocation slots

Size defaults to retail's ledger row for the RVA when one exists.
"""
import argparse
import csv
import hashlib
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build

ROOT = Path(__file__).resolve().parents[1]
LEVERS = {
    "exact": "nothing to do -- land it with tools/add_match.py",
    "sib-order": "shape_levers.md row 1: add the pointer as an integer on the right of the counter: *(T*)(i + (unsigned)p)",
    "eh-transposition": "shape_levers.md row 2: by-value string class must be `: private StringBase<T>` with INLINE forwarding copy ctor/dtor (reference/shims/stringinline/StringInline.h)",
    "register-mirror": "shape_levers.md rows 3-5: reorder local DEFINITIONS to retail's first-use order; copy params to locals just before the guard; call dllimports directly (IAT CSE)",
    "adjacent-swap": "shape_levers.md rows 3-4: two values materialized in the other order -- swap the two local DEFINITIONS (or move the param copies to just before the guard); if one side is an EH state store see row 2",
    "length-delta": "shape/CSE/inline difference at the first divergent instruction -- see shape_levers.md rows 6, 8, 9 (flag tail, `new` statement, trivially-copyable arg)",
}


def ledger_size(rva):
    with open(ROOT / "reverse/functions.csv", newline="", encoding="utf-8", errors="replace") as f:
        for r in csv.DictReader(f):
            try:
                if int(r["target_rva"], 16) == rva:
                    return int(r["target_size"])
            except ValueError:
                pass
    return None


def disasm(data, base=0):
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    return list(md.disasm(bytes(data), base))


def masked(data, relocs):
    d = bytearray(data)
    for ro, _t, _n in relocs:
        for k in range(4):
            if ro + k < len(d):
                d[ro + k] = 0
    return bytes(d)


REG = re.compile(r"\b(e?[abcd]x|e?[sd]i|e?[sb]p|[abcd][lh])\b")


def skeleton(ins):
    """Instruction with registers blanked, to detect renames."""
    return ins.mnemonic + " " + REG.sub("R", ins.op_str)


def classify(ret_ins, our_ins, ret_b, our_b):
    if ret_b == our_b:
        return "exact"
    if len(ret_ins) != len(our_ins) or len(ret_b) != len(our_b):
        return "length-delta"
    swaps = renames = sib = 0
    eh = False
    i = 0
    n = len(ret_ins)
    while i < n:
        r, o = ret_ins[i], our_ins[i]
        if r.bytes == o.bytes:
            i += 1
            continue
        if i + 1 < n and ret_ins[i].bytes == our_ins[i + 1].bytes and ret_ins[i + 1].bytes == our_ins[i].bytes:
            swaps += 1
            pair = (r.op_str.strip(), ret_ins[i + 1].op_str.strip())
            if any(p.startswith("dword ptr [esp") and p.endswith(", esp") for p in pair) and "ecx, esp" in pair:
                eh = True
            i += 2
            continue
        if r.mnemonic == o.mnemonic and skeleton(r) == skeleton(o):
            rr = set(REG.findall(r.op_str))
            oo = set(REG.findall(o.op_str))
            if rr == oo and "[" in r.op_str and r.op_str != o.op_str:
                sib += 1
            else:
                renames += 1
            i += 1
            continue
        renames += 1
        i += 1
    if eh:
        return "eh-transposition"
    if sib and not renames and not swaps:
        return "sib-order"
    if swaps and not renames:
        return "adjacent-swap"
    return "register-mirror"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("source")
    ap.add_argument("symbol")
    ap.add_argument("rva", help="retail RVA as in the ledger (use --va if you pass a 0x4xxxxxxx virtual address)")
    ap.add_argument("--va", action="store_true", help="the address is a VA; subtract the 0x400000 image base")
    ap.add_argument("--size", type=int)
    ap.add_argument("--all", action="store_true", help="print the whole side-by-side, not just the divergence window")
    a = ap.parse_args()

    rva = int(a.rva, 16)
    if a.va:
        rva -= 0x400000
    src = Path(a.source)
    src = src if src.is_absolute() else (ROOT / src).resolve()
    tag = hashlib.md5(str(src).encode()).hexdigest()[:10]
    objdir = ROOT / "build" / "probe"
    objdir.mkdir(parents=True, exist_ok=True)
    obj = objdir / f"{src.stem}_{tag}.obj"

    build.compile_source(src, obj)
    try:
        compiled, relocs = build.read_object_symbol_bytes(obj, a.symbol)
    except ValueError as e:
        if "symbol not found in object" not in str(e):
            raise
        # The most common worker failure: a guessed mangled name. Show what the
        # object actually defines, nearest first, so the fix is one copy-paste.
        import difflib
        syms = [s["name"] for s in build.read_object_symbols(obj.read_bytes())
                if s["section"] > 0 and s["name"].startswith(("?", "_", "@")) and not s["name"].startswith(("$", ".", "__real", "??_C"))]
        want = a.symbol
        ranked = sorted(set(syms), key=lambda n: -difflib.SequenceMatcher(None, n, want).ratio())
        print(f"symbol   {want}")
        print("result   NOT IN OBJECT -- the TU compiled, but defines no symbol by that name.")
        print("nearest  defined symbols in this object (copy the exact one):")
        for n in ranked[:8]:
            print(f"         {n}")
        print("hint     the class/namespace/const-ness/calling convention in the mangled name must match the C++ you wrote;")
        print("         `add_match.py` needs the same exact name.")
        sys.exit(2)
    compiled = bytes(compiled)

    size = a.size or ledger_size(rva) or len(compiled)
    image = open(build.EXE, "rb").read()
    secs = build.pe_sections(image)
    off = build.rva_to_file_offset(secs, rva)
    retail = image[off: off + size]

    ours_m = masked(compiled, relocs)
    ret_m = masked(retail, relocs)
    diffs = [i for i in range(min(len(ours_m), len(ret_m))) if ours_m[i] != ret_m[i]]

    print(f"symbol   {a.symbol}")
    print(f"size     ours={len(compiled)} retail={size}  relocs={len(relocs)}")
    if len(compiled) == size and not diffs:
        print("result   EXACT (modulo relocation slots)")
        print("lever    " + LEVERS["exact"])
        return
    first = diffs[0] if diffs else min(len(compiled), size)
    print(f"diffs    {len(diffs)} non-reloc byte(s); first at +{first}")

    ret_ins = disasm(retail)
    our_ins = disasm(compiled)
    kind = classify(ret_ins, our_ins, ret_m, ours_m)
    # Evidence: the instruction pairs that differ. The label is a candidate
    # cause keyed on byte pattern; the same pattern can have another source
    # (a control-flow shape looked like a register mirror on 0x00339B90).
    def masked_ins(ins, m):
        return m[ins.address: ins.address + ins.size]
    pairs = [(r, o) for r, o in zip(ret_ins, our_ins)
             if masked_ins(r, ret_m) != masked_ins(o, ours_m)]
    covered = sum(len(r.bytes) for r, _ in pairs)
    confidence = "high" if kind == "exact" or (pairs and covered >= len(diffs)) else "low"
    print(f"candidate {kind}  (confidence {confidence}; verify against the evidence below)")
    print(f"lever     {LEVERS[kind]}")
    for r, o in pairs[:6]:
        print(f"evidence  +{r.address:04x}  retail: {r.mnemonic} {r.op_str:32}  ours: {o.mnemonic} {o.op_str}")
    if len(pairs) > 6:
        print(f"evidence  ... {len(pairs) - 6} more differing instruction(s)")

    def rows(ins):
        return [(i.address, " ".join(f"{b:02x}" for b in i.bytes), f"{i.mnemonic} {i.op_str}") for i in ins]
    R, O = rows(ret_ins), rows(our_ins)
    lo = 0 if a.all else max(0, first - 24)
    hi = max(len(retail), len(compiled)) if a.all else first + 40
    print()
    print(f"{'retail':44} | ours")
    ri = oi = 0
    while ri < len(R) or oi < len(O):
        ra = R[ri][0] if ri < len(R) else 10 ** 9
        oa = O[oi][0] if oi < len(O) else 10 ** 9
        addr = min(ra, oa)
        if addr > hi:
            break
        left = f"{R[ri][0]:04x} {R[ri][1]:20} {R[ri][2]}" if ra == addr else ""
        right = f"{O[oi][0]:04x} {O[oi][1]:20} {O[oi][2]}" if oa == addr else ""
        if addr >= lo:
            same = left and right and R[ri][1] == O[oi][1]
            mark = "  " if same else "!!"
            print(f"{mark}{left:42} | {right}")
        if ra == addr:
            ri += 1
        if oa == addr:
            oi += 1


if __name__ == "__main__":
    main()
