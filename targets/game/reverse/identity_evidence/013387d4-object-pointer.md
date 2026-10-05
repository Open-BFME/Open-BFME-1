# Object-pointer datum at VA 0x013387D4

## Result

The datum is the initially null head of the Apt Boolean-value free list. Its canonical spelling remains `g_rva008D2A80` with pointee `class Rva008D2A80`. No exact Apt static-member name is proven. The node stores vptr and flags at +0 and +4 and reuses +8 for an intrusive next-pointer or a Boolean payload.

The datum has size 4 and lies in `.data`. Retail initially contains `00 00 00 00`. It is in the virtual zero-filled tail of the section. The PE base-relocation directory is absent. There is no initialized pointer value or relocation to resolve at this slot. Retail dword operand widths and the compiled canonical pointer symbol independently prove the four-byte extent. The range scan finds no existing data row and no DIR32 name in its interior; competing names all start at the same address.

## Retail facts and receiver and argument contract

RVA 0x008D2A80 reads the head, stores it at [ECX+8], and publishes ECX. RVAs 0x008D2A30 and 0x008D2A90 push onto that identical address. RVA 0x008D2A40 drains the list using next at +8. The Boolean factory at RVA 0x008996B0 pops +8, allocates 12 bytes on the fresh path, and stores its Boolean payload at +8. Its type discriminator is 5. The push contract is an ECX node receiver with no stack arguments; factory payload and local node views require casts, not another global.

## Read and write references

The table lists every decoded direct absolute reference in the byte scan, grouped by instruction site. A literal occurrence outside the function maps is handled separately above for the map-holder startup writer. Overlapping ledger and Ghidra extents are deduplicated here.

| Instruction VA | Retail instruction | Containing body RVA |
|---|---|---|
| 0x00C996B0 | `mov eax, dword ptr [0x13387d4]` | 0x008996B0 |
| 0x00C996C4 | `mov dword ptr [0x13387d4], ecx` | 0x008996B0 |
| 0x00C99823 | `mov eax, dword ptr [0x13387d4]` | 0x00899800 |
| 0x00C9982F | `mov dword ptr [0x13387d4], ecx` | 0x00899800 |
| 0x00C9999A | `mov eax, dword ptr [0x13387d4]` | 0x00899800 |
| 0x00C999AC | `mov dword ptr [0x13387d4], ecx` | 0x00899800 |
| 0x00C99A7B | `mov eax, dword ptr [0x13387d4]` | 0x00899800 |
| 0x00C99A8B | `mov dword ptr [0x13387d4], edx` | 0x00899800 |
| 0x00CA55D4 | `mov eax, dword ptr [0x13387d4]` | 0x008A5560 |
| 0x00CA55E6 | `mov dword ptr [0x13387d4], ecx` | 0x008A5560 |
| 0x00CA56ED | `mov eax, dword ptr [0x13387d4]` | 0x008A5560 |
| 0x00CA56F9 | `mov dword ptr [0x13387d4], edx` | 0x008A5560 |
| 0x00CA57C5 | `mov eax, dword ptr [0x13387d4]` | 0x008A5560 |
| 0x00CA57D7 | `mov dword ptr [0x13387d4], ecx` | 0x008A5560 |
| 0x00CA59BB | `mov eax, dword ptr [0x13387d4]` | 0x008A58C0 |
| 0x00CA59CA | `mov dword ptr [0x13387d4], edx` | 0x008A58C0 |
| 0x00CA5AF0 | `mov eax, dword ptr [0x13387d4]` | 0x008A58C0 |
| 0x00CA5B02 | `mov dword ptr [0x13387d4], ecx` | 0x008A58C0 |
| 0x00CA5CEB | `mov eax, dword ptr [0x13387d4]` | 0x008A5BF0 |
| 0x00CA5CFD | `mov dword ptr [0x13387d4], ecx` | 0x008A5BF0 |
| 0x00CA5E60 | `mov eax, dword ptr [0x13387d4]` | 0x008A5BF0 |
| 0x00CA5E6C | `mov dword ptr [0x13387d4], edx` | 0x008A5BF0 |
| 0x00CA5F94 | `mov eax, dword ptr [0x13387d4]` | 0x008A5BF0 |
| 0x00CA5FA6 | `mov dword ptr [0x13387d4], ecx` | 0x008A5BF0 |
| 0x00CA7676 | `mov eax, dword ptr [0x13387d4]` | 0x008A73E0 |
| 0x00CA768D | `mov dword ptr [0x13387d4], ecx` | 0x008A73E0 |
| 0x00CB106B | `mov eax, dword ptr [0x13387d4]` | 0x008B0EE0 |
| 0x00CB107B | `mov dword ptr [0x13387d4], edx` | 0x008B0EE0 |
| 0x00CB16D7 | `mov eax, dword ptr [0x13387d4]` | 0x008B0EE0 |
| 0x00CB16E3 | `mov dword ptr [0x13387d4], ecx` | 0x008B0EE0 |
| 0x00CB3F0D | `mov eax, dword ptr [0x13387d4]` | 0x008B3C40 |
| 0x00CB4000 | `mov eax, dword ptr [0x13387d4]` | 0x008B3C40 |
| 0x00CB4019 | `mov dword ptr [0x13387d4], ecx` | 0x008B3C40 |
| 0x00CC757F | `mov eax, dword ptr [0x13387d4]` | 0x008C7500 |
| 0x00CC758B | `mov dword ptr [0x13387d4], edx` | 0x008C7500 |
| 0x00CC76B1 | `mov eax, dword ptr [0x13387d4]` | 0x008C7500 |
| 0x00CC76C8 | `mov dword ptr [0x13387d4], ecx` | 0x008C7500 |
| 0x00CC95CF | `mov eax, dword ptr [0x13387d4]` | 0x008C8AC0 |
| 0x00CC95E5 | `mov dword ptr [0x13387d4], ecx` | 0x008C8AC0 |
| 0x00CCC181 | `mov eax, dword ptr [0x13387d4]` | 0x008CBDF0 |
| 0x00CCC192 | `mov dword ptr [0x13387d4], edx` | 0x008CBDF0 |
| 0x00CCEF62 | `mov eax, dword ptr [0x13387d4]` | 0x008CEE40 |
| 0x00CCEF74 | `mov dword ptr [0x13387d4], ecx` | 0x008CEE40 |
| 0x00CD2A30 | `mov eax, dword ptr [0x13387d4]` | 0x008D2A30 |
| 0x00CD2A40 | `mov ecx, dword ptr [0x13387d4]` | 0x008D2A40 |
| 0x00CD2A58 | `mov ecx, dword ptr [0x13387d4]` | 0x008D2A40 |
| 0x00CD2A6D | `mov dword ptr [0x13387d4], ecx` | 0x008D2A40 |
| 0x00CD2A80 | `mov eax, dword ptr [0x13387d4]` | 0x008D2A80 |
| 0x00CD2A88 | `mov dword ptr [0x13387d4], ecx` | 0x008D2A80 |
| 0x00CD2A90 | `mov eax, dword ptr [0x13387d4]` | 0x008D2A90 |
| 0x00CD2A98 | `mov dword ptr [0x13387d4], ecx` | 0x008D2A90 |

## Competing spellings before correction

Counts are game source files whose compiled objects reference or define the exact decorated spelling. Zero means that spelling is dormant; the raw count log also identifies three unlisted class-kind or namespace variants. Counts select nothing: retail facts and the existing identity pin select the canonical spelling.

| Decorated spelling | Game files |
|---|---|
| `?Rva008D2A30Head@@3PAURva008D2A30Node@@A` | 1 |
| `?Rva008D2A40Head@@3PAURva008D2A40Node@@A` | 0 |
| `?Rva008D2A90Head@@3PAURva008D2A90Node@@A` | 0 |
| `?g_rva008D2A80@@3PAVRva008D2A80@@A` | 9 |

Additional emitted spellings absent from the DIR32 table are also consolidated:

- `?Rva013387D4@@3PAURva008995E0Value@@A` appears in 2 game file(s).

## Correction and refutation

Define `?g_rva008D2A80@@3PAVRva008D2A80@@A` once in `game/GameEngine/Source/Common/Rva008D2A80Link.cpp` and add its byte-verified data row. All authored callers declare this canonical pointee type; differing local use views are explicit casts. Existing pins and DIR32 rows are retained. The chosen DIR32 spelling already exists, so no duplicate row is appended. Function identities and ledger row order remain unchanged.

A push or factory referencing a different datum, a non-pointer access to the head, or incompatible next-field offsets would refute the unification. A witnessed Apt static-member name would settle the remaining descriptive identity.

## Raw evidence

`build/rlink/identity-seven-1791161098/retail-probe.log` records image hash, section bounds, bytes, range checks, all references and followed five-byte E9 chains. `retail-refs.json` records decoded sites and owning rows. `ledger-spellings.log`, `game-users.log`, `spelling-counts-v2.log` and `spelling-counts.json` preserve the spelling census. `additional-apt-spelling.log` captures both extra Boolean head declarations. `maplist-startup-disasm.log`, `static-holder.log`, `allocator-use.log`, `allocator-writer.log`, `pointee-data.log`, `allocator-vtable-methods.log`, `codec-scalar-pointee.log` and `codec-simd-pointee.log` contain focused probes. `classic-builder-disasm.log` and `classic-name-and-thunk.log` prove the C literal and its E9 constructor route. `maplist-reference-full.log` and `vendor-locale.log` record reference evidence. `ownership-audit.log` and `ownership-audit.json` prove one compiled definition and canonical declarations in every authored retail user. Per-source build and link logs and gate results are indexed in `build/worker-final.md`.

Three declaration changes renumbered compiler cleanup labels. The repository EH-state tool bound the labels through retail and COFF unwind maps and updated only seven `functions.csv` notes. `eh-before/report.json`, `eh-fix.log`, `eh-after/report.json` and `build-eh-repaired.log` preserve the independent state mapping and byte verification. No function extent or identity changes.
