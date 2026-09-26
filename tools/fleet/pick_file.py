#!/usr/bin/env python3
"""Select the next dump file for a fleet seat. Prints its path.

A file is busy while a live run owns one of its bodies, or while an old
unreconciled seat log assigns its stem. Finished sessions leave most bodies unconverted (a session
lands ~5 of 25), so the old append-only claim list starved the fleet once every
big file had been touched once. Order: landed-neighbour density first (see below), then remaining dump bytes,
at least argv[1] briefable dump bodies (default 6) no larger than argv[2]
(default 2500 bytes).
"""
import collections, sys, time
from pathlib import Path
sys.path.insert(0, 'tools')
from portable_lock import lock
from fleet_run import active_rvas
import eligibility
ROOT = Path('.').resolve()
seats_log = ROOT / 'build' / 'fleet_logs' / 'seats.log'
lf = (ROOT / 'build' / '.fleet_claims.lock').open('a')
lock(lf, exclusive=True)

busy_stems = {token for token in eligibility.legacy_busy_tokens(ROOT, seats_log)
              if not token.startswith('0x')}
active = active_rvas(ROOT)

minb = int(sys.argv[1]) if len(sys.argv) > 1 else 6
maxb = int(sys.argv[2]) if len(sys.argv) > 2 else 2500
rows = eligibility.load_rows(ROOT / 'targets/game/reverse/functions.csv')
latest = eligibility.latest_verdicts(ROOT / 'targets/game/reverse/re_attempts.log')
# Count the bodies the following brief can actually include.  A dead-end or
# oversized row must not make a file look full, and aliases count only once.
live_by_file = collections.defaultdict(dict)
asm_rows = [row for row in rows if (row.get('source') or '').endswith('.asm')]
for row in eligibility.open_dumps(rows=asm_rows, latest=latest, max_size=maxb):
    source = row['source']
    rva = eligibility.rva_of(row)
    if rva is not None:
        live_by_file[source][rva] = int(row.get('target_size') or 0)
b = {source: sum(sizes.values()) for source, sizes in live_by_file.items()}
n = {source: len(sizes) for source, sizes in live_by_file.items()}
lo = {source: min(sizes) for source, sizes in live_by_file.items()}
hi = {source: max(sizes) for source, sizes in live_by_file.items()}
landed = []
for row in rows:
    source = row.get('source') or ''
    rva = eligibility.rva_of(row)
    if rva is None:
        continue
    if source.endswith('.asm'):
        # Keep the file exclusive even if its owned row was since retired.
        if f'0x{rva:08x}' in active:
            busy_stems.add(Path(source).stem)
    elif row.get('status') == 'matched' and not source.startswith('game/gen_'):
        landed.append(rva)
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
    # Selection is advisory; fleet_run atomically claims actual brief RVAs.
    with open(seats_log, 'a') as f:
        f.write(f"{time.strftime('%H:%M')} seat pick selected {stem}\n")
    print(s)
    break
