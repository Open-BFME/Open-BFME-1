# TheSpecialPowerStore at VA 0x012ED80C

Corrected. The datum is one mutable `SpecialPowerStore *`, four bytes, initially zero in the virtual zero-filled tail of retail `.data`. No other DIR32 address lies inside these four bytes. The initial image has no relocation in this cell; the unpacked PE base-relocation directory is absent. The final range probe reports the newly added data row as the sole overlap. This is runtime singleton storage, not a compiler constant or a name table.

parseSpecialPowerDefinition and script special-power lookup bodies load this cell as the receiver for the SpecialPowerStore template lookup. GameEngine initialization passes the address of this singleton cell into subsystem registration.

The Zero Hour reference defines `SpecialPowerStore *TheSpecialPowerStore = NULL` in `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/RTS/SpecialPower.cpp`. The exact reference declaration is retained in `build/rlink/zh-global-definitions.log`. This reference type, the retail receiver uses, and the existing DIR32 spelling `?TheSpecialPowerStore@@3PAVSpecialPowerStore@@A` agree. They establish the identity independently of the number of declarations.

The one declaration using void * in ScriptActions_doTeamGiveTeamUpgrade.cpp now uses SpecialPowerStore *. The existing definition stays in SpecialPower.cpp. The data row is additive. The chosen spelling already exists in DIR32 and is retained, along with competing historical spellings. No existing symbol pin, function ledger row, function ABI or verified instruction is changed. No shared header is edited.

Raw retail facts are in `build/rlink/012ed80c-retail.log` and `build/rlink/012ed80c-bodies.log`, including all direct absolute reference sites and complete containing bodies. Every direct call route is read from its five-byte E9 entries until its final target. Range bytes and interior-name checks are in `build/rlink/ranges-and-cloud-tables-final.log`. The complete declaration census is `build/rlink/declaration-counts-final-verified.log`; counts below describe direct declarations in the initial working tree, including headers and definitions, not uses inherited through includes.

| Existing spelling | Game files declaring it |
|---|---:|
| `?TheSpecialPowerStore@@3PAVSpecialPowerStore@@A` | 15 |
| `?TheSpecialPowerStore@@3PAXA` | 1 |
| `?g_bfmeRegistryBH@@3PAVBfmeRegistryBH@@A` | 0 |

A consumer requiring a different receiver contract, a factory result that is not `SpecialPowerStore`, an integer interpretation of this cell, nonzero initial bytes, a competing storage object inside the four-byte range, or a byte mismatch after the declaration change would refute this correction. A class layout in a partial consumer does not by itself establish a second identity for the singleton.
