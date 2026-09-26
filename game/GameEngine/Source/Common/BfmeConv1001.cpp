// Open-BFME5 conversions.

class BfmeX1001
{
public:
	void *bfmeOwner1001();
};

struct BfmeY1001
{
	char m_bfmePad[0x344];
	char m_bfmeFlags;
};

class BfmeLook1001
{
public:
	BfmeX1001 *bfmeFindA1001(int id);
	BfmeY1001 *bfmeFindB1001(int id);
};

extern BfmeLook1001 *g_bfmeLook1001;

class BfmeA1001
{
public:
	void bfmeGo1001A(void *a);

	char m_bfmePad[8];
	int m_bfmeId;
};

void BfmeA1001::bfmeGo1001A(void *a)
{
	int id = m_bfmeId;

	if (!id)
		return;

	BfmeX1001 *x = g_bfmeLook1001->bfmeFindA1001(id);

	if (x && x->bfmeOwner1001() == a)
		return;

	m_bfmeId = 0;
}

class BfmeUnit1001
{
public:
	char bfmeReady1001();
	char bfmeKind1001(int k);
};

struct BfmeHold1001
{
	char m_bfmePad[0x10];
	BfmeUnit1001 *m_bfmeUnit;
	char m_bfmePad2[0x2c];
	char m_bfmeBusy;
};

class BfmeSink1001
{
public:
	virtual void bfmeVS01001();
	virtual void bfmeVS11001();
	virtual void bfmeVS21001();
	virtual void bfmeVS31001();
	virtual int bfmeRun1001();
};

class BfmeC1001
{
public:
	int bfmeGo1001C();
	int bfmeGo1001D();

	char m_bfmePad[0x1c];
	BfmeHold1001 *m_bfmeHold;
	char m_bfmePad2[4];
	BfmeSink1001 *m_bfmeSink;
};

int BfmeC1001::bfmeGo1001C()
{
	if (!m_bfmeSink)
		return -2;

	BfmeUnit1001 *u = m_bfmeHold->m_bfmeUnit;

	if (u->bfmeReady1001() && !u->bfmeKind1001(0x19))
		return -2;

	m_bfmeHold->m_bfmeBusy = 1;

	int r = m_bfmeSink->bfmeRun1001();

	m_bfmeHold->m_bfmeBusy = 0;
	return r;
}
int BfmeC1001::bfmeGo1001D()
{
	if (!m_bfmeSink)
		return -2;

	BfmeUnit1001 *u = m_bfmeHold->m_bfmeUnit;

	if (u->bfmeReady1001() && !u->bfmeKind1001(0x19))
		return -2;

	m_bfmeHold->m_bfmeBusy = 1;

	int r = m_bfmeSink->bfmeRun1001();

	m_bfmeHold->m_bfmeBusy = 0;
	return r;
}
