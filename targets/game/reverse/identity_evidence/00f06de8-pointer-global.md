# Datum identity at VA 0x01306DE8

The datum is `?TheW3DBufferManager@@3PAVW3DBufferManager@@A` in `game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DBufferManager.cpp`. The W3DBufferManager singleton for shadow vertex and index buffer slots.

Retail has a 4-byte extent in `.data`, initialized to `00 00 00 00`. The PE base-relocation directory is absent (RVA and size both zero), and the initial value contains no pointer relocation. The complete range has no overlapping data row and no other DIR32 name strictly inside it. Alternative spellings at the start are preserved additively in the DIR32 ledger.

W3DVolumetricShadowManager constructor at 0x007BB520 constructs and stores the buffer manager here. Its destructor 0x007BDE90 deletes and clears the pointer. Volumetric shadow bodies allocate/release VB and IB slots and call freeAllBuffers through this receiver.

Zero Hour GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DBufferManager.cpp:29 defines W3DBufferManager *TheW3DBufferManager; Include/W3DDevice/GameClient/W3DBufferManager.h:178 declares it.

## Receiver and argument contract

A scalar datum stores one 32-bit pointer. Loads passed in ECX are member receivers; stores publish the constructed or factory-returned pointer or clear it to zero. No wrapper, forwarder, inheritance relationship or second object identity is introduced. Existing locally modeled member-call ABIs remain unchanged through casts at their use sites.

## Competing spellings before correction

| Decorated spelling | Game files declaring it |
|---|---:|
| `?TheBfmeReleaseOwner@@3PAVRva007ADB80Owner@@A` | 0 |
| `?TheBfmeReleaseOwner@@3PAVW3DBufferManager@@A` | 0 |
| `?TheW3DBufferManager@@3PAVW3DBufferManager@@A` | 7 |

Macro-generated S4 declarations and the terrain-track guarded-call declaration are counted in their owning source. The raw contract log lists each counted path; counts decide no identity.

## Retail reads and writes

Readers:

- `??1W3DVolumetricShadow@@UAE@XZ` at RVA `0x007BCF50` (game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadowCompleteDestructor.cpp)
- `??1W3DVolumetricShadowManager@@QAE@XZ` at RVA `0x007BDE90` (game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadowManagerDestructorThunk.cpp)
- `?ReAcquireResources@W3DShadowHelperManager@@QAE_NXZ` at RVA `0x007B9810` (game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DShadowHelperManagerReAcquireResources.cpp)
- `?Update@W3DVolumetricShadow@@IAEXXZ` at RVA `0x007BF7D0` (game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadow_UpdateMethodThunk.cpp)
- `?constructVolumeVB@W3DVolumetricShadow@@IAEXPAVVector3@@MHH@Z` at RVA `0x007B8980` (game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadow.cpp)
- `?h00024D2A@GenAlpha@@QAEXXZ` at RVA `0x007B9760` (game/GameEngine/Source/Common/GenAlpha_h00024D2A.cpp)
- `?h00044062@GenAlpha@@QAEXXZ` at RVA `0x007BD0C0` (game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/GenAlphaFreeShadowResources.cpp)
- `?renderShadows@W3DVolumetricShadowManager@@QAEX_N@Z` at RVA `0x007BFB90` (game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadow.cpp)
- `?resetShadowVolume@W3DVolumetricShadow@@IAEXHH@Z` at RVA `0x007B9110` (game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadow.cpp)

Writers:

- `??0W3DVolumetricShadowManager@@QAE@XZ` at RVA `0x007BB520` (game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadowManager_ctor_Thunk.cpp)
- `??1W3DVolumetricShadowManager@@QAE@XZ` at RVA `0x007BDE90` (game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadowManagerDestructorThunk.cpp)

## Refutation and verification

A different allocation target, a nonzero initial byte, a pointer adjustment between the published receiver and these accesses, an overlapping datum, or an indexed access beyond the verified extent would refute this storage/type correction. For a reference-derived name, a retail constructor/vtable or member contract inconsistent with that reference type would also refute it. An EA class-name discovery can improve the retained address-derived renderer types without changing the established datum ownership.

Raw evidence is in `build/rlink/pointer-globals-20261005/01306DE8-retail.log`, `01306DE8-routes.log`, `01306DE8-source.log` and `01306DE8-contract.log`. Retail log instructions and route logs preserve bytes and every observed five-byte E9 thunk through its final target. `reference-defs.log`, `selected-pins.log` and the constructor probes provide the supporting reference and pin extracts. The data-match and per-source Functions gates are recorded in `build/worker-final.md`; verified function bytes and function ledger rows remain unchanged.
