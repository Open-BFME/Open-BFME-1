#!/usr/bin/env python3
"""Name the FILES that bind a DIR32 symbol to each address.

verify_dir32_consistency reports `sym: bases [0x..., 0x...]` and stops there. It
proves a global is referenced at two addresses without saying which bodies did
it, so a red gate names a bug and hides its location -- the ThePartitionManager
red blocked all header and shim work for hours on exactly that gap.

This runs the same relocation scan and keeps the attribution, so the fix becomes
a list of call sites instead of a search. Read-only; touches no ledger.

    python3 tools/dir32_sites.py '?TheFoo@@3PAVFoo@@A'
"""
import struct
import sys
from collections import defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build  # noqa: E402

DIR32 = 0x0006


def base_of(target, body, off):
    """The address a reference resolves to, with the compiled addend removed."""
    final = struct.unpack_from("<I", target, off)[0]
    addend = struct.unpack_from("<I", body, off)[0]
    return (final - addend) & 0xFFFFFFFF


def sites_for(symbol, rows):
    """{base: [(source, row name, offset)]} for every DIR32 reference to `symbol`."""
    found = defaultdict(list)
    for row in rows:
        try:
            obj = build.require_row_object(row)
            size = int(row["target_size"])
            target = build.read_target_bytes(int(row["target_rva"], 16), size)
            body, relocs = build.read_object_symbol_bytes(
                obj, build.ledger_object_symbol(row), size)
        except BaseException:
            # A row whose object is absent cannot be attributed. It is skipped
            # and COUNTED -- a silent skip here reads as "no such reference",
            # which is the answer that sent an earlier sweep looking for a
            # symbol it had simply failed to load.
            found["skipped"].append(row.get("source", "?"))
            continue
        for off, rtype, sym in relocs:
            if rtype != DIR32 or sym != symbol:
                continue
            if off + 4 > size or off + 4 > len(body):
                continue
            found[base_of(target, body, off)].append(
                (row["source"], row["name"], off))
    return found


def main():
    if len(sys.argv) != 2:
        raise SystemExit(f"usage: {Path(sys.argv[0]).name} '<mangled symbol>'")
    symbol = sys.argv[1]
    found = sites_for(symbol, build.load_function_rows())
    skipped = found.pop("skipped", [])
    print(f"{symbol}")
    print(f"  {len(skipped)} row(s) skipped (object absent)")
    if not found:
        print("  no DIR32 reference to this symbol in any matched row")
        return
    for base in sorted(found):
        print(f"\n=== base 0x{base:08X}  ({len(found[base])} reference(s)) ===")
        for src, name, off in sorted(found[base]):
            print(f"    {src}\n        {name}  +0x{off:x}")


if __name__ == "__main__":
    main()
