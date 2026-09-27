# AC transition trace (diagnostic only)

This instrument records why members of a melee horde stop attacking. It does
not change attack selection, orders, or state transitions. It is opt-in and
absent from `mods/dist/`. To test the current partial AC patch with the trace:

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
The member snapshots include every discovered horde member's state, victim ID,
goal ID, and path pointer. Once discovered, a member's transitions and per-frame
changes are recorded even when the next state is idle or its victim clears
without a transition. Combat records are flushed at each frame;
delivered chat is flushed immediately. A `heartbeat` reports dropped events.

The question for the next live test is: **which rear Uruk first loses its
victim or leaves its attack state, and which command or decision precedes that
change?** The Uruk controller should issue no new order during the attempt.
Record the frame of the other player's click and what was clicked. Compare
each client's `command_dispatch`, `readiness_snapshot`, `member_change`, `state_transition`,
`melee_plan`, and `damage_result` records by frame and object ID. Do not infer
that the click caused the transition merely because they occurred together.

The old saved replay proves the target-discovery failure from the earlier test,
but it has not been shown to include the later behavior the requester identified
in the video. A live two-client reproduction is still needed. A successful
diagnostic run has no dropped events, no write failure, and a trace for each
rear member through the disengagement. It does not itself prove a fix.
