#!/usr/bin/env python3
"""Claim near-landed bodies: dump rows with a banked stash scoring
>= --min-score (default 0.9). 228 such bodies (40KB) sat in the queue on
2026-09-03 while seats started fresh files; a session that begins from a 0.9+
stash is usually one lever from landing.

Reads the stash on disk, not only the log's LATEST verdict: a `blocked` row
recorded after the bank hid 234 of 381 servable bodies on 2026-09-15. Only a
dead-end verdict (no-match, refuted, ...) retires the address, as in re_log.
Prints N RVAs (largest first), one per line. Claims live in seats.log via the
'seat pick ->' marker, same as pick_file.py.
"""
import csv, re, sys, time
from pathlib import Path
sys.path.insert(0, 'tools')
from portable_lock import lock
from fleet_run import active_rvas
from re_log import latest_records, stash_for, DEAD_END_STATUSES
import build
ROOT = Path('.').resolve()
seats_log = ROOT / 'build' / 'fleet_logs' / 'seats.log'
n_want = int(sys.argv[1]) if len(sys.argv) > 1 else 2
min_score = float(sys.argv[2]) if len(sys.argv) > 2 else 0.9
lf = (ROOT / 'build' / '.fleet_claims.lock').open('a')
lock(lf, exclusive=True)

busy = {}
if seats_log.exists():
    for l in seats_log.read_text(encoding='utf-8', errors='replace').splitlines():
        m = re.match(r'\S+ seat (\S+) (->|done) (\S+)', l)
        if m:
            busy[m.group(3).lower()] = (m.group(2) == '->')
claimed = set()
claimed |= active_rvas(ROOT)
for cf in ('fleet_big_claimed.txt', 'fleet_fin_claimed.txt'):
    p = ROOT / 'build' / cf
    if p.exists():
        claimed |= {l.strip().lower() for l in p.read_text().splitlines() if l.strip()}
# one finish session per body: a seat re-picking the body it just failed on
# (still 0.9+, no longer busy) was observed; record every pick permanently
fin_claims = ROOT / 'build' / 'fleet_fin_claimed.txt'

latest = {f'0x{rva:08x}': fields[3] for rva, fields in latest_records(ROOT / 'reverse/re_attempts.log').items()}

cands = []
for r in csv.DictReader(open(ROOT / 'reverse/functions.csv', newline='', encoding='utf-8', errors='replace')):
    rva = (r.get('target_rva') or '').lower()
    src = r.get('source') or ''
    if not rva or r.get('status') != 'matched':
        continue
    if not (build.is_scaffold_row(r) or src.endswith(('.asm', '.s'))):
        continue                      # already real source: nothing to finish
    if latest.get(rva) in DEAD_END_STATUSES:
        continue                      # boundary refuted after the bank
    found = stash_for(int(rva, 16))
    if not found or found[1] < min_score:
        continue
    if busy.get(rva) or rva in claimed:
        continue
    # best-first: score, then bytes. The remaining work is the distance from
    # the stash, so a 0.99 body of 60 B outranks a 0.90 body of 900 B.
    cands.append((found[1], int(r.get('target_size') or 0), r['target_rva']))
cands.sort(reverse=True)
picked = [rva for _, _, rva in cands[:n_want]]
with open(seats_log, 'a') as f, open(fin_claims, 'a') as c:
    for rva in picked:
        f.write(f"{time.strftime('%H:%M')} seat pick -> {rva}\n")
        c.write(rva + '\n')
print('\n'.join(picked))
