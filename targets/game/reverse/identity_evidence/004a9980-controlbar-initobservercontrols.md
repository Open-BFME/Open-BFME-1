# 0x004A9980 ControlBar::initObserverControls (679 B)

Identity correction: the row was the naked `__emit` lift `??1ControlBar@@UAE@XZ` in
`ControlBarDestructorThunk.cpp` (deleted). The body is
`?initObserverControls@ControlBar@@QAEXXZ`.

## BFME 1 target evidence
- `ilt_oracle.py check ?initObserverControls@ControlBar@@QAEXXZ 0x004A9980`: CONFIRMED
  (exact); `??1ControlBar@@UAE@XZ` is CONTRADICTED there.
- An earlier verdict already refuted the destructor name (SEH GUI window-lookup routine,
  no teardown) and noted that ControlBarObserver.cpp's initObserverControls is the 679-byte
  body here, not 0x004A9CD0 (now the matched ControlBar::populateObserverList).
- Retail literals are exactly Zero Hour's: `ControlBar.wnd:ObserverPlayerInfoWindow`,
  `...ObserverPlayerListWindow`, `...ButtonPlayer%d`, `...StaticTextPlayer%d`,
  `...StaticTextNumberOfUnits`, `...NumberOfBuildings`, `...NumberOfUnitsKilled`,
  `...NumberOfUnitsLost`, `...StaticTextPlayerName`, `...WinFlag`,
  `...WinGeneralPortrait`, `...ButtonCancel` (checked in the retail image).
- Boundary: SEH prologue, single RET at +0x2A6; 679 bytes.
- The Zero Hour body, unchanged, compiles exact in the TU's existing context
  (ControlBarObserver.cpp, beside the matched populateObserverList and
  ControlBarObserverSystem, which share its file statics).

## Donor evidence (BFME 2, 59e3f8f825)
- `Code/GameEngine/Source/GameClient/GUI/Rva0050DE39Observer.cpp`
  `?initObserverControls@ControlBar@@QAEXXZ` (BFME 2 0x0050DE39, 597 B, matched there)
  carries the same Zero Hour statement sequence.
