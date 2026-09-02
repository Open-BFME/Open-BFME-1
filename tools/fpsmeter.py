#!/usr/bin/env python3
"""Read 036-fpsprobe's capture and answer whether the SCREEN got faster.

    python3 tools/fpsmeter.py --preflight run/FpsProbe.jsonl
    python3 tools/fpsmeter.py run/FpsProbe.jsonl
    python3 tools/fpsmeter.py --compare retail.jsonl fixed.jsonl

The probe samples eight consecutive presents every two seconds and hashes a
48-tile grid of the backbuffer at each. Two quantities come out of that, and
they answer different questions:

  present cadence   ms between consecutive presents inside a burst. This is the
                    render loop's rate. It is NOT evidence the game looks
                    smoother -- a build that presents the same image twice
                    doubles this number and changes nothing a player sees.

  duplicate rate    per tile, the fraction of consecutive present pairs whose
                    32x32 hash did not change. This is the quantity that cannot
                    be faked. A tile over a moving unit reads ~0% when the frame
                    it belongs to was really redrawn from a new interpolated
                    pose, and ~50% at 60 Hz when every second frame is a repeat.

Tiles are classified from the data, not from a constant here: the ones that
never change ARE the UI, and which tile holds a moving unit is a property of the
scene, the camera and the resolution rather than something worth hard-coding
into an instrument that would then be run against a scene that had moved.

A capture carrying a `stop` line is refused outright. The probe stops on a
multisampled backbuffer, an unknown pixel format and a mid-capture resolution
change -- each of which would otherwise leave a file that looks like a capture
which simply found no motion.
"""
import argparse
import json
import sys
from pathlib import Path

# A gap longer than this between two samples is a burst boundary or a stall, not
# a frame time. Bursts are two seconds apart by construction, so anything near
# that is the gap between them.
BURST_GAP_MS = 500.0

# What the classifier calls a tile. Deliberately wide apart: a tile between them
# is reported as its own class rather than being rounded into one of these, and
# a stepped tile is exactly the finding this instrument exists to surface.
STATIC_AT = 0.95
LIVE_AT = 0.05


def load(path):
    """One capture: the open record, the frame samples, and any stop."""
    head, frames, stops, torn = None, [], [], 0
    for line in Path(path).read_text().splitlines():
        line = line.strip()
        if not line:
            continue
        try:
            e = json.loads(line)
        except ValueError:
            torn += 1          # a crash is how most captures end
            continue
        ev = e.get("ev")
        if ev == "open":
            head = e
        elif ev == "frame":
            frames.append(e)
        elif ev == "stop":
            stops.append(e)
    return dict(path=str(path), head=head, frames=frames, stops=stops, torn=torn)


def clock(cap):
    """QueryPerformanceCounter -> milliseconds, from the frequency in the file."""
    head = cap["head"]
    freq = head["qfreqlo"] | (head["qfreqhi"] << 32)
    if freq <= 0:
        raise SystemExit(f"{cap['path']}: performance frequency is {freq}")
    for f in cap["frames"]:
        f["t"] = (f["qlo"] | (f["qhi"] << 32)) * 1000.0 / freq
    return freq


def pairs(cap):
    """Consecutive-present pairs inside a burst.

    Both tests matter. `seq` consecutive says the probe wrote the two lines
    back to back; `present` consecutive says the ENGINE presented them back to
    back with nothing in between. Only the second makes a hash comparison mean
    "the next thing the player saw", and they differ exactly when a burst was
    cut short -- which is when the instrument would otherwise invent a duplicate
    across a two-second gap.
    """
    out = []
    for a, b in zip(cap["frames"], cap["frames"][1:]):
        if b["seq"] != a["seq"] + 1 or b["present"] != a["present"] + 1:
            continue
        dt = b["t"] - a["t"]
        if dt < 0 or dt > BURST_GAP_MS:
            continue
        out.append((a, b, dt))
    return out


def pct(values, q):
    if not values:
        raise SystemExit("percentile of nothing")
    s = sorted(values)
    return s[min(len(s) - 1, int(q / 100.0 * len(s)))]


LIVE_MIN = 0.90


def live_fraction(cap):
    """Share of sampled presents taken while a match was actually running.

    A capture whose match ended partway still yields a present interval and a
    tile duplicate rate, and both look entirely reasonable, because the menu
    presents at a steady rate and its pixels are static. Every rate computed
    below is meaningless unless this is near 1.0, so nothing may read one
    without checking this first.
    """
    frames = cap["frames"]
    if not frames:
        return 0.0
    return sum(1 for f in frames if f["live"] == 1) / len(frames)


def require_live(caps):
    """Refuse to report on a capture whose match was not up throughout."""
    dead = [(Path(c["path"]).name, live_fraction(c)) for c in caps
            if live_fraction(c) < LIVE_MIN]
    if dead:
        raise SystemExit(
            "match was not running for these captures, so no rate below them "
            "means anything:\n"
            + "\n".join(f"  {n}: {f:.0%} of samples in-match "
                         f"(need {LIVE_MIN:.0%})" for n, f in dead)
            + "\nre-run the capture; do not interpret a partial match.")


def logic_rate(cap):
    """Logic frames per wall second, over the whole capture.

    The game-speed gate. Measured across bursts rather than inside one, because
    at 5 Hz a two-second burst spans one logic frame and the slope over the
    whole file is the only estimate with any samples in it.
    """
    live = [f for f in cap["frames"] if f["live"] == 1 and f["f"] >= 0]
    if len(live) < 2:
        return None
    first, last = live[0], live[-1]
    span_s = (last["t"] - first["t"]) / 1000.0
    frames = last["f"] - first["f"]
    if span_s <= 0 or frames <= 0:
        return None
    return frames / span_s


def anim_rate(cap):
    """Animation milliseconds per real millisecond.

    WW3D::SyncTime is what every W3D animation plays against, and it advances
    by a fixed 33 ms per client frame with no wall-clock term -- so this slope
    is animation speed, and 1.0 is real time. It is the one thing here the cell
    hashes cannot see: an animation running at double speed still changes on
    the same fraction of presented frames.
    """
    live = [f for f in cap["frames"] if f.get("anim") is not None]
    if len(live) < 2:
        return None
    first, last = live[0], live[-1]
    span = last["t"] - first["t"]
    # The clock is a 32-bit accumulator; a capture that spans its wrap would
    # read negative rather than quietly reporting a small positive slope.
    delta = last["anim"] - first["anim"]
    if span <= 0 or delta < 0:
        return None
    return delta / span


def tiles(cap):
    """Per-tile duplicate rate over consecutive-present pairs."""
    ps = pairs(cap)
    if not ps:
        raise SystemExit(f"{cap['path']}: no consecutive-present pairs to compare")
    n = len(ps[0][0]["tiles"])
    same = [0] * n
    for a, b, _ in ps:
        if len(a["tiles"]) != n or len(b["tiles"]) != n:
            raise SystemExit(f"{cap['path']}: sample {a['seq']} has "
                             f"{len(a['tiles'])} tiles, not {n}")
        for i in range(n):
            if a["tiles"][i] == b["tiles"][i]:
                same[i] += 1
    return [c / len(ps) for c in same], len(ps)


def distinct_rate(rates, present_hz):
    """New images per second, per cell: (1 - duplicate rate) x present rate.

    This is the quantity "60 FPS" ought to mean, and it is not the present
    rate. A build that presents twice as often while repeating every second
    frame doubles the present rate and leaves this alone; a build that
    simulates twice as often at the same present rate raises this without
    touching the present rate at all. Only a change that puts more DIFFERENT
    images on the screen per second moves it.

    Reported over cells rather than as one number because the screen does not
    have one rate: retail's camera redraws every present and its units advance
    with the simulation, and a single average hides which of the two a change
    moved.
    """
    return [(1.0 - r) * present_hz for r in rates]


def classify(rates):
    static = [i for i, r in enumerate(rates) if r >= STATIC_AT]
    livet = [i for i, r in enumerate(rates) if r <= LIVE_AT]
    stepped = [i for i, r in enumerate(rates) if LIVE_AT < r < STATIC_AT]
    return static, livet, stepped


def activity(cap):
    """Cells that changed, per consecutive-present pair, in order.

    The raw shape behind every duplicate rate. One number per pair rather than
    one per capture, which is what makes a walk visible as an interval."""
    return [(b["seq"], b["t"], sum(1 for x, y in zip(a["tiles"], b["tiles"]) if x != y))
            for a, b, _ in pairs(cap)]


def walk_duration(cap, marks):
    """How long the world kept moving after the move order.

    The game-speed measurement, and the only one here that a doubled simulation
    cannot pass. The network frame rate is not that measurement and cannot be:
    it is paced by the network at 5 Hz in both arms, so a build that advances
    the world twice as far per network frame reads a reassuring 5.0/s while
    running at double speed.

    Measured on the cells that were STATIC during this capture's own still
    phase, not on a threshold over how many cells changed. The first version
    took the still phase's p90 changed-cell count as "quiet" and reported the
    driven seat's walk as 0.00 s: that seat's still phase already had thirty-odd
    cells changing every frame -- the palantir ring animates continuously -- so
    a handful of units crossing open ground never cleared the bar. Cells that
    did not change at all while nothing was happening have a baseline of zero
    by construction, and a unit walking through one is unambiguous.
    """
    clock(cap)
    still = window(cap, *marks["still"])
    still_rates, _ = tiles(still)
    static = [i for i, r in enumerate(still_rates) if r >= STATIC_AT]
    if not static:
        raise SystemExit("no cell held still while nothing was happening; "
                         "there is no baseline to measure a walk against")

    order = marks["order_at"]
    acts = []
    for a, b, _ in pairs(window(cap, order, marks["walk"][1])):
        moved = sum(1 for i in static if a["tiles"][i] != b["tiles"][i])
        acts.append((b["seq"], b["t"], moved))
    if not acts:
        raise SystemExit("no pairs after the move order")

    t0 = acts[0][1]
    # More than one, so a single cell flickering at the edge of the shroud is
    # not a walk. The LAST busy pair rather than the first quiet one: a walk
    # crosses cells unevenly and a quiet pair mid-walk is a unit passing behind
    # scenery.
    busy = [(seq, t) for seq, t, moved in acts if moved > 1]
    return dict(static_cells=len(static), samples=len(acts), busy=len(busy),
                seconds=(busy[-1][1] - t0) / 1000.0 if busy else 0.0,
                peak=max(m for _, _, m in acts))


def preflight(caps):
    """Refuse a capture that cannot answer the question, and say which one."""
    bad = 0
    for cap in caps:
        problems = []
        if cap["head"] is None:
            problems.append("no open record: the probe never reached a present")
        for s in cap["stops"]:
            problems.append(f"probe stopped: {s['why']} (hr={s['hr']:#x})"
                            if s["hr"] else f"probe stopped: {s['why']}")
        if not cap["frames"]:
            problems.append("no frame samples")
        elif cap["head"] is not None:
            clock(cap)
            if not pairs(cap):
                problems.append("no consecutive-present pairs: every burst was cut short")
        if problems:
            bad = 1
            print(f"REFUSED {cap['path']}")
            for p in problems:
                print(f"  {p}")
        else:
            print(f"ok      {cap['path']}: {len(cap['frames'])} samples, "
                  f"{len(pairs(cap))} pairs, {cap['torn']} torn line(s)")
    return bad


def window(cap, lo, hi):
    """A copy of the capture holding only samples with lo <= seq < hi."""
    kept = dict(cap)
    kept["frames"] = [f for f in cap["frames"] if lo <= f["seq"] < hi]
    return kept


def report(cap, title=None):
    clock(cap)
    head = cap["head"]
    ps = pairs(cap)
    dts = [dt for _, _, dt in ps]
    rates, npairs = tiles(cap)
    static, livet, stepped = classify(rates)
    cols, rows = head["cols"], head["rows"]

    print(f"== {title or cap['path']}")
    print(f"   {head['w']}x{head['h']} fmt {head['fmt']} bpp {head['bpp']}, "
          f"{cols}x{rows} cells of {head['cellw']}x{head['cellh']}px, "
          f"{len(cap['frames'])} samples in {npairs + 1} bursts-worth")
    print()
    print(f"   present interval  median {pct(dts, 50):6.2f} ms  "
          f"p90 {pct(dts, 90):6.2f}  p99 {pct(dts, 99):6.2f}"
          f"   ({1000.0 / pct(dts, 50):.1f} Hz median)")
    phases = sorted({f["phase"] for f in cap["frames"] if f["phase"] >= 0})
    if phases:
        # The engine's own record of the sub-step cycle, so a build claiming to
        # have doubled it has to show twelve values here and not six.
        steps = max(phases)
        print(f"   sub-step cycle    1..{steps}"
              f"   ({len(phases)} distinct values seen: "
              f"{phases if len(phases) <= 14 else str(phases[:14]) + '...'})")
    rate = logic_rate(cap)
    if rate is None:
        print("   logic rate        no in-match samples: this capture is menu only")
    else:
        print(f"   logic rate        {rate:.3f} network frames/s  "
              f"({1000.0 / rate:.1f} ms per network frame)")
        if phases:
            print(f"   simulation rate   {rate * max(phases):.1f} sub-steps/s"
                  f"   ({max(phases)} per network frame)")
    print()
    hz = 1000.0 / pct(dts, 50)
    fresh = sorted(distinct_rate(rates, hz), reverse=True)
    # The engine's own headroom. `idle` is only meaningful where `limited` is
    # set: the no-limit path stores a literal zero into it, so a zero there
    # means the limiter did not run, not that the budget was exhausted.
    limited = [f for f in cap["frames"] if f.get("limited")]
    if limited:
        work = sorted(f["work"] for f in limited)
        idle = sorted(f["idle"] for f in limited)
        starved = sum(1 for f in limited if f["idle"] == 0)
        print(f"   headroom          work p50 {work[len(work)//2]} ms  "
              f"p90 {work[int(len(work)*0.9)]} ms   "
              f"idle p50 {idle[len(idle)//2]} ms  p10 {idle[len(idle)//10]} ms")
        print(f"                     {starved}/{len(limited)} limited frames had "
              f"NO budget left ({100.0*starved/len(limited):.0f}%)")
    elif cap["frames"]:
        print("   headroom          the frame limiter never ran in this window")

    slope = anim_rate(cap)
    if slope is not None:
        print(f"   animation clock   {slope:.3f} animation-ms per real-ms"
              f"   ({slope:.2f}x real time)")

    bad = [f["seq"] for f in cap["frames"] if f["desync"]]
    if bad:
        print(f"   *** DESYNC *** the engine's own flag raised from sample "
              f"{bad[0]}; nothing below is a measurement of a working build")
    print(f"   new images/s      fastest cell {fresh[0]:5.1f}   "
          f"top decile {fresh[len(fresh) // 10]:5.1f}   median {fresh[len(fresh) // 2]:5.1f}")
    print("                     (what 60 FPS ought to mean: a repeated frame "
          "does not count)")
    print()
    print(f"   tiles  {len(livet):2d} live (<={LIVE_AT:.0%} duplicate)   "
          f"{len(stepped):2d} stepped   {len(static):2d} static (>={STATIC_AT:.0%})")
    print()
    print("   duplicate rate per tile, screen layout:")
    for r in range(rows):
        row = "".join(f"{rates[r * cols + c] * 100:6.0f}" for c in range(cols))
        print(f"     {row}")
    if stepped:
        print()
        print("   STEPPED tiles are the finding: something in them changed on")
        print("   some presents and not others.")
        for i in sorted(stepped, key=lambda i: rates[i]):
            print(f"     tile {i:2d} (col {i % cols}, row {i // cols}): "
                  f"{rates[i] * 100:.0f}% duplicate")
    return 0


def compare(caps):
    """Two arms side by side, on the quantities the gates are written on."""
    rows = []
    require_live(caps)
    for cap in caps:
        clock(cap)
        dts = [dt for _, _, dt in pairs(cap)]
        rates, npairs = tiles(cap)
        _, livet, _ = classify(rates)
        rows.append(dict(path=Path(cap["path"]).name, med=pct(dts, 50),
                         p99=pct(dts, 99), logic=logic_rate(cap),
                         live=len(livet), pairs=npairs, rates=rates))
    w = max(len(r["path"]) for r in rows)
    print(f"{'capture':<{w}}  {'present med':>11}  {'p99':>7}  "
          f"{'Hz':>6}  {'logic/s':>8}  {'live tiles':>10}")
    for r in rows:
        logic = f"{r['logic']:>8.3f}" if r["logic"] is not None else "       -"
        print(f"{r['path']:<{w}}  {r['med']:>8.2f} ms  {r['p99']:>5.2f}  "
              f"{1000.0 / r['med']:>6.1f}  {logic}  {r['live']:>10d}")
    print()
    base = rows[0]
    for r in rows[1:]:
        speed = (r["logic"] / base["logic"]
                 if base["logic"] and r["logic"] else None)
        print(f"{r['path']} vs {base['path']}:")
        print(f"  render  {base['med'] / r['med']:.2f}x more presents per second")
        if speed is not None:
            verdict = "UNCHANGED" if abs(speed - 1.0) <= 0.01 else "*** MOVED ***"
            print(f"  game speed  {speed:.3f}x  {verdict}")
        print(f"  live tiles  {base['live']} -> {r['live']}")
    return 0


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("files", nargs="+")
    ap.add_argument("--preflight", action="store_true",
                    help="check the captures are usable and say why not")
    ap.add_argument("--compare", action="store_true",
                    help="two or more arms side by side")
    ap.add_argument("--walk", metavar="PHASES.JSON",
                    help="how long the world kept moving after the move order, "
                         "which is the game-speed gate the logic rate cannot be")
    ap.add_argument("--phases", metavar="PHASES.JSON",
                    help="report each phase of a run separately, using the "
                         "sample indices the runner recorded while capturing")
    a = ap.parse_args()
    caps = [load(p) for p in a.files]
    if a.preflight:
        return preflight(caps)
    for cap in caps:
        if cap["head"] is None or cap["stops"] or not cap["frames"]:
            raise SystemExit(f"{cap['path']} is not usable; run --preflight for why")
    if a.compare:
        return compare(caps)
    if a.walk:
        marks = json.loads(Path(a.walk).read_text())
        for cap in caps:
            w = walk_duration(cap, marks)
            name = Path(cap["path"]).name
            print(f"{name}: {w['static_cells']} cells were static while nothing "
                  f"was happening; after the order {w['busy']}/{w['samples']} "
                  f"pairs disturbed more than one of them (peak {w['peak']}), "
                  f"the last {w['seconds']:.2f}s in")
        return 0
    if a.phases:
        marks = json.loads(Path(a.phases).read_text())
        # The runner records scalars beside the phase windows (the sample index
        # a move order went out at, the pid it throttled). Only the [lo, hi]
        # pairs are phases.
        windows = {k: v for k, v in marks.items()
                   if isinstance(v, list) and len(v) == 2
                   and all(isinstance(x, int) for x in v)}
        for cap in caps:
            clock(cap)
            for name, (lo, hi) in windows.items():
                sub = window(cap, lo, hi)
                if len(sub["frames"]) < 2:
                    print(f"== {Path(cap['path']).name} / {name}: "
                          f"{len(sub['frames'])} samples, nothing to compare\n")
                    continue
                report(sub, f"{Path(cap['path']).name} / {name}  "
                            f"(samples {lo}..{hi})")
                print()
        return 0
    for cap in caps:
        report(cap)
    return 0


if __name__ == "__main__":
    sys.exit(main())
