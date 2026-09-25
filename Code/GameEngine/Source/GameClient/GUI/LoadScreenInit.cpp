// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ?init@ShellGameLoadScreen@@UAEXPAVGameInfo@@@Z: Code/GameEngine/Source/GameClient/GUI/LoadScreen.cpp
// readable body of ?init@MapTransferLoadScreen@@UAEXPAVGameInfo@@@Z: Code/GameEngine/Source/GameClient/GUI/LoadScreen.cpp
//
// The load screens' init methods, slot 2 of each subclass's table:
//
//   ShellGameLoadScreen   vtable 0x010F9B0C  0x004920E0
//   MapTransferLoadScreen vtable 0x010F9B60  0x00492C40
//
// Written beside LoadScreenUpdates.cpp rather than inside LoadScreen.cpp,
// which builds against Zero Hour's headers: BFME's LoadScreen base is eight
// bytes wider, winCreateFromScript takes a third argument, and AsciiString is
// the StringBase<char> shim, none of which that TU can say without putting
// its matched rows at risk.

#include "string_base.h"

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
enum NameKeyType { NAMEKEY_INVALID = 0 };

#define FALSE 0
#define TRUE 1

extern "C" __declspec(dllimport) UnsignedInt __stdcall timeGetTime( void );
extern "C" __declspec(dllimport) void __stdcall Sleep( UnsignedInt milliseconds );

// Retail's AsciiString is the StringBase<char> shim, and str() is inline:
// the text is read eight bytes past the header, "" when there is none.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() { m_data = 0; }
	AsciiString( const char *s )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase( s );
	}
	AsciiString( const AsciiString &that )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&that );
	}
	~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }

	void __cdecl format( AsciiString fmt, ... );

	const char *str() const
	{
		return m_data ? (const char *)(m_data + 8) : "";
	}

private:
	char *m_data;
};

// Copies and releases through StringBase<unsigned short> directly, as the
// by-value arguments in retail do.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:
	static UnicodeString TheEmptyString;

	UnicodeString( const UnicodeString &that )
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
			*(const StringBase<unsigned short> *)&that );
	}
	~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }

private:
	unsigned short *m_data;
};

class Image;
class WindowLayoutInfo;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	Int winHide( Bool hide );
	Int winBringToTop( void );
	Int winSetEnabledImage( Int index, const Image *image );
	Int winSetEnabledColor( Int index, Int color );
	void winSetEnabledTextColors( Int color, Int borderColor );
	Int winGetEnabledTextBorderColor( void );

	unsigned char m_unmodelled_000[0x1f4];
	// BFME clears this straight after winCreateFromScript returns, as in
	// GameWindowManagerMessageBox.cpp; Zero Hour's source has no such store.
	void *m_clearedOnCreate;					// +0x1F4
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	// Retail reserves three argument slots at the call.
	virtual GameWindow *winCreateFromScript( AsciiString file, WindowLayoutInfo *info = 0, void *extra = 0 );	// +0x68
	virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32();
	virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38();
	virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43(); virtual void slot44();
	virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50();
	virtual void slot51(); virtual void slot52(); virtual void slot53();
	virtual void slot54();
	virtual GameWindow *winGetWindowFromId( GameWindow *win, Int id );	// +0xdc
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const AsciiString &name );
	NameKeyType nameToKey( const char *name );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Image.h
class ImageCollection
{
public:
	const Image *findImageByName( const AsciiString &name );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowTransitions.h
class GameWindowTransitionsHandler
{
public:
	void reverse( AsciiString groupName );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameLOD.h
class GameLODManager
{
public:
	Bool didMemPass( void );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	unsigned char m_unmodelled_000[0xdbf];
	// Cleared where Zero Hour's ShellGameLoadScreen::init clears
	// m_breakTheMovie, right after the title image goes up.
	Bool m_breakTheMovie;						// +0xDBF
};

void GadgetProgressBarSetProgress( GameWindow *g, Int progress );
void GadgetStaticTextSetText( GameWindow *g, UnicodeString text );

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GadgetProgressBar.h
inline void GadgetProgressBarSetEnabledBarColor( GameWindow *g, Int color )
{
	g->winSetEnabledColor( 4, color );
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	Bool isHuman( void ) const;
	Int getApparentColor( void ) const;
	UnicodeString getName( void ) const;
	Bool hasMap( void ) const { return m_hasMap; }

private:
	unsigned char m_unmodelled_000[9];
	Bool m_hasMap;								// +0x09
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	GameSlot *getSlot( Int slotNum );
	const GameSlot *getConstSlot( Int slotNum ) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MultiplayerSettings.h
class MultiplayerColorDefinition
{
public:
	Int getColor( void ) const { return m_color; }

private:
	unsigned char m_unmodelled_000[0x10];
	Int m_color;								// +0x10
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MultiplayerSettings.h
class MultiplayerSettings
{
public:
	MultiplayerColorDefinition *getColor( Int which );
};

extern GameWindowManager *TheWindowManager;
extern NameKeyGenerator *TheNameKeyGenerator;
extern ImageCollection *TheMappedImageCollection;
extern GameWindowTransitionsHandler *TheTransitionHandler;
extern GameLODManager *TheGameLODManager;
extern GlobalData *TheWritableGlobalData;
extern GameInfo *TheGameInfo;
extern MultiplayerSettings *TheMultiplayerSettings;

enum { MAX_SLOTS = 8 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/LoadScreen.h
// The layout LoadScreenUpdates.cpp witnesses: window at +0x08, ready byte at
// +0x0C, subclass members from +0x10.
class LoadScreen
{
public:
	virtual void slot00();
	virtual void update( Int percent );
	virtual void init( GameInfo *game );
	virtual void reset();

protected:
	unsigned char m_unmodelled_04[4];
	GameWindow *m_loadScreen;					// this+0x08
	unsigned char m_ready;						// this+0x0C
	unsigned char m_unmodelled_0D[3];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/LoadScreen.h
class ShellGameLoadScreen : public LoadScreen
{
public:
	virtual void init( GameInfo *game );

private:
	GameWindow *m_progressBar;					// this+0x10
};

// ?init@ShellGameLoadScreen@@UAEXPAVGameInfo@@@Z
// Retail 0x004920E0, 517 bytes, slot 2 of 0x010F9B0C. Zero Hour's body, with
// BFME's fade: the first time the title image goes up the FadeWholeScreen
// transition group is reversed before the legal text shows.
void ShellGameLoadScreen::init( GameInfo *game )
{
	static Int firstLoad = TRUE;

	m_loadScreen = TheWindowManager->winCreateFromScript( AsciiString( "Menus/ShellGameLoadScreen.wnd" ) );
	m_loadScreen->winHide( FALSE );
	m_loadScreen->winBringToTop();

	m_progressBar = TheWindowManager->winGetWindowFromId( m_loadScreen,
		TheNameKeyGenerator->nameToKey( AsciiString( "ShellGameLoadScreen.wnd:ProgressLoad" ).str() ) );
	GadgetProgressBarSetProgress( m_progressBar, 0 );
	m_progressBar->winHide( TRUE );

	if( m_loadScreen && firstLoad && TheGameLODManager && TheGameLODManager->didMemPass() )
	{
		m_loadScreen->winSetEnabledImage( 0, TheMappedImageCollection->findImageByName( AsciiString( "TitleScreen" ) ) );
		TheTransitionHandler->reverse( AsciiString( "FadeWholeScreen" ) );
		TheWritableGlobalData->m_breakTheMovie = FALSE;

		GameWindow *win = TheWindowManager->winGetWindowFromId( m_loadScreen,
			TheNameKeyGenerator->nameToKey( AsciiString( "ShellGameLoadScreen.wnd:StaticTextLegal" ) ) );
		if( win )
			win->winHide( FALSE );
		firstLoad = FALSE;

		UnsignedInt showTime = timeGetTime();
		while( showTime + 3000 > timeGetTime() )
		{
			LoadScreen::update( 0 );
			Sleep( 100 );
		}
	}
	m_progressBar->winHide( FALSE );
}

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/LoadScreen.h
// Zero Hour's members at the uniform +8 of the wider BFME base.
class MapTransferLoadScreen : public LoadScreen
{
public:
	virtual void init( GameInfo *game );

private:
	GameWindow *m_progressBars[MAX_SLOTS];		// this+0x10
	GameWindow *m_playerNames[MAX_SLOTS];		// this+0x30
	GameWindow *m_progressText[MAX_SLOTS];		// this+0x50
	Int m_playerLookup[MAX_SLOTS];				// this+0x70
	Int m_oldProgress[MAX_SLOTS];				// this+0x90
	GameWindow *m_fileNameText;					// this+0xB0
	GameWindow *m_timeoutText;					// this+0xB4
};

// ?init@MapTransferLoadScreen@@UAEXPAVGameInfo@@@Z
// Retail 0x00492C40, 988 bytes, slot 2 of 0x010F9B60. Zero Hour's body; the
// only BFME addition is the store that clears the new window's +0x1F4.
void MapTransferLoadScreen::init( GameInfo *game )
{
	m_loadScreen = TheWindowManager->winCreateFromScript( AsciiString( "Menus/MapTransferScreen.wnd" ) );
	if( !m_loadScreen )
		return;

	m_loadScreen->winHide( FALSE );
	m_loadScreen->winBringToTop();
	// Through a copy of the pointer: stored straight through m_loadScreen
	// the reload lands in ecx instead of retail's eax.
	GameWindow *screen = m_loadScreen;
	screen->m_clearedOnCreate = 0;

	AsciiString winName;
	Int i;

	winName.format( "MapTransferScreen.wnd:StaticTextCurrentFile" );
	m_fileNameText = TheWindowManager->winGetWindowFromId( m_loadScreen, TheNameKeyGenerator->nameToKey( winName.str() ) );

	winName.format( "MapTransferScreen.wnd:StaticTextTimeout" );
	m_timeoutText = TheWindowManager->winGetWindowFromId( m_loadScreen, TheNameKeyGenerator->nameToKey( winName.str() ) );

	Int netSlot = 0;
	for( i = 0; i < MAX_SLOTS; ++i )
	{
		winName.format( "MapTransferScreen.wnd:ProgressLoad%d", i );
		m_progressBars[i] = TheWindowManager->winGetWindowFromId( m_loadScreen, TheNameKeyGenerator->nameToKey( winName.str() ) );
		GadgetProgressBarSetProgress( m_progressBars[i], 0 );

		winName.format( "MapTransferScreen.wnd:StaticTextPlayer%d", i );
		m_playerNames[i] = TheWindowManager->winGetWindowFromId( m_loadScreen, TheNameKeyGenerator->nameToKey( winName.str() ) );

		winName.format( "MapTransferScreen.wnd:StaticTextProgress%d", i );
		m_progressText[i] = TheWindowManager->winGetWindowFromId( m_loadScreen, TheNameKeyGenerator->nameToKey( winName.str() ) );

		GameSlot *slot = game->getSlot( i );
		if( !slot || !slot->isHuman() )
			continue;
		Int houseColor = TheMultiplayerSettings->getColor( slot->getApparentColor() )->getColor();
		GadgetProgressBarSetEnabledBarColor( m_progressBars[netSlot], houseColor );

		UnicodeString name = slot->getName();
		GadgetStaticTextSetText( m_playerNames[netSlot], name );
		m_playerNames[netSlot]->winSetEnabledTextColors( houseColor, m_playerNames[netSlot]->winGetEnabledTextBorderColor() );

		GadgetStaticTextSetText( m_progressText[netSlot], UnicodeString::TheEmptyString );
		m_progressText[netSlot]->winSetEnabledTextColors( houseColor, m_progressText[netSlot]->winGetEnabledTextBorderColor() );

		if( ( i == 0 || ( TheGameInfo->getConstSlot( i )->isHuman() && TheGameInfo->getConstSlot( i )->hasMap() ) ) && m_progressBars[netSlot] )
			m_progressBars[netSlot]->winHide( TRUE );

		m_playerLookup[i] = netSlot;

		netSlot++;
	}

	for( i = netSlot; i < MAX_SLOTS; ++i )
	{
		m_progressBars[i]->winHide( TRUE );
		m_playerNames[i]->winHide( TRUE );
		m_progressText[i]->winHide( TRUE );
	}
}
