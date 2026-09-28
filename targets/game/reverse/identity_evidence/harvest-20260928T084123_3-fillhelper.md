# name_regression findings for 0x0019F890 fillHelper (seat 20260928T084123_3)

The deleted bank targets/game/reverse/attempts/0x0019f890.cpp (banked on master in
db31116051 while this seat was running; the seat never saw it) is paired with the
landed game/GameEngine/Source/GameLogic/Map/Rva0019F890FillHelper.cpp and, by the
deleted-to-added heuristic, with the seat's new stash for a DIFFERENT body,
targets/game/reverse/attempts/0x0019ff20.cpp.

1. `SideEntry0019F890 -> Rva001A0320Record` (both pairings). The same 0x18-byte
   record at +0x2C of Rva001A0320Owner is already named `Rva001A0320Record` by the
   matched caller game/GameEngine/Source/Common/Rva0019FD00Fill.cpp (line 39,
   `struct Rva001A0320Record`) and by the pinned mangled name in symbols.csv
   `?buildScriptData@Rva001A0320Owner@@AAEXPAURva001A0320Record@@PAVScriptList@@PAVRva0019A1D0Owner@@@Z,0x0003DC0D`.
   `SideEntry0019F890` existed only in the bank. The landed body adopts the name its
   matched caller already uses instead of adding a second name for one type.
2. `SidesList -> Rva00357800Owner` (landed source). Token-alignment artifact:
   `class SidesList` is still declared (Rva0019F890FillHelper.cpp line 49) and used
   (line 69, `SidesList *sides = ...->load(name)`); `Rva00357800Owner` was already a
   separate class in the bank and is still the ScriptList swap owner (line 76).
3. `swap -> j_00020d92` (landed source). Token-alignment artifact: `swap` is still
   called (line 76, `((Rva00357800Owner*)scripts)->swap(...)`). `j_00020d92` is the
   ILT thunk to the ScriptList clone constructor (functions.csv
   `?j_00020d92@@YAXXZ,,0x00020D92,5,...,gen-thunk;target=FUN_0075e3b0`, i.e. RVA
   0x0035E3B0, the constructor the bank reached as `??0Gen0035E3B0` via /alternatename).
4. `SidesList -> Rva00197AE0Temporary` (0x0019ff20 stash). Cross-body pairing
   artifact: the stash is 0x0019FF20, a different function that never held the
   0x0019F890 bank's text; `Rva00197AE0Temporary` is the fill temporary type the
   matched Rva0019FD00Fill.cpp already uses.
