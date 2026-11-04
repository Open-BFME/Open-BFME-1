# Build_Textures duplicate provider removal

Queue rank 15, claim 0xF6EE31C0. BFME 1 start 77a8439ee4 (worker branch
created from current parent checkout). The census e9a5ae5b4c records a wrong
strong Build_Textures in render2dsentence.cpp and the retail 530-byte provider
in Render2DSentenceClass_Build_TexturesMethodThunk.cpp. The native source
still contained the old Zero Hour implementation under present-unmatched.
Remove that definition; callers retain their existing declaration and bind
to the existing byte-proven BFME implementation at RVA 0x0093DD60.

Removing the old body also stopped emitting the already-ledgered
DynamicVectorClass<PendingSurfaceStruct>::Delete_All at 0x00980740. Explicit
instantiation retains this exact 25-byte helper, following the adjacent
SentenceDataStruct instantiation. No type, layout, name, pin or flag changes.
The scoped normal build verifies all 67 rows across provider and consumer,
all 32 DIR32 references and five float constants. Source-claim check passes.
Cleanup labels renumbered by the removal are reconciled by eh_state_pins.py.

BFME 2 donor59e3f8f825b698775df9e1728265fe962a5d0c02 reviewed:
Code/Libraries/Source/WWVegas/WW3D2/Render2DSentenceBuildTexturesBFME2.cpp,
Render2DSentenceDonorView.h and existing BFME 1 recovery provenance. The
BFME handle implementation was already recovered; the Zero Hour surface/
texture classes do not represent BFME's provider. No donor code imported.

Before link_check on the split provider: duplicate Build_Textures plus
selected non-retail definition; 0 linked bytes. After: current-object
selection is unknown because the local census is from 2026-10-19 and most
current objects are absent. Do not claim a linked-byte gain from this repair.
