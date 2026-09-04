#!/usr/bin/env python3
"""Atomically pick the next dump file for a fleet seat. Prints its path.

A file is busy only while a seat is CURRENTLY on it (seats.log: last event for
the stem is '->'). Finished sessions leave most bodies unconverted (a session
lands ~5 of 25), so the old append-only claim list starved the fleet once every
big file had been touched once. Order: landed-neighbour density first (see below), then remaining dump bytes,
at least argv[1] remaining dump bodies (default 6).
"""
import csv, collections, re, sys, time
from pathlib import Path
sys.path.insert(0, 'tools')
from portable_lock import lock
ROOT = Path('.').resolve()
seats_log = ROOT / 'build' / 'fleet_logs' / 'seats.log'
lf = (ROOT / 'build' / '.fleet_claims.lock').open('a')
lock(lf, exclusive=True)

busy = {}
if seats_log.exists():
    for l in seats_log.read_text(encoding='utf-8', errors='replace').splitlines():
        m = re.match(r'\S+ seat (\S+) (->|done) (\S+)', l)
        if m:
            busy[m.group(3)] = (m.group(2) == '->', m.group(1))
busy_stems = {stem for stem, (on, _) in busy.items() if on}
# sessions older than 3h with no 'done' are dead seats, not busy (log has only HH:MM; be lenient)

minb = int(sys.argv[1]) if len(sys.argv) > 1 else 6
b = collections.Counter(); n = collections.Counter()
for _ in range(4):
    try:
        rows = list(csv.DictReader(open(ROOT / 'reverse/functions.csv', newline='', encoding='utf-8', errors='replace')))
        if all(r.get('source') is not None for r in rows):
            break
    except Exception:
        rows = []
    time.sleep(1)
lo = {}; hi = {}; landed = []
for r in rows:
    s = r.get('source') or ''
    rva = r.get('target_rva') or ''
    if not rva.startswith('0x'):
        continue
    if s.endswith('.asm'):
        b[s] += int(r.get('target_size') or 0); n[s] += 1
        a = int(rva, 16); lo[s] = min(lo.get(s, a), a); hi[s] = max(hi.get(s, a), a)
    elif r.get('status') == 'matched' and not s.startswith('Code/gen_'):
        landed.append(int(rva, 16))
# Order by landed-neighbour density: real C++ rows inside the file's address
# range per remaining dump body. Measured land rate is 19.5% for a body whose
# file has no landed siblings and 46.5% with ten or more (AGENTS.md), so the
# fleet should drain files whose layouts and pins are already proven before
# opening cold ones. Remaining bytes break ties.
import bisect
landed.sort()
def density(s):
    return (bisect.bisect_right(landed, hi[s]) - bisect.bisect_left(landed, lo[s])) / max(n[s], 1)
ordered = sorted(b, key=lambda s: (-density(s), -b[s]))
for s in ordered:
    by = b[s]
    stem = Path(s).stem
    if stem in busy_stems or n[s] < minb:
        continue
    # claim: write the assignment marker the seat script would write, so two
    # seats picking within the same second cannot both take it
    with open(seats_log, 'a') as f:
        f.write(f"{time.strftime('%H:%M')} seat pick -> {stem}\n")
    print(s)
    break
