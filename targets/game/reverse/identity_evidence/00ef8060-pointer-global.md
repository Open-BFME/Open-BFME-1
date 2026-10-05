# Datum identity at VA 0x012F8060

The datum is `?m_3DInterfaceScene@W3DDisplay@@2PAVRTS3DInterfaceScene@@A` in `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp`. W3DDisplay static RTS3DInterfaceScene pointer for interface/cursor objects.

Retail has a 4-byte extent in `.data`, initialized to `00 00 00 00`. The PE base-relocation directory is absent (RVA and size both zero), and the initial value contains no pointer relocation. The complete range has no overlapping data row and no other DIR32 name strictly inside it. Alternative spellings at the start are preserved additively in the DIR32 ledger.

The display constructor clears it, init allocates 0x108 bytes, calls 0x00711B00, publishes at RVA 0x006ED63C and sets ambient light. The display destructor releases it. W3DMouse draw/free-assets/setCursor bodies access this scene for cursor render objects.

Zero Hour W3DDisplay.cpp:371 defines RTS3DInterfaceScene *W3DDisplay::m_3DInterfaceScene; W3DMouse.cpp adds, removes and renders cursor models through that scene.

## Receiver and argument contract

A scalar datum stores one 32-bit pointer. Loads passed in ECX are member receivers; stores publish the constructed or factory-returned pointer or clear it to zero. No wrapper, forwarder, inheritance relationship or second object identity is introduced. Existing locally modeled member-call ABIs remain unchanged through casts at their use sites.

## Competing spellings before correction

| Decorated spelling | Game files declaring it |
|---|---:|
| `?Rva012F8060@@3PAVRva00711B00@@A` | 1 |
| `?m_3DInterfaceScene@W3DDisplay@@2PAVRTS3DInterfaceScene@@A` | 2 |

Macro-generated S4 declarations and the terrain-track guarded-call declaration are counted in their owning source. The raw contract log lists each counted path; counts decide no identity.

## Retail reads and writes

Readers:

- `??1W3DDisplay@@UAE@XZ` at RVA `0x006EFC20` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayDestructor.cpp)
- `?draw@W3DMouse@@UAEXXZ` at RVA `0x00700A40` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DMouse.cpp)
- `?freeW3DAssets@W3DMouse@@AAEXXZ` at RVA `0x00700710` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DMouse.cpp)
- `?setCursor@W3DMouse@@UAEXW4MouseCursor@Mouse@@@Z` at RVA `0x007018A0` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DMouse.cpp)

Writers:

- `??0Gen006EF850@@QAE@XZ` at RVA `0x006EF850` (game/GameEngineDevice/Source/W3DDevice/GameClient/Gen006EF850Constructor.cpp)
- `??1W3DDisplay@@UAE@XZ` at RVA `0x006EFC20` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayDestructor.cpp)
- `?init@W3DDisplay@@UAEXXZ` at RVA `0x006ED5B0` (game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayInit_Bfme.cpp)

## Refutation and verification

A different allocation target, a nonzero initial byte, a pointer adjustment between the published receiver and these accesses, an overlapping datum, or an indexed access beyond the verified extent would refute this storage/type correction. For a reference-derived name, a retail constructor/vtable or member contract inconsistent with that reference type would also refute it. An EA class-name discovery can improve the retained address-derived renderer types without changing the established datum ownership.

Raw evidence is in `build/rlink/pointer-globals-20261005/012F8060-retail.log`, `012F8060-routes.log`, `012F8060-source.log` and `012F8060-contract.log`. Retail log instructions and route logs preserve bytes and every observed five-byte E9 thunk through its final target. `reference-defs.log`, `selected-pins.log` and the constructor probes provide the supporting reference and pin extracts. The data-match and per-source Functions gates are recorded in `build/worker-final.md`; verified function bytes and function ledger rows remain unchanged.
