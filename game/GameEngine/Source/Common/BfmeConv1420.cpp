// Open-BFME5 conversions.

extern "C" void *memset(void *d, int c, unsigned n);
#pragma intrinsic(memset)

struct BfmeVtVLU
{
	void *(__cdecl *m_bfmeAllocVLU)(unsigned n);
};

// The allocator pair pointer at VA 0x01337A30 is defined once, as
// g_rva01337A30AllocPair, in game/Libraries/Source/Apt/Apt.cpp.
struct BfmeStringPool3AF0;
extern struct BfmeStringPool3AF0 *g_rva01337A30AllocPair;

struct BfmeHdrVLU
{
	unsigned short m_bfme00;
	unsigned short m_bfme02;
	unsigned short m_bfme04;
	unsigned short m_bfme06;
	char m_bfme08[1];
};

// The shared empty EA string block at 0x012D5298 is defined once, as
// EAStringC::StringDataC, in game/GameEngine/Source/Common/Data/Rva012D5298.cpp;
// this TU keeps its own local view of the block and casts at each use.
class EAStringC
{
public:
	class StringDataC;
};
extern EAStringC::StringDataC g_rva012D5298Empty;

class BfmeStrVLU
{
public:
	BfmeStrVLU *bfmeInitVLU(int c, unsigned n);
	BfmeHdrVLU *m_bfme00;
};

BfmeStrVLU *BfmeStrVLU::bfmeInitVLU(int c, unsigned n)
{
	if (n != 0)
	{
		unsigned size = (n + 0xc) & ~3u;
		m_bfme00 = (BfmeHdrVLU *)((BfmeVtVLU *)g_rva01337A30AllocPair)->m_bfmeAllocVLU(size);
		m_bfme00->m_bfme00 = 1;
		m_bfme00->m_bfme04 = (unsigned short)(size - 9);
		memset(m_bfme00->m_bfme08, c, n);
		m_bfme00->m_bfme02 = (unsigned short)n;
		m_bfme00->m_bfme06 = 0;
		m_bfme00->m_bfme08[n] = 0;
	}
	else
	{
		m_bfme00 = (BfmeHdrVLU *)&g_rva012D5298Empty;
		++((BfmeHdrVLU *)&g_rva012D5298Empty)->m_bfme00;
	}
	return this;
}
