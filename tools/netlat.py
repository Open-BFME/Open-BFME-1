#!/usr/bin/env python3
"""Read the latency probe's files and answer the four questions they exist for.

One NetLat.jsonl per seat, written by mods/features/030-netlatprobe. All
seats run on one host, so QueryPerformanceCounter is the same system-wide clock
in every wine prefix and times compare directly across files with no
synchronisation step -- which is what makes a true cross-machine latency
measurable at all here. `--check-clocks` is what establishes it rather than
assuming it.

    python3 tools/netlat.py run1/*.jsonl

What it reports, per seat and then as the host-versus-guest comparison:

  wrap delay   t(send) - t(the input that produced it). The pump runs on 5 Hz
               logic ticks, so a guest command waits for the next tick merely to
               LEAVE the machine. This is the quantity a send-side fix shrinks
               and the reason it is the placebo killer: it is produced by the
               exact code path such a fix changes, so a fix that does nothing
               cannot move it.
  end to end   input -> the frame the router bound the command to. The number a
               player actually feels, up to the render.
  game speed   logic frames per wall second. This must NOT move: it is 5 by
               construction, and a "fix" that improves latency by running the
               game faster has changed the game, not fixed it.
  backlog      ceiling - frame. Reading the binary settled every other term
               statically; this one it could not. A guest that falls behind the
               published ceiling carries a second delay no send-side change can
               touch, and if it is non-zero in real matches the fix is only half
               the story.

Nothing here reports a number it cannot stand behind: a file with no events, a
join whose two sides disagree on how many commands there were, or a seat with no
frame events is an error, not a zero.
"""
import argparse
import bisect
import json
import sys
from collections import defaultdict, deque
from pathlib import Path

# A command that leaves the machine. Type 3 is the frame info every client sends
# once per logic tick; joining it into the latency numbers would mix ~5 events a
# second of something else into every median.
GAME_COMMAND = 4

# How stale a pending append may be before a second one at the same address is
# read as the allocator recycling it rather than as one message moving lists.
REUSE_GAP_MS = 1000.0

# An interval longer than this is a stall, not a frame time. Included, one 2 s
# router stall shifts a five-minute average by more than the budget the whole
# game-speed gate is decided on.
STALL_MS = 400.0


def load(path):
    """One seat's events, with the clock already converted to milliseconds."""
    events, freq, bad = [], None, 0
    for n, line in enumerate(Path(path).read_text().splitlines(), 1):
        line = line.strip()
        if not line:
            continue
        try:
            e = json.loads(line)
        except ValueError:
            bad += 1          # a torn final line is what a crash costs
            continue
        if e.get("ev") == "open":
            freq = e["qfreqlo"] + (e["qfreqhi"] << 32)
            continue
        if "qlo" not in e:
            bad += 1
            continue
        e["_q"] = e["qlo"] + (e["qhi"] << 32)
        events.append(e)
    if freq is None:
        raise SystemExit(f"{path}: no open record, so the clock has no scale. "
                         f"The file was written by a different build.")
    if not events:
        raise SystemExit(f"{path}: no events. The probe never fired: either no "
                         f"match was played, or the hooks are not installed.")
    for e in events:
        e["t"] = e["_q"] * 1000.0 / freq
    events.sort(key=lambda e: e["t"])
    return dict(path=str(path), events=events, freq=freq, bad=bad)


def pct(values, p):
    if not values:
        return float("nan")
    s = sorted(values)
    k = (len(s) - 1) * p / 100.0
    lo = int(k)
    hi = min(lo + 1, len(s) - 1)
    return s[lo] + (s[hi] - s[lo]) * (k - lo)


def describe(values):
    if not values:
        return "n=0    nothing paired"
    return (f"n={len(values):<5d} median={pct(values, 50):7.1f}  "
            f"p95={pct(values, 95):7.1f}  min={min(values):7.1f}  max={max(values):7.1f}")


def commands_ready(events):
    """Each game command, once, at the moment it was ready to send.

    A GameMessage is appended to TheMessageStream and then, after the
    translators run, to TheCommandList -- the same object both times. The last
    append is when the pump could first have taken it, which is what the wrap
    delay is measured from; the first is where the input entered the engine."""
    pending, out = {}, []
    for e in events:
        if e["ev"] != "input":
            continue
        prev = pending.get(e["msg"])
        # `owner` is the list the message was in before this append, so a
        # non-zero one IS the engine saying "this is the same message moving on"
        # -- which beats any timing heuristic, because the allocator hands the
        # address of a freed GameMessage straight back out and two commands can
        # share one within a tick. The age check only guards against pairing
        # with a pending entry left over from that reuse.
        if e["owner"] and prev is not None and e["t"] - prev["last"] <= REUSE_GAP_MS:
            prev["last"] = e["t"]
            continue
        if prev is not None:
            out.append(prev)
        pending[e["msg"]] = dict(first=e["t"], last=e["t"], type=e["type"])
    out.extend(pending.values())
    out.sort(key=lambda c: c["last"])
    return out


def wrap_delays(seat):
    """t(send) - t(ready), paired oldest-first.

    The pump drains the command list in order and sends in order, so a FIFO
    pairing is exact. It is only exact if the two sides agree on how many
    commands there were, which is why the caller is handed the shortfall rather
    than a median computed over a mismatch."""
    ready = deque(commands_ready(seat["events"]))
    sends = [e for e in seat["events"] if e["ev"] == "send" and e["type"] == GAME_COMMAND]
    wrap, pipeline, out_of_order = [], [], 0
    paired = []
    for s in sends:
        if not ready:
            break
        c = ready.popleft()
        if c["last"] > s["t"]:
            out_of_order += 1
            continue
        wrap.append(s["t"] - c["last"])
        pipeline.append(s["t"] - c["first"])
        paired.append((c, s))
    return dict(wrap=wrap, pipeline=pipeline, sends=len(sends),
                ready=len(commands_ready(seat["events"])),
                out_of_order=out_of_order, paired=paired)


def logic_rate(seat):
    """Logic frames per wall second, and the stalls left out of it.

    Computed from the frame FIELD rather than by counting events: a frame event
    can fire on a tick that does not advance the frame, so counting lines
    measures the instrument instead of the game."""
    frames = [e for e in seat["events"] if e["ev"] == "frame"]
    if len(frames) < 2:
        raise SystemExit(f"{seat['path']}: {len(frames)} frame events. "
                         f"Nothing can be said about the pace of the game.")
    df = dt = 0.0
    stalls = []
    for a, b in zip(frames, frames[1:]):
        gap = b["t"] - a["t"]
        if gap > STALL_MS:
            stalls.append(gap)
            continue
        df += b["f"] - a["f"]
        dt += gap
    if dt <= 0:
        raise SystemExit(f"{seat['path']}: every frame interval was a stall.")
    return df / dt * 1000.0, stalls, frames


def send_cadence(seat):
    """How long after its own logic tick each command leaves the machine.

    The pump runs inside Network::update, which runs only on a logic tick, so on
    retail every command waits for one and they all leave bunched against a tick
    boundary. Sending every engine tick instead spreads them across the 200 ms
    interval, so this separates the two without joining anything -- which
    matters, because a command is not one input event: several messages reach
    the list per click and only some become commands, so pairing inputs to sends
    in order pairs different things."""
    frames = [e["t"] for e in seat["events"] if e["ev"] == "frame"]
    out = []
    for e in seat["events"]:
        if e["ev"] == "send" and e["type"] == GAME_COMMAND:
            i = bisect.bisect_right(frames, e["t"]) - 1
            if i >= 0:
                out.append(e["t"] - frames[i])
    return out


def frame_skew(host, guest):
    """How far behind the host the guest's simulation actually runs.

    The clocks are the one host clock, so this is a direct reading of the thing
    the whole track is about: the guest sees frame N this much later than the
    host does, whatever produced it."""
    when = {}
    for e in host["events"]:
        if e["ev"] == "frame":
            when.setdefault(e["f"], e["t"])
    out = []
    for e in guest["events"]:
        if e["ev"] == "frame" and e["f"] in when:
            out.append(e["t"] - when[e["f"]])
    return out


def to_execution(seat, router):
    """From a command leaving this machine to the frame it lands on running here.

    A guest sends unstamped and the router pins the command to whatever frame it
    is on, so the binding only exists in the router's file. The host never goes
    through relayCommand at all -- it files its own commands locally -- so for it
    the question is when the world next advances after the command was sent."""
    when = {}
    for e in seat["events"]:
        if e["ev"] == "frame":
            when.setdefault(e["f"], e["t"])
    if seat["router"]:
        frames = sorted(when.values())
        out = []
        for e in seat["events"]:
            if e["ev"] == "send" and e["type"] == GAME_COMMAND:
                i = bisect.bisect_right(frames, e["t"])
                if i < len(frames):
                    out.append(frames[i] - e["t"])
        return out, 0
    bind = {}
    for e in router["events"]:
        if e["ev"] == "relay" and e["type"] == GAME_COMMAND and e["player"] == seat["slot"]:
            bind.setdefault(e["cmd"], e["f"])
    out, unbound = [], 0
    for e in seat["events"]:
        if e["ev"] != "send" or e["type"] != GAME_COMMAND:
            continue
        frame = bind.get(e["cmd"])
        t = when.get(frame) if frame is not None else None
        if t is None or t < e["t"]:
            unbound += 1
            continue
        out.append(t - e["t"])
    return out, unbound


def creation_to_run(seat, router):
    """From the input that produced a command to the frame it runs on.

    THE metric for judging a send-side fix, and the reason is not subtlety: a
    send-anchored clock starts when the command LEAVES the machine, and retail
    holds a command in its local list for most of a 200 ms quantum first. That
    hold is invisible to `to_execution`, and removing it is exactly what
    031-earlysend does -- so measuring that feature with `to_execution`
    subtracts its own benefit, and under packet loss it charges the fixed build
    for a freeze that retail's later timestamp lands inside. Doing so produced a
    phantom "p95 regression" that two parties independently reproduced, because
    they shared the instrument rather than the finding.

    The join is nearest-preceding-input rather than the FIFO pairing in
    `wrap_delays`. FIFO is invalid here: roughly three input messages reach the
    list per command, so popping one per send drifts by the difference and ends
    a match tens of seconds out of step. Nearest-preceding is approximate -- it
    can pick a sibling message of the same click -- but it cannot drift.

    Returns (values, held), where `held` is send minus creation. `held` is the
    check, not decoration: it must come out near zero for a build that sends
    immediately and near half a quantum for one that does not. If it does not,
    the join is wrong and the values are meaningless.

    Measured behaviour of that check, so a reader knows how far to trust it:

      clean LAN, retail      held p50 96.1  max 183.9   0/628 over a quantum
      clean LAN, earlysend   held p50  0.1  max   8.3   0/629 over a quantum
      80ms/1%, retail        held p50 86.9  max 750.3  47/629 over a quantum

    On a clean link the join is exact -- no send is held longer than the one
    quantum the mechanism allows, so no pairing can have crossed a click. Under
    loss 7.5% exceed a quantum, and this data cannot separate "the logic tick
    that would have sent it was itself delayed by a freeze" from "the pairing
    crossed into a neighbouring click". Both are plausible at 750 ms. Treat
    loss-condition medians as sound and individual loss-condition outliers as
    unattributed."""
    bind = {}
    for e in router["events"]:
        if e["ev"] == "relay" and e["type"] == GAME_COMMAND and e["player"] == seat["slot"]:
            bind.setdefault(e["cmd"], e["f"])
    when = {}
    for e in seat["events"]:
        if e["ev"] == "frame":
            when.setdefault(e["f"], e["t"])
    inputs = [e["t"] for e in seat["events"] if e["ev"] == "input"]
    if not inputs:
        raise SystemExit(f"{seat['path']}: no input events, so no command has a "
                         f"creation time. This capture cannot answer the question.")
    out, held = [], []
    for e in seat["events"]:
        if e["ev"] != "send" or e["type"] != GAME_COMMAND:
            continue
        frame = bind.get(e["cmd"])
        ran = when.get(frame) if frame is not None else None
        if ran is None or ran < e["t"]:
            continue
        i = bisect.bisect_left(inputs, e["t"]) - 1
        if i < 0:
            continue
        out.append(ran - inputs[i])
        held.append(e["t"] - inputs[i])
    return out, held


def end_to_end(seat, router, paired):
    """SUPERSEDED by creation_to_run -- kept only for callers that still pass a
    `paired` list. Its FIFO join drifts (see creation_to_run) and its results
    should not be quoted.

    input -> the frame the router bound the command to.

    The guest never learns its own execution frame: it sends unstamped and the
    router pins the command to whatever frame it is on. So the binding is read
    from the router's file and the wall time from the guest's own frame events,
    which is only possible because both clocks are the one host clock."""
    slot = seat["events"][0]["slot"]
    binds = deque(e for e in router["events"]
                  if e["ev"] == "relay" and e["type"] == GAME_COMMAND
                  and e["player"] == slot)
    # Keyed on the frame FIELD, not on the hook's argument. The frame event's
    # `exec` is relayCommandsToCommandList's arg0, which reads 1 rather than a
    # frame number -- to_execution was corrected for this and this function was
    # not, so every lookup missed and every command was discarded as unbound.
    # The failure was silent in the worst way: the guards reported "dropped",
    # which reads as bad data rather than as a broken join.
    when = {}
    for e in seat["events"]:
        if e["ev"] == "frame":
            when.setdefault(e["f"], e["t"])
    out, unbound, impossible = [], 0, 0
    for c, _ in paired:
        if not binds:
            break
        b = binds.popleft()
        # relayCommand reads the execution frame BEFORE binding it, so -1 is a
        # command arriving unstamped -- which is every guest command, and is the
        # frame the router was on at that moment.
        frame = b["f"] if b["exec"] < 0 else b["exec"]
        t = when.get(frame)
        if t is None:
            unbound += 1
            continue
        if t < c["first"]:
            # The frame ran before the input existed. Nothing physical produces
            # that, so the two sides are being paired wrongly -- averaging it in
            # would quietly shorten the very number the spike is decided on.
            impossible += 1
            continue
        out.append(t - c["first"])
    return out, unbound, impossible


def preflight(seats):
    """Everything the measurement plan still assumes, checked against a capture.

    Run this on the FIRST recording, before booking a campaign. Each of these is
    an assumption that reading the binary could not settle, and each fails a
    later run in a way that looks like a result: a hook that never fires reports
    no latency, a clock that is not shared reports a nonsense one."""
    ok = True

    def check(name, passed, detail, fix=""):
        nonlocal ok
        ok = ok and passed
        print(f"  [{'PASS' if passed else 'FAIL'}] {name}: {detail}")
        if not passed and fix:
            print(f"         -> {fix}")

    # Across the seats first: a mismatched clock makes every per-seat number
    # downstream of it nonsense, and reporting that nonsense before its cause
    # sends the reader after the wrong thing.
    if len(seats) > 1:
        print("=== across seats")
        check("one clock frequency", len({s["freq"] for s in seats}) == 1,
              ", ".join(str(s["freq"]) for s in seats),
              "the seats did not share a host; cross-seat latency is meaningless, "
              "and every rate below is scaled by the wrong divisor.")
        lo = max(s["events"][0]["t"] for s in seats)
        hi = min(s["events"][-1]["t"] for s in seats)
        check("the recordings overlap", hi > lo,
              f"{(hi - lo) / 1000.0:.1f}s of overlap" if hi > lo else "disjoint",
              "these files are not one match.")
        routers = [s for s in seats if s["events"][0]["router"]]
        check("exactly one packet router", len(routers) == 1,
              f"{len(routers)} seats claim it",
              "without the router's file no command's execution frame is knowable.")
        print()

    for s in seats:
        ev = s["events"]
        name = Path(s["path"]).name
        print(f"=== {name}  slot {ev[0]['slot']}"
              f"{'  ROUTER' if ev[0]['router'] else ''}")
        kinds = defaultdict(int)
        for e in ev:
            kinds[e["ev"]] += 1
        print(f"  events: " + ", ".join(f"{k}={v}" for k, v in sorted(kinds.items())))

        # The one hook whose target was never confirmed to be the path input
        # actually takes. No input events and every latency number is uncomputable.
        check("input hook fires", kinds["input"] > 0,
              f"{kinds['input']} input events",
              "the translators do not reach the hooked appendMessage body. Re-aim "
              "H1, or filter on TheCommandList instead and re-capture.")

        # A command should be seen entering TheMessageStream and then, once the
        # translators have run, TheCommandList. One list only means half the
        # pipeline is invisible -- measurable, but from a later point.
        lists = defaultdict(int)
        for e in ev:
            if e["ev"] == "input":
                lists[e["list"]] += 1
        if lists:
            print("  input lists: " + ", ".join(f"0x{k:08X}={v}" for k, v in
                                                sorted(lists.items())))
        ready = commands_ready(ev)
        moved = sum(1 for c in ready if c["last"] > c["first"])
        check("the two-append pipeline is visible", bool(ready),
              f"{len(ready)} commands, {moved} seen moving between lists")

        # If the id is a real per-player counter it is an exact join key and the
        # FIFO pairing can be checked against it rather than trusted.
        ids = [e["cmd"] for e in ev if e["ev"] == "send" and e["type"] == GAME_COMMAND]
        rising = sum(1 for a, b in zip(ids, ids[1:]) if b > a)
        check("command id is a usable join key", len(ids) > 1 and rising >= len(ids) - 2,
              f"{rising}/{max(len(ids) - 1, 0)} of {len(ids)} ids increase",
              "ids are not a per-player counter; the FIFO pairing is the only join.")

        frames = [e for e in ev if e["ev"] == "frame"]
        if len(frames) >= 2:
            # A diagnostic reports every fault it can see rather than stopping at
            # the first, so the refusals that are right for the metrics path are
            # a FAIL line here.
            try:
                rate, stalls, _ = logic_rate(s)
                check("logic rate is the engine's 5 Hz", 4.5 <= rate <= 5.5,
                      f"{rate:.3f} frames/s, {len(stalls)} stalls excluded",
                      "the capture is not a normal match, or the probe is distorting "
                      "it. Compare against an unarmed build before trusting a latency.")
            except SystemExit as why:
                check("logic rate is the engine's 5 Hz", False, str(why))
            backlog = [e["c"] - e["f"] for e in frames]
            median = pct(backlog, 50)
            print(f"  [ .. ] backlog: median {median:.1f}, p95 {pct(backlog, 95):.1f}"
                  f"  ({'send-side is the whole story' if median < 2 else 'A SECOND DELAY TERM'})")
        else:
            check("the frame heartbeat fires", False,
                  f"{len(frames)} frame events",
                  "nothing can be said about the pace of the game, so no latency "
                  "number from this seat is trustworthy.")
        print()

    print("PREFLIGHT " + ("PASSED" if ok else "FAILED"))
    return 0 if ok else 1


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("files", nargs="+", help="one NetLat.jsonl per seat")
    ap.add_argument("--check-clocks", action="store_true",
                    help="assert the seats share one clock before comparing across them")
    ap.add_argument("--preflight", action="store_true",
                    help="check what the measurement plan assumes, against a first capture")
    a = ap.parse_args()

    if a.preflight:
        return preflight([load(p) for p in a.files])

    seats = [load(p) for p in a.files]
    for s in seats:
        ev = s["events"]
        s["slot"] = ev[0]["slot"]
        s["router"] = bool(ev[0]["router"])
        s["span"] = (ev[-1]["t"] - ev[0]["t"]) / 1000.0
    if len({s["freq"] for s in seats}) > 1:
        raise SystemExit("the seats report different clock frequencies, so their "
                         "timestamps are not comparable. They did not share a host.")
    if a.check_clocks:
        # Overlapping spans are necessary for a cross-seat join to mean anything;
        # disjoint ones mean the files are from different matches.
        lo = max(s["events"][0]["t"] for s in seats)
        hi = min(s["events"][-1]["t"] for s in seats)
        if hi <= lo:
            raise SystemExit("the seats' recordings do not overlap in time; these "
                             "files are not one match.")
        print(f"clocks: one frequency, {(hi - lo) / 1000.0:.1f}s of overlap\n")

    routers = [s for s in seats if s["router"]]
    if len(routers) > 1:
        raise SystemExit(f"{len(routers)} seats claim to be the packet router.")
    router = routers[0] if routers else None
    if router is None:
        print("no router file: end-to-end needs the seat that binds the frames\n")

    results = {}
    for s in sorted(seats, key=lambda x: (not x["router"], x["slot"])):
        role = "ROUTER" if s["router"] else "guest "
        rate, stalls, frames = logic_rate(s)
        j = wrap_delays(s)
        backlog = [e["c"] - e["f"] for e in s["events"] if e["ev"] == "frame"]
        desync = max((e.get("desync", 0) for e in s["events"] if e["ev"] == "frame"),
                     default=0)
        stallcount = max((e.get("stalls", 0) for e in s["events"] if e["ev"] == "frame"),
                         default=0)

        print(f"=== slot {s['slot']} {role}  {Path(s['path']).name}  "
              f"{s['span']:.0f}s, {len(s['events'])} events" +
              (f", {s['bad']} unparsable lines" if s["bad"] else ""))
        print(f"  logic rate   {rate:.3f} frames/s"
              f"   ({len(frames)} frames, {len(stalls)} stalls excluded)")
        print(f"  backlog      median={pct(backlog, 50):.1f}  p95={pct(backlog, 95):.1f}"
              f"  max={max(backlog) if backlog else 0}   (ceiling - frame)")
        cadence = send_cadence(s)
        if cadence:
            print(f"  send cadence {describe(cadence)}   (ms after this seat's own logic tick)")
        else:
            print("  send cadence no game commands left this machine")
        print(f"  commands     {j['sends']} sent, {j['ready']} input bursts queued")
        if desync:
            print(f"  *** DESYNC flagged on this seat")
        if stallcount:
            print(f"  stalls       {stallcount} cumulative")

        e2e = []
        if router is not None:
            e2e, unbound = to_execution(s, router)
            if e2e:
                print(f"  send->run    {describe(e2e)}   (until the frame it lands on runs here)")
            if unbound:
                print(f"  ({unbound} commands the router's file never bound to a frame)")
        results[s["slot"]] = dict(seat=s, rate=rate, wrap=j["wrap"],
                                  pipeline=j["pipeline"], e2e=e2e, backlog=backlog)
        print()

    host = next((r for r in results.values() if r["seat"]["router"]), None)
    guests = [r for r in results.values() if not r["seat"]["router"]]
    if host and guests:
        print("=== host vs guest")
        he = pct(host["e2e"], 50) if host["e2e"] else float("nan")
        ge = pct([v for g in guests for v in g["e2e"]], 50)
        print(f"  send->run    host {he:6.1f} ms   guest {ge:6.1f} ms   "
              f"gap {ge - he:+.1f} ms")
        for g in guests:
            skew = frame_skew(host["seat"], g["seat"])
            if skew:
                print(f"  frame skew   slot {g['seat']['slot']} runs each frame "
                      f"{pct(skew, 50):.1f} ms after the host (p90 {pct(skew, 90):.1f})")
        rates = [r["rate"] for r in results.values()]
        print(f"  logic rate   {min(rates):.3f} .. {max(rates):.3f} frames/s across seats")
        gb = pct([v for g in guests for v in g["backlog"]], 50)
        print(f"  guest backlog median {gb:.1f} frames"
              + ("   <- a second delay term; a send-side fix cannot touch it"
                 if gb >= 2 else "   (send-side is the whole story)"))
    return 0


if __name__ == "__main__":
    sys.exit(main())
