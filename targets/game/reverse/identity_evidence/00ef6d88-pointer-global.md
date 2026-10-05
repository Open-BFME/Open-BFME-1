# Datum identity at VA 0x012F6D88

The datum is `?TheGen012F6D88@@3PAVGen0090F680@@A` in `game/GameEngine/Source/Common/S4CtorThenPublishNew.cpp`. An owning pointer to the 44-byte non-polymorphic renderer record constructed at RVA 0x0090F650 and destroyed at RVA 0x0090F680. Its actual EA class name is unresolved; the existing address-derived Gen0090F680 type is retained. The two independent globals at 0x012F6D88 and 0x012F6DFC hold instances of this same type, not one shared object.

Retail has a 4-byte extent in `.data`, initialized to `00 00 00 00`. The PE base-relocation directory is absent (RVA and size both zero), and the initial value contains no pointer relocation. The complete range has no overlapping data row and no other DIR32 name strictly inside it. Alternative spellings at the start are preserved additively in the DIR32 ledger.

The publisher at RVA 0x005F2D80 allocates 0x2C bytes, directly calls 0x0090F650 with ECX equal to the allocation, and stores EAX at 0x012F6D88. The shutdown helper at 0x005F0D10 loads this address into ECX and directly calls 0x0090F680, then frees the same allocation. Constructor stores zero at offsets 0..0x14, additive sprite shader bits at 0x18 and four float ones at 0x1C..0x28. The consumer at 0x005F1370 edits the texture handle at 0x14 and shader at 0x18.

No Zero Hour class is asserted. The constructor and destructor pins establish the address-derived allocation and cleanup views; ctor-0090F650.log records the complete 48-byte constructor.

## Receiver and argument contract

A scalar datum stores one 32-bit pointer. Loads passed in ECX are member receivers; stores publish the constructed or factory-returned pointer or clear it to zero. No wrapper, forwarder, inheritance relationship or second object identity is introduced. Existing locally modeled member-call ABIs remain unchanged through casts at their use sites.

## Competing spellings before correction

| Decorated spelling | Game files declaring it |
|---|---:|
| `?TheGen012F6D88@@3PAVGen0090F680@@A` | 1 |
| `?g_s4Made005F2D80@@3PAUS4Made0090F650@@A` | 1 |

Macro-generated S4 declarations and the terrain-track guarded-call declaration are counted in their owning source. The raw contract log lists each counted path; counts decide no identity.

## Retail reads and writes

Readers:

- `?Rva005F0D10@@YAXXZ` at RVA `0x005F0D10` (game/GameEngine/Source/Common/Open2Conv002.cpp)
- `?d_005f1370@@YAXXZ` at RVA `0x005F1370` (game/gen_asm/d_004e8320.asm)

Writers:

- `??0S4Publisher005F2D80@@QAE@XZ` at RVA `0x005F2D80` (game/GameEngine/Source/Common/S4CtorThenPublishNew.cpp)

## Refutation and verification

A different allocation target, a nonzero initial byte, a pointer adjustment between the published receiver and these accesses, an overlapping datum, or an indexed access beyond the verified extent would refute this storage/type correction. For a reference-derived name, a retail constructor/vtable or member contract inconsistent with that reference type would also refute it. An EA class-name discovery can improve the retained address-derived renderer types without changing the established datum ownership.

Raw evidence is in `build/rlink/pointer-globals-20261005/012F6D88-retail.log`, `012F6D88-routes.log`, `012F6D88-source.log` and `012F6D88-contract.log`. Retail log instructions and route logs preserve bytes and every observed five-byte E9 thunk through its final target. `reference-defs.log`, `selected-pins.log` and the constructor probes provide the supporting reference and pin extracts. The data-match and per-source Functions gates are recorded in `build/worker-final.md`; verified function bytes and function ledger rows remain unchanged.
