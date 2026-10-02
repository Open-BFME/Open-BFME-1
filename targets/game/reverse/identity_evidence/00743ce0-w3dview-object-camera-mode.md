# RVA 0x00743CE0: W3DView object camera operation, spelling unresolved

The owner is W3DView. This does not establish the original method spelling,
so the generated body and address-derived ledger identity remain unchanged.

## Native ownership and route

The retail PE constructor at RVA 0x00745B10 stores primary vtable VA
0x011217A0 into [ESI] at 0x00745B5D (operand 0x00745B5F). The complete
destructor at 0x007461B0 reinstalls that table (operand 0x007461D9).
Independently matched init@W3DView (0x00742700) and reset@W3DView
(0x0073AC90) occupy slots 4 and 5, through ILTs 0x0002A487 and 0x00014A38.
The authentic W3DView scalar-deleting destructor is slot zero.

Slot 115, VA 0x0112196C = table + 0x1CC, contains VA 0x00427F84.
That ILT's E9 targets this body. Ghidra search_byte_patterns for
84 7F 42 00 returns exactly 0x0112196C; direct retail memory confirms it.
An executable E8/E9 scan finds only the ILT entering the body; no direct
caller of the ILT or stored body pointer was found.

## Body and extent

The receiver saves ECX in ESI. Argument three is tested as a byte. On its
true path, slot +0x1C8 is tested; the first argument is resolved through
GameLogic::findObjectByID. Slot +0x1D0 is compared with the found object's
+0x74 field; slot +0x1D4 receives that field. The operation saves view
state into globals VA 0x012F9DC0..0x012F9DF8 when [ESI+0x2439] is clear,
then sets that byte. It moves the view through slot +0x54 using the object's
position at +0x38, changes pitch through +0xF0 and updates heading at
[ESI+0x28]. Argument four participates in the branch at 0x00743E3F.
The false initial branch calls slot +0x1D8.

Neighbour slot 114 resolves to the existing getter at 0x00746080,
which returns [ECX+0x2439]; slot 113 is the separately matched named-entry
operation at 0x00743BF0. These facts support an object camera mode, but do
not prove a native method name or an exact four-argument declaration.
Zero Hour's camera-lock methods have different interfaces and are only hints.

Both native exits use RET 0x10: 0x00743ED5 and 0x00743EEF. The last return
ends at 0x00743EF2, followed by INT3: extent 530 bytes. All addresses above
were checked against inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe.
No conversion or identity rename is claimed.
