// ?Rva0002AF86ParticleSysBoneInfoUninitializedCopyThunk@@YAXXZ
// Retail RVA 0x0002AF86 is a five-byte tail jump to the matched STLport
// ParticleSysBoneInfo uninitialized-copy body at RVA 0x000A7AA0.
// cl: /O2 /MD /D_STLP_USE_STATIC_LIB

// The jump target carries the callee's own decorated name
// ??$__uninitialized_copy@PBUParticleSysBoneInfo@@PAU1@@_STL@@YAPAUParticleSysBoneInfo@@PBU1@0PAU1@ABU__false_type@0@@Z,
// a _STL function template explicitly instantiated in
// ParticleSysBoneInfoUninitializedCopyBody.cpp. Retail's incremental-link thunk
// only forwards the caller's four arguments, which the cdecl caller already
// placed on the stack, so the five-byte body is a bare tail jump. C++ cannot
// spell that name here: reproducing the template needs the TU-local _STL
// declarations the body owns, and __identifier carries the decorated name
// itself instead. With no arguments __cdecl, __stdcall and __thiscall encode
// the same call, so the void() prototype still compiles to the five-byte jump.
extern "C" void __identifier("??$__uninitialized_copy@PBUParticleSysBoneInfo@@PAU1@@_STL@@YAPAUParticleSysBoneInfo@@PBU1@0PAU1@ABU__false_type@0@@Z")(void);

void Rva0002AF86ParticleSysBoneInfoUninitializedCopyThunk(void)
{
	__identifier("??$__uninitialized_copy@PBUParticleSysBoneInfo@@PAU1@@_STL@@YAPAUParticleSysBoneInfo@@PBU1@0PAU1@ABU__false_type@0@@Z")();
}
