// RVA003F0EC0,43B. The banked bfmeFwdEQC label is retained under an
// address-derived owner; no semantic class identity is asserted.
// The caller keeps ECX live through ILT0001FA14 to physical003EEB90.
// That helper saves ECX in EBX at003EEBA3 and reads receiver+8 at003EEBCB.
// It consumes seven stack arguments and returns with ret1C at003EFE7E.
// Its args0/6 are byte predicates; arg2 is an object pointer; args3/4
// address three floats. Args1/5 remain opaque 32-bit values.
// Both functions must therefore be thiscall, not the bank's free stdcall.
// Keeping the field load as a local then forwarding reproduces all43B.
struct BfmeSrcEQC
{
	unsigned char m_unreconstructed[0x10];
	unsigned int m_bfmeKindEQC;
};

class Rva003F0EC0Owner {
public:
 int bfmeInnerEQC(bool a, unsigned int kind, void *b, const void *c, const void *d, unsigned int e, bool f);
 int bfmeFwdEQC(bool a, BfmeSrcEQC *src, void *b, const void *c, const void *d, unsigned int e);
};
int Rva003F0EC0Owner::bfmeFwdEQC(bool a, BfmeSrcEQC *src, void *b, const void *c, const void *d, unsigned int e)
{
 unsigned int kind = src->m_bfmeKindEQC;
 return bfmeInnerEQC(a, kind, b, c, d, e, 0);
}
