#!/usr/bin/env python3
"""Normalize reverse/functions.csv and reverse/symbols.csv after a union merge.

Many agents append rows concurrently and push straight to main; the union merge
driver combines both sides, which can leave the ledger unsorted or holding two
rows for one (address, name). This collapses each (address, name) pair to a
single row and re-sorts, deterministically, so any agent can run it and get the
identical result. Distinct names at one address are ICF alias groups and are
kept.

functions.csv: one row per (target_rva, name) — ICF alias groups legitimately
hold several names at one address (folded identical COMDATs), so the name is part
of the key. A matched row beats an unmatched one; among equals the smaller
target_size wins (a trimmed-padding row). If rows still tie but name DIFFERENT
sources, only byte-verification can say which source really defines the symbol,
so this refuses to guess and exits 1 naming both. (It used to break that tie on
the lexically first source, which silently repointed findFieldParse at ini.cpp
after it had moved to ini_parsers.cpp — the row then referenced a file that no
longer defined it, and the full gate died with "symbol not found in object".)
symbols.csv: unique (name,address) lines. Run with no arguments; edits in place.
"""
import csv
import io
import sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
FIELDS = ["name", "export_rva", "target_rva", "target_size", "source", "status", "notes"]


def dedup_functions(path):
    rows = [
        row for row in csv.DictReader(path.open(encoding="utf-8", newline=""))
        if row.get("name") != "name" and row.get("target_rva") != "target_rva"
    ]
    def rank(row):
        return (0 if row["status"] == "matched" else 1,   # matched wins
                int(row["target_size"]))                    # smaller (trimmed) wins

    groups = defaultdict(list)
    for row in rows:
        groups[(int(row["target_rva"], 16), row["name"])].append(row)

    best, ambiguous = {}, []
    for key, group in groups.items():
        finalists = [r for r in group if rank(r) == min(rank(r) for r in group)]
        if len({r["source"] for r in finalists}) > 1:
            existing_sources = {r["source"] for r in finalists
                                if (ROOT / r["source"]).is_file()}
            if len(existing_sources) == 1:
                # A union merge can retain a row for a source deleted by the
                # conversion commit.  The sole surviving source is the only
                # ledger owner that can be byte-verified in this checkout.
                finalists = [r for r in finalists if r["source"] in existing_sources]
            else:
                ambiguous.append((key, sorted({r["source"] for r in finalists})))
                continue
        # Same source, so only notes differ: keep the most informative one.
        best[key] = max(finalists, key=lambda r: (len(r["notes"]), r["notes"]))

    if ambiguous:
        print(f"dedup_csv: {len(ambiguous)} row(s) claimed by more than one source "
              "refusing to guess (nothing written):", file=sys.stderr)
        for (rva, name), sources in sorted(ambiguous, key=lambda a: a[0][1]):
            print(f"  - {name} @ 0x{rva:08X}", file=sys.stderr)
            for source in sources:
                print(f"      {source}", file=sys.stderr)
        print("Byte-verify which source defines the symbol (./build.sh <source>), delete "
              "the losing row, then re-run.", file=sys.stderr)
        raise SystemExit(1)

    ordered = sorted(best.values(), key=lambda r: r["name"])
    buffer = io.StringIO()
    writer = csv.DictWriter(buffer, fieldnames=FIELDS)
    writer.writeheader()
    for row in ordered:
        writer.writerow({field: row.get(field, "") for field in FIELDS})
    path.write_text(buffer.getvalue(), encoding="utf-8")
    return len(rows), len(ordered)


def dedup_symbols(path):
    if not path.exists():
        return 0, 0
    lines = path.read_text(encoding="utf-8").splitlines()
    header, body = lines[0], lines[1:]
    # Key on (name,address): union merges can land the same pin twice with
    # different notes text, which exact-line dedup keeps. Prefer the longer
    # line (the one carrying notes), then lexical, so the pick is
    # merge-order-independent.
    best = {}
    for line in body:
        if not line.strip():
            continue
        parts = next(csv.reader(io.StringIO(line)))
        if parts[:2] == ["name", "address"]:
            continue
        key = (parts[0], parts[1] if len(parts) > 1 else "")
        if key not in best or (-len(line), line) < (-len(best[key]), best[key]):
            best[key] = line
    unique = sorted(best.values())
    path.write_text(header + "\n" + "\n".join(unique) + "\n", encoding="utf-8")
    return len(body), len(unique)


def main():
    before, after = dedup_functions(ROOT / "reverse" / "functions.csv")
    print(f"functions.csv: {before} -> {after} rows")
    before, after = dedup_symbols(ROOT / "reverse" / "symbols.csv")
    print(f"symbols.csv:   {before} -> {after} rows")


if __name__ == "__main__":
    main()
