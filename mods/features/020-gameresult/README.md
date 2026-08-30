# 020-gameresult — match results, plus the desync flag retail hides

Shipped in `mods/dist`, and the feature the ladder already runs.

## It also reports something retail hides

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
