# 0x0024A350: `comment` is a `#pragma` keyword, not a name

name_regression paired the deleted bank
`targets/game/reverse/attempts/0x0024a350.cpp` with
`game/GameEngine/Source/GameLogic/Object/Contain/HordeSiegeEngineContainCreatePayload.cpp`
and reported `comment -> j_00004d63`. Nothing was renamed.

- The old bank bound its callees with
  `#pragma comment(linker, "/alternatename:?invoke@Rva0024A350MapCall@@QAEXPAVObject@@@Z=?j_00004d63@@YAXXZ")`
  (bank line 50) and five similar lines. `comment` there is the pragma
  keyword, not an identifier of the game.
- The landed source drops all `#pragma comment` alternatenames (0 remain) and
  calls the same ILT thunk directly: `extern void j_00004d63();` (line 36).
  `?j_00004d63@@YAXXZ` is the address-claimed ILT placeholder the old bank was
  already aliasing to, so the callee identity is unchanged.
- The function keeps its established name,
  `?createPayload@HordeSiegeEngineContain@@MAEXXZ` at 0x0024A350 (413 B,
  byte-verified `matched` in `targets/game/reverse/functions.csv`).
