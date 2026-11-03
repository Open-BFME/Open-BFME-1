# 0x00621600 GameInfoToAsciiString (843 B)

Identity correction: the row was the naked `__emit` lift `?isSandbox@GameInfo@@QAE_NXZ`
in `GameInfo.cpp`. The body is `?GameInfoToAsciiString@@YA?AVAsciiString@@PBVGameInfo@@_N@Z`.

## BFME 1 target evidence
- `ilt_oracle.py check ?GameInfoToAsciiString@@YA?AVAsciiString@@PBVGameInfo@@_N@Z 0x621600`:
  CONFIRMED (p_false 7.18e-04, exact). The pinned ILT 0x0000E70A (symbols.csv, "Skirmish
  SlotList formatter ILT") jumps here.
- Callers reach it through ILT 0x0000E70A: RecorderClass::startRecording and
  SkirmishPreferences::setSlotList (earlier verdicts in re_attempts.log).
- Retail strings are the Zero Hour GameInfo.cpp formatter's: `M=%3.3x%s;MC=%X;MS=%d;SD=%d;`,
  `H%s,%X,%d,%c%c,%d,%d,%d,%d,%d:`, `C%c,%d,%d,%d,%d:`, `O:` / `X:`.
- Boundary: RET at +0x34A, INT3 after; 843 bytes. A `bool` second argument gates the slot
  names (the BFME signature; Zero Hour's has one argument).
- Nothing in `game/` calls `GameInfo::isSandbox` as the non-virtual `QAE` member except the
  unmatched Zero Hour ScoreScreen.cpp copy; BFME declares isSandbox virtual elsewhere.

## Donor evidence (BFME 2, 45afcff3)
- `Code/GameEngine/Source/GameNetwork/GameSlotApparent.cpp` GameInfoToAsciiString (0x00400AF8,
  827 B, matched there). Its note that retail reads the connection record's ip/port as plain
  members while the other fields go through getters is the lever that closed the last 34
  bytes here; the BFME 2 body itself differs (GSID/GT/SI/GR header, hero byte).

## Structural inference
- The body lives in GameInfoParseOptions.cpp, beside the matched ParseAsciiStringToGameInfo
  (0x00621C40), sharing its BFME GameSlot/GameInfo view.
