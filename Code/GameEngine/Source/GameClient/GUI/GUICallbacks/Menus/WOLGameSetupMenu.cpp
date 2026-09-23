// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringbaseunicode /Ireference/shims/stringbaseascii /Ireference/shims/psplayerstats /Ireference/shims/nat /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /ICode/Libraries/Source/WWVegas/WWLib
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
#include <string>
// stlport
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////
// FILE: WOLGameSetupMenu.cpp
// Author: Matt Campbell, December 2001
// Description: WOL Game Options Menu
///////////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// BFME layouts used by the update callback below. The ZH/nat headers do not
// provide these complete object lifetimes and virtual slots. Instruction
// witnesses are recorded in build/gap_004f6ad9/LAYOUTS.md; unused bytes retain
// opaque names. Keep these corrections scoped to this translation unit.
#ifndef __GAMEINFO_H__
#define __GAMEINFO_H__

#include "Common/Snapshot.h"
#include "Common/Money.h"
#include "GameNetwork/NetworkDefs.h"
#include "GameNetwork/FirewallHelper.h"

enum SlotState
{
	SLOT_OPEN,
	SLOT_CLOSED,
	SLOT_EASY_AI,
	SLOT_MED_AI,
	SLOT_BRUTAL_AI,
	SLOT_PLAYER
};

enum
{
	PLAYERTEMPLATE_RANDOM = -1,
	PLAYERTEMPLATE_OBSERVER = -2,
	PLAYERTEMPLATE_MIN = PLAYERTEMPLATE_OBSERVER
};

/**
  * Connection info for a slot - the NAT/Firewall behavior and the
	* port number the slot's player communicates on.  BFME passes this
	* around as a unit (GameSlot::setState takes a pointer to one).
	*/
struct GameSlotConnectInfo {
    FirewallHelperClass::FirewallBehaviorType m_nat;
    unsigned short m_port;
};
struct BfmeWolAddress { unsigned int ip; unsigned short port; };


/**
  * GameSlot class - maintains information about the contents of a
	* game slot.  This persists throughout the game.
	*/
class GameSlot
{
public:
	GameSlot();
	~GameSlot();
	virtual void reset();

	void setAccept( void ) { m_isAccepted = true; }		///< Accept the current options
	void unAccept( void );														///< Unaccept (options changed, etc)
	Bool isAccepted( void ) const { return m_isAccepted; }	///< Non-human slots are always accepted

	void setMapAvailability( Bool hasMap );						///< Set whether the slot has the map
	Bool hasMap( void ) const { return m_hasMap; }		///< Non-human slots always have the map

	void setState( SlotState state,
		UnicodeString name = UnicodeString::TheEmptyString,
		const GameSlotConnectInfo *connectInfo = NULL);	///< Set the slot's state (human, AI, open, etc)
	SlotState getState( void ) const { return m_state; }		///< Get the slot state

	void setColor( Int color ) { m_color = color; }
	Int getColor( void ) const { return m_color; }

	void setStartPos( Int startPos ) { m_startPos = startPos; }
	Int getStartPos( void ) const { return m_startPos; }

	void setPlayerTemplate( Int playerTemplate )
	{ m_playerTemplate = playerTemplate;
		if (playerTemplate <= PLAYERTEMPLATE_MIN)
			m_startPos = -1;
	 }
	Int getPlayerTemplate( void ) const { return m_playerTemplate; }

	void setTeamNumber( Int teamNumber ) { m_teamNumber = teamNumber; }
	Int getTeamNumber( void ) const { return m_teamNumber; }

	inline void setName( UnicodeString name ) { m_name = name; }
	inline UnicodeString getName( void ) const { return m_name; }

	BfmeWolAddress getAddress() const { return m_address; }
	void setAddress(BfmeWolAddress value) { m_address = value; }
	inline void setIP( UnsignedInt IP ) { m_address.ip = IP; }
	inline UnsignedInt getIP( void ) const { return m_address.ip; }

	inline void setPort( UnsignedShort port ) { m_address.port = port; }
	inline UnsignedShort getPort( void ) const { return m_address.port; }

	inline void setNATBehavior( FirewallHelperClass::FirewallBehaviorType NATBehavior) { m_nat = NATBehavior; }
	inline FirewallHelperClass::FirewallBehaviorType getNATBehavior() const { return m_nat; }
	
	void saveOffOriginalInfo( void );
	inline Int getOriginalPlayerTemplate( void ) const	{ return m_origPlayerTemplate; }
	inline Int getOriginalColor( void ) const						{ return m_origColor; }
	inline Int getOriginalStartPos( void ) const				{ return m_origStartPos; }
	Int getApparentPlayerTemplate( void ) const;
	Int getApparentColor( void ) const;
	Int getApparentStartPos( void ) const;
	UnicodeString getApparentPlayerTemplateDisplayName( void ) const;

	// Various tests
	Bool isHuman( void ) const;															///< Is this slot occupied by a human player?
	Bool isOccupied( void ) const;													///< Is this slot occupied (by a human or an AI)?
	Bool isAI( void ) const;																///< Is this slot occupied by an AI?
	Bool isPlayer( AsciiString userName ) const;						///< Does this slot contain the given user?
	Bool isPlayer( UnicodeString userName ) const;					///< Does this slot contain the given user?
	Bool isPlayer( UnsignedInt ip ) const;									///< Is this slot at this IP?
	Bool isOpen( void ) const;

	void setLastFrameInGame( UnsignedInt frame ) { m_lastFrameInGame = frame; }
	void markAsDisconnected( void ) { m_disconnected = TRUE; }
	UnsignedInt lastFrameInGame( void ) const { return m_lastFrameInGame; }
	Bool disconnected( void ) const { return isHuman() && m_disconnected; }

	void mute( Bool isMuted ) { m_isMuted = isMuted; }
	Bool isMuted( void ) const { return m_isMuted; }
protected:
	SlotState m_state;
	Bool m_isAccepted;
	Bool m_hasMap;
	Bool m_isMuted;
	Int m_color;																			///< color, or -1 for random
	Int m_startPos;																		///< start position, or -1 for random
	Int m_playerTemplate;															///< PlayerTemplate
	Int m_teamNumber;																	///< alliance, -1 for none
	Int m_origColor;																			///< color, or -1 for random
	Int m_origStartPos;																		///< start position, or -1 for random
	Int m_origPlayerTemplate;															///< PlayerTemplate
	UnicodeString m_name;															///< Only valid for human players
	AsciiString m_opaque2c;												///< unpinned; see the note at the top
	BfmeWolAddress m_address;																	///< Only valid for human players in LAN/WOL
	FirewallHelperClass::FirewallBehaviorType m_nat;								///< NAT behavior and port for this slot's player.
	UnsignedInt m_lastFrameInGame;	// only valid for human players
	Bool m_disconnected;						// only valid for human players
};

/**
  * GameInfo class - maintains information about the game setup and
	* the contents of its slot list hroughout the game.
	*/
class GameInfo
{
public:
	GameInfo();
	virtual void slot_000();
	virtual void slot_004();
	
	void init( void );
	virtual void reset( void );

	void clearSlotList( void );

	Int getNumPlayers( void ) const;									///< How many players (human and AI) are in the game?
	Int getNumNonObserverPlayers( void ) const;				///< How many non-observer players (human and AI) are in the game?
	Int getMaxPlayers( void ) const;									///< How many players (human and AI) can be in the game?

	void enterGame( void );														///< Mark us as having entered the game
	void leaveGame( void );														///< Mark us as having left the game
	virtual void startGame( Int gameID );											///< Mark our game as started, and record the game ID
	void endGame( void );															///< Mark us as out of game
	Int getGameID( void ) const { return m_gameID; }								///< Get the game ID of the current game or the last one if we're not in game

	void setInGame( void ) { m_inGame = true; }										///< set the m_inGame flag
	Bool isInGame( void ) const { return m_inGame; }											///< Are we (in game or in game setup)?  As opposed to chatting, matching, etc
	Bool isGameInProgress( void ) const { return m_inProgress; }							///< Is the game in progress?
	inline void setGameInProgress( Bool inProgress ); ///< Set whether the game is in progress or not.
	void setSlot( Int slotNum, GameSlot slotInfo );		///< Set the slot state (human, open, AI, etc)
	GameSlot* getSlot( Int slotNum );									///< Get the slot
	const GameSlot* getConstSlot( Int slotNum ) const;	///< Get the slot
	virtual Bool amIHost( void ) const;															///< Convenience function - is the local player the game host?
	virtual Int getLocalSlotNum( void ) const;				///< Get the local slot number, or -1 if we're not present
	Int getSlotNum( AsciiString userName ) const;			///< Get the slot number corresponding to a specific user, or -1 if he's not present

	// Game options
	void setMap( AsciiString mapName );								///< Set the map to play on
	void setMapCRC( UnsignedInt mapCRC );							///< Set the map CRC
	void setMapSize( UnsignedInt mapSize );						///< Set the map size
	void setMapContentsMask( Int mask );							///< Set the map contents mask (1=map,2=preview,4=map.ini)
	inline AsciiString getMap( void ) const;								///< Get the game map
	UnsignedInt getMapCRC( void ) const { return m_mapCRC; }							///< Get the map CRC
	UnsignedInt getMapSize( void ) const { return m_mapSize; }						///< Get the map size
	Int getMapContentsMask( void ) const { return m_mapMask; }						///< Get the map contents mask
	void setSeed( Int seed );													///< Set the random seed for the game
	Int getSeed( void ) const { return m_seed; }												///< Get the game seed
	Int getUseStats( void ) const { return m_useStats; }		///< Does this game count towards gamespy stats?
	inline void setUseStats( Int useStats );

UnsignedShort getSuperweaponRestriction( void ) const { return m_superweaponRestriction; } ///< Get any optional limits on superweapons
  void setSuperweaponRestriction( UnsignedShort restriction ); ///< Set the optional limits on superweapons
const Money& getStartingCash( void ) const { return m_startingCash; } 
  void setStartingCash( const Money & startingCash );

	void setSlotPointer( Int index, GameSlot *slot );	///< Set the slot info pointer

	void setLocalIP( UnsignedInt ip ) { m_localIP =ip; }	///< Set the local IP
	UnsignedInt getLocalIP( void ) const { return m_localIP; }	///< Get the local IP

	Bool isColorTaken(Int colorIdx, Int slotToIgnore = -1 ) const;
	Bool isStartPositionTaken(Int positionIdx, Int slotToIgnore = -1 ) const;

	virtual void resetAccepted(void);															///< Reset the accepted flag on all players
	virtual void resetStartSpots(void);						///< reset the start spots for the new map.
	virtual void adjustSlotsForMap(void);					///< adjusts the slots to open and closed depending on the players in the game and the number of players the map can hold.

	virtual void closeOpenSlots(void);						///< close all slots that are currently unoccupied.

	// CRC checking hack
	void setCRCInterval( Int val ) { m_crcInterval = (val<100)?val:100; }
	inline Int getCRCInterval( void ) const { return m_crcInterval; }
	
	Bool haveWeSurrendered(void) { return m_surrendered; }
	void markAsSurrendered(void) { m_surrendered = TRUE; }

	Bool isSkirmish(void); // TRUE if 1 human & 1+ AI are present && !isSandbox()
	Bool isMultiPlayer(void); // TRUE if 2+ human are present
	Bool isSandbox(void); // TRUE if everybody is on the same team
	
	Bool isPlayerPreorder(Int index);
	void markPlayerAsPreorder(Int index);

Bool oldFactionsOnly(void) const { return m_oldFactionsOnly; }
void setOldFactionsOnly( Bool oldFactionsOnly ) { m_oldFactionsOnly = oldFactionsOnly; }

protected:
	Int m_preorderMask;
	Int m_crcInterval;
	Bool m_inGame;
	Bool m_inProgress;
	Bool m_surrendered;
	Int m_gameID;
	GameSlot *m_slot[MAX_SLOTS];

	UnsignedInt m_localIP;

	// Game options
	UnsignedInt m_opaque38;
	AsciiString m_mapName;
	UnsignedInt m_mapCRC;
	UnsignedInt m_mapSize;
	Int m_mapMask;
	Int m_seed;
	Int m_useStats;
  Money         m_startingCash;
  UnsignedShort m_superweaponRestriction;
  Bool m_oldFactionsOnly; // Only USA, China, GLA -- not USA Air Force General, GLA Toxic General, et al
};

extern GameInfo *TheGameInfo;

// Inline functions
AsciiString	GameInfo::getMap( void ) const									{ return m_mapName; }
void				GameInfo::setGameInProgress( Bool inProgress )	{ m_inProgress = inProgress; }
void				GameInfo::setUseStats( Int useStats )           { m_useStats = useStats; }
AsciiString GameInfoToAsciiString( const GameInfo *game );
Bool ParseAsciiStringToGameInfo( GameInfo *game, AsciiString options, Bool value );


/**
  * The SkirmishGameInfo class holds information about the skirmish game and
	* the contents of its slot list.
	*/

class SkirmishGameInfo : public GameInfo, public Snapshot
{
private:
	GameSlot m_skirmishSlot[MAX_SLOTS];

protected:
	// snapshot methods
	virtual void crc( Xfer *xfer );
	virtual void xfer( Xfer *xfer );
	virtual void loadPostProcess( void );

public:
	SkirmishGameInfo()
	{
		for (Int i = 0; i< MAX_SLOTS; ++i)
			setSlotPointer(i, &m_skirmishSlot[i]);
	}
};

extern SkirmishGameInfo *TheSkirmishGameInfo;
extern SkirmishGameInfo *TheChallengeGameInfo;

#endif // __GAMEINFO_H__


#include "Common/GameEngine.h"
#include "Common/GameState.h"
#include "GameClient/GameText.h"
#include "Common/MultiplayerSettings.h"
#include "Common/PlayerTemplate.h"
#include "Common/CustomMatchPreferences.h"
#include "GameClient/AnimateWindowManager.h"
#include "GameClient/InGameUI.h"
#include "GameClient/WindowLayout.h"
#include "GameClient/Mouse.h"
#include "GameClient/Gadget.h"
#include "GameClient/Shell.h"
#include "GameClient/KeyDefs.h"
#include "GameClient/GameWindowManager.h"
#include "GameClient/GadgetComboBox.h"
#include "GameClient/GadgetListBox.h"
#include "GameClient/GadgetTextEntry.h"
#include "GameClient/GadgetPushButton.h"
#include "GameClient/GadgetStaticText.h"
#include "GameClient/GadgetCheckBox.h"
#include "GameClient/MapUtil.h"
#include "GameClient/EstablishConnectionsMenu.h"
#include "GameClient/GameWindowTransitions.h"
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: PeerDefs.h //////////////////////////////////////////////////////
// Generals GameSpy Peer (chat) definitions
// Author: Matthew D. Campbell, June 2002

#pragma once

#ifndef __PEERDEFS_H__
#define __PEERDEFS_H__

#include "GameSpy/Peer/Peer.h"
#include "GameSpy/GP/GP.h"

#include "GameClient/Color.h"
#include "Common/STLTypedefs.h"
#include "GameNetwork/GameSpy/StagingRoomGameInfo.h"

class GameWindow;
class PSPlayerStats;

typedef std::set<AsciiString> IgnoreList;
typedef std::map<Int, AsciiString> SavedIgnoreMap;

enum RCItemType
{
	ITEM_BUDDY,
	ITEM_REQUEST,
	ITEM_NONBUDDY,
	ITEM_NONE,
};

class GameSpyRCMenuData
{
public:
	AsciiString m_nick;
	GPProfile m_id;
	RCItemType m_itemType;
};

class BuddyInfo
{
public:
	GPProfile m_id;
	AsciiString m_name;
	AsciiString m_email;
	AsciiString m_countryCode;
	GPEnum m_status;
	UnicodeString m_statusString;
	UnicodeString m_locationString;
};
typedef std::map<GPProfile, BuddyInfo> BuddyInfoMap;

class BuddyMessage
{
public:
	UnsignedInt m_timestamp;
	GPProfile m_senderID;
	AsciiString m_senderNick;
	GPProfile m_recipientID;
	AsciiString m_recipientNick;
	UnicodeString m_message;
};
typedef std::list<BuddyMessage> BuddyMessageList;

class GameSpyGroupRoom
{
public:
	GameSpyGroupRoom() { m_name = AsciiString::TheEmptyString; m_translatedName = UnicodeString::TheEmptyString; m_groupID = m_numWaiting = m_maxWaiting = m_numGames = m_numPlaying = 0; }
	AsciiString m_name;
	UnicodeString m_translatedName;
	Int m_groupID;
	Int m_numWaiting;
	Int m_maxWaiting;
	Int m_numGames;
	Int m_numPlaying;
};
typedef std::map<Int, GameSpyGroupRoom> GroupRoomMap;

class Transport;
class NAT;

typedef std::map<Int, GameSpyStagingRoom *> StagingRoomMap;

class PlayerInfo {
public:
    PlayerInfo();
    PlayerInfo(const PlayerInfo &);
    ~PlayerInfo();
    AsciiString m_name, m_baseName, m_locale;
    int m_wins, m_losses, m_profileID, m_flags, m_rankPoints;
    int m_opaque20, m_opaque24, m_opaque28, m_side, m_preorder;
    Bool isIgnored();
};
typedef char BfmePlayerInfoSize[sizeof(PlayerInfo) == 0x34 ? 1 : -1];

struct AsciiComparator
{
	bool operator()(AsciiString s1, AsciiString s2) const;
};


typedef std::map<AsciiString, PlayerInfo, AsciiComparator> PlayerInfoMap;

enum GameSpyColors {
	GSCOLOR_DEFAULT = 0,
	GSCOLOR_CURRENTROOM,
	GSCOLOR_ROOM,
	GSCOLOR_GAME,
	GSCOLOR_GAME_FULL,
	GSCOLOR_GAME_CRCMISMATCH,
	GSCOLOR_PLAYER_NORMAL,
	GSCOLOR_PLAYER_OWNER,
	GSCOLOR_PLAYER_BUDDY,
	GSCOLOR_PLAYER_SELF,
	GSCOLOR_PLAYER_IGNORED,
	GSCOLOR_CHAT_NORMAL,
	GSCOLOR_CHAT_EMOTE,
	GSCOLOR_CHAT_OWNER,
	GSCOLOR_CHAT_OWNER_EMOTE,
	GSCOLOR_CHAT_PRIVATE,
	GSCOLOR_CHAT_PRIVATE_EMOTE,
	GSCOLOR_CHAT_PRIVATE_OWNER,
	GSCOLOR_CHAT_PRIVATE_OWNER_EMOTE,
	GSCOLOR_CHAT_BUDDY,
	GSCOLOR_CHAT_SELF,
	GSCOLOR_ACCEPT_TRUE,
	GSCOLOR_ACCEPT_FALSE,
	GSCOLOR_MAP_SELECTED,
	GSCOLOR_MAP_UNSELECTED,
	GSCOLOR_MOTD,
	GSCOLOR_MOTD_HEADING,
	GSCOLOR_MAX
};

extern Color GameSpyColor[GSCOLOR_MAX];

enum GameSpyBuddyStatus {
	BUDDY_OFFLINE,
	BUDDY_ONLINE,
	BUDDY_LOBBY,
	BUDDY_STAGING,
	BUDDY_LOADING,
	BUDDY_PLAYING,
	BUDDY_MATCHING,
	BUDDY_MAX
};

// ---------------------------------------------------
// this class holds info used in the main thread
class GameSpyInfoInterface
{
public:
	virtual ~GameSpyInfoInterface() {};
	virtual void reset( void ) {};
	virtual void clearGroupRoomList( void ) = 0;
	virtual GroupRoomMap* getGroupRoomList( void ) = 0;
	virtual void addGroupRoom( GameSpyGroupRoom room ) = 0;
	virtual Bool gotGroupRoomList( void ) = 0;
	virtual void joinGroupRoom( Int groupID ) = 0;
	virtual void leaveGroupRoom( void ) = 0;
	virtual void joinBestGroupRoom( void ) = 0;
	virtual void setCurrentGroupRoom( Int groupID ) = 0;
	virtual Int  getCurrentGroupRoom( void ) = 0;
	virtual void updatePlayerInfo( PlayerInfo pi, AsciiString oldNick = AsciiString::TheEmptyString ) = 0;
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

	virtual void setDisallowAsianText( Bool val ) = 0;
	virtual void setDisallowNonAsianText( Bool val ) = 0;
	virtual Bool getDisallowAsianText( void ) = 0;
	virtual Bool getDisallowNonAsianText(void ) = 0;

	// chat
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

	virtual void setPingString( const AsciiString& ping ) = 0;
	virtual const AsciiString& getPingString( void ) = 0;
	virtual Int getPingValue( const AsciiString& otherPing ) = 0;

	static GameSpyInfoInterface* createNewGameSpyInfoInterface( void );
	
	virtual void addToSavedIgnoreList( Int profileID, AsciiString nick ) = 0;
	virtual void removeFromSavedIgnoreList( Int profileID ) = 0;
	virtual Bool isSavedIgnored( Int profileID ) = 0;		
	virtual SavedIgnoreMap returnSavedIgnoreList( void ) = 0;
	virtual void loadSavedIgnoreList( void ) = 0;
	
	virtual IgnoreList returnIgnoreList( void ) = 0;
	virtual void addToIgnoreList( AsciiString nick ) = 0;
	virtual void removeFromIgnoreList( AsciiString nick ) = 0;
	virtual Bool isIgnored( AsciiString nick ) = 0;

	virtual void setLocalIPs(UnsignedInt internalIP, UnsignedInt externalIP) = 0;
	virtual UnsignedInt getInternalIP(void) = 0;
	virtual UnsignedInt getExternalIP(void) = 0;

	virtual Bool isDisconnectedAfterGameStart(Int *reason) const = 0;
	virtual void markAsDisconnectedAfterGameStart(Int reason) = 0;

	virtual Bool didPlayerPreorder( Int profileID ) const = 0;
	virtual void markPlayerAsPreorder( Int profileID ) = 0;

	virtual void setMaxMessagesPerUpdate( Int num ) = 0;
	virtual Int getMaxMessagesPerUpdate( void ) = 0;

	virtual Int getAdditionalDisconnects( void ) = 0;
	virtual void clearAdditionalDisconnects( void ) = 0;
	virtual void readAdditionalDisconnects( void ) = 0;
	virtual void updateAdditionalGameSpyDisconnections(Int count) = 0;
};

extern GameSpyInfoInterface *TheGameSpyInfo;

void WOLDisplayGameOptions( void );
void WOLDisplaySlotList( void );
Bool GetLocalChatConnectionAddress(AsciiString serverName, UnsignedShort serverPort, UnsignedInt& localIP);
void SetLobbyAttemptHostJoin(Bool start);
void SendStatsToOtherPlayers(const GameInfo *game);

class PSPlayerStats;
void GetAdditionalDisconnectsFromUserFile(PSPlayerStats *stats);
extern Int GetAdditionalDisconnectsFromUserFile(Int playerID);

//-------------------------------------------------------------------------
// These functions set up the globals and threads neccessary for our GameSpy impl.

void SetUpGameSpy( const char *motdBuffer, const char *configBuffer );
void TearDownGameSpy( void );

#endif // __PEERDEFS_H__

/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// FILE: PeerThread.h //////////////////////////////////////////////////////
// Generals GameSpy Peer-to-peer chat thread class interface
// Author: Matthew D. Campbell, June 2002

#pragma once

#ifndef __PEERTHREAD_H__
#define __PEERTHREAD_H__

#include "GameSpy/Peer/Peer.h"
#include "GameNetwork/NetworkDefs.h"

enum SerialAuthResult
{
	SERIAL_NONEXISTENT,
	SERIAL_AUTHFAILED,
	SERIAL_BANNED,
	SERIAL_OK
};

// this class encapsulates a request for the peer thread
class PeerRequest
{
public:
	enum
	{
		PEERREQUEST_LOGIN,				// attempt to login
		PEERREQUEST_LOGOUT,				// log out if connected
		PEERREQUEST_MESSAGEPLAYER,
		PEERREQUEST_MESSAGEROOM,
		PEERREQUEST_JOINGROUPROOM,
		PEERREQUEST_LEAVEGROUPROOM,
		PEERREQUEST_STARTGAMELIST,
		PEERREQUEST_STOPGAMELIST,
		PEERREQUEST_CREATESTAGINGROOM,
		PEERREQUEST_SETGAMEOPTIONS,
		PEERREQUEST_JOINSTAGINGROOM,
		PEERREQUEST_LEAVESTAGINGROOM,
		// Both NAT call sites that the reference writes as PEERREQUEST_UTMPLAYER
		// -- notifyTargetOfProbe and notifyUsersOfConnectionFailed -- store 13,
		// not 12. Two independent sites agreeing is much better evidence for the
		// enum having gained a value ahead of UTMPLAYER than for both of them
		// having switched to UTMROOM. Where the extra value really sits is not
		// recoverable from those two stores; putting it here is the minimal
		// assumption, since it shifts UTMPLAYER and everything after it and
		// leaves the values before it alone.
		PEERREQUEST_BFMEUNKNOWN,
		PEERREQUEST_UTMPLAYER,
		PEERREQUEST_UTMROOM,
		PEERREQUEST_STARTGAME,
		PEERREQUEST_STARTQUICKMATCH,
		PEERREQUEST_WIDENQUICKMATCHSEARCH,
		PEERREQUEST_STOPQUICKMATCH,
		PEERREQUEST_PUSHSTATS,
		PEERREQUEST_GETEXTENDEDSTAGINGROOMINFO,
		PEERREQUEST_MAX
	} peerRequestType;

	std::string nick;	// only used by login, but must be outside the union b/c of copy constructor
	std::wstring text;  // can't be in a union
	std::string password;
	std::string email;
	std::string id;
	
	// gameopts
	std::string options; // full string for UTMs
	std::string ladderIP;
	std::string hostPingStr;
	std::string gameOptsMapName;
	std::string gameOptsPlayerNames[MAX_SLOTS];

	std::vector<bool> qmMaps;

	union
	{
		struct
		{
			Int profileID;
		} login;

		struct
		{
			Int id;
		} groupRoom;
		
		struct
		{
			Bool restrictGameList;
		} gameList;

		struct
		{
			Bool isAction;
		} message;

		struct
		{
			Int id;
		} stagingRoom;

		struct
		{
			UnsignedInt exeCRC;
			UnsignedInt iniCRC;
			UnsignedInt gameVersion;
			Bool allowObservers;
      Bool useStats;
			UnsignedShort ladPort;
			UnsignedInt ladPassCRC;
			Bool restrictGameList;
		} stagingRoomCreation;

		struct
		{
			Int wins[MAX_SLOTS];
			Int losses[MAX_SLOTS];
			Int profileID[MAX_SLOTS];
			Int faction[MAX_SLOTS];
			Int color[MAX_SLOTS];
			Int numPlayers;
			Int maxPlayers;
			Int numObservers;
			// BFME's PeerRequest is four bytes larger than the reference's, and
			// the extra dword is somewhere at or after the union: retail puts
			// `id` at +0x34 and the UTM union at +0xE4, both exactly where the
			// reference's layout puts them. gameOptions is the union's largest
			// member at 172 bytes, so one more Int here is what moves sizeof
			// from 0x190 to the 0x194 retail's callers reserve. Nothing landed
			// against this header reads gameOptions, so which field BFME
			// actually added is still open -- only the size is pinned.
			Int bfmeExtraGameOption;
		} gameOptions;

		struct
		{
			Bool isStagingRoom;
		} UTM;

		struct
		{
			Int minPointPercentage, maxPointPercentage, points;
			Int widenTime;
			Int ladderID;
			UnsignedInt ladderPassCRC;
			Int maxPing;
			Int maxDiscons, discons;
			char pings[17]; // 8 servers (0-ff), 1 NULL
			Int numPlayers;
			Int botID;
			Int roomID;
			Int side;
			Int color;
			Int NAT;
			UnsignedInt exeCRC;
			UnsignedInt iniCRC;
		} QM;

		struct
		{
			Int locale;
			Int wins;
			Int losses;
			Int rankPoints;
			Int side;
			Bool preorder;
		} statsToPush;

	};
};

//-------------------------------------------------------------------------

enum DisconnectReason
{
	DISCONNECT_NICKTAKEN = 1,
	DISCONNECT_BADNICK,
	DISCONNECT_LOSTCON,
	DISCONNECT_COULDNOTCONNECT,
	DISCONNECT_GP_LOGIN_TIMEOUT,
	DISCONNECT_GP_LOGIN_BAD_NICK,
	DISCONNECT_GP_LOGIN_BAD_EMAIL,
	DISCONNECT_GP_LOGIN_BAD_PASSWORD,
	DISCONNECT_GP_LOGIN_BAD_PROFILE,
	DISCONNECT_GP_LOGIN_PROFILE_DELETED,
	DISCONNECT_GP_LOGIN_CONNECTION_FAILED,
	DISCONNECT_GP_LOGIN_SERVER_AUTH_FAILED,
	DISCONNECT_SERIAL_INVALID,
	DISCONNECT_SERIAL_NOT_PRESENT,
	DISCONNECT_SERIAL_BANNED,
	DISCONNECT_GP_NEWUSER_BAD_NICK,
	DISCONNECT_GP_NEWUSER_BAD_PASSWORD,
	DISCONNECT_GP_NEWPROFILE_BAD_NICK,
	DISCONNECT_GP_NEWPROFILE_BAD_OLD_NICK,
	DISCONNECT_MAX,
};

enum QMStatus
{
	QM_IDLE,
	QM_JOININGQMCHANNEL,
	QM_LOOKINGFORBOT,
	QM_SENTINFO,
	QM_WORKING,
	QM_POOLSIZE,
	QM_WIDENINGSEARCH,
	QM_MATCHED,
	QM_INCHANNEL,
	QM_NEGOTIATINGFIREWALLS,
	QM_STARTINGGAME,
	QM_COULDNOTFINDBOT,
	QM_COULDNOTFINDCHANNEL,
	QM_COULDNOTNEGOTIATEFIREWALLS,
	QM_STOPPED,
};

// this class encapsulates an action the peer thread wants from the UI
class PeerResponse
{
public:
	enum
	{
		PEERRESPONSE_LOGIN,
		PEERRESPONSE_DISCONNECT,
		PEERRESPONSE_MESSAGE,
		PEERRESPONSE_GROUPROOM,
		PEERRESPONSE_STAGINGROOM,
		PEERRESPONSE_STAGINGROOMLISTCOMPLETE,
		PEERRESPONSE_STAGINGROOMPLAYERINFO,
		PEERRESPONSE_JOINGROUPROOM,
		PEERRESPONSE_CREATESTAGINGROOM,
		PEERRESPONSE_JOINSTAGINGROOM,
		PEERRESPONSE_PLAYERJOIN,
		PEERRESPONSE_PLAYERLEFT,
		PEERRESPONSE_PLAYERCHANGEDNICK,
		PEERRESPONSE_PLAYERINFO,
		PEERRESPONSE_PLAYERCHANGEDFLAGS,
		PEERRESPONSE_ROOMUTM,
		PEERRESPONSE_PLAYERUTM,
		PEERRESPONSE_QUICKMATCHSTATUS,
		PEERRESPONSE_GAMESTART,
		PEERRESPONSE_FAILEDTOHOST,
		PEERRESPONSE_MAX
	} peerResponseType;

	std::string groupRoomName; // can't be in union

	std::string nick;   // can't be in a union
	std::string oldNick;   // can't be in a union
	std::wstring text;  // can't be in a union
	std::string locale; // can't be in a union

	std::string stagingServerGameOptions; // full string from UTMs

	// game opts sent with PEERRESPONSE_STAGINGROOM
	std::wstring stagingServerName;
	std::string stagingServerPingString;
	std::string stagingServerLadderIP;
	std::string stagingRoomMapName;

	// game opts sent with PEERRESPONSE_STAGINGROOMPLAYERINFO
	std::string stagingRoomPlayerNames[MAX_SLOTS];

	std::string command;
	std::string commandOptions;

	union
	{
		struct
		{
			DisconnectReason reason;
		} discon;

		struct
		{
			Int id;
			Int numWaiting;
			Int maxWaiting;
			Int numGames;
			Int numPlaying;
		} groupRoom;

		struct
		{
			Int id;
			Bool ok;
		} joinGroupRoom;
		
		struct
		{
			Int result;
		} createStagingRoom;
		
		struct
		{
			Int id;
			Bool ok;
			Bool isHostPresent;
			Int result; // for failures
		} joinStagingRoom;
		
		struct
		{
			Bool isPrivate;
			Bool isAction;
			Int profileID;
		} message;

		struct
		{
			Int profileID;
			Int wins;
			Int losses;
			RoomType roomType;
			Int flags;
			UnsignedInt IP;
			Int rankPoints;
			Int side;
			Int preorder;
			UnsignedInt internalIP; // for us, on connection
			UnsignedInt externalIP; // for us, on connection
		} player;

		struct
		{
			Int id;
			Int action;
			Bool isStaging;
			Bool requiresPassword;
			Bool allowObservers;
      Bool useStats;
			UnsignedInt version;
			UnsignedInt exeCRC;
			UnsignedInt iniCRC;
			UnsignedShort ladderPort;
			Int wins[MAX_SLOTS];
			Int losses[MAX_SLOTS];
			Int profileID[MAX_SLOTS];
			Int faction[MAX_SLOTS];
			Int color[MAX_SLOTS];
			Int numPlayers;
			Int numObservers;
			Int maxPlayers;
			Int percentComplete;
		} stagingRoom;

		struct
		{
			QMStatus status;
			Int poolSize;
			Int mapIdx; // when matched
			Int seed; // when matched
			UnsignedInt IP[MAX_SLOTS]; // when matched
			Int side[MAX_SLOTS]; // when matched
			Int color[MAX_SLOTS]; // when matched
			Int nat[MAX_SLOTS];
		} qmStatus;
	unsigned char bfmeOpaquePayload[572];
	};
};

//-------------------------------------------------------------------------

// this is the actual message queue used to pass messages between threads
class GameSpyPeerMessageQueueInterface
{
public:
	virtual ~GameSpyPeerMessageQueueInterface() {}
	virtual void startThread( void ) = 0;
	virtual void endThread( void ) = 0;
	virtual Bool isThreadRunning( void ) = 0;
	virtual Bool isConnected( void ) = 0;
	virtual Bool isConnecting( void ) = 0;

	virtual void addRequest( const PeerRequest& req ) = 0;
	virtual Bool getRequest( PeerRequest& req ) = 0;

	virtual void addResponse( const PeerResponse& resp ) = 0;
	virtual Bool getResponse( PeerResponse& resp ) = 0;

	virtual SerialAuthResult getSerialAuthResult( void ) = 0;

	static GameSpyPeerMessageQueueInterface* createNewMessageQueue( void );
};

extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;

#endif // __PEERTHREAD_H__

#include "GameNetwork/GameSpy/LobbyUtils.h"

#include "GameNetwork/GameSpy/BuddyDefs.h"
#include "GameNetwork/GameSpy/PeerDefs.h"
#include "GameNetwork/GameSpy/PeerThread.h"
#include "GameNetwork/GameSpy/PersistentStorageDefs.h"
#include "GameNetwork/GameSpy/PersistentStorageThread.h"
#include "GameNetwork/GameSpyOverlay.h"
#include "GameNetwork/NAT.h"
#include "GameNetwork/GUIUtil.h"
#include "GameNetwork/GameSpy/GSConfig.h"

// Complete local objects and by-value argument extents witnessed in retail.
typedef char BfmeWolPeerResponseSize[sizeof(PeerResponse) == 0x330 ? 1 : -1];
typedef char BfmeWolPeerRequestSize[sizeof(PeerRequest) == 0x194 ? 1 : -1];
typedef char BfmeWolGameSlotSize[sizeof(GameSlot) == 0x44 ? 1 : -1];
typedef char BfmeWolPlayerStatsSize[sizeof(PSPlayerStats) == 0x1c4 ? 1 : -1];

//-------------------------------------------------------------------------------------------------
// Two BFME vtable drifts this file needs. Both are read straight off the retail
// call sites in getNextSelectablePlayer at 0x004F0B60, which is the body that
// proves this compiland owns them: GameSpyInfoInterface::getCurrentStagingRoom
// is slot 0xC4 (0xA8 in the vendored header) and GameInfo::amIHost /
// getLocalSlotNum are slots 0x10 / 0x14 (0x08 / 0x0C there). Spelled TU-locally
// rather than in the headers, the way this tree spells every other slot drift.
//-------------------------------------------------------------------------------------------------
class GameSpyStagingRoom;

// BFME clears the menu's retail state block through the already matched
// 0x004F0970 body (the 0x0001B095 incremental-link thunk).
void bfmeClearStateVJ( void );

// BFME's map-transfer predicate receives the game object.  The ZH header only
// exposes the AsciiString overload; the retail call site passes the staging
// room itself through the BFME overload below.
Bool WouldMapTransfer( GameInfo *game );
#pragma comment(linker, "/alternatename:?WouldMapTransfer@@YA_NPAVGameInfo@@@Z=?j_000393fb@@YAXXZ")

class BfmeVirtualGameSpyInfo
{
public:
	virtual void slot000() = 0;
	virtual void slot004() = 0;
	virtual void slot008() = 0;
	virtual void slot00C() = 0;
	virtual void slot010() = 0;
	virtual void slot014() = 0;
	virtual void slot018() = 0;
	virtual void slot01C() = 0;
	virtual void slot020() = 0;
	virtual void slot024() = 0;
	virtual void slot028() = 0;
	virtual void slot02C() = 0;
	virtual void slot030() = 0;
	virtual void slot034() = 0;
	virtual void slot038() = 0;
	virtual void slot03C() = 0;
	virtual void slot040() = 0;
	virtual void slot044() = 0;
	virtual void slot048() = 0;
	virtual void slot04C() = 0;
	virtual void slot050() = 0;
	virtual void slot054() = 0;
	virtual void slot058() = 0;
	virtual void slot05C() = 0;
	virtual void slot060() = 0;
	virtual void slot064() = 0;
	virtual void slot068() = 0;
	virtual void slot06C() = 0;
	virtual void slot070() = 0;
	virtual void slot074() = 0;
	virtual void slot078() = 0;
	virtual void slot07C() = 0;
	virtual void slot080() = 0;
	virtual void slot084() = 0;
	virtual void slot088() = 0;
	virtual void slot08C() = 0;
	virtual void slot090() = 0;
	virtual void slot094() = 0;
	virtual void slot098() = 0;
	virtual void slot09C() = 0;
	virtual void slot0A0() = 0;
	virtual void slot0A4() = 0;
	virtual void slot0A8() = 0;
	virtual void slot0AC() = 0;
	virtual void leaveStagingRoom() = 0;
	virtual void slot0B4() = 0;
	virtual void slot0B8() = 0;
	virtual void slot0BC() = 0;
	virtual Bool amIHost() = 0;
	virtual GameSpyStagingRoom *getCurrentStagingRoom() = 0;
	virtual void slot0C8() = 0;
	virtual void setGameOptions() = 0;
	virtual void slot0D0() = 0;
	virtual void slot0D4() = 0;
	virtual void slot0D8() = 0;
	virtual void slot0DC() = 0;
	virtual void slot0E0() = 0;
	virtual void slot0E4() = 0;
	virtual void unregisterTextWindow( GameWindow *window ) = 0;
	virtual Int addText( UnicodeString message, Color c, GameWindow *win ) = 0;
	virtual void slot0F0() = 0;
	virtual void slot0F4() = 0;
	virtual void slot0F8() = 0;
	virtual void slot0FC() = 0;
	virtual void slot100() = 0;
	virtual void slot104() = 0;
	virtual void slot108() = 0;
	virtual void slot10C() = 0;
	virtual void slot110() = 0;
	virtual const AsciiString &getPingString() = 0;
};

class BfmeWOLGameSpyStagingRoom
{
public:
	virtual void slot000() = 0;
	virtual void slot004() = 0;
	virtual void reset() = 0;
};

class Rva00537C00
{
public:
	void set();
};

extern Rva00537C00 *s_popBackExtra;

class BfmeWOLMapSelectLayout
{
public:
	virtual void slot00() = 0;
	virtual ~BfmeWOLMapSelectLayout();
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void destroyWindows() = 0;
};

// WindowLayout::hide is virtual in BFME at vtable slot 0x10, while the
// vendored ZH header exposes it as a non-virtual member.
class BfmeVirtualHideLayout
{
public:
	virtual void slot0() = 0;
	virtual void slot4() = 0;
	virtual void slot8() = 0;
	virtual void slotC() = 0;
	virtual void hide( Bool immediate ) = 0;
};

class BfmeVirtualStagingRoom
{
public:
	virtual void slot000() = 0;
	virtual void slot004() = 0;
	virtual void slot008() = 0;
	virtual void slot00C() = 0;
	virtual Bool amIHost() = 0;
	virtual Int getLocalSlotNum() = 0;
};

// GameInfo's BFME vtable has two leading slots that are absent from the
// vendored NAT shim. That puts resetAccepted at +0x18 in this callback's
// retail body. Keep this view local; the normal GameInfo type remains useful
// for its non-virtual slot accessors below.
class BfmeTemplateSelectionGameInfo
{
public:
	virtual Int slot000() = 0;
	virtual Int slot004() = 0;
	virtual void reset() = 0;
	virtual void startGame( Int gameID ) = 0;
	virtual Bool amIHost() const = 0;
	virtual Int getLocalSlotNum() const = 0;
	virtual void resetAccepted() = 0;
};

class BfmeStartGameInfo
{
public:
	virtual void slot000() = 0;
	virtual void slot004() = 0;
	virtual void slot008() = 0;
	virtual void startGame( Int gameID ) = 0;
};

// BFME's StringBase payload starts eight bytes after m_data.  The vendored
// StringBase wrappers keep str() out of line, but this body has the retail
// inline access at each of these call sites.
static __forceinline const char *BfmeStartAsciiString( const AsciiString &string )
{
	void *data = *(void *const *)&string;
	return data ? (const char *)data + 8 : (const char *)0x0107388B;
}

static __forceinline const unsigned short *BfmeStartUnicodeString( const UnicodeString &string )
{
	void *data = *(void *const *)&string;
	return data ? (const unsigned short *)((const char *)data + 8)
	            : (const unsigned short *)0x0107388C;
}

struct BfmeStartMapMetaDataView
{
	void *m_displayName;
	void *m_description;
	unsigned char m_extent[24];
	Int m_numPlayers;
	Bool m_isMultiplayer;
	Bool m_isScenarioMP;
	Bool m_isOfficial;
};

struct BfmeStartGlobalDataView
{
	unsigned char m_prefix[0xB0C];
	Int m_netMinPlayers;
};


void WOLDisplaySlotList( void );
extern void j_00006942();

#ifdef _INTERNAL
// for occasional debugging...
//#pragma optimize("", off)
//#pragma MESSAGE("************************************** WARNING, optimization disabled for debugging purposes")
#endif

extern std::list<PeerResponse> TheLobbyQueuedUTMs;
extern void MapSelectorTooltip(GameWindow *window, WinInstanceData *instData,	UnsignedInt mouse);


#if defined(_DEBUG) || defined(_INTERNAL)
extern Bool g_debugSlots;
void slotListDebugLog(const char *fmt, ...)
{
	static char buf[1024];
	va_list va;
	va_start( va, fmt );
	_vsnprintf(buf, 1024, fmt, va );
	va_end( va );
	buf[1023] = 0;

	DEBUG_LOG(("%s", buf));
	if (g_debugSlots)
	{
		UnicodeString msg;
		msg.translate(buf);
		TheGameSpyInfo->addText(msg, GameSpyColor[GSCOLOR_DEFAULT], NULL);
	}
}
#define SLOTLIST_DEBUG_LOG(x) slotListDebugLog x
#else
#define SLOTLIST_DEBUG_LOG(x) DEBUG_LOG(x)
#endif

// Verified BFME implementation: GameNetwork/GameSpy/SendStatsToOtherPlayers.cpp
extern void SendStatsToOtherPlayers(const GameInfo *game);

// PRIVATE DATA ///////////////////////////////////////////////////////////////////////////////////
static Bool isShuttingDown = false;
static Bool buttonPushed = false;
static char *nextScreen = NULL;
static Bool raiseMessageBoxes = false;
static Bool launchGameNext = FALSE;

// window ids ------------------------------------------------------------------------------
static NameKeyType parentWOLGameSetupID = NAMEKEY_INVALID;

static NameKeyType comboBoxPlayerID[MAX_SLOTS] = { NAMEKEY_INVALID,NAMEKEY_INVALID,
																											NAMEKEY_INVALID,NAMEKEY_INVALID,
																											NAMEKEY_INVALID,NAMEKEY_INVALID,
																											NAMEKEY_INVALID,NAMEKEY_INVALID };

static NameKeyType staticTextPlayerID[MAX_SLOTS] = { NAMEKEY_INVALID,NAMEKEY_INVALID,
																											NAMEKEY_INVALID,NAMEKEY_INVALID,
																											NAMEKEY_INVALID,NAMEKEY_INVALID,
																											NAMEKEY_INVALID,NAMEKEY_INVALID };

static NameKeyType buttonAcceptID[MAX_SLOTS] = { NAMEKEY_INVALID,NAMEKEY_INVALID,
																									NAMEKEY_INVALID,NAMEKEY_INVALID,
																									NAMEKEY_INVALID,NAMEKEY_INVALID,
																									NAMEKEY_INVALID,NAMEKEY_INVALID };

static NameKeyType comboBoxColorID[MAX_SLOTS] = { NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID };

static NameKeyType comboBoxPlayerTemplateID[MAX_SLOTS] = { NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID };

static NameKeyType comboBoxTeamID[MAX_SLOTS] = { NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID };
//static NameKeyType buttonStartPositionID[MAX_SLOTS] = { NAMEKEY_INVALID,NAMEKEY_INVALID,
//																										NAMEKEY_INVALID,NAMEKEY_INVALID,
//																										NAMEKEY_INVALID,NAMEKEY_INVALID,
//																										NAMEKEY_INVALID,NAMEKEY_INVALID };

static NameKeyType buttonMapStartPositionID[MAX_SLOTS] = { NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID };
static NameKeyType genericPingWindowID[MAX_SLOTS] = { NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID,
																										NAMEKEY_INVALID,NAMEKEY_INVALID };

static NameKeyType textEntryChatID = NAMEKEY_INVALID;
static NameKeyType textEntryMapDisplayID = NAMEKEY_INVALID;
static NameKeyType buttonBackID = NAMEKEY_INVALID;
static NameKeyType buttonStartID = NAMEKEY_INVALID;
static NameKeyType buttonEmoteID = NAMEKEY_INVALID;
static NameKeyType buttonSelectMapID = NAMEKEY_INVALID;
static NameKeyType windowMapID = NAMEKEY_INVALID;

static NameKeyType windowMapSelectMapID = NAMEKEY_INVALID;
static NameKeyType checkBoxUseStatsID = NAMEKEY_INVALID;
static NameKeyType checkBoxLimitSuperweaponsID = NAMEKEY_INVALID;
static NameKeyType comboBoxStartingCashID = NAMEKEY_INVALID;
static NameKeyType checkBoxLimitArmiesID = NAMEKEY_INVALID;

// Window Pointers ------------------------------------------------------------------------
static GameWindow *parentWOLGameSetup = NULL;
static GameWindow *buttonBack = NULL;
static GameWindow *buttonStart = NULL;
static GameWindow *buttonSelectMap = NULL;
static GameWindow *buttonEmote = NULL;
static GameWindow *textEntryChat = NULL;
static GameWindow *textEntryMapDisplay = NULL;
static GameWindow *windowMap = NULL;
static GameWindow *checkBoxUseStats = NULL;
static GameWindow *checkBoxLimitSuperweapons = NULL;
static GameWindow *comboBoxStartingCash = NULL;
static GameWindow *checkBoxLimitArmies = NULL;

static GameWindow *comboBoxPlayer[MAX_SLOTS] = {NULL,NULL,NULL,NULL,
																									 NULL,NULL,NULL,NULL };
static GameWindow *staticTextPlayer[MAX_SLOTS] = {NULL,NULL,NULL,NULL,
																									 NULL,NULL,NULL,NULL };
static GameWindow *buttonAccept[MAX_SLOTS] = {NULL,NULL,NULL,NULL,
																								NULL,NULL,NULL,NULL };

static GameWindow *comboBoxColor[MAX_SLOTS] = {NULL,NULL,NULL,NULL,
																								NULL,NULL,NULL,NULL };

static GameWindow *comboBoxPlayerTemplate[MAX_SLOTS] = {NULL,NULL,NULL,NULL,
																								NULL,NULL,NULL,NULL };

static GameWindow *comboBoxTeam[MAX_SLOTS] = {NULL,NULL,NULL,NULL,
																								NULL,NULL,NULL,NULL };

//static GameWindow *buttonStartPosition[MAX_SLOTS] = {NULL,NULL,NULL,NULL,
//																								NULL,NULL,NULL,NULL };
//
static GameWindow *buttonMapStartPosition[MAX_SLOTS] = {NULL,NULL,NULL,NULL,
																								NULL,NULL,NULL,NULL };

static GameWindow *genericPingWindow[MAX_SLOTS] = {NULL,NULL,NULL,NULL,
																								NULL,NULL,NULL,NULL };

static const Image *pingImages[3] = { NULL, NULL, NULL };

WindowLayout *WOLMapSelectLayout = NULL;

void PopBackToLobby( void )
{
	delete TheNAT;
	TheNAT = NULL;

	if (TheGameSpyInfo)
	{
		((BfmeWOLGameSpyStagingRoom *)
			((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->getCurrentStagingRoom())->reset();
		((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->leaveStagingRoom();
	}

	if (parentWOLGameSetup)
	{
		nextScreen = "Menus/WOLCustomLobby.wnd";
		TheShell->pop();
		return;
	}

	if (s_popBackExtra)
		s_popBackExtra->set();
}

void updateMapStartSpots( GameInfo *myGame, GameWindow *buttonMapStartPositions[], Bool onLoadScreen = FALSE );
void positionStartSpots( GameInfo *myGame, GameWindow *buttonMapStartPositions[], GameWindow *mapWindow, Bool onLoadScreen = FALSE);
void positionStartSpots(AsciiString mapName, GameWindow *buttonMapStartPositions[], GameWindow *mapWindow, Bool onLoadScreen = FALSE);
void WOLPositionStartSpots( void )
{
	GameWindow *win = windowMap;
	if (WOLMapSelectLayout != NULL) {
		win = TheWindowManager->winGetWindowFromId(NULL, windowMapSelectMapID);

		// get the controls.
		NameKeyType listboxMapID = TheNameKeyGenerator->nameToKey( AsciiString("WOLMapSelectMenu.wnd:ListboxMap") );
		GameWindow *listboxMap = TheWindowManager->winGetWindowFromId( NULL, listboxMapID );

		if (listboxMap != NULL) {
			Int selected;
			UnicodeString map;
			
			// get the selected index
			GadgetListBoxGetSelected( listboxMap, &selected );

			if( selected != -1 )
			{

				// get text of the map to load
				map = GadgetListBoxGetText( listboxMap, selected, 0 );
				
				
				// set the map name in the global data map name
				AsciiString asciiMap;
				const char *mapFname = (const char *)GadgetListBoxGetItemData( listboxMap, selected );
				DEBUG_ASSERTCRASH(mapFname, ("No map item data"));
				if (mapFname) {
					asciiMap = mapFname;
				} else {
					asciiMap.translate( map );
				}

				positionStartSpots(asciiMap, buttonMapStartPosition, win);
			}			
		}

	} else {
		DEBUG_ASSERTCRASH(win != NULL, ("no map preview window"));
		positionStartSpots( ((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->getCurrentStagingRoom(), buttonMapStartPosition, win);
	}
}
static void savePlayerInfo( void )
{
	if (TheGameSpyGame)
	{
		Int slotNum = TheGameSpyGame->getLocalSlotNum();
		if (slotNum >= 0)
		{
			GameSpyGameSlot *slot = TheGameSpyGame->getGameSpySlot(slotNum);
			if (slot)
			{
				// save off some prefs
				CustomMatchPreferences pref;
				pref.setPreferredColor(slot->getColor());
				pref.setPreferredFaction(slot->getPlayerTemplate());
				if (TheGameSpyGame->amIHost())
				{
					pref.setPreferredMap(TheGameSpyGame->getMap());
          pref.setSuperweaponRestricted( TheGameSpyGame->getSuperweaponRestriction() != 0 );
          pref.setStartingCash( TheGameSpyGame->getStartingCash() );
        }
				pref.write();
			}
		}
	}
}

// Tooltips -------------------------------------------------------------------------------

static void playerTooltip(GameWindow *window,
													WinInstanceData *instData,
													UnsignedInt mouse)
{
	Int slotIdx = -1;
	for (Int i=0; i<MAX_SLOTS; ++i)
	{
		if (window == comboBoxPlayer[i] || window == staticTextPlayer[i])
		{
			slotIdx = i;
			break;
		}
	}
	if (slotIdx < 0)
	{
		TheMouse->setCursorTooltip( UnicodeString::TheEmptyString, -1, NULL, 1.5f );
		return;
	}

	GameSpyStagingRoom *game = TheGameSpyInfo->getCurrentStagingRoom();
	if (!game)
	{
		TheMouse->setCursorTooltip( UnicodeString::TheEmptyString, -1, NULL, 1.5f );
		return;
	}

	GameSpyGameSlot *slot = game->getGameSpySlot(slotIdx);
	if (!slot || !slot->isHuman())
	{
		TheMouse->setCursorTooltip( UnicodeString::TheEmptyString, -1, NULL, 1.5f );
		return;
	}

	// for tooltip, we want:
	// * player name
	// * ping
	// * locale
	// * win/loss history
	// * discons/desyncs as one var
	// * favorite army
	// in that order.  got it?  good.

	UnicodeString uName = slot->getName();

	AsciiString aName;
	aName.translate(uName);
	PlayerInfoMap::iterator pmIt = TheGameSpyInfo->getPlayerInfoMap()->find(aName);
	if (pmIt == TheGameSpyInfo->getPlayerInfoMap()->end())
	{
		TheMouse->setCursorTooltip( uName, -1, NULL, 1.5f );
		return;
	}
	Int profileID = pmIt->second.m_profileID;

	PSPlayerStats stats = TheGameSpyPSMessageQueue->findPlayerStatsByID(profileID);
	if (stats.id == 0)
	{
		TheMouse->setCursorTooltip( uName, -1, NULL, 1.5f );
		return;
	}

	Bool isLocalPlayer = slot == game->getGameSpySlot(game->getLocalSlotNum());

	AsciiString localeIdentifier;
	localeIdentifier.format("WOL:Locale%2.2d", stats.locale);
	UnicodeString	playerInfo;
	Int totalWins = 0, totalLosses = 0, totalDiscons = 0;
	PerGeneralMap::iterator it;

	for (it = stats.wins.begin(); it != stats.wins.end(); ++it)
	{
		totalWins += it->second;
	}
	for (it = stats.losses.begin(); it != stats.losses.end(); ++it)
	{
		totalLosses += it->second;
	}
	for (it = stats.discons.begin(); it != stats.discons.end(); ++it)
	{
		totalDiscons += it->second;
	}
	for (it = stats.desyncs.begin(); it != stats.desyncs.end(); ++it)
	{
		totalDiscons += it->second;
	}
	UnicodeString favoriteSide;
	Int numGames = 0;
	Int favorite = 0;
	for(it = stats.games.begin(); it != stats.games.end(); ++it)
	{
		if(it->second >= numGames)
		{
			numGames = it->second;
			favorite = it->first;
		}
	}
	if(numGames == 0)
		favoriteSide = TheGameText->fetch("GUI:None");
	else if( stats.gamesAsRandom >= numGames )
		favoriteSide = TheGameText->fetch("GUI:Random");
	else
	{		
		const PlayerTemplate *fac = ThePlayerTemplateStore->getNthPlayerTemplate(favorite);
		if (fac)
		{
			AsciiString side;
			side.format("SIDE:%s", fac->getSide().str());

			favoriteSide = TheGameText->fetch(side);
		}
	}

	playerInfo.format(TheGameText->fetch("TOOLTIP:StagingPlayerInfo"),
		TheGameText->fetch(localeIdentifier).str(),
		slot->getPingAsInt(),
		totalWins, totalLosses, totalDiscons,
		favoriteSide.str());

	UnicodeString tooltip = UnicodeString::TheEmptyString;
	if (isLocalPlayer)
	{
		tooltip.format(TheGameText->fetch("TOOLTIP:LocalPlayer"), uName.str());
	}
	else
	{
		// not us
		if (TheGameSpyInfo->getBuddyMap()->find(profileID) != TheGameSpyInfo->getBuddyMap()->end())
		{
			// buddy
			tooltip.format(TheGameText->fetch("TOOLTIP:BuddyPlayer"), uName.str());
		}
		else
		{
			if (profileID)
			{
				// non-buddy profiled player
				tooltip.format(TheGameText->fetch("TOOLTIP:ProfiledPlayer"), uName.str());
			}
			else
			{
				// non-profiled player
				tooltip.format(TheGameText->fetch("TOOLTIP:GenericPlayer"), uName.str());
			}
		}
	}

	tooltip.concat(playerInfo);

	TheMouse->setCursorTooltip( tooltip, -1, NULL, 1.5f ); // the text and width are the only params used.  the others are the default values.
}

void gameAcceptTooltip(GameWindow *window, WinInstanceData *instData, UnsignedInt mouse)
{
	Int x, y;
	x = LOLONGTOSHORT(mouse);
	y = HILONGTOSHORT(mouse);

	Int winPosX, winPosY, winWidth, winHeight;

	window->winGetScreenPosition(&winPosX, &winPosY);

	window->winGetSize(&winWidth, &winHeight);

	if ((x > winPosX && x < (winPosX + winWidth)) && (y > winPosY && y < (winPosY + winHeight)))
	{
		TheMouse->setCursorTooltip(TheGameText->fetch("TOOLTIP:GameAcceptance"), -1, NULL);
	}
}

void pingTooltip(GameWindow *window, WinInstanceData *instData, UnsignedInt mouse)
{
	Int x, y;
	x = LOLONGTOSHORT(mouse);
	y = HILONGTOSHORT(mouse);

	
	Int winPosX, winPosY, winWidth, winHeight;

	window->winGetScreenPosition(&winPosX, &winPosY);

	window->winGetSize(&winWidth, &winHeight);

	if ((x > winPosX && x < (winPosX + winWidth)) && (y > winPosY && y < (winPosY + winHeight)))
	{
		TheMouse->setCursorTooltip(TheGameText->fetch("TOOLTIP:ConnectionSpeed"), -1, NULL);
	}
}

//external declarations of the Gadgets the callbacks can use
GameWindow *listboxGameSetupChat = NULL;
NameKeyType listboxGameSetupChatID = NAMEKEY_INVALID;

static void handleColorSelection(int index)
{
	GameWindow *combo = comboBoxColor[index];
	Int color, selIndex;
	GadgetComboBoxGetSelectedPos(combo, &selIndex);
	color = (Int)GadgetComboBoxGetItemData(combo, selIndex);

	GameInfo *myGame = TheGameSpyInfo->getCurrentStagingRoom();

	if (myGame)
	{
		GameSlot * slot = myGame->getSlot(index);
		if (color == slot->getColor())
			return;

		if (color >= -1 && color < TheMultiplayerSettings->getNumColors())
		{
			Bool colorAvailable = TRUE;
			if(color != -1 )
			{
				for(Int i=0; i <MAX_SLOTS; i++)
				{
					GameSlot *checkSlot = myGame->getSlot(i);
					if(color == checkSlot->getColor() && slot != checkSlot)
					{
						colorAvailable = FALSE;
						break;
					}
				}
			}
			if(!colorAvailable)
				return;
		}

		slot->setColor(color);

		if (TheGameSpyInfo->amIHost())
		{
			// send around a new slotlist
			TheGameSpyInfo->setGameOptions();
			WOLDisplaySlotList();
		}
		else
		{
			// request the color from the host
			if (!slot->isPlayer(TheGameSpyInfo->getLocalName()))
				return;

			AsciiString options;
			options.format("Color=%d", color);
			AsciiString hostName;
			hostName.translate(myGame->getSlot(0)->getName());
			PeerRequest req;
			req.peerRequestType = PeerRequest::PEERREQUEST_UTMPLAYER;
			req.UTM.isStagingRoom = TRUE;
			req.id = "REQ/";
			req.nick = hostName.str();
			req.options = options.str();
			TheGameSpyPeerMessageQueue->addRequest(req);
		}
	}
}

static void handlePlayerTemplateSelection(int index)
{
	GameWindow *combo = comboBoxPlayerTemplate[index];
	Int playerTemplate, selIndex;
	GadgetComboBoxGetSelectedPos(combo, &selIndex);
	playerTemplate = (Int)GadgetComboBoxGetItemData(combo, selIndex);
	GameInfo *myGame = ((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->getCurrentStagingRoom();

	if (myGame)
	{
		GameSlot * slot = myGame->getSlot(index);
		if (playerTemplate == slot->getPlayerTemplate())
			return;

		Int oldTemplate = slot->getPlayerTemplate();
		slot->setPlayerTemplate(playerTemplate);

		if (oldTemplate == PLAYERTEMPLATE_OBSERVER)
		{
			// was observer, so populate color & team with all, and enable
			GadgetComboBoxSetSelectedPos(comboBoxColor[index], 0);
			GadgetComboBoxSetSelectedPos(comboBoxTeam[index], 0);
			slot->setStartPos(-1);
		}
		else if (playerTemplate == PLAYERTEMPLATE_OBSERVER)
		{
			// is becoming observer, so populate color & team with random only, and disable
			GadgetComboBoxSetSelectedPos(comboBoxColor[index], 0);
			GadgetComboBoxSetSelectedPos(comboBoxTeam[index], 0);
			slot->setStartPos(-1);
		}


		if (((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->amIHost())
		{
			// send around a new slotlist
			((BfmeTemplateSelectionGameInfo *)myGame)->resetAccepted();
			((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->setGameOptions();
			j_00006942();
		}
		else
		{
			// request the playerTemplate from the host
			AsciiString options;
			options.format("PlayerTemplate=%d", playerTemplate);
			AsciiString hostName;
			hostName.translate(myGame->getSlot(0)->getName());
			PeerRequest req;
			req.peerRequestType = PeerRequest::PEERREQUEST_UTMPLAYER;
			req.UTM.isStagingRoom = TRUE;
			req.id = "REQ/";
			req.nick = BfmeStartAsciiString(hostName);
			req.options = BfmeStartAsciiString(options);
			TheGameSpyPeerMessageQueue->addRequest(req);
		}
	}
}


static void handleStartPositionSelection(Int player, int startPos)
{
	GameSpyStagingRoom *myGame = TheGameSpyInfo->getCurrentStagingRoom();
	
	if (myGame)
	{
		GameSpyGameSlot * slot = myGame->getGameSpySlot(player);
		if (!slot)
			return;

		if (startPos == slot->getStartPos())
			return;
		Bool skip = FALSE;
		if (startPos < 0)
		{
			skip = TRUE;
		}

		if(!skip)
		{	
			Bool isAvailable = TRUE;
			for(Int i = 0; i < MAX_SLOTS; ++i)
			{
				if(i != player && myGame->getSlot(i)->getStartPos() == startPos)
				{
					isAvailable = FALSE;
					break;
				}
			}
			if( !isAvailable )
				return;
		}
		slot->setStartPos(startPos);

		if (myGame->amIHost())
		{
			// send around a new slotlist
			myGame->resetAccepted();
			TheGameSpyInfo->setGameOptions();
			WOLDisplaySlotList();
		}
		else
		{
			// request the color from the host
			if (AreSlotListUpdatesEnabled())
			{
				// request the playerTemplate from the host
				AsciiString options;
				options.format("StartPos=%d", slot->getStartPos());
				AsciiString hostName;
				hostName.translate(myGame->getSlot(0)->getName());
				PeerRequest req;
				req.peerRequestType = PeerRequest::PEERREQUEST_UTMPLAYER;
				req.UTM.isStagingRoom = TRUE;
				req.id = "REQ/";
				req.nick = hostName.str();
				req.options = options.str();
				TheGameSpyPeerMessageQueue->addRequest(req);

			}
		}
	}
}



static void handleTeamSelection(int index)
{
	GameWindow *combo = comboBoxTeam[index];
	Int team, selIndex;
	GadgetComboBoxGetSelectedPos(combo, &selIndex);
	team = (Int)GadgetComboBoxGetItemData(combo, selIndex);
	GameInfo *myGame = ((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->getCurrentStagingRoom();

	if (myGame)
	{
		GameSlot * slot = myGame->getSlot(index);
		if (team == slot->getTeamNumber())
			return;

		slot->setTeamNumber(team);

		if (((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->amIHost())
		{
			// send around a new slotlist
			((BfmeTemplateSelectionGameInfo *)myGame)->resetAccepted();
			((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->setGameOptions();
			j_00006942();
		}
		else
		{
			// request the team from the host
			AsciiString options;
			options.format("Team=%d", team);
			AsciiString hostName;
			hostName.translate(myGame->getSlot(0)->getName());
			PeerRequest req;
			req.peerRequestType = PeerRequest::PEERREQUEST_UTMPLAYER;
			req.UTM.isStagingRoom = TRUE;
			req.id = "REQ/";
			req.nick = BfmeStartAsciiString(hostName);
			req.options = BfmeStartAsciiString(options);
			TheGameSpyPeerMessageQueue->addRequest(req);
		}
	}
}

static void handleStartingCashSelection()
{
  GameInfo *myGame = TheGameSpyInfo->getCurrentStagingRoom();
  
  if (myGame)
  {
    Int selIndex;
    GadgetComboBoxGetSelectedPos(comboBoxStartingCash, &selIndex);
    
    Money startingCash;
    startingCash.deposit( (UnsignedInt)GadgetComboBoxGetItemData( comboBoxStartingCash, selIndex ), FALSE );
    myGame->setStartingCash( startingCash );
    myGame->resetAccepted();
    
    if (myGame->amIHost())
    {
      // send around the new data
      TheGameSpyInfo->setGameOptions();
      WOLDisplaySlotList();// Update the accepted button UI
    }
  }
}

static void handleLimitSuperweaponsClick()
{
  GameInfo *myGame = TheGameSpyInfo->getCurrentStagingRoom();
  
  if (myGame)
  {
    // At the moment, 1 and 0 are the only choices supported in the GUI, though the system could
    // support more.
    if ( GadgetCheckBoxIsChecked( checkBoxLimitSuperweapons ) )
    {
      myGame->setSuperweaponRestriction( 1 );
    }
    else
    {
      myGame->setSuperweaponRestriction( 0 );
    }
    myGame->resetAccepted();
    
    if (myGame->amIHost())
    {
      // send around a new slotlist
      TheGameSpyInfo->setGameOptions();
      WOLDisplaySlotList();// Update the accepted button UI
    }
  }
}


static void StartPressed(void)
{
	Bool isReady = TRUE;
	Bool allHaveMap = TRUE;
	Int playerCount = 0;
	Int humanCount = 0;
	GameSpyStagingRoom *myGame = ((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->getCurrentStagingRoom();
	if (!myGame)
		return;

	// see if everyone's accepted and count the number of players in the game
	UnicodeString mapDisplayName;
	const MapMetaData *mapData = TheMapCache->findMap( myGame->getMap() );
	Bool willTransfer = TRUE;
	if (mapData)
	{
		const BfmeStartMapMetaDataView *bfmeMapData = (const BfmeStartMapMetaDataView *)mapData;
		mapDisplayName.format(UnicodeString(L"%ls"), BfmeStartUnicodeString(*(const UnicodeString *)&bfmeMapData->m_displayName));
		willTransfer = !bfmeMapData->m_isOfficial;
	}
	else
	{
		mapDisplayName.format(UnicodeString(L"%hs"), BfmeStartAsciiString(myGame->getMap()));
		willTransfer = WouldMapTransfer(myGame);
	}
	for( int i = 0; i < MAX_SLOTS; i++ )
	{
		if ((myGame->getSlot(i)->isAccepted() == FALSE) && (myGame->getSlot(i)->isHuman() == TRUE))
		{
			isReady = FALSE;
			if (!myGame->getSlot(i)->hasMap() && !willTransfer)
			{
				UnicodeString msg;
				msg.format(TheGameText->fetch("GUI:PlayerNoMap"), BfmeStartUnicodeString(myGame->getSlot(i)->getName()), BfmeStartUnicodeString(mapDisplayName));
				((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->addText(msg, GameSpyColor[GSCOLOR_DEFAULT], listboxGameSetupChat);
				allHaveMap = FALSE;
			}
		}
		if(myGame->getSlot(i)->isOccupied() && myGame->getSlot(i)->getPlayerTemplate() != PLAYERTEMPLATE_OBSERVER)
		{
			if (myGame->getSlot(i)->isHuman())
				humanCount++;
			playerCount++;
		}
	}

	// Check for too many players
	const MapMetaData *md = TheMapCache->findMap( myGame->getMap() );
	if (!md || ((const BfmeStartMapMetaDataView *)md)->m_numPlayers < playerCount)
	{
		if (((BfmeVirtualStagingRoom *)myGame)->amIHost())
		{
			UnicodeString text;
			text.format(TheGameText->fetch("LAN:TooManyPlayers"), (md)?((const BfmeStartMapMetaDataView *)md)->m_numPlayers:0);
			((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->addText(text, GameSpyColor[GSCOLOR_DEFAULT], listboxGameSetupChat);
		}
		return;
	}

	// Check for observer + AI players
	if (((const BfmeStartGlobalDataView *)TheGlobalData)->m_netMinPlayers && !humanCount)
	{
		if (((BfmeVirtualStagingRoom *)myGame)->amIHost())
		{
			UnicodeString text = TheGameText->fetch("GUI:NeedHumanPlayers");
			((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->addText(text, GameSpyColor[GSCOLOR_DEFAULT], listboxGameSetupChat);
		}
		return;
	}

	// Check for too few players
	if (playerCount < ((const BfmeStartGlobalDataView *)TheGlobalData)->m_netMinPlayers)
	{
		if (((BfmeVirtualStagingRoom *)myGame)->amIHost())
		{
			UnicodeString text;
			text.format(TheGameText->fetch("LAN:NeedMorePlayers"),playerCount);
			((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->addText(text, GameSpyColor[GSCOLOR_DEFAULT], listboxGameSetupChat);
		}
		return;
	}

	// Check for too few teams
	int numRandom = 0;
	std::set<Int> teams; 
	for (i=0; i<MAX_SLOTS; ++i)
	{
		GameSlot *slot = myGame->getSlot(i);
		if (slot && slot->isOccupied() && slot->getPlayerTemplate() != PLAYERTEMPLATE_OBSERVER)
		{
			if (slot->getTeamNumber() >= 0)
			{
				teams.insert(slot->getTeamNumber());
			}
			else
			{
				++numRandom;
			}
		}
	}
	if (numRandom + teams.size() < ((const BfmeStartGlobalDataView *)TheGlobalData)->m_netMinPlayers)
	{
		if (((BfmeVirtualStagingRoom *)myGame)->amIHost())
		{
			UnicodeString text;
			text.format(TheGameText->fetch("LAN:NeedMoreTeams"));
			((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->addText(text, GameSpyColor[GSCOLOR_DEFAULT], listboxGameSetupChat);
		}
		return;
	}

	if (numRandom + teams.size() < 2)
	{
		UnicodeString text;
		text.format(TheGameText->fetch("GUI:SandboxMode"));
		((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->addText(text, GameSpyColor[GSCOLOR_DEFAULT], listboxGameSetupChat);
	}

	if(isReady)
	{
		PeerRequest req;
		req.peerRequestType = PeerRequest::PEERREQUEST_STARTGAME;
		TheGameSpyPeerMessageQueue->addRequest(req);

		SendStatsToOtherPlayers(myGame);

		// we've started, there's no going back
		// i.e. disable the back button.
		buttonBack->winEnable(FALSE);
		GameWindow *buttonBuddy = TheWindowManager->winGetWindowFromId(NULL, NAMEKEY("GameSpyGameOptionsMenu.wnd:ButtonCommunicator"));
		if (buttonBuddy)
			buttonBuddy->winEnable(FALSE);
		GameSpyCloseOverlay(GSOVERLAY_BUDDY);

		*TheGameSpyGame = *myGame;
		((BfmeStartGameInfo *)TheGameSpyGame)->startGame(0);
	}
	else if (allHaveMap)
	{
		((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->addText(TheGameText->fetch("GUI:NotifiedStartIntent"), GameSpyColor[GSCOLOR_DEFAULT], listboxGameSetupChat);
		PeerRequest req;
		req.peerRequestType = PeerRequest::PEERREQUEST_UTMROOM;
		req.UTM.isStagingRoom = TRUE;
		req.id = "HWS/";
		req.options = "true";
		TheGameSpyPeerMessageQueue->addRequest(req);
	}

}//void StartPressed(void)

//-------------------------------------------------------------------------------------------------
/** Update options on screen */
//-------------------------------------------------------------------------------------------------
void WOLDisplayGameOptions( void )
{
	GameSpyStagingRoom *theGame =
		((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->getCurrentStagingRoom();
	if (!parentWOLGameSetup || !theGame)
		return;

	const GameSlot *localSlot = NULL;
	if (((BfmeVirtualStagingRoom *)theGame)->getLocalSlotNum() >= 0)
		localSlot = theGame->getConstSlot(
			((BfmeVirtualStagingRoom *)theGame)->getLocalSlotNum());

	const MapMetaData *md = TheMapCache->findMap(
		((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->getCurrentStagingRoom()->getMap());
	if (md && localSlot && localSlot->hasMap())
	{
		GadgetStaticTextSetText(textEntryMapDisplay, md->m_displayName);
	}
	else
	{
		AsciiString s =
			((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->getCurrentStagingRoom()->getMap();
		if (s.reverseFind('\\'))
		{
			s = s.reverseFind('\\') + 1;
		}
		UnicodeString mapDisplay;
		mapDisplay.translate(s);
		GadgetStaticTextSetText(textEntryMapDisplay, mapDisplay);
	}
	WOLPositionStartSpots();
	updateMapStartSpots(
		((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->getCurrentStagingRoom(),
		buttonMapStartPosition);
}


//  -----------------------------------------------------------------------------------------
// The Bad munkee slot list displaying function
//-------------------------------------------------------------------------------------------------
void WOLDisplaySlotList( void )
{
	if (!parentWOLGameSetup || !((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->getCurrentStagingRoom())
		return;

	GameSpyStagingRoom *game = ((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->getCurrentStagingRoom();
	if (!game->isInGame())
		return;

	DEBUG_ASSERTCRASH(!game->getConstSlot(0)->isOpen(), ("Open host!"));

	UpdateSlotList( game, comboBoxPlayer, comboBoxColor,
		comboBoxPlayerTemplate, comboBoxTeam, buttonAccept, buttonStart, buttonMapStartPosition );

	WOLDisplayGameOptions();

	for (Int i=0; i<MAX_SLOTS; ++i)
	{
		GameSpyGameSlot *slot = game->getGameSpySlot(i);
		if (slot && slot->isHuman())
		{
			if (i == ((BfmeVirtualStagingRoom *)game)->getLocalSlotNum())
			{
				// set up my own ping...
				slot->setPingString(((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->getPingString());
			}

			if (genericPingWindow[i])
			{
				genericPingWindow[i]->winHide(FALSE);
				Int ping = slot->getPingAsInt();
				if (ping < TheGameSpyConfig->getPingCutoffGood())
				{
					genericPingWindow[i]->winSetEnabledImage(0, pingImages[0]);
				}
				else if (ping < TheGameSpyConfig->getPingCutoffBad())
				{
					genericPingWindow[i]->winSetEnabledImage(0, pingImages[1]);
				}
				else
				{
					genericPingWindow[i]->winSetEnabledImage(0, pingImages[2]);
				}
			}
		}
		else
		{
			if (genericPingWindow[i])
				genericPingWindow[i]->winHide(TRUE);
		}
	}
}

//-------------------------------------------------------------------------------------------------
/** Initialize the Gadgets Options Menu */
//-------------------------------------------------------------------------------------------------
void InitWOLGameGadgets( void )
{
	GameSpyStagingRoom *theGameInfo = TheGameSpyInfo->getCurrentStagingRoom();
	pingImages[0] = TheMappedImageCollection->findImageByName("Ping03");
	pingImages[1] = TheMappedImageCollection->findImageByName("Ping02");
	pingImages[2] = TheMappedImageCollection->findImageByName("Ping01");
	DEBUG_ASSERTCRASH(pingImages[0], ("Can't find ping image!"));
	DEBUG_ASSERTCRASH(pingImages[1], ("Can't find ping image!"));
	DEBUG_ASSERTCRASH(pingImages[2], ("Can't find ping image!"));

	//Initialize the gadget IDs
	parentWOLGameSetupID = TheNameKeyGenerator->nameToKey( AsciiString( "GameSpyGameOptionsMenu.wnd:GameSpyGameOptionsMenuParent" ) );
	buttonBackID = TheNameKeyGenerator->nameToKey( AsciiString( "GameSpyGameOptionsMenu.wnd:ButtonBack" ) );
	buttonStartID = TheNameKeyGenerator->nameToKey( AsciiString( "GameSpyGameOptionsMenu.wnd:ButtonStart" ) );
	textEntryChatID = TheNameKeyGenerator->nameToKey( AsciiString( "GameSpyGameOptionsMenu.wnd:TextEntryChat" ) );
	textEntryMapDisplayID = TheNameKeyGenerator->nameToKey( AsciiString( "GameSpyGameOptionsMenu.wnd:TextEntryMapDisplay" ) );
	listboxGameSetupChatID = TheNameKeyGenerator->nameToKey( AsciiString( "GameSpyGameOptionsMenu.wnd:ListboxChatWindowGameSpyGameSetup" ) );
	buttonEmoteID = TheNameKeyGenerator->nameToKey( AsciiString( "GameSpyGameOptionsMenu.wnd:ButtonEmote" ) );
	buttonSelectMapID = TheNameKeyGenerator->nameToKey( AsciiString( "GameSpyGameOptionsMenu.wnd:ButtonSelectMap" ) );
	checkBoxUseStatsID = TheNameKeyGenerator->nameToKey( AsciiString( "GameSpyGameOptionsMenu.wnd:CheckBoxUseStats" ) );
	windowMapID = TheNameKeyGenerator->nameToKey( AsciiString( "GameSpyGameOptionsMenu.wnd:MapWindow" ) );
  checkBoxLimitSuperweaponsID = TheNameKeyGenerator->nameToKey(AsciiString("GameSpyGameOptionsMenu.wnd:CheckboxLimitSuperweapons"));
  comboBoxStartingCashID = TheNameKeyGenerator->nameToKey(AsciiString("GameSpyGameOptionsMenu.wnd:ComboBoxStartingCash"));
  checkBoxLimitArmiesID = TheNameKeyGenerator->nameToKey(AsciiString("GameSpyGameOptionsMenu.wnd:CheckBoxLimitArmies"));
	windowMapSelectMapID = TheNameKeyGenerator->nameToKey(AsciiString("WOLMapSelectMenu.wnd:WinMapPreview"));

	NameKeyType staticTextTitleID = NAMEKEY("GameSpyGameOptionsMenu.wnd:StaticTextGameName");

	// Initialize the pointers to our gadgets
	parentWOLGameSetup = TheWindowManager->winGetWindowFromId( NULL, parentWOLGameSetupID );
	buttonEmote = TheWindowManager->winGetWindowFromId( parentWOLGameSetup,buttonEmoteID  );
	buttonSelectMap = TheWindowManager->winGetWindowFromId( parentWOLGameSetup,buttonSelectMapID  );
	checkBoxUseStats = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, checkBoxUseStatsID );
	buttonStart = TheWindowManager->winGetWindowFromId( parentWOLGameSetup,buttonStartID  );
	buttonBack = TheWindowManager->winGetWindowFromId( parentWOLGameSetup,  buttonBackID);
	listboxGameSetupChat = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, listboxGameSetupChatID );
	textEntryChat = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, textEntryChatID );
	textEntryMapDisplay = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, textEntryMapDisplayID );
	windowMap = TheWindowManager->winGetWindowFromId( parentWOLGameSetup,windowMapID  );
  DEBUG_ASSERTCRASH(windowMap, ("Could not find the parentWOLGameSetup.wnd:MapWindow" ));

  checkBoxLimitSuperweapons = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, checkBoxLimitSuperweaponsID );
  DEBUG_ASSERTCRASH(windowMap, ("Could not find the GameSpyGameOptionsMenu.wnd:CheckboxLimitSuperweapons" ));
  comboBoxStartingCash = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, comboBoxStartingCashID );
  DEBUG_ASSERTCRASH(windowMap, ("Could not find the GameSpyGameOptionsMenu.wnd:ComboBoxStartingCash" ));
  PopulateStartingCashComboBox( comboBoxStartingCash, TheGameSpyGame );
  checkBoxLimitArmies = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, checkBoxLimitArmiesID );
  DEBUG_ASSERTCRASH(windowMap, ("Could not find the GameSpyGameOptionsMenu.wnd:CheckBoxLimitArmies" ));

  // Limit Armies can ONLY be set in the Host Game window (PopupHostGame.wnd)
  checkBoxLimitArmies->winEnable( false );
  // Ditto use stats
  checkBoxUseStats->winEnable( false );
	Int isUsingStats = TheGameSpyGame->getUseStats();
  GadgetCheckBoxSetChecked(checkBoxUseStats, isUsingStats );
  checkBoxUseStats->winSetTooltip( TheGameText->fetch( isUsingStats ? "TOOLTIP:UseStatsOn" : "TOOLTIP:UseStatsOff" ) );

  if ( !TheGameSpyGame->amIHost() )
  {
    checkBoxLimitSuperweapons->winEnable( false );
    comboBoxStartingCash->winEnable( false );
		NameKeyType labelID = TheNameKeyGenerator->nameToKey(AsciiString("GameSpyGameOptionsMenu.wnd:StartingCashLabel"));
		TheWindowManager->winGetWindowFromId(parentWOLGameSetup, labelID)->winEnable( FALSE );
  }

	if (isUsingStats)
	{
		// Recorded stats games can never limit superweapons, limit armies, or have inflated starting cash.
		// This should probably be enforced at the gamespy level as well, to prevent expoits.
		checkBoxLimitSuperweapons->winEnable( FALSE );
		comboBoxStartingCash->winEnable( FALSE );
		checkBoxLimitArmies->winEnable( FALSE );
		NameKeyType labelID = TheNameKeyGenerator->nameToKey(AsciiString("GameSpyGameOptionsMenu.wnd:StartingCashLabel"));
		TheWindowManager->winGetWindowFromId(parentWOLGameSetup, labelID)->winEnable( FALSE );
	}

	//Added By Sadullah Nader
	//Tooltip Function set 
	windowMap->winSetTooltipFunc(MapSelectorTooltip);
	//
	
	GameWindow *staticTextTitle = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, staticTextTitleID );
	if (staticTextTitle)
	{
		GadgetStaticTextSetText(staticTextTitle, TheGameSpyGame->getGameName());
	}

	if (!theGameInfo)
	{
		DEBUG_CRASH(("No staging room!"));
		return;
	}

	for (Int i = 0; i < MAX_SLOTS; i++)
	{
		AsciiString tmpString;
		tmpString.format("GameSpyGameOptionsMenu.wnd:ComboBoxPlayer%d", i);
		comboBoxPlayerID[i] = TheNameKeyGenerator->nameToKey( tmpString );
		comboBoxPlayer[i] = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, comboBoxPlayerID[i] );
		GadgetComboBoxReset(comboBoxPlayer[i]);
		comboBoxPlayer[i]->winSetTooltipFunc(playerTooltip);

		tmpString.format("GameSpyGameOptionsMenu.wnd:StaticTextPlayer%d", i);
		staticTextPlayerID[i] = TheNameKeyGenerator->nameToKey( tmpString );
		staticTextPlayer[i] = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, staticTextPlayerID[i] );
		staticTextPlayer[i]->winSetTooltipFunc(playerTooltip);
		if (TheGameSpyInfo->amIHost())
			staticTextPlayer[i]->winHide(TRUE);

		if(i==0 && TheGameSpyInfo->amIHost())
		{
			UnicodeString uName;
			uName.translate(TheGameSpyInfo->getLocalName());
			GadgetComboBoxAddEntry(comboBoxPlayer[i],uName,GameSpyColor[GSCOLOR_PLAYER_OWNER]);
			GadgetComboBoxSetSelectedPos(comboBoxPlayer[0],0);
		}
		else
		{
			GadgetComboBoxAddEntry(comboBoxPlayer[i],TheGameText->fetch("GUI:Open"),GameSpyColor[GSCOLOR_PLAYER_NORMAL]);
			GadgetComboBoxAddEntry(comboBoxPlayer[i],TheGameText->fetch("GUI:Closed"),GameSpyColor[GSCOLOR_PLAYER_NORMAL]);
			GadgetComboBoxAddEntry(comboBoxPlayer[i],TheGameText->fetch("GUI:EasyAI"),GameSpyColor[GSCOLOR_PLAYER_NORMAL]);
			GadgetComboBoxAddEntry(comboBoxPlayer[i],TheGameText->fetch("GUI:MediumAI"),GameSpyColor[GSCOLOR_PLAYER_NORMAL]);
			GadgetComboBoxAddEntry(comboBoxPlayer[i],TheGameText->fetch("GUI:HardAI"),GameSpyColor[GSCOLOR_PLAYER_NORMAL]);
			GadgetComboBoxSetSelectedPos(comboBoxPlayer[i],0);
		}

		tmpString.format("GameSpyGameOptionsMenu.wnd:ComboBoxColor%d", i);
		comboBoxColorID[i] = TheNameKeyGenerator->nameToKey( tmpString );
		comboBoxColor[i] = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, comboBoxColorID[i] );
		DEBUG_ASSERTCRASH(comboBoxColor[i], ("Could not find the comboBoxColor[%d]",i ));
		PopulateColorComboBox(i, comboBoxColor, theGameInfo);
		GadgetComboBoxSetSelectedPos(comboBoxColor[i], 0);
		
		tmpString.format("GameSpyGameOptionsMenu.wnd:ComboBoxPlayerTemplate%d", i);
		comboBoxPlayerTemplateID[i] = TheNameKeyGenerator->nameToKey( tmpString );
		comboBoxPlayerTemplate[i] = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, comboBoxPlayerTemplateID[i] );
		DEBUG_ASSERTCRASH(comboBoxPlayerTemplate[i], ("Could not find the comboBoxPlayerTemplate[%d]",i ));
		PopulatePlayerTemplateComboBox(i, comboBoxPlayerTemplate, theGameInfo, theGameInfo->getAllowObservers() );

		// add tooltips to the player template combobox and listbox
		comboBoxPlayerTemplate[i]->winSetTooltipFunc(playerTemplateComboBoxTooltip);
		GadgetComboBoxGetListBox(comboBoxPlayerTemplate[i])->winSetTooltipFunc(playerTemplateListBoxTooltip);

		tmpString.format("GameSpyGameOptionsMenu.wnd:ComboBoxTeam%d", i);
		comboBoxTeamID[i] = TheNameKeyGenerator->nameToKey( tmpString );
		comboBoxTeam[i] = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, comboBoxTeamID[i] );
		DEBUG_ASSERTCRASH(comboBoxTeam[i], ("Could not find the comboBoxTeam[%d]",i ));
		PopulateTeamComboBox(i, comboBoxTeam, theGameInfo);

		tmpString.format("GameSpyGameOptionsMenu.wnd:ButtonAccept%d", i); 
		buttonAcceptID[i] = TheNameKeyGenerator->nameToKey( tmpString );
		buttonAccept[i] = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, buttonAcceptID[i] );
		DEBUG_ASSERTCRASH(buttonAccept[i], ("Could not find the buttonAccept[%d]",i ));
		buttonAccept[i]->winSetTooltipFunc(gameAcceptTooltip);

		tmpString.format("GameSpyGameOptionsMenu.wnd:GenericPing%d", i); 
		genericPingWindowID[i] = TheNameKeyGenerator->nameToKey( tmpString );
		genericPingWindow[i] = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, genericPingWindowID[i] );
		DEBUG_ASSERTCRASH(genericPingWindow[i], ("Could not find the genericPingWindow[%d]",i ));
		genericPingWindow[i]->winSetTooltipFunc(pingTooltip);

//		tmpString.format("GameSpyGameOptionsMenu.wnd:ButtonStartPosition%d", i);
//		buttonStartPositionID[i] = TheNameKeyGenerator->nameToKey( tmpString );
//		buttonStartPosition[i] = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, buttonStartPositionID[i] );
//		DEBUG_ASSERTCRASH(buttonStartPosition[i], ("Could not find the ButtonStartPosition[%d]",i ));

		tmpString.format("GameSpyGameOptionsMenu.wnd:ButtonMapStartPosition%d", i);
		buttonMapStartPositionID[i] = TheNameKeyGenerator->nameToKey( tmpString );
		buttonMapStartPosition[i] = TheWindowManager->winGetWindowFromId( parentWOLGameSetup, buttonMapStartPositionID[i] );
		DEBUG_ASSERTCRASH(buttonMapStartPosition[i], ("Could not find the ButtonMapStartPosition[%d]",i ));

//		if (buttonStartPosition[i])
//			buttonStartPosition[i]->winHide(TRUE);

		if(i !=0 && buttonAccept[i])
			buttonAccept[i]->winHide(TRUE);
	}

	if( buttonAccept[0] )
		buttonAccept[0]->winEnable(TRUE);

	if (buttonBack != NULL)
	{
		buttonBack->winEnable(TRUE);
	}
		//GadgetButtonSetEnabledColor(buttonAccept[0], GameSpyColor[GSCOLOR_ACCEPT_TRUE]);
}

void DeinitWOLGameGadgets( void )
{
	parentWOLGameSetup = NULL;
	buttonEmote = NULL;
	buttonSelectMap = NULL;
	buttonStart = NULL;
	buttonBack = NULL;
	listboxGameSetupChat = NULL;
	textEntryChat = NULL;
	textEntryMapDisplay = NULL;
	windowMap = NULL;
	checkBoxUseStats = NULL;
  checkBoxLimitSuperweapons = NULL;
  comboBoxStartingCash = NULL;
  
//	GameWindow *staticTextTitle = NULL;
	for (Int i = 0; i < MAX_SLOTS; i++)
	{
		comboBoxPlayer[i] = NULL;
		staticTextPlayer[i] = NULL;
		comboBoxColor[i] = NULL;
		comboBoxPlayerTemplate[i] = NULL;
		comboBoxTeam[i] = NULL;
		buttonAccept[i] = NULL;
//		buttonStartPosition[i] = NULL;
		buttonMapStartPosition[i] = NULL;
		genericPingWindow[i] = NULL;
	}
}

static Bool initDone = false;
UnsignedInt lastSlotlistTime = 0;
UnsignedInt enterTime = 0;
Bool initialAcceptEnable = FALSE;
//-------------------------------------------------------------------------------------------------
/** Initialize the Lan Game Options Menu */
//-------------------------------------------------------------------------------------------------
void WOLGameSetupMenuInit( WindowLayout *layout, void *userData )
{
	if (TheGameSpyGame && TheGameSpyGame->isGameInProgress())
	{
		TheGameSpyGame->setGameInProgress(FALSE);

		// check if we were disconnected
		Int disconReason;
		if (TheGameSpyInfo->isDisconnectedAfterGameStart(&disconReason))
		{
			AsciiString disconMunkee;
			disconMunkee.format("GUI:GSDisconReason%d", disconReason);
			UnicodeString title, body;
			title = TheGameText->fetch( "GUI:GSErrorTitle" );
			body = TheGameText->fetch( disconMunkee );
			GameSpyCloseAllOverlays();
			GSMessageBoxOk( title, body );
			TheGameSpyInfo->reset();
			DEBUG_LOG(("WOLGameSetupMenuInit() - game was in progress, and we were disconnected, so pop immediate back to main menu\n"));
			TheShell->popImmediate();
			return;
		}

		// If we init while the game is in progress, we are really returning to the menu
		// after the game.  So, we pop the menu and go back to the lobby.  Whee!
		DEBUG_LOG(("WOLGameSetupMenuInit() - game was in progress, so pop immediate back to lobby\n"));
		TheShell->popImmediate();
		if (TheGameSpyPeerMessageQueue && TheGameSpyPeerMessageQueue->isConnected())
		{
			DEBUG_LOG(("We're still connected, so pushing back on the lobby\n"));
			TheShell->push("Menus/WOLCustomLobby.wnd", TRUE);
		}
		return;
	}
	TheGameSpyInfo->setCurrentGroupRoom(0);

	if (TheNAT != NULL) {
		delete TheNAT;
		TheNAT = NULL;
	}

	nextScreen = NULL;
	buttonPushed = false;
	isShuttingDown = false;
	launchGameNext = FALSE;

	//initialize the gadgets
	EnableSlotListUpdates(FALSE);
	InitWOLGameGadgets();
	EnableSlotListUpdates(TRUE);
	TheGameSpyInfo->registerTextWindow(listboxGameSetupChat);

	//The dialog needs to react differently depending on whether it's the host or not.
	TheMapCache->updateCache();
	GameSpyStagingRoom *game = TheGameSpyInfo->getCurrentStagingRoom();
	GameSpyGameSlot *hostSlot = game->getGameSpySlot(0);
	hostSlot->setAccept();
	if (TheGameSpyInfo->amIHost())
	{
		OptionPreferences natPref;
		CustomMatchPreferences customPref;
		hostSlot->setColor( customPref.getPreferredColor() );
		hostSlot->setPlayerTemplate( customPref.getPreferredFaction() );
		hostSlot->setNATBehavior((FirewallHelperClass::FirewallBehaviorType)natPref.getFirewallBehavior());
		hostSlot->setPingString(TheGameSpyInfo->getPingString());
		game->setMap(customPref.getPreferredMap());

		// Recorded stats games can never limit superweapons, limit armies, or have inflated starting cash.
		// This should probably be enforced at the gamespy level as well, to prevent expoits.
		Int isUsingStats = TheGameSpyGame->getUseStats();
		game->setStartingCash( isUsingStats? TheMultiplayerSettings->getDefaultStartingMoney() : customPref.getStartingCash() );
		game->setSuperweaponRestriction( isUsingStats? 0 : customPref.getSuperweaponRestricted() ? 1 : 0 );
		if (isUsingStats)
			game->setOldFactionsOnly( 0 );

		//game->setOldFactionsOnly( customPref.getFactionsLimited() );
    if ( game->oldFactionsOnly() )
    {
      // Make sure host follows the old factions only restrictions!
      const PlayerTemplate *fac = ThePlayerTemplateStore->getNthPlayerTemplate(hostSlot->getPlayerTemplate());

      if ( fac != NULL && !fac->isOldFaction() )
      {
        hostSlot->setPlayerTemplate( PLAYERTEMPLATE_RANDOM );
      }
    }

		for (Int i=1; i<MAX_SLOTS; ++i)
		{
			GameSpyGameSlot *slot = game->getGameSpySlot(i);
			slot->setState( SLOT_OPEN );
		}

		AsciiString lowerMap = customPref.getPreferredMap();
		lowerMap.toLower();
		std::map<AsciiString, MapMetaData>::iterator it = TheMapCache->find(lowerMap);
		if (it != TheMapCache->end())
		{
			hostSlot->setMapAvailability(TRUE);
			game->setMapCRC( it->second.m_CRC );
			game->setMapSize( it->second.m_filesize );

			game->adjustSlotsForMap(); // BGC- adjust the slots for the new map.
		}


		WOLDisplaySlotList();
		WOLDisplayGameOptions();
	}
	else
	{
		OptionPreferences natPref;
		CustomMatchPreferences customPref;
		AsciiString options;
		PeerRequest req;
		UnicodeString uName = hostSlot->getName();
		AsciiString aName;
		aName.translate(uName);
		req.peerRequestType = PeerRequest::PEERREQUEST_UTMPLAYER;
		req.UTM.isStagingRoom = TRUE;
		req.id = "REQ/";
		req.nick = aName.str();
		options.format("PlayerTemplate=%d", customPref.getPreferredFaction());
		req.options = options.str();
		TheGameSpyPeerMessageQueue->addRequest(req);
		options.format("Color=%d", customPref.getPreferredColor());
		req.options = options.str();
		TheGameSpyPeerMessageQueue->addRequest(req);
		options.format("NAT=%d", natPref.getFirewallBehavior());
		req.options = options.str();
		TheGameSpyPeerMessageQueue->addRequest(req);
		options.format("Ping=%s", TheGameSpyInfo->getPingString().str());
		req.options = options.str();
		TheGameSpyPeerMessageQueue->addRequest(req);
   
		game->setMapCRC( game->getMapCRC() );		// force a recheck
		game->setMapSize( game->getMapSize() ); // of if we have the map

		for (Int i = 0; i < MAX_SLOTS; ++i)
		{
			//I'm a client, disable the controls I can't touch.
			comboBoxPlayer[i]->winEnable(FALSE);

			comboBoxColor[i]->winEnable(FALSE);
			comboBoxPlayerTemplate[i]->winEnable(FALSE);
			comboBoxTeam[i]->winEnable(FALSE);
//			buttonStartPosition[i]->winEnable(FALSE);
			buttonMapStartPosition[i]->winEnable(FALSE);

		}
		buttonStart->winSetText(TheGameText->fetch("GUI:Accept"));
		buttonStart->winEnable( FALSE );
		buttonSelectMap->winEnable( FALSE );
    checkBoxLimitSuperweapons->winEnable( FALSE ); // Can look but only host can touch
    comboBoxStartingCash->winEnable( FALSE );      // Ditto
		initialAcceptEnable = FALSE;
	}

	// Show the Menu
	layout->hide( FALSE );
	
	// Make sure the text fields are clear
	GadgetListBoxReset( listboxGameSetupChat );
	GadgetTextEntrySetText(textEntryChat, UnicodeString::TheEmptyString);	

	initDone = true;
	TheGameSpyInfo->setGameOptions();
	//TheShell->registerWithAnimateManager(parentWOLGameSetup, WIN_ANIMATION_SLIDE_TOP, TRUE);
	WOLPositionStartSpots();

	lastSlotlistTime = 0;
	enterTime = timeGetTime();

	// Set Keyboard to chat entry
	TheWindowManager->winSetFocus( textEntryChat );
	raiseMessageBoxes = true;
	TheTransitionHandler->setGroup("GameSpyGameOptionsMenuFade");
}// void WOLGameSetupMenuInit( WindowLayout *layout, void *userData )

//-------------------------------------------------------------------------------------------------
/** This is called when a shutdown is complete for this menu */
//-------------------------------------------------------------------------------------------------
// Retail spells this file-static helper `shutdownComplete`; give the source
// body a TU-specific name so the flat reverse ledger cannot confuse it with
// the other menu copies.
static void shutdownCompleteWOLGameSetupMenu( WindowLayout *layout )
{

	isShuttingDown = false;

	// hide the layout
	((BfmeVirtualHideLayout *)layout)->hide( TRUE );

	// our shutdown is complete
	TheShell->shutdownComplete( layout, (nextScreen != NULL) );

	if (nextScreen != NULL)
	{
		if (!TheGameSpyPeerMessageQueue || !TheGameSpyPeerMessageQueue->isConnected())
		{
			DEBUG_LOG(("GameSetup shutdownComplete() - skipping push because we're disconnected\n"));
		}
		else
		{
			TheShell->push( AsciiString(nextScreen) );
		}
	}

	/*
	if (launchGameNext)
	{
		TheGameSpyGame->launchGame();
		TheGameSpyInfo->leaveStagingRoom();
	}
	*/

	nextScreen = NULL;

}  // end if

//-------------------------------------------------------------------------------------------------
/** GameSpy Game Options menu shutdown method */
//-------------------------------------------------------------------------------------------------
void WOLGameSetupMenuShutdown( WindowLayout *layout, void *userData )
{
	((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->unregisterTextWindow(listboxGameSetupChat);

	if( WOLMapSelectLayout )
	{
		((BfmeWOLMapSelectLayout *)WOLMapSelectLayout)->destroyWindows();
		delete (BfmeWOLMapSelectLayout *)WOLMapSelectLayout;
		WOLMapSelectLayout = NULL;
	}
	parentWOLGameSetup = NULL;
	EnableSlotListUpdates(FALSE);
	bfmeClearStateVJ();
	if (TheEstablishConnectionsMenu != NULL)
	{
		TheEstablishConnectionsMenu->endMenu();
	}
	initDone = false;

	isShuttingDown = true;

	// if we are shutting down for an immediate pop, skip the animations
	Bool popImmediate = *(Bool *)userData;
	if( popImmediate )
	{

		shutdownCompleteWOLGameSetupMenu( layout );
		return;

	}  //end if

	TheShell->reverseAnimatewindow();

	RaiseGSMessageBox();
	TheTransitionHandler->reverse("GameSpyGameOptionsMenuFade");
}  // void WOLGameSetupMenuShutdown( WindowLayout *layout, void *userData )

class BFMEPlayerInfoString : private StringBase<char>
{
public:
	BFMEPlayerInfoString &operator=( const char *text )
	{
		StringBase<char>::set( text, text ? strlen( text ) : 0 );
		return *this;
	}
};

class BFMEPlayerInfoLayout
{
public:
	BFMEPlayerInfoString m_name;
	BFMEPlayerInfoString m_baseName;
	BFMEPlayerInfoString m_locale;
	Int m_wins;
	Int m_losses;
	Int m_profileID;
	Int m_flags;
	Int m_rankPoints;
	Int m_bfmeBookkeeping[ 3 ];
	Int m_side;
	Int m_preorder;
};

typedef char BFMEPlayerInfoStringSize[
	sizeof( BFMEPlayerInfoString ) == 4 ? 1 : -1 ];
typedef char BFMEPlayerInfoLayoutSize[
	sizeof( BFMEPlayerInfoLayout ) == 0x34 ? 1 : -1 ];

static void fillPlayerInfo( const PeerResponse *resp, PlayerInfo *info )
{
	BFMEPlayerInfoLayout *bfmeInfo =
		reinterpret_cast<BFMEPlayerInfoLayout *>( info );
	char baseName[ 256 ] = { 0 };
	strncpy( baseName, resp->nick.c_str(), 255 );
	char *suffix = strrchr( baseName, '-' );
	if( suffix )
		*suffix = 0;

	const char *nick = resp->nick.c_str();
	bfmeInfo->m_name = nick;
	bfmeInfo->m_baseName = baseName;
	bfmeInfo->m_profileID = resp->player.profileID;
	bfmeInfo->m_flags = resp->player.flags;
	bfmeInfo->m_wins = resp->player.wins;
	bfmeInfo->m_losses = resp->player.losses;
	const char *locale = resp->locale.c_str();
	bfmeInfo->m_locale = locale;
	bfmeInfo->m_rankPoints = resp->player.rankPoints;
	bfmeInfo->m_side = resp->player.side;
	bfmeInfo->m_preorder = resp->player.preorder;
}


//-------------------------------------------------------------------------------------------------
/** WOL game setup update. FunctionLexicon: 00EA9B98 -> 000349A0 -> 004F6B60. */
//-------------------------------------------------------------------------------------------------
class BfmeWolUpdateInfo {
public:
    virtual ~BfmeWolUpdateInfo() = 0;
    virtual void reset() = 0;
    virtual void slot_008() = 0;
    virtual void slot_00C() = 0;
    virtual void slot_010() = 0;
    virtual void slot_014() = 0;
    virtual void slot_018() = 0;
    virtual void slot_01C() = 0;
    virtual void slot_020() = 0;
    virtual void slot_024() = 0;
    virtual void slot_028() = 0;
    virtual void slot_02C() = 0;
    virtual void slot_030() = 0;
    virtual void slot_034() = 0;
    virtual void slot_038() = 0;
    virtual void slot_03C() = 0;
    virtual void updatePlayerInfo(PlayerInfo pi, AsciiString oldNick = AsciiString::TheEmptyString) = 0;
    virtual void playerLeftGroupRoom(AsciiString nick) = 0;
    virtual PlayerInfoMap *getPlayerInfoMap() = 0;
    virtual void slot_04C() = 0;
    virtual void slot_050() = 0;
    virtual void slot_054() = 0;
    virtual void slot_058() = 0;
    virtual void slot_05C() = 0;
    virtual void slot_060() = 0;
    virtual void slot_064() = 0;
    virtual void slot_068() = 0;
    virtual void slot_06C() = 0;
    virtual void slot_070() = 0;
    virtual void slot_074() = 0;
    virtual void slot_078() = 0;
    virtual void slot_07C() = 0;
    virtual void slot_080() = 0;
    virtual void slot_084() = 0;
    virtual void slot_088() = 0;
    virtual void slot_08C() = 0;
    virtual void slot_090() = 0;
    virtual void slot_094() = 0;
    virtual void slot_098() = 0;
    virtual void slot_09C() = 0;
    virtual void slot_0A0() = 0;
    virtual void slot_0A4() = 0;
    virtual void slot_0A8() = 0;
    virtual void slot_0AC() = 0;
    virtual void leaveStagingRoom() = 0;
    virtual void slot_0B4() = 0;
    virtual void slot_0B8() = 0;
    virtual void slot_0BC() = 0;
    virtual Bool amIHost() = 0;
    virtual GameSpyStagingRoom *getCurrentStagingRoom() = 0;
    virtual void slot_0C8() = 0;
    virtual void setGameOptions() = 0;
    virtual void slot_0D0() = 0;
    virtual void slot_0D4() = 0;
    virtual void slot_0D8() = 0;
    virtual void slot_0DC() = 0;
    virtual void slot_0E0() = 0;
    virtual void slot_0E4() = 0;
    virtual void slot_0E8() = 0;
    virtual Int addText(UnicodeString message, Color c, GameWindow *win) = 0;
    virtual void addChat(AsciiString nick, Int profileID, UnicodeString msg, Bool isPublic, Bool isAction, GameWindow *win) = 0;
    virtual void slot_0F4() = 0;
    virtual void slot_0F8() = 0;
    virtual void slot_0FC() = 0;
    virtual void slot_100() = 0;
    virtual void slot_104() = 0;
    virtual void slot_108() = 0;
    virtual void slot_10C() = 0;
    virtual void slot_110() = 0;
    virtual void slot_114() = 0;
    virtual void slot_118() = 0;
    virtual void slot_11C() = 0;
    virtual void slot_120() = 0;
    virtual void slot_124() = 0;
    virtual void slot_128() = 0;
    virtual void slot_12C() = 0;
    virtual void slot_130() = 0;
    virtual void slot_134() = 0;
    virtual void slot_138() = 0;
    virtual void slot_13C() = 0;
    virtual void slot_140() = 0;
    virtual void slot_144() = 0;
    virtual void slot_148() = 0;
    virtual void slot_14C() = 0;
    virtual void slot_150() = 0;
    virtual void slot_154() = 0;
    virtual Bool isDisconnectedAfterGameStart(Int *reason) const = 0;
    virtual void markAsDisconnectedAfterGameStart(Int reason) = 0;
    virtual void slot_160() = 0;
    virtual void slot_164() = 0;
    virtual void slot_168() = 0;
    virtual Int getMaxMessagesPerUpdate() = 0;
};

class BfmeWolInGameUI { public:
    virtual void slot_000();
    virtual void slot_004();
    virtual void slot_008();
    virtual void slot_00C();
    virtual void slot_010();
    virtual void slot_014();
    virtual void slot_018();
    virtual void slot_01C();
    virtual void slot_020();
    virtual void slot_024();
    virtual void slot_028();
    virtual void slot_02C();
    virtual void message(AsciiString label, ...);
};
struct BfmeWolMapMetaData {
    UnicodeString m_displayName;
    UnicodeString m_description;
    unsigned char m_extent[24];
    int m_numPlayers;
    bool m_isMultiplayer, m_isScenarioMP, m_isOfficial;
};
struct BfmeWolWideText {
    static __forceinline const wchar_t *str(const UnicodeString &value) {
        const char *p = *(const char *const *)&value;
        return p ? (const wchar_t *)(p + 8) : L"";
    }
};
void WOLDisplaySlotList();
Bool WouldMapTransfer(GameInfo *game);
void SendStatsToOtherPlayers(const GameInfo *game);

void WOLGameSetupMenuUpdate( WindowLayout * layout, void *userData)
{
	// We'll only be successful if we've requested to 
	if(isShuttingDown && TheShell->isAnimFinished() && TheTransitionHandler->isFinished())
	{
		shutdownCompleteWOLGameSetupMenu(layout);
		return;
	}

	if (raiseMessageBoxes)
	{
		RaiseGSMessageBox();
		raiseMessageBoxes = false;
	}

	if (TheShell->isAnimFinished() && !buttonPushed && TheGameSpyPeerMessageQueue)
	{
		HandleBuddyResponses();
		HandlePersistentStorageResponses();

		if (TheGameSpyGame && TheGameSpyGame->isGameInProgress())
		{
			if (((BfmeWolUpdateInfo *)TheGameSpyInfo)->isDisconnectedAfterGameStart(NULL))
			{
				return; // already been disconnected, so don't worry.
			}

			Int allowedMessages = ((BfmeWolUpdateInfo *)TheGameSpyInfo)->getMaxMessagesPerUpdate();
			Bool sawImportantMessage = FALSE;
			PeerResponse resp;
			while (allowedMessages-- && !sawImportantMessage && TheGameSpyPeerMessageQueue->getResponse( resp ))
			{
				switch (resp.peerResponseType)
				{
				case PeerResponse::PEERRESPONSE_DISCONNECT:
					{
						sawImportantMessage = TRUE;
						AsciiString disconMunkee;
						disconMunkee.format("GUI:GSDisconReason%d", resp.discon.reason);

						// check for scorescreen
						NameKeyType listboxChatWindowScoreScreenID = NAMEKEY("ScoreScreen.wnd:ListboxChatWindowScoreScreen");
						GameWindow *listboxChatWindowScoreScreen = TheWindowManager->winGetWindowFromId( NULL, listboxChatWindowScoreScreenID );
						if (listboxChatWindowScoreScreen)
						{
							GadgetListBoxAddEntryText(listboxChatWindowScoreScreen, TheGameText->fetch(disconMunkee),
								GameSpyColor[GSCOLOR_DEFAULT], -1);
						}
						else
						{
							// still ingame
							((BfmeWolInGameUI *)TheInGameUI)->message(disconMunkee);
						}
						((BfmeWolUpdateInfo *)TheGameSpyInfo)->markAsDisconnectedAfterGameStart(resp.discon.reason);
					}
				}
			}

			return; // if we're in game, all we care about is if we've been disconnected from the chat server
		}

		Bool isHosting = ((BfmeWolUpdateInfo *)TheGameSpyInfo)->amIHost(); // only while in game setup screen
		isHosting = isHosting || (TheGameSpyGame && TheGameSpyGame->isInGame() && TheGameSpyGame->amIHost()); // while in game
		if (!isHosting && !lastSlotlistTime && timeGetTime() > enterTime + 10000)
		{
			// don't do this if we're disconnected
			if (TheGameSpyPeerMessageQueue->isConnected())
			{
				// haven't seen ourselves
				buttonPushed = true;
				DEBUG_LOG(("Haven't seen ourselves in slotlist\n"));
				if (TheGameSpyGame)
					TheGameSpyGame->reset();
				((BfmeWolUpdateInfo *)TheGameSpyInfo)->leaveStagingRoom();
				//((BfmeWolUpdateInfo *)TheGameSpyInfo)->joinBestGroupRoom();
				GSMessageBoxOk(TheGameText->fetch("GUI:HostLeftTitle"), TheGameText->fetch("GUI:HostLeft"));
				nextScreen = "Menus/WOLCustomLobby.wnd";
				TheShell->pop();
			}
			return;
		}

		if (TheNAT != NULL) {
			NATStateType NATState = TheNAT->update();
			if (NATState == NATSTATE_DONE)
			{
				//launchGameNext = TRUE;
				//TheShell->pop();
				TheGameSpyGame->launchGame();
				if (TheGameSpyInfo) // this can be blown away by a disconnect on the map transfer screen
					((BfmeWolUpdateInfo *)TheGameSpyInfo)->leaveStagingRoom();
				return;
			}
			else if (NATState == NATSTATE_FAILED)
			{
				// Just back out.  This cleans up some slot list problems
				buttonPushed = true;

				// delete TheNAT, its no good for us anymore.
				delete TheNAT;
				TheNAT = NULL;

				((BfmeWolUpdateInfo *)TheGameSpyInfo)->getCurrentStagingRoom()->reset();
				((BfmeWolUpdateInfo *)TheGameSpyInfo)->leaveStagingRoom();
				//((BfmeWolUpdateInfo *)TheGameSpyInfo)->joinBestGroupRoom();
				GSMessageBoxOk(TheGameText->fetch("GUI:Error"), TheGameText->fetch("GUI:NATNegotiationFailed"));
				nextScreen = "Menus/WOLCustomLobby.wnd";
				TheShell->pop();
				return;
			}
		}

		PeerResponse resp;

		Int allowedMessages = ((BfmeWolUpdateInfo *)TheGameSpyInfo)->getMaxMessagesPerUpdate();
		Bool sawImportantMessage = FALSE;
		while (allowedMessages-- && !sawImportantMessage)
		{

		if (!TheLobbyQueuedUTMs.empty())
		{
			DEBUG_LOG(("Got response from queued lobby UTM list\n"));
			resp = TheLobbyQueuedUTMs.front();
			TheLobbyQueuedUTMs.pop_front();
		}
		else if (TheGameSpyPeerMessageQueue->getResponse( resp ))
		{
			DEBUG_LOG(("Got response from message queue\n"));
		}
			else
		{
				break;
			}
			switch (resp.peerResponseType)
			{
			case PeerResponse::PEERRESPONSE_FAILEDTOHOST:
				{
					// oops - we've not heard from the qr server.  bail.
					((BfmeWolUpdateInfo *)TheGameSpyInfo)->addText(TheGameText->fetch("GUI:GSFailedToHost"), GameSpyColor[GSCOLOR_DEFAULT], NULL);
				}
				break;
			case PeerResponse::PEERRESPONSE_GAMESTART:
				{
					sawImportantMessage = TRUE;
					GameSpyStagingRoom *myGame = ((BfmeWolUpdateInfo *)TheGameSpyInfo)->getCurrentStagingRoom();
					if (!myGame || !myGame->isInGame())
						break;

					if (!TheGameSpyGame)
						break;

					SendStatsToOtherPlayers(TheGameSpyGame);

					// we've started, there's no going back
					// i.e. disable the back button.
					buttonBack->winEnable(FALSE);
					GameWindow *buttonBuddy = TheWindowManager->winGetWindowFromId(NULL, NAMEKEY("GameSpyGameOptionsMenu.wnd:ButtonCommunicator"));
					if (buttonBuddy)
						buttonBuddy->winEnable(FALSE);
					GameSpyCloseOverlay(GSOVERLAY_BUDDY);

					*TheGameSpyGame = *myGame;
					TheGameSpyGame->startGame(0);
				}
				break;
			case PeerResponse::PEERRESPONSE_PLAYERCHANGEDFLAGS:
				{
					PlayerInfo p;
					fillPlayerInfo(&resp, &p);
					((BfmeWolUpdateInfo *)TheGameSpyInfo)->updatePlayerInfo(p);
					WOLDisplaySlotList();
				}
				break;
			case PeerResponse::PEERRESPONSE_PLAYERINFO:
				{
					PlayerInfo p;
					fillPlayerInfo(&resp, &p);
					((BfmeWolUpdateInfo *)TheGameSpyInfo)->updatePlayerInfo(p);
					WOLDisplaySlotList();
					// send out new slotlist if I'm host
					((BfmeWolUpdateInfo *)TheGameSpyInfo)->setGameOptions();
				}
				break;
			case PeerResponse::PEERRESPONSE_PLAYERJOIN:
				{
					if (resp.player.roomType != StagingRoom)
					{
						break;
					}
					sawImportantMessage = TRUE;
					PlayerInfo p;
					fillPlayerInfo(&resp, &p);
					((BfmeWolUpdateInfo *)TheGameSpyInfo)->updatePlayerInfo(p);

					if (p.m_profileID)
					{
						if (TheGameSpyPSMessageQueue->findPlayerStatsByID(p.m_profileID).id == 0)
						{
							PSRequest req;
							req.requestType = PSRequest::PSREQUEST_READPLAYERSTATS;
							req.player.id = p.m_profileID;
							TheGameSpyPSMessageQueue->addRequest(req);
						}
					}

					// check if we have room for the dude
					GameInfo *game = ((BfmeWolUpdateInfo *)TheGameSpyInfo)->getCurrentStagingRoom();
					if (((BfmeWolUpdateInfo *)TheGameSpyInfo)->amIHost() && game)
					{
						if (TheNAT)
						{
							// ditch him
							PeerRequest req;
							req.peerRequestType = PeerRequest::PEERREQUEST_UTMPLAYER;
							req.UTM.isStagingRoom = TRUE;
							req.id = "KICK/";
							req.nick = p.m_name.str();
							req.options = "GameStarted";
							TheGameSpyPeerMessageQueue->addRequest(req);
						}
						else
						{
							// look for room for him
							// See if there's room
							// First get the number of players currently in the room.
							Int numPlayers = 0;
							for (Int player = 0; player < MAX_SLOTS; ++player)
							{
								if (game->getSlot(player)->isOccupied() &&
									game->getSlot(player)->getPlayerTemplate() != PLAYERTEMPLATE_OBSERVER)
								{
									++numPlayers;
								}
							}

							// now get the number of starting spots on the map.
							Int numStartingSpots = MAX_SLOTS;
							const BfmeWolMapMetaData *md = (const BfmeWolMapMetaData *)TheMapCache->findMap(game->getMap());
							if (md != NULL)
							{
								numStartingSpots = md->m_numPlayers;
							}

							Int openSlotIndex = -1;
							for (Int i=0; i<MAX_SLOTS; ++i)
							{
								const GameSlot *slot = game->getConstSlot(i);
								if (slot && slot->isOpen())
								{
									openSlotIndex = i;
									break;
								}
							}

							if (openSlotIndex >= 0)
							{
								// add him
								GameSlot newSlot;
								UnicodeString uName;
								uName.translate(p.m_baseName);
								{
                                    GameSlotConnectInfo connect;
                                    connect.m_nat = (FirewallHelperClass::FirewallBehaviorType)0;
                                    connect.m_port = 0;
                                    newSlot.setState(SLOT_PLAYER, uName, &connect);
                                }
								BfmeWolAddress address;
                                address.ip = htonl(resp.player.IP);
                                address.port = 8088;
                                newSlot.setAddress(address);
								game->setSlot( openSlotIndex, newSlot );
								game->resetAccepted(); // BGC - need to unaccept everyone if someone joins the game.
							}
							else
							{
								// ditch him
								PeerRequest req;
								req.peerRequestType = PeerRequest::PEERREQUEST_UTMPLAYER;
								req.UTM.isStagingRoom = TRUE;
								req.id = "KICK/";
								req.nick = p.m_name.str();
								req.options = "GameFull";
								TheGameSpyPeerMessageQueue->addRequest(req);
							}

							// send out new slotlist if I'm host
							((BfmeWolUpdateInfo *)TheGameSpyInfo)->setGameOptions();
						}
					}
					WOLDisplaySlotList();
				}
				break;

			case PeerResponse::PEERRESPONSE_PLAYERLEFT:
				{
					sawImportantMessage = TRUE;
					PlayerInfo p;
					fillPlayerInfo(&resp, &p);
					((BfmeWolUpdateInfo *)TheGameSpyInfo)->playerLeftGroupRoom(resp.nick.c_str());

					if (TheGameSpyGame && TheGameSpyGame->isGameInProgress())
					{
						break;
					}

					if (TheNAT == NULL) // don't update slot list if we're trying to start a game
					{

						GameInfo *game = ((BfmeWolUpdateInfo *)TheGameSpyInfo)->getCurrentStagingRoom();
						if (game && ((BfmeWolUpdateInfo *)TheGameSpyInfo)->amIHost())
						{
							Int idx = game->getSlotNum(p.m_baseName.str());
							if (idx >= 0)
							{
								GameSlotConnectInfo connect;
                                connect.m_nat = (FirewallHelperClass::FirewallBehaviorType)0;
                                connect.m_port = 0;
                                game->getSlot(idx)->setState(SLOT_OPEN, UnicodeString::TheEmptyString, &connect);
								game->resetAccepted(); // BGC - need to unaccept everyone if someone leaves the game.
							}
						}

						// send out new slotlist if I'm host
						((BfmeWolUpdateInfo *)TheGameSpyInfo)->setGameOptions();
						WOLDisplaySlotList();
						
						if (game && !((BfmeWolUpdateInfo *)TheGameSpyInfo)->amIHost())
						{
							Int idx = game->getSlotNum(p.m_baseName.str());
							if (idx == 0)
							{
								// host left
								buttonPushed = true;
								((BfmeWolUpdateInfo *)TheGameSpyInfo)->getCurrentStagingRoom()->reset();
								((BfmeWolUpdateInfo *)TheGameSpyInfo)->leaveStagingRoom();
								//((BfmeWolUpdateInfo *)TheGameSpyInfo)->joinBestGroupRoom();
								GSMessageBoxOk(TheGameText->fetch("GUI:HostLeftTitle"), TheGameText->fetch("GUI:HostLeft"));
								nextScreen = "Menus/WOLCustomLobby.wnd";
								TheShell->pop();
							}
						}

					}
				}
				break;

			case PeerResponse::PEERRESPONSE_MESSAGE:
				{
					((BfmeWolUpdateInfo *)TheGameSpyInfo)->addChat(resp.nick.c_str(), resp.message.profileID,
						UnicodeString(resp.text.c_str()), !resp.message.isPrivate, resp.message.isAction, listboxGameSetupChat);
				}
				break;

			case PeerResponse::PEERRESPONSE_DISCONNECT:
				{
					sawImportantMessage = TRUE;
					UnicodeString title, body;
					AsciiString disconMunkee;
					disconMunkee.format("GUI:GSDisconReason%d", resp.discon.reason);
					title = TheGameText->fetch( "GUI:GSErrorTitle" );
					body = TheGameText->fetch( disconMunkee );
					GameSpyCloseAllOverlays();
					GSMessageBoxOk( title, body );
					((BfmeWolUpdateInfo *)TheGameSpyInfo)->reset();
					TheShell->pop();
					TearDownGameSpy();
				}
				break;

			case PeerResponse::PEERRESPONSE_ROOMUTM:
				{
					sawImportantMessage = TRUE;
#if defined(_DEBUG) || defined(_INTERNAL)
					if (g_debugSlots)
					{
						DEBUG_LOG(("About to process a room UTM.  Command is '%s', command options is '%s'\n",
							resp.command.c_str(), resp.commandOptions.c_str()));
					}
#endif
					if (!strcmp(resp.command.c_str(), "SL"))
					{
						// slotlist
						GameSpyStagingRoom *game = ((BfmeWolUpdateInfo *)TheGameSpyInfo)->getCurrentStagingRoom();
                        PlayerInfoMap::iterator playerIt = ((BfmeWolUpdateInfo *)TheGameSpyInfo)->getPlayerInfoMap()->find(resp.nick.c_str());
                        AsciiString playerName;
                        if (playerIt != ((BfmeWolUpdateInfo *)TheGameSpyInfo)->getPlayerInfoMap()->end())
                            playerName = playerIt->second.m_baseName;
                        else
                            playerName = resp.nick.c_str();
						Bool isValidSlotList = game && game->getSlot(0) && game->getSlot(0)->isPlayer( playerName ) && !((BfmeWolUpdateInfo *)TheGameSpyInfo)->amIHost();
						if (!isValidSlotList)
						{
							SLOTLIST_DEBUG_LOG(("Not a valid slotlist\n"));
							if (!game)
							{
								SLOTLIST_DEBUG_LOG(("No game!\n"));
							}
							else
							{
								if (!game->getSlot(0))
								{
									SLOTLIST_DEBUG_LOG(("No slot 0!\n"));
								}
								else
								{
									if (((BfmeWolUpdateInfo *)TheGameSpyInfo)->amIHost())
									{
										SLOTLIST_DEBUG_LOG(("I'm the host!\n"));
									}
									else
									{
										SLOTLIST_DEBUG_LOG(("Not from the host!  isHuman:%d, name:'%ls', sender:'%s'\n",
											game->getSlot(0)->isHuman(), game->getSlot(0)->getName().str(),
											resp.nick.c_str()));
									}
								}
							}
						}
						else // isValidSlotList
						{
							Int oldLocalSlotNum = (game->isInGame()) ? game->getLocalSlotNum() : -1;
							Bool wasInGame = oldLocalSlotNum >= 0;
							AsciiString oldMap = game->getMap();
							UnsignedInt oldMapCRC, newMapCRC;
							oldMapCRC = game->getMapCRC();

							AsciiString options = resp.commandOptions.c_str();
							options.trim();
							UnsignedShort ports[MAX_SLOTS];
							UnsignedInt ips[MAX_SLOTS];
							Int i;
							for (i=0; i<MAX_SLOTS; ++i)
							{
								if (game && game->getConstSlot(i))
								{
									ips[i] = game->getConstSlot(i)->getIP();
									ports[i] = game->getConstSlot(i)->getPort();
								}
								else
								{
									ips[i] = 0;
									ports[i] = 0;
								}
							}
							Bool optionsOK = ParseAsciiStringToGameInfo(game, options.str(), TRUE);
							Int newLocalSlotNum = (game->isInGame()) ? game->getLocalSlotNum() : -1;
							Bool isInGame = newLocalSlotNum >= 0;
							if (!optionsOK)
							{
								SLOTLIST_DEBUG_LOG(("Options are bad!  bailing!\n"));
								break;
							}
							else
							{
								SLOTLIST_DEBUG_LOG(("Options are good, local slot is %d\n", newLocalSlotNum));
								if (!isInGame)
								{
									SLOTLIST_DEBUG_LOG(("Not in game; players are:\n"));
									for (Int i=0; i<MAX_SLOTS; ++i)
									{
										const GameSpyGameSlot *slot = game->getGameSpySlot(i);
										if (slot && slot->isHuman())
										{
											UnicodeString munkee;
											munkee.format(UnicodeString(L"\t%d: %ls"), i, BfmeWolWideText::str(slot->getName()));
											SLOTLIST_DEBUG_LOG(("%ls\n", munkee.str()));
										}
									}
								}
							}
							WOLDisplaySlotList();

							// if I changed map availability, send it across
							newMapCRC = game->getMapCRC();
							if (isInGame)
							{
								lastSlotlistTime = timeGetTime();
								if ( (oldMapCRC ^ newMapCRC) || (!wasInGame && isInGame) )
								{
									// it changed.  send it
									UnicodeString hostName = ((BfmeWolUpdateInfo *)TheGameSpyInfo)->getCurrentStagingRoom()->getSlot(0)->getName();
									AsciiString asciiName;
									asciiName.translate(hostName);
									PeerRequest req;
									req.peerRequestType = PeerRequest::PEERREQUEST_UTMPLAYER;
									req.UTM.isStagingRoom = TRUE;
									req.id = "MAP";
									req.nick = asciiName.str();
									req.options = (game->getSlot(newLocalSlotNum)->hasMap())?"1":"0";
									TheGameSpyPeerMessageQueue->addRequest(req);
									if (!game->getSlot(newLocalSlotNum)->hasMap())
									{
										UnicodeString text;
										UnicodeString mapDisplayName;
										const BfmeWolMapMetaData *mapData = (const BfmeWolMapMetaData *)TheMapCache->findMap( game->getMap() );
										Bool willTransfer = TRUE;
										if (mapData)
										{
											mapDisplayName.format(UnicodeString(L"%ls"), BfmeWolWideText::str(mapData->m_displayName));
											willTransfer = !mapData->m_isOfficial;
										}
										else
										{
											mapDisplayName.format(UnicodeString(L"%hs"), TheGameState->getMapLeafName(game->getMap()).str());
											willTransfer = WouldMapTransfer(game);
										}
										if (willTransfer)
											text.format(TheGameText->fetch("GUI:LocalPlayerNoMapWillTransfer"), BfmeWolWideText::str(mapDisplayName));
										else
											text.format(TheGameText->fetch("GUI:LocalPlayerNoMap"), BfmeWolWideText::str(mapDisplayName));
										((BfmeWolUpdateInfo *)TheGameSpyInfo)->addText(text, GameSpyColor[GSCOLOR_DEFAULT], listboxGameSetupChat);
									}
								}
								if (!initialAcceptEnable)
								{
									buttonStart->winEnable( TRUE );
									initialAcceptEnable = TRUE;
								}
							}
							else
							{
								if (lastSlotlistTime)
								{
									// can't see ourselves
									buttonPushed = true;
									DEBUG_LOG(("Can't see ourselves in slotlist %s\n", options.str()));
									((BfmeWolUpdateInfo *)TheGameSpyInfo)->getCurrentStagingRoom()->reset();
									((BfmeWolUpdateInfo *)TheGameSpyInfo)->leaveStagingRoom();
									//((BfmeWolUpdateInfo *)TheGameSpyInfo)->joinBestGroupRoom();
									GSMessageBoxOk(TheGameText->fetch("GUI:GSErrorTitle"), TheGameText->fetch("GUI:GSKicked"));
									nextScreen = "Menus/WOLCustomLobby.wnd";
									TheShell->pop();
								}
							}
						}
					}
					else if (!strcmp(resp.command.c_str(), "HWS"))
					{
						// host wants to start
						GameInfo *game = ((BfmeWolUpdateInfo *)TheGameSpyInfo)->getCurrentStagingRoom();
						if (game && game->isInGame() && game->getSlot(0) && game->getSlot(0)->isPlayer( resp.nick.c_str() ))
						{
							Int slotNum = game->getLocalSlotNum();
							GameSlot *slot = game->getSlot(slotNum);
							if (slot && (slot->isAccepted() == false))
							{
								((BfmeWolUpdateInfo *)TheGameSpyInfo)->addText(TheGameText->fetch("GUI:HostWantsToStart"), GameSpyColor[GSCOLOR_DEFAULT], listboxGameSetupChat);
							}
						}
					}
					else if (!stricmp(resp.command.c_str(), "NAT"))
					{
						if (TheNAT != NULL) {
							TheNAT->processGlobalMessage(-1, resp.commandOptions.c_str());
						}
					}
					else if (!stricmp(resp.command.c_str(), "Pings"))
					{
						if (!((BfmeWolUpdateInfo *)TheGameSpyInfo)->amIHost())
						{
							AsciiString pings = resp.commandOptions.c_str();
							AsciiString token;
							for (Int i=0; i<MAX_SLOTS; ++i)
							{
								GameSpyGameSlot *slot = ((BfmeWolUpdateInfo *)TheGameSpyInfo)->getCurrentStagingRoom()->getGameSpySlot(i);
								if (pings.nextToken(&token, ","))
								{
									token.trim();
									slot->setPingString(token);
								}
								else
								{
									slot->setPingString("");
								}
							}
						}
					}
				}
				break;

			case PeerResponse::PEERRESPONSE_PLAYERUTM:
				{
					sawImportantMessage = TRUE;
					if (!strcmp(resp.command.c_str(), "STATS"))
					{
						PSPlayerStats stats = TheGameSpyPSMessageQueue->parsePlayerKVPairs(resp.commandOptions.c_str());
						if (stats.id && (TheGameSpyPSMessageQueue->findPlayerStatsByID(stats.id).id == 0))
							TheGameSpyPSMessageQueue->trackPlayerStats(stats);
						break;
					}
					GameSpyStagingRoom *game = ((BfmeWolUpdateInfo *)TheGameSpyInfo)->getCurrentStagingRoom();
					if (game)
					{

                        PlayerInfoMap::iterator playerIt = ((BfmeWolUpdateInfo *)TheGameSpyInfo)->getPlayerInfoMap()->find(resp.nick.c_str());
                        AsciiString playerName;
                        if (playerIt != ((BfmeWolUpdateInfo *)TheGameSpyInfo)->getPlayerInfoMap()->end())
                            playerName = playerIt->second.m_baseName;
                        else
                            playerName = resp.nick.c_str();
						Int slotNum = game->getSlotNum(playerName);
						if ((slotNum >= 0) && (slotNum < MAX_SLOTS) && (!stricmp(resp.command.c_str(), "NAT"))) {
							// this is a command for NAT negotiations, pass if off to TheNAT
							if (TheNAT != NULL) {
								TheNAT->processGlobalMessage(slotNum, resp.commandOptions.c_str());
							}
						}
						if (slotNum == 0 && !((BfmeWolUpdateInfo *)TheGameSpyInfo)->amIHost())
						{
							if (!strcmp(resp.command.c_str(), "KICK"))
							{
								// oops - we've been kicked.  bail.
								buttonPushed = true;
								((BfmeWolUpdateInfo *)TheGameSpyInfo)->getCurrentStagingRoom()->reset();
								((BfmeWolUpdateInfo *)TheGameSpyInfo)->leaveStagingRoom();
								//((BfmeWolUpdateInfo *)TheGameSpyInfo)->joinBestGroupRoom();
								UnicodeString message = TheGameText->fetch("GUI:GSKicked");
								AsciiString commandMessage = resp.commandOptions.c_str();
								commandMessage.trim();
								DEBUG_LOG(("We were kicked: reason was '%s'\n", resp.commandOptions.c_str()));
								if (commandMessage.compare("GameStarted") == 0)
								{
									message = TheGameText->fetch("GUI:GSKickedGameStarted");
								}
								else if (commandMessage.compare("GameFull") == 0)
								{
									message = TheGameText->fetch("GUI:GSKickedGameFull");
								}
								GSMessageBoxOk(TheGameText->fetch("GUI:GSErrorTitle"), message);
								nextScreen = "Menus/WOLCustomLobby.wnd";
								TheShell->pop();
							}
						}
						else if (slotNum > 0 && ((BfmeWolUpdateInfo *)TheGameSpyInfo)->amIHost())
						{
							if (!strcmp(resp.command.c_str(), "accept"))
							{
								game->getSlot(slotNum)->setAccept();
								((BfmeWolUpdateInfo *)TheGameSpyInfo)->setGameOptions();
								WOLDisplaySlotList();
							}
							else if (!strcmp(resp.command.c_str(), "MAP"))
							{
								Bool hasMap = atoi(resp.commandOptions.c_str());
								game->getSlot(slotNum)->setMapAvailability(hasMap);
								if (!hasMap)
								{
									// tell the host the user doesn't have the map
									UnicodeString mapDisplayName;
									const BfmeWolMapMetaData *mapData = (const BfmeWolMapMetaData *)TheMapCache->findMap( game->getMap() );
									Bool willTransfer = TRUE;
									if (mapData)
									{
										mapDisplayName.format(UnicodeString(L"%ls"), BfmeWolWideText::str(mapData->m_displayName));
										willTransfer = !mapData->m_isOfficial;
									}
									else
									{
										mapDisplayName.format(UnicodeString(L"%hs"), game->getMap().str());
										willTransfer = WouldMapTransfer(game);
									}
									UnicodeString text;
									if (willTransfer)
										text.format(TheGameText->fetch("GUI:PlayerNoMapWillTransfer"), BfmeWolWideText::str(game->getSlot(slotNum)->getName()), BfmeWolWideText::str(mapDisplayName));
									else
										text.format(TheGameText->fetch("GUI:PlayerNoMap"), BfmeWolWideText::str(game->getSlot(slotNum)->getName()), BfmeWolWideText::str(mapDisplayName));
									((BfmeWolUpdateInfo *)TheGameSpyInfo)->addText(text, GameSpyColor[GSCOLOR_DEFAULT], listboxGameSetupChat);
								}
								WOLDisplaySlotList();
							}
							else if (!strcmp(resp.command.c_str(), "REQ"))
							{
								AsciiString options = resp.commandOptions.c_str();
								options.trim();

								Bool change = false;
								Bool shouldUnaccept = false;
								AsciiString key;
								options.nextToken(&key, "=");
								Int val = atoi(options.str()+1);
								UnsignedInt uVal = atoi(options.str()+1);
								DEBUG_LOG(("GameOpt request: key=%s, val=%s from player %d\n", key.str(), options.str()+1, slotNum));

								GameSpyGameSlot *slot = game->getGameSpySlot(slotNum);
								if (!slot)
									break;

								if (key.compare("Color") == 0)
								{
									if (val >= -1 && val < TheMultiplayerSettings->getNumColors() && val != slot->getColor() && slot->getPlayerTemplate() != PLAYERTEMPLATE_OBSERVER)
									{
										Bool colorAvailable = TRUE;
										if(val != -1 )
										{
											for(Int i=0; i <MAX_SLOTS; i++)
											{
												GameSlot *checkSlot = game->getSlot(i);
												if(val == checkSlot->getColor() && slot != checkSlot)
												{
													colorAvailable = FALSE;
													break;
												}
											}
										}
										if(colorAvailable)
											slot->setColor(val);
										change = true;
									}
									else
									{
										DEBUG_LOG(("Rejecting invalid color %d\n", val));
									}
								}
								else if (key.compare("PlayerTemplate") == 0)
								{
									if (val >= PLAYERTEMPLATE_MIN && val < ThePlayerTemplateStore->getPlayerTemplateCount() && val != slot->getPlayerTemplate())
									{

										slot->setPlayerTemplate(val);
										if (val == PLAYERTEMPLATE_OBSERVER)
										{
											slot->setColor(-1);
											slot->setStartPos(-1);
											slot->setTeamNumber(-1);
										}
										change = true;
										shouldUnaccept = true;
									}
									else
									{
										DEBUG_LOG(("Rejecting invalid PlayerTemplate %d\n", val));
									}
								}
								else if (key.compare("StartPos") == 0)
								{
									if (val >= -1 && val < MAX_SLOTS && val != slot->getStartPos() && slot->getPlayerTemplate() != PLAYERTEMPLATE_OBSERVER)
									{
										Bool startPosAvailable = TRUE;
										if(val != -1)
										{
											for(Int i=0; i <MAX_SLOTS; i++)
											{
												GameSlot *checkSlot = game->getSlot(i);
												if(val == checkSlot->getStartPos() && slot != checkSlot)
												{
													startPosAvailable = FALSE;
													break;
												}
											}
										}
										if(startPosAvailable)
											slot->setStartPos(val);
										change = true;
										shouldUnaccept = true;
									}
									else
									{
										DEBUG_LOG(("Rejecting invalid startPos %d\n", val));
									}
								}
								else if (key.compare("Team") == 0)
								{
									if (val >= -1 && val < MAX_SLOTS/2 && val != slot->getTeamNumber() && slot->getPlayerTemplate() != PLAYERTEMPLATE_OBSERVER)
									{
										slot->setTeamNumber(val);
										change = true;
										shouldUnaccept = true;
									}
									else
									{
										DEBUG_LOG(("Rejecting invalid team %d\n", val));
									}
								}
								else if (key.compare("IP") == 0)
								{
									if (uVal != slot->getIP())
									{
										DEBUG_LOG(("setting IP of player %ls from 0x%08x to be 0x%08x", BfmeWolWideText::str(slot->getName()), slot->getIP(), uVal));
										BfmeWolAddress address = slot->getAddress();
                                        address.ip = uVal;
                                        slot->setAddress(address);
										change = true;
										shouldUnaccept = true;
									}
									else
									{
										DEBUG_LOG(("Rejecting invalid IP %d\n", uVal));
									}
								}
								else if (key.compare("NAT") == 0)
								{
									if ((val >= FirewallHelperClass::FIREWALL_MIN) &&
											(val <= FirewallHelperClass::FIREWALL_MAX))
									{
										slot->setNATBehavior((FirewallHelperClass::FirewallBehaviorType)val);
										DEBUG_LOG(("Setting NAT behavior to %d for player %d\n", val, slotNum));
										change = true;
									}
									else
									{
										DEBUG_LOG(("Rejecting invalid NAT behavior %d from player %d\n", val, slotNum));
									}
								}
								else if (key.compare("Ping") == 0)
								{
									slot->setPingString(options.str()+1);
									((BfmeWolUpdateInfo *)TheGameSpyInfo)->setGameOptions();
									DEBUG_LOG(("Setting ping string to %s for player %d\n", options.str()+1, slotNum));
								}

								if (change)
								{
									if (shouldUnaccept)
										game->resetAccepted();

									((BfmeWolUpdateInfo *)TheGameSpyInfo)->setGameOptions();

									WOLDisplaySlotList();
									DEBUG_LOG(("Slot value is color=%d, PlayerTemplate=%d, startPos=%d, team=%d, IP=0x%8.8X\n",
										slot->getColor(), slot->getPlayerTemplate(), slot->getStartPos(), slot->getTeamNumber(), slot->getIP()));
									DEBUG_LOG(("Slot list updated to %s\n", GameInfoToAsciiString(game).str()));
								}
							}
						}
					}
				}
				break;

			}
		}


	}
}// void WOLGameSetupMenuUpdate( WindowLayout * layout, void *userData)


//-------------------------------------------------------------------------------------------------
/** Lan Game Options menu input callback */
//-------------------------------------------------------------------------------------------------
WindowMsgHandledType WOLGameSetupMenuInput( GameWindow *window, UnsignedInt msg,
																			 WindowMsgData mData1, WindowMsgData mData2 )
{
	/*
	switch( msg ) 
	{

		//-------------------------------------------------------------------------------------------------
		case GWM_RIGHT_UP:
		{
			if (buttonPushed)
				break;

			GameWindow *control = (GameWindow *)mData1;
			NameKeyType controlID = (NameKeyType)control->winGetWindowId();
			DEBUG_LOG(("GWM_RIGHT_UP for control %d(%s)\n", controlID, TheNameKeyGenerator->keyToName(controlID).str()));
			break;
		}

		// --------------------------------------------------------------------------------------------
		case GWM_CHAR:
		{
			UnsignedByte key = mData1;
			UnsignedByte state = mData2;
			if (buttonPushed)
				break;

			switch( key )
			{
				// ----------------------------------------------------------------------------------------
				case KEY_ESC:
				{
					//
					// send a simulated selected event to the parent window of the
					// back/exit button
					//
					if( BitTest( state, KEY_STATE_UP ) )
					{
						TheWindowManager->winSendSystemMsg( window, GBM_SELECTED, 
																							(WindowMsgData)buttonBack, buttonBackID );
					}  // end if
					// don't let key fall through anywhere else
					return MSG_HANDLED;
				}  // end escape
			}  // end switch( key )
		}  // end char
	}  // end switch( msg )
	*/
	return MSG_IGNORED;
}//WindowMsgHandledType WOLGameSetupMenuInput( GameWindow *window, UnsignedInt msg,


// Slash commands -------------------------------------------------------------------------
extern "C" {
int getQR2HostingStatus(void);
}
extern int isThreadHosting;

Bool handleGameSetupSlashCommands(UnicodeString uText)
{
	AsciiString message;
	message.translate(uText);

	if (message.getCharAt(0) != '/')
	{
		return FALSE; // not a slash command
	}

	AsciiString remainder = message.str() + 1;
	AsciiString token;
	remainder.nextToken(&token);
	token.toLower();

	if (token == "host")
	{
		UnicodeString s;
		s.format(L"Hosting qr2:%d thread:%d", getQR2HostingStatus(), isThreadHosting);
		TheGameSpyInfo->addText(s, GameSpyColor[GSCOLOR_DEFAULT], NULL);
		return TRUE; // was a slash command
	}
	else if (token == "me" && uText.getLength()>4)
	{
		TheGameSpyInfo->sendChat(UnicodeString(uText.str()+4), TRUE, NULL);
		return TRUE; // was a slash command
	}
#if defined(_DEBUG) || defined(_INTERNAL)
	else if (token == "slots")
	{
		g_debugSlots = !g_debugSlots;
		TheGameSpyInfo->addText(UnicodeString(L"Toggled SlotList debug"), GameSpyColor[GSCOLOR_DEFAULT], NULL);
		return TRUE; // was a slash command
	}
	else if (token == "discon")
	{
		PeerRequest req;
		req.peerRequestType = PeerRequest::PEERREQUEST_LOGOUT;
		TheGameSpyPeerMessageQueue->addRequest( req );
		return TRUE;
	}
#endif // defined(_DEBUG) || defined(_INTERNAL)

	return FALSE; // not a slash command
}

static Int getNextSelectablePlayer(Int start)
{
	GameSpyStagingRoom *game = ((BfmeVirtualGameSpyInfo *)TheGameSpyInfo)->getCurrentStagingRoom();
	if (!((BfmeVirtualStagingRoom *)game)->amIHost())
		return -1;
	for (Int j=start; j<MAX_SLOTS; ++j)
	{
		GameSpyGameSlot *slot = game->getGameSpySlot(j);
		if (slot && slot->getStartPos() == -1 &&
			( (j==((BfmeVirtualStagingRoom *)game)->getLocalSlotNum() && game->getConstSlot(j)->getPlayerTemplate()!=PLAYERTEMPLATE_OBSERVER)
			|| slot->isAI()))
		{
			return j;
		}
	}
	return -1;
}

static Int getFirstSelectablePlayer(const GameInfo *game)
{
	const GameSlot *slot = game->getConstSlot(game->getLocalSlotNum());
	if (!game->amIHost() || slot && slot->getPlayerTemplate() != PLAYERTEMPLATE_OBSERVER)
		return game->getLocalSlotNum();

	for (Int i=0; i<MAX_SLOTS; ++i)
	{
		slot = game->getConstSlot(i);
		if (slot && slot->isAI())
			return i;
	}

	return game->getLocalSlotNum();
}

//-------------------------------------------------------------------------------------------------
/** WOL Game Options menu window system callback */
//-------------------------------------------------------------------------------------------------
WindowMsgHandledType WOLGameSetupMenuSystem( GameWindow *window, UnsignedInt msg, 
														 WindowMsgData mData1, WindowMsgData mData2 )
{
	UnicodeString txtInput;
	static buttonCommunicatorID = NAMEKEY_INVALID;
	switch( msg )
	{
		//-------------------------------------------------------------------------------------------------	
		case GWM_CREATE:
			{
				buttonCommunicatorID = NAMEKEY("GameSpyGameOptionsMenu.wnd:ButtonCommunicator");
				break;
			} // case GWM_DESTROY:
		//-------------------------------------------------------------------------------------------------
		case GWM_DESTROY:
			{
				break;
			} // case GWM_DESTROY:
		//-------------------------------------------------------------------------------------------------
		case GWM_INPUT_FOCUS:
			{	
				// if we're givin the opportunity to take the keyboard focus we must say we want it
				if( mData1 == TRUE )
					*(Bool *)mData2 = TRUE;

				return MSG_HANDLED;
			}//case GWM_INPUT_FOCUS:
		//-------------------------------------------------------------------------------------------------
		case GCM_SELECTED:
			{
				if (!initDone)
					break;
				if (buttonPushed)
					break;
				GameWindow *control = (GameWindow *)mData1;
				Int controlID = control->winGetWindowId();
        if ( controlID == comboBoxStartingCashID )
        {
          handleStartingCashSelection();
        }
        else
        {
				  GameSpyStagingRoom *myGame = TheGameSpyInfo->getCurrentStagingRoom();
				  for (Int i = 0; i < MAX_SLOTS; i++)
				  {
					  if (controlID == comboBoxColorID[i])
					  {
						  handleColorSelection(i);
					  }
					  else if (controlID == comboBoxPlayerTemplateID[i])
					  {
						  handlePlayerTemplateSelection(i);
					  }
					  else if (controlID == comboBoxTeamID[i])
					  {
						  handleTeamSelection(i);
					  }
					  else if( controlID == comboBoxPlayerID[i] && TheGameSpyInfo->amIHost() )
					  {
						  // We don't have anything that'll happen if we click on ourselves
						  if(i == myGame->getLocalSlotNum())
						   break;
						  // Get
						  Int pos = -1;
						  GadgetComboBoxGetSelectedPos(comboBoxPlayer[i], &pos);
						  if( pos != SLOT_PLAYER && pos >= 0)
						  {
							  if( myGame->getSlot(i)->getState() == SLOT_PLAYER )
							  {
								  PeerRequest req;
								  req.peerRequestType = PeerRequest::PEERREQUEST_UTMPLAYER;
								  req.UTM.isStagingRoom = TRUE;
								  AsciiString aName;
								  aName.translate(myGame->getSlot(i)->getName());
								  req.nick = aName.str();
								  req.id = "KICK/";
								  req.options = "true";
								  TheGameSpyPeerMessageQueue->addRequest(req);

								  UnicodeString name = myGame->getSlot(i)->getName();
								  myGame->getSlot(i)->setState(SlotState(pos));
								  myGame->resetAccepted();
								  TheGameSpyInfo->setGameOptions();
								  WOLDisplaySlotList();
								  //TheLAN->OnPlayerLeave(name);
							  }
							  else if( myGame->getSlot(i)->getState() != pos )
							  {
								  Bool wasAI = (myGame->getSlot(i)->isAI());
								  myGame->getSlot(i)->setState(SlotState(pos));
								  Bool isAI = (myGame->getSlot(i)->isAI());
								  myGame->resetAccepted();
								  if (wasAI ^ isAI)
									  PopulatePlayerTemplateComboBox(i, comboBoxPlayerTemplate, myGame, wasAI && myGame->getAllowObservers());
								  TheGameSpyInfo->setGameOptions();
								  WOLDisplaySlotList();
							  }
						  }
						  break;
					  }
				  }
        }
        break;
			}// case GCM_SELECTED:
		//-------------------------------------------------------------------------------------------------
		case GBM_SELECTED:
			{
				if (buttonPushed)
					break;

				GameWindow *control = (GameWindow *)mData1;
				Int controlID = control->winGetWindowId();
				static buttonCommunicatorID = NAMEKEY("GameSpyGameOptionsMenu.wnd:ButtonCommunicator");
				if ( controlID == buttonBackID )
				{
					savePlayerInfo();
					if( WOLMapSelectLayout )
					{
						WOLMapSelectLayout->destroyWindows();
						WOLMapSelectLayout->deleteInstance();
						WOLMapSelectLayout = NULL;
					}

					TheGameSpyInfo->getCurrentStagingRoom()->reset();
					//peerLeaveRoom(TheGameSpyChat->getPeer(), StagingRoom, NULL);
					TheGameSpyInfo->leaveStagingRoom();
					buttonPushed = true;
					nextScreen = "Menus/WOLCustomLobby.wnd";
					TheShell->pop();

				} //if ( controlID == buttonBack )
				else if ( controlID == buttonCommunicatorID )
				{
					GameSpyToggleOverlay( GSOVERLAY_BUDDY );

				}
				else if ( controlID == buttonEmoteID )
				{
					// read the user's input
					txtInput.set(GadgetTextEntryGetText( textEntryChat ));
					// Clear the text entry line
					GadgetTextEntrySetText(textEntryChat, UnicodeString::TheEmptyString);
					// Clean up the text (remove leading/trailing chars, etc)
					txtInput.trim();
					// Echo the user's input to the chat window
					if (!txtInput.isEmpty())
						TheGameSpyInfo->sendChat(txtInput, FALSE, NULL); // 'emote' button is now carriage-return
				} //if ( controlID == buttonEmote )
				else if ( controlID == buttonSelectMapID )
				{
					WOLMapSelectLayout = TheWindowManager->winCreateLayout( "Menus/WOLMapSelectMenu.wnd" );
					WOLMapSelectLayout->runInit();
					WOLMapSelectLayout->hide( FALSE );
					WOLMapSelectLayout->bringForward();
				}
				else if ( controlID == buttonStartID )
				{
					savePlayerInfo();
					if (TheGameSpyInfo->amIHost())
					{
						StartPressed();
					}
					else
					{
						//I'm the Client... send an accept message to the host.
						GameSlot *localSlot = TheGameSpyInfo->getCurrentStagingRoom()->getSlot(TheGameSpyInfo->getCurrentStagingRoom()->getLocalSlotNum());
						if (localSlot)
						{
							localSlot->setAccept();
						}
						UnicodeString hostName = TheGameSpyInfo->getCurrentStagingRoom()->getSlot(0)->getName();
						AsciiString asciiName;
						asciiName.translate(hostName);
						PeerRequest req;
						req.peerRequestType = PeerRequest::PEERREQUEST_UTMPLAYER;
						req.UTM.isStagingRoom = TRUE;
						req.id = "accept";
						req.nick = asciiName.str();
						req.options = "true";
						TheGameSpyPeerMessageQueue->addRequest(req);
						//peerSetReady( PEER, PEERTrue );
						WOLDisplaySlotList();
					}
				}
        else if ( controlID == checkBoxLimitSuperweaponsID )
        {
          handleLimitSuperweaponsClick();
        }
				else
				{
					for (Int i = 0; i < MAX_SLOTS; i++)
					{
						if (controlID == buttonMapStartPositionID[i])
						{
							GameSpyStagingRoom *game = TheGameSpyInfo->getCurrentStagingRoom();
							Int playerIdxInPos = -1;
							for (Int j=0; j<MAX_SLOTS; ++j)
							{
								GameSpyGameSlot *slot = game->getGameSpySlot(j);
								if (slot && slot->getStartPos() == i)
								{
									playerIdxInPos = j;
									break;
								}
							}
							if (playerIdxInPos >= 0)
							{
								GameSpyGameSlot *slot = game->getGameSpySlot(playerIdxInPos);
								if (playerIdxInPos == game->getLocalSlotNum() || (game->amIHost() && slot && slot->isAI()))
								{
									// it's one of my type.  Try to change it.
									Int nextPlayer = getNextSelectablePlayer(playerIdxInPos+1);
									handleStartPositionSelection(playerIdxInPos, -1);
									if (nextPlayer >= 0)
									{
										handleStartPositionSelection(nextPlayer, i);
									}
								}
							}
							else
							{
								// nobody in the slot - put us in
								Int nextPlayer = getNextSelectablePlayer(0);
								if (nextPlayer < 0)
									nextPlayer = getFirstSelectablePlayer(game);
								handleStartPositionSelection(nextPlayer, i);
							}
						}
					}
				}


				break;
			}// case GBM_SELECTED:
		//-------------------------------------------------------------------------------------------------
		case GBM_SELECTED_RIGHT:
   		{
   			if (buttonPushed)
   				break;
   
   			GameWindow *control = (GameWindow *)mData1;
				Int controlID = control->winGetWindowId();
				for (Int i = 0; i < MAX_SLOTS; i++)
				{
					if (controlID == buttonMapStartPositionID[i])
					{
						GameSpyStagingRoom *game = TheGameSpyInfo->getCurrentStagingRoom();
						Int playerIdxInPos = -1;
						for (Int j=0; j<MAX_SLOTS; ++j)
						{
							GameSpyGameSlot *slot = game->getGameSpySlot(j);
							if (slot && slot->getStartPos() == i)
							{
								playerIdxInPos = j;
								break;
							}
						}
						if (playerIdxInPos >= 0)
						{
							GameSpyGameSlot *slot = game->getGameSpySlot(playerIdxInPos);
							if (playerIdxInPos == game->getLocalSlotNum() || (game->amIHost() && slot && slot->isAI()))
							{
								// it's one of my type.  Remove it.
								handleStartPositionSelection(playerIdxInPos, -1);
							}
						}
					}
				}
				break;
			}

		//-------------------------------------------------------------------------------------------------
		case GEM_EDIT_DONE:
			{
				GameWindow *control = (GameWindow *)mData1;
				Int controlID = control->winGetWindowId();
				// Take the user's input and echo it into the chat window as well as
				// send it to the other clients on the lan
				if ( controlID == textEntryChatID )
				{
					
					// read the user's input
					txtInput.set(GadgetTextEntryGetText( textEntryChat ));
					// Clear the text entry line
					GadgetTextEntrySetText(textEntryChat, UnicodeString::TheEmptyString);
					// Clean up the text (remove leading/trailing chars, etc)
					txtInput.trim();
					// Echo the user's input to the chat window
					if (!txtInput.isEmpty())
					{
						if (!handleGameSetupSlashCommands(txtInput))
						{
							TheGameSpyInfo->sendChat(txtInput, false, NULL);
						}
					}

				}// if ( controlID == textEntryChatID )
				break;
			}
		//-------------------------------------------------------------------------------------------------
		default:
			return MSG_IGNORED;
	}//Switch
	return MSG_HANDLED;
}//WindowMsgHandledType WOLGameSetupMenuSystem( GameWindow *window, UnsignedInt msg, 
