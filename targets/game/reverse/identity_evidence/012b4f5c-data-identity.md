# Datum identity at VA 0x012B4F5C

Corrected `Rva012b4f5c` to `TheDrawableIconNames` and exposed the existing definition in `Drawable.cpp` with external linkage. The datum is an array of fifteen `const char *` elements: fourteen names followed by NULL. Its extent is 60 bytes, ending at VA `0x012B4F98` before the following float.

The Zero Hour definition is in `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/Drawable.cpp:94`. Every entry, including `Demoralized_OBSOLETE` and the final NULL, matches BFME retail. Retail RVA `0x00410A70` indexes this base with a four-byte stride and returns the pointer; RVA `0x00410A80` scans fourteen entries. RVA `0x00415D50` reads named entries for static-image initialization, and RVA `0x0041D290` reads them for icon transfer. No writer was found in the typed absolute-reference scan.

The definition has fourteen DIR32 string relocations. Every complete compiler string equals its corresponding null-terminated retail string at the table pointer. The exact offsets, targets, decorated string spellings and byte comparisons are in `build/rlink/string-relocations.log`. Existing pointer-array declarations in the initialization source already use the chosen spelling; both transfer declarations and their users now use it too.

The table has no receiver. The index getter receives the icon index in EAX in retail; the name scanner consumes a char pointer and returns an icon index. Their original function source and ABI are unchanged. The table is defined only in its reference owner, `game/GameEngine/Source/GameClient/Drawable.cpp`.

A mismatched name or order, a non-null fifteenth element, another datum inside the 60-byte extent, a writer requiring a different element type, or a changed verified function would refute the correction.

The inspected extent is VA `0x012B4F5C` through exclusive `0x012B4F98` in `.data`. Initial bytes are `a4 11 0f 01 94 11 0f 01 84 11 0f 01 68 11 0f 01 5c 11 0f 01 4c 11 0f 01 e4 3c 08 01 30 11 0f 01 10 11 0f 01 ec 10 0f 01 e0 10 0f 01 d0 10 0f 01 c0 10 0f 01 b4 10 0f 01 00 00 00 00`. The extent and declaration audit is in `build/rlink/extent-and-declarations.log`. No other DIR32 name lies strictly inside any corrected extent; the only data-row overlap after correction is its own owner.

| Existing decorated spelling | Game files declaring it before correction |
|---|---:|
| `?Rva012b4f5c@@3PAPBDA` | 1 |
| `?TheDrawableIconNames@@3PAPBDA` | 2 |

Counts use direct game-source declarations and declaration-producing macro invocations, count a file once, and exclude comment-only mentions. The raw search and exact declaring lines are in `build/rlink/declarations-rg.jsonl` and `build/rlink/extent-and-declarations.log`. These counts do not decide the preferred identity.

| Retail user RVA | Ledger spelling | Absolute references |
|---|---|---|
| `0x00410A70` | `?drawableIconIndexToName@@YAPBDW4DrawableIconType@@@Z` | VA 0x810a70: `mov eax, dword ptr [eax*4 + 0x12b4f5c]` |
| `0x00410A80` | `?drawableIconNameToIndex@@YA?AW4DrawableIconType@@PBD@Z` | VA 0x810a90: `mov eax, dword ptr [esi*4 + 0x12b4f5c]` |
| `0x00415D50` | `?initStaticImages@Drawable@@CAXXZ` | VA 0x815ed5: `mov eax, dword ptr [0x12b4f5c]`; VA 0x815f14: `mov eax, dword ptr [0x12b4f60]`; VA 0x815f51: `mov eax, dword ptr [0x12b4f64]`; VA 0x815f8e: `mov eax, dword ptr [0x12b4f6c]`; VA 0x815fcb: `mov eax, dword ptr [0x12b4f70]`; VA 0x816008: `mov eax, dword ptr [0x12b4f74]`; VA 0x816045: `mov eax, dword ptr [0x12b4f78]`; VA 0x816082: `mov eax, dword ptr [0x12b4f7c]`; VA 0x8160bf: `mov eax, dword ptr [0x12b4f80]`; VA 0x816108: `mov ecx, dword ptr [0x12b4f88]`; VA 0x816146: `mov edx, dword ptr [0x12b4f8c]`; VA 0x816184: `mov edx, dword ptr [0x12b4f90]` |
| `0x0041D290` | `?xfer@Drawable@@MAEXPAVXfer@@@Z` | VA 0x81d991: `mov ebx, 0x12b4f5c`; VA 0x81dc03: `mov edx, dword ptr [edi*4 + 0x12b4f5c]` |

Raw retail data, complete user disassembly, all five-byte E9 routes to these users and callers through the routes are retained in `build/rlink/retail-probe.log` and `build/rlink/focused-retail.log`. The latter rejects raw byte coincidences that are not data operands, but any remaining instruction-shaped references need their enclosing body context. The parse-real callback is independently disassembled in `build/rlink/parse-real-retail-full.log`.

For corrected addresses, `build/rlink/add-data-012b4f5c.log` records the byte, sizeof and relocation gate. Relevant per-source gates are `build/rlink/after-<source-stem>.log`; all changed sources are listed in `build/rlink/changed-sources.json`. Ledger, pin and declaration gates are `check-csv-after.log`, `pin-consistency-after.log`, and `declared-unmatched-after.log` in that folder. Per-file LINKED results and remaining unrelated blockers are in `link-before.log` and `link-after.log`.
