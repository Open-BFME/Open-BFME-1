# AnimalAIUpdate::update, RVA 0x002B32A0 / 3352 bytes

This is a complete C++ bank, not a native landing. No function row or symbol
pin changed. The preferred body emits 3342 bytes and 194 relocations; the
retail body is 3352 bytes. `probe.py` reports 2221 differing non-relocation
positions and ten missing bytes: 1121/3352 equal masked positions, score
0.3344272076372315. Normalized instruction agreement is 0.949 with 59
structural differences; that is a separate diagnostic, not byte coverage.
175 relocation sites do not align, so this is not a strict resolved match.

## Identity and receiver

`AnimalAIUpdateCtorThunk.cpp` contains the independently recovered 118-byte
constructor at 0x002B3090. It installs VA 0x010C5590 at full-object +0x10.
That vtable's slot 0 routes through ILT 0x0001D9F3 to this 3352-byte body.
The matching factory allocates 0x358 bytes. The body therefore receives the
secondary update-interface pointer, ten hexadecimal bytes into the object;
its module-data and object pointers are at this-0xC and this-8. AI commands
use this+0x10; primary virtual slot +0x1FC uses this-0x10. A native MSVC
multiple-inheritance experiment independently reproduces this secondary
receiver convention. Retail debug literals supply the AnimalAIUpdate.cpp
file and method behavior; this is not a guessed identity from those alone.

Fields at secondary-this +0x334, +0x338, +0x344 and +0x345 are the scaring
object ID, original position, processed flag and returning flag. Data table
0x00C89AC8 proves FleeRange/+0x64, FleeDistance/+0x68,
WanderPercentage/+0x6C, MaxWanderDistance/+0x70,
MaxWanderRadius/+0x74 and UpdateTimer/+0x78.

## Corrections to the old bank

The periodic enemy search ends before the idle/wander handling. Both wander
branches call getUnitDirectionVector2D twice, copy the second result, add
cos/sin to X/Y, scale all XYZ by the random distance, then add the current
position only to X/Y. The old bank discarded the direction and Z scale.
No-emitter distance uses Coord3D::GetLengthEstimate, not squared distance.
Arrival at the original position uses a strict less-than 10 comparison.
The emitter test is squared distance greater than float(integer radius
squared), not less-than-or-equal. Two virtual +0x1FC calls, repeated current
state calls, the special flee command, and the debug flag around only the
emitter wander move are retained. These differences were checked directly
against the complete retail instruction stream.

## Independent direct-callee and filter evidence

All 22 distinct direct targets were inventoried with callees.py before
writing. Existing native owners establish AIUpdateInterface::update,
getCurrentStateID (0x000C3D90, unsigned const no-arg), AICommandInterface
commands, TerrainLogic::getLayerForDestination, GameLogic::findObjectByID
(int argument), Thing getters, Overridable traversal, Coord3D length,
random integer generation and Sin/Cos. The 33-byte distance function at
0x0016E370 has the existing address-derived Gen_0016E370/BfmeSpotCN
signature; the bank uses it without inventing an Object method name.

The periodic mask constructor at 0x000C4BC0 is 129 bytes: reset six words,
set four integer-selected bits, return this, RET20. The one-index constructor
at 0x000C4B00 is 57 bytes and RET8. Their actual noinline bodies are visible
in the bank, not synthetic pure stand-ins. The periodic one-mask filter
keeps the existing Rva0025F2D0KindOfAnyFilter identity: VA 0x010B243C,
61-byte copying constructor and the independently native isAnyKindOf slot.
The relationship filter VA 0x01085DC0 is supported by existing native
allow/getPlayerMask/destructor owners; its object, flags=3 and bool=false
fields agree with the retail stores.

The 102-byte constructor at 0x000C3DD0 installs VA 0x01083B70, zeros next,
copies two 24-byte masks to +8/+0x20, and returns with RET8. Its predicate
slot routes through 0x00031DF9 to native 0x001DCC80 (isKindOfMulti).
This independently proves PartitionFilterAcceptByKindOf and its existing
constructor pin through 0x000382FD. The vtable has an older address-derived
ledger spelling; do not add a conflicting pin just to resolve this bank.

The 22 logger calls are variadic cdecl, with the sink passed on the stack,
through 0x0003A17A to 0x00065C80. CRCParameterCheck ownership is independently
supported by its native body and engine users; the bank keeps an
address-derived method label. Remaining alias bindings still require strict
resolution before landing. No speculative dependency pin was added.

## Bounded levers and resumption

The first mismatch is the stack frame: 0x8C versus retail 0x74. Authentic
visible four-index BitFlags construction combined with reuse of the
no-emitter coordinate changes it to 0x6C; this alternative is 3334 bytes,
2359 differing positions, score0.2908711217183771, normalized shape0.946.
One-index visibility alone does not change it. Six entry declaration orders,
inline state getters, explicit mask temporaries, logger capture, native
coordinate forms, inline/noinline accept-filter construction and full
multiple-inheritance layout were measured. No dummy locals, volatile,
assembly, barriers or unsupported pure/no-throw assumptions were used.

The previous preferred source emitted 3499 bytes with 2480 differences:
872/3499 equal masked positions, measured score0.2492140611603315. Its0.68
header was an author estimate; the original bytes were archived before that
metadata was corrected. The original archive is targets/game/reverse/attempt_history/0x002b32a0/34be6b385390395add22c69fabe23510533e06353dcd7294e7dd4b577b788829.json.
The coordinate-reuse alternative is targets/game/reverse/attempt_history/0x002b32a0/210aa37aa2201d07a456bb9f31f9cd523193dbfa847056f9d8a86055cff1b3a6.json.
The preferred bank is targets/game/reverse/attempts/0x002b32a0.cpp.
