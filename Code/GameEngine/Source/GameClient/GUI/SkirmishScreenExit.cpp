// cl: /O2 /Ob0 /DNDEBUG /MD
//
// Retail 0x005791C0: finish the Skirmish APT animation and release the
// currently published skirmish game-info object before hiding the quit menu.

class AptAnimation
{
public:
	virtual void slot0( void );
	virtual void slot1( void );
	virtual void slot2( void );
	virtual void reset( void );
};

class SkirmishGameInfoState
{
public:
	virtual void reset( bool );
};

class SkirmishGameInfo
{
private:
	char m_pad[ 0x58 ];

public:
	SkirmishGameInfoState m_state;
};

class WindowManager
{
public:
	void hideQuitMenu( void );
};

class BfmeAptScreenSkirmish
{
public:
	void _bfme_exit( void *argument );

private:
	char m_pad[ 0x3AC ];
	AptAnimation m_animation;
};

extern SkirmishGameInfo *g_bfmeCurrentCB;
extern void *g_obj12F4B54;
extern WindowManager *g_theWindowManager;

void BfmeAptScreenSkirmish::_bfme_exit( void * )
{
	m_animation.reset();

	if( g_bfmeCurrentCB )
		g_bfmeCurrentCB->m_state.reset( true );

	void *screen = g_obj12F4B54;
	g_bfmeCurrentCB = 0;
	if( screen )
		g_theWindowManager->hideQuitMenu();
}
