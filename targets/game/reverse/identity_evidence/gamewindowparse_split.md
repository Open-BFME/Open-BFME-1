# GameWindowManagerScript split: GameWindowParse is not renamed

The lift seat of 2026-09-27 moved the parse-window lift out of
`GameWindowManagerScript.cpp` into `GameWindowManagerScriptParseWindow.cpp` as
real C++ (gpt-6-astra, byte-exact). `name_regression` pairs the two files and
reports `GameWindowParse -> Gen_004791e0`.

No identifier was renamed: the new file still declares `struct
GameWindowParse` and `extern GameWindowParse gameWindowFieldList[]` and uses
them. `Gen_004791e0` is a different symbol the body now calls by its existing
ledger name: `?m@Gen_004791e0@@QAEHXZ`, the 7-byte getter at 0x004791E0
(game/gen_small/fun_003.cpp).
