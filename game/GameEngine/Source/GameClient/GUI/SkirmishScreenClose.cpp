// cl: /O2 /Ob0 /DNDEBUG /MD
//
// BFME Skirmish.apt close/profile-popup callback, retail 0x0057CE00.

class WindowManager
{
public:
	void unidentified_00015235( int movie, const char *function,
		int argumentCount, const void *argument1, const void *argument2,
		int unused1, int unused2, int unused3 );
	void hideQuitMenu();
};

extern WindowManager *g_theWindowManager;

class SkirmishPreferences
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void close();

	bool unidentified_00017AF8();

private:
	char m_unmodelled[ 0x50 ];
};

class SkirmishGameInfoState
{
public:
	virtual void reset( bool resetGame );
};

class SkirmishGameInfo
{
private:
	char m_unmodelled[ 0x58 ];

public:
	SkirmishGameInfoState m_state;
};

extern SkirmishGameInfo *g_bfmeCurrentCB;
extern void *g_obj12F4B54;

class BfmeAptScreenSkirmish
{
public:
	void _bfme_close( int argument );
	void _bfme_refreshProfile();

private:
	char m_unmodelled_250[ 0x250 ];
	int m_movie;
	char m_unmodelled_254[ 0x158 ];
	SkirmishPreferences m_preferences;
	int m_state;
	char m_unmodelled_404[ 5 ];
	bool m_profileOpen;
};

// ?_bfme_close@BfmeAptScreenSkirmish@@QAEXH@Z
void BfmeAptScreenSkirmish::_bfme_close( int )
{
	int state = m_state;
	if( state == 2 || state == 4 )
	{
		g_theWindowManager->unidentified_00015235(
			m_movie, "PopUpControl", 1, "close", 0, 0, 0, 0 );
		m_profileOpen = true;
		m_state = 7;
		_bfme_refreshProfile();

		if( !m_preferences.unidentified_00017AF8() )
		{
			m_preferences.close();

			if( g_bfmeCurrentCB )
				g_bfmeCurrentCB->m_state.reset( true );

			void *screen = g_obj12F4B54;
			g_bfmeCurrentCB = 0;
			if( screen )
				g_theWindowManager->hideQuitMenu();
		}
		return;
	}

	if( state != 3 )
		return;

	g_theWindowManager->unidentified_00015235(
		m_movie, "PopUpControl", 1, "close", 0, 0, 0, 0 );
	m_profileOpen = true;
	m_state = 7;
	_bfme_refreshProfile();
}
