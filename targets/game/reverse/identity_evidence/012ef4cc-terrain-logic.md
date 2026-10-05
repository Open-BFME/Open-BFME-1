# TheTerrainLogic at VA 0x012EF4CC

Corrected. The datum is one mutable `TerrainLogic *`, four bytes, initially zero in the virtual zero-filled tail of retail `.data`. No other DIR32 address lies inside these four bytes. The initial image has no relocation in this cell; the unpacked PE base-relocation directory is absent. The final range probe reports the newly added data row as the sole overlap. This is runtime singleton storage, not a compiler constant or a name table.

GameLogic stores the createTerrainLogic result in this cell and clears it on teardown. Named ground-height, waypoint, terrain state and virtual terrain consumers load the same pointer. These contracts match the Zero Hour TerrainLogic singleton.

The Zero Hour reference defines `TerrainLogic *TheTerrainLogic = NULL` in `inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Map/TerrainLogic.cpp`. The exact reference declaration is retained in `build/rlink/zh-global-definitions.log`. This reference type, the retail receiver uses, and the existing DIR32 spelling `?TheTerrainLogic@@3PAVTerrainLogic@@A` agree. They establish the identity independently of the number of declarations.

GameLogic.cpp, FlameStep00294410.cpp and Rva0077B3F0.cpp now declare TerrainLogic *TheTerrainLogic. Their partial-layout accesses use casts. The existing definition stays in TerrainLogic.cpp. The data row is additive. The chosen spelling already exists in DIR32 and is retained, along with competing historical spellings. No existing symbol pin, function ledger row, function ABI or verified instruction is changed. No shared header is edited.

Raw retail facts are in `build/rlink/012ef4cc-retail.log` and `build/rlink/012ef4cc-bodies.log`, including all direct absolute reference sites and complete containing bodies. Every direct call route is read from its five-byte E9 entries until its final target. Range bytes and interior-name checks are in `build/rlink/ranges-and-cloud-tables-final.log`. The complete declaration census is `build/rlink/declaration-counts-final-verified.log`; counts below describe direct declarations in the initial working tree, including headers and definitions, not uses inherited through includes.

| Existing spelling | Game files declaring it |
|---|---:|
| `?Rva012ef4cc@@3PAVRva0041D290Client@@A` | 0 |
| `?TheBfmeImpl_002EFC30@@3PAUGen_002EFC30Impl@@A` | 0 |
| `?TheTerrainLogic@@3PAURva003FD060TerrainLogic@@A` | 0 |
| `?TheTerrainLogic@@3PAVBFMETerrainLogic@@A` | 0 |
| `?TheTerrainLogic@@3PAVBfmeMoveHintTerrainLogic@@A` | 0 |
| `?TheTerrainLogic@@3PAVRva001A1DF0TerrainLogic@@A` | 0 |
| `?TheTerrainLogic@@3PAVRva002113A0Terrain@@A` | 0 |
| `?TheTerrainLogic@@3PAVRva002B7C80TerrainLogicPre@@A` | 0 |
| `?TheTerrainLogic@@3PAVRva002C96D0TerrainLogicPre@@A` | 0 |
| `?TheTerrainLogic@@3PAVRva003FD060TerrainLogic@@A` | 0 |
| `?TheTerrainLogic@@3PAVRva012EF4CCTerrain@@A` | 0 |
| `?TheTerrainLogic@@3PAVTerrain208A50@@A` | 0 |
| `?TheTerrainLogic@@3PAVTerrainLogic@@A` | 211 |
| `?TheTerrainLogic@@3PAVTerrainLogicByValue@@A` | 0 |
| `?TheTerrainLogic@@3PAVTerrainLogicP48Owner@@A` | 0 |
| `?TheTerrainLogic@@3PAVTerrainLogic_259CD0@@A` | 0 |
| `?TheTerrainLogic@@3PAXA` | 0 |
| `?g002705D0Va012EF4CC@@3PAVMelee002705D0Terrain@@A` | 0 |
| `?g012EF4CC@@3PAURva0038DA10Terrain@@A` | 1 |
| `?g_bfme1263@@3PAVBfmeR1263@@A` | 0 |
| `?g_bfme1268@@3PAVBfmeR1268@@A` | 0 |
| `?g_bfmeHolderBS@@3PAVBfmeHolderBS@@A` | 0 |
| `?g_bfmeTerrainGJ@@3PAVBfmeTerrainGJ@@A` | 0 |
| `?g_rva001077D0TerrainLogic@@3PAVRva001077D0TerrainLogic@@A` | 0 |
| `?g_terrain00294410@@3PAVTerrain00294410@@A` | 1 |
| `?g_va012EF4CC@@3PAVRva0077B3F0Terrain@@A` | 1 |

A consumer requiring a different receiver contract, a factory result that is not `TerrainLogic`, an integer interpretation of this cell, nonzero initial bytes, a competing storage object inside the four-byte range, or a byte mismatch after the declaration change would refute this correction. A class layout in a partial consumer does not by itself establish a second identity for the singleton.
