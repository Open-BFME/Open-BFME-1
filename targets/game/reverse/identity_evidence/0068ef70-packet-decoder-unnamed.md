# 0x0068EF70: LAN packet game-info decoder, identity unproven

`ParseGameOptionsString` (0x00690490) calls ILT 0x00048702 -> 0x0068EF70 at
+0x1B1 on its packet path as a cdecl `bool (GameInfo *, char *buffer, UnsignedInt length)`.
0x0068EF70 is a 1881-byte body still filed as the gen dump `?d_0068ef70`.

The name is address-keyed (`Rva0068EF70ParseBuffer`) because nothing proves a real one:
- `ParseAsciiStringToGameInfo` (the banked stash's name) is Zero Hour's options-STRING
  parser (`LANGameInfo.cpp`). It takes an AsciiString, not a raw buffer and length.
- `_parseGameInfoFromBuffer` (the router worker's name) was invented to describe the
  call site. The worker's own pin note says so.

Rename to a real name once a matched caller or a string or vtable witness names it.
