# 0x001E74B0 is `??0WeaponTemplate@@QAE@XZ`, not `??0Weapon@@QAE@XZ`

The ledger row at 0x001E74B0 is a naked `__emit` lift named
`??0Weapon@@QAE@XZ` (`game/GameEngine/Source/GameLogic/Object/WeaponDefaultCtorThunk.cpp`).
The body proves the name is wrong; every independent line of evidence names
`WeaponTemplate`.

## 1. Vtable installed by the body (primary evidence)

`tools/vtable_lookup.py 0x010A1418` reports exactly two `.text` functions
carrying the constant 0x010A1418:

- `0x001E74B0` (this body) stores it as `mov dword ptr [esi], 0x010A1418`
  at +0x27 (the first store after the SEH registration).
- `0x001E7940` `??1WeaponTemplate@@MAE@XZ`, landed and matched at
  `game/GameEngine/Source/GameLogic/Object/WeaponTemplateDestructor.cpp`.

A constructor that installs the same vtable a matched destructor removes is
the constructor of that class. Class `Weapon` has its own, smaller vtable and
is not this class.

## 2. Callers name the returned type

The two call sites (from `tools/callees.py` / caller inventory) both route
through the incremental-link thunk at 0x0004456C to 0x001E74B0:

- `?newWeaponTemplate@WeaponStore@@IAEPAVWeaponTemplate@@VAsciiString@@...`
  (`game/GameEngine/Source/GameLogic/Object/Weapon.cpp`)
- `?newOverride@WeaponStore@@IAEPAVWeaponTemplate@@PAV2@@Z`
  (`game/GameEngine/Source/GameLogic/Object/WeaponStore_newOverride.cpp`)

Both are typed to return `WeaponTemplate *` and are matched. A matched caller
naming the symbol is the strongest identity evidence.

## 3. Body shape matches WeaponTemplate's layout

The 933-byte body constructs nine `AudioEventRTS` members (nine calls to
`??0AudioEventRTS@@QAE@ABVAsciiString@@H@Z` through ILT 0x00025306) and
initialises fields up to +0x534, matching the 0x53C-byte `WeaponTemplate`
whose destructor is already landed. Class `Weapon` is much smaller and has a
different member set.

## 4. ZH source

`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Weapon.cpp`
defines `WeaponTemplate::WeaponTemplate()` (line 255) and
`WeaponTemplate::~WeaponTemplate()` (line 333). BFME keeps the ZH skeleton and
adds fields; the destructor TU already uses that layout.

## Conclusion

Land under `??0WeaponTemplate@@QAE@XZ` at 0x001E74B0/933 with
`--replace-rva 0x001E74B0 --correct-identity '??0Weapon@@QAE@XZ'`.
