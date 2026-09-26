# TerrainLogic trigger-area lookup identity at 0x001AAC30

The retail `TerrainLogicBase` constructor at 0x001ADB80 installs primary
vtable 0x0109C428. The derived terrain constructor at 0x006BE070 installs
primary vtable 0x0111D090. In both, slot 31 routes to the matched
`getWaypointByName`, slot 32 to `getWaypointByID`, slot 33 to
`getClosestWaypointOnPath`, and slot 35 to `isPurposeOfPath`. The following
slot 36 (`+0x90`) routes through ILT 0x0003166F to **0x001AAC30**. In the
native `TerrainLogic.h`, `getTriggerAreaByName(AsciiString)` immediately
follows `isPurposeOfPath` in the virtual declaration order.

The 255-byte retail body walks the list rooted at VA 0x012ACB50, copies and
compares the AsciiString at each node's `+0x08`, and returns the matching node
or null. That global is independently pinned as
`g_bfmePolygonTriggerTable` from the TerrainLogic water lookup. The native
`TerrainLogic::getTriggerAreaByName` implementation walks
`PolygonTrigger::getFirstPolygonTrigger()` via `getNext()` and compares each
trigger name. The body returns with `ret 4`: one by-value AsciiString stack
argument, with `this` in ECX unused by the body, fits the declared virtual
member ABI.

`game/GameEngine/Source/Common/Rva001AAC30LookupByName.cpp` already emits the
exact retail bytes via the free-function symbol
`?bfmeLookupByName@@YGPAVBfmeEntryCN@@VAsciiString@@@Z`. The ledger's
`object-symbol=` alias retains that verified implementation while recording
the proven virtual method identity. The separately compiled native definition
in `TerrainLogic.cpp` remains marked `present-unmatched`; this correction
does not claim that its emitted bytes match.
