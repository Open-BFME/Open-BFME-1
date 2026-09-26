// cl: /DNDEBUG /MD /EHsc

#include "../../../../../../../inputs/reference/shims/stringinline/StringInline.h"

typedef unsigned int NameKeyType;

class GameWindow;
class WindowLayout;

class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};

extern NameKeyGenerator *TheNameKeyGenerator;

class GameWindowManager
{
public:
#define BFME_UNUSED_SLOT(n) virtual void unused##n();
	BFME_UNUSED_SLOT(0)
	BFME_UNUSED_SLOT(1)
	BFME_UNUSED_SLOT(2)
	BFME_UNUSED_SLOT(3)
	BFME_UNUSED_SLOT(4)
	BFME_UNUSED_SLOT(5)
	BFME_UNUSED_SLOT(6)
	BFME_UNUSED_SLOT(7)
	BFME_UNUSED_SLOT(8)
	BFME_UNUSED_SLOT(9)
	BFME_UNUSED_SLOT(10)
	BFME_UNUSED_SLOT(11)
	BFME_UNUSED_SLOT(12)
	BFME_UNUSED_SLOT(13)
	BFME_UNUSED_SLOT(14)
	BFME_UNUSED_SLOT(15)
	BFME_UNUSED_SLOT(16)
	BFME_UNUSED_SLOT(17)
	BFME_UNUSED_SLOT(18)
	BFME_UNUSED_SLOT(19)
	BFME_UNUSED_SLOT(20)
	BFME_UNUSED_SLOT(21)
	BFME_UNUSED_SLOT(22)
	BFME_UNUSED_SLOT(23)
	BFME_UNUSED_SLOT(24)
	BFME_UNUSED_SLOT(25)
	BFME_UNUSED_SLOT(26)
	BFME_UNUSED_SLOT(27)
	BFME_UNUSED_SLOT(28)
	BFME_UNUSED_SLOT(29)
	BFME_UNUSED_SLOT(30)
	BFME_UNUSED_SLOT(31)
	BFME_UNUSED_SLOT(32)
	BFME_UNUSED_SLOT(33)
	BFME_UNUSED_SLOT(34)
	BFME_UNUSED_SLOT(35)
	BFME_UNUSED_SLOT(36)
	BFME_UNUSED_SLOT(37)
	BFME_UNUSED_SLOT(38)
	BFME_UNUSED_SLOT(39)
	BFME_UNUSED_SLOT(40)
	BFME_UNUSED_SLOT(41)
	BFME_UNUSED_SLOT(42)
	BFME_UNUSED_SLOT(43)
	BFME_UNUSED_SLOT(44)
	BFME_UNUSED_SLOT(45)
	BFME_UNUSED_SLOT(46)
	BFME_UNUSED_SLOT(47)
	BFME_UNUSED_SLOT(48)
	BFME_UNUSED_SLOT(49)
	BFME_UNUSED_SLOT(50)
	BFME_UNUSED_SLOT(51)
	BFME_UNUSED_SLOT(52)
	BFME_UNUSED_SLOT(53)
	BFME_UNUSED_SLOT(54)
#undef BFME_UNUSED_SLOT
	virtual GameWindow *winGetWindowFromId( GameWindow *parent, NameKeyType id );
};

extern GameWindowManager *TheWindowManager;

extern void GadgetStaticTextSetText( GameWindow *window, UnicodeString text );
extern void GadgetListBoxReset( GameWindow *window );

static GameWindow *parent = 0;
static GameWindow *staticTextGameName = 0;
static GameWindow *staticTextMapName = 0;
static GameWindow *listBoxPlayers = 0;
static GameWindow *winCrates = 0;
static GameWindow *winSuperWeapons = 0;
static GameWindow *winFreeForAll = 0;
static NameKeyType parentID = 0;
static NameKeyType staticTextGameNameID = 0;
static NameKeyType staticTextMapNameID = 0;
static NameKeyType listBoxPlayersID = 0;
static NameKeyType winCratesID = 0;
static NameKeyType winSuperWeaponsID = 0;
static NameKeyType winFreeForAllID = 0;
static WindowLayout *gameInfoWindowLayout = 0;
static UnicodeString TheEmptyString;

// The retail body resolves GameInfoWindowInit through the callback lexicon.
void GameInfoWindowInit( WindowLayout *layout, void *userData )
{
	parentID = TheNameKeyGenerator->nameToKey( "GameInfoWindow.wnd:ParentGameInfo" );
	staticTextGameNameID = TheNameKeyGenerator->nameToKey( "GameInfoWindow.wnd:StaticTextGameName" );
	staticTextMapNameID = TheNameKeyGenerator->nameToKey( "GameInfoWindow.wnd:StaticTextMapName" );
	listBoxPlayersID = TheNameKeyGenerator->nameToKey( "GameInfoWindow.wnd:ListBoxPlayers" );
	winCratesID = TheNameKeyGenerator->nameToKey( "GameInfoWindow.wnd:WinCrates" );
	winSuperWeaponsID = TheNameKeyGenerator->nameToKey( "GameInfoWindow.wnd:WinSuperWeapons" );
	winFreeForAllID = TheNameKeyGenerator->nameToKey( "GameInfoWindow.wnd:WinFreeForAll" );

	parent = TheWindowManager->winGetWindowFromId( 0, parentID );
	staticTextGameName = TheWindowManager->winGetWindowFromId( parent, staticTextGameNameID );
	staticTextMapName = TheWindowManager->winGetWindowFromId( parent, staticTextMapNameID );
	listBoxPlayers = TheWindowManager->winGetWindowFromId( parent, listBoxPlayersID );
	winCrates = TheWindowManager->winGetWindowFromId( parent, winCratesID );
	winSuperWeapons = TheWindowManager->winGetWindowFromId( parent, winSuperWeaponsID );
	winFreeForAll = TheWindowManager->winGetWindowFromId( parent, winFreeForAllID );

	GadgetStaticTextSetText( staticTextGameName, TheEmptyString );
	GadgetStaticTextSetText( staticTextMapName, TheEmptyString );
	GadgetListBoxReset( listBoxPlayers );
}
