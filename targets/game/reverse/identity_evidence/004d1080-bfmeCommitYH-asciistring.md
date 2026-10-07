# 0x004D1080 takes a real AsciiString by value

- The body at 0x004D1080 (117 B) receives a by-value StringBase<char> and
  releases it with the inline AsciiString destructor (direct call to
  ?releaseBuffer@?$StringBase@D@@AAEXXZ, 0x00887940); retail has no separate
  destructor body for a derived parameter type.
- Its caller MapSelectMenu.cpp (MapSelectMenuSystem 0x004D1C40) calls it as
  ?bfmeCommitYH@@YAXVAsciiString@@@Z, the spelling symbols.csv pins at
  0x004D1080.
- The old ?bfmeCommitYH@@YAXVAsciiStringYH@@@Z spelling made VC7.1 emit a
  ??1AsciiStringYH@@QAE@XZ COMDAT that is not retail's body (link census
  verdict "wrong"). With AsciiString the bytes are unchanged (byte gate).
