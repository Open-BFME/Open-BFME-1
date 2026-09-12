#!/usr/bin/env python3
"""Move attempt rows for FINISHED work out of reverse/re_attempts.log.

The log is 24,457 lines and every work-selection tool reads it -- next_work,
brief, fleet_run and the three fleet pickers through re_log, plus
ledger_watchdog, stale_partials and ported_unmatched which iterate raw lines and
compute their own last-wins. It only grows.

WHY THIS IS NOT "KEEP THE LATEST ROW PER RVA". That was the obvious compaction
and it is wrong. re_log's contract is order-dependent in three ways a per-RVA
projection destroys: annotations (`note`, `lever`, `method`, ...) hang on an
EARLIER finding and are skipped rather than counted; the last *verdict* wins
after earlier dead ends, so those dead ends have to still be there; and `void`
RETRACTS a previous row, which needs the row it retracts. re_log says it plainly
-- "The raw log stays intact".

WHAT IS SAFE. A row whose RVA is now a real matched function -- real name, real
source, not a gen- placeholder -- describes work that is FINISHED. No selection
tool can serve that candidate again, so its history cannot change any answer.
That is 8,471 lines over 5,004 RVAs, 35% of the file, and it shrinks as a
consequence of conversions landing rather than by discarding evidence.

Nothing here is taken on trust. The rows are moved only after every consumer is
shown to compute an IDENTICAL answer from the compacted file: re_log's own
latest_records, its dead-end/deferred/standing-status verdicts over every symbol
in the log, and the raw last-wins projection the three direct readers use. Any
difference aborts with the symbol that differed.

    python3 tools/compact_re_attempts.py --check    # report, touch nothing
    python3 tools/compact_re_attempts.py --apply

Removed rows go to reverse/re_attempts-converted.log, which is evidence, not a
middens: it is never read by tooling and never appended to by an agent.
"""
import argparse
import csv
import importlib
import shutil
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
LOG = ROOT / "reverse/re_attempts.log"
ARCHIVE = ROOT / "reverse/re_attempts-converted.log"
FUNCTIONS = ROOT / "reverse/functions.csv"

PLACEHOLDER_PREFIXES = ("?dup_", "?d_", "?j_", "?uw_")


def finished_rvas():
    """RVAs the ledger now claims with a real name backed by real source."""
    done = set()
    for row in csv.DictReader(open(FUNCTIONS, newline="")):
        if row.get("status") != "matched":
            continue
        name = row.get("name") or ""
        source = row.get("source") or ""
        if name.startswith(PLACEHOLDER_PREFIXES) or source.startswith("Code/gen_"):
            continue
        rva = (row.get("target_rva") or "").lower()
        if rva:
            done.add(rva)
    return done


def split(lines, done):
    """A symbol moves only when EVERY row it owns is finished work.

    Moving just the finished rows of a symbol that also has unfinished ones
    resurrects whatever verdict preceded them: ??0TerrainLogic@@QAE@XZ goes from
    `landed` back to `no-match` and the candidate gets suppressed. That is the
    "last verdict wins after earlier dead ends" rule in re_log biting from the
    other side, and it is why this is per-symbol rather than per-row.
    """
    rows_by_symbol = {}
    for line in lines:
        parts = line.rstrip("\n").split("\t")
        rows_by_symbol.setdefault(parts[0] if parts else "", []).append((line, parts))

    sys.path.insert(0, str(ROOT / "tools"))
    import re_log
    movable = set()
    for sym, rows in rows_by_symbol.items():
        if not sym:
            continue
        if not all(len(p) >= 5 and p[1].startswith("0x") and p[1].lower() in done
                   for _, p in rows):
            continue
        # A symbol whose whole history moves vanishes from the verdict map, so a
        # suppression it currently carries would be LOST and next_work would serve
        # the candidate again. re_log prefers leaking to burying, but a leak is
        # still a behaviour change; keep anything currently suppressed.
        if re_log.is_dead_end(sym) or re_log.is_deferred(sym):
            continue
        movable.add(sym)

    keep, move = [], []
    for line in lines:
        parts = line.rstrip("\n").split("\t")
        (move if parts and parts[0] in movable else keep).append(line)
    return keep, move


def projections(path):
    """Everything any consumer derives from the log, as one comparable blob.

    re_log caches per process, so it is reloaded against the candidate file
    rather than trusted to notice the change.
    """
    sys.path.insert(0, str(ROOT / "tools"))
    import re_log
    importlib.reload(re_log)
    re_log.RE_ATTEMPTS = path

    # keys are INT rvas here, hex strings in the raw projection -- the two
    # namespaces are compared separately and must not be conflated.
    latest = {k: tuple(v) if isinstance(v, list) else v
              for k, v in re_log.latest_records(path).items()}

    symbols, raw = set(), {}
    for line in open(path, encoding="utf-8", errors="replace"):
        parts = line.rstrip("\n").split("\t")
        if parts and parts[0]:
            symbols.add(parts[0])
        # the shape ledger_watchdog / stale_partials / ported_unmatched use
        if len(parts) >= 5 and parts[1].startswith("0x"):
            raw[parts[1].lower()] = (parts[3], parts[4])

    verdicts = {}
    for sym in sorted(symbols):
        verdicts[sym] = (re_log.is_dead_end(sym), re_log.is_deferred(sym),
                         re_log.standing_status(sym))
    return {"latest": latest, "raw": raw, "verdicts": verdicts}


def compare(before, after, moved_hex):
    """Differences that matter. An RVA whose every row moved is expected to
    disappear; a CHANGED answer for one still present is a regression."""
    moved_int = {int(h, 16) for h in moved_hex}
    bad = []
    for rva, val in before["latest"].items():
        if rva in moved_int:
            continue
        if after["latest"].get(rva) != val:
            bad.append(f"latest_records changed for {rva:#010x}")
    for rva, val in before["raw"].items():
        if rva in moved_hex:
            continue
        if after["raw"].get(rva) != val:
            bad.append(f"raw last-wins changed for {rva}")
    for sym, val in before["verdicts"].items():
        if sym not in after["verdicts"]:
            # Its whole history moved. That is only safe if it carried no
            # suppression -- split() enforces that, and this re-asserts it here
            # so the invariant cannot be lost in one place without the other.
            if val[0] or val[1]:
                bad.append(f"suppression lost for {sym}: {val}")
            continue
        if after["verdicts"][sym] != val:
            bad.append(f"verdict changed for {sym}: {val} -> {after['verdicts'][sym]}")
    return bad


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--apply", action="store_true")
    args = ap.parse_args()

    lines = open(LOG, encoding="utf-8", errors="replace").readlines()
    done = finished_rvas()
    keep, move = split(lines, done)
    print(f"re_attempts.log: {len(lines):,} lines")
    print(f"  finished-work rows (RVA is a real matched row): {len(move):,} "
          f"({100 * len(move) / max(len(lines), 1):.0f}%)")
    print(f"  kept                                          : {len(keep):,}")
    if not move:
        return 0

    scratch = ROOT / "build/re_attempts.candidate.log"
    scratch.parent.mkdir(exist_ok=True)
    scratch.write_text("".join(keep), encoding="utf-8")

    moved_rvas = {p.split("\t")[1].lower() for p in move
                  if len(p.split("\t")) >= 5 and p.split("\t")[1].startswith("0x")}
    before = projections(LOG)
    after = projections(scratch)
    bad = compare(before, after, moved_rvas)
    if bad:
        print(f"\nREFUSING: {len(bad)} consumer answer(s) would change:", file=sys.stderr)
        for b in bad[:15]:
            print(f"   {b}", file=sys.stderr)
        return 1
    print(f"  every consumer answer identical "
          f"({len(before['verdicts']):,} symbols, {len(before['raw']):,} RVAs checked)")

    if not args.apply:
        print("\n--apply to write. Removed rows go to reverse/re_attempts-converted.log")
        return 0

    with open(ARCHIVE, "a", encoding="utf-8") as fh:
        fh.write("".join(move))
    shutil.move(str(scratch), str(LOG))
    print(f"\nwrote {LOG.name} ({len(keep):,} lines) and appended "
          f"{len(move):,} to {ARCHIVE.name}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
