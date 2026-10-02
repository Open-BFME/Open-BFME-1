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

// Both bodies read retail's global at 0x012ED748, which is PlayerList.cpp's
// `PlayerList *ThePlayerList` (mangled ?ThePlayerList@@3PAVPlayerList@@A), so
// both references carry that one name. BfmeGlobESC is this TU's local view of
// the pointee; cast at each use.
class PlayerList;
extern PlayerList *ThePlayerList;

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
	return ((BfmeGlobESC *)ThePlayerList)->bfmeLookESC(s->m_bfmeK, 4, 0);
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
	return ((BfmeGlobESC *)ThePlayerList)->bfmeLookESC(s->m_bfmeK, 4, 0);
}
