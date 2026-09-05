// ?Do_Onetime_Device_Dependent_Shutdowns@DX8Wrapper@@SAXXZ
// partial score=0.85 date=2026-09-05
// This candidate is meant to replace the "present-unmatched" ZH-ported stub
// already sitting at Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.cpp lines
// ~501-535 (DX8Wrapper::Do_Onetime_Device_Dependent_Shutdowns). Land it there,
// reusing that file's existing includes/classes -- do not build this snippet
// standalone. cl flags stay the file's own: /DNDEBUG /DWIN32 /D_WINDOWS /MD
// /EHsc plus the WW3D2/reference include paths already on that TU.
//
// IDENTITY: confirmed via ZH reference (dx8wrapper.cpp:463-496,
// GeneralsMD tree) -- same call list/order, same globals:
//   render_state.vertex_buffers[0..1] @ 0x1341120/0x1341124 (VertexBufferClass*)
//   render_state.index_buffer         @ 0x1341128 (IndexBufferClass*)
//   render_state.material             @ 0x1340EC4 (VertexMaterialClass*, ==
//     family model's "ScreenMaterial")
//   CurrentCaps                       @ 0x1340578 (DX8Caps*; confirmed by
//     symbols.csv rows ?BfmeCurrentCaps@@3PAEA / ?TheDX8Caps@@3PAEA at the
//     same VA) -- +0x278 is MaxTexturesPerPass, +0x29C/+0x2A0/+0x2A4/+0x2A8
//     are DriverDLL/Direct3D*/CapsLog/CompactLog exactly per
//     reference/CnC_Generals_Zero_Hour/GeneralsMD/.../dx8caps.h.
//   render_state.Textures[] array     @ 0x1340EC8 (TextureBaseClass*[..])
//
// Retail (BFME) differs from the ZH shape only by: no TextureLoader::Deinit()
// call, and several ZH-named calls (ShatterSystem::Shutdown,
// PointGroupClass::_Shutdown, BoxRenderObjClass::Shutdown, SHD_SHUTDOWN) come
// out either as already-ledgered placeholders or as plain "no-this" calls in
// BFME's reshaped binary:
//   SortingRendererClass::Deinit()      (already matched, sortingrenderer.cpp)
//   d_0091daa0()                        (already matched dump; ~DynamicVBAccessClass::_Deinit shape)
//   DynamicIBAccessClass::_Deinit()     (already matched, dx8indexbuffer.cpp)
//   0x00912CF0                          (NOT YET in functions.csv; 358B real
//                                        function per ghidra_functions.csv;
//                                        symbols.csv now carries an alias pin
//                                        ?Rva00912CF0@@YAXXZ,0x00912CF0)
//   Gen_0090f260::m @ 0x0090F260        (already matched gen-shim, single
//                                        `ret`; retail call site has NO ecx
//                                        setup, so it cannot be the thiscall
//                                        `?m@Gen_0090f260@@QAEXXZ` -- use the
//                                        symbols.csv alias
//                                        ?Rva0090F260Nop@@YAXXZ,0x0090F260
//                                        instead so the call compiles with no
//                                        `this` argument)
//   VertexMaterialClass::Shutdown()    (already matched, vertmaterial.cpp)
//   bfmeGo911C()                       (already matched free function,
//                                        BfmeConv911.cpp -- unrelated name,
//                                        but resolves to the right address)
//   TheDX8MeshRenderer (BFME pointer form, see
//     Code/Libraries/Source/WWVegas/WW3D2/WW3D_SetNPatchesLevelThunk.cpp)
//     ->Shutdown()                     @ via [0x0134B0E8], already matched
//                                        (?Shutdown@DX8MeshRendererClass@@QAEXXZ)
//   ((Gen_00944c30*)same pointer)->m() (already matched gen-shim, single
//                                        `ret`; retail DOES reload
//                                        [0x0134B0E8] into ecx a second time
//                                        before this call, so it genuinely is
//                                        thiscall through that pointer, unlike
//                                        Gen_0090f260)
//
// REMAINING GAP (169->188 non-reloc bytes depending on shape tried, ours=318
// retail=401, i.e. 83 B short): retail wraps the WHOLE function in a
// per-function SEH frame (`push -1; push <scopetable>; mov eax,fs:[0]; push
// eax; mov fs:[0],esp; push ecx; push esi; push edi; ...` at entry, mirrored
// at the epilogue) that our candidate never emits. Inside that frame, retail
// tracks an unwind STATE variable at [esp+0x14] (values 2, then 1, then -1)
// around the three sequential StringClass destructor calls
// (CompactLog@+0x2A8, CapsLog@+0x2A4, DriverDLL@+0x29C, in that reverse-
// declaration order) before the final `operator delete`. That is the
// signature of an MSVC7.1-SYNTHESIZED (not user-written) destructor for an
// aggregate with 3+ non-trivially-destructible members being INLINED into
// the caller, carrying its own EH state bookkeeping along with it.
//
// Tried and did NOT reproduce the SEH frame/state var (all under this file's
// existing /EHsc, no other flags changed):
//   1. `delete CurrentCaps;` (plain, real DX8Caps type)            -> 292 B, no SEH.
//   2. `CurrentCaps->~DX8Caps(); operator delete(CurrentCaps);`    -> 295 B, no SEH.
//   3. A minimal BfmeCapsShutdownShim reinterpret (only the trailing
//      MaxTexturesPerPass/DriverDLL/Direct3D/CapsLog/CompactLog fields,
//      single use site in the whole program) with `delete shim;`  -> 292 B,
//      identical to (1); still calls one out-of-line synthesized dtor.
//   4. Same shim with an explicit `__forceinline ~BfmeCapsShutdownShim(){}`
//      (still auto member cleanup) and `delete shim;`             -> 292 B,
//      no change -- forceinline was not honoured for the dtor either.
//   5. Hand-written explicit member destructor calls in reverse order
//      (`caps->CompactLog.~StringClass(); caps->CapsLog.~StringClass();
//      caps->DriverDLL.~StringClass(); operator delete(caps);`)   -> 318 B.
//      THIS is the best shape found: the tail disassembly then matches
//      retail instruction-for-instruction (same lea/call sequence, same
//      final `push esi; call operator delete; mov [0x1340578],edi`), the
//      ONLY remaining difference being retail's interleaved
//      `mov [esp+0x14], 2/1/-1` state stores and the outer SEH push/pop pair.
//      Use this exact shape (see BfmeCapsShutdownShim + the three explicit
//      `.~StringClass()` calls below) as the starting point.
//
// NEXT AGENT: the state-store bytes strongly suggest MSVC 7.1 needs to
// believe it is emitting the COMPILER-GENERATED aggregate destructor itself
// (not a hand-called sequence) to bother with the state variable + SEH frame
// -- but every attempt to trigger real destructor synthesis+inlining above
// failed to produce it. Untried ideas: build this one function in its own
// translation unit (a `dx8wrapper_shutdown.cpp`-style split) so the shim
// type's destructor is unambiguously single-TU/single-use without the noise
// of the rest of dx8wrapper.cpp's other CurrentCaps/DX8Caps uses nearby;
// try declaring three real (not reinterpret_cast) StringClass& references
// bound to the object's fields and let them go out of scope via an inner
// `{ }` block ending right before `operator delete`, so the scope-exit is
// driven by the compiler's own local-object EH machinery instead of by
// hand-written statements; or check whether this file needs an explicit
// /Ob1 (vs whatever /Ob level it defaults to with no /O flag at all --
// dx8wrapper.cpp's cl line carries NO optimization flag, so it is almost
// certainly compiling at the cl.exe default /Od, which does not usually
// synthesize this kind of state machine at all -- worth testing a TU-scoped
// /O1 or /O2 override for just this function's translation unit, mirroring
// how TextureBaseReleaseRefThunk.cpp carries its own "/O2 /Ob2" cl line).
//
// Both symbols.csv aliases below are already landed in the shared ledger
// file and do not need to be re-added:
//   ?Rva0090F260Nop@@YAXXZ,0x0090F260
//   ?Rva00912CF0@@YAXXZ,0x00912CF0

void Rva0090F260Nop(void);
void Rva00912CF0(void);
void d_0091daa0(void);
void bfmeGo911C(void);
struct Gen_00944c30 { void m(); };
extern DX8MeshRendererClass *g_bfmeMeshRendererSingleton;   // 0x0134B0E8

struct BfmeCapsShutdownShim
{
	unsigned char pad0[0x29C];
	StringClass DriverDLL;
	void *Direct3D;
	StringClass CapsLog;
	StringClass CompactLog;
};

void DX8Wrapper::Do_Onetime_Device_Dependent_Shutdowns(void)
{
	int i;
	for (i=0;i<MAX_VERTEX_STREAMS;++i) {
		if (render_state.vertex_buffers[i]) render_state.vertex_buffers[i]->Release_Engine_Ref();
		REF_PTR_RELEASE(render_state.vertex_buffers[i]);
	}
	if (render_state.index_buffer) render_state.index_buffer->Release_Engine_Ref();
	REF_PTR_RELEASE(render_state.index_buffer);
	REF_PTR_RELEASE(render_state.material);
	for (i=0;i<CurrentCaps->Get_Max_Textures_Per_Pass();++i) REF_PTR_RELEASE(render_state.Textures[i]);

	SortingRendererClass::Deinit();
	d_0091daa0();
	DynamicIBAccessClass::_Deinit();
	Rva00912CF0();
	Rva0090F260Nop();
	VertexMaterialClass::Shutdown();
	bfmeGo911C();
	g_bfmeMeshRendererSingleton->Shutdown();
	((Gen_00944c30 *)g_bfmeMeshRendererSingleton)->m();

	if (CurrentCaps) {
		BfmeCapsShutdownShim *caps = reinterpret_cast<BfmeCapsShutdownShim *>(CurrentCaps);
		caps->CompactLog.~StringClass();
		caps->CapsLog.~StringClass();
		caps->DriverDLL.~StringClass();
		operator delete(caps);
		CurrentCaps=NULL;
	}
}
