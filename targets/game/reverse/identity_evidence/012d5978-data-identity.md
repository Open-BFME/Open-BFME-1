# Data identity at VA 0x012D5978

Corrected: BfmeStr1233, one pointer member holding an Apt string block.

## Retail facts and extent

The accepted row is `?g_bfmeStr1233@@3UBfmeStr1233@@A` at VA 0x012D5978, RVA 0x00ED5978, with 4 bytes in `.data`, owned by `game/GameEngine/Source/Common/BfmeConv1233.cpp`. Retail initial bytes and all in-range raw text references are recorded in `build/rlink/identity-data-20261005/retail-details.log`; the narrow byte dump and neighboring DIR32 names are in `build/rlink/identity-data-20261005/012D5978-retail.log`. The PE has no base-relocation directory; accepted relocation counts come from the verified COFF initializer, not a pointer scan. The original range probe found no overlapping data row and no interior DIR32 name. The accepted gate checks every initial byte and every emitted relocation target.

Retail initially points to the empty EA string block at VA 0x012D5298. RVA 0x008B99B0 passes this global address to a string-output member, invokes the sort callback, releases the pointed-to block, and restores the empty block. RVA 0x008B91F0 passes its address as a string key or reads the block text at +8 for atoi. RVA 0x00C70F40 is the refcount cleanup. The string-object declaration therefore describes the stored object; the raw BfmeRefEMI* name is only a cleanup view of its first member.

Initial bytes: `98 52 2d 01`.

The verified COFF initializer has 1 relocation(s). Its single pointer field is at offset zero and targets the address recorded above. The instruction-decoded direct references are in `build/rlink/identity-data-20261005/retail-accesses.log` and its machine-readable `retail-accesses.json`. The scan distinguishes memory reads and writes from address immediates; indexed operations and calls can access storage after an address is loaded. The bodies containing these references are `0x008B91F0` (`_bfmeHandler1233`, address immediate, read), `0x008B99B0` (`?bfmeVisit1233@@YAPAXPAVBfmeN1233@@H@Z`, address immediate, read, write), `0x00C70F40` (`?bfmeGoEMIb@@YAXXZ`, read).

## Receiver and argument contract

The field-handler callback is cdecl with two tagged-value pointer arguments. The global is a string-output object and lookup key. The cleanup has no receiver or arguments and decrements the block refcount.

## Competing declarations

The counts describe direct declarations or definitions in the initial game tree, including macro-emitted declarations and excluding files that only include another file. Raw source-search output is `build/rlink/identity-data-20261005/012D5978-sources.log`; focused declaration context is `build/rlink/identity-data-20261005/declaration-context.log`, and initial source backups accompany it. Reference declarations and uses are retained in `build/rlink/identity-data-20261005/reference-names.log`. Counts do not establish identity.

- `?g_bfmeRefEMIb@@3PAUBfmeRefEMI@@A`: 1 game file(s).
- `?g_bfmeStr1233@@3UBfmeStr1233@@A`: 2 game file(s).

## Change and verification

Defined the existing g_bfmeStr1233 identity once in BfmeConv1233.cpp with its witnessed empty-block pointer. BfmeConv820.cpp now names its member for cleanup. The field-handler source already spells the selected identity.

The raw datum gate output is `build/rlink/identity-data-20261005/add-apt-sort-string.log`. Full instruction contracts and followed five-byte E9 routes are in `build/rlink/identity-data-20261005/contracts.log`; in-range readers and writers with their ledger or Ghidra boundaries are in `build/rlink/identity-data-20261005/retail-details.log`. Per-source build, linkage, CSV, pin and declaration checks are recorded in `build/worker-final.md`. Existing competing pins remain additive evidence and were not rewritten or removed.

## Refutation and remaining work

Any additional object field, a different initial block, incompatible string-output contract, or any changed callback or cleanup byte would refute this correction.
