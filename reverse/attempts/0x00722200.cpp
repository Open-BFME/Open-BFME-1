// ?d_00722200@@YAXXZ
// partial score=0.55 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

// Open-BFME5 partial: ?ReAcquireResources@W3DSmudgeManager@@UAEXXZ
// retail 0x00722200, 297 bytes.
//
// IDENTITY (high confidence): W3DSmudgeManager::ReAcquireResources.
//   reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Source/
//   W3DDevice/GameClient/W3DSmudge.cpp defines
//   `#define SMUDGE_DRAW_SIZE 500` and ReAcquireResources() fills a
//   DX8IndexBufferClass sized SMUDGE_DRAW_SIZE*4*3 = 6000 = 0x1770 bytes with
//   a 500-iteration loop writing 12 UnsignedShort indices per iteration
//   (offsets 0..0x16 step 2, stride 0x18=24 bytes/iteration). The retail
//   disassembly of 0x00722200 has EXACTLY this shape: edi=0x1F4(500) loop
//   counter, ecx+=5 each iteration, 12 `mov word ptr [eax+N], reg16` stores
//   per iteration matching the vbCount/vbCount+1..+4 index pattern from the
//   "quad of 4 triangles" (0-1-2-3 + center vertex 4) comment in that file.
//   This is the row immediately after ??0Rva00722120@@QAE@XZ (landed,
//   "SmudgeManager derived ctor zeros seven dwords then one color" ==
//   W3DSmudgeManager ctor / SmudgeManager base ctor initializer) and right
//   before ?dup_007225d0@@YAXXZ (an ICF alias of ~FontLibrary, unrelated).
//
// CALL-TARGET CONFIRMATION: the retail bytes bracket the body with calls to
// VA 0x00903090 / 0x00905B10, which reverse/symbols.csv already names
// ?W3DRadarResetLock@@YAXXZ / ?W3DRadarResetUnlock@@YAXXZ -- the exact same
// lock/unlock guard pair used by the already-landed
// Code/GameEngine/Source/GameClient/FontLibrary_deleteAllFonts.cpp (the
// preceding function, 0x00722190). Remaining call targets, decoded from the
// retail REL32 displacements at each call site (VA - 0x400000 = RVA):
//   RVA 0x00905070  -> already matched: ?getBackBufferSurface006e@@YA?AVW3DRadarResetSurface@@H@Z
//                       (BFME's DX8Wrapper::_Get_DX8_Back_Buffer equivalent;
//                       returns a BY-VALUE RAII wrapper "W3DRadarResetSurface",
//                       NOT the raw SurfaceClass* the ZH source uses -- BFME
//                       rewrote this accessor.)
//   RVA 0x008FC5C0  -> already matched: ?Get_Description@SurfaceClass@@QAEXAAUSurfaceDescription@1@@Z
//   RVA 0x00881F30  -> already matched: operator new (??2@YAPAXI@Z)
//   RVA 0x0091D0A0  -> already matched: DX8IndexBufferClass ctor
//   RVA 0x0091CE50  -> already matched: DX8IndexBufferClass::WriteLockClass ctor
//   RVA 0x0091CEF0  -> already matched: DX8IndexBufferClass::WriteLockClass dtor
//   RVA 0x008FC5B0  -> already matched: ??1W3DRadarResetSurface@@QAE@XZ
//                       ("isolated clean wrapper release through proven
//                       vtable slot 2" -- confirms the by-value RAII wrapper
//                       theory above)
//
// BLOCKER: SmudgeManager (base, Code/GameEngine/Include/GameClient/Smudge.h)
// declares ReleaseResources/ReAcquireResources VIRTUAL (W3DSmudgeManager's
// own header doesn't repeat `virtual`, it's inherited) -- retail's very
// first instruction after the SEH prologue is `call [eax+0xC]`, matching
// SmudgeManager's vtable order (dtor=0, init=4, reset=8,
// ReleaseResources=0xC, ReAcquireResources=0x10), so `ReleaseResources()` at
// the top of the source IS that call and does not need a REL32 symbol pin.
// Confirmed member layout by reading retail stores directly:
//   SmudgeManager:      vtable@0x00, m_hardwareSupportStatus@0x04,
//                        m_usedSmudgeSetList(DLListClass<SmudgeSet>,
//                        12B: vtable+head+tail)@0x08,
//                        m_freeSmudgeSetList@0x14, m_smudgeCountLastFrame@0x20
//                        (SmudgeManager instance size 0x24)
//   W3DSmudgeManager:   m_smudgeGroup@0x24, m_posBuffer@0x28,
//                        m_RGBABuffer@0x2C, m_sizeBuffer@0x30,
//                        m_indexBuffer@0x34, m_backBufferWidth@0x38,
//                        m_backBufferHeight@0x3C
//   -- this matches retail's `mov [esi+0x34],eax` (m_indexBuffer),
//   `mov [esi+0x38],eax` / `[esi+0x3C],ecx` (m_backBufferWidth/Height)
//   exactly.
//
// What's NOT yet resolved: the local `SurfaceClass::SurfaceDescription`-style
// struct BFME's getBackBufferSurface006e/Get_Description pair actually use is
// smaller/reordered vs. the real D3DSURFACE_DESC (Width read at local
// struct offset +4, Height at +8 in the retail disassembly, not D3D8's
// canonical +0x18/+0x1C) -- BFME appears to have swapped in a reduced
// descriptor struct. A faithful minimal stand-in class
// (W3DRadarResetSurface : with a nested 3-field SurfaceDescription and a
// ~W3DRadarResetSurface dtor pinned to 0x008FC5B0, plus a free function
// `getBackBufferSurface006e` pinned to 0x00905070 by matching its already-
// landed mangled name) should let this compile and should reproduce the
// prologue/epilogue/index-fill-loop bytes once /EHsc is enabled per-TU (the
// vendored reference/ path always forces -EHsc-, so this row cannot be
// landed by pointing straight at the reference .cpp -- it needs a Code/
// source with its own `// cl:` line, which is why this file exists).
//
// Not landed: ran out of the session's time budget turning the descriptor
// struct's exact field layout + minimal SurfaceClass/W3DRadarResetSurface
// stand-ins into a byte-exact compile. Next step: instantiate the two
// stand-in classes above, call ReleaseResources()/ReAcquireResources() via a
// virtual thunk matching the SmudgeManager vtable order documented above,
// and iterate with tools/explain_mismatch.py against RVA 0x00722200 (size
// 297).
