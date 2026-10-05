# Object-pointer datum at VA 0x012ED5DC

## Result

The datum is the initially null pointer to the map-object list holder. Keep the existing pinned `BfmeTheMapObjectListHolder` spelling and `class BfmeMapObjectListHolder *` type. The exact BFME holder class identity is not proven, so this correction does not invent a MapObjectList identity. The pointee first dword is the MapObject head, and a MapObject next-pointer is at +4.

The datum has size 4 and lies in `.data`. Retail initially contains `00 00 00 00`. It is backed by four raw file bytes. The PE base-relocation directory is absent. There is no initialized pointer value or relocation to resolve at this slot. Retail dword operand widths and the compiled canonical pointer symbol independently prove the four-byte extent. The range scan finds no existing data row and no DIR32 name in its interior; competing names all start at the same address.

## Retail facts and receiver and argument contract

The 11 bytes at RVA 0x00C6AA40 are `c7 05 dc d5 2e 01 4c 7a 2a 01 c3`: startup publishes the address 0x012A7A4C. That static holder begins with zero. The getter at RVA 0x00087480 loads [0x012ED5DC] and then [EAX], proving the extra indirection. MapObject::fastAssignAllUniqueIDs and verifyValidUniqueID obtain their first MapObject through the same two loads. WorldHeightMap::freeListOfMapObjects at RVA 0x00746E90 deletes the first object, then clears [holder], retaining the global holder pointer. The reference WorldHeightMap.cpp lines 89 and 431-439 owns `MapObject::TheMapObjectListPtr` and deletes and clears that list; the BFME holder indirection is additional retail evidence and is not present in that Zero Hour counterpart.

## Read and write references

The table lists every decoded direct absolute reference in the byte scan, grouped by instruction site. A literal occurrence outside the function maps is handled separately above for the map-holder startup writer. Overlapping ledger and Ghidra extents are deduplicated here.

| Instruction VA | Retail instruction | Containing body RVA |
|---|---|---|
| 0x00487480 | `mov eax, dword ptr [0x12ed5dc]` | 0x00087480 |
| 0x00488B24 | `mov ecx, dword ptr [0x12ed5dc]` | 0x00088B20 |
| 0x00489490 | `mov edx, dword ptr [0x12ed5dc]` | 0x00089450 |
| 0x00489AA3 | `mov ecx, dword ptr [0x12ed5dc]` | 0x00089AA0 |
| 0x00489DD8 | `mov eax, dword ptr [0x12ed5dc]` | 0x00089DC0 |
| 0x005AC236 | `mov ecx, dword ptr [0x12ed5dc]` | 0x001AC1E0 |
| 0x0078F909 | `mov eax, dword ptr [0x12ed5dc]` | 0x0038F7B0 |
| 0x0079171E | `mov eax, dword ptr [0x12ed5dc]` | 0x003916F0 |
| 0x00794CF8 | `mov ecx, dword ptr [0x12ed5dc]` | 0x00394260 |
| 0x00ADA8AE | `mov eax, dword ptr [0x12ed5dc]` | 0x006DA8A0 |
| 0x00B100EC | `mov eax, dword ptr [0x12ed5dc]` | 0x007100C0 |
| 0x00B31251 | `mov ecx, dword ptr [0x12ed5dc]` | 0x00731190 |
| 0x00B3154C | `mov eax, dword ptr [0x12ed5dc]` | 0x00731190 |
| 0x00B46E90 | `mov eax, dword ptr [0x12ed5dc]` | 0x00746E90 |
| 0x00B46EA1 | `mov eax, dword ptr [0x12ed5dc]` | 0x00746E90 |
| 0x00B4AD71 | `mov ecx, dword ptr [0x12ed5dc]` | 0x0074ACB0 |
| 0x00B4AD8B | `mov eax, dword ptr [0x12ed5dc]` | 0x0074ACB0 |

## Competing spellings before correction

Counts are game source files whose compiled objects reference or define the exact decorated spelling. Zero means that spelling is dormant; the raw count log also identifies three unlisted class-kind or namespace variants. Counts select nothing: retail facts and the existing identity pin select the canonical spelling.

| Decorated spelling | Game files |
|---|---|
| `?BfmeTheMapObjectListHolder@@3PAUMapObjectList@@A` | 0 |
| `?BfmeTheMapObjectListHolder@@3PAVBfmeMapObjectListHolder@@A` | 2 |
| `?g_bfmeListEYE@@3PAUBfmeListEYE@@A` | 0 |
| `?g_rva00087480@@3PAHA` | 6 |

Additional emitted spellings absent from the DIR32 table are also consolidated:

- `?BfmeTheMapObjectListHolder@@3PAUBfmeMapObjectListHolder@@A` appears in 1 game file(s).

## Correction and refutation

Define `?BfmeTheMapObjectListHolder@@3PAVBfmeMapObjectListHolder@@A` once in `game/GameEngineDevice/Source/W3DDevice/GameClient/WorldHeightMap.cpp` and add its byte-verified data row. All authored callers declare this canonical pointee type; differing local use views are explicit casts. Existing pins and DIR32 rows are retained. The chosen DIR32 spelling already exists, so no duplicate row is appended. Function identities and ledger row order remain unchanged.

A startup store with a target other than 0x012A7A4C, a reader interpreting the global value as the first MapObject directly, or an independently proven incompatible holder identity would refute this consolidation. The holder real class name would require independent EA or reference evidence.

## Raw evidence

`build/rlink/identity-seven-1791161098/retail-probe.log` records image hash, section bounds, bytes, range checks, all references and followed five-byte E9 chains. `retail-refs.json` records decoded sites and owning rows. `ledger-spellings.log`, `game-users.log`, `spelling-counts-v2.log` and `spelling-counts.json` preserve the spelling census. `additional-apt-spelling.log` captures both extra Boolean head declarations. `maplist-startup-disasm.log`, `static-holder.log`, `allocator-use.log`, `allocator-writer.log`, `pointee-data.log`, `allocator-vtable-methods.log`, `codec-scalar-pointee.log` and `codec-simd-pointee.log` contain focused probes. `classic-builder-disasm.log` and `classic-name-and-thunk.log` prove the C literal and its E9 constructor route. `maplist-reference-full.log` and `vendor-locale.log` record reference evidence. `ownership-audit.log` and `ownership-audit.json` prove one compiled definition and canonical declarations in every authored retail user. Per-source build and link logs and gate results are indexed in `build/worker-final.md`.

Three declaration changes renumbered compiler cleanup labels. The repository EH-state tool bound the labels through retail and COFF unwind maps and updated only seven `functions.csv` notes. `eh-before/report.json`, `eh-fix.log`, `eh-after/report.json` and `build-eh-repaired.log` preserve the independent state mapping and byte verification. No function extent or identity changes.
