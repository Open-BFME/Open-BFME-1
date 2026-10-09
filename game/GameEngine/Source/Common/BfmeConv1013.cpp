// Open-BFME5 conversions.

class GameWindow
{
public:
	int winEnable(bool enable);
};

class BfmeA1013
{
public:
	void bfmeGo1013A(int unused);

	char m_bfmePad[0x188];
	int m_bfmeState;
	char m_bfmePad2[0x14];
	GameWindow *m_bfmeA;
	GameWindow *m_bfmeB;
};

void BfmeA1013::bfmeGo1013A(int unused)
{
	int s = m_bfmeState;

	if (s == 2 || s == 3) {
		m_bfmeA->winEnable(false);
		m_bfmeB->winEnable(false);
		m_bfmeState = 4;
	}
}

class BfmeHub1013
{
public:
	virtual void bfmeVH01013();
	virtual void bfmeVH11013();
	virtual void bfmeVH21013();
	virtual void bfmeVH31013();
	virtual void bfmeReset1013();
};

// Retail 0x012F3330 is EA's GameWindowTransitionsHandler *TheTransitionHandler;
// BfmeHub1013 is this TU's view of the object, so the use casts.
class GameWindowTransitionsHandler;

extern GameWindowTransitionsHandler *TheTransitionHandler;

void _bfme_leaveScoreScreen();

class BfmeB1013
{
public:
	int bfmeGo1013B();

	char m_bfmePad[0x258];
	int m_bfmeMode;
	char m_bfmePad2[5];
	char m_bfmeFlag;
};

int BfmeB1013::bfmeGo1013B()
{
	if (m_bfmeFlag) {
		m_bfmeFlag = 0;
		_bfme_leaveScoreScreen();
		return 1;
	}

	if (m_bfmeMode == 1) {
		((BfmeHub1013 *)TheTransitionHandler)->bfmeReset1013();
		m_bfmeMode = 0;
	}

	return 1;
}

// TU-local view of the retail WindowManager; the global below is the real class.
class BfmeLevelAN
{
public:
	char *bfmeBuildAN(unsigned int level, int p2, int p3, int p4, int p5, int p6, int p7, int p8);
};

class WindowManager;

// retail 0x012F19E8; the single definition is
// game/GameEngine/Source/GameClient/GUI/WindowManager.cpp
extern WindowManager *g_rva012F19E8WindowManager;

class BfmeAptScreenLanLobby
{
public:
	bool refreshLanGameRva00519CB0();
};

class AptLanLobby
{
public:
	void OnGameJoin();

	char m_bfmePad[0x250];
	int m_bfmeId;
	char m_bfmePad2[0x154];
	int m_bfmeState;
};

void AptLanLobby::OnGameJoin()
{
	if (m_bfmeState != 8)
		return;

	if (((BfmeAptScreenLanLobby *)this)->refreshLanGameRva00519CB0()) {
		((BfmeLevelAN *)g_rva012F19E8WindowManager)->bfmeBuildAN((unsigned int)m_bfmeId, (int)"JoinGame", 0, 0, 0, 0, 0, 0);
		m_bfmeState = 9;
	} else {
		m_bfmeState = 1;
	}
}
