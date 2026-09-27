# Experimental partial AC patch

**AC is still reproducible.** This patch improved one part of the reported
attack-cancel behavior, but the requester reviewing the live-test video saw
rear Uruks give up when the player clicked the target again. It is opt-in for
investigation and is **not** in `mods/dist/lotrbfme.exe`. This repository does
not control Arena deployment; Arena's reported package includes only the
network-delay fix. Build this patch separately with
`python3 tools/modbuild.py --only 055-ac-attack-view -o build/ac-test.exe`.
Both players in a multiplayer test must use the same executable.

## The failure this patch addresses

In a replay captured during an earlier two-client test, Gondor Soldiers
attacked an Isengard mill while nearby Isengard Uruks failed to keep attacking
them. The replay is a local diagnostic artifact, not a file included in this
repository. Inspection
of the replay showed that the game's two nearby-object searches did not return
four of those Soldiers as possible melee targets. The Soldiers occupied cells
whose **goal reservation IDs** identified them, but the searches read the cells'
**position IDs** and, at one site, **obstacle IDs**. Those IDs were empty for
these Soldiers, so the searches ignored their reservations. A target absent
from both search results cannot be selected by the later melee code.

This is a target-discovery failure. It does not explain every reason a unit may
cancel or abandon an attack, especially the rear-unit behavior seen after a
second click in the live-test video.

## What the code does

Four hooks in the two searches call `ac_attack_view_goal` before the original
game code reads a candidate ID. The callback in `src/view_goal.h` returns the
original ID unless the cell has **no position or obstacle ID** and its goal
reservation resolves to a member of an **enemy horde** that is directly
attacking a **structure** in the game's normal object-attack state (state ID
50). If every check passes, it returns the reservation ID so the original
search can consider that member. The game's later target filters and candidate
limit remain in place; the patch does not edit pathfinder cells.

The rule has **no faction, unit-type, or formation check**. It does not name
Gondor, Isengard, Soldiers, Uruks, or guard formation. It can expose a member
of any enemy horde meeting the cell, goal, and state conditions above. The
callback leaves targets outside a horde or outside that attack state unchanged.
Qualifying hordes on other maps or factions have not been gameplay-tested.

The tested executable also contained four earlier melee-predicate hooks in
`src/predicate_gate.h`. For a target or its containing horde with a structure
attack goal, they temporarily set an existing predicate-skip bit during a
retail melee check and restore only the bit they set afterward. Those hooks
alone failed to solve AC in an earlier live test, but we have not live-tested
this view change without them. Their independent contribution and possible
side effects are therefore unknown. Their scope is separate from the
candidate rule above.

## Evidence and limits

- In the recorded replay without the candidate rule, the four measured
  Soldiers were omitted from both searches and took no Uruk damage during the
  measured AC interval.
- In an instrumented replay of the same match, a build with the candidate rule
  and retained predicate hooks let Uruks acquire and damage all four Soldiers.
  This demonstrates improved target discovery for that encounter.
- The initial live two-client test appeared successful. The original requester
  subsequently reviewed its video and reported that **rear Uruks still cancel
  or give up immediately after a re-click**. We treat this as an unresolved
  part of AC, not a successful full fix.
- `tools/tests/test_ac_attack_view_hook.py` and
  `tools/tests/test_ac_predicate_gate.py` verify the compiled hooks and their
  return to the original game instructions. They do not establish general
  gameplay safety or prove the remaining cancellation is fixed.

The next investigation needs a recording or logs that identify each Uruk's
order, target, attack state and reason for leaving it at the re-click. The
current patch has no chat or combat logging. It remains opt-in until the
remaining behavior is explained and retested.
