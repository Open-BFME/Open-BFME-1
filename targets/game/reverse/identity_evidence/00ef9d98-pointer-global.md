# Datum identity at VA 0x012F9D98

The datum is `?TheTerrainTracksRenderObjClassSystem@@3PAVTerrainTracksRenderObjClassSystem@@A` in `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainTracks.cpp`. The terrain-track rendering system singleton.

Retail has a 4-byte extent in `.data`, initialized to `00 00 00 00`. The PE base-relocation directory is absent (RVA and size both zero), and the initial value contains no pointer relocation. The complete range has no overlapping data row and no other DIR32 name strictly inside it. Alternative spellings at the start are preserved additively in the DIR32 ledger.

Terrain visual construction/init allocates, publishes and initializes this object with the primary scene. Terrain visual shutdown deletes and clears it. The guarded update at 0x00730FE0 loads this pointer into ECX and calls 0x0072F080. Track-drawing bodies use it for track-edge counts and flushing.

Zero Hour GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainTracks.cpp:979 defines TerrainTracksRenderObjClassSystem *TheTerrainTracksRenderObjClassSystem; W3DTerrainVisual.cpp constructs and initializes it with W3DDisplay::m_3DScene.

## Receiver and argument contract

A scalar datum stores one 32-bit pointer. Loads passed in ECX are member receivers; stores publish the constructed or factory-returned pointer or clear it to zero. No wrapper, forwarder, inheritance relationship or second object identity is introduced. Existing locally modeled member-call ABIs remain unchanged through casts at their use sites.

## Competing spellings before correction

| Decorated spelling | Game files declaring it |
|---|---:|
| `?TheTerrainTracksRenderObjClassSystem@@3PAVTerrainTracksRenderObjClassSystem@@A` | 6 |
| `?g_Glo00EF9D98@@3PAVGen0072F080@@A` | 1 |

Macro-generated S4 declarations and the terrain-track guarded-call declaration are counted in their owning source. The raw contract log lists each counted path; counts decide no identity.

## Retail reads and writes

Readers:

- `??1W3DModelDraw@@MAE@XZ` at RVA `0x0077B090` (game/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DModelDrawDestructorThunk.cpp)
- `??1W3DTerrainVisual@@UAE@XZ` at RVA `0x00731050` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisualDestructorBfme.cpp)
- `?ReAcquireResources@BaseHeightMapRenderObjClass@@UAEXXZ` at RVA `0x006C6190` (game/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMapReAcquireResources_Bfme.cpp)
- `?ReleaseResources@BaseHeightMapRenderObjClass@@UAEXXZ` at RVA `0x006C5FC0` (game/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMapReleaseResources_Bfme.cpp)
- `?Rva00730FE0@@YAXXZ` at RVA `0x00730FE0` (game/GameEngine/Source/Common/R1GuardedPointerTailCalls.cpp)
- `?addCapEdgeToTrack@BfmeTrackLikeD62640@@QAEXMM@Z` at RVA `0x0072F390` (game/GameEngineDevice/Source/W3DDevice/GameClient/TerrainTracksBfmeAddCap.cpp)
- `?addEdgeToTrack@TerrainTracksRenderObjClass@@QAEXMM@Z` at RVA `0x0072F760` (game/GameEngineDevice/Source/W3DDevice/GameClient/TerrainTracksBfmeAddCap.cpp)
- `?d_006d3480@@YAXXZ` at RVA `0x006D3480` (game/gen_asm/d_00610140.asm)
- `?d_006f3fc0@@YAXXZ` at RVA `0x006F3FC0` (game/gen_asm/d_006e2ac0.asm)
- `?d_00755f70@@YAXXZ` at RVA `0x00755F70` (game/gen_asm/d_006e2ac0.asm)
- `?reset@W3DTerrainVisual@@UAEXXZ` at RVA `0x007308F0` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisual.cpp)

Writers:

- `??1W3DTerrainVisual@@UAE@XZ` at RVA `0x00731050` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisualDestructorBfme.cpp)
- `?init@Rva00730590@@UAEXXZ` at RVA `0x00730590` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainVisualRva00730590Init.cpp)

## Supplemental retail accesses

`build/rlink/pointer-globals-20261005/012F9D98-missing-refs.log` disassembles additional Ghidra extents from their recorded starts. These are retail instructions, not a decompiler draft. The additional containing bodies and instruction sites are:

- RVA `0x778590`, recorded extent 3983 bytes: `0x00778EF1`, `0x00778F3D`.

Local byte-hit candidates outside these extents are also preserved in that raw log. Their containing-body boundaries remain open and do not establish another datum identity. The original contract log retains the complete byte-hit inventory.

## Refutation and verification

A different allocation target, a nonzero initial byte, a pointer adjustment between the published receiver and these accesses, an overlapping datum, or an indexed access beyond the verified extent would refute this storage/type correction. For a reference-derived name, a retail constructor/vtable or member contract inconsistent with that reference type would also refute it. An EA class-name discovery can improve the retained address-derived renderer types without changing the established datum ownership.

Raw evidence is in `build/rlink/pointer-globals-20261005/012F9D98-retail.log`, `012F9D98-routes.log`, `012F9D98-source.log` and `012F9D98-contract.log`. Retail log instructions and route logs preserve bytes and every observed five-byte E9 thunk through its final target. `reference-defs.log`, `selected-pins.log` and the constructor probes provide the supporting reference and pin extracts. The data-match and per-source Functions gates are recorded in `build/worker-final.md`; verified function bytes and function ledger rows remain unchanged.
