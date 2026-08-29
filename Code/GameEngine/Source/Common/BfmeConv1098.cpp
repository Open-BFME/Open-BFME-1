// Open-BFME5 conversions.

struct BfmeQ1098
{
	char m_bfmePad[0xbd];
	char m_bfmebd;
};

class BfmeR1098
{
public:
	char bfmeOk1098(void);
	int bfmeEach1098(void *f, void *ctx);
	char m_bfmePad[4];
	BfmeQ1098 *m_bfme04;
};

class BfmeD1098
{
public:
	BfmeR1098 *bfmeLook1098(short *h);
	int bfmeStart1098(int a, int b, int c);
};

extern BfmeD1098 *g_bfmeD1098;

BfmeR1098 *bfmeGo1098A(short *h)
{
	while (*h) {
		BfmeR1098 *r = g_bfmeD1098->bfmeLook1098(h);

		if (r && r->bfmeOk1098() && r->m_bfme04 && r->m_bfme04->m_bfmebd)
			return r;
	}
	return 0;
}

class BfmeCtx1098
{
public:
	void bfmeInit1098(int a, int b);
	char m_bfmePad[0x18];
	char m_bfme18;
	char m_bfmePad1[3];
};

void __cdecl bfmeCb1098(void);

char bfmeGo1098B(int a, int b, int c)
{
	BfmeCtx1098 ctx;
	int h;

	h = g_bfmeD1098->bfmeStart1098(a, 3, 0);
	ctx.bfmeInit1098(b, c);
	while ((short)h) {
		BfmeR1098 *r = g_bfmeD1098->bfmeLook1098((short *)&h);

		if (r && !r->bfmeEach1098((void *)bfmeCb1098, &ctx))
			return 0;
	}
	return ctx.m_bfme18;
}
