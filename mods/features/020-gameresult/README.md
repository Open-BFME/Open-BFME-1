# 020-gameresult — match results, plus the desync flag retail hides

Shipped in `mods/dist`, and the feature the ladder already runs. This file is
the whole of it: where the records land, what quitting actually does to them,
and the divergence flag stock BFME detects and tells nobody about.

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

## The desync flag

Every `end` record carries a `desync` field, read from `GameLogic+0x6C`:

```json
{"ev":"end", "frame":3757, "result":"victory", "desync":0, ...}
```

That byte is the engine's own divergence flag, and retail sets it during normal
play with no special switches. What retail does **not** do is tell anybody. The
routine that writes a `CLIENT_DESYNC_*.txt` report (RVA `0x00065470`) is gated
on `[0x12ED4E4]`, which is set only by a command-line option handler
(`0x00461470`, which also ORs `0x1000` into the option word at `0x012A6FA0`).
A normal launch passes no such switch, so a retail client detects the
divergence, records it internally, and writes no report.

Confirmed by positive control rather than by reading alone: the refuted
`034-framedrain` arm raised this flag on both seats from logic frame 102 on a
plain launch, while four other captures of 877–1326 frames each read zero.

## Why the ladder should care

**A desynced match has no single winner.** Once seats diverge they are
simulating different games, so each reports the outcome of *its own* game.
Whichever seat's record the ladder happens to ingest decides the result, and the
other seat's record may disagree — silently, with nothing anywhere marking the
match as suspect.

This field is the mark. `desync != 0` on any seat's record means that match's
result should not be rated. Retail cannot offer that signal at all; a client
running this build can, and it costs nothing to check because the field is
already in every record the ladder collects.

**This is independent of everything else in this repository.** It needs no
network change, no `031-earlysend`, no `033-retrytime` — the field has been in
the records the ladder is already ingesting.

## What is not established

How often it fires in real ladder matches. Every clean capture on the rig reads
zero, and the only non-zero came from a deliberately broken build.

**An earlier revision of this file proposed asking the ladder to count
`desync != 0` as a test of `033-retrytime`'s mechanism. That was wrong and is
withdrawn.** Tracing the abandonment through the exe (see
`mods/features/033-retrytime`, "What an abandoned command actually does") shows
it never produces two seats simulating different games: the receiving seat's
frame is short one command, nothing in BFME can complete it, and the seat freezes
until the disconnect timers drop it. That path does not raise this flag. The
quantity that would test the mechanism is the ladder's **disconnect / drop rate**
bucketed by player count and match length, not its desync rate.

**The field is still worth what this file claims for it** — it just tests a
different thing. `desync != 0` marks a match whose result should not be rated,
and it is already present in every record the ladder collects. That value does
not depend on `033` or on any network change. Its rate in real matches remains
unmeasured, and a count across existing records is still worth having for its own
sake; it simply is not a test of the retransmission mechanism.
