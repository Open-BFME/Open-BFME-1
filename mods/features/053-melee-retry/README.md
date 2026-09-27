# Experimental AC planning retry

**Manual result, 2026-09-27: did not fix AC.** Chat and damage logs confirmed
the Uruks stopped damaging Soldiers while the Soldiers damaged a slaughterhouse.
At frame 470 the forced retry ran, all ten member slots rescheduled to frame 490,
and every member still had no victim or goal. Native readiness remained false.
The horde reentered wait at frame 473 and reported ready during the continuing
damage gap (last Uruk damage at 445, next at 589). The cooldown and wait timeout
are therefore insufficient explanations; investigate member planning failures.
Keep this variant unshipped as the recorded experiment.

This unshipped variant adds one planning retry at an existing melee readiness
timeout. It includes the current 051 bypass and all [052 diagnostics](../052-meleeprobe/README.md).
Build every shipped feature except 051, plus 053. Both LAN clients must use
the same executable. Do not stack 051, 052 and 053.

## Evidence and hypothesis

During the first manual test, the user observed Uruks failing to attack Gondor
Soldiers that were attacking an Isengard mill. Both clients recorded identical combat events.
In one episode, Object 626 targeting Object 614 passed the patched predicate but
remained not ready during frames 596–610, then failed at its deadline, frame 610.
The capture had no annotations proving that episode was the successful AC attempt.

Retail member planning can schedule another attempt 20 frames later on failure
(`0x002393B0`), while the horde wait state expires after 15 frames without
readiness (`0x00175B26`). `updateMeleeTarget` skips a future retry deadline unless
its existing one-call force flag at interface `+0x119` is set (`0x002442F6`).
The hypothesis is that this cooldown prevents useful replanning before the wait
state fails. The first capture did not record member cooldowns, so this remains
an experiment.

## Change

At the original timeout, and only for a target passing 051's structure-goal
filter, set the existing force flag and call ordinary `updateMeleeTarget` once.
Then call ordinary `isMeleeTargetReady`. A true result refreshes the original
15-frame deadline; a false result leaves the original failure in place.
The interface's two virtual method pointers must match the witnessed retail
HordeContain implementations before reading or changing its fields.

This preserves the planner's target, weapon and path eligibility checks.
Recovery can cause a second ordinary update in the same frame, allowing more
members to be processed that frame; damage cadence needs an in-game check.
No result from compilation or detour tests establishes that AC is fixed.

## Next manual test

Use global in-game chat to mark `AC start`, `AC succeeded`, or `AC failed`.
Reproduce Gondor Soldiers attacking an Isengard mill while Uruks attack them.
Also check ordinary unit fights, moving targets, stop orders and unreachable
targets. Look for positive damage against the Soldiers and compare with 052's
control build. Chat, commands, transitions, timeout snapshots, retry outcomes
and damage records share frame numbers; chat arrival frames may differ by client.
