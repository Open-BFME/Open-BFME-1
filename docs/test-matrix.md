# LAN result-recording test matrix

What the mod has to get right is not "who won" but "who won, as reconstructed
from whichever files still exist". Every row below is chosen because it changes
*which machines produce a file*, or *what the survivors say about the missing
ones* — not to enumerate combinations for their own sake.

## Setup

Team A = **P1** (always the host) and **P2**. Team B = **P3** and **P4**.
A 1v1 is P1 against P3, so the host/joiner asymmetry is still exercised.

P1 hosts in every row on purpose. The host runs the lobby, owns the disconnect
vote, and is the one whose departure the others have to survive, so "the host
lost" and "a joiner lost" are different code paths, not a relabelling.

## Exit modes

| Code | Action | Own record | Seen by others as |
|------|--------|-----------|-------------------|
| **D** | Demolish citadel | writes `defeat` | `leave=0`, `defeated=1`, real `defeatFrame` |
| **Q** | ESC → Exit (graceful quit) | **none** | `leave=1` + `leaveFrame` |
| **K** | `kill -9` (crash) | **none** | expected `leave=1` or `2` — **unmeasured** |
| **F** | `kill -STOP` (freeze/hang) | none while stopped | expected `leave=2` (voted out) — **unmeasured** |

**F is the important one and the only one that reaches the vote path in a live
match.** K closes the client's sockets as the kernel reaps it, so peers get an
immediate disconnect. F sends nothing at all — the peers just stop hearing from
it, which is the case the in-game timeouts (`NetworkDisconnectTime`,
`NetworkPlayerTimeoutTime`) actually exist for. `leave=2` has so far only been
observed on players who never finished loading, never on a live participant.

Two behaviours already established and assumed throughout: **a quitter does not
write its own end record** (unless the match happens to end within a frame of
the quit), and **demolishing produces a genuine defeat** with `leave=0`, not a
quit.

## Columns

Per-machine outcome: `win` / `loss` / `—` (no file written). The last column is
the one that matters — whether the surviving files identify the winner at all.

---

## 1v1 — P1 (host, A) vs P3 (B)

| # | Scenario | P1 | P3 | Probes |
|---|----------|----|----|--------|
| 1 | P3 demolishes | win | loss | baseline; both sides write, must agree |
| 2 | P3 quits | win | — | loser silent; winner must name the result |
| 3 | P3 killed | win | — | crash ≠ quit? what `leave` does P1 record |
| 4 | P3 frozen | win | — | the vote path; expect `leave=2` |
| 5 | P1 demolishes | loss | win | **host loses** — joiner must still record |
| 6 | P1 quits | — | win | host leaves; does the match resolve at all |
| 7 | P1 killed | — | win | host crash; joiner is the only witness |
| 8 | P1 frozen | — | win | host freeze; joiner must vote out the host |
| 9 | both quit together | — | — | expected zero files — reconciler must cope |
| 10 | P3 demolishes, P1 quits same instant | win? | loss | race: does the winner's record land |

## 2v2 — Team B loses (A wins)

Ordered pair = (first player out, second player out). P3 and P4 are both
joiners, so ordering between them is the least interesting axis; these rows fix
that and vary the modes.

| # | Scenario | P1 | P2 | P3 | P4 | Probes |
|---|----------|----|----|----|----|--------|
| 11 | (D,D) | win | win | loss | loss | **measured** — all four agree, frame 3757 |
| 12 | (Q,D) | win | win | — | loss | one silent loser, one real defeat |
| 13 | (D,Q) | win | win | loss | — | reverse order |
| 14 | (Q,Q) | win | win | — | — | whole team silent; does the match end |
| 15 | (K,D) | win | win | — | loss | crash then defeat |
| 16 | (K,K) | win | win | — | — | whole team crashes |
| 17 | (F,D) | win | win | — | loss | freeze then defeat; expect `leave=2` |
| 18 | (F,F) | win | win | — | — | both frozen — pure timeout resolution |
| 19 | (K,Q) | win | win | — | — | mixed silent exits |

## 2v2 — Team A loses (B wins), host involved

| # | Scenario | P1 | P2 | P3 | P4 | Probes |
|---|----------|----|----|----|----|--------|
| 20 | (D,D), P1 first | loss | loss | win | win | mirror of row 11 |
| 21 | (Q,D), P1 quits first | — | loss | win | win | **host leaves mid-match, game continues** |
| 22 | (D,Q), P2 quits last | loss | — | win | win | last member of a team quits |
| 23 | (K,D), P1 crashes first | — | loss | win | win | host crash with a teammate still in |
| 24 | (F,D), P1 frozen first | — | loss | win | win | host freeze; joiners must vote out the host |
| 25 | (Q,Q) | — | — | win | win | losing team fully silent |
| 26 | (K,K) | — | — | win | win | losing team fully gone |

## 2v2 — the winning team loses a member first

The case you called out originally: someone quits and their team still wins.
The question each row asks is whether the departed player is still credited
`teamWon=1` in the survivors' records.

| # | Scenario | P1 | P2 | P3 | P4 | Probes |
|---|----------|----|----|----|----|--------|
| 27 | P2 quits, then B both demolish | win | — | loss | loss | quitter credited as winner? |
| 28 | P2 killed, then B both demolish | win | — | loss | loss | crashed winner |
| 29 | P2 frozen, then B both demolish | win | — | loss | loss | frozen winner, `leave=2` + `teamWon=1` |
| 30 | **P1 (host) quits**, then B both demolish | — | win | loss | loss | host leaves and its team still wins |
| 31 | **P1 (host) killed**, then B both demolish | — | win | loss | loss | no host, no host record |
| ~~32~~ | ~~Both A quit, then B demolish~~ | | | | | **dropped — incoherent, see below** |

Row 32 was dropped. `processDestroyPlayerCommand` issues `MSG_SELF_DESTRUCT`
for a departing player, so quitting *is* defeat: once both of Team A quit,
Team B has already won and never gets to demolish. The row cannot happen.

The same reasoning kills the whole category. "Winners silent, losers recording"
is impossible by construction — to win you must remain, and remaining means you
are present to write the record. The only genuine zero-record case is everyone
leaving, which row 9 covers.

## Not covered, and why

* **Observer** — needs a fifth client joining as observer. `amIObserver` has
  never been non-zero. Worth one row once a 5-seat lobby is proven.
* **Desync** — `desync` has been `0` in every run. Forcing a genuine desync
  means diverging game state deliberately; there is no cheap handle for it, so
  it stays unmeasured rather than faked.

## Cost

Each row is a full seat-and-play cycle: roughly 6–8 minutes with
`lan4-netns.sh` (about 4 to seat, the rest to play and collect). All 32 rows is
therefore ~3–4 hours of machine time.

Suggested order, because later rows depend on semantics the earlier ones pin
down:

1. **Rows 3, 4, 7, 8** first — they define what K and F actually look like in a
   record. Every 2v2 row containing K or F is uninterpretable until then.
2. **Rows 2, 5, 6** — quit and host-loss semantics in the simplest shape.
3. **Rows 27, 30, 32** — the winner-lost-a-member cases, which is what the
   reconciler is actually for.
4. Everything else, which is then mostly confirmation.

Rows 1 and 11 are already measured and serve as the regression baseline.
