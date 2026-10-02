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
