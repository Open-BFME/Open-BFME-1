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


// Retail's GameLogic singleton (0x012F0898) is EA's `GameLogic *TheGameLogic`
// (mangled ?TheGameLogic@@3PAVGameLogic@@A, defined in GameLogic.cpp).  This TU
// keeps its own partial view of the object and casts at each use.
class GameLogic;

extern GameLogic *TheGameLogic;


// ?ThePlayerList@@3PAVPlayerList@@A -- retail 0x012ED748, defined once in
// Common/RTS/PlayerList.cpp. The view above is this TU's own layout of it.
class PlayerList;
extern PlayerList *ThePlayerList;

class ControlBar;

extern ControlBar *TheControlBar;

// Callees (tools/callees.py): ILT 0x1F253 -> 0x0009A510 GameLogic::findObjectByID,
// ILT 0x3A85 -> 0x000DF810 PlayerList::isLocalAlliedWith, ILT 0x3BCCD ->
// 0x004C1B60 ControlBar::rva004C1B60.
class Object;
class GameWindow;

class GameLogic
{
public:
	Object *findObjectByID(int id);
};

class PlayerList
{
public:
	unsigned char isLocalAlliedWith(Object *obj);
};

class ControlBar
{
public:
	void rva004C1B60(GameWindow *window, void *data);
};

#define bfmeSelectTG(item, flag) rva004C1B60((GameWindow *)(item), (void *)(flag))

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

	BfmePlayerTG *player = (BfmePlayerTG *)TheGameLogic->findObjectByID((int)base->m_bfmeKeyTG);

	if (player != 0)
	{
		if (ThePlayerList == 0)
			return;

		if (!ThePlayerList->isLocalAlliedWith((Object *)player))
			return;
	}

	TheControlBar->bfmeSelectTG(item, 0);
}
