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

records = re_log.latest_records()
attempts = eligibility.attempt_counts()
unlocked = eligibility.unlocked_rvas()


def blocked(rva):
    a = int(rva, 16)
    # 5+ verdicts: 1-2% land rate per session (2026-09-17); see pick_anon
    if attempts.get(a, 0) >= eligibility.ATTEMPT_CAP and a not in unlocked:
        return True
    return eligibility.retired(a, latest) or eligibility.boundary_suspect(a, records)

# Score the BODIES, not the file's address span. A catch-all dump file
# (Code/gen_small/dumps_000.cpp holds bodies from 0x005ADC10 to 0x009B58F0)
# spans every landed row in the image, so span/len scored it 492 against ~1
# for a real file and it won every pick: three unrelated bodies, no shared
# neighbourhood. eligibility.neighbour_density asks each body how many of its
# 12 nearest ledger rows are landed C++ (50% land rate at >= 0.75, 7% below 0.25).
density = eligibility.neighbour_density(rows)
WINDOW = 0x8000          # bodies served together must be close enough to share context
best = None
for f, rvas in files.items():
    mids = [a for a in rvas if min_b <= size[a] <= max_b and a not in taken and not blocked(a)]
    if len(mids) < n_want:
        continue
    mids.sort(key=lambda a: int(a, 16))
    for i in range(len(mids) - n_want + 1):
        group = mids[i:i + n_want]
        if int(group[-1], 16) - int(group[0], 16) > WINDOW:
            continue
        shares = [density(int(a, 16)) or 0.0 for a in group]
        # expected landed bytes of the group: size x measured land rate
        score = sum(size[a] * eligibility.neighbour_prior(d) for a, d in zip(group, shares))
        if best is None or score > best[0]:
            # largest first: land rate is flat across 300-2,500 B, bytes are not
            best = (score, f, sorted(group, key=lambda a: -size[a]))
if not best:
    sys.exit(0)
picked = best[2][:n_want]
if not dry:
    with open(ROOT / 'build' / 'fleet_logs' / 'seats.log', 'a') as h:
        h.write(f"{time.strftime('%H:%M')} seat pick -> {' '.join(picked)}\n")
print('\n'.join(picked))
if dry:
    print(f'# file {best[1]} expected landed bytes {best[0]:.0f}; neighbours landed: '
          + ' '.join(f"{density(int(a, 16)) or 0:.2f}" for a in picked), file=sys.stderr)
