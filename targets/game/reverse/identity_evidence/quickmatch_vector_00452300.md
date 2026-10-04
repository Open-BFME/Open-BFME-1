# Native map-pointer vector: 00452300 / 00452E10 / 00453480

The 265-byte overflow and 50-byte push-back rows replace generated four-byte
POD stand-ins using the actual vendored STLport 4.5.3 vector. These two
rows are classified vendored=stlport-4.5.3, not hand-authored game logic. No STLport source,
filename-sort implementation, or import-address cell is changed.

## Independent native contract

The existing matched `MapCache::findMap(AsciiString)` at 00454500 returns
`const MapMetaData *`. Its quick-match caller 0055AE10 appends that returned
pointer itself, and calls the same overflow as collector 00453480. The
collector appends the address of a map tree node's value at +14, never a copied
four-byte record. The matched metadata lifecycle and native reads establish
player count +20 and flags +24/+25/+26. Pointee constness is not recoverable
from machine bytes alone; the established lookup return is the independent
source contract supporting the consistent const-pointer specialization.

Overflow is thiscall with five stack slots: position, pointer-value reference,
true-type tag reference, count and at-end bool. Native vector fields are
start/finish/end at +0/+4/+8 with four-byte elements; the body ends in RET20.
Push-back is thiscall with a reference to one pointer value and RET4. Its
call at +2B uses ILT 0002F3EC to overflow 00452300. Collector is cdecl with
flags/vector parameters and RET; its overflow call is at +BD through the
same ILT. Genuine template definitions reproduce all three complete extents.

The collector's existing address-qualified name is retained. Native xrefs
through its ILT 0000BCD5 reach population 00456A90, generated 0052A2E0 and
naked getDefaultMap 00457FB0. Only population had an authored typed vector
contract. It now directly supplies `vector<const MapMetaData*>` without a
cross-specialization cast. Metadata reads and const filename calls preserve
its behavior. No type is inferred from the generated or naked callers.

## Genuine source visibility and COMDAT ownership

A declaration-only extraction changes population from 1178 to 1200 bytes:
MSVC 7.1 loses knowledge that the collector does not retain the vector's
address and reloads its fields after the existing filename-sort call. The
real collector therefore lives once in a narrow implementation header as
an inline exported body, included by both natural users. The public `<map>`
header supplies the genuine `_Rb_global<bool>` declaration. No synthetic
noescape helper, wrapper or forced noinline attribute is introduced.

The dedicated TU owns the 265/50/225 ledger rows. Its emitted collector and
vector helpers are foldable COMDATs. The population TU retains the genuine
collector definition for compiler visibility and owns only its original
1178-byte row. The original public population signature, filename-sort
`Rva00456860(Q3SortElem4*,Q3SortElem4*,Q3SortCompare)` boundary and initialization
remain unchanged. Its body and complete relocation sequence are identical
to the baseline, including the EH paths. Callers 00457050/00457090 are unchanged.

The prior two opaque/mutable pointer specializations collapse to one const
pointer specialization. Every old/new emitted definition, EH entry and SafeSEH
section must be covered by the accompanying build receipts; source byte gates
alone are not an ownership proof. The pre-existing five Skirmish selected
provider blockers in population are outside this repair.

## Import and old-identity retirement

The native FF15 operands at overflow +7F/+B4 and collector +26 read
VA0135945C. The retail PE descriptor identifies MSVCR71.dll!memmove, whose
VC7.1 import-library symbol is `__imp__memmove`. Both TUs now use that real
dllimport declaration. They neither define an IAT cell nor use an alias or
new pin. The old `_bfme_memmove_ptr` pin remains for unrelated consumers.

Only the obsolete opaque-pointer overflow and generated false-type overflow
pins at 00452300 are retired after consumer audit. Generated source files are
not hand edited: `add_match --replace-rva` rehomes their two rows. Their other
selected definitions and unrelated row extents remain intact. The existing
native allocator/deallocator and tree-increment routes are unchanged.

Evidence sources: canonical retail PE disassembly/call resolution; matched
MapCacheLookup.cpp and MapMetaData lifecycle source; Ghidra MCP xrefs and
native byte receipts from the independent planning audit; fresh MSVC 7.1
object, boundary, relocation, import-binding and selected-provider checks.
