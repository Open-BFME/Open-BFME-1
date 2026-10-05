# Datum identity at VA 0x012F805C

The datum is `?m_2DScene@W3DDisplay@@2PAVRTS2DScene@@A` in `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp`. W3DDisplay static RTS2DScene pointer.

Retail has a 4-byte extent in `.data`, initialized to `00 00 00 00`. The PE base-relocation directory is absent (RVA and size both zero), and the initial value contains no pointer relocation. The complete range has no overlapping data row and no other DIR32 name strictly inside it. Alternative spellings at the start are preserved additively in the DIR32 ledger.

The display constructor clears this pointer, init allocates and publishes RTS2DScene at store RVA 0x006ED691 and sets ambient light, and the display destructor releases and clears it. The 2D display/view rendering path reads this distinct scene.

Zero Hour W3DDisplay.cpp:370 defines RTS2DScene *W3DDisplay::m_2DScene, and W3DView.cpp renders the 2D scene with m_2DCamera.

## Receiver and argument contract

A scalar datum stores one 32-bit pointer. Loads passed in ECX are member receivers; stores publish the constructed or factory-returned pointer or clear it to zero. No wrapper, forwarder, inheritance relationship or second object identity is introduced. Existing locally modeled member-call ABIs remain unchanged through casts at their use sites.

## Competing spellings before correction

| Decorated spelling | Game files declaring it |
|---|---:|
| `?Rva012F805C@@3PAVRTS2DScene@@A` | 1 |
| `?m_2DScene@W3DDisplay@@2PAVRTS2DScene@@A` | 2 |

Macro-generated S4 declarations and the terrain-track guarded-call declaration are counted in their owning source. The raw contract log lists each counted path; counts decide no identity.

## Retail reads and writes

Readers:

- `??1W3DDisplay@@UAE@XZ` at RVA `0x006EFC20` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayDestructor.cpp)
- `?d_0073e050@@YAXXZ` at RVA `0x0073E050` (game/gen_asm/d_0073e050.asm)

Writers:

- `??0Gen006EF850@@QAE@XZ` at RVA `0x006EF850` (game/GameEngineDevice/Source/W3DDevice/GameClient/Gen006EF850Constructor.cpp)
- `??1W3DDisplay@@UAE@XZ` at RVA `0x006EFC20` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayDestructor.cpp)
- `?init@W3DDisplay@@UAEXXZ` at RVA `0x006ED5B0` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayInit_Bfme.cpp)

## Refutation and verification

A different allocation target, a nonzero initial byte, a pointer adjustment between the published receiver and these accesses, an overlapping datum, or an indexed access beyond the verified extent would refute this storage/type correction. For a reference-derived name, a retail constructor/vtable or member contract inconsistent with that reference type would also refute it. An EA class-name discovery can improve the retained address-derived renderer types without changing the established datum ownership.

Raw evidence is in `build/rlink/pointer-globals-20261005/012F805C-retail.log`, `012F805C-routes.log`, `012F805C-source.log` and `012F805C-contract.log`. Retail log instructions and route logs preserve bytes and every observed five-byte E9 thunk through its final target. `reference-defs.log`, `selected-pins.log` and the constructor probes provide the supporting reference and pin extracts. The data-match and per-source Functions gates are recorded in `build/worker-final.md`; verified function bytes and function ledger rows remain unchanged.
