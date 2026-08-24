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
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import ledger_io  # noqa: E402  (after the path insert that makes it importable)

ROOT = Path(__file__).resolve().parents[1]
FUNCTIONS = ROOT / "reverse" / "functions.csv"
SYMBOLS = ROOT / "reverse" / "symbols.csv"
DELETED = ROOT / "reverse" / "deleted_rows.csv"

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


def tombstones():
    """(name, rva) pairs deleted on purpose -> why. See reverse/deleted_rows.csv.

    functions.csv merges with git's union driver, which cannot express a
    deletion: any branch forked before the delete puts the row back with no
    conflict. Without this, a proven-wrong row silently returns to master.
    """
    if not DELETED.exists():
        return {}
    out = {}
    for line in DELETED.read_text(encoding="utf-8").splitlines():
        if not line.strip() or line.startswith("#") or line.startswith("name,"):
            continue
        row = next(csv.reader(io.StringIO(line)))
        if len(row) < 2:
            continue
        try:
            out[(row[0], int(row[1], 16))] = row[2] if len(row) > 2 else ""
        except ValueError:
            continue
    return out


def check_functions(raw, problems, sources_ok):
    deleted = tombstones()
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

        if (name, rva) in deleted:
            problems.append(f"functions.csv line {i}: {name} @ {target_rva} was deleted on "
                            f"purpose and has come back (a union merge from a branch that "
                            f"forked before the delete). Reason it was deleted: "
                            f"{deleted[(name, rva)]}. Drop the row again, or — if you can "
                            f"byte-prove it — remove its line from reverse/deleted_rows.csv "
                            f"in the same commit.")

        key = (name, target_rva)
        if key in seen_exact:
            problems.append(f"functions.csv line {i}: exact duplicate row for {name} @ {target_rva}. "
                            "Fix: python3 tools/dedup_csv.py")
        seen_exact.add(key)

        rva = int(target_rva, 16)
        gen_row = _notes.lstrip().startswith("gen-")
        if rva in by_rva and by_rva[rva][0] != name:
            prev_name, prev_size, prev_gen = by_rva[rva]
            if prev_size != size:
                problems.append(f"functions.csv: two names claim target_rva {target_rva} with "
                                f"different sizes: {prev_name} ({prev_size}B) and {name} ({size}B). "
                                "Byte-verify decides which is real.")
            elif gen_row != prev_gen:
                # A gen-* placeholder sharing an exact range with a real identity
                # is not an ICF alias — the placeholder is the same function under
                # a synthetic name and must yield (union merges land both sides
                # silently; this is the only gate that can see it).
                problems.append(f"functions.csv: {name} and {prev_name} claim the same range "
                                f"at {target_rva} but exactly one is a gen-* placeholder. "
                                "Retract the placeholder row and tombstone it in "
                                "reverse/deleted_rows.csv.")
            # same (rva, size), same kind: ICF alias group — identical COMDATs
            # folded to one address in retail; each byte-verifies independently.
        by_rva.setdefault(rva, (name, size, gen_row))

        if name in by_name and by_name[name] != rva and name not in ALLOWED_DUP_NAMES:
            problems.append(f"functions.csv: {name} claims two addresses: "
                            f"0x{by_name[name]:08X} and 0x{rva:08X}. One is wrong.")
        by_name.setdefault(name, rva)

        if status == "matched":
            matched_ranges.append((rva, rva + size, name))

    matched_ranges.sort()
    for (a_start, a_end, a_name), (b_start, b_end, b_name) in zip(matched_ranges, matched_ranges[1:]):
        if b_start < a_end:
            if a_start == b_start and a_end == b_end:
                continue  # ICF alias group: identical range claimed by multiple names
            problems.append(f"functions.csv: matched ranges overlap: {a_name} "
                            f"[0x{a_start:08X}-0x{a_end:08X}) and {b_name} @ 0x{b_start:08X}. "
                            "The full gate will refuse to patch. Byte-verify decides which is real.")
    return len([r for r in rows[1:] if len(r) == 7])


def check_symbols(raw, problems):
    # Rows may be 2-field (name,address — the form docs/matching.md tells agents
    # to append) or 3-field with notes. A name may legitimately appear at several
    # addresses: build.py's load_symbol_map treats them all as REL32 resolution
    # candidates. Only exact duplicates and malformed rows are errors.
    #
    # The file must carry ONE terminator, and this is where that is caught. It is
    # merge=union, so a pin differing from its twin by a single \r is a distinct
    # line to the merge driver and lands twice; a duplicate pin is legal, so
    # nothing downstream notices, while the same mixing in functions.csv trips
    # the duplicate-name rule above. gen_small.line_terminator refuses to append
    # to a mixed file — that stops a whole wave, in a session that did not cause
    # it. 66 LF pins reached master this way and blocked landing until they were
    # repaired by hand.
    census = ledger_io.terminator_census(raw)
    if len(census) > 1:
        spelling = {b"\n": "LF", b"\r\n": "CRLF", b"\r\r\n": "CRCRLF"}
        odd = min(census.items(), key=lambda item: len(item[1]))
        problems.append(
            f"symbols.csv mixes line terminators: {len(odd[1])} "
            f"{spelling.get(odd[0], repr(odd[0]))} line(s) in a file that is otherwise "
            f"{spelling.get(max(census, key=lambda t: len(census[t])), '?')} "
            f"(line {odd[1][0]}{', ...' if len(odd[1]) > 1 else ''}). It is union-merged, "
            "so the odd lines duplicate every pin they carry on the next rebase. "
            "Fix: python3 tools/dedup_csv.py")
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
        # Short addresses are only inconsistent zero-padding and parse fine, but
        # more than eight hex digits cannot be a 32-bit RVA in any spelling, so
        # it is always a typo — three such rows reached the ledger before this
        # check existed, each one digit too long and silently parsing correctly.
        if len(address.removeprefix("0x").removeprefix("0X")) > 8:
            problems.append(f"symbols.csv line {i} ({name}): address '{address}' has "
                            f"more than 8 hex digits; write it as 0x{addr:08X}")
        if (name, addr) in seen_exact:
            problems.append(f"symbols.csv line {i}: exact duplicate row for {name}. "
                            "Fix: python3 tools/dedup_csv.py")
        seen_exact.add((name, addr))
    return len(rows) - 1


ATTEMPTS_DIR = "reverse/attempts/"
ATTEMPT_NAME = re.compile(r"^0x[0-9a-f]{8}\.cpp$")
ATTEMPT_LIMIT = 64 * 1024


def _attempt_paths(spec):
    """Stash files as they exist in the state being gated, never on disk.

    A working-tree scan would fail an unrelated `--ref` push over a stray
    uncommitted file, so this reads the same source of truth known_sources does.
    """
    return sorted(p for p in known_sources(spec)
                  if p.startswith(ATTEMPTS_DIR) and p != ATTEMPTS_DIR)


def check_attempts(spec, problems):
    """Validate banked near-miss bodies under reverse/attempts/.

    A stash is evidence handed to the next agent, so a malformed one is worse
    than none: it gets served at a score nobody measured. Absent directory means
    nothing banked yet, which is the normal state and passes.
    """
    paths = _attempt_paths(spec)
    if not paths:
        return 0
    import re_log

    matched = {}
    for row in csv.reader(io.StringIO(read_ledger(FUNCTIONS, spec).decode(
            "utf-8", errors="replace"))):
        if len(row) == 7 and row[5] == "matched":
            matched.setdefault(row[2].lower(), []).append((row[0], row[4]))

    for rel in paths:
        name = rel[len(ATTEMPTS_DIR):]
        if not ATTEMPT_NAME.match(name):
            problems.append(
                f"{rel}: name must be the lowercase rva it banks, e.g. "
                f"0x000c8220.cpp — serving looks the stash up by address.")
            continue
        blob = read_ledger(ROOT / rel, spec)
        if len(blob) > ATTEMPT_LIMIT:
            problems.append(f"{rel}: {len(blob)} bytes, over {ATTEMPT_LIMIT}. "
                            f"That is not one function body; delete it.")
        lines = blob.decode("utf-8", errors="replace").splitlines()
        if len(lines) < 2 or not re_log._STASH_SCORE.match(lines[1]):
            problems.append(
                f"{rel}: line 2 must read '// partial score=<0..1> date=<iso>'. "
                f"An unreadable score cannot be ranked; rewrite or delete it.")
            continue
        rva = name[:-len(".cpp")]
        claims = matched.get(rva, [])
        # A stash on a matched rva is an orphan ONLY when real C++ already owns
        # it. Every dump candidate is matched by construction -- a naked
        # transcription lands byte-verified -- and converting those is exactly
        # what a stash is for, so the dump lane must survive this check.
        for sym, source in claims:
            # Same two-part test progress.py uses to route a row to its `dump`
            # lane: an .asm/.lib row is retail re-encoded by extension alone,
            # and a .cpp row is one when its body is a naked/__emit lift.
            if Path(source).suffix.lower() in (".asm", ".s", ".lib"):
                continue
            text = read_ledger(ROOT / source, spec).decode("utf-8", errors="replace")
            if "__declspec(naked)" in text or "_emit" in text:
                continue
            problems.append(
                f"{rel}: {rva} already has real C++ at {source} ({sym}). "
                f"It landed — delete the stash.")
            break
    return len(paths)


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
    check_attempts(spec, problems)

    if problems:
        print(f"check_csv: {len(problems)} problem(s):", file=sys.stderr)
        for p in problems:
            print(f"  - {p}", file=sys.stderr)
        raise SystemExit(1)
    print(f"check_csv: OK (functions.csv {n_funcs} rows, symbols.csv {n_syms} rows)")


if __name__ == "__main__":
    main()
