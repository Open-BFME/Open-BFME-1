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

class Object;

// retail global at 0x012F0898 is EA's `GameLogic *TheGameLogic`, defined once in
// game/GameEngine/Source/GameLogic/System/GameLogic.cpp; this view carries the pinned
// findObjectByID row (0x0009A510, ILT 0x0001F253).
class GameLogic
{
public:
	Object *findObjectByID(int id);
};
extern GameLogic *TheGameLogic;

// retail's player-list global at 0x012ED748 links against
// game/GameEngine/Source/Common/RTS/PlayerList.cpp's definition; this view carries the pinned
// isLocalAlliedWith row (0x000DF810, ILT 0x00003A85).
class PlayerList
{
public:
	unsigned char isLocalAlliedWith(Object *o);
};
extern PlayerList *ThePlayerList;

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

	Object *o = TheGameLogic->findObjectByID(id);

	if (o == 0)
		return;

	if (ThePlayerList == 0)
		return;

	if (ThePlayerList->isLocalAlliedWith(o) == 0)
		return;

	int again = m_bfmeIdDN;

	BfmeMsgDN msg(again);

	TheControlBar->bfmeShowDN(&msg);
}
