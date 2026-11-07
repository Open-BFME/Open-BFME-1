# 0x006C43F0: radar object-list renderer, Color third parameter

Retail 0x006C43F0, 1296 bytes. It ends in `ret 0Ch` (thiscall, three stack arguments). The extent is the same as the retired MASM row.

Old row: `?renderObjectList@W3DRadar@@IAEXPBVRadarObject@@PAVTextureClass@@_N@Z`, from `W3DRadar_renderObjectList.asm`.
New row: `?renderObjectListRva006C43F0@W3DRadar@@IAEXPBVRadarObject@@PAVW3DRadarResetTexture@@H@Z`, from `W3DRadar_renderObjectList.cpp`.

## BFME 1 target evidence

**The role is supported.** The body is Zero Hour's `W3DRadar::renderObjectList` with BFME additions:
- the walk over the RadarObject list
- the `getShroudedStatus` / `getRadarPriority` skip tests
- the `DrawPixel` four-pixel plot
- the stealth-colour helper 0x006C42B0
- the DISGUISER blob and blip helpers 0x006C2A20 and 0x006C2DD0

Its only caller is the matched 0x006C4A50 (`?method@Rva006C4A50Owner@@QAEXHHHHH@Z`, BFME's radar draw). That caller calls it twice: once with the object list at `this+0x10` and once with the local object list at `this+0x14`. Both calls pass the texture at `this+0x1488`. This is the same call pair Zero Hour's `W3DRadar::draw` makes.

**The third parameter is a Color, not a Bool.**
- 0x006C4A50 passes its `color` argument as that third argument. It passes the same `color` to `Rva006C0890(0xff000000, color)` and `Rva006C0890(0xff323232, color)`.
- 0x006C43F0 forwards its third argument unchanged as the second argument of `Rva006C0890`. That callee is the matched packed-colour multiplier `Color Rva006C0890(Color, Color)` (`?Rva006C0890@@YAHHH@Z`).
- Measured with the probe: declaring the parameter `bool` while the callee keeps its recorded `(Color, Color)` signature makes the compiler insert a zero-extension, giving 325 byte diffs. The `int`/Color spelling is EXACT.

So the old decoration's `_N` is wrong for BFME. Zero Hour's `Bool calcHero` was replaced by a colour modulation.

**The full decorated name is unproven.** `tools/ilt_oracle.py check` contradicts every decoration tried at this address (p_false 1.3e-4). The tried decorations combine:
- classes: `W3DRadar`, `Radar`, `Rva006C4A50Owner`
- access: `QAE`, `IAE`, `AAE`, `UAE`, `MAE`, `EAE`
- first parameter: `PBVRadarObject@@`, `PAVRadarObject@@`, `PAX`, `PBX`
- texture: `PAVTextureClass@@`, `PAVW3DRadarResetTexture@@`, `PAVTextureBaseClass@@`, `PAVSurfaceClass@@`, `PAX`
- third parameter: `_N`, `H`, `I`, `W4Bool@@`

The old name was already in `ilt_contradicted_baseline.txt`.

The new name therefore keeps the supported role, the W3DRadar `this` layout and the recorded texture view, and carries the address. Its texture view is `W3DRadarResetTexture`, the recorded owner of the callee `getSurfaceLevel` at 0x0090E670. That is the same typing as the caller's call-view pin, `?renderObjectList@Rva006C4A50Owner@@QAEXPAXPAVW3DRadarResetTexture@@H@Z`.

## Donor and reference

Zero Hour (`GeneralsMD/.../W3DRadar.cpp`) is the structural reference only. BFME 2 did not contribute to this recovery.
