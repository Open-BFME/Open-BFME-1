# BFME1 `GameLogic` phase update

This note describes retail BFME 1.03 code beginning at RVA `0x0038DA10`
(VA `0x0078DA10`). It is a semantic recovery of the phase dispatcher, not a
byte-exact reconstruction or a multiplayer fix.

The six substantial callees still surrounding this body are inventoried in
[`bfme1-update-dependency-map.md`](bfme1-update-dependency-map.md).

## Boundary and identity

The previously reported 2,094-byte boundary is wrong. As an exclusive end, RVA
`0x0038E23E` cuts off the final byte of `mov edx,[esp+0x28]`, which begins at
`0x0038E23B`; the next instruction begins at `0x0038E23F`. The function
continues through `ret 4` at `0x0038E25E`; alignment begins at `0x0038E261`.
The verified range is therefore:

| Item | Value | Status |
|---|---:|---|
| Entry RVA / VA | `0x0038DA10` / `0x0078DA10` | proven from the ILT target and caller |
| Exclusive end | `0x0038E261` | proven by complete instruction decoding and `ret 4` |
| Size | `0x851` = 2,129 bytes | proven |
| ILT thunk | RVA `0x0003A9C7` | exact five-byte thunk, already matched |
| Caller | `GameEngine::_bfme_updateNetworkAndLogic`, RVA `0x0006BAE0` | exact clean C++ already matched |
| Virtual slot | `GameLogic` slot `+0x20` (index 8) | call at `0x0006BB86`; vtable entries point to VA `0x0043A9C7` |
| ABI | virtual `thiscall`, one 32-bit phase argument | load at `0x0038DA47`; `ret 4` at `0x0038E25E` |
| Current ledger owner | none for the body; only its ILT thunk is claimed | checked in `reverse/functions.csv` |

The `reverse/symbols.csv` label `?update@GameLogic@@UAEXXZ` describes the old
parameterless Zero Hour signature. It cannot be the retail BFME ABI. Keep the
name as comparison evidence until the correct BFME declaration is recovered.

Two vtable images contain the thunk VA at slot `+0x20`: bases `0x010EB574` and
`0x0111CA5C`, with the entries at `0x010EB594` and `0x0111CA7C`. This establishes
the dispatch slot but does not by itself identify both concrete classes.

## Phase table

All addresses in the table are RVAs. “Update” on an unresolved singleton means
a virtual call through slot `+0x14`; it does not assert a more specific effect.

| Phase | Work performed | Direct state changes |
|---:|---|---|
| 1 | Runs the logic-debug-frame helper and the freeze gate; queries the network packet-router state; runs the phase-1 object special case; updates ScriptEngine, LuaScriptEngine (`0x012F060C`), TerrainLogic, and optional VictorySystem; creates periodic logic CRC messages; clears the optional `CRCParameterCheck`; updates StatsCollector and Recorder; consumes the command list; performs per-object interface work and the phase-1 object tail. | Records phase 1 at `GameLogic+0x168`; clears the accumulated RNG/pathfinding CRC diagnostic strings; may set `GameClient+0xC4` false on freeze or true after a completed phase; conditionally increments the simulation frame at `GameLogic+0x3C` exactly once near the end. |
| 2 | Updates PartitionManager and CollisionManager (`TheCollisionManager`, VA `0x012ED5C4`). CollisionManager's virtual update forwards to its owned collision-data object at `+0x0C`. It then walks all objects and calls the transform/frame recorder when object `+0x168` differs from the current simulation frame. | Records phase 2. CollisionManager brackets three collision-processing calls with its owned data's busy byte at `+0xC06D`. Does not increment the simulation frame. |
| 3 | Processes the first half of sleepy-update vector 0 (`GameLogic+0xC4`). Due entries may call their update module and receive a new wake frame. | Records phase 3; writes `GameLogic+0x100` around callbacks; updates entry wake frame `+0x14`; may change heap indices `+0x18/+0x1C` and move expired entries to `GameLogic+0xF4`. |
| 4 | Processes the second half of sleepy-update vector 0. | Same sleepy-entry changes as phase 3. It begins at `size/2`, complementing phase 3's stop at `size/2`. |
| 5 | Processes sleepy-update vectors 1 and 2, then updates AI. After the common deferred-owned-entry drain, it calls `GameLogic::processDestroyList` at body RVA `0x0038AE90`, drains ShroudManager's pending `PartitionData`, and follows TaintManager's empty update path; calls the empty `BuildAssistant::update` hook; and updates LargeGroupAudio, WeaponStore, LocomotorStore, VictoryConditions, ExperienceLevelSystem, and the embedded LivingWorld reinforcement-army store at `GameLogic+0x170` (direct thiscall to body RVA `0x00367810` via ILT `0x000159C9` at call-site RVA `0x0038E17B`; gated on the Display movie predicate and `GameLogic::isLivingWorld`). | Same sleepy-entry changes; destroys every object pending end-of-frame deletion and removes its update modules from the phase vectors; drains queued Shroud work; records phase 5. `TaintManager::update`, `BuildAssistant::update`, `WeaponStore::update`, and `LocomotorStore::update` change no state in BFME 1.03. No simulation-frame increment. |
| 6 | Processes sleepy-update vector 3. | Same sleepy-entry changes; records phase 6. No simulation-frame increment. |

The jump table at VA `0x0078E264` maps phase 3 and phase 4 to the common vector-0
case at `0x0038DEF1`, phase 5 to `0x0038DEFA`, and phase 6 to `0x0038DF06`.
The phase value remains live because the vector-0 loop splits its range at
`0x0038DF30` and `0x0038DF67`.

## Common control flow

Entry first maintains a reentrancy depth at `GameLogic+0x1A0`. When the old
value is zero, `0x0038DA3C` calls `setFPMode`; `0x0038DA4B` increments the depth.
Every return path decrements it (`0x0038DACF`, `0x0038DB25`, or
`0x0038E244`). This is proven counter behavior. Calling it a frame counter
would be wrong.

A source-shape probe also rules out a named local copy of this depth. Keeping
the value in a local made MSVC preserve it in a nonvolatile register, retained
an extra copy of `this`, and raised the local allocation from retail's `0x2C`
to `0x3C`. The retail instruction sequence loads the field into `eax`, tests
it, optionally resets FP mode, reloads the field, and increments it directly.

Only phase 1 enters the freeze test at `0x0038DA57`. After that gate, every
admitted phase resets the end of the deferred-owned-entry vector: the retail
self-range copy at `0x0038DAAE..0x0038DAFC` reduces to
`GameLogic+0x160 = GameLogic+0x15C`. Work during the phase may append entries.
The exact clean C++ callee at body RVA `0x0038A6F0`, called at `0x0038E10C` by
every normal phase, deletes those entries and restores an empty range. This
ordering explains the otherwise strange reset at entry.

If `GameLogic+0x11D` is set, phase 1 calls
`GameLogic::processCommandList()` at RVA `0x00383050`, sets
`GameClient+0xC4 = 1`, and returns. Other phases return without that call
(`0x0038DB02..0x0038DB3D`). This is a command-only transition path: the helper
dispatches every pending command and resets `TheCommandList`, while the rest of
the phase-1 simulation work is skipped.

On the normal path, phase 1 optionally calls the network virtual at slot
`+0x8C` (`0x0038DB40..0x0038DB57`). The return value is unused. All phases then
write their phase to `GameLogic+0x168`, save `GameLogic+0x6B`, set that byte to
one, and restore it in the epilogue. Zero Hour layout and the RAII-shaped code
support the name `m_isInUpdate`, while the save/set/restore behavior itself is
proven at `0x0038DB57..0x0038DB80` and `0x0038E23B..0x0038E251`.

Phase 1 owns the large front half through `0x0038DE83`. Phase 2 has its own
block at `0x0038DE89..0x0038DECF`. Phases 3–6 select sleepy queues at
`0x0038DED4..0x0038E0F4`. The shared drain follows. Phase 5 then runs its
post-simulation subsystem batch at `0x0038E116..0x0038E17F`. Every normal phase
passes the copy-protection check, but only phase 1 passes the final object walk
and simulation-frame increment.

These blocks are separate source conditionals, not one phase-1 `if` followed by
an `else if` chain. Retail retests the phase before CRC, before the optional
StatsCollector update, before Recorder and command-list consumption, and again
before phase 2. Modeling one large phase-1 branch removes those repeated tests
and changes the control-flow layout. The direct calls in this region also use
`thiscall`: the ScriptEngine debug/freeze helpers, Pathfinder queue processor,
CRCParameterCheck clear, StatsCollector update, GameLogic command dispatcher,
and the Object status/transform helpers are not cdecl shims or virtual calls.

The phase-2 object loop compares `Object+0x168` with the current frame at
`GameLogic+0x3C`. A mismatch calls the direct thiscall
`Object::bfmeRecordTransform(frame)` through ILT RVA `0x0002BB43`, passing that
current frame as its sole stack argument.

## Phase 5 pending-object destruction

The body at RVA `0x0038AE90..0x0038B046` is the 438-byte
`GameLogic::processDestroyList`. The 430-byte Ghidra inventory entry stops after
`pop edi` and omits the remaining epilogue; the following `INT3` establishes the
correct end. Its phase-5 call is at `0x0038E144`, and the exact GameLogic clear
routine at `0x0038D000` calls the same body through ILT `0x00015028`.

For each object in the STLport list at `GameLogic+0x104`, the function walks the
null-terminated behavior-module array at `Object+0x1F0`. Each behavior's update
interface is queried through virtual slot `+0x20`. A scheduled update has its
index and phase fields at `UpdateModule+0x18/+0x1C` reset to `-1`, then is
removed by swap-and-pop. Negative-phase entries come from the vector at
`GameLogic+0xF4`; phases 0 through 3 select the four vectors beginning at
`GameLogic+0xC4` with stride 12. When an entry moves, the function repairs the
moved module's phase and index fields.

The object is then removed from the AI pathfinding map, unlinked from the
GameLogic object list at `+0xA8/+0xAC`, erased from the ObjectID lookup hash at
`+0xB0`, and deleted through its scalar deleting destructor. Finally, the
pending-destruction list is cleared. Phase 5 is therefore the end-of-frame
object destruction phase, not an unnamed finish transition.

## Phase 1 ordering

The following order is instruction-level fact:

1. ScriptEngine's logic-debug-frame helper is called at `0x0038DA5D`.
2. TacticalView and ScriptEngine freeze predicates run at
   `0x0038DA62..0x0038DA90`.
3. A pending `MSG_CLEAR_GAME_DATA` (`0x1D`) is queried at `0x0038DA92`; when
   present, ScriptEngine is force-unfrozen at `0x0038DAA3`. Without it, the
   function sets `GameClient+0xC4 = 0` and returns at `0x0038DAC2`.
4. After the common entry bookkeeping, a frame-2-only object block runs at
   `0x0038DB83..0x0038DC06` under several global predicates. It walks
   `TheBfmeGameLogic->m_objList`, reads each object's AI update interface at
   `Object+0x204`, calls its path-destruction predicate at RVA `0x00278830`,
   and, when true, calls `destroyPath()` at RVA `0x0026F080`.
5. `Pathfinder::processPathfindQueue()` is called on `TheAI->m_pathfinder`
   (`TheAI+0x0C`) at `0x0038DC0E`, followed by `setFPMode`. Its ILT is RVA
   `0x000313A9`; the 716-byte body is RVA `0x003DC190` (VA `0x007DC190`).
   The body recalculates zones when needed, refreshes logical terrain bounds,
   and services queued object path requests until the per-frame cell budget is
   consumed. Both calls precede the next phase-1 test; the pathfinder and FP
   reset therefore run for every admitted phase.
6. ScriptEngine, LuaScriptEngine (`0x012F060C`), TerrainLogic, and optional VictorySystem update
   at `0x0038DC1C..0x0038DC4D`. VictorySystem's update is independently mapped
   to body RVA `0x001DFBA0`. The LuaScriptEngine identity is direct: the
   `GameEngine::init` registration block at `0x00079F36` pushes the literal
   `"TheLuaScriptEngine"`, then passes global `0x012F060C` to the matched
   `initSubsystem<LuaScriptEngine>` body at RVA `0x00074ED0`.
7. Logic CRC generation and message creation occur at
   `0x0038DC50..0x0038DDF5`.
8. Optional `TheCRCParameterCheck` (VA `0x012ED4FC`) clears its accumulated
   `AsciiString` range, followed by the phase-1-only `TheStatsCollector`
   (`0x012ED63C`) and Recorder (`0x0038DDF5..0x0038DE27`). The identity is
   fixed by its exact constructor at RVA `0x000659C0`, its vector-appending
   logger at `0x00065C80`, and the `GameLogic::getCRC` caller of RVA
   `0x00065D90`, which transfers the same vector under the literal block name
   `"CRCParameterCheck"`. `GameEngine::reset` calls the same exact clear body
   at RVA `0x00065A40`. The direct call at `0x0038DE16` follows ILT
   `0x000467D1` to the exact `StatsCollector::update` body at RVA
   `0x000A2E60`. Independent calls on the same global reach exact
   `writeFileEnd`, `collectMsgStats`, `startScrollTime`, and `endScrollTime`
   bodies; the matched Money methods access its money counters at `+4/+8`.
9. Every node starting at `TheCommandList+8` is passed to the GameLogic command
   processor with argument zero; CommandList is then reset through virtual slot
   `+0x10` (`0x0038DE2A..0x0038DE50`). Commands are therefore consumed and
   cleared during phase 1, before phases 2–6.
10. The object list at `GameLogic+0xA8` receives interface work at
    `0x0038DE53..0x0038DE83`. For each object, retail first calls virtual slot
    `+0x28` as a null test, then, only when non-null, pushes zero, calls slot
    `+0x28` a second time, and invokes the returned interface's direct callback
    at RVA `0x0041B200`. This establishes `getDrawable()->callback(0)` and its
    evaluation order; caching the first getter result changes the call stream.
11. After the later shared drain and copy-protection check, phase 1 walks the
    object list again at `0x0038E1C3..0x0038E212`. It conditionally calls three
    helpers based on object `+0x1A4`, bit `0x200` at `+0x98`, and bit `0x10` at
    `+0x90`, then always calls object virtual slot `+0x3C`. The first helper is
    `Object::checkDisabledStatus()` at RVA `0x001C5780`: it tests all 11
    `DisabledType` bits and clears each active type whose expiration frame at
    `Object+0x1A8+4*type` is no later than the current simulation frame. The
    final virtual is `Object::updatePendingDamage()` at RVA `0x001C7B80`. It
    subtracts one frame from each 92-byte queued `DamageInfo` record at
    `Object+0x34C`; a delay that becomes negative is applied through
    `attemptDamage()` and erased from the vector.
12. If byte `GameLogic+0xA0` is clear and byte `GameLogic+0x40` is set, the
    function increments `GameLogic+0x3C` at `0x0038E225`. It then sets
    `GameClient+0xC4 = 1`.

The entire phase-1 object tail is now identified and byte-exact in clean C++.

## CRC behavior

CRC work is phase 1 only and is skipped in game modes 4 and 8
(`0x0038DC50..0x0038DC70`). It also requires a Recorder. Multiplayer/replay
cadence divides the current frame by the interval at `TheGameInfo+8`; mode 2
suppresses that path (`0x0038DC7E..0x0038DCAE`). A debug frame window rooted at
global `0x012A6F38` can force the path and uses writable-global-data offset
`+0xCB4` (`0x0038DCAE..0x0038DCE8`).

The CRC is calculated by `GameLogic::getCRC(AsciiString)` at body RVA
`0x00383150` through ILT RVA `0x0000B532`. Its argument is BFME's one-word
AsciiString passed by value, and the body returns with `ret 4`. The call site
therefore pushes exactly one 32-bit word: a null AsciiString buffer on the
normal path, or a copied buffer on the diagnostic path. The older decorated
pin that includes an additional integer parameter is stale ABI evidence and
must not be copied into the parent TU.

The diagnostic path formats the current frame with `"%d"` into a one-word
AsciiString, copies its buffer through the factory at RVA `0x009CB5F0`, and
passes the copy to `getCRC`. The normal path temporarily sets byte
`0x012ED4E6`, calls `getCRC(0)`, and clears the byte. Byte `0x012ED4E5` selects
the diagnostic path; either byte being set also selects the later detailed CRC
handler. The local player index comes from
`(*(ThePlayerList+0x0C))+0x24`.

Retail then appends message type `0x449` and arguments in this order: CRC,
current simulation frame, whether `Recorder::getMode()` equals one, and either
false or a call to `bfme_processLogicCRC` at RVA `0x0038B430`. The detailed
handler receives CRC, player index, frame, message, false, and the copied
string-buffer word (`0x0038DD84..0x0038DDF5`). This all happens before Recorder
update, command consumption, sleepy updates, deferred destruction, the phase-1
object tail, and the frame increment. A repeated phase 1 can therefore
calculate and enqueue another CRC against the state at that invocation; it is
not a harmless network-only poll.

## Sleepy-update partition

Four vector triplets begin at `GameLogic+0xC4`, with stride `0x0C`. For each
selected vector, the loop examines pointer entries in vector order. An entry is
due when its `+0x14` wake frame is no greater than the current frame
(`0x0038DF79..0x0038DF92`). Its owner is at `+0x08`; owner disabled state is at
`+0x1A4`. The small polymorphic object embedded at entry `+0x10` supplies a
disabled-types mask through slot `+0x04` and performs the update through slot
zero.

Around an admitted callback, `GameLogic+0x100` is set to the entry and then
cleared (`0x0038DFBC..0x0038DFF1`). A callback sleep below one is clamped to
one; owner flag bit one at `+0x90` chooses the sentinel `0x3FFFFFFF`. The next
wake frame is current frame plus sleep, saturated at that sentinel
(`0x0038DFFB..0x0038E01A`). Sentinel entries are removed from the active vector
and appended to the vector at `GameLogic+0xF4`, while entry indices `+0x18` and
`+0x1C` are repaired (`0x0038E03E..0x0038E0DA`).

Phase 3 stops at half of vector 0. Phase 4 starts at half of the then-current
vector 0. Because the vector can be mutated while it is processed, reproducing
the exact index and removal order matters; a range-for rewrite would not be
behaviorally equivalent without proof.

The retail implementation uses two passes. The forward pass processes due
entries and writes their next wake frame but does not erase sentinel entries.
For phases greater than three, a separate reverse pass finds wake values at or
above `0x3FFFFFFF`, swap-pops those entries from the active vector, repairs the
moved entry's phase and index, sets the removed entry's phase to `-1`, and
appends it to `GameLogic+0xF4`. Removing sentinel entries during the forward
pass is behaviorally different because it changes the remaining iteration
indices.

## Pause, loading, and game mode

These are distinct gates:

- Network admission is outside this function in
  `GameEngine::_bfme_updateNetworkAndLogic`. It is tested only for phase 1.
  Phases 2–6 reach this function unconditionally from that caller.
- Logic/camera freeze is inside phase 1. A rejected freeze path executes the
  debug-frame prefix and depth-counter entry, sets `GameClient+0xC4 = 0`, then
  returns before phase recording, CRC, commands, objects, or frame increment.
- `GameLogic+0x11D` is an early command-only transition gate after the deferred
  vector was reset. The BFME `GameState::loadGame` mission-save branch sets it
  at `0x00110B6F`; the GameLogic constructor, `init`, and reset/default paths
  clear it. Its original field name remains unproven.
- Game modes 4 and 8 suppress both CRC work and the frame-1024 copy-protection
  check. Mode 2 separately suppresses the multiplayer CRC cadence.
- The frame increments only when phase 1 completes, `GameLogic+0xA0 == 0`, and
  `GameLogic+0x40 != 0`.

## Rejection, retry, and framedrain

A rejected phase-1 network admission never enters `0x0038DA10`. It changes
`GameClient+0xC4` in the exact caller and omits every operation described here.
A later retry is a fresh phase-1 call. This differs from an in-function freeze
rejection, which runs the phase-1 debug/freeze prefix and depth bookkeeping
before returning.

Feature `034-framedrain` inserted extra calls to
`_bfme_updateNetworkAndLogic(1)`. Every admitted extra call repeats the complete
phase-1 workload: script and terrain work, eligible CRC creation, Recorder and
command consumption, phase-1 object work, deferred destruction, object-tail
maintenance, and potentially one simulation-frame increment. It does not run
phases 2–6 between those repetitions. The reported desync is consistent with
violating the retail one-through-six ordering, but the precise desync cause has
not been proven by runtime or multiplayer traces.

## Dependency status

| Dependency | Status for this target | Evidence / next question |
|---|---|---|
| `_bfme_updateNetworkAndLogic` at `0x0006BAE0` | already understood and exact | matched clean C++; proves phase-1-only admission and slot `+0x20` |
| ILT `0x0003A9C7` | already understood and exact | matched five-byte thunk to target |
| `setFPMode` at `0x008FC4C0` | sufficiently understood | same direct callee and role as source donor |
| VictorySystem update at `0x001DFBA0` | sufficiently understood | vtable slot and phase-1 caller mapped |
| `getCRC` at `0x00383150` and CRC handler at `0x0038B430` | sufficiently understood | argument and message flow visible in caller; handler mapped |
| deferred owned-entry clear at `0x0038A6F0` | already understood and exact | 92-byte clean C++ match in `Bfme5SelfRangeClears.cpp` |
| GameLogic clear/walk at `0x0038D000` | already understood and exact, related lifecycle evidence | exact 112-byte clean C++; proves `+0xA8` object list and `+0x15C` vector coexist in the layout |
| `GameLogic::processDestroyList` at `0x0038AE90` | behavior and identity solved; clean C++ near match banked | corrected boundary is 438 bytes; phase-5 caller, clear-path caller, field effects, and destruction order agree; remaining 416/438-byte mismatch is register allocation |
| helper on `GameLogic+0x170`, body `0x00367810` | already understood and exact; class name still address-derived | 164-byte clean C++ thiscall, direct via ILT `0x000159C9`, sole caller is phase 5 at RVA `0x0038E17B` (`lea ecx,[ebp+0x170]`); member built at `0x00366B90` (ctor site `0x00392B27`), torn down at `0x003643C0` (dtor site `0x0038F220`), serviced in startNewGame at `0x00367470` (site `0x00395E70`); entries are LivingWorld reinforcement/auto-summon records, so the narrowest description is the embedded LivingWorld reinforcement-army store; exact C++ class name unproven |
| `GameLogic::processCommandList()` at `0x00383050` | solved and byte-exact | 47-byte clean C++; walks `TheCommandList+8`, calls `logicMessageDispatcher(message, NULL)`, then resets the list; the normal phase-1 path inlines the same body at `0x0038DE2A` |
| `Pathfinder::processPathfindQueue`, body RVA `0x003DC190` | solved identity and behavior; body remains a byte-true dump | called on `TheAI->m_pathfinder` at `+0x0C`; source twin and complete body state/queue layout agree |
| command processor body `0x00797540` | sufficiently understood for ordering | each CommandList node and argument zero are explicit; detailed command dispatch is separate work |
| `Object::checkDisabledStatus()` at `0x001C5780` | solved and byte-exact | corrected 102-byte boundary includes the complete epilogue; checks 11 disabled bits against expiration frames rooted at `Object+0x1A8`, calls `clearDisabled(type)`, and clears the bit |
| `Object::clearStatus(ObjectStatusTypes)` at `0x00162CD0` | solved and byte-exact | corrected an older `clearModelConditionState` identity: the body builds one bit in an 86-bit object-status mask and calls `setStatus(mask, false)`; both expiry helpers call it |
| `Object::checkIgnoreAICommandStatus()` at `0x001CE7B0` | solved and byte-exact | status bit 73 is `IGNORE_AI_COMMAND`; when the nonzero expiration at `Object+0x338` is older than the current frame, clears the status and zeros the expiration |
| `Object::checkNoCollisionsStatus()` at `0x001CE7F0` | solved and byte-exact | corrected RVA (the earlier `0x005CE7F0` was a VA); when the nonzero expiration at `Object+0x33C` is older than the current frame, clears status bit 4 (`NO_COLLISIONS`) and zeros the expiration |
| `Object::updatePendingDamage()` at `0x001C7B80` | solved and byte-exact | Object vtable `0x0109EE58` slot `+0x3C`; decrements delay `DamageInfo+0x24`, applies records only after the delay becomes negative through virtual `attemptDamage` at slot `+0x38`, then erases the 92-byte record |
| `Object::getDrawable() const` at `0x001BE440` | solved and byte-exact | Object vtable `0x0109EE58` slot `+0x28` reaches the seven-byte getter through ILT `0x0002074D`; it returns the proven `Object+0x80` drawable pointer used by the phase-1 per-object callback sequence |
| `CopyProtect::validate()` at `0x00102240` | identity and 36-byte boundary solved; clean C++ intentionally unavailable | the frame-1024 phase-1 gate calls this body through ILT `0x00009999`; retail tests `s_protectedData` and then unconditionally jumps to the success return, bypassing its 0x25-byte comparison block. That post-link disarm has the same impossible branch shape as the documented patched `notifyLauncher`, so the final parent must reference the retail helper rather than spend time trying to compile its bytes from clean C++ |
| `TheLuaScriptEngine` global `0x012F060C` | solved | constructor-tag registration and matched `initSubsystem<LuaScriptEngine>` call prove the identity; phase 1 calls virtual `update` at slot `+0x14` |
| `TheStatsCollector` global `0x012ED63C` | solved | five exact member-function callees share this receiver; phase 1 calls exact `StatsCollector::update` at RVA `0x000A2E60` |
| `TheBuildAssistant` global `0x012ED83C` | solved and byte-exact update | `GameEngine::init` pairs this global with the `"TheBuildAssistant"` tag and matched `initSubsystem<BuildAssistant>`; constructor vtable `0x010EA8D4` slot `+0x14` reaches the one-byte `BuildAssistant::update` at RVA `0x0037CAC0` |
| `TheLargeGroupAudio` global `0x012F1044` | solved and byte-exact update | constructor vtable `0x010EE13C` slot `+0x14` reaches `LargeGroupAudio::update` at RVA `0x003D2440`; its 61-byte clean C++ body walks the outer group vector and each group's `+0x18..+0x1C` element vector, calling the established `0x00025603` element thunk |
| `TheWeaponStore` global `0x012EF738` | solved and byte-exact update | `GameEngine::init` constructor/tag evidence and WeaponStore vtable `0x010A13C8` identify the singleton; slot `+0x14` reaches the one-byte empty `WeaponStore::update` at RVA `0x001E17B0` through ILT `0x0000FFB0` |
| `TheExperienceLevelSystem` global `0x012F0888` | solved and byte-exact update | constructor vtable `0x010EA948` slot `+0x14` reaches `ExperienceLevelSystem::update` at RVA `0x0037F4C0` through ILT `0x0001270B`; the 180-byte clean C++ body drains the `+0x1C` pending-level list, resolves each nonzero ObjectID through `GameLogic`'s `+0xB0` hash, skips null or status-bit-0 objects, calls the pending-level apply body `0x0037F280`, and clears the list |
| `TheShroudManager` global `0x012ED5BC` | solved for phase 5; forwarder and drain are byte-exact | facade vtable `0x01138D18` slot `+0x14` reaches the exact eight-byte forwarder at `0x008F7360`; it loads the pimpl at `+0x0C` and tail-jumps to exact 54-byte `ShroudManagerImpl008FBA40::drainPending` at `0x008FAFD0`, which unlinks each pending `PartitionData`, updates it through `0x008F8800`, and processes it through `0x008FADD0` |
| `TheTaintManager` global `0x012ED5C0` | solved and byte-exact empty update | facade vtable `0x01132B54` slot `+0x14` reaches the exact eight-byte forwarder at `0x00880E00`; it loads the owned `Gen_008812D0` grid at `+0x0C` and tail-jumps to the one-byte `Gen_008812D0::update` at `0x008811D0`, which returns without changing state |

## Reconstruction status and attack plan

The existing Zero Hour derived `GameLogic::update(void)` was compiled against
the corrected target range. It produces 1,010 bytes versus retail's 2,129,
first diverges at stack allocation `0x0038DA25` (`0x1C` versus `0x2C`), lacks
the phase argument, and has unresolved calls. It is a semantic donor, not a
valid BFME partial, so it has not been banked under the primary RVA. There is
no build/link or runtime verification for a BFME phase-update replacement.

A later dedicated `GameLogic::update(int)` experiment now models the proven
BFME offsets, all early returns, the independent phase-1 conditionals, phases
2 through 6, the four sleepy vectors, the reverse sentinel sweep, deferred
vector insertion, the phase-5 subsystem batch, CRC/debug-string construction,
copy-protection gate, and both phase-1 object walks. The latest probe produces
2,200 bytes and 656 decoded instructions versus retail's 2,129 bytes and 637
instructions. Its mnemonic-sequence similarity remains about 0.63, 93 object
relocations no longer align with the corresponding retail operands, and the
first structural divergence is still the prologue: the experiment allocates
`0x3C` local bytes and keeps `this` in `esi`, while retail allocates `0x2C` and
keeps `this` in `ebp`. This is still not a near miss, so the source remains
under ignored `build/` scratch and has not been banked.

Full-body tuning is suspended. Continue by recovering independently
committable leaves in the parent dependency cone, reassessing after each exact
body:

1. CRC/debug helpers and one-word AsciiString operations.
2. Command-list helpers and the command dispatcher.
3. The earlier phase-1 Drawable callback and its smaller dependencies.
4. Phase-2 transform, collision, and object helpers.
5. Sleepy-update module predicates, wake scheduling, and removal helpers.
6. Banked near-matches whose parent call sites now establish their identity or
   ABI.

Large callees such as the Drawable callback, CRC handler, and
VictoryConditions update should be treated as parents of their own smaller
dependency cones. Do not resume byte-level work on the 2,129-byte body until
the obvious exact leaves have been exhausted.

Semantic recovery here is strong enough to state what each phase schedules and
where the authoritative frame advances. Byte-exact reconstruction remains
open. Runtime behavior and multiplayer correctness remain untested.
