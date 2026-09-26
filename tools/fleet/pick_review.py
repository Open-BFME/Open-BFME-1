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


def prepare(lo, hi, root=ROOT):
    """Rank the whole current review pool without holding the picker lock."""
    latest = eligibility.latest_verdicts(root / "targets/game/reverse/re_attempts.log")
    busy = eligibility.busy_rvas(root)
    recent = eligibility.recent_run_rvas(48, root)
    rows = eligibility.load_rows(root / "targets/game/reverse/functions.csv")
    cands = []
    for row, path, score in eligibility.finish_bodies(lo, rows=rows, latest=latest):
        rva = eligibility.rva_of(row)
        key = f"0x{rva:08x}"
        if score >= hi or key in busy or key in recent:
            continue
        if not eligibility.deferred(rva, latest):
            continue
        cands.append((score, int(row.get("target_size") or 0), row["target_rva"]))
    cands.sort(reverse=True)
    return cands


def finalize(prepared, n_want, lo, hi, root=ROOT, dry=False):
    """Recheck a bounded shortlist before returning an advisory selection."""
    if not prepared or n_want <= 0:
        return []
    shortlist = prepared[:max(32, n_want)]
    wanted = {int(c[2], 16) for c in shortlist}
    with (root / "build/.fleet_claims.lock").open("a+b") as handle:
        lock(handle, exclusive=True)
        rows = eligibility.load_rows(root / "targets/game/reverse/functions.csv", rvas=wanted)
        latest = eligibility.latest_verdicts(root / "targets/game/reverse/re_attempts.log")
        live_sizes = {row["target_rva"].lower(): int(row.get("target_size") or 0)
                      for row, path, score in eligibility.finish_bodies(
                    lo, rows=rows, latest=latest)
                      if score < hi and eligibility.deferred(eligibility.rva_of(row), latest)}
        taken = eligibility.busy_rvas(root) | eligibility.recent_run_rvas(48, root)
        picked = [rva for _, size, rva in shortlist
                  if live_sizes.get(rva.lower()) == size
                  and rva.lower() not in taken][:n_want]
        if picked and not dry:
            with (root / "build/fleet_logs/seats.log").open("a", encoding="utf-8") as fh:
                fh.write(f"{time.strftime('%H:%M')} seat pick selected {' '.join(picked)}\n")
    return picked


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    dry = "--dry" in sys.argv
    n_want = int(args[0]) if len(args) > 0 else 2
    lo = float(args[1]) if len(args) > 1 else 0.5
    hi = float(args[2]) if len(args) > 2 else 0.95
    print("\n".join(finalize(prepare(lo, hi), n_want, lo, hi, dry=dry)))


if __name__ == "__main__":
    main()
