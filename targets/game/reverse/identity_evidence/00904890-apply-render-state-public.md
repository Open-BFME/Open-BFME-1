# 0x00904890 DX8Wrapper::Apply_Render_State_Changes is public static (SAXXZ)

The 774-byte body at 0x00904890 was matched as
`?Apply_Render_State_Changes@DX8Wrapper@@CAXXZ` (private static) only because
the TU-local class shim in `DX8Wrapper_DrawPrimitives.cpp` declared it in a
private section. Retail code outside DX8Wrapper calls this exact address:

- matched `?setup@WaterShader007A6460@@QAEXPAD@Z` (0x007A6460, a WaterShader
  method, not a DX8Wrapper member or friend) calls 0x904890 once
  (`python3 tools/callees.py 0x007A6460 1268`);
- 55 authored TUs (W3DWater, W3DShaderManager, BaseHeightMap, W3DTreeBuffer,
  shdrenderer, ...) call `DX8Wrapper::Apply_Render_State_Changes()` from
  outside the class, as the Westwood `dx8wrapper.h` does (declared in its
  `public:` section, line 350 under `public:` at 258).

A private member could not be called from those classes, so the identity is
the public static decoration `?Apply_Render_State_Changes@DX8Wrapper@@SAXXZ`,
which symbols.csv already pins at 0x00904890. The duplicate upstream body in
`dxwrapper.cpp` (Zero Hour copy, not retail) is removed.
