# Datum identity at VA 0x012F6DA4

The datum is `?TheBfmeSecondManager@@3PAVPointGroupClass@@A` in `game/GameEngine/Source/Common/S4CtorThenPublishNew.cpp`. An owning PointGroupClass pointer for point-group rendering. The existing role-describing global name is retained.

Retail has a 4-byte extent in `.data`, initialized to `00 00 00 00`. The PE base-relocation directory is absent (RVA and size both zero), and the initial value contains no pointer relocation. The complete range has no overlapping data row and no other DIR32 name strictly inside it. Alternative spellings at the start are preserved additively in the DIR32 ledger.

RVA 0x005F36D0 allocates 0x5C bytes and directly calls 0x00912580, then writes the returned pointer to 0x012F6DA4. The constructor writes vtable VA 0x0113ACA4, six array pointers, a texture pointer, the additive sprite shader and unit default color and alpha. The shutdown at 0x005F3140 null-checks the global and calls virtual slot zero with the scalar-delete flag 1.

The existing ??0PointGroupClass@@QAE@XZ pin at RVA 0x00912580 is backed by the constructor layout in Zero Hour Libraries/Source/WWVegas/WW3D2/pointgr.cpp. ctor-00912580.log records the retail stores; the 91-byte constructor ends in RET at +0x5A.

## Receiver and argument contract

A scalar datum stores one 32-bit pointer. Loads passed in ECX are member receivers; stores publish the constructed or factory-returned pointer or clear it to zero. No wrapper, forwarder, inheritance relationship or second object identity is introduced. Existing locally modeled member-call ABIs remain unchanged through casts at their use sites.

## Competing spellings before correction

| Decorated spelling | Game files declaring it |
|---|---:|
| `?TheBfmeSecondManager@@3PAVBfmeDeletable@@A` | 1 |
| `?g_s4Made005F36D0@@3PAUS4Made00912580@@A` | 1 |

Macro-generated S4 declarations and the terrain-track guarded-call declaration are counted in their owning source. The raw contract log lists each counted path; counts decide no identity.

## Retail reads and writes

Readers:

- `?Gen_005f3140@@YAXXZ` at RVA `0x005F3140` (game/GameEngine/Source/Common/S3GlobalDeletes.cpp)
- `?d_005f31a0@@YAXXZ` at RVA `0x005F31A0` (game/gen_asm/d_005f31a0.asm)

Writers:

- `??0S4Publisher005F36D0@@QAE@XZ` at RVA `0x005F36D0` (game/GameEngine/Source/Common/S4CtorThenPublishNew.cpp)

## Refutation and verification

A different allocation target, a nonzero initial byte, a pointer adjustment between the published receiver and these accesses, an overlapping datum, or an indexed access beyond the verified extent would refute this storage/type correction. For a reference-derived name, a retail constructor/vtable or member contract inconsistent with that reference type would also refute it. An EA class-name discovery can improve the retained address-derived renderer types without changing the established datum ownership.

Raw evidence is in `build/rlink/pointer-globals-20261005/012F6DA4-retail.log`, `012F6DA4-routes.log`, `012F6DA4-source.log` and `012F6DA4-contract.log`. Retail log instructions and route logs preserve bytes and every observed five-byte E9 thunk through its final target. `reference-defs.log`, `selected-pins.log` and the constructor probes provide the supporting reference and pin extracts. The data-match and per-source Functions gates are recorded in `build/worker-final.md`; verified function bytes and function ledger rows remain unchanged.
