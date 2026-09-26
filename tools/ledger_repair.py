#!/usr/bin/env python3
"""Repair targets/game/reverse/*.csv after a rebase that union-merged our own appended rows.

`merge=union` keeps both sides of every appended line, so rebasing over one's own
work resurrects rows this branch had superseded. A rebase runs no hook, so nothing
else catches it, and each unrepaired rebase makes the next one worse. Five shapes,
in descending order of confidence -- nothing here guesses:

  1. exact-duplicate records (byte-identical payload seen earlier) -> drop later
  2. a row whose `source` file does not exist, where another row for the same
     (name, target_rva) names a file that does                    -> drop the dead one
  3. same, matched by target_rva alone, for rows where this branch renamed the
     SYMBOL as well as the file                                    -> drop the dead one
  4. a row targets/game/reverse/deleted_rows.csv already tombstones, arriving again from a
     branch that forked before the delete                          -> re-apply the
     tombstone; the recorded reason is the proof, so this is replay, not a decision
  5. a bare LF terminator in the otherwise-CRLF symbols.csv. The union driver
     treats it as a DISTINCT line and re-adds it on every rebase, which is how
     4,172 pins became 8,784 (see ledger_io.uniform_terminator) and how this file
     arrived DOUBLED three separate times in one session. functions.csv
     legitimately mixes all three terminators, so it is left alone.

Anything else is reported and left alone. Run from the repo root, then check_csv,
pin_consistency --check and identity_guard.

Never rewrite game/gen_asm/ rows' bytes here: conversion_gate rule C3 reads the
range as "adds dump rows AND edits sources" and blocks the push.
"""
import collections
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import ledger_io
import merge_cluster as mc
from portable_lock import lock, unlock


def repair():
    handle = (ROOT / mc.LOCK).open("a")
    lock(handle, exclusive=True, wait_notice="ledger_repair: waiting for the ledger lock...")
    try:
        for rel in ("targets/game/reverse/functions.csv", "targets/game/reverse/symbols.csv"):
            path = ROOT / rel
            records = ledger_io.split_records(path.read_bytes())

            seen, kept, dups = set(), [], 0
            for i, (payload, term) in enumerate(records):
                if i and payload in seen:
                    dups += 1
                    continue
                seen.add(payload)
                kept.append((payload, term))

            dead_named = dead_addr = resurrected = 0
            unresolved = []
            if rel.endswith("functions.csv"):
                live_pair, live_rva = set(), set()
                for i, (payload, _t) in enumerate(kept):
                    if not i:
                        continue
                    f = ledger_io.fields(payload)
                    if len(f) >= 6 and f[4] and (ROOT / f[4]).exists():
                        live_pair.add((f[0], f[2]))
                        live_rva.add(f[2])
                out = []
                for i, (payload, term) in enumerate(kept):
                    if i:
                        f = ledger_io.fields(payload)
                        if (len(f) >= 6 and f[4].startswith("game/")
                                and not (ROOT / f[4]).exists()):
                            if (f[0], f[2]) in live_pair:
                                dead_named += 1
                                continue
                            if f[2] in live_rva:
                                dead_addr += 1
                                continue
                            unresolved.append((f[0][:70], f[4]))
                    out.append((payload, term))
                kept = out

            # A row tombstoned in targets/game/reverse/deleted_rows.csv comes back through
            # union merge from any branch that forked before the delete, and
            # check_csv refuses the commit. The tombstone already carries the
            # proof, so re-applying it is replay, not a new decision.
            if rel.endswith("functions.csv"):
                tomb = set()
                path_t = ROOT / "targets/game/reverse/deleted_rows.csv"
                if path_t.exists():
                    for i, (payload, _t) in enumerate(
                            ledger_io.split_records(path_t.read_bytes())):
                        if not i:
                            continue
                        f = ledger_io.fields(payload)
                        if len(f) >= 2:
                            tomb.add((f[0], f[1].upper()))
                out = []
                for i, (payload, term) in enumerate(kept):
                    f = ledger_io.fields(payload)
                    if i and len(f) >= 3 and (f[0], f[2].upper()) in tomb:
                        resurrected += 1
                        continue
                    out.append((payload, term))
                kept = out

            # symbols.csv must use ONE terminator or union merge duplicates every
            # pin whose spelling differs -- ledger_io.uniform_terminator records
            # that this is how 4,172 pins became 8,784, and it is why this file
            # arrived DOUBLED after three separate rebases. Nothing enforces it
            # after a rebase, because a rebase runs no hook. functions.csv
            # legitimately mixes all three, so it is left alone.
            fixed = 0
            if rel.endswith("symbols.csv") and len(kept) > 1:
                census = collections.Counter(t for _, t in kept[1:])
                dominant = census.most_common(1)[0][0]
                rebuilt = [kept[0]]
                for payload, term in kept[1:]:
                    if term != dominant:
                        term = dominant
                        fixed += 1
                    rebuilt.append((payload, term))
                kept = rebuilt

            ledger_io.atomic_write_bytes(path, b"".join(p + t for p, t in kept))
            print("%s: %d exact dup(s), %d dead-by-name, %d dead-by-address, "
                  "%d resurrected tombstone(s), %d terminator(s) normalised, "
                  "%d unresolved"
                  % (rel, dups, dead_named, dead_addr, resurrected, fixed,
                     len(unresolved)))
            for name, src in unresolved[:10]:
                print("    UNRESOLVED %s -> %s" % (name, src))
    finally:
        unlock(handle)
        handle.close()


if __name__ == "__main__":
    repair()
