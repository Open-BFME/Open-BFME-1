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

extern BfmeAllocFnVKI *g_bfmeAllocVKI;
extern BfmeHdrVKI g_bfmeEmptyVKI;

class BfmeStrVKI
{
public:
	void bfmeSetVKI(const char *s);
	BfmeHdrVKI *m_bfme00;
};

void BfmeStrVKI::bfmeSetVKI(const char *s)
{
	if (*s == 0)
	{
		m_bfme00 = &g_bfmeEmptyVKI;
		++g_bfmeEmptyVKI.m_bfme00;
		return;
	}
	int len = strlen(s);
	unsigned sz = (len + 0xc) & ~3;
	m_bfme00 = (BfmeHdrVKI *)(*g_bfmeAllocVKI)(sz);
	m_bfme00->m_bfme00 = 1;
	m_bfme00->m_bfme04 = (unsigned short)(sz - 9);
	m_bfme00->m_bfme02 = (unsigned short)len;
	m_bfme00->m_bfme06 = 0;
	memcpy((char *)m_bfme00 + 8, s, len + 1);
}
