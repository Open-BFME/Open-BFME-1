#!/usr/bin/env python3
"""Why a guest holds a logic frame it is already allowed to run.

    python3 tools/netlat_admit.py build/netlat/admit2/*.jsonl

A guest runs frame N one 200 ms quantum after the host does. The released-frame
test in getFrameAdvanceCount is `ceiling - frame + 1 > 0`, which already admits
frame N the moment the ceiling reaches N, and its single caller uses the return
value as a boolean -- exactly one logic frame runs per call. So the ceiling is
not what holds a guest back.

What the captures showed instead: the guest calls that driver ONCE per logic
frame (poll gap p50 198.1 ms) while the router calls it 2.5 times per frame.
The guest is handed permission, spends it in 0.2 ms, and does not ask again for
a whole quantum.

  polls       calls to the driver per logic frame. Also a FREEZE PROXY, which is
              not obvious and is worth knowing before comparing arms: a frozen
              guest keeps calling the driver and keeps being declined, so the
              rate rises with time spent frozen and not with any feature.
              Measured on one build with only the condition changing --
              clean LAN 1.00, 80ms/1% 1.61-1.72, and 80ms/1% with the retransmit
              timer shortened back to 1.05.

              DO NOT EXTRAPOLATE IT. At 150ms/3% a controlled pair showed a 5.9x
              poll ratio against a 1.13x freeze ratio, so whatever drives polling
              there is not freeze time and this calibration does not reach it.
              Inverting the 80ms fit onto that pair returns "262% of wall time
              frozen", which is the kind of impossible answer that should stop a
              reader rather than be reported.

              The deeper reason to keep this hook out of any freeze comparison is
              not that it differs across arms -- it is a thermometer that HEATS
              WHAT IT MEASURES. More freezing means more polls, more polls means
              more flushed lines in the hot path, and more logging in the hot
              path means more freezing. An arm that freezes more pays a
              compounding instrument cost the other arm does not.

              It is also the root cause of the one-frame lag, so it leads;
              everything below is downstream of it.
  gate        how often the readiness test said no, split by WHICH side of its
              comparison was wrong -- expected == -1 is "no authoritative count
              delivered yet", expected > received is "delivered, commands
              missing". These want opposite fixes.
  hold        t(ran N) - t(the first tick that said frame N was complete). Near
              zero means there is no slack to reclaim at the gate itself.
  prize       t(ran N) - t(the first tick at which the guest, sitting on N-1,
              could already see N was complete).

A WARNING about `prize`, learned the hard way: acting on it desyncs. 034-framedrain
forced the extra pass this number appears to justify and produced 26 desync
events from frame 102. areFrameCommandsComplete compares a count that is a
SNAPSHOT and can still grow, so a frame it calls complete is not necessarily
settled. Retail is safe because a guest is asked only once per quantum. Treat
`prize` as a description of the protocol's margin, not as an opportunity.
"""
import argparse
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from netlat import load, pct  # noqa: E402

NO_COUNT = -1     # the sentinel for "this frame has no authoritative total yet"


def admits(seat):
    out = [e for e in seat["events"] if e["ev"] == "admit"]
    if not out:
        raise SystemExit(
            f"{seat['path']}: no admit events. This capture came from a build "
            f"without the getFrameAdvanceCount hook, so nothing here applies to "
            f"it -- rebuild 030-netlatprobe and re-run.")
    return out


def ran(seat):
    """First wall time at which each logic frame was about to run."""
    out = {}
    for e in seat["events"]:
        if e["ev"] == "frame":
            out.setdefault(e["f"], e["t"])
    return out


def gate(rows):
    """Why the readiness test said no, split by which side was wrong.

    Guests only. getFrameAdvanceCount splits on whether this seat is the packet
    router, and the router's half never looks at the ceiling: it accumulates
    QueryPerformanceCounter ticks against a fixed QPF/5 quantum. Its ceiling is
    its own published frame, so `allow` comes out non-positive on every tick and
    tallying it here would report the seat that sets the pace as the one being
    starved by it."""
    tally = {"admitted": 0, "no count yet": 0, "commands missing": 0,
             "more than expected": 0, "not permitted": 0}
    for e in rows:
        if e["allow"] <= 0:
            tally["not permitted"] += 1
        elif e["ok"]:
            tally["admitted"] += 1
        elif e["exp"] == NO_COUNT:
            tally["no count yet"] += 1
        elif e["exp"] > e["got"]:
            tally["commands missing"] += 1
        else:
            tally["more than expected"] += 1
    return tally


def first_true(rows, field, frame_of):
    """First tick at which `field` was true, keyed by the frame it was about."""
    out = {}
    for e in rows:
        if e[field]:
            out.setdefault(frame_of(e), e["t"])
    return out


def report(seat):
    rows = admits(seat)
    when = ran(seat)
    router = bool(rows[0]["router"])
    print(f"\n=== {Path(seat['path']).name}  slot {rows[0]['slot']}"
          f"  {'ROUTER' if router else 'guest'}  ({len(rows)} admit ticks) ===")

    polls = len(rows) / max(len(when), 1)
    print(f"  polls   {polls:.2f} per logic frame "
          f"({len(rows)} calls, {len(when)} frames)")
    # Present from the build that carries the loop counters; absent from older
    # captures, which is why it is reported only when it is there rather than
    # defaulted to zero.
    loops = [e.get("loops") for e in seat["events"]
             if e["ev"] == "frame" and e.get("loops") is not None][1:]
    drivers = [e.get("drivers") for e in seat["events"]
               if e["ev"] == "frame" and e.get("drivers") is not None][1:]
    if loops:
        print(f"  loop    {pct(loops, 50):.1f} main-loop iterations per logic frame")
    if drivers:
        print(f"  driver  {pct(drivers, 50):.1f} driver entries per logic frame "
              f"(of which {polls:.2f} reached the readiness test)")
    if router:
        print("  gate    n/a -- the router is paced by its own QPF/5 quantum, "
              "not by the ceiling")
        return dict(hold=[], prize=[], router=True, polls=polls)

    tally = gate(rows)
    total = sum(tally.values())
    print("  gate")
    for name, n in tally.items():
        print(f"      {name:20s} {n:6d}  {n / total * 100:5.1f}%")

    ready = first_true(rows, "ok", lambda e: e["f"])
    ahead = first_true(rows, "ok1", lambda e: e["f"] + 1)
    hold = [when[n] - ready[n] for n in sorted(when)
            if n in ready and when[n] >= ready[n]]
    prize = [when[n] - ahead[n] for n in sorted(when)
             if n in ahead and when[n] >= ahead[n]]
    print("  hold   (ran N, after N was first reported complete)")
    print(f"      n={len(hold):<5d} p50 {pct(hold, 50):7.1f}ms  "
          f"p90 {pct(hold, 90):7.1f}  max {max(hold) if hold else 0:7.1f}")
    print("  prize  (ran N, after N was first VISIBLY complete from frame N-1)")
    print(f"      n={len(prize):<5d} p50 {pct(prize, 50):7.1f}ms  "
          f"p90 {pct(prize, 90):7.1f}  max {max(prize) if prize else 0:7.1f}")
    print("      NOTE: acting on this desyncs -- see 034-framedrain. The count "
          "it rests on is a snapshot that can still grow.")
    return dict(hold=hold, prize=prize, router=router, polls=polls)


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("files", nargs="+")
    a = ap.parse_args()
    out = [report(load(p)) for p in a.files]
    guests = [o for o in out if not o["router"]]
    if guests:
        prize = [v for o in guests for v in o["prize"]]
        if prize:
            print(f"\nguest prize pooled: n={len(prize)}  p50 {pct(prize, 50):.1f}ms  "
                  f"p90 {pct(prize, 90):.1f}ms")
    return 0


if __name__ == "__main__":
    sys.exit(main())
