# 0x0081D600 LineTable callback identity

The bank previously called this body `parseLineTable@SubtitleManager`. That owner and decorated method name were estimates, not independent identity evidence. The bank now uses `Rva0081D600ParseLineTable` so the unproven owner remains address-qualified.

Evidence:

- `targets/game/reverse/ghidra_functions.csv:46678` records a 341-byte function at `0x0081D600` under the generic name `FUN_00c1d600`; it does not identify a C++ owner.
- `targets/game/reverse/string_xrefs.tsv:7872-7873` ties both the missing-SubtitleManager diagnostic and the LineTable range/increasing-value diagnostic to `0x0081D600`. This supports the LineTable parser role, not `SubtitleManager` member ownership.
- `targets/game/reverse/field_names.csv:4360-4364` names `LineTable` at offset `+0x24` in the table at `0x00D2CDA0`. It identifies a field, not the callback address or its declaring C++ type.
- `targets/game/reverse/string_xrefs.tsv:7874` and `game/GameEngine/Source/GameClient/parseSubtitle.cpp:4-7,73-89` identify the distinct `parseSubtitle` callback at `0x0081D7C0`; it is not evidence for the C++ owner of `0x0081D600`.

The available independent evidence supports the callback's role but does not establish the old class qualification or exact decorated name. This correction removes that unsupported identity claim; it does not assert that class membership is impossible.
