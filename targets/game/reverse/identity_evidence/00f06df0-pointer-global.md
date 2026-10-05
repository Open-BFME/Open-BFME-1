# Datum identity at VA 0x01306DF0

The datum is `?TheW3DProjectedShadowManager@@3PAVW3DProjectedShadowManager@@A` in `game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DProjectedShadow.cpp`. The concrete W3DProjectedShadowManager singleton.

Retail has a 4-byte extent in `.data`, initialized to `00 00 00 00`. The PE base-relocation directory is absent (RVA and size both zero), and the initial value contains no pointer relocation. The complete range has no overlapping data row and no other DIR32 name strictly inside it. Alternative spellings at the start are preserved additively in the DIR32 ledger.

W3DShadowManager constructor at 0x007B7900 allocates 0x254 bytes and calls ILT 0x000246BD, which jumps to constructor 0x007AF5A0. That constructor installs the pinned W3DProjectedShadowManager vtable at VA 0x01128404. The caller publishes it at 0x007B7A74 and also stores its interface pointer at 0x01306DEC. Reacquire, reset, addShadow and shadow-removal bodies use this same concrete singleton; placeholder types are retained only as local receiver casts.

Zero Hour Shadow/W3DProjectedShadow.cpp:84 defines W3DProjectedShadowManager *TheW3DProjectedShadowManager; Include/W3DDevice/GameClient/W3DProjectedShadow.h:92 declares it. The existing constructor, destructor and vtable pins independently support the retail type.

## Receiver and argument contract

A scalar datum stores one 32-bit pointer. Loads passed in ECX are member receivers; stores publish the constructed or factory-returned pointer or clear it to zero. No wrapper, forwarder, inheritance relationship or second object identity is introduced. Existing locally modeled member-call ABIs remain unchanged through casts at their use sites.

## Competing spellings before correction

| Decorated spelling | Game files declaring it |
|---|---:|
| `?R2Ptr01306DF0@@3PAVR2GlobalReceiver@@A` | 1 |
| `?TheGamma@@3PAVGenGamma@@A` | 1 |
| `?TheW3DProjectedShadowManager@@3PAVW3DProjectedShadowManager@@A` | 3 |
| `?g_01306DF0@@3PAVGen_01306DF0@@A` | 2 |
| `?g_bfmeB1062@@3PAVBfmeB1062@@A` | 1 |
| `?g_rva007b13d0@@3PAVW3DProjectedShadowManager@@A` | 1 |
| `?g_rva007b3e60@@3PAVRva007B3E60G@@A` | 1 |

Macro-generated S4 declarations and the terrain-track guarded-call declaration are counted in their owning source. The raw contract log lists each counted path; counts decide no identity.

## Retail reads and writes

Readers:

- `??1W3DShadowManager@@QAE@XZ` at RVA `0x007B7AF0` (game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DShadow.cpp)
- `?DoShadows@@YAXAAVRenderInfoClass@@_N@Z` at RVA `0x007B73D0` (game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/DoShadowsThunk.cpp)
- `?ReAcquireResources@W3DShadowManager@@QAE_NXZ` at RVA `0x007B7620` (game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DShadowManagerReAcquireThunk.cpp)
- `?Rva007B7580@@YAXXZ` at RVA `0x007B7580` (game/GameEngine/Source/Common/S3GuardedGlobalTriples.cpp)
- `?Rva007B75C0@@YAXXZ` at RVA `0x007B75C0` (game/GameEngine/Source/Common/S3GuardedGlobalTriples.cpp)
- `?Rva007B7600@@YAXXZ` at RVA `0x007B7600` (game/GameEngine/Source/Common/R2GuardedGlobalCalls.cpp)
- `?Rva007B7680@@YAXXZ` at RVA `0x007B7680` (game/GameEngine/Source/Common/S3GuardedGlobalTriples.cpp)
- `?Rva007B7880@@YAXXZ` at RVA `0x007B7880` (game/GameEngine/Source/Common/S3GuardedGlobalTriples.cpp)
- `?Rva007B78C0@@YAXXZ` at RVA `0x007B78C0` (game/GameEngine/Source/Common/S3GuardedGlobalTriples.cpp)
- `?addShadow@W3DShadowManager@@QAEPAVShadow@@PAVRenderObjClass@@PAUShadowTypeInfo@2@PAVDrawable@@@Z` at RVA `0x007B76C0` (game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DShadowManagerAddShadow.cpp)
- `?bfmeGo1062A@@YAXXZ` at RVA `0x007B77F0` (game/GameEngine/Source/Common/BfmeConv1062.cpp)
- `?init@W3DShadowManager@@QAE_NXZ` at RVA `0x007B7500` (game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DShadowManagerInit.cpp)
- `?run@Rva007B13D0@@QAEXXZ` at RVA `0x007B13D0` (game/GameEngine/Source/Common/Rva007B13D0Call.cpp)
- `?run@Rva007B3E60@@QAEXXZ` at RVA `0x007B3E60` (game/GameEngine/Source/Common/Rva007B3E60Call.cpp)

Writers:

- `??0W3DShadowManager@@QAE@XZ` at RVA `0x007B7900` (game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DShadow.cpp)
- `??1W3DShadowManager@@QAE@XZ` at RVA `0x007B7AF0` (game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DShadow.cpp)

## Refutation and verification

A different allocation target, a nonzero initial byte, a pointer adjustment between the published receiver and these accesses, an overlapping datum, or an indexed access beyond the verified extent would refute this storage/type correction. For a reference-derived name, a retail constructor/vtable or member contract inconsistent with that reference type would also refute it. An EA class-name discovery can improve the retained address-derived renderer types without changing the established datum ownership.

Raw evidence is in `build/rlink/pointer-globals-20261005/01306DF0-retail.log`, `01306DF0-routes.log`, `01306DF0-source.log` and `01306DF0-contract.log`. Retail log instructions and route logs preserve bytes and every observed five-byte E9 thunk through its final target. `reference-defs.log`, `selected-pins.log` and the constructor probes provide the supporting reference and pin extracts. The data-match and per-source Functions gates are recorded in `build/worker-final.md`; verified function bytes and function ledger rows remain unchanged.
