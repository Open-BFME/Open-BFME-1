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

sys.path.insert(0, str(Path(__file__).resolve().parent))
import ledger_io  # noqa: E402  (after the path insert that makes it importable)

ROOT = Path(__file__).resolve().parents[1]
FIELDS = ["name", "export_rva", "target_rva", "target_size", "source", "status", "notes"]


def dedup_functions(path):
    # Each row is carried as the bytes it arrived as, terminator included, and a
    # survivor is re-emitted verbatim. Rebuilding rows through csv.DictWriter
    # rewrote all three of functions.csv's historical terminators as \r\n --
    # 95,184 lines on the live ledger, for rows that already exist byte for byte
    # on every other branch, which is 95,184 fresh lines to a union merge. It
    # collapsed nothing at all on that run (157,958 -> 157,958).
    raw = path.read_bytes()
    header, *records = ledger_io.split_records(raw)
    rows = []
    for payload, term in records:
        values = ledger_io.fields(payload)
        if not values:
            continue    # a blank line; the live ledger holds two, csv.DictReader ate them
        row = {field: values[i] if i < len(values) else "" for i, field in enumerate(FIELDS)}
        if row["name"] == "name" and row["target_rva"] == "target_rva":
            continue    # a header line a union merge pushed into the body
        row["_record"] = payload + term
        rows.append(row)

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
            ambiguous.append((key, sorted({r["source"] for r in finalists})))
            continue
        # Same source, so only notes differ: keep the most informative one.
        best[key] = max(finalists, key=lambda r: (len(r["notes"]), r["notes"]))

    if ambiguous:
        print(f"dedup_csv: {len(ambiguous)} row(s) claimed by more than one source — "
              "refusing to guess (nothing written):", file=sys.stderr)
        for (rva, name), sources in sorted(ambiguous, key=lambda a: a[0][1]):
            print(f"  - {name} @ 0x{rva:08X}", file=sys.stderr)
            for source in sources:
                print(f"      {source}", file=sys.stderr)
        print("Byte-verify which source defines the symbol (./build.sh <source>), delete "
              "the losing row, then re-run.", file=sys.stderr)
        raise SystemExit(1)

    ordered = sorted(best.values(), key=lambda r: r["name"])
    out = header[0] + header[1] + b"".join(row["_record"] for row in ordered)
    # Sorting is what makes two agents merging differently converge on one file,
    # but it also moves every row appended since the last run. Writing only on a
    # real change keeps `dedup_csv.py` -- the fix every check_csv message names --
    # from handing the merge driver a whole-file reorder to collapse nothing.
    if out != raw:
        ledger_io.atomic_write_bytes(path, out)
    return len(rows), len(ordered)


def dedup_symbols(path):
    if not path.exists():
        return 0, 0
    raw = path.read_bytes()
    # This rewrites every line, so it decides the file's terminator -- and it used
    # to decide LF unconditionally, which flipped all 70,871 CRLF pins at once and
    # handed the union merge driver a brand-new line for each. Keep what the file
    # already uses; being the tool that rewrites everything also makes this the
    # right place to repair a merged-in stray, out loud.
    census = ledger_io.terminator_census(raw)
    eol = max(census, key=lambda term: len(census[term]), default=b"\r\n").decode("latin1")
    for term, lines in census.items():
        if term != eol.encode("latin1"):
            print(f"symbols.csv:   {len(lines)} line(s) rewritten to the file's own "
                  f"terminator (first line {lines[0]})")
    lines = raw.decode("utf-8").splitlines()
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
    ledger_io.atomic_write_bytes(path, (eol.join([header, *unique]) + eol).encode("utf-8"))
    return len(body), len(unique)


def main():
    before, after = dedup_functions(ROOT / "reverse" / "functions.csv")
    print(f"functions.csv: {before} -> {after} rows")
    before, after = dedup_symbols(ROOT / "reverse" / "symbols.csv")
    print(f"symbols.csv:   {before} -> {after} rows")


if __name__ == "__main__":
    main()
