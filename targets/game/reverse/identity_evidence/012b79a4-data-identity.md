# Datum identity at VA 0x012B79A4

Corrected the datum spelling to `?g_ObfRecord012B79A4@@3UBigObfSelectorRecord@@A`. This is an address-preserving structural identity, not a recovered EA identifier. Retail establishes a 40-byte record containing two arrays of five unsigned 32-bit encoded values; the constructor consumes the first array as arithmetic keys and the second as initial encoded seeds.

The reader at RVA `0x0054D600` stores zero into a selector local, overwrites it from ESP, masks it with 3, and loads one dword at base plus index times 4 and another at base plus `0x14` plus index times 4. The constructor at RVA `0x0054DBC0` reads the same two positions and multiplies the key into an XOR chain over its receiver. It never dereferences a selected table value as a pointer. Both fifth dwords are zero. The next bytes are outside the second terminated five-dword group.

The compiled definition has no data relocations. The image has no base-relocation directory; an in-image numeric value alone is not treated as a relocation. The direct arithmetic users establish the numeric element contract, including values that happen to lie inside an image section.

The receiver is the constructor ECX object, whose eight dwords are written by the XOR chain. Its two stack arguments point at input dwords, and retail returns with `RET 8`. The reader has two stack out-parameters and writes exactly one dword through each. Its existing `int **` source ABI is retained with explicit bit-preserving casts from the numeric record; this correction does not assign a new identity to that function.

The datum is defined once in `game/GameEngine/Source/Common/BigObfHookWrappers.cpp`. The appropriate selector-reader file now declares that same numeric record and spelling. There is no evidence of a writer to the record in the typed absolute-reference scan. These writes are to the constructor receiver or reader outputs, not to the record.

A retail consumer that dereferences a selected value as an address before decoding it, a real relocation attached to a stored word, a named datum inside the claimed 40 bytes, or a changed verified instruction would refute the correction. The original EA type and semantic identifier remain unproven. The Zero Hour reference does not supply these BFME obfuscation objects.

The inspected extent is VA `0x012B79A4` through exclusive `0x012B79CC` in `.data`. Initial bytes are `0a 98 2c bb ca be ad 0c 8a 6d 2d eb 4a 04 b6 06 00 00 00 00 0b 90 0c b3 cb ee 8d 04 8b 27 a1 a7 4b 14 9a 4e 00 00 00 00`. The extent and declaration audit is in `build/rlink/extent-and-declarations.log`. No other DIR32 name lies strictly inside any corrected extent; the only data-row overlap after correction is its own owner.

| Existing decorated spelling | Game files declaring it before correction |
|---|---:|
| `?g_ObfRecord012B79A4@@3UBigObfSelectorRecord@@A` | 1 |
| `?g_twoBitSelectorRecord012B79A4@@3UTwoBitSelectorRecord@@A` | 1 |

Counts use direct game-source declarations and declaration-producing macro invocations, count a file once, and exclude comment-only mentions. The raw search and exact declaring lines are in `build/rlink/declarations-rg.jsonl` and `build/rlink/extent-and-declarations.log`. These counts do not decide the preferred identity.

| Retail user RVA | Ledger spelling | Absolute references |
|---|---|---|
| `0x0054D600` | `?Rva0054D600@@YAXPAPAH0@Z` | VA 0x94d615: `mov ecx, dword ptr [eax*4 + 0x12b79b8]`; VA 0x94d61e: `mov eax, dword ptr [eax*4 + 0x12b79a4]` |
| `0x0054DBC0` | `??0Obf0054DBC0@@QAE@PAH0@Z` | VA 0x94dbd7: `mov ecx, dword ptr [edx*4 + 0x12b79a4]`; VA 0x94dbde: `mov edx, dword ptr [edx*4 + 0x12b79b8]` |

Raw retail data, complete user disassembly, all five-byte E9 routes to these users and callers through the routes are retained in `build/rlink/retail-probe.log` and `build/rlink/focused-retail.log`. The latter rejects raw byte coincidences that are not data operands, but any remaining instruction-shaped references need their enclosing body context. The parse-real callback is independently disassembled in `build/rlink/parse-real-retail-full.log`.

For corrected addresses, `build/rlink/add-data-012b79a4.log` records the byte, sizeof and relocation gate. Relevant per-source gates are `build/rlink/after-<source-stem>.log`; all changed sources are listed in `build/rlink/changed-sources.json`. Ledger, pin and declaration gates are `check-csv-after.log`, `pin-consistency-after.log`, and `declared-unmatched-after.log` in that folder. Per-file LINKED results and remaining unrelated blockers are in `link-before.log` and `link-after.log`.
