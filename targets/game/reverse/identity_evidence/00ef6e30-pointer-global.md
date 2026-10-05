# Datum identity at VA 0x012F6E30

The datum is `?g_rva005F7FA0Resource@@3PAVStreakLineClass@@A` in `game/GameEngine/Source/Common/S4CtorThenPublishNew.cpp`. An owning StreakLineClass pointer for a ref-counted renderer resource. The global retains its existing resource role.

Retail has a 4-byte extent in `.data`, initialized to `00 00 00 00`. The PE base-relocation directory is absent (RVA and size both zero), and the initial value contains no pointer relocation. The complete range has no overlapping data row and no other DIR32 name strictly inside it. Alternative spellings at the start are preserved additively in the DIR32 ledger.

RVA 0x005F8540 allocates 0x1A0 bytes and directly calls StreakLineClass constructor 0x0091A730 before storing EAX here. That constructor invokes RenderObjClass at 0x009204B0, installs vtables at 0x0113AD28 and 0x0113AD20 and constructs SegLineRendererClass at +0x104 and StreakRendererClass at +0x154. RVA 0x005F7FA0 decrements the dword reference count at pointee +4, calls virtual slot zero at count zero, and clears the global.

The matched ??0StreakLineClass@@QAE@XZ row at RVA 0x0091A730 and the Zero Hour Libraries/Source/WWVegas/WW3D2/streak.cpp constructor establish the pointee. ctor-0091A730.log includes the complete 207-byte constructor through RET at +0xCE.

## Receiver and argument contract

A scalar datum stores one 32-bit pointer. Loads passed in ECX are member receivers; stores publish the constructed or factory-returned pointer or clear it to zero. No wrapper, forwarder, inheritance relationship or second object identity is introduced. Existing locally modeled member-call ABIs remain unchanged through casts at their use sites.

## Competing spellings before correction

| Decorated spelling | Game files declaring it |
|---|---:|
| `?g_rva005F7FA0Resource@@3PAVRefCountClass@@A` | 1 |
| `?g_s4Made005F8540@@3PAUS4Made0091A730@@A` | 1 |

Macro-generated S4 declarations and the terrain-track guarded-call declaration are counted in their owning source. The raw contract log lists each counted path; counts decide no identity.

## Retail reads and writes

Readers:

- `?d_005f8010@@YAXXZ` at RVA `0x005F8010` (game/gen_asm/d_004e8320.asm)
- `?releaseRva005F7FA0Resource@@YAXXZ` at RVA `0x005F7FA0` (game/GameEngine/Source/Common/RefCountedGlobalReleases.cpp)

Writers:

- `??0S4Publisher005F8540@@QAE@XZ` at RVA `0x005F8540` (game/GameEngine/Source/Common/S4CtorThenPublishNew.cpp)
- `?releaseRva005F7FA0Resource@@YAXXZ` at RVA `0x005F7FA0` (game/GameEngine/Source/Common/RefCountedGlobalReleases.cpp)

## Refutation and verification

A different allocation target, a nonzero initial byte, a pointer adjustment between the published receiver and these accesses, an overlapping datum, or an indexed access beyond the verified extent would refute this storage/type correction. For a reference-derived name, a retail constructor/vtable or member contract inconsistent with that reference type would also refute it. An EA class-name discovery can improve the retained address-derived renderer types without changing the established datum ownership.

Raw evidence is in `build/rlink/pointer-globals-20261005/012F6E30-retail.log`, `012F6E30-routes.log`, `012F6E30-source.log` and `012F6E30-contract.log`. Retail log instructions and route logs preserve bytes and every observed five-byte E9 thunk through its final target. `reference-defs.log`, `selected-pins.log` and the constructor probes provide the supporting reference and pin extracts. The data-match and per-source Functions gates are recorded in `build/worker-final.md`; verified function bytes and function ledger rows remain unchanged.
