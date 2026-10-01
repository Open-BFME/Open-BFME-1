struct BfmeSubESA
{
	unsigned char m_bfmeHead[0x24];
	int m_bfmeK;
};

class Player;

// The ledger names bfmeGoESB's parameter BfmeObjESA, so the body-facing
// stand-in keeps that spelling; the call these bodies make is retail's real
// Object::getControllingPlayer (0x001BE3F0, pinned), named on the retail type
// through a no-op pointer cast.
class Object
{
public:
	Player *getControllingPlayer() const;
};

class BfmeObjESA
{
};

struct BfmeThingESB
{
	bool bfmeGoESB(BfmeObjESA *o);
	unsigned char m_bfmeHead[8];
	void *m_bfmeP;
};

bool BfmeThingESB::bfmeGoESB(BfmeObjESA *o)
{
	return m_bfmeP == ((Object *)o)->getControllingPlayer();
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
	BfmeSubESA *s = (BfmeSubESA *)((Object *)m_bfmeP)->getControllingPlayer();
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
	BfmeSubESA *s = (BfmeSubESA *)((Object *)m_bfmeP)->getControllingPlayer();
	if (!s)
		return -1;
	return g_bfmeObjESCb->bfmeLookESC(s->m_bfmeK, 4, 0);
}
