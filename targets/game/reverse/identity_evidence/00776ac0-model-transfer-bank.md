# 0x00776AC0: complete transfer reconstruction, still unlanded

Retail extent is 0x00776AC0 through RET 4 at 0x007777FB (3390 bytes).
Ghidra get_xrefs_to(0x00411CBB) returns data VA 0x01123D44,
slot 3 of table 0x01123D38. Existing W3DModelDraw family witnesses support
the owner, but conflicting crc/xfer pins do not establish a full method name.
The bank deliberately uses Rva00776AC0Owner::rva00776AC0.

## New reconstruction evidence

The native Xfer header in Common/System/xfer.h supplies every dispatched
slot: loading +4, storing +8, light CRC +0x10, version +0x28,
coordinate +0x60, ASCII +0x68, float +0x6C, uint +0x74, int +0x78,
and bool +0x8C. The version is the two-byte pair {1,4}.
The existing Zero Hour transfer body does not describe this BFME body.
Retail has two vectors at owner +0x4C/+0x58 of 24-byte records:
one AsciiString, a bool at +4, and four floats at +8/+C/+10/+14.
The vector at owner +0x130 contains 32-byte records: render pointer,
native STLport string, three float coordinates, and an int at +0x1C.
Both load and save paths, the animation restore, all tail scalar transfers,
and the version gates are reconstructed.

Retail eh_info reports handler C4FF35, FuncInfo E3F854, 12 states.
State 0 destroys the 24-byte record at EBP-4C through 753450 (string
release); 1 is placement cleanup; 2/3 protect the load-path native string
and record; 4/5 protect its ASCII temporaries; 6/7 cover placement copy;
8/9 protect save-path string and record; 10/11 protect ASCII temporaries.
No manually written EH state, assembly, or byte emission is in the bank.

## Measured result

Native AsciiString, STLport vector/string, and Coord3DBase are included.
An address-qualified coordinate copy wrapper keeps the nested memberwise
copy; an address-qualified Version constructor keeps the two-byte object's
lifetime and stack home. These source distinctions recover retail's 0x7C
frame and the entire 3390-byte extent.
The final probe differs in 22 non-relocation bytes, all at +0x185..+0x19C:
FMUL/FSTP interleaving with argument pushes for the render +0x20C call.
All 50 relocation sites align. Masked byte score is 3368/3390 =
0.9935103244837759; instruction shape is 0.998. This is NOT strict
relocation verification and does not claim production progress.

Six ordinary expression/local-order variants leave the same residue;
compound multiplication grows to 3393B. /G5, /G6 and /GB leave the same
22 bytes; /G7 and /Op change the body substantially. The source retains
the default flags. No shared header was changed.

## Integration still required

The bank's address-qualified callable declarations are unbound ABI views,
not new identities or pins. Before production, reconcile each with its
existing retail target. Direct call inventory (ILT -> body):
2FD88->1139A0; 8CA1->10C3E0; 37BA->76AEA0;
26DD7->1CB270; 3D87->754E10 (twice); 36539->7709C0 (twice);
334EC->768D20; 2A801->771B10 (twice); 2B297->A5810;
32308->774580; 1A50->10C460; 1CA8->765FB0.
The vector erase currently carries ProductionPrerequisite's name despite
this caller's distinct string/bool/four-float payload. Do not invent a new
semantic identity or retire that claim on shape alone.
Create_Render_Obj at 8FF290 has its real existing render-object return type;
the bank's separate render interface view must be bridged to that declaration.
Scene datum VA 012F8058, all dynamic render slots, string/allocator helpers,
and all EH cleanup bindings require strict verification before landing.
