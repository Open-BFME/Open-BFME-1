// ?SetUpGameSpy@@YAXPBD0@Z
// partial score=0.94 date=2026-09-10
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringbaseascii /Ireference/shims/psplayerstats /Ireference/shims/peerdefs /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME: clean C++ reconstruction of SetUpGameSpy.
// Retail boundary: 0x006377D0, 723 bytes.

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define _BFME_RETAIL_PLAYER_INFO_LAYOUT
#define __PLACEMENT_VEC_NEW_INLINE
#include <map>
#include "PreRTS.h"
#include <set>

#include "Common/GameState.h"
#include "Common/RandomValue.h"
#include "Common/IgnorePreferences.h"
#include "Common/CustomMatchPreferences.h"
#include "Common/GameSpyMiscPreferences.h"
#include "Common/Recorder.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/PlayerTemplate.h"
#include "GameClient/MapUtil.h"
#include "GameClient/ShellHooks.h"
#include "GameClient/GameText.h"
#include "GameNetwork/GameSpy/LadderDefs.h"
#include "GameNetwork/GameSpy/PeerDefsImplementation.h"
#include "GameNetwork/GameSpy/BuddyThread.h"
#include "GameNetwork/GameSpy/PeerThread.h"
#include "GameNetwork/GameSpy/PingThread.h"
#include "GameNetwork/GameSpy/PersistentStorageThread.h"
#include "GameNetwork/GameSpy/GSConfig.h"
#include "GameNetwork/GameSpyOverlay.h"
#include "GameNetwork/RankPointValue.h"
#include "GameLogic/GameLogic.h"
#include "string_base.h"

// The retail accessor is the ILT at 0x000106EA.  GlobalData.h provides an
// inline implementation for the normal build, so this declaration-only view
// keeps this TU on the already-proven retail accessor without emitting a new
// helper or changing the shared header.
class Rva006C9270GlobalData
{
public:
	AsciiString getPath_UserData() const;
};

// The GameSpyInfoInterface shim has the ZH slot order.  Retail's named
// callers and this body's calls prove one extra slot before the four text
// preference methods and one more before chat: retail uses +0xD4 for
// setDisallowAsianText and +0x100/+0x108 for setMOTD/setConfig.  This
// declaration-only ABI view models those slots; it has no definitions or
// emitted callback symbols.
class SetUpGameSpyInfoView
{
public:
	virtual ~SetUpGameSpyInfoView();
	virtual void reset( void ) = 0;
	virtual void clearGroupRoomList( void ) = 0;
	virtual GroupRoomMap* getGroupRoomList( void ) = 0;
	virtual void addGroupRoom( GameSpyGroupRoom room ) = 0;
	virtual Bool gotGroupRoomList( void ) = 0;
	virtual void joinGroupRoom( Int groupID ) = 0;
	virtual void leaveGroupRoom( void ) = 0;
	virtual void joinBestGroupRoom( void ) = 0;
	virtual void setCurrentGroupRoom( Int groupID ) = 0;
	virtual Int getCurrentGroupRoom( void ) = 0;
	virtual void updatePlayerInfo( PlayerInfo pi, AsciiString oldNick ) = 0;
	virtual void playerLeftGroupRoom( AsciiString nick ) = 0;
	virtual PlayerInfoMap* getPlayerInfoMap( void ) = 0;
	virtual BuddyInfoMap* getBuddyMap( void ) = 0;
	virtual BuddyInfoMap* getBuddyRequestMap( void ) = 0;
	virtual BuddyMessageList* getBuddyMessages( void ) = 0;
	virtual Bool isBuddy( Int id ) = 0;
	virtual void setLocalName( AsciiString name ) = 0;
	virtual AsciiString getLocalName( void ) = 0;
	virtual void setLocalProfileID( Int profileID ) = 0;
	virtual Int getLocalProfileID( void ) = 0;
	virtual AsciiString getLocalEmail( void ) = 0;
	virtual void setLocalEmail( AsciiString email ) = 0;
	virtual AsciiString getLocalPassword( void ) = 0;
	virtual void setLocalPassword( AsciiString passwd ) = 0;
	virtual void setLocalBaseName( AsciiString name ) = 0;
	virtual AsciiString getLocalBaseName( void ) = 0;
	virtual void setCachedLocalPlayerStats( PSPlayerStats stats ) = 0;
	virtual PSPlayerStats getCachedLocalPlayerStats( void ) = 0;
	virtual void clearStagingRoomList( void ) = 0;
	virtual StagingRoomMap* getStagingRoomList( void ) = 0;
	virtual GameSpyStagingRoom* findStagingRoomByID( Int id ) = 0;
	virtual void addStagingRoom( GameSpyStagingRoom room ) = 0;
	virtual void updateStagingRoom( GameSpyStagingRoom room ) = 0;
	virtual void _bfme_setup_unidentified_slot_0( void ) = 0;
	virtual void _bfme_setup_unidentified_slot_1( void ) = 0;
	virtual void _bfme_setup_unidentified_slot_2( void ) = 0;
	virtual void _bfme_setup_unidentified_slot_3( void ) = 0;
	virtual void _bfme_setup_unidentified_slot_4( void ) = 0;
	virtual void _bfme_setup_unidentified_slot_5( void ) = 0;
	virtual void _bfme_setup_unidentified_slot_6( void ) = 0;
	virtual void removeStagingRoom( GameSpyStagingRoom room ) = 0;
	virtual Bool hasStagingRoomListChanged( void ) = 0;
	virtual void leaveStagingRoom( void ) = 0;
	virtual void markAsStagingRoomHost( void ) = 0;
	virtual void markAsStagingRoomJoiner( Int game ) = 0;
	virtual void sawFullGameList( void ) = 0;
	virtual Bool amIHost( void ) = 0;
	virtual GameSpyStagingRoom* getCurrentStagingRoom( void ) = 0;
	virtual void setGameOptions( void ) = 0;
	virtual Int getCurrentStagingRoomID( void ) = 0;
	virtual void _bfme_setup_unidentified_slot_before_disallow( void ) = 0;
	virtual void setDisallowAsianText( Bool val ) = 0;
	virtual void setDisallowNonAsianText( Bool val ) = 0;
	virtual Bool getDisallowAsianText( void ) = 0;
	virtual Bool getDisallowNonAsianText( void ) = 0;
	virtual void _bfme_setup_unidentified_slot_before_chat( void ) = 0;
	virtual void registerTextWindow( GameWindow *win ) = 0;
	virtual void unregisterTextWindow( GameWindow *win ) = 0;
	virtual Int addText( UnicodeString message, Color c, GameWindow *win ) = 0;
	virtual void addChat( PlayerInfo p, UnicodeString msg, Bool isPublic, Bool isAction, GameWindow *win ) = 0;
	virtual void addChat( AsciiString nick, Int profileID, UnicodeString msg, Bool isPublic, Bool isAction, GameWindow *win ) = 0;
	virtual Bool sendChat( UnicodeString message, Bool isAction, GameWindow *playerListbox ) = 0;
	virtual void setMOTD( const AsciiString& motd ) = 0;
	virtual const AsciiString& getMOTD( void ) = 0;
	virtual void setConfig( const AsciiString& config ) = 0;
	virtual const AsciiString& getConfig( void ) = 0;
};

// BFME routes these two interface factories to different concrete
// implementations than the Zero Hour headers.  Declaration-only views keep
// this caller on the retail ILTs without misnaming either concrete class.
class BfmeSetUpPSFactory
{
public:
	static GameSpyPSMessageQueueInterface *createNewMessageQueue();
};

class BfmeSetUpPingerFactory
{
public:
	static PingerInterface *createNewPingerInterface();
};

// BFME's RankPoints object is 0x30 bytes; the Zero Hour definition is 0x3c.
class BfmeSetUpRankPoints
{
public:
	BfmeSetUpRankPoints();

private:
	unsigned char m_fields[0x30];
};

void SetUpGameSpy(const char *motdBuffer, const char *configBuffer)
{
	if (!motdBuffer)
		motdBuffer = "";
	if (!configBuffer)
		configBuffer = "";
	TearDownGameSpy();

	AsciiString dir = reinterpret_cast<const Rva006C9270GlobalData *>(TheWritableGlobalData)->getPath_UserData();
	CreateDirectory(dir.str(), NULL);
	dir.format(AsciiString("%sLoTRB4MEOnline"), reinterpret_cast<const Rva006C9270GlobalData *>(TheWritableGlobalData)->getPath_UserData().str());
	CreateDirectory(dir.str(), NULL);
	dir.format(AsciiString("%sLoTRB4MEOnline\\Ladders"), reinterpret_cast<const Rva006C9270GlobalData *>(TheWritableGlobalData)->getPath_UserData().str());
	CreateDirectory(dir.str(), NULL);

	TheGameSpyBuddyMessageQueue = GameSpyBuddyMessageQueueInterface::createNewMessageQueue();
	TheGameSpyBuddyMessageQueue->startThread();

	TheGameSpyPeerMessageQueue = GameSpyPeerMessageQueueInterface::createNewMessageQueue();
	TheGameSpyPeerMessageQueue->startThread();

	TheGameSpyPSMessageQueue = BfmeSetUpPSFactory::createNewMessageQueue();
	TheGameSpyPSMessageQueue->startThread();

	TheGameSpyInfo = GameSpyInfoInterface::createNewGameSpyInfoInterface();
	reinterpret_cast<SetUpGameSpyInfoView *>(TheGameSpyInfo)->setMOTD(motdBuffer);
	reinterpret_cast<SetUpGameSpyInfoView *>(TheGameSpyInfo)->setConfig(configBuffer);

	CustomMatchPreferences pref;
	reinterpret_cast<SetUpGameSpyInfoView *>(TheGameSpyInfo)->setDisallowAsianText(pref.getDisallowAsianText());
	reinterpret_cast<SetUpGameSpyInfoView *>(TheGameSpyInfo)->setDisallowNonAsianText(pref.getDisallowNonAsianText());

	TheGameSpyConfig = GameSpyConfigInterface::create(configBuffer);

	TheLadderList = NEW LadderList;

	ThePinger = BfmeSetUpPingerFactory::createNewPingerInterface();
	ThePinger->startThreads();

	TheRankPointValues = (RankPoints *)NEW BfmeSetUpRankPoints;
}
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/asciistringsetoutofline /Ireference/shims/psplayerstats /Ireference/shims/peerdefs /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWLib
