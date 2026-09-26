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

extern Rva00367E30Logic *TheBfmeGameLogic;

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

	BfmeObjDN *o = TheBfmeGameLogic->bfmeFindDN(id);

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
