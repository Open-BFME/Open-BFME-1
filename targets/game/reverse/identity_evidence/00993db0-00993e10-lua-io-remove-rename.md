# 0x00993DB0 and 0x00993E10 are liolib.c's io_remove and io_rename

Both rows were Open-BFME5 C++ copies in
`game/GameEngine/Source/Common/BfmeConv1367.cpp`
(`?bfmeGoVHR@@YAHPAUBfmeLuaVHR@@@Z`, `?bfmeGoVHS@@YAHPAUBfmeLuaVHR@@@Z`) over
an opaque `BfmeLuaVHR`, calling `remove`/`rename` under invented import
names. Meanwhile liolib.c compiled its own upstream io_remove/io_rename, which
retail does not contain, so a real link ran non-retail code for both
bindings (`python3 tools/component_link.py lua`: MISMATCH at both addresses).

Evidence:

- Retail's `iolib[]` table, liolib.c's own `.rdata` placed at 0x00D3FFA0 by
  the relocations of matched liolib code, holds `{"remove", 0x00993DB0}` at
  0x00D40030 and `{"rename", 0x00993E10}` at 0x00D40038. The name strings are
  read from retail at the pointers stored beside them.
- Both addresses sit inside liolib.c's run of rows, between `_io_execute`
  (0x00993D70) and `_io_tmpname` (0x00993E80), the upstream source order.
- With upstream's bodies using retail's fixed error tuple (`pushresult_close`,
  as io_open/io_write/io_seek/io_flush already do), liolib.c compiles to
  retail's 92 and 109 bytes, and the `remove`/`rename` calls read retail's
  MSVCR71 `remove`/`rename` IAT slots.

The names are upstream Lua 4.0.1's; the ledger spells liolib statics as
`_io_<name>`.
