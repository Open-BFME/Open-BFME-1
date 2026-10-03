// Open-BFME5 conversions.
// stlport

#include "Thing/GameLogicObjectLookup.h"

class Player;
#define OBJECT_TU_MEMBERS Player *getControllingPlayer() const;
#include "../GameLogic/Object/object.h"
#undef OBJECT_TU_MEMBERS

struct BfmeStateA979
{
	char m_bfmePad[0x10c];
	int m_bfmeMode;
};

class WindowManager
{
public:
	void bfme_showBackground(int kind);
};

class Shell
{
public:
	bool showShellMap(bool useShellMap);
};

// Retail [0x012F0898] is EA's GameLogic *TheGameLogic (see
// game/GameEngine/Source/GameLogic/System/GameLogic.cpp); the canonical
// declaration is what links. Only the +0x10c mode slot of this TU's view is
// recovered, so the view is cast at each use.
class GameLogic;
extern GameLogic *TheGameLogic;

// Retail 0x012F19E8 is the game-wide manager pointer EA defines as
// `WindowManager *g_rva012F19E8WindowManager` in
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp. This TU only needs
// the background-kind call at ILT 0x00009494, defined by AptScreenFactories.cpp.
extern WindowManager *g_rva012F19E8WindowManager;

extern Shell *TheShell;

char bfmeGo979A(void)
{
	if (!((BfmeStateA979 *)TheGameLogic) || !TheShell || ((BfmeStateA979 *)TheGameLogic)->m_bfmeMode == 4
			|| !TheShell->showShellMap(true))
		return 1;

	g_rva012F19E8WindowManager->bfme_showBackground(1);
	return 0;
}

class TunnelTracker
{
public:
	void onTunnelCreated(const Object *object);
};

struct BfmeX979
{
	char m_bfmePad[0x22c];
	TunnelTracker *m_bfmeSink;
};

class BfmeB979
{
public:
	virtual void bfmeV0979B();
	virtual void bfmeV1979B();
	virtual char bfmeReady979B();

	void bfmeGo979B();

	char m_bfmePad[0x9c];
	char m_bfmeFlagA;
	char m_bfmeFlagB;
};

void BfmeB979::bfmeGo979B()
{
	if (!bfmeReady979B())
		return;

	Object *k = *(Object **)((char *)this - 0x2c);
	m_bfmeFlagA = 0;

	BfmeX979 *x = (BfmeX979 *)k->getControllingPlayer();
	if (!x)
		return;

	TunnelTracker *s = x->m_bfmeSink;
	if (!s)
		return;

	s->onTunnelCreated(*(Object **)((char *)this - 0x2c));
	m_bfmeFlagB = 1;
}

class BfmeC979
{
public:
	void bfmeGo979C();

	char m_bfmePad[0x338];
	char m_bfmeFlag;
	char m_bfmePad2[0xb];
	ObjectID m_bfmeA;
	ObjectID m_bfmeB;
	ObjectID m_bfmeC;
};

void BfmeC979::bfmeGo979C()
{
	GameLogic *g = TheGameLogic;

	if (!g->findObjectByID(m_bfmeA) && !g->findObjectByID(m_bfmeB)
			&& !g->findObjectByID(m_bfmeC))
		m_bfmeFlag = 0;
}
