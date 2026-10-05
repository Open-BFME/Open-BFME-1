# Datum identity at VA 0x012F6DFC

The datum is `?TheGen012F6DFC@@3PAVGen0090F680@@A` in `game/GameEngine/Source/Common/S4CtorThenPublishNew.cpp`. A second owning pointer to the same 44-byte renderer-record type as 0x012F6D88. Its EA class name is unresolved; the existing Gen0090F680 type remains honest.

Retail has a 4-byte extent in `.data`, initialized to `00 00 00 00`. The PE base-relocation directory is absent (RVA and size both zero), and the initial value contains no pointer relocation. The complete range has no overlapping data row and no other DIR32 name strictly inside it. Alternative spellings at the start are preserved additively in the DIR32 ledger.

RVA 0x005F6590 allocates 0x2C bytes, directly calls constructor 0x0090F650 and stores EAX to this global. RVA 0x005F5500 passes the stored pointer in ECX to destructor 0x0090F680 before freeing it. The separate consumer at 0x005F5560 treats its +0x14 field as a texture handle and +0x18 as shader bits.

No Zero Hour class name is asserted. The shared constructor and destructor targets prove the two allocation views denote one pointee type. ctor-0090F650.log records all 48 constructor bytes.

## Receiver and argument contract

A scalar datum stores one 32-bit pointer. Loads passed in ECX are member receivers; stores publish the constructed or factory-returned pointer or clear it to zero. No wrapper, forwarder, inheritance relationship or second object identity is introduced. Existing locally modeled member-call ABIs remain unchanged through casts at their use sites.

## Competing spellings before correction

| Decorated spelling | Game files declaring it |
|---|---:|
| `?TheGen012F6DFC@@3PAVGen0090F680@@A` | 1 |
| `?g_s4Made005F6590@@3PAUS4Made0090F650@@A` | 1 |

Macro-generated S4 declarations and the terrain-track guarded-call declaration are counted in their owning source. The raw contract log lists each counted path; counts decide no identity.

## Retail reads and writes

Readers:

- `?Rva005F5500@@YAXXZ` at RVA `0x005F5500` (game/GameEngine/Source/Common/Open2Conv002.cpp)
- `?d_005f5570@@YAXXZ` at RVA `0x005F5570` (game/gen_asm/d_004e8320.asm)

Writers:

- `??0S4Publisher005F6590@@QAE@XZ` at RVA `0x005F6590` (game/GameEngine/Source/Common/S4CtorThenPublishNew.cpp)

## Refutation and verification

A different allocation target, a nonzero initial byte, a pointer adjustment between the published receiver and these accesses, an overlapping datum, or an indexed access beyond the verified extent would refute this storage/type correction. For a reference-derived name, a retail constructor/vtable or member contract inconsistent with that reference type would also refute it. An EA class-name discovery can improve the retained address-derived renderer types without changing the established datum ownership.

Raw evidence is in `build/rlink/pointer-globals-20261005/012F6DFC-retail.log`, `012F6DFC-routes.log`, `012F6DFC-source.log` and `012F6DFC-contract.log`. Retail log instructions and route logs preserve bytes and every observed five-byte E9 thunk through its final target. `reference-defs.log`, `selected-pins.log` and the constructor probes provide the supporting reference and pin extracts. The data-match and per-source Functions gates are recorded in `build/worker-final.md`; verified function bytes and function ledger rows remain unchanged.
