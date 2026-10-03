# RVA 00C47150 pair cleanup and 00692000 destructor

Retail image: BFME 1.03 unpacked, image base 00400000. Addresses below are RVAs.

The independently matched native hash-map index at 00693880 installs handler
00C47169. That handler loads FuncInfo 00E36C24, whose unwind map at 00E36C1C
has state 0 -> -1, action 00C47150. Raw image reads and Ghidra memory reads
agree. The action tests mask 1 at EBP-18, clears that bit, addresses EBP-14,
and jumps through ILT 00046D9E to 00692000. The conditional RET at 00C47168
bounds the action at 25 bytes, immediately before its handler.

The native parent itself witnesses the temporary: 006938B6 copies its key
through StringBase<char>'s real copy constructor at 00887B60, 006938BB zeros
the adjacent scalar, and 006938D3 passes the pair address to insertion.
Its normal cleanup calls the genuine releaseBuffer at 00887940 on the
string at 006938F3. The return addresses the mapped scalar. The mapped type
is still the existing address-derived Rva00693020Mapped view; no semantic enum
identity is asserted here.

The out-of-line cleanup target 00692000 is exactly E9 to 00887940, followed
by INT3 at 00692005..0069200F. It is the temporary pair's destructor body,
reached through a separate ILT, not an extra ILT name for releaseBuffer.
The existing native template emits
`??1?$pair@$$CBVAsciiString@@W4Rva00693020Mapped@@@_STL@@QAE@XZ`
as five executable bytes with that same releaseBuffer relocation.
The ledger retains an opaque `?dup_00692000@@YAXXZ` identity with this
object-symbol, replacing the old generated `?j_00692000` row at the same extent.
One pin binds that emitted template symbol to this independently verified body;
no second ledger identity or semantic mapped-type name is introduced.

Native action $L19713 in the parent EH section then resolves to this body
through the real retail ILT. Strict source verification passes all 11 claims,
including the parent, five-byte destructor, and 25-byte action. Pin consistency
passes after adding the single native-body binding. No C++ source or shared
header changed.
