# TheControlBar at VA 0x012F33F8

## Result and retail extent

This datum is one zero-initialized four-byte `ControlBar *TheControlBar` in retail `.data`. Its initial bytes are `00 00 00 00` in the section's virtual-only tail, so it holds null and no initialized pointer relocation needs following. The image has no base-relocation directory. Raw word accesses prove the pointer width. No data row overlaps this word and no DIR32 symbol starts strictly inside its extent. The canonical spelling is already in `dir32_addresses.csv` and the competing rows are retained; adding a duplicate row would be redundant. One definition is backed by `tools/add_data_match.py` in `game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp`.

## Retail facts and reference

InGameUI::createReplayControl at VA 00840B40 stores a newly constructed object at 00840E9F; InGameUI::createControlBar at 00842370 stores a newly constructed object at 008423F2. InGameUI destructor clears the same slot at 0084AEC1. ControlBar init, science and command-button consumers act on that singleton. The existing ControlBar typed pin, the reference singleton declaration and these consumers establish the ControlBar role. BfmeMgr and command-manager spellings are local partial views of this same object.

Reference location: `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBar.cpp:93`. Existing names alone do not decide the pointee; the EA strings, initialization, typed consumer operations and reference contract above do.

## Receiver and argument contract

The word holds an object pointer. Retail loads it into ECX for thiscall members or reads its vptr for virtual dispatch. Each local partial view retains its original method signatures, offsets and arguments behind a cast at its use. The global declaration uses the one canonical pointee type. Null assignment writes the canonical pointer directly. No inheritance, wrapper, forwarding function or linker alias is introduced. All existing verified function bytes must remain identical.

## Readers and writers

Decoded retail bodies referencing this address: `0x004B7F80`, `0x004B8070`, `0x004C6820`, `0x004C9600`, `0x004C9960`, `0x004D5380`, `0x004D5F30`, `0x004D7E30`, `0x004DF860`, `0x004DF8A0`, `0x004DFCD0`, `0x004FDBF0`, `0x00508A60`, `0x00543580`, `0x00551430`, `0x005636D0`, `0x00587860`, `0x005C4710`, `0x005C4780`, `0x005C4A30`, `0x005D21F0`, `0x005D2810`, `0x005EDC00`, `0x005EDCA0`, `0x0060D310`, `0x0060E580`, `0x0062A860`, `0x006489E0`, `0x0066C9E0`, `0x0067A2F0`, `0x0067A380`, `0x0067DF90`, `0x0068ADA0`, `0x0068B360`, `0x0069E330`, `0x006A1F80`, `0x006A32D0`, `0x006AC440`, `0x006AD380`, `0x006D4120`, `0x006D4310`, `0x006D4470`, `0x006D9510`, `0x006D9570`, `0x006EE720`, `0x006EF010`, `0x006F0740`, `0x006F4A20`, `0x006F4AB0`, `0x006F4B60`, `0x006F54C0`, `0x006F6D70`, `0x006F6EB0`, `0x006F7B80`, `0x006F9DA0`, `0x006F9E40`, `0x006F9F10`, `0x006F9FF0`, `0x006FA2D0`, `0x006FA4E0`, `0x006FA7C0`, `0x006FA9B0`, `0x006FB170`, `0x006FB4F0`, `0x006FB8D0`, `0x006FBC90`, `0x006FC050`, `0x006FC570`, `0x006FDCD0`, `0x006FE110`, `0x006FF770`, `0x006FFB60`, `0x00722E80`, `0x00725150`, `0x00791C40`, `0x00794260`, `0x00796950`, `0x00796B00`, `0x00796D40`, `0x00797350`, `0x00797540`, `0x007BF190`, `0x00840B40`, `0x008410C0`, `0x00842300`, `0x008445C0`, `0x008462D0`, `0x00846490`, `0x00847F10`, `0x0084AE70`, `0x0084B3F0`, `0x0089C4B0`, `0x0089C7C0`, `0x0089CA90`, `0x008A04C0`, `0x008A09D0`, `0x008A2150`, `0x008A4240`, `0x008A5E30`, `0x008AA690`, `0x008ABA80`, `0x008AE080`, `0x008AEE00`, `0x008AF6A0`, `0x008BCCE0`, `0x008C0560`, `0x008C0C80`, `0x008C0E10`, `0x008C1040`, `0x008C1990`, `0x008C48C0`, `0x008C4920`, `0x00983680`, `0x00988AD0`, `0x00988C70`, `0x00988CA0`, `0x00989700`, `0x0098BB30`, `0x0098BC20`, `0x0098BCD0`, `0x0098BD70`, `0x0098BFE0`, `0x0098C050`, `0x0098C100`, `0x0098C1A0`, `0x0098D000`, `0x0098D820`, `0x0098D990`, `0x0098DA50`, `0x0098ECA0`, `0x0098EDB0`, `0x0098EED0`, `0x00990480`, `0x009915E0`, `0x009917E0`, `0x00993310`, `0x00997130`, `0x00997A30`, `0x009996F0`, `0x0099B980`, `0x009A7E20`, `0x009A9C90`, `0x009ADE90`, `0x009AFFB0`, `0x00A091B0`, `0x00B99FA0`, `0x00B9CC00`, `0x00B9CD60`. The raw xref file lists every observed instruction, distinguishes reads and writes, and records each five-byte E9 step to the final target. The writer-context file gives larger initialization and destruction windows. This census is restricted to raw absolute-address references decoded within repository function extents; an indirect access through an escaped pointer is not asserted absent.

## Competing spellings

The counts describe matching explicit game declarations or definitions in the strict original-declaration inventory; comments and same-named statics can require manual interpretation and the counts do not decide identity.

| Decorated spelling | Game files declaring it |
|---|---:|
| `?TheControlBar@@3PAURva002AD380ControlBar@@A` | 1 |
| `?TheControlBar@@3PAVBfmeA993@@A` | 1 |
| `?TheControlBar@@3PAVBfmeMgr977@@A` | 0 |
| `?TheControlBar@@3PAVControlBar5@@A` | 1 |
| `?TheControlBar@@3PAVControlBar@@A` | 94 |
| `?TheControlBar@@3PAVRva004C1040ControlBar@@A` | 0 |
| `?g_bfmeDirtyAE@@3PAVBfmeDirtyAE@@A` | 0 |
| `?g_bfmeE1022@@3PAVBfmeE1022@@A` | 0 |
| `?g_bfmeGlobMB@@3PAVBfmeGlobMB@@A` | 1 |
| `?g_bfmeMgr977@@3PAVBfmeMgr977@@A` | 1 |
| `?g_bfmeObjEZF@@3PAVBfmeGlobEZF@@A` | 0 |
| `?g_bfmeRegistryYI@@3PAVBfmeRegistryYI@@A` | 0 |
| `?g_bfmeRegistryYT@@3PAVBfmeRegistryYT@@A` | 0 |
| `?g_bfmeRegistryYU@@3PAVBfmeRegistryYU@@A` | 0 |
| `?g_bfmeRegistryYV@@3PAVControlBar@@A` | 1 |
| `?g_bfmeSinkAAA@@3PAVBfmeSinkAAA@@A` | 0 |
| `?g_bfmeSinkAAB@@3PAVBfmeSinkAAB@@A` | 0 |
| `?g_bfmeStateUYA@@3PAUBfmeStateUYA@@A` | 0 |
| `?g_bfmeStateXC@@3PAVBfmeStateXC@@A` | 0 |
| `?g_bfmeWorldRV@@3PAUBfmeWorldRV@@A` | 0 |
| `?g_mgr12F33F8@@3PAVBfmeMgr33F@@A` | 0 |
| `?g_mgr12F33F8@@3PAVBfmeMgr412@@A` | 0 |
| `?g_rva0058C100CommandManager@@3PAVRva0058C100CommandManager@@A` | 0 |

## Refutation and raw evidence

A writer publishing a different subsystem, a consumer requiring another object instead of the witnessed partial view, a mismatched reference contract, an interior datum boundary, a different ILT destination or any changed verified instruction would refute this correction. The retail factory outputs and singleton naming strings are independently re-checkable at the addresses above.

Raw logs: `build/rlink/pointer-globals-20261005/012f33f8-retail-xrefs.log`, `012f33f8-writer-context.log`, `inventory.log`, `strict-original-declarations.log`, `strict-original-declarations.log`, `global-type-pins.log`, `selected-constructor-rows.log`, `zh-global-declarations.log` and `zh-global-uses.log`. Source gates, data gates, declaration checks and before/after LINKED measurements are retained beside them and indexed in `check-receipts.jsonl` and `build/worker-final.md`.
