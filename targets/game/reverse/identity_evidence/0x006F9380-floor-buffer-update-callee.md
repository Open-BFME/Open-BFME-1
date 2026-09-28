# 0x006F9380: the buffer-rebuild callee is Rva006F8F00Owner::updateBuffers

The banked attempt for 0x006F9380 declared its dirty-flag callee as
`BufferRebuild006F8F00::rebuild()`, and its own header comment called that an
UNPINNED address-derived declaration to confirm before landing.

Retail evidence:

- 0x006F9380 +0x191: `mov ecx, ebp; call 0x004472BC`, i.e. ILT 0x000472BC,
  which is `jmp 0x006F8F00` (thiscall, `this` = the floor buffer, no stack
  arguments, result unused).
- 0x006F8F00 is already a matched ledger row:
  `?updateBuffers@Rva006F8F00Owner@@QAEXXZ` (264 B,
  `game/GameEngineDevice/Source/W3DDevice/GameClient/Rva006F8F00Owner_updateBuffers.cpp`).

Retail links without identical-COMDAT folding, so that body has exactly one
identity. The landing calls it by its ledger name instead of introducing a second
address-derived name (`BufferRebuild006F8F00::rebuild`) that nothing pins. Both
names are opaque address tokens; this is not a loss of descriptive information.
