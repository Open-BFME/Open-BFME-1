# RVA 0x002372C0: native-container draft, not matched

The owner and 994-byte RET4 extent remain as established in
002372c0-hordecontain-slot37.md. This bank uses an opaque address name;
it makes no claim to the native method spelling. The owner evidence allows
reconstruction despite older verdicts treating unknown spelling as a blocker.

Fresh Ghidra creation/decompilation at VA 0x006372C0 was cross-checked with
all 994 retail bytes using pefile and capstone. This body has no SEH prologue,
contrary to the earliest history verdict. It traverses the ObjectID tree
header at receiver+0x30 and the list returned by slot65 of receiver-0xC4.
Object IDs resolve through the native unsigned STLport hash at GameLogic+B0;
retail uses unsigned DIV and the redundant found-node/end test. It averages
eligible member positions and selects a nearby member position, testing
Pathfinder movement eligibility in the second list. The distance expression
is recomputed on acceptance, rather than stored before the comparison.

The six direct contracts were checked against tools/callees.py and existing
sources: Gen_001C5BE0::bfmeIsClear, _STL::_Rb_global<bool>::_M_increment,
Gen_001BEC20::bfmeScale, Pathfinder::validMovementPosition,
Thing::setPosition and Object::setLayer. The bank includes canonical Object,
Thing and WWMath coordinate declarations. The unsigned hash layout is an
address-derived view, not a new GameLogic definition or method identity.

An initial draft with native nontrivial coordinate copying, scalar x87
differences, and STLport hash/list traversal measured989/994 bytes with610
non-relocation differences and11 relocation-layout drifts. Its normalized
instruction similarity0.956 is NOT byte quality. This improves the old
886/890-byte drafts with812/805 differences. Separate x/y/z zero assignments
and authentic non-inlined visibility for the two existing tiny query callees
left those counts unchanged. The final iterator-order experiment and saved
measurement are recorded below.

Remaining promotion prerequisites: recover retail's0x38 frame (initial draft
uses0x34) and receiver register lifetime; use the canonical Pathfinder header
and reconcile the native struct/class Coord3D decorated argument tags rather
than adding alternate pins. Query helper names are the existing opaque
canonical names, not evidence of native Object member identities. No source,
pin or functions.csv change is authorized by this bank alone.

Initializing the first iterator before the mean and spelling count<=0
produced989/994B with614 differences, so it was not retained. The saved
draft measures989/994B,610 differences,first+2,11 relocation drifts,
quality0.3763 (including the five-byte size penalty twice).
