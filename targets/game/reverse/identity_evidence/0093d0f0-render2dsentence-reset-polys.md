# 0x0093D0F0 Render2DSentenceClass::Reset_Polys (38 B)

Replaces the placeholder `?process@Gen_0093D0F0@@QAEXXZ`.

BFME 1 target evidence:
- symbols.csv pins `?Reset_Polys@Render2DSentenceClass@@QAEXXZ` at 0x0093D0F0
  from the matched `W3DGameWindow::drawText` (0x0078D6D0), whose direct call
  `m_textRenderer.Reset_Polys()` lands there (no ILT; ilt_oracle UNTESTABLE).
- Body: walk `Renderers` (array +0x38, count +0x44, 8-byte entries) and call
  matched `Render2DClass::Reset` (0x00934820) on each entry's renderer. This
  is WW3D2 render2dsentence.cpp `Reset_Polys`; retail calls Reset directly,
  so the vendored body's call is qualified (`Render2DClass::Reset`).

Link queue #101 (census bb53b24f2b, losers): the vendored body made a virtual
call and nothing rowed the name, so W3DGameWindowDrawText.cpp linked to it.
