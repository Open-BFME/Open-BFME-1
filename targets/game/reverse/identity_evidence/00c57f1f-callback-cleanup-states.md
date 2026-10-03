# Callback dispatch cleanup states at 008A6440

All addresses below are RVAs. The unchanged native source is
`game/Libraries/Source/EA/Apt/CachedCallbackLookup008A6440.cpp`.
Retail parent 008A6440 loads handler 00C5801E at +8. That handler
loads FuncInfo 00E473AC, whose 18-state unwind map is 00E4731C.
The native parent strictly matches 2156 bytes, including its EH state stores.

The actions are **not** identified by byte similarity alone: all 18 native
actions have the same 15-byte instruction shape. The compiler handler's
DIR32 relocation selects FuncInfo `$T798`, which selects unwind map `$T802`.
Each state entry's second dword independently selects the action below.
All four predecessors are -1, matching retail.

| Action | State | Retail map action dword | Compiler map relocation | Native action | Last RET |
|---|---:|---|---|---|---|
| 00C57F1F | 1 | 00E47328 | +0xC | `$L724` | 00C57F2D |
| 00C57F6A | 6 | 00E47350 | +0x34 | `$L729` | 00C57F78 |
| 00C57FB5 | 11 | 00E47378 | +0x5C | `$L734` | 00C57FC3 |
| 00C58000 | 16 | 00E473A0 | +0x84 | `$L739` | 00C5800E |

Each action pushes size 0x24 and EBP+4, calls 00897670, pops eight bytes,
and returns. The next byte starts a distinct cleanup rather than padding.
Ghidra raw memory agrees with the independently decoded retail PE bytes.
Every selected COFF symbol is executable code (section flags 0x60501020),
with eleven concrete bytes and one REL32 at +7 naming the existing
`??3Rva00897670HeaderedDelete@@SAXPAXI@Z`. That native sized-delete
implementation removes the eight-byte allocation header before freeing.
No callee alias, new semantic owner, or source edit is introduced.

The final scoped gate verifies the parent and all four selected actions,
including all 90 existing DIR32 references. Opaque address names retain the
separate retail identities despite the identical action shapes.
