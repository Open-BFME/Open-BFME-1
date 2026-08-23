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
score screen a tick later — so **a quitter writes no `end` record**. This is
the single most important consequence of the whole path, and it is why the
`end` record carries all eight slots rather than just the local verdict: a
quitter's or a crasher's fate is recoverable from any surviving machine.

Three machines do wait: a leaver whose game ended while still in the in-game
state (10 s fallback); a leaving packet router, which holds its own leave until
every peer reaches the frame its PLAYERLEAVE executed on; and the survivors of
a router that quit, who fall through to the DisconnectManager timeout. The
constants are 10 000 ms in `hasLeaveRequestTimedOut` (`0x00662E30`), 30 000 ms
in `Connection::doSend` (`0x00661F10`), and the INI-driven
`NetworkPlayerTimeoutTime`.

### Leave codes

| Value | Meaning | Seen |
|---|---|---|
| 0 | never left — played to the end, won or lost | yes |
| 1 | graceful quit | yes |
| 2 | voted out by the others | only on players who never finished loading |

Demolishing your own citadel is **not** a quit: it defeats you instantly with
`leave=0`, `defeated=1` and a real `defeatFrame`. It is the only way to make a
player lose on demand, and the resulting record is a genuine loss.
