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

  python tools/fleet/pick_anon.py [N] [min_bytes] [max_bytes] [--dry]
Prints RVAs one per line; the pick is diagnostic only. The durable claim is
fleet_run's atomic lease on the filtered brief targets.
"""
import re
import sys
import time
from pathlib import Path

sys.path.insert(0, "tools")
sys.path.insert(0, "tools/fleet")
from portable_lock import lock  # noqa: E402
import eligibility  # noqa: E402
import re_log  # noqa: E402
import context_pack  # noqa: E402  (loads the image once, ~20 s cold)

ROOT = Path(".").resolve()


def warmth(rva, unlocked):
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
    # a Zero Hour function of the same shape: a class to test and a source to start from
    score += 3 if "ZH fuzzy twin (strong" in text else 2 if "ZH fuzzy twin (plausible" in text else 0
    score += 4 if (rva if isinstance(rva, int) else int(rva, 16)) in unlocked else 0
    return score


def prepare(min_b, max_b, root=ROOT):
    """Build and score the whole pool without monopolizing the claim lock."""
    latest = eligibility.latest_verdicts(root / "targets/game/reverse/re_attempts.log")
    ledger_rows = eligibility.load_rows(root / "targets/game/reverse/functions.csv")
    rows = eligibility.open_dumps(
        rows=ledger_rows, latest=latest,
        min_size=min_b, max_size=max_b, anonymous=True, include_carved=True,
        carved_path=root / "targets/game/reverse/carved.csv")
    busy = eligibility.busy_rvas(root) | eligibility.recent_run_rvas(48, root)
    attempts = eligibility.attempt_counts(root / "targets/game/reverse/re_attempts.log")
    records = re_log.latest_records(root / "targets/game/reverse/re_attempts.log")
    # An unlocked shared prerequisite adds a new lead to the evidence pack.
    unlocked = eligibility.unlocked_rvas(root / "targets/game/reverse/unlocked.txt")
    density = eligibility.neighbour_density(rows=ledger_rows)
    cands = []
    for row in rows:
        rva = eligibility.rva_of(row)
        if f"0x{rva:08x}" in busy:
            continue
        w = warmth(rva, unlocked)
        tried = attempts.get(rva, 0)
        # Evidence beats history, but an unchanged blind third pass waits.
        if w == 0 and tried >= 2:
            continue
        if tried >= eligibility.ATTEMPT_CAP and rva not in unlocked:
            continue
        if eligibility.boundary_suspect(rva, records):
            continue
        cands.append((w, int(row.get("target_size") or 0), row["target_rva"],
                      density(rva), w - (4 if rva in unlocked else 0)))
    # Expected bytes uses evidence warmth, size, and landed neighbours.
    cands.sort(key=lambda t: eligibility.expected_bytes(t[0], t[1], t[3]), reverse=True)
    return cands, attempts


def finalize(prepared, n_want, min_b, max_b, root=ROOT, dry=False):
    """Recheck selected work, including carved overlaps, under the picker lock."""
    if not prepared or n_want <= 0:
        return []
    shortlist = prepared[:max(32, n_want)]
    wanted = {int(c[2], 16) for c in shortlist}
    with (root / "build/.fleet_claims.lock").open("a+b") as handle:
        lock(handle, exclusive=True)
        latest = eligibility.latest_verdicts(root / "targets/game/reverse/re_attempts.log")
        # Carved rows must be checked against EVERY current claimed range, not
        # only the shortlist, or a newly landed overlap could be resurrected.
        live = {eligibility.rva_of(row): row for row in eligibility.open_dumps(
            rows=eligibility.load_rows(root / "targets/game/reverse/functions.csv"), latest=latest,
            min_size=min_b, max_size=max_b, anonymous=True, include_carved=True,
            carved_path=root / "targets/game/reverse/carved.csv")
            if eligibility.rva_of(row) in wanted}
        taken = eligibility.busy_rvas(root) | eligibility.recent_run_rvas(48, root)
        attempts = eligibility.attempt_counts(root / "targets/game/reverse/re_attempts.log")
        unlocked = eligibility.unlocked_rvas(root / "targets/game/reverse/unlocked.txt")
        records = re_log.latest_records(root / "targets/game/reverse/re_attempts.log")
        valid = []
        for c in shortlist:
            rva = int(c[2], 16)
            row = live.get(rva)
            if (row is None or int(row.get("target_size") or 0) != c[1]
                    or c[2].lower() in taken):
                continue
            tried = attempts.get(rva, 0)
            # The evidence score was prepared earlier. If an unlock was
            # removed meanwhile, its four bonus points cannot authorize an
            # unchanged third blind attempt.
            if (c[4] == 0 and rva not in unlocked and tried >= 2) or (
                    tried >= eligibility.ATTEMPT_CAP and rva not in unlocked):
                continue
            if eligibility.boundary_suspect(rva, records):
                continue
            valid.append(c)
        picked = [c[2] for c in valid[:n_want]]
        if picked and not dry:
            with (root / "build/fleet_logs/seats.log").open("a", encoding="utf-8") as log:
                log.write(f"{time.strftime('%H:%M')} seat pick selected {' '.join(picked)}\n")
    return picked


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    dry = "--dry" in sys.argv
    n_want = int(args[0]) if len(args) > 0 else 2
    min_b = int(args[1]) if len(args) > 1 else 300
    max_b = int(args[2]) if len(args) > 2 else 2500
    cands, attempts = prepare(min_b, max_b)
    picked = finalize(cands, n_want, min_b, max_b, dry=dry)
    print("\n".join(picked))
    if dry:
        by_rva = {c[2]: c for c in cands}
        for rva in picked:
            w, sz, _, d, _ = by_rva[rva]
            print(f"# {rva} {sz}B warmth={w} neighbours_landed={'?' if d is None else format(d, '.2f')} attempts={attempts.get(int(rva, 16), 0)}", file=sys.stderr)


if __name__ == "__main__":
    main()
