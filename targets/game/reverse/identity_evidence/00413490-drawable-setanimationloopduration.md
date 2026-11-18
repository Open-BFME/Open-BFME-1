# 0x00413490 Drawable::setAnimationLoopDuration

Previously `?bfmeSubDAll1158@BfmeOwner1158@@QAEXPAVBfmeArg1158@@@Z` (placeholder,
BfmeConv1158.cpp). Now `?setAnimationLoopDuration@Drawable@@QAEXI@Z` in
DrawableBFME.cpp.

BFME 1 target evidence:
- 53 B thiscall, `ret 4`: walks the draw-module list at `this+0x150` (the same
  field DrawableBFME.cpp's matched Drawable members walk), calls slot 39
  (`+0x9c`, getObjectDrawInterface) and forwards the argument to slot 24
  (`+0x60`).
- Slot 24 of the W3DModelDraw object-draw vtable is
  `W3DModelDraw::setAnimationLoopDuration` (0x0075C760, matched row).
- Callers: `BattlePlanUpdate::setStatus` (0x00286440, matched) calls ILT
  0x000478CA -> 0x00413490 six times on `obj->getDrawable()`, at the six places
  Zero Hour's BattlePlanUpdate::setStatus calls
  `getDrawable()->setAnimationLoopDuration(...)`;
  `BuildAssistant::sellObject` 0x001003C0 +0x114 does the same with `push 7`.
- symbols.csv already pins `?setAnimationLoopDuration@Drawable@@QAEXI@Z` at ILT
  0x000478CA -> 0x00413490.

Donor/reference: Zero Hour `GeneralsMD/Code/GameEngine/Source/GameClient/Drawable.cpp`
Drawable::setAnimationLoopDuration (same loop; ZH reaches the list through
getDrawModules()). The sibling at 0x00413530 (slot 25, `+0x64`) matches ZH's
setAnimationCompletionTime and is left under its placeholder for now.

Link-queue row #5 (census 6c4dd9e650): BattlePlanUpdateSetStatus.cpp referenced
the real name, which no ledger row defined.
