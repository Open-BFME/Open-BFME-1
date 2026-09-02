// ?d_00722640@@YAXXZ
// partial score=0.25 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

// Open-BFME5 partial: candidate for retail 0x00722640, 1098 bytes.
//
// IDENTITY (moderate confidence): W3DSmudgeManager::render(RenderInfoClass&)
// from reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/
// Source/W3DDevice/GameClient/W3DSmudge.cpp. It is the largest remaining
// member of that class (the file also declares testHardwareSupport(),
// ReleaseResources(), the ctor/dtor and init()/reset() -- all far smaller
// than 1098 bytes) and by elimination against the other three rows in this
// batch (0x00722200 = ReAcquireResources, confirmed; 0x007225D0 = an
// unrelated ICF alias of ~FontLibrary already landed; 0x00722380 = probably
// another W3DSmudgeManager member, see that RVA's own partial) it is the
// only slot left for the class's biggest function.
//
// render() walks m_usedSmudgeSetList / each SmudgeSet's used-Smudge list,
// projects each Smudge's 5 verts through the view/projection matrices, then
// issues a batch of DX8Wrapper::Set_Transform / Set_Index_Buffer /
// Set_Shader / Set_DX8_Texture / DrawIndexedPrimitive-shaped device calls --
// consistent with the retail body's large (0x27C-byte) stack frame, SEH
// prologue, heavy virtual-call traffic and float/SSE-shaped constant loads
// visible in a raw capstone disassembly of the RVA (not fully cross-checked
// against source line-by-line this session).
//
// UPDATE: ran that check this session. Compiling the vendored file
// stand-alone (see the 0x00722200/0x00722380 partials for why the
// reference/ path always forces -EHsc- and can't itself be the landed
// source) gives `?render@W3DSmudgeManager@@QAEXAAVRenderInfoClass@@@Z`,
// **3420 compiled bytes vs. 1098 target bytes** -- a 3x size gap, much
// larger than the modest differences seen on the other two rows in this
// batch. Unresolved REL32 callees:
//   ?Get_Projection_Matrix@CameraClass@@QAEXPAVMatrix4x4@@@Z
//   ?getRenderTexture@W3DShaderManager@@SAPAUIDirect3DTexture8@@XZ
//   ?testHardwareSupport@W3DSmudgeManager@@AAE_NXZ (not yet landed itself)
// The retail prologue is `push ebp; mov ebp,esp; and esp,0xFFFFFFF8` (8-byte
// stack realignment, present) before the usual SEH push; the ZH-source
// compile does NOT realign the stack the same way, meaning the vendored
// tree's WWMath Vector3/Matrix3D/Matrix4x4 either aren't producing the same
// alignment requirements as retail's real types, or retail's actual
// function differs from ZH's source more substantially than a like-for-like
// port (BFME may have changed the vertex-offset/UV math). Given the 3x size
// gap this needs real investigation, not a small tweak: confirm real
// Vector2/Vector3/Matrix3D/Matrix4x4 sizes+alignment match retail (WWMath
// headers already used elsewhere in Code/Libraries/Source/WWVegas/WWMath),
// and pin the three unresolved callees above (CameraClass::
// Get_Projection_Matrix, W3DShaderManager::getRenderTexture,
// W3DSmudgeManager::testHardwareSupport -- the last of which is itself the
// best remaining candidate for 0x00722380 in this same batch, so landing it
// first would help both rows) before iterating on this one.
