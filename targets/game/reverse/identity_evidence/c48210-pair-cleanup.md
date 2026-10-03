# RVA 00C48210 pair cleanup and 0069DEC0 destructor

Retail image: BFME 1.03 unpacked, image base 00400000. Addresses below are RVAs.

The independently matched native hash-map index at 006AC440 installs handler
00C48229. That handler loads FuncInfo 00E37CB8, whose unwind map at 00E37CB0
has state 0 -> -1, action 00C48210. Raw image reads and Ghidra memory reads
agree. The action tests mask 1 at EBP-18, clears that bit, addresses EBP-14,
and jumps through ILT 00036291 to 0069DEC0. The conditional RET at 00C48228
bounds the action at 25 bytes, immediately before its handler.

The native parent itself witnesses the temporary: 006AC476 copies its key
through StringBase<char>'s real copy constructor at 00887B60, 006AC47B zeros
the adjacent scalar, and 006AC493 passes the pair address to insertion.
Its normal cleanup calls the genuine releaseBuffer at 00887940 on the
string at 006AC4B3. The return addresses the mapped scalar. The mapped type
is still the existing address-derived Rva006A7AD0Mapped view; no semantic enum
identity is asserted here.

The out-of-line cleanup target 0069DEC0 is exactly E9 to 00887940, followed
by INT3 at 0069DEC5..0069DECF. It is the temporary pair's destructor body,
reached through a separate ILT, not an extra ILT name for releaseBuffer.
The existing native template emits
`??1?$pair@$$CBVAsciiString@@W4Rva006A7AD0Mapped@@@_STL@@QAE@XZ`
as five executable bytes with that same releaseBuffer relocation.
The ledger retains an opaque `?dup_0069DEC0@@YAXXZ` identity with this
object-symbol, replacing the old generated `?j_0069DEC0` row at the same extent.
One pin binds that emitted template symbol to this independently verified body;
no second ledger identity or semantic mapped-type name is introduced.

Native action $L19806 in the parent EH section then resolves to this body
through the real retail ILT. Strict source verification passes all 13 claims,
including the parent, five-byte destructor, and 25-byte action. Pin consistency
passes after adding the single native-body binding. No C++ source or shared
header changed.
