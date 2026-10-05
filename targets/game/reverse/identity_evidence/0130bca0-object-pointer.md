# Object-pointer datum at VA 0x0130BCA0

## Result

The datum is the initially null STLport classic-locale implementation pointer. Prefer the existing pinned `_STL::_Bfme_classic_locale` spelling and the reference-defined `_STL::_Locale_impl` pointee over the two void-pointer spellings. The Bfme-prefixed storage spelling is retained; the exact upstream storage identifier is not newly asserted.

The datum has size 4 and lies in `.data`. Retail initially contains `00 00 00 00`. It is in the virtual zero-filled tail of the section. The PE base-relocation directory is absent. There is no initialized pointer value or relocation to resolve at this slot. Retail dword operand widths and the compiled canonical pointer symbol independently prove the four-byte extent. The range scan finds no existing data row and no DIR32 name in its interior; competing names all start at the same address.

## Retail facts and receiver and argument contract

The builder at RVA 0x0083B330 placement-constructs the "C" locale implementation at VA 0x0130B2A0 and initializes its standard facets. Matched writers at RVAs 0x0083B6C0, 0x0083CB30 and 0x00C6D850 store that builder result to the identical global. `_STL::locale::locale()` at RVA 0x00832120 loads this pointer and invokes virtual slot 1 before assigning its `_M_impl`. Release bodies at RVAs 0x00832100, 0x00832740 and 0x00C70CA0 invoke virtual slot 2 and decrement the classic-locale initialization count. The vendored STLport `_locale.h` line 44 declares `_Locale_impl`, lines 117-118 accept that pointer, line 170 declares locale::classic(), and line 190 types `_M_impl` as `_Locale_impl *`. This independently establishes the pointee spelling. The Zero Hour snapshot omits STLport implementation sources, so no claim is made from a missing counterpart.

## Read and write references

The table lists every decoded direct absolute reference in the byte scan, grouped by instruction site. A literal occurrence outside the function maps is handled separately above for the map-holder startup writer. Overlapping ledger and Ghidra extents are deduplicated here.

| Instruction VA | Retail instruction | Containing body RVA |
|---|---|---|
| 0x00C32109 | `mov ecx, dword ptr [0x130bca0]` | 0x00832100 |
| 0x00C32129 | `mov ecx, dword ptr [0x130bca0]` | 0x00832120 |
| 0x00C32749 | `mov ecx, dword ptr [0x130bca0]` | 0x00832740 |
| 0x00C36701 | `mov ecx, dword ptr [0x130bca0]` | 0x008366E0 |
| 0x00C3673B | `mov ecx, dword ptr [0x130bca0]` | 0x008366E0 |
| 0x00C36751 | `mov dword ptr [0x130bca0], ecx` | 0x008366E0 |
| 0x00C3B6D3 | `mov dword ptr [0x130bca0], eax` | 0x0083B6C0 |
| 0x00C3CB46 | `mov dword ptr [0x130bca0], eax` | 0x0083CB30 |
| 0x0106D866 | `mov dword ptr [0x130bca0], eax` | 0x00C6D850 |
| 0x01070CA9 | `mov ecx, dword ptr [0x130bca0]` | 0x00C70CA0 |

## Competing spellings before correction

Counts are game source files whose compiled objects reference or define the exact decorated spelling. Zero means that spelling is dormant; the raw count log also identifies three unlisted class-kind or namespace variants. Counts select nothing: retail facts and the existing identity pin select the canonical spelling.

| Decorated spelling | Game files |
|---|---|
| `?_Bfme_classic_locale@_STL@@3PAV_Locale_impl@1@A` | 1 |
| `?g_bfmeObjWE@@3PAXA` | 4 |
| `?g_bfmePtrTB@@3PAXA` | 1 |

Additional emitted spellings absent from the DIR32 table are also consolidated:

- `?_Bfme_classic_locale@@3PAXA` appears in 1 game file(s).

## Correction and refutation

Define `?_Bfme_classic_locale@_STL@@3PAV_Locale_impl@1@A` once in `game/GameEngine/Source/Common/BfmeGrokOnce.cpp` and add its byte-verified data row. All authored callers declare this canonical pointee type; differing local use views are explicit casts. Existing pins and DIR32 rows are retained. The chosen DIR32 spelling already exists, so no duplicate row is appended. Function identities and ledger row order remain unchanged.

A builder return other than the C-locale implementation, a constructor reading another pointer, or a conflicting reference-defined pointee type would refute the correction. A full upstream implementation matching this version would settle the original storage identifier.

## Raw evidence

`build/rlink/identity-seven-1791161098/retail-probe.log` records image hash, section bounds, bytes, range checks, all references and followed five-byte E9 chains. `retail-refs.json` records decoded sites and owning rows. `ledger-spellings.log`, `game-users.log`, `spelling-counts-v2.log` and `spelling-counts.json` preserve the spelling census. `additional-apt-spelling.log` captures both extra Boolean head declarations. `maplist-startup-disasm.log`, `static-holder.log`, `allocator-use.log`, `allocator-writer.log`, `pointee-data.log`, `allocator-vtable-methods.log`, `codec-scalar-pointee.log` and `codec-simd-pointee.log` contain focused probes. `classic-builder-disasm.log` and `classic-name-and-thunk.log` prove the C literal and its E9 constructor route. `maplist-reference-full.log` and `vendor-locale.log` record reference evidence. `ownership-audit.log` and `ownership-audit.json` prove one compiled definition and canonical declarations in every authored retail user. Per-source build and link logs and gate results are indexed in `build/worker-final.md`.
