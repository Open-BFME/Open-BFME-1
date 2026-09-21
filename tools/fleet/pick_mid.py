#!/usr/bin/env python3
"""Claim N mid-size dump bodies (default 300..2500 B, largest first) from ONE dump file whose
address neighbourhood already holds landed real C++.

Why: the file lane briefs smallest-first, so 2,167 bodies / 1.13 MB in the
300-1000 B band are rarely reached, while the 1000-2500 B lane landed 3 in 21
sessions. Mid bodies carry ~5x the bytes of a file-lane landing, and the land
rate more than doubles when siblings in the same file are already C++ (their
class layout, pins and callees are worked out). A file is scored by landed
real-C++ rows inside its address range per remaining dump body.

  python tools/fleet/pick_mid.py [N] [min_bytes] [max_bytes] [--dry]
Prints RVAs one per line. A pick is marked in build/fleet_logs/seats.log under
the fleet claims lock until the seat logs "done"; leases and the 48 h touched
cooldown (tools/eligibility.py) replace the old append-only claim file."""
import csv, re, sys, time
from pathlib import Path
sys.path.insert(0, 'tools')
from portable_lock import lock
import eligibility
import re_log
ROOT = Path('.').resolve()
args = [a for a in sys.argv[1:] if not a.startswith('--')]
dry = '--dry' in sys.argv
n_want = int(args[0]) if len(args) > 0 else 3
min_b = int(args[1]) if len(args) > 1 else 300
max_b = int(args[2]) if len(args) > 2 else 2500
lf = (ROOT / 'build' / '.fleet_claims.lock').open('a')
lock(lf, exclusive=True)
# live leases and seats, plus anything a run touched in the last 48 h; the
# append-only claim file is no longer read (it starved the lane for ever)
taken = eligibility.busy_rvas(ROOT) | eligibility.recent_run_rvas(48, ROOT)
latest = eligibility.latest_verdicts()
rows = eligibility.load_rows()

landed = []          # rvas of real C++ rows
files = {}           # dump file -> [rvas of remaining dump rows]
size = {}
for r in rows:
    rva = r['target_rva'].lower()
    if not rva.startswith('0x'):
        continue
    src = r['source']
    if eligibility.is_dump_row(r):
        files.setdefault(src, []).append(rva)
        size[rva] = int(r['target_size'] or 0)
    elif r.get('status') == 'matched' and not src.startswith('Code/gen_'):
        landed.append(int(rva, 16))
landed.sort()
import bisect

records = re_log.latest_records()
attempts = eligibility.attempt_counts()
unlocked = eligibility.unlocked_rvas()


def blocked(rva):
    a = int(rva, 16)
    # 5+ verdicts: 1-2% land rate per session (2026-09-17); see pick_anon
    if attempts.get(a, 0) >= eligibility.ATTEMPT_CAP and a not in unlocked:
        return True
    return eligibility.retired(a, latest) or eligibility.boundary_suspect(a, records)

best = None
for f, rvas in files.items():
    mids = [a for a in rvas if min_b <= size[a] <= max_b and a not in taken and not blocked(a)]
    if len(mids) < n_want:
        continue
    lo = min(int(a, 16) for a in rvas); hi = max(int(a, 16) for a in rvas)
    n_landed = bisect.bisect_right(landed, hi) - bisect.bisect_left(landed, lo)
    score = n_landed / max(len(rvas), 1)
    if best is None or score > best[0]:
        # largest first: land rate is flat across 300-2,500 B, bytes are not
        best = (score, f, sorted(mids, key=lambda a: -size[a]))
if not best:
    sys.exit(0)
picked = best[2][:n_want]
if not dry:
    with open(ROOT / 'build' / 'fleet_logs' / 'seats.log', 'a') as h:
        h.write(f"{time.strftime('%H:%M')} seat pick -> {' '.join(picked)}\n")
print('\n'.join(picked))
if dry:
    print(f'# file {best[1]} landed-neighbour score {best[0]:.2f}', file=sys.stderr)
