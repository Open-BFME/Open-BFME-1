// Open-BFME5 conversions.

struct BfmeObj985
{
	char m_bfmePad[0x254];
	char m_bfmeFlag;
	char m_bfmePad2[7];
	int m_bfmeMode;
};

struct BfmeAux985
{
	char m_bfmePad[0x50];
	char m_bfmeFlag;
};

class BfmeHub985
{
public:
	void bfmeDo985();
};

extern BfmeObj985 *g_bfmeObj985;
extern BfmeAux985 *g_bfmeAux985;
extern BfmeHub985 *g_bfmeHub985;

class BfmeA985
{
public:
	void bfmeGo985A(int unused);

	char m_bfmePad[0x258];
	char m_bfmeOwn;
};

void BfmeA985::bfmeGo985A(int unused)
{
	m_bfmeOwn = 1;

	BfmeObj985 *p = g_bfmeObj985;

	if (!p)
		return;
	if (p->m_bfmeFlag)
		return;

	p->m_bfmeFlag = 1;
	g_bfmeObj985->m_bfmeMode = 2;
	g_bfmeAux985->m_bfmeFlag = 1;
	g_bfmeHub985->bfmeDo985();
}

void __stdcall bfmeGo985B(int unused)
{
	BfmeObj985 *p = g_bfmeObj985;

	if (!p)
		return;
	if (p->m_bfmeFlag)
		return;

	p->m_bfmeFlag = 1;
	g_bfmeObj985->m_bfmeMode = 0;
	g_bfmeAux985->m_bfmeFlag = 1;
	g_bfmeHub985->bfmeDo985();
}

class BfmeArg985
{
public:
	char bfmeHas985C(int v);
	char bfmeBlocked985C(int v);
};

class BfmeC985
{
public:
	char bfmeGo985C(BfmeArg985 *a);

	char m_bfmePad[8];
	int m_bfmeVal;
};

char BfmeC985::bfmeGo985C(BfmeArg985 *a)
{
	if (a->bfmeHas985C(m_bfmeVal) && !a->bfmeBlocked985C(m_bfmeVal))
		return 1;

	return 0;
}
