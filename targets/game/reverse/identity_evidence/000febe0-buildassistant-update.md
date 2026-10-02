# BuildAssistant::update at 0x000FEBE0, EmotionSystem::update at 0x0037CAC0

Before this change the ledger had:

- 0x000FEBE0 (748 bytes): `?process@SellList000FEBE0@@QAEXXZ`, an
  address-derived name. Its header said the "established update method is
  separate".
- 0x0037CAC0 (1 byte, `C3`): `?update@BuildAssistant@@UAEXXZ`, with no
  evidence beyond its own comment: "GameLogic calls this virtual ... through
  vtable 0x010EA8D4 slot +0x14".

The construction code in GameEngine::init shows which table belongs to which
subsystem. Under that evidence the second name sits on the wrong class.

## GameEngine::init (retail 1.03, image base 0x400000)

Each subsystem is created by `new` + constructor, and the result is passed to
`initSubsystem<T>` with the literal name of its global:

| call site | `new` size | constructor (via ILT) | literal pushed | initSubsystem |
|---|---|---|---|---|
| 0x00079B22 | 0x14 | ILT 0x000463A8 -> 0x000FDA80 | 0x01076388 "TheBuildAssistant" | 0x00079B49 -> ILT 0x000014F1 -> 0x00074390 `??$initSubsystem@VBuildAssistant@@...`, global 0x012ED83C (`?TheBuildAssistant@@3PAVBuildAssistant@@A`) |
| 0x00079B68 | 0x20 | ILT 0x00023141 -> 0x0037CC20 | 0x01076374 "TheEmotionSystem" | 0x00079B8F -> ILT 0x00047C21 -> 0x00074450 `??$initSubsystem@VEmotionSystem@@...`, global 0x012F0878 |

The constructors install their tables at +0:

- 0x000FDA80: `call SubsystemInterface::SubsystemInterface` (0x009A1A30), then
  at 0x000FDAA5 `C7 06 D8 60 08 01` (`mov [esi], 0x010860D8`). The destructor at
  0x000FDB40 stores the same table.
- 0x0037CC20: `call SubsystemInterface::SubsystemInterface`, then at 0x0037CC2A
  `C7 06 D4 A8 0E 01` (`mov [esi], 0x010EA8D4`); the destructor at 0x0037CC50
  stores it too.

So 0x010860D8 is BuildAssistant's table and 0x010EA8D4 is EmotionSystem's.
The ledger already agrees that 0x010860D8 is BuildAssistant's:
`?sellObject@BuildAssistant@@UAEXPAVObject@@@Z` (0x001003C0) is its slot 18.
The EmotionSystem table sits among EmotionSystem bodies: `createEmotion`
0x0037CAD0, `findNugget` 0x0037CD70, `addNugget` 0x0037CF10.

The constructor 0x0037CC20 and the table's `??_G` at 0x0037CE80 are filed under
SupplyCenterProductionExitUpdateModuleData. That is a separate misnaming; this
change does not touch it.

## Slot 5 is `update`

In every SubsystemInterface table, slots 2 and 3 share
`SubsystemInterface::loadIniFilesFromLegend` and `postProcessLoad`, slot 4 is
`reset`, slot 5 is `update`, and slot 6 is the shared default `draw` (0x00067940).
Examples with independently named owners:
GameEngine (`reset` 0x0006E7A0, `update` 0x0006E910), PlayerList (0x000DF2B0,
0x000DF2D0), TerrainLogic (0x001ACF90, 0x001A2BE0), VictorySystem (0x001DE5B0,
0x001DFBA0), CDManager (0x00101C70, 0x00101C40), VictoryConditions, SidesList,
ScriptEngine (`update` 0x0034B9A0). This matches Zero Hour's SubsystemInterface
order (`init`, `postProcessLoad`, `reset`, `update`, `draw`) with BFME's
`loadIniFilesFromLegend` inserted at slot 2.

- Table 0x010860D8 slot 5 (+0x14) = ILT 0x0003FE72 -> **0x000FEBE0**.
- Table 0x010EA8D4 slot 5 (+0x14) = ILT 0x0002FAAE -> **0x0037CAC0**.

## The bodies agree

0x000FEBE0 walks the list at this+0x10. For each ObjectSellInfo it looks up the
object, removes stale entries, refunds the controlling player, shows
"GUI:AddCash", cancels production and kills the object. It deletes each entry
as it goes. This is Zero Hour's `BuildAssistant::update` sell-list loop (ZH
BuildAssistant.cpp, the update phase), with BFME's immediate refund. The list
at this+0x10 is the one `sellObject` and `xferTheSellList` use. 0x0037CAC0 is
a bare `ret`, EmotionSystem's empty update.

## Renames

- 0x0037CAC0: `?update@BuildAssistant@@UAEXXZ` -> `?update@EmotionSystem@@UAEXXZ`
- 0x000FEBE0: `?process@SellList000FEBE0@@QAEXXZ` -> `?update@BuildAssistant@@UAEXXZ`
