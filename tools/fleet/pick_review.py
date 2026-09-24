#!/usr/bin/env python3
"""Pick banked anonymous-lane bodies for a REVIEWER seat.

Workers produce a candidate body plus evidence; a reviewer checks the
assumptions the byte gate cannot see (function identity, class layout,
calling convention, callee names), repairs promising candidates, and
redirects stalled ones. Trial arrangement per the 2026-09-15 consensus:
measure landed bytes per reviewer-hour before expanding it.

Serves: dump addresses whose banked stash scores in [--min, --max) (default
0.5..0.95), latest verdict a deferral, not busy, not reviewed in the last 48 h.
Highest score first. Prints RVAs one per line.

  python tools/fleet/pick_review.py [N] [min] [max] [--dry]
"""
import sys
import time
from pathlib import Path

sys.path.insert(0, "tools")
from portable_lock import lock  # noqa: E402
import eligibility  # noqa: E402

ROOT = Path(".").resolve()
args = [a for a in sys.argv[1:] if not a.startswith("--")]
dry = "--dry" in sys.argv
n_want = int(args[0]) if len(args) > 0 else 2
lo = float(args[1]) if len(args) > 1 else 0.5
hi = float(args[2]) if len(args) > 2 else 0.95
seats_log = ROOT / "build" / "fleet_logs" / "seats.log"
lf = (ROOT / "build" / ".fleet_claims.lock").open("a")
lock(lf, exclusive=True)

latest = eligibility.latest_verdicts()
busy = eligibility.busy_rvas(ROOT)
recent = eligibility.recent_run_rvas(48, ROOT)
cands = []
for row, path, score in eligibility.finish_bodies(lo, latest=latest):
    rva = eligibility.rva_of(row)
    key = f"0x{rva:08x}"
    if score >= hi or key in busy or key in recent:
        continue
    if not eligibility.deferred(rva, latest):
        continue
    cands.append((score, int(row.get("target_size") or 0), row["target_rva"]))
cands.sort(reverse=True)
picked = [rva for _, _, rva in cands[:n_want]]
if picked and not dry:
    with open(seats_log, "a", encoding="utf-8") as fh:
        fh.write(f"{time.strftime('%H:%M')} seat pick selected {' '.join(picked)}\n")
print("\n".join(picked))
