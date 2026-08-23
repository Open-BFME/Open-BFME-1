# Quitting, and where the result lands

## Where

`BFME_RESULT_PATH` if set, otherwise
`%APPDATA%\My Battle for Middle-earth Files\GameResult.jsonl` — beside
`Replays\`. Opened `"a"` and flushed per line, so a crash costs at most a torn
final line. One file per WINEPREFIX, which is what makes four clients on one
box separable.

**Known gap:** `getenv("APPDATA")` is not null-checked. If it is unset, the
result goes straight into `sprintf("%s\...")`, the CRT formats `(null)`,
`fopen` fails and the record is dropped with no diagnostic at all. Nothing in
the harness sets `APPDATA`, so this has never fired — but it is a silent
failure and should be a hard error instead.

## Format

JSONL. One `start` line per match, one `end` line per match that reaches an
end on that machine.

```
{"ev":"start","t":1787485862,"slot":0}
{"ev":"end","t":...,"slot":0,"frame":3757,"result":"victory",
 "observer":0,"desync":0,
 "slots":[{"leave":0,"leaveFrame":0,"defeatFrame":2583,
           "slotIndex":0,"namePtr":323928344,"name":"P3_T2"}, ...×8],
 "players":[{"player":143839956,"defeated":0,"teamWon":1}, ...×8]}
```

`result` is `victory`, `defeat` or `undecided`. **Reconcile on `teamWon`, not
`result`** — `result` is that machine's own verdict, `teamWon` is the team
outcome every machine agrees on. Empty slots carry `slotIndex":255`.

The `start` line exists so "crashed mid-match" is distinguishable from "never
played".

## Quitting

`Network::quitGame` — vtable VA `0x0111A968` slot `+0x78`, body `0x006822E0`.

BFME does not leave the way Zero Hour does. ZH sends one direct PLAYERLEAVE to
every peer and tears down. BFME sends **REQUESTPLAYERLEAVE** (command 7) to
every peer, and only the packet router turns it into the frame-synchronised
**PLAYERLEAVE** (10) / **DESTROYPLAYER** (11) pair the others execute.

**The leaver does not wait.** It posts `MSG_CLEAR_GAME_DATA` and is on the
score screen a tick later. Whether it still writes an `end` record depends on
whether the match outlives it:

* **The match ends at the quit** — a 1v1, or the last opponent leaving. The
  leaver is still in the in-game state and *does* write its own `end`. Row 2
  measured it: the quitter recorded `defeat`, `leave=1`, `leaveFrame=57`,
  `defeatFrame=58`, defeated one frame after leaving.
* **The match continues** — a 2v2 whose team fights on. No `end` is written and
  the file holds `start` alone, which is byte-identical to what a crashed client
  leaves.

That second case is why the `end` record carries all eight slots rather than
just the local verdict: a quitter's or a crasher's fate stays recoverable from
any surviving machine.

Three machines do wait: a leaver whose game ended while still in the in-game
state (10 s fallback); a leaving packet router, which holds its own leave until
every peer reaches the frame its PLAYERLEAVE executed on; and the survivors of
a router that quit, who fall through to the DisconnectManager timeout. The
constants are 10 000 ms in `hasLeaveRequestTimedOut` (`0x00662E30`), 30 000 ms
in `Connection::doSend` (`0x00661F10`), and the INI-driven
`NetworkPlayerTimeoutTime`.

### Leave codes

| Value | Meaning | Measured in |
|---|---|---|
| 0 | never left — played to the end, won or lost | every row; the survivor of rows 3, 4, 7 and 8 |
| 1 | graceful quit through the pause menu | row 2 — `leaveFrame=57`, `defeatFrame=58` |
| 2 | stopped answering and was dropped | rows 3, 4, 7 and 8 |

Demolishing your own citadel is **not** a quit: it defeats you instantly with
`leave=0`, `defeated=1` and a real `defeatFrame`. It is the only way to make a
player lose on demand, and the resulting record is a genuine loss.

**A crash and a freeze are the same record.** Row 3 SIGKILLs a joiner and row 4
SIGSTOPs one; rows 7 and 8 do the same two things to the host. The kernel closes
a killed client's sockets, so its peers see the connection go, while a frozen
one's sockets stay open and silent and its peers can only time it out — and the
survivors write the same thing in all four cases:

| Row | Who went | How | What the survivor recorded |
|---|---|---|---|
| 3 | joiner | SIGKILL | `leave=2 leaveFrame=32 defeatFrame=33 defeated=1 teamWon=0`, end frame 33 |
| 4 | joiner | SIGSTOP | `leave=2 leaveFrame=32 defeatFrame=33 defeated=1 teamWon=0`, end frame 33 |
| 7 | host | SIGKILL | `leave=2 leaveFrame=22 defeatFrame=25 defeated=1 teamWon=0`, end frame 25 |
| 8 | host | SIGSTOP | `leave=2 leaveFrame=24 defeatFrame=25 defeated=1 teamWon=0`, end frame 25 |

So `leave=2` means *stopped answering*, and nothing in the record says whether
the process died or hung, nor whether it was the host or a joiner. Losing the
host is not a special case for the survivor: it takes the match with it either
way, and the survivor still wins it.

This is also the first time `leave=2` has been measured on players who were
fully in the match. It had only ever been seen on players who never finished
loading, which is why it was read as "voted out by the others"; these four rows
show the same code on the ordinary disconnect path.

Neither a killed nor a frozen client writes an `end` of its own — all four rows
leave the missing machine holding nothing but its `start` line, which is exactly
what that line is for. **A resumed frozen client writes nothing either**:
measured in rows 4 and 8, forty-five seconds after `SIGCONT` both files still
held only `start`. Freezing therefore costs nothing beyond the obligation to
thaw the process before the row ends, since a client left stopped holds its wine
prefix open.
