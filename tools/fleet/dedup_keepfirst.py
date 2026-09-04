#!/usr/bin/env python3
"""Drop EXACT duplicate records (keep first) from the ledgers, under the lock.
The union-merge artifact after every rebase; see docs/lessons.md."""
import sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2 if Path(__file__).resolve().parent.name == "fleet" else 1]
sys.path.insert(0, str(ROOT / "tools"))
import os, ledger_io, portable_lock
with open(ROOT / "reverse/.add_match.lock", "a+") as h:
    if not os.environ.get("HARVEST_HAS_LOCK"):
        portable_lock.lock(h, exclusive=True)
    for name in ("reverse/functions.csv", "reverse/symbols.csv"):
        p = ROOT / name
        raw = p.read_bytes()
        seen = set()
        def keep(f, seen=seen):
            k = tuple(f)
            if k in seen:
                return False
            seen.add(k)
            return True
        new, dropped = ledger_io.rewrite(raw, keep)
        if dropped:
            ledger_io.atomic_write_bytes(p, new)
        print(f"{name}: dropped {dropped} exact duplicate(s)")
    if not os.environ.get("HARVEST_HAS_LOCK"):
        portable_lock.unlock(h)
