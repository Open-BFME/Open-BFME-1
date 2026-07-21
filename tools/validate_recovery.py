#!/usr/bin/env python3
"""Filter symbol<->RVA mispairings out of a recovered-candidate batch.

int3 boundary-recovery (skip leading 0xcc padding to snap a drift candidate to the
real ghidra function start) surfaces genuine function starts, but the drift voter
sometimes pairs a symbol with the WRONG address. Tell-tale: the symbol's source
compiles to a size wildly different from the target function's size (observed 238B
vs 18B). This compiles each candidate and flags any whose emitted size disagrees
with the claimed size beyond TOLERANCE, so agents never spend a slot on a candidate
that cannot match by construction.

Catches size-class mispairings; a same-size wrong-symbol pairing still needs a byte
compare (run explain_mismatch). Usage: python3 tools/validate_recovery.py <batch.tsv>
(any column order; needs a Code/... path field and a ?mangled@ symbol field).
"""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build  # noqa: E402

TOLERANCE = 0.25


def parse(row):
    rva = next(f for f in row if f.lower().startswith("0x"))
    size = next(int(f) for f in row if f.isdigit())
    source = next(f for f in row if f.startswith("Code/"))
    symbol = next(f for f in row if f.startswith("?") and "@" in f)
    return rva, size, source, symbol


def main():
    rows = [l.rstrip("\n").split("\t") for l in open(sys.argv[1]) if l.strip()]
    obj_cache = {}
    passed = mispaired = skipped = 0
    for row in rows:
        try:
            rva, size, source, symbol = parse(row)
        except StopIteration:
            continue
        src = build.ROOT / source
        if src not in obj_cache:
            try:
                obj = build.obj_path(src)
                build.compile_source(src, obj)
                obj_cache[src] = obj
            except SystemExit:
                obj_cache[src] = None
        obj = obj_cache[src]
        if obj is None:
            print(f"  SKIP      {rva} {symbol[:44]}  (source will not compile — a build blocker, not a mispairing)")
            skipped += 1
            continue
        try:
            body, _ = build.read_object_symbol_bytes(obj, symbol, size)
            emitted = len(body.rstrip(b"\xcc\x00"))
        except Exception:
            print(f"  SKIP      {rva} {symbol[:44]}  (symbol not emitted by its source)")
            skipped += 1
            continue
        off = abs(emitted - size) / max(size, 1)
        if off > TOLERANCE:
            print(f"  MISPAIRED {rva} claimed={size}B emitted={emitted}B ({int(off * 100)}% off)  {symbol[:44]}")
            mispaired += 1
        else:
            print(f"  PASS      {rva} claimed={size}B emitted={emitted}B  {symbol[:44]}")
            passed += 1
    print(f"\n{passed} PASS  {mispaired} MISPAIRED  {skipped} SKIP (blocked/absent)")


if __name__ == "__main__":
    main()
