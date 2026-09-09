// ??1BfmeAptScreenQuitMenu@@UAE@XZ
// partial score=0.9 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenQuitMenu destructor, retail 0x00569720, 504 bytes. Own class
// layout (bases, member offsets, both entry vtables 0x0110A388/0x0110A384)
// mirrors Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/
// BfmeAptScreenQuitMenuConstructor.cpp, which is landed; this destructor is
// a SEPARATE TU so it can use real C++ multiple inheritance (letting the
// dtor prologue auto-install both entry vtables in one deterministic block,
// same technique proven on BfmeConv2181.cpp / BfmeAptScreenScoreScreen)
// instead of the constructor's manual raw stores.
//
// When this is the live singleton (g_obj12F4B40 == this): clears the
// singleton, tells TheInGameUI (vtable slot +0x150) to drop client-quiet,
// and -- unless the game mode is already 1/5 (LAN/skirmish-ish) -- pauses
// TheBfmeGameLogic (setGamePaused, already pinned real body 0x00383490,
// reached here through ILT 0x00006F50). Commits TheMouse's pending cursor
// state (ILT 0x0003950E -> 0x005A4470, Bfme5FortyNine.cpp). Hides the shell
// once (Shell::hide, ILT 0x000428ED) unless m_field258 is already set. Then,
// if TheBfmeGameLogic exists and m_field258 is set, runs the ZH QuitMenu.cpp
// exit path: local-player-index-in-range + mode 1/5 -> TheNetwork->quitGame
// (vtable +0x78); otherwise posts MSG_CLEAR_GAME_DATA through the pinned
// ILT thunk ?bfmeCall_000238a3@BfmeGlobal_012f0898@@QAEXXZ (ecx = the
// GameLogic global). A victory/defeat pair at Glo012F1028+0x2c/+0x2d gates a
// later Shell::showShell(TRUE). g_theWindowManager->bfme_showBackground(1)
// always runs there. The ELSE arm (m_field258 not set) instead runs
// bfme_hideBackground(FALSE) unless m_field259 is set. Both arms join to set
// the "APT:Pause" apt text (TheGameText->fetch + bfme_setAptText, same idiom
// as the constructor's GUI:Menu pause text) and chain to the
// _bfme_AptGameWindow base destructor.

class AsciiString
{
private:
	void *m_data;
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString( const char *text );
	~BFMERetailAsciiString() { releaseBuffer(); }
	void releaseBuffer();

private:
	void *m_data;
};

struct UnicodeStringData
{
	unsigned int m_refCount;
	unsigned short m_length;
};

class UnicodeString
{
public:
	~UnicodeString();

private:
	UnicodeStringData *m_data;
};

class GameTextInterface
{
public:
#define GAMETEXT_SLOT( N ) virtual void slot##N();
	GAMETEXT_SLOT( 00 ) GAMETEXT_SLOT( 01 ) GAMETEXT_SLOT( 02 ) GAMETEXT_SLOT( 03 )
	GAMETEXT_SLOT( 04 ) GAMETEXT_SLOT( 05 ) GAMETEXT_SLOT( 06 ) GAMETEXT_SLOT( 07 )
	GAMETEXT_SLOT( 08 ) GAMETEXT_SLOT( 09 )
#undef GAMETEXT_SLOT
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

class InGameUIView
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
	virtual void slot84( bool flag );
};

extern InGameUIView *TheInGameUI;

class BfmeGlobal_012f0898
{
public:
	int m_unused00[ ( 0x3c ) / 4 ];
	unsigned int m_localPlayerIndex;
	char m_pad40[ 0x10c - 0x40 ];
	int m_gameMode;

	void bfmeCall_000238a3();
};

class BfmeGameLogicPause
{
public:
	void setGamePaused( bool paused, int pauseMode, bool affectMouse );
};

#define TheBfmeGameLogic (*(BfmeGlobal_012f0898 **)0x012f0898)
#define TheBfmeGameLogicPause (*(BfmeGameLogicPause **)0x012f0898)

void j_0003950e(); // TheMouse->bfmeCommit(), real body 0x005A4470

extern void *TheMouse_012f4c5c;
#define TheMouse ( *(void **)0x012f4c5c )

class Shell
{
public:
	void hide( bool doHide );
	void showShell( bool doShow );
};

extern Shell *TheShell;

class NetworkInterfaceView
{
public:
#define NET_SLOT( N ) virtual void slot##N();
	NET_SLOT( 00 ) NET_SLOT( 01 ) NET_SLOT( 02 ) NET_SLOT( 03 ) NET_SLOT( 04 )
	NET_SLOT( 05 ) NET_SLOT( 06 ) NET_SLOT( 07 ) NET_SLOT( 08 ) NET_SLOT( 09 )
	NET_SLOT( 10 ) NET_SLOT( 11 ) NET_SLOT( 12 ) NET_SLOT( 13 ) NET_SLOT( 14 )
	NET_SLOT( 15 ) NET_SLOT( 16 ) NET_SLOT( 17 ) NET_SLOT( 18 ) NET_SLOT( 19 )
	NET_SLOT( 20 ) NET_SLOT( 21 ) NET_SLOT( 22 ) NET_SLOT( 23 ) NET_SLOT( 24 )
	NET_SLOT( 25 ) NET_SLOT( 26 ) NET_SLOT( 27 ) NET_SLOT( 28 ) NET_SLOT( 29 )
#undef NET_SLOT
	virtual void quitGame();
};

extern NetworkInterfaceView *TheNetwork;

struct Glo012F1028Type
{
	char m_pad[ 0x2c ];
	bool m_flag2c;
	bool m_flag2d;
};

extern Glo012F1028Type *Glo012F1028;

extern unsigned int g_playerCountLimit_10ead50;
#define kPlayerCountLimit ( *(unsigned int *)0x010ead50 )

class _bfme_AptGameWindow
{
public:
	virtual ~_bfme_AptGameWindow();

private:
	char m_unmodelled[ 0x214 ];
};

class BfmeAptScreenQuitMenuSecondary
{
public:
	virtual void slot00() = 0;

private:
	char m_unmodelled[ 0x3c ];
};

class BfmeAptScreenQuitMenu;
#define g_obj12F4B40 (*(BfmeAptScreenQuitMenu **)0x012f4b40)

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

		if( TheBfmeGameLogic )
		{
			int gameMode = TheBfmeGameLogic->m_gameMode;
			if( gameMode != 1 && gameMode != 5 )
				TheBfmeGameLogicPause->setGamePaused( false, m_field25C, true );
		}

		(void)*(BfmeGlobal_012f0898 *volatile *)&TheBfmeGameLogic;
		if( TheMouse )
			( (void ( __fastcall * )( void * ))j_0003950e )( TheMouse );

		(void)*(BfmeGlobal_012f0898 *volatile *)&TheBfmeGameLogic;
		if( TheShell && !m_field258 )
			TheShell->hide( false );

		if( TheBfmeGameLogic && m_field258 )
		{
			bool quit = false;
			if( TheBfmeGameLogic->m_localPlayerIndex < kPlayerCountLimit )
			{
				int gameMode = TheBfmeGameLogic->m_gameMode;
				if( gameMode == 1 || gameMode == 5 )
				if( TheNetwork )
				{
					TheNetwork->quitGame();
					quit = true;
				}
			}

			bool victory = ( Glo012F1028 && Glo012F1028->m_flag2c && Glo012F1028->m_flag2d );

			if( !quit )
				TheBfmeGameLogic->bfmeCall_000238a3();

			if( g_theWindowManager )
				g_theWindowManager->bfme_showBackground( 1 );

			if( victory )
				TheShell->showShell( true );
		}
		else
		{
			if( !m_field259 && g_theWindowManager )
				g_theWindowManager->bfme_hideBackground( false );
		}

		{
			BFMERetailAsciiString name( "APT:Pause" );
			UnicodeString text = TheGameText->fetch( "APT:Pause" );
			g_theWindowManager->bfme_setAptText( reinterpret_cast<const AsciiString &>( name ), text );
		}
	}
}
