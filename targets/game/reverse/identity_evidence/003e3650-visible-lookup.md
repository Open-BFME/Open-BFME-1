# Pathfinder cell walk at RVA 0x003E3650

The existing byte-matched world-space overload at RVA 0x003E7F20, in
`pathfind_iterateCellsAlongLine_world.cpp`, names this exact cell-space overload
and passes two ICoord2D references, a PathfindLayerEnum, and an opaque
Rva003E3650Struct pointer. Its pinned ILT RVA 0x0004940E is an E9 to RVA
0x003E3650. The original Zero Hour cell-walk family and matched caller establish
Pathfinder::iterateCellsAlongLine; the user-data type keeps its address because
a forwarder cannot establish the original record name.

In the unpacked retail image, the body starts at RVA 0x003E3650. The loop's
ordinary zero return ends with RET 0x10 at RVA 0x003E3856. Its separate found
arm starts at RVA 0x003E3859, stores the found Object, and returns one with
RET 0x10 at RVA 0x003E3867. INT3 padding starts at RVA 0x003E386A, bounding
538 bytes. Ghidra independently recovers the Bresenham walk, layer-map lookup,
obstacle object resolution, template mask test and ignored-ID check.

The served bank already emitted 538 bytes, with eighteen differences caused
by EBX and EBP exchanging the coordinate values. The actual noinline
`GameLogic::findObjectByID` definition in the existing
`GameLogicObjectLookup.h`, enabled with `BFME_GAMELOGIC_LOOKUP_VISIBLE`, makes
the compiler reproduce the complete caller. This is the real 82-byte hash-map
lookup at RVA 0x0009A510, not a made-up read-only stub. Its emitted copy is
independently probed; the authoritative ledger row stays with
`SelectionAll00595230.cpp`. The existing ILT pin remains unchanged.

The caller also adopts the canonical BFME Object header. The bank's scalar
`m_kindOf` at ThingTemplate+0xD0 is represented as the third word of the full
six-word block at +0xC8, matching the existing byte-verified ThingTemplate
constructor/copy layout and BitFlags<192> storage. The test remains word 2,
mask 2; no semantic flag name is inferred. The buffer and coordinate views
remain local, and the user-data name is still address-qualified.

The two other callees are existing independently matched definitions:
PathfindLayer::getCell at RVA 0x003FBAB0 through ILT RVA 0x000105CD, and
Overridable::getFinalOverride at RVA 0x00087A80 through ILT RVA 0x000022BB.
The source adds no pin or alias. Strict add_match/build verification is required
in addition to the relocation-masked caller/helper probes.
