#!/usr/bin/env python3
"""Fast integrity check for reverse/functions.csv and reverse/symbols.csv (<1s).

Catches the corruption classes that break the full gate long after the fact:
duplicate rows from union merges, two agents claiming overlapping bytes,
malformed rows, rows pointing at missing sources, and LF damage to the CRLF
ledgers. Run it before committing, after every merge/rebase, and in hooks.

Exit 0: both ledgers clean. Exit 1: every problem printed with the fix.
"""
import argparse
import csv
import io
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
FUNCTIONS = ROOT / "reverse" / "functions.csv"
SYMBOLS = ROOT / "reverse" / "symbols.csv"

# realcrc.cpp is linked twice in the retail exe, so these two symbols
# legitimately appear at two addresses each. Any other duplicate name is a bug.
ALLOWED_DUP_NAMES = {
    "?CRC_Memory@@YAKPBEKK@Z",
    "?CRC_String@@YAKPBDK@Z",
}

FUNCTIONS_HEADER = "name,export_rva,target_rva,target_size,source,status,notes"
SYMBOLS_HEADER = "name,address,notes"


def read_ledger(path, spec):
    """spec: None = working tree, "" = git index (staged), else a ref/SHA."""
    if spec is None:
        return path.read_bytes()
    rel = path.relative_to(ROOT).as_posix()
    out = subprocess.run(["git", "-C", str(ROOT), "show", f"{spec}:{rel}"],
                         capture_output=True)
    if out.returncode != 0:
        raise SystemExit(f"check_csv: cannot read {spec}:{rel}: "
                         f"{out.stderr.decode().strip()}")
    return out.stdout


def known_sources(spec):
    """Sources a ledger row may legally reference for the given state.

    A row whose source exists on disk but is not in git is the worst failure
    class this tool guards: the row pushes fine locally and breaks every
    other clone ("references missing source file"). So worktree/staged modes
    require git-tracked (staged counts during a commit), and --ref mode
    requires presence in that commit's tree.
    """
    if spec:  # a ref/SHA
        out = subprocess.run(["git", "-C", str(ROOT), "ls-tree", "-r", "--name-only", spec],
                             capture_output=True, text=True)
        if out.returncode != 0:
            raise SystemExit(f"check_csv: git ls-tree {spec} failed: {out.stderr.strip()}")
        return set(out.stdout.splitlines())
    tracked = subprocess.run(["git", "-C", str(ROOT), "ls-files"],
                             capture_output=True, text=True)
    if tracked.returncode != 0:
        raise SystemExit(f"check_csv: git ls-files failed: {tracked.stderr.strip()}")
    allowed = set(tracked.stdout.splitlines())
    staged = subprocess.run(["git", "-C", str(ROOT), "diff", "--cached", "--name-only",
                             "--diff-filter=ACMRT"], capture_output=True, text=True)
    if staged.returncode == 0:
        allowed.update(staged.stdout.splitlines())
    return allowed


def check_functions(raw, problems, sources_ok):
    if b"\r\n" not in raw[:200]:
        problems.append("functions.csv: CRLF line endings were lost (file is LF). "
                        "Restore from git and use binary-safe edits (tools/dedup_csv.py "
                        "or tools/add_match.py), not csv.writer defaults.")
        # keep checking the content anyway
    text = raw.decode("utf-8", errors="replace")
    rows = list(csv.reader(io.StringIO(text)))
    if not rows or ",".join(rows[0]) != FUNCTIONS_HEADER:
        problems.append(f"functions.csv: bad header (expected '{FUNCTIONS_HEADER}')")
        return
    header_count = sum(1 for r in rows if ",".join(r) == FUNCTIONS_HEADER)
    if header_count > 1:
        problems.append(f"functions.csv: header appears {header_count} times "
                        "(bad merge). Fix: python3 tools/dedup_csv.py")

    seen_exact = set()
    by_rva = {}
    by_name = {}
    matched_ranges = []
    for i, r in enumerate(rows[1:], start=2):
        if not r or (len(r) == 1 and not r[0]):
            continue
        if len(r) != 7:
            problems.append(f"functions.csv line {i}: {len(r)} fields, expected 7: {r[:2]}...")
            continue
        name, export_rva, target_rva, target_size, source, status, _notes = r
        if not name:
            problems.append(f"functions.csv line {i}: empty name")
            continue
        if export_rva:
            try:
                int(export_rva, 16)
            except ValueError:
                problems.append(f"functions.csv line {i} ({name}): bad export_rva '{export_rva}'")
        if not target_rva:
            problems.append(f"functions.csv line {i} ({name}): empty target_rva")
            continue
        try:
            rva = int(target_rva, 16)
        except ValueError:
            problems.append(f"functions.csv line {i} ({name}): bad target_rva '{target_rva}'")
            continue
        try:
            size = int(target_size) if target_size else 0
        except ValueError:
            problems.append(f"functions.csv line {i} ({name}): bad target_size '{target_size}'")
            continue
        if status not in ("matched", "unmatched"):
            problems.append(f"functions.csv line {i} ({name}): bad status '{status}'")
        if status == "matched" and size <= 0:
            problems.append(f"functions.csv line {i} ({name}): matched with target_size {size}")
        if not source:
            problems.append(f"functions.csv line {i} ({name}): empty source")
        elif source not in sources_ok:
            hint = ("file exists on disk but is NOT tracked by git — `git add` it"
                    if (ROOT / source).exists()
                    else "a commit added rows without adding the file")
            problems.append(f"functions.csv line {i} ({name}): source not in git: {source} ({hint})")

        key = (name, target_rva)
        if key in seen_exact:
            problems.append(f"functions.csv line {i}: exact duplicate row for {name} @ {target_rva}. "
                            "Fix: python3 tools/dedup_csv.py")
        seen_exact.add(key)

        rva = int(target_rva, 16)
        if rva in by_rva and by_rva[rva] != name:
            problems.append(f"functions.csv: two names claim target_rva {target_rva}: "
                            f"{by_rva[rva]} and {name}. Byte-verify decides which is real.")
        by_rva.setdefault(rva, name)

        if name in by_name and by_name[name] != rva and name not in ALLOWED_DUP_NAMES:
            problems.append(f"functions.csv: {name} claims two addresses: "
                            f"0x{by_name[name]:08X} and 0x{rva:08X}. One is wrong.")
        by_name.setdefault(name, rva)

        if status == "matched":
            matched_ranges.append((rva, rva + size, name))

    matched_ranges.sort()
    for (a_start, a_end, a_name), (b_start, _b_end, b_name) in zip(matched_ranges, matched_ranges[1:]):
        if b_start < a_end:
            problems.append(f"functions.csv: matched ranges overlap: {a_name} "
                            f"[0x{a_start:08X}-0x{a_end:08X}) and {b_name} @ 0x{b_start:08X}. "
                            "The full gate will refuse to patch. Byte-verify decides which is real.")
    return len([r for r in rows[1:] if len(r) == 7])


def check_symbols(raw, problems):
    # symbols.csv is LF-native. Rows may be 2-field (name,address — the form
    # docs/matching.md tells agents to append) or 3-field with notes. A name
    # may legitimately appear at several addresses: build.py's load_symbol_map
    # treats them all as REL32 resolution candidates. Only exact duplicates
    # and malformed rows are errors.
    text = raw.decode("utf-8", errors="replace")
    rows = list(csv.reader(io.StringIO(text)))
    if not rows or ",".join(rows[0]) != SYMBOLS_HEADER:
        problems.append(f"symbols.csv: bad header (expected '{SYMBOLS_HEADER}')")
        return
    seen_exact = set()
    for i, r in enumerate(rows[1:], start=2):
        if not r or (len(r) == 1 and not r[0]):
            continue
        if len(r) < 2:
            problems.append(f"symbols.csv line {i}: {len(r)} fields, expected at least 2: {r}...")
            continue
        # >3 fields happens when notes contain commas; the gate only reads
        # name and address, so that is fine.
        name, address = r[0], r[1]
        if not name or not address:
            problems.append(f"symbols.csv line {i}: empty name or address")
            continue
        try:
            addr = int(address, 16)
        except ValueError:
            problems.append(f"symbols.csv line {i} ({name}): bad address '{address}'")
            continue
        if (name, addr) in seen_exact:
            problems.append(f"symbols.csv line {i}: exact duplicate row for {name}. "
                            "Fix: python3 tools/dedup_csv.py")
        seen_exact.add((name, addr))
    return len(rows) - 1


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    where = parser.add_mutually_exclusive_group()
    where.add_argument("--staged", action="store_true",
                       help="validate the git-staged ledgers instead of the working tree")
    where.add_argument("--ref", metavar="REF",
                       help="validate the ledgers as committed at REF")
    args = parser.parse_args()

    spec = "" if args.staged else args.ref  # None -> working tree
    problems = []
    n_funcs = check_functions(read_ledger(FUNCTIONS, spec), problems, known_sources(spec))
    n_syms = check_symbols(read_ledger(SYMBOLS, spec), problems)

    if problems:
        print(f"check_csv: {len(problems)} problem(s):", file=sys.stderr)
        for p in problems:
            print(f"  - {p}", file=sys.stderr)
        raise SystemExit(1)
    print(f"check_csv: OK (functions.csv {n_funcs} rows, symbols.csv {n_syms} rows)")


if __name__ == "__main__":
    main()
