// ?Rva0002AF86ParticleSysBoneInfoUninitializedCopyThunk@@YAXXZ
// Retail RVA 0x0002AF86 is a five-byte tail jump to the matched STLport
// ParticleSysBoneInfo uninitialized-copy body at RVA 0x000A7AA0.
// cl: /O2 /MD /D_STLP_USE_STATIC_LIB

extern void rva0002af86Target(void);

#pragma comment(linker, "/alternatename:?rva0002af86Target@@YAXXZ=??$__uninitialized_copy@PBUParticleSysBoneInfo@@PAU1@@_STL@@YAPAUParticleSysBoneInfo@@PBU1@0PAU1@ABU__false_type@0@@Z")

void Rva0002AF86ParticleSysBoneInfoUninitializedCopyThunk(void)
{
	rva0002af86Target();
}
