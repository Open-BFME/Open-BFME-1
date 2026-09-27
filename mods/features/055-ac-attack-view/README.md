# AC: make structure attackers visible to melee target search

This is the **only AC feature to build or ship**. It is included by
`python3 tools/modbuild.py --dist` in `mods/dist/lotrbfme.exe`. The old 051–054
feature directories were investigation stages, not alternatives for players;
they were removed after the live test. Their source, logs described in their
READMEs, and unsuccessful hypotheses remain available with `git show` (for
example, `git show 614cc45e41:mods/features/054-melee-target-goal/README.md`).

## What went wrong

The reported AC case was Gondor Soldiers attacking an Isengard mill while nearby
Isengard Uruks failed to attack them. In the saved replay, Soldiers 616–619 were
only 1–4 game units from the Uruks, yet neither of the two native nearby-object
searches handed those Soldiers to the melee target selector. The Soldiers were
there: their pathfinder cells held their **goal-reservation IDs** at cell-info
`+0x14`. The native attack-view searches looked at the cells' **position IDs**
(and, in one search, obstacle IDs), which were empty for these Soldiers. An
unseen candidate cannot be chosen, regardless of later melee or pathing logic.

The diagnostic replay narrowed this down before the patch. During frames
446–588, the later search made 338 object queries but none for Soldiers
616–619; the earlier search returned only four friendly Uruks. A separate
experiment that cleared certain goal reservations helped some movement plans
but still left all four Soldiers untouched. The older melee-predicate bypass
alone also failed in the user's earlier live test. Those observations are why
this feature changes *candidate visibility* rather than adding another retry
or relaxing collision checks.

## How the patch changes the search

The four attack-view hooks cover the two search routines at both candidate-read
sites. Each calls `ac_attack_view_goal` before the native search consumes a cell
ID. `src/view_goal.h` returns the original position ID except when **all** of
these conditions hold:

1. The cell's position ID and obstacle ID are empty, and it has a nonzero goal
   reservation ID different from the attacker itself.
2. `GameLogic::findObjectByID` resolves that reservation to an Object contained
   by a horde (`Object+0x214`, `KINDOF_HORDE`).
3. The horde has a structure as its direct attack goal and is in the normal
   object-attack state (state ID 50, expected vtable and attacking flag).
4. The game's own relationship function says the horde is an enemy of the
   searching attacker.

Only then does the callback return the goal-reservation ID as the candidate ID.
The **original game code** resolves the ID, applies its normal enemy and target
filters, suppresses duplicates, and keeps its 16-candidate limit. The callback
does not write to the pathfinder cell or change movement, terrain, or obstacle
checks. A cell with an obstacle ID stays on the native path; this guard was
added after an explicit diagnostic run measured obstacle IDs at all 840
candidate overrides in the AC replay.

The live-tested build also retained the earlier melee-predicate hooks, now in
`src/predicate_gate.h`. They temporarily set the predicate's existing skip bit
for a target with a structure-attack goal, then restore only the bit they set
immediately after the call. **These hooks alone did not fix AC.** We have not
removed them from the working combination because that narrower change has not
had a live two-client test. Keeping them here makes the exact shipped behavior
visible in one feature rather than hiding a dependency on a second feature.

## Why we believe it fixes this case

| Evidence | Result |
| --- | --- |
| Control replay | Soldiers 616–619 stayed absent from both searches and took no Uruk damage in the AC window. |
| Diagnostic build with attack-view rule and old retry/placement exceptions disabled | Uruks damaged all four Soldiers starting at frames 461–469. |
| Shared-source replay with the obstacle guard | 840 candidate overrides, 239 damage records and 47 target dispatches through frame 800; the compared command/damage/dispatch records matched the earlier successful diagnostic run. The capture had zero dropped records. |
| Live two-client test, 2026-09-27 | The player repeated the Gondor Soldiers versus Isengard Uruks and mill scenario and reported that AC no longer worked. |

The checked hook tests verify that the compiled binary detours the intended
retail instructions, preserves registers and native branches, and resumes the
original code. `test_ac_predicate_gate.py` also checks the retail predicate
call sites. These checks protect the patch layout; the replay and live test
supply the gameplay evidence.

## Impact and remaining limits

The guard confines the new candidate rule to empty position/obstacle cells
reserved by an enemy horde that is normally attacking a structure. Other cells
return their original ID. This is a **reasoned limit on possible side effects**,
not proof that every map, unit, command, or multiplayer situation is unchanged.
The patch intentionally makes previously invisible structure attackers
attackable, so fights involving them can change. The predicate hooks also
remain active in that situation. We have one reported successful live AC
retest and the replay comparisons above; we do not yet have a broad regression
matrix or a live test of a build with the predicate hooks removed.

Both multiplayer clients must run the same mod build. This feature has no chat
or combat logging hooks. The historical diagnostic variants can be recovered
from Git if a new failure requires another instrumented run.
