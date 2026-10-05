# Object-pointer datum at VA 0x0130A5B0

## Result

The datum is the initially null process-wide allocator interface pointer. The chosen existing spelling is `g_Rva0130A5B0`, typed `struct Rva007F00B0Allocator *`, owned by its main writer. No EA allocator class name is asserted. The 12-byte object contains its vptr at +0, allocation callback at +4, and release callback at +8.

The datum has size 4 and lies in `.data`. Retail initially contains `00 00 00 00`. It is in the virtual zero-filled tail of the section. The PE base-relocation directory is absent. There is no initialized pointer value or relocation to resolve at this slot. Retail dword operand widths and the compiled canonical pointer symbol independently prove the four-byte extent. The range scan finds no existing data row and no DIR32 name in its interior; competing names all start at the same address.

## Retail facts and receiver and argument contract

RVA 0x007F00B0 returns when the global is already non-null. Otherwise it obtains 12 bytes through its first cdecl callback argument (size 12, second argument 0), or through operator new. It stores the allocation callback at +4, the vptr 0x0112A5C4 at +0, and the release callback at +8, then publishes the object. RVAs 0x007EFF10 and 0x007F0060 call the object field at +8 as cdecl (object, 0) and clear the global. RVAs 0x007F0000 and 0x007F0030 load the vptr from the same object and use slots +8 and +12 with ECX as receiver and two stack arguments. The vtable contains VA 0x00BEFF40, 0x00BEFF50, 0x00BEFF60 and 0x00BEFF80; the latter two read the allocation and release callbacks at object+4 and object+8. The first-use path references the EA literal at VA 0x0112A5A8, "no FESL allocator defined", which independently proves the FESL allocator role. The BfmeS1019 declaration is therefore a virtual-interface use view of the object, not a second singleton.

## Read and write references

The table lists every decoded direct absolute reference in the byte scan, grouped by instruction site. A literal occurrence outside the function maps is handled separately above for the map-holder startup writer. Overlapping ledger and Ghidra extents are deduplicated here.

| Instruction VA | Retail instruction | Containing body RVA |
|---|---|---|
| 0x00BEFF10 | `mov eax, dword ptr [0x130a5b0]` | 0x007EFF10 |
| 0x00BEFF22 | `mov dword ptr [0x130a5b0], 0` | 0x007EFF10 |
| 0x00BEFFC0 | `mov eax, dword ptr [0x130a5b0]` | 0x007EFFC0 |
| 0x00BEFFD3 | `mov eax, dword ptr [0x130a5b0]` | 0x007EFFC0 |
| 0x00BF0000 | `mov ecx, dword ptr [0x130a5b0]` | 0x007F0000 |
| 0x00BF0014 | `mov ecx, dword ptr [0x130a5b0]` | 0x007F0000 |
| 0x00BF0030 | `mov ecx, dword ptr [0x130a5b0]` | 0x007F0030 |
| 0x00BF0044 | `mov ecx, dword ptr [0x130a5b0]` | 0x007F0030 |
| 0x00BF0060 | `mov eax, dword ptr [0x130a5b0]` | 0x007F0060 |
| 0x00BF0072 | `mov dword ptr [0x130a5b0], 0` | 0x007F0060 |
| 0x00BF00B0 | `mov eax, dword ptr [0x130a5b0]` | 0x007F00B0 |
| 0x00BF00FF | `mov dword ptr [0x130a5b0], eax` | 0x007F00B0 |
| 0x00BF0106 | `mov dword ptr [0x130a5b0], 0` | 0x007F00B0 |

## Competing spellings before correction

Counts are game source files whose compiled objects reference or define the exact decorated spelling. Zero means that spelling is dormant; the raw count log also identifies three unlisted class-kind or namespace variants. Counts select nothing: retail facts and the existing identity pin select the canonical spelling.

| Decorated spelling | Game files |
|---|---|
| `?g_Rva0130A5B0@@3PAURva007F0060Allocator@@A` | 0 |
| `?g_Rva0130A5B0@@3PAURva007F00B0Allocator@@A` | 2 |
| `?g_bfme929Ptr@@3PAXA` | 2 |
| `?g_bfmeS1019@@3PAVBfmeS1019@@A` | 2 |

## Correction and refutation

Define `?g_Rva0130A5B0@@3PAURva007F00B0Allocator@@A` once in `game/GameEngine/Source/Common/Rva007F00B0AllocatorInit.cpp` and add its byte-verified data row. All authored callers declare this canonical pointee type; differing local use views are explicit casts. Existing pins and DIR32 rows are retained. The chosen DIR32 spelling already exists, so no duplicate row is appended. Function identities and ledger row order remain unchanged.

A writer allocating a different layout, a teardown callback obtained from a vtable instead of object+8, or a virtual user loading a different global would refute this contract. An EA string or independent reference could supply the interface real name.

## Raw evidence

`build/rlink/identity-seven-1791161098/retail-probe.log` records image hash, section bounds, bytes, range checks, all references and followed five-byte E9 chains. `retail-refs.json` records decoded sites and owning rows. `ledger-spellings.log`, `game-users.log`, `spelling-counts-v2.log` and `spelling-counts.json` preserve the spelling census. `additional-apt-spelling.log` captures both extra Boolean head declarations. `maplist-startup-disasm.log`, `static-holder.log`, `allocator-use.log`, `allocator-writer.log`, `pointee-data.log`, `allocator-vtable-methods.log`, `codec-scalar-pointee.log` and `codec-simd-pointee.log` contain focused probes. `classic-builder-disasm.log` and `classic-name-and-thunk.log` prove the C literal and its E9 constructor route. `maplist-reference-full.log` and `vendor-locale.log` record reference evidence. `ownership-audit.log` and `ownership-audit.json` prove one compiled definition and canonical declarations in every authored retail user. Per-source build and link logs and gate results are indexed in `build/worker-final.md`.
