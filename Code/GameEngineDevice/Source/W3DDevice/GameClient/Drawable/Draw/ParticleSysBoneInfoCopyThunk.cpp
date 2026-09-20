// ?Rva00039577ParticleSysBoneInfoCopyThunk@@YAXXZ
// Retail RVA 0x00039577 is a five-byte tail jump to the matched STLport
// ParticleSysBoneInfo const-source copy body at RVA 0x000A78A0. The forwarding
// declaration keeps the caller's existing copy arguments on the stack.
// cl: /O2 /MD /D_STLP_USE_STATIC_LIB

extern void rva00039577Target(void);

#pragma comment(linker, "/alternatename:?rva00039577Target@@YAXXZ=??$__copy@PBUParticleSysBoneInfo@@PAU1@H@_STL@@YAPAUParticleSysBoneInfo@@PBU1@0PAU1@ABUrandom_access_iterator_tag@0@PAH@Z")

void Rva00039577ParticleSysBoneInfoCopyThunk(void)
{
	rva00039577Target();
}
