#!/usr/bin/env python3
"""Claim N mid-size dump bodies (default 300..1000 B) from ONE dump file whose
address neighbourhood already holds landed real C++.

Why: the file lane briefs smallest-first, so 2,167 bodies / 1.13 MB in the
300-1000 B band are rarely reached, while the 1000-2500 B lane landed 3 in 21
sessions. Mid bodies carry ~5x the bytes of a file-lane landing, and the land
rate more than doubles when siblings in the same file are already C++ (their
class layout, pins and callees are worked out). A file is scored by landed
real-C++ rows inside its address range per remaining dump body.

  python build/pick_mid.py [N] [min_bytes] [max_bytes] [--dry]
Prints RVAs one per line; claims go to build/fleet_mid_claimed.txt under the
fleet claims lock (same pattern as pick_big.py)."""
import csv, re, sys, time
from pathlib import Path
sys.path.insert(0, 'tools')
from portable_lock import lock
from fleet_run import active_rvas
from re_log import latest_records, DEAD_END_STATUSES
ROOT = Path('.').resolve()
args = [a for a in sys.argv[1:] if not a.startswith('--')]
dry = '--dry' in sys.argv
n_want = int(args[0]) if len(args) > 0 else 3
min_b = int(args[1]) if len(args) > 1 else 300
max_b = int(args[2]) if len(args) > 2 else 1000
claims = ROOT / 'build' / 'fleet_mid_claimed.txt'
lf = (ROOT / 'build' / '.fleet_claims.lock').open('a')
lock(lf, exclusive=True)
taken = {l.strip().lower() for l in claims.read_text().splitlines() if l.strip()} if claims.exists() else set()
taken |= active_rvas(ROOT)

latest = {f'0x{rva:08x}': fields for rva, fields in latest_records(ROOT / 'reverse/re_attempts.log').items()}

rows = []
for _ in range(4):
    try:
        rows = list(csv.DictReader(open(ROOT / 'reverse/functions.csv', newline='', encoding='utf-8', errors='replace')))
        if all(r.get('source') is not None and r.get('target_rva') is not None for r in rows):
            break
    except Exception:
        pass
    time.sleep(1)

landed = []          # rvas of real C++ rows
files = {}           # dump file -> [rvas of remaining dump rows]
size = {}
for r in rows:
    rva = r['target_rva'].lower()
    if not rva.startswith('0x'):
        continue
    src = r['source']
    if src.endswith('.asm'):
        files.setdefault(src, []).append(rva)
        size[rva] = int(r['target_size'] or 0)
    elif r.get('status') == 'matched' and not src.startswith('Code/gen_'):
        landed.append(int(rva, 16))
landed.sort()
import bisect

def blocked(rva):
    record = latest.get(rva)
    return bool(record and record[3] in DEAD_END_STATUSES)

best = None
for f, rvas in files.items():
    mids = [a for a in rvas if min_b <= size[a] <= max_b and a not in taken and not blocked(a)]
    if len(mids) < n_want:
        continue
    lo = min(int(a, 16) for a in rvas); hi = max(int(a, 16) for a in rvas)
    n_landed = bisect.bisect_right(landed, hi) - bisect.bisect_left(landed, lo)
    score = n_landed / max(len(rvas), 1)
    if best is None or score > best[0]:
        best = (score, f, sorted(mids, key=lambda a: size[a]))
if not best:
    sys.exit(0)
picked = best[2][:n_want]
if not dry:
    with open(claims, 'a') as h:
        for a in picked:
            h.write(a + '\n')
print('\n'.join(picked))
if dry:
    print(f'# file {best[1]} landed-neighbour score {best[0]:.2f}', file=sys.stderr)
