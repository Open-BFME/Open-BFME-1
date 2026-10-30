# WW3D device-setter family 0x008FD0E0 / 0x008FD110 / 0x008FD160

BFME 1 target evidence (retail 1.03 unpacked):

- `ww3d.cpp` unit order in retail: Set_NPatches_Level 0x008FD080 (matched),
  0x008FD0E0 (44 B), 0x008FD110 (11 B), Set_Render_Device(int,...) 0x008FD120
  (matched, 54 B), 0x008FD160 (11 B), Get_Window 0x008FD170 (matched). This is
  the Zero Hour `ww3d.cpp` order: Set_Render_Device(const char *),
  Set_Any_Render_Device, Set_Render_Device(int), Set_Next_Render_Device,
  Get_Window.
- Each body calls exactly the DX8Wrapper method of the same name:
  0x008FD0E0 -> `?Set_Render_Device@DX8Wrapper@@KA_NPBDHHHH_N@Z` 0x0090B850
  (six forwarded args), 0x008FD110 -> `Set_Any_Render_Device` 0x0090B7E0,
  0x008FD160 -> `Set_Next_Render_Device` 0x0090B410.
- All three end `test al,al; setne al; ret`, the same tail as the matched
  `?Set_Render_Device@WW3D@@SA_NHHHHH_N00@Z` 0x008FD120 (`success ? true :
  false`). Zero Hour's WW3DErrorType mapping (OK=0) would invert the result,
  so BFME returns bool for these as it does for the int overload. No caller
  of the enum form exists in `game/`.
- Not ILT-testable (library region); identity rests on unit order plus the
  unique same-name callee.

0x008FD0E0 was previously landed under the opaque
`?setRenderDeviceChecked@Rva008FD0E0Wrapper@@SA_NPBDHHHH_N@Z`; it is renamed
to `?Set_Render_Device@WW3D@@SA_NPBDHHHH_N@Z` in ww3d.cpp.
