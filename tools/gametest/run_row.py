#!/usr/bin/env python3
"""run_row.py <row-id> [<row-id>...] -- play declared matrix rows and land their
records as fixtures.

Each row is one full seat-and-play cycle on the existing rig: lan4-netns.sh puts
one client in one network namespace each, run_lan4.py seats them and clicks PLAY
GAME, this applies the row's exits in the declared order, and every client's
GameResult.jsonl is copied to reverse/game_end/measured/<row-id>/.

Nothing about a row is spelled here. The seats, their teams, how each one leaves
and in what order all come from tools/gametest/rows.py, which was written before
any of these rows were run -- that is what makes the fixtures a measurement
against a prediction rather than against themselves.

A row that cannot be completed writes nothing and is reported as not-run. There
is no path here that infers an outcome from a client that failed to produce one:
a seat that does not seat, a citadel that cannot be found, a match that never
resolves all end the row with an exception and an empty measured directory.
"""
import os
import re
import signal
import subprocess
import sys
import threading
import time
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path.insert(0, str(HERE))

import exits  # noqa: E402
import rows  # noqa: E402
import run_lan4  # noqa: E402
from driver import Driver  # noqa: E402

MEASURED = ROOT / "reverse" / "game_end" / "measured"
SHOTS = ROOT / "build" / "gametest"
RESULT_REL = ("drive_c/users/wacket/AppData/Roaming/"
              "My Battle for Middle-earth Files/GameResult.jsonl")

# Two kinds of exit, and they are not interchangeable. A UI exit is driven
# through the client's own screen and needs its Driver; a signal exit is
# delivered to the client's process and needs its WINEPREFIX, which is how the
# process is identified on a machine shared with another agent.
UI_EXITS = {"D": exits.demolish, "Q": exits.quit}
SIGNAL_EXITS = {"K": exits.kill, "F": exits.freeze}

SEAT_TIMEOUT = 900      # lobby walk, host, join, teams, PLAY GAME
LOAD_TIMEOUT = 900      # PLAY GAME until every client has a local slot
END_TIMEOUT = 900       # the last exit until the match resolves
# Long enough that "this machine wrote no end record" is a fact about the engine
# rather than about when the files were read. The four machines of the measured
# 2v2 all wrote theirs within the same second.
SETTLE = 45
# The same margin again, after a frozen client is resumed, so "a resumed client
# writes nothing" is a fact rather than a report on how soon it was looked at.
THAW_SETTLE = 45


def env_file():
    """The displays and prefixes this rig was given, from the repo .env.

    Read rather than taken from the environment: the displays are DETECTED by
    gpu-displays.sh and written there, and a runner that guessed :2-:5 would
    drive whatever else happened to hold those numbers on a shared machine."""
    values = {}
    for line in (ROOT / ".env").read_text().splitlines():
        if line.startswith("#") or "=" not in line:
            continue
        key, _, value = line.partition("=")
        values[key.strip()] = value.strip().strip('"').split()
    return values


def result_path(prefix):
    return Path(prefix) / RESULT_REL


def records(path):
    """The record kinds in one client's file, in order, or [] if it has none."""
    if not path.exists():
        return []
    return [line.split('"ev":"', 1)[1].split('"', 1)[0]
            for line in path.read_text(encoding="utf-8").splitlines() if line.strip()]


def wait_for(what, predicate, timeout, poll=5):
    deadline = time.time() + timeout
    while time.time() < deadline:
        if predicate():
            return time.time()
        time.sleep(poll)
    raise RuntimeError(f"{what} did not happen within {timeout}s")


class Rig:
    """One run of lan4-netns.sh, held open for the length of a row.

    The bridge the clients' veths plug into lives in the namespace this process
    owns, so it has to outlive the match: BFME_HOLD keeps the inner script
    sleeping after it has seated everyone, and tearing it down early takes the
    network away from a live match."""

    def __init__(self, displays, shotdir):
        self.lines = []
        self.proc = subprocess.Popen(
            [str(HERE / "lan4-netns.sh"), *displays, str(shotdir)],
            cwd=str(ROOT), env=dict(os.environ, BFME_HOLD=str(SEAT_TIMEOUT + END_TIMEOUT)),
            stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True,
            start_new_session=True)
        self.pump = threading.Thread(target=self._pump, daemon=True)
        self.pump.start()

    def _pump(self):
        for line in self.proc.stdout:
            self.lines.append(line.rstrip())
            print(f"    | {line.rstrip()}", flush=True)

    def seated(self, want):
        """The count run_lan4.py verified by looking at each joiner's screen."""
        for line in self.lines:
            found = re.match(r"SEATED (\d+)/(\d+)", line)
            if found:
                got, total = (int(n) for n in found.groups())
                if got != total or total != want:
                    raise RuntimeError(f"seating failed: {line}")
                return True
        if self.proc.poll() is not None:
            raise RuntimeError(f"the rig exited (rc={self.proc.returncode}) before seating")
        return False

    def stop(self):
        for sig in (signal.SIGTERM, signal.SIGKILL):
            try:
                os.killpg(os.getpgid(self.proc.pid), sig)
                self.proc.wait(timeout=30)
                return
            except (ProcessLookupError, subprocess.TimeoutExpired):
                continue


def play(row_id, row, values):
    """Play one row and return {seat: bytes of that client's record file}."""
    seats = sorted(row["seats"])
    displays = values["BFME_DISPLAYS"][:len(seats)]
    prefixes = values["BFME_PREFIXES"][:len(seats)]
    if run_lan4.SEATS[len(seats)] != tuple(seats):
        raise RuntimeError(
            f"{row_id} declares seats {seats}, but a {len(seats)}-client rig seats "
            f"{list(run_lan4.SEATS[len(seats)])}")
    for seat in seats:
        mode = row["seats"][seat]["exit"]
        if mode is not None and mode not in UI_EXITS and mode not in SIGNAL_EXITS:
            raise RuntimeError(f"{row_id} {seat}: exit mode {mode!r} has no primitive")

    shotdir = SHOTS / row_id
    (SHOTS / "logs").mkdir(parents=True, exist_ok=True)   # lan4-netns-inner.sh writes here
    prefix_of = dict(zip(seats, prefixes))
    paths = {seat: result_path(prefix) for seat, prefix in prefix_of.items()}
    frozen = [seat for seat in seats if row["seats"][seat]["exit"] == "F"]
    launched = time.time()
    rig = Rig(displays, shotdir)
    try:
        print(f"  seating {len(seats)} client(s) on {' '.join(displays)}", flush=True)
        wait_for("seating", lambda: rig.seated(len(seats)), SEAT_TIMEOUT)
        wait_for("every client reaching the match",
                 lambda: all(records(p) for p in paths.values()), LOAD_TIMEOUT)
        print(f"  in the match after {int(time.time() - launched)}s", flush=True)

        drivers = {}
        for seat, display in zip(seats, displays):
            drivers[seat] = Driver(shotdir / rows.NAMES[seat], seat, display=display)
            drivers[seat].n = 20        # past run_lan4.py's numbering for this client

        def apply_exit(seat, mode):
            if mode in UI_EXITS:
                UI_EXITS[mode](drivers[seat])
            else:
                SIGNAL_EXITS[mode](prefix_of[seat])

        exiting = {seat: row["seats"][seat] for seat in seats
                   if row["seats"][seat]["exit"] is not None}
        for order in sorted({spec["order"] for spec in exiting.values()}):
            batch = [s for s, spec in exiting.items() if spec["order"] == order]
            doing = ", ".join(f"{s} {exiting[s]['exit']}" for s in batch)
            print(f"  exit {order}: {doing}", flush=True)
            with ThreadPoolExecutor(max_workers=len(batch)) as pool:
                list(pool.map(lambda s: apply_exit(s, exiting[s]["exit"]), batch))

        # Wait on the seats the row says will witness the end, then settle for
        # the ones it says will not. Only the wait is taken from the row: what
        # the files hold when it is over is read, never assumed, so a seat that
        # writes a record it was not predicted to write is still collected and
        # still contradicts its declaration.
        witnesses = [s for s in seats if row["seats"][s]["records"] == "start+end"]
        if witnesses:
            wait_for("the match resolving",
                     lambda: all("end" in records(paths[s]) for s in witnesses), END_TIMEOUT)
            print(f"  resolved after {int(time.time() - launched)}s", flush=True)
        time.sleep(SETTLE)

        collected = {}
        for seat in seats:
            path = paths[seat]
            if not path.exists():
                raise RuntimeError(f"{seat}: {path} was never written")
            if path.stat().st_mtime < launched:
                raise RuntimeError(f"{seat}: {path} is older than this run")
            collected[seat] = path.read_bytes()
            print(f"  {seat}: {records(path)}", flush=True)
        # Everyone still there gets a final screenshot. A killed client does
        # not: kill() established that its processes are gone, so its window is
        # gone with them, and a display with nothing mapped has no screen to
        # capture -- asking would fail the row over data it had already read.
        for seat, driver in drivers.items():
            if row["seats"][seat]["exit"] != "K":
                driver.shot("collected")

        # The fixture is what a frozen client's file held while it was frozen,
        # so the bytes are taken before it is resumed. Resuming it is not part
        # of the row -- it is the cleanup the row owes -- but whether a resumed
        # client then writes anything decides whether freeze can be reused at
        # all, so it is measured here rather than assumed either way.
        for seat in frozen:
            before = records(paths[seat])
            exits.thaw(prefix_of[seat])
            time.sleep(THAW_SETTLE)
            print(f"  {seat}: resumed, {before} -> {records(paths[seat])}", flush=True)
        return collected
    finally:
        # Before anything else: a client left stopped holds its wine prefix, and
        # the next run that reaches for that prefix attaches to the wineserver it
        # never let go of. This runs on the failed path too, which is the one
        # that would otherwise leave one behind.
        for seat in frozen:
            exits.thaw(prefix_of[seat])
        rig.stop()
        subprocess.run([str(HERE / "kill-mine.sh"), *displays, *prefixes],
                       cwd=str(ROOT), check=True)


def main(row_ids):
    values = env_file()
    unknown = [r for r in row_ids if r not in rows.ROWS]
    if unknown:
        raise SystemExit(f"no such row in tools/gametest/rows.py: {', '.join(unknown)}")

    failed = []
    for row_id in row_ids:
        row = rows.ROWS[row_id]
        print(f"\n=== {row_id} (matrix row {row['matrix']}, {row['shape']}, "
              f"team {row['won']} declared to win) ===", flush=True)
        try:
            collected = play(row_id, row, values)
        except Exception as exc:                      # noqa: BLE001 - reported, not handled
            print(f"NOT RUN {row_id}: {exc}", flush=True)
            failed.append(row_id)
        else:
            out = MEASURED / row_id
            out.mkdir(parents=True, exist_ok=True)
            for seat, blob in collected.items():
                (out / f"{seat}.jsonl").write_bytes(blob)
            print(f"LANDED {row_id} -> {out}", flush=True)
        time.sleep(15)      # let the wineservers go before the next row launches

    if failed:
        print(f"\nnot run: {', '.join(failed)}", flush=True)
    return 1 if failed else 0


if __name__ == "__main__":
    if len(sys.argv) < 2:
        raise SystemExit(__doc__.splitlines()[0])
    sys.exit(main(sys.argv[1:]))
