# RVA 0x0076EB50: scripted-model secondary-interface indexed name getter

This proves the complete owner and subobject adjustment of the matched
`Rva0076EB50::method` body. It does not prove the original BFME method or
interface spelling. Retail pefile/capstone facts use image base 0x00400000.
Ghidra's stub-VA pattern search independently corroborates the table pointers.

## The table belongs to a secondary subobject

The independent native module-name/factory proof for W3DScriptedModelDraw is
in [the primary-slot note](0076b6e0-w3dscriptedmodeldraw-radius-decal.md).
Its factory, RVA 0x006BF040, calls constructor 0x00773360. That constructor
finally stores **0x01123C68** at object **+0x0C**, at 0x0077339E. Its earlier
+0x0C store of 0x01123848 is an abstract base interface, overwritten before
construction completes; it is not the final dispatch table.

Slot **10**, offset **+0x28**, VA **0x01123C90**, of the final secondary table
stores ILT VA **0x00408FA3** -> RVA **0x0076EB50**. The same slot occurs in
these independently constructor-installed secondary tables:

| Class | Secondary table VA | Store RVA |
|---|---|---|
| W3DHordeModelDraw | 0x011223A0 | 0x00751D1E |
| W3DQuadrupedDraw | 0x011232C0 | 0x0075974A |
| W3DSupplyDraw | 0x01125600 | 0x0077DB8A |
| W3DTankDraw | 0x011259E0 | 0x0077F087 |
| W3DTruckDraw | 0x011264E0 | 0x0077FB57 |

Every listed store targets +0x0C. The pointer pattern at RVA 0x0047F459 is
not a dispatch table: it is part of the REL32 operand of the call at
0x0047F458, which targets 0x00888400. Reject it as a raw-pattern false hit.
There are no direct transfers to the candidate's ILT beyond table dispatch.

## The body confirms that offset and ABI

At 0x0076EB57 it saves ECX in ESI; at 0x0076EB61 it computes **ECX = ESI-0x0C**
for the stale-state refresh call through ILT 0x00024F5F -> 0x0076C080.
The stamp at subobject+0x90 therefore lies at complete owner+0x9C. Treating
ECX as the complete owner would silently shift the layout by 12 bytes.

The index is the second stack slot; the first is a hidden return-object
pointer. Negative indices and unsigned indices >=3 return a null string.
For a valid index it reads the item pointer at subobject+0xD0+index*0x1C
(complete owner+0xDC), calls that item's vtable slot +8, then constructs
StringBase<char> from the returned char pointer through RVA 0x00888BC0.
This confirms an indexed name getter returning a string by value, but the
item's authentic type and name-slot spelling remain unproved here.

The 108-byte body has `ret 8` at 0x0076EBB9 and INT3 starts at 0x0076EBBC.
The existing source is already byte-matched; no body or ledger rename is
needed to preserve that progress. Native owner/secondary-slot evidence now
supersedes the older no-owner verdict. Neither the upstream header nor a
named BFME caller supplies this particular getter's method spelling, so
`getAnimationName` or another plausible name must not be introduced.
