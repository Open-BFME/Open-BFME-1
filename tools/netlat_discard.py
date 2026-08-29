#!/usr/bin/env python3
"""Does BFME actually throw a command away, and how close does normal play come?

    python3 tools/netlat_discard.py build/netlat/lean-retry1

`033-retrytime` rests on one branch in `Connection::update` (VA 0x00A620A4).
After an ack-required command is put in a packet, the engine keeps it only while

    execution_frame + NetworkRunAheadSlack >= TheGameLogic->getFrame()

and otherwise deletes it from the send queue for good. Nothing in BFME can
recover from that: the readiness test is a single equality on summed command
counts with no resend-request path, so a seat that missed the command could never
complete that frame.

MEASURED RESULT, AND IT IS NOT THE ALARMING ONE. The guard is reached routinely
-- 2.5% of router game-command sends in a retail match at 150 ms / 3% -- but
every discard observed was of a command the peer HAD ALREADY RECEIVED. The guard
fires when an ACK is lost or still in flight, and dropping an already-delivered
command from the retry queue costs nothing. So a raw discard count reads as
damage and is not; the tool splits the two and only the never-delivered count
matters. The harmful case needs a discard AND non-delivery -- roughly p^2 at
retail's one attempt per horizon -- and has never been observed.

Only the ROUTER can discard a game command. A guest's own commands carry
exec == -1 until the router binds them, and the guard skips unbound commands
(cmp eax,-1 / je), so a guest reaches this site only for frame info.

Two constants collide at the same number, which is the whole argument. The retry
interval is 2000 ms, and the slack is 10 frames -- also exactly 2000 ms at
BFME's 5 Hz logic rate. So retail fires its single retransmission at the very
instant the command becomes eligible to be discarded, and a shorter timer buys
attempts inside the same fixed horizon.

WHY THIS FILE EXISTS RATHER THAN A PROXY. That branch was read out of the
disassembly and, for most of this work, never observed. Two attempts to reach it
indirectly -- through a seat's headroom over the published frame ceiling -- were
both wrong, in the same way and for the same reason: the ceiling is a monotonic
maximum of ANNOUNCED frames (0x00A6A4BE raises it and nothing lowers it), so it
runs ahead of every seat's current frame by roughly the run-ahead. Headroom
bounds this quantity loosely from above; it is not this quantity. The hook
measures the engine's own comparison at the moment the engine makes it.

  margin      exec + slack - now, in logic frames, at the decision point.
              NEGATIVE means the command was discarded. This is the headline: a
              distribution, not a yes/no, so it says how close ordinary play
              comes to the cliff even in runs that never go over.
  doomed      how many were actually discarded. A single one in a retail arm
              establishes the mechanism fires; a single one in a fixed arm kills
              the fix, because that is the failure it exists to prevent.
  retries     Connection::m_numRetries at the decision. Note it is ZEROED every
              10 s by the engine's own metrics timer, so it is a recent-rate
              indicator and NOT a per-command attempt count -- do not read it as
              "this command was tried N times".

A CLEAN RESULT IS NOT A NULL RESULT. If no arm discards anything, the margin
distribution still says whether retail runs closer to the horizon than the fixed
build does, and that is a measurement of the mechanism rather than an absence of
one. Report the percentiles either way.
"""
import argparse
import json
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from netlat import GAME_COMMAND, load, pct  # noqa: E402


def discards(seat):
    rows = [e for e in seat["events"] if e["ev"] == "discard"]
    if not rows:
        raise SystemExit(
            f"{seat['path']}: no discard events. This capture came from a build "
            f"without the Connection::update hook, so nothing here applies to it "
            f"-- rebuild 030-netlatprobe and re-run.")
    return rows


def delivered_ids(seats, exclude):
    """Every command id any OTHER seat was seen to handle.

    A discarded command only costs anything if the peer never got it. A command
    whose ACK was lost is still delivered, and dropping it from the sender's
    retry queue is free. Without this split the tool reports a discard count that
    reads as damage and is not.
    """
    out = set()
    for s in seats:
        if s["path"] == exclude:
            continue
        for e in s["events"]:
            if e.get("cmd"):
                out.add(e["cmd"])
    return out


def report(run):
    seats = [load(p) for p in sorted(Path(run).glob("*.jsonl"))]
    if not seats:
        raise SystemExit(f"{run}: no captures.")
    print(f"\n=== {Path(run).name} ===")
    out = []
    for s in seats:
        rows = discards(s)
        router = bool(rows[0]["router"])
        margins = sorted(e["margin"] for e in rows)
        doomed = [e for e in rows if e["doomed"]]
        slack = rows[0]["slack"]
        # GAME commands only. A guest never reaches this site for its own orders
        # -- they carry exec == -1 until the router binds them and the guard
        # skips unbound commands -- so only the router can discard one.
        game = [e for e in rows if e.get("type") == GAME_COMMAND]
        game_doomed = [e for e in game if e["doomed"]]
        seen = delivered_ids(seats, s["path"])
        lost = [e for e in game_doomed if e["cmd"] not in seen]
        print(f"  slot {rows[0]['slot']} {'ROUTER' if router else 'guest '}  "
              f"{len(rows):5d} decisions, slack {slack} frames")
        print(f"      margin (frames to the discard cliff)  "
              f"min {margins[0]:4d}  p1 {pct(margins, 1):5.1f}  "
              f"p10 {pct(margins, 10):5.1f}  p50 {pct(margins, 50):5.1f}")
        if game:
            print(f"      game commands  {len(game):5d} decisions  "
                  f"{len(game_doomed):4d} discarded ({len(game_doomed)/len(game)*100:5.2f}%)")
            if game_doomed:
                print(f"          of those, already delivered to the peer: "
                      f"{len(game_doomed) - len(lost)}")
                print(f"          NEVER DELIVERED (the harmful case):      "
                      f"{len(lost)}"
                      + ("" if not lost else
                         f"  *** ids {sorted(e['cmd'] for e in lost)[:8]}"))
        else:
            print("      game commands  none reach this site (unbound, exec == -1)")
        if not doomed:
            print(f"      discarded 0 of any type — closest approach {margins[0]} frame(s)")
        out.append(dict(router=router, margins=margins, doomed=len(doomed),
                        game=len(game), game_doomed=len(game_doomed), lost=len(lost)))
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("runs", nargs="+", metavar="DIR")
    a = ap.parse_args()
    allout = [(r, report(r)) for r in a.runs]
    print("\n" + "=" * 62)
    for run, seats in allout:
        m = sorted(v for s in seats for v in s["margins"])
        d = sum(s["doomed"] for s in seats)
        if not m:
            continue
        print(f"{Path(run).name:20s} closest {m[0]:4d}  p1 {pct(m, 1):6.1f}  "
              f"p50 {pct(m, 50):6.1f}  discarded {d}")
    total = sum(s["doomed"] for _, seats in allout for s in seats)
    harmful = sum(s["lost"] for _, seats in allout for s in seats)
    gd = sum(s["game_doomed"] for _, seats in allout for s in seats)
    print(f"\ndiscards across every capture: {total} "
          f"({gd} game commands, of which {harmful} never reached the peer)")
    if harmful:
        print("*** A game command was discarded that the peer never received.\n"
              "    That is the failure 033-retrytime exists to prevent, and in a\n"
              "    fixed arm it kills the feature.")
    elif gd:
        print("Every discarded game command had already been delivered — the\n"
              "guard fires on commands whose ACK was lost, which costs nothing.\n"
              "The harmful case needs a discard AND non-delivery, which is ~p^2.")
    if total == 0:
        print("Not a null result — compare the `closest` and p1 columns across arms.\n"
              "A build that runs closer to the cliff is the one that will go over it\n"
              "first on a worse link, at more players, or in a longer match.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
