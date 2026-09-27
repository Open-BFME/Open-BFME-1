# Experimental AC fix

This feature addresses two reasons melee horde members stop attacking an enemy
horde while that enemy attacks a structure. It remains opt-in and is absent from
`mods/dist/lotrbfme.exe`. Build it with
`python3 tools/modbuild.py --only 055-ac-attack-view -o build/ac-test.exe`.
Both players in a multiplayer match must use the same executable.

## What failed

In a recorded match, Gondor Soldiers attacked an Isengard mill while nearby
Isengard Uruks fought them. The original game sometimes omitted Soldiers from
the Uruks' melee target search: the Soldiers occupied pathfinder cells by
**goal reservation ID**, while the search read **position ID** or **obstacle
ID**. The search could not choose a Soldier it had never found.

Other Uruks did find a Soldier and received an attack command, but stopped when
that Soldier moved out of weapon range. At frame 474 of the diagnostic replay,
Uruk 619 left its melee engage state after the game's horde-member check
refused to compute an individual path. Its next state refused reacquisition
because the Uruk still belonged to a horde. The Uruk returned to idle although
its horde retained an attack order. This sequence also occurred for other
members. The trace that identified these exits is in the separate
[`056-ac-transition-trace`](../056-ac-transition-trace/README.md) feature.

## What the code changes

The target-search hooks expose a goal reservation to the original search only
when the cell has no position or obstacle ID, the reserved object belongs to
an enemy horde actively attacking a structure, and the game's normal target
checks still apply. This rule does not depend on faction, unit type, or
formation.

The member-path hook runs only after the game's weapon-range check has failed.
It permits the original path calculation when the member's own horde is in its
attack state with an order against the target's horde, and the two hordes are
enemies. All other calls keep the game's original horde-member result. The
pathfinder and subsequent attack states remain the game's own code.

Four earlier melee-predicate hooks are retained because the tested target-view
build included them. Those hooks temporarily set an existing predicate-skip
bit for a target with a structure-attack goal, then restore only the bit they
set. Their independent contribution has not been established.

## Evidence and limits

The same multiplayer replay was run offline with and without the member-path
hook. The baseline had four of ten Uruks actively attacking at frame 500 and
55 hits on Soldiers during frames 456–623. With the hook, all ten were
actively attacking at frame 500 and the trace recorded 82 hits. Both runs
recorded 61 hits on the mill and zero dropped trace events. A broad diagnostic
bypass and the conditional hook produced identical command, damage, and member
state records for frames 400–623. The replay is a local diagnostic artifact;
it is not included in this repository.

The compiled-hook tests verify the detours and their return to the original
instructions. The replay demonstrates this encounter, not every map, unit, or
formation. Allowing an ordered horde member to path independently may change
formation movement in other horde-versus-horde fights. A live two-client test
of this exact build and broader combat tests are required before shipping it.
