# BFME1 `GameLogic::update` dependency map

This note maps the six substantial callees that remain around retail BFME 1.03
`GameLogic::update(int phase)` at RVA `0x0038DA10`. It deliberately stops one
level below those bodies. The purpose is to select small, independently
verifiable leaves before returning to a large parent.

The status words have a narrow meaning here:

- **EXACT**: clean C++ emits the retail body byte for byte.
- **PARTIAL**: a banked clean body has the right behavior but does not yet match.
- **DUMP**: bytes are preserved by generated assembly, a generated shim, or an
  `__emit` carrier; this is not a clean-C++ recovery.
- **SEMANTICALLY_SOLVED**: control flow and effects are established, but no clean
  matching body exists.
- **UNKNOWN**: identity or behavior is still too weak to claim.

ILT addresses below are omitted from the component RVA column. The RVA is the
body behind the thunk. Imported runtime functions have no BFME body size.

## Phase-1 Drawable callback — `0x0041B200`, 1,368 bytes

The caller invokes this as `getDrawable()->callback(0)`. The callback is a
`__thiscall void(Bool)` body (`ret 4`), but its retail name is not proven. It is
distinct from `Drawable::updateDrawable()` at `0x0041BE60`.

Logical regions:

1. Set `Drawable+0x3B4` and invalidate the word at `+0x23C`.
2. If `+0xFC` is null, copy the base transform and vectors into both history
   blocks and return.
3. Otherwise select transform sources from the object at `+0xFC`; the Boolean
   argument selects which history/current blocks receive them.
4. If the dirty byte at `+0x3B3` is set, merge three model-condition sets at
   `+0x250`, `+0x278`, and `+0x2A0`, walk the pointer array at `+0x150`, notify
   each module, and clear the dirty byte.
5. Bytes `+0x184..+0x186` of the `+0xFC` object select the final vectors copied
   from its transform blocks. The final row helper fills the vector at
   `Drawable+0x388`.

| Component | RVA / size | Caller relationship and signature | Status | Parent value |
| --- | --- | --- | --- | --- |
| Address-derived Drawable callback | `0x0041B200` / 1,368 | phase 1, `__thiscall void(Bool)` | DUMP | Parent |
| `ModelConditionFlags::clearAndSet` | `0x001C5FA0` / 216 | direct; `__thiscall void(const ModelConditionFlags&, const ModelConditionFlags&)` | EXACT | Condition merge is closed |
| `Gen_001C1D60::bfmeGetRow` | `0x001C1D60` / 45 | direct; address-derived `__thiscall` vector-return helper | EXACT | Final vector extraction is closed |
| Array element virtual slot `+0x9C` | no body identified | returns an interface/object for each `+0x150` element | UNKNOWN | Needed to name the notification walk |
| Returned-interface virtual slot `+0x4C` | no body identified | called with `(&Drawable[0x250], 0, 0)` | UNKNOWN | Likely the only open leaf in the dirty-condition region |

Subsystem/layout dependencies are the owner object at `+0xFC`, the module
pointer array at `+0x150`, transform blocks `+0x08..+0x38` and
`+0x31C..+0x3A0`, model-condition sets `+0x250/+0x278/+0x2A0`, and dirty/state
bytes `+0x3B3/+0x3B4`. There are no directly called constructors, destructors,
or STL bodies.

## CRC handler — `0x0038B430`, 1,078 bytes

The proven identity is
`GameLogic::bfme_processLogicCRC(unsigned, int, unsigned, GameMessage*, bool,
int)`, with exact parameter meanings still partly inferred. The member returns
with `ret 0x18` and maintains a sorted report list at `GameLogic+0x44`.

Logical regions:

1. Find, coalesce, or insert a 24-byte per-frame CRC report node.
2. Optionally append `false` to the incoming message; allocate and initialize a
   new node when the frame is absent.
3. Maintain the associated integer/message list and cull records older than
   `NetworkCRCDelay + 3`.
4. Track report count, player mask, CRC agreement, and playback consistency.
5. Wait for the network/recorder quorum, create message type `0x449`, append the
   frame, CRC, timestamp, and Boolean fields, propagate it, and call the network
   slot at `+0x24`.
6. Invoke the desync reporter, clear the queued nodes, and call network slot
   `+0x78` (`quitGame`) for a mismatch outside playback.

| Component | RVA / size | Caller relationship and signature | Status | Parent value |
| --- | --- | --- | --- | --- |
| `GameLogic::bfme_processLogicCRC` | `0x0038B430` / 1,078 | `__thiscall`, six stack arguments | DUMP | Parent |
| `GameMessage::appendBooleanArgument` | `0x0008AB90` / 22 | direct, `__thiscall void(Bool)` | EXACT | Message field append closed |
| `GameMessage::appendIntegerArgument` | `0x0008AB50` / 22 | direct, `__thiscall void(Int)` | EXACT | Message field append closed |
| `GameMessage::appendTimestampArgument` | `0x0008ACE0` / 22 | direct, `__thiscall void(UnsignedInt)` | EXACT | Message field append closed |
| list `push_back` body | `0x00387F20` / 45 | direct on the CRC-side list; present clean alias names another pointer-list instantiation | EXACT | Bytes closed; exact element type remains open |
| `list<int>::size` | `0x00387F00` / 24 | direct `__thiscall const` | DUMP | Tiny clean-conversion leaf |
| `list<int>::pop_front` | `0x003872B0` / 26 | direct `__thiscall void()` | DUMP | Tiny clean-conversion leaf |
| `BfmeThingEC::bfmeTakeEC` | `0x009CB1F0` / boundary in its ledger row | direct list/value extraction helper | EXACT | Container extraction closed |
| `GameLogic::bfme_appendGameOverDetails` | `0x00387A50` / 657 | direct `__thiscall void()` | DUMP | Important subordinate parent; semantic identity is proven |
| `RecorderClass::getMode` | `0x000977F0` / 4 | direct `__thiscall` accessor | EXACT | Playback branches closed |
| `MessageStream::propagateMessages` | `0x0008ADF0` / 129 | direct `__thiscall void()` | EXACT | Message propagation closed |
| `GameLogic::bfme_reportDesync` | `0x00388C10` / 1,744 | direct `__thiscall`; called on both mismatch exits | DUMP | Large subordinate parent; map recursively before attempting |
| `operator new/delete`, node allocator/free | runtime | direct allocation and 24-byte-node destruction | EXACT | Library machinery |
| `MessageStream` virtual slot `+0x34` | no body identified | creates message type `0x449` | SEMANTICALLY_SOLVED | Body identity remains open |
| Network virtual slot `+0x94` | no body identified | returns participant/quorum count | SEMANTICALLY_SOLVED | Needed mainly for naming |
| Network virtual slot `+0x8C` | no body identified | Boolean readiness predicate, called twice | UNKNOWN | Naming and edge behavior remain open |
| Network virtual slot `+0x24` | no body identified | consumes/sends the propagated CRC message with argument zero | UNKNOWN | Naming remains open |
| Network virtual slot `+0x78` | no body identified | `quitGame` on mismatch | SEMANTICALLY_SOLVED | Exit behavior closed |

Important fields are frame `+0x3C`, sorted report-list head `+0x44`, associated
list storage `+0x48/+0x4C`, mismatch flag `+0x6C`, and the game-over text vector
and once flag used by `0x00387A50`. Globals are `TheNetwork`, `TheRecorder`,
`TheMessageStream`, `TheGameLogic`, `TheWritableGlobalData` (CRC delay at
`+0xCB4`), current/network frame state near `0x012A6F38`, and diagnostic toggle
`0x012ED4E8`.

## `VictoryConditions::update` — `0x0035F920`, 986 bytes

The current ledger body is an `__emit` carrier. Retail calls the slot-21
end-screen timer first, then applies the configurable frame delay at
`GlobalData+0x11F8`.

Logical regions:

1. Update the end-screen timer and gate the scan by recorder mode, local slot,
   observer state, game mode, and frame delay.
2. Scan 32 cached players for one surviving alliance using the virtual defeat
   predicate and `areAllies`; record `+0xBD` and end frame `+0x98`.
3. Scan for newly defeated players, mark `+0x9C[index]`, record their defeat
   frame, reveal shroud, and choose living-world/local or multiplayer UI text.
4. For allied defeats, query relationship and queue EVA event 9. The alternate
   branch sends two strings through an unresolved manager virtual slot `+0x48`.
5. Format `"player%d"`, hash the name, find each of eight game slots, copy the
   AI display name, and set the slot frame.
6. Kill each newly defeated player. The final local-defeat state affects radar,
   chat/diplomacy, and the end-game UI through the surrounding subsystem.

| Component | RVA / size | Caller relationship and signature | Status | Parent value |
| --- | --- | --- | --- | --- |
| `VictoryConditions::update` | `0x0035F920` / 986 | virtual slot 5, `__thiscall void()` | DUMP | Parent |
| `VictoryConditions::updateEndGame` | `0x0035F1A0` / 36 | virtual slot `+0x54`, `__thiscall void()` | EXACT | Entry timer closed |
| `VictoryConditions::hasSinglePlayerBeenDefeated` | `0x0035FDF0` / 221 | virtual slot `+0x2C`, `Bool(Player*)` | EXACT | Main defeat predicate closed |
| TU-local `areAllies` | `0x0035F150` / 53 | direct; custom EAX/ESI register convention | EXACT | Alliance comparison closed |
| `RecorderClass::isMultiplayer` | `0x00097800` / 103 | direct `__thiscall Bool()` | EXACT | Mode gate closed |
| `GameLogic::bfme_setPlayerDefeatFrame` | `0x00383C00` / 35 | direct `__thiscall void(Int slot)`; current ledger name is generic | EXACT | Defeat timestamp closed |
| `PartitionManager::revealMapForPlayerPermanently` | `0x008F73E0` / 8 | direct `__thiscall void(Int)` delegate | DUMP | Identity known; clean wrapper remains |
| `GameLogic::_bfme_isInLivingWorldCampaign` | `0x00382B50` / 91 | direct `__thiscall Bool()` | EXACT | Campaign branch closed |
| `Player::isLocalPlayer` | `0x000C96D0` / 19 | direct `__thiscall Bool() const` | EXACT | Local message branch closed |
| `GameLogic::isInSinglePlayerGame` | `0x00382B00` / 64 | direct `__thiscall Bool()` | EXACT | UI branch closed |
| `Player::getPlayerDisplayName` | `0x00098FD0` / 32 | direct hidden-return `UnicodeString` accessor | EXACT | Display name closed |
| `Player::getRelationship` | `0x000D19C0` / 162 | direct `__thiscall Relationship(const Team*) const` | EXACT | Allied-defeat branch closed |
| `Eva::setShouldPlay` | `0x004233A0` / 146 | direct `__thiscall Bool(EvaMessage, const Coord3D*)`, called as `(9, 0)` | DUMP | Named, small clean-conversion leaf |
| Player evil getter | `0x00267FA0` / 17 | direct guarded `__thiscall Bool() const`; semantic field is known | EXACT | Bytes closed; canonical name remains open |
| `NameKeyGenerator::nameToKey` | `0x0008FFC0` / 299 | direct `__thiscall NameKeyType(const char*)` | EXACT | Slot lookup key closed |
| `GameInfo::getSlot` | `0x0061E8B0` / 32 | direct `__thiscall GameSlot*(Int)` | EXACT | Slot lookup closed |
| `GameSlot::isAI` | `0x0061E5C0` / 27 | direct `__thiscall Bool() const` | EXACT | AI slot branch closed |
| `Player::killPlayer` | `0x000CE170` / 184 | direct `__thiscall void()` | DUMP | Identity/semantics known; current body is an emit carrier |
| `AsciiString` constructors/destructors, `UnicodeString::set`, `__ftol2` | runtime/exact support | direct temporary-string and conversion machinery | EXACT | Compiler/runtime machinery |
| `GameInfo` virtual slot `+0x30` | no body identified | Boolean session predicate | UNKNOWN | Only naming remains |
| `InGameUI` slots `+0x30/+0x3C` | no body identified | one-key and key-plus-display-name messages | SEMANTICALLY_SOLVED | UI effects known |
| Manager virtual slot `+0x48` | no body identified | called with two temporary `AsciiString` values | UNKNOWN | Open branch leaf |

The core layout is cached players `+0x14[32]`, local slot `+0x94`, end frame
`+0x98`, defeated bytes `+0x9C[32]`, local-defeat/single-alliance/observer bytes
`+0xBC..+0xBE`, and defeat counter `+0xC0`. Globals include `TheGameLogic`,
`TheRecorder`, `TheGameInfo`, `ThePlayerList`, `TheShroudManager`, `TheInGameUI`,
`TheEva`, the window/manager globals, and writable global data.

## `Pathfinder::processPathfindQueue` — `0x003DC190`, 716 bytes

Logical regions:

1. Call a three-byte zone-manager method with zero, reject an unready map, and
   handle two refresh flags at `+0x243F4/+0x243F5`.
2. Run one incremental zone-calculation step.
3. Ask terrain logic for its `Region3D`, scale/floor all four XY bounds, and
   store the inclusive logical extent at `+0x24`.
4. Reset the cell counter at `+0x840`; use a 400,000-cell budget before frame 25
   and 4,000 afterward.
5. Walk the 512-entry circular request queue (`+0x24718`, head/tail
   `+0x24F18/+0x24F1C`), resolve ObjectIDs through the GameLogic hash at
   `+0xB4/+0xB8`, clear each consumed slot, and call AI virtual `doPathfind`.
6. Measure slow requests, tint the object tree when the global threshold is
   exceeded, advance/wrap the head, and call the refresh helper on the blocked
   exit.

| Component | RVA / size | Caller relationship and signature | Status | Parent value |
| --- | --- | --- | --- | --- |
| `Pathfinder::processPathfindQueue` | `0x003DC190` / 716 | `__thiscall void()` | DUMP | Parent |
| Address-derived zone-manager no-op | `0x00403850` / 3 | direct on `this+0xC9C`, one stack argument, `ret 4` | DUMP | Easy leaf, but semantic name is unproven |
| `PathfindZoneManager::calculateZonesIncremental` | `0x00408AD0` / 410 | direct `__thiscall void(PathfindCell**, PathfindLayer*, const IRegion2D&)` | DUMP | Subordinate parent; map recursively before attempting |
| `Pathfinder::bfmeTintSlowPathfindObject` | `0x003DAB50` / 159 | direct free helper `void(Object*)` | EXACT | Slow-request branch closed |
| `Pathfinder::bfmePrepareRefresh` | `0x003F9070` / 99 | direct `__thiscall void()` | EXACT | Blocked-refresh exit closed |
| `TerrainLogic` virtual slot `+0x20` | no body identified | `getExtent(Region3D*)` | SEMANTICALLY_SOLVED | Extent source closed |
| `AIUpdateInterface` virtual slot `+0x1F8` | no body identified | `doPathfind(Pathfinder*)` | SEMANTICALLY_SOLVED | Queue payload operation closed |
| floor import | runtime | four direct calls on scaled extent coordinates | EXACT | Runtime conversion |
| `QueryPerformanceFrequency/Counter` | imports | timing calls around each request | EXACT | Debug timing machinery |

Other important dependencies are `TheTerrainLogic`, `TheGameLogic`, the ObjectID
hash, `Object+0x204` AI interface, zone manager `+0xC9C`, map `+0x10`, layers
`+0x85C`, extent `+0x14`, and the slow-request threshold in writable global data
near `+0x1270`.

## `GameLogic::processDestroyList` — `0x0038AE90`, 438 bytes

The banked 416-byte C++ body has the complete semantics and scores 0.90; its
remaining difference is MSVC register allocation and repeated vector loads.

Logical regions:

1. Walk the pending-destruction list at `GameLogic+0x104`.
2. Walk the object's behavior-module array at `Object+0x1F0`; obtain each update
   interface through module virtual slot `+0x20`.
3. Remove scheduled updates from either the negative sleepy vector
   (`+0xF4/+0xF8`) or one of four phase vectors starting at `+0xC4`, using
   swap-and-pop and repairing the moved module's phase/index fields.
4. Remove the object from pathfinding, the intrusive object list
   (`+0xA8/+0xAC`), and the ObjectID hash at `+0xB0`.
5. Invoke the object's scalar deleting destructor and free/clear every pending
   list node, including nodes appended while destruction ran.

| Component | RVA / size | Caller relationship and signature | Status | Parent value |
| --- | --- | --- | --- | --- |
| `GameLogic::processDestroyList` | `0x0038AE90` / 438 | private `__thiscall void()` | PARTIAL | Parent; banked score 0.90 |
| Behavior-module virtual slot `+0x20` | no body identified | returns its `UpdateModule` interface | SEMANTICALLY_SOLVED | Module-to-update conversion closed |
| `Pathfinder::removeObjectFromPathfindMap` | `0x003D5810` / 17 | direct `__thiscall void(Object*)` | EXACT | Pathfinding unlink closed |
| `Object::removeFromList` BFME variant | `0x001BECF0` / 105 | direct `__thiscall void(Object **tail, Object **head)` (the two pointer roles are fixed by the retail stack stores) | EXACT | Intrusive-list unlink closed |
| ObjectID/Object* hashtable `erase` | `0x00387640` / 146 | direct `__thiscall size_type(const ObjectID&)` | DUMP | Identity proven; clean STL leaf |
| Object scalar deleting destructor | vtable slot `+0x1C` | called with delete flag 1 | SEMANTICALLY_SOLVED | Destruction semantics closed |
| STLport node deallocator | runtime | direct, frees 12-byte pending-list nodes | EXACT | Container cleanup closed |

The pending-list node is 12 bytes (links plus `Object*`). Update scheduling uses
module phase/index fields at offsets `+0x1C/+0x18` after conversion to the update
interface. The phase-vector array has 12-byte strides.

## `AIUpdateInterface::isMoving` — `0x00278830`, 99 bytes

The identity is established by seven callers. The banked body reproduces all
99 bytes of control flow and memory access except for a whole-body ESI/EDI
assignment mirror.

Logical regions:

1. Starting from `this`, follow `AI+0x08 -> Object+0x214 -> Object+0x204` while
   the linked object is kind-of `0x6C`.
2. Test byte `AI+0x324`; if it is clear, call virtual `isIdle` at slot `+0x180`.
3. If the AI is not idle, inspect the goal/state word at `AI+0x1D8` and return
   the moving predicate.

| Component | RVA / size | Caller relationship and signature | Status | Parent value |
| --- | --- | --- | --- | --- |
| `AIUpdateInterface::isMoving` | `0x00278830` / 99 | `__thiscall Bool() const` | PARTIAL | Parent/leaf; banked score 0.85 |
| `Thing::isKindOf` | `0x000A2CF0` / 64 | direct `__thiscall Bool(KindOfType) const`, argument `0x6C` | EXACT | Linked-object filter closed |
| `AIUpdateInterface::isIdle` | virtual slot `+0x180` | `__thiscall Bool() const` | SEMANTICALLY_SOLVED | Body address remains unidentified |

There are no open direct callees. The remaining mismatch is a compiler register
choice, so this is no longer an easy semantic recovery.

## Leaf order after this map

The highest-confidence next leaf is `Object::removeFromList` at `0x001BECF0`:
its 105-byte boundary, member calling convention, two pointer arguments, caller,
intrusive-list fields, and Zero Hour source donor are all available. Next are
the ObjectID hashtable erase at `0x00387640`, `Eva::setShouldPlay` at
`0x004233A0`, and the two tiny CRC list operations. The three-byte Pathfinder
body is mechanically easiest but should retain an address-derived name until
another caller or a class layout proves its semantic identity.

Among the six parents, `GameLogic::processDestroyList` is closest to a clean
match after its leaves: it is already fully decomposed and banked at 0.90. The
AI predicate is smaller but blocked only by register allocation and does not
benefit from more dependency recovery. The next larger parent by dependency
readiness is the Drawable callback, whose two direct callees are already exact.

## Phase-2 transform and collision cone

Phase 2 is a separate branch of the dispatcher. It first updates the partition
manager, then dispatches `CollisionManager::update`, and finally walks the object
list at `GameLogic+0xA8`. Each object whose frame stamp at `+0x168` differs from
the current frame `GameLogic+0x3C` receives `Object::bfmeRecordTransform(frame)`.
The object-list walk follows the `+0x88` link and does not increment the frame.

| Component | RVA / size | Caller relationship and signature | Status | Parent value |
| --- | --- | --- | --- | --- |
| `PartitionManager::update` | body address not yet pinned | virtual slot `+0x14` from `ThePartitionManager` | UNKNOWN | Large phase-2 parent |
| `CollisionManager::update` | `0x009A2560` / 8 | virtual slot `+0x14`, forwards through `+0x0C` | EXACT | Collision dispatch closed |
| `Rva009A45A0CollisionData::update` | `0x009A4A30` / 41 | tail body; three collision passes bracketed by busy byte `+0xC06D` | EXACT | Collision implementation closed |
| `Object::bfmeRecordTransform` (Drawable body) | `0x001C0BE0` / 217 | Object ILT `0x0002BB43` calls the Drawable-compatible body with frame | EXACT | Transform history closed |
| `Object::bfmeReactToTransformChange` | `0x001BE700` / 65 | adjacent Object vtable helper for transform changes | EXACT | Shroud/collision/contain notifications closed |
| `PartitionManager` collision/contact helpers | several exact bodies in `PartitionManager.cpp` | reached through the manager update body, not directly by the dispatcher | EXACT / UNKNOWN ownership | Useful only after the manager entry is pinned |

The remaining phase-2 uncertainty is the retail `PartitionManager::update`
identity and its vtable slot body. The collision wrapper/data pair and the
transform helper are already clean, independently verified leaves.

## Phases 3–6 sleepy entries and update modules

After phase-2 work, the dispatcher uses a two-pass sleepy-vector algorithm. It
selects entries whose `nextCallFrame` is due, calls each update-module virtual
slot `+0x14`, and interprets the returned sleep state. Removal uses the same
swap-and-pop/index-repair machinery as `processDestroyList`. Phase 5 additionally
updates the object-creation list, the victory conditions subsystem, the
experience-level system, and the embedded LivingWorld entry range.

| Component | RVA / size | Caller relationship and signature | Status | Parent value |
| --- | --- | --- | --- | --- |
| `GameLogic::popSleepyUpdate` | `0x0038C1E0` / 2,876 | phase 3–6 direct call; `__thiscall void()` | DUMP | Main sleepy parent |
| update-module virtual slot `+0x14` | no single body | invoked for each normal/sleepy module; returns the update sleep enum | SEMANTICALLY_SOLVED | Core module dispatch |
| `GameLogic::processDestroyList` | `0x0038AE90` / 438 | phase 3–6 tail and phase-1 destruction path | PARTIAL | Removal dependency |
| `GameLogic::bfmeClear` | `0x0038A6F0` / 92 | phase-5 direct cleanup helper | EXACT | Phase-5 cleanup closed |
| `Rva00367810Entries::update` | `0x00367810` / 164 | phase-5 embedded entry at `GameLogic+0x170` | EXACT | LivingWorld phase-5 arm closed |
| `ScriptEngine::bfme_updateLogicDebugFrame` | `0x00339B10` / 102 | phase-1 debug frame support | EXACT | Debug update leaf closed |
| `ScriptEngine::isTimeFrozenDebug` | `0x00336F20` / 36 | phase-1 debug freeze predicate | EXACT | Debug gate closed |
| `ScriptEngine::forceUnfreezeTime` | `0x00337040` / 28 | phase-1 debug recovery call | EXACT | Debug recovery closed |
| `AIUpdateInterface::destroyPath` | `0x0026F080` / 70 | phase-1 object path cleanup before sleepy work | EXACT | Object path leaf closed |
| module disabled-mask/priority/index accessors | virtual or inline | fields at module `+0x18/+0x1C`, phase vectors at `+0xC4` stride 12 | SEMANTICALLY_SOLVED | Needed for exact allocator shape |

The parent body also calls several subsystem virtual updates at slot `+0x14`
(`TheAI`-owned pathfinder, shroud/taint/object-creation/victory/experience
systems). Those slots are semantically identified by their singleton and phase
position; their concrete implementations are outside this cone unless the
sleepy parent needs their code generation.
