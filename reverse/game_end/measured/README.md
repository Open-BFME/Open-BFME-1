# Measured game-end records

One directory per row of the LAN result matrix, one `P<n>.jsonl` per machine
that took part — the file that client wrote for itself, copied verbatim off its
own WINEPREFIX. `docs/game-quitting.md` describes the record format.

Every row is declared in `tools/gametest/rows.py` **before** it is run, and
`tools/tests/test_game_records.py` holds these files against that declaration:
the survivors must agree with each other, the declared files must exist holding
the declared record kinds, they must between them name every player in the lobby
and credit exactly one team, and `desync`/`observer` must be 0. A contradiction
is a finding about the engine, not a test to relax.

Seating is fixed by the rig: **P1 always hosts**, P1+P2 are team 1, P3+P4 team 2,
and a 1v1 is P1 against P3 so the host/joiner asymmetry survives the smaller
shape. Run a row with `python3 tools/gametest/run_row.py <row-id>`, which
installs `overlay/dist/lotrbfme.exe` before seating — every row here is a
measurement of the shipped artifact.

## How a client leaves

| Code | Action | Its own file | Seen by the others as |
|---|---|---|---|
| **D** | demolish citadel | `start` + `end` (`defeat`) | `leave=0`, `defeated=1`, a real `defeatFrame` |
| **Q** | ESC → Exit | `start` + `leave`, plus `end` if the match ends at the quit | `leave=1` + `leaveFrame` |
| **K** | `kill -9` | `start` alone — it is killed before it can write more | `leave=2` |
| **F** | `kill -STOP` | `start` alone | `leave=2` — identical to K |

## The rows measured so far

`S` = `start`, `L` = `leave` (with the frame it was written on), `E` = `end`
(with that machine's own verdict). A machine that wrote no `end` has no verdict
of its own; the survivors' records carry its fate.

| fixture | row | shape | what the players did | P1 | P2 | P3 | P4 | end |
|---|---|---|---|---|---|---|---|---|
| `row01` | 1 | 1v1 | P3 demolishes | `S+E vic` | — | `S+E def` | — | 54 |
| `row02` | 2 | 1v1 | P3 quits | `S+E vic` | — | `S+L@59+E def` | — | 62 |
| `row03` | 3 | 1v1 | P3 SIGKILLed | `S+E vic` | — | `S` | — | 33 |
| `row04` | 4 | 1v1 | P3 SIGSTOPped | `S+E vic` | — | `S` | — | 33 |
| `row05` | 5 | 1v1 | P1 demolishes | `S+E def` | — | `S+E vic` | — | 48 |
| `row06` | 6 | 1v1 | P1 (host) quits | `S+L@61+E def` | — | `S+E vic` | — | 62 |
| `row07` | 7 | 1v1 | P1 (host) SIGKILLed | `S` | — | `S+E vic` | — | 25 |
| `row08` | 8 | 1v1 | P1 (host) SIGSTOPped | `S` | — | `S+E vic` | — | 25 |
| `2v2-four-player` | 11 | 2v2 | P3, then P4 demolish | `S+E vic` | `S+E vic` | `S+E def` | `S+E def` | 3757 |
| `row27-pre-fix` | 27 | 2v2 | P2 quits, then P3+P4 demolish | `S+E vic` | `S` | `S+E def` | `S+E def` | 126 |
| `row27` | 27 | 2v2 | the same row, on the exe with the detour | `S+E vic` | `S+L@40` | `S+E def` | `S+E def` | 126 |
| `row30-pre-fix` | 30 | 2v2 | P1 (host) quits, then P3+P4 demolish | `S` | `S+E vic` | `S+E def` | `S+E def` | 103 |
| `row30` | 30 | 2v2 | the same row, on the exe with the detour | `S+L@44` | `S+E vic` | `S+E def` | `S+E def` | 108 |

The two `-pre-fix` directories are the red evidence the `leave` record exists to
remove: on the pre-detour exe a quitter whose team fights on wrote `start` alone,
which is byte-identical to what `row03`'s SIGKILLed client wrote. They are kept
because `run_row.py` writes by row id and re-running the row overwrites it.

Three results worth knowing before reading any of these:

* **A quitter is credited with its team's win.** In `row30` the host left on
  frame 44 and all three survivors still record `teamWon=1` for it at frame 108.
* **A quit ends a 1v1**, so there the leaver is still in the in-game state when
  the end frame is set and writes an `end` of its own (`row02`, `row06`) — the
  host/joiner asymmetry row 6 exists to probe is not there.
* **A crash and a freeze are the same record** (`row03`/`row04`, `row07`/`row08`).

## Not measured

The remaining matrix rows are declared in `tools/gametest/rows.py` and simply
have not been run; each is a full seat-and-play cycle, roughly 6-8 minutes.
Row 32 was dropped as incoherent: `processDestroyPlayerCommand` issues
`MSG_SELF_DESTRUCT` for a departing player, so quitting *is* defeat and a team
that all quit has already lost before it can be demolished.

`observer` needs a fifth client joining as one and has never been non-zero.
`desync` has been 0 in every run; forcing a real one means diverging game state
deliberately, so it stays unmeasured rather than faked.
