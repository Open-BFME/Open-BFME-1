# Datum identity at VA 0x012F9D28

The datum is `?g_bfmeTableDU@@3PAVBfmeHandleCX@@A` in `game/GameEngine/Source/Common/Rva00C6C520StaticInit.cpp`. An inline array of eight owning shader texture handles, not a pointer global and not a pointer to a table. Its element storage is BfmeHandleCX[8]; the role is the shader texture table. The existing role-bearing spelling remains.

Retail has a 32-byte extent in `.data`, initialized to `00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00`. The PE base-relocation directory is absent (RVA and size both zero), and the initial value contains no pointer relocation. The complete range has no overlapping data row and no other DIR32 name strictly inside it. Alternative spellings at the start are preserved additively in the DIR32 ledger.

RVA 0x00C6C520 passes address 0x012F9D28, element size 4 and count 8 to the compiler array constructor and registers cleanup 0x00C70A20. RVA 0x006D25E0 loads and stores [index*4+0x012F9D28], acquires the replacement by incrementing word +4 and releases the old handle. RVA 0x007C34A0 copies an indexed handle by value. Shader shutdown walks to end address 0x012F9D48. Publish at 0x00704AF0 updates element zero directly.

Zero Hour W3DShaderManager.h declares an eight-entry m_Textures array, but its raw TextureClass * type does not describe BFME owning-handle construction and destruction. The BfmeHandleCX array declaration and reference-counted local views are verified without inventing a Zero Hour type identity. Every byte over the 32-byte array is zero; no data row overlaps and no other DIR32 name starts inside it.

## Receiver and argument contract

For the texture table, the datum itself is the inline eight-element array; direct indexed accesses and constructor arguments establish the 4-byte element and 32-byte extent. Each element holds a 32-bit ref-counted texture pointer. The compiler array constructor takes the array address, element stride 4, count 8 and the existing element constructor/destructor addresses. Existing texture assignment and release calls keep their argument and receiver contracts through local views.

## Competing spellings before correction

| Decorated spelling | Game files declaring it |
|---|---:|
| `?TheOpen2PublishedTexture@@3PAVTextureBaseClass@@A` | 1 |
| `?g_bfme5TextureSlots@@3PAPAVTextureClass@@A` | 0 |
| `?g_bfmeTableDU@@3PAVBfmeHandleCX@@A` | 6 |
| `?g_bfmeTableDU@@3PAVTextureHandle@@A` | 1 |
| `?rva012F9D28@@3PAVShaderTextureHandle@@A` | 0 |

Macro-generated S4 declarations and the terrain-track guarded-call declaration are counted in their owning source. The raw contract log lists each counted path; counts decide no identity.

## Retail reads and writes

Readers:

- `?Install_Materials@W3DShroudMaterialPassClass@@UBEXXZ` at RVA `0x0071A680` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShroudMaterialPassClass_Install_Materials.cpp)
- `?bfme5SetTextureSlot@@YAXHPAPAVTextureClass@@@Z` at RVA `0x006D25E0` (game/GameEngine/Source/Common/Bfme5ReadyQueue.cpp)
- `?bfmeGet@@YA?AVBfmeHandleCX@@H@Z` at RVA `0x007C34A0` (game/GameEngine/Source/Common/Bfme5FiftyOne.cpp)
- `?d_006da2d0@@YAXXZ` at RVA `0x006DA2D0` (game/gen_asm/d_006d2000.asm)
- `?d_007a8400@@YAXXZ` at RVA `0x007A8400` (game/gen_asm/d_00776ac0.asm)
- `?d_007a8ff0@@YAXXZ` at RVA `0x007A8FF0` (game/gen_asm/d_00776ac0.asm)
- `?drawRoads@W3DRoadBuffer@@QAEXPAVCameraClass@@ABVTextureHandle@@1_NHHHHPAV?$RefMultiListIterator@VRenderObjClass@@@@@Z` at RVA `0x00710620` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DRoadBuffer_drawRoads.cpp)
- `?publish@Rva00704AF0@@QAEXXZ` at RVA `0x00704AF0` (game/GameEngine/Source/Common/Open2Conv004.cpp)
- `?releaseDependentResources@BfmeShaderShutdown@@SAXXZ` at RVA `0x00717C90` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManagerReleaseResources.cpp)
- `?drawSea@WaterRenderObjClass@@IAEXAAVRenderInfoClass@@@Z` at RVA `0x007A37B0` (game/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWater.cpp)

Writers:

- `?Install_Materials@W3DShroudMaterialPassClass@@UBEXXZ` at RVA `0x0071A680` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShroudMaterialPassClass_Install_Materials.cpp)
- `?bfme5SetTextureSlot@@YAXHPAPAVTextureClass@@@Z` at RVA `0x006D25E0` (game/GameEngine/Source/Common/Bfme5ReadyQueue.cpp)
- `?d_006da2d0@@YAXXZ` at RVA `0x006DA2D0` (game/gen_asm/d_006d2000.asm)
- `?d_007a8400@@YAXXZ` at RVA `0x007A8400` (game/gen_asm/d_00776ac0.asm)
- `?d_007a8ff0@@YAXXZ` at RVA `0x007A8FF0` (game/gen_asm/d_00776ac0.asm)
- `?drawRoads@W3DRoadBuffer@@QAEXPAVCameraClass@@ABVTextureHandle@@1_NHHHHPAV?$RefMultiListIterator@VRenderObjClass@@@@@Z` at RVA `0x00710620` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DRoadBuffer_drawRoads.cpp)
- `?publish@Rva00704AF0@@QAEXXZ` at RVA `0x00704AF0` (game/GameEngine/Source/Common/Open2Conv004.cpp)
- `?releaseDependentResources@BfmeShaderShutdown@@SAXXZ` at RVA `0x00717C90` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManagerReleaseResources.cpp)
- `?drawSea@WaterRenderObjClass@@IAEXAAVRenderInfoClass@@@Z` at RVA `0x007A37B0` (game/GameEngineDevice/Source/W3DDevice/GameClient/Water/W3DWater.cpp)

Address users:

- `?Rva00C6C520Init@@YAXXZ` at RVA `0x00C6C520` (game/GameEngine/Source/Common/Rva00C6C520StaticInit.cpp)
- `?d_006d3480@@YAXXZ` at RVA `0x006D3480` (game/gen_asm/d_00610140.asm)
- `?Rva00C70A20Cleanup@@YAXXZ` at RVA `0x00C70A20` (game/GameEngine/Source/Common/Rva00C6C520StaticInit.cpp)

## Refutation and verification

A different allocation target, a nonzero initial byte, a pointer adjustment between the published receiver and these accesses, an overlapping datum, or an indexed access beyond the verified extent would refute this storage/type correction. For a reference-derived name, a retail constructor/vtable or member contract inconsistent with that reference type would also refute it. An EA class-name discovery can improve the retained address-derived renderer types without changing the established datum ownership.

Raw evidence is in `build/rlink/pointer-globals-20261005/012F9D28-retail.log`, `012F9D28-routes.log`, `012F9D28-source.log` and `012F9D28-contract.log`. Retail log instructions and route logs preserve bytes and every observed five-byte E9 thunk through its final target. `reference-defs.log`, `selected-pins.log` and the constructor probes provide the supporting reference and pin extracts. The data-match and per-source Functions gates are recorded in `build/worker-final.md`; verified function bytes and function ledger rows remain unchanged.
