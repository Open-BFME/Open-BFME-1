// Open-BFME5 conversions.

struct BfmeStateA979
{
	char m_bfmePad[0x10c];
	int m_bfmeMode;
};

class BfmeActA979
{
public:
	void bfmeDo979A(int a);
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
// the call through it, so the pointee stays the local BfmeActA979 view and the
// access is cast at the use.
class WindowManager;
extern WindowManager *g_rva012F19E8WindowManager;

extern Shell *TheShell;

char bfmeGo979A(void)
{
	if (!((BfmeStateA979 *)TheGameLogic) || !TheShell || ((BfmeStateA979 *)TheGameLogic)->m_bfmeMode == 4
			|| !TheShell->showShellMap(true))
		return 1;

	((BfmeActA979 *)g_rva012F19E8WindowManager)->bfmeDo979A(1);
	return 0;
}

class BfmeKey979;

class BfmeSink979
{
public:
	void bfmeSend979B(BfmeKey979 *k);
};

struct BfmeX979
{
	char m_bfmePad[0x22c];
	BfmeSink979 *m_bfmeSink;
};

class BfmeKey979
{
public:
	BfmeX979 *bfmeGet979B();
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

	BfmeKey979 *k = *(BfmeKey979 **)((char *)this - 0x2c);
	m_bfmeFlagA = 0;

	BfmeX979 *x = k->bfmeGet979B();
	if (!x)
		return;

	BfmeSink979 *s = x->m_bfmeSink;
	if (!s)
		return;

	s->bfmeSend979B(*(BfmeKey979 **)((char *)this - 0x2c));
	m_bfmeFlagB = 1;
}

class BfmeThing979;

class BfmeLook979
{
public:
	void *bfmeFind979C(BfmeThing979 *t);
};



class BfmeC979
{
public:
	void bfmeGo979C();

	char m_bfmePad[0x338];
	char m_bfmeFlag;
	char m_bfmePad2[0xb];
	BfmeThing979 *m_bfmeA;
	BfmeThing979 *m_bfmeB;
	BfmeThing979 *m_bfmeC;
};

void BfmeC979::bfmeGo979C()
{
	BfmeLook979 *g = (BfmeLook979 *)TheGameLogic;

	if (!g->bfmeFind979C(m_bfmeA) && !g->bfmeFind979C(m_bfmeB)
			&& !g->bfmeFind979C(m_bfmeC))
		m_bfmeFlag = 0;
}
