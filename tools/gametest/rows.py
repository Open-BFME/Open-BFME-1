"""Declared outcomes for the LAN result-recording matrix.

One entry per row, written from the model of the engine *before* the row is run,
so tools/tests/test_game_records.py holds a measurement against a prediction
rather than against itself. run_row.py reads the same dict; a row is spelled
here and nowhere else.

A measurement that contradicts its row is a finding about the engine. Change a
prediction only in a commit that states why the original model was wrong.
"""

# The seating rig fixes both of these, so neither is per-row data: P1 always
# hosts, P1/P2 are team 1 and P3/P4 team 2, and a 1v1 is P1 against P3 so the
# host/joiner asymmetry survives the smaller shape.
TEAMS = {"P1": 1, "P2": 1, "P3": 2, "P4": 2}
NAMES = {"P1": "P1_T1", "P2": "P2_T1", "P3": "P3_T2", "P4": "P4_T2"}

# How a client leaves the match.
EXITS = {
    None: "plays to the end",
    "D": "demolish citadel",
    "Q": "ESC -> Exit, graceful quit",
    "K": "kill -9, crash",
    "F": "kill -STOP, freeze",
}

# Which records that client's own GameResult.jsonl ends up holding. Every client
# that entered the match writes `start`. `end` follows only on a machine that is
# still in the in-game state when the match resolves, which a quitter is only
# when the match ends at its own quit. `leave` comes from the
# ConnectionManager::sendPlayerLeaveCommands detour and so appears on exactly
# the seats that quit -- that is the whole point of it: without it a quitter's
# file is `start` alone, which is also what a crashed client leaves.
RECORDS = ("start", "start+end", "start+leave", "start+leave+end")

SPEC = ("exit", "order", "records")


def _row(matrix, shape, won, **seats):
    """One matrix row. Each seat is (exit mode, exit order, own records)."""
    assert won in (1, 2, None), f"row {matrix}: winning team {won!r}"
    assert len(seats) == {"1v1": 2, "2v2": 4}[shape], f"row {matrix}: {shape} with {len(seats)} seats"
    for seat, (exit_mode, order, records) in seats.items():
        assert seat in TEAMS, f"row {matrix}: unknown seat {seat}"
        assert exit_mode in EXITS, f"row {matrix} {seat}: unknown exit mode {exit_mode!r}"
        assert records in RECORDS, f"row {matrix} {seat}: unknown record pattern {records!r}"
        assert (order is None) == (exit_mode is None), \
            f"row {matrix} {seat}: exit {exit_mode!r} with order {order!r}"
    return {"matrix": matrix, "shape": shape, "won": won,
            "seats": {seat: dict(zip(SPEC, spec)) for seat, spec in seats.items()}}


STAY = (None, None, "start+end")

ROWS = {
    # Matrix row 11, measured before the rows were given ids, kept under the
    # directory name it landed as. There is deliberately no "row11".
    "2v2-four-player": _row(11, "2v2", won=1, P1=STAY, P2=STAY,
                            P3=("D", 1, "start+end"), P4=("D", 2, "start+end")),

    # 1v1 -- P1 (host, team 1) against P3 (team 2).
    "row01": _row(1, "1v1", won=1, P1=STAY, P3=("D", 1, "start+end")),
    # Measured, and the original "start" here was wrong against this file's own
    # rule: a 1v1 quit ends the match, so the leaver is still in the in-game
    # state when the end frame is set and writes an `end` like anyone else. The
    # entry had followed the per-row column of the matrix, which said the
    # quitter writes nothing and contradicted the exit-mode table beside it.
    # P3 records `defeat` with leave=1, leaveFrame=61, defeatFrame=62 --
    # defeated one frame after leaving -- and P1 records `victory`.
    # The `leave` lands BEFORE that `end`, which is measured rather than
    # predicted: the leave record is written where the leave command is
    # sent (frame 59) and the end record where VictoryConditions sees the match
    # resolve (frame 62), three frames later.
    "row02": _row(2, "1v1", won=1, P1=STAY, P3=("Q", 1, "start+leave+end")),
    "row03": _row(3, "1v1", won=1, P1=STAY, P3=("K", 1, "start")),
    "row04": _row(4, "1v1", won=1, P1=STAY, P3=("F", 1, "start")),
    "row05": _row(5, "1v1", won=2, P1=("D", 1, "start+end"), P3=STAY),
    # Measured, and "start" was wrong here for the same reason it was wrong for
    # row02: the shape decides, not the seat. A 1v1 quit ends the match whoever
    # does it, so the host is still in the in-game state when the end frame is
    # set and writes an `end` like the joiner did. P1 records `defeat` with
    # leave=1, leaveFrame=61, defeatFrame=62, and P3 records `victory`; both
    # machines agree on frame 62. Matrix row 6 asks "does the match resolve at
    # all" when the host leaves -- it does, identically to row 2, so the
    # host/joiner asymmetry this row exists to probe is not there. Its `leave`
    # lands before that `end`, at frame 61.
    "row06": _row(6, "1v1", won=2, P1=("Q", 1, "start+leave+end"), P3=STAY),
    "row07": _row(7, "1v1", won=2, P1=("K", 1, "start"), P3=STAY),
    "row08": _row(8, "1v1", won=2, P1=("F", 1, "start"), P3=STAY),
    "row09": _row(9, "1v1", won=None, P1=("Q", 1, "start+leave"), P3=("Q", 1, "start+leave")),
    "row10": _row(10, "1v1", won=1, P1=("Q", 1, "start+leave"), P3=("D", 1, "start+end")),

    # 2v2 -- team 2 loses.
    "row12": _row(12, "2v2", won=1, P1=STAY, P2=STAY,
                  P3=("Q", 1, "start+leave"), P4=("D", 2, "start+end")),
    "row13": _row(13, "2v2", won=1, P1=STAY, P2=STAY,
                  P3=("D", 1, "start+end"), P4=("Q", 2, "start+leave")),
    "row14": _row(14, "2v2", won=1, P1=STAY, P2=STAY,
                  P3=("Q", 1, "start+leave"), P4=("Q", 2, "start+leave")),
    "row15": _row(15, "2v2", won=1, P1=STAY, P2=STAY,
                  P3=("K", 1, "start"), P4=("D", 2, "start+end")),
    "row16": _row(16, "2v2", won=1, P1=STAY, P2=STAY,
                  P3=("K", 1, "start"), P4=("K", 2, "start")),
    "row17": _row(17, "2v2", won=1, P1=STAY, P2=STAY,
                  P3=("F", 1, "start"), P4=("D", 2, "start+end")),
    "row18": _row(18, "2v2", won=1, P1=STAY, P2=STAY,
                  P3=("F", 1, "start"), P4=("F", 2, "start")),
    "row19": _row(19, "2v2", won=1, P1=STAY, P2=STAY,
                  P3=("K", 1, "start"), P4=("Q", 2, "start+leave")),

    # 2v2 -- team 1 loses, so the host is one of the losers.
    "row20": _row(20, "2v2", won=2, P3=STAY, P4=STAY,
                  P1=("D", 1, "start+end"), P2=("D", 2, "start+end")),
    "row21": _row(21, "2v2", won=2, P3=STAY, P4=STAY,
                  P1=("Q", 1, "start+leave"), P2=("D", 2, "start+end")),
    "row22": _row(22, "2v2", won=2, P3=STAY, P4=STAY,
                  P1=("D", 1, "start+end"), P2=("Q", 2, "start+leave")),
    "row23": _row(23, "2v2", won=2, P3=STAY, P4=STAY,
                  P1=("K", 1, "start"), P2=("D", 2, "start+end")),
    "row24": _row(24, "2v2", won=2, P3=STAY, P4=STAY,
                  P1=("F", 1, "start"), P2=("D", 2, "start+end")),
    "row25": _row(25, "2v2", won=2, P3=STAY, P4=STAY,
                  P1=("Q", 1, "start+leave"), P2=("Q", 2, "start+leave")),
    "row26": _row(26, "2v2", won=2, P3=STAY, P4=STAY,
                  P1=("K", 1, "start"), P2=("K", 2, "start")),

    # 2v2 -- the winning team loses a member first, so the survivors have to
    # credit a player who is no longer there.
    "row27": _row(27, "2v2", won=1, P1=STAY, P2=("Q", 1, "start+leave"),
                  P3=("D", 2, "start+end"), P4=("D", 3, "start+end")),
    "row28": _row(28, "2v2", won=1, P1=STAY, P2=("K", 1, "start"),
                  P3=("D", 2, "start+end"), P4=("D", 3, "start+end")),
    "row29": _row(29, "2v2", won=1, P1=STAY, P2=("F", 1, "start"),
                  P3=("D", 2, "start+end"), P4=("D", 3, "start+end")),
    "row30": _row(30, "2v2", won=1, P2=STAY, P1=("Q", 1, "start+leave"),
                  P3=("D", 2, "start+end"), P4=("D", 3, "start+end")),
    "row31": _row(31, "2v2", won=1, P2=STAY, P1=("K", 1, "start"),
                  P3=("D", 2, "start+end"), P4=("D", 3, "start+end")),

    # Rows 27 and 30 as they measure BEFORE the leave detour. run_row.py writes
    # by row id, so re-running either row once the detour is in overwrites the
    # red evidence the fix is asserted against; these are the copies that
    # survive it, and these declarations are the pre-detour prediction,
    # unchanged from the rows they were taken from.
    "row27-pre-fix": _row(27, "2v2", won=1, P1=STAY, P2=("Q", 1, "start"),
                          P3=("D", 2, "start+end"), P4=("D", 3, "start+end")),
    "row30-pre-fix": _row(30, "2v2", won=1, P2=STAY, P1=("Q", 1, "start"),
                          P3=("D", 2, "start+end"), P4=("D", 3, "start+end")),
}
