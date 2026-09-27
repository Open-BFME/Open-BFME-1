# Experimental target-horde goal reservation exception

Unshipped. Replay testing leaves AC unresolved. This variant keeps the failed
053 retry experiment as its comparison baseline and adds one narrower
destination-check exception. It includes all 052 diagnostics. Build every shipped feature except
051, plus 054; both LAN clients must use the same executable. Do not stack 051,
052, 053 and 054. Startup identifies `054-melee-target-goal-v2`, `retry_enabled:1` and
`target_goal_enabled:1`.

## Replay result

The completed 054v2 replay recorded 111 reservation overrides through frame 800,
starting at frame 452. Some previously failed member plans succeeded.

The eight additional Uruk hits during frames 543–579 all hit Soldier 615, who
was dueling Uruks. Soldiers 616–619 continued attacking the structure and
received zero Uruk damage during frames 446–588. The positioning improvement
therefore did not fix the observed protection of the structure attackers.

Evidence: `build/ac-offline-20260927/analysis-054-v2.md`. The capture had zero
dropped records; the compared events matched the 053 control before frame 452.

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
