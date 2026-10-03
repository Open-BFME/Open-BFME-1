# RVA 002C4FD0: typed field setters and native call ABI

The retail body begins after INT3 at 002C4FD0 and ends RET8 at 002C5147,
followed by INT3 at 002C514A: 378 bytes. Ghidra creation/decompilation and
independent PE disassembly agree. The matched BfmeConv1969 caller reaches
ILT0003C8CB, and Rva002C5240's command dispatch supplies the object and
command-source arguments. These callers have synthetic names; no EA owner
or member name is established. Production therefore uses Rva002C4FD0::method.

The preferred bank measures 378 bytes with fourteen non-relocation register
differences, despite a normalized shape of 1.000. Two inline setters for
fields +344 and +348 fix the first scratch-register choice and the subsequent
rotation through the floating calculation and geometry copies. The ordinary floating coordinate-copy trial retains fourteen differences;
the existing Coord3DBase raw assignment grows to 394 bytes with 260
positional differences. The setters alone are sufficient; no volatile,
assembly, artificial reads, or extra runtime operations are needed.

The final source includes canonical Object/Thing, Snapshot, coordinate and
CommandSourceType headers. Object+38 position, +74 ID, and +AC geometry match
the declared offsets. The legacy geometry.h explicitly describes the smaller
Zero Hour layout; canonical object.h itself warns that its 23-word/92-byte
BFME GeometryInfo is not geometry.h's type. Therefore the TU retains a
92-byte GeometryInfo view using opaque storage after the Snapshot base,
not fabricated vector element types. The independently matched 194-byte copy
constructor at 000FFD10 copies through +58 and two vectors at +2C/+38.
The +10 float read is kept unnamed; name_oracle supplied no BFME field witness.
No shared header is changed to force the old ZH layout onto BFME.

Both geometry copies bind to 000FFD10 via ILT0002B355; both destructor calls
bind to 000FFCA0 via ILT000309F4. The movement call is the matched
AIUpdateInterface::privateMoveToPosition at 00278280 through ILT0002D6F5.
Its existing declaration is protected virtual, with (const Coord3D*,
CommandSourceType). The TU uses a qualified direct call matching retail,
with friendship solely to permit the opaque receiver view. The earlier
nonvirtual protected declaration was rejected by the gate and corrected;
no compensating pin was added.

The exact old bank is preserved in 002c4fd0-original-bank.cpp.txt. Narrow
snapshot-bound corrections cover only the historical synthetic bank names;
no established production identity is replaced. The old production row is
the generated d_002c4fd0 placeholder.
