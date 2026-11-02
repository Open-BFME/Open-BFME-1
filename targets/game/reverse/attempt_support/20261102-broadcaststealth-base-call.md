# BroadcastStealthUpdate loadPostProcess: resolve the base-call reference

Queue #34, ?bfmeBase987@BfmeA987@@QAEXXZ; census d08539a550.
Target before: 1148d6b4c5.

BFME 1 0x00289D40..0x00289E11 (209 bytes) calls ILT 0x00015E0B
at +9 after MOV ESI,ECX. The target chain, decoded independently:

- 0x00015E0B: E9 -> 0x002B2070
- 0x002B2070: E9 -> 0x0004049E
- 0x0004049E: E9 -> 0x001EF410
- 0x001EF410: C3, followed by INT3

The thunk is already a matched defining row ?j_00015e0b@@YAXXZ in
game/gen_small/thunks_010.cpp. The caller currently names an undefined
BfmeA987::bfmeBase987 with only a pin. Follow the established
Rva00225960ListDrain.cpp repair: reference the real thunk through a typed
zero-argument member-pointer view, preserving the original ECX receiver
and no-argument stack contract. No function body, pin or linker alias is
created, and no original member identity is inferred from the empty leaf.
The BfmeA987 layout remains the existing four-byte base.

Normal scoped checks pass the 209-byte caller, the 249-byte sibling and
the five-byte thunk provider. The caller COFF no longer references
?bfmeBase987@BfmeA987@@QAEXXZ and instead references the defined thunk.
All other caller bytes and encoded call targets remain verified.

Before link_check --census-only: unresolved placeholder plus four STLport
COMDAT conflicts, using available old index e9a5ae5b4c (2026-10-19).
After link_check with current consumer: selection is UNKNOWN with missing
current dependencies. Removal of the placeholder reference is independently
proven by COFF; no fully linked-byte gain is claimed.

BFME 2 revision 92f12c3 was reviewed through committed files:
Code/GameEngine/Source/GameLogic/Object/Update/BroadcastStealthUpdate.cpp
and UpdateModuleLoadPostProcess.cpp. Its UpdateModule forwards to
BehaviorModule, with different target addresses and layout. This supplies
context, not a BFME 1 body/name/ABI proof or an adapted donor repair.
The target thunk chain and existing BFME 1 sibling provide this repair.
