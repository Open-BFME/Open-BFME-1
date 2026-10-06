// Open-BFME5 conversions.

extern "C" unsigned strlen(const char *s);
extern "C" void *memcpy(void *d, const void *s, unsigned n);
#pragma intrinsic(strlen)
#pragma intrinsic(memcpy)

struct BfmeHdrVKI
{
	unsigned short m_bfme00;
	unsigned short m_bfme02;
	unsigned short m_bfme04;
	unsigned short m_bfme06;
};

typedef void *(__cdecl *BfmeAllocFnVKI)(unsigned n);

// Retail 0x01337A30 is the Apt allocator pair defined once as
// g_rva01337A30AllocPair (data_rows.csv, game/Libraries/Source/Apt/Apt.cpp);
// its first slot is the allocate function this body calls.
struct BfmeStringPool3AF0;
extern BfmeStringPool3AF0 *g_rva01337A30AllocPair;
// The shared empty EA string block at 0x012D5298 is defined once, as
// EAStringC::StringDataC, in game/GameEngine/Source/Common/Data/Rva012D5298.cpp;
// this TU keeps its own local view of the block and casts at each use.
class EAStringC
{
public:
	class StringDataC;
};
extern EAStringC::StringDataC g_rva012D5298Empty;

class BfmeStrVKI
{
public:
	void bfmeSetVKI(const char *s);
	BfmeStrVKI &assignRva00891B50(const char *s);
	BfmeHdrVKI *m_bfme00;
};

void BfmeStrVKI::bfmeSetVKI(const char *s)
{
	if (*s == 0)
	{
		m_bfme00 = (BfmeHdrVKI *)&g_rva012D5298Empty;
		++((BfmeHdrVKI *)&g_rva012D5298Empty)->m_bfme00;
		return;
	}
	int len = strlen(s);
	unsigned sz = (len + 0xc) & ~3;
	m_bfme00 = (BfmeHdrVKI *)(*(BfmeAllocFnVKI *)g_rva01337A30AllocPair)(sz);
	m_bfme00->m_bfme00 = 1;
	m_bfme00->m_bfme04 = (unsigned short)(sz - 9);
	m_bfme00->m_bfme02 = (unsigned short)len;
	m_bfme00->m_bfme06 = 0;
	memcpy((char *)m_bfme00 + 8, s, len + 1);
}

BfmeStrVKI &BfmeStrVKI::assignRva00891B50(const char *s)
{
	bfmeSetVKI(s);
	return *this;
}
