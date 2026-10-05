# Datum identity at VA 0x012B7788

Corrected the datum spelling to `?g_ObfRecord012B7788@@3UBigObfSelectorRecord012B7788@@A`. This is an address-preserving structural identity, not a recovered EA identifier. The verified numeric range is 36 bytes: four unsigned 32-bit keys at offset zero, a zero padding dword at offset `0x10`, and four unsigned 32-bit seeds at offset `0x14`. The constructor consumes the keys arithmetically and the seeds as initial encoded values.

The reader at RVA `0x005264B0` stores zero into a selector local, overwrites it from ESP, masks it with 3, and loads one dword at base plus index times 4 and another at base plus `0x14` plus index times 4. The constructor at RVA `0x00526F20` reads the same two positions and multiplies the key into an XOR chain over its receiver. It never dereferences a selected table value as a pointer. Both users can address exactly four entries of each group; the final accessed seed ends at exclusive VA `0x012B77AC`.

The next three bytes are zero, and VA `0x012B77AF` holds a separate one-byte flag initialized to 1. Retail body RVA `0x005280A0` compares that byte at VA `0x009280EC`, writes 1 at VA `0x00928153`, `0x0092825A` and `0x00928282`, and writes BL at VA `0x0092829E`. These byte operations are unrelated to the masked numeric selector and prove that the proposed fifth seed dword at VA `0x012B77AC` must not be claimed by this definition. The source therefore uses an address-specific structural type instead of the generic forty-byte record. The initial forty-byte candidate row was removed; its raw successful size gate is retained as `build/rlink/add-data-012b7788.attempt1.log`, and its removal and excluded flag bytes are in `build/rlink/fix-7788.log`.

The compiled definition has no data relocations. The image has no base-relocation directory; an in-image numeric value alone is not treated as a relocation. The direct arithmetic users establish the numeric element contract, including values that happen to lie inside an image section.

The receiver is the constructor ECX object, whose eight dwords are written by the XOR chain. Its two stack arguments point at input dwords, and retail returns with `RET 8`. The reader has two stack out-parameters and writes exactly one dword through each. Its existing `int **` source ABI is retained with explicit bit-preserving casts from the numeric record; this correction does not assign a new identity to that function.

The datum is defined once in `game/GameEngine/Source/Common/BigObfHookWrappers.cpp`. The appropriate selector-reader file now declares that same numeric record and spelling. There is no evidence of a writer to the record in the typed absolute-reference scan. These writes are to the constructor receiver or reader outputs, not to the record.

A retail consumer that dereferences a selected value as an address before decoding it, indexes a fifth entry, a real relocation attached to a stored word, a named datum inside the claimed 36 bytes, or a changed verified instruction would refute the correction. The original EA type and semantic identifier remain unproven. The Zero Hour reference does not supply these BFME obfuscation objects. `build/rlink/name-oracle-012b7788.log` finds no witnessed class layout, so the new structural type retains the address token.

The inspected extent is VA `0x012B7788` through exclusive `0x012B77AC` in `.data`. Initial bytes are `8a 03 75 c9 0a 44 c4 a0 4a 45 f9 03 0a af 66 1f 00 00 00 00 cb 0b f1 9d 4b 16 68 a0 0b 05 59 43 4b af c6 5b`. The extent and declaration audit is in `build/rlink/extent-and-declarations.log`. No other DIR32 name lies strictly inside any corrected extent; the only data-row overlap after correction is its own owner. The new decorated spelling was added beside the existing rows; the old DIR32 names were retained.

| Existing decorated spelling | Game files declaring it before correction |
|---|---:|
| `?g_ObfRecord012B7788@@3UBigObfSelectorRecord@@A` | 1 |
| `?g_twoBitSelectorRecord012B7788@@3UTwoBitSelectorRecord@@A` | 1 |
| `?g_ObfRecord012B7788@@3UBigObfSelectorRecord012B7788@@A` | 0 |

Counts use direct game-source declarations and declaration-producing macro invocations, count a file once, and exclude comment-only mentions. The raw search and exact declaring lines are in `build/rlink/declarations-rg.jsonl` and `build/rlink/extent-and-declarations.log`. These counts do not decide the preferred identity.

| Retail user RVA | Ledger spelling | Absolute references |
|---|---|---|
| `0x005264B0` | `?Rva005264B0@@YAXPAPAH0@Z` | VA 0x9264c5: `mov ecx, dword ptr [eax*4 + 0x12b779c]`; VA 0x9264ce: `mov eax, dword ptr [eax*4 + 0x12b7788]` |
| `0x00526F20` | `??0Obf00526F20@@QAE@PAH0@Z` | VA 0x926f37: `mov ecx, dword ptr [edx*4 + 0x12b7788]`; VA 0x926f3e: `mov edx, dword ptr [edx*4 + 0x12b779c]` |

Raw retail data, complete user disassembly, all five-byte E9 routes to these users and callers through the routes are retained in `build/rlink/retail-probe.log` and `build/rlink/focused-retail.log`. The latter rejects raw byte coincidences that are not data operands, but any remaining instruction-shaped references need their enclosing body context. The parse-real callback is independently disassembled in `build/rlink/parse-real-retail-full.log`.

For corrected addresses, `build/rlink/add-data-012b7788.log` records the byte, sizeof and relocation gate. Relevant per-source gates are `build/rlink/after-<source-stem>.log`; all changed sources are listed in `build/rlink/changed-sources.json`. Ledger, pin and declaration gates are `check-csv-after.log`, `pin-consistency-after.log`, and `declared-unmatched-after.log` in that folder. Per-file LINKED results and remaining unrelated blockers are in `link-before.log` and `link-after.log`.
