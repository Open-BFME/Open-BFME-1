# MapSelectMenu's SetDifficultyRadioButton at 0x004D1120

The 471-byte body at 0x004D1120 was landed as `?dup_004d1120@@YAXXZ`, with
`object-symbol=?SetDifficultyRadioButton@@YAXXZ`. It is compiled from
MapSelectMenu.cpp's Zero Hour helper `SetDifficultyRadioButton`, which looks up
"MapSelectMenu.wnd:MapSelectMenuParent" and one of the three
"MapSelectMenu.wnd:RadioButton*AI" windows from the script engine's global
difficulty.

Evidence for the caller:

- The FunctionLexicon row at VA 0x012A99A4 pairs the literal 0x01086CC0,
  "MapSelectMenuInit", with ILT 0x0000274D. That ILT jumps to 0x004D1370.
- MapSelectMenuInit (0x004D1370, 868 B) calls this body through ILT
  0x00019727 at +0x2B7. That is the same position as Zero Hour's
  `SetDifficultyRadioButton();` call in MapSelectMenuInit, between the two
  registerWithAnimateManager calls and the RadioButtonSystemMaps lookup.
- MapSelectMenuInit is landed in the same commit from the same source file,
  and it byte-matches.

Why the name carries a suffix:

- Zero Hour defines a function named `SetDifficultyRadioButton` in two files:
  - MapSelectMenu.cpp, where it has external linkage;
  - DifficultySelect.cpp, where it is `static`.
- Both mangle to `?SetDifficultyRadioButton@@YAXXZ`.
- The ledger already gives that name to DifficultySelect's copy at 0x004C6E70.
  It is matched, and the matched DifficultySelectInit calls it.
- A second row under that name would give one name two bodies. It would also
  resolve MapSelectMenuInit's call to 0x004C6E70, and the scoped gate refuses
  that.
- So this copy takes the menu suffix. `SetDifficultyRadioButtonMapSelectMenu`
  follows the same convention as `shutdownCompleteMapSelectMenu` in the same
  file.
- The bytes are unchanged, at 471/471 exact. Only the name changes, from an
  unproven `?dup_` alias to the identity proven by the caller.
