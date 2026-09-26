// Address-derived forwarder at retail RVA 0x003F0F00. It reads the +0x10
// word from the source record and calls the witnessed seven-argument helper
// with the trailing flag set.
struct BfmeSrcEQC
{
	unsigned char m_unreconstructed[0x10];
	unsigned int m_bfmeKindEQC;
};

class Rva003F0EC0Owner
{
public:
	int bfmeInnerEQC(bool a, unsigned int kind, void *b, const void *c,
		const void *d, unsigned int e, bool f);
	int bfmeFwdEQC(bool a, BfmeSrcEQC *src, void *b, const void *c,
		const void *d, unsigned int e);
};

class Rva003F0F00Owner
{
public:
	int rva003F0F00(bool a, BfmeSrcEQC *src, void *b, const void *c,
		const void *d, unsigned int e);
};

int Rva003F0F00Owner::rva003F0F00(bool a, BfmeSrcEQC *src, void *b,
	const void *c, const void *d, unsigned int e)
{
	unsigned int kind = src->m_bfmeKindEQC;
	return reinterpret_cast<Rva003F0EC0Owner *>(this)->bfmeInnerEQC(
		a, kind, b, c, d, e, true);
}
