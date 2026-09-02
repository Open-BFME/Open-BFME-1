#!/usr/bin/env python3
"""Is the motion SMOOTH, or just frequent?

New images per second says how much changes; it says nothing about whether the
changes arrive evenly. Two builds with identical new-image rates look completely
different if one delivers its frames on a steady cadence and the other bunches
them, and the second is what a player calls stutter. That distinction is the one
gap every other instrument here shares, and it is what let 037-fps60 report green
everywhere while visibly running a spell animation at double speed.

Two quantities, both from consecutive presents inside a burst:

PACING  -- the spread of present intervals. A steady 38 Hz reads better than a
mean 76 Hz delivered as alternating 5 ms and 21 ms gaps, because the eye tracks
the long gap, not the average. Reported as p99/p50: 1.0 is metronomic, and
anything past ~2 is a visible hitch.

HEALTH -- whether the machine is keeping up at all. Present rate is the WRONG
thing to watch for this: starve a client to a quarter core and it only halves,
38 -> 19 or 77 -> 39, which reads as survivable. The simulation clocks collapse
by ten times over the same interval -- network 5.0 -> 0.52/s, animation 0.99 ->
0.10 -- because the frame limiter gives up rendering long before the engine gives
up simulating. Retail does this identically (0.521 against 0.532), so it is the
game's own failure mode and not a cost of raising the limit, but it is what a
weak machine actually does and in lockstep it stalls every peer.

STALENESS -- how long the same picture persists, in runs of consecutive
identical frames, over the cells that actually change. Doubling the present rate
while repeating each image twice leaves the picture exactly as stale as before
and shows up here as unchanged run lengths, which is the failure that matters
for units and the one a present-rate counter cannot see.
"""
import argparse, json, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent))
import fpsmeter


# Below this fraction of retail's animation rate the machine is not keeping up.
# Chosen well clear of both regimes: healthy captures read 0.984-1.009 and
# starved ones 0.104-0.105, so anything in between is a machine in trouble and
# there is no honest reading near the line.
STRUGGLING_AT = 0.80


def bursts(cap):
    """Consecutive presents grouped into the runs the probe actually captured."""
    out, cur = [], []
    for a, b, _ in fpsmeter.pairs(cap):
        if cur and cur[-1] is not a:
            out.append(cur)
            cur = []
        cur.append(a)
        cur.append(b)
        cur = cur[:1] + [x for i, x in enumerate(cur[1:]) if x is not cur[i]]
    if cur:
        out.append(cur)
    return [b for b in out if len(b) >= 3]


def staleness(cap, cells):
    """Mean run of consecutive identical frames, over the given cells."""
    runs = []
    for burst in bursts(cap):
        for i in cells:
            run = 1
            for a, b in zip(burst, burst[1:]):
                if a["tiles"][i] == b["tiles"][i]:
                    run += 1
                else:
                    runs.append(run)
                    run = 1
            runs.append(run)
    return (sum(runs) / len(runs)) if runs else float("nan")


def report(run, phase):
    d = Path("build/fps") / run
    cap = fpsmeter.load(str(d / "P1.jsonl"))
    fpsmeter.clock(cap)
    marks = json.loads((d / "phases.json").read_text())
    if phase not in marks:
        return None
    sub = fpsmeter.window(cap, *marks[phase])
    if fpsmeter.live_fraction(sub) < fpsmeter.LIVE_MIN:
        return None
    dts = [dt for _, _, dt in fpsmeter.pairs(sub)]
    if len(dts) < 10:
        return None
    p50, p99 = fpsmeter.pct(dts, 50), fpsmeter.pct(dts, 99)
    rates = fpsmeter.tiles(sub)[0]
    # The cells that change at all; a screen of static terrain has nothing to
    # say about smoothness and would drown the ones that do.
    active = [i for i, r in enumerate(rates) if r < 0.9]
    anim = fpsmeter.anim_rate(sub)
    return dict(hz=1000.0 / p50, p50=p50, p99=p99, jitter=p99 / p50,
                active=len(active), stale=staleness(sub, active),
                stale_ms=staleness(sub, active) * p50,
                net=fpsmeter.logic_rate(sub), anim=anim,
                struggling=(None if anim is None else anim < STRUGGLING_AT))


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("runs", nargs="+")
    ap.add_argument("--phase", default="walk")
    args = ap.parse_args()

    print(f"{'run':<14}{'present':>8} {'jitter':>7} {'stale ms':>9} "
          f"{'net/s':>7} {'anim':>7}  health")
    for run in args.runs:
        r = report(run, args.phase)
        if r is None:
            print(f"{run:<14}  no usable in-match samples in phase {args.phase!r}")
            continue
        # No animation clock, no verdict. A capture predating that probe field
        # cannot answer this, and saying "keeping up" for it would be inventing
        # evidence -- the one reading nobody would think to check.
        health = {None: "UNKNOWN (capture has no animation clock)",
                  True: "*** STRUGGLING ***",
                  False: "keeping up"}[r["struggling"]]
        if r["jitter"] > 2.0:
            health += f"  (uneven pacing: p99 {r['p99']:.0f}ms)"
        print(f"{run:<14}{r['hz']:>7.1f}H {r['jitter']:>7.2f} {r['stale_ms']:>9.1f} "
              f"{r['net'] or float('nan'):>7.3f} {r['anim'] or float('nan'):>7.3f}  {health}")
    print("\njitter 1.0 = metronomic; >2 = a visible hitch.")
    print("stale ms = how long one picture persists on the cells that change; "
          "lower is smoother, and it is what the present rate cannot tell you.")
    print(f"health = animation clock against retail; below {STRUGGLING_AT:.2f} the "
          "machine is not keeping up.\n  Watch this and NOT the present rate: "
          "starvation halves the present rate and divides this by ten.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
