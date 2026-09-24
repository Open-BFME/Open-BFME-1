#!/usr/bin/env python3
"""Claim near-landed bodies: dump rows with a banked stash scoring
>= --min-score (default 0.9). Args: N MIN_SCORE MAX_ATTEMPTS COOLDOWN_DAYS. 228 such bodies (40KB) sat in the queue on
2026-09-03 while seats started fresh files; a session that begins from a 0.9+
stash is usually one lever from landing.

Reads the stash on disk, not only the log's LATEST verdict: a `blocked` row
recorded after the bank hid 234 of 381 servable bodies on 2026-09-15. Only a
dead-end verdict (no-match, refuted, ...) retires the address, as in re_log.
Prints N selected RVAs, one per line. Selection is advisory; fleet_run claims
only actual brief targets before launch.
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
# best-first on what the COMPILER says about the stash (tools/finish_measure.py):
# the header score is an author estimate and runs optimistic. Up to 8 unmeasured
# stashes are measured per pick (~2 s each, cached by stash body), best author
# score first, so the cache fills in a few picks; FINISH_MEASURE=0 skips that.
import os
import finish_measure
cands = [(score, int(r.get('target_size') or 0), r['target_rva'], path)
         for r, path, score in eligibility.finish_bodies(
             min_score, max_attempts=max_attempts, cooldown_days=cooldown_days)
         if r['target_rva'].lower() not in claimed]
cands.sort(key=lambda c: (-c[0], -c[1]))
measured = finish_measure.ensure([(int(c[2], 16), c[3]) for c in cands],
                                 budget=int(os.environ.get('FINISH_MEASURE', '8')))
cands.sort(key=lambda c: finish_measure.rank_key(measured, int(c[2], 16), c[3], c[0], c[1]))
picked = [c[2] for c in cands[:n_want]]
if picked:
    with open(seats_log, 'a') as f:
        f.write(f"{time.strftime('%H:%M')} seat pick selected {' '.join(picked)}\n")
print('\n'.join(picked))
