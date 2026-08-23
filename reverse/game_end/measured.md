# Measured LAN result records

`measured.jsonl` — 68 records, one JSON object per line, `row` and `seat`
prepended. `tools/tests/test_game_records.py` holds each row against the
prediction `tools/tests/rows.py` declared before it ran.

`S`=start, `E`=end, `L@n`=leave on frame n. P1 hosts; P1/P2 team 1, P3/P4
team 2; a 1v1 is P1 against P3.

| Row | # | Shape | Event | P1 | P2 | P3 | P4 | End |
|---|---|---|---|---|---|---|---|---|
| `row01` | 1 | 1v1 | P3 demolishes | `S+E vic` | — | `S+E def` | — | 54 |
| `row02` | 2 | 1v1 | P3 quits | `S+E vic` | — | `S+L@59+E def` | — | 62 |
| `row03` | 3 | 1v1 | P3 SIGKILLed | `S+E vic` | — | `S` | — | 33 |
| `row04` | 4 | 1v1 | P3 SIGSTOPped | `S+E vic` | — | `S` | — | 33 |
| `row05` | 5 | 1v1 | P1 demolishes | `S+E def` | — | `S+E vic` | — | 48 |
| `row06` | 6 | 1v1 | host quits | `S+L@61+E def` | — | `S+E vic` | — | 62 |
| `row07` | 7 | 1v1 | host SIGKILLed | `S` | — | `S+E vic` | — | 25 |
| `row08` | 8 | 1v1 | host SIGSTOPped | `S` | — | `S+E vic` | — | 25 |
| `2v2-four-player` | 11 | 2v2 | P3+P4 demolish | `S+E vic` | `S+E vic` | `S+E def` | `S+E def` | 3757 |
| `row27-pre-fix` | 27 | 2v2 | P2 quits, P3+P4 demolish | `S+E vic` | `S` | `S+E def` | `S+E def` | 126 |
| `row27` | 27 | 2v2 | same, with the detour | `S+E vic` | `S+L@40` | `S+E def` | `S+E def` | 126 |
| `row30-pre-fix` | 30 | 2v2 | host quits, P3+P4 demolish | `S` | `S+E vic` | `S+E def` | `S+E def` | 103 |
| `row30` | 30 | 2v2 | same, with the detour | `S+L@44` | `S+E vic` | `S+E def` | `S+E def` | 108 |

## What these establish

**Crash and freeze are the same record** — rows 3/4 and 7/8 all yield `leave=2`,
host and joiner alike.

**Match shape, not seat, decides whether a quitter writes an `end`.** A 1v1 quit
ends the match, so the quitter records its own defeat one frame later (rows 2,
6). In a 2v2 whose team fights on, none (rows 27, 30).

**A quitter keeps its team's win** — row 27's P2 and row 30's host are both
`defeated=1` and `teamWon=1` in every survivor's record.

**The `-pre-fix` rows are the red evidence.** Pre-detour, a 2v2 quitter's file
held `start` alone, identical to row 3's SIGKILLed client. Neither can be
regenerated without reverting the exe.
