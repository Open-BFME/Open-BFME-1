// Open-BFME5 conversions.

struct BfmeT1090
{
	char m_bfmePad[8];
	int m_bfme08;
};

class BfmeS1090
{
public:
	char bfmeChk1090(void);
	char m_bfmePad[4];
};

class BfmeR1090
{
public:
	int bfmeVal1090(void);
	char m_bfmePad[0xa4];
	BfmeS1090 m_bfmeSub;
	char m_bfmePad1[0x17c];
	int m_bfme224;
	char m_bfmePad2[0x30];
	int m_bfme258;
};

class BfmeD1090
{
public:
	BfmeR1090 *bfmeLook1090(short *h);
};

class BfmeP1090
{
public:
	int bfmeNext1090(int a);
};

extern BfmeD1090 *g_bfmeD1090;
extern BfmeP1090 *g_bfmeP1090;

char __stdcall bfmeGo1090A(int a, BfmeT1090 *t)
{
	a = g_bfmeP1090->bfmeNext1090(a);
	while ((short)a) {
		BfmeR1090 *r = g_bfmeD1090->bfmeLook1090((short *)&a);

		if (r && t->m_bfme08 - 1 == r->m_bfme224)
			return 1;
	}
	return 0;
}

char __stdcall bfmeGo1090B(int a)
{
	a = g_bfmeP1090->bfmeNext1090(a);
	while ((short)a) {
		BfmeR1090 *r = g_bfmeD1090->bfmeLook1090((short *)&a);

		if (r) {
			BfmeS1090 *s = &r->m_bfmeSub;

			if (s && s->bfmeChk1090())
				return 1;
		}
	}
	return 0;
}

char __stdcall bfmeGo1090C(int a)
{
	a = g_bfmeP1090->bfmeNext1090(a);
	while ((short)a) {
		BfmeR1090 *r = g_bfmeD1090->bfmeLook1090((short *)&a);

		if (r) {
			int v = r->m_bfme258;

			if (v >= r->bfmeVal1090())
				return 1;
		}
	}
	return 0;
}
