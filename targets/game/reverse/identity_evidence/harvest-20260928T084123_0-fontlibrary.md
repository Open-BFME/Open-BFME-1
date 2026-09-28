# name_regression finding `FontLibraryBFMERetail -> Gen_00942BC0` (seat 20260928T084123_0)

Finding: `targets/game/reverse/attempts/0x006f4f50.cpp ->
game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayStringCheckForChangedTextData.cpp:
FontLibraryBFMERetail -> Gen_00942BC0`.

Not a rename; two different entities that the token diff aligned.

- The bank was a copy of the whole ZH W3DDisplayString.cpp (reset, notifyTextChanged,
  checkForChangedTextData, draw, getSize, getWidth, setFont, setClipRegion,
  computeExtents). Its private `class FontLibraryBFMERetail { GameFont *getFont(...); }`
  served only `W3DDisplayString::setFont` (bank line 418, `TheFontLibrary->getFont`).
- The landed source contains only checkForChangedTextData (retail 0x006F4F50), which
  never touches the font library, so the declaration was dropped, not renamed.
  FontLibraryBFMERetail stays the established name in the matched sources
  (game/GameEngine/Source/GameClient/GUI/FontLibraryBFMERetail_getFont.cpp and others).
- In its place the new source declares the callee at 0x00942BC0 under the name the
  ledger already gives that address: functions.csv row
  `?process@Gen_00942BC0@@QAEXPAX00@Z,,0x00942BC0,40,game/GameEngine/Source/Common/Gen_00942BC0.cpp,matched`.
  No new identity is introduced for it.
