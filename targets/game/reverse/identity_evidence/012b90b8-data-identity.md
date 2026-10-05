# Data identity at VA 0x012B90B8

Corrected: BigObfSelectorRecord, two unsigned int[5] fields.

## Retail facts and extent

The accepted row is `?g_ObfRecord012B90B8@@3UBigObfSelectorRecord@@A` at VA 0x012B90B8, RVA 0x00EB90B8, with 40 bytes in `.data`, owned by `game/GameEngine/Source/Common/BigObfHookWrappers.cpp`. Retail initial bytes and all in-range raw text references are recorded in `build/rlink/identity-data-20261005/retail-details.log`; the narrow byte dump and neighboring DIR32 names are in `build/rlink/identity-data-20261005/012B90B8-retail.log`. The PE has no base-relocation directory; accepted relocation counts come from the verified COFF initializer, not a pointer scan. The original range probe found no overlapping data row and no interior DIR32 name. The accepted gate checks every initial byte and every emitted relocation target.

Retail RVA 0x00619E50 selects index rdtsc & 3, reads +0 and +0x14, and uses the first dword in repeated imul and xor operations. Every nonzero initial entry lies outside the retail image, so these are encoded arithmetic words rather than relocation pointers. Both fifth entries are zero; the next named object starts at VA 0x012B90E0. RVA 0x00619B10 moves the same selected values through its output parameters without dereferencing them. BigObfSelectorRecord is the existing arithmetic declaration; TwoBitSelectorRecord instead declares int* arrays.

Initial bytes: `8f f9 61 c9 8f 8b 8b f8 8f 69 ea ba 0f 63 92 56 00 00 00 00 4b b9 c9 d9 4b cb 03 b4 4b 29 46 ea cb 23 be 1a 00 00 00 00`.

The verified COFF initializer has 0 relocation(s). The instruction-decoded direct references are in `build/rlink/identity-data-20261005/retail-accesses.log` and its machine-readable `retail-accesses.json`. The scan distinguishes memory reads and writes from address immediates; indexed operations and calls can access storage after an address is loaded. The bodies containing these references are `0x00619B10` (`?Rva00619B10@@YAXPAPAH0@Z`, indexed read), `0x00619E50` (`??0Obf00619E50@@QAE@PAH0@Z`, indexed read).

## Receiver and argument contract

The constructor uses ECX for its 32-byte destination and pops two stack pointer arguments with ret 8. The free selector reader takes two int** output arguments and returns with plain ret. Its pointer casts preserve the existing output ABI and exact bytes.

## Competing declarations

The counts describe direct declarations or definitions in the initial game tree, including macro-emitted declarations and excluding files that only include another file. Raw source-search output is `build/rlink/identity-data-20261005/012B90B8-sources.log`; focused declaration context is `build/rlink/identity-data-20261005/declaration-context.log`, and initial source backups accompany it. Reference declarations and uses are retained in `build/rlink/identity-data-20261005/reference-names.log`. Counts do not establish identity.

- `?g_ObfRecord012B90B8@@3UBigObfSelectorRecord@@A`: 1 game file(s).
- `?g_twoBitSelectorRecord012B90B8@@3UTwoBitSelectorRecord@@A`: 1 game file(s).

## Change and verification

Defined g_ObfRecord012B90B8 once in BigObfHookWrappers.cpp. Q3SelectorRecordReaders.cpp now names that same record and casts the selected raw words to the existing out-parameter types. Other records are untouched.

The raw datum gate output is `build/rlink/identity-data-20261005/add-obf.log`. Full instruction contracts and followed five-byte E9 routes are in `build/rlink/identity-data-20261005/contracts.log`; in-range readers and writers with their ledger or Ghidra boundaries are in `build/rlink/identity-data-20261005/retail-details.log`. Per-source build, linkage, CSV, pin and declaration checks are recorded in `build/worker-final.md`. Existing competing pins remain additive evidence and were not rewritten or removed.

## Refutation and remaining work

A dereference of an entry as an image pointer, a relocation within the record, or a byte difference in either reader would refute the chosen arithmetic type.
