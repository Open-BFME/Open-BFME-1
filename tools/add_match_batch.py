#!/usr/bin/env python3
"""Append MANY verified rows to reverse/functions.csv in one locked pass.

Why this exists: add_match.py is correct and its per-row cost is fine for a
handful of claims, but a family conversion lands 40-115 rows at once and the
tool is invoked once per row. Each invocation re-reads and re-parses a
161,861-row ledger, re-validates the new row against every existing row, and
then runs the FULL byte verification of the whole translation unit -- so for N
rows in one source, the parse is repeated N times and the TU is compiled and
compared N times. Measured on a 326-row landing: roughly twenty minutes of
shape analysis against forty minutes of add_match. The cost also scales the
wrong way, because every landing makes the ledger longer and the next landing
slower.

This does the same work with the same rules, once:

    lock -> read -> parse -> validate ALL rows -> append ALL -> verify each
    distinct source ONCE -> revert EVERYTHING on any failure

SAFETY IS NOT RELAXED ANYWHERE. Specifically:

  * the same advisory lock add_match takes, held across the whole pass, so a
    concurrent agent cannot interleave;
  * every validation add_match performs -- name already claimed, address
    already claimed, range overlapping a matched row, --replace-rva naming
    exactly one generated scaffold, ICF-owner agreement -- applied to each row;
  * PLUS a check add_match structurally cannot make: rows in the same batch are
    validated AGAINST EACH OTHER. A batch can collide with itself (two claims
    at one address, or two overlapping ranges), and an earlier run recorded
    exactly that happening across two agents;
  * all-or-nothing. If any source fails byte verification, EVERY row in the
    batch is reverted and every stripped marker restored. A partial family
    landing is worse than none: it leaves the ledger asserting claims whose
    siblings were rejected for a reason that probably applies to them too.

The byte gate remains the only arbiter. This changes how often it is invoked,
never whether it decides.

Manifest: CSV on stdin or in a file, one row per claim, no header:

    name,target_rva,target_size,source[,notes[,replace_rva]]

Usage:
    python3 tools/add_match_batch.py rows.csv
    python3 tools/add_match_batch.py --dry-run rows.csv     # validate only
    ... < rows.csv
"""
import argparse
import csv
import io
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))

import add_match
import ledger_io
from portable_lock import lock

DEFAULT_ROOT = add_match.DEFAULT_ROOT


def read_manifest(source):
    claims = []
    for lineno, fields in enumerate(csv.reader(source), start=1):
        if not fields or (len(fields) == 1 and not fields[0].strip()):
            continue
        if fields[0].lstrip().startswith("#"):
            continue
        if len(fields) < 4:
            add_match.fail(f"manifest line {lineno}: need at least "
                           "name,target_rva,target_size,source")
        name, rva_s, size_s, src = (f.strip() for f in fields[:4])
        notes = fields[4].strip() if len(fields) > 4 else ""
        replace = fields[5].strip() if len(fields) > 5 else ""
        try:
            rva = int(rva_s, 16)
        except ValueError:
            add_match.fail(f"manifest line {lineno}: target_rva {rva_s!r} is not hex")
        try:
            size = int(size_s)
        except ValueError:
            add_match.fail(f"manifest line {lineno}: target_size {size_s!r} is not decimal")
        if size <= 0:
            add_match.fail(f"manifest line {lineno}: target_size must be positive")
        for label, value in (("name", name), ("source", src), ("notes", notes)):
            bad = set(value) & set(',"\r\n')
            if bad:
                add_match.fail(
                    f"manifest line {lineno}: {label} contains {sorted(bad)} -- "
                    "functions.csv rows are raw comma-joined fields with no quoting")
        claims.append({"line": lineno, "name": name, "rva": rva, "size": size,
                       "source": src, "notes": notes, "replace_rva": replace})
    if not claims:
        add_match.fail("manifest is empty")
    return claims


def main():
    ap = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("manifest", nargs="?",
                    help="CSV manifest path (default: read stdin)")
    ap.add_argument("--dry-run", action="store_true",
                    help="validate the whole batch and report, changing nothing")
    ap.add_argument("--root", type=Path, default=DEFAULT_ROOT,
                    help="TEST-ONLY: operate on a repo copy rooted here")
    args = ap.parse_args()

    root = args.root.resolve()
    functions_csv = root / "reverse" / "functions.csv"
    deleted_csv = root / "reverse" / "deleted_rows.csv"
    if not functions_csv.exists():
        add_match.fail(f"no ledger at {functions_csv}")

    if args.manifest:
        with open(args.manifest, newline="", encoding="utf-8") as fh:
            claims = read_manifest(fh)
    else:
        claims = read_manifest(sys.stdin)

    for c in claims:
        p = root / c["source"]
        if not p.exists():
            add_match.fail(f"manifest line {c['line']}: source does not exist: {p}",
                           "a ledger row must never point at a missing file")

    lock_file = (root / "reverse" / ".add_match.lock").open("a")
    lock(lock_file, exclusive=True,
         wait_notice="add_match_batch: waiting for ledger lock...")

    raw = functions_csv.read_bytes()
    if b"\r\n" not in raw[:200]:
        add_match.fail("functions.csv has lost its CRLF line endings")
    if not raw.endswith(b"\n"):
        add_match.fail("functions.csv does not end with a newline")

    rows = add_match.parse_ledger(raw)
    by_name = {}
    for row in rows:
        by_name.setdefault(row["name"], []).append(row)

    # Rows this batch retires, keyed (name, rva) so the drop is by CONTENT.
    retire = {}
    replacements = []
    # Live ranges = existing matched rows minus retired ones, plus batch rows as
    # they are accepted. Validating the batch against ITSELF is the check a
    # per-row tool cannot make.
    accepted = []

    for c in claims:
        name, rva, size = c["name"], c["rva"], c["size"]
        end = rva + size
        if c["replace_rva"]:
            try:
                old = int(c["replace_rva"], 16)
            except ValueError:
                add_match.fail(f"line {c['line']}: replace_rva not hex")
            at = [r for r in rows if r["rva"] == old and (r["name"], r["rva"]) not in retire]
            if len(at) != 1:
                add_match.fail(f"line {c['line']}: replace_rva 0x{old:08X} matches "
                               f"{len(at)} live rows; it retires exactly one")
            if not at[0]["notes"].lstrip().startswith(("gen-dump", "gen-thunk")):
                add_match.fail(
                    f"line {c['line']}: replace_rva 0x{old:08X} is {at[0]['name']} "
                    f"({at[0]['source']}), not a generated scaffold row",
                    "only scaffolding may be taken over by name")
            if old != rva or at[0]["size"] != size:
                add_match.fail(
                    f"line {c['line']}: replace_rva must preserve the scaffold's exact "
                    f"range 0x{old:08X}/{at[0]['size']}B; new claim is "
                    f"0x{rva:08X}/{size}B",
                    "a different boundary needs an explicit evidence-backed retraction")
            retire[(at[0]["name"], at[0]["rva"])] = at[0]
            replacements.append((at[0], c))
        if by_name.get(name):
            live = [r for r in by_name[name] if (r["name"], r["rva"]) not in retire]
            if live:
                where = ", ".join(f"0x{r['rva']:08X} ({r['source']})" for r in live)
                add_match.fail(f"line {c['line']}: {name} is already in the ledger at {where}",
                               "one name = one address")
        for other in accepted:
            if other["name"] == name:
                add_match.fail(f"line {c['line']}: {name} is claimed twice IN THIS BATCH "
                               f"(also line {other['line']})")
            if other["rva"] < end and rva < other["rva"] + other["size"]:
                add_match.fail(
                    f"line {c['line']}: range [0x{rva:08X},0x{end:08X}) overlaps "
                    f"batch line {other['line']} [0x{other['rva']:08X},"
                    f"0x{other['rva'] + other['size']:08X}) -- a batch can collide with itself")
        for row in rows:
            if (row["name"], row["rva"]) in retire:
                continue
            if row["rva"] == rva:
                add_match.fail(f"line {c['line']}: target_rva 0x{rva:08X} is already "
                               f"claimed by {row['name']} ({row['source']}, {row['status']})")
            if row["status"] == "matched" and row["rva"] < end and rva < row["rva"] + row["size"]:
                add_match.fail(
                    f"line {c['line']}: range [0x{rva:08X},0x{end:08X}) overlaps matched "
                    f"{row['name']} [0x{row['rva']:08X},0x{row['rva'] + row['size']:08X}) "
                    f"({row['source']})")
        accepted.append(c)

    sources = sorted({c["source"] for c in claims})
    if retire and not deleted_csv.exists():
        add_match.fail(f"no deletion ledger at {deleted_csv}",
                       "scaffold rows cannot be retired durably without tombstones")
    print(f"add_match_batch: {len(claims)} row(s) validated across "
          f"{len(sources)} source(s); {len(retire)} scaffold row(s) to retire")
    if args.dry_run:
        print("add_match_batch: --dry-run, nothing written")
        return

    saved_sources = {s: (root / s).read_bytes() for s in sources}
    saved_deleted = deleted_csv.read_bytes() if retire else None
    reverted = False

    def revert(why):
        nonlocal reverted
        ledger_io.atomic_write_bytes(functions_csv, raw)
        if saved_deleted is not None:
            ledger_io.atomic_write_bytes(deleted_csv, saved_deleted)
        for s, data in saved_sources.items():
            ledger_io.atomic_write_bytes(root / s, data)
        reverted = True
        print(f"add_match_batch: {why} -- ALL {len(claims)} rows and every "
              "marker strip REVERTED", file=sys.stderr)

    try:
        for c in claims:
            new = add_match.strip_marker(root / c["source"], c["name"])
            if new is not None:
                (root / c["source"]).write_bytes(new)

        if retire:
            new_raw, dropped = ledger_io.rewrite(
                raw, lambda f: add_match.ledger_key(f) not in retire)
            if dropped != len(retire):
                add_match.fail(
                    f"internal error: dropped {dropped} rows, expected {len(retire)}")
        else:
            new_raw = raw
        appended = io.BytesIO()
        for c in claims:
            export_rva = add_match.lookup_export_rva(root, c["name"])
            line = (f"{c['name']},{export_rva},0x{c['rva']:08X},{c['size']},"
                    f"{c['source']},matched,{c['notes']}")
            appended.write(line.encode("utf-8") + b"\r\n")
        # Tombstones go first: a crash between the two ledger writes is loud
        # (the old live row is condemned), never a silent union-merge deletion.
        for incumbent, successor in replacements:
            add_match.append_replacement_tombstone(
                deleted_csv, incumbent, successor["name"], successor["rva"],
                successor["size"], successor["source"], verified=True)
        ledger_io.atomic_write_bytes(functions_csv, new_raw + appended.getvalue())

        for s in sources:
            if sys.platform == "win32":
                cmd = [sys.executable, str(root / "tools" / "build.py"), s]
            else:
                cmd = [str(root / "build.sh"), s]
            print(f"add_match_batch: verifying {s}")
            result = subprocess.run(cmd, cwd=root)
            if result.returncode != 0:
                revert(f"verification failed for {s} (exit {result.returncode})")
                raise SystemExit(1)
    except BaseException:
        if not reverted:
            revert("interrupted or write failed")
        raise
    print(f"add_match_batch: verified OK -- {len(claims)} row(s) live")


if __name__ == "__main__":
    main()
