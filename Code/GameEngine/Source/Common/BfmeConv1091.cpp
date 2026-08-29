// Open-BFME5 conversions.

struct BfmeB1091
{
	char m_bfmePad[0x3c];
	unsigned int m_bfme3c;
};

struct BfmeM1091
{
	char m_bfmePad[0x11f8];
	float m_bfme11f8;
};

class BfmeR1091
{
public:
	char bfmeHas1091(int a);
	char bfmeChk1091(void);
	char bfmeTest1091(int a);
};

class BfmeD1091
{
public:
	BfmeR1091 *bfmeLook1091(short *h);
};

class BfmeP1091
{
public:
	int bfmeNext1091(int a);
};

class BfmeC1091
{
public:
	int bfmeFind1091(int a);
};

extern BfmeB1091 *g_bfmeB1091;
extern BfmeM1091 *g_bfmeM1091;
extern BfmeC1091 *g_bfmeC1091;
extern BfmeD1091 *g_bfmeD1091;
extern BfmeP1091 *g_bfmeP1091;

char __stdcall bfmeGo1091A(int a, int b)
{
	int e = g_bfmeC1091->bfmeFind1091(b + 0x10);

	if (e == -1)
		return 0;
	b = g_bfmeP1091->bfmeNext1091(a);
	while ((short)b) {
		BfmeR1091 *r = g_bfmeD1091->bfmeLook1091((short *)&b);

		if (r && r->bfmeHas1091(e))
			return 1;
	}
	return 0;
}

char __stdcall bfmeGo1091B(int a)
{
	unsigned int n = g_bfmeB1091->m_bfme3c;

	if (n < (unsigned int)(int)(g_bfmeM1091 ? g_bfmeM1091->m_bfme11f8 * 5.0f : 25.0f))
		return 0;
	a = g_bfmeP1091->bfmeNext1091(a);
	while ((short)a) {
		BfmeR1091 *r = g_bfmeD1091->bfmeLook1091((short *)&a);

		if (r && r->bfmeChk1091())
			return 0;
	}
	return 1;
}

char __stdcall bfmeGo1091C(int a)
{
	unsigned int n = g_bfmeB1091->m_bfme3c;

	if (n < (unsigned int)(int)(g_bfmeM1091 ? g_bfmeM1091->m_bfme11f8 * 5.0f : 25.0f))
		return 0;
	a = g_bfmeP1091->bfmeNext1091(a);
	while ((short)a) {
		BfmeR1091 *r = g_bfmeD1091->bfmeLook1091((short *)&a);

		if (r && r->bfmeTest1091(0))
			return 0;
	}
	return 1;
}
