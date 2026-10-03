# BuildAssistant::addBibs, RVA 0x000FF290

## Identity and extent

The constructor at RVA 0x000FDA80 stores BuildAssistant table VA 0x010860D8
at RVA 0x000FDAA5.
Slot 13 at VA 0x0108610C contains VA 0x0043D7BC, a five-byte jump to VA
0x004FF290. The Zero Hour BuildAssistant declaration order identifies addBibs;
the implementation in GeneralsMD/Code/GameEngine/Source/Common/System/
BuildAssistant.cpp:1073 confirms the structure filter, vision-plus-three-radii
range, removable-object exclusion and immobile faction-bib dispatch. The
BFME table/body alignment agrees with these independent algorithm witnesses.
Retail RET 8 is at RVA 0x000FF451, and INT3 begins at 0x000FF454: 452 bytes.
Ghidra's reachable body omits six bytes of internal alignment.

## ABI and source visibility

The bank's integer-bit spelling of the range and opaque filter constructor
leave a 0x54-byte frame, versus retail 0x50, with 23 differing bytes. Using
the already-pinned float-range spelling at 0x009F2960 alone changes nothing.
The actual noinline PartitionFilterAcceptByKindOf constructor copies both
six-word masks into its +8 and +0x20 subobjects; it retains neither reference.
Making those copies visible closes every caller byte, including reuse of the
dead build-argument slot for range and then the returned iterator handle.
The complete helper independently matches 102 bytes through RET 8 at C3E33;
its derived vtable operand is VA 0x01083B70, already recorded. Its existing
symbol pin routes through ILT 0x000382FD to 0x000C3DD0. No new pin or helper
ledger identity is added.

The native Object and GeometryInfo headers preserve the exact caller. The
ThingTemplate geometry prefix is at +0x60, the six KindOf words at +0xC8 and
vision range at +0x3A4, all confirmed by name_oracle and retail operands.
The code never constructs the opaque ThingTemplate geometry storage.
The filter base-vtable operand is the recorded VA 0x01083B5C. KINDOFMASK_NONE,
the float constant 3.0 and all direct call operands are checked by the strict
gate; no modulo-relocation result alone is accepted as the conversion.
