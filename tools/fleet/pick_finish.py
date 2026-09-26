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
import os
import sys
import time
from pathlib import Path
sys.path.insert(0, 'tools')
from portable_lock import lock
import eligibility
import finish_measure
ROOT = Path('.').resolve()


def finalize(prepared, measured, n_want, min_score, max_attempts,
             cooldown_days, root=ROOT):
    """Recheck a bounded shortlist under the picker lock before advisory output.

    The runner's atomic brief-target claim is still the launch authority.
    Losing a race here or there costs one brief, never duplicate execution.
    """
    if not prepared or n_want <= 0:
        return []
    shortlist = finish_measure.select(prepared, measured, max(32, n_want))
    wanted = {int(c[2], 16) for c in shortlist}
    with (root / 'build/.fleet_claims.lock').open('a+b') as handle:
        lock(handle, exclusive=True)
        rows = eligibility.load_rows(root / 'targets/game/reverse/functions.csv', rvas=wanted)
        latest = eligibility.latest_verdicts(root / 'targets/game/reverse/re_attempts.log')
        counts = eligibility.attempt_counts(root / 'targets/game/reverse/re_attempts.log') if max_attempts else {}
        live = {r['target_rva'].lower(): (score, int(r.get('target_size') or 0),
                                          r['target_rva'], path)
                for r, path, score in eligibility.finish_bodies(
                    min_score, rows=rows, latest=latest, max_attempts=max_attempts,
                    counts=counts, cooldown_days=cooldown_days)}
        taken = eligibility.busy_rvas(root) | eligibility.recent_run_rvas(48, root)
        valid = [live[c[2].lower()] for c in shortlist
                 if c[2].lower() in live and c[2].lower() not in taken
                 and live[c[2].lower()][1] == c[1]]
        picked = [c[2] for c in finish_measure.select(valid, measured, n_want)]
        if picked:
            with (root / 'build/fleet_logs/seats.log').open('a', encoding='utf-8') as log:
                log.write(f"{time.strftime('%H:%M')} seat pick selected {' '.join(picked)}\n")
    return picked


def main():
    n_want = int(sys.argv[1]) if len(sys.argv) > 1 else 2
    min_score = float(sys.argv[2]) if len(sys.argv) > 2 else 0.9
    # 2026-09-16: 550 of the last 800 verdict rows were sixth-or-later passes
    # on the same near misses. 0 disables the cap or cooldown for lunaxhigh.
    max_attempts = int(sys.argv[3]) if len(sys.argv) > 3 else 5
    cooldown_days = int(sys.argv[4]) if len(sys.argv) > 4 else 2
    taken = eligibility.busy_rvas(ROOT) | eligibility.recent_run_rvas(48, ROOT)
    cands = [(score, int(r.get('target_size') or 0), r['target_rva'], path)
             for r, path, score in eligibility.finish_bodies(
                 min_score, max_attempts=max_attempts, cooldown_days=cooldown_days)
             if r['target_rva'].lower() not in taken]
    cands.sort(key=lambda c: (-c[0], -c[1]))
    # Compiler probes and full-pool ranking happen outside the shared lock.
    measured = finish_measure.ensure([(int(c[2], 16), c[3]) for c in cands],
                                     budget=int(os.environ.get('FINISH_MEASURE', '8')))
    print('\n'.join(finalize(cands, measured, n_want, min_score, max_attempts,
                             cooldown_days)))


if __name__ == '__main__':
    main()
