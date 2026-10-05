# TheGameClient at VA 0x012F1464

## Result and retail extent

This datum is one zero-initialized four-byte `GameClient *TheGameClient` in retail `.data`. Its initial bytes are `00 00 00 00` in the section's virtual-only tail, so it holds null and no initialized pointer relocation needs following. The image has no base-relocation directory. Raw word accesses prove the pointer width. No data row overlaps this word and no DIR32 symbol starts strictly inside its extent. The canonical spelling is already in `dir32_addresses.csv` and the competing rows are retained; adding a duplicate row would be redundant. One definition is backed by `tools/add_data_match.py` in `game/GameEngine/Source/GameClient/GameClient.cpp`.

## Retail facts and reference

GameEngine initialization at VA 00479060 passes slot address 012F1464 at 00479CE3 to ILT 004341D5 (E9 F6060400), ending at 004748D0. The naming string at 010762EC is TheGameClient. Consumers use the singleton for drawable lookup and creation, client-frame state, and virtual client update. The partial clock and drawable-factory types describe fields or interfaces of that one client object. Their declarations are canonicalized to GameClient and their original partial views remain casts at use sites.

Reference location: `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/GameClient.cpp:95`. Existing names alone do not decide the pointee; the EA strings, initialization, typed consumer operations and reference contract above do.

## Receiver and argument contract

The word holds an object pointer. Retail loads it into ECX for thiscall members or reads its vptr for virtual dispatch. Each local partial view retains its original method signatures, offsets and arguments behind a cast at its use. The global declaration uses the one canonical pointee type. Null assignment writes the canonical pointer directly. No inheritance, wrapper, forwarding function or linker alias is introduced. All existing verified function bytes must remain identical.

## Readers and writers

Decoded retail bodies referencing this address: `0x0046B910`, `0x0046BAE0`, `0x0046BD3C`, `0x0046E910`, `0x00479060`, `0x0047E9B0`, `0x0049A580`, `0x004B4020`, `0x004B4210`, `0x004B4290`, `0x004B48D0`, `0x004B4960`, `0x004D77B0`, `0x004DF8A0`, `0x00507140`, `0x005077D0`, `0x00507D60`, `0x00508520`, `0x005112D0`, `0x00513280`, `0x005330E0`, `0x005A7A90`, `0x005AD080`, `0x00667B10`, `0x006AC620`, `0x006EDE20`, `0x006F0DD0`, `0x006F0DF0`, `0x00703BF0`, `0x00737280`, `0x00739B90`, `0x00783440`, `0x0078D000`, `0x0078DA10`, `0x00794260`, `0x0080AF50`, `0x0080AFF0`, `0x00810C20`, `0x00810D30`, `0x00810D80`, `0x00811600`, `0x00811840`, `0x00811B20`, `0x008120E0`, `0x008142B0`, `0x00814310`, `0x00814380`, `0x00816550`, `0x008165F0`, `0x00818DA0`, `0x00819A10`, `0x0081BE60`, `0x0081CEC0`, `0x00820860`, `0x00828C60`, `0x00829C10`, `0x00832010`, `0x0083ACA0`, `0x0083AF00`, `0x0083F110`, `0x00842FD0`, `0x008435A0`, `0x00843910`, `0x00844450`, `0x008445C0`, `0x00845080`, `0x00846550`, `0x008481C0`, `0x008498D0`, `0x0084A2E0`, `0x0084A6A0`, `0x008585F0`, `0x00859200`, `0x00859960`, `0x0088E480`, `0x0088E5C0`, `0x0088FC90`, `0x0089DF00`, `0x0089F8B0`, `0x0089FC90`, `0x008A2500`, `0x008A2F80`, `0x008BFFE0`, `0x008FC7C0`, `0x0091D300`, `0x0091F3A0`, `0x0095E320`, `0x00992DD0`, `0x00994010`, `0x00997A30`, `0x009AFFB0`, `0x009B51D0`, `0x009B5E50`, `0x009B6BA0`, `0x009B8520`, `0x009BA1D0`, `0x009BA200`, `0x009BA250`, `0x009BA4D0`, `0x009BA6C0`, `0x009C37E0`, `0x009CF330`, `0x009CF850`, `0x009D1140`, `0x009FC320`, `0x009FC450`, `0x009FED60`, `0x00A038C0`, `0x00A03BB0`, `0x00A03FE0`, `0x00A07A30`, `0x00A07BE0`, `0x00A4B6B0`, `0x00A65D10`, `0x00A65ED0`, `0x00A957E0`, `0x00A9F8A0`, `0x00ABBD80`, `0x00ABD6E0`, `0x00ABEB90`, `0x00AC1280`, `0x00AC3170`, `0x00AC42B0`, `0x00AC4A50`, `0x00ADC0D0`, `0x00AE2540`, `0x00AE2AC0`, `0x00AE6A80`, `0x00AE8310`, `0x00AE9AB0`, `0x00AE9B30`, `0x00AF0300`, `0x00AF2CC0`, `0x00AF3FC0`, `0x00AF5170`, `0x00AF56A0`, `0x00AF9A30`, `0x00AF9A90`, `0x00AFC5A0`, `0x00B2C7F0`, `0x00B3AED0`, `0x00B3BB10`, `0x00B3E050`, `0x00B41D30`, `0x00B42920`, `0x00B42CC0`, `0x00B42E60`, `0x00B42F70`, `0x00B446A0`, `0x00B45370`, `0x00B55170`, `0x00B5BBA0`, `0x00B5C940`, `0x00B629F0`, `0x00B6B980`, `0x00B6E7F0`, `0x00B6E90A`, `0x00B7B3F0`, `0x00BAFB50`, `0x00BB4620`, `0x00BB4FE0`, `0x00BD1F00`. The raw xref file lists every observed instruction, distinguishes reads and writes, and records each five-byte E9 step to the final target. The writer-context file gives larger initialization and destruction windows. This census is restricted to raw absolute-address references decoded within repository function extents; an indirect access through an escaped pointer is not asserted absent.

## Competing spellings

The counts describe matching explicit game declarations or definitions in the strict original-declaration inventory; comments and same-named statics can require manual interpretation and the counts do not decide identity.

| Decorated spelling | Game files declaring it |
|---|---:|
| `?ClientAt012F1464@@3PAVClient0009A580@@A` | 0 |
| `?ClientGlobal007629F0@@3PAVClient007629F0@@A` | 0 |
| `?TheBFMEDrawableFactory@@3PAVBFMEDrawableFactory@@A` | 0 |
| `?TheBfmeClientYB@@3PAVBfmeClientYB@@A` | 0 |
| `?TheGameClient@@3PAVBfmeMoveHintGameClient@@A` | 0 |
| `?TheGameClient@@3PAVClientRoot4120@@A` | 1 |
| `?TheGameClient@@3PAVGameClient@@A` | 95 |
| `?TheGameClient@@3PAVRva0043F110ClientRoot4120@@A` | 0 |
| `?TheGameClient@@3PAVRva004FC7C0Client@@A` | 0 |
| `?TheGameClientClientUpdate@@3PAVBuffManagerRegistry@@A` | 0 |
| `?TheGameClientClientUpdate@@3PAVClientFrameSubsystem@@A` | 1 |
| `?ZoomTerrain@@3PAVZoomEnvironment@@A` | 1 |
| `?g012F1464@@3PAURva0038DA10Client@@A` | 1 |
| `?g_Rva002F0DF0Global@@3PAVRva002F0DF0Global@@A` | 0 |
| `?g_bfmeClientETE@@3PAVBfmeClientETE@@A` | 0 |
| `?g_bfmeClock997@@3PAVBfmeClock997@@A` | 0 |
| `?g_bfmeE1021@@3PAVBfmeE1021@@A` | 0 |
| `?g_bfmeHolderBP@@3PAVBfmeHolderBP@@A` | 0 |
| `?g_bfmeSingletonR@@3PAVBfmeSingletonR@@A` | 0 |
| `?g_bfmeSinkB1010@@3PAVBfmeSinkB1010@@A` | 0 |
| `?g_bfmeSrc1007@@3PAVBfmeSrc1007@@A` | 0 |
| `?g_bfmeSrc962@@3PAVBfmeSrc962@@A` | 0 |
| `?g_bfmeT1057@@3PAVBfmeT1057@@A` | 0 |
| `?g_bfmeT1058@@3PAVBfmeT1058@@A` | 1 |
| `?g_rva001077D0FrameSource@@3PAVRva001077D0FrameSource@@A` | 0 |
| `?g_rva0048E5C0Clock@@3PAURva0048E5C0Clock@@A` | 0 |
| `?g_u4Clock006038C0@@3PAVU4Clock006038C0@@A` | 0 |
| `?g_va012F1464@@3PAVRva0077B3F0Client@@A` | 0 |

## Refutation and raw evidence

A writer publishing a different subsystem, a consumer requiring another object instead of the witnessed partial view, a mismatched reference contract, an interior datum boundary, a different ILT destination or any changed verified instruction would refute this correction. The retail factory outputs and singleton naming strings are independently re-checkable at the addresses above.

Raw logs: `build/rlink/pointer-globals-20261005/012f1464-retail-xrefs.log`, `012f1464-writer-context.log`, `inventory.log`, `strict-original-declarations.log`, `strict-original-declarations.log`, `global-type-pins.log`, `selected-constructor-rows.log`, `zh-global-declarations.log` and `zh-global-uses.log`. Source gates, data gates, declaration checks and before/after LINKED measurements are retained beside them and indexed in `check-receipts.jsonl` and `build/worker-final.md`.
