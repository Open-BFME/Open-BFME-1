# Datum identity at VA 0x01306954

The datum is `?g_rva00785FD0Renderer@@3PAVRva00785FD0Renderer@@A` in `game/Libraries/Source/WWVegas/WW3D2/RendererInitialize00782ED0.cpp`. The owned APT renderer singleton. Its EA class name is unresolved; the existing Rva00785FD0Renderer type and renderer role are retained.

Retail has a 4-byte extent in `.data`, initialized to `00 00 00 00`. The PE base-relocation directory is absent (RVA and size both zero), and the initial value contains no pointer relocation. The complete range has no overlapping data row and no other DIR32 name strictly inside it. Alternative spellings at the start are preserved additively in the DIR32 ledger.

RVA 0x00782ED0 checks this pointer, allocates 0xE0 bytes, calls constructor ILT 0x0003164C ending at 0x0078B310 and stores the result at 0x00782F23. Shutdown 0x00783F60 deletes and clears this same pointer. APT flush 0x00785FD0 and rounded-bounds 0x00786060 call its mode/stencil/begin/end functions; 0x00783010 calls its finish body.

No Zero Hour renderer class is asserted: the APT renderer donor is absent. The existing constructor/deletion receiver pins and direct matched caller contracts establish the address-derived object type. TheOpen2Hub and BfmeHub982 are local views, retained through casts at their existing method-call sites.

## Receiver and argument contract

A scalar datum stores one 32-bit pointer. Loads passed in ECX are member receivers; stores publish the constructed or factory-returned pointer or clear it to zero. No wrapper, forwarder, inheritance relationship or second object identity is introduced. Existing locally modeled member-call ABIs remain unchanged through casts at their use sites.

## Competing spellings before correction

| Decorated spelling | Game files declaring it |
|---|---:|
| `?TheOpen2Hub@@3PAVOpen2Hub@@A` | 1 |
| `?g_bfmeHub982@@3PAVBfmeHub982@@A` | 2 |
| `?g_rva00785FD0Renderer@@3PAVRva00785FD0Renderer@@A` | 3 |

Macro-generated S4 declarations and the terrain-track guarded-call declaration are counted in their owning source. The raw contract log lists each counted path; counts decide no identity.

## Retail reads and writes

Readers:

- `?Rva00783010@@YAXXZ` at RVA `0x00783010` (game/GameEngine/Source/Common/Open2Conv007.cpp)
- `?applyRoundedBounds00786060@@YAXPBDHPAVBoundsSource00786060@@H@Z` at RVA `0x00786060` (game/GameEngineDevice/Source/W3DDevice/GameClient/GUI/Rva00786060AptRoundedBounds.cpp)
- `?bfmeGo982C@@YAXPAVBfmeT982@@@Z` at RVA `0x00786C30` (game/GameEngine/Source/Common/BfmeConv982.cpp)
- `?bfmeOneSGA@BfmeThingSGA@@QAEXXZ` at RVA `0x00782ED0` (game/Libraries/Source/WWVegas/WW3D2/RendererInitialize00782ED0.cpp)
- `?bfmeShutYP@@YAXXZ` at RVA `0x00783F60` (game/GameEngine/Source/Common/BfmeConv2101.cpp)
- `?d_00785300@@YAXXZ` at RVA `0x00785300` (game/gen_asm/d_00781660.asm)
- `?d_007874f0@@YAXXZ` at RVA `0x007874F0` (game/gen_asm/d_006f60e0.asm)
- `?rva00785FD0Flush@@YAXXZ` at RVA `0x00785FD0` (game/GameEngine/Source/GameClient/GUI/Rva00785FD0AptFlush.cpp)

Writers:

- `?bfmeOneSGA@BfmeThingSGA@@QAEXXZ` at RVA `0x00782ED0` (game/Libraries/Source/WWVegas/WW3D2/RendererInitialize00782ED0.cpp)
- `?bfmeShutYP@@YAXXZ` at RVA `0x00783F60` (game/GameEngine/Source/Common/BfmeConv2101.cpp)

## Refutation and verification

A different allocation target, a nonzero initial byte, a pointer adjustment between the published receiver and these accesses, an overlapping datum, or an indexed access beyond the verified extent would refute this storage/type correction. For a reference-derived name, a retail constructor/vtable or member contract inconsistent with that reference type would also refute it. An EA class-name discovery can improve the retained address-derived renderer types without changing the established datum ownership.

Raw evidence is in `build/rlink/pointer-globals-20261005/01306954-retail.log`, `01306954-routes.log`, `01306954-source.log` and `01306954-contract.log`. Retail log instructions and route logs preserve bytes and every observed five-byte E9 thunk through its final target. `reference-defs.log`, `selected-pins.log` and the constructor probes provide the supporting reference and pin extracts. The data-match and per-source Functions gates are recorded in `build/worker-final.md`; verified function bytes and function ledger rows remain unchanged.
