# set_00710e30: unsigned char param corrected to bool (0x00710E30, 10 B)

Link queue row 9 (`?HighlightRendering@@3_NA` unresolved) is repaired by
defining the highlight-rendering datum once under its recorded retail name.
That repair forces one identity correction on the datum's owning setter.

## Facts established from BFME 1 target evidence

- Retail body at 0x00710E30 (10 B, unchanged extent):
  `8a 44 24 04  a2 2c f4 33 01  c3`
  = `mov al, [esp+4]; mov ds:0x0133F42C, al; ret` — a plain byte move from the
  stack parameter into the global, with no normalization.
- The datum is `?HighlightRendering@@3_NA` (bool) at VA 0x0133F42C:
  `targets/game/reverse/dir32_addresses.csv` line 6124 records that exact
  mangled name at that VA, and the matched consumers
  `ScreenFilterRva007D85C0PostRender.cpp`, `RTS3DSceneCustomizedRender.cpp`,
  `ScreenHilightFilterPostRender.cpp` and `W3DWater.cpp` reference it.
- MSVC 13.10.3077 codegen measured this session: `HighlightRendering = v;`
  with `unsigned char v` emits `84 c0 0f 95 c0` (`test al,al; setne al`)
  before the store — 4 bytes retail does not have. With `bool v` it emits
  exactly the retail 10 bytes. The retail body therefore proves the parameter
  was bool; the old `E` (unsigned char) mangling was the placeholder landing's
  guess, not target evidence.

## Identity correction

- Old row: `?set_00710e30@@YAXE@Z`, 0x00710E30, 10 B,
  `game/GameEngineDevice/Source/W3DDevice/GameClient/Gen_00710e30_SetGlobal.cpp`.
- New row: `?set_00710e30@@YAX_N@Z`, same RVA, same size, same source.
- The function name, address, extent, ABI (cdecl, one byte argument at
  [esp+4]) and body are unchanged; only the parameter's declared type is
  corrected to the codegen-proven bool.

## Related changes in the same repair

- `?HighlightRendering@@3_NA` defined once in the same TU and rowed in
  data_rows.csv at 0x0133F42C (1 B, retail zero-filled .data).
- Placeholder references renamed onto the recorded name:
  `g_00710e30` in `DX8Wrapper_DrawPrimitives.cpp`,
  `g_Va0133F42C` in `SmallLeafBodies2.cpp` (getter 0x006D1C10 unchanged
  signature and bytes).
