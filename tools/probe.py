#!/usr/bin/env python3
"""Compile one TU, diff one symbol against retail, and name the wall.

Read-only: writes its cache and experiment history under build/, never touches
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
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build

ROOT = Path(__file__).resolve().parents[1]
LEVERS = {
    "exact": "instruction shape matches; validate callees and identity with tools/add_match.py before claiming a conversion",
    "sib-order": "shape_levers.md row 1: add the pointer as an integer on the right of the counter: *(T*)(i + (unsigned)p)",
    "eh-transposition": "shape_levers.md row 2: by-value string class must be `: private StringBase<T>` with INLINE forwarding copy ctor/dtor (reference/shims/stringinline/StringInline.h)",
    "register-mirror": "shape_levers.md rows 3-5: reorder local DEFINITIONS to retail's first-use order; copy params to locals just before the guard; call dllimports directly (IAT CSE)",
    "adjacent-swap": "shape_levers.md rows 3-4: two values materialized in the other order -- swap the two local DEFINITIONS (or move the param copies to just before the guard); if one side is an EH state store see row 2",
    "length-delta": "shape/CSE/inline difference at the first divergent instruction -- see shape_levers.md rows 6, 8, 9 (flag tail, `new` statement, trivially-copyable arg)",
    "operand-change": "compare literal values, field offsets and branch destinations before changing register allocation",
    "instruction-change": "different operations or inconsistent register mapping; inspect the first differing instruction before choosing a lever",
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
    for ro, kind, _n in relocs:
        width = build.RELOC_WIDTH.get(kind)
        if width is None or ro < 0:
            raise ValueError("unknown relocation type or negative offset")
        for k in range(width):
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
    mapping, reverse_mapping = {}, {}
    i = 0
    n = len(ret_ins)
    while i < n:
        r, o = ret_ins[i], our_ins[i]
        if r.bytes == o.bytes:
            for reg in REG.findall(r.op_str):
                if mapping.get(reg, reg) != reg or reverse_mapping.get(reg, reg) != reg:
                    return "instruction-change"
                mapping[reg] = reverse_mapping[reg] = reg
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
                for left, right in zip(REG.findall(r.op_str), REG.findall(o.op_str)):
                    if mapping.get(left, right) != right or reverse_mapping.get(right, left) != left:
                        return "instruction-change"
                    mapping[left], reverse_mapping[right] = right, left
                renames += 1
            i += 1
            continue
        return "operand-change" if r.mnemonic == o.mnemonic else "instruction-change"
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
    from experiment_store import compile_cached, record_result
    obj, reused = compile_cached(src)
    print(f"compile  {'reused verified dependency cache' if reused else 'compiled new experiment'}")
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
    outcome = record_result(src, a.symbol, rva, retail, compiled, relocs)
    print(f"history  {outcome['seen_before']} prior experiment(s) with this instruction/relocation result")

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

    # Diagnose only concrete differences; link-time addresses are not register
    # or literal mismatches. They still require the normal strict byte gate.
    ret_ins = disasm(ret_m)
    our_ins = disasm(ours_m)
    kind = classify(ret_ins, our_ins, ret_m, ours_m)
    # Evidence: the instruction pairs that differ. The label is a candidate
    # cause keyed on byte pattern; the same pattern can have another source
    # (a control-flow shape looked like a register mirror on 0x00339B90).
    def masked_ins(ins, m):
        return m[ins.address: ins.address + ins.size]
    pairs = [(r, o) for r, o in zip(ret_ins, our_ins)
             if masked_ins(r, ret_m) != masked_ins(o, ours_m)]
    confidence = "pattern only"
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
