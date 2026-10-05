# TheDisplay at VA 0x012F1270

Corrected. The datum is one mutable `Display *`, four bytes, initially zero in the virtual zero-filled tail of retail `.data`. No other DIR32 address lies inside these four bytes. The initial image has no relocation in this cell; the unpacked PE base-relocation directory is absent. The final range probe reports the newly added data row as the sole overlap. This is runtime singleton storage, not a compiler constant or a name table.

GameClient stores its created display receiver at this address and clears it during teardown. Named width, height, draw and display-update consumers load this pointer and use the Display contract.

The Zero Hour reference defines `Display *TheDisplay = NULL` in `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameClient/Display.cpp`. The exact reference declaration is retained in `build/rlink/zh-global-definitions.log`. This reference type, the retail receiver uses, and the existing DIR32 spelling `?TheDisplay@@3PAVDisplay@@A` agree. They establish the identity independently of the number of declarations.

ClientUpdate004329D0.cpp now declares Display *TheDisplay and retains its existing partial-layout casts. The existing definition stays in Display.cpp. The data row is additive. The chosen spelling already exists in DIR32 and is retained, along with competing historical spellings. No existing symbol pin, function ledger row, function ABI or verified instruction is changed. No shared header is edited.

Raw retail facts are in `build/rlink/012f1270-retail.log` and `build/rlink/012f1270-bodies.log`, including all direct absolute reference sites and complete containing bodies. Every direct call route is read from its five-byte E9 entries until its final target. Range bytes and interior-name checks are in `build/rlink/ranges-and-cloud-tables-final.log`. The complete declaration census is `build/rlink/declaration-counts-final-verified.log`; counts below describe direct declarations in the initial working tree, including headers and definitions, not uses inherited through includes.

| Existing spelling | Game files declaring it |
|---|---:|
| `?Rva00367810TheVirtualGate@@3PAVRva00367810VirtualGate@@A` | 1 |
| `?ShaderDisplay@@3PAVDisplay@@A` | 0 |
| `?TheBfmeDisplayXL@@3PAVBfmeDisplayXL@@A` | 0 |
| `?TheBfmeDisplayXW@@3PAVBfmeDisplayXW@@A` | 0 |
| `?TheDisplay@@3PAVBFMERetailDisplayVTable@@A` | 0 |
| `?TheDisplay@@3PAVBfmeDisplay@@A` | 0 |
| `?TheDisplay@@3PAVBfmeStrVM0@@A` | 0 |
| `?TheDisplay@@3PAVBfmeThingVMZ@@A` | 0 |
| `?TheDisplay@@3PAVDisplay@@A` | 133 |
| `?TheDisplay@@3PAVRva00491DB0Display@@A` | 0 |
| `?TheDisplay@@3PAVRva004ED400Display@@A` | 0 |
| `?TheDisplay@@3PAVRva004FC7C0Display@@A` | 0 |
| `?TheDisplay@@3PAXA` | 0 |
| `?TheDisplay@@3QAVDisplay@@A` | 0 |
| `?TheDisplayShim@@3PAVDisplayShim@@A` | 0 |
| `?g_Va012F1270@@3PAVVDispatch@@A` | 0 |
| `?g_bfmeA1019@@3PAVBfmeA1019@@A` | 0 |
| `?g_bfmeA1020@@3PAVBfmeA1020@@A` | 0 |
| `?g_bfmeC1082@@3PAVBfmeC1082@@A` | 0 |
| `?g_bfmeObjFGA@@3PAUBfmeGlobFGA@@A` | 0 |
| `?g_bfmeRegistryCC@@3PAVBfmeRegistryCC@@A` | 0 |

A consumer requiring a different receiver contract, a factory result that is not `Display`, an integer interpretation of this cell, nonzero initial bytes, a competing storage object inside the four-byte range, or a byte mismatch after the declaration change would refute this correction. A class layout in a partial consumer does not by itself establish a second identity for the singleton.
