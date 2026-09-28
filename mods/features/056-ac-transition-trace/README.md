# 056-ac-transition-trace: logs why melee horde members stop attacking

**Players do not need this feature to fix AC.** Use
[`055-ac-attack-view`](../055-ac-attack-view/README.md) by itself for the
gameplay fix. This instrument records the decisions around melee horde members
stopping attacks. It does not change attack selection, orders, or state
transitions. It is opt-in and absent from `mods/dist/`.

To diagnose AC while running the gameplay fix:

```sh
python3 tools/modbuild.py --only 055-ac-attack-view \
  --only 056-ac-transition-trace -o build/ac-transition-trace.exe
```

Both multiplayer clients must run the same executable. Set `BFME_AC_PATH` in
each Wine process to a writable Windows path ending in `.jsonl`; give each
client its own path. Set `BFME_AC_RUN` and `BFME_AC_BUILD` to simple tokens
containing only letters, digits, hyphens, underscores, or dots. The build token
should be the executable's SHA-256. The trace fails visibly if these settings
are missing, a write fails, a per-frame event limit is reached, or its watched
member table fills. A `startup` record with matching build hashes and a
`heartbeat` from **each** client are required before testing.

The trace records command dispatches with object and target IDs, state changes,
member readiness snapshots, melee planner outcomes, damage, and delivered chat.
`reacquire_throttle` records a same-frame reacquisition refusal.
`reacquire_fail` records the owner's status word and field at `0x214` at the
other failure exit. If status bit `0x20` and that field are both set, that guard
refused reacquisition; otherwise the weapon lookup returned null (the machine
pointer has already been dereferenced on this path).
`engage_horde_range_refusal` records the branch where a horde member, already
outside weapon range, is prevented from computing its own path to the target.
`engage_enter_fail` records the unit and machine goal at the shared failure
exit, which can also be reached for other reasons.
The member snapshots include every discovered horde member's state, victim ID,
goal ID, and path pointer. Once discovered, a member's transitions and per-frame
changes are recorded even when the next state is idle or its victim clears
without a transition. Combat records are flushed at each frame;
delivered chat is flushed immediately. A `heartbeat` reports dropped events.

For a new test, compare when each rear member loses its victim or leaves its
attack state with the preceding command and decision. Record which player
clicked what and at which frame. Compare
each client's `command_dispatch`, `readiness_snapshot`, `member_change`, `state_transition`,
`melee_plan`, and `damage_result` records by frame and object ID. Do not infer
that the click caused the transition merely because they occurred together.

An offline replay of a captured two-client match reproduced a disengagement.
The `engage_horde_range_refusal` and `reacquire_fail` records identify
the two consecutive exits for an out-of-range member of a horde. A successful
diagnostic run has no dropped events, no write failure, and a trace for each
rear member through the disengagement being diagnosed. The trace alone does not prove a fix.
