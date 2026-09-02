// ?d_00722380@@YAXXZ
// partial score=0.3 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

// Open-BFME5 partial: candidate for retail 0x00722380, 326 bytes.
//
// This RVA sits between the (identity-confirmed, see the 0x00722200 partial
// in this same batch) W3DSmudgeManager::ReAcquireResources at 0x00722200
// and the ICF-aliased ~FontLibrary body at 0x007225D0 (unrelated, already
// landed under ?dup_007225d0@@YAXXZ). It is almost certainly another
// W3DSmudgeManager member from
// reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Source/
// W3DDevice/GameClient/W3DSmudge.cpp.
//
// TRIED: `copyRect(unsigned char*, Int, int, int, int, int)`, the free
// function in that same file that testHardwareSupport() calls twice to read
// back rendered pixels. Compiling the vendored file stand-alone (it always
// forces -EHsc- regardless of any // cl: line -- see build.py
// source_extra_flags/zh_reference_source) produced
// `?copyRect@@YAHPAEHHHHH@Z`, 283 bytes vs. target 326, and the overall
// control-flow shape lines up (null-check a device/surface pointer, call
// through its vtable, check result, compute a RECT, call again, LockRect-
// shaped call, GetDesc-shaped call, rep movsd/movsb memcpy, final call) but
// the exact vtable slot numbers do not: compiled uses the canonical D3D8
// IDirect3DDevice8 slots (GetRenderTarget=0x80, ShowCursor=0x30,
// CreateImageSurface=0x6C, CopyRects=0x70, LockRect=0x24) while retail uses
// 0x98, ?, 0x70, 0x88, 0x34 at the corresponding call sites -- a non-uniform
// shift, so it is not simply "the same interface at a different base slot".
// Two readings: (a) this is genuinely copyRect but called through a
// wrapped/derived device interface with extra virtual slots inserted before
// the D3D8 methods it uses (plausible given the W3DRadarResetSurface /
// getBackBufferSurface006e byval-wrapper rewrite already confirmed for the
// neighboring ReAcquireResources body), or (b) this RVA is a different
// W3DSmudgeManager member entirely (testHardwareSupport() is the next-best
// candidate by size/complexity, but wasn't tried this session).
//
// Also tried testHardwareSupport() directly this session: compiled size 919
// bytes vs. target 326, a much worse size gap than copyRect's 283 vs 326 --
// copyRect remains the better-fitting candidate by size even though its
// vtable slots don't line up yet. testHardwareSupport's own unresolved
// callee is `?getRenderTexture@W3DShaderManager@@SAPAUIDirect3DTexture8@@XZ`
// (also needed by the 0x00722640/render() candidate in this batch).
//
// Not landed: identity not confirmed to the byte-match bar. Next step: get
// explain_mismatch's per-call target breakdown for the *compiled*
// candidate and cross-reference each retail call site's REL32 target
// (already-matched functions resolve silently; anything left unresolved
// after fixing the /EHsc-forced-off vendored-path problem, by copying this
// function into a Code/ TU with its own `// cl:` line, will name the exact
// missing callee) before concluding whether copyRect or testHardwareSupport
// is the right shape, or whether the wrapping-interface theory needs a
// stand-in vtable with a handful of unused leading slots.
