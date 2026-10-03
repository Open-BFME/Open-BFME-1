# One allocator callback cell at VA 0x01337828

This is a linkage correction, not a recovery of EA's original global name.
The five changed consumer TUs used `WideAllocPtr`; the verified data owner is
`Rva008C5D70Alloc` in `game/Libraries/Source/EA/Apt/Rva008C4650HeaderedAlloc.cpp`.

Independent evidence refutes treating these as distinct globals:

- `dir32_addresses.csv` pins both exact C++ function-pointer symbols to
  VA 0x01337828. Both declarations have the same cdecl `void *(unsigned int)`
  signature, storage width and indirection; no cast or calling-convention
  adapter is introduced.
- `data_rows.csv` contains the single four-byte owner at that VA, defined by
  the existing Apt allocation wrapper. Its row verifies the retail zero-filled
  `.data` cell and cites installer RVA 0x00789440 plus bootstrap RVA 0x0089487A.
  The installer stores the same allocation-handler address in this cell.
- Every changed caller's retail `ff 15` operand reaches this one cell. This is
  independently checked by byte verification and DIR32 consistency on all
  21 consumer bodies (48 + 63 + 57 + 17*33 + 38 = 767 bytes).
- The callback is also used for ordinary list nodes and raw counted buffers;
  no separate wide-character allocator cell or ABI is evidenced. The old
  source name does not establish a separate semantic identity. We retain the
  already verified provider spelling rather than inventing or duplicating it.

The correction preserves all function names, extents, logic, data definitions,
ledger rows and ABI. It only changes consumer references to the existing owner.
`WideAllocPtr` remains in other unmodified callers, which are future work.

Verification on the scoped batch used the full five consumer objects and full
objects of the allocator owner and `Bfme5FiftyFour.cpp` list-push provider.
MSVC 7.1 link.exe with `/NODEFAULTLIB /NOENTRY /OPT:REF /OPT:NOICF` and all
21 matched entry points rooted failed before with precisely one unresolved
`WideAllocPtr`; it succeeded after the adoption. The final map retained 21
separate function addresses; disassembly showed each indirect call bound to
the single canonical allocator slot. No stub, alias, absolute-address
substitution, duplicate datum, or verified-code removal was used.

The official index from successful Actions run 37137734966 (commit
1677ebdc33, census 2026-10-03 17:32) agrees: the five source previews change
from blocked to 767 linked bytes. That historical preview is not a fresh
whole-repository census. The real link result above is restricted to this
explicit object set.
