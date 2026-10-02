# DamageModuleInterface slots 0 and 1: onDamage and onHealing

## Binary and independent owner evidence

All addresses below are RVAs unless explicitly marked VA. Read with pefile and
Capstone from `inputs/baselines/bfme1/retail-1.03-unpacked/files/lotrbfme.exe`,
SHA-256 `1fbdc0ced8f283732c094c4f0804ce8dc1e3e3675b720bcab066c94fed964e75`.

`module_registry.tsv` identifies BoneFXDamage's registered instance factory at
0011E800, its registration site 0012FA58, and constructor 00250740. The factory
calls ILT 00005B19, which resolves to that constructor. The constructor's final
stores install primary table VA 010B1FB4, behavior table VA 010B1EF0 at +0x0C,
and damage table VA 010B1EDC at +0x10. The earlier +0x10 store installs the
abstract table VA 010A1BFC, whose three entries are pure virtual. The primary
table's slot 2 is ILT 00049B61 -> getter 00250790 returning the literal
`BoneFXDamage`; thus ownership does not depend on a guessed destructor name.

## Slot mapping and exact-name witness

GeneralsMD `Code/GameEngine/Include/GameLogic/Module/DamageModule.h:46` declares
exactly three virtual callbacks, in this order: `onDamage(DamageInfo*)`,
`onHealing(DamageInfo*)`, `onBodyDamageStateChange(const DamageInfo*,
BodyDamageType, BodyDamageType)`. The BFME table has three entries followed by
zero. Slot 2 is independently matched BoneFXDamage::onBodyDamageStateChange
at 00250940 (ILT 00048CE8). The constructor's abstract three-slot table and
this nontrivial third-slot twin anchor the same interface and order.

GeneralsMD `BoneFXDamage.h:58-59` explicitly defines **both** public, non-const,
virtual overrides as empty bodies. These are class-specific definitions, not
inherited callbacks. Their BFME table entries and boundaries are:

| Owner | Slot | Table-entry VA | ILT RVA | Body RVA | Bytes | Name |
|---|---:|---|---|---|---|---|
| BoneFXDamage | 0 | 010B1EDC | 000373F3 | 002507A0 | C2 04 00 | onDamage |
| BoneFXDamage | 1 | 010B1EE0 | 0001FE29 | 002507B0 | C2 04 00 | onHealing |

GhidraMCP read_memory at VA 010B1EDC independently returned
`f373430029fe4100e88c440000000000`, agreeing with the retail file.
Each ILT is a five-byte E9 branch directly to the listed body. Searching the
complete mapped retail image for each ILT VA as a little-endian dword yields
exactly the single table-entry VA above. Each body is a complete `ret 4`,
followed immediately by INT3 alignment through the next 16-byte boundary.
There are no calls or accesses to `this`. The return and argument cleanup
agree with the witnessed void return and single DamageInfo pointer argument.
The names are `?onDamage@BoneFXDamage@@UAEXPAVDamageInfo@@@Z` and
`?onHealing@BoneFXDamage@@UAEXPAVDamageInfo@@@Z`.

## Correction and verification

The old `Rva002507A0Body::body(int)` and `Rva002507B0Body::body(int)` definitions
only described the stack cleanup; they did not assert a historical identity.
Replace them with the existing upstream inline methods emitted by
`game/GameEngine/Source/GameLogic/Object/Damage/BoneFXDamage.cpp`, retaining
the exact three-byte extents. No shared header or ABI pin changes are needed.
Each replacement must pass the decorated-symbol byte verification separately.

The staged-source audit also exposed five pre-existing orphan definitions in
AddressTinyBodies.cpp. Remove these duplicate, unledgered copies as required
to retire the two callback placeholders cleanly. The authoritative rows are
already elsewhere: RVAs 00891AB0, 008AB800, 008BD000 and 008F8E60 in
AddressTinyBodiesD0083FDF0.cpp, and 0083FE30 (`basic_streambuf<wchar_t>::pubsync`)
in stlport_wide_streambuf_xsgetn.cpp. No ledger claim or name at these five
addresses changes.

## TransitionDamageFX: the same two slots

Registered factory 0011E880 (registration 0012FA95, literal VA 0108FCD8)
calls ILT 0003F526 -> constructor 00252F50. Its last vtable stores are
primary VA 010B265C, behavior VA 010B2598 at +0x0C, and damage VA 010B2588
at +0x10. The earlier +0x10 store is the identical three-pure-virtual abstract
table VA 010A1BFC used by BoneFXDamage. Primary slot 2 is ILT 00007725 ->
00252FD0, a six-byte getter returning that `TransitionDamageFX` literal.
Thus both the registered factory route and an independent primary-table
getter prove this class owns the damage table.

| Owner | Slot | Table-entry VA | ILT RVA | Body RVA | Bytes | Name |
|---|---:|---|---|---|---|---|
| TransitionDamageFX | 0 | 010B2588 | 0001F1CC | 00252FE0 | C2 04 00 | onDamage |
| TransitionDamageFX | 1 | 010B258C | 0003A418 | 00252FF0 | C2 04 00 | onHealing |

Slot 2 is ILT 00001ABE -> 002525E0, followed by zero at VA 010B2594.
Each of the slot-0/1 ILT VAs occurs exactly once as a dword in the complete
mapped retail image, at the listed entry. Both are E9 stubs directly to the
listed three-byte `ret 4` body; INT3 starts immediately after each body.
GeneralsMD `TransitionDamageFX.h:254-256` explicitly declares this class's
empty public virtual `onDamage(DamageInfo*)` and `onHealing(DamageInfo*)`
overrides immediately before its body-damage-state callback. These class-specific
ZH twins, the same abstract interface table, and the proven BoneFXDamage slot
mapping supply the exact method identities and ABI. No inherited-body claim
is made. Use the existing TransitionDamageFX.cpp TU, which includes that
upstream header, and remove the two retired AddressTinyBodies.cpp definitions.
The manglings are `?onDamage@TransitionDamageFX@@UAEXPAVDamageInfo@@@Z` and
`?onHealing@TransitionDamageFX@@UAEXPAVDamageInfo@@@Z`.

## FireWeaponWhenDamagedBehavior: slot 1

Its registered instance factory 00116F30 calls ILT 0002A379 -> constructor
001FB5D0. Unlike the simpler damage modules above, this class seats its
DamageModuleInterface at **+0x28**: the constructor first writes abstract
table VA 010A1BFC at 001FB63F, then final table VA 010A3DD4 at 001FB666.
Its primary table is VA 010A3F04 (store 001FB652); primary slot 2 is ILT
0004B4D9 -> 001FB1E0, returning literal VA 010909A4,
`FireWeaponWhenDamagedBehavior`. The registered factory route and literal
getter independently establish ownership.

The damage table is three entries followed by zero:

| Slot | ILT RVA | Body RVA | Method |
|---|---|---|---|
| 0 | 00008C8D | 001FB930 | matched onDamage |
| 1 | 0001FB81 | 001FB230 | onHealing |
| 2 | 0001FD11 | 001FB240 | onBodyDamageStateChange |

The slot-1 stub VA appears exactly once in the complete mapped image, at
VA 010A3DD8, and E9 resolves directly to 001FB230. Its entire body is
`C2 04 00`, followed by INT3. GeneralsMD FireWeaponWhenDamagedBehavior.h:127
explicitly defines public virtual non-const `void onHealing(DamageInfo*) {}`.
Thus the same proven damage-interface order, matched slot-0 method, unique
stub and class-specific ZH twin prove
`?onHealing@FireWeaponWhenDamagedBehavior@@UAEXPAVDamageInfo@@@Z`.
Retire the stdcall placeholder in Rva001FB230Ret4.cpp and add the method to
the existing class view in FireWeaponWhenDamagedBehavior_onDamage.cpp.
No field layout or existing method changes are needed.
