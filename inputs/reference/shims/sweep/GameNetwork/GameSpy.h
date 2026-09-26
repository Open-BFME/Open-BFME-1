/*
**  GameNetwork/GameSpy.h shim — verbatim Generals header
**  (reference/CnC_Generals_Zero_Hour/Generals/Code/GameEngine/Include/GameNetwork/GameSpy.h)
**  plus the GP shim include that BFME sources expect through this path.
*/

#pragma once

#ifndef __GameSpy_H__
#define __GameSpy_H__

#include "GameSpy/Peer/Peer.h"

#include "GameClient/Color.h"
#include "Common/STLTypedefs.h"
#include "Common/SubsystemInterface.h"

// shim addition: the real GameSpy SDK headers leaked `using std::set` into
// the global namespace (GameSpyChat.cpp:38 uses bare `set<AsciiString>`).
using std::set;

class GameSpyGroupRoom
{
public:
	GameSpyGroupRoom() { m_name = AsciiString::TheEmptyString; m_groupID = m_numWaiting = m_maxWaiting = m_numGames = m_numPlaying = 0; }
	AsciiString m_name;
	Int m_groupID;
	Int m_numWaiting;
	Int m_maxWaiting;
	Int m_numGames;
	Int m_numPlaying;
};
typedef std::map<Int, GameSpyGroupRoom> GroupRoomMap;

class GameSpyChatInterface : public SubsystemInterface
{
public:
	virtual ~GameSpyChatInterface() { };

	virtual void init( void ) = 0;
	virtual void reset( void ) = 0;
	virtual void update( void ) = 0;

	virtual Bool isConnected( void ) = 0;
	virtual void login(AsciiString loginName, AsciiString password = AsciiString::TheEmptyString, AsciiString email = AsciiString::TheEmptyString) = 0;
	virtual void reconnectProfile( void ) = 0;
	virtual void disconnectFromChat( void ) = 0;

	virtual void UTMRoom( RoomType roomType, const char *key, const char *val, Bool authenticate = FALSE ) = 0;
	virtual void UTMPlayer( const char *name, const char *key, const char *val, Bool authenticate = FALSE ) = 0;
	virtual void startGame( void ) = 0;
	virtual void leaveRoom( RoomType roomType ) = 0;
	virtual void setReady( Bool ready ) = 0;
	virtual void enumPlayers( RoomType roomType, peerEnumPlayersCallback callback, void *userData ) = 0;
	virtual void startListingGames( peerListingGamesCallback callback ) = 0;
	virtual void stopListingGames( void ) = 0;

	virtual void joinGroupRoom( Int ID ) = 0;
	virtual void joinStagingRoom( GServer server, AsciiString password ) = 0;
	virtual void createStagingRoom( AsciiString gameName, AsciiString password, Int maxPlayers ) = 0;
	virtual void joinBestGroupRoom( void ) = 0;

	inline PEER getPeer( void )									{ return m_peer; }
	inline AsciiString getLoginName( void )			{ return m_loginName; }
	inline AsciiString getPassword( void )			{ return m_password; }
	inline GroupRoomMap* getGroupRooms( void )	{ return &m_groupRooms; }
	inline Int getCurrentGroupRoomID( void )		{ return m_currentGroupRoomID; }
	inline Bool getUsingProfile( void )					{ return m_usingProfiles; }
	inline Int getProfileID( void )							{ return m_profileID; }

	inline void setCurrentGroupRoomID( Int ID )	{ m_currentGroupRoomID = ID; }
	void clearGroupRoomList(void);
	inline Int getNumGroupRooms( void )					{ return m_groupRooms.size(); }


protected:

	AsciiString m_loginName;
	AsciiString m_password;
	AsciiString m_email;
	Bool m_usingProfiles;
	Int m_profileID;
	PEER m_peer;

	GroupRoomMap m_groupRooms;
	Int m_currentGroupRoomID;
};

GameSpyChatInterface *createGameSpyChat( void );

extern GameSpyChatInterface *TheGameSpyChat;


void JoinRoomCallback(PEER peer, PEERBool success,
											PEERJoinResult result, RoomType roomType,
											void *param);																	///< Called when we (fail to) join a room.  param is address of Bool to store result

void ListGroupRoomsCallback(PEER peer, PEERBool success,
														int groupID, GServer server,
														const char * name, int numWaiting,
														int maxWaiting, int numGames,
														int numPlaying, void * param);					///< Called while listing group rooms

enum GameSpyColors {
	GSCOLOR_DEFAULT = 0,
	GSCOLOR_CURRENTROOM,
	GSCOLOR_ROOM,
	GSCOLOR_GAME,
	GSCOLOR_PLAYER_NORMAL,
	GSCOLOR_PLAYER_OWNER,
	GSCOLOR_PLAYER_BUDDY,
	GSCOLOR_PLAYER_SELF,
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
	GSCOLOR_MAX
};

extern const Color GameSpyColor[GSCOLOR_MAX];

#include "GameSpy/GP/GP.h"

#endif // __GameSpy_H__
