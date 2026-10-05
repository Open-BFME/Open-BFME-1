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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
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

extern SkirmishGameInfo *TheSkirmishGameInfo;
class BfmeAptScreenSkirmish;
extern BfmeAptScreenSkirmish *Rva012F4B54Skirmish;
extern WindowManager *g_rva012F19E8WindowManager;	// retail [0x012F19E8]

void BfmeAptScreenSkirmish::_bfme_exit( void * )
{
	m_animation.reset();

	if( TheSkirmishGameInfo )
		TheSkirmishGameInfo->m_state.reset( true );

	void *screen = reinterpret_cast<void * &>(Rva012F4B54Skirmish);
	TheSkirmishGameInfo = 0;
	if( screen )
		g_rva012F19E8WindowManager->hideQuitMenu();
}
