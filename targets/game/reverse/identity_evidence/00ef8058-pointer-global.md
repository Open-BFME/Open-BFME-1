# Datum identity at VA 0x012F8058

The datum is `?m_3DScene@W3DDisplay@@2PAVRTS3DScene@@A` in `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp`. W3DDisplay static primary RTS3DScene pointer.

Retail has a 4-byte extent in `.data`, initialized to `00 00 00 00`. The PE base-relocation directory is absent (RVA and size both zero), and the initial value contains no pointer relocation. The complete range has no overlapping data row and no other DIR32 name strictly inside it. Alternative spellings at the start are preserved additively in the DIR32 ledger.

The W3DDisplay constructor at 0x006EF850 clears it. W3DDisplay::init at 0x006ED5B0 allocates 0x8A0 bytes and calls constructor 0x00712F60 through its ILT. The display destructor at 0x006EFC20 releases it. Main-world terrain, lights, drawables and view methods load this primary scene. createLightsIterator calls through ILT to 0x007123F0, whose RTS3DScene pin names the receiver.

Zero Hour GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp:369 defines RTS3DScene *W3DDisplay::m_3DScene. The three separate scene addresses and their construction/use roles match the reference; BFME allocation views remain casts to the canonical pointer.

## Receiver and argument contract

A scalar datum stores one 32-bit pointer. Loads passed in ECX are member receivers; stores publish the constructed or factory-returned pointer or clear it to zero. No wrapper, forwarder, inheritance relationship or second object identity is introduced. Existing locally modeled member-call ABIs remain unchanged through casts at their use sites.

## Competing spellings before correction

| Decorated spelling | Game files declaring it |
|---|---:|
| `?Rva012F8058@@3PAVRva00712F60@@A` | 1 |
| `?g_Va012F8058@@3PAVSceneClass@@A` | 0 |
| `?g_bfmeGlobPB@@3PAVBfmeGlobPB@@A` | 0 |
| `?g_bfmeGlobPB@@3PAVBfmeScene@@A` | 0 |
| `?g_bfmeGlobQC@@3PAVBfmeGlobQC@@A` | 0 |
| `?g_lightPulseScene@@3PAVRTS3DSceneLightPulseShim@@A` | 0 |
| `?g_rva006BC6C0Target@@3PAVRva006BC6C0Target@@A` | 0 |
| `?g_scene@@3PAVSceneClass@@A` | 0 |
| `?m_3DScene@W3DDisplay@@2PAVBFME3DScene@@A` | 0 |
| `?m_3DScene@W3DDisplay@@2PAVRTS3DScene@@A` | 32 |
| `?m_3DScene@W3DDisplay@@2PAVSceneClass@@A` | 1 |

Macro-generated S4 declarations and the terrain-track guarded-call declaration are counted in their owning source. The raw contract log lists each counted path; counts decide no identity.

## Retail reads and writes

Readers:

- `??0Particle@@QAE@ABVBfmeParticleSystemHandle@@PBVParticleInfo@@@Z` at RVA `0x005CF330` (game/GameEngine/Source/GameClient/System/ParticleConstructor.cpp)
- `??0W3DDefaultDraw@@QAE@PAVThing@@PBVModuleData@@@Z` at RVA `0x007513C0` (game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DDefaultDrawConstructor.cpp)
- `??0W3DLightDraw@@QAE@PAVThing@@PBVModuleData@@@Z` at RVA `0x007583A0` (game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DLightDrawConstructor.cpp)
- `??0W3DStreakDraw@@QAE@PAVThing@@PBVModuleData@@@Z` at RVA `0x0077D930` (game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DStreakDrawConstructor.cpp)
- `??1W3DDebrisDraw@@MAE@XZ` at RVA `0x00750730` (game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DDebrisDrawDestructor.cpp)
- `??1W3DDefaultDraw@@MAE@XZ` at RVA `0x007510D0` (game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DDefaultDrawDestructor.cpp)
- `??1W3DDisplay@@UAE@XZ` at RVA `0x006EFC20` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayDestructor.cpp)
- `??1W3DLaserDraw@@MAE@XZ` at RVA `0x00757A50` (game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DLaserDrawDestructor.cpp)
- `??1W3DModelDraw@@MAE@XZ` at RVA `0x0077B090` (game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawDestructorThunk.cpp)
- `??1W3DStreakDraw@@UAE@XZ` at RVA `0x0077D510` (game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DStreakDrawDestructor.cpp)
- `?apply@Rva006BC6C0@@QAEXXZ` at RVA `0x006BC6C0` (game/GameEngine/Source/Common/Rva006BC6C0Apply.cpp)
- `?bfmeGoPB@BfmeThingPB@@QAEXH@Z` at RVA `0x006BC850` (game/GameEngine/Source/Common/BfmeConv906.cpp)
- `?bfmeGoQC@@YGXPAX@Z` at RVA `0x006EAB90` (game/GameEngine/Source/Common/BfmeConv907.cpp)
- `?bfmeSweepBP@BfmeHostBP@@QAEXXZ` at RVA `0x006BC7B0` (game/GameEngine/Source/Common/BfmeConv1915.cpp)
- `?buildSegments@W3DRopeDraw@@AAEXXZ` at RVA `0x0075A990` (game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DRopeDraw.cpp)
- `?calculateTerrainLOD@W3DDisplay@@IAEXXZ` at RVA `0x006E8E60` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayCalculateTerrainLOD.cpp)
- `?createDynamicLight@W3DPoliceCarDraw@@IAEPAVW3DDynamicLight@@XZ` at RVA `0x00758C30` (game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DPoliceCarDrawCreateDynamicLight.cpp)
- `?createLightPulse@W3DDisplay@@UAEXPBUCoord3D@@PBURGBColor@@MMII@Z` at RVA `0x006E9540` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayCreate.cpp)
- `?d_006bd6e0@@YAXXZ` at RVA `0x006BD6E0` (game/gen_asm/d_006b9500.asm)
- `?d_006e6a80@@YAXXZ` at RVA `0x006E6A80` (game/gen_asm/d_006e0580.asm)
- `?d_006eb500@@YAXXZ` at RVA `0x006EB500` (game/gen_asm/d_006e0580.asm)
- `?d_006ebc30@@YAXXZ` at RVA `0x006EBC30` (game/gen_asm/d_006e7d70.asm)
- `?d_00731190@@YAXXZ` at RVA `0x00731190` (game/gen_asm/d_006e2ac0.asm)
- `?d_0073e050@@YAXXZ` at RVA `0x0073E050` (game/gen_asm/d_0073e050.asm)
- `?d_00745370@@YAXXZ` at RVA `0x00745370` (game/gen_asm/d_00733000.asm)
- `?d_00755f70@@YAXXZ` at RVA `0x00755F70` (game/gen_asm/d_006e2ac0.asm)
- `?d_00776ac0@@YAXXZ` at RVA `0x00776AC0` (game/gen_asm/d_00776ac0.asm)
- `?d_00777b50@@YAXXZ` at RVA `0x00777B50` (game/gen_asm/d_007739f0.asm)
- `?d_0077ab30@@YAXXZ` at RVA `0x0077AB30` (game/gen_asm/d_00776ac0.asm)
- `?dispatch@W3DShrubBuffer@@QAEXHH@Z` at RVA `0x007202F0` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShrubBufferRva007202F0.cpp)
- `?drawMoveHints@W3DInGameUI@@MAEXPAVView@@@Z` at RVA `0x006FC5A0` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DInGameUI_drawMoveHints.cpp)
- `?drawPlaceAngle@W3DInGameUI@@QAEXPAVView@@@Z` at RVA `0x006FC0D0` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DInGameUI_drawPlaceAngle.cpp)
- `?init@Rva00730590@@UAEXXZ` at RVA `0x00730590` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisualRva00730590Init.cpp)
- `?init@W3DDisplay@@UAEXXZ` at RVA `0x006ED5B0` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayInit_Bfme.cpp)
- `?nukeCurrentRender@W3DModelDraw@@AAEXPAVMatrix3D@@@Z` at RVA `0x0075C050` (game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawNukeCurrentRender.cpp)
- `?reset@W3DDisplay@@UAEXXZ` at RVA `0x006E8210` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayReset.cpp)
- `?rva006E9940@W3DDisplay@@UAEXM@Z` at RVA `0x006E9940` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayRva006E9940.cpp)
- `?rva00736150@W3DTreeBuffer@@QAEXHH@Z` at RVA `0x00736150` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeBufferRva00736150.cpp)
- `?rva00779910@W3DModelDraw@@QAEXXZ` at RVA `0x00779910` (game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawRva00779910.cpp)
- `?setCameraTransform@W3DView@@AAEXXZ` at RVA `0x007423B0` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DView.cpp)
- `?setLocalPlayerIndex@W3DGhostObjectManager@@UAEXH@Z` at RVA `0x006BC8F0` (game/GameEngineDevice/Source/W3DDevice/GameLogic/W3DGhostObjectSetLocalPlayerIndex.cpp)
- `?setModelName@W3DDebrisDraw@@UAEXVAsciiString@@HW4ShadowType@@@Z` at RVA `0x00750CC0` (game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DDebrisDraw.cpp)
- `?snapShot@W3DGhostObject@@UAEXH@Z` at RVA `0x006BDE00` (game/GameEngineDevice/Source/W3DDevice/GameLogic/W3DGhostObjectSnapShot.cpp)
- `?tossSegments@W3DRopeDraw@@AAEXXZ` at RVA `0x0075A660` (game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DRopeDrawDestructorThunk.cpp)
- `?update@Rva006E2540@@QAEXXZ` at RVA `0x006E2540` (game/GameEngine/Source/Common/Rva006E2540.cpp)
- `?update@W3DView@@UAEXXZ` at RVA `0x007446A0` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewUpdateBfme.cpp)
- `??0W3DLaserDraw@@QAE@PAVThing@@PBVModuleData@@@Z` at RVA `0x00757E70` (game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DLaserDrawBfmeConstructor.cpp)
- `?rva00744360HasClearShot@W3DView@@UAE_NW4ObjectID@@0H@Z` at RVA `0x00744360` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewRva00744360.cpp)

Writers:

- `??0Gen006EF850@@QAE@XZ` at RVA `0x006EF850` (game/GameEngineDevice/Source/W3DDevice/GameClient/Gen006EF850Constructor.cpp)
- `??1W3DDisplay@@UAE@XZ` at RVA `0x006EFC20` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayDestructor.cpp)
- `?init@W3DDisplay@@UAEXXZ` at RVA `0x006ED5B0` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayInit_Bfme.cpp)

## Supplemental retail accesses

`build/rlink/pointer-globals-20261005/012F8058-missing-refs.log` disassembles additional Ghidra extents from their recorded starts. These are retail instructions, not a decompiler draft. The additional containing bodies and instruction sites are:

- RVA `0x778590`, recorded extent 3983 bytes: `0x0077936D`.

Local byte-hit candidates outside these extents are also preserved in that raw log. Their containing-body boundaries remain open and do not establish another datum identity. The original contract log retains the complete byte-hit inventory.

## Refutation and verification

A different allocation target, a nonzero initial byte, a pointer adjustment between the published receiver and these accesses, an overlapping datum, or an indexed access beyond the verified extent would refute this storage/type correction. For a reference-derived name, a retail constructor/vtable or member contract inconsistent with that reference type would also refute it. An EA class-name discovery can improve the retained address-derived renderer types without changing the established datum ownership.

Raw evidence is in `build/rlink/pointer-globals-20261005/012F8058-retail.log`, `012F8058-routes.log`, `012F8058-source.log` and `012F8058-contract.log`. Retail log instructions and route logs preserve bytes and every observed five-byte E9 thunk through its final target. `reference-defs.log`, `selected-pins.log` and the constructor probes provide the supporting reference and pin extracts. The data-match and per-source Functions gates are recorded in `build/worker-final.md`; verified function bytes and function ledger rows remain unchanged.
