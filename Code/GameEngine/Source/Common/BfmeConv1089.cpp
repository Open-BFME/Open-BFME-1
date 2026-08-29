// Open-BFME5 conversions.

struct BfmeT1089
{
	char m_bfmePad[8];
	int m_bfme08;
};

class BfmeR1089
{
public:
	char bfmeChk1089(void);
	int bfmeVal1089(void);
	char m_bfmePad[0x264];
	int m_bfme264;
};

class BfmeD1089
{
public:
	BfmeR1089 *bfmeLook1089(short *h);
};

class BfmeP1089
{
public:
	int bfmeNext1089(int a);
};

extern BfmeD1089 *g_bfmeD1089;
extern BfmeP1089 *g_bfmeP1089;

char __stdcall bfmeGo1089A(int a, int t)
{
	int n = ((BfmeT1089 *)t)->m_bfme08;

	t = g_bfmeP1089->bfmeNext1089(a);
	while ((short)t) {
		BfmeR1089 *r = g_bfmeD1089->bfmeLook1089((short *)&t);

		if (r && r->m_bfme264 >= n)
			return 1;
	}
	return 0;
}

char __stdcall bfmeGo1089B(int a)
{
	a = g_bfmeP1089->bfmeNext1089(a);
	while ((short)a) {
		BfmeR1089 *r = g_bfmeD1089->bfmeLook1089((short *)&a);

		if (r && r->bfmeChk1089())
			return 1;
	}
	return 0;
}

char __stdcall bfmeGo1089C(BfmeT1089 *t, int a)
{
	int n;

	a = g_bfmeP1089->bfmeNext1089(a);
	n = 0;
	while ((short)a) {
		BfmeR1089 *r = g_bfmeD1089->bfmeLook1089((short *)&a);

		if (r)
			n += r->bfmeVal1089();
	}
	return t->m_bfme08 >= n;
}
