# 0x007171F0 W3DShaderManager::startRenderToTexture body: MASM dump to C++

Retail 0x007171F0, 445 bytes, RET at +0x1BC followed by INT3 padding. The row
moves from the MASM dump `?Rva007171F0@@YAXXZ`
(`game/masm_dumps/Rva007171F0RenderToTexture.asm`) to clean C++
`?start@W3DShaderManagerStartRenderToTextureShim@@SAXXZ` in
`game/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManagerStartRenderToTexture.cpp`.

## BFME 1 target facts

- symbols.csv already pins `?start@W3DShaderManagerStartRenderToTextureShim@@SAXXZ`
  to 0x007171F0. The matched 5-byte static entry
  `?startRenderToTexture@W3DShaderManager@@SAXXZ` at ILT 0x000154E7
  (`game/GameEngine/Source/Common/ExactStaticThunks.cpp`) forwards to this
  address, and the render filters in W3DShaderManager.cpp call it. The row
  takes the existing pinned name, so no pin changes.
- Every data reference resolves to an existing recorded symbol:
  `W3DShaderManager::m_renderingToTexture` (0x012F9D00),
  `m_newRenderSurface` (0x012F9D0C), `m_oldDepthSurface` (0x012F9D10),
  `m_currentFilter` (0x012F9CFC), `DX8Wrapper::D3DDevice` (0x01340534),
  `DX8Wrapper::render_state_changed` (0x0133F49C),
  `ShaderClass::_PresetOpaqueSolidShader` (0x012D6E38),
  `Rva01340EC4Material` (0x01340EC4), `TheWritableGlobalData`
  (0x012ED5C8) and `TheBfmeGlobal_012f7fe0` (0x012F7FE0).
- Calls go to `Set_Render_Target(IDirect3DSurface8*, bool)`, to
  `Set_DX8_Render_State` (ILT 0x0001321E), to `Set_Shader` (ILT 0x000173C3),
  to `VertexMaterialClass::Get_Preset`, to `bfmeDrawFilterUV(int, int, Coord2D*)`
  (ILT 0x000196A0) and to the seven-argument `DX8Wrapper::Clear`. All of these
  names are already pinned or matched.

## Reference source

The Zero Hour `W3DShaderManager::startRenderToTexture` (GeneralsMD
W3DShaderManager.cpp) has the same control flow and the same shader and
material sequence. BFME adds the TestCooperativeLevel guard, a three-argument
blit with a (1,1) UV scale and the FT_VIEW_DEFAULT clear. Open-BFME-2
`Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShaderManager.cpp`
(`startRenderToTexture`) gives the same BFME structure and was used for
comparison only.

## Byte result

The 0.991 bank kept four register-swap bytes at +0x11C..+0x132 for many
sessions. Three source changes give an exact build: 445 bytes and 26
relocations.

1. The blit's scale is a temporary built in the argument list rather than a
   union slot filled before the call. This puts the address in ECX and the
   opacity global in EDX.
2. The shader local sits in a nested scope. Its slot at -0x14 is then free
   for the scale temporary, as in retail.
3. Both clears pass the opacity through its inline getter, so its return
   temporary keeps retail's stack copy at -0x14.

The material swap needs `__forceinline` (WWINLINE) on `Set_Material`.
