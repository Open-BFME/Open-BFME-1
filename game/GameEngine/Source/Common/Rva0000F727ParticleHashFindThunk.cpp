// Retail RVA 0x0000F727 is a five-byte tail jump to the matched STLport
// ParticleSystemTemplate hash lookup at RVA 0x005C76A0.
// The _M_find pin and thirteen callers prove this forwarding identity.
// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /O2

extern void rva0000f727Target(void);

#pragma comment(linker, "/alternatename:?rva0000f727Target@@YAXXZ=??$_M_find@VAsciiString@@@?$hashtable@U?$pair@$$CBVAsciiString@@PAVParticleSystemTemplate@@@_STL@@VAsciiString@@U?$hash@VAsciiString@@@rts@@U?$_Select1st@U?$pair@$$CBVAsciiString@@PAVParticleSystemTemplate@@@_STL@@@2@U?$equal_to@VAsciiString@@@5@V?$allocator@U?$pair@$$CBVAsciiString@@PAVParticleSystemTemplate@@@_STL@@@2@@_STL@@ABEPAU?$_Hashtable_node@U?$pair@$$CBVAsciiString@@PAVParticleSystemTemplate@@@_STL@@@1@ABVAsciiString@@@Z")

void Rva0000F727ParticleHashFindThunk(void)
{
	rva0000f727Target();
}
