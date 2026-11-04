# 0x0113C614 vftable (link queue #18): the blocker is a row-identity cascade

Seat sonnet-seat-a, BFME 1 at origin/master 2026-11-05. No source edit retained.
Follows 0113c614-material-vector-slots-20261101.md and
20261102-material-vector-id-slots/index.md.

## Why both emitted copies are "wrong"

Reproduced with RetailTruth (tools/link_census.py): matinfo.obj's 24-byte copy
(digest b91e8deb677b) names six VertexMaterialClass functions. The ledger
puts them at 0x94E3E0 (==), 0x974500 (Resize, shared alias row), 0x94E4F0
(Clear), 0x93D7E0 and 0x94E430 (ID). Retail slots hold 0x9305B0, 0x92F6B0,
0x930290, 0x930240, 0x930210, 0x930270 (RVA), so every relocation misses.

## New observation: 0x94E3E0 / 0x94E4F0 / 0x94E430 are not VertexMaterialClass*

A second DynamicVectorClass table sits at VA 0x0113D0B0 (slot 1 = 0x94E3E0,
slot 3 = 0x94E4F0). Its only .text store is in MeshLoadContextClass::
MeshLoadContextClass (0x970180, store at 0x970243), next to the 0x113C614 store
at 0x970214. Slot 0 of that table is the ledger's
??_G?$DynamicVectorClass@PAULegacyMaterialClass@MeshLoadContextClass@@@@
(0x94F0E0). So the matinfo.cpp rows
?Clear@?$DynamicVectorClass@PAVVertexMaterialClass@@@@ (0x94E4F0),
??8?$VectorClass@PAVVertexMaterialClass@@@@ (0x94E3E0) and
?ID@?$VectorClass@PAVVertexMaterialClass@@@@ (0x94E430) look like the
LegacyMaterialClass* instantiation, mislabeled. Observation from retail
layout and ledger labels; not a verified identity.

## Cascade to fix it (why it was not done in one pass)

1. Six slot rows (agg_def.cpp, assetmgr.cpp x3, VectorShaderDeletingDestructor.cpp,
   W3DTankDraw.cpp alias, ode.cpp alias) re-identified to VertexMaterialClass*.
2. matinfo.cpp's four VMC-labeled rows re-identified (LegacyMaterialClass*),
   which retypes the bodies in matinfo.cpp and the $L funclet rows anchored on
   MaterialCollectorClass ctor numbering (dup_00C5CE00 / uw_00c5ce11, 20 of 35
   rows break if the ctor is deleted).
3. Then one TU emits a vtable whose six slot names land on the new rows.
Each step moves matched rows with +0 exact bytes; the 517 B it unlocks is a
linking figure only.

Released unrepaired. Next agent: start with step 1 using the per-slot evidence
in the two earlier notes; slot 0 needs ??_G versus ??_E settled first.
