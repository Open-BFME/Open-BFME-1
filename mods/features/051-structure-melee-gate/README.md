# 051-structure-melee-gate — unverified bypass hypothesis

This feature contains a patch hypothesis for melee attacks against a battalion
that is attacking a structure. The patch builds and its hook layout is checked;
its intended in-game effect has **not** been verified, and the reported attempt
did not fix the issue. The feature name describes the gate this attempt targeted;
the attempted gameplay result remains unverified.

Ships in `mods/dist/lotrbfme.exe`. `python3 tools/modbuild.py --dist` builds
that executable from every feature in `FEATURES`, and this one is on the list.

## Observed retail behavior

Melee hordes do not swing from the ordinary attack cycle. When the weapon is a
contact weapon and the template bit at `+0xD4` is `0x400000`, the machine built
at `0x001812B0` runs approach (`0xC9`) → horde wait (`0xCB`) → path wait
(`0xCC`). The swing is `updateMeleeTarget` (`0x002440E0`). The wait state is the
only thing that calls it, and only when the wait stays entered.

`bfmeMeleeHordeTargetInvalid` (`0x00175820`) is the gate. Its first instruction
that matters is:

```asm
0x00175830  test byte ptr [esi+0x344], 1
0x00175837  jne  0x001758B7          ; return 0 — not invalid
```

`esi` is the target. Bit 0 of the byte at `Object+0x344` means "do not apply
the facing test". Otherwise the function dots the target's facing with
`target - attacker`. A negative dot is "attacker is in front", and the function
returns 0. A non-negative dot is "attacker is behind or beside", and the
function then compares the target's current locomotor max speed times `0.25`
(`0x01083B6C`) with the float at locomotor `+0x3C`. Slow, and the target is
invalid.

Both `AIAttackMeleeHordeWaitState::onEnter` (`0x001758F0`) and `::update`
(`0x00175A80`) call that function and, when it returns non-zero, return `-2`.
`-2` is failure. The machine built at `0x001812B0` sends wait-failure to the
path-wait state, and path-wait-failure back to approach. `beginMelee`
(`0x00243EA0`) and `updateMeleeTarget` do not call the predicate at all, so
this loop never reaches a swing.

A battalion told to hit a building turns to face it and stays there. Anyone
behind it is looking at its back, the locomotor is the slow infantry one, and
the gate stays true for the whole order. Re-clicking attack restarts the same
loop. Moving first can put the attacker in front, the dot product passes, and
the wait is allowed to commit. That is the structure exploit.

Tapping stop while running does not hold this condition. The stop flag at
`AIUpdate+0x33A` is read on the unit that received the stop — approach
`onEnter` at `0x001834E0` checks the chaser, not the target. A runner's goal is
a move or an idle, not a building, so this feature leaves that chase alone.

Nothing on this path calls `isInMultiplayerGame`. The same bytes run in
skirmish. It shows up against a human because a human attack click sits in
that one loop. Skirmish AI reissues instead of camping the back of a horde.

## State return names

`AIAttackMeleeHordeWaitState_update.cpp` uses the engine values: success is
`-1`, failure is `-2`, and continue is `0`. The predicate and timeout exits
return `STATE_FAILURE`, which sends the horde machine to path-wait. The earlier
inverted labels were corrected without changing the matched retail bytes.

## Failed patch hypothesis and implementation shape

The hypothesis was that the predicate's bit 0 at `Object+0x344` could bypass
the facing test. The hook sets that bit for the duration of the two calls, and
only when the object whose facing is about to be tested is attacking a
structure, then puts the bit back before `test al`. This describes what the
patch attempts; it does not establish that this produces the desired gameplay
result.

The shim `cave.py` generates saves every register and puts them back. A hook
that cleared `al` itself would be undone before `test al` ran. Setting the bit
the predicate already honours leaves `al` as the call's own return value, which
is what the following `je` reads. The same reason `042-tracksfix` borrows
flush's list guard instead of adding a second one.

Two shapes that look simpler and are worse:

* Clearing `al` in the payload. The shim's `popad` restores it, so the `je`
  still sees the retail result.
* Changing `bfmeMeleeHordeTargetInvalid` for every caller. Approach `onEnter`
  uses the same predicate for a different decision: a target that is *not*
  invalid and is already melee-ready fails the approach and leaves the attack
  machine. Widening the predicate would drop orders that currently keep going.

The two call sites, and the five bytes that follow each of them (`add esp, 8` /
`test al`), which is where the bit is restored:

| Predicate call | register value passed to setter | restore hook |
|---|---|---|
| `onEnter` | `0x00175979`, `esi` | `0x0017597E` |
| `update` | `0x00175AF0`, `edi` | `0x00175AF5` |

"Attacking a structure" is the goal object of that target's state machine
(`AI` at `Object+0x204`, machine at `AI+0x30`, goal id at `StateMachine+0x20`,
resolved by `StateMachine::getGoalObject` at `0x000A1490`) being kind `7`.
Kind `7` is `KINDOF_STRUCTURE`: `TunnelTracker::updateNemesis` at `0x000F90D0`
tests structure, infantry and vehicle with 7, 8 and 9, and the path-wait state
pushes 7 for the same question. If the object in the register has no such goal,
the pointer at `Object+0x214` is checked once — that is the other object
`bfmeResolveMeleeTarget` (`0x001CB020`) will substitute when it is kind `0x6C`.

A runner, a unit tapping stop, and a unit whose goal is another unit are intended
to fail the patch's structure-goal filter. The byte-level checks below establish
hook placement and control-flow preservation only. They do not test target
selection, a melee swing, or the reported gameplay outcome.

## What the automated checks establish

`tools/tests/test_structure_melee_gate.py` checks that the feature is registered for
distribution, the payload has no unresolved runtime symbols, both retail call
sites target the predicate, the restore sites preserve the following test and
branch, and the installed detours enter the payload and resume at the expected
addresses. None of those checks exercises a match or verifies that the patch
changes the melee outcome.
