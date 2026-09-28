# RVA 0x001F2E80: BridgeBehavior damage-state callback

The previous `LANAPI::OnGameJoin(ReturnType, LANGameInfo*)` row claimed only
30 bytes and ended in the middle of `mov edi,[esp+0x4c]` at RVA 0x001F2E9C.
The complete body ends with `ret 0x0c` at 0x001F3099, followed by 148 int3
bytes through 0x001F3130. It consumes three stack arguments, not two.

Independent semantic evidence:

- It calls BridgeBehavior::resolveFX at 0x001F2AF0 through ILT 0x000085A3,
  with `ecx = secondary-this - 0x24`.
- It calls Bridge::getBridgeTemplateName at 0x001F22A0 through ILT 0x0004A83B,
  then TerrainRoadCollection::findBridge at 0x006024E0 through 0x00034D8D.
- Both branches call BridgeBehavior::doAreaEffects at 0x001F2450 through
  ILT 0x00049FA8, three times, using the damage or repair OCL/FX arrays.
- It compares the third argument to BODY_RUBBLE (3), clears m_deathFrame
  when leaving rubble, updates terrain bridge states, and refreshes the radar
  when either old or new state is rubble.
- The complete algorithm is the reference BridgeBehavior::onBodyDamageStateChange
  in game/GameEngine/Source/GameLogic/Object/Behavior/BridgeBehavior.cpp.
  The BFME AudioEventRTS records have stride 0x70, moving m_fxResolved to
  primary-this +0x47c and m_deathFrame to +0x484.

The C++ reconstruction in BridgeBehaviorBodyState.cpp compiles to all 540
bytes exactly (probe), including the three-argument return and both effect
loops. The 30-byte equal-range identity transaction is refused because it cuts an
instruction. A combined rollback-protected transaction first verifies the full
540-byte extent using an explicit object-symbol for the bridge method, then
corrects the ledger name at that same proven extent. Both add_match scoped
gates pass. No LAN API behavior is used by this body.
