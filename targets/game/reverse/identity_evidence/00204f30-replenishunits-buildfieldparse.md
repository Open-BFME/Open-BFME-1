# ReplenishUnitsBehaviorModuleData::buildFieldParse at 0x00204F30

The 35-byte body at RVA 0x00204F30 (ret at +0x22) adds the table at VA
0x010A5D68 at offset 0, then UpgradeMuxData's table at VA 0x010898A0 at offset 8.
The first table holds seven rows and a NULL terminator:

| token | parser | offset |
| --- | --- | --- |
| `StartsActive` | `INI::parseBool` | 0x8C |
| `ReplenishDelay` | `INI::parseDurationUnsignedInt` | 0x88 |
| `ReplenishRadius` | `INI::parseReal` | 0x70 |
| `NoReplenishIfEnemyWithinRadius` | `INI::parseReal` | 0x74 |
| `ReplenishFXList` | `INI::parseFXList` | 0x78 |
| `ReplenishStatii` | thunk 0x00029B9A | 0x7C |
| `ReplenishHordeMembersOnly` | `INI::parseBool` | 0x8D |

The body's only reference is ILT 0x0002B1F7. The only reference to that thunk
is the `push 0x0042B1F7` at RVA 0x00117471, inside the module-data factory at
0x00117420. That factory allocates 0x90 bytes, constructs them through ILT
0x0003025B, which jumps to the matched `ReplenishUnitsBehaviorModuleData`
constructor at 0x00204ED0, and hands the thunk to `INI::initFromINIMultiProc`.
The factory sits next to the matched
`ReplenishUnitsBehavior::friend_newModuleInstance` at 0x001173A0, and retail
carries the module name string `ReplenishUnitsBehavior`.

So the body is `ReplenishUnitsBehaviorModuleData::buildFieldParse`. The old
name, `AutoHealBehaviorModuleData::buildFieldParse`, matched only because the
table address is a masked relocation. AutoHeal's real builder is 0x001298A0:
`AutoHealBehavior::friend_newModuleData` (0x00129E40) pushes its ILT
0x0003AF21, and its table at 0x0108EE60 holds HealingAmount, HealingDelay,
Radius and the other AutoHeal keys.
