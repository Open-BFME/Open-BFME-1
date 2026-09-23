// ?input@AptMainMenu@@UAEHIII@Z
// partial score=0.571776 date=2026-09-23
// cl: /DNDEBUG /MD /EHsc

#include <stdlib.h>

class WindowManager
{
public:
	void *_bfme_callAptFunction( unsigned int level, const char *functionName,
		int argCount, const char *a0, const char *a1, const char *a2,
		const char *a3, const char *a4 );
};

extern WindowManager *g_theWindowManager;

class Mouse
{
public:
	void _bfme_setEngineVisibility( bool visible );
};

extern Mouse *TheMouse;

class AptMainMenu
{
public:
	virtual ~AptMainMenu();
	virtual int input( unsigned int message, unsigned int data, unsigned int state );
	void BattleSchool( void *unused );

private:
	unsigned char m_unmodelled04[ 0x24C ];
	unsigned int m_field250;
	unsigned char m_unmodelled254[ 5 ];
	unsigned char m_b259;
	unsigned char m_b25a;
	unsigned char m_unmodelled25b[ 5 ];
	int m_z260;
	int m_i264;
};

__declspec(noinline) AptMainMenu::~AptMainMenu() {}

// ?input@AptMainMenu@@UAEHIII@Z
int AptMainMenu::input( unsigned int message, unsigned int data, unsigned int state )
{
	if ( m_i264 == 8 )
		return 0;

	if ( m_b259 )
	{
		if ( message != 0x15 || (unsigned char)data - 1 != 0 )
			return 0;

		if ( ( state & 1 ) == 0 )
			return 1;

		if ( m_i264 == 1 || m_i264 == 2 )
			return 1;

		if ( m_i264 == 4 )
		{
			g_theWindowManager->_bfme_callAptFunction(
				m_field250, "MainMenuLevel", 0, 0, 0, 0, 0, 0 );
			return 1;
		}

		if ( m_i264 == 7 )
		{
			BattleSchool( 0 );
			return 1;
		}

		g_theWindowManager->_bfme_callAptFunction(
			m_field250, "MainMenuContinueCampaign", 0, 0, 0, 0, 0, 0 );

		return 1;
	}

	if ( m_b25a )
		m_b259 = 1;

	if ( message == 0x15 )
	{
		if ( m_i264 != 4 )
			m_b259 = 1;
	}
	else if ( message == 0x18 )
	{
		int y = (int)( data >> 16 );
		int x = (int)( data & 0xffff );

		if ( x != 0 || y != 0 )
		{
			unsigned int flags = *(unsigned int *)0x012F49C0;
			if ( ( flags & 1 ) == 0 )
			{
				flags |= 1;
				*(unsigned int *)0x012F49C0 = flags;
				*(int *)0x012F49BC = x;
			}
			if ( ( flags & 2 ) == 0 )
			{
				flags |= 2;
				*(unsigned int *)0x012F49C0 = flags;
				*(int *)0x012F49B8 = y;
			}

			if ( abs( x - *(int *)0x012F49BC ) > 20 ||
				abs( y - *(int *)0x012F49B8 ) > 20 )
				m_b259 = 1;
		}
	}

	if ( m_b259 )
	{
		TheMouse->_bfme_setEngineVisibility( true );
		m_b259 = 1;
		g_theWindowManager->_bfme_callAptFunction(
			m_field250, "BlinkBattleSchoolOff", 0, 0, 0, 0, 0, 0 );
	}

	return 0;
}
