# Datum identity at VA 0x012B4FC8

Unresolved and unchanged. Retail establishes three adjacent sixteen-byte four-float records, each initialized to (0.5, 0.5, 0.5, 0), and indexed at a sixteen-byte stride. `HighlightColors` describes the observed rendering role; the record-array interpretation is stronger than a scalar `LightingCoord00747FF0` or an array of integer `BfmeEntryFA` values.

RVA `0x007D7040` reads the indexed first three components with floating arithmetic for highlight pixel constants. RVAs `0x00746DA0` and `0x00746DE0` store or load those same raw three dwords with an index times 16. The GlobalLighting parser at RVA `0x00747FF0` writes the three records, and writer RVA `0x00748860` reads them. All these uses are present in the raw probes.

A 48-byte array at VA `0x012B4FC8` contains other existing DIR32 names at VA `0x012B4FD8` and `0x012B4FE8`. The brief requires that no other named datum lie inside a new definition. Defining only the first sixteen bytes would not satisfy the indexed users, so no data row or declaration correction was attempted. The next datum begins at VA `0x012B4FF8`.

No exact Zero Hour `HighlightColors` declaration was found. A verified original array declaration, and independent reconciliation of both interior names to elements of that array, would settle the owner and allow one full definition without overlapping identities. A pointer relocation in the initialized components, a different stride or an interior independent datum would refute the proposed float-array interpretation.

The inspected extent is VA `0x012B4FC8` through exclusive `0x012B4FF8` in `.data`. Initial bytes are `00 00 00 3f 00 00 00 3f 00 00 00 3f 00 00 00 00 00 00 00 3f 00 00 00 3f 00 00 00 3f 00 00 00 00 00 00 00 3f 00 00 00 3f 00 00 00 3f 00 00 00 00`. The extent and declaration audit is in `build/rlink/extent-and-declarations.log`. No other DIR32 name lies strictly inside any corrected extent; the only data-row overlap after correction is its own owner.

| Existing decorated spelling | Game files declaring it before correction |
|---|---:|
| `?HighlightColors@@3PAUColor@@A` | 1 |
| `?Value012B4FC8@@3ULightingCoord00747FF0@@A` | 1 |
| `?g_bfmeTableFA@@3PAVBfmeEntryFA@@A` | 2 |

Counts use direct game-source declarations and declaration-producing macro invocations, count a file once, and exclude comment-only mentions. The raw search and exact declaring lines are in `build/rlink/declarations-rg.jsonl` and `build/rlink/extent-and-declarations.log`. These counts do not decide the preferred identity.

| Retail user RVA | Ledger spelling | Absolute references |
|---|---|---|
| `0x00746DA0` | `?bfmeStore@@YAXHHHH@Z` | VA 0xb46db9: `mov dword ptr [eax + 0x12b4fc8], ecx`; VA 0xb46dc3: `mov dword ptr [eax + 0x12b4fcc], edx`; VA 0xb46dc9: `mov dword ptr [eax + 0x12b4fd0], ecx` |
| `0x00746DE0` | `?bfmeLoad@@YAXPAH00H@Z` | VA 0xb46df5: `mov ecx, dword ptr [eax + 0x12b4fc8]`; VA 0xb46dfd: `mov ecx, dword ptr [eax + 0x12b4fcc]`; VA 0xb46e09: `mov eax, dword ptr [eax + 0x12b4fd0]` |
| `0x00747FF0` | `?ParseLightingDataChunk@Rva0074A680ParserRegistration@@UAE_NAAVDataChunkInput@@PAUDataChunkInfo@@@Z` | VA 0xb485e5: `fstp dword ptr [0x12b4fd0]`; VA 0xb485f3: `mov dword ptr [0x12b4fc8], edx`; VA 0xb485f9: `mov dword ptr [0x12b4fcc], eax`; VA 0xb48631: `fstp dword ptr [0x12b4fe0]`; VA 0xb48641: `mov dword ptr [0x12b4fd8], edx`; VA 0xb48647: `mov dword ptr [0x12b4fdc], eax`; VA 0xb48667: `fstp dword ptr [0x12b4ff0]`; VA 0xb48675: `mov dword ptr [0x12b4fe8], ecx`; VA 0xb4867b: `mov dword ptr [0x12b4fec], edx` |
| `0x00748860` | `?WriteGlobalLighting00748860@@YAXPAVDataChunkOutput@@@Z` | VA 0xb48cc9: `mov ecx, dword ptr [0x12b4fd0]`; VA 0xb48ccf: `mov edx, dword ptr [0x12b4fc8]`; VA 0xb48cd5: `mov eax, dword ptr [0x12b4fcc]`; VA 0xb48d02: `mov ecx, dword ptr [0x12b4fd8]`; VA 0xb48d08: `mov edx, dword ptr [0x12b4fdc]`; VA 0xb48d0e: `mov eax, dword ptr [0x12b4fe0]`; VA 0xb48d3b: `mov ecx, dword ptr [0x12b4fec]`; VA 0xb48d41: `mov eax, dword ptr [0x12b4fe8]`; VA 0xb48d46: `mov edx, dword ptr [0x12b4ff0]` |
| `0x007D7040` | `?postRender@ScreenHilightFilter@@UAE_NHIAA_NPAUCoord2D@@@Z` | VA 0xbd71e4: `fld dword ptr [eax + 0x12b4fc8]`; VA 0xbd720c: `fld dword ptr [eax + 0x12b4fcc]`; VA 0xbd721c: `fld dword ptr [eax + 0x12b4fd0]` |

Raw retail data, complete user disassembly, all five-byte E9 routes to these users and callers through the routes are retained in `build/rlink/retail-probe.log` and `build/rlink/focused-retail.log`. The latter rejects raw byte coincidences that are not data operands, but any remaining instruction-shaped references need their enclosing body context. The parse-real callback is independently disassembled in `build/rlink/parse-real-retail-full.log`.

For corrected addresses, `build/rlink/add-data-012b4fc8.log` records the byte, sizeof and relocation gate. Relevant per-source gates are `build/rlink/after-<source-stem>.log`; all changed sources are listed in `build/rlink/changed-sources.json`. Ledger, pin and declaration gates are `check-csv-after.log`, `pin-consistency-after.log`, and `declared-unmatched-after.log` in that folder. Per-file LINKED results and remaining unrelated blockers are in `link-before.log` and `link-after.log`.
