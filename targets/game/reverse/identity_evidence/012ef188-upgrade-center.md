# TheUpgradeCenter at VA 0x012EF188

Corrected. The datum is one mutable `UpgradeCenter *`, four bytes, initially zero in the virtual zero-filled tail of retail `.data`. No other DIR32 address lies inside these four bytes. The initial image has no relocation in this cell; the unpacked PE base-relocation directory is absent. The final range probe reports the newly added data row as the sole overlap. This is runtime singleton storage, not a compiler constant or a name table.

Upgrade parsing and named upgrade lookups load the pointer as their UpgradeCenter receiver. GameEngine initialization supplies the cell address for subsystem registration. The BfmeConv1095 consumer performs a thiscall on the loaded pointer, rather than reading an integer.

The Zero Hour reference defines `UpgradeCenter *TheUpgradeCenter = NULL` in `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/System/Upgrade.cpp`. The exact reference declaration is retained in `build/rlink/zh-global-definitions.log`. This reference type, the retail receiver uses, and the existing DIR32 spelling `?TheUpgradeCenter@@3PAVUpgradeCenter@@A` agree. They establish the identity independently of the number of declarations.

BfmeConv1095.cpp now declares UpgradeCenter *TheUpgradeCenter and casts that receiver to its existing partial layout for the existing call. The existing definition stays in Upgrade.cpp. The data row is additive. The chosen spelling already exists in DIR32 and is retained, along with competing historical spellings. No existing symbol pin, function ledger row, function ABI or verified instruction is changed. No shared header is edited.

Raw retail facts are in `build/rlink/012ef188-retail.log` and `build/rlink/012ef188-bodies.log`, including all direct absolute reference sites and complete containing bodies. Every direct call route is read from its five-byte E9 entries until its final target. Range bytes and interior-name checks are in `build/rlink/ranges-and-cloud-tables-final.log`. The complete declaration census is `build/rlink/declaration-counts-final-verified.log`; counts below describe direct declarations in the initial working tree, including headers and definitions, not uses inherited through includes.

| Existing spelling | Game files declaring it |
|---|---:|
| `?TheUpgradeCenter@@3PAVBfmeThingND@@A` | 0 |
| `?TheUpgradeCenter@@3PAVUpgradeCenter@@A` | 36 |
| `?TheUpgradeCenter@@3PAXA` | 0 |
| `?g_bfmeQ1095@@3PAVBfmeQ1095A@@A` | 1 |
| `?g_bfmeSinkBMD@@3PAVBfmeSinkBMD@@A` | 0 |

A consumer requiring a different receiver contract, a factory result that is not `UpgradeCenter`, an integer interpretation of this cell, nonzero initial bytes, a competing storage object inside the four-byte range, or a byte mismatch after the declaration change would refute this correction. A class layout in a partial consumer does not by itself establish a second identity for the singleton.
