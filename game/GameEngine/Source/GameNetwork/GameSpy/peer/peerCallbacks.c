// cl: /DNDEBUG /MD -Iinputs/reference/shims/gamespy
/* GameSpy Peer SDK -- peerCallbacks.c, the deferred-callback marshalling half.
   Reconstructed, not vendored.  The Area 51 carrier that supplies the rest of
   this directory (github.com/bisc67/Area51, Support/NetworkMgr/GameSpy) ships
   no chat/ or peer/ module at all, so the upstream 2004 text of this file is
   not in hand.  What IS in hand is the 2007 SDK (nitrocaster/GameSpy,
   src/GameSpy/Peer/peerCallbacks.c), whose bodies here are transcribed
   verbatim; only the surrounding declarations are local, because peer.h /
   peerMain.h / chat.h of the 2004 vintage are likewise unavailable and the
   2007 ones drag in the common/gsPlatform layer that did not exist in 2004.

   The identification is not a guess.  retail carries `callbackFuncs[]` at
   0x00D30D50: 34 sixteen-byte rows {type, copy, free, call} in ascending type
   order, 0..33, closed by a {34,NULL,NULL,NULL} terminator -- exactly the
   shape, order and cardinality of piCallbackType (PI_NUM_CALLBACK_TYPES==34)
   and of the callbackFuncs[] initialiser in the 2007 file.  Every triple in
   that table lands on a body in 0x0085C600..0x0085DF10.  Two independent
   layout facts fall out of it and both check: piCallbackData is
   {type,success,callback,callbackParam,params,ID,inCall} because every *Call
   trampoline reads callback from +8, success from +4 and callbackParam from
   +0xC; and CHATChannelMode is eight ints because piRoomModeChangedCopy at
   0x0085CE50 copies its `mode` member with `mov ecx,8 / rep movsd`.

   The 34 copy/free/call triples and the table came first; piAddCallback and
   the twenty global-callback entry points followed, once piConnection grew
   the PEERCallbacks block the entry points read.  piCallbacksThink and the
   operation-completion entry points (types 0..8, and 26/29/30/32/33) are
   still outstanding: those carry the callback and ID in their own arguments
   rather than reading them off the connection, and are a separate shape.

   One thing piAddCallback cost a build to learn, worth having written down:
   the allocated params block must be a LOCAL, not written straight into
   data.params.  Spelled `data.params = gsimalloc(...)` the store lands
   immediately, VC7.1 spends a stack slot keeping it, and the extra pressure
   pushes `paramsSize` out of the private register convention -- `peer` and
   `callback` get the registers instead of `peer` and `paramsSize`, and all
   twenty call sites go wrong with it.  Held in a local the pointer stays in
   ESI to the end, the struct is filled in one block, and the convention is
   retail's.  The parameter ORDER is not what decides this; moving
   paramsSize to position two changed nothing.

   piAddChangeNickCallback is the one body here whose two field stores are
   emitted in reverse.  Its params are two char * of the same width, and
   VC7.1 schedules the pair the other way round from every neighbour whose
   two fields differ in type; the source has to write newNick first.  Its
   twin piAddPlayerChangedNickCallback does NOT -- same two names, three
   fields, declaration order.  Only the bytes tell them apart.

   Build flags follow the rest of this SDK: /MD so libc is __imp__ indirect,
   __cdecl, NDEBUG so the asserts vanish, Win32 headers from
   inputs/reference/shims/gamespy. */

#include <string.h>
#include <stdlib.h>
#include <assert.h>

/* --- local stand-ins for peer.h / peerMain.h / chat.h / sb_serverbrowsing.h,
       carrying only what this file's bodies need.  Widths are what matter and
       every one of these is a 32-bit scalar or pointer. --- */

#define PEER_ADD        0  // a server is being added
#define PEER_UPDATE     1  // a server has been updated
#define PEER_REMOVE     2  // a server has been removed
#define PEER_CLEAR      3  // all the servers have been cleared

typedef void * PEER;

typedef enum
{
	PEERFalse,
	PEERTrue
} PEERBool;

typedef enum
{
	TitleRoom,
	GroupRoom,
	StagingRoom,
	NumRooms
} RoomType;

typedef enum
{
	NormalMessage,
	ActionMessage,
	NoticeMessage
} MessageType;

typedef enum
{
	PEERJoinSuccess,
	PEERFullRoom,
	PEERInviteOnlyRoom,
	PEERBannedFromRoom,
	PEERBadPassword,
	PEERAlreadyInRoom,
	PEERNoTitleSet,
	PEERNoConnection,
	PEERAutoMatching,
	PEERJoinFailed
} PEERJoinResult;

typedef enum
{
	PEERFailed,
	PEERSearching,
	PEERWaiting,
	PEERStaging,
	PEERReady,
	PEERComplete
} PEERAutoMatchStatus;

typedef struct _SBServer *SBServer;

typedef enum
{
	CHATFalse,
	CHATTrue
} CHATBool;

typedef struct CHATChannelMode
{
	CHATBool InviteOnly;
	CHATBool Private;
	CHATBool Secret;
	CHATBool Moderated;
	CHATBool NoExternalMessages;
	CHATBool OnlyOpsChangeTopic;
	CHATBool OpsObeyChannelLimit;
	int Limit;
} CHATChannelMode;

typedef char gsi_char;

#define PEERCBType void*

#define GSI_UNUSED(x) (void)x

#define gsimalloc malloc
#define gsifree free

/* nonport.c's strdup; retail's copy lives at 0x008543B0. */
char * goastrdup(const char *src);

/* peerAutoMatch.c, retail 0x00858120. */
PEERBool peerIsAutoMatching(PEER peer);

#include "../darray.h"

/* piConnection.  peerMain.h of this vintage is not in hand either, and only
   two of its members are reached from this file, so only those two are
   modelled -- at the offsets retail reads them at, which is where these two
   numbers come from and the only thing that makes them checkable:
   piListingGamesCall at 0x0085C7D0 passes [peer+0x1818] to ArrayLength and
   ArrayNth, and piPlayerInfoCall at 0x0085D4E0 indexes [peer+roomType*4+0x390].
   Everything else is reserved space, deliberately unnamed rather than guessed. */
/* PEERCallbacks.  The offsets are read out of retail, not guessed: each
   piAdd*Callback entry point below loads its own callback from a fixed
   slot and the shared user-data from +0x1814, and the twenty slots run
   0x17a4..0x17f0 in the callbackFuncs[] type order.  Twenty-nine dwords
   from 0x17a4 land exactly on callbackList at 0x1818, which is where the
   eight unnamed qr* slots in between come from -- they are counted, not
   invented.  Widths are all that matter here, so every slot is void *. */
/* piOperation, only the three members piAddAutoMatchStatusCallback reads.
   peerOperations.c next door names the same object's type at +0x04, room
   at +0x1c and cancelled flag at +0x38; these three are the ones this file
   reaches, and the +0x0c one is named ID because that is the argument the
   single reader here hands piAddCallback. */
typedef struct piOperation
{
	char reserved0[0x0c];
	int ID;				/* +0x0c */
	void * callback;		/* +0x10 */
	char reserved14[0x18 - 0x10 - 4];
	void * param;			/* +0x18 */
} piOperation;

typedef struct PEERCallbacks
{
	void * disconnected;	/* +0x17a4 */
	void * roomMessage;
	void * roomUTM;
	void * roomNameChanged;
	void * roomModeChanged;
	void * playerMessage;
	void * playerUTM;
	void * readyChanged;
	void * gameStarted;
	void * playerJoined;
	void * playerLeft;
	void * kicked;
	void * newPlayerList;
	void * playerChangedNick;
	void * playerInfo;
	void * playerFlagsChanged;
	void * ping;
	void * crossPing;
	void * globalKeyChanged;
	void * roomKeyChanged;	/* +0x17f0 */
	void * reserved[8];	/* the qr* callbacks, +0x17f4 .. +0x1810 */
	void * param;	/* +0x1814 */
} PEERCallbacks;

typedef struct piConnection
{
	char reserved0[0x4c];
	void * nickErrorCallback;	/* +0x4c */
	char reserved0b[0x390 - 0x4c - 4];
	PEERBool inRoom[NumRooms];
	char reserved1[0x17a4 - 0x390 - 3 * 4];
	PEERCallbacks callbacks;
	DArray callbackList;
	int callbackListLen;
	int numCallbacksCalled;		/* +0x1820 */
	int numCallbacksInCall;		/* +0x1824 */
	char reserved2[0x18d4 - 0x1824 - 4];
	int autoMatchStatus;		/* +0x18d4 */
	char reserved3[0x1ef0 - 0x18d4 - 4];
	piOperation * autoMatchOperation;	/* +0x1ef0 */
} piConnection;

#define PEER_CONNECTION           piConnection * connection;\
                                  assert(peer);\
                                  connection = (piConnection *)peer;\
								  GSI_UNUSED(connection);

typedef void (* peerDisconnectedCallback)
(
	PEER peer,  // The peer object.
	const gsi_char * reason,  // The reason for the disconnection.
	void * param  // User-data.
);

typedef void (* peerRoomMessageCallback)
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The type of room that the message was in.
	const gsi_char * nick,  // The nick of the player who sent the message.
	const gsi_char * message,  // The text of the message.
	MessageType messageType,  // The type of message.
	void * param  // User-data.
);

typedef void (* peerRoomUTMCallback)
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The type of room that the UTM was in.
	const gsi_char * nick,  // The nick of the player who sent the UTM.
	const gsi_char * command, // The UTM command for this message.
	const gsi_char * parameters,  // Any parameters for this UTM.
	PEERBool authenticated,  // True if this has been authenticated by the server.
	void * param  // User-data.
);

typedef void (* peerRoomNameChangedCallback)
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The type of room that the name changed in.
	void * param  // User-data
);

typedef void (* peerRoomModeChangedCallback)
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The type of room that the name changed in.
	CHATChannelMode * mode,  // The current mode for this room.
	void * param  // User-data
);

typedef void (* peerPlayerMessageCallback)
(
	PEER peer,  // The peer object.
	const gsi_char * nick,  // The nick of the player who sent the message.
	const gsi_char * message,  // The text of the message.
	MessageType messageType,  // The type of message.
	void * param  // User-data
);

typedef void (* peerPlayerUTMCallback)
(
	PEER peer,  // The peer object.
	const gsi_char * nick,  // The nick of the player who sent the UTM.
	const gsi_char * command, // The UTM command for this message.
	const gsi_char * parameters,  // Any parameters for this UTM.
	PEERBool authenticated,  // True if this has been authenticated by the server.
	void * param  // User-data
);

typedef void (* peerReadyChangedCallback)
(
	PEER peer,  // The peer object.
	const gsi_char * nick,  // The nick of the player who's ready state changed.
	PEERBool ready,  // The player's new ready state.
	void * param  // User-data.
);

typedef void (* peerGameStartedCallback)
(
	PEER peer,  // The peer object.
	SBServer server,  // A server object representing this host.
	const gsi_char * message,  // A message that was passed into peerStartGame().
	void * param  // User-data.
);

typedef void (* peerPlayerJoinedCallback)
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The type of room that the player joined.
	const gsi_char * nick,  // The nick of the player that joined.
	void * param  // User-data.
);

typedef void (* peerPlayerLeftCallback)
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The type of room that the player left.
	const gsi_char * nick,  // The nick of the player that left.
	const gsi_char * reason,  // The reason the player left.
	void * param  // User-data.
);

typedef void (* peerKickedCallback)
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The type of room that the player was kicked from.
	const gsi_char * nick,  // The nick of the player that did the kicking.
	const gsi_char * reason,  // An optional reason for the kick.
	void * param  // User-data.
);

typedef void (* peerNewPlayerListCallback)
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The type of room.
	void * param  // User-data
);

typedef void (* peerPlayerChangedNickCallback)
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The type of the room the nick changed was in.
	const gsi_char * oldNick,  // The player's old nick.
	const gsi_char * newNick,  // The player's new nick.
	void * param  // User-data.
);

typedef void (* peerPlayerInfoCallback)
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The room the info was gotten in.
	const gsi_char * nick,  // The nick of the player the info is for.
	unsigned int IP,  // The player's IP.
	int profileID,  // The player's profile ID.
	void * param  // User-data.
);

typedef void (* peerPlayerFlagsChangedCallback)
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The room the flags were changed in.
	const gsi_char * nick,  // The player whose flags have changed.
	int oldFlags,  // The player's old flags.
	int newFlags,  // The player's new flags.
	void * param  // User-data
);

typedef void (* peerPingCallback)
(
	PEER peer,  // The peer object.
	const gsi_char * nick,  // The other player's nick.
	int ping,  // The ping.
	void * param  // User-data.
);

typedef void (* peerCrossPingCallback)
(
	PEER peer,  // The peer object.
	const gsi_char * nick1,  // The first player's nick.
	const gsi_char * nick2,  // The second player's nick.
	int crossPing,  // The cross-ping.
	void * param  // User-data.
);

typedef void (* peerGlobalKeyChangedCallback)
(
	PEER peer,  // The peer object.
	const gsi_char * nick,  // The player whose key changed.
	const gsi_char * key,  // The key.
	const gsi_char * value,  // The value.
	void * param  // User-data.
);

typedef void (* peerRoomKeyChangedCallback)
(
	PEER peer,  // The peer object.
	RoomType roomType,  // The room the player is in.
	const gsi_char * nick,  // The player whose key changed.
	const gsi_char * key,  // The key.
	const gsi_char * value,  // The value.
	void * param  // User-data.
);

typedef void (* peerConnectCallback)
(
	PEER peer,  // The peer object.
	PEERBool success,  // PEERTrue if success, PEERFalse if failure.
	int failureReason,  // If failure, the reason for it (PEER_DISCONNECTED, etc.)
	void * param  // User-data.
);

typedef void (* peerNickErrorCallback)
(
	PEER peer,  // The peer object.
	int type,  // The type of nick error (PEER_IN_USE, PEER_INVALID, etc.)
	const gsi_char * nick,  // The bad nick.
	int numSuggestedNicks,  // The number of suggested nicks.
	const gsi_char ** suggestedNicks,  // The array of nicks.
	void * param  // User-data.
);

typedef void (* peerChangeNickCallback)
(
	PEER peer,  // The peer object.
	PEERBool success,  // PEERTrue if success, PEERFalse if failure.
	const gsi_char * oldNick,  // The old nickname.
	const gsi_char * newNick,  // The new nickname.
	void * param  // User-data.
);

typedef void (* peerAuthenticateCDKeyCallback)
(
	PEER peer,  // The peer object.
	int result,  // 1 if authenticated, otherwise not authenticated.
	const gsi_char * message,  // A string representing the result.
	void * param  // User-data.
);

typedef void (* peerJoinRoomCallback)
(
	PEER peer,  // The peer object.
	PEERBool success,  // PEERTrue if success, PEERFalse if failure.
	PEERJoinResult result,  // The result of the attempt.
	RoomType roomType,  // The type of room joined/created.
	void * param  // User-data.
);

typedef void (* peerListGroupRoomsCallback)
(
	PEER peer,  // The peer object.
	PEERBool success,  // PEERTrue if success, PEERFalse if failure.
	int groupID,  // A unique ID for this group.
	SBServer server,  // The server object for this group room.
	const gsi_char * name,  // The group room's name.
	int numWaiting,  // The number of players in the room.
	int maxWaiting,  // The maximum number of players allowed in the room.
	int numGames,  // The number of games either staging or running in the group.
	int numPlaying,  // The total number of players in games in the group.
	void * param  // User-data.
);

typedef void (* peerListingGamesCallback)
(
	PEER peer,  // The peer object.
	PEERBool success,  // PEERTrue if success, PEERFalse if failure.
	const gsi_char * name,  // The name of the game being listed.
	SBServer server,  // The server object for this game.
	PEERBool staging,  // If PEERTrue, this is a staging room and not a running game.
	int msg,  // The type of message this is.
		// PEER_CLEAR:
		//   Clear the list.  This has the same effect as if this was called
		//   with PEER_REMOVE for every server listed.
		// PEER_ADD:
		//   This is a new server. Add it to the list.
		// PEER_UPDATE:
		//   This server is already on the list, and its been updated.
		// PEER_REMOVE:
		//   Remove this server from the list.  The server object for this server
		//   should not be used again after this callback returns.
	int progress,  // The percent of servers that have been added.
	void * param  // User-data.
);

typedef void (* peerEnumPlayersCallback)
(
	PEER peer,  // The peer object.
	PEERBool success,  // PEERTrue if success, PEERFalse if failure.
	RoomType roomType,  // The room whose players are being enumerated.
	int index,  // The index of the player (0 to (N - 1)).  -1 when finished.
	const gsi_char * nick,  // The nick of the player.
	int flags,  // This player's flags (see #define's above).  PANTS|03.12.01
	void * param  // User-data.
);

typedef void (* peerGetPlayerInfoCallback)
(
	PEER peer,  // The peer object.
	PEERBool success,  // PEERTrue if success, PEERFalse if failure.
	const gsi_char * nick,  // The player's nick.
	unsigned int IP,  // The player's IP, in network byte order.
	int profileID,  // The player's profile ID.
	void * param  // User-data.
);

typedef void (* peerGetPlayerProfileIDCallback)
(
	PEER peer,  // The peer object.
	PEERBool success,  // PEERTrue if success, PEERFalse if failure.
	const gsi_char * nick,  // The player's nick.
	int profileID,  // The player's profile ID.
	void * param  // User-data.
);

typedef void (* peerGetPlayerIPCallback)
(
	PEER peer,  // The peer object.
	PEERBool success,  // PEERTrue if success, PEERFalse if failure.
	const gsi_char * nick,  // The player's nick.
	unsigned int IP,  // The player's IP, in network byte order.  PANTS|09.11.00 - was unsigned long
	void * param  // User-data.
);

typedef void (* peerGetGlobalKeysCallback)
(
	PEER peer,  // The peer object.
	PEERBool success,  // If PEERFalse, unable to get the keys.
	const gsi_char * nick,  // The player the keys are for.
	int num,  // The number of keys.
	const gsi_char ** keys,  // The keys got.
	const gsi_char ** values,  // The values for the keys.
	void * param  // User-data.
);

typedef void (* peerGetRoomKeysCallback)
(
	PEER peer,  // The peer object.
	PEERBool success,  // If PEERFalse, unable to get the keys.
	RoomType roomType,  // The room the keys are in.
	const gsi_char * nick,  // The player the keys are for, or NULL for the room.
	int num,  // The number of keys.
	gsi_char ** keys,  // The keys.
	gsi_char ** values,  // The values for the keys.
	void * param  // User-data.
);

typedef void (* peerAutoMatchStatusCallback)
(
	PEER peer,  // The peer object.
	PEERAutoMatchStatus status,  // The current status.
	void * param  // User-data.
);


typedef enum piCallbackType
{
	PI_CONNECT_CALLBACK,
	PI_JOIN_ROOM_CALLBACK,
	PI_LIST_GROUP_ROOMS_CALLBACK,
	PI_LISTING_GAMES_CALLBACK,
	PI_NICK_ERROR_CALLBACK,
	PI_ENUM_PLAYERS_CALLBACK,
	PI_GET_PLAYER_INFO_CALLBACK,
	PI_GET_PLAYER_PROFILE_ID_CALLBACK,
	PI_GET_PLAYER_IP_CALLBACK,
	PI_ROOM_MESSAGE_CALLBACK,
	PI_ROOM_UTM_CALLBACK,
	PI_ROOM_NAME_CHANGED_CALLBACK,
	PI_ROOM_MODE_CHANGED_CALLBACK,
	PI_PLAYER_MESSAGE_CALLBACK,
	PI_PLAYER_UTM_CALLBACK,
	PI_READY_CHANGED_CALLBACK,
	PI_GAME_STARTED_CALLBACK,
	PI_PLAYER_JOINED_CALLBACK,
	PI_PLAYER_LEFT_CALLBACK,
	PI_KICKED_CALLBACK,
	PI_NEW_PLAYER_LIST_CALLBACK,
	PI_PLAYER_CHANGED_NICK_CALLBACK,
	PI_PLAYER_INFO_CALLBACK,
	PI_DISCONNECTED_CALLBACK,
	PI_PING_CALLBACK,
	PI_CROSS_PING_CALLBACK,
	PI_CHANGE_NICK_CALLBACK,
	PI_GLOBAL_KEY_CHANGED_CALLBACK,
	PI_ROOM_KEY_CHANGED_CALLBACK,
	PI_GET_GLOBAL_KEYS_CALLBACK,
	PI_GET_ROOM_KEYS_CALLBACK,
	PI_PLAYER_FLAGS_CHANGED_CALLBACK,
	PI_AUTHENTICATE_CDKEY_CALLBACK,
	PI_AUTO_MATCH_STATUS_CALLBACK,
	PI_NUM_CALLBACK_TYPES
} piCallbackType;

typedef struct piCallbackData
{
	piCallbackType type;  // PI_<type>_CALLBACK
	PEERBool success;  // operation success
	PEERCBType callback;  // the function callback -- int type for ANSI compatability
	void * callbackParam;  // user-data for the callback
	void * params;  // extra callback params
	int ID;  // unique ID for this callback
	PEERBool inCall;  // set to true immediately before callback is called, then to false
} piCallbackData;

typedef struct piCallbackFuncs
{
	piCallbackType type;
	PEERBool (* copy)
	(
		void * paramsOut,
		void * paramsIn
	);
	void (* gsifree)
	(
		void * params
	);
	void (* call)
	(
		PEER peer,
		piCallbackData * data
	);
} piCallbackFuncs;

typedef struct piConnectParams
{
	int failureReason;
} piConnectParams;
static PEERBool piConnectCopy(void * paramsOut_, void * paramsIn_)
{
	piConnectParams * paramsOut = (piConnectParams *)paramsOut_;
	piConnectParams * paramsIn = (piConnectParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	paramsOut->failureReason = paramsIn->failureReason;
	
	return PEERTrue;
}
static void piConnectFree(void * params_)
{
	piConnectParams * params = (piConnectParams *)params_;

	assert(params);
	GSI_UNUSED(params);
}
static void piConnectCall(PEER peer, piCallbackData * data)
{
	piConnectParams * params;

	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_CONNECT_CALLBACK);
	
	params = data->params;
	((peerConnectCallback)data->callback)(peer, data->success, params->failureReason, data->callbackParam);
}
typedef struct piJoinRoomParams
{
	PEERJoinResult result;
	RoomType roomType;
} piJoinRoomParams;
static PEERBool piJoinRoomCopy(void * paramsOut_, void * paramsIn_)
{
	piJoinRoomParams * paramsOut = (piJoinRoomParams *)paramsOut_;
	piJoinRoomParams * paramsIn = (piJoinRoomParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	paramsOut->result = paramsIn->result;
	paramsOut->roomType = paramsIn->roomType;
	
	return PEERTrue;
}
static void piJoinRoomFree(void * params_)
{
	piJoinRoomParams * params = (piJoinRoomParams *)params_;

	assert(params);
	GSI_UNUSED(params);
}
static void piJoinRoomCall(PEER peer, piCallbackData * data)
{
	piJoinRoomParams * params;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_JOIN_ROOM_CALLBACK);
	
	params = data->params;
	((peerJoinRoomCallback)(PEERCBType)data->callback)(peer, data->success, params->result, params->roomType, data->callbackParam);
}
typedef struct piListGroupRoomsParams
{
	int groupID;
	SBServer server;
	char * name;
	int numWaiting;
	int maxWaiting;
	int numGames;
	int numPlaying;
} piListGroupRoomsParams;
static PEERBool piListGroupRoomsCopy(void * paramsOut_, void * paramsIn_)
{
	piListGroupRoomsParams * paramsOut = (piListGroupRoomsParams *)paramsOut_;
	piListGroupRoomsParams * paramsIn = (piListGroupRoomsParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	paramsOut->groupID = paramsIn->groupID;
	paramsOut->server = paramsIn->server;
	paramsOut->numWaiting = paramsIn->numWaiting;
	paramsOut->maxWaiting = paramsIn->maxWaiting;
	paramsOut->numGames = paramsIn->numGames;
	paramsOut->numPlaying = paramsIn->numPlaying;
	if(paramsIn->name)
	{
		paramsOut->name = goastrdup(paramsIn->name);
		if(paramsIn->name && !paramsOut->name)
			return PEERFalse;
	}
	else
		paramsOut->name = NULL;

	return PEERTrue;
}
static void piListGroupRoomsFree(void * params_)
{
	piListGroupRoomsParams * params = (piListGroupRoomsParams *)params_;

	assert(params);

	gsifree(params->name);
}
static void piListGroupRoomsCall(PEER peer, piCallbackData * data)
{
	piListGroupRoomsParams * params;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_LIST_GROUP_ROOMS_CALLBACK);
	
	params = data->params;
	
#ifndef GSI_UNICODE
	((peerListGroupRoomsCallback)(PEERCBType)data->callback)(peer, data->success, params->groupID, params->server, params->name, params->numWaiting, params->maxWaiting, params->numGames, params->numPlaying, data->callbackParam);
#else
	{
		unsigned short* name_W = NULL;
		if (params->name != NULL)
			name_W = UTF8ToUCS2StringAlloc(params->name);
		((peerListGroupRoomsCallback)(int)data->callback)(peer, data->success, params->groupID, params->server, name_W, params->numWaiting, params->maxWaiting, params->numGames, params->numPlaying, data->callbackParam);
		gsifree(name_W);
	}
#endif
}
typedef struct piListingGamesParams
{
	char * name;
	SBServer server;
	PEERBool staging;
	int msg;
	int progress;
} piListingGamesParams;
static PEERBool piListingGamesCopy(void * paramsOut_, void * paramsIn_)
{
	piListingGamesParams * paramsOut = (piListingGamesParams *)paramsOut_;
	piListingGamesParams * paramsIn = (piListingGamesParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	if(paramsIn->name)
	{
		paramsOut->name = goastrdup(paramsIn->name);
		if(paramsIn->name && !paramsOut->name)
			return PEERFalse;
	}
	else
		paramsOut->name = NULL;
	paramsOut->staging = paramsIn->staging;
	paramsOut->server = paramsIn->server;
	paramsOut->msg = paramsIn->msg;
	paramsOut->progress = paramsIn->progress;
	
	return PEERTrue;
}
static void piListingGamesFree(void * params_)
{
	piListingGamesParams * params = (piListingGamesParams *)params_;

	assert(params);

	gsifree(params->name);
}
static void piListingGamesCall(PEER peer, piCallbackData * data)
{
	piListingGamesParams * params;
	int len;
	int i;

	PEER_CONNECTION;
		
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_LISTING_GAMES_CALLBACK);

	params = data->params;

	// This is a bit of a hack.  We don't want the server browser progess to show
	//	100% until the last callback is being called.
	if (params->progress == 100)
	{
		len = ArrayLength(connection->callbackList);
		for(i = 0; i < len; i++)
		{
			// look for a listing games callback
			piCallbackData* anotherData = (piCallbackData *)ArrayNth(connection->callbackList, i);
			if(anotherData != data && anotherData->type == PI_LISTING_GAMES_CALLBACK)
			{
				piListingGamesParams* anotherParams = (piListingGamesParams *)anotherData->params;
				if(anotherParams->msg == PEER_UPDATE)
				{
					// Another update callback will follow this one,
					// limit the current callback's progress to 99%
					params->progress = 99;
					break;
				}
			}
		}
	}

#ifndef GSI_UNICODE
	((peerListingGamesCallback)(PEERCBType)data->callback)(peer, data->success, params->name, params->server, params->staging, params->msg, params->progress, data->callbackParam);
#else
	{
		unsigned short* name_W = NULL; 
		if (params->name != NULL)
			name_W = UTF8ToUCS2StringAlloc(params->name);
		((peerListingGamesCallback)(int)data->callback)(peer, data->success, name_W, params->server, params->staging, params->msg, params->progress, data->callbackParam);
		gsifree(name_W);
	}
#endif
}
typedef struct piNickErrorParams
{
	int type;
	char * nick;
	int numSuggestedNicks;
	char ** suggestedNicks;
} piNickErrorParams;
static PEERBool piNickErrorCopy(void * paramsOut_, void * paramsIn_)
{
	int i;
	int num;
	PEERBool success = PEERTrue;
	piNickErrorParams * paramsOut = (piNickErrorParams *)paramsOut_;
	piNickErrorParams * paramsIn = (piNickErrorParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	memset(paramsOut, 0, sizeof(piNickErrorParams));
	num = paramsOut->numSuggestedNicks = paramsIn->numSuggestedNicks;

	paramsOut->type = paramsIn->type;
	if(paramsIn->nick)
	{
		paramsOut->nick = goastrdup(paramsIn->nick);
		if(!paramsOut->nick)
			success = PEERFalse;
	}
	else
		paramsOut->nick = NULL;

	if(success && num && paramsIn->suggestedNicks)
	{
		paramsOut->suggestedNicks = (char **)gsimalloc(sizeof(char *) * num);
		if(!paramsOut->suggestedNicks)
			success = PEERFalse;
		else
			memset(paramsOut->suggestedNicks, 0, sizeof(char *) * num);

		for(i = 0 ; success && (i < num) ; i++)
		{
			paramsOut->suggestedNicks[i] = goastrdup(paramsIn->suggestedNicks[i]);
			if(!paramsOut->suggestedNicks[i])
				success = PEERFalse;
		}
	}

	if(!success)
	{
		gsifree(paramsOut->nick);
		for(i = 0 ; i < num ; i++)
		{
			if(paramsOut->suggestedNicks)
				gsifree(paramsOut->suggestedNicks[i]);
		}
		gsifree(paramsOut->suggestedNicks);
	}

	return success;
}
static void piNickErrorFree(void * params_)
{
	int i;
	piNickErrorParams * params = (piNickErrorParams *)params_;

	assert(params);

	gsifree(params->nick);
	for(i = 0 ; i < params->numSuggestedNicks ; i++)
	{
		if(params->suggestedNicks)
			gsifree(params->suggestedNicks[i]);
	}
	gsifree(params->suggestedNicks);
}
static void piNickErrorCall(PEER peer, piCallbackData * data)
{
	piNickErrorParams * params;

	//PEER_CONNECTION;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_NICK_ERROR_CALLBACK);

	params = data->params;
#ifndef GSI_UNICODE
	((peerNickErrorCallback)(PEERCBType)data->callback)(peer, params->type, params->nick, params->numSuggestedNicks, (const char **)params->suggestedNicks, data->callbackParam);
#else
	{
		unsigned short* nick_W = UTF8ToUCS2StringAlloc(params->nick);
		unsigned short** suggestedNicks_W = UTF8ToUCS2StringArrayAlloc((const UTF8String *)params->suggestedNicks, params->numSuggestedNicks);
		int i;
		((peerNickErrorCallback)data->callback)(peer, params->type, nick_W, params->numSuggestedNicks, (const unsigned short**)suggestedNicks_W, data->callbackParam);
		gsifree(nick_W);
		for (i=0; i < params->numSuggestedNicks; i++)
		{
			gsifree(suggestedNicks_W[i]);
		}
		gsifree(suggestedNicks_W);
	}
#endif
}
typedef struct piEnumPlayersParams
{
	RoomType roomType;
	int index;
	char * nick;
	int flags;
} piEnumPlayersParams;
static PEERBool piEnumPlayersCopy(void * paramsOut_, void * paramsIn_)
{
	piEnumPlayersParams * paramsOut = (piEnumPlayersParams *)paramsOut_;
	piEnumPlayersParams * paramsIn = (piEnumPlayersParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	paramsOut->roomType = paramsIn->roomType;
	paramsOut->index = paramsIn->index;
	paramsOut->flags = paramsIn->flags;
	if(paramsIn->nick)
	{
		paramsOut->nick = goastrdup(paramsIn->nick);
		if(paramsIn->nick && !paramsOut->nick)
			return PEERFalse;
	}
	else
		paramsOut->nick = NULL;
	
	return PEERTrue;
}
static void piEnumPlayersFree(void * params_)
{
	piEnumPlayersParams * params = (piEnumPlayersParams *)params_;

	assert(params);

	gsifree(params->nick);
}
static void piEnumPlayersCall(PEER peer, piCallbackData * data)
{
	piEnumPlayersParams * params;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_ENUM_PLAYERS_CALLBACK);
	
	params = data->params;
#ifndef GSI_UNICODE
	((peerEnumPlayersCallback)data->callback)(peer, data->success, params->roomType, params->index, params->nick, params->flags, data->callbackParam);
#else
	{
		unsigned short* nick_W = UTF8ToUCS2StringAlloc(params->nick);
		((peerEnumPlayersCallback)data->callback)(peer, data->success, params->roomType, params->index, nick_W, params->flags, data->callbackParam);
		gsifree(nick_W);
	}
#endif
}
typedef struct piGetPlayerInfoParams
{
	char * nick;
	unsigned int IP;
	int profileID;
} piGetPlayerInfoParams;
static PEERBool piGetPlayerInfoCopy(void * paramsOut_, void * paramsIn_)
{
	piGetPlayerInfoParams * paramsOut = (piGetPlayerInfoParams *)paramsOut_;
	piGetPlayerInfoParams * paramsIn = (piGetPlayerInfoParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	if(paramsIn->nick)
	{
		paramsOut->nick = goastrdup(paramsIn->nick);
		if(!paramsOut->nick)
			return PEERFalse;
	}
	else
		paramsOut->nick = NULL;
	paramsOut->IP = paramsIn->IP;
	paramsOut->profileID = paramsIn->profileID;
	
	return PEERTrue;
}
static void piGetPlayerInfoFree(void * params_)
{
	piGetPlayerInfoParams * params = (piGetPlayerInfoParams *)params_;

	assert(params);

	gsifree(params->nick);
}
static void piGetPlayerInfoCall(PEER peer, piCallbackData * data)
{
	piGetPlayerInfoParams * params;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_GET_PLAYER_INFO_CALLBACK);
	
	params = data->params;
#ifndef GSI_UNICODE
	((peerGetPlayerInfoCallback)data->callback)(peer, data->success, params->nick, params->IP, params->profileID, data->callbackParam);
#else
	{
		unsigned short* nick_W = UTF8ToUCS2StringAlloc(params->nick);
		((peerGetPlayerInfoCallback)data->callback)(peer, data->success, nick_W, params->IP, params->profileID, data->callbackParam);
		gsifree(nick_W);
	}
#endif
}
typedef struct piGetPlayerProfileIDParams
{
	char * nick;
	int profileID;
} piGetPlayerProfileIDParams;
static PEERBool piGetPlayerProfileIDCopy(void * paramsOut_, void * paramsIn_)
{
	piGetPlayerProfileIDParams * paramsOut = (piGetPlayerProfileIDParams *)paramsOut_;
	piGetPlayerProfileIDParams * paramsIn = (piGetPlayerProfileIDParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	if(paramsIn->nick)
	{
		paramsOut->nick = goastrdup(paramsIn->nick);
		if(!paramsOut->nick)
			return PEERFalse;
	}
	else
		paramsOut->nick = NULL;
	paramsOut->profileID = paramsIn->profileID;
	
	return PEERTrue;
}
static void piGetPlayerProfileIDFree(void * params_)
{
	piGetPlayerProfileIDParams * params = (piGetPlayerProfileIDParams *)params_;

	assert(params);

	gsifree(params->nick);
}
static void piGetPlayerProfileIDCall(PEER peer, piCallbackData * data)
{
	piGetPlayerProfileIDParams * params;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_GET_PLAYER_PROFILE_ID_CALLBACK);
	
	params = data->params;
#ifndef GSI_UNICODE
	((peerGetPlayerProfileIDCallback)data->callback)(peer, data->success, params->nick, params->profileID, data->callbackParam);
#else
	{
		unsigned short* nick_W = UTF8ToUCS2StringAlloc(params->nick);
		((peerGetPlayerProfileIDCallback)data->callback)(peer, data->success, nick_W, params->profileID, data->callbackParam);
		gsifree(nick_W);
	}
#endif
}
typedef struct piGetPlayerIPParams
{
	char * nick;
	unsigned int IP;
} piGetPlayerIPParams;
static PEERBool piGetPlayerIPCopy(void * paramsOut_, void * paramsIn_)
{
	piGetPlayerIPParams * paramsOut = (piGetPlayerIPParams *)paramsOut_;
	piGetPlayerIPParams * paramsIn = (piGetPlayerIPParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	paramsOut->IP = paramsIn->IP;
	if(paramsIn->nick)
	{
		paramsOut->nick = goastrdup(paramsIn->nick);
		if(!paramsOut->nick)
			return PEERFalse;
	}
	else
		paramsOut->nick = NULL;
	
	return PEERTrue;
}
static void piGetPlayerIPFree(void * params_)
{
	piGetPlayerIPParams * params = (piGetPlayerIPParams *)params_;

	assert(params);

	gsifree(params->nick);
}
static void piGetPlayerIPCall(PEER peer, piCallbackData * data)
{
	piGetPlayerIPParams * params;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_GET_PLAYER_IP_CALLBACK);
	
	params = data->params;
#ifndef GSI_UNICODE
	((peerGetPlayerIPCallback)data->callback)(peer, data->success, params->nick, params->IP, data->callbackParam);
#else
	{
		unsigned short* nick_W = UTF8ToUCS2StringAlloc(params->nick);
		((peerGetPlayerIPCallback)data->callback)(peer, data->success, nick_W, params->IP, data->callbackParam);
		gsifree(nick_W);
	}
#endif
}
typedef struct piRoomMessageParams
{
	RoomType roomType;
	char * nick;
	char * message;
	MessageType messageType;
} piRoomMessageParams;
static PEERBool piRoomMessageCopy(void * paramsOut_, void * paramsIn_)
{
	piRoomMessageParams * paramsOut = (piRoomMessageParams *)paramsOut_;
	piRoomMessageParams * paramsIn = (piRoomMessageParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	paramsOut->roomType = paramsIn->roomType;
	paramsOut->messageType = paramsIn->messageType;
	if(paramsIn->nick)
	{
		paramsOut->nick = goastrdup(paramsIn->nick);
		if(!paramsOut->nick)
			return PEERFalse;
	}
	else
		paramsOut->nick = NULL;
	if(paramsIn->message)
	{
		paramsOut->message = goastrdup(paramsIn->message);
		if(!paramsOut->message)
		{
			gsifree(paramsOut->nick);
			return PEERFalse;
		}
	}
	else
		paramsOut->message = NULL;
	
	return PEERTrue;
}
static void piRoomMessageFree(void * params_)
{
	piRoomMessageParams * params = (piRoomMessageParams *)params_;

	assert(params);

	gsifree(params->nick);
	gsifree(params->message);
}
static void piRoomMessageCall(PEER peer, piCallbackData * data)
{
	piRoomMessageParams * params;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_ROOM_MESSAGE_CALLBACK);
	
	params = data->params;
#ifndef GSI_UNICODE
	((peerRoomMessageCallback)data->callback)(peer, params->roomType, params->nick, params->message, params->messageType, data->callbackParam);
#else
	{
		unsigned short* nick_W = UTF8ToUCS2StringAlloc(params->nick);
		unsigned short* message_W = UTF8ToUCS2StringAlloc(params->message);

		((peerRoomMessageCallback)data->callback)(peer, params->roomType, nick_W, message_W, params->messageType, data->callbackParam);
		gsifree(nick_W);
		gsifree(message_W);
	}
#endif
}
typedef struct piRoomUTMParams
{
	RoomType roomType;
	char * nick;
	char * command;
	char * parameters;
	PEERBool authenticated;
} piRoomUTMParams;
static PEERBool piRoomUTMCopy(void * paramsOut_, void * paramsIn_)
{
	piRoomUTMParams * paramsOut = (piRoomUTMParams *)paramsOut_;
	piRoomUTMParams * paramsIn = (piRoomUTMParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	paramsOut->authenticated = paramsIn->authenticated;
	paramsOut->roomType = paramsIn->roomType;
	if(paramsIn->nick)
	{
		paramsOut->nick = goastrdup(paramsIn->nick);
		if(!paramsOut->nick)
			return PEERFalse;
	}
	else
		paramsOut->nick = NULL;
	if(paramsIn->command)
	{
		paramsOut->command = goastrdup(paramsIn->command);
		if(!paramsOut->command)
		{
			gsifree(paramsOut->nick);
			return PEERFalse;
		}
	}
	else
		paramsOut->command = NULL;
	if(paramsIn->parameters)
	{
		paramsOut->parameters = goastrdup(paramsIn->parameters);
		if(!paramsOut->parameters)
		{
			gsifree(paramsOut->nick);
			gsifree(paramsOut->command);
			return PEERFalse;
		}
	}
	else
		paramsOut->parameters = NULL;

	return PEERTrue;
}
static void piRoomUTMFree(void * params_)
{
	piRoomUTMParams * params = (piRoomUTMParams *)params_;

	assert(params);

	gsifree(params->nick);
	gsifree(params->command);
	gsifree(params->parameters);
}
static void piRoomUTMCall(PEER peer, piCallbackData * data)
{
	piRoomUTMParams * params;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_ROOM_UTM_CALLBACK);
	
	params = data->params;
#ifndef GSI_UNICODE
	((peerRoomUTMCallback)data->callback)(peer, params->roomType, params->nick, params->command, params->parameters, params->authenticated, data->callbackParam);
#else
	{
		unsigned short* nick_W = UTF8ToUCS2StringAlloc(params->nick);
		unsigned short* command_W = UTF8ToUCS2StringAlloc(params->command);
		unsigned short* parameters_W = UTF8ToUCS2StringAlloc(params->parameters);
		((peerRoomUTMCallback)data->callback)(peer, params->roomType, nick_W, command_W, parameters_W, params->authenticated, data->callbackParam);
		gsifree(nick_W);
		gsifree(command_W);
		gsifree(parameters_W);
	}
#endif
}
typedef struct piRoomNameChangedParams
{
	RoomType roomType;
} piRoomNameChangedParams;
static PEERBool piRoomNameChangedCopy(void * paramsOut_, void * paramsIn_)
{
	piRoomNameChangedParams * paramsOut = (piRoomNameChangedParams *)paramsOut_;
	piRoomNameChangedParams * paramsIn = (piRoomNameChangedParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	paramsOut->roomType = paramsIn->roomType;
	
	return PEERTrue;
}
static void piRoomNameChangedFree(void * params_)
{
	piRoomNameChangedParams * params = (piRoomNameChangedParams *)params_;

	assert(params);
	GSI_UNUSED(params);
}
static void piRoomNameChangedCall(PEER peer, piCallbackData * data)
{
	piRoomNameChangedParams * params;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_ROOM_NAME_CHANGED_CALLBACK);
	
	params = data->params;
	((peerRoomNameChangedCallback)data->callback)(peer, params->roomType, data->callbackParam);
}
typedef struct piRoomModeChangedParams
{
	RoomType roomType;
	CHATChannelMode mode;
} piRoomModeChangedParams;
static PEERBool piRoomModeChangedCopy(void * paramsOut_, void * paramsIn_)
{
	piRoomModeChangedParams * paramsOut = (piRoomModeChangedParams *)paramsOut_;
	piRoomModeChangedParams * paramsIn = (piRoomModeChangedParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	paramsOut->roomType = paramsIn->roomType;
	paramsOut->mode = paramsIn->mode;
	
	return PEERTrue;
}
static void piRoomModeChangedFree(void * params_)
{
	piRoomModeChangedParams * params = (piRoomModeChangedParams *)params_;

	assert(params);
	GSI_UNUSED(params);
}
static void piRoomModeChangedCall(PEER peer, piCallbackData * data)
{
	piRoomModeChangedParams * params;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_ROOM_MODE_CHANGED_CALLBACK);
	
	params = data->params;
	((peerRoomModeChangedCallback)data->callback)(peer, params->roomType, &params->mode, data->callbackParam);
}
typedef struct piPlayerMessageParams
{
	char * nick;
	char * message;
	MessageType messageType;
} piPlayerMessageParams;
static PEERBool piPlayerMessageCopy(void * paramsOut_, void * paramsIn_)
{
	piPlayerMessageParams * paramsOut = (piPlayerMessageParams *)paramsOut_;
	piPlayerMessageParams * paramsIn = (piPlayerMessageParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	paramsOut->messageType = paramsIn->messageType;
	if(paramsIn->nick)
	{
		paramsOut->nick = goastrdup(paramsIn->nick);
		if(!paramsOut->nick)
			return PEERFalse;
	}
	else
		paramsOut->nick = NULL;
	if(paramsIn->message)
	{
		paramsOut->message = goastrdup(paramsIn->message);
		if(!paramsOut->message)
		{
			gsifree(paramsOut->nick);
			return PEERFalse;
		}
	}
	else
		paramsOut->message = NULL;
	
	return PEERTrue;
}
static void piPlayerMessageFree(void * params_)
{
	piPlayerMessageParams * params = (piPlayerMessageParams *)params_;

	assert(params);

	gsifree(params->nick);
	gsifree(params->message);
}
static void piPlayerMessageCall(PEER peer, piCallbackData * data)
{
	piPlayerMessageParams * params;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_PLAYER_MESSAGE_CALLBACK);
	
	params = data->params;
#ifndef GSI_UNICODE
	((peerPlayerMessageCallback)data->callback)(peer, params->nick, params->message, params->messageType, data->callbackParam);
#else
	{
		unsigned short* nick_W = UTF8ToUCS2StringAlloc(params->nick);
		unsigned short* message_W = UTF8ToUCS2StringAlloc(params->message);
		((peerPlayerMessageCallback)data->callback)(peer, nick_W, message_W, params->messageType, data->callbackParam);
		gsifree(nick_W);
		gsifree(message_W);
	}
#endif
}
typedef struct piPlayerUTMParams
{
	char * nick;
	char * command;
	char * parameters;
	PEERBool authenticated;
} piPlayerUTMParams;
static PEERBool piPlayerUTMCopy(void * paramsOut_, void * paramsIn_)
{
	piPlayerUTMParams * paramsOut = (piPlayerUTMParams *)paramsOut_;
	piPlayerUTMParams * paramsIn = (piPlayerUTMParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	paramsOut->authenticated = paramsIn->authenticated;
	if(paramsIn->nick)
	{
		paramsOut->nick = goastrdup(paramsIn->nick);
		if(!paramsOut->nick)
			return PEERFalse;
	}
	else
		paramsOut->nick = NULL;
	if(paramsIn->command)
	{
		paramsOut->command = goastrdup(paramsIn->command);
		if(!paramsOut->command)
		{
			gsifree(paramsOut->nick);
			return PEERFalse;
		}
	}
	else
		paramsOut->command = NULL;
	if(paramsIn->parameters)
	{
		paramsOut->parameters = goastrdup(paramsIn->parameters);
		if(!paramsOut->parameters)
		{
			gsifree(paramsOut->nick);
			gsifree(paramsOut->command);
			return PEERFalse;
		}
	}
	else
		paramsOut->parameters = NULL;

	return PEERTrue;
}
static void piPlayerUTMFree(void * params_)
{
	piPlayerUTMParams * params = (piPlayerUTMParams *)params_;

	assert(params);

	gsifree(params->nick);
	gsifree(params->command);
	gsifree(params->parameters);
}
static void piPlayerUTMCall(PEER peer, piCallbackData * data)
{
	piPlayerUTMParams * params;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_PLAYER_UTM_CALLBACK);
	
	params = data->params;
#ifndef GSI_UNICODE
	((peerPlayerUTMCallback)data->callback)(peer, params->nick, params->command, params->parameters, params->authenticated, data->callbackParam);
#else
	{
		unsigned short* nick_W = UTF8ToUCS2StringAlloc(params->nick);
		unsigned short* command_W = UTF8ToUCS2StringAlloc(params->command);
		unsigned short* parameters_W = UTF8ToUCS2StringAlloc(params->parameters);
		((peerPlayerUTMCallback)data->callback)(peer, nick_W, command_W, parameters_W, params->authenticated, data->callbackParam);
		gsifree(nick_W);
		gsifree(command_W);
		gsifree(parameters_W);
	}
#endif
}
typedef struct piReadyChangedParams
{
	char * nick;
	PEERBool ready;
} piReadyChangedParams;
static PEERBool piReadyChangedCopy(void * paramsOut_, void * paramsIn_)
{
	piReadyChangedParams * paramsOut = (piReadyChangedParams *)paramsOut_;
	piReadyChangedParams * paramsIn = (piReadyChangedParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	if(paramsIn->nick)
	{
		paramsOut->nick = goastrdup(paramsIn->nick);
		if(!paramsOut->nick)
			return PEERFalse;
	}
	else
		paramsOut->nick = NULL;
	paramsOut->ready = paramsIn->ready;
	
	return PEERTrue;
}
static void piReadyChangedFree(void * params_)
{
	piReadyChangedParams * params = (piReadyChangedParams *)params_;

	assert(params);

	gsifree(params->nick);
}
static void piReadyChangedCall(PEER peer, piCallbackData * data)
{
	piReadyChangedParams * params;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_READY_CHANGED_CALLBACK);

	params = data->params;
#ifndef GSI_UNICODE
	((peerReadyChangedCallback)data->callback)(peer, params->nick, params->ready, data->callbackParam);
#else
	{
		unsigned short* nick_W = UTF8ToUCS2StringAlloc(params->nick);
		((peerReadyChangedCallback)data->callback)(peer, nick_W, params->ready, data->callbackParam);
		gsifree(nick_W);
	}
#endif
}
typedef struct piGameStartedParams
{
	SBServer server;
	char * message;
} piGameStartedParams;
static PEERBool piGameStartedCopy(void * paramsOut_, void * paramsIn_)
{
	piGameStartedParams * paramsOut = (piGameStartedParams *)paramsOut_;
	piGameStartedParams * paramsIn = (piGameStartedParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	paramsOut->server = paramsIn->server;
	if(paramsIn->message)
	{
		paramsOut->message = goastrdup(paramsIn->message);
		if(!paramsOut->message)
			return PEERFalse;
	}
	else
		paramsOut->message = NULL;
	
	return PEERTrue;
}
static void piGameStartedFree(void * params_)
{
	piGameStartedParams * params = (piGameStartedParams *)params_;

	assert(params);

	gsifree(params->message);
}
static void piGameStartedCall(PEER peer, piCallbackData * data)
{
	piGameStartedParams * params;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_GAME_STARTED_CALLBACK);

	params = data->params;
#ifndef GSI_UNICODE
	((peerGameStartedCallback)data->callback)(peer, params->server, params->message, data->callbackParam);
#else
	{
		unsigned short* message_W = UTF8ToUCS2StringAlloc(params->message);
		((peerGameStartedCallback)data->callback)(peer, params->server, message_W, data->callbackParam);
		gsifree(message_W);
		}
#endif
}
typedef struct piPlayerJoinedParams
{
	RoomType roomType;
	char * nick;
} piPlayerJoinedParams;
static PEERBool piPlayerJoinedCopy(void * paramsOut_, void * paramsIn_)
{
	piPlayerJoinedParams * paramsOut = (piPlayerJoinedParams *)paramsOut_;
	piPlayerJoinedParams * paramsIn = (piPlayerJoinedParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	paramsOut->roomType = paramsIn->roomType;
	if(paramsIn->nick)
	{
		paramsOut->nick = goastrdup(paramsIn->nick);
		if(!paramsOut->nick)
			return PEERFalse;
	}
	else
		paramsOut->nick = NULL;
	
	return PEERTrue;
}
static void piPlayerJoinedFree(void * params_)
{
	piPlayerJoinedParams * params = (piPlayerJoinedParams *)params_;

	assert(params);

	gsifree(params->nick);
}
static void piPlayerJoinedCall(PEER peer, piCallbackData * data)
{
	piPlayerJoinedParams * params;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_PLAYER_JOINED_CALLBACK);

	params = data->params;
#ifndef GSI_UNICODE
	((peerPlayerJoinedCallback)data->callback)(peer, params->roomType, params->nick, data->callbackParam);
#else
	{
		unsigned short* nick_W = UTF8ToUCS2StringAlloc(params->nick);
		((peerPlayerJoinedCallback)data->callback)(peer, params->roomType, nick_W, data->callbackParam);
		gsifree(nick_W);
	}
#endif
}
typedef struct piPlayerLeftParams
{
	RoomType roomType;
	char * nick;
	char * reason;
} piPlayerLeftParams;
static PEERBool piPlayerLeftCopy(void * paramsOut_, void * paramsIn_)
{
	piPlayerLeftParams * paramsOut = (piPlayerLeftParams *)paramsOut_;
	piPlayerLeftParams * paramsIn = (piPlayerLeftParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	paramsOut->roomType = paramsIn->roomType;
	if(paramsIn->nick)
	{
		paramsOut->nick = goastrdup(paramsIn->nick);
		if(!paramsOut->nick)
			return PEERFalse;
	}
	else
		paramsOut->nick = NULL;
	if(paramsIn->reason)
	{
		paramsOut->reason = goastrdup(paramsIn->reason);
		if(!paramsOut->reason)
		{
			gsifree(paramsOut->nick);
			return PEERFalse;
		}
	}
	else
		paramsOut->reason = NULL;
	
	return PEERTrue;
}
static void piPlayerLeftFree(void * params_)
{
	piPlayerLeftParams * params = (piPlayerLeftParams *)params_;

	assert(params);

	gsifree(params->nick);
	gsifree(params->reason);
}
static void piPlayerLeftCall(PEER peer, piCallbackData * data)
{
	piPlayerLeftParams * params;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_PLAYER_LEFT_CALLBACK);

	params = data->params;
#ifndef GSI_UNICODE
	((peerPlayerLeftCallback)data->callback)(peer, params->roomType, params->nick, params->reason, data->callbackParam);
#else
	{
		unsigned short* nick_W = UTF8ToUCS2StringAlloc(params->nick);
		unsigned short* reason_W = UTF8ToUCS2StringAlloc(params->reason);
		((peerPlayerLeftCallback)data->callback)(peer, params->roomType, nick_W, reason_W, data->callbackParam);
		gsifree(nick_W);
		gsifree(reason_W);
	}
#endif
}
typedef struct piKickedParams
{
	RoomType roomType;
	char * nick;
	char * reason;
} piKickedParams;
static PEERBool piKickedCopy(void * paramsOut_, void * paramsIn_)
{
	piKickedParams * paramsOut = (piKickedParams *)paramsOut_;
	piKickedParams * paramsIn = (piKickedParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	paramsOut->roomType = paramsIn->roomType;
	if(paramsIn->nick)
	{
		paramsOut->nick = goastrdup(paramsIn->nick);
		if(!paramsOut->nick)
			return PEERFalse;
	}
	else
		paramsOut->nick = NULL;
	if(paramsIn->reason)
	{
		paramsOut->reason = goastrdup(paramsIn->reason);
		if(!paramsOut->reason)
		{
			gsifree(paramsOut->nick);
			return PEERFalse;
		}
	}
	else
		paramsOut->reason = NULL;
	
	return PEERTrue;
}
static void piKickedFree(void * params_)
{
	piKickedParams * params = (piKickedParams *)params_;

	assert(params);

	gsifree(params->nick);
	gsifree(params->reason);
}
static void piKickedCall(PEER peer, piCallbackData * data)
{
	piKickedParams * params;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_KICKED_CALLBACK);

	params = data->params;
#ifndef GSI_UNICODE
	((peerKickedCallback)data->callback)(peer, params->roomType, params->nick, params->reason, data->callbackParam);
#else
	{
		unsigned short* nick_W = UTF8ToUCS2StringAlloc(params->nick);
		unsigned short* reason_W = UTF8ToUCS2StringAlloc(params->reason);
		((peerKickedCallback)data->callback)(peer, params->roomType, nick_W, reason_W, data->callbackParam);
		gsifree(nick_W);
		gsifree(reason_W);
	}
#endif
}
typedef struct piNewPlayerListParams
{
	RoomType roomType;
} piNewPlayerListParams;
static PEERBool piNewPlayerListCopy(void * paramsOut_, void * paramsIn_)
{
	piNewPlayerListParams * paramsOut = (piNewPlayerListParams *)paramsOut_;
	piNewPlayerListParams * paramsIn = (piNewPlayerListParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	paramsOut->roomType = paramsIn->roomType;

	return PEERTrue;
}
static void piNewPlayerListFree(void * params_)
{
	piNewPlayerListParams * params = (piNewPlayerListParams *)params_;

	assert(params);
	GSI_UNUSED(params);
}
static void piNewPlayerListCall(PEER peer, piCallbackData * data)
{
	piNewPlayerListParams * params;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_NEW_PLAYER_LIST_CALLBACK);

	params = data->params;
	((peerNewPlayerListCallback)data->callback)(peer, params->roomType, data->callbackParam);
}
typedef struct piPlayerChangedNickParams
{
	RoomType roomType;
	char * oldNick;
	char * newNick;
} piPlayerChangedNickParams;
static PEERBool piPlayerChangedNickCopy(void * paramsOut_, void * paramsIn_)
{
	piPlayerChangedNickParams * paramsOut = (piPlayerChangedNickParams *)paramsOut_;
	piPlayerChangedNickParams * paramsIn = (piPlayerChangedNickParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	paramsOut->roomType = paramsIn->roomType;
	if(paramsIn->oldNick)
	{
		paramsOut->oldNick = goastrdup(paramsIn->oldNick);
		if(!paramsOut->oldNick)
			return PEERFalse;
	}
	else
		paramsOut->oldNick = NULL;
	if(paramsIn->newNick)
	{
		paramsOut->newNick = goastrdup(paramsIn->newNick);
		if(!paramsOut->newNick)
		{
			gsifree(paramsOut->oldNick);
			return PEERFalse;
		}
	}
	else
		paramsOut->newNick = NULL;
	
	return PEERTrue;
}
static void piPlayerChangedNickFree(void * params_)
{
	piPlayerChangedNickParams * params = (piPlayerChangedNickParams *)params_;

	assert(params);

	gsifree(params->oldNick);
	gsifree(params->newNick);
}
static void piPlayerChangedNickCall(PEER peer, piCallbackData * data)
{
	piPlayerChangedNickParams * params;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_PLAYER_CHANGED_NICK_CALLBACK);

	params = data->params;
#ifndef GSI_UNICODE
	((peerPlayerChangedNickCallback)data->callback)(peer, params->roomType, params->oldNick, params->newNick, data->callbackParam);
#else
	{
		unsigned short* oldNick_W = UTF8ToUCS2StringAlloc(params->oldNick);
		unsigned short* newNick_W = UTF8ToUCS2StringAlloc(params->newNick);
		((peerPlayerChangedNickCallback)data->callback)(peer, params->roomType, oldNick_W, newNick_W, data->callbackParam);
		gsifree(oldNick_W);
		gsifree(newNick_W);
	}
#endif
}
typedef struct piPlayerInfoParams
{
	RoomType roomType;
	char * nick;
	unsigned int IP;
	int profileID;
} piPlayerInfoParams;
static PEERBool piPlayerInfoCopy(void * paramsOut_, void * paramsIn_)
{
	piPlayerInfoParams * paramsOut = (piPlayerInfoParams *)paramsOut_;
	piPlayerInfoParams * paramsIn = (piPlayerInfoParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	paramsOut->roomType = paramsIn->roomType;
	if(paramsIn->nick)
	{
		paramsOut->nick = goastrdup(paramsIn->nick);
		if(!paramsOut->nick)
			return PEERFalse;
	}
	else
		paramsOut->nick = NULL;
	paramsOut->IP = paramsIn->IP;
	paramsOut->profileID = paramsIn->profileID;
	
	return PEERTrue;
}
static void piPlayerInfoFree(void * params_)
{
	piPlayerInfoParams * params = (piPlayerInfoParams *)params_;

	assert(params);

	gsifree(params->nick);
}
static void piPlayerInfoCall(PEER peer, piCallbackData * data)
{
	piPlayerInfoParams * params;
	PEER_CONNECTION;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_PLAYER_INFO_CALLBACK);

	params = data->params;

	// Don't call this if we're not in the room anymore.
	////////////////////////////////////////////////////
	if(!connection->inRoom[params->roomType])
		return;

#ifndef GSI_UNICODE
	((peerPlayerInfoCallback)data->callback)(peer, params->roomType, params->nick, params->IP, params->profileID, data->callbackParam);
#else
	{
		unsigned short* nick_W = UTF8ToUCS2StringAlloc(params->nick);
		((peerPlayerInfoCallback)data->callback)(peer, params->roomType, nick_W, params->IP, params->profileID, data->callbackParam);
		gsifree(nick_W);
		}
#endif
}
typedef struct piDisconnectedParams
{
	char * reason;
} piDisconnectedParams;
static PEERBool piDisconnectedCopy(void * paramsOut_, void * paramsIn_)
{
	piDisconnectedParams * paramsOut = (piDisconnectedParams *)paramsOut_;
	piDisconnectedParams * paramsIn = (piDisconnectedParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	if(paramsIn->reason)
	{
		paramsOut->reason = goastrdup(paramsIn->reason);
		if(!paramsOut->reason)
			return PEERFalse;
	}
	else
		paramsOut->reason = NULL;
	
	return PEERTrue;
}
static void piDisconnectedFree(void * params_)
{
	piDisconnectedParams * params = (piDisconnectedParams *)params_;

	assert(params);

	gsifree(params->reason);
}
static void piDisconnectedCall(PEER peer, piCallbackData * data)
{
	piDisconnectedParams * params;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_DISCONNECTED_CALLBACK);

	params = data->params;
#ifndef GSI_UNICODE
	((peerDisconnectedCallback)data->callback)(peer, params->reason, data->callbackParam);
#else
	{
		unsigned short* reason_W = UTF8ToUCS2StringAlloc(params->reason);
		((peerDisconnectedCallback)data->callback)(peer, reason_W, data->callbackParam);
		gsifree(reason_W);
		}
#endif
}
typedef struct piPingParams
{
	char * nick;
	int ping;
} piPingParams;
static PEERBool piPingCopy(void * paramsOut_, void * paramsIn_)
{
	piPingParams * paramsOut = (piPingParams *)paramsOut_;
	piPingParams * paramsIn = (piPingParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	paramsOut->ping = paramsIn->ping;
	if(paramsIn->nick)
	{
		paramsOut->nick = goastrdup(paramsIn->nick);
		if(!paramsOut->nick)
			return PEERFalse;
	}
	else
		paramsOut->nick = NULL;
	
	return PEERTrue;
}
static void piPingFree(void * params_)
{
	piPingParams * params = (piPingParams *)params_;

	assert(params);

	gsifree(params->nick);
}
static void piPingCall(PEER peer, piCallbackData * data)
{
	piPingParams * params;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_PING_CALLBACK);

	params = data->params;
#ifndef GSI_UNICODE
	((peerPingCallback)data->callback)(peer, params->nick, params->ping, data->callbackParam);
#else
	{
		unsigned short* nick_W = UTF8ToUCS2StringAlloc(params->nick);
		((peerPingCallback)data->callback)(peer, nick_W, params->ping, data->callbackParam);
		gsifree(nick_W);
		}
#endif
}
typedef struct piCrossPingParams
{
	char * nick1;
	char * nick2;
	int crossPing;
} piCrossPingParams;
static PEERBool piCrossPingCopy(void * paramsOut_, void * paramsIn_)
{
	piCrossPingParams * paramsOut = (piCrossPingParams *)paramsOut_;
	piCrossPingParams * paramsIn = (piCrossPingParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	paramsOut->crossPing = paramsIn->crossPing;
	if(paramsIn->nick1)
	{
		paramsOut->nick1 = goastrdup(paramsIn->nick1);
		if(!paramsOut->nick1)
			return PEERFalse;
	}
	else
		paramsOut->nick1 = NULL;
	if(paramsIn->nick2)
	{
		paramsOut->nick2 = goastrdup(paramsIn->nick2);
		if(!paramsOut->nick2)
		{
			gsifree(paramsOut->nick1);
			return PEERFalse;
		}
	}
	else
		paramsOut->nick2 = NULL;
	
	return PEERTrue;
}
static void piCrossPingFree(void * params_)
{
	piCrossPingParams * params = (piCrossPingParams *)params_;

	assert(params);

	gsifree(params->nick1);
	gsifree(params->nick2);
}
static void piCrossPingCall(PEER peer, piCallbackData * data)
{
	piCrossPingParams * params;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_CROSS_PING_CALLBACK);

	params = data->params;
#ifndef GSI_UNICODE
	((peerCrossPingCallback)data->callback)(peer, params->nick1, params->nick2, params->crossPing, data->callbackParam);
#else
	{
		unsigned short* nick1_W = UTF8ToUCS2StringAlloc(params->nick1);
		unsigned short* nick2_W = UTF8ToUCS2StringAlloc(params->nick2);
		((peerCrossPingCallback)data->callback)(peer, nick1_W, nick2_W, params->crossPing, data->callbackParam);
		gsifree(nick1_W);
		gsifree(nick2_W);
	}
#endif
}
typedef struct piChangeNickParams
{
	char * oldNick;
	char * newNick;
} piChangeNickParams;
static PEERBool piChangeNickCopy(void * paramsOut_, void * paramsIn_)
{
	piChangeNickParams * paramsOut = (piChangeNickParams *)paramsOut_;
	piChangeNickParams * paramsIn = (piChangeNickParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	if(paramsIn->newNick)
	{
		paramsOut->newNick = goastrdup(paramsIn->newNick);
		if(!paramsOut->newNick)
			return PEERFalse;
	}
	else
		paramsOut->newNick = NULL;
	if(paramsIn->oldNick)
	{
		paramsOut->oldNick = goastrdup(paramsIn->oldNick);
		if(!paramsOut->oldNick)
		{
			gsifree(paramsOut->newNick);
			return PEERFalse;
		}
	}
	else
		paramsOut->oldNick = NULL;

	return PEERTrue;
}
static void piChangeNickFree(void * params_)
{
	piChangeNickParams * params = (piChangeNickParams *)params_;

	assert(params);

	gsifree(params->newNick);
	gsifree(params->oldNick);
}
static void piChangeNickCall(PEER peer, piCallbackData * data)
{
	piChangeNickParams * params;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_CHANGE_NICK_CALLBACK);
	
	params = data->params;
#ifndef GSI_UNICODE
	((peerChangeNickCallback)data->callback)(peer, data->success, params->oldNick, params->newNick, data->callbackParam);
#else
	{
		unsigned short* oldNick_W = UTF8ToUCS2StringAlloc(params->oldNick);
		unsigned short* newNick_W = UTF8ToUCS2StringAlloc(params->newNick);
		((peerChangeNickCallback)data->callback)(peer, data->success, oldNick_W, newNick_W, data->callbackParam);
		gsifree(oldNick_W);
		gsifree(newNick_W);
	}
#endif
}
typedef struct piGlobalGlobalKeyChangedParams
{
	RoomType roomType;
	char * nick;
	char * key;
	char * value;
} piGlobalKeyChangedParams;
static PEERBool piGlobalKeyChangedCopy(void * paramsOut_, void * paramsIn_)
{
	piGlobalKeyChangedParams * paramsOut = (piGlobalKeyChangedParams *)paramsOut_;
	piGlobalKeyChangedParams * paramsIn = (piGlobalKeyChangedParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	paramsOut->roomType = paramsIn->roomType;
	if(paramsIn->nick)
	{
		paramsOut->nick = goastrdup(paramsIn->nick);
		if(!paramsOut->nick)
			return PEERFalse;
	}
	else
		paramsOut->nick = NULL;
	if(paramsIn->key)
	{
		paramsOut->key = goastrdup(paramsIn->key);
		if(!paramsOut->key)
		{
			gsifree(paramsOut->nick);
			return PEERFalse;
		}
	}
	else
		paramsOut->key = NULL;
	if(paramsIn->value)
	{
		paramsOut->value = goastrdup(paramsIn->value);
		if(!paramsOut->value)
		{
			gsifree(paramsOut->nick);
			gsifree(paramsOut->key);
			return PEERFalse;
		}
	}
	else
		paramsOut->value = NULL;
	
	return PEERTrue;
}
static void piGlobalKeyChangedFree(void * params_)
{
	piGlobalKeyChangedParams * params = (piGlobalKeyChangedParams *)params_;

	assert(params);

	gsifree(params->nick);
	gsifree(params->key);
	gsifree(params->value);
}
static void piGlobalKeyChangedCall(PEER peer, piCallbackData * data)
{
	piGlobalKeyChangedParams * params;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_GLOBAL_KEY_CHANGED_CALLBACK);

	params = data->params;
#ifndef GSI_UNICODE
	((peerGlobalKeyChangedCallback)data->callback)(peer, params->nick, params->key, params->value, data->callbackParam);
#else
	{
		unsigned short* nick_W = UTF8ToUCS2StringAlloc(params->nick);
		unsigned short* key_W = UTF8ToUCS2StringAlloc(params->key);
		unsigned short* value_W = UTF8ToUCS2StringAlloc(params->value);
		((peerGlobalKeyChangedCallback)data->callback)(peer, nick_W, key_W, value_W, data->callbackParam);
		gsifree(nick_W);
		gsifree(key_W);
		gsifree(value_W);
	}
#endif
}
typedef struct piRoomKeyChangedParams
{
	RoomType roomType;
	char * nick;
	char * key;
	char * value;
} piRoomKeyChangedParams;
static PEERBool piRoomKeyChangedCopy(void * paramsOut_, void * paramsIn_)
{
	piRoomKeyChangedParams * paramsOut = (piRoomKeyChangedParams *)paramsOut_;
	piRoomKeyChangedParams * paramsIn = (piRoomKeyChangedParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	paramsOut->roomType = paramsIn->roomType;
	if(paramsIn->nick)
	{
		paramsOut->nick = goastrdup(paramsIn->nick);
		if(!paramsOut->nick)
			return PEERFalse;
	}
	else
		paramsOut->nick = NULL;
	if(paramsIn->key)
	{
		paramsOut->key = goastrdup(paramsIn->key);
		if(!paramsOut->key)
		{
			gsifree(paramsOut->nick);
			return PEERFalse;
		}
	}
	else
		paramsOut->key = NULL;
	if(paramsIn->value)
	{
		paramsOut->value = goastrdup(paramsIn->value);
		if(!paramsOut->value)
		{
			gsifree(paramsOut->nick);
			gsifree(paramsOut->key);
			return PEERFalse;
		}
	}
	else
		paramsOut->value = NULL;
	
	return PEERTrue;
}
static void piRoomKeyChangedFree(void * params_)
{
	piRoomKeyChangedParams * params = (piRoomKeyChangedParams *)params_;

	assert(params);

	gsifree(params->nick);
	gsifree(params->key);
	gsifree(params->value);
}
static void piRoomKeyChangedCall(PEER peer, piCallbackData * data)
{
	piRoomKeyChangedParams * params;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_ROOM_KEY_CHANGED_CALLBACK);

	params = data->params;
#ifndef GSI_UNICODE
	((peerRoomKeyChangedCallback)data->callback)(peer, params->roomType, params->nick, params->key, params->value, data->callbackParam);
#else
	{
		unsigned short* nick_W = UTF8ToUCS2StringAlloc(params->nick);
		unsigned short* key_W = UTF8ToUCS2StringAlloc(params->key);
		unsigned short* value_W = UTF8ToUCS2StringAlloc(params->value);
		((peerRoomKeyChangedCallback)data->callback)(peer, params->roomType, nick_W, key_W, value_W, data->callbackParam);
		gsifree(nick_W);
		gsifree(key_W);
		gsifree(value_W);
	}
#endif
}
typedef struct piGetGlobalKeysParams
{
	char * nick;
	int num;
	char ** keys;
	char ** values;
} piGetGlobalKeysParams;
static PEERBool piGetGlobalKeysCopy(void * paramsOut_, void * paramsIn_)
{
	int i;
	int num;
	PEERBool success = PEERTrue;
	piGetGlobalKeysParams * paramsOut = (piGetGlobalKeysParams *)paramsOut_;
	piGetGlobalKeysParams * paramsIn = (piGetGlobalKeysParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	memset(paramsOut, 0, sizeof(piGetGlobalKeysParams));
	num = paramsOut->num = paramsIn->num;

	if(paramsIn->nick)
	{
		paramsOut->nick = goastrdup(paramsIn->nick);
		if(!paramsOut->nick)
			success = PEERFalse;
	}
	else
		paramsOut->nick = NULL;

	if(success && num)
	{
		paramsOut->keys = (char **)gsimalloc(sizeof(char *) * num);
		if(!paramsOut->keys)
			success = PEERFalse;
		else
			memset(paramsOut->keys, 0, sizeof(char *) * num);
	}

	if(success && num && paramsIn->values)
	{
		paramsOut->values = (char **)gsimalloc(sizeof(char *) * num);
		if(!paramsOut->values)
			success = PEERFalse;
		else
			memset(paramsOut->values, 0, sizeof(char *) * num);
	}

	if(success && num && paramsIn->values)
	{
		for(i = 0 ; success && (i < num) ; i++)
		{
			paramsOut->keys[i] = goastrdup(paramsIn->keys[i]);
			if(!paramsOut->keys[i])
				success = PEERFalse;
			else
			{
				paramsOut->values[i] = goastrdup(paramsIn->values[i]);
				if(!paramsOut->values[i])
					success = PEERFalse;
			}
		}
	}

	if(!success)
	{
		gsifree(paramsOut->nick);
		for(i = 0 ; i < num ; i++)
		{
			if(paramsOut->keys)
				gsifree(paramsOut->keys[i]);
			if(paramsOut->values)
				gsifree(paramsOut->values[i]);
		}
		gsifree(paramsOut->keys);
		gsifree(paramsOut->values);
	}

	return success;
}
static void piGetGlobalKeysFree(void * params_)
{
	int i;
	piGetGlobalKeysParams * params = (piGetGlobalKeysParams *)params_;

	assert(params);

	gsifree(params->nick);
	for(i = 0 ; i < params->num ; i++)
	{
		gsifree(params->keys[i]);
		if(params->values)
			gsifree(params->values[i]);
	}
	gsifree(params->keys);
	gsifree(params->values);
}
static void piGetGlobalKeysCall(PEER peer, piCallbackData * data)
{
	piGetGlobalKeysParams * params;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_GET_GLOBAL_KEYS_CALLBACK);
	
	params = data->params;
#ifndef GSI_UNICODE
	((peerGetGlobalKeysCallback)data->callback)(peer, data->success, params->nick, params->num, (const char **)params->keys, (const char **)params->values, data->callbackParam);
#else
	{
		unsigned short* nick_W = UTF8ToUCS2StringAlloc(params->nick);
		unsigned short** keys_W = UTF8ToUCS2StringArrayAlloc((const UTF8String *)params->keys, params->num);
		unsigned short** values_W = UTF8ToUCS2StringArrayAlloc((const UTF8String *)params->values, params->num);
		int i;
		((peerGetGlobalKeysCallback)data->callback)(peer, data->success, nick_W, params->num, (const unsigned short**)keys_W, (const unsigned short**)values_W, data->callbackParam);
		gsifree(nick_W);
		for (i=0; i < params->num; i++)
		{
			gsifree(keys_W[i]);
			if (values_W != NULL) // may be a NULL when getting keys for "*"
				gsifree(values_W[i]);
		}
		gsifree(keys_W);
		gsifree(values_W);
	}
#endif
}
typedef struct piGetRoomKeysParams
{
	RoomType roomType;
	char * nick;
	int num;
	char ** keys;
	char ** values;
} piGetRoomKeysParams;
static PEERBool piGetRoomKeysCopy(void * paramsOut_, void * paramsIn_)
{
	int i;
	int num;
	PEERBool success = PEERTrue;
	piGetRoomKeysParams * paramsOut = (piGetRoomKeysParams *)paramsOut_;
	piGetRoomKeysParams * paramsIn = (piGetRoomKeysParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	memset(paramsOut, 0, sizeof(piGetRoomKeysParams));
	num = paramsOut->num = paramsIn->num;

	paramsOut->roomType = paramsIn->roomType;

	if(paramsIn->nick)
	{
		paramsOut->nick = goastrdup(paramsIn->nick);
		if(!paramsOut->nick)
			success = PEERFalse;
	}
	else
		paramsOut->nick = NULL;

	if(success && num)
	{
		paramsOut->keys = (char **)gsimalloc(sizeof(char *) * num);
		if(!paramsOut->keys)
			success = PEERFalse;
		else
			memset(paramsOut->keys, 0, sizeof(char *) * num);
	}

	if(success && num && paramsIn->values)
	{
		paramsOut->values = (char **)gsimalloc(sizeof(char *) * num);
		if(!paramsOut->values)
			success = PEERFalse;
		else
			memset(paramsOut->values, 0, sizeof(char *) * num);
	}

	if(success && num && paramsIn->values)
	{
		for(i = 0 ; success && (i < num) ; i++)
		{
			paramsOut->keys[i] = goastrdup(paramsIn->keys[i]);
			if(!paramsOut->keys[i])
				success = PEERFalse;
			else if(paramsOut->values)
			{
				paramsOut->values[i] = goastrdup(paramsIn->values[i]);
				if(!paramsOut->values[i])
					success = PEERFalse;
			}
		}
	}

	if(!success)
	{
		gsifree(paramsOut->nick);
		for(i = 0 ; i < num ; i++)
		{
			if(paramsOut->keys)
				gsifree(paramsOut->keys[i]);
			if(paramsOut->values)
				gsifree(paramsOut->values[i]);
		}
		gsifree(paramsOut->keys);
		gsifree(paramsOut->values);
	}

	return success;
}
static void piGetRoomKeysFree(void * params_)
{
	int i;
	piGetRoomKeysParams * params = (piGetRoomKeysParams *)params_;

	assert(params);

	gsifree(params->nick);
	for(i = 0 ; i < params->num ; i++)
	{
		gsifree(params->keys[i]);
		if(params->values)
			gsifree(params->values[i]);
	}
	gsifree(params->keys);
	gsifree(params->values);
}
static void piGetRoomKeysCall(PEER peer, piCallbackData * data)
{
	piGetRoomKeysParams * params;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_GET_ROOM_KEYS_CALLBACK);
	
	params = data->params;
#ifndef GSI_UNICODE
	((peerGetRoomKeysCallback)data->callback)(peer, data->success, params->roomType, params->nick, params->num, params->keys, params->values, data->callbackParam);
#else
	{
		unsigned short* nick_W = UTF8ToUCS2StringAlloc(params->nick);
		unsigned short** keys_W = UTF8ToUCS2StringArrayAlloc((const UTF8String *)params->keys, params->num);
		unsigned short** values_W = UTF8ToUCS2StringArrayAlloc((const UTF8String *)params->values, params->num);
		int i;
		((peerGetRoomKeysCallback)data->callback)(peer, data->success, params->roomType, nick_W, params->num, keys_W, values_W, data->callbackParam);
		gsifree(nick_W);
		for (i=0; i < params->num; i++)
		{
			gsifree(keys_W[i]);
			if (values_W != NULL) // may be a NULL when getting keys for "*"
				gsifree(values_W[i]);
		}
		gsifree(keys_W);
		gsifree(values_W);
	}
#endif
}
typedef struct piPlayerFlagsChangedParams
{
	RoomType roomType;
	char * nick;
	int oldFlags;
	int newFlags;
} piPlayerFlagsChangedParams;
static PEERBool piPlayerFlagsChangedCopy(void * paramsOut_, void * paramsIn_)
{
	piPlayerFlagsChangedParams * paramsOut = (piPlayerFlagsChangedParams *)paramsOut_;
	piPlayerFlagsChangedParams * paramsIn = (piPlayerFlagsChangedParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	paramsOut->roomType = paramsIn->roomType;
	paramsOut->newFlags = paramsIn->newFlags;
	paramsOut->oldFlags = paramsIn->oldFlags;
	if(paramsIn->nick)
	{
		paramsOut->nick = goastrdup(paramsIn->nick);
		if(!paramsOut->nick)
			return PEERFalse;
	}
	else
		paramsOut->nick = NULL;
	
	return PEERTrue;
}
static void piPlayerFlagsChangedFree(void * params_)
{
	piPlayerFlagsChangedParams * params = (piPlayerFlagsChangedParams *)params_;

	assert(params);

	gsifree(params->nick);
}
static void piPlayerFlagsChangedCall(PEER peer, piCallbackData * data)
{
	piPlayerFlagsChangedParams * params;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_PLAYER_FLAGS_CHANGED_CALLBACK);

	params = data->params;
#ifndef GSI_UNICODE
	((peerPlayerFlagsChangedCallback)data->callback)(peer, params->roomType, params->nick, params->oldFlags, params->newFlags, data->callbackParam);
#else
	{
		unsigned short* nick_W = UTF8ToUCS2StringAlloc(params->nick);
		((peerPlayerFlagsChangedCallback)data->callback)(peer, params->roomType, nick_W, params->oldFlags, params->newFlags, data->callbackParam);
		gsifree(nick_W);
	}
#endif
}
typedef struct piAuthenticateCDKeyParams
{
	int result;
	char * message;
} piAuthenticateCDKeyParams;
static PEERBool piAuthenticateCDKeyCopy(void * paramsOut_, void * paramsIn_)
{
	piAuthenticateCDKeyParams * paramsOut = (piAuthenticateCDKeyParams *)paramsOut_;
	piAuthenticateCDKeyParams * paramsIn = (piAuthenticateCDKeyParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	paramsOut->result = paramsIn->result;
	if(paramsIn->message)
	{
		paramsOut->message = goastrdup(paramsIn->message);
		if(!paramsOut->message)
			return PEERFalse;
	}
	else
		paramsOut->message = NULL;

	return PEERTrue;
}
static void piAuthenticateCDKeyFree(void * params_)
{
	piAuthenticateCDKeyParams * params = (piAuthenticateCDKeyParams *)params_;

	assert(params);

	gsifree(params->message);
}
static void piAuthenticateCDKeyCall(PEER peer, piCallbackData * data)
{
	piAuthenticateCDKeyParams * params;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_AUTHENTICATE_CDKEY_CALLBACK);
	
	params = data->params;
#ifndef GSI_UNICODE
	((peerAuthenticateCDKeyCallback)data->callback)(peer, params->result, params->message, data->callbackParam);
#else
	{
		unsigned short* message_W = UTF8ToUCS2StringAlloc(params->message);
		((peerAuthenticateCDKeyCallback)data->callback)(peer, params->result, message_W, data->callbackParam);
		gsifree(message_W);
	}
#endif
}
typedef struct piAutoMatchStatusParams
{
	PEERAutoMatchStatus status;
} piAutoMatchStatusParams;
static PEERBool piAutoMatchStatusCopy(void * paramsOut_, void * paramsIn_)
{
	piAutoMatchStatusParams * paramsOut = (piAutoMatchStatusParams *)paramsOut_;
	piAutoMatchStatusParams * paramsIn = (piAutoMatchStatusParams *)paramsIn_;

	assert(paramsOut);
	assert(paramsIn);

	paramsOut->status = paramsIn->status;

	return PEERTrue;
}
static void piAutoMatchStatusFree(void * params_)
{
	piAutoMatchStatusParams * params = (piAutoMatchStatusParams *)params_;

	assert(params);
	GSI_UNUSED(params);
}
static void piAutoMatchStatusCall(PEER peer, piCallbackData * data)
{
	piAutoMatchStatusParams * params;
	
	assert(data);
	assert(data->callback);
	assert(data->params);
	assert(data->type == PI_AUTO_MATCH_STATUS_CALLBACK);

	params = data->params;
	((peerAutoMatchStatusCallback)data->callback)(peer, params->status, data->callbackParam);
}

/************
** GLOBALS **
************/
static const piCallbackFuncs callbackFuncs[] =
{
	{
		PI_CONNECT_CALLBACK,
		piConnectCopy,
		piConnectFree,
		piConnectCall
	},
	{
		PI_JOIN_ROOM_CALLBACK,
		piJoinRoomCopy,
		piJoinRoomFree,
		piJoinRoomCall
	},
	{
		PI_LIST_GROUP_ROOMS_CALLBACK,
		piListGroupRoomsCopy,
		piListGroupRoomsFree,
		piListGroupRoomsCall
	},
	{
		PI_LISTING_GAMES_CALLBACK,
		piListingGamesCopy,
		piListingGamesFree,
		piListingGamesCall
	},
	{
		PI_NICK_ERROR_CALLBACK,
		piNickErrorCopy,
		piNickErrorFree,
		piNickErrorCall
	},
	{
		PI_ENUM_PLAYERS_CALLBACK,
		piEnumPlayersCopy,
		piEnumPlayersFree,
		piEnumPlayersCall
	},
	{
		PI_GET_PLAYER_INFO_CALLBACK,
		piGetPlayerInfoCopy,
		piGetPlayerInfoFree,
		piGetPlayerInfoCall
	},
	{
		PI_GET_PLAYER_PROFILE_ID_CALLBACK,
		piGetPlayerProfileIDCopy,
		piGetPlayerProfileIDFree,
		piGetPlayerProfileIDCall
	},
	{
		PI_GET_PLAYER_IP_CALLBACK,
		piGetPlayerIPCopy,
		piGetPlayerIPFree,
		piGetPlayerIPCall
	},
	{
		PI_ROOM_MESSAGE_CALLBACK,
		piRoomMessageCopy,
		piRoomMessageFree,
		piRoomMessageCall
	},
	{
		PI_ROOM_UTM_CALLBACK,
		piRoomUTMCopy,
		piRoomUTMFree,
		piRoomUTMCall
	},
	{
		PI_ROOM_NAME_CHANGED_CALLBACK,
		piRoomNameChangedCopy,
		piRoomNameChangedFree,
		piRoomNameChangedCall
	},
	{
		PI_ROOM_MODE_CHANGED_CALLBACK,
		piRoomModeChangedCopy,
		piRoomModeChangedFree,
		piRoomModeChangedCall
	},
	{
		PI_PLAYER_MESSAGE_CALLBACK,
		piPlayerMessageCopy,
		piPlayerMessageFree,
		piPlayerMessageCall
	},
	{
		PI_PLAYER_UTM_CALLBACK,
		piPlayerUTMCopy,
		piPlayerUTMFree,
		piPlayerUTMCall
	},
	{
		PI_READY_CHANGED_CALLBACK,
		piReadyChangedCopy,
		piReadyChangedFree,
		piReadyChangedCall
	},
	{
		PI_GAME_STARTED_CALLBACK,
		piGameStartedCopy,
		piGameStartedFree,
		piGameStartedCall
	},
	{
		PI_PLAYER_JOINED_CALLBACK,
		piPlayerJoinedCopy,
		piPlayerJoinedFree,
		piPlayerJoinedCall
	},
	{
		PI_PLAYER_LEFT_CALLBACK,
		piPlayerLeftCopy,
		piPlayerLeftFree,
		piPlayerLeftCall
	},
	{
		PI_KICKED_CALLBACK,
		piKickedCopy,
		piKickedFree,
		piKickedCall
	},
	{
		PI_NEW_PLAYER_LIST_CALLBACK,
		piNewPlayerListCopy,
		piNewPlayerListFree,
		piNewPlayerListCall
	},
	{
		PI_PLAYER_CHANGED_NICK_CALLBACK,
		piPlayerChangedNickCopy,
		piPlayerChangedNickFree,
		piPlayerChangedNickCall
	},
	{
		PI_PLAYER_INFO_CALLBACK,
		piPlayerInfoCopy,
		piPlayerInfoFree,
		piPlayerInfoCall
	},
	{
		PI_DISCONNECTED_CALLBACK,
		piDisconnectedCopy,
		piDisconnectedFree,
		piDisconnectedCall
	},
	{
		PI_PING_CALLBACK,
		piPingCopy,
		piPingFree,
		piPingCall
	},
	{
		PI_CROSS_PING_CALLBACK,
		piCrossPingCopy,
		piCrossPingFree,
		piCrossPingCall
	},
	{
		PI_CHANGE_NICK_CALLBACK,
		piChangeNickCopy,
		piChangeNickFree,
		piChangeNickCall
	},
	{
		PI_GLOBAL_KEY_CHANGED_CALLBACK,
		piGlobalKeyChangedCopy,
		piGlobalKeyChangedFree,
		piGlobalKeyChangedCall
	},
	{
		PI_ROOM_KEY_CHANGED_CALLBACK,
		piRoomKeyChangedCopy,
		piRoomKeyChangedFree,
		piRoomKeyChangedCall
	},
	{
		PI_GET_GLOBAL_KEYS_CALLBACK,
		piGetGlobalKeysCopy,
		piGetGlobalKeysFree,
		piGetGlobalKeysCall
	},
	{
		PI_GET_ROOM_KEYS_CALLBACK,
		piGetRoomKeysCopy,
		piGetRoomKeysFree,
		piGetRoomKeysCall
	},
	{
		PI_PLAYER_FLAGS_CHANGED_CALLBACK,
		piPlayerFlagsChangedCopy,
		piPlayerFlagsChangedFree,
		piPlayerFlagsChangedCall
	},
	{
		PI_AUTHENTICATE_CDKEY_CALLBACK,
		piAuthenticateCDKeyCopy,
		piAuthenticateCDKeyFree,
		piAuthenticateCDKeyCall
	},
	{
		PI_AUTO_MATCH_STATUS_CALLBACK,
		piAutoMatchStatusCopy,
		piAutoMatchStatusFree,
		piAutoMatchStatusCall
	},
	{
		PI_NUM_CALLBACK_TYPES,
		NULL,
		NULL,
		NULL
	}
};

/* Bodies this file emits that it does not claim.

   Six of them compile to a single `ret` -- the *Free of a params struct that
   owns no heap.  Retail has them (0x0085C620, 0x0085C670, 0x0085CE20,
   0x0085CE80, 0x0085D380, 0x0085DF00, each one byte) and this file reproduces
   them, but one byte is no evidence of anything: a bare `ret` is shared with
   every other empty function in the image, so the comparison cannot tell this
   file's from anyone else's and the row is not landed.

   _piConnectFree present-unmatched
   _piJoinRoomFree present-unmatched
   _piRoomNameChangedFree present-unmatched
   _piRoomModeChangedFree present-unmatched
   _piNewPlayerListFree present-unmatched
   _piAutoMatchStatusFree present-unmatched

   The rest are byte-exact here but already carry a ledger row pointing at
   another source, and a green build is not a licence to repoint someone else's
   claim.  Recorded rather than taken; see the report accompanying this file.
   The six 16-byte `jmp free` thunks and two 29-byte loops below are ICF folds
   the other TUs reached first; the two 18-byte copies at 0x0085CE00 and
   0x0085D360 are the interesting pair, because callbackFuncs[] puts them at
   type 11 (ROOM_NAME_CHANGED) and type 20 (NEW_PLAYER_LIST) of this table.

   _piListingGamesFree present-unmatched
   _piGetPlayerInfoFree present-unmatched
   _piGetPlayerProfileIDFree present-unmatched
   _piGetPlayerIPFree present-unmatched
   _piReadyChangedFree present-unmatched
   _piDisconnectedFree present-unmatched
   _piPlayerMessageFree present-unmatched
   _piCrossPingFree present-unmatched
   _piRoomNameChangedCopy present-unmatched
   _piNewPlayerListCopy present-unmatched
*/

/* --- the piAddCallback machinery, the half of this retail TU the first pass
       left out.  piAddCallback is static and every call site is in this file,
       so VC7.1 gives it a private register convention: `peer` arrives in EBX
       and `paramsSize` in EAX, with the remaining six arguments on the stack.
       That is not something a declaration can ask for -- it falls out of the
       function being static with all its callers visible -- and it is the one
       fact each entry point below depends on.

       The entry points are named by callbackFuncs[]: the type each one passes
       to piAddCallback indexes that table, and the table's `call` column is
       already named in this file.  Type 15 is PI_READY_CHANGED_CALLBACK, so
       the body at 0x0085E8D0 that passes 15 is piAddReadyChangedCallback. */

static int piAddCallback(PEER peer,
						 PEERBool blocking,
						 void * callback,
						 void * param,
						 piCallbackType type,
						 void * params,
						 int paramsSize,
						 int ID)
{
	piCallbackData data;
	void * paramsCopy;
	PEER_CONNECTION;

	if(!callback)
		return -1;

	paramsCopy = gsimalloc((unsigned int)paramsSize);
	if(!paramsCopy)
		return -1;
	memset(paramsCopy, 0, (unsigned int)paramsSize);

	if(!callbackFuncs[type].copy(paramsCopy, params))
	{
		gsifree(paramsCopy);
		return -1;
	}

	data.type = type;
	data.success = blocking;
	data.callback = (PEERCBType)callback;
	data.callbackParam = param;
	data.params = paramsCopy;
	data.ID = ID;
	data.inCall = PEERFalse;

	ArrayAppend(connection->callbackList, &data);
	connection->callbackListLen++;

	return data.ID;
}

void piAddConnectCallback(PEER peer, PEERBool success, int failureReason, void * callback, void * param, int ID)
{
	piConnectParams params;
	PEER_CONNECTION;

	params.failureReason = failureReason;

	piAddCallback(peer, success, callback, param, PI_CONNECT_CALLBACK,
		&params, sizeof(params), ID);
}

void piAddListGroupRoomsCallback(PEER peer, PEERBool success, int groupID, SBServer server, const char *name, int numWaiting, int maxWaiting, int numGames, int numPlaying, void * callback, void * param, int ID)
{
	piListGroupRoomsParams params;
	PEER_CONNECTION;

	params.groupID = groupID;
	params.server = server;
	params.name = (char *)name;
	params.numWaiting = numWaiting;
	params.maxWaiting = maxWaiting;
	params.numGames = numGames;
	params.numPlaying = numPlaying;

	piAddCallback(peer, success, callback, param, PI_LIST_GROUP_ROOMS_CALLBACK,
		&params, sizeof(params), ID);
}

void piAddNickErrorCallback(PEER peer, int type, const char * nick,
		int numSuggestedNicks, char ** suggestedNicks, void * param, int ID)
{
	piNickErrorParams params;
	PEER_CONNECTION;

	params.type = type;
	params.nick = (char *)nick;
	params.numSuggestedNicks = numSuggestedNicks;
	params.suggestedNicks = suggestedNicks;

	piAddCallback(peer, PEERFalse, connection->nickErrorCallback, param,
		PI_NICK_ERROR_CALLBACK, &params, sizeof(params), ID);
}

void piAddEnumPlayersCallback(PEER peer, PEERBool success, RoomType roomType, int index, const char *nick, int flags, void * callback, void * param, int ID)
{
	piEnumPlayersParams params;
	PEER_CONNECTION;

	params.roomType = roomType;
	params.index = index;
	params.nick = (char *)nick;
	params.flags = flags;

	piAddCallback(peer, success, callback, param, PI_ENUM_PLAYERS_CALLBACK,
		&params, sizeof(params), ID);
}

void piAddGetPlayerInfoCallback(PEER peer, PEERBool success, const char *nick, unsigned int IP, int profileID, void * callback, void * param, int ID)
{
	piGetPlayerInfoParams params;
	PEER_CONNECTION;

	params.nick = (char *)nick;
	params.IP = IP;
	params.profileID = profileID;

	piAddCallback(peer, success, callback, param, PI_GET_PLAYER_INFO_CALLBACK,
		&params, sizeof(params), ID);
}

void piAddGetPlayerProfileIDCallback(PEER peer, PEERBool success, const char *nick, int profileID, void * callback, void * param, int ID)
{
	piGetPlayerProfileIDParams params;
	PEER_CONNECTION;

	params.nick = (char *)nick;
	params.profileID = profileID;

	piAddCallback(peer, success, callback, param, PI_GET_PLAYER_PROFILE_ID_CALLBACK,
		&params, sizeof(params), ID);
}

void piAddGetPlayerIPCallback(PEER peer, PEERBool success, const char *nick, unsigned int IP, void * callback, void * param, int ID)
{
	piGetPlayerIPParams params;
	PEER_CONNECTION;

	params.nick = (char *)nick;
	params.IP = IP;

	piAddCallback(peer, success, callback, param, PI_GET_PLAYER_IP_CALLBACK,
		&params, sizeof(params), ID);
}
void piAddRoomMessageCallback(PEER peer, RoomType roomType, const char *nick, const char *message, MessageType messageType)
{
	piRoomMessageParams params;
	PEER_CONNECTION;

	if(!connection->callbacks.roomMessage)
		return;

	params.roomType = roomType;
	params.nick = (char *)nick;
	params.message = (char *)message;
	params.messageType = messageType;

	piAddCallback(peer, PEERTrue, connection->callbacks.roomMessage,
		connection->callbacks.param, PI_ROOM_MESSAGE_CALLBACK, &params,
		sizeof(params), -1);
}

void piAddRoomUTMCallback(PEER peer, RoomType roomType, const char *nick, const char *command, const char *parameters, PEERBool authenticated)
{
	piRoomUTMParams params;
	PEER_CONNECTION;

	if(!connection->callbacks.roomUTM)
		return;

	params.roomType = roomType;
	params.nick = (char *)nick;
	params.command = (char *)command;
	params.parameters = (char *)parameters;
	params.authenticated = authenticated;

	piAddCallback(peer, PEERTrue, connection->callbacks.roomUTM,
		connection->callbacks.param, PI_ROOM_UTM_CALLBACK, &params,
		sizeof(params), -1);
}

void piAddRoomNameChangedCallback(PEER peer, RoomType roomType)
{
	piRoomNameChangedParams params;
	PEER_CONNECTION;

	if(!connection->callbacks.roomNameChanged)
		return;

	params.roomType = roomType;

	piAddCallback(peer, PEERTrue, connection->callbacks.roomNameChanged,
		connection->callbacks.param, PI_ROOM_NAME_CHANGED_CALLBACK, &params,
		sizeof(params), -1);
}

void piAddRoomModeChangedCallback(PEER peer, RoomType roomType, CHATChannelMode * mode)
{
	piRoomModeChangedParams params;
	PEER_CONNECTION;

	if(!connection->callbacks.roomModeChanged)
		return;

	params.roomType = roomType;
	params.mode = *mode;

	piAddCallback(peer, PEERTrue, connection->callbacks.roomModeChanged,
		connection->callbacks.param, PI_ROOM_MODE_CHANGED_CALLBACK, &params,
		sizeof(params), -1);
}

void piAddPlayerMessageCallback(PEER peer, const char *nick, const char *message, MessageType messageType)
{
	piPlayerMessageParams params;
	PEER_CONNECTION;

	if(!connection->callbacks.playerMessage)
		return;

	params.nick = (char *)nick;
	params.message = (char *)message;
	params.messageType = messageType;

	piAddCallback(peer, PEERTrue, connection->callbacks.playerMessage,
		connection->callbacks.param, PI_PLAYER_MESSAGE_CALLBACK, &params,
		sizeof(params), -1);
}

void piAddPlayerUTMCallback(PEER peer, const char *nick, const char *command, const char *parameters, PEERBool authenticated)
{
	piPlayerUTMParams params;
	PEER_CONNECTION;

	if(!connection->callbacks.playerUTM)
		return;

	params.nick = (char *)nick;
	params.command = (char *)command;
	params.parameters = (char *)parameters;
	params.authenticated = authenticated;

	piAddCallback(peer, PEERTrue, connection->callbacks.playerUTM,
		connection->callbacks.param, PI_PLAYER_UTM_CALLBACK, &params,
		sizeof(params), -1);
}

void piAddReadyChangedCallback(PEER peer, const char *nick, PEERBool ready)
{
	piReadyChangedParams params;
	PEER_CONNECTION;

	if(!connection->callbacks.readyChanged)
		return;

	params.nick = (char *)nick;
	params.ready = ready;

	piAddCallback(peer, PEERTrue, connection->callbacks.readyChanged,
		connection->callbacks.param, PI_READY_CHANGED_CALLBACK, &params,
		sizeof(params), -1);
}

void piAddGameStartedCallback(PEER peer, SBServer server, const char *message)
{
	piGameStartedParams params;
	PEER_CONNECTION;

	if(!connection->callbacks.gameStarted)
		return;

	params.server = server;
	params.message = (char *)message;

	piAddCallback(peer, PEERTrue, connection->callbacks.gameStarted,
		connection->callbacks.param, PI_GAME_STARTED_CALLBACK, &params,
		sizeof(params), -1);
}

void piAddPlayerJoinedCallback(PEER peer, RoomType roomType, const char *nick)
{
	piPlayerJoinedParams params;
	PEER_CONNECTION;

	if(!connection->callbacks.playerJoined)
		return;

	params.roomType = roomType;
	params.nick = (char *)nick;

	piAddCallback(peer, PEERTrue, connection->callbacks.playerJoined,
		connection->callbacks.param, PI_PLAYER_JOINED_CALLBACK, &params,
		sizeof(params), -1);
}

void piAddPlayerLeftCallback(PEER peer, RoomType roomType, const char *nick, const char *reason)
{
	piPlayerLeftParams params;
	PEER_CONNECTION;

	if(!connection->callbacks.playerLeft)
		return;

	params.roomType = roomType;
	params.nick = (char *)nick;
	params.reason = (char *)reason;

	piAddCallback(peer, PEERTrue, connection->callbacks.playerLeft,
		connection->callbacks.param, PI_PLAYER_LEFT_CALLBACK, &params,
		sizeof(params), -1);
}

void piAddKickedCallback(PEER peer, RoomType roomType, const char *nick, const char *reason)
{
	piKickedParams params;
	PEER_CONNECTION;

	if(!connection->callbacks.kicked)
		return;

	params.roomType = roomType;
	params.nick = (char *)nick;
	params.reason = (char *)reason;

	piAddCallback(peer, PEERTrue, connection->callbacks.kicked,
		connection->callbacks.param, PI_KICKED_CALLBACK, &params,
		sizeof(params), -1);
}

void piAddNewPlayerListCallback(PEER peer, RoomType roomType)
{
	piNewPlayerListParams params;
	PEER_CONNECTION;

	if(!connection->callbacks.newPlayerList)
		return;

	params.roomType = roomType;

	piAddCallback(peer, PEERTrue, connection->callbacks.newPlayerList,
		connection->callbacks.param, PI_NEW_PLAYER_LIST_CALLBACK, &params,
		sizeof(params), -1);
}

void piAddPlayerChangedNickCallback(PEER peer, RoomType roomType, const char *oldNick, const char *newNick)
{
	piPlayerChangedNickParams params;
	PEER_CONNECTION;

	if(!connection->callbacks.playerChangedNick)
		return;

	params.roomType = roomType;
	params.oldNick = (char *)oldNick;
	params.newNick = (char *)newNick;

	piAddCallback(peer, PEERTrue, connection->callbacks.playerChangedNick,
		connection->callbacks.param, PI_PLAYER_CHANGED_NICK_CALLBACK, &params,
		sizeof(params), -1);
}

void piAddPlayerInfoCallback(PEER peer, RoomType roomType, const char *nick, unsigned int IP, int profileID)
{
	piPlayerInfoParams params;
	PEER_CONNECTION;

	if(!connection->callbacks.playerInfo)
		return;

	params.roomType = roomType;
	params.nick = (char *)nick;
	params.IP = IP;
	params.profileID = profileID;

	piAddCallback(peer, PEERTrue, connection->callbacks.playerInfo,
		connection->callbacks.param, PI_PLAYER_INFO_CALLBACK, &params,
		sizeof(params), -1);
}

void piAddDisconnectedCallback(PEER peer, const char *reason)
{
	piDisconnectedParams params;
	PEER_CONNECTION;

	if(!connection->callbacks.disconnected)
		return;

	params.reason = (char *)reason;

	piAddCallback(peer, PEERTrue, connection->callbacks.disconnected,
		connection->callbacks.param, PI_DISCONNECTED_CALLBACK, &params,
		sizeof(params), -1);
}

void piAddPingCallback(PEER peer, const char *nick, int ping)
{
	piPingParams params;
	PEER_CONNECTION;

	if(!connection->callbacks.ping)
		return;

	params.nick = (char *)nick;
	params.ping = ping;

	piAddCallback(peer, PEERTrue, connection->callbacks.ping,
		connection->callbacks.param, PI_PING_CALLBACK, &params,
		sizeof(params), -1);
}

void piAddCrossPingCallback(PEER peer, const char *nick1, const char *nick2, int crossPing)
{
	piCrossPingParams params;
	PEER_CONNECTION;

	if(!connection->callbacks.crossPing)
		return;

	params.nick1 = (char *)nick1;
	params.nick2 = (char *)nick2;
	params.crossPing = crossPing;

	piAddCallback(peer, PEERTrue, connection->callbacks.crossPing,
		connection->callbacks.param, PI_CROSS_PING_CALLBACK, &params,
		sizeof(params), -1);
}

void piAddGlobalKeyChangedCallback(PEER peer, const char *nick, const char *key, const char *value)
{
	piGlobalKeyChangedParams params;
	PEER_CONNECTION;

	if(!connection->callbacks.globalKeyChanged)
		return;

	params.nick = (char *)nick;
	params.key = (char *)key;
	params.value = (char *)value;

	piAddCallback(peer, PEERTrue, connection->callbacks.globalKeyChanged,
		connection->callbacks.param, PI_GLOBAL_KEY_CHANGED_CALLBACK, &params,
		sizeof(params), -1);
}

void piAddRoomKeyChangedCallback(PEER peer, RoomType roomType, const char *nick, const char *key, const char *value)
{
	piRoomKeyChangedParams params;
	PEER_CONNECTION;

	if(!connection->callbacks.roomKeyChanged)
		return;

	params.roomType = roomType;
	params.nick = (char *)nick;
	params.key = (char *)key;
	params.value = (char *)value;

	piAddCallback(peer, PEERTrue, connection->callbacks.roomKeyChanged,
		connection->callbacks.param, PI_ROOM_KEY_CHANGED_CALLBACK, &params,
		sizeof(params), -1);
}

void piAddPlayerFlagsChangedCallback(PEER peer, RoomType roomType, const char *nick, int oldFlags, int newFlags)
{
	piPlayerFlagsChangedParams params;
	PEER_CONNECTION;

	if(!connection->callbacks.playerFlagsChanged)
		return;

	params.roomType = roomType;
	params.nick = (char *)nick;
	params.oldFlags = oldFlags;
	params.newFlags = newFlags;

	piAddCallback(peer, PEERTrue, connection->callbacks.playerFlagsChanged,
		connection->callbacks.param, PI_PLAYER_FLAGS_CHANGED_CALLBACK, &params,
		sizeof(params), -1);
}

void piAddChangeNickCallback(PEER peer, PEERBool success, const char *oldNick, const char *newNick, void * callback, void * param, int ID)
{
	piChangeNickParams params;
	PEER_CONNECTION;

	params.newNick = (char *)newNick;
	params.oldNick = (char *)oldNick;

	piAddCallback(peer, success, callback, param, PI_CHANGE_NICK_CALLBACK,
		&params, sizeof(params), ID);
}

void piAddGetGlobalKeysCallback(PEER peer, PEERBool success, const char *nick, int num, char **keys, char **values, void * callback, void * param, int ID)
{
	piGetGlobalKeysParams params;
	PEER_CONNECTION;

	params.nick = (char *)nick;
	params.num = num;
	params.keys = keys;
	params.values = values;

	piAddCallback(peer, success, callback, param, PI_GET_GLOBAL_KEYS_CALLBACK,
		&params, sizeof(params), ID);
}

void piAddGetRoomKeysCallback(PEER peer, PEERBool success, RoomType roomType, const char *nick, int num, char **keys, char **values, void * callback, void * param, int ID)
{
	piGetRoomKeysParams params;
	PEER_CONNECTION;

	params.roomType = roomType;
	params.nick = (char *)nick;
	params.num = num;
	params.keys = keys;
	params.values = values;

	piAddCallback(peer, success, callback, param, PI_GET_ROOM_KEYS_CALLBACK,
		&params, sizeof(params), ID);
}

void piAddAuthenticateCDKeyCallback(PEER peer, int result, const char * message,
		void * callback, void * param, int ID)
{
	piAuthenticateCDKeyParams params;
	PEER_CONNECTION;

	params.result = result;
	params.message = (char *)message;

	piAddCallback(peer, PEERTrue, callback, param, PI_AUTHENTICATE_CDKEY_CALLBACK,
		&params, sizeof(params), ID);
}

void piAddAutoMatchStatusCallback(PEER peer)
{
	piAutoMatchStatusParams params;
	piOperation * operation;
	PEER_CONNECTION;

	operation = connection->autoMatchOperation;
	if(!operation)
		return;

	if(!operation->callback)
		return;

	params.status = (PEERAutoMatchStatus)connection->autoMatchStatus;

	piAddCallback(peer, PEERTrue, operation->callback, operation->param,
		PI_AUTO_MATCH_STATUS_CALLBACK, &params, sizeof(params), operation->ID);
}

void piAddJoinRoomCallback(PEER peer, PEERBool success, PEERJoinResult result,
		RoomType roomType, peerJoinRoomCallback callback, void * param, int ID)
{
	piJoinRoomParams params;
	PEER_CONNECTION;

	/* an auto-match staging join is reported straight to the caller. */
	if(peerIsAutoMatching(peer) && (roomType == StagingRoom))
	{
		callback(peer, success, result, StagingRoom, param);
		return;
	}

	params.result = result;
	params.roomType = roomType;

	piAddCallback(peer, success, callback, param, PI_JOIN_ROOM_CALLBACK,
		&params, sizeof(params), ID);
}

/* The callback list's own lifecycle.  ArrayNew's element size settles the
   element type without any help: 0x1c is sizeof(piCallbackData), the layout
   the *Call trampolines in this file were already read against.  And the free
   callback proves the table column: it indexes callbackFuncs[] at +8, the
   third of the four members, which is the one this file spells gsifree. */

static void piCallbackFree(void * elem)
{
	piCallbackData * data = (piCallbackData *)elem;

	callbackFuncs[data->type].gsifree(data->params);
	gsifree(data->params);
}

PEERBool piCallbacksInit(PEER peer)
{
	PEER_CONNECTION;

	connection->callbackListLen = 0;
	connection->numCallbacksCalled = 0;
	connection->numCallbacksInCall = 0;

	connection->callbackList = ArrayNew(sizeof(piCallbackData), 0, piCallbackFree);

	return (PEERBool)(connection->callbackList != NULL);
}

void piCallbacksCleanup(PEER peer)
{
	PEER_CONNECTION;

	if(connection->callbackList)
		ArrayFree(connection->callbackList);
}

/* piCallbacksThink and the static it drives.  The two counters piCallbacksInit
   zeroes are named here rather than there because this is where they are
   used, and what they are is not a guess: +0x1824 is bumped immediately
   before a callback is invoked and dropped immediately after, and +0x1820 is
   bumped once per callback that completes.

   piCallCallback is static and both its arguments arrive in registers -- it
   has no stack parameters at all -- so it must stay static with both call
   sites in this file.  It re-fetches the element after the callback returns,
   which is not redundant: the callback can add callbacks, and the array can
   have moved under it.

   The ID sweep stops on the first match OR on any PI_DISCONNECTED_CALLBACK,
   tested second, which is the order the source writes them. */

static void piCallCallback(PEER peer, int index)
{
	piCallbackData * data;
	PEER_CONNECTION;

	data = (piCallbackData *)ArrayNth(connection->callbackList, index);
	data->inCall = PEERTrue;
	connection->numCallbacksInCall++;

	callbackFuncs[data->type].call(peer, data);

	data = (piCallbackData *)ArrayNth(connection->callbackList, index);
	data->inCall = PEERFalse;
	connection->numCallbacksInCall--;
	connection->numCallbacksCalled++;

	ArrayDeleteAt(connection->callbackList, index);
}

void piCallbacksThink(PEER peer, int ID)
{
	piCallbackData * data;
	int len;
	int i;
	PEER_CONNECTION;

	if(ID != -1)
	{
		len = ArrayLength(connection->callbackList);
		for(i = 0 ; i < len ; i++)
		{
			data = (piCallbackData *)ArrayNth(connection->callbackList, i);
			if((data->ID == ID) || (data->type == PI_DISCONNECTED_CALLBACK))
			{
				piCallCallback(peer, i);
				return;
			}
		}

		return;
	}

	i = 0;
	while(ArrayLength(connection->callbackList) > i)
	{
		data = (piCallbackData *)ArrayNth(connection->callbackList, i);
		if(data->inCall)
			i++;
		else
			piCallCallback(peer, i);
	}
}

/* Two sweeps that drop queued callbacks before they run.  Both walk the list
   BACKWARDS, which is what makes deleting as they go safe, and both re-read
   the list pointer from the connection every pass while calling ArrayLength
   exactly once up front.

   The second one's filter is what identifies it: type 3 is
   PI_LISTING_GAMES_CALLBACK, and it compares +4 of that entry's params, which
   piListingGamesParams puts the SBServer at.

   The two names describe what the bodies do.  No peer.h of this vintage is in
   hand to attest them, and unlike the piAdd* family next door there is no
   table here to read them off, so they are stated as a reading rather than a
   recovery. */

void piClearCallbacks(PEER peer, piCallbackType type)
{
	piCallbackData * data;
	int i;
	PEER_CONNECTION;

	for(i = ArrayLength(connection->callbackList) - 1 ; i >= 0 ; i--)
	{
		data = (piCallbackData *)ArrayNth(connection->callbackList, i);
		if(data->type == type)
			ArrayDeleteAt(connection->callbackList, i);
	}
}

void piClearServerCallbacks(PEER peer, SBServer server)
{
	piCallbackData * data;
	int i;
	PEER_CONNECTION;

	for(i = ArrayLength(connection->callbackList) - 1 ; i >= 0 ; i--)
	{
		data = (piCallbackData *)ArrayNth(connection->callbackList, i);
		if((data->type == PI_LISTING_GAMES_CALLBACK) &&
			(((piListingGamesParams *)data->params)->server == server))
			ArrayDeleteAt(connection->callbackList, i);
	}
}
