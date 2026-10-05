# Object-pointer datum at VA 0x013387CC

## Result

The datum is the initially null head of the Apt floating-value free list. Its canonical spelling remains `g_rva008D29A0` with pointee `class Rva008D29A0`. The exact original Apt static-member name is not established. The node has a vptr at +0, flags at +4, and an intrusive next-pointer or float payload at +8. The address-derived pointee names are layout views of this one list, not separate globals.

The datum has size 4 and lies in `.data`. Retail initially contains `00 00 00 00`. It is in the virtual zero-filled tail of the section. The PE base-relocation directory is absent. There is no initialized pointer value or relocation to resolve at this slot. Retail dword operand widths and the compiled canonical pointer symbol independently prove the four-byte extent. The range scan finds no existing data row and no DIR32 name in its interior; competing names all start at the same address.

## Retail facts and receiver and argument contract

RVA 0x008D29A0 reads the head into EAX, stores it at [ECX+8], then publishes ECX. RVAs 0x008D2950 and 0x008D29B0 do the same. RVA 0x008D2960 reads next at +8, performs cleanup and deletion, and stores the saved next as the head. RVA 0x008A4CD0 pops the same +8 field and writes a float there; the fresh-object path allocates 12 bytes. The other float-producing readers follow this same pop contract. There is no stack argument to the three push members, and ECX is the node receiver.

## Read and write references

The table lists every decoded direct absolute reference in the byte scan, grouped by instruction site. A literal occurrence outside the function maps is handled separately above for the map-holder startup writer. Overlapping ledger and Ghidra extents are deduplicated here.

| Instruction VA | Retail instruction | Containing body RVA |
|---|---|---|
| 0x00CA4CD0 | `mov eax, dword ptr [0x13387cc]` | 0x008A4CD0 |
| 0x00CA4CE4 | `mov dword ptr [0x13387cc], ecx` | 0x008A4CD0 |
| 0x00CA6E0E | `mov eax, dword ptr [0x13387cc]` | 0x008A6CB0 |
| 0x00CA6E20 | `mov dword ptr [0x13387cc], ecx` | 0x008A6CB0 |
| 0x00CA6EC6 | `mov eax, dword ptr [0x13387cc]` | 0x008A6CB0 |
| 0x00CA6ED6 | `mov dword ptr [0x13387cc], edx` | 0x008A6CB0 |
| 0x00CA6FF8 | `mov eax, dword ptr [0x13387cc]` | 0x008A6CB0 |
| 0x00CA7014 | `mov dword ptr [0x13387cc], ecx` | 0x008A6CB0 |
| 0x00CA70BA | `mov eax, dword ptr [0x13387cc]` | 0x008A6CB0 |
| 0x00CA70CA | `mov dword ptr [0x13387cc], edx` | 0x008A6CB0 |
| 0x00CAF3D5 | `mov eax, dword ptr [0x13387cc]` | 0x008AF330 |
| 0x00CAF3E8 | `mov dword ptr [0x13387cc], ecx` | 0x008AF330 |
| 0x00CAF565 | `mov eax, dword ptr [0x13387cc]` | 0x008AF4C0 |
| 0x00CAF578 | `mov dword ptr [0x13387cc], ecx` | 0x008AF4C0 |
| 0x00CB038F | `mov eax, dword ptr [0x13387cc]` | 0x008B02A0 |
| 0x00CB03C4 | `mov dword ptr [0x13387cc], edx` | 0x008B02A0 |
| 0x00CB0481 | `mov eax, dword ptr [0x13387cc]` | 0x008B02A0 |
| 0x00CB0493 | `mov dword ptr [0x13387cc], ecx` | 0x008B02A0 |
| 0x00CB0539 | `mov eax, dword ptr [0x13387cc]` | 0x008B02A0 |
| 0x00CB054B | `mov dword ptr [0x13387cc], ecx` | 0x008B02A0 |
| 0x00CB05F1 | `mov eax, dword ptr [0x13387cc]` | 0x008B02A0 |
| 0x00CB0603 | `mov dword ptr [0x13387cc], ecx` | 0x008B02A0 |
| 0x00CB141F | `mov eax, dword ptr [0x13387cc]` | 0x008B0EE0 |
| 0x00CB142F | `mov dword ptr [0x13387cc], ecx` | 0x008B0EE0 |
| 0x00CB1B82 | `mov eax, dword ptr [0x13387cc]` | 0x008B0EE0 |
| 0x00CB1B8E | `mov dword ptr [0x13387cc], edx` | 0x008B0EE0 |
| 0x00CC9992 | `mov eax, dword ptr [0x13387cc]` | 0x008C9650 |
| 0x00CC99A4 | `mov dword ptr [0x13387cc], ecx` | 0x008C9650 |
| 0x00CCBF93 | `mov eax, dword ptr [0x13387cc]` | 0x008CBDF0 |
| 0x00CCBFA5 | `mov dword ptr [0x13387cc], ecx` | 0x008CBDF0 |
| 0x00CD2950 | `mov eax, dword ptr [0x13387cc]` | 0x008D2950 |
| 0x00CD2958 | `mov dword ptr [0x13387cc], ecx` | 0x008D2950 |
| 0x00CD2960 | `mov ecx, dword ptr [0x13387cc]` | 0x008D2960 |
| 0x00CD2978 | `mov ecx, dword ptr [0x13387cc]` | 0x008D2960 |
| 0x00CD298D | `mov dword ptr [0x13387cc], ecx` | 0x008D2960 |
| 0x00CD29A0 | `mov eax, dword ptr [0x13387cc]` | 0x008D29A0 |
| 0x00CD29A8 | `mov dword ptr [0x13387cc], ecx` | 0x008D29A0 |
| 0x00CD29B0 | `mov eax, dword ptr [0x13387cc]` | 0x008D29B0 |
| 0x00CD29B8 | `mov dword ptr [0x13387cc], ecx` | 0x008D29B0 |

## Competing spellings before correction

Counts are game source files whose compiled objects reference or define the exact decorated spelling. Zero means that spelling is dormant; the raw count log also identifies three unlisted class-kind or namespace variants. Counts select nothing: retail facts and the existing identity pin select the canonical spelling.

| Decorated spelling | Game files |
|---|---|
| `?Rva008AF330Head@@3PAVRva008A4C00Value@@A` | 0 |
| `?Rva008D2950Head@@3PAURva008D2950Node@@A` | 0 |
| `?Rva008D2960Head@@3PAURva008D2960Node@@A` | 0 |
| `?Rva008D29B0Head@@3PAURva008D29B0Node@@A` | 0 |
| `?g_rva008D29A0@@3PAVRva008D29A0@@A` | 8 |

Additional emitted spellings absent from the DIR32 table are also consolidated:

- `?Rva008AF330Head@@3PAURva008A4C00Value@@A` appears in 1 game file(s).

## Correction and refutation

Define `?g_rva008D29A0@@3PAVRva008D29A0@@A` once in `game/GameEngine/Source/Common/Rva008D29A0Link.cpp` and add its byte-verified data row. All authored callers declare this canonical pointee type; differing local use views are explicit casts. Existing pins and DIR32 rows are retained. The chosen DIR32 spelling already exists, so no duplicate row is appended. Function identities and ledger row order remain unchanged.

A different absolute address in any push or pop, a next-field offset other than +8, or a reader that consumes this global as a scalar instead of a pointer would refute the unification. A proven Apt static-member identity could replace the retained address-derived spelling later.

## Raw evidence

`build/rlink/identity-seven-1791161098/retail-probe.log` records image hash, section bounds, bytes, range checks, all references and followed five-byte E9 chains. `retail-refs.json` records decoded sites and owning rows. `ledger-spellings.log`, `game-users.log`, `spelling-counts-v2.log` and `spelling-counts.json` preserve the spelling census. `additional-apt-spelling.log` captures both extra Boolean head declarations. `maplist-startup-disasm.log`, `static-holder.log`, `allocator-use.log`, `allocator-writer.log`, `pointee-data.log`, `allocator-vtable-methods.log`, `codec-scalar-pointee.log` and `codec-simd-pointee.log` contain focused probes. `classic-builder-disasm.log` and `classic-name-and-thunk.log` prove the C literal and its E9 constructor route. `maplist-reference-full.log` and `vendor-locale.log` record reference evidence. `ownership-audit.log` and `ownership-audit.json` prove one compiled definition and canonical declarations in every authored retail user. Per-source build and link logs and gate results are indexed in `build/worker-final.md`.
