// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/GameEngine/Include /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// BfmeAptScreenSaveLoad destructor, retail 0x0056E230 (753 bytes of code, jump table after).
// Identity: installs the vtable pair 0x0110A684 / 0x0110A680 of constructor 0x0056E980, and its
// only caller is the deleting destructor 0x0056E830; layout follows AptQuitMenu.cpp.

#include <list>
#include "GameClient/BfmeAptScreenBaseLayout.h"
#include "ascii_string.h"

typedef int Int;
typedef bool Bool;

#define TRUE true
#define FALSE false

// BFME SaveGameInfo (GameStateSaveGameInfoDtor.cpp): saveFileType at +0x28.
class SaveGameInfo
{
public:
	~SaveGameInfo();

	char m_unmodelled00[ 0x28 ];
	Int saveFileType;
	char m_unmodelled2C[ 0x04 ];
};

// Zero Hour GameState.h AvailableGameInfo; 0x3C bytes in BFME.
struct AvailableGameInfo
{
	AvailableGameInfo( const AvailableGameInfo &other );

	AsciiString filename;
	SaveGameInfo saveGameInfo;
	AvailableGameInfo *next;
	AvailableGameInfo *prev;
};

// Zero Hour GameState.h numbering.
enum SaveCode
{
	SC_INVALID = -1,
	SC_OK,
	SC_NO_FILE_AVAILABLE,
	SC_FILE_NOT_FOUND
};

class BfmePopupSaveGameState
{
public:
	SaveCode loadGame( AvailableGameInfo gameInfo );
};

class GameState;
extern GameState *TheGameState;

class RecorderClass
{
public:
	Bool playbackFile( AsciiString filename );
};

extern RecorderClass *TheRecorder;

class GameEngine
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void reset();
};

extern GameEngine *TheGameEngine;

// ?setGamePaused@BfmeGameLogicPause@@QAEX_NH0@Z, body 0x00383490.
class BfmeGameLogicPause
{
public:
	void setGamePaused( Bool paused, Int pauseMode, Bool affectInput );
	void clearGameData( Bool showScoreScreen, Bool unknown );
};

class GameLogic : public BfmeGameLogicPause
{
};

extern GameLogic * const TheGameLogic;

class Shell
{
public:
	void hide( Bool doHide );
	void showShell( Bool runInit );
};

extern Shell *TheShell;

class Rva0051D690Shell
{
public:
	bool check();
};

extern Rva0051D690Shell *g_obj12F4B58;

class Rva0051D690Audio
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0c();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2c();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3c();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4c();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5c();
	virtual void slot60(); virtual void slot64(); virtual void slot68();
	virtual void slot6c( int a, int b, int c );
};

extern Rva0051D690Audio *TheAudioClientUpdate;

class WindowManager
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();

	void bfme_hideBackground( bool flag );
};

extern WindowManager *g_theWindowManager;

// 0x0046DD00 (`add ecx,0x1c; jmp`), landed under this opaque name; it takes the
// registration name, so the call casts it to that signature.
class Rva0046DD00
{
public:
	void invoke();
};

typedef void ( Rva0046DD00::*Rva0046DD00TakeName )( const AsciiString &name );

class GameWindowManager
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
};

extern GameWindowManager *TheWindowManager;

// The 0x012F4B40 singleton is the quit menu (AptQuitMenu.cpp clears it and
// tests its +0x259 flag before hiding the background).
class BfmeAptScreenQuitMenu
{
public:
	char m_unmodelled00[ 0x259 ];
	bool m_field259;
};

extern void *g_obj12F4B40;

class AptSaveLoad;
extern AptSaveLoad *TheAptSaveLoad;

extern const char *g_saveLoadRegistrations012B7E60[ 2 ];

void _bfme_closeAptScreen( const AsciiString &name );
void bfmeOpenEAH( void *param );

class _bfme_AptGameWindow
{
public:
	virtual ~_bfme_AptGameWindow();

private:
	BfmeAptScreenBaseLayout<> m_primaryStorage;
};

class BfmeAptScreenSaveLoadSecondary
{
public:
	virtual void slot00() = 0;

private:
	char m_unmodelled[ 0x3c ];
};

class BfmeAptScreenSaveLoad : public _bfme_AptGameWindow, public BfmeAptScreenSaveLoadSecondary
{
public:
	virtual ~BfmeAptScreenSaveLoad();

private:
	Int m_state;
	AvailableGameInfo *m_selectedGame25C;
	Bool m_pausedOnEntry260;
	char m_unmodelled261[ 0x278 - 0x261 ];
	Bool m_flag278;
	char m_unmodelled279[ 0x280 - 0x279 ];
	Bool m_flag280;
	_STL::list<AvailableGameInfo> m_games284;
};

// ??1BfmeAptScreenSaveLoad@@UAE@XZ
BfmeAptScreenSaveLoad::~BfmeAptScreenSaveLoad()
{
	if( g_theWindowManager )
	{
		Bool showBackground = FALSE;
		for( Int i = 0; i < 2; ++i )
		{
			( reinterpret_cast<Rva0046DD00 *>( g_theWindowManager )->*
				reinterpret_cast<Rva0046DD00TakeName>( &Rva0046DD00::invoke ) )(
				AsciiString( g_saveLoadRegistrations012B7E60[ i ] ) );
		}

		_bfme_closeAptScreen( AsciiString( "AptSaveLoad::InitGadgets" ) );
		TheAptSaveLoad = 0;

		if( TheGameLogic )
			TheGameLogic->setGamePaused( m_pausedOnEntry260, 2, TRUE );

		if( m_state == 5 && m_selectedGame25C )
		{
			switch( m_selectedGame25C->saveGameInfo.saveFileType )
			{
			case 0:
				showBackground = TRUE;
			case 1:
				m_flag280 = TRUE;
				break;
			case 2:
				if( g_obj12F4B40 )
					static_cast<BfmeAptScreenQuitMenu *>( g_obj12F4B40 )->m_field259 = TRUE;
				m_flag280 = FALSE;
				break;
			case 3:
				m_flag280 = TRUE;
				break;
			}

			bfmeOpenEAH( (void *)2 );
			g_theWindowManager->slot14();
			TheWindowManager->slot14();
			TheShell->hide( TRUE );

			if( m_selectedGame25C->saveGameInfo.saveFileType != 3 )
			{
				switch( ((BfmePopupSaveGameState *)TheGameState)->loadGame( *m_selectedGame25C ) )
				{
				case SC_FILE_NOT_FOUND:
					TheGameLogic->clearGameData( FALSE, TRUE );
					TheGameEngine->reset();
					TheShell->showShell( TRUE );
					break;
				}
			}
			else if( !TheRecorder->playbackFile( m_selectedGame25C->filename ) )
			{
				TheGameLogic->clearGameData( FALSE, TRUE );
				TheGameEngine->reset();
				TheShell->showShell( TRUE );
			}
		}
		else if( m_state == 9 )
		{
			bfmeOpenEAH( 0 );
			if( m_flag278 )
				TheShell->hide( TRUE );
		}

		if( m_flag280 )
			g_theWindowManager->bfme_hideBackground( showBackground );

		if( !g_obj12F4B58 || !g_obj12F4B58->check() )
			TheAudioClientUpdate->slot6c( 2, 1, 0 );
	}
}
