# 00C6BDA0 init: region bonus key at 0x012F4B88

Retail `?Rva00C6BDA0Init@@YAXXZ` (0x00C6BDA0, 27B, matched in
`game/GameEngine/Source/Common/StaticInit/Rva012F4B88Global.cpp`,
object-symbol `_$E1`) constructs the region bonus key `AsciiString
key012F4B88("LW:RegionLegendaryBonus")` at VA 0x012F4B88 and registers its
cleanup via `atexit`, mirroring the sibling initializers at 0x00C6BD40
(`key012F4B80`) and 0x00C6BD70 (`key012F4B84`).

Retail bytes: `push 0x110ab94` ("LW:RegionLegendaryBonus" literal);
`mov ecx,0x012F4B88`; `call j_00012c42` (AsciiString from `const char*`);
`push 0x1070290` (dtor forwarder); `call _atexit`.

The key is extern-declared and read only in
`game/GameEngine/Source/GameClient/GUI/PopupCountdown005868D0.cpp`
(`extern AsciiString key012F4B80,key012F4B84,key012F4B88;`); the TU above is
its only definition. The 4-byte `.data` datum at 0x012F4B88 is owned by this
TU's matched static initializer.
