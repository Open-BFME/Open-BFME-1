// Open-BFME5 conversions.

class BfmeS1096;

class BfmeR1096
{
public:
	void bfmeSet1096(int a);
	void bfmeAdj1096(int a);
	void bfmeUse1096(int a);
	void bfmeOn1096(BfmeS1096 *s);
	void bfmeOff1096(BfmeS1096 *s);
	char m_bfmePad[0x258];
	int m_bfme258;
	char m_bfmePad1[0x425];
	char m_bfme681;
};

class BfmeM1096
{
public:
	BfmeS1096 *bfmeMake1096(int a);
};

extern BfmeM1096 *g_bfmeM1096;

class BfmeD1096
{
public:
	BfmeR1096 *bfmeLook1096(short *h);
};

class BfmeP1096
{
public:
	int bfmeFirst1096(int a, int b);
};

extern BfmeD1096 *g_bfmeD1096;
extern BfmeP1096 *g_bfmeP1096;

void __stdcall bfmeGo1096A(int a, char b)
{
	a = g_bfmeP1096->bfmeFirst1096(a, 0);
	while ((short)a) {
		BfmeR1096 *r = g_bfmeD1096->bfmeLook1096((short *)&a);

		if (r)
			r->m_bfme681 = b;
	}
}

void __stdcall bfmeGo1096B(int a, int b)
{
	a = g_bfmeP1096->bfmeFirst1096(a, 0);
	while ((short)a) {
		BfmeR1096 *r = g_bfmeD1096->bfmeLook1096((short *)&a);

		if (r)
			r->bfmeSet1096(b - 1);
	}
}

void __stdcall bfmeGo1096C(int a, int b)
{
	a = g_bfmeP1096->bfmeFirst1096(a, 0);
	while ((short)a) {
		BfmeR1096 *r = g_bfmeD1096->bfmeLook1096((short *)&a);

		if (r) {
			r->bfmeAdj1096(r->m_bfme258 + b);
			r->bfmeUse1096(r->m_bfme258);
		}
	}
}

void __stdcall bfmeGo1096D(int a, int b, char c)
{
	BfmeS1096 *s = g_bfmeM1096->bfmeMake1096(b);

	if (!s)
		return;
	b = g_bfmeP1096->bfmeFirst1096(a + 0x10, 0);
	while ((short)b) {
		BfmeR1096 *r = g_bfmeD1096->bfmeLook1096((short *)&b);

		if (r) {
			if (c)
				r->bfmeOn1096(s);
			else
				r->bfmeOff1096(s);
		}
	}
}
