#!/usr/bin/env python3
"""Claim N anonymous dump bodies for the anonymous lane, warmest evidence first.

97% of the remaining dump bytes are anonymous `?d_` bodies, and 69% of the
17,029 blocked verdicts of 2026-09-08..12 said "cannot establish identity".
Most of that was the evidence pack not seeing through ILT thunks (callers
reached 3 of 60 sampled bodies; 38 of 60 after the fix). This picker ranks by
what the pack can now prove -- callers, string literals, a vtable install or
slot, a witnessed layout, landed neighbours -- so a seat starts on a body with
a lead, not a blob. Prior attempts count against a body only when the pack
still has nothing new to say about it.

  python build/pick_anon.py [N] [min_bytes] [max_bytes] [--dry]
Prints RVAs one per line; the pick is recorded in seats.log ('seat pick ->')
so a concurrent picker sees it busy. The durable claim is fleet_run's lease.
"""
import re
import sys
import time
from pathlib import Path

sys.path.insert(0, "tools")
sys.path.insert(0, "tools/fleet")
from portable_lock import lock  # noqa: E402
import eligibility  # noqa: E402

ROOT = Path(".").resolve()
args = [a for a in sys.argv[1:] if not a.startswith("--")]
dry = "--dry" in sys.argv
n_want = int(args[0]) if len(args) > 0 else 2
min_b = int(args[1]) if len(args) > 1 else 300
max_b = int(args[2]) if len(args) > 2 else 2500
seats_log = ROOT / "build" / "fleet_logs" / "seats.log"
lf = (ROOT / "build" / ".fleet_claims.lock").open("a")
lock(lf, exclusive=True)

latest = eligibility.latest_verdicts()
rows = eligibility.open_dumps(latest=latest, min_size=min_b, max_size=max_b, anonymous=True)
busy = eligibility.busy_rvas(ROOT) | eligibility.recent_run_rvas(48, ROOT)
attempts = eligibility.attempt_counts()
# reverse/unlocked.txt: a session already landed the shim/pins this body's
# family shares; the pack now proves its callees, so serve it first.
unlocked = eligibility.unlocked_rvas()

import context_pack  # noqa: E402  (loads the image once, ~20 s cold)


def warmth(rva):
    lines = context_pack.pack(rva)
    text = "\n".join(lines)
    callers = re.search(r"callers \((\d+) sites", text)
    n_callers = int(callers.group(1)) if callers else 0
    score = 0
    score += 3 if "  strings:" in text else 0
    score += 2 if ("vtable slot:" in text or "installs vtable" in text) else 0
    score += 2 * min(n_callers, 3)
    score += 1 if "BFME layout" in text else 0
    score += 1 if "landed neighbours:" in text else 0
    score += 4 if (rva if isinstance(rva, int) else int(rva, 16)) in unlocked else 0
    return score


cands = []
for row in rows:
    rva = eligibility.rva_of(row)
    key = f"0x{rva:08x}"
    if key in busy:
        continue
    w = warmth(rva)
    tried = attempts.get(rva, 0)
    # evidence beats history: a body with no lead after two tries waits;
    # a body with a lead is served however often blind sessions bounced off it
    if w == 0 and tried >= 2:
        continue
    cands.append((w, int(row.get("target_size") or 0), row["target_rva"]))
cands.sort(reverse=True)
picked = [rva for _, _, rva in cands[:n_want]]
if picked and not dry:
    with open(seats_log, "a", encoding="utf-8") as fh:
        fh.write(f"{time.strftime('%H:%M')} seat pick -> {' '.join(picked)}\n")
print("\n".join(picked))
if dry:
    for w, sz, rva in cands[:n_want]:
        print(f"# {rva} {sz}B warmth={w} attempts={attempts.get(int(rva, 16), 0)}", file=sys.stderr)
