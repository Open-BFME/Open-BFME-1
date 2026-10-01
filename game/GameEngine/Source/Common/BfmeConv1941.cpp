struct BfmeMsgDN
{
	BfmeMsgDN(int id)
	{
		m_bfmeIdDN = id;
		m_bfmeZeroDN = 0;
	}

	virtual ~BfmeMsgDN() {}

	int m_bfmeIdDN;
	int m_bfmeZeroDN;
};

class BfmeObjDN;

struct Rva00367E30Logic
{
	BfmeObjDN *bfmeFindDN(int id);
};

// retail global at 0x012F0898 is EA's `GameLogic *TheGameLogic`, defined once in
// game/GameEngine/Source/GameLogic/System/GameLogic.cpp.  Only the symbol name
// matters here; Rva00367E30Logic is this TU's view of the pointee.
class GameLogic;
extern GameLogic *TheGameLogic;

static inline Rva00367E30Logic *theBfmeGameLogic()
{
	return (Rva00367E30Logic *)TheGameLogic;
}

struct Rva002EE330PlayerList
{
	char bfmeOwnsDN(BfmeObjDN *o);
};

extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

class ControlBar
{
public:
	void bfmeShowDN(BfmeMsgDN *msg);
};

extern ControlBar *TheControlBar;

class BfmeHostDN
{
public:
	void bfmeNotifyDN(void *unused);

	unsigned char m_bfmeHeadDN[4];
	int m_bfmeIdDN;
};

void BfmeHostDN::bfmeNotifyDN(void *unused)
{
	int id = m_bfmeIdDN;

	if (id == 0)
		return;

	BfmeObjDN *o = theBfmeGameLogic()->bfmeFindDN(id);

	if (o == 0)
		return;

	if (Rva002EE330ThePlayers == 0)
		return;

	if (Rva002EE330ThePlayers->bfmeOwnsDN(o) == 0)
		return;

	int again = m_bfmeIdDN;

	BfmeMsgDN msg(again);

	TheControlBar->bfmeShowDN(&msg);
}
