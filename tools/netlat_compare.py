#!/usr/bin/env python3
"""Pool several matches per arm and compare them.

    python3 tools/netlat_compare.py --baseline build/netlat/s1 build/netlat/base2 \
                                    --fix build/netlat/s2fix build/netlat/fix2

One match is an anecdote: wine scheduling, the map, and where the scripted clicks
happen to land against the 5 Hz tick all move the medians a little. So every
number here is reported as the median across matches AND the spread between the
best and worst match of that arm -- an improvement smaller than the spread is not
an improvement, and saying so is the whole point of running more than one.

Each match is summarised by its own per-seat medians first, so one long match
cannot outvote the others by contributing more samples.
"""
import argparse
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from netlat import (GAME_COMMAND, creation_to_run, frame_skew, load,  # noqa: E402
                    logic_rate, pct, send_cadence, to_execution)


def summarise(run):
    """One match, as the handful of numbers the comparison is made of."""
    seats = [load(p) for p in sorted(Path(run).glob("*.jsonl"))]
    for s in seats:
        s["slot"] = s["events"][0]["slot"]
        s["router"] = bool(s["events"][0]["router"])
    router = next((s for s in seats if s["router"]), None)
    guests = [s for s in seats if not s["router"]]
    if router is None or not guests:
        raise SystemExit(f"{run}: needs one router file and at least one guest")
    guest = guests[0]

    out = {"run": Path(run).name}
    for name, seat in (("host", router), ("guest", guest)):
        cad = send_cadence(seat)
        e2e, _ = to_execution(seat, router)
        # The creation-anchored metric, and the one to read. `to_execution`
        # starts its clock when a command LEAVES the machine, which subtracts a
        # send-side fix's own benefit -- it is what produced a phantom p95
        # regression that two sessions reproduced because they shared it.
        # `held` is not a diagnostic: it is send minus creation, i.e. exactly the
        # local delay a send-side fix removes, and it read 86.9-96.1 ms in every
        # retail arm against 0.1 ms in every 031-earlysend arm from the first
        # capture onward. It was labelled a validity check and went unread as a
        # result for four hours.
        # The ROUTER has no creation-anchored figure and this is structural, not
        # a failure: creation_to_run binds a command to its frame using the
        # router's relay events, and the router binds its OWN commands inside
        # sendLocalCommand (0x00A6478D) without ever relaying them to itself. So
        # no relay event carries the router's own player id and the join is
        # empty. Reported as "n/a (structural)" rather than nan, because a bare
        # nan reads as a broken measurement.
        try:
            e2r, held = creation_to_run(seat, router)
        except SystemExit as why:
            print(f"  {run}: {name} has no creation-anchored figure -- {why}",
                  file=sys.stderr)
            e2r, held = [], []
        rate, stalls, frames = logic_rate(seat)
        out[f"{name}_cadence"] = pct(cad, 50) if cad else float("nan")
        out[f"{name}_earliest"] = min(cad) if cad else float("nan")
        out[f"{name}_run"] = pct(e2e, 50) if e2e else float("nan")
        out[f"{name}_created"] = pct(e2r, 50) if e2r else float("nan")
        out[f"{name}_held"] = pct(held, 50) if held else float("nan")
        out[f"{name}_rate"] = rate
        out[f"{name}_frames"] = max(e["f"] for e in seat["events"] if e["ev"] == "frame")
        out[f"{name}_desync"] = max((e.get("desync", 0) for e in seat["events"]
                                     if e["ev"] == "frame"), default=0)
        out[f"{name}_backlog"] = pct([e["c"] - e["f"] for e in seat["events"]
                                      if e["ev"] == "frame"], 50)
        out[f"{name}_cmds"] = sum(1 for e in seat["events"]
                                  if e["ev"] == "send" and e["type"] == GAME_COMMAND)
    skew = frame_skew(router, guest)
    out["skew"] = pct(skew, 50) if skew else float("nan")
    out["gap"] = out["guest_run"] - out["host_run"]
    return out


def pool(runs, key):
    values = [r[key] for r in runs if r[key] == r[key]]     # drop NaN
    return (pct(values, 50), min(values), max(values)) if values else (float("nan"),) * 3


# The host's creation-anchored rows are omitted deliberately -- see summarise().
# The router never relays its own commands, so the join has nothing to bind to,
# and printing nan there invites a reader to think something broke.
ROWS = [
    ("guest: CREATED -> it runs", "guest_created", "ms"),
    ("guest: held locally before send", "guest_held", "ms"),
    ("guest: send -> it runs (SUPERSEDED)", "guest_run", "ms"),
    ("host: send -> it runs (SUPERSEDED)", "host_run", "ms"),
    ("host vs guest gap", "gap", "ms"),
    ("guest send cadence", "guest_cadence", "ms"),
    ("guest earliest send", "guest_earliest", "ms"),
    ("host send cadence", "host_cadence", "ms"),
    ("guest frame skew behind host", "skew", "ms"),
    ("guest logic rate", "guest_rate", "/s"),
    ("guest backlog", "guest_backlog", "fr"),
]


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--baseline", nargs="+", required=True, metavar="DIR")
    ap.add_argument("--fix", nargs="+", required=True, metavar="DIR")
    ap.add_argument("--label", default="fix")
    a = ap.parse_args()

    arms = {"retail": [summarise(r) for r in a.baseline],
            a.label: [summarise(r) for r in a.fix]}
    for name, runs in arms.items():
        print(f"{name}: {len(runs)} matches -- {', '.join(r['run'] for r in runs)}")
        for r in runs:
            print(f"    {r['run']:<10s} guest run {r['guest_run']:7.1f}ms  "
                  f"cadence {r['guest_cadence']:6.1f}ms  frames {r['guest_frames']}  "
                  f"rate {r['guest_rate']:.3f}/s  cmds {r['guest_cmds']}"
                  + ("  DESYNC" if r["guest_desync"] or r["host_desync"] else ""))
    print()

    b, f = arms["retail"], arms[a.label]
    print(f"{'':32s} {'retail':>24s} {a.label:>24s} {'change':>10s}")
    for label, key, unit in ROWS:
        # A rate near 5 and a latency near 400 need different precision: one
        # decimal on the rate would hide exactly the drift the row exists to catch.
        dp = 3 if unit == "/s" else 1
        bm, blo, bhi = pool(b, key)
        fm, flo, fhi = pool(f, key)
        print(f"{label:32s} {bm:9.{dp}f}{unit} [{blo:.{dp}f}-{bhi:.{dp}f}]"
              f"{fm:11.{dp}f}{unit} [{flo:.{dp}f}-{fhi:.{dp}f}]"
              f"{fm - bm:+9.{dp}f}")

    # Game speed is the invariant, so it is checked rather than merely printed.
    frames = {n: {r[f"{s}_frames"] for r in runs for s in ("host", "guest")}
              for n, runs in arms.items()}
    print(f"\nlogic frames executed   retail {sorted(frames['retail'])}   "
          f"{a.label} {sorted(frames[a.label])}")
    desync = [r["run"] for runs in arms.values() for r in runs
              if r["host_desync"] or r["guest_desync"]]
    print("desync                  " + ("NONE in any match" if not desync
                                        else f"*** {desync}"))
    return 0


if __name__ == "__main__":
    sys.exit(main())
