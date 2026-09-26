// Open-BFME5 conversions.

extern "C" void *memset(void *d, int c, unsigned n);
#pragma intrinsic(memset)

struct BfmeVtVLU
{
	void *(__cdecl *m_bfmeAllocVLU)(unsigned n);
};

extern BfmeVtVLU *g_bfmeVtVLU;

struct BfmeHdrVLU
{
	unsigned short m_bfme00;
	unsigned short m_bfme02;
	unsigned short m_bfme04;
	unsigned short m_bfme06;
	char m_bfme08[1];
};

extern BfmeHdrVLU g_bfmeEmptyVLU;

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
		m_bfme00 = (BfmeHdrVLU *)g_bfmeVtVLU->m_bfmeAllocVLU(size);
		m_bfme00->m_bfme00 = 1;
		m_bfme00->m_bfme04 = (unsigned short)(size - 9);
		memset(m_bfme00->m_bfme08, c, n);
		m_bfme00->m_bfme02 = (unsigned short)n;
		m_bfme00->m_bfme06 = 0;
		m_bfme00->m_bfme08[n] = 0;
	}
	else
	{
		m_bfme00 = &g_bfmeEmptyVLU;
		++g_bfmeEmptyVLU.m_bfme00;
	}
	return this;
}
