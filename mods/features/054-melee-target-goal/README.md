# Experimental target-horde goal reservation exception

Unshipped diagnostic variant. The original target-goal placement exception
did not fix AC. Version 10 disabled both that exception and the 053 retry,
then added the attack-view goal-reservation rule documented in
`../055-ac-attack-view/README.md`. It includes all 052 diagnostics. Build every
shipped feature except 051, plus 054. Do not stack 051–055. Startup identifies
`054-melee-target-goal-v11`, `retry_enabled:0`, `target_goal_enabled:1` and
`view_goal_enabled:1`; the target-goal hook observes but no longer overrides.

Version 6 records three diagnostic events around member target acquisition:
`target_acquire_enter`, `target_acquire_selected`, and `target_acquire_dispatch`.
They record whether a phase-3 member selects a candidate and reaches the final
virtual dispatch. They do not change the reservation exception or attack orders.
The first diagnostic build crashed when the selection was null; version 4 logs
that normal null result without dereferencing it.
Version 5 also records the nearby candidate ID, resolved Object, enemy-filter
pass, and final selection flag. These events identify where the candidate is
lost; they do not alter any filter.
Version 8 records the earlier nearby-object search and raw member/candidate
position bits, because version 5 showed that the later search omitted all four
structure-attacking Soldiers.
Version 6's first-search hook replaced an instruction entered by a native
branch and crashed. The hook now sits at the next branch-safe instruction; the
image test checks direct branches into every acquisition hook span.
Version 8 also records horde-member positions in the periodic snapshots so
the two attack-view searches can be compared with actual unit separation.

Version 9 made empty-position attack-view cells expose a goal-reservation ID
when its owner belonged to an enemy horde in the normal structure-attack state.
All four previously protected Soldiers received damage in the replay, though
the old retry and placement exceptions were still enabled. Version 10 disabled
both old experiments. Uruks then damaged Soldiers 616–619 starting at frames
461, 461, 463, and 465. Its capture reached frame 1051 with zero dropped
records. Version 11 compiles the same rule from the shared source used by 055;
its command, damage, target-dispatch and view-override records match version 10
through frame 800, including damage to all four previously protected Soldiers.
The version 11 capture reached frame 883 with zero dropped records.

## Replay result

The completed 054v2 replay recorded 111 reservation overrides through frame 800,
starting at frame 452. Some previously failed member plans succeeded.

The eight additional Uruk hits during frames 543–579 all hit Soldier 615, who
was dueling Uruks. Soldiers 616–619 continued attacking the structure and
received zero Uruk damage during frames 446–588. The positioning improvement
therefore did not fix the observed protection of the structure attackers.

Evidence: `build/ac-offline-20260927/analysis-054-v2.md`. The capture had zero
dropped records; the compared events matched the 053 control before frame 452.

In the version 4 replay, all command, damage, planner and state-transition
records matched version 2 through frame 800. During frames 446–588, Uruks
reached the selection join 101 times. Ninety-eight selected no candidate; the
other three selected Soldier 615, who was already fighting. They never selected
Soldiers 616–619, who kept attacking the structure.

In version 5, the later search queried 338 objects for Uruks in frames 446–588:
three queries found Soldier 615, 287 found friendly Uruks, and 48 found the
slaughterhouse. It did not query Soldiers 616–619. The earlier search is the
remaining unobserved source of potential targets.

Version 7 found only four entries in that earlier search during the same
interval, all friendly Uruks. Neither search returned Soldiers 616–619. Its
command, damage, planner, state-transition and target-selection records matched
version 5 through frame 800, with zero dropped events.

## Evidence and hypothesis

The recorded AC replay contains member-planning failures where every queried
destination failed its legality check. Among the first rejected cells of 67
failed calls, 35 were empty Soldier goal reservations, 24 were occupied/reserved
by another Uruk and eight were slaughterhouse obstacles. This is a sample of one
rejection per failed call, not a count of every rejected cell.

The hypothesis is that an empty destination reserved by the attacked battalion
can unnecessarily block an approaching melee member while that battalion attacks
a structure. Occupied cells, unrelated reservations and obstacles still need
their original checks.

## Scope

The callback at retail RVA `0x003df445` runs after the physical-occupant and
terrain checks. It receives the original goal-reservation ID, current cell-info
pointer, and querying Object. It returns the original ID unless all guards pass:

- A member-planner point query is active and its member is the querying Object.
- The cell-info goal ID matches the original ID and position-unit ID is zero.
- The planner target is a horde, is an enemy of the querying member, and has a
  direct structure goal in the normal object-attack command state.
- The reservation owner resolves to an Object whose immediate container is that
  exact target horde.

For an eligible reservation only, the callback returns zero in EAX. The original
lookup at `0x003df44c` resolves zero to null and continues with the next cell.
The callback does not change cell memory or return success for the whole point
query. Other cells in the member footprint and the planner's subsequent line
checks continue normally.

`melee_plan` aggregates callback checks and override count plus the first/last
reservation IDs overridden. Those counts are independent of the diagnostic
record cap and are reset per planner call. No per-cell output is added, and the
behavior remains independent of logging failures and first-rejection sampling.
Version 2 adds per-guard rejection counts in `goal_rejections` and the first
observed target-kind result, target-machine state vtable/ID and attacking-object
byte (`-1` when its class is not the witnessed attack state), relationship enum,
and reservation-owner/container IDs. Each observed-value group has a presence
flag. Scope rejections count only while a planner is active; unrelated global
pathfinder calls are not assigned to a planner. The state-level correction is documented below.

## Identity evidence

Matched `ObjectOnContainedBy` at `0x001cb9f0` stores the container Object pointer
at member `+0x214`; the nearby-object check at `0x0023be60` independently compares
that field with the owning horde. Retail KindOf string-table entry `0x6c` names
`HORDE`. `GameLogic::findObjectByID` at `0x0009a510` supplies the read-only ID
lookup. The direct structure-goal filter uses 051's existing witnessed queries. Target
AI+0x30 -> machine+0x1c supplies the outer command state. It must have vtable
`0x0109a0c8`, state ID 50, and attacking-object byte +0x45 set. Retail
`AIStateMachine` construction at `0x00185a20` registers ID 50 using
`AIAttackState` construction at `0x0017c910`; forced attack ID 51 is excluded.
Follow ID 12 shares the vtable, so checking only the class is insufficient.
Version 1 incorrectly compared this outer state with the nested melee-state
vtables and produced no overrides. Version 2 corrects that level mismatch;
the nested attack machine is held at outer-state +0x28.
`ObjectGetRelationshipBody` at `0x001c7950` returns ENEMIES=0, NEUTRAL=1 and
ALLIES=2; the callback uses its actual enemy result, including native defection
and special-unit policy, rather than comparing player identities.
