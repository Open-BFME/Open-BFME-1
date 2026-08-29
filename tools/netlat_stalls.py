#!/usr/bin/env python3
"""How much of a match a guest spends frozen, and how long each freeze lasts.

    python3 tools/netlat_stalls.py --baseline build/netlat/s7base1 ... \
                                   --fix build/netlat/s7retry1 ...

BFME is lockstep: a command that does not arrive stops every seat, not just the
one that lost it. `Connection::init` sets m_retryTime to 2000, so an unacked
command waits two seconds before it is put in a packet again, and that wait is
the freeze. Under 40 ms delay and 1% loss the guest stall histogram piles up at
exactly 2.0 s -- which is the claim this file exists to test.

The median latency is NOT the quantity here and is deliberately not reported.
A shorter retry timer does not move it: the same commands bind to the same
frames. What it should move is the tail -- how long a freeze lasts once one
starts -- so the headline is the histogram, and the summary numbers are
normalised per minute so matches of different lengths can be pooled.

Three things are excluded or guarded rather than averaged in:

  * the match-start gap. Every capture has exactly one multi-second gap at the
    first frame, on BOTH seats, and it is loading, not the network. Measured at
    11-23 s, and it varies between runs for reasons unrelated to the arm -- one
    pair here differed by 12 s, enough to move a per-minute rate by 5% on its
    own -- so it is excluded from the numerator AND the denominator.
  * the router, from the headline. It is NOT immune -- at 40 ms/1% it takes
    roughly a quarter as many freezes as the guest -- but it takes them for a
    different reason and in a different shape, so pooling the seats would blur
    the quantity the fix is aimed at. Its count is printed alongside instead of
    dropped, because a change that helped the guest by hurting the router would
    otherwise be invisible here.
  * desync and game speed, which are gates rather than results.
"""
import argparse
import sys
from collections import Counter
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from netlat import load, logic_rate, pct  # noqa: E402

# A frame gap longer than this missed at least one 200 ms logic frame. Below it
# is jitter in when the frame event fired, not the game stopping.
STALL_MS = float(__import__('os').environ.get('BFME_STALL_MS', 400.0))
BUCKET_MS = 500.0


def stalls(seat):
    """Every freeze in one seat's capture, in ms, match-start excluded."""
    frames = [e["t"] for e in seat["events"] if e["ev"] == "frame"]
    if len(frames) < 2:
        raise SystemExit(f"{seat['path']}: {len(frames)} frame events -- this "
                         f"capture has no match in it to measure.")
    gaps = [(b - a, n) for n, (a, b) in enumerate(zip(frames, frames[1:]))]
    # The first gap is the load. Dropped by POSITION, not by size: dropping the
    # largest gap would also discard the genuine multi-second freezes this whole
    # file exists to count, and the result would look like a fix that removed
    # them.
    body = [g for g, n in gaps if n > 0]
    return [g for g in body if g > STALL_MS], sum(body) / 60000.0


def summarise(run):
    seats = [load(p) for p in sorted(Path(run).glob("*.jsonl"))]
    for s in seats:
        s["router"] = bool(s["events"][0]["router"])
    guests = [s for s in seats if not s["router"]]
    if not guests:
        raise SystemExit(f"{run}: no guest seat; the freezes are one-sided and "
                         f"there is nothing here to measure.")
    guest = guests[0]
    router = next((x for x in seats if x["router"]), None)
    router_lost = len(stalls(router)[0]) if router is not None else -1
    lost, minutes = stalls(guest)
    if minutes <= 0:
        raise SystemExit(f"{run}: the capture spans no time.")

    rate, _, frames = logic_rate(guest)
    # Threshold-free: over the played body, how much wall time did the guest
    # spend beyond the 200 ms per frame it owed? No choice of stall threshold
    # can bias this, so it is the row to trust when the histogram and the rates
    # appear to disagree.
    body_gaps = [b["t"] - a["t"] for a, b in zip(frames, frames[1:])][1:]
    body_span = sum(body_gaps) / 1000.0
    behind = body_span - len(body_gaps) * 0.2
    overall = len(body_gaps) / body_span if body_span else 0.0

    desync = max((e.get("desync", 0) for s in seats for e in s["events"]
                  if e["ev"] == "frame"), default=0)
    return dict(run=Path(run).name, lost=lost, minutes=minutes, overall=overall,
                router_lost=router_lost, behind=behind,
                behind_pct=behind / body_span * 100.0 if body_span else 0.0,
                per_min=len(lost) / minutes,
                secs_per_min=sum(lost) / 1000.0 / minutes,
                share=sum(lost) / (minutes * 60000.0) * 100.0,
                p50=pct(lost, 50), p90=pct(lost, 90),
                worst=max(lost) if lost else 0.0,
                rate=rate, desync=desync)


def histogram(runs, width=44):
    counts = Counter(round(g / BUCKET_MS) * BUCKET_MS / 1000.0
                     for r in runs for g in r["lost"])
    if not counts:
        print("      (no freezes at all)")
        return
    top = max(counts.values())
    for k in sorted(counts):
        print(f"      {k:5.1f}s  {'#' * max(1, round(counts[k] / top * width))} {counts[k]}")


# Two different quantities a reader will otherwise read as one. A guest that
# freezes for 2 s and then runs frames back-to-back to catch up has spent real
# wall time frozen (what a player sees) and yet may have lost almost no game
# time by the end (what the simulation sees). Both are reported, named so they
# cannot be swapped.
ROWS = [("NET game time lost (after catch-up)", "behind_pct", "%", 2),
        ("WALL time spent inside a freeze", "share", "%", 1),
        ("freezes per minute", "per_min", "", 2),
        ("seconds frozen per minute", "secs_per_min", "s", 2),
        ("freeze length p50", "p50", "ms", 0),
        ("freeze length p90", "p90", "ms", 0),
        ("worst freeze", "worst", "ms", 0)]


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--baseline", nargs="+", required=True, metavar="DIR")
    ap.add_argument("--fix", nargs="+", required=True, metavar="DIR")
    ap.add_argument("--label", default="retry400")
    a = ap.parse_args()

    arms = {"retail+earlysend": [summarise(r) for r in a.baseline],
            a.label: [summarise(r) for r in a.fix]}
    for name, runs in arms.items():
        print(f"\n=== {name}: {len(runs)} matches ===")
        for r in runs:
            print(f"    {r['run']:<12s} {r['minutes']:4.1f} min  "
                  f"{len(r['lost']):3d} freezes  {sum(r['lost'])/1000:5.1f}s frozen  "
                  f"(router {r['router_lost']:2d})  "
                  f"rate {r['overall']:.3f}/s overall, {r['rate']:.3f}/s between"
                  + ("  DESYNC" if r["desync"] else ""))
        print("    freeze lengths:")
        histogram(runs)

    b, f = arms["retail+earlysend"], arms[a.label]
    print(f"\n{'':36s} {'retail+earlysend':>20s} {a.label:>20s} {'change':>10s}")
    for label, key, unit, dp in ROWS:
        bv = [r[key] for r in b]
        fv = [r[key] for r in f]
        bm, fm = pct(bv, 50), pct(fv, 50)
        print(f"{label:36s} {bm:10.{dp}f}{unit} [{min(bv):.{dp}f}-{max(bv):.{dp}f}]"
              f"{fm:10.{dp}f}{unit} [{min(fv):.{dp}f}-{max(fv):.{dp}f}]"
              f"{fm - bm:+10.{dp}f}")

    over = [r["overall"] for runs in arms.values() for r in runs]
    # The gate is "not slower than the baseline arm", NOT "equals 5.000".
    # Retail itself does not reach 5 on a bad link -- measured at 4.575 frames
    # per wall second at 150ms round trip with 3% loss -- because the freezes it
    # suffers are not fully recovered by catch-up. Gating on 5.000 would fail
    # every arm at that condition including the baseline, and gating on "above
    # baseline is a violation" would report the fix recovering lost game time as
    # if it were speeding the game up.
    bm = pct([r["overall"] for r in b], 50)
    fm = pct([r["overall"] for r in f], 50)
    print(f"\ngame speed   baseline {bm:.3f} vs {a.label} {fm:.3f} frames/wall-second")
    if fm > 5.01:
        print("             *** RUNS FAST -- above nominal 5 Hz is a different game")
    elif fm < bm - 0.01:
        print("             *** SLOWER THAN BASELINE")
    else:
        print("             OK -- at or above baseline, never above nominal 5")
    bad = [r["run"] for runs in arms.values() for r in runs if r["desync"]]
    print("desync       " + ("NONE in any match" if not bad else f"*** {bad}"))

    # A freeze COUNT is only meaningful when the threshold is well below both
    # arms' freeze lengths. A retransmit-timer fix produces freezes just above
    # its own timer, so a threshold anywhere near that value counts some and
    # discards others and the ratio becomes a property of the threshold rather
    # than of the fix. Measured on one real pair: the same two arms give a count
    # ratio of 1.53x at a 300 ms threshold, 2.34x at 400 ms, and 24x at 700 ms.
    # The reader cannot see that from a single number, so the tool says it.
    near = [(name, pct([r["p50"] for r in runs], 50))
            for name, runs in arms.items()
            if pct([r["p50"] for r in runs], 50) < STALL_MS * 2]
    if near:
        print(f"\nthreshold    *** COUNT ROWS ARE NOT TRUSTWORTHY HERE")
        for name, p50 in near:
            print(f"             {name}'s freeze p50 is {p50:.0f}ms against a "
                  f"{STALL_MS:.0f}ms threshold")
        print("             Freezes near the threshold are counted or dropped "
              "arbitrarily.\n"
              "             Use 'NET game time lost', which no threshold can bias, "
              "or re-run\n"
              "             with a threshold well below both arms' freeze lengths.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
