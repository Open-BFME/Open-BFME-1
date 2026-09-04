#!/usr/bin/env python3
"""Atomically claim the next N unassigned LARGE dump bodies for a big-body seat.
Prints RVAs, one per line.

Window defaults to 1000..2500 bytes: the first hour of 3-6KB picks re-worked
bodies that already carried banked partials (the known walls) and landed 1 of
38. Never-attempted bodies come first, then by size descending; bodies whose
latest attempt is from today are skipped (someone is on it or just gave up).
"""
import csv, sys, time, datetime
from pathlib import Path
sys.path.insert(0, 'tools')
from portable_lock import lock
from fleet_run import active_rvas
from re_log import latest_records
ROOT = Path('.').resolve()
claims = ROOT / 'build' / 'fleet_big_claimed.txt'
n_want = int(sys.argv[1]) if len(sys.argv) > 1 else 2
min_bytes = int(sys.argv[2]) if len(sys.argv) > 2 else 1000
max_bytes = int(sys.argv[3]) if len(sys.argv) > 3 else 2500
lf = (ROOT / 'build' / '.fleet_claims.lock').open('a')
lock(lf, exclusive=True)
taken = set()
if claims.exists():
    taken = {l.strip().lower() for l in claims.read_text().splitlines() if l.strip()}
taken |= active_rvas(ROOT)

latest = {f'0x{rva:08x}': fields for rva, fields in latest_records(ROOT / 'reverse/re_attempts.log').items()}
today = datetime.date.today().isoformat()

def read_rows():
    for _ in range(4):   # a torn read mid-write yields None fields; retry
        try:
            rows = list(csv.DictReader(open(ROOT / 'reverse/functions.csv', newline='', encoding='utf-8', errors='replace')))
            if all(r.get('source') is not None and r.get('target_rva') is not None for r in rows):
                return rows
        except Exception:
            pass
        time.sleep(1)
    return []

cands = []
for r in read_rows():
    if r['source'].endswith('.asm') and r['target_rva'].startswith('0x'):
        sz = int(r['target_size'] or 0)
        rva = r['target_rva'].lower()
        if not (min_bytes <= sz <= max_bytes) or rva in taken:
            continue
        p = latest.get(rva)
        if p and p[0].startswith(today):
            continue
        cands.append((0 if p is None else 1, -sz, r['target_rva']))
cands.sort()
picked = [rva for _, _, rva in cands[:n_want]]
with open(claims, 'a') as f:
    for rva in picked:
        f.write(rva + '\n')
print('\n'.join(picked))
