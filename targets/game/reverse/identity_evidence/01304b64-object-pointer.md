# Object-pointer datum at VA 0x01304B64

## Result

The datum is the initially null published helper pointer. The chosen existing spelling is `g_bfmeCurrentYS`, typed `class BfmeHelperYS *`, defined by the publisher file. No real EA helper class identity is claimed. The other two pointee classes are method-call views of the identical published object.

The datum has size 4 and lies in `.data`. Retail initially contains `00 00 00 00`. It is in the virtual zero-filled tail of the section. The PE base-relocation directory is absent. There is no initialized pointer value or relocation to resolve at this slot. Retail dword operand widths and the compiled canonical pointer symbol independently prove the four-byte extent. The range scan finds no existing data row and no DIR32 name in its interior; competing names all start at the same address.

## Retail facts and receiver and argument contract

RVA 0x00755E70 constructs its function-local static helper once, sets ECX to its address, stores ECX to [0x01304B64] at VA 0x00B55ECA, then attaches the owner. RVA 0x00754A10 loads that same address as the ECX receiver, null-checks it, and tail-calls the helper method at RVA 0x00754850. RVA 0x00755C80 null-checks the same receiver and calls through ILT RVA 0x0003B02A, whose E9 reaches RVA 0x00755A70; it stores EAX to [0x01304B5C]. Both consumers take no stack arguments. Their existing method pins are retained, with casts at the use sites.

## Read and write references

The table lists every decoded direct absolute reference in the byte scan, grouped by instruction site. A literal occurrence outside the function maps is handled separately above for the map-holder startup writer. Overlapping ledger and Ghidra extents are deduplicated here.

| Instruction VA | Retail instruction | Containing body RVA |
|---|---|---|
| 0x00B54A10 | `mov ecx, dword ptr [0x1304b64]` | 0x00754A10 |
| 0x00B55C80 | `mov ecx, dword ptr [0x1304b64]` | 0x00755C80 |
| 0x00B55ECA | `mov dword ptr [0x1304b64], ecx` | 0x00755E70 |

## Competing spellings before correction

Counts are game source files whose compiled objects reference or define the exact decorated spelling. Zero means that spelling is dormant; the raw count log also identifies three unlisted class-kind or namespace variants. Counts select nothing: retail facts and the existing identity pin select the canonical spelling.

| Decorated spelling | Game files |
|---|---|
| `?g_Glo00F04B64@@3PAVGen00754850@@A` | 1 |
| `?g_Va01304B64@@3PAVGen01304B64@@A` | 1 |
| `?g_bfmeCurrentYS@@3PAVBfmeHelperYS@@A` | 1 |

## Correction and refutation

Define `?g_bfmeCurrentYS@@3PAVBfmeHelperYS@@A` once in `game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/BfmeHelperAttachYS.cpp` and add its byte-verified data row. All authored callers declare this canonical pointee type; differing local use views are explicit casts. Existing pins and DIR32 rows are retained. The chosen DIR32 spelling already exists, so no duplicate row is appended. Function identities and ledger row order remain unchanged.

A receiver adjustment before either call, a thunk that reaches another body, or a publisher storing a different object would refute the shared-pointer identity. A real class name remains open pending independent EA or reference evidence.

## Raw evidence

`build/rlink/identity-seven-1791161098/retail-probe.log` records image hash, section bounds, bytes, range checks, all references and followed five-byte E9 chains. `retail-refs.json` records decoded sites and owning rows. `ledger-spellings.log`, `game-users.log`, `spelling-counts-v2.log` and `spelling-counts.json` preserve the spelling census. `additional-apt-spelling.log` captures both extra Boolean head declarations. `maplist-startup-disasm.log`, `static-holder.log`, `allocator-use.log`, `allocator-writer.log`, `pointee-data.log`, `allocator-vtable-methods.log`, `codec-scalar-pointee.log` and `codec-simd-pointee.log` contain focused probes. `classic-builder-disasm.log` and `classic-name-and-thunk.log` prove the C literal and its E9 constructor route. `maplist-reference-full.log` and `vendor-locale.log` record reference evidence. `ownership-audit.log` and `ownership-audit.json` prove one compiled definition and canonical declarations in every authored retail user. Per-source build and link logs and gate results are indexed in `build/worker-final.md`.
