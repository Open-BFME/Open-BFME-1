# WW3D::Set_Render_Device (0x008FD120) and WW3D::Set_Device_Resolution (0x008FD1C0) return bool

The rows carried Zero Hour's `WW3DErrorType` return in their mangled names. Retail's
bodies only produce an 8-bit value, so the return type is `bool`.

* **Body tails.** Each body forwards its arguments to the DX8Wrapper overload with the
  same parameters, then ends `add esp,N / test al,al / setne al / ret`. Nothing widens
  AL into EAX. MSVC 7.1 has no underlying-type syntax for native enums (error C3177),
  so a function returning an int-sized `WW3DErrorType` always widens the result with
  `movzx` or a `neg/sbb`. Earlier verdicts on both addresses stopped at exactly this
  residue (re_attempts: 0x008FD120 51/54 bytes, 0x008FD1C0 "bool-to-enum return tail").
* **Callers read only AL.** Both named callers of 0x008FD120 consume a byte:
  `W3DDisplay::init` (0x006ED5B0) compares it with `cmp al,1`, and `Reset_D3D_Device`
  (0x006E7D70) tests AL. Their sources had forced this with `(unsigned char)` and
  `(char)` casts on the enum. Declared `bool`, both callers stay byte-exact with no
  casts.
* **Prior pin.** reverse/symbols.csv already pinned 0x008FD1C0 as
  `?Set_Device_Resolution@WW3D@@SA_NHHHH_N@Z` for the same reason.
* **Source shape.** `bool success = DX8Wrapper::...(...); return success ? true : false;`
  compiles byte-exact for both bodies, keeping ZH's `success` local.

The class, method names and parameter lists are unchanged from Zero Hour. Only the
return type changes.
