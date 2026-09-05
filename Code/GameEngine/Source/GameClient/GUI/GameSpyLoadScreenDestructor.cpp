// cl: /DNDEBUG /MD
// GameSpyLoadScreen destructor. Offsets from landed processProgress
// (bars +0x10, lookup +0x154) and the ZH dtor loop in LoadScreen.cpp.

class Gen_0051b720Base
{
public:
	virtual void slot0();
	~Gen_0051b720Base();
};

class GameWindow;

enum { MAX_SLOTS = 8 };

class GameSpyLoadScreen : public Gen_0051b720Base
{
public:
	virtual ~GameSpyLoadScreen();

private:
	char m_baseTail[0x0C];
	GameWindow *m_progressBars[MAX_SLOTS];
	GameWindow *m_playerNames[MAX_SLOTS];
	GameWindow *m_playerSide[MAX_SLOTS];
	GameWindow *m_playerFavoriteFactions[MAX_SLOTS];
	GameWindow *m_playerTotalDisconnects[MAX_SLOTS];
	GameWindow *m_playerWin[MAX_SLOTS];
	GameWindow *m_playerWinLosses[MAX_SLOTS];
	GameWindow *m_playerRank[MAX_SLOTS];
	GameWindow *m_playerOfficerMedal[MAX_SLOTS];
	GameWindow *m_mapPreview;
	GameWindow *m_buttonMapStartPosition[MAX_SLOTS];
	int m_playerLookup[MAX_SLOTS];
};

GameSpyLoadScreen::~GameSpyLoadScreen()
{
	for (int i = 0; i < MAX_SLOTS; ++i)
	{
		m_progressBars[i] = 0;
		m_playerNames[i] = 0;
		m_playerSide[i] = 0;
		m_playerLookup[i] = -1;
		m_playerFavoriteFactions[i] = 0;
		m_playerTotalDisconnects[i] = 0;
		m_playerWin[i] = 0;
		m_playerWinLosses[i] = 0;
	}
}
