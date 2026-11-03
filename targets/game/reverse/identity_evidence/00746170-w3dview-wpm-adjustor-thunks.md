# W3DView WPM adjustor thunks (s555)

Retail 0x00746170 and 0x00746180 are 11-byte this-adjusting entries
(`81 E9 FC 00 00 00` sub ecx,0xFC; `E9 rel32` jmp) referenced only by ILT
entries 0x00036D63 / 0x0003F995; nothing calls or jumps to their +6 bytes,
which earlier carried 5-byte gen-thunk scaffold rows (retired in
deleted_rows.csv).

- 0x00746170 jumps to ILT 0x00041191 -> scalar deleting destructor 0x007463F0.
  `ilt_oracle.py check` CONFIRMS (exact) ??_EW3DView@@WPM@AEPAXI@Z here and
  CONTRADICTS the protected spelling ??_EW3DView@@OPM@AEPAXI@Z. At 0x007463F0 it
  CONFIRMS ??_GW3DView@@UAEPAXI@Z / ??_EW3DView@@UAEPAXI@Z and CONTRADICTS the
  ledger's ??_GW3DView@@MAEPAXI@Z (left for a separate correction).
- 0x00746180 jumps to ILT 0x00014A38 -> ?reset@W3DView@@UAEXXZ (0x0073AC90).
  `ilt_oracle.py check` CONFIRMS (exact) ?reset@W3DView@@WPM@AEXXZ.

0xFC = `WPM@`: the SubsystemInterface base of W3DView sits at +0xFC, and
reset is declared in both View and SubsystemInterface (ZH View.h /
SubsystemInterface.h), which is what makes MSVC emit the reset adjustor.
W3DViewAdjustorThunks.cpp models only that offset and those overrides; the
thunk's REL32 names ??_EW3DView@@UAEPAXI@Z, the weak external that defaults to
??_G in the same object, so the ??_E pin sits on the ILT entry the thunk jumps
to (same recipe as 00711ed0-rts-scene-adjustor-deleting-dtor-aliases.md).

pin-identity-override: ??_EW3DView@@UAEPAXI@Z 0x00041191 caller=0x00746170 the WPM adjustor thunk 0x00746170 (W3DViewAdjustorThunks.cpp) jumps via ILT 0x00041191 to 0x007463F0 through the weak alias ??_E that defaults to ??_GW3DView in the same object
