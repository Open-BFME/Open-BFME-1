# Parser binding base: TU-local name corrected to the recorded vtable owner

`??_7ParserBase0019B030@@6B@` (the TU-local parser base in
`game/GameEngine/Source/GameLogic/Map/Rva0019B030LoadBuildLists.cpp`) is the
same class as the canonical `BfmeParserBindingBaseVE` defined in
`game/GameEngine/Source/Common/System/BfmeDataChunkParserBinding.cpp`.

## Facts

- Retail vtable at 0x0107C7D0 is DIR32-recorded as
  `??_7BfmeParserBindingBaseVE@@6B@`
  (`targets/game/reverse/dir32_addresses.csv`), with the binding vtable
  0x0109BFD4 recorded under the same name.
- The canonical base (BfmeDataChunkParserBinding.cpp) and the former TU-local
  base share the layout (vfptr + two pointers, 12 bytes) and the slot count
  (two virtuals, `bfmeSlot0`/`bfmeSlot1`), the same inline constructor shape
  around the parser-registration call, and the same drop-on-destruction
  behavior. The derived binding keeps its recorded name and vtable.
- The rename carries the recorded class name so the constructor's vfptr store
  references the defining vtable symbol; no member, virtual, call target or
  layout changes. Scoped build of the TU stays byte-identical for its matched
  row (`?rva0019B030@BfmeTableERJ@@QAEXXZ`, 641 B), and the keyed DIR32 debt
  for 0x0107C7D0 verifies clean.

## Contract

- `ParserBase0019B030` was a TU-local duplicate name for the recorded
  `BfmeParserBindingBaseVE` base; the recorded name is the identity.
- Callers, vtable slot evidence and the canonical definition (above) are the
  basis; no new member or type name is invented here.
