# RVA A08043/A0804D native mesh mask boundaries and ABI

Original d3dx9.lib member `obj\i386\createmesh.obj` independently defines
the two code COMDATs in sections374/376. Their names are respectively
`?BHasNeighborData@?$GXTri3Mesh@I$0A@$0?0@@ABEIXZ` and
`?BHasPointRepData@?$GXTri3Mesh@I$0A@$0?0@@ABEIXZ`: unsigned-int return,
const thiscall, no arguments. Each entire body is ten bytes with zero
relocations, loading dword [ECX+218], applying its mask (1/2), then RET.

Positive original function boundaries come from placement of the complete
native section sequence, not just the appearance of RET bytes. Sections
372/374/376/378/380/382/384/386 are the13-byte UnlockVB wrapper, six10-byte
mask methods and the16-byte dword-indexed WGetPointRep. Their concatenated
89 bytes occur exactly once in retail .text, at A08036. Thus the claimed
starts A08043/A0804D and final RETs A0804C/A08056 have original code-symbol
witnesses, alongside the already-claimed native getter at A0807F. Ghidra
read_memory independently agrees with all89 bytes.

The ushort-indexed family has a different18-byte getter and its unique
91-byte sequence starts A07FB9. Identical mask instructions do not merge
those owners or function entries. This reconstruction uses a separate fully
address-qualified storage view and method names for the two dword-family
bodies. It claims no new semantic owner/method spelling, boolean return,
callee pin, or remaining native method.

## Remaining masks, independently checked in session 4

The same original object gives four more distinct code COMDATs. Their full
89-byte enclosing sequence was re-read from the archive and found exactly
once in retail .text; Ghidra read_memory at VA 00E08036 agrees byte for byte.

| Section | Original method (same uint-indexed owner) | RVA | Mask | Final RET |
| --- | --- | --- | ---: | --- |
| 378 | BHasPerFaceAttributeId | 00A08057 | 4 | 00A08060 |
| 380 | BHasPerFaceAttributeIndex | 00A08061 | 8 | 00A0806A |
| 382 | BHasAttributeTable | 00A0806B | 16 | 00A08074 |
| 384 | BSharedVB | 00A08075 | 32 | 00A0807E |

Each original symbol ends `@?$GXTri3Mesh@I$0A@$0?0@@ABEIXZ`; each section
is ten code bytes without relocations. These independently establish unsigned
int return, const-thiscall/no stack arguments and the separate entry/return
boundaries. The reconstruction retains address-qualified methods and the
existing measured storage view. Only ledgered methods are promoted.
