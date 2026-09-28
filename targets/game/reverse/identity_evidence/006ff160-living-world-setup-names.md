# 0x006FF160: owner and placeholder names in the banked body

The 2026-09-02 skeleton bank named this body `LivingWorldManager::init` with
helpers `initializeWorldGeometry`, `BfmeLivingWorldConfiguration`,
`BfmeLivingWorldName`, `BfmeLivingWorldScene` and `m_prefix`/`m_between*`
padding. None of those names had a witness: no caller, vtable slot, string or
name_oracle entry supplies them.

Evidence used for the 2026-09-28 bank instead:

- The only caller is the matched `Rva00700030::initialize` (0x00700030,
  `game/GameEngineDevice/Source/W3DDevice/GameClient/Rva00700030Initialize.cpp`),
  which passes its own receiver in ECX through ILT `0x0003D01E`
  (`?j_0003d01e@@YAXXZ`, target FUN_00aff160). The owner is therefore
  `Rva00700030`; its camera +0x70, scene +0x74 and three LightClass pointers
  +0x78..+0x80 are the same members this body reads. The method keeps the
  address token (`rva006ff160`).
- `initializeWorldGeometry` was the guessed name of the ILT `0x0001F744` call
  (target 0x006FE730, still a gen_asm dump with no identity), now called by
  address through that thunk.
- The settings block the body reads lives at `g_bfmeGameCW + 0x0C`; its
  members are unnamed in `name_oracle.py`, so the bank uses address-derived
  types (`Rva006FF160Settings`, `Rva006FF160LightDesc`, `Rva006FF160Name`) and
  offset padding (`m_padNNN`).
- `Gen_0090E810` and `Rva009EB7A0RefOwner` are the existing ledger/pin
  spellings of the two texture-handle callees (0x0090E810 bfmeSetFlag, matched
  in Bfme5TinyEight.cpp; 0x009EB7A0 Release_Ref pin), not renames of the old
  scene/manager guesses; the name-regression pairing matched them only by
  position.
