#!/usr/bin/env python3
"""Tabulate the register webs an allocation-only near miss gets wrong.

For a body whose `probe.py` shape score is 1.000 (the retail instruction
sequence, register names and constants aside), pair the two streams
instruction-for-instruction, split retail's registers into def-use webs
(reaching definitions over the body's CFG), and print every web whose
register differs in our build, with the features an allocator could key on:

  kind      how the web's value is born: this (ECX at entry), arg (load of an
            incoming stack argument), callret (EAX after a call), load, lea,
            const, arith, entry (a callee-saved register's caller value)
  uses      instructions reading the web
  span      instructions from first def to last use (linear order)
  calls     calls strictly inside that span (the web crosses them)
  loop      1 when any def/use sits inside a CFG back-edge region
  first     offset of the first def

  python3 tools/alloc_residue.py <stash.cpp> "<mangled>" 0xRVA [--size N] [--json]
  python3 tools/alloc_residue.py --list build/_alloc_only.txt [--json out.json]

Stack slots are reported separately: each memory operand on ESP/EBP whose
displacement differs, as (retail disp, our disp) pairs. Read-only.
"""
import argparse
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build  # noqa: E402

ROOT = Path(__file__).resolve().parents[1]
GPR = ["eax", "ecx", "edx", "ebx", "esp", "ebp", "esi", "edi"]
SUB = {"al": "eax", "ah": "eax", "ax": "eax", "cl": "ecx", "ch": "ecx", "cx": "ecx",
       "dl": "edx", "dh": "edx", "dx": "edx", "bl": "ebx", "bh": "ebx", "bx": "ebx",
       "si": "esi", "di": "edi", "bp": "ebp", "sp": "esp"}
ALLOC = {"eax", "ecx", "edx", "ebx", "esi", "edi", "ebp"}
CALLER_SAVED = {"eax", "ecx", "edx"}


def full(name):
    return SUB.get(name, name)


def disasm(data):
    import capstone
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    return list(md.disasm(bytes(data), 0))


def reg_access(ins):
    """(reads, writes) as full 32-bit GPR names, explicit + implicit."""
    r, w = ins.regs_access()
    reads = {full(ins.reg_name(x)) for x in r}
    writes = {full(ins.reg_name(x)) for x in w}
    reads &= set(GPR)
    writes &= set(GPR)
    m = ins.mnemonic
    # xor r,r / sub r,r read nothing meaningful
    if m in ("xor", "sub", "sbb") and len(ins.operands) == 2:
        a, b = ins.operands
        if a.type == 1 and b.type == 1 and a.reg == b.reg:
            reads.discard(full(ins.reg_name(a.reg)))
    if m == "call":
        writes |= CALLER_SAVED
    # a partial-register write (mov al,..; setcc al) keeps the rest: it also reads
    for op in ins.operands:
        if op.type == 1 and (op.access & 2) and ins.reg_name(op.reg) in SUB and ins.reg_name(op.reg) not in ("sp",):
            if m not in ("movzx", "movsx"):
                reads.add(full(ins.reg_name(op.reg)))
    return reads, writes


def operand_regs(ins, sorted_mem=False):
    """Ordered register mentions (full names) per operand, for pairing.
    sorted_mem lists a scale-1 base+index pair in name order, so a SIB
    base/index swap (a separate, documented residue) pairs as identity."""
    out = []
    for op in ins.operands:
        if op.type == 1:
            out.append(full(ins.reg_name(op.reg)))
        elif op.type == 3:
            pair = []
            if op.mem.base:
                pair.append(full(ins.reg_name(op.mem.base)))
            if op.mem.index:
                pair.append(full(ins.reg_name(op.mem.index)))
            if sorted_mem and len(pair) == 2 and op.mem.scale == 1:
                pair.sort()
            out += pair
    return out


def sib_swapped(a, b):
    """Same registers, base and index exchanged (scale 1)."""
    if a.bytes == b.bytes or a.mnemonic != b.mnemonic:
        return False
    return (operand_regs(a, True) == operand_regs(b, True)
            and operand_regs(a) != operand_regs(b))


def cfg(ins_list):
    """Successor indices for each instruction."""
    by_addr = {ins.address: i for i, ins in enumerate(ins_list)}
    succ = []
    for i, ins in enumerate(ins_list):
        m = ins.mnemonic
        s = []
        if m.startswith("j"):
            op = ins.operands[0] if ins.operands else None
            if op is not None and op.type == 2 and op.imm in by_addr:
                s.append(by_addr[op.imm])
            if m != "jmp" and i + 1 < len(ins_list):
                s.append(i + 1)
        elif m in ("ret", "retn"):
            pass
        elif i + 1 < len(ins_list):
            s.append(i + 1)
        succ.append(s)
    return succ


def webs(ins_list):
    """Union-find def-use webs. A def is (index, reg); index -1 is function entry."""
    n = len(ins_list)
    succ = cfg(ins_list)
    acc = [reg_access(i) for i in ins_list]
    # reaching defs: IN[i][reg] = set of def indices
    IN = [dict() for _ in range(n)]
    IN[0] = {r: {-1} for r in GPR}
    changed = True
    OUT = [None] * n
    while changed:
        changed = False
        for i in range(n):
            cur = {r: set(v) for r, v in IN[i].items()}
            for r in acc[i][1]:
                cur[r] = {i}
            if OUT[i] != cur:
                OUT[i] = cur
                for s in succ[i]:
                    for r, v in cur.items():
                        t = IN[s].setdefault(r, set())
                        if not v <= t:
                            t |= v
                            changed = True
    parent = {}

    def find(x):
        parent.setdefault(x, x)
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x

    def union(a, b):
        parent[find(a)] = find(b)

    for i in range(n):
        for r in acc[i][0]:
            ds = sorted(IN[i].get(r, {-1}))
            for d in ds:
                find((d, r))
            for d in ds[1:]:
                union((ds[0], r), (d, r))
        for r in acc[i][1]:
            find((i, r))
    groups = {}
    for key in list(parent):
        groups.setdefault(find(key), set()).add(key)
    use_map = {}
    for i in range(n):
        for r in acc[i][0]:
            ds = IN[i].get(r, {-1})
            use_map.setdefault(find((min(ds), r)), []).append(i)
    out = []
    for root, defs in groups.items():
        out.append({"reg": root[1], "defs": sorted(d for d, _ in defs),
                    "uses": sorted(set(use_map.get(root, [])))})
    return out, succ


def loop_members(succ):
    """Instructions inside a natural-ish loop: any i reachable from j and j->i back edge."""
    inside = set()
    for i, ss in enumerate(succ):
        for s in ss:
            if s <= i:  # back edge i -> s
                inside.update(range(s, i + 1))
    return inside


def classify_def(ins_list, d, reg):
    if d == -1:
        return "this" if reg == "ecx" else ("entry" if reg != "esp" else "sp")
    ins = ins_list[d]
    m, ops = ins.mnemonic, ins.op_str
    if m == "call":
        return "callret"
    if m == "lea":
        return "lea"
    if m in ("mov", "movzx", "movsx"):
        src = ins.operands[1]
        if src.type == 2:
            return "const"
        if src.type == 3:
            base = ins.reg_name(src.mem.base) if src.mem.base else ""
            if base == "esp" and src.mem.disp > 0 or base == "ebp" and src.mem.disp > 0:
                return "stackload"
            return "load"
        if src.type == 1:
            return "copy"
    if m == "pop":
        return "pop"
    if m in ("xor", "or") and "0xffffffff" in ops or (m == "xor" and len(set(ops.split(", "))) == 1):
        return "const"
    return "arith:" + m


def analyse(retail, compiled, relocs):
    import probe
    ret_raw, our_raw, ret_ins, our_ins, *_ = probe.diagnostic_streams(retail, compiled, relocs)
    if len(ret_ins) != len(our_ins):
        return {"error": f"instruction count {len(ret_ins)} vs {len(our_ins)}"}
    for a, b in zip(ret_ins, our_ins):
        if probe.shape_text(a) != probe.shape_text(b):
            return {"error": f"shape differs at +{a.address:x}: {a.mnemonic} {a.op_str} / {b.mnemonic} {b.op_str}"}
    rw, succ = webs(ret_ins)
    loops = loop_members(succ)
    calls = [i for i, x in enumerate(ret_ins) if x.mnemonic == "call"]
    # per-instruction register pairing retail -> ours
    pair_at = {}
    sib = []
    for i, (a, b) in enumerate(zip(ret_ins, our_ins)):
        if sib_swapped(a, b):
            sib.append(f"+{a.address:04x}")
        pa, pb = operand_regs(a, True), operand_regs(b, True)
        m = {}
        for x, y in zip(pa, pb):
            m.setdefault(x, y)
        pair_at[i] = m
    mism = []
    for w in rw:
        reg = w["reg"]
        if reg not in ALLOC:
            continue
        seen = {}
        for i in w["defs"] + w["uses"]:
            if i >= 0 and reg in pair_at[i]:
                seen.setdefault(pair_at[i][reg], []).append(i)
        ours = sorted(seen) if seen else []
        if not ours or ours == [reg]:
            continue
        idx = [i for i in w["defs"] + w["uses"] if i >= 0]
        lo, hi = (min(idx), max(idx)) if idx else (0, 0)
        if -1 in w["defs"]:
            lo = 0
        # entry webs that only feed a prologue push and epilogue pop are saves
        kinds = sorted({classify_def(ret_ins, d, reg) for d in w["defs"]})
        uses_txt = [ret_ins[i].mnemonic for i in w["uses"]]
        if kinds == ["entry"] and set(uses_txt) <= {"push"}:
            kinds = ["save"]
        mism.append({
            "retail": reg, "ours": "/".join(ours),
            "kind": ",".join(kinds),
            "first": f"+{ret_ins[lo].address:04x}",
            "def": (f"{ret_ins[w['defs'][0]].mnemonic} {ret_ins[w['defs'][0]].op_str}"
                    if w["defs"][0] >= 0 else "(entry)"),
            "uses": len(w["uses"]),
            "span": hi - lo + 1,
            "calls": sum(1 for c in calls if lo < c < hi),
            "loop": int(any(i in loops for i in idx)),
            "ndefs": len(w["defs"]),
        })
    slots = {}
    for a, b in zip(ret_ins, our_ins):
        for oa, ob in zip(a.operands, b.operands):
            if oa.type == 3 and ob.type == 3 and oa.mem.base and ob.mem.base:
                ba, bb = a.reg_name(oa.mem.base), b.reg_name(ob.mem.base)
                if ba in ("esp", "ebp") and ba == bb and oa.mem.disp != ob.mem.disp:
                    slots.setdefault((ba, oa.mem.disp - ob.mem.disp), []).append(f"+{a.address:04x}")
    diff_ins = sum(1 for a, b in zip(ret_raw, our_raw) if a.bytes != b.bytes)
    return {"n_ins": len(ret_ins), "diff_ins": diff_ins, "calls": len(calls),
            "loops": int(bool(loops)), "webs": mism, "sib": sib,
            "slots": [{"base": k[0], "delta": k[1], "sites": v} for k, v in sorted(slots.items())]}


def run(source, symbol, rva, size=None):
    import probe
    from experiment_store import compile_cached
    src = Path(source)
    src = src if src.is_absolute() else (ROOT / src).resolve()
    obj, _ = compile_cached(src)
    compiled, relocs = build.read_object_symbol_bytes(obj, symbol)
    compiled = bytes(compiled)
    size = size or probe.ledger_size(rva) or len(compiled)
    image = open(build.EXE, "rb").read()
    off = build.rva_to_file_offset(build.pe_sections(image), rva)
    retail = image[off:off + size]
    if len(retail) != len(compiled):
        return {"error": f"size {len(compiled)} vs {size}"}
    return analyse(retail, compiled, relocs)


def show(name, res):
    if "error" in res:
        print(f"== {name}: {res['error']}")
        return
    print(f"== {name}: {res['n_ins']} ins, {res['diff_ins']} differ, {res['calls']} calls, loops={res['loops']}")
    for w in res["webs"]:
        print(f"   {w['retail']:>3} -> {w['ours']:<8} {w['kind']:<14} first {w['first']} uses {w['uses']:>3} "
              f"span {w['span']:>4} calls {w['calls']:>2} loop {w['loop']} defs {w['ndefs']}  {w['def']}")
    for s in res["slots"]:
        print(f"   slot {s['base']} delta {s['delta']:+d} at {len(s['sites'])} site(s) first {s['sites'][0]}")
    if res.get("sib"):
        print(f"   sib base/index swap at {', '.join(res['sib'])}")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("source", nargs="?")
    ap.add_argument("symbol", nargs="?")
    ap.add_argument("rva", nargs="?")
    ap.add_argument("--size", type=int)
    ap.add_argument("--list")
    ap.add_argument("--json")
    a = ap.parse_args()
    results = {}
    if a.list:
        for line in Path(a.list).read_text().splitlines():
            parts = line.split()
            if len(parts) < 3:
                continue
            rva, size, sym = parts[0], int(parts[1]), parts[2]
            src = ROOT / "targets/game/reverse/attempts" / f"{rva.lower()}.cpp"
            try:
                res = run(src, sym, int(rva, 16), size)
            except Exception as e:  # noqa: BLE001 -- report and continue the sweep
                res = {"error": f"{type(e).__name__}: {e}"}
            res["size"] = size
            res["symbol"] = sym
            results[rva] = res
            show(f"{rva} {size} {sym[:60]}", res)
    else:
        res = run(a.source, a.symbol, int(a.rva, 16), a.size)
        results[a.rva] = res
        show(a.rva, res)
    if a.json:
        Path(a.json).write_text(json.dumps(results, indent=1))


if __name__ == "__main__":
    main()
