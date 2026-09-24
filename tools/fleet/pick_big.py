#!/usr/bin/env python3
"""Select the next N available LARGE dump bodies for a big-body seat.
Prints RVAs, one per line.

Window defaults to 1000..2500 bytes: the first hour of 3-6KB picks re-worked
bodies that already carried banked partials (the known walls) and landed 1 of
38. Fewest prior attempts first, then by size descending. Busy and recently-run
bodies come from tools/eligibility.py, the predicate every lane shares.
"""
import csv, sys, time, datetime
from pathlib import Path
sys.path.insert(0, 'tools')
from portable_lock import lock
import eligibility
ROOT = Path('.').resolve()
n_want = int(sys.argv[1]) if len(sys.argv) > 1 else 2
min_bytes = int(sys.argv[2]) if len(sys.argv) > 2 else 1000
max_bytes = int(sys.argv[3]) if len(sys.argv) > 3 else 2500
lf = (ROOT / 'build' / '.fleet_claims.lock').open('a')
lock(lf, exclusive=True)
taken = eligibility.busy_rvas(ROOT) | eligibility.recent_run_rvas(48, ROOT)
latest = eligibility.latest_verdicts()
attempts = eligibility.attempt_counts()

cands = []
for r in eligibility.open_dumps(latest=latest, min_size=min_bytes, max_size=max_bytes):
    rva = r['target_rva'].lower()
    if rva in taken:
        continue
    cands.append((attempts.get(int(rva, 16), 0), -int(r['target_size'] or 0), r['target_rva']))
cands.sort()
picked = [rva for _, _, rva in cands[:n_want]]
if picked:
    with open(ROOT / 'build' / 'fleet_logs' / 'seats.log', 'a') as f:
        f.write(f"{time.strftime('%H:%M')} seat pick selected {' '.join(picked)}\n")
print('\n'.join(picked))
