# 0x004AEE00 ControlBar::populateStructureInventory (1188 B): first bank, shape 0.908

Bank: targets/game/reverse/attempts/0x004aee00.cpp (s531, claude-opus-5-5). Flags
`/DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB` plus STLport.

Identity (BFME 1 evidence): symbols.csv pins
`?populateStructureInventory@ControlBar@@IAEXPAVObject@@_N@Z` at ILT 0x0001DF4D and
`tools/ilt_oracle.py check` CONFIRMS it (p_false 2.6e-4). The ledger row's name
`?updateSlotExitImage@ControlBar@@QAEXPBVImage@@@Z` is CONTRADICTED at that ILT. The row is the
__emit lift in ControlBarUpdateSlotExitImageThunk.cpp. The official home is
ControlBarStructureInventory.cpp, which already matches the next body 0x004AF490
(updateContextContestedStructureInventory). That body calls this one as `bfmeApplyZA(b, 1)`, a
placeholder pinned at the same ILT. The STL callees are also ILT-confirmed:
vector<GameWindow*>::reserve at 0x46F4C (body 0x4A4090, a gen-tgrid row) and
_M_insert_overflow at 0x56CD (body 0x483A10, a gen-shim row).

Donor: Open-BFME-2 Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarUpdateConstruction.cpp
(BFME2 0x0053E783), with the same control flow. The BFME 1 differences are listed in the bank
header.

Byte-proven shapes:
- The evacuate lookup is an if/else with two findCommandButton calls. Retail cross-jumps the
  shared call and destructor, so the temp slot is shared and the EH states are 0 and 1. A
  ternary of two AsciiString temps instead emits conditional destruction flags.
- The template portrait uses a ZH OVERRIDE operator-> with an inline recursive
  getFinalOverride. That gives retail's `xor ecx,ecx` null arm.
- The loop body, push_back, second loop, evacuate block, info record and iterate call all match
  instruction for instruction.

Residue (855 B, 1163/1188): global register allocation. Retail keeps zero in EBX and `this` in
EDI, spilling `this` to [esp+0x18] at entry and reloading it after the image block, where EDI
holds the window. It also pushes EBP late, for `contain`. Ours puts zero in EDI and `this` in
EBP, and enregisters `building`. Retail's contested arm also loads the vtable inside each arm.
The earlier helper that wrongly passed the portrait to images 5/6 had 742 diffs with retail's
EBX/EDI roles. That suggests the zero-constant weight decides the partition.
Inert: ally as bool/char/unsigned char, `== false` gate test, explicit window local for the
image calls, NULL spelling. The max/count ternaries give 1179 B with contain in ESI (worse).
