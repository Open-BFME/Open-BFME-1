#!/usr/bin/env python3
"""Claim near-landed bodies: dump rows whose latest banked partial scored
>= --min-score (default 0.9) and has a stash. 228 such bodies (40KB) sat in
the queue on 2026-09-03 while seats started fresh files; a session that
begins from a 0.9+ stash is usually one lever from landing.
Prints N RVAs (largest first), one per line. Claims live in seats.log via the
'seat pick ->' marker, same as pick_file.py.
"""
import csv, re, sys, time
from pathlib import Path
sys.path.insert(0, 'tools')
from portable_lock import lock
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
for cf in ('fleet_big_claimed.txt', 'fleet_fin_claimed.txt'):
    p = ROOT / 'build' / cf
    if p.exists():
        claimed |= {l.strip().lower() for l in p.read_text().splitlines() if l.strip()}
# one finish session per body: a seat re-picking the body it just failed on
# (still 0.9+, no longer busy) was observed; record every pick permanently
fin_claims = ROOT / 'build' / 'fleet_fin_claimed.txt'

latest = {}
for l in open(ROOT / 'reverse/re_attempts.log', encoding='utf-8', errors='replace'):
    p = l.rstrip('\n').split('\t')
    if len(p) >= 5 and p[1].startswith('0x'):
        latest[p[1].lower()] = p

cands = []
for r in csv.DictReader(open(ROOT / 'reverse/functions.csv', newline='', encoding='utf-8', errors='replace')):
    rva = (r.get('target_rva') or '').lower()
    if not rva or not (r.get('source') or '').endswith('.asm'):
        continue
    p = latest.get(rva)
    if not p or p[3] != 'partial' or 'stash=' not in p[4]:
        continue
    m = re.search(r'score=([0-9.]+)', p[4])
    if not m or float(m.group(1)) < min_score:
        continue
    if busy.get(rva) or rva in claimed:
        continue
    cands.append((int(r.get('target_size') or 0), r['target_rva']))
cands.sort(reverse=True)
picked = [rva for _, rva in cands[:n_want]]
with open(seats_log, 'a') as f, open(fin_claims, 'a') as c:
    for rva in picked:
        f.write(f"{time.strftime('%H:%M')} seat pick -> {rva}\n")
        c.write(rva + '\n')
print('\n'.join(picked))
