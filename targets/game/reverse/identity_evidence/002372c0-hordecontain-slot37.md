# RVA 0x002372C0: HordeContain slot 37, spelling unresolved

The 994-byte body is HordeContain's implementation of secondary
HordeContainInterface slot 37. The incoming receiver is complete
HordeContain+0xE4 and the one stack argument is an Object*. This proves the
concrete owner and ABI, not the method's original spelling.

All native facts below were checked against retail-1.03-unpacked
lotrbfme.exe, base 0x00400000, using pefile and capstone. GhidraMCP creates a
994-byte function at VA 0x006372C0; its decompiler is only a structural aid.

ILT RVA 0x0001E411 targets VA 0x006372C0. Its absolute pointers occur only at
VA 0x010AE2C4, 0x010AEDEC and 0x010B0874, all slot 37 of the AODHordeContain,
HordeContain and HorseHordeContain +0xE4 tables respectively. The constructor
stores and clean HordeContain constructor are established independently in
002408e0-hordecontain-destroymember.md. The concrete HordeContain table starts
at VA 0x010AED58, and its slot 37 is VA 0x010AEDEC. The base interface table
VA 0x010AE8E0, installed earlier by the same constructor, has the matched
pure-virtual reporting body VA 0x00C8C500 at slot 37, VA 0x010AE974.
Thus shared derived tables do not make the concrete owner ambiguous; they
inherit the HordeContain implementation. EA's file hint likewise points to
GameLogic/Object/Contain/HordeContain/HordeContain.cpp.

The body iterates a tree at interface+0x30 containing Object IDs, independently
resolves IDs through TheGameLogic's hash layout, adds eligible objects'
positions, and also includes objects from the primary contain-interface list.
It averages those positions and selects a nearby eligible member position,
including a Pathfinder::validMovementPosition check for the second list.
The final calls use the Object* argument as receiver for Thing::setPosition
through ILT 0x0003A1A7 and Object::setLayer through ILT 0x00035E0E. These
independently named callees corroborate the pointer argument and update
contract. RET4 at RVA 0x00237691 and 0x0023769F, followed by INT3 at
0x002376A2, proves the 994-byte extent and one stack argument.

Matched HordeContainInterface declarations inspected here still call this
slot slot37. No matched caller names the method. A descriptive placement or
center method name would therefore be a guess. Retain an address-derived
method name until native caller or declaration evidence resolves it.

Earlier 886/890-byte reconstruction experiments were far from retail and
had many relocation/layout differences. No conversion, new pin or bank is
installed by this owner proof. The previous shared-vtable-owner blocker is
resolved; authentic method spelling and large-body code generation remain.
