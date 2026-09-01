// Open-BFME5 conversions.

extern "C" void *memcpy(void *d, const void *s, unsigned n);
#pragma intrinsic(memcpy)

struct BfmeHdrVKJ
{
	unsigned short m_bfme00;
	unsigned short m_bfme02;
};

struct BfmeAllocVKJ
{
	void *(__cdecl *m_bfmeAlloc)(unsigned n);
	void (__cdecl *m_bfmeFree)(void *p);
};

extern BfmeAllocVKJ *g_bfmeAllocVKJ;

class BfmeStrVKJ
{
public:
	BfmeStrVKJ *bfmeAssignVKJ(const BfmeStrVKJ &o);
	void bfmeReserveVKJ(unsigned a, int b, unsigned c, int d, unsigned e);
	BfmeHdrVKJ *m_bfme00;
};

BfmeStrVKJ *BfmeStrVKJ::bfmeAssignVKJ(const BfmeStrVKJ &o)
{
	unsigned len = m_bfme00->m_bfme02;
	if (len == 0)
	{
		++o.m_bfme00->m_bfme00;
		BfmeHdrVKJ *h = m_bfme00;
		if (--h->m_bfme00 == 0)
			g_bfmeAllocVKJ->m_bfmeFree(h);
		m_bfme00 = o.m_bfme00;
		return this;
	}
	unsigned olen = o.m_bfme00->m_bfme02;
	if (olen != 0)
	{
		unsigned total = olen + len;
		bfmeReserveVKJ(total, 0, len, 0, total);
		memcpy((char *)m_bfme00 + len + 8, (char *)o.m_bfme00 + 8, olen + 1);
	}
	return this;
}
