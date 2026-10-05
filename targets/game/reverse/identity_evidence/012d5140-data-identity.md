# Data identity at VA 0x012D5140

Corrected: BfmeStrVKI, one pointer member holding an Apt string block.

## Retail facts and extent

The accepted row is `?g_String012D5140@@3VBfmeStrVKI@@A` at VA 0x012D5140, RVA 0x00ED5140, with 4 bytes in `.data`, owned by `game/GameEngine/Source/Common/BfmeConv820.cpp`. Retail initial bytes and all in-range raw text references are recorded in `build/rlink/identity-data-20261005/retail-details.log`; the narrow byte dump and neighboring DIR32 names are in `build/rlink/identity-data-20261005/012D5140-retail.log`. The PE has no base-relocation directory; accepted relocation counts come from the verified COFF initializer, not a pointer scan. The original range probe found no overlapping data row and no interior DIR32 name. The accepted gate checks every initial byte and every emitted relocation target.

Retail initially points to the independently owned empty EA string block at VA 0x012D5298. The push-string body at RVA 0x008CE910 constructs a temporary string, adjusts 16-bit refcounts, replaces this pointer member, and passes the address of the global as a string receiver. Other string operations at RVAs 0x00894800 and 0x00894A90 read and replace the same member. The cleanup body at RVA 0x00C70F20 decrements the pointed-to block refcount. This supports the existing string-object spelling over the raw cleanup-view pointer spelling.

Initial bytes: `98 52 2d 01`.

The verified COFF initializer has 1 relocation(s). Its single pointer field is at offset zero and targets the address recorded above. The instruction-decoded direct references are in `build/rlink/identity-data-20261005/retail-accesses.log` and its machine-readable `retail-accesses.json`. The scan distinguishes memory reads and writes from address immediates; indexed operations and calls can access storage after an address is loaded. The bodies containing these references are `0x00894800` (`?d_00894800@@YAXXZ`, read, write), `0x00894A90` (`?d_00894a90@@YAXXZ`, read, write), `0x008CE910` (`?pushString008CE910@@YAXPAVRva008AE770Stack@@PAURva008CE910Context@@@Z`, address immediate, read, write), `0x00C70F20` (`?bfmeGoEMIa@@YAXXZ`, read).

## Receiver and argument contract

The global address is passed as a string object; the sole member points to a block whose refcount is a 16-bit field at offset zero and whose text starts at offset eight in related string operations. The cleanup function is cdecl with no receiver or arguments.

## Competing declarations

The counts describe direct declarations or definitions in the initial game tree, including macro-emitted declarations and excluding files that only include another file. Raw source-search output is `build/rlink/identity-data-20261005/012D5140-sources.log`; focused declaration context is `build/rlink/identity-data-20261005/declaration-context.log`, and initial source backups accompany it. Reference declarations and uses are retained in `build/rlink/identity-data-20261005/reference-names.log`. Counts do not establish identity.

- `?g_String012D5140@@3VBfmeStrVKI@@A`: 1 game file(s).
- `?g_bfmeRefEMIa@@3PAUBfmeRefEMI@@A`: 1 game file(s).

## Change and verification

Defined the existing g_String012D5140 identity once in BfmeConv820.cpp, the cleanup owner, using the independently defined empty string block. Its cleanup now names that object member. The push-string user retains its existing spelling and ABI.

The raw datum gate output is `build/rlink/identity-data-20261005/add-apt-push-string.log`. Full instruction contracts and followed five-byte E9 routes are in `build/rlink/identity-data-20261005/contracts.log`; in-range readers and writers with their ledger or Ghidra boundaries are in `build/rlink/identity-data-20261005/retail-details.log`. Per-source build, linkage, CSV, pin and declaration checks are recorded in `build/worker-final.md`. Existing competing pins remain additive evidence and were not rewritten or removed.

## Refutation and remaining work

An additional inline field in the string object, a non-string use of the block, a different initial target, or a byte change in either cleanup or push-string would refute the correction.
