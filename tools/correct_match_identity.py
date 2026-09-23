#!/usr/bin/env python3
"""Correct one evidence-backed matched name without changing its verified body.

The replacement keeps the same source, RVA and extent. ``object-symbol=`` names
the C++ symbol that still emits the bytes while the ledger records the retail
identity. Unlike add_match --replace-rva, this is for an existing native claim;
the retired name gets a tombstone so union merges cannot resurrect it.
"""

import argparse
import csv
import io
import subprocess
import sys
from pathlib import Path

import add_match
import ledger_io
from portable_lock import lock

ROOT = Path(__file__).resolve().parents[1]


def fail(message):
    raise SystemExit(f"correct_match_identity: {message}")


def checked_field(label, value):
    if not value or set(value) & set(',";\r\n'):
        fail(f"{label} is empty or contains a CSV delimiter")
    return value


def correct(root, old_name, new_name, rva, size, source, evidence):
    root = Path(root).resolve()
    old_name = checked_field("old name", old_name)
    new_name = checked_field("new name", new_name)
    source = checked_field("source", source)
    evidence = checked_field("evidence", evidence)
    if old_name == new_name:
        fail("old and new names are identical")
    if not evidence.startswith(("docs/", "reverse/")) or ".." in Path(evidence).parts:
        fail("evidence must be a file under docs/ or reverse/")
    if not source.startswith("Code/") or ".." in Path(source).parts:
        fail("source must be a file under Code/")
    if not (root / evidence).is_file() or not (root / evidence).read_bytes().strip():
        fail(f"evidence file is missing or empty: {evidence}")
    if not (root / source).is_file():
        fail(f"source file is missing: {source}")
    functions = root / "reverse/functions.csv"
    deleted = root / "reverse/deleted_rows.csv"
    with (root / "reverse/.add_match.lock").open("a") as lock_file:
        lock(lock_file, exclusive=True,
             wait_notice="correct_match_identity: waiting for ledger lock...")
        before = functions.read_bytes()
        old_deleted = deleted.read_bytes()
        add_match.validate_tombstone_append_target(old_deleted, deleted)
        rows = add_match.parse_ledger(before)
        at_rva = [row for row in rows if row["rva"] == rva]
        if len(at_rva) != 1:
            fail(f"0x{rva:08X} has {len(at_rva)} rows; exactly one is required")
        row = at_rva[0]
        if (row["name"], row["size"], row["source"], row["status"]) != (
                old_name, size, source, "matched"):
            fail(f"0x{rva:08X} no longer has the expected matched native row")
        if add_match.replaceable_scaffold(row):
            fail("use add_match --replace-rva for a generated scaffold")
        if any(other["name"] == new_name for other in rows):
            fail(f"new name is already claimed: {new_name}")
        if "object-symbol=" in row["notes"]:
            fail("the old row already uses an object-symbol alias; inspect it first")

        # Keep the corrected row at its original location and preserve all
        # surrounding mixed CRCRLF/CRLF/LF terminators exactly.
        new_records = []
        count = 0
        for payload, terminator in ledger_io.split_records(before):
            fields = ledger_io.fields(payload)
            if len(fields) == 7 and fields[0] == old_name and int(fields[2], 16) == rva:
                if fields[1]:
                    fail("export_rva is set; this correction cannot preserve its meaning")
                note = fields[6]
                note += (";" if note and not note.endswith(";") else "")
                note += f"object-symbol={old_name};identity-evidence={evidence}"
                fields[0], fields[6] = new_name, note
                encoded = io.StringIO(newline="")
                csv.writer(encoded, lineterminator="").writerow(fields)
                new_records.append(encoded.getvalue().encode("utf-8") + terminator)
                count += 1
            else:
                new_records.append(payload + terminator)
        if count != 1:
            fail(f"expected one exact ledger record, found {count}")
        changed = b"".join(new_records)

        try:
            add_match.append_replacement_tombstone(
                deleted, row, new_name, rva, size, source, verified=True)
            ledger_io.atomic_write_bytes(functions, changed)
            env = add_match.verification_environment(root / source, source, new_name, rva)
            command = ([sys.executable, str(root / "tools/build.py"), source]
                       if sys.platform == "win32" else [str(root / "build.sh"), source])
            result = subprocess.run(command, cwd=root, env=env)
            if result.returncode:
                fail(f"scoped byte gate failed with exit {result.returncode}")
            result = subprocess.run([sys.executable, str(root / "tools/check_csv.py")],
                                    cwd=root)
            if result.returncode:
                fail(f"check_csv failed with exit {result.returncode}")
        except BaseException:
            ledger_io.atomic_write_bytes(functions, before)
            ledger_io.atomic_write_bytes(deleted, old_deleted)
            print("correct_match_identity: rolled back both ledgers", file=sys.stderr)
            raise
    print(f"correct_match_identity: verified {new_name} at 0x{rva:08X}/{size}B")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("old_name")
    parser.add_argument("new_name")
    parser.add_argument("rva", type=lambda value: int(value, 16))
    parser.add_argument("size", type=int)
    parser.add_argument("source")
    parser.add_argument("--evidence", required=True)
    parser.add_argument("--root", type=Path, default=ROOT,
                        help="test-only repository root override")
    args = parser.parse_args()
    if args.size <= 0:
        fail("size must be positive")
    correct(args.root, args.old_name, args.new_name, args.rva,
            args.size, args.source, args.evidence)


if __name__ == "__main__":
    main()
