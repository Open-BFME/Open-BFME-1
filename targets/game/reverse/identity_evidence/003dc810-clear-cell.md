# Pathfinder::clearCellForDiameter — RVA 0x003DC810

The GeneralsMD AIPathfind.cpp twin at line 6724 scans the cells covered by a
path diameter, cuts the outer corners, checks stationary occupants and fences,
and retries at diameter minus two. BFME preserves that algorithm while adding
an unsigned crusher level and a sixth Boolean stop-on-failure argument.

The already matched GroundPathPassableStruct::cellCallback at 0x003DEDA0
(PathfindCellCallbackDeda0.cpp) names clearCellForDiameter and calls its ILT
0x00048D29, which branches to 0x003DC810. It supplies the pathfinder receiver,
cell coordinates, cell layer, diameter, and a final literal one. Its older
all-int declaration describes the same machine inputs but is not the recovered
source signature. The retail body consumes the sixth input as a byte, uses
unsigned comparison after sign-extending the occupant crushability byte, and
ends with RET 0x18 at 0x003DCAE6. INT3 starts at 0x003DCAE9: exactly 729 bytes.
Ghidra read_memory independently confirms that return and padding.

The data offsets are the established BFME pathfind view: map +0x10, extent
+0x14, layers +0x85c with stride 0x44, cell info +0, cell type/flags in the
three-bit fields at +0x0c. This scan looks up an ObjectID from info +0x18; the fence predicate
reads bit one at +0x24. The old bank called +0x18 m_posUnitID, but the
existing getPosUnit body at 0x003D4BF0 demonstrably reads +0x20. This source
therefore uses an address-qualified side-table view and accessor, without
asserting that the +0x18 ID is the field named by that existing getter. Unused side-table fields remain opaque. The partial
pathfind shim cannot express this six-argument method or these cell operations.

Calls bind to existing native bodies: PathfindLayer::getCell (0x003FBAB0,
85 bytes), Object::getCrushableLevel (0x001C74E0, 57 bytes), and
GameLogic::findObjectByID (0x0009A510, 82 bytes). No new pins are needed.
The canonical Object header supplies its layout; GameLogicObjectLookup.h
supplies the actual noinline lookup. Its authoritative ledger row is unchanged.

Starting from the bank yielded 745 bytes with 521 nonrelocation differences,
mostly from a misplaced failure block. Merely exposing the real lookup changes
that block placement and produces all 729 retail bytes. Canonical Object
adoption preserves the exact result. This is callee side-effect knowledge,
not a barrier, forced register, synthetic helper, or alternate calling convention.

Validation: the scoped strict gate passes the complete 729-byte method, its
callee bindings and both DIR32 references. The visible lookup emission was
also separately probed against its full 82-byte retail extent and is exact.
