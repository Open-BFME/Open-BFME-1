// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ?init@ShellGameLoadScreen@@UAEXPAVGameInfo@@@Z: Code/GameEngine/Source/GameClient/GUI/LoadScreen.cpp
// readable body of ?init@MapTransferLoadScreen@@UAEXPAVGameInfo@@@Z: Code/GameEngine/Source/GameClient/GUI/LoadScreen.cpp
// readable body of ?init@MultiPlayerLoadScreen@@UAEXPAVGameInfo@@@Z: Code/GameEngine/Source/GameClient/GUI/LoadScreen.cpp
//
// The load screens' init methods, slot 2 of each subclass's table:
//
//   ShellGameLoadScreen   vtable 0x010F9B0C  0x004920E0
//   MapTransferLoadScreen vtable 0x010F9B60  0x00492C40
//   MultiPlayerLoadScreen vtable 0x010F9B28  0x00492400
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
#define NULL 0

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
	// The header's length is the word four bytes in.
	Bool isEmpty() const
	{
		return !m_data || !*(const unsigned short *)(m_data + 4);
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
	void winSetUserData( void *data );
	UnsignedInt winSetStatus( UnsignedInt status );
	UnsignedInt winClearStatus( UnsignedInt status );

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
	UnicodeString getApparentPlayerTemplateDisplayName( void ) const;
	Bool isOccupied( void ) const;
	Bool isAI( void ) const;
	Bool hasMap( void ) const { return m_hasMap; }
	Int getPlayerTemplate( void ) const { return m_playerTemplate; }
	Int getTeamNumber( void ) const { return m_teamNumber; }

private:
	unsigned char m_unmodelled_000[9];
	Bool m_hasMap;								// +0x09
	unsigned char m_unmodelled_00A[0x14 - 0x0a];
	Int m_playerTemplate;						// +0x14
	// Read where Zero Hour reads getTeamNumber() for the "Team:%d" label.
	Int m_teamNumber;							// +0x18
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameInfo
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04();
	virtual Int getLocalSlotNum( void ) const;	// +0x14

	AsciiString getMap( void ) const;
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
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerTemplate.h
class PlayerTemplate
{
public:
	const AsciiString &getLoadScreenMusic( void ) const { return m_loadScreenMusic; }
	const AsciiString &getLoadScreenImage( void ) const { return m_loadScreenImage; }

private:
	unsigned char m_unmodelled_000[0xb8];
	AsciiString m_loadScreenMusic;				// +0xB8
	unsigned char m_unmodelled_0BC[0xd0 - 0xbc];
	AsciiString m_loadScreenImage;				// +0xD0
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerTemplate.h
class PlayerTemplateStore
{
public:
	const PlayerTemplate *findPlayerTemplate( NameKeyType namekey ) const;
	const PlayerTemplate *getNthPlayerTemplate( Int i ) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AudioEventRTS.h
class AudioEventRTS
{
public:
	AudioEventRTS( const AsciiString &eventName, Int extra );
	virtual void slot00();
	~AudioEventRTS();
	void setIsLogicalAudio( Bool isLogical );

private:
	char m_unmodelled_004[0x6c];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
class AudioManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04();
	virtual void update( void );										// +0x14
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16();
	virtual unsigned int addAudioEvent( const AudioEventRTS *event );	// +0x44
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26();
	// Called with (2, 1, 0) just before the load-screen music starts, as
	// CreditsMenu.cpp's call before the credits music; three arguments where
	// Zero Hour's removeAudioEvent(AHSV_StopTheMusicFade) takes one, so only
	// the slot is named.
	virtual void slot6C( Int a, Int b, Int c );						// +0x6C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameText.h
class GameTextInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual UnicodeString fetch( AsciiString label, Bool *exists = 0 );	// +0x24
};

class MapMetaData;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/MapUtil.h
class MapCache
{
public:
	const MapMetaData *findMap( AsciiString mapName );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/GameLogic.h
class GameLogic
{
public:
	void initTimeOutValues( void );
};

Image *getMapPreviewImage( AsciiString mapName );
void positionStartSpots( GameInfo *myGame, GameWindow *buttonMapStartPositions[], GameWindow *mapWindow, Bool force );
void updateMapStartSpots( GameInfo *myGame, GameWindow *buttonMapStartPositions[], Bool onLoadScreen );

enum { WIN_STATUS_IMAGE = 0x00000080 };

extern GameInfo *TheGameInfo;
extern PlayerTemplateStore *ThePlayerTemplateStore;
extern AudioManager *TheAudio;
extern GameTextInterface *TheGameText;
extern MapCache *TheMapCache;
extern GameLogic *TheGameLogic;
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/LoadScreen.h
// BFME drops Zero Hour's local-general portrait, features and name windows;
// the map preview and start-position buttons follow the lookup table.
class MultiPlayerLoadScreen : public LoadScreen
{
public:
	virtual void init( GameInfo *game );

private:
	GameWindow *m_progressBars[MAX_SLOTS];		// this+0x10
	GameWindow *m_playerNames[MAX_SLOTS];		// this+0x30
	GameWindow *m_playerSide[MAX_SLOTS];		// this+0x50
	Int m_playerLookup[MAX_SLOTS];				// this+0x70
	GameWindow *m_mapPreview;					// this+0x90
	GameWindow *m_buttonMapStartPosition[MAX_SLOTS];	// this+0x94
};

// ?init@MultiPlayerLoadScreen@@UAEXPAVGameInfo@@@Z
// Retail 0x00492400, 1688 bytes, slot 2 of 0x010F9B28. Zero Hour's body
// without the local general's portrait panel: BFME puts the local player's
// faction load-screen image on the screen itself and starts the faction's
// load-screen music, then fills the per-slot windows exactly as Zero Hour
// does, colouring the progress bar rather than swapping its image.
void MultiPlayerLoadScreen::init( GameInfo *game )
{
	m_loadScreen = TheWindowManager->winCreateFromScript( AsciiString( "Menus/MultiplayerLoadScreen.wnd" ) );
	m_loadScreen->winHide( FALSE );
	m_loadScreen->winBringToTop();
	m_mapPreview = TheWindowManager->winGetWindowFromId( m_loadScreen, TheNameKeyGenerator->nameToKey( "MultiplayerLoadScreen.wnd:WinMapPreview" ) );

	GameSlot *lSlot = game->getSlot( game->getLocalSlotNum() );
	if( lSlot )
	{
		const PlayerTemplate *pt;
		if( lSlot->getPlayerTemplate() >= 0 )
			pt = ThePlayerTemplateStore->getNthPlayerTemplate( lSlot->getPlayerTemplate() );
		else
			pt = ThePlayerTemplateStore->findPlayerTemplate( TheNameKeyGenerator->nameToKey( "FactionObserver" ) );

		const Image *loadScreenImage = TheMappedImageCollection->findImageByName( pt->getLoadScreenImage() );

		AsciiString musicName = pt->getLoadScreenMusic();
		if( !musicName.isEmpty() )
		{
			TheAudio->slot6C( 2, 1, 0 );
			AudioEventRTS event( musicName, 2 );
			event.setIsLogicalAudio( TRUE );
			TheAudio->addAudioEvent( &event );
			TheAudio->update();
		}

		if( loadScreenImage )
			m_loadScreen->winSetEnabledImage( 0, loadScreenImage );
	}

	GameWindow *teamWin[MAX_SLOTS];
	Int i;
	for( i = 0; i < MAX_SLOTS; ++i )
		teamWin[i] = NULL;

	Int netSlot = 0;
	for( i = 0; i < MAX_SLOTS; ++i )
	{
		AsciiString winName;
		winName.format( "MultiplayerLoadScreen.wnd:ProgressLoad%d", i );
		m_progressBars[i] = TheWindowManager->winGetWindowFromId( m_loadScreen, TheNameKeyGenerator->nameToKey( winName.str() ) );
		GadgetProgressBarSetProgress( m_progressBars[i], 0 );

		winName.format( "MultiplayerLoadScreen.wnd:ButtonMapStartPosition%d", i );
		m_buttonMapStartPosition[i] = TheWindowManager->winGetWindowFromId( m_loadScreen, TheNameKeyGenerator->nameToKey( winName.str() ) );

		winName.format( "MultiplayerLoadScreen.wnd:StaticTextPlayer%d", i );
		m_playerNames[i] = TheWindowManager->winGetWindowFromId( m_loadScreen, TheNameKeyGenerator->nameToKey( winName.str() ) );

		winName.format( "MultiplayerLoadScreen.wnd:StaticTextSide%d", i );
		m_playerSide[i] = TheWindowManager->winGetWindowFromId( m_loadScreen, TheNameKeyGenerator->nameToKey( winName.str() ) );

		winName.format( "MultiplayerLoadScreen.wnd:StaticTextTeam%d", i );
		teamWin[i] = TheWindowManager->winGetWindowFromId( m_loadScreen, TheNameKeyGenerator->nameToKey( winName.str() ) );

		GameSlot *slot = game->getSlot( i );
		if( !slot || !slot->isOccupied() )
			continue;

		Int houseColor = TheMultiplayerSettings->getColor( slot->getApparentColor() )->getColor();
		GadgetProgressBarSetEnabledBarColor( m_progressBars[netSlot], houseColor );

		UnicodeString name = slot->getName();
		GadgetStaticTextSetText( m_playerNames[netSlot], name );
		m_playerNames[netSlot]->winSetEnabledTextColors( houseColor, m_playerNames[netSlot]->winGetEnabledTextBorderColor() );

		GadgetStaticTextSetText( m_playerSide[netSlot], slot->getApparentPlayerTemplateDisplayName() );
		m_playerSide[netSlot]->winSetEnabledTextColors( houseColor, m_playerSide[netSlot]->winGetEnabledTextBorderColor() );

		if( slot->isAI() && m_progressBars[netSlot] )
			m_progressBars[netSlot]->winHide( TRUE );

		if( teamWin[netSlot] )
		{
			AsciiString teamStr;
			teamStr.format( "Team:%d", slot->getTeamNumber() + 1 );
			GadgetStaticTextSetText( teamWin[netSlot], TheGameText->fetch( teamStr ) );
			teamWin[netSlot]->winSetEnabledTextColors( houseColor, m_playerNames[netSlot]->winGetEnabledTextBorderColor() );
		}

		m_playerLookup[i] = netSlot;

		netSlot++;
	}

	for( i = netSlot; i < MAX_SLOTS; ++i )
	{
		m_progressBars[i]->winHide( TRUE );
		m_playerNames[i]->winHide( TRUE );
		m_playerSide[i]->winHide( TRUE );
		teamWin[i]->winHide( TRUE );
	}

	if( m_mapPreview )
	{
		const MapMetaData *mmd = TheMapCache->findMap( game->getMap() );
		Image *image = getMapPreviewImage( game->getMap() );
		m_mapPreview->winSetUserData( (void *)mmd );

		positionStartSpots( game, m_buttonMapStartPosition, m_mapPreview, FALSE );
		updateMapStartSpots( game, m_buttonMapStartPosition, TRUE );
		if( image )
		{
			m_mapPreview->winSetStatus( WIN_STATUS_IMAGE );
			m_mapPreview->winSetEnabledImage( 0, image );
		}
		else
		{
			m_mapPreview->winClearStatus( WIN_STATUS_IMAGE );
		}
	}

	TheGameLogic->initTimeOutValues();
}
