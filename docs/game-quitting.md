# Quitting, and where the result lands

## Where

`BFME_RESULT_PATH` if set, else
`%APPDATA%\My Battle for Middle-earth Files\GameResult.jsonl`. Opened `"a"` and
flushed per line, so a crash costs at most a torn last line. One file per
WINEPREFIX. **Gap:** `getenv("APPDATA")` is unchecked — unset, the CRT formats
`(null)`, `fopen` fails, the record is dropped silently.

## Format

JSONL: one `start` per match, one `leave` if this machine walked out mid-game,
one `end` if the match resolved here.

```
{"ev":"start","t":1787485862,"slot":0}
{"ev":"leave","t":1787507086,"slot":1,"frame":40}
{"ev":"end","t":...,"slot":0,"frame":3757,"result":"victory","observer":0,"desync":0,
 "slots":[{"leave":0,"leaveFrame":0,"defeatFrame":2583,"slotIndex":0,
           "namePtr":323928344,"name":"P3_T2"}, ...x8],
 "players":[{"player":143839956,"defeated":0,"teamWon":1}, ...x8]}
```

**Reconcile on `teamWon`, not `result`**: `result` is one machine's verdict.
Empty slots carry `slotIndex:255`. A `leave` frame is when the request was
*sent*; survivors log when the router's PLAYERLEAVE executed, a frame or two
later (row 27: 40 against 42).

## Quitting

BFME sends **REQUESTPLAYERLEAVE** (7) to every peer; only the packet router
turns it into the frame-synchronised **PLAYERLEAVE** (10) / **DESTROYPLAYER**
(11) pair. The leaver does not wait — it posts `MSG_CLEAR_GAME_DATA` and is on
the score screen a tick later. It writes its own `end` only when the match ends
at its quit: in a 1v1, row 2 measured `defeat`, `leave=1`, `leaveFrame=57`,
`defeatFrame=58`. When its team fights on, the file holds `start` + `leave` and
no more. That is why every `end` carries all eight slots: a departed player's
fate lives only in the survivors' files.

The `leave` line comes from `ConnectionManager::sendPlayerLeaveCommands`
(`0x00665C10`) — **not** `Network::quitGame` (`0x006822E0`), which a four-client
probe recorded firing zero times. It is gated on
`TheVictoryConditions->m_endFrame == 0` (`0x012F079C`, `+0x98`), because the
same entry fires when a player leaves a *finished* match.

## Leave codes

| Value | Meaning | Measured in |
|---|---|---|
| 0 | never left; played to the end | every row |
| 1 | graceful quit | rows 2, 6, 27, 30 |
| 2 | stopped answering, dropped | rows 3, 4, 7, 8 |

Demolishing your citadel is **not** a quit: `leave=0`, `defeated=1`, a real
`defeatFrame` — a genuine loss on demand.

**A crash and a freeze are the same record.** SIGKILL closes the client's
sockets so peers see the connection go; SIGSTOP leaves them open and silent so
peers can only time it out. The survivor records `leave=2` either way, host or
joiner, with a defeat frame one to three frames later. Neither writes an `end`,
and a resumed frozen client still writes nothing 45 s after `SIGCONT`.
