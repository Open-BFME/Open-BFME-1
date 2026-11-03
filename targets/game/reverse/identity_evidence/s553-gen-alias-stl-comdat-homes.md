# Gen-alias STL COMDAT homes replaced by their callers' own instantiations (s553)

Each row below was a `?dup_` gen-alias home: the retail body's bytes were
borrowed from a COMDAT another TU emits under a different instantiation's
name. Retail was linked without identical-COMDAT folding, so each address
has exactly one identity.

## Facts from BFME 1 retail, per row

- A matched C++ row in the named source calls the address (directly or via
  its ILT thunk); that source already emits a COMDAT of the same size whose
  bytes equal retail outside relocation slots (relocations are then verified
  by add_match/build.sh).
- `tools/ilt_oracle.py check NAME RVA` CONFIRMS the decorated name at the
  address (exact slot window; a wrong name fits by chance ~6e-4).

These are byte and thunk-table facts; the element/key types come from the
caller TUs' existing (Zero Hour or address-derived) declarations.

| RVA | bytes | previous row | source | name |
|---|---|---|---|---|
| 0x00062110 | 45 | `?dup_00062110@@YAXXZ` (game/GameEngine/Source/Common/System/SubsystemLegend.cpp) | game/GameEngineDevice/Source/Win32Device/Common/Win32BIGFileSystem_vectorFillInsert.cpp | `??$__uninitialized_copy@PAVAsciiString@@PAV1@@_STL@@YAPAVAsciiString@@PAV1@00ABU__false_type@0@@Z` |
| 0x000FDE20 | 45 | `?dup_000fde20@@YAXXZ` (game/GameEngine/Source/GameClient/GUI/Shell/ShellMenuSchemeManager_parseImagePart_Thunk.cpp) | game/GameEngine/Source/GameClient/DrawableReaction0041EBD0.cpp | `?push_back@?$list@PAVDrawable@@V?$allocator@PAVDrawable@@@_STL@@@_STL@@QAEXABQAVDrawable@@@Z` |
| 0x00129270 | 59 | `?dup_00129270@@YAXXZ` (game/Libraries/Source/WWVegas/WWLib/RvaTreeCopy001373D0.cpp) | game/Libraries/Source/WWVegas/WWLib/RvaTreeCopy001373D0.cpp | `?_M_erase@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@VAudioEventRTS@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@VAudioEventRTS@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@VAudioEventRTS@@@_STL@@@3@@_STL@@AAEXPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@VAudioEventRTS@@@_STL@@@2@@Z` |
| 0x0013F870 | 40 | `?dup_0013f870@@YAXXZ` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLWelcomeMenu.cpp) | game/GameEngine/Source/Common/Thing/ThingTemplate_parseArbitraryFXIntoMap.cpp | `??$make_pair@VAsciiString@@PBVFXList@@@_STL@@YA?AU?$pair@VAsciiString@@PBVFXList@@@0@ABVAsciiString@@ABQBVFXList@@@Z` |
| 0x00194FD0 | 40 | `?dup_00194fd0@@YAXXZ` (game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/WOLWelcomeMenu.cpp) | game/GameEngine/Source/GameLogic/Map/CachedSidesLoader0019EC80.cpp | `??$make_pair@VAsciiString@@PAVSidesList@@@_STL@@YA?AU?$pair@VAsciiString@@PAVSidesList@@@0@ABVAsciiString@@ABQAVSidesList@@@Z` |
| 0x001B6880 | 71 | `?dup_001b6880@@YAXXZ` (game/GameEngine/Source/Common/RTS/Player.cpp) | game/GameEngine/Source/GameLogic/Object/Locomotor.cpp | `??$find@W4NameKeyType@@@?$_Rb_tree@W4NameKeyType@@U?$pair@$$CBW4NameKeyType@@PAVLocomotorTemplate@@@_STL@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@PAVLocomotorTemplate@@@_STL@@@3@U?$less@W4NameKeyType@@@3@V?$allocator@U?$pair@$$CBW4NameKeyType@@PAVLocomotorTemplate@@@_STL@@@3@@_STL@@QBE?AU?$_Rb_tree_iterator@U?$pair@$$CBW4NameKeyType@@PAVLocomotorTemplate@@@_STL@@U?$_Const_traits@U?$pair@$$CBW4NameKeyType@@PAVLocomotorTemplate@@@_STL@@@2@@1@ABW4NameKeyType@@@Z` |
| 0x002D8760 | 97 | `?dup_002d8760@@YAXXZ` (game/GameEngine/Source/GameNetwork/GameSpy/Thread/PersistentStorageThread.cpp) | game/Libraries/Source/WWVegas/WWLib/MoneyPutCharString.cpp | `??$_M_range_initialize@PBD@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@AAEXPBD0ABUforward_iterator_tag@1@@Z` |
| 0x00384FD0 | 120 | `?dup_00384fd0@@YAXXZ` (game/GameEngine/Source/Common/RTS/Player.cpp) | game/GameEngine/Source/GameLogic/System/GameLogic.cpp | `??$__find@PAPAVObject@@PAV1@@_STL@@YAPAPAVObject@@PAPAV1@0ABQAV1@ABUrandom_access_iterator_tag@0@@Z` |
| 0x0040CDC0 | 45 | `?dup_0040cdc0@@YAXXZ` (game/GameEngine/Source/GameClient/GUI/Shell/ShellMenuSchemeManager_parseImagePart_Thunk.cpp) | game/GameEngine/Source/GameClient/CreditsAddText0040D540List.cpp | `?push_back@?$list@PAVCreditsLine@@V?$allocator@PAVCreditsLine@@@_STL@@@_STL@@QAEXABQAVCreditsLine@@@Z` |
