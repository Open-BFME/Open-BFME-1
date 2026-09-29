# 0x00455F60 positionStartSpots (AsciiString overload), 1069 B

Claimed as `?positionStartSpots@@YAXVAsciiString@@QAPAVGameWindow@@PAV2@PAVGameWindow@@Z`
-- retail 0x00455F60, 1069 bytes, byte-verified from
`game/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/PositionStartSpotsBFME.cpp`.

## Arity and the first three parameters

The matched GameInfo overload at 0x004564A0
(`?positionStartSpots@@YAXPAVGameInfo@@QAPAVGameWindow@@PAV2@_N@Z`,
game/GameEngine/Source/GameClient/GUI/PositionStartSpotsGameInfo.cpp) reaches this
body through ILT thunk 0x0003D901 and pushes, in order, `AsciiString` (built by
`??0AsciiString@@QAE@ABV0@@Z` into the argument slot), its own `buttonMapStartPositions`,
`mapWindow` and its own fourth argument. So the AsciiString overload takes
`(AsciiString, GameWindow *[], GameWindow *, X)`.

Five more call sites of the same ILT thunk push four words each, so the arity is
four and not three:

| call site | containing body | 4th word pushed |
|---|---|---|
| 0x004564A0+0x7E | `?positionStartSpots@@YAXPAVGameInfo@@...` (matched) | its own 4th argument |
| 0x004D0D10 | `?LanMapSelectMenuSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z` (matched) | `ebp` (zero) |
| 0x004D0E16 | same | `eax` = `_winMapPreview` region reload (zero) |
| 0x004F1B44 | `?WOLPositionStartSpots@@YAXXZ` (matched) | `0` immediate |
| 0x00504A0E | `?d_00504600@@YAXXZ` (gen-dump, byte-true) | `ebx` |
| 0x00504B1F | same | `ebx` |

The Zero Hour twin in
`inputs/reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/SkirmishGameOptionsMenu.cpp:663`
is the three-argument form of the same function (`AsciiString mapName,
GameWindow *buttonMapStartPositions[], GameWindow *mapWindow`), with the same
map-cache lookup, the same `getMapPreviewImage` / `positionAdditionalImages` /
`positionStartSpotControls` sequence and the same MAX_SLOTS hide loop. BFME added
the fourth argument, the `APT:MapTitle` commit and renamed `UnknownMap` to
`MissingMap` (the literal at 0x010F6310 is "MissingMap"). That is the whole
difference between the two sources, so the function identity is the Zero Hour
`positionStartSpots` and not a new BFME-only helper.

## The fourth parameter is a GameWindow *, not a Bool

`targets/game/reverse/symbols.csv` pins
`?positionStartSpots@@YAXVAsciiString@@QAPAVGameWindow@@PAV2@_N@Z` at the thunk
0x0003D901, and the three caller TUs declare the fourth parameter `Bool`. Retail's
own bytes contradict that spelling, so this row does not repeat it:

* +0x001F `mov ebx, dword ptr [esp + 0x13c]` then +0x0028 `cmp ebx, edi`: the
  fourth word is read and compared as a full dword against zero. Measured on
  this machine: declaring the parameter `Bool` makes MSVC 7.1 emit
  `mov bl, byte ptr [esp + 0x13c]` / `test bl, bl` and the body grows to 1087
  bytes against retail's 1069, first divergence at +0x001F.
* +0x0033 `push ebx; call 0x0040A3DF` -> ILT 0x0000A3DF -> 0x004B7880
  `GadgetListBoxReset(GameWindow *listbox)` (matched,
  game/GameEngine/Source/GameClient/GUI/Gadget/GadgetListBox.cpp:2677), guarded
  by that same `cmp ebx, edi`.
* +0x03C2 `push ebx; call 0x0043FE86` after pushing `1, -1, -1, -1`:
  `GadgetListBoxAddEntryText(listbox, mmd.getDescription(), -1, -1, -1, TRUE)`.

One word, read whole, tested for null and passed to two `GameWindow *` APIs. It
is a list box; the `Bool` spelling in the pin and in the caller declarations is
an over-claim about a parameter retail reads as a pointer. Every mapped call
site happens to pass zero, so both list-box calls are dead in the shipped game
and no call site can settle the type on its own -- only the body can, and it
says pointer.

The name therefore keeps the proven function name and the proven first three
parameter types and spells the fourth as the pointer retail reads. The thunk pin
at 0x0003D901 is left alone: it routes the six call sites' relocations and its
`_N` spelling is their business, not this body's.

## Names inside the body

Only two names are claimed here and both are address-derived or copied from a
matched row:

* `errorListBox` -- the fourth parameter, named for the two list-box calls it
  reaches. `tools/name_oracle.py` was not consulted for it because the name
  describes the witnessed use, not an invented class or member.
* `g_Rva012F15EC` / `g_Rva012F15E8` -- the two function-local statics that cache
  the "MissingMap" image on the map-not-found path (+0x0089) and the
  preview-image-missing path (+0x0212). They are named for the addresses they
  occupy; the Zero Hour source spells the same statics
  `static const Image *unknownImage`.

`MapMetaData` keeps retail's layout because the matched copy constructor
(0x000C1240) and destructor (0x00078540) witness it, and the tail padding after
the player records is load-bearing: it sets the frame size retail allocates
(`sub esp, 0x110`). `m_unmodelledFC` is a pad word added to reach that size; it
is not a field the body reads.

## Verification

`tools/probe.py` reports EXACT (modulo relocation slots), ours = 1069 = retail,
74 relocation sites. The one structural difference found while writing it -- the
map-found branch evaluated `mmd.bfme_getDisplayName()` before constructing the
`AsciiString("APT:MapTitle")` temporary, giving 1071 bytes -- is the named-local
form the matched sibling at 0x00520920
(game/GameEngine/Source/GameClient/GUI/AptMapPreviewSetMapTitle.cpp) already
uses, and the two agree byte for byte.
