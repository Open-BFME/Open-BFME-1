# Dozer build/repair position helper: member ABI and native vector shape

## Identity and correction

Zero Hour's `GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdate.cpp`
defines `DozerAIUpdate::findGoodBuildOrRepairPosition` (line 1879) and its
`AndTarget` caller. The already matched BFME caller at RVA 0x002B8890, in
`DozerAIUpdate_findGoodBuildOrRepairPositionAndTarget.cpp`, makes both observed
calls to this helper using the same method name. This establishes the method
identity. It does not establish Zero Hour's static qualifier in BFME.

Retail RVA 0x002B6C40 saves the incoming ECX in EBP at +0x1E, preserving it
until the call to `AIUpdateInterface::findNearestLabeledContactPointOnTarget`
through ILT RVA 0x00015AE6 (body RVA 0x00272800). The matched caller likewise
supplies its receiver. The helper therefore uses thiscall, not the static
cdecl spelling of the old naked lift. Its final RET 0xC is at +0x1BA;
INT3 padding starts at +0x1BD. The complete body is 445 bytes, independently
created and decompiled at VA 0x006B6C40 in Ghidra.

The correction retains the established class and method name, changing only
`SA` (static) to `QA` (public member) in the decorated symbol. The old matched
row and naked source are retired through add_match's identity-correction path.
The matched caller's obsolete /alternatename is removed: it already has an
explicit pinned member ABI at ILT RVA 0x00043130, which independently decodes
to this body. No new pin or alternate name is added. The existing caller's
address-qualified slice name remains unchanged.

## Source shape and layouts

The served bank emits 445 bytes with eighteen non-relocation differences.
Using the existing native Vector3 header reduces that to thirteen; writing
`maxRadius = 100.0f` before `sourceToPathToDest = me` removes the remaining
store transposition. Both changes are needed. The emitted body then matches
all 445 bytes modulo relocation operands.

The shared BFME Object header replaces the bank's local Object layout.
Its position is Thing+0x38. Its GeometryInfo storage starts at Object+0xAC;
this routine reads only the established major-radius prefix member at +0x10,
hence Object+0xBC, using the existing GeometryInfo header's accessor. This
prefix view does not assert that the entire BFME geometry has the reference
header's size. Native Object/geometry/header adoption preserves the match.
The existing nontrivial coordinate copy shape is retained.

Callees retain their established names: Object::isUsingAirborneLocomotor
(RVA 0x001C1770 through ILT 0x0000A001), WWMath::Inv_Sqrt (RVA 0x00131C90
through ILT 0x00027A43), AIUpdateInterface's labeled-contact query, and the
free cdecl `findPositionAround` (RVA 0x001AF610 through ILT 0x00026C4C).
The latter takes three stack arguments, cleans up in the caller, and returns
its verdict in AL. No new callee identity or semantic flag name is introduced.
Strict build validation and the affected caller gate complement the probe.
