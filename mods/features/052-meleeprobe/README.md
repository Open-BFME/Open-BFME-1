# AC melee diagnostic

This unshipped instrument replaces the four hooks owned by
`051-structure-melee-gate`. It includes that feature's source directly and runs
its existing setter/restorer unchanged. Build every shipped feature except 051,
plus 052, into a separate executable. Never stack 051 and 052; the builder checks
the retail instruction bytes and rejects an already patched site. `FEATURES`
and `mods/dist` are unchanged. Both LAN seats must use the same executable.

Set these variables in each Wine process before launch:

- `BFME_AC_PATH`: an existing writable directory plus the desired JSONL filename,
  using a Wine-visible path. The file is opened in append mode.
- `BFME_AC_RUN`: a distinct run/seat token, at most 128 letters, digits, dots,
  underscores or hyphens.
- `BFME_AC_BUILD`: the executable's SHA-256, supplied by the launcher. Startup
  records report this supplied identity; the payload does not hash itself.

A missing variable, failed open, write or flush produces a visible error dialog
and an OutputDebugString message. The fix continues to run after capture fails.
The startup line identifies the schema, process, run, enabled fix, clock frequency
and event limit. Loop heartbeats work in menus and during stalls; each includes
cumulative predicate-call, emitted-event and dropped-event counts. Captures are
buffered and flushed when the observed logic frame changes, or once a second if
it does not. A crash can lose the current frame's buffered records.

Each `enter_predicate` / `update_predicate` line pairs one call's original skip
byte, armed byte, actual returned AL, and restored byte. `owned` says whether 051
set the bit. A preexisting bit with no ownership cannot distinguish an accepted
filter from a rejected one; the record says so explicitly. Context records the
attacker, predicate target and machine goal pointers/IDs, current state pointer,
goal ID, wait deadline, target AI/machine/goal, and the real `isKindOf(7)` result
for the target's goal (`-1` means no goal). `target_raw_214` is an uninterpreted
pointer-sized value, never a claim about its relation to the target.

Events also mark wait-state entry/update, beginMelee/updateMeleeTarget call sites,
the update stealth failure, readiness branches, distance check and the return
`-2` paths. On-enter failure `raw_ebx` is 40 or 60 after the distance path; on the
predicate failure path it still holds the state pointer. Update failure following
`update_not_ready` can be compared with `wait_until`; predicate AL nonzero selects
the earlier predicate failure. Early exits and successful return paths are not
fully instrumented. No root cause or fix effectiveness is asserted by this probe.

The cap is 256 event records per observed logic frame (or one-second heartbeat
interval while the frame is unchanged). Drops are explicit and make that interval
incomplete; use the small two-battalion reproduction to keep the capture focused.
All wait states contribute to this cap. The probe can change timing and is not a
benchmark. It performs no floating-point formatting or computations; hooks sit
before x87 work or after its results have been consumed.

Identity/layout evidence: `name_oracle.py --class Object --offset 0x74` reports
`m_id`, also witnessed by retail Object::setID at RVA `0x001BEC70`. `+0x7c` is the
builder ID and is not used as the object ID. `State+0x1c` is the machine pointer;
`StateMachine+0x1c` is the current State pointer; `+0x20` is the goal ObjectID,
resolved by retail `getGoalObject` at `0x000A1490`. The wait deadline `State+0x24`
is written at `0x00175A0C` / `0x00175B21` and compared at `0x00175B2F`.

`tools/tests/test_meleeprobe.py` verifies detour argument registers, preserved
GPRs/flags, relocated retail instructions and exact resume addresses. It does
not simulate gameplay. Set `BFME_MELEEPROBE_TEST_EXE` to test an already built
instrument; otherwise the fixture builds the standalone instrument.
