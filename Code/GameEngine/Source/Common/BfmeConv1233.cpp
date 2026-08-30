// Open-BFME5 conversions.

struct BfmeBuf1233
{
	unsigned short m_bfme00;
	unsigned short m_bfme02;
};

struct BfmeStr1233
{
	BfmeBuf1233 *m_bfme00;
};

struct BfmeAlloc1233
{
	void *m_bfme00;
	void (__cdecl *m_bfme04)(BfmeBuf1233 *a);
};

class BfmeE1233
{
public:
	void bfmeName1233(BfmeStr1233 *a);
};

class BfmeN1233
{
public:
	unsigned m_bfme00;
	unsigned m_bfme04;
	char m_bfmePad08[0x20 - 0x08];
	void *m_bfme20;
	char m_bfmePad24[4];
	void *m_bfme28;
};

extern BfmeStr1233 g_bfmeStr1233;
extern BfmeBuf1233 g_bfmeEmpty1233;
extern BfmeAlloc1233 *g_bfmeAlloc1233;
extern BfmeE1233 **g_bfmeArr1233;
extern int g_bfmeCount1233;
extern void *g_bfmeResult1233;

extern "C" void bfmeHandler1233(void);
extern "C" void bfmeReport1233(void *a, void *b, int c, void (*d)(void));

void *bfmeVisit1233(BfmeN1233 *a, int n)
{
	BfmeE1233 *e;
	BfmeBuf1233 *buf;

	if ((a->m_bfme04 & 0x3f) == 0x16 && !((unsigned char)(~(a->m_bfme04 >> 15)) & 1) && n > 0) {
		e = g_bfmeArr1233[g_bfmeCount1233 - 1];
		e->bfmeName1233(&g_bfmeStr1233);
		bfmeReport1233(a->m_bfme20, a->m_bfme28, 4, bfmeHandler1233);
		buf = g_bfmeStr1233.m_bfme00;
		--buf->m_bfme00;
		if (buf->m_bfme00 == 0)
			g_bfmeAlloc1233->m_bfme04(buf);
		++g_bfmeEmpty1233.m_bfme00;
		g_bfmeStr1233.m_bfme00 = &g_bfmeEmpty1233;
	}
	return g_bfmeResult1233;
}
