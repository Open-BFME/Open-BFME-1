class BfmePlayerTG;

struct BfmeElemTG
{
	void *m_bfmeItemTG;
	unsigned char m_bfmePadTG[28];
};

class BfmeBaseTG
{
public:
	unsigned char m_bfmeHeadTG[4];
	void *m_bfmeKeyTG;
	unsigned char m_bfmeGapTG[0x24];
	BfmeElemTG m_bfmeElemsTG[1];
};

struct Rva00367E30Logic
{
	BfmePlayerTG *bfmeFindTG(void *key);
};

// Retail's GameLogic singleton (0x012F0898) is EA's `GameLogic *TheGameLogic`
// (mangled ?TheGameLogic@@3PAVGameLogic@@A, defined in GameLogic.cpp).  This TU
// keeps its own partial view of the object and casts at each use.
class GameLogic;

extern GameLogic *TheGameLogic;

struct Rva002EE330PlayerList
{
	char bfmeHasTG(BfmePlayerTG *player);
};

// ?ThePlayerList@@3PAVPlayerList@@A -- retail 0x012ED748, defined once in
// Common/RTS/PlayerList.cpp. The view above is this TU's own layout of it.
class PlayerList;
extern PlayerList *ThePlayerList;

class ControlBar
{
public:
	void bfmeSelectTG(void *item, int flag);
};

extern ControlBar *TheControlBar;

class BfmeOwnerTG
{
public:
	void bfmeShowTG(int unused);

	unsigned char m_bfmeOwnHeadTG[8];
	BfmeBaseTG *m_bfmeBaseTG;
	int m_bfmeIndexTG;
};

void BfmeOwnerTG::bfmeShowTG(int unused)
{
	BfmeBaseTG *base = m_bfmeBaseTG;
	void *item = base->m_bfmeElemsTG[m_bfmeIndexTG].m_bfmeItemTG;

	if (item == 0)
		return;

	BfmePlayerTG *player = ((Rva00367E30Logic *)TheGameLogic)->bfmeFindTG(base->m_bfmeKeyTG);

	if (player != 0)
	{
		if (ThePlayerList == 0)
			return;

		if (!((Rva002EE330PlayerList *)ThePlayerList)->bfmeHasTG(player))
			return;
	}

	TheControlBar->bfmeSelectTG(item, 0);
}
