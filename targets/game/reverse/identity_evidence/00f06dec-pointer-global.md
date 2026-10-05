# Datum identity at VA 0x01306DEC

The datum is `?TheProjectedShadowManager@@3PAVProjectedShadowManager@@A` in `game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DProjectedShadow.cpp`. The ProjectedShadowManager interface view of the projected-shadow singleton also stored at 0x01306DF0. These are two pointer datums holding the same object, not two aliases of one datum.

Retail has a 4-byte extent in `.data`, initialized to `00 00 00 00`. The PE base-relocation directory is absent (RVA and size both zero), and the initial value contains no pointer relocation. The complete range has no overlapping data row and no other DIR32 name strictly inside it. Alternative spellings at the start are preserved additively in the DIR32 ledger.

W3DShadowManager constructor at 0x007B7900 constructs the projected manager through ILT 0x000246BD and writes the same EAX to 0x01306DF0 at 0x007B7A74 and to 0x01306DEC at 0x007B7A79, without pointer adjustment. Decal-creation bodies invoke its interface vtable, including slot +0x10 in 0x00299BB0. The manager destructor clears both datums.

Zero Hour Shadow/W3DProjectedShadow.cpp:84-85 defines both W3DProjectedShadowManager *TheW3DProjectedShadowManager and ProjectedShadowManager *TheProjectedShadowManager. Shadow/W3DShadow.cpp assigns the concrete manager to the interface pointer. Retail separately stores both views exactly this way.

## Receiver and argument contract

A scalar datum stores one 32-bit pointer. Loads passed in ECX are member receivers; stores publish the constructed or factory-returned pointer or clear it to zero. No wrapper, forwarder, inheritance relationship or second object identity is introduced. Existing locally modeled member-call ABIs remain unchanged through casts at their use sites.

## Competing spellings before correction

| Decorated spelling | Game files declaring it |
|---|---:|
| `?TheProjectedShadowManager@@3PAVProjectedShadowManager@@A` | 7 |
| `?g_manager00299BB0@@3PAVManager00299BB0@@A` | 1 |

Macro-generated S4 declarations and the terrain-track guarded-call declaration are counted in their owning source. The raw contract log lists each counted path; counts decide no identity.

## Retail reads and writes

Readers:

- `?bfmeGoZF@BfmeSubZF@@QAEXPAX00PAUBfmeStateZF@@@Z` at RVA `0x00458AA0` (game/GameEngine/Source/Common/BfmeSubZF_bfmeGoZF.cpp)
- `?create@DecalCreate00299BB0@@QAEXXZ` at RVA `0x00299BB0` (game/GameEngine/Source/Common/DecalCreate00299BB0.cpp)
- `?createRadiusDecal@RadiusDecalTemplate@@QAEXMMMIHAAVRadiusDecal@@M@Z` at RVA `0x004588D0` (game/GameEngine/Source/GameClient/RadiusDecalTemplate_createSelection.cpp)
- `?createRadiusDecal@RadiusDecalTemplate@@QBEXABUCoord3D@@MPBVPlayer@@AAVRadiusDecal@@@Z` at RVA `0x00458C80` (game/GameEngine/Source/GameClient/RadiusDecalTemplate_createRadiusDecal.cpp)
- `?rva007633A0@W3DModelDraw@@UAEXPAURva007633A0Input@@@Z` at RVA `0x007633A0` (game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawRva007633A0.cpp)
- `?setTerrainDecal@W3DModelDraw@@UAEXW4TerrainDecalType@@@Z` at RVA `0x00763230` (game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawSetTerrainDecal.cpp)
- `?doFXPos@DynamicDecalFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z` at RVA `0x00429080` (game/GameEngine/Source/GameClient/DynamicDecalFXNuggetDoFXPos.cpp)

Writers:

- `??0W3DShadowManager@@QAE@XZ` at RVA `0x007B7900` (game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DShadow.cpp)
- `??1W3DShadowManager@@QAE@XZ` at RVA `0x007B7AF0` (game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DShadow.cpp)

## Refutation and verification

A different allocation target, a nonzero initial byte, a pointer adjustment between the published receiver and these accesses, an overlapping datum, or an indexed access beyond the verified extent would refute this storage/type correction. For a reference-derived name, a retail constructor/vtable or member contract inconsistent with that reference type would also refute it. An EA class-name discovery can improve the retained address-derived renderer types without changing the established datum ownership.

Raw evidence is in `build/rlink/pointer-globals-20261005/01306DEC-retail.log`, `01306DEC-routes.log`, `01306DEC-source.log` and `01306DEC-contract.log`. Retail log instructions and route logs preserve bytes and every observed five-byte E9 thunk through its final target. `reference-defs.log`, `selected-pins.log` and the constructor probes provide the supporting reference and pin extracts. The data-match and per-source Functions gates are recorded in `build/worker-final.md`; verified function bytes and function ledger rows remain unchanged.
