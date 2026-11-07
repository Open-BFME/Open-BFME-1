# 0x006EB500 `?rva006EB500@W3DDisplay@@QAE_NI@Z` (1215 B): EXACT

Best candidate: `build/wf/006eb500/best.cpp` (`// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc`,
unchanged from the bank). `probe.py` result: 1215/1215 B, 85 relocs, `EXACT (modulo relocation slots)`.
Baseline: the bank `targets/game/reverse/attempts/0x006eb500.cpp` reproduced as logged
(21 non-reloc diffs, first +0x309, shape 0.997).

## Root cause of the 21-byte "receiver vtable hoist" wall
Earlier sessions modelled the m_34 site as `slot0E0(m_34->slot03C(m_f8, m_fc, m_100, m_104, -1))`,
which assigned the five stack arguments to the wrong call. Retail pushes `-1, [+0x104], [+0x100],
[+0xFC], [+0xF8]`, then calls panel slot 0x3C with **no** stack arguments, pushes its result, and
calls `this` slot 0xE0. So the pushes belong to the outer call. Because the outer call is the one
being evaluated, MSVC hoists the outer vtable into EDI first and loads the panel vtable late.
Retail evidence follows:
- W3DDisplay vtable 0x0111EDD0 slot 56 (+0xE0) -> ILT 0x0001680B -> 0x006EA360, ledger row
  `?drawImage@W3DDisplay@@UAEXPAVImage@@MMMMH@Z` (matched, W3DDisplayDrawImage.cpp), `ret 0x18` at
  +0x15A, so it takes 6 stack arguments: Image*, four floats and an int.
- BFME 2 donor (open-bfme-2 `dbde7dbe`, `Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp`,
  `?rva0004A462@W3DDisplay@@QAE_NI@Z`, matched there) writes
  `drawImage(m_38->s3c(), m_fc, m_100, m_104, m_108, -1);`. This is a donor lead only. The BFME 1 facts
  are the slot, the `ret` and the ledger name above.

Fix (minimal): `drawImage(m_34->slot03C(), m_f8, m_fc, m_100, m_104, -1);` with `Image *slot03C(void)`
and members +0xF8..+0x104 typed `Real`, as the drawImage mangling `MMMM` requires. Exact with both Int
and Real member types; Real is the ABI-consistent one.

## Hypotheses tested this session
- drawImage outer call with `void*`/Int params (v1): EXACT.
- Same with ledger types Image*/Real (v2): EXACT.
- ZH function-local `static Bool couldRender = true;` instead of extern global (v3): EXACT.
- Rebind 0x0040EE90 to ledger `Rva0040EE90Owner::update` (v4 = best): EXACT.

All earlier families (11+3+3 spellings, 36 rotation toggles, EH groups, flag sweeps, permute 1185
trials, volatile, noinline helpers) were attacking a mis-assigned argument list and are superseded.

## Landing notes (read-only checks; nothing landed)
a. `ilt_oracle.py check '?rva006EB500@W3DDisplay@@QAE_NI@Z' 0x006EB500` returns CONTRADICTED
   (p_false=1.96e-4, slots 50034:29625-29627). `tier()` classifies the name as **placeholder**
   (`Rva` + hex), which `ilt_guard` exempts. symbols.csv has no pin for the target's ILT
   0x0001EF7B (only `?b_006eb500@@YAXXZ` gen-thunk body). Keep the address-derived name. The real
   EA name is unknown.
b. Helpers: the TU emits COMDATs for inline-only views (`Rva006EB500RenderLock` ctor/dtor,
   `DX8Wrapper::_Get_D3D_Device8`, `ScriptEngine::frozenPair006EB500`,
   `BfmeA1087::getWaterTransparency`). None has its own ledger row, so there is no COMDAT loser.
   Callee binding: every call resolves to a ledger name or pin except **0x0044A6A0** (ILT 0x0001F8F2,
   ledger `?d_0044a6a0@@YAXXZ` gen_asm dump). The candidate calls it as `InGameUI::rva1f8f2()`, so it
   needs one pin with independent ABI proof (callees.py: __thiscall, 0 stack slots; a prior
   gpt-6.1-sol trial proved the zero-stack ECX ABI). Already pinned: `?test@Rva003968A0@@QAE_NXZ`,
   `?rva000652A0@GameLogic@@QBE_NXZ`. Begin_Render/End_Render bool spellings have object-symbol
   aliases.
c. Globals: every referenced global is in dir32_addresses.csv (TheWritableGlobalData,
   TheScriptEngine, TheBfmeGameLogic, Glo012F1028, TheInGameUI, Rva00579160TheManager,
   TheWindowManager, TheTransitionHandler, TheMouse, TheParticleSystemManager, g_bfmeA1087,
   g_bfmeGlobPB, DX8Wrapper::D3DDevice, ShaderClass::_PresetOpaqueShader 0x012D6E08,
   `__real@00000000` 0x01075350, `__real@4f800000` 0x01075358) **except VA 0x012BAA54**
   (.data, initial byte 01 = ZH `static Bool couldRender = true`). It needs a data row
   (`add_data_match.py`), either as extern `g_couldRender012BAA54` or as the function-local static
   (v3 spelling, TU-local data).
d. TU: new `game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplayRva006EB500.cpp`, following
   the sibling `W3DDisplayRva006EB3E0.cpp`. The body has no visible helper it shares with another TU.
   Commit title prefix `[BFME 2 donor]`.
