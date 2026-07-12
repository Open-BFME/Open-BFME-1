/*
**	GameSpy Peer SDK shim — declarations for sweep compilation.
**	Callback typedefs + PEERCallbacks layout match the 2003-era Peer SDK
**	(struct order per the GameSpy SDK documentation; individual callback
**	signatures cross-checked against ZH's own callback definitions in
**	PeerThread.cpp, so member offsets are the real thing).
*/

#pragma once

#ifndef __PEER_H__
#define __PEER_H__

#include "GameSpy/qr2/qr2.h"
#include <winsock2.h>

typedef int PEERBool;
#define PEERTrue  1
#define PEERFalse 0

typedef void* PEER;

typedef enum {
	TitleRoom,
	GroupRoom,
	StagingRoom,
	NumRooms,
} RoomType;

typedef enum {
	PEERJoinNoError,
	PEERJoinSuccess,
	PEERFullRoom,
	PEERAlreadyInRoom,
	PEERInviteOnlyRoom,
	PEERInUse,
	PEERBannedFromRoom,
	PEERBadPassword,
	PEERNoConnection,
	PEERJoinFailed,
} PEERJoinResult;

// nick-error types for peerNickErrorCallback
#define PEER_IN_USE  0
#define PEER_INVALID 1

typedef enum {
	NormalMessage,
	ActionMessage,
} MessageType;

// PEER connection constants
enum {
	PEER_ADD,
	PEER_UPDATE,
	PEER_REMOVE,
	PEER_CLEAR,
	PEER_STOP_REPORTING,
	PEER_FLAG_OP = 0x01,
};

// ServerBrowsing SDK: GServer is SBServer (server-browser handle)
typedef struct _SBServer {
	void *keyvals;	// PeerThread.cpp probes this for liveness
} *SBServer;
typedef int SBBool;
#define SBTrue  1
#define SBFalse 0
typedef SBServer GServer;

char *SBServerGetStringValue(SBServer server, const char *keyname, char *def);
int SBServerGetIntValue(SBServer server, const char *keyname, int def);
char *SBServerGetPlayerStringValue(SBServer server, int playernum, const char *keyname, char *def);
int SBServerGetPlayerIntValue(SBServer server, int playernum, const char *keyname, int def);
unsigned int SBServerGetPublicInetAddress(SBServer server);
unsigned int SBServerGetPrivateInetAddress(SBServer server);
unsigned short SBServerGetPublicQueryPort(SBServer server);
unsigned short SBServerGetPrivateQueryPort(SBServer server);
SBBool SBServerHasBasicKeys(SBServer server);
SBBool SBServerHasFullKeys(SBServer server);

// Peer SDK callback typedefs (2003-era SDK)
typedef void (*peerDisconnectedCallback)(PEER peer, const char *reason, void *param);
typedef void (*peerRoomMessageCallback)(PEER peer, RoomType roomType, const char *nick, const char *message, MessageType messageType, void *param);
typedef void (*peerRoomUTMCallback)(PEER peer, RoomType roomType, const char *nick, const char *command, const char *parameters, PEERBool authenticated, void *param);
typedef void (*peerRoomNameChangedCallback)(PEER peer, RoomType roomType, void *param);
typedef void (*peerRoomModeChangedCallback)(PEER peer, RoomType roomType, int mode, void *param);
typedef void (*peerPlayerMessageCallback)(PEER peer, const char *nick, const char *message, MessageType messageType, void *param);
typedef void (*peerPlayerUTMCallback)(PEER peer, const char *nick, const char *command, const char *parameters, PEERBool authenticated, void *param);
typedef void (*peerReadyChangedCallback)(PEER peer, const char *nick, PEERBool ready, void *param);
typedef void (*peerGameStartedCallback)(PEER peer, unsigned int IP, const char *message, void *param);
typedef void (*peerPlayerJoinedCallback)(PEER peer, RoomType roomType, const char *nick, void *param);
typedef void (*peerPlayerLeftCallback)(PEER peer, RoomType roomType, const char *nick, const char *reason, void *param);
typedef void (*peerKickedCallback)(PEER peer, RoomType roomType, const char *nick, const char *reason, void *param);
typedef void (*peerNewPlayerListCallback)(PEER peer, RoomType roomType, void *param);
typedef void (*peerPlayerChangedNickCallback)(PEER peer, RoomType roomType, const char *oldNick, const char *newNick, void *param);
typedef void (*peerPlayerInfoCallback)(PEER peer, RoomType roomType, const char *nick, unsigned int IP, int profileID, void *param);
typedef void (*peerPlayerFlagsChangedCallback)(PEER peer, RoomType roomType, const char *nick, int oldFlags, int newFlags, void *param);
typedef void (*peerPingCallback)(PEER peer, const char *nick, int ping, void *param);
typedef void (*peerCrossPingCallback)(PEER peer, const char *nick1, const char *nick2, int crossPing, void *param);
typedef void (*peerGlobalKeyChangedCallback)(PEER peer, const char *nick, const char *key, const char *val, void *param);
typedef void (*peerRoomKeyChangedCallback)(PEER peer, RoomType roomType, const char *nick, const char *key, const char *val, void *param);
typedef void (*peerQRServerKeyCallback)(PEER peer, int key, qr2_buffer_t buffer, void *param);
typedef void (*peerQRPlayerKeyCallback)(PEER peer, int key, int index, qr2_buffer_t buffer, void *param);
typedef void (*peerQRTeamKeyCallback)(PEER peer, int key, int index, qr2_buffer_t buffer, void *param);
typedef void (*peerQRKeyListCallback)(PEER peer, qr2_key_type type, qr2_keybuffer_t keyBuffer, void *param);
typedef int (*peerQRCountCallback)(PEER peer, qr2_key_type type, void *param);
typedef void (*peerQRAddErrorCallback)(PEER peer, qr2_error_t error, char *errorString, void *param);
typedef void (*peerQRNatNegotiateCallback)(PEER peer, int cookie, void *param);
typedef void (*peerQRPublicAddressCallback)(PEER peer, unsigned int ip, unsigned short port, void *param);

typedef void (*peerEnumPlayersCallback)(PEER peer, PEERBool success,
	RoomType roomType, int index, const char *nick, int flags, void *param);

typedef void (*peerListingGamesCallback)(PEER peer, PEERBool success,
	const char *name, GServer server, PEERBool staging, int msg, int progress,
	void *param);

typedef void (*peerGetRoomKeysCallback)(PEER peer, PEERBool success,
	RoomType roomType, const char *nick, int num, char **keys, char **values,
	void *param);

// Struct passed into peerInitialize(); order per the GameSpy SDK docs.
typedef struct PEERCallbacks {
	peerDisconnectedCallback disconnected;
	peerRoomMessageCallback roomMessage;
	peerRoomUTMCallback roomUTM;
	peerRoomNameChangedCallback roomNameChanged;
	peerRoomModeChangedCallback roomModeChanged;
	peerPlayerMessageCallback playerMessage;
	peerPlayerUTMCallback playerUTM;
	peerReadyChangedCallback readyChanged;
	peerGameStartedCallback gameStarted;
	peerPlayerJoinedCallback playerJoined;
	peerPlayerLeftCallback playerLeft;
	peerKickedCallback kicked;
	peerNewPlayerListCallback newPlayerList;
	peerPlayerChangedNickCallback playerChangedNick;
	peerPlayerInfoCallback playerInfo;
	peerPlayerFlagsChangedCallback playerFlagsChanged;
	peerPingCallback ping;
	peerCrossPingCallback crossPing;
	peerGlobalKeyChangedCallback globalKeyChanged;
	peerRoomKeyChangedCallback roomKeyChanged;
	peerQRServerKeyCallback qrServerKey;
	peerQRPlayerKeyCallback qrPlayerKey;
	peerQRTeamKeyCallback qrTeamKey;
	peerQRKeyListCallback qrKeyList;
	peerQRCountCallback qrCount;
	peerQRAddErrorCallback qrAddError;
	peerQRNatNegotiateCallback qrNatNegotiateCallback;
	peerQRPublicAddressCallback qrPublicAddressCallback;
	void *param;
} PEERCallbacks;

// Peer SDK function declarations (sweep compilation only)
PEER peerInitialize(PEERCallbacks *callbacks);
PEERBool peerParseQuery(PEER peer, char *data, int len, struct sockaddr *from);
void peerMessageRoom(PEER peer, RoomType roomType, const char* message, MessageType msgType);
void peerMessagePlayer(PEER peer, const char* nick, const char* message, MessageType msgType);
PEERBool peerGetPlayerFlags(PEER peer, const char* nick, RoomType roomType, int* flags);
void peerSetRoomKeys(PEER peer, RoomType roomType, const char *nick,
	int num, const char **keys, const char **values);
void peerGetRoomKeys(PEER peer, RoomType roomType, const char *nick,
	int num, const char **keys, peerGetRoomKeysCallback callback, void *param,
	PEERBool dontTranslate);
void peerStopGame(PEER peer);
void peerSetRoomWatchKeys(PEER peer, RoomType roomType, int numKeys,
	const char **keys, PEERBool addKeys);

typedef void (*peerAuthenticateCDKeyCallback)(PEER peer, int result,
	const char *message, void *param);
void peerAuthenticateCDKey(PEER peer, const char *cdkey,
	peerAuthenticateCDKeyCallback callback, void *param, PEERBool blocking);

typedef void (*peerConnectCallback)(PEER peer, PEERBool success, void *param);
typedef void (*peerNickErrorCallback)(PEER peer, int type, const char *nick, void *param);
typedef void (*peerJoinRoomCallback)(PEER peer, PEERBool success,
	PEERJoinResult result, RoomType roomType, void *param);
typedef void (*peerListGroupRoomsCallback)(PEER peer, PEERBool success,
	int groupID, GServer server, const char *name, int numWaiting,
	int maxWaiting, int numGames, int numPlaying, void *param);
typedef void (*peerGetPlayerProfileIDCallback)(PEER peer, PEERBool success,
	const char *nick, int profileID, void *param);

void peerConnect(PEER peer, const char *nick, int profileID,
	peerNickErrorCallback nickErrorCallback,
	peerConnectCallback connectCallback, void *param, PEERBool blocking);
void peerDisconnect(PEER peer);
void peerShutdown(PEER peer);
void peerThink(PEER peer);
PEERBool peerIsConnected(PEER peer);
void peerRetryWithNick(PEER peer, const char *nick);
PEERBool peerSetTitle(PEER peer, const char *title, const char *qrSecretKey,
	const char *engineName, const char *engineSecretKey, int engineVersion,
	int engineMaxUpdates, PEERBool filter, PEERBool pingRooms[NumRooms],
	PEERBool crossPingRooms[NumRooms]);
void peerJoinGroupRoom(PEER peer, int groupID, peerJoinRoomCallback callback,
	void *param, PEERBool blocking);
void peerJoinStagingRoom(PEER peer, GServer server, const char *password,
	peerJoinRoomCallback callback, void *param, PEERBool blocking);
void peerCreateStagingRoomWithSocket(PEER peer, const char *name,
	int maxPlayers, const char *password, SOCKET socket, int port,
	peerJoinRoomCallback callback, void *param, PEERBool blocking);
void peerLeaveRoom(PEER peer, RoomType roomType, const char *reason);
void peerListGroupRooms(PEER peer, const char *filter,
	peerListGroupRoomsCallback callback, void *param, PEERBool blocking);
void peerEnumPlayers(PEER peer, RoomType roomType,
	peerEnumPlayersCallback callback, void *param);
void peerStartListingGames(PEER peer, unsigned char *keys, int numKeys,
	const char *filter, peerListingGamesCallback callback, void *param);
void peerStopListingGames(PEER peer);
void peerStartGame(PEER peer, const char *message, PEERBool stopReporting);
void peerStateChanged(PEER peer);
void peerUTMRoom(PEER peer, RoomType roomType, const char *command,
	const char *parameters, PEERBool authenticate);
void peerUTMPlayer(PEER peer, const char *nick, const char *command,
	const char *parameters, PEERBool authenticate);
void peerUpdateGame(PEER peer, GServer server, PEERBool fullUpdate);
void peerSetGlobalKeys(PEER peer, int num, const char **keys,
	const char **values);
void peerSetGlobalWatchKeys(PEER peer, RoomType roomType, int numKeys,
	const char **keys, PEERBool addKeys);
const char *peerGetGlobalWatchKey(PEER peer, const char *nick,
	const char *key);
unsigned int peerGetLocalIP(PEER peer);
PEERBool peerGetPlayerInfoNoWait(PEER peer, const char *nick,
	unsigned int *IP, int *profileID);
void peerGetPlayerProfileID(PEER peer, const char *nick,
	peerGetPlayerProfileIDCallback callback, void *param, PEERBool blocking);

// Chat SDK
void chatSetLocalIP(unsigned int ip);

// qr2 SDK reserved-key count (PeerThread builds its key enum off this)
#define NUM_RESERVED_KEYS 50

#endif // __PEER_H__
