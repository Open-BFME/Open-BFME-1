# 0x0043DBE0 InGameUI::setRadiusCursor takes four arguments

Retail facts (BFME 1.03):

- The body ends `ret 0x10` (four stack dwords on a `__thiscall`), and its caller in
  InGameUI::setGUICommand (0x0043AE68) pushes four dwords before `call [edx+0x118]`.
- The fourth argument is a byte read at the end (`mov al,[esp+0x2c]`) that selects the
  decal tint 0xFFFFFFFF / 0xFFFF1414.
- `tools/ilt_oracle.py check '?setRadiusCursor@InGameUI@@UAEXW4RadiusCursorType@@PBVSpecialPowerTemplate@@W4WeaponSlotType@@_N@Z' 0x43DBE0`
  prints CONFIRMED (exact, p_false 2.61e-04); the three-argument Zero Hour decoration the
  row carried is contradicted by the same ILT slot 0x0003F2CE.

Structure (Zero Hour InGameUI.cpp setRadiusCursor) is the semantic guide; the extra
argument's meaning beyond "tint selector" is not established, so it keeps a neutral name.
