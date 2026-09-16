#!/usr/bin/env python3
"""Claim near-landed bodies: dump rows with a banked stash scoring
>= --min-score (default 0.9). Args: N MIN_SCORE MAX_ATTEMPTS COOLDOWN_DAYS. 228 such bodies (40KB) sat in the queue on
2026-09-03 while seats started fresh files; a session that begins from a 0.9+
stash is usually one lever from landing.

Reads the stash on disk, not only the log's LATEST verdict: a `blocked` row
recorded after the bank hid 234 of 381 servable bodies on 2026-09-15. Only a
dead-end verdict (no-match, refuted, ...) retires the address, as in re_log.
Prints N RVAs (largest first), one per line. Claims live in seats.log via the
'seat pick ->' marker, same as pick_file.py.
"""
import sys, time
from pathlib import Path
sys.path.insert(0, 'tools')
from portable_lock import lock
import eligibility
ROOT = Path('.').resolve()
seats_log = ROOT / 'build' / 'fleet_logs' / 'seats.log'
n_want = int(sys.argv[1]) if len(sys.argv) > 1 else 2
min_score = float(sys.argv[2]) if len(sys.argv) > 2 else 0.9
# 2026-09-16: 550 of the last 800 verdict rows were sixth-or-later passes on
# the same near misses. Cap attempts and honour the stash date (cross-host);
# 0 disables either, which is how the lunaxhigh lane asks for the hard set.
max_attempts = int(sys.argv[3]) if len(sys.argv) > 3 else 5
cooldown_days = int(sys.argv[4]) if len(sys.argv) > 4 else 2
lf = (ROOT / 'build' / '.fleet_claims.lock').open('a')
lock(lf, exclusive=True)

# busy = live lease or a seat currently on it; a body a finish session just
# left waits 48 h (immutable run records) instead of being claimed for ever
claimed = eligibility.busy_rvas(ROOT) | eligibility.recent_run_rvas(48, ROOT)
# best-first: score, then bytes. The remaining work is the distance from the
# stash, so a 0.99 body of 60 B outranks a 0.90 body of 900 B.
cands = [(score, int(r.get('target_size') or 0), r['target_rva'])
         for r, _, score in eligibility.finish_bodies(
             min_score, max_attempts=max_attempts, cooldown_days=cooldown_days)
         if r['target_rva'].lower() not in claimed]
cands.sort(reverse=True)
picked = [rva for _, _, rva in cands[:n_want]]
if picked:
    with open(seats_log, 'a') as f:
        f.write(f"{time.strftime('%H:%M')} seat pick -> {' '.join(picked)}\n")
print('\n'.join(picked))
