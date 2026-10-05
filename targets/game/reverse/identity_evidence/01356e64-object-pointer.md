# Object-pointer datum at VA 0x01356E64

## Result

The datum is the initially null mutable codec bounding-setup callback slot. Keep the existing `g_rva01356E64` spelling with type `int *(__cdecl *)(Rva009ACBA0Context *, int)`. It points to a function, not to a codec context. The context type names in the callers are partial views; the returning-int spelling loses pointer type information.

The datum has size 4 and lies in `.data`. Retail initially contains `00 00 00 00`. It is in the virtual zero-filled tail of the section. The PE base-relocation directory is absent. There is no initialized pointer value or relocation to resolve at this slot. Retail dword operand widths and the compiled canonical pointer symbol independently prove the four-byte extent. The range scan finds no existing data row and no DIR32 name in its interior; competing names all start at the same address.

## Retail facts and receiver and argument contract

RVA 0x009B0D60 writes RVA 0x009B6D40 into this slot in the two SIMD branches, and RVA 0x009ACBA0 in the scalar branch. Both targets take (context, integer) from the stack and return an int-buffer pointer in EAX with a plain ret. The scalar target loads context+0x3C and returns its base+256-int interior; the SIMD target loads context+0x3C, aligns its base+0x400 to 32 bytes, writes six dwords, and returns that buffer. Indirect callers at RVAs 0x009ACC40, 0x009AF320 and 0x009B3800 push two arguments, call the same absolute slot, and use EAX as the resulting buffer. The state field at +0x38 receives the pointer bits. The writer previously used a TU-local grouping array; only its slot 1 is respelled to the exported datum, leaving the other slots unchanged.

## Read and write references

The table lists every decoded direct absolute reference in the byte scan, grouped by instruction site. A literal occurrence outside the function maps is handled separately above for the map-holder startup writer. Overlapping ledger and Ghidra extents are deduplicated here.

| Instruction VA | Retail instruction | Containing body RVA |
|---|---|---|
| 0x00DACC72 | `call dword ptr [0x1356e64]` | 0x009ACC40 |
| 0x00DAF34F | `call dword ptr [0x1356e64]` | 0x009AF320 |
| 0x00DB0DA8 | `mov dword ptr [0x1356e64], 0xdb6d40` | 0x009B0D60 |
| 0x00DB0ECB | `mov dword ptr [0x1356e64], 0xdb6d40` | 0x009B0D60 |
| 0x00DB0FDD | `mov dword ptr [0x1356e64], 0xdacba0` | 0x009B0D60 |
| 0x00DB3843 | `call dword ptr [0x1356e64]` | 0x009B3800 |

## Competing spellings before correction

Counts are game source files whose compiled objects reference or define the exact decorated spelling. Zero means that spelling is dormant; the raw count log also identifies three unlisted class-kind or namespace variants. Counts select nothing: retail facts and the existing identity pin select the canonical spelling.

| Decorated spelling | Game files |
|---|---|
| `?g_rva01356E64@@3P6AHPAURva009ACC40State@@H@ZA` | 1 |
| `?g_rva01356E64@@3P6APAHPAURva009ACBA0Context@@H@ZA` | 1 |
| `?g_rva01356E64@@3P6APAHPAURva009B3800Context@@H@ZA` | 1 |

## Correction and refutation

Define `?g_rva01356E64@@3P6APAHPAURva009ACBA0Context@@H@ZA` once in `game/GameEngine/Source/Common/BfmeCodecCpuDispatch.cpp` and add its byte-verified data row. All authored callers declare this canonical pointee type; differing local use views are explicit casts. Existing pins and DIR32 rows are retained. The chosen DIR32 spelling already exists, so no duplicate row is appended. Function identities and ledger row order remain unchanged.

A dispatched target with a different stack-pop or return contract, a caller passing an adjusted receiver incompatible with context+0x3C, or an interior datum inside these four bytes would refute the unified callback type.

## Raw evidence

`build/rlink/identity-seven-1791161098/retail-probe.log` records image hash, section bounds, bytes, range checks, all references and followed five-byte E9 chains. `retail-refs.json` records decoded sites and owning rows. `ledger-spellings.log`, `game-users.log`, `spelling-counts-v2.log` and `spelling-counts.json` preserve the spelling census. `additional-apt-spelling.log` captures both extra Boolean head declarations. `maplist-startup-disasm.log`, `static-holder.log`, `allocator-use.log`, `allocator-writer.log`, `pointee-data.log`, `allocator-vtable-methods.log`, `codec-scalar-pointee.log` and `codec-simd-pointee.log` contain focused probes. `classic-builder-disasm.log` and `classic-name-and-thunk.log` prove the C literal and its E9 constructor route. `maplist-reference-full.log` and `vendor-locale.log` record reference evidence. `ownership-audit.log` and `ownership-audit.json` prove one compiled definition and canonical declarations in every authored retail user. Per-source build and link logs and gate results are indexed in `build/worker-final.md`.
