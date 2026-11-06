# Logic time scale at VA 0x012A72A4

The decorated identity `?g_012A72A4@@3MA` (C++ `float g_012A72A4`) owns
4 bytes at VA 0x012A72A4 in retail `.data`. Retail holds `00 00 80 3F`
(1.0f) there (read via `reloc_ledger.Image.read`), matching the in-tree
definition's initializer `= 1.0f`.

- Defined in `game/GameEngine/Source/Common/GameEngineFramePacing.cpp`,
  the TU that reads it through `#define LogicTimeScale g_012A72A4`
  (`_bfme_updateNetworkAndLogic` compares `LogicTimeScale < One` with
  `One` = 1.0f).
- `game/GameEngine/Source/Common/GameEngine_execute.cpp` reads the same
  address through a hard-coded `(*(float *)0x012A72A4)` spelling; it keeps
  that spelling (a named extern there changes its generated code) and is
  untouched.

The name is address-derived: no caller, string, or cross-reference proves
an EA name; the float's role (logic time scale, default 1.0f) comes from
its sole reader's comparison.

## Extent and all users

`sizeof` 4 bytes at VA 0x012A72A4 as proven by the data gate. Sole
DIR32 consumer is `_bfme_updateNetworkAndLogic` in GameEngineFramePacing.cpp.
