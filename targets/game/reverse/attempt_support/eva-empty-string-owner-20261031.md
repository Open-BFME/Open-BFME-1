# EVA member teardown: bind the existing empty EA string block

Base `9637ac8ec`; claimed `Q3EhMember0089C900::~Q3EhMember0089C900`, RVA
`0089C900`, 180 bytes. The census queue reports only the declaration-only
`g_emptyStringData` spelling as unresolved in this source.

Native `0089C953` compares the current string pointer with VA `012D5298`.
The existing data row and `Common/Data/Rva012D5298.cpp` already own that
16-byte sentinel as `EAStringC::StringDataC g_rva012D5298Empty`. Its initial
reference word is `0101`, its length is zero, and the existing owner's
constructor/release evidence establishes this shared block independently.
Replace only the obsolete forward type/global and the comparison referent
with that existing owner, keeping the consumer's partial refcount view.

All 180 raw bytes remain identical. Only DIR32 at +85 changes, from the old
global to the established nested-type owner. No code definition is added or
removed, and no other relocation changes. The normal consumer/data-owner
gate passes the function, the full existing data row, three DIR32 references
and the body guards. Frozen definitions pass. No new datum, alias, pin,
shared header, class layout or function identity is introduced.

Reviewed BFME 2 pin `b5a7b8290a0c4c20b03a3664609d434904e228eb`:
`Code/Libraries/Source/Apt/AptString.cpp` and
`AptActionInterpreterSetVariable.cpp` consistently reference their existing
`EAStringC::StringDataC g_eaEmptyStringData` sentinel and its reference word.
Their native `00DDC020` address and other layouts are not imported. The shared
ownership/type pattern is applicable; BFME 1's native compare and established
data row determine the actual binding. EVA's exact BFME-only member identity
is not inferred from that donor and its existing address-scoped name stays.

Against official frozen index `afbe8bafb6` (2026-10-31 12:37), the consumer
previews unresolved/0 -> LINKS/180 authored bytes; its data-only owner also
links. This is a bounded prediction, not a new census or a complete current
selection result. The local ledger-object set remains incomplete, so no
unchanged broad scan or runtime test is repeated or claimed.

Native disassembly, original source/object, whole-object relocation control
and build/link logs are retained under ignored
`build/two-each-no-qwen-20261031-1707` and the matching create-only diagnostic
package. Qwen and other local inference remain off; the shared ten-worker
build cap is retained.
