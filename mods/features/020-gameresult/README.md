# 020-gameresult: match results, plus the desync flag retail hides

Shipped in `mods/dist`; the BFME ladder reused its win-detection findings in
its own tools. Each client
writes one JSON line per match event, including the engine's own desync flag,
which retail detects but never reports.

## Where

`BFME_RESULT_PATH` if set, else
`%APPDATA%\My Battle for Middle-earth Files\GameResult.jsonl`, one file per Wine
prefix. The file is opened for append and flushed per line, so a crash costs at
most a torn last line. If `APPDATA` is unset, the open fails and the record is
dropped silently.

## Format

One `start` per match, one `leave` if this machine walked out mid-game, and one
`end` if the match resolved here:

```
{"ev":"start","t":1787485862,"slot":0}
{"ev":"leave","t":1787507086,"slot":1,"frame":40}
{"ev":"end","t":...,"slot":0,"frame":3757,"result":"victory","observer":0,"desync":0,
 "slots":[{"leave":0,"leaveFrame":0,"defeatFrame":2583,"slotIndex":0,
           "namePtr":323928344,"name":"P3_T2"}, ...x8],
 "players":[{"player":143839956,"defeated":0,"teamWon":1}, ...x8]}
```

* Reconcile on `teamWon`, not `result`: `result` is one machine's verdict.
* Empty slots carry `slotIndex:255`.
* A `leave` frame is when the quit request was sent; survivors record the
  router's PLAYERLEAVE a frame or two later.
* A player who quits writes its own `end` only if the match ends at its quit.
  Otherwise its file holds `start` and `leave` only, which is why every `end`
  carries all eight slots.

Leave codes: `0` played to the end, `1` graceful quit, `2` stopped answering and
was dropped. All three were observed in test matches. Demolishing your own
citadel is a defeat (`leave=0`, `defeated=1`), not a quit. A crash and a freeze
give the same record: survivors log `leave=2`, and neither the crashed nor the
frozen client writes an `end`.

The `leave` line comes from `ConnectionManager::sendPlayerLeaveCommands`
(`0x00665C10`), not `Network::quitGame`, which never fired in a four-client
probe. It is gated on `TheVictoryConditions->m_endFrame == 0` because the same
entry fires when a player leaves a finished match.

## The desync flag

`desync` is read from `GameLogic+0x6C`, the engine's own divergence flag, which
retail sets during normal play. Retail writes a `CLIENT_DESYNC_*.txt` report
(RVA `0x00065470`) only when a command-line option sets `[0x12ED4E4]`, and a
normal launch passes none. On a plain launch, a test build known to desync
(`034-framedrain`, in git history) raised the flag on both seats from logic
frame 102, while four other captures of 877–1326 frames read zero.

**A desynced match has no single winner.** Each seat reports the outcome of its
own diverged game, so any record with `desync != 0` marks a match that should
not be rated. This needs no network change: the field is already in every record
the ladder collects.

## Build

`python3 tools/modbuild.py --dist` builds the bundle into `mods/dist/`.

## Limits

* How often the flag fires in real ladder matches is unmeasured; every clean
  test capture read zero.
* The desync rate does not test `033-retrytime`. An abandoned command freezes
  the receiving seat until the disconnect timers drop it, without two seats
  diverging, and that path does not raise this flag. The ladder's disconnect
  and drop rate, by player count and match length, would test that mechanism.
