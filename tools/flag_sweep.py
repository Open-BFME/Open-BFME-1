#!/usr/bin/env python3
"""Sweep the compiler switches that steer register allocation over one body.

The largest class of near misses compiles to retail's exact SHAPE -- the same
instructions once register names and constants are normalised (probe.py's
shape score) -- and differs only in which register or stack slot the allocator
chose. Source respellings have not moved that class: a 1,871-mutation permuter
improved 0 of 9 bodies, and one body saw ~25 hand shapes. MSVC 7.1's allocator
also depends on the optimisation level, the inlining level, the CPU target and
frame-pointer omission, and retail objects did not all use one setting (4,300
landed files already carry per-file `// cl:` switches: /Ob0 /Ob1 /Ob2 /Od /Oy-
/G6 /O1). A body built with other switches cannot be matched by any source
change. This compiles a source under every combination of those switches and
reports which one, if any, reproduces retail.

  python3 tools/flag_sweep.py SOURCE.cpp "MANGLED" 0xRVA [--size N] [--jobs 4]

Each variant is a temporary copy beside SOURCE (so relative includes resolve)
with its `// cl:` line rewritten: every non-O/G switch the file declares is
kept, the optimisation/CPU switches are replaced. The copies are always
removed. A winning variant is a `// cl:` line to put in the landing source.
"""
import argparse
import itertools
import re
import sys
import uuid
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

import build
import probe

OPT = ["/O2", "/O1", "/Ox"]
INLINE = ["/Ob0", "/Ob1", "/Ob2"]
CPU = ["", "/G5", "/G6", "/G7", "/GB"]
FRAME = ["", "/Oy-"]
TUNING = re.compile(r"^[-/](O[a-z0-9]*-?|G[5-7B]|GB)$", re.I)


def split_cl(text):
    """(line index or None, the file's non-O/G switches) from its `// cl:` line."""
    for index, line in enumerate(text.splitlines()[:40]):
        if line.startswith("// cl:"):
            keep = [flag for flag in line[len("// cl:"):].split() if not TUNING.match(flag)]
            return index, keep
    return None, []


def variant_text(text, flags):
    lines = text.splitlines(keepends=True)
    index, keep = split_cl(text)
    newline = "\r\n" if lines and lines[0].endswith("\r\n") else "\n"
    cl = "// cl: " + " ".join(keep + [f for f in flags if f]) + newline
    if index is None:
        return cl + text
    lines[index] = cl
    return "".join(lines)


def measure(source, text, symbol, retail, flags):
    scratch = source.with_name(f"_flagsweep_{uuid.uuid4().hex[:10]}{source.suffix}")
    obj = build.ROOT / "build" / "flag_sweep" / (scratch.stem + ".obj")
    obj.parent.mkdir(parents=True, exist_ok=True)
    try:
        scratch.write_bytes(variant_text(text, flags).encode("utf-8"))
        ok, _, _ = build.try_compile_source(scratch, obj)
        if not ok:
            return {"flags": flags, "error": "compile failed"}
        compiled, relocs = build.read_object_symbol_bytes(obj, symbol)
        compiled = bytes(compiled)
        ours, theirs = probe.masked(compiled, relocs), probe.masked(retail, relocs)
        diffs = sum(1 for i in range(min(len(ours), len(theirs))) if ours[i] != theirs[i])
        diffs += abs(len(compiled) - len(retail))
        streams = probe.diagnostic_streams(retail, compiled, relocs)
        shape, _ = probe.shape_compare(streams[0], streams[1])
        return {"flags": flags, "size": len(compiled), "diffs": diffs, "shape": shape,
                "exact": diffs == 0 and len(compiled) == len(retail)}
    except (Exception, SystemExit) as error:
        return {"flags": flags, "error": str(error)[:80]}
    finally:
        scratch.unlink(missing_ok=True)
        obj.unlink(missing_ok=True)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("source")
    ap.add_argument("symbol")
    ap.add_argument("rva")
    ap.add_argument("--size", type=int)
    ap.add_argument("--jobs", type=int, default=4)
    ap.add_argument("--top", type=int, default=8)
    args = ap.parse_args(argv)

    source = Path(args.source)
    source = (source if source.is_absolute() else build.ROOT / source).resolve()
    rva = int(args.rva, 16)
    size = args.size or probe.ledger_size(rva)
    if not size:
        raise SystemExit("flag_sweep: no ledger size for this RVA; pass --size")
    retail = build.read_target_bytes(rva, size)
    text = source.read_text(encoding="utf-8-sig", errors="replace")
    combos = [list(c) for c in itertools.product(OPT, INLINE, CPU, FRAME)]
    with ThreadPoolExecutor(max_workers=args.jobs) as pool:
        results = list(pool.map(lambda flags: measure(source, text, args.symbol, retail, flags), combos))
    good = [r for r in results if "error" not in r]
    good.sort(key=lambda r: (not r["exact"], r["diffs"], -r["shape"]))
    _, keep = split_cl(text)
    print(f"flag_sweep: {len(combos)} variants, {len(good)} compiled; file switches kept: {' '.join(keep) or '(none)'}")
    for r in good[:args.top]:
        mark = "EXACT" if r["exact"] else f"{r['diffs']:4} diff"
        print(f"  {mark:9} shape {r['shape']:.3f} size {r['size']:5}  {' '.join(f for f in r['flags'] if f)}")
    exact = [r for r in good if r["exact"]]
    if exact:
        print("LANDABLE: put this in the source's first lines -> // cl: "
              + " ".join(keep + [f for f in exact[0]["flags"] if f]))
    return 0 if exact else 1


if __name__ == "__main__":
    sys.exit(main())
