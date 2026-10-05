# TheWindowManager at VA 0x012F1B40

## Result and retail extent

This datum is one zero-initialized four-byte `GameWindowManager *TheWindowManager` in retail `.data`. Its initial bytes are `00 00 00 00` in the section's virtual-only tail, so it holds null and no initialized pointer relocation needs following. The image has no base-relocation directory. Raw word accesses prove the pointer width. No data row overlaps this word and no DIR32 symbol starts strictly inside its extent. The canonical spelling is already in `dir32_addresses.csv` and the competing rows are retained; adding a duplicate row would be redundant. One definition is backed by `tools/add_data_match.py` in `game/GameEngine/Source/GameClient/GUI/GameWindowManager.cpp`.

## Retail facts and reference

GameClient initialization at VA 0082F5A0 calls its window-manager factory through the GameClient vtable at offset 0x98 and stores the result at 0082FC81. The naming string at 010F3720 is TheWindowManager. The destructor clears it at 008314B1. Window lookup, creation and system-message consumers match the Zero Hour GameWindowManager interface. This address is distinct from BFME WindowManager at VA 012F19E8, which owns Apt objects; a WindowManager spelling at 012F1B40 cannot turn this into the separate Apt manager.

Reference location: `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/GUI/GameWindowManager.cpp:58`. Existing names alone do not decide the pointee; the EA strings, initialization, typed consumer operations and reference contract above do.

## Receiver and argument contract

The word holds an object pointer. Retail loads it into ECX for thiscall members or reads its vptr for virtual dispatch. Each local partial view retains its original method signatures, offsets and arguments behind a cast at its use. The global declaration uses the one canonical pointee type. Null assignment writes the canonical pointer directly. No inheritance, wrapper, forwarding function or linker alias is introduced. All existing verified function bytes must remain identical.

## Readers and writers

Decoded retail bodies referencing this address: `0x0046E7A0`, `0x00499980`, `0x00507340`, `0x00794260`, `0x00796950`, `0x00797190`, `0x0080E680`, `0x0080E9E0`, `0x0080F780`, `0x0082EE70`, `0x0082F5A0`, `0x00831380`, `0x008329D0`, `0x0083B970`, `0x0083E3A0`, `0x0083E3E0`, `0x00840B40`, `0x008410C0`, `0x00841AF0`, `0x00841C50`, `0x00842040`, `0x00842300`, `0x008445C0`, `0x00845080`, `0x0085EF90`, `0x00862D40`, `0x00863340`, `0x00863850`, `0x00863E30`, `0x00865770`, `0x00865CE0`, `0x00865D50`, `0x008675A0`, `0x0086A870`, `0x0086E850`, `0x008703F0`, `0x00870510`, `0x00870720`, `0x00877DA0`, `0x00878250`, `0x008782E0`, `0x00878390`, `0x00878CB0`, `0x008794F0`, `0x008795A0`, `0x0087C190`, `0x0087C220`, `0x0087D040`, `0x0087D090`, `0x0087D500`, `0x0087DC50`, `0x0087DD90`, `0x0087DEC0`, `0x0087E5B0`, `0x0087EF70`, `0x0087F6E0`, `0x0087F757`, `0x00880090`, `0x00884610`, `0x00886B10`, `0x008874A0`, `0x00887870`, `0x00887B50`, `0x00887F80`, `0x0088A020`, `0x0088A6A0`, `0x0088AC10`, `0x0088D530`, `0x0088D8B0`, `0x0088D9C0`, `0x0088DCA0`, `0x0088DED0`, `0x00890470`, `0x008914C0`, `0x008920E0`, `0x00892400`, `0x00892C40`, `0x00893120`, `0x00897A50`, `0x0089CAE0`, `0x0089CC00`, `0x0089D160`, `0x0089DA40`, `0x0089E780`, `0x0089F0E0`, `0x0089F1C0`, `0x0089F640`, `0x0089F8B0`, `0x0089FC90`, `0x008A0B90`, `0x008A0F70`, `0x008A2500`, `0x008A2F80`, `0x008A3830`, `0x008A5950`, `0x008A9980`, `0x008AA7C0`, `0x008AAA70`, `0x008AAC50`, `0x008AB100`, `0x008AB1A0`, `0x008AB630`, `0x008ABA80`, `0x008AE080`, `0x008AF520`, `0x008B2D10`, `0x008B2DC0`, `0x008B2F30`, `0x008B31D0`, `0x008B3250`, `0x008B3330`, `0x008B39D0`, `0x008B3A00`, `0x008B3C00`, `0x008B3C30`, `0x008B3C70`, `0x008B3CB0`, `0x008B3CF0`, `0x008B3D60`, `0x008B3E30`, `0x008B4010`, `0x008B42F0`, `0x008B4F40`, `0x008B4FF0`, `0x008B5530`, `0x008B5C90`, `0x008B5E40`, `0x008B6190`, `0x008B69D0`, `0x008B71A0`, `0x008B7350`, `0x008B77E0`, `0x008B7810`, `0x008B7840`, `0x008B7880`, `0x008B7B20`, `0x008B7ED0`, `0x008B84A0`, `0x008B84F0`, `0x008B8940`, `0x008B9A50`, `0x008B9F10`, `0x008BB4B0`, `0x008BBB00`, `0x008BBCF0`, `0x008BBFC0`, `0x008BC6E0`, `0x008BCBB0`, `0x008BCF70`, `0x008BCFD0`, `0x008BD270`, `0x008BD2A0`, `0x008BD400`, `0x008BD7A0`, `0x008BDC70`, `0x008BDE80`, `0x008BE180`, `0x008BE340`, `0x008BE6F0`, `0x008BEBD0`, `0x008BF660`, `0x008BFBE0`, `0x008C0560`, `0x008C0C80`, `0x008C0E10`, `0x008C1040`, `0x008C1C30`, `0x008C3480`, `0x008C3DE0`, `0x008C4630`, `0x008C4AB0`, `0x008C4BD0`, `0x008C5000`, `0x008C50F0`, `0x008C5860`, `0x008C6B70`, `0x008C6C60`, `0x008C7020`, `0x008C72C0`, `0x008C74B0`, `0x008C7780`, `0x008C8360`, `0x008C85B0`, `0x008C8660`, `0x008C8830`, `0x008C8910`, `0x008C9290`, `0x008CA140`, `0x008CAA90`, `0x008CB190`, `0x008CBBB0`, `0x008CDA50`, `0x008CDF20`, `0x008CE7B0`, `0x008CE980`, `0x008CEC00`, `0x008CF440`, `0x008D00E0`, `0x008D0230`, `0x008D0720`, `0x008D0820`, `0x008D1120`, `0x008D1370`, `0x008D17B0`, `0x008D1C40`, `0x008D24D0`, `0x008D2700`, `0x008D3C40`, `0x008D3D20`, `0x008D3F30`, `0x008D68C0`, `0x008D7300`, `0x008D7AF0`, `0x008D8440`, `0x008D87C0`, `0x008D8A80`, `0x008D8FB0`, `0x008DA630`, `0x008DDD10`, `0x008DE1F0`, `0x008DE270`, `0x008DE460`, `0x008DEB70`, `0x008DEF10`, `0x008DEFE0`, `0x008DF130`, `0x008DF520`, `0x008DFEF0`, `0x008E0680`, `0x008E1D00`, `0x008E25F0`, `0x008E2730`, `0x008E3150`, `0x008E3720`, `0x008E3D40`, `0x008E4790`, `0x008E5420`, `0x008E5DF0`, `0x008E88E0`, `0x008E8A70`, `0x008E8B80`, `0x008E8DC0`, `0x008E9590`, `0x008E97E0`, `0x008E9C10`, `0x008EA9D0`, `0x008EB100`, `0x008EC6E0`, `0x008ED400`, `0x008EFAF0`, `0x008EFED0`, `0x008F0410`, `0x008F0520`, `0x008F19F0`, `0x008F2C00`, `0x008F49E0`, `0x008F52C0`, `0x008F5D10`, `0x008F6B60`, `0x008F9680`, `0x008FB500`, `0x008FBBE0`, `0x008FC7C0`, `0x008FF030`, `0x008FF910`, `0x008FFB10`, `0x00900A20`, `0x00903E80`, `0x00903FA0`, `0x00904500`, `0x00904600`, `0x00904D00`, `0x00904E10`, `0x00904FB0`, `0x009050C0`, `0x009054B0`, `0x00906720`, `0x009091F0`, `0x0090AA52`, `0x0090AD00`, `0x0090AE10`, `0x0090B080`, `0x0090B440`, `0x0090B930`, `0x0090BA40`, `0x0090C160`, `0x0090E9A0`, `0x0090FF30`, `0x00911340`, `0x00911CC0`, `0x00912050`, `0x00915810`, `0x00915E60`, `0x009187F0`, `0x00918FF0`, `0x009199A0`, `0x0091BF30`, `0x0092CD10`, `0x0092CD70`, `0x0092D8F0`, `0x009337E0`, `0x00933EA0`, `0x00934380`, `0x00934A60`, `0x00935090`, `0x0093C7C0`, `0x0093FC00`, `0x009406E0`, `0x009409A0`, `0x0094CB60`, `0x00951DD0`, `0x00958FB0`, `0x0095A240`, `0x0095DB20`, `0x0095DCB0`, `0x0095E470`, `0x0096E230`, `0x009701D0`, `0x00974500`, `0x0097D350`, `0x0097E9A0`, `0x0097EDB0`, `0x0097FCB0`, `0x0097FE80`, `0x0097FEC0`, `0x00988AD0`, `0x00989750`, `0x00991D60`, `0x00995D40`, `0x00996500`, `0x00996970`, `0x009990E0`, `0x0099B980`, `0x0099E320`, `0x0099E4E0`, `0x0099EC20`, `0x009A67E0`, `0x009AFFB0`, `0x009B3AD0`, `0x009B7FD0`, `0x009B9C70`, `0x00A23BC0`, `0x00A27FA0`, `0x00A2D810`, `0x00A2E2E0`, `0x00A2F7F0`, `0x00A8EBF0`, `0x00AEB500`, `0x00AFBFF0`, `0x00B45370`, `0x00B8D410`, `0x00B8D6D0`, `0x00B8E570`, `0x00B8FF40`, `0x00B901F0`, `0x00B90530`, `0x00B90770`, `0x00B90970`, `0x00B90D80`, `0x00B90EA0`, `0x00B91210`, `0x00B91730`, `0x00B921E0`, `0x00B92350`, `0x00B92A20`, `0x00B92CE0`, `0x00B93260`, `0x00B93520`, `0x00B93620`, `0x00B94120`, `0x00B94790`, `0x00B94D30`, `0x00B96480`, `0x00B96710`, `0x00B96D50`, `0x00B96ED0`, `0x00B97600`, `0x00B97EF0`, `0x00B986C0`, `0x00B98F30`, `0x00B991A0`, `0x00B997E0`, `0x00B99900`, `0x00B9A2C0`, `0x00B9A980`, `0x00B9AEC0`, `0x00B9B7D0`, `0x00B9C7E0`, `0x00B9CC00`, `0x00B9CD60`. The raw xref file lists every observed instruction, distinguishes reads and writes, and records each five-byte E9 step to the final target. The writer-context file gives larger initialization and destruction windows. This census is restricted to raw absolute-address references decoded within repository function extents; an indirect access through an escaped pointer is not asserted absent.

## Competing spellings

The counts describe matching explicit game declarations or definitions in the strict original-declaration inventory; comments and same-named statics can require manual interpretation and the counts do not decide identity.

| Decorated spelling | Game files declaring it |
|---|---:|
| `?Control0040F780@@3PAUMovieControl0040F780@@A` | 2 |
| `?TheBfmeManagerZE@@3PAVBfmeManagerZE@@A` | 0 |
| `?TheRva0045EF90Registry@@3PAVRva0045EF90Registry@@A` | 0 |
| `?TheWindowManager@@3PAVBfmeEstablishWindowManager@@A` | 0 |
| `?TheWindowManager@@3PAVBfmeGameWindowManager@@A` | 0 |
| `?TheWindowManager@@3PAVBfmeWindowManager@@A` | 1 |
| `?TheWindowManager@@3PAVGameWindowManager@@A` | 154 |
| `?TheWindowManager@@3PAVRva004C1040WindowManager@@A` | 0 |
| `?TheWindowManager@@3PAVRva004EC6E0WindowManager@@A` | 0 |
| `?TheWindowManager@@3PAVRva004ED400WindowManager@@A` | 0 |
| `?TheWindowManager@@3PAVRva004FC7C0WindowManager@@A` | 1 |
| `?TheWindowManager@@3PAVWindowManager@@A` | 0 |
| `?g_bfmeClock977@@3PAVBfmeClock977@@A` | 0 |
| `?g_bfmeClock983@@3PAVBfmeClock983@@A` | 0 |
| `?g_bfmeN1020@@3PAVBfmeN1020@@A` | 1 |
| `?g_bfmeN1021@@3PAVBfmeN1021@@A` | 1 |
| `?g_bfmeN1022@@3PAVBfmeN1022@@A` | 0 |
| `?g_bfmeObjEGD@@3PAVBfmeObjEGD@@A` | 0 |
| `?g_bfmeThreeAOA@@3PAVBfmeThreeAOA@@A` | 1 |
| `?g_bfmeWindowManagerAR@@3PAVBfmeWindowManagerAR@@A` | 0 |
| `?g_bfmeWindowManagerERC@@3PAVBfmeWindowManagerERC@@A` | 0 |

## Refutation and raw evidence

A writer publishing a different subsystem, a consumer requiring another object instead of the witnessed partial view, a mismatched reference contract, an interior datum boundary, a different ILT destination or any changed verified instruction would refute this correction. The retail factory outputs and singleton naming strings are independently re-checkable at the addresses above.

Raw logs: `build/rlink/pointer-globals-20261005/012f1b40-retail-xrefs.log`, `012f1b40-writer-context.log`, `inventory.log`, `strict-original-declarations.log`, `strict-original-declarations.log`, `global-type-pins.log`, `selected-constructor-rows.log`, `zh-global-declarations.log` and `zh-global-uses.log`. Source gates, data gates, declaration checks and before/after LINKED measurements are retained beside them and indexed in `check-receipts.jsonl` and `build/worker-final.md`.
