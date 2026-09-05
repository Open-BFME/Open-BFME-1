// ?postRender@ScreenBWFilterDOT3@@MAE_NW4FilterModes@@AAUCoord2D@@AA_N@Z
// partial score=0.35 date=2026-09-05
// PARTIAL / NOT BYTE-VERIFIED. Banked evidence for retail 0x007D1610 (924 B).
// Strong identity hypothesis: ScreenBWFilterDOT3::postRender (declared, and marked
// present-unmatched, in W3DShaderManager.cpp lines 761-847). The callee list matches
// that source almost exactly once one alias is accounted for:
//
//   0x0003FAC6 x1  bfmeEndRenderToTexture       -> W3DShaderManager::endRenderToTexture()
//   0x0000AE5C x1  j_0000ae5c (FUN_0045c600)    -> same unresolved helper as 0x007D0CE0
//   0x009F6E38 x1  __ftol2                      -> (Int)((1.0f-m_curFadeValue)*255.0f)
//   0x0001321E x2  Set_DX8_Render_State          -> the two D3DRS_TEXTUREFACTOR calls
//                                                   (one per branch of
//                                                   Get_Current_Caps()->Support_Dot3())
//   0x000261E3 x11 Set_DX8_Texture_Stage_State    -> 7 (DOT3 branch) + 3 (else branch)
//                                                   + 1 (D3DTSS_ALPHAOP SELECTARG2) = 11
//   0x000173C3 x1  "BaseHeightMapScorchSetShader" -> SAME ILT thunk address as
//                                                   ?Set_Shader@DX8Wrapper@@SAXABVShaderClass@@@Z
//                                                   (both pinned in reverse/symbols.csv
//                                                   at 0x000173C3 -- an ICF alias, not
//                                                   two different callees). Matches
//                                                   DX8Wrapper::Set_Shader(shader) call
//                                                   for the ShaderClass::_PresetAlphaShader
//                                                   with Set_Depth_Compare(PASS_ALWAYS).
//   0x00904890 x1  Apply_Render_State_Changes     -> the single Apply_Render_State_Changes()
//                                                   after Set_Shader, matches count x1.
//
// This accounts for every REL32 callee in the brief's list, in the same order as the
// ZH-derived source reads top to bottom. The DOT3-support branch test reads a global
// bitfield/byte at [g_currentCaps+0x272] off a pointer cached at 0x01340578 (not yet
// pinned) instead of a virtual Get_Current_Caps()->Support_Dot3() call -- consistent
// with BFME inlining that capability check to a flat byte read.
//
// UNRESOLVED (why this is banked, not landed) -- same open items as 0x007D0CE0, which
// shares this body's early shape verbatim (endRenderToTexture / early-out / set(mode)
// shared tail, then TheTacticalView getOrigin/getWidth/getHeight at 0x012F1600 vtable
// slots 0x4c/0x3c/0x44, then the reciprocal-multiply FP block reading 1.0f from
// 0x01075334 and 0.5f from 0x0107533C through a 4th parameter pointer instead of
// TheDisplay->getWidth()/getHeight()). Confirming FUN_0045c600 and that 4th parameter
// should let both this body and 0x007D0CE0 land together -- do the smaller one
// (0x007D0CE0, 665 B) first, the FP block is identical machinery.
//
// Additional globals seen only in this larger body: 0x013071A8 (fmul divisor near the
// end of the FP block) and 0x01084068 (fmul multiplicand) -- both unidentified,
// likely more display/viewport-derived float constants or cached reciprocals.
//
// Vertex/device/view vtable model is identical to 0x007D0CE0's (see that stash file
// for the full slot table: Device@0x01340534 slots 0x104/0x164/0x14c, TacticalView
// @0x012F1600 slots 0x4c/0x3c/0x44), plus the BFME_SET_RS/BFME_SET_TSS raw-vtable
// convention at slots 0xE4 and 0x10C already proven in FlatShroudTextureShaderReset.cpp.
