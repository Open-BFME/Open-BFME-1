// Open-BFME5 conversions.

class BfmeP1040
{
public:
	virtual void bfmeVP01040();
	virtual void bfmeVP11040();
	virtual void bfmeStop1040();

	char m_bfmePad[0x4c];
	int m_bfme50;
};

extern void (__cdecl *g_bfmeFree1040)(void *p, int n);

class BfmeA1040
{
public:
	void *bfmeGo1040A(unsigned int f);

	BfmeP1040 *m_bfmeP;
};

void *BfmeA1040::bfmeGo1040A(unsigned int f)
{
	m_bfmeP->m_bfme50 = 0;
	m_bfmeP->bfmeStop1040();

	if ((f & 1) != 0)
		g_bfmeFree1040(this, 4);

	return this;
}

struct BfmeS1040
{
	int m_bfmeIdx;
	void *m_bfmeNext;
	char m_bfmePad[0x30];
	void *m_bfmeCur;
	void *m_bfmeTab[1];
	unsigned char m_bfmePad2[0x101];
	unsigned char m_bfmeData[0x3f];
	unsigned short *m_bfmeDestA;
	unsigned short *m_bfmeDestB;
};

extern void (__cdecl *g_bfmeHook1040)(BfmeS1040 *s);

extern const unsigned g_bfmeTableBZ[64];
extern unsigned g_Rva01141808[];

static const unsigned short *const g_bfmeApplyTableA =
	(const unsigned short *)g_bfmeTableBZ;
static const unsigned short *const g_bfmeApplyTableB =
	(const unsigned short *)g_Rva01141808;
extern const unsigned short g_bfmeApplyTableC[64] =
{
	47, 47, 47, 47, 45, 43, 43, 43,
	43, 43, 42, 41, 41, 40, 40, 40,
	40, 35, 35, 35, 35, 33, 33, 33,
	33, 32, 32, 32, 27, 27, 26, 26,
	25, 25, 24, 24, 23, 23, 19, 19,
	19, 19, 18, 18, 17, 16, 16, 16,
	16, 16, 15, 11, 11, 11, 10, 10,
	9, 8, 7, 5, 3, 3, 2, 2,
};
extern const short g_bfmeApplyTableD[64] =
{
	47, 47, 47, 47, 45, 43, 43, 43,
	43, 43, 42, 41, 41, 40, 40, 40,
	40, 35, 35, 35, 35, 33, 33, 33,
	33, 32, 32, 32, 27, 27, 26, 26,
	25, 25, 24, 24, 23, 23, 19, 19,
	19, 19, 18, 18, 17, 16, 16, 16,
	16, 16, 15, 11, 11, 11, 10, 10,
	9, 8, 7, 5, 3, 3, 2, 2,
};

void bfmeApply1040(BfmeS1040 *s, int)
{
	unsigned char *p = s->m_bfmeData + 1;
	int count = 0x15;

	do
	{
		s->m_bfmeDestA[p[-1]] = g_bfmeApplyTableA[s->m_bfmeIdx * 2] << 2;
		s->m_bfmeDestA[p[0]] = g_bfmeApplyTableA[s->m_bfmeIdx * 2] << 2;
		s->m_bfmeDestA[p[1]] = g_bfmeApplyTableA[s->m_bfmeIdx * 2] << 2;
		p += 3;
	}
	while (--count != 0);

	s->m_bfmeDestA[0] = g_bfmeApplyTableC[s->m_bfmeIdx] << 2;

	p = s->m_bfmeData + 1;
	count = 0x15;

	do
	{
		s->m_bfmeDestB[p[-1]] = g_bfmeApplyTableB[s->m_bfmeIdx * 2] << 2;
		s->m_bfmeDestB[p[0]] = g_bfmeApplyTableB[s->m_bfmeIdx * 2] << 2;
		s->m_bfmeDestB[p[1]] = g_bfmeApplyTableB[s->m_bfmeIdx * 2] << 2;
		p += 3;
	}
	while (--count != 0);

	s->m_bfmeDestB[0] = (unsigned short)g_bfmeApplyTableD[s->m_bfmeIdx] << 2;
}

void bfmeGo1040B(BfmeS1040 *s, int a)
{
	if (s->m_bfmeTab[s->m_bfmeIdx] == s->m_bfmeCur)
		return;

	s->m_bfmeCur = s->m_bfmeNext;
	g_bfmeHook1040(s);
	bfmeApply1040(s, a);
}

struct BfmeE1040
{
	char m_bfmePad[8];
	int m_bfmeH;
};

class BfmeD1040
{
public:
	BfmeE1040 *bfmeGet1040(void);
};

void bfmeQuery1040(int h, int *out);

class BfmeC1040
{
public:
	int bfmeGo1040C(void);

	BfmeD1040 *m_bfmeD;
};

int BfmeC1040::bfmeGo1040C(void)
{
	BfmeD1040 *d = m_bfmeD;

	if (d == 0)
		return -1;

	int r = -1;
	int h = d->bfmeGet1040()->m_bfmeH;

	bfmeQuery1040(h, &r);
	return r;
}

struct BfmeCs1040
{
	char m_bfmePad[0x18];
};

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(BfmeCs1040 *c);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(BfmeCs1040 *c);
void __stdcall bfmeFree1040E(void *p);

class BfmeK1040
{
public:
	void bfmeGo1040K(void);

	void *m_bfmeP;
	BfmeCs1040 m_bfmeCs;
};

void BfmeK1040::bfmeGo1040K(void)
{
	EnterCriticalSection(&m_bfmeCs);

	if (m_bfmeP != 0)
		bfmeFree1040E(m_bfmeP);

	m_bfmeP = 0;
	LeaveCriticalSection(&m_bfmeCs);
}

