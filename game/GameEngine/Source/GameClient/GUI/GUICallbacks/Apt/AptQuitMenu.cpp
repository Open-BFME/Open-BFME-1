// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/GameEngine/Include /Igame/Libraries/Source/WWVegas/WWLib
//
// BfmeAptScreenQuitMenu destructor, retail 0x00569720, 504 bytes.
// Identity: vtable 0x0110A388 slot 0 is the deleting destructor 0x00569DE0,
// which calls this body through ILT 0x000271F6; the landed constructor
// 0x0056A2F0 installs the same vtable pair (0x0110A388 / 0x0110A384 at
// +0x218) and publishes `this` to the singleton 0x012F4B40 that this body
// clears. The live-singleton path is Zero Hour's QuitMenu.cpp HideQuitMenu
// (InGameUI visibility off, unpause unless isInMultiplayerGame) followed by
// the exit path (TheNetwork->quitGame in a LAN/internet game, else the local
// quit); it ends by resetting the "APT:Pause" text and chains to the
// _bfme_AptGameWindow base destructor (0x00465430 via ILT 0x000204C3).
//
// Retail keeps the 0x012F0898 value in ECX across the whole body
// and reloads it after every call (0x0056978B, 0x005697C1, 0x0056982F),
// which MSVC only does for a global it may treat as invariant; the same
// choice frees ESI so `this` lands in EDI as retail has it.

#include "GameClient/BfmeAptScreenBaseLayout.h"
#include "ascii_string.h"
#include "unicode_string.h"

class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09();
	virtual UnicodeString fetch( const char *label, bool *exists = 0 );
};

extern GameTextInterface *TheGameText;

class WindowManager
{
public:
	void bfme_showBackground( int kind );
	void bfme_hideBackground( bool flag );
	void bfme_setAptText( const AsciiString &name, const UnicodeString &text );
};

extern WindowManager *g_theWindowManager;

class InGameUI
{
public:
#define IGUI_SLOT( N ) virtual void slot##N();
	IGUI_SLOT( 00 ) IGUI_SLOT( 01 ) IGUI_SLOT( 02 ) IGUI_SLOT( 03 ) IGUI_SLOT( 04 )
	IGUI_SLOT( 05 ) IGUI_SLOT( 06 ) IGUI_SLOT( 07 ) IGUI_SLOT( 08 ) IGUI_SLOT( 09 )
	IGUI_SLOT( 10 ) IGUI_SLOT( 11 ) IGUI_SLOT( 12 ) IGUI_SLOT( 13 ) IGUI_SLOT( 14 )
	IGUI_SLOT( 15 ) IGUI_SLOT( 16 ) IGUI_SLOT( 17 ) IGUI_SLOT( 18 ) IGUI_SLOT( 19 )
	IGUI_SLOT( 20 ) IGUI_SLOT( 21 ) IGUI_SLOT( 22 ) IGUI_SLOT( 23 ) IGUI_SLOT( 24 )
	IGUI_SLOT( 25 ) IGUI_SLOT( 26 ) IGUI_SLOT( 27 ) IGUI_SLOT( 28 ) IGUI_SLOT( 29 )
	IGUI_SLOT( 30 ) IGUI_SLOT( 31 ) IGUI_SLOT( 32 ) IGUI_SLOT( 33 ) IGUI_SLOT( 34 )
	IGUI_SLOT( 35 ) IGUI_SLOT( 36 ) IGUI_SLOT( 37 ) IGUI_SLOT( 38 ) IGUI_SLOT( 39 )
	IGUI_SLOT( 40 ) IGUI_SLOT( 41 ) IGUI_SLOT( 42 ) IGUI_SLOT( 43 ) IGUI_SLOT( 44 )
	IGUI_SLOT( 45 ) IGUI_SLOT( 46 ) IGUI_SLOT( 47 ) IGUI_SLOT( 48 ) IGUI_SLOT( 49 )
	IGUI_SLOT( 50 ) IGUI_SLOT( 51 ) IGUI_SLOT( 52 ) IGUI_SLOT( 53 ) IGUI_SLOT( 54 )
	IGUI_SLOT( 55 ) IGUI_SLOT( 56 ) IGUI_SLOT( 57 ) IGUI_SLOT( 58 ) IGUI_SLOT( 59 )
	IGUI_SLOT( 60 ) IGUI_SLOT( 61 ) IGUI_SLOT( 62 ) IGUI_SLOT( 63 ) IGUI_SLOT( 64 )
	IGUI_SLOT( 65 ) IGUI_SLOT( 66 ) IGUI_SLOT( 67 ) IGUI_SLOT( 68 ) IGUI_SLOT( 69 )
	IGUI_SLOT( 70 ) IGUI_SLOT( 71 ) IGUI_SLOT( 72 ) IGUI_SLOT( 73 ) IGUI_SLOT( 74 )
	IGUI_SLOT( 75 ) IGUI_SLOT( 76 ) IGUI_SLOT( 77 ) IGUI_SLOT( 78 ) IGUI_SLOT( 79 )
	IGUI_SLOT( 80 ) IGUI_SLOT( 81 ) IGUI_SLOT( 82 ) IGUI_SLOT( 83 )
#undef IGUI_SLOT
	virtual void slot84( bool visible );
};

extern InGameUI *TheInGameUI;

// ?setGamePaused@BfmeGameLogicPause@@QAEX_NH0@Z, body 0x00383490.
class BfmeGameLogicPause
{
public:
	void setGamePaused( bool paused, int pauseMode, bool affectMouse );
};

enum GameMode
{
	GAME_SINGLE_PLAYER,
	GAME_LAN,
	GAME_SKIRMISH,
	GAME_REPLAY,
	GAME_SHELL,
	GAME_INTERNET
};

// This TU's view of the real GameLogic (VA 0x012F0898), spelled under its real
// name so its method calls keep the retail callee spelling.
class GameLogic : public BfmeGameLogicPause
{
public:
	// Zero Hour GameLogic.h inline.
	bool isInMultiplayerGame() { return m_gameMode == GAME_LAN || m_gameMode == GAME_INTERNET; }
	void _bfme_quitLocalGame();

	char m_unmodelled00[ 0x3c ];
	unsigned int m_unmodelled3C;
	char m_unmodelled40[ 0x10c - 0x40 ];
	int m_gameMode;
};

extern GameLogic *TheGameLogic;

// ?bfmeCommit@Gen_005A4470@@QAEXXZ, body 0x005A4470, called on TheMouse.
class Gen_005A4470
{
public:
	void bfmeCommit();
};

extern Gen_005A4470 *TheMouse;

class Shell
{
public:
	void hide( bool doHide );
	void showShell( bool doShow );
};

extern Shell *TheShell;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetworkInterface.h
// quitGame at +0x78 as in AptScreenFactories.cpp (DisconnectScreen::_bfme_onQuit).
class NetworkInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29();
	virtual void quitGame();
};

extern NetworkInterface *TheNetwork;

class Glo012F1028Type
{
public:
	char m_unmodelled00[ 0x2c ];
	bool m_byte2C;
	bool m_byte2D;
};

extern Glo012F1028Type *Glo012F1028;

extern unsigned int g_dword010EAD50;

extern void *g_obj12F4B40;

class _bfme_AptGameWindow
{
public:
	virtual ~_bfme_AptGameWindow();

private:
	BfmeAptScreenBaseLayout<> m_primaryStorage;
};

class BfmeAptScreenQuitMenuSecondary
{
public:
	virtual void slot00() = 0;

private:
	char m_unmodelled[ 0x3c ];
};

class BfmeAptScreenQuitMenu : public _bfme_AptGameWindow, public BfmeAptScreenQuitMenuSecondary
{
public:
	virtual ~BfmeAptScreenQuitMenu();

private:
	bool m_field258;
	bool m_field259;
	bool m_field25A;
	int m_field25C;
};

BfmeAptScreenQuitMenu::~BfmeAptScreenQuitMenu()
{
	if( this == g_obj12F4B40 )
	{
		g_obj12F4B40 = 0;

		if( TheInGameUI )
			TheInGameUI->slot84( false );

		if( TheGameLogic && !TheGameLogic->isInMultiplayerGame() )
			TheGameLogic->setGamePaused( false, m_field25C, true );

		if( TheMouse )
			TheMouse->bfmeCommit();

		if( TheShell && !m_field258 )
			TheShell->hide( false );

		if( TheGameLogic && m_field258 )
		{
			bool quit = false;
			if( TheGameLogic->m_unmodelled3C < g_dword010EAD50 &&
				TheGameLogic->isInMultiplayerGame() && TheNetwork )
			{
				TheNetwork->quitGame();
				quit = true;
			}

			bool victory = Glo012F1028 && Glo012F1028->m_byte2C && Glo012F1028->m_byte2D;

			if( !quit )
				TheGameLogic->_bfme_quitLocalGame();

			if( g_theWindowManager )
				g_theWindowManager->bfme_showBackground( 1 );

			if( victory )
				TheShell->showShell( true );
		}
		else if( !m_field259 && g_theWindowManager )
		{
			g_theWindowManager->bfme_hideBackground( false );
		}

		AsciiString name( "APT:Pause" );
		g_theWindowManager->bfme_setAptText( name, TheGameText->fetch( "APT:Pause" ) );
	}
}
