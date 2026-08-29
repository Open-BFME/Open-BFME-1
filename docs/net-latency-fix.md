# Fixing BFME 1's off-host input delay

`031-earlysend`. ~106 bytes in a code cave. Ships **with** `033-retrytime`.

## The problem

All game logic runs at a compiled-in 5 Hz. Retail drains the outbound command
list only from `Network::update`, on a logic tick — so a guest's command waits up
to a 200 ms quantum before it even leaves the machine. The host pays nothing: it
stamps and executes inside the same tick that wrapped the command.

## The fix

A detour at RVA `0x0006BA44`, immediately before the engine's own
`liteupdate(FALSE)`, calling `Network::getCommandsFromCommandList`. Purely
additive — the retail flush still runs and finds the list empty. It does not
touch the 5 Hz quantum, the frame ceiling, or GameLogic's cadence.

## What it does, measured

Two mechanical results, both deterministic and present in every capture:

* **Hold removed.** Time from a command being created to leaving the machine:
  retail 68–160 ms (median ~95, bounded by one quantum); earlysend **0.1 ms**.
  Zero overlap, on selections and on real build orders alike.
* **Sends released from the tick.** 84–88% of game commands leave mid-period with
  the hook; **0.0–0.9%** without it.

## What it is worth

| condition | commands | effect |
|---|---|---|
| clean LAN | selections | **−152 ms** (n=3, tight) |
| clean LAN | build orders | **−80 ms**, p = 0.060 (n=5) |
| 150 ms/3% | selections | −69 ms at p90, disjoint at n=3 |
| 150 ms/3% | build orders | **indistinguishable** — floor is ~2000 ms |
| 150 ms/3% | on top of 033 | **+95 ms p50, +69 p90, +88 p95**, disjoint n=3 |

The benefit is a *translation* — a constant ~90 ms off every command — so it is
visible where the baseline is quiet and invisible where it is not. Under loss the
floor is freezes. **Its effect is only measurable once `033` removes them**,
which is why the pair is the shipping unit.

## Cost

+21% datagrams (9.90–10.70 → 12.96–13.02 /s). Each extra datagram costs one
retry interval if lost — expensive at 2000 ms, negligible at 400. That is the
whole reason it must not ship alone.

## Two corrections worth keeping

**The original metric was wrong.** `send→run` starts its clock at the moment this
fix moves, crediting retail with a free ~90 ms. It made earlysend look 514 ms
*worse* at p95. Anchor to command creation, and validate with the held column:
an arm that sends immediately must read ~0, one that waits must read half a
quantum. Both reproduce in every capture.

**A user-reported +90 ms did not reproduce.** On the same action (placing a farm
as a guest), on a controlled link, the fix is ~80 ms *faster*. Every mechanism
for the opposite sign was eliminated: no command splitting (0% of 22 builds; the
pair is [build, deselect]), hold fully removed, render rate untouched (the loop
spin-waits to a fixed period). Likely cross-session variance — retail's own
click-to-build varies 449→561 ms within one match.
