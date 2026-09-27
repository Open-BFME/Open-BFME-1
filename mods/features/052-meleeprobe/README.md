# AC melee diagnostic v3

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
The startup line identifies schema 3, probe version, process, run, enabled fix,
clock frequency and event limits. Loop heartbeats work in menus and during stalls; each includes
cumulative predicate-call, emitted-event and dropped-event counts. Captures are
buffered and flushed when the observed logic frame changes, or once a second if
it does not. A crash can lose the current frame's buffered combat records.

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

Delivered in-game chat emits `chat` with the local simulation frame and clock,
raw `text`, `displayed_text` (including the game's player-name prefix),
`sender_slot`, `recipient_mask` and `local_slot`. The recipient mask is recorded
as a mask; it is not assigned an assumed global/team channel. Each text field is
bounded to 512 UTF-16 code units, escaped as ASCII JSON, and has explicit
`_code_units` / `_truncated` fields. Chat bypasses the combat cap and is flushed
immediately, so a message such as `AC1 start`, `AC1 worked` or `AC2 failed` can mark
a trial even when combat events overflow. Muted or unaddressed normal messages do
not reach these display hooks. Lobby chat uses another path and is not captured.
The frame is when this client displayed the message, not a synchronized command
execution frame; compare both clients and allow for delivery delay.

`command_dispatch` records attempted move (0), stop/idle (5), attack (11), forced
attack (12), attack-position (14) and attack-move (15) dispatch, including owner,
machine, command/source numbers, target and raw coordinate bits; it does not
prove the command was accepted. Target IDs are resolved only for attack/forced
attack; other command records carry zero for that field. Human commands use
source 0, scripts 1, and AI 2. `state_transition` records actual old/new state
pointers, IDs and vtables when either side is the melee approach, wait or
path-wait class. The filter uses vtables because other classes reuse these IDs.
`damage_result` records victim/source IDs, body pointer, actual/clipped damage as
IEEE-754 bits, and `no_effect`, after the body dispatch site. A null body means no
body call occurred, and this hook is not reached when the victim's early skip bit
is set. Requested damage is omitted because its field identity is unresolved.

The cap is 256 combat event records per observed logic frame (or one-second
heartbeat interval while the frame is unchanged). Drops are explicit and make
that interval incomplete; use the small two-battalion reproduction to keep the
capture focused. All wait states, state transitions, command dispatches, planner aggregates and damage results
contribute to this cap; chat has a separate cumulative heartbeat count. The probe can change timing and is not a
benchmark. It performs no floating-point formatting or computations; hooks sit
before x87 work or after its results have been consumed.

Identity/layout evidence: `name_oracle.py --class Object --offset 0x74` reports
`m_id`, also witnessed by retail Object::setID at RVA `0x001BEC70`. `+0x7c` is the
builder ID and is not used as the object ID. `State+0x1c` is the machine pointer;
`StateMachine+0x1c` is the current State pointer; `+0x20` is the goal ObjectID,
resolved by retail `getGoalObject` at `0x000A1490`. The wait deadline `State+0x24`
is written at `0x00175A0C` / `0x00175B21` and compared at `0x00175B2F`.
The chat hooks at `0x00667238` / `0x006671A1` are the two display paths in retail
`ConnectionManager::processChat`; message `+0x0c` is sender slot, `+0x20` recipient
mask, and manager `+0x12028` local slot. The raw UnicodeString lives at message
`+0x1c`; its data starts eight bytes after the shared string header. Retail
`StringBase::getLength` at `0x0005e4f0` witnesses the header's 16-bit length at +4;
the probe uses the NUL-terminated text. Command dispatch at `0x00277780` receives
the command interface (AI+0x20) and AICommandParms. The transition hook at
`0x000a13d9` precedes the current-state pointer store. Retail machine construction
at `0x001812b0` witnesses melee approach/wait/path-wait vtables `0x0109a540`,
`0x01097b68`, `0x01097be0`. The damage hook at
`0x001d04b0` receives Object/DamageInfo; result fields `+0x50`, `+0x54`, `+0x58`
are witnessed by DamageInfo construction/assignment and InactiveBody.

At the not-ready deadline, `readiness_snapshot` adds a bounded snapshot of the
horde's cached target/deadline, raw flag bytes, up to 32 formation slots and up
to 32 contained members. Slot records expose raw phase, raw +0x10 flag, retry deadline and
raw +0x18 frame value; member records expose object ID, AI victim ID, state pointer/vtable/ID, goal,
path pointer and raw AI+0x1d8. These are separate arrays: their positions do not
establish a member-to-slot mapping. Vector range/stride validity, total slots,
truncation and broken member links are explicit. The snapshot makes no readiness
or other extra game-method calls. Ready hordes also emit it every 15 simulation
frames with `stage:"ready"`; timeout/retry captures use `before` / `after`. This
lets a stalled member be observed even while the horde reports ready. It runs only when interface vtable slots
+0x11c/+0x124 match retail thunks `0x0042be6d` / `0x0042b5b7`; unsupported
interfaces emit `interface_supported:0` without reading that layout.

Retail `HordeContain` readiness/update implementations at `0x002439f0` /
`0x002440e0` witness interface-relative cached target +0x100, expiry +0x104,
flag +0x119 and formation vector +0xf4/+0xf8 with stride 0x1c. The member list
sentinel is at interface-0xac; nodes contain next at +0 and Object pointer at +8.
Formation slot +0x10 is a raw planning flag; the retry deadline is +0x14. Slot
+0x18 is written for either an object-flag or attacking condition and remains raw.
The AI victim ID at +0x40 is witnessed by the getter at `0x002739d0`; AI path
+0x140 is witnessed by the layout oracle. AI+0x1d8 remains explicitly raw.

`melee_plan` aggregates one invocation of the member-position planner reached
from `HordeContain::updateMeleeTarget`. It includes member/target IDs, the actual
returned AL and retry-out DWORD, plus candidate, distance-pass, point-query,
point-rejection, passed-point, passed-line and chosen counters. Layer values are
recorded at the distance-pass hook. The first point-query rejection also records
the candidate's x/y/z IEEE-754 bits, without extra pathfinder calls. These
counters describe the visited branches; a false point query alone does not name
the blocking object or prove the cause of AC. Slot fields are captured before
the caller applies the planner result.

The entry hook at `0x00238d10` records stack arguments 0/2/5/6 (member, target,
retry-out pointer and raw last argument). Counters are at `0x0023900a`,
`0x002390ad`, `0x0023910f`, `0x0023926c`, `0x0023929b` and `0x002392aa`.
`0x0023910a` saves the point-query argument. Completion at `0x00244455` receives
AL, member and formation slot. A single static aggregate is reset at entry and
consumed at completion. `paired` and cumulative `overwritten_total` expose
unpaired or overwritten captures; retry-out memory is read only for a paired
completion. Planner hooks only read game memory and count visits. They share the
combat cap, and no planner decision or retry deadline is changed by 052.

The separate unshipped `053-melee-retry` variant includes this source with
`BFME_AC_RETRY=1`; 052 leaves that behavior disabled. Its startup reports the
variant and `retry_enabled`. At a not-ready timeout against a structure-attacking
target, the experiment sets the update flag +0x119 and invokes retail
`updateMeleeTarget`, then retail `isMeleeTargetReady` (whose return is **AL**, not
all of EAX). Only an actual true result extends the wait deadline by the same 15
frames as the retail ready branch. An unsupported interface or rejected structure
filter causes no mutation; `retry_attempt` records eligibility and whether it
ran. Failed readiness preserves the existing timeout. Before/after snapshots
and force-byte/readiness/deadline values document what happened.

The user reproduced AC with the 053 retry experiment, so it is not an AC fix.
The timeout-recovery hypothesis did not explain that reproduction; 052v3 is the
diagnostic control for the next capture. The successful recovery path subsequently reaches
the original update call too, so formation planning cadence is a regression risk
to check in normal melee, movement and building attacks. Both LAN seats must use
the same variant. Diagnostics remain useful if the experiment still fails.

`tools/tests/test_meleeprobe.py` verifies detour argument registers, preserved
GPRs/flags, relocated retail instructions and exact resume addresses. It does
not simulate gameplay. Native tests also exercise the actual bounded chat escape
helper on quotes, controls, Unicode and truncation. Set `BFME_MELEEPROBE_TEST_EXE` to test an already built
instrument; otherwise the fixture builds the standalone instrument.
