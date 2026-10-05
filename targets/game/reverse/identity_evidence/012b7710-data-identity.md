# Datum identity at VA 0x012B7710

Corrected the datum spelling to `?g_ObfRecord012B7710@@3UBigObfSelectorRecord@@A`. This is an address-preserving structural identity, not a recovered EA identifier. Retail establishes a 40-byte record containing two arrays of five unsigned 32-bit encoded values; the constructor consumes the first array as arithmetic keys and the second as initial encoded seeds.

The reader at RVA `0x005263F0` stores zero into a selector local, overwrites it from EBP, masks it with 3, and loads one dword at base plus index times 4 and another at base plus `0x14` plus index times 4. The constructor at RVA `0x00526C80` reads the same two positions and multiplies the key into an XOR chain over its receiver. It never dereferences a selected table value as a pointer. Both fifth dwords are zero. The next bytes are outside the second terminated five-dword group.

The compiled definition has no data relocations. The image has no base-relocation directory; an in-image numeric value alone is not treated as a relocation. The direct arithmetic users establish the numeric element contract, including values that happen to lie inside an image section.

The receiver is the constructor ECX object, whose eight dwords are written by the XOR chain. Its two stack arguments point at input dwords, and retail returns with `RET 8`. The reader has two stack out-parameters and writes exactly one dword through each. Its existing `int **` source ABI is retained with explicit bit-preserving casts from the numeric record; this correction does not assign a new identity to that function.

The datum is defined once in `game/GameEngine/Source/Common/BigObfHookWrappers.cpp`. The appropriate selector-reader file now declares that same numeric record and spelling. There is no evidence of a writer to the record in the typed absolute-reference scan. These writes are to the constructor receiver or reader outputs, not to the record.

A retail consumer that dereferences a selected value as an address before decoding it, a real relocation attached to a stored word, a named datum inside the claimed 40 bytes, or a changed verified instruction would refute the correction. The original EA type and semantic identifier remain unproven. The Zero Hour reference does not supply these BFME obfuscation objects.

The inspected extent is VA `0x012B7710` through exclusive `0x012B7738` in `.data`. Initial bytes are `0a 44 c4 a0 4a 45 f9 03 0a af 66 1f 0a 9b c9 2e 00 00 00 00 4b 16 68 a0 0b 05 59 43 4b af c6 5b 4b 93 41 6a 00 00 00 00`. The extent and declaration audit is in `build/rlink/extent-and-declarations.log`. No other DIR32 name lies strictly inside any corrected extent; the only data-row overlap after correction is its own owner.

| Existing decorated spelling | Game files declaring it before correction |
|---|---:|
| `?g_ObfRecord012B7710@@3UBigObfSelectorRecord@@A` | 1 |
| `?g_r3Record012B7710@@3UR3SelectorRecord@@A` | 1 |

Counts use direct game-source declarations and declaration-producing macro invocations, count a file once, and exclude comment-only mentions. The raw search and exact declaring lines are in `build/rlink/declarations-rg.jsonl` and `build/rlink/extent-and-declarations.log`. These counts do not decide the preferred identity.

| Retail user RVA | Ledger spelling | Absolute references |
|---|---|---|
| `0x005263F0` | `?Rva005263F0@@YAXPAPAH0@Z` | VA 0x926405: `mov ecx, dword ptr [eax*4 + 0x12b7724]`; VA 0x92640e: `mov eax, dword ptr [eax*4 + 0x12b7710]` |
| `0x00526C80` | `??0Obf00526C80@@QAE@PAH0@Z` | VA 0x926c97: `mov ecx, dword ptr [edx*4 + 0x12b7710]`; VA 0x926c9e: `mov edx, dword ptr [edx*4 + 0x12b7724]` |

Raw retail data, complete user disassembly, all five-byte E9 routes to these users and callers through the routes are retained in `build/rlink/retail-probe.log` and `build/rlink/focused-retail.log`. The latter rejects raw byte coincidences that are not data operands, but any remaining instruction-shaped references need their enclosing body context. The parse-real callback is independently disassembled in `build/rlink/parse-real-retail-full.log`.

For corrected addresses, `build/rlink/add-data-012b7710.log` records the byte, sizeof and relocation gate. Relevant per-source gates are `build/rlink/after-<source-stem>.log`; all changed sources are listed in `build/rlink/changed-sources.json`. Ledger, pin and declaration gates are `check-csv-after.log`, `pin-consistency-after.log`, and `declared-unmatched-after.log` in that folder. Per-file LINKED results and remaining unrelated blockers are in `link-before.log` and `link-after.log`.
