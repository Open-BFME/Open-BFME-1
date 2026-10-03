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
	int bfmeFwdEQC(bool a, BfmeSrcEQC *src, void *b, const void *c,
		const void *d, unsigned int e);
};

// Use the dump's emitted symbol with its observed member-call ABI. The extra
// fastcall register slot repeats b, which is already in EDX at the call site.
void d_003eeb90(void);

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
	typedef int (__fastcall *DumpHelper)(Rva003F0EC0Owner *, void *, bool,
		unsigned int, void *, const void *, const void *, unsigned int, bool);
	return reinterpret_cast<DumpHelper>(&d_003eeb90)(
		reinterpret_cast<Rva003F0EC0Owner *>(this), b, a, kind, b, c, d, e,
		true);
}
