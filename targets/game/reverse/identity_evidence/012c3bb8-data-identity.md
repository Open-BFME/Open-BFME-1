# Data identity at VA 0x012C3BB8

Corrected: void* scalar pointing at the three-byte ID string.

## Retail facts and extent

The accepted row is `?g_bfmeWhatBGE@@3PAXA` at VA 0x012C3BB8, RVA 0x00EC3BB8, with 4 bytes in `.data`, owned by `game/GameEngine/Source/Common/BfmeConv461.cpp`. Retail initial bytes and all in-range raw text references are recorded in `build/rlink/identity-data-20261005/retail-details.log`; the narrow byte dump and neighboring DIR32 names are in `build/rlink/identity-data-20261005/012C3BB8-retail.log`. The PE has no base-relocation directory; accepted relocation counts come from the verified COFF initializer, not a pointer scan. The original range probe found no overlapping data row and no interior DIR32 name. The accepted gate checks every initial byte and every emitted relocation target.

Retail initially points to VA 0x0112BEAC, whose bytes are 49 44 00. RVAs 0x007FBB60 and 0x007FBB80 load the same slot and pass its value to the member bodies at RVAs 0x007E88D0 and 0x007E8900. The two old spellings already declare the same pointer type; they are duplicate local spellings, not two differently typed objects. The next named datum starts immediately at VA 0x012C3BBC. The original higher-level variable name is not recovered.

Initial bytes: `ac be 12 01`.

The verified COFF initializer has 1 relocation(s). Its single pointer field is at offset zero and targets the address recorded above. The instruction-decoded direct references are in `build/rlink/identity-data-20261005/retail-accesses.log` and its machine-readable `retail-accesses.json`. The scan distinguishes memory reads and writes from address immediates; indexed operations and calls can access storage after an address is loaded. The bodies containing these references are `0x007FBB60` (`?bfmeGoBKG@@YGXPAVBfmeSubBKG@@PAX@Z`, read), `0x007FBB80` (`?bfmeGoBGE@@YGXPAVBfmeSubBGE@@@Z`, read).

## Receiver and argument contract

The two stdcall adapters take respectively an object and a value, or an object alone. They move the object to ECX and pass this stored pointer as the first callee argument. The datum is neither a function pointer nor an array.

## Competing declarations

The counts describe direct declarations or definitions in the initial game tree, including macro-emitted declarations and excluding files that only include another file. Raw source-search output is `build/rlink/identity-data-20261005/012C3BB8-sources.log`; focused declaration context is `build/rlink/identity-data-20261005/declaration-context.log`, and initial source backups accompany it. Reference declarations and uses are retained in `build/rlink/identity-data-20261005/reference-names.log`. Counts do not establish identity.

- `?g_bfmeWhatBGE@@3PAXA`: 1 game file(s).
- `?g_bfmeWhatBKG@@3PAXA`: 1 game file(s).

## Change and verification

Defined the existing g_bfmeWhatBGE spelling once in BfmeConv461.cpp, changed BfmeConv482.cpp to it, and added the emitted ID literal spelling to DIR32 at its witnessed retail address. No alias identity or new semantic name was introduced.

The raw datum gate output is `build/rlink/identity-data-20261005/add-id-pointer-retry.log`. Full instruction contracts and followed five-byte E9 routes are in `build/rlink/identity-data-20261005/contracts.log`; in-range readers and writers with their ledger or Ghidra boundaries are in `build/rlink/identity-data-20261005/retail-details.log`. Per-source build, linkage, CSV, pin and declaration checks are recorded in `build/worker-final.md`. Existing competing pins remain additive evidence and were not rewritten or removed.

## Refutation and remaining work

A different string target, a code-pointer use, a write establishing another interpretation, or a difference in either adapter would refute this unification.
