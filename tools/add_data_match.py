#!/usr/bin/env python3
"""Append ONE data row to targets/game/reverse/data_rows.csv, byte-gated.

A data-only translation unit owns its globals here (tools/data_rows.py). This
compiles the source, finds the symbol, proves its size from the object,
verifies it against retail (bytes over the extent, every relocation on
retail's pointer; a zero-filled symbol alone at its address), checks the
ledger's integrity with the row added, and only then appends. Nothing lands
unverified; there is no --no-verify.

  python3 tools/add_data_match.py '?OurLanguage@@3W4LanguageID@@A' 0x012ED5D4 --va \\
      game/GameEngine/Source/Common/Language.cpp --model claude-opus-5.5 \\
      --evidence "ZH Common/Language.cpp defines it; retail .data holds 0 (LANGUAGE_ID_US)"

The size defaults to the proven size when exactly one is proven; pass --size
to choose between an extent and a declared scalar size.
"""
if __name__ == "__main__":
    from target_guard import require_game_cli
    require_game_cli("add_data_match.py")

import argparse
import csv
import io
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import data_rows  # noqa: E402
from portable_lock import lock  # noqa: E402

ROOT = Path(__file__).resolve().parents[1]


def row_text(row):
    out = io.StringIO()
    csv.writer(out, lineterminator="\n").writerow([row[f] for f in data_rows.FIELDS])
    return out.getvalue()


def address_token(name):
    """The bare address-spelled global a mangled data name defines
    (`?g_Va012BA084@@3GA` -> `g_Va012BA084`), else None."""
    import hatch_counters
    if name.startswith("?"):
        bare = name[1:].split("@", 1)[0]
    else:
        bare = name[1:] if name.startswith("_") else name
    return bare if hatch_counters.ADDR_GLOBAL.fullmatch(bare) else None


def admit_address_global(source, name):
    """After a verified write: admit this row's address-spelled global in the
    escape-hatch register (tools/hatch_counters.py) as a tool allowance. Only
    that one token; any other address global in the file stays counted growth."""
    import hatch_counters
    token = address_token(name)
    if token is None:
        return None
    return hatch_counters.admit(source, "add_data_match: verified data row names its address",
                                tokens={token})


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("name", help="the COFF symbol the source defines (mangled)")
    ap.add_argument("address", help="hex address")
    kind = ap.add_mutually_exclusive_group(required=True)
    kind.add_argument("--va", action="store_true", help="the address is a VA")
    kind.add_argument("--rva", action="store_true", help="the address is an RVA")
    ap.add_argument("source", help="game/ .c/.cpp that defines the symbol")
    ap.add_argument("--size", type=int, help="bytes (must be a proven size)")
    ap.add_argument("--model", required=True)
    ap.add_argument("--evidence", required=True)
    args = ap.parse_args(argv)
    import build
    import reloc_ledger
    address = int(args.address, 16)
    row = {"name": args.name, "address": f"0x{address:08X}", "address_kind": "va" if args.va else "rva",
           "size": "", "section": "", "source": Path(args.source).as_posix(), "status": "matched",
           "evidence": args.evidence, "model": args.model}
    va = data_rows.va_of(row)
    img = reloc_ledger.Image()
    row["section"] = img.section(va) or ""
    source = ROOT / row["source"]
    obj = build.obj_path(source)
    ok, text, _ = build.try_compile_source(source, obj)
    if not ok:
        raise SystemExit(f"add_data_match: {row['source']} does not compile:\n{text}")
    sections, symbols = reloc_ledger.parse_coff(obj.read_bytes())
    found = [s for s in symbols.values() if s["name"] == args.name and s["storage"] == data_rows.EXTERNAL
             and (s["section"] > 0 or s["value"] > 0)]
    if len(found) != 1:
        raise SystemExit(f"add_data_match: {args.name} is not defined once in {obj.name}")
    sizes, why = data_rows.symbol_size(sections, symbols, found[0], source)
    if not sizes:
        raise SystemExit(f"add_data_match: no size is proven for {args.name}: {why}")
    size = args.size if args.size is not None else next(iter(sizes))
    if size not in sizes:
        raise SystemExit(f"add_data_match: size {size} is not proven ({why}: {sorted(sizes)})")
    row["size"] = str(size)
    lock_file = (ROOT / "targets/game/reverse" / ".add_match.lock").open("a")
    lock(lock_file, exclusive=True, wait_notice="add_data_match: waiting for the ledger lock...")
    path = data_rows.DATA_ROWS
    existing = path.read_bytes() if path.exists() else (data_rows.HEADER + "\n").encode()
    candidate = existing + row_text(row).encode()
    problems = []
    data_rows.check(candidate, problems)
    if problems:
        raise SystemExit("add_data_match: the ledger would be invalid:\n  " + "\n  ".join(problems))
    rows = [r for _, r in data_rows.parse(candidate) if "_fields" not in r]
    ok, message = data_rows.verify_row(row, img, data_rows.Resolver(rows), compile=False)
    if not ok:
        raise SystemExit(f"add_data_match: {args.name} does not verify: {message}")
    path.write_bytes(candidate)
    import gate_writers
    gate_writers.stamp("data_row", existing, candidate)
    admit_address_global(row["source"], args.name)
    print(f"add_data_match: {args.name} -> {row['source']}: {message}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
