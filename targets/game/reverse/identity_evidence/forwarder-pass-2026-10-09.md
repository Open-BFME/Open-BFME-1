# Name-forwarder pass, 2026-10-09

Owner-approved single pass (build/linkfleet/owner_forwarder_verdict.md, groups 1 and 2) over the `#define` /
`typedef` forwarders the 2026-10-06..09 link fleet added so call respellings would not trip name_regression.
Each forwarder kept an old spelling and routed it to the ledger row's name. This pass deletes the forwarder and
spells the call with the ledger name. A `#define` or `typedef` emits no code, so every touched TU stays
byte-identical (`./build.sh`, 100% matched) and keeps linking (`tools/link_check.py`, LINKED unchanged).

None of the descriptive spellings below is EA's name for its target. BFME1 retail ships no symbols, so a
descriptive name needs an independent witness: a Zero Hour counterpart, an ILT bucket fit
(`tools/ilt_oracle.py check`), or matched callers that use the name. The forwarder spellings were invented by
workers to keep the old call text compiling; a define is not evidence for its own name.

## FESL message helpers (Rva008097D0LanTheaterRemove, Rva00803730FeslAttrs, FeslEchoNotifier, FeslTidMessageSender, Rva0080A110Route)

- `sendFeslMessage` -> `Rva007F93E0` (0x007F93E0, ledger note "FESL routed message sender").
  `tools/ilt_oracle.py check '?sendFeslMessage@@YAPAXPAX00@Z' 0x7F93E0` and the same check of the ledger name
  both return UNTESTABLE (not a thunk target: FESL library region), so the ILT cannot witness any name here.
  FESL is EA Online code that Zero Hour does not contain, so there is no ZH name either. The body does route a
  message (dispatcher callers), but "sendFeslMessage" is a worker's paraphrase, not a recovered identity.
  Unproven: callers now spell `Rva007F93E0`.
- `addInt` -> `BfmeThingCIB::bfmeGoCIB` (0x007E88D0), `getPtr` -> `BfmeThingRF::bfmeGoRF` (0x007E8900),
  `getBool` -> `BfmeThingVMQ::bfmeGoVMQ` (0x007E89C0): FESL key/value accessors in the same library region,
  same ILT status, no ZH counterpart. Unproven paraphrases; callers spell the ledger names.
- `submit` -> `Rva008038F0Sender::send` (0x008038F0): the ledger name already says "send"; "submit" was a
  second, unwitnessed spelling. Callers spell `send`.
- `typedef BfmeC994 FeslEchoMessage`: BfmeC994 is the FESL message class (ctor 0x007E8850). No witness names
  it FeslEchoMessage; the local is declared as `BfmeC994`.
- `Rva007EFFC0Get()` / `Gen00809750_delete()` (group 2, placeholder to placeholder): spelled as their
  expansions (`bfmeGo929C`, `Gen007F0170::operator delete`).

## Second batch (AIGuard, W3DView, pause buttons, model-condition table, ControlBar, fire-special-power, ParticleSystem::DoXfer, BfmeConv1085)

- `getPosition` -> `Team::getEstimateTeamPosition_000EDCD0` (0x000EDCD0). Zero Hour's counterpart is
  `const Coord3D *Team::getEstimateTeamPosition() const`, but BFME's body takes an out-parameter, and
  `ilt_oracle check` CONTRADICTS `?getEstimateTeamPosition@Team@@QBEXPAUCoord3D@@@Z` and the `PAV` spelling
  at this body (slot 28773). "getPosition" is neither EA's name nor the ledger's; callers spell the ledger name.
- `getCenter` -> `BfmeA1263::bfmeGet1263` (0x0018F790). Zero Hour's AIGuard calls
  `area->getCenterPoint(&pos)` on the guarded PolygonTrigger, and
  `ilt_oracle check '?getCenterPoint@PolygonTrigger@@QBEXPAVCoord3D@@@Z' 0x18F790` is CONFIRMED (exact), while
  `?getCenter@BfmeA1263@...` is CONTRADICTED. So the forwarder's "getCenter" was not the name; the real name is
  PolygonTrigger::getCenterPoint with a *class* Coord3D parameter. Renaming the row needs the deferred
  Coord3D struct->class change (#47) in every caller TU, so this pass spells the ledger name and leaves the
  ILT-confirmed rename as an operator/name-lane candidate.
- `helper()` -> `Rva0045B5D0::run` (0x0045B5D0, ledger note "identity not recovered").
  `?helper@W3DView@@QAEXXZ` is CONTRADICTED by the ILT window. Callers spell the ledger name.
- `invokeAtLevel` -> `BfmeLevelAN::bfmeBuildAN` (0x004675F0). `?invokeAtLevel@WindowManager@@QAEPADIHHHHHHH@Z`
  is CONTRADICTED by the ILT window (slot 16496). Callers spell the ledger name.
- `ModelConditionNames` -> data row `Rva00EA6918ModelConditionNames` (0x00EA6918, slots point at TOPPLED,
  FRONTCRUSHED, ... per symbols.csv). The table really is the model-condition name list, and the ledger name
  already says so; EA's symbol is not proven (body_guard_baseline records a competing
  `?ModelConditionNames@@3QBQBDB` claim on the same address), so the short spelling is not adopted.
- `bfme_preloadAssets_impl()` -> `Rva00170460AIStateMachine::clear`. "preloadAssets" belongs to the caller
  (ControlBar::preloadAssets), not the callee; `?preloadAssets@ControlBarSchemeManager@@QAEXXZ` is CONTRADICTED
  at 0x00170460. Callers spell the ledger name.
- `BfmeTeamInstanceLink` / `_bfme_nextInInstanceList` -> `Gen_000c8a30::m` (0x000C8A30, 4-byte getter) and
  `BfmePlayerTeamInstanceIterator` -> the TU-local `Rva002F48B0TeamInstanceIterator`: worker-invented
  spellings with no witness. The type and call now use the ledger/address names.
- `bfmeHandOver_0000240A` -> `Rva0010C2E0` and `BfmeParticleSystemXferHandle` -> `Rva0010C3E0` (25-byte cdecl
  forwarders onto virtual slot 0x90 per the ledger): no witness for either spelling.
- BfmeConv1085: the placeholders `bfmeOpen1085` / `bfmeShut1085` forwarded to `WindowManager::hideAptWindow`
  (ILT 0x0002144A -> 0x00467460) and `showAptWindow` (ILT 0x00012733 -> 0x00465C50), i.e. "open" hid and
  "shut" showed the window. The calls now spell hideAptWindow/showAptWindow. `bfmeSet1085` -> `aiIdle`,
  `bfmeUse1085` -> `setSequentialTimer` are respelled likewise (group 2).
- Rva0056ABE0PauseButtons: `bfmeStop1013` -> `GameWindow::winEnable`, `bfmeTestME` ->
  `Rva0056AB50Owner::getSelectedItemData` respelled (group 2).
