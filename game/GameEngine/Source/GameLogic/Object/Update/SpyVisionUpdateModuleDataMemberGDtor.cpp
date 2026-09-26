// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME5: vector<12-byte elem> dtor at 0x00374990. Reloc-named as
// SpyVisionUpdateModuleDataMemberG (caller in SpyVisionUpdateModuleData
// dtor). Each element destroys two AsciiString-shaped members at +0/+4;
// block release is the usual >0x80 free / node-alloc path. Retail extent
// is 204 bytes (Ghidra's 197 stopped mid-epilogue).

#include <vector>

struct Mem00887940
{
	~Mem00887940();
	void *m_data;
};

struct SpyVisionMemberGElem
{
	Mem00887940 m_a;
	Mem00887940 m_b;
	int m_pad;
};

template class _STL::vector<SpyVisionMemberGElem>;
