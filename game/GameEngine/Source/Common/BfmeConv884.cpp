struct BfmeSubESA
{
	unsigned char m_bfmeHead[0x24];
	int m_bfmeK;
};

class BfmeObjESA
{
public:
	BfmeSubESA *bfmeGetESA();
};

struct BfmeThingESB
{
	bool bfmeGoESB(BfmeObjESA *o);
	unsigned char m_bfmeHead[8];
	void *m_bfmeP;
};

bool BfmeThingESB::bfmeGoESB(BfmeObjESA *o)
{
	return m_bfmeP == o->bfmeGetESA();
}

class BfmeGlobESC
{
public:
	unsigned short bfmeLookESC(int k, int n, int f);
};

extern BfmeGlobESC *g_bfmeObjESCa;
extern BfmeGlobESC *g_bfmeObjESCb;

struct BfmeThingESCa
{
	int bfmeGoESCa();
	unsigned char m_bfmeHead[8];
	BfmeObjESA *m_bfmeP;
};

int BfmeThingESCa::bfmeGoESCa()
{
	BfmeSubESA *s = m_bfmeP->bfmeGetESA();
	if (!s)
		return -1;
	return g_bfmeObjESCa->bfmeLookESC(s->m_bfmeK, 4, 0);
}

struct BfmeThingESCb
{
	int bfmeGoESCb();
	unsigned char m_bfmeHead[8];
	BfmeObjESA *m_bfmeP;
};

int BfmeThingESCb::bfmeGoESCb()
{
	BfmeSubESA *s = m_bfmeP->bfmeGetESA();
	if (!s)
		return -1;
	return g_bfmeObjESCb->bfmeLookESC(s->m_bfmeK, 4, 0);
}
