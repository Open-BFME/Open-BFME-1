#!/usr/bin/env python3
"""A ThrowInfo as the compiler emits it, checked against retail and moved.

`throw T(...)` makes cl write T's exception graph as COMDATs: ThrowInfo
`__TI<n><T>` (16 bytes: attributes, unwind = T's destructor, forward-compat,
-> CatchableTypeArray), `__CTA<n><T>` (count, -> CatchableType per base),
`__CT...` (28 bytes: properties, -> TypeDescriptor, PMD, size, copy
constructor) and TypeDescriptor `??_R0<T>@8` (-> type_info vftable, spare,
decorated name). That object graph, not a hand-typed 4-byte `int`, is the
definition a manual `_CxxThrowException(&e, &g_...ThrowInfo)` needs; the
manual spelling binds to it with `/alternatename:<spelled>=__TI1<T>`
(tools/tests/test_throwinfo_graph.py links and runs that at a moved base,
with a wrong-type negative control).

  python3 tools/throwinfo_graph.py OBJ [--symbol __TI1?AVXferException@@] [--va 0x011DFE5C]

walks the graph in OBJ from --symbol and places it at retail's --va:
  bytes    each item equals retail outside its relocation fields
  edges    each graph edge lands on the child item's retail address
  targets  each terminal (destructor, copy constructor, vftable) resolves
           through the ledger/pins (startup_tables.Resolver) to what retail
           holds there, directly or through an incremental-link jmp; a
           type_info-style vftable no row names is accepted when its first
           slot is the class's ledgered deleting destructor
  moved    no dword in the items that retail holds as an in-image address
           lies outside a relocation field, so every pointer moves with its
           target when the graph is placed anywhere else
"""
import argparse
import json
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from reloc_ledger import parse_coff  # noqa: E402

DIR32 = 0x0006
GRAPH = re.compile(r"^(__TI|__CTA|__CT|\?\?_R0)")


def walk(data, root):
    """{symbol: {"bytes", "relocs": [(offset, target symbol)]}} for the EH items
    reachable from `root` inside one object, and the terminal symbols."""
    sections, symbols = parse_coff(data)
    by_name = {s["name"]: s for s in symbols.values() if s["section"] > 0}
    items, terminals, todo = {}, set(), [root]
    while todo:
        name = todo.pop()
        if name in items:
            continue
        sym = by_name.get(name)
        if sym is None:
            raise SystemExit(f"throwinfo_graph: {name} is not defined in this object")
        sec = sections[sym["section"] - 1]
        relocs = []
        for where, index, kind in sec["relocs"]:
            if kind != DIR32:
                raise SystemExit(f"throwinfo_graph: {name} has a non-DIR32 relocation")
            target = symbols[index]["name"]
            relocs.append((where - sym["value"], target))
            if GRAPH.match(target):
                todo.append(target)
            else:
                terminals.add(target)
        items[name] = {"bytes": bytes(sec["body"][sym["value"]:]), "relocs": sorted(relocs)}
    return items, terminals


def vftable_class(name):
    m = re.fullmatch(r"\?\?_7(.+?)@@6B@", name)
    return m.group(1) if m else None


def verify(items, root, va, retail, resolver, rows_at):
    """Place the graph at retail and report every check (see module doc)."""
    base = retail.base
    place, order, problems, fields = {root: va}, [root], [], []
    i = 0
    while i < len(order):
        name = order[i]
        i += 1
        at = place[name]
        for off, target in items[name]["relocs"]:
            value = retail.u32(at + off - base)
            if target in items and target not in place:
                place[target] = value
                order.append(target)
    for name in order:
        at, item = place[name], items[name]
        here = bytearray(retail.image[at - base:at - base + len(item["bytes"])])
        mine = bytearray(item["bytes"])
        covered = set()
        for off, target in item["relocs"]:
            covered.update(range(off, off + 4))
            mine[off:off + 4] = here[off:off + 4]
            value = struct.unpack_from("<I", here, off)[0]
            if target in items:
                ok, how = value == place[target], "edge"
            else:
                rva = resolver("", target, 2)
                if rva is not None:
                    reached = value - base
                    ok = rva in (reached, retail_ilt(retail, reached))
                    how = "ledger"
                else:
                    cls = vftable_class(target)
                    slot0 = retail.u32(value - base) - base if cls else None
                    names = rows_at.get(slot0, [])
                    ok = bool(cls) and any(n.startswith((f"??_E{cls}@@", f"??_G{cls}@@")) for n in names)
                    how = f"vftable slot0 {names[:1]}" if cls else "unplaced"
            fields.append({"item": name, "offset": off, "target": target, "retail": f"0x{value:08X}",
                           "how": how, "ok": ok})
            if not ok:
                problems.append(f"{name}+{off}: {target} is not what retail holds (0x{value:08X})")
        if mine != here:
            problems.append(f"{name}: bytes differ from retail at 0x{at:08X} outside relocations")
        # a TypeDescriptor's decorated name (offset 8 on) is text, not pointers
        span = 8 if name.startswith("??_R0") else len(here) - 3
        for off in range(0, span, 4):
            word = struct.unpack_from("<I", here, off)[0]
            if off not in covered and base <= word < base + len(retail.image):
                problems.append(f"{name}+{off}: retail holds in-image 0x{word:08X} with no relocation")
    return {"placement": {k: f"0x{v:08X}" for k, v in place.items()},
            "bytes": sum(len(items[n]["bytes"]) for n in order), "fields": fields, "problems": problems}


def retail_ilt(retail, rva):
    if retail.image[rva:rva + 1] == bytes([0xE9]):
        return (rva + 5 + struct.unpack_from("<i", retail.image, rva + 1)[0]) & 0xFFFFFFFF
    return rva


def main(argv=None):
    import startup_tables as st
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("obj", type=Path)
    ap.add_argument("--symbol", default="__TI1?AVXferException@@")
    ap.add_argument("--va", default="0x011DFE5C")
    args = ap.parse_args(argv)
    items, terminals = walk(args.obj.read_bytes(), args.symbol)
    rows = st.matched_rows()
    rows_at = {}
    for r in rows:
        rows_at.setdefault(int(r["target_rva"], 16), []).append(r["name"])
    report = verify(items, args.symbol, int(args.va, 16), st.Retail(), st.Resolver(rows), rows_at)
    print(json.dumps(report, indent=1))
    return 1 if report["problems"] else 0


if __name__ == "__main__":
    sys.exit(main())
