// ?postRender@ScreenDefaultFilter@@MAE_NW4FilterModes@@AAUCoord2D@@AA_N@Z
// partial score=0.3 date=2026-09-05
// PARTIAL / NOT BYTE-VERIFIED. Banked evidence for retail 0x007D0CE0 (665 B).
// Disassembly (capstone, see build/sonnet/quickcap.py) shows this is a close sibling
// of ScreenDefaultFilter::postRender (W3DShaderManager.cpp lines 392-441) and of the
// larger 0x007D1610 body (ScreenBWFilterDOT3::postRender hypothesis, also banked).
//
// Confirmed object/vtable model from the disassembly (shared with 0x007D1610):
//   - "this" (edi) is a filter object: vtable+0x14 = virtual set(mode) (bool ret);
//     vtable+0x18 = virtual reset(void); called at the very end. Matches
//     W3DFilterInterface's set()/reset() slots used throughout W3DShaderManager.cpp.
//   - REL32 0x0003FAC6 = W3DShaderManager::endRenderToTexture() (still a dump; pinned
//     "?bfmeEndRenderToTexture@@YAPAXXZ"), called first; null check shares its "return
//     false" tail with the set(mode)==false path (one fall-through tail, see
//     docs/shape_levers.md).
//   - REL32 0x0000AE5C (thunks_004.cpp, target FUN_0045c600, 48 B) is called once
//     right after entering the non-null-tex path, with args (lit=0x438384, 4, 0x1c,
//     &local). 0x438384 looks like a string literal address (candidate:
//     "Require rendered texture." from DEBUG_ASSERTCRASH) -- NOT yet confirmed what
//     FUN_0045c600 actually does; that is the blocker for an exact match.
//   - Global 0x01340534 = cached Direct3D device pointer (DX8Wrapper's D3DDevice).
//     Its vtable (raw slot-index calls, matching the BFME_SET_RS/BFME_SET_TSS
//     convention already proven in W3DShaderManager.cpp and in the landed
//     FlatShroudTextureShaderReset.cpp):
//       slot 0x104 (65)  -> SetTexture(Device*, stage, IDirect3DBaseTexture8*)
//       slot 0x164 (89)  -> SetVertexShader(Device*, DWORD FVF)   (FVF constant
//                            pushed is literal 0x144 = D3DFVF_XYZRHW|DIFFUSE|TEX1)
//       slot 0x14c (83)  -> DrawPrimitiveUP(Device*, D3DPT_TRIANGLESTRIP=5,
//                            PrimitiveCount=2, pVertices, Stride=0x1c=28)
//   - Global 0x012F1600 = TheTacticalView. Its vtable:
//       slot 0x4c (19) -> getOrigin(int*,int*)   (both out-params point at the SAME
//                          stack slot in this body -- unexplained, possibly a single
//                          combined Coord read)
//       slot 0x3c (15) -> getWidth()  (int, result in eax)
//       slot 0x44 (17) -> getHeight() (int, result in eax; added to prior getWidth())
//   - Vertex struct is the same _TRANS_LIT_TEX_VERTEX (D3DXVECTOR4 p; DWORD color;
//     float u,v;) as ScreenDefaultFilter::postRender / ScreenMotionBlurFilter /
//     ScreenBWFilterDOT3::postRender; stride 0x1c confirms 4 floats + dword + 2 floats.
//   - Colors are the constant 0xffffffff (no fade multiply, unlike ScreenBWFilterDOT3).
//
// UNRESOLVED (why this is banked, not landed):
//   - "ret 0x10" (4 explicit stack dwords popped) is one MORE dword than ZH's
//     Bool postRender(FilterModes mode, Coord2D &scrollDelta, Bool &doExtraRender)
//     (3 dwords). A pointer read from [esp+0xbc] (deep in the incoming-args region,
//     i.e. NOT a local spill) is dereferenced twice, at offset 0 and +4, as float
//     divisors (fdiv, no int-to-float fild first -- so the fields are already
//     float, not int pixel counts read through getWidth()/getHeight()). The
//     dividend is a float constant read from 0x01075334 (candidate: 1.0f, giving a
//     reciprocal-then-multiply reassociation of ZH's straight division -- classic
//     MSVC 7.1 x87 trap per docs/shape_levers.md) and 0x0107533C (candidate: 0.5f,
//     matches the "-0.5f" in the vertex corner offsets). Best hypothesis: BFME's
//     postRender signature carries a 4th parameter (a display-size struct/pointer
//     with two float fields, width then height) that ZH read through
//     TheDisplay->getWidth()/getHeight() instead. Confirming that 4th parameter
//     (and FUN_0045c600's real behaviour) is the fastest path to landing both this
//     body and its 0x007D1610 sibling, which shares the identical shape verbatim.
//
// Class layout skeleton (uncompiled placeholder, do not build from this file):
//
// struct Device; struct TacticalView;
// extern Device *ScreenDevice;          // 0x01340534
// extern TacticalView *TheTacticalView;  // 0x012F1600
// struct _TRANS_LIT_TEX_VERTEX { float p[4]; unsigned color; float u,v; };
// class ScreenXXXFilter {
//   virtual int set(int mode);           // vtable+0x14
//   ...
//   virtual void reset(void);            // vtable+0x18
//   bool postRender(int mode, void *scrollDelta, bool *doExtraRender, void *extra4th);
// };
