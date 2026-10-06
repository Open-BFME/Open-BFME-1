# Native node walk at 0x008BE2C0

The complete 230-byte body is `[0x008BE2C0, 0x008BE3A6)`. Its final
`ret 4` begins at 0x008BE3A3; ten INT3 bytes separate it from the next body.
The native entry dereferences the ECX receiver twice, then loads the node
link at +0x58. The sole stack argument is tested only for null. Recursion
passes the current node as that argument and uses its info pointer +0x24
as the new receiver. The result is unused; no consistent return value is
defined. No external caller or original owner identity is proved.

The source therefore uses the address-qualified `Rva008BE2C0` receiver and
node/info/string views. They describe observed field offsets, not complete
game classes or a proposed `BfmeSuffixParser` identity. `AptInput.cpp`
independently corroborates node flags +4, name +0x0C, link +0x4C, info +0x50,
the info's iterator list +0x10, and the two-word tagged iterator entry.
No shared header declares these local view types or iterator declarations.

## Complete relocation proof

- DIR32 operand +0x22 names the existing `g_rva012D5298Empty` datum with
  its canonical `EAStringC::StringDataC` type. The physical owner is
  `game/GameEngine/Source/Common/Data/Rva012D5298.cpp`.
- REL32 operand +0x3F calls the 55-byte `BfmeIteratorList1285::bfmeFirst1285`
  at 0x0089D100, defined in `BfmeIteratorFirst1285.cpp`.
- REL32 operand +0x98 calls the 49-byte `BfmeIteratorList1285::bfmeNext1285`
  at 0x0089D140, defined in `AptNativeHash.cpp`.
- REL32 operand +0xD0 recursively calls this same 230-byte body.

The iterator provider definitions establish ordinary thiscall conventions,
their returned iterator pointer and the one-pointer argument to Next. Both
provider TUs pass the unchanged scoped byte, data-reference and body checks.
The walk's production-path gate passes all 230 bytes with all four references
resolved, one DIR32 reference, and no skipped string/constant/body checks.

## Source and emitted code

Integer locals for the two unsigned-short lengths reproduce the zero-extended
comparison and native `memcmp` expansion. Materializing the iterator-list
receiver before Next preserves its observed load order. Reading `flags04`
directly in the two recursive-call conditions retains the retail branch
structure. No assembly, volatile barrier, forced inlining or register trick
is used.

The final object defines only the 230-byte walk. There are no predicate
copies, vtables, EH functions or extra data definitions. An earlier exact
walk probe emitted two non-retail 31-byte predicate copies; that form was
rejected and replaced before publication. No new pin or baseline is needed.

Unchanged `progress.py` reports +230 C++ bytes and exact C++ coverage +230,
with ASM-only coverage -230 and total exact coverage unchanged. No linking
gain or original semantic name is claimed.
