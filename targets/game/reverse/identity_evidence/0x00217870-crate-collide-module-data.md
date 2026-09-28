# 0x00217870 is CrateCollideModuleData's constructor, not ShroudCrateCollideModuleData's

## What the body is

`tools/dis_retail.py 0x00217870 147` is a module-data constructor with an SEH
frame whose only throwing step copies a narrow string. It installs vtable
`0x010AA378` and then initialises exactly eleven members, and every one of them
is recorded by name and offset in the retail FieldParse table at `0x00CAA4B0`
(`targets/game/reverse/field_names.csv` rows 2073-2083, and
`python3 tools/name_oracle.py --class CrateCollideModuleData --offset 0x8` answers
`m_kindof`, `--offset 0x20` answers `m_kindofnot`, `--offset 0x44` answers
`m_executionAnimationTemplate`; each at confidence 1.00):

| offset | member | retail initialiser |
|--------|--------|-------------------|
| +0x08 | `m_kindof` | six-dword clear (`BitFlags<192>`) |
| +0x20 | `m_kindofnot` | six-dword clear (`BitFlags<192>`) |
| +0x38 | `m_isForbidOwnerPlayer` | byte 0 |
| +0x39 | `m_isBuildingPickup` | byte 0 |
| +0x3A | `m_isHumanOnlyPickup` | byte 0 |
| +0x3C | `m_pickupScience` | `-1` |
| +0x40 | `m_executeFX` | 0 |
| +0x44 | `m_executionAnimationTemplate` | copy of the global empty `AsciiString` at `0x01336E50`, by a call to `StringBase<char>::StringBase<char>(const StringBase<char>&)` at `0x00887B60` |
| +0x48 | `m_executeAnimationDisplayTimeInSeconds` | 0 |
| +0x4C | `m_executeAnimationZRisePerSecond` | 0 |
| +0x50 | `m_executeAnimationFades` | byte 1 |

That is the member list of
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CrateCollide.h`'s
`CrateCollideModuleData`, in the same order, at the same offsets. Nothing in the
body is Shroud-specific: ShroudCrateCollideModuleData has no member the
CrateCollide base does not already have.

## The callers decide it

`python3 tools/callers_of.py 0x00217870` returns eight sites, and they split
cleanly into "derived class calls its base constructor" and "module-data factory
constructs the base directly":

* `??0UnitCrateCollideModuleData@@QAE@XZ` (0x00125EA0) calls it, then stores its
  own vtable `0x0108E8E8` and writes `+0x54`/`+0x58`. Its FieldParse entries put
  `m_unitCount` at +0x54 and `m_unitType` at +0x58
  (`field_names.csv` rows 798-799). The landed sibling
  `game/GameEngine/Source/GameLogic/Object/Collide/CrateCollide/UnitCrateCollideModuleDataCtorThunk.cpp`
  already declares `class UnitCrateCollideModuleData : public CrateCollideModuleData`.
* `?dup_00125fa0@@YAXXZ` (0x00125FA0, the ConvertToCarBomb module-data
  constructor) calls it, then stores vtable `0x0108E940` and writes +0x54/+0x58/+0x59/+0x5C.
* `??0Rva00126080ModuleData@@QAE@XZ` (0x00126080) calls it, then stores vtable
  `0x0108E998` and writes +0x54..+0x70.
* `?dup_00126f70@@YAXXZ` (0x00126F70, the Money module-data constructor) calls
  it, then stores vtable `0x0108EAA0` and writes +0x54, where
  `field_names.csv` row 797 puts `m_moneyProvided`.

A constructor that derived classes call as their base is the base's own
constructor.

The four `friend_newModuleData` factories settle the last doubt.
`?friend_newModuleData@ShroudCrateCollide@@SAPAVModuleData@@P` at 0x0011EDC0 is
`push 0x54; call operator new(0x54)` followed by `call ?j_000441ca` (the ILT
thunk to 0x00217870) and **no vtable store at all**: the object it allocates is
0x54 bytes -- the exact size of the class this body constructs -- and carries
this body's vtable. An empty derived class of its own would have needed its own
constructor body, and retail was linked without identical-COMDAT folding
(`python3 tools/one_identity.py`), so no such body exists in the image.

## What it retires

Four `functions.csv` rows claimed 0x00217870/147B, all pointing at
byte-identical `__declspec(naked)` `__emit` lifts of the same 147 bytes:

* `??0ShroudCrateCollideModuleData@@QAE@XZ` (the lift this conversion replaces)
* `??0HealCrateCollideModuleData@@QAE@XZ`
* `??0MoneyCrateCollideModuleData@@QAE@XZ`
* `??0ConvertToCarBombCrateCollideModuleData@@QAE@XZ`

The names came with the lifts, not with evidence. HealCrateCollide's
`friend_newModuleData` is not even in the caller list above, which is what
identical-COMDAT folding of the *empty derived classes* predicts. The real
identity is `??0CrateCollideModuleData@@QAE@XZ`, and this row is the only one
the body can carry.
