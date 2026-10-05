# TheInGameUI at VA 0x012F148C

## Result and retail extent

This datum is one zero-initialized four-byte `InGameUI *TheInGameUI` in retail `.data`. Its initial bytes are `00 00 00 00` in the section's virtual-only tail, so it holds null and no initialized pointer relocation needs following. The image has no base-relocation directory. Raw word accesses prove the pointer width. No data row overlaps this word and no DIR32 symbol starts strictly inside its extent. The canonical spelling is already in `dir32_addresses.csv` and the competing rows are retained; adding a duplicate row would be redundant. One definition is backed by `tools/add_data_match.py` in `game/GameEngine/Source/GameClient/InGameUI.cpp`.

## Retail facts and reference

GameClient initialization at VA 0082F5A0 calls its factory at vtable offset 0x88 and stores the result at 0082FD40. The subsequent naming path uses TheInGameUI at 010F36F4. The destructor at 00831380 deletes and clears the same pointer at 00831460. InGameUI selection, input, movie and spell-store consumers read that same word. The existing typed singleton pin and the EA string agree with the Zero Hour InGameUI class and singleton. Movie and spell views are access views of this object, not separate globals.

Reference location: `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/InGameUI.cpp:106`. Existing names alone do not decide the pointee; the EA strings, initialization, typed consumer operations and reference contract above do.

## Receiver and argument contract

The word holds an object pointer. Retail loads it into ECX for thiscall members or reads its vptr for virtual dispatch. Each local partial view retains its original method signatures, offsets and arguments behind a cast at its use. The global declaration uses the one canonical pointee type. Null assignment writes the canonical pointer directly. No inheritance, wrapper, forwarding function or linker alias is introduced. All existing verified function bytes must remain identical.

## Readers and writers

Decoded retail bodies referencing this address: `0x00465470`, `0x0046B910`, `0x004C4740`, `0x004C9A20`, `0x004D5160`, `0x004D7680`, `0x004DFCD0`, `0x004FEBE0`, `0x005083D0`, `0x0050AF70`, `0x00510170`, `0x005104E4`, `0x005112D0`, `0x005C98C0`, `0x005CEAD0`, `0x005CEFC0`, `0x005D1020`, `0x005D4530`, `0x005EEDE0`, `0x005FCA90`, `0x0060BAE0`, `0x0060E580`, `0x00617730`, `0x00618200`, `0x00618E70`, `0x00618EE0`, `0x0062A860`, `0x0062AC00`, `0x00649140`, `0x0064BA90`, `0x0064ED40`, `0x00655BE0`, `0x00658800`, `0x00667B10`, `0x00668F30`, `0x006693E0`, `0x00669600`, `0x0066A1A0`, `0x00680EE0`, `0x006810B0`, `0x00686440`, `0x0069E330`, `0x006AB690`, `0x006AC620`, `0x006B0D40`, `0x006B6350`, `0x006B8FF0`, `0x006B9970`, `0x006BA240`, `0x006BAC00`, `0x006CF2C0`, `0x006EE6E0`, `0x006EE860`, `0x006EF010`, `0x006EF090`, `0x006EF6A0`, `0x006EF770`, `0x006EF790`, `0x006EF7B0`, `0x006EF7F0`, `0x006EF9B0`, `0x006EF9D0`, `0x006F0FD0`, `0x006F10F0`, `0x006F3BA0`, `0x006F9660`, `0x006F9790`, `0x006F9870`, `0x006F99A0`, `0x006FAF10`, `0x00703BF0`, `0x0072B730`, `0x00748430`, `0x0075F920`, `0x00782E30`, `0x00782F50`, `0x00783490`, `0x007839E0`, `0x00794260`, `0x00796B00`, `0x00796D40`, `0x00797350`, `0x00797540`, `0x007BC1E0`, `0x007BDB80`, `0x007C3850`, `0x00811CD0`, `0x00811F80`, `0x00814BE0`, `0x00814E40`, `0x00818880`, `0x0081CA50`, `0x0081FDF0`, `0x00820150`, `0x0082B370`, `0x0082B3D0`, `0x0082F5A0`, `0x00831110`, `0x00831380`, `0x00831900`, `0x008329D0`, `0x0083AAA0`, `0x0083BAE0`, `0x0083E0F0`, `0x0083E420`, `0x0083EC00`, `0x0083EC30`, `0x0083ED60`, `0x0083EE20`, `0x0083EF70`, `0x0083F950`, `0x008431B0`, `0x00843270`, `0x00843F60`, `0x008445C0`, `0x00846550`, `0x00847A40`, `0x00847F10`, `0x00848700`, `0x0084A2E0`, `0x00858FC0`, `0x00859060`, `0x008590D0`, `0x00859140`, `0x00859200`, `0x00878F60`, `0x0088E480`, `0x0089CB90`, `0x0089CBB0`, `0x0089DC90`, `0x0089DD20`, `0x0089E5A0`, `0x0089E780`, `0x0089F8B0`, `0x0089FC90`, `0x008A2500`, `0x008A37E0`, `0x008A4240`, `0x008A6570`, `0x008A6E20`, `0x008A9010`, `0x008A9300`, `0x008A9620`, `0x008AF3D0`, `0x008BC8A0`, `0x008BCCE0`, `0x008BFFE0`, `0x008C0560`, `0x008C15D0`, `0x008C1C30`, `0x008C3350`, `0x008C3DE0`, `0x008C4630`, `0x008C48C0`, `0x008C5060`, `0x008C50F0`, `0x008E4790`, `0x008EB2A0`, `0x008F6B60`, `0x00906720`, `0x0090E5A0`, `0x0090E9A0`, `0x00911CC0`, `0x0092B2A0`, `0x0092BEC0`, `0x009695A0`, `0x00969720`, `0x009699B0`, `0x00969E10`, `0x0096D070`, `0x00989940`, `0x0098E220`, `0x00994740`, `0x00994D60`, `0x00995230`, `0x00996D40`, `0x00999330`, `0x00999490`, `0x009A7E20`, `0x009A8850`, `0x009A8A10`, `0x009A9C90`, `0x009ACBB0`, `0x009ACD40`, `0x009ACF80`, `0x009AD330`, `0x009AD4C0`, `0x009AD660`, `0x009AD9C0`, `0x009ADA90`, `0x009ADB50`, `0x009ADC10`, `0x009ADE90`, `0x009AFFB0`, `0x009B1610`, `0x009B17E0`, `0x009B18C0`, `0x009B1A80`, `0x009B1C70`, `0x009B22B0`, `0x009B3AD0`, `0x009B4D40`, `0x009B51D0`, `0x009B52B0`, `0x009B5590`, `0x009B5E50`, `0x009B7370`, `0x009B7390`, `0x009B7690`, `0x009B8230`, `0x009B8520`, `0x009B9C70`, `0x00A03520`, `0x00A03640`, `0x00A091B0`, `0x00A0F220`, `0x00A12070`, `0x00A12160`, `0x00A13D60`, `0x00A15900`, `0x00A25570`, `0x00A66300`, `0x00A67060`, `0x00AEB500`, `0x00AF0300`, `0x00AF2CC0`, `0x00B00820`, `0x00B00A40`, `0x00B3BB10`, `0x00B3E050`, `0x00B446A0`, `0x00B46A30`, `0x00B99D00`, `0x00B99DC0`, `0x00BACBD0`. The raw xref file lists every observed instruction, distinguishes reads and writes, and records each five-byte E9 step to the final target. The writer-context file gives larger initialization and destruction windows. This census is restricted to raw absolute-address references decoded within repository function extents; an indirect access through an escaped pointer is not asserted absent.

## Competing spellings

The counts describe matching explicit game declarations or definitions in the strict original-declaration inventory; comments and same-named statics can require manual interpretation and the counts do not decide identity.

| Decorated spelling | Game files declaring it |
|---|---:|
| `?TheInGameUI@@3PAUInGameUI@@A` | 1 |
| `?TheInGameUI@@3PAVBfmeInGameUI@@A` | 0 |
| `?TheInGameUI@@3PAVDesyncInGameUI@@A` | 0 |
| `?TheInGameUI@@3PAVInGameUI@@A` | 131 |
| `?TheInGameUI@@3PAVInGameUISpellStoreView@@A` | 0 |
| `?TheInGameUI@@3PAVRva00506720UI@@A` | 2 |
| `?TheInGameUI@@3PAVRva00615900InGameUI@@A` | 0 |
| `?TheMovieSourceShim@@3PAVMovieSourceShim@@A` | 1 |
| `?TheOpen24590D0Source@@3PAVOpen24590D0Source@@A` | 0 |
| `?g_Va012F148C@@3PAVVDispatch@@A` | 0 |
| `?g_bfme1254@@3PAVBfmeR1254@@A` | 0 |
| `?g_bfme1256@@3PAVBfmeR1256@@A` | 0 |
| `?g_bfmeA1095@@3PAVBfmeA1095@@A` | 1 |
| `?g_bfmeGlobJB@@3PAVBfmeGlobJB@@A` | 0 |
| `?g_bfmeHub993@@3PAVBfmeHub993@@A` | 0 |
| `?g_bfmeObj2EGE@@3PAVBfmeObj2EGE@@A` | 0 |
| `?g_bfmeRva9140GlobalC@@3PAVBfmeRva9140GlobalC@@A` | 0 |
| `?g_bfmeRvaBA90GlobalC@@3PAVBfmeRvaBA90GlobalC@@A` | 1 |
| `?g_bfmeSinkBL@@3PAVBfmeSinkBL@@A` | 0 |
| `?g_bfmeSinkBM@@3PAVBfmeSinkBM@@A` | 0 |
| `?g_mgr12F148C@@3PAVBfmeMgrF14@@A` | 1 |

## Refutation and raw evidence

A writer publishing a different subsystem, a consumer requiring another object instead of the witnessed partial view, a mismatched reference contract, an interior datum boundary, a different ILT destination or any changed verified instruction would refute this correction. The retail factory outputs and singleton naming strings are independently re-checkable at the addresses above.

Raw logs: `build/rlink/pointer-globals-20261005/012f148c-retail-xrefs.log`, `012f148c-writer-context.log`, `inventory.log`, `strict-original-declarations.log`, `strict-original-declarations.log`, `global-type-pins.log`, `selected-constructor-rows.log`, `zh-global-declarations.log` and `zh-global-uses.log`. Source gates, data gates, declaration checks and before/after LINKED measurements are retained beside them and indexed in `check-receipts.jsonl` and `build/worker-final.md`.
