// Open-BFME5 conversions.

class BfmeRun1006
{
public:
	void bfmeRun1006();
};

class BfmeStop1006
{
public:
	void bfmeStop1006();
};

extern BfmeRun1006 *g_bfmeRun1006;
extern BfmeStop1006 *g_bfmeStop1006;
extern char g_bfmeFlag1006;

class BfmeA1006
{
public:
	void bfmeGo1006A();

	char m_bfmePad[0x3d];
	char m_bfmeDone;
	char m_bfmePad2[2];
	int m_bfmeVal;
};

void BfmeA1006::bfmeGo1006A()
{
	if (m_bfmeDone)
		return;
	if (!m_bfmeVal)
		return;

	if (!g_bfmeRun1006) {
		g_bfmeStop1006->bfmeStop1006();
		g_bfmeFlag1006 = 1;
		return;
	}

	g_bfmeRun1006->bfmeRun1006();
}

struct BfmeObj1006
{
	char m_bfmePad[0x254];
	char m_bfmeFlag;
};

struct BfmeAux1006
{
	char m_bfmePad[0x50];
	char m_bfmeFlag;
};

class BfmeHub1006
{
public:
	void bfmeDo1006();
};

extern BfmeObj1006 *g_bfmeObj1006;
extern BfmeAux1006 *g_bfmeAux1006;
extern BfmeHub1006 *g_bfmeHub1006;

class BfmeB1006
{
public:
	void bfmeGo1006B(int unused);

	char m_bfmePad[0x25a];
	char m_bfmeWant;
};

void BfmeB1006::bfmeGo1006B(int unused)
{
	if (!m_bfmeWant)
		return;

	BfmeObj1006 *p = g_bfmeObj1006;

	if (p && !p->m_bfmeFlag) {
		p->m_bfmeFlag = 1;
		g_bfmeAux1006->m_bfmeFlag = 1;
		g_bfmeHub1006->bfmeDo1006();
	}

	m_bfmeWant = 0;
}
