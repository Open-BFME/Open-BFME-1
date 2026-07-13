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
target_size wins (a trimmed-padding row), then the lexically first source, so the
choice never depends on merge order. symbols.csv: unique (name,address) lines.
Run with no arguments; edits both files in place.
"""
import csv
import io
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
FIELDS = ["name", "export_rva", "target_rva", "target_size", "source", "status", "notes"]


def dedup_functions(path):
    rows = list(csv.DictReader(path.open(encoding="utf-8", newline="")))
    best = {}
    for row in rows:
        key = (int(row["target_rva"], 16), row["name"])
        rank = (
            0 if row["status"] == "matched" else 1,   # matched wins
            int(row["target_size"]),                    # smaller (trimmed) wins
            row["source"],                              # deterministic tiebreak
        )
        if key not in best or rank < best[key][0]:
            best[key] = (rank, row)
    ordered = sorted((entry[1] for entry in best.values()), key=lambda r: r["name"])
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
