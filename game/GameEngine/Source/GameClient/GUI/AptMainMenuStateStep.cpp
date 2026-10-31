// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
//
// Retail 0x0051D700, 484 bytes: slots 5 and 6 of BfmeAptScreenMainMenu's
// vtable (0x011061C4, through ILT 0x000026A8), installed by the matched
// constructor at 0x0051F3A0.  It steps the main menu's pending state at
// +0x264: state 1 hides the shell and, when the "00000000.sav" check passes,
// restarts the engine side and shows the shell again (otherwise moves to
// state 2); state 4 refreshes the credits sink and hides the credits
// movie; state 5 runs the firewall helper at +0x268 and either starts
// multiplayer or raises the no-admin message box, then like state 6 clears
// the state.  The member name is unrecorded and keeps the address.
//
// The APT action calls go through WindowManager::_bfme_callAptFunction
// (0x004675F0) on the 0x012F19E8 window manager, with the movie level read
// into a block-scoped local as OnlineLoginUpdate.cpp does; that local is what
// lets both state-5 arms share the manager/level loads retail hoists above
// the init() test.
#include "StringInline.h"

class GameWindow;

class Shell
{
public:
	void hide( bool hide );
	void showShell( bool runInit );
};
extern Shell *TheShell;

enum SaveCode { SC_OK };
class GameState
{
public:
	SaveCode rva001127F0( const AsciiString &filename );
};
extern GameState *TheGameState;

class GameEngine
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
};
extern GameEngine *TheGameEngine;

class BfmeSinkBOE
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10();
	virtual void slot14();
	unsigned char m_unmodelled04[0x2C];
	bool m_rva30;
};
extern BfmeSinkBOE *g_bfmeSinkBOE;

class WindowManager
{
public:
	void *_bfme_callAptFunction( unsigned int, const char *, int, const char *, const char *, const char *, const char *, const char * );
	void bfme_hideBackground( bool hide );
};
extern WindowManager *g_rva012F19E8WindowManager;

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24();
	virtual UnicodeString fetch( const char *label, bool *exists = 0 );
};
extern GameTextInterface *TheGameText;

void GSMessageBoxOk( UnicodeString title, UnicodeString message, void (*okFunc)( void ) );

class Rva00690CB0Owner
{
public:
	bool init();
};

class BfmeAptScreenMainMenu
{
public:
	int rva0051D700();

private:
	unsigned char m_unmodelled000[0x250];
	unsigned int m_movie;
	unsigned char m_unmodelled254[5];
	bool m_rva259;
	unsigned char m_unmodelled25A[0xA];
	int m_state;
	Rva00690CB0Owner m_firewall;
};

// ?rva0051D700@BfmeAptScreenMainMenu@@QAEHXZ
int BfmeAptScreenMainMenu::rva0051D700()
{
	switch( m_state )
	{
		case 1:
		{
			TheShell->hide( true );
			bool found = TheGameState->rva001127F0( AsciiString( "00000000.sav" ) ) != 0;
			if( found )
			{
				TheGameEngine->slot10();
				TheShell->showShell( true );
				m_rva259 = false;
				m_state = 0;
				g_rva012F19E8WindowManager->bfme_hideBackground( false );
			}
			else
				m_state = 2;
			break;
		}

		case 4:
			if( g_bfmeSinkBOE )
			{
				g_bfmeSinkBOE->slot14();
				if( g_bfmeSinkBOE->m_rva30 )
					g_rva012F19E8WindowManager->_bfme_callAptFunction( m_movie, "HideCredits", 0, 0, 0, 0, 0, 0 );
			}
			break;

		case 5:
			if( !m_firewall.init() )
			{
				{
					unsigned int level = m_movie;
					g_rva012F19E8WindowManager->_bfme_callAptFunction( level,
						"FirewallMessageClose", 0, 0, 0, 0, 0, 0 );
				}
				GSMessageBoxOk( TheGameText->fetch( "GUI:FirewallNoAdminTitle" ),
					TheGameText->fetch( "GUI:FirewallNoAdminMessage" ), 0 );
			}
			else
			{
				unsigned int level = m_movie;
				g_rva012F19E8WindowManager->_bfme_callAptFunction( level,
					"FirewallMessageClose", 1, "startMulti", 0, 0, 0, 0 );
			}
			// fall through
		case 6:
			m_state = 0;
			break;
	}
	return 1;
}
