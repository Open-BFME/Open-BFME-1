# RVA 0x006D2A00 (HeightMapRenderObjClass006D2A00::updateCenter, ILT-confirmed FlatHeightMapRenderObjClass::updateCenter): EXACT

Best candidate: build/wf/006d2a00/final.cpp, probe `result EXACT (modulo relocation slots)` at 1984/1984 bytes, 16 relocs.
Symbol: `?updateCenter@HeightMapRenderObjClass006D2A00@@UAEXPAVCameraClass@@PAV?$RefMultiListIterator@VRenderObjClass@@@@@Z`.
Flags unchanged from the bank: `/DNDEBUG /MD /EHs-c- /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib` (probe defaults otherwise).

## Baseline
Bank targets/game/reverse/attempts/0x006d2a00.cpp reproduces as logged: 1984 bytes, 13 non-reloc diffs at +0x31C..+0x329
(retail `mov ebx,[down]; mov ebp,[up]; cmp down.changed; store; store`, bank `mov ebx,[down]; cmp; store ebx; mov ebx,[up]; store`).
The bank also relied on `*(const volatile int*)&field_30fc` to force the budget reload in the bisection loop (not landable).

## Donor
BFME 2 `Code/GameEngineDevice/Source/W3DDevice/GameClient/FlatHeightMapUpdateCenter.cpp` at open-bfme-2 2bac16a6
(rowed matched 1773B at BFME 2 0x000E3CE1) is the same routine (multi-camera variant). Its statement order and loop forms were ported onto the bank's BFME 1 layout view.
Donor facts used: neighbor statement order and the do/while budget search. Layout offsets, callees and ABI stay from BFME 1 evidence (bank).

## What fixed it (ablations, each n=1 probe)
| Variant | Result |
|---|---|
| bank | 13 diffs |
| bank + donor neighbor loop only (volatile search kept) | EXACT |
| bank + donor search only | 13 diffs |
| final (both) | EXACT |
| final, i==0 middle case back to bottom, top, right order | 13 diffs (the bank residue) |
| final with bank-style index/index+1/index-1 | EXACT |
| final with bank declaration `int top=0,right=0,bottom=0,left=0;` | EXACT |
| final, `bool changed;` uninitialised | EXACT |
| final, separate `left=0;bottom=0;right=0;top=0;` statements | 2035B, 1176 diffs |

Decisive lever 1: in the `i==0`, middle-row case assign `bottom`, then `right`, then `top` (donor order) and test
`down||right||up`. MSVC 7.1 then cross-jumps the right load into the shared tail at +0x443 and the bottom and top loads
stay live together (EBX/EBP) before the changed test. Previous trials only swapped bottom and top (15 diffs) and never moved right between them.
Decisive lever 2 (removes volatile): donor do/while search `do { ... if(count<field_30fc){low=high;high*=2;} } while(count<field_30fc);`
and the bisection compares `count` directly with member `field_30fc`; this restores the per-pass member reload without volatile.

## Ruled out earlier (see identity_evidence/006d2a00-*.md)
volatile reads, wrappers, getters, local permutations, register hints, G5/G6/G7/GB, switch forms, flag snapshots, visible helpers: none needed.

## Landing notes (read-only checks, not landed)
(a) `ilt_oracle.py check` for the bank's address-derived symbol: CONTRADICTED (placeholder name, as before);
`?updateCenter@FlatHeightMapRenderObjClass@@UAEXPAVCameraClass@@PAV?$RefMultiListIterator@VRenderObjClass@@@@@Z` is CONFIRMED (exact).
symbols.csv has only `?b_006d2a00@@YAXXZ` (gen-thunk body) at this address. Use the FlatHeightMap name if the class gate allows a TU view;
otherwise keep the bank's placeholder name like the prior bank did.
(b) The TU defines no helper bodies (callees are declared only); nothing to probe for COMDAT losers.
(c) Calls (callees.py): j_0002fe50 -> 0x6C8E50 `?updateCenter@BaseHeightMapRenderObjClass@@...` (x2), j_00041cc7 -> 0x728D30
`?updateCenter@W3DTerrainBackground@@QAEXPAVCameraClass@@@Z`, j_00039dfb -> 0x7287E0 `?setAndClear@Rva007287E0StateReset@@QAEHPAE@Z`,
`?Get_Position@RenderObjClass@@QBE?AVVector3@@XZ` 0x9202C0, and the neighbor setter through `?j_00031de0@@YAXXZ` (bank's member-pointer union; body row is
`?bfmeSet@Gen_0072EA60@@QAEXHHHHH@Z`, whose int fifth argument reshapes the caller frame, so the bank binds the ILT name).
Globals: VA 0x012F08A0 `Rva012F08A0` (dir32; data_rows owner `?g_aiTargetDispatchSuppressed@@3_NA`), VA 0x012ED5C8 `Rva012ED5C8` (dir32;
data_rows owner `?TheWritableGlobalData@@3PAVGlobalData@@A`). VA 0x012F8010/14/18 are referenced as `Rva00EF8010/14/18` and have NO row in
dir32_addresses.csv or data_rows.csv; the prior bank reported DIR32 ownership passing, but if the gate refuses them they need data rows
(tools/add_data_match.py). Constants at 0x01096418 (400.0f) and 0x0107533C (0.5f, `g_rva0107533C`) were reported verified by the prior run.
(d) TU: a standalone game/GameEngineDevice/Source/W3DDevice/GameClient/FlatHeightMapUpdateCenter.cpp (mirrors the donor file; the
existing FlatHeightMap.cpp compiles the incompatible Zero Hour layout).
