# ??0ActiveBodyModuleData@@QAE@XZ — 0x0020F7C0, 230 bytes

The lift carried the name `??0ActiveBodyModuleData@@QAE@XZ`
(`game/GameEngine/Source/GameLogic/Object/Body/ActiveBodyModuleDataCtorThunk.cpp`,
a `__declspec(naked)` `__emit` copy of retail). Nothing in the body contradicts
it, and three independent lines of evidence fix the identity.

## 1. The vptr the body installs belongs to this class

`0x0060F7E5: mov dword ptr [esi], 0x010A76C0` is the only vptr store in the
body; there is no base-constructor call, so `ModuleData`'s own constructor is
inlined away (or trivial) in retail. The vtable at 0x010A76C0 has 17 slots and
its slot 0 is a destructor, and the only `.text` body that carries the constant
is this constructor. So the object is the most-derived type here and its vtable
belongs to it.

## 2. The FieldParse table at 0x00CA7AA8 is this class's, and it fixes every offset

Decoded from the retail image, that table pairs 17 INI keys with the offsets
this body writes. `targets/game/reverse/field_names.csv` already carries
`MaxHealth@0x8` and `InitialHealth@0xc` under `upstream_class =
ActiveBodyModuleData` from this same table (2 votes, margin 1), and the
remaining keys line up with the body's stores one for one:

| offset | key | what the body writes |
| --- | --- | --- |
| 0x08 | MaxHealth | `0` |
| 0x0C | InitialHealth | `-1.0f` (0xBF800000) |
| 0x10 | MaxHealthDamaged | `0` |
| 0x14 | MaxHealthReallyDamaged | `0` |
| 0x18 | DodgePercent | `0` |
| 0x1C | EnteringDamagedTransitionTime | `0` |
| 0x20 | EnteringReallyDamagedTransitionTime | `0` |
| 0x24 | RecoveryTime | `0` |
| 0x28 | UseDefaultDamageSettings | `1` (byte) |
| 0x2C | GrabObject | `set("EntThrownBuildingRock", 21)` |
| 0x30 | DamagedAttributeModifier | release/clear call |
| 0x34 | ReallyDamagedAttributeModifier | release/clear call |
| 0x38 | GrabFX | `0` |
| 0x3C | GrabDamage | `200.0f` |
| 0x40 | GrabOffset | `0`, `0` (its INI parser at 0x00C533E0 writes two floats) |
| 0x48 | HealingBuffFx | `0`, then the FXList lookup result |
| 0x4C | CheerRadius | `200.0f` |
| 0x50 | (not parsed) | three-word container, the 12-byte-stride vector of the destructor TU |

## 3. The lookup is the module's own healing-buff FX list

`0x0060F85E..0x0060F88E` reads `TheGlobalData` (0x012ED5C8) at +0xAA4, guards it
with the two inline string accessors (data pointer non-null, length word at +4
non-zero; then `m_data + 8` or the empty literal 0x0107388b), and calls the
FXList store at 0x012F144C. `field_names.csv` records +0xAA4 of GlobalData as
`DefaultUnitHealingBuffFxList` (321 votes), and the store result lands on 0x48,
the HealingBuffFx slot. The Zero Hour twin's `StructureBodyModuleData`
constructor
(`game/GameEngine/Source/GameLogic/Object/Body/StructureBodyModuleDataCtorThunk.cpp`)
compiles the same guard from the same global and is already byte-matched, so the
accessor spelling here is copied from a proven one.

## 4. Callers

Six call sites, all through ILT thunks, all of them constructors of classes that
derive from this one -- among them `ActiveBody::friend_newModuleData`
(ModuleFactory.cpp), `UpgradeModuleModuleData`, `StructureBodyModuleData` and
`FlightDeckBehaviorModuleData`. Each passes the pointer straight through with no
`lea`, the signature of a base constructor at offset 0, consistent with
evidence 1.

`targets/game/reverse/lift_arity.csv` row 144 already read this body as
arity-consistent, and the body returns `eax = this` (a non-void constructor),
which the lift did too.
