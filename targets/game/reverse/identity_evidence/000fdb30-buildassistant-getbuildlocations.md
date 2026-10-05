# BuildAssistant::getBuildLocations at 0x000FDB30

The 4-byte body `mov eax, [ecx+8]; ret` was matched under the address-derived
accessor `?get@Rva000FDB30Dword@@QBEIXZ` ("sole edge is address thunk").

- Its only reference is ILT 0x00012E77, and that ILT's only reference is slot 15
  (+0x3C) of BuildAssistant's table 0x010860D8 (installed by the constructor
  0x000FDA80 that GameEngine::init hands to `initSubsystem<BuildAssistant>`;
  see `000febe0-buildassistant-update.md` and the slot table in
  `000fc010-buildassistant-buildtiledlocations.md`).
- Slot 14 is buildTiledLocations (0x000FC010) and slot 18 the matched
  `BuildAssistant::sellObject`. Zero Hour's BuildAssistant.h declares, in that
  order, `buildTiledLocations`, then the inline virtual
  `Coord3D *getBuildLocations( void ) { return m_buildPositions; }`.
- buildTiledLocations reads and replaces `m_buildPositions` at `this+0x08`
  (`mov [esi+8], edi` after `new Coord3D[maxTiles]`), the field this getter
  returns.

The Zero Hour header's inline definition, compiled in
`game/GameEngine/Source/Common/System/BuildAssistant.cpp` (which emits
BuildAssistant's vtable), reproduces the four bytes exactly.
