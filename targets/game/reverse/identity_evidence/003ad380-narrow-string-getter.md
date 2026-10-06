# 003AD380: by-value narrow string getter at +0x28

The complete retail body is 32 bytes at RVA 003AD380 (padding follows to
003AD3A0, the next 32-byte getter in the same run). It is a thiscall const
getter returning a string by value: the hidden return slot is the one stack
argument (`ret 4`), `ecx + 0x28` is pushed as the source, the EH state word is
zeroed, and the only call goes to 0x00887B60.

0x00887B60 is `??0?$StringBase@D@@AAE@ABV0@@Z`, the narrow `StringBase<char>`
copy constructor (functions.csv row, StringBase.cpp). The copied member is
therefore a narrow string, and the body has the same shape as the landed
`?bfmeGet@Gen006372D0@@QBE?AVAsciiString@@XZ` (Bfme7NarrowStringGetter.cpp,
member at +0x78).

## Why the old row is wrong

The old row `?dup_003ad380@@YAXXZ` used GameInfoWindow.cpp's emitted COMDAT
`?getName@GameSlot@@QBE?AVUnicodeString@@XZ` as its object symbol (a ZH
"exact-multi" twin). Retail's GameSlot::getName is the 32-byte body at
0x003879C0 (LANGameInfoSlotLookup.cpp), which copies a WIDE string through
`StringBase<unsigned short>`'s copy constructor. GameInfoWindow's copy calls
`??0UnicodeString@@QAE@ABV0@@Z` instead, so link_census judges it a wrong copy
of GameSlot::getName, and the link can select it for every caller of that
name. Retail had no identical-COMDAT folding, so 0x003AD380 is not GameSlot's.

## Identity

Not recovered. No direct caller reaches 0x003AD380 (`callers_of.py`). The
class is named for its address (`Rva003AD380`) and its member for its offset
(`rva28`); only the narrow string type and the +0x28 offset are claimed.
