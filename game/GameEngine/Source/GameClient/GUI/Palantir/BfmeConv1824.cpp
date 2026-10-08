class BfmePlayerTF;

struct BfmeElemTF
{
	void *m_bfmeItemTF;
	unsigned char m_bfmePadTF[28];
};

class BfmeBaseTF
{
public:
	unsigned char m_bfmeHeadTF[4];
	void *m_bfmeKeyTF;
	unsigned char m_bfmeGapTF[0x24];
	BfmeElemTF m_bfmeElemsTF[1];
};


// Retail's GameLogic singleton (0x012F0898) is EA's `GameLogic *TheGameLogic`
// (mangled ?TheGameLogic@@3PAVGameLogic@@A, defined in GameLogic.cpp).  This TU
// keeps its own partial view of the object and casts at each use.
class GameLogic;

extern GameLogic *TheGameLogic;


// ThePlayerList (retail 0x012ED748) is PlayerList*; keep the local view, cast at the use.
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

#define bfmeSelectTF(item, flag) rva004C1B60((GameWindow *)(item), (void *)(flag))

class BfmeOwnerTF
{
public:
	void bfmeShowTF(int unused);

	BfmeBaseTF *m_bfmeBaseTF;
	int m_bfmeIndexTF;
};

void BfmeOwnerTF::bfmeShowTF(int unused)
{
	BfmeBaseTF *base = m_bfmeBaseTF;
	void *item = base->m_bfmeElemsTF[m_bfmeIndexTF].m_bfmeItemTF;

	if (item == 0)
		return;

	BfmePlayerTF *player = (BfmePlayerTF *)TheGameLogic->findObjectByID((int)base->m_bfmeKeyTF);

	if (player != 0)
	{
		if (ThePlayerList == 0)
			return;

		if (!ThePlayerList->isLocalAlliedWith((Object *)player))
			return;
	}

	TheControlBar->bfmeSelectTF(item, 0);
}
