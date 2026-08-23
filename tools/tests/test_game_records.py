"""Property tests over the measured game-end records in reverse/game_end/measured/.

Each fixture directory is one row of the LAN result matrix, and every row is
declared in tools/gametest/rows.py before it is run. These hold the measurement
against that prediction: the machines that survived agree with each other, the
declared files appeared holding the declared record kinds, the survivors between
them name every player in the lobby and credit exactly one team, and neither
`desync` nor `observer` fired.

A failure is a finding about the engine, not a test to relax. A fixture with no
row, or a row whose measurement contradicts it, fails.
"""
import json
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
MEASURED = ROOT / "reverse" / "game_end" / "measured"

sys.path.insert(0, str(ROOT / "tools" / "gametest"))
import rows  # noqa: E402

SEAT_OF = {name: seat for seat, name in rows.NAMES.items()}
EMPTY_SLOT = 255

# What every machine that wrote an `end` record has to say identically. The
# per-slot tuple deliberately omits namePtr: it is a live address in the writing
# process and differs on every machine by construction.
AGREE = {
    "the frame the match ended on": lambda r: r["frame"],
    "the teamWon vector": lambda r: [p["teamWon"] for p in r["players"]],
    "each slot's leave/leaveFrame/defeatFrame":
        lambda r: [[s["leave"], s["leaveFrame"], s["defeatFrame"]] for s in r["slots"]],
}


def _fixture_dirs():
    assert MEASURED.is_dir(), (
        f"{MEASURED} is missing: the measured records are committed data, so a "
        f"run with nothing to check is a broken checkout, not a pass")
    found = sorted(d for d in MEASURED.iterdir() if d.is_dir())
    assert found, f"{MEASURED} holds no fixture directories"
    return found


def _read(path):
    lines = path.read_text(encoding="utf-8").splitlines()
    assert lines, f"{path}: empty record file"
    return [json.loads(line) for line in lines]


@pytest.mark.parametrize("directory", _fixture_dirs(), ids=lambda d: d.name)
def test_row_records_match_their_declaration(directory):
    row = rows.ROWS.get(directory.name)
    assert row is not None, (
        f"{directory} has no entry in tools/gametest/rows.py: a measured row with "
        f"no prediction is compared only against itself and proves nothing")
    seats = row["seats"]

    files = {path.stem: path for path in directory.glob("P*.jsonl")}
    assert set(files) == set(seats), (
        f"{directory.name}: machines {sorted(files)} wrote a file, the row declares "
        f"{sorted(seats)}")

    ends = {}
    for seat, path in sorted(files.items()):
        got = _read(path)
        want = seats[seat]["records"].split("+")
        assert [record["ev"] for record in got] == want, (
            f"{directory.name}/{path.name}: holds {[r['ev'] for r in got]}, the row "
            f"declares {want} for a seat that exits with {seats[seat]['exit']!r}")
        if got[-1]["ev"] == "end":
            ends[seat] = got[-1]

    assert (row["won"] is None) == (not ends), (
        f"{directory.name}: {len(ends)} end record(s) but the row declares winning "
        f"team {row['won']}; a winner needs a witness and a witness needs a winner")

    if ends:
        for seat, record in sorted(ends.items()):
            assert len(record["slots"]) == len(record["players"]) == 8, (
                f"{directory.name}/{seat}: {len(record['slots'])} slots and "
                f"{len(record['players'])} players, not the 8 of a lobby")

        for label, read in AGREE.items():
            seen = {seat: read(record) for seat, record in sorted(ends.items())}
            assert len({json.dumps(value) for value in seen.values()}) == 1, (
                f"{directory.name}: the machines disagree on {label}: "
                + "; ".join(f"{seat}={value}" for seat, value in seen.items()))

        named = {slot["name"] for record in ends.values() for slot in record["slots"]
                 if slot["slotIndex"] != EMPTY_SLOT}
        assert named == {rows.NAMES[seat] for seat in seats}, (
            f"{directory.name}: the surviving records between them name {sorted(named)}, "
            f"the lobby held {sorted(rows.NAMES[seat] for seat in seats)}")

        won = {rows.TEAMS[SEAT_OF[slot["name"]]]
               for record in ends.values()
               for slot, player in zip(record["slots"], record["players"])
               if slot["slotIndex"] != EMPTY_SLOT and player["teamWon"]}
        assert len(won) <= 1, (
            f"{directory.name}: teams {sorted(won)} both carry teamWon=1, so the "
            f"records describe two winning teams")
        assert won == {row["won"]}, (
            f"{directory.name}: the records credit team(s) {sorted(won)}, the row "
            f"declares team {row['won']}")

        for seat, record in sorted(ends.items()):
            assert record["desync"] == 0 and record["observer"] == 0, (
                f"{directory.name}/{seat}: desync={record['desync']} "
                f"observer={record['observer']}; neither has ever been non-zero, so "
                f"this row measured something no other row has")

    print(f"PASS {directory.name} (matrix row {row['matrix']}, {row['shape']}): "
          f"{len(files)} machine(s), {len(ends)} end record(s), "
          f"team {row['won']} won as declared")


def test_a_quitter_says_so_where_a_crash_cannot():
    """The gap the `leave` record closes, held against measured data on both sides.

    `row27-pre-fix` is row 27 played on the pre-detour exe: P2 quits while its
    team fights on, so the match never ends under it and VictoryConditions
    ::update never reaches its end path. Its file then holds exactly what row
    3's SIGKILLed client holds -- one `start` and nothing else -- and from the
    departing machine's own file the two events are indistinguishable.

    `row27` is the same row on the exe with the leave detour. Start alone now
    means crashed; start+leave means quit, and the leave record names the slot
    and the frame it left on.

    The other half of the gate -- that a player leaving a *completed* match
    writes no leave line -- is held by the declarations above: every seat that
    plays to the end declares `start+end`, so a detour that fired post-game
    would show up there as `start+end+leave`.
    """
    crashed = [record["ev"] for record in _read(MEASURED / "row03" / "P3.jsonl")]
    before = [record["ev"] for record in _read(MEASURED / "row27-pre-fix" / "P2.jsonl")]
    assert crashed == before == ["start"], (
        f"row27-pre-fix/P2 holds {before} and row03/P3 holds {crashed}; the red state "
        f"this fix is asserted against is that these are the same file shape")

    got = _read(MEASURED / "row27" / "P2.jsonl")
    assert [record["ev"] for record in got] == ["start", "leave"], (
        f"row27/P2 holds {[r['ev'] for r in got]}: a 2v2 quitter whose team fights on "
        f"is still indistinguishable from row03/P3's crashed client")
    start, leave = got
    assert leave["slot"] == start["slot"], (
        f"row27/P2 left as slot {leave['slot']} but started as {start['slot']}")
    assert leave["frame"] > 0, (
        f"row27/P2 left on frame {leave['frame']}; a quit inside a running match "
        f"cannot be frame 0")
