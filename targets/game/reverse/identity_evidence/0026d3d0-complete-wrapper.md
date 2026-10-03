# Complete 0026D3D0 wrapper, not an interior ILT

Retail and Ghidra agree on the complete 16-byte window:
`C7 44 24 04 01 00 00 00 E9 3D 2D DD FF CC CC CC`.
The first instruction overwrites one incoming stack word with 1; the second
jumps to ILT 0004011A, independently decoded as E9 to 002A8940.
That existing matched 741-byte SpecialAbilityUpdate::startPacking(bool)
body uses the incoming receiver, reads its boolean success argument, and
ends with RET 4 at 002A8C22, followed by padding.

Vtable VA 010B8D18 slot 19 contains 00431B4C, an ILT to 0066D3D0.
Matched WeaponFireSpecialAbilityUpdate constructor 0026D670 and destructor
0026D320 install this table. This establishes the entry and receiver context,
but no full method identity is inferred. Rva0026D3D0::method uses an opaque
unsigned stack-word view because retail never reads the original argument.
The view claims only one callee-cleaned 4-byte argument, not its source type.
The existing SpecialAbilityUpdate declaration/definition is reused in its
own TU; no second callee identity, alias or pin is added.

The generated five-byte j_0026d3d8 row covered only the final instruction.
Ghidra reports no references to that interior address. It is retired with
a tombstone, without editing generated source. The complete 13-byte parent
ends before the three INT3 bytes and is separately gated with its original
startPacking provider. callees.py was run; its call-only list omits the E9.
