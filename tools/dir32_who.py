#!/usr/bin/env python3
"""Which object and which function claims each address for a dir32 symbol.

WHY. `DIR32 consistency` reports "same symbol, multiple addresses" and stops
there, which is enough to know something is wrong and not enough to fix it. The
question that makes a row actionable is WHO: a symbol resolving to two bases
because two TUs disagree is a placement problem, and the same symbol resolving to
two bases inside ONE function is an identity problem -- our source is using one
name for two different retail globals.

`?ZNear@DX8Wrapper@@1MA` is the second kind. `?set@BFMEZBiasSetter@@SAXM@Z`, one
function in one object, references it at both 0x133f498 and 0x1340500. Its source
reads `if (ZNear!=ZFar) { tmp[3][2] -= (ZNear*ZFar/(ZNear-ZFar)) * ...; }`, so
several of those reads are not the global we named. The bytes match anyway --
build.py masks non-string DIR32s, so the byte gate is structurally blind to a
wrong global address, which is the whole reason this check exists.

Feed it names from build/dir32_inconsistent.txt, which the gate writes when it
fails.

    python3 tools/dir32_who.py '?ZNear@DX8Wrapper@@1MA'
    python3 tools/dir32_who.py --all        # every symbol in the report file
"""
import argparse
import collections
import struct
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build

ROOT = Path(__file__).resolve().parents[1]
REPORT = ROOT / "build/dir32_inconsistent.txt"


def claims(wanted):
    """symbol -> {(base, object, function)}, read the way the gate reads them."""
    out = collections.defaultdict(set)
    for row in build.load_function_rows():
        obj = build.require_row_object(row)
        size = int(row["target_size"])
        target = build.read_target_bytes(int(row["target_rva"], 16), size)
        try:
            body, relocs = build.read_object_symbol_bytes(
                obj, build.ledger_object_symbol(row), size)
        except ValueError:
            # A row whose object no longer emits its symbol is a different
            # defect with its own tool; skip rather than guess at its relocs.
            continue
        for off, rtype, sym in relocs:
            if rtype != 0x0006 or sym not in wanted or off + 4 > min(size, len(body)):
                continue
            final = struct.unpack_from("<I", target, off)[0]
            addend = struct.unpack_from("<I", body, off)[0]
            out[sym].add((hex((final - addend) & 0xFFFFFFFF), obj.name, row["name"]))
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("symbol", nargs="*")
    ap.add_argument("--all", action="store_true",
                    help=f"every symbol in {REPORT.relative_to(ROOT)}")
    args = ap.parse_args()

    wanted = set(args.symbol)
    if args.all:
        if not REPORT.exists():
            raise SystemExit(f"{REPORT.relative_to(ROOT)} does not exist. It is written "
                             "by a failing DIR32 consistency check -- run the gate, or "
                             "name the symbols on the command line.")
        wanted |= {l.split("\t")[0] for l in REPORT.read_text().splitlines() if l.strip()}
    if not wanted:
        raise SystemExit("name at least one symbol, or pass --all")

    found = claims(wanted)
    for sym in sorted(wanted):
        rows = sorted(found.get(sym, ()))
        print(f"\n{sym}  ({len({b for b, _, _ in rows})} address(es), {len(rows)} site(s))")
        if not rows:
            print("    no reloc to this symbol in any matched row")
        per_function = collections.Counter((o, f) for _, o, f in rows)
        for base, obj, func in rows:
            # A function appearing under two bases is the identity case: one
            # source name standing for two different retail globals.
            mark = "  <-- same function, 2+ addresses" if per_function[(obj, func)] > 1 else ""
            print(f"    {base:<12} {obj[-44:]:<44} {func[:46]}{mark}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
