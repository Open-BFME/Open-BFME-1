# Native D3DX mask leaves at A07FC6

These are independently delimited functions, not a guessed subdivision of
the uncovered interval. The original `inputs/vendor/d3dx9/d3dx9.lib` member
`obj\i386\createmesh.obj` contains the following distinct code COMDATs:

| Section | Original owner/method | Bytes | Retail RVA |
| --- | --- | ---: | --- |
| 354 | GXTri3Mesh<unsigned short,1,65535>::UnlockVB | 13 | 00A07FB9 |
| 356 | same owner, BHasNeighborData | 10 | 00A07FC6 |
| 358 | same owner, BHasPointRepData | 10 | 00A07FD0 |
| 360 | same owner, BHasPerFaceAttributeId | 10 | 00A07FDA |
| 362 | same owner, BHasPerFaceAttributeIndex | 10 | 00A07FE4 |
| 364 | same owner, BHasAttributeTable | 10 | 00A07FEE |
| 366 | same owner, BSharedVB | 10 | 00A07FF8 |
| 368 | same owner, WGetPointRep | 18 | 00A08002 |

Every section has zero relocations. Concatenating their complete bodies
produces a 91-byte sequence occurring exactly once in retail .text, starting
at A07FB9. The last 18-byte word-indexed getter is also an existing ledger
anchor. Ghidra raw memory independently agrees with all 91 bytes. Thus each
interior start and RET boundary comes from an original function symbol and
its unique complete sequence placement, not merely a guessed RET split.

The six mask signatures all end `ABEIXZ`: private const thiscall, unsigned
int return, no stack arguments. Each body loads dword [ECX+218], ANDs its
separate mask (1,2,4,8,16,32), and returns. These return the masked integer,
not a normalized bool. The native archive also has a uint-indexed family;
its bookend differs, and it is not merged with this address sequence.

The reconstruction uses an address-qualified storage view and methods,
including the field's measured offset. It makes no new semantic method-name
claim and adds no pin. Only individually listed matched ledger rows are
promoted; documenting the remaining original sections is not a claim on them.
