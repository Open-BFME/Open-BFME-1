# BridgeBehavior seat: two false name pairings

name_regression reported two renames to `Rva000EE6D0StringAccessor`. Neither
is a rename: `Rva000EE6D0StringAccessor` is an EXISTING ledger class
(`?getString@Rva000EE6D0StringAccessor@@QAE?AVAsciiString@@XZ`, 0x000EE6D0,
32 B, matched, `game/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarObserver.cpp`),
which the new BridgeBehavior sources declare so they can call it.

## `InGameUI -> Rva000EE6D0StringAccessor`

Cross-file pairing of the deleted lift `InGameUI_addSuperweapon_Thunk.cpp`
with the new `BridgeBehaviorResolveFX.cpp`. The lift was replaced by
`game/GameEngine/Source/GameClient/InGameUIAddSuperweapon.cpp`, which still
declares `class InGameUI` (line 71) and defines `InGameUI::addSuperweapon`
(line 83); ledger row `?addSuperweapon@InGameUI@@UAEXHABVAsciiString@@W4ObjectID@@PBVSpecialPowerTemplate@@@Z`
at 0x0044C970. The name `InGameUI` is retained.

## `BridgeAreaEffectsRandomPositionShim -> Rva000EE6D0StringAccessor`

`targets/game/reverse/attempts/0x001f38a0.cpp` (bank for
`BridgeBehavior::update`, 0x001F38A0) was the whole 1,532-line ZH
BridgeBehavior.cpp; `BridgeAreaEffectsRandomPositionShim` (old bank line 581)
is used only inside `BridgeBehavior::doAreaEffects` (old lines 602-629), a
different function. The rewritten bank is trimmed to `update` alone (117
lines) and neither declares nor calls that shim; its pin
(`?pick@BridgeAreaEffectsRandomPositionShim@@...`, `symbols.csv`, 0x000406FB)
is untouched. No name was replaced.
