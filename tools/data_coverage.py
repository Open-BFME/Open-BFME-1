#!/usr/bin/env python3
"""How much of the exe's DATA (.rdata + .data) would a clean link reproduce?

This is deliberately NOT part of tools/progress.py and never feeds its
headline. progress.py measures the code section; a whole-exe clean link also
needs every byte of .rdata and .data, and until now nothing measured those.
Different question, different denominator, different tool. Do not fold the
two numbers together: 100% of .text with 0% of .data is not a game.

Method (read-only, ~30 s, no compiler):
  1. Scan .text for 4-byte values that point into .rdata/.data (the same scan
     tools/fleet/vtable_rank.py uses to find vtables). Each hit is a reference
     SITE inside some ledger function, so the site's owner row says which lane
     referenced it: authored / vendored / generated / library C++, or a dump.
  2. Scan .rdata and .data for pointers into data, so tables reachable only
     through other data are told apart from bytes nothing points at.
  3. Split each data section at every referenced address; the extent runs to
     the next referenced address (capped). Classify each extent by its bytes:
     a run of .text pointers is a code-pointer table (vtable or switch table),
     a printable NUL-terminated run is a string literal, <= 16 bytes is a
     small constant; an extent that is mostly strings, mostly .text pointers
     or almost all zero bytes is classified by that make-up. Those are
     EMITTED BY THE COMPILER from the source that references them (a zero
     block is a default-initialised global), so they come for free once that
     source exists. Anything else is global data that needs a definition.
  4. Roll bytes up into the buckets printed below.

The reference scan is a byte scan, not a disassembly, so a coincidental
4-byte value inside an instruction can create a false site; the same
limitation applies to vtable_rank.py and has been acceptable there. Extents
are gap-derived, so an object nothing references is folded into the extent
before it. Treat the figures as a map of where the data work is, not as a
byte-exact ledger.

  python3 tools/data_coverage.py            # summary
  python3 tools/data_coverage.py --json     # machine-readable buckets
  python3 tools/data_coverage.py --todo N   # largest "needs definition" extents
"""
import argparse
import bisect
import csv
import json
import struct
import sys
from collections import Counter, defaultdict
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build  # noqa: E402
from progress import source_lane  # noqa: E402

ROOT = Path(__file__).resolve().parents[1]
BASE = 0x400000
DATA_SECTIONS = (".rdata", ".data")
SMALL_CONSTANT = 16
MAX_EXTENT = 65536
REBUILDABLE_LANES = ("authored", "vendored", "generated", "library")
_U32 = struct.Struct("<I")


# ----------------------------------------------------------------- image ----
def load_image():
    exe = open(build.EXE, "rb").read()
    secs = build.pe_sections(exe)
    by_name = {s["name"]: s for s in secs}
    return exe, secs, by_name


def section_bytes(exe, sec):
    """Bytes the file actually holds for a section (the initialised part)."""
    size = min(sec["size"], sec.get("raw_size", sec["size"]))
    return exe[sec["raw_pointer"]:sec["raw_pointer"] + size], size


def scan_pointers(raw, base_va, lo, hi):
    """{target_va: [site_va, ...]} for every 4-byte value in raw within [lo, hi)."""
    hits = defaultdict(list)
    unpack = _U32.unpack_from
    for i in range(len(raw) - 3):
        value = unpack(raw, i)[0]
        if lo <= value < hi:
            hits[value].append(base_va + i)
    return hits


# ---------------------------------------------------------------- ledger ----
def load_owner_index():
    """Sorted function starts and rows, so a .text site maps to its owner row."""
    rows = []
    with open(ROOT / "targets/game/reverse/functions.csv", newline="", encoding="utf-8", errors="replace") as fh:
        for row in csv.DictReader(fh):
            if row.get("status") != "matched" or not (row.get("target_rva") or "").startswith("0x"):
                continue
            rows.append((int(row["target_rva"], 16), int(row.get("target_size") or 0), row))
    rows.sort(key=lambda t: t[0])
    return [r[0] for r in rows], rows


def owner_of(site_rva, starts, rows):
    i = bisect.bisect_right(starts, site_rva) - 1
    if i < 0:
        return None
    start, size, row = rows[i]
    return row if site_rva < start + size else None


def lane_of(row):
    return source_lane(row["source"], row.get("notes", ""), False)


# ------------------------------------------------------------- classify ----
def is_string_run(chunk):
    """ASCII or UTF-16LE printable run of >= 3 chars ending in a terminator."""
    if len(chunk) < 4:
        return False
    end = chunk.find(b"\x00")
    if end >= 3 and all(32 <= b < 127 or b in (9, 10, 13) for b in chunk[:end]):
        return True
    n = 0
    while n + 1 < len(chunk) and chunk[n + 1] == 0 and 32 <= chunk[n] < 127:
        n += 2
    return n >= 6 and n + 1 < len(chunk) and chunk[n] == 0 and chunk[n + 1] == 0


def is_code_pointer_table(chunk, text_lo, text_hi):
    """At least two consecutive 4-byte pointers into .text at the start."""
    if len(chunk) < 8:
        return False
    count = 0
    for i in range(0, len(chunk) - 3, 4):
        value = _U32.unpack_from(chunk, i)[0]
        if text_lo <= value < text_hi:
            count += 1
        else:
            break
    return count >= 2


def composition(chunk, text_lo, text_hi):
    """Fractions of the extent that are printable-string bytes, .text-pointer
    words, and zero bytes. A gap-derived extent often spans many objects (a
    reference into a string block is followed by 6 KB of more strings), so
    the extent's make-up decides what a link would need, not its first bytes."""
    n = len(chunk)
    if n == 0:
        return 0.0, 0.0, 0.0
    printable = 0
    i = 0
    while i < n:
        j = i
        while j < n and (32 <= chunk[j] < 127 or chunk[j] in (9, 10, 13)):
            j += 1
        if j - i >= 3 and j < n and chunk[j] == 0:
            printable += j - i + 1
        i = j + 1
    pointers = sum(4 for k in range(0, n - 3, 4)
                   if text_lo <= _U32.unpack_from(chunk, k)[0] < text_hi)
    zeros = chunk.count(0)
    return printable / n, pointers / n, zeros / n


def classify_extent(chunk, text_lo, text_hi):
    if is_code_pointer_table(chunk, text_lo, text_hi):
        return "code-pointer-table"
    if is_string_run(chunk):
        return "string"
    if len(chunk) <= SMALL_CONSTANT:
        return "small-constant"
    strings, pointers, zeros = composition(chunk, text_lo, text_hi)
    if strings >= 0.6:
        return "string"
    if pointers >= 0.6:
        return "code-pointer-table"
    if zeros >= 0.95:
        return "zero-initialised"
    return "global"


def split_extents(referenced, sec_lo, sec_end):
    """[(start, end)] from each referenced address to the next, capped."""
    starts = sorted(a for a in referenced if sec_lo <= a < sec_end)
    out = []
    for i, start in enumerate(starts):
        end = starts[i + 1] if i + 1 < len(starts) else sec_end
        out.append((start, min(end, start + MAX_EXTENT)))
    return out


# --------------------------------------------------------------- measure ----
def measure():
    exe, secs, by_name = load_image()
    text = by_name[".text"]
    text_lo, text_hi = BASE + text["rva"], BASE + text["rva"] + text["size"]
    starts, rows = load_owner_index()

    ranges = {}
    for name in DATA_SECTIONS:
        sec = by_name[name]
        raw, size = section_bytes(exe, sec)
        ranges[name] = (BASE + sec["rva"], BASE + sec["rva"] + size, raw)
    data_lo = min(lo for lo, _, _ in ranges.values())
    data_hi = max(hi for _, hi, _ in ranges.values())

    text_raw, _ = section_bytes(exe, text)
    from_code = scan_pointers(text_raw, text_lo, data_lo, data_hi)
    from_data = {}
    for name, (lo, hi, raw) in ranges.items():
        for target, sites in scan_pointers(raw, lo, data_lo, data_hi).items():
            from_data.setdefault(target, []).extend(sites)

    buckets = Counter()
    per_section = {name: Counter() for name in DATA_SECTIONS}
    todo = []
    referenced = set(from_code) | set(from_data)
    for name, (lo, hi, raw) in ranges.items():
        covered = 0
        extents = split_extents(referenced, lo, hi)
        for start, end in extents:
            chunk = raw[start - lo:end - lo]
            kind = classify_extent(chunk, text_lo, text_hi)
            lanes = Counter()
            for site in from_code.get(start, ()):
                row = owner_of(site - BASE, starts, rows)
                lanes[lane_of(row) if row else "unclaimed"] += 1
            code_refs = sum(lanes.values())
            rebuildable = code_refs > 0 and all(l in REBUILDABLE_LANES for l in lanes)
            emitted = kind in ("code-pointer-table", "string", "small-constant", "zero-initialised")
            if code_refs == 0:
                bucket = "referenced-from-data-only"
            elif emitted and rebuildable:
                bucket = "compiler-emitted, referenced by rebuildable code"
            elif emitted:
                bucket = "compiler-emitted, referenced only by dumps/unclaimed"
            elif rebuildable:
                bucket = "global data, needs a source definition"
            else:
                bucket = "global data, referenced only by dumps/unclaimed"
            size = end - start
            buckets[bucket] += size
            per_section[name][bucket] += size
            covered += size
            if bucket.startswith("global data, needs"):
                todo.append((size, start, name, dict(lanes)))
        unref = (hi - lo) - covered
        buckets["not referenced from .text or data"] += unref
        per_section[name]["not referenced from .text or data"] += unref

    denominator = sum(hi - lo for lo, hi, _ in ranges.values())
    outside = {s["name"] or "<unnamed>": s["size"] for s in secs
               if s["name"] not in DATA_SECTIONS and s["name"] != ".text"}
    todo.sort(reverse=True)
    return {"denominator": denominator, "buckets": dict(buckets),
            "per_section": {k: dict(v) for k, v in per_section.items()},
            "outside_scope": outside, "todo": todo}


ORDER = (
    "compiler-emitted, referenced by rebuildable code",
    "global data, needs a source definition",
    "compiler-emitted, referenced only by dumps/unclaimed",
    "global data, referenced only by dumps/unclaimed",
    "referenced-from-data-only",
    "not referenced from .text or data",
)


def print_report(result):
    d = result["denominator"]
    print("DATA COVERAGE  (.rdata + .data; separate from progress.py, NOT part of its headline)")
    print(f"denominator = {d:,} initialised data bytes\n")
    free = result["buckets"].get(ORDER[0], 0)
    print(f"  comes free from code we hold      {free:>10,} bytes ({100 * free / d:6.2f}%)"
          f"  <- literals/tables the compiler emits from landed source")
    for key in ORDER[1:]:
        value = result["buckets"].get(key, 0)
        print(f"  {key:<34} {value:>10,} bytes ({100 * value / d:6.2f}%)")
    print("\n  per section:")
    for name, counts in result["per_section"].items():
        total = sum(counts.values())
        need = counts.get(ORDER[1], 0)
        print(f"    {name:<7} {total:>10,} bytes; needs definition now: {need:,}")
    print("\n  outside this measure (decide separately):")
    for name, size in result["outside_scope"].items():
        print(f"    {name:<10} {size:>10,} bytes")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--todo", type=int, metavar="N", help="largest extents needing a definition")
    args = ap.parse_args()
    result = measure()
    if args.json:
        result["todo"] = [{"size": s, "va": f"0x{va:08X}", "section": n, "lanes": l}
                          for s, va, n, l in result["todo"][:200]]
        print(json.dumps(result, indent=2))
        return
    print_report(result)
    if args.todo:
        print(f"\n  largest 'needs a source definition' extents:")
        for size, va, name, lanes in result["todo"][:args.todo]:
            print(f"    0x{va:08X} {size:>8,} B  {name}  referenced by {lanes}")


if __name__ == "__main__":
    main()
