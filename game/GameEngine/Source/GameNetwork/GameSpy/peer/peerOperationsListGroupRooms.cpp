// cl: /DNDEBUG /MD
// Upstream: GameSpy Peer SDK peerOperations.c, 2007 release.

#include <stdlib.h>
#include <string.h>

// Existing matched C++ providers at 00857250 and 00863B40, respectively.
// The caller's cdecl stack arguments match these declarations exactly.
void bfmeCallAll250(void *);
struct BfmeTableAT;
void bfmeSetNameAT(BfmeTableAT *, int, const char *);

extern "C" {
typedef void *PEER;
typedef int PEERBool;
typedef void *PEERCBType;

typedef struct piOperation
{
	PEER peer;
	int type;
	void *data;
	int ID;
	PEERCBType callback;
	PEERCBType callback2;
	void *callbackParam;
	int roomType;
	char *name;
	char *password;
	int num;
	unsigned int socket;
	unsigned short port;
	PEERBool socketClose;
	PEERBool cancel;
} piOperation;

typedef struct piOperationContainer
{
	piOperation *operation;
} piOperationContainer;

typedef struct piConnection
{
	void *chat;
	char nick[64];
	int connecting;
	int connected;
	void *nickErrorCallback;
	unsigned int lastChatPing;
	unsigned int publicIP;
	unsigned int privateIP;
	int profileID;
	char title[32];
	char room[3][257];
	int enteringRoom[3];
	int inRoom[3];
	char reservedRooms[0xAF0 - 0x39C];
	void *queryReporting;
	char reservedReporting[0xB40 - 0xAF4];
	int hosting;
	char reservedHosting[0xB48 - 0xB44];
	int maxPlayers;
	int passwordedRoom;
	char reservedPlayers0[0xB58 - 0xB50];
	char sbName[32];
	char sbSecretKey[8];
	char reservedPlayers[0x1790 - 0xB80];
	piOperation *listingGroupsOperation;
	int nextID;
	void *operationList;
	int operationsStarted;
	char reserved2[0x1EF0 - 0x17A0];
	piOperation *autoMatchOperation;
	char reserved3[0x1F04 - 0x1EF4];
	int disconnect;
} piConnection;

typedef struct chatGlobalCallbacks
{
	void *raw;
	void *disconnected;
	void *privateMessage;
	void *invited;
	void *param;
} chatGlobalCallbacks;

void *memset(void *dest, int value, unsigned int count);
void ArrayAppend(void *array, const void *element);
PEERBool piSBStartListingGroups(PEER peer, const char *fields);
void piGetPlayerInfoCallbackA(void *chat, int success, const char *nick,
	const char *user, const char *address, void *param);
void chatGetBasicUserInfoA(void *chat, const char *nick, void *callback,
	void *param, int blocking);
/* Matched peerOperations.c providers: 0085FCD0 and 00860020.
   Operation constructors pass these addresses as Chat completion callbacks. */
void piChangeNickCallback(void *chat, int success, const char *oldNick,
 const char *newNick, void *param);
void chatChangeNickA(void *chat, const char *newNick, void *callback,
	void *param, int blocking);
void piAuthenticateCDKeyCallback(void *chat, int result, const char *message,
 void *param);
void chatAuthenticateCDKeyA(void *chat, const char *cdkey, void *callback,
	void *param, int blocking);
void piSetAutoMatchStatus(PEER peer, int status);
void piSetChannelCallbacks(PEER peer, void *callbacks);
static void piJoinRoomEnterChannelCallbackA(void *chat, int success,
	int result, const char *channel, void *param);
void chatEnterChannelA(void *chat, const char *channel, const char *password,
	void *callbacks, void *callback, void *param, int blocking);
void piSBFreeHostServer(PEER peer);
void piRemoveOperation(PEER peer, piOperation *operation);
void piJoinRoomEnumUsersCallbackA(void *chat, int success,
	const char *channel, int numUsers, const char **users, int *modes,
	void *param);
void chatEnumUsersA(void *chat, const char *channel, void *callback,
	void *param, int blocking);
void piLeaveRoom(PEER peer, int roomType, const char *reason);
void piAddJoinRoomCallback(PEER peer, int success, int result, int roomType,
	PEERCBType callback, void *callbackParam, int opID);
void chatSetChannelPasswordA(void *chat, const char *channel, int enabled,
	const char *password);
void piCreateStagingRoomEnumUsersCallbackA(void *chat, int success,
	const char *channel, int numUsers, const char **users, int *modes,
	void *param);
void piCreateStagingRoomEnterChannelCallbackA(void *chat, int success,
	int result, const char *channel, void *param);
int piConnectTitle(PEER peer);
unsigned int current_time(void);
const char *chatGetNickA(void *chat);
__declspec(dllimport) int strcmpi(const char *left, const char *right);
void piAddConnectCallback(PEER peer, int success, int failureReason,
	PEERCBType callback, void *callbackParam, int opID);
int piDemangleUser(const char *user, unsigned int *IP, int *profileID);
void piSetPlayerIPAndProfileID(PEER peer, const char *nick, unsigned int IP,
	int profileID);
void piAddGetPlayerInfoCallback(PEER peer, int success, const char *nick,
	unsigned int IP, int profileID, PEERCBType callback,
	void *callbackParam, int opID);
void piAddGetPlayerProfileIDCallback(PEER peer, int success,
	const char *nick, int profileID, PEERCBType callback,
	void *callbackParam, int opID);
void piAddGetPlayerIPCallback(PEER peer, int success, const char *nick,
	unsigned int IP, PEERCBType callback, void *callbackParam, int opID);
void piGetChannelKeysCallbackA(void *chat, int success, const char *channel,
	const char *user, int num, const char **keys, const char **values,
	void *param);
void chatGetChannelKeysA(void *chat, const char *channel, const char *nick,
	int num, const char **keys, void *callback, void *param, int blocking);
void piRoomKeyChanged(PEER peer, int roomType, const char *nick,
	const char *key, const char *value);
void piAddGetRoomKeysCallback(PEER peer, int success, int roomType,
	const char *nick, int num, const char **keys, const char **values,
	PEERCBType callback, void *callbackParam, int opID);
void piGlobalKeyChanged(PEER peer, const char *nick, const char *key,
	const char *value);
void piAddGetGlobalKeysCallback(PEER peer, int success, const char *nick,
	int num, const char **keys, const char **values, PEERCBType callback,
	void *callbackParam, int opID);
void chatGetGlobalKeysA(void *chat, const char *target, int num,
	const char **keys, void *callback, void *param, int blocking);
void piFinishedEnteringRoom(PEER peer, int roomType, const char *reason);
void piPlayerJoinedRoom(PEER peer, const char *nick, int roomType, int mode);
int peerIsAutoMatching(PEER peer);
int piStartHosting(PEER peer, unsigned int socket, unsigned short port);
void chatSetChannelTopicA(void *chat, const char *channel, const char *topic);
void chatSetChannelLimitA(void *chat, const char *channel, int limit);
int qr2_create_socket(unsigned int *socket, const char *ip, int *port);
typedef struct in_addr
{
	unsigned int s_addr;
} in_addr;
char *__stdcall inet_ntoa(in_addr address);
void piMangleStagingRoom(char *room, const char *title,
	unsigned int publicIP, unsigned int privateIP, unsigned short port);
char *goastrdup(const char *text);
extern const char *(__cdecl *GOAGetUniqueID)(void);
void MD5Digest(const unsigned char *text, unsigned int length, char *digest);
/* Chat disconnected/private-message callbacks: the constructor's DIR32
   references are retail 0086B2D0 and 0086B360. Use the matched C providers. */
struct Rva0086B2D0Connection;
void Rva0086B2D0Disconnected(void *chat, const char *reason,
 struct Rva0086B2D0Connection *connection);
void Rva0086B360Dispatch(void *chat, const char *nick, const char *message,
 int mode, PEER peer);
void piConnectNickErrorCallbackA(PEER peer, int type, const char *nick,
		int numSuggestedNicks, const char **suggestedNicks, void *param);
void piConnectFillInUserCallbackA(void);
void piConnectConnectCallback(void *chat, int success,
	int failureReason, void *param);
void *chatConnectSecureA(const char *server, int port, const char *nick,
	const char *name, const char *game, const char *secret,
	chatGlobalCallbacks *callbacks, void *nickErrorCallback,
	void *fillInUserCallback, void *connectCallback, void *param, int blocking);
void *chatConnectLoginA(const char *server, int port, int namespaceID,
	const char *email, const char *profilenick, const char *uniquenick,
	const char *password, const char *name, const char *game,
	const char *secret, chatGlobalCallbacks *callbacks,
	void *nickErrorCallback, void *fillInUserCallback, void *connectCallback,
	void *param, int blocking);
void *chatConnectPreAuthA(const char *server, int port,
	const char *authtoken, const char *partnerchallenge, const char *name,
	const char *game, const char *secret, chatGlobalCallbacks *callbacks,
	void *nickErrorCallback, void *fillInUserCallback, void *connectCallback,
	void *param, int blocking);

static piOperation *piAddOperation(PEER peer, int type, void *data,
	PEERCBType callback, void *callbackParam, int opID)
{
	piConnection *connection = (piConnection *)peer;
	piOperationContainer container;
	piOperation *operation;

	if (!connection->operationList)
		return 0;

	operation = (piOperation *)malloc(sizeof(piOperation));
	if (!operation)
		return 0;

	memset(operation, 0, sizeof(piOperation));
	operation->peer = peer;
	operation->type = type;
	operation->data = data;
	operation->ID = opID;
	operation->callback = callback;
	operation->callbackParam = callbackParam;
	operation->name = 0;
	operation->cancel = 0;

	container.operation = operation;
	ArrayAppend(connection->operationList, &container);
	connection->operationsStarted++;

	return operation;
}

PEERBool piNewConnectOperation(PEER peer, int connectType, const char *nick,
	int namespaceID, const char *email, const char *profilenick,
	const char *uniquenick, const char *password, const char *authtoken,
	const char *partnerchallenge, PEERCBType callback, void *callbackParam,
	int opID)
{
	static const char server[] = "peerchat.gamespy.com";
	piConnection *connection = (piConnection *)peer;
	piOperation *operation;
	chatGlobalCallbacks globalCallbacks;
	const char *uniqueID;
	char encodedUniqueID[33];
	void *nickErrorCallback;

	operation = piAddOperation(peer, 0, 0, callback, callbackParam, opID);
	if (!operation)
		return 0;

	memset(&globalCallbacks, 0, sizeof(globalCallbacks));
	globalCallbacks.disconnected = Rva0086B2D0Disconnected;
	globalCallbacks.privateMessage = Rva0086B360Dispatch;
	globalCallbacks.param = peer;

	uniqueID = GOAGetUniqueID();
	MD5Digest((const unsigned char *)uniqueID, strlen(uniqueID),
		encodedUniqueID);

	nickErrorCallback = connection->nickErrorCallback ?
		piConnectNickErrorCallbackA : 0;
	if (connectType == 0)
	{
		connection->chat = chatConnectSecureA(server, 6667, nick,
			encodedUniqueID, connection->sbName, connection->sbSecretKey,
			&globalCallbacks, nickErrorCallback, piConnectFillInUserCallbackA,
			piConnectConnectCallback, operation, 0);
	}
	else if (connectType == 1 || connectType == 2)
	{
		connection->chat = chatConnectLoginA(server, 6667, namespaceID,
			email, profilenick, uniquenick, password, encodedUniqueID,
			connection->sbName, connection->sbSecretKey, &globalCallbacks,
			nickErrorCallback, piConnectFillInUserCallbackA,
			piConnectConnectCallback, operation, 0);
	}
	else if (connectType == 3)
	{
		connection->chat = chatConnectPreAuthA(server, 6667, authtoken,
			partnerchallenge, encodedUniqueID, connection->sbName,
			connection->sbSecretKey, &globalCallbacks, nickErrorCallback,
			piConnectFillInUserCallbackA, piConnectConnectCallback,
			operation, 0);
	}

	if (!connection->chat)
	{
		piRemoveOperation(peer, operation);
		return 0;
	}
	return 1;
}

void piConnectConnectCallback(void *chat, int success,
	int failureReason, void *param)
{
	piOperation *operation = (piOperation *)param;
	PEER peer = operation->peer;
	piConnection *connection = (piConnection *)peer;

	if (success)
	{
		if (!piConnectTitle(peer))
		{
			bfmeCallAll250(peer);
			success = 0;
		}
	}

	connection->connecting = 0;
	connection->connected = success;

	if (success)
	{
		const char *nick;

		connection->lastChatPing = current_time();
		nick = chatGetNickA(chat);
		if (strcmpi(connection->nick, nick) != 0)
			strcpy(connection->nick, nick);
	}
	else
	{
		connection->disconnect = 1;
	}

	piAddConnectCallback(peer, success, failureReason, operation->callback,
		operation->callbackParam, operation->ID);
	piRemoveOperation(peer, operation);
}

void piGetPlayerInfoCallbackA(void *chat, int success, const char *nick,
	const char *user, const char *address, void *param)
{
	int profileID = 0;
	unsigned int IP = 0;
	piOperation *operation = (piOperation *)param;
	PEER peer = operation->peer;

	if (success)
	{
		if (!piDemangleUser(user, &IP, &profileID))
			success = 0;
		if (success)
			piSetPlayerIPAndProfileID(peer, nick, IP, profileID);
	}
	if (!success)
	{
		profileID = 0;
		IP = 0;
	}

	if (operation->callback)
	{
		if (operation->type == 6)
			piAddGetPlayerInfoCallback(peer, success, nick, IP, profileID,
				operation->callback, operation->callbackParam, operation->ID);
		else if (operation->type == 7)
			piAddGetPlayerProfileIDCallback(peer, success, nick, profileID,
				operation->callback, operation->callbackParam, operation->ID);
		else if (operation->type == 8)
			piAddGetPlayerIPCallback(peer, success, nick, IP,
				operation->callback, operation->callbackParam, operation->ID);
	}

	piRemoveOperation(peer, operation);
	(void)chat;
	(void)address;
}

void piGetChannelKeysCallbackA(void *chat, int success, const char *channel,
	const char *user, int num, const char **keys, const char **values,
	void *param)
{
	piOperation *operation = (piOperation *)param;
	PEER peer = operation->peer;
	int i;

	if (success && user)
	{
		for (i = 0; i < num; i++)
			piRoomKeyChanged(peer, operation->roomType, user,
				keys[i], values[i]);
	}

	if (operation->callback)
		piAddGetRoomKeysCallback(peer, success, operation->roomType, user,
			num, keys, values, operation->callback,
			operation->callbackParam, operation->ID);

	if (!success || !user || !operation->num)
		piRemoveOperation(peer, operation);

	(void)chat;
	(void)channel;
}

void piGetGlobalKeysCallbackA(void *chat, int success, const char *user,
	int num, const char **keys, const char **values, void *param)
{
	piOperation *operation = (piOperation *)param;
	PEER peer = operation->peer;
	int i;

	if (success && user)
	{
		for (i = 0; i < num; i++)
			piGlobalKeyChanged(peer, user, keys[i], values[i]);
	}

	if (operation->callback)
		piAddGetGlobalKeysCallback(peer, success, user, num, keys, values,
			operation->callback, operation->callbackParam, operation->ID);

	if (!success || !user || !operation->num)
		piRemoveOperation(peer, operation);

	(void)chat;
}

void piJoinRoomEnumUsersCallbackA(void *chat, int success,
	const char *channel, int numUsers, const char **users, int *modes,
	void *param)
{
	piOperation *operation = (piOperation *)param;
	PEER peer = operation->peer;
	int i;

	if (operation->cancel)
	{
		piRemoveOperation(peer, operation);
		return;
	}

	if (success)
	{
		piFinishedEnteringRoom(peer, operation->roomType, "");
		for (i = 0; i < numUsers; i++)
			piPlayerJoinedRoom(peer, users[i], operation->roomType, modes[i]);
	}
	else
	{
		piLeaveRoom(peer, operation->roomType, 0);
	}

	piAddJoinRoomCallback(peer, success, success ? 0 : 10,
		operation->roomType, operation->callback, operation->callbackParam,
		operation->ID);
	piRemoveOperation(peer, operation);

	(void)chat;
	(void)channel;
}

void piCreateStagingRoomEnumUsersCallbackA(void *chat, int success,
	const char *channel, int numUsers, const char **users, int *modes,
	void *param)
{
	typedef struct qr2_s
	{
		char reserved[0xC4];
		int read_socket;
	} qr2_t;

	piOperation *operation = (piOperation *)param;
	PEER peer = operation->peer;
	piConnection *connection = (piConnection *)peer;
	int i;

	if (operation->cancel)
	{
		piRemoveOperation(peer, operation);
		return;
	}

	if (success)
	{
		if (!peerIsAutoMatching(peer))
		{
			if (!piStartHosting(peer, operation->socket, operation->port))
				success = 0;
			else if (operation->socketClose)
			{
				operation->socketClose = 0;
				((qr2_t *)connection->queryReporting)->read_socket = 1;
			}
		}
		else
		{
			connection->hosting = 1;
		}
	}

	if (success)
	{
		piFinishedEnteringRoom(peer, 2, operation->name);
		for (i = 0; i < numUsers; i++)
			piPlayerJoinedRoom(peer, users[i], 2, modes[i]);

		chatSetChannelTopicA(connection->chat, channel, operation->name);
		if (connection->maxPlayers)
			chatSetChannelLimitA(connection->chat, channel,
				connection->maxPlayers);

		if (operation->socketClose && peerIsAutoMatching(peer))
		{
			connection->autoMatchOperation->socket = operation->socket;
			connection->autoMatchOperation->port = operation->port;
			connection->autoMatchOperation->socketClose = 1;
			operation->socketClose = 0;
		}
	}
	else
	{
		piLeaveRoom(peer, 2, 0);
	}

	piAddJoinRoomCallback(peer, success, success ? 0 : 10, 2,
		operation->callback, operation->callbackParam, operation->ID);
	piRemoveOperation(peer, operation);

	(void)chat;
}

PEERBool piNewListGroupRoomsOperation(PEER peer, const char *fields,
	PEERCBType callback, void *param, int opID)
{
	piConnection *connection = (piConnection *)peer;
	piOperation *operation;

	operation = connection->listingGroupsOperation =
		piAddOperation(peer, 4, 0, callback, param, opID);
	if (!operation)
		return 0;

	return piSBStartListingGroups(peer, fields);
}

PEERBool piNewGetPlayerInfoOperation(PEER peer, const char *nick,
	PEERCBType callback, void *param, int opID)
{
	piConnection *connection = (piConnection *)peer;
	piOperation *operation = piAddOperation(peer, 6, 0, callback, param, opID);

	if (!operation)
		return 0;

	chatGetBasicUserInfoA(connection->chat, nick,
		piGetPlayerInfoCallbackA, operation, 0);
	return 1;
}

PEERBool piNewGetProfileIDOperation(PEER peer, const char *nick,
	PEERCBType callback, void *param, int opID)
{
	piConnection *connection = (piConnection *)peer;
	piOperation *operation = piAddOperation(peer, 7, 0, callback, param, opID);

	if (!operation)
		return 0;

	chatGetBasicUserInfoA(connection->chat, nick,
		piGetPlayerInfoCallbackA, operation, 0);
	return 1;
}

PEERBool piNewGetIPOperation(PEER peer, const char *nick,
	PEERCBType callback, void *param, int opID)
{
	piConnection *connection = (piConnection *)peer;
	piOperation *operation = piAddOperation(peer, 8, 0, callback, param, opID);

	if (!operation)
		return 0;

	chatGetBasicUserInfoA(connection->chat, nick,
		piGetPlayerInfoCallbackA, operation, 0);
	return 1;
}

PEERBool piNewChangeNickOperation(PEER peer, const char *newNick,
	PEERCBType callback, void *param, int opID)
{
	piConnection *connection = (piConnection *)peer;
	piOperation *operation = piAddOperation(peer, 9, 0, callback, param, opID);

	if (!operation)
		return 0;

	chatChangeNickA(connection->chat, newNick,
		piChangeNickCallback, operation, 0);
	return 1;
}

PEERBool piNewAuthenticateCDKeyOperation(PEER peer, const char *cdkey,
	PEERCBType callback, void *param, int opID)
{
	piConnection *connection = (piConnection *)peer;
	piOperation *operation = piAddOperation(peer, 12, 0, callback, param, opID);

	if (!operation)
		return 0;

	chatAuthenticateCDKeyA(connection->chat, cdkey,
		piAuthenticateCDKeyCallback, operation, 0);
	return 1;
}

PEERBool piNewAutoMatchOperation(PEER peer, unsigned int socket,
	unsigned short port, PEERCBType statusCallback,
	PEERCBType rateCallback, void *param, int opID)
{
	piConnection *connection = (piConnection *)peer;
	piOperation *operation =
		piAddOperation(peer, 13, 0, statusCallback, param, opID);

	if (!operation)
		return 0;

	operation->callback2 = rateCallback;
	operation->socket = socket;
	operation->port = port;
	connection->autoMatchOperation = operation;
	piSetAutoMatchStatus(peer, 1);
	return 1;
}

PEERBool piNewGetRoomKeysOperation(PEER peer, int roomType,
	const char *nick, int num, const char **keys, PEERCBType callback,
	void *param, int opID)
{
	piConnection *connection = (piConnection *)peer;
	piOperation *operation;

	if (num < 0)
		return 0;
	if (num > 0 && !keys)
		return 0;
	if (!connection->enteringRoom[roomType] && !connection->inRoom[roomType])
		return 0;

	operation = piAddOperation(peer, 11, 0, callback, param, opID);
	if (!operation)
		return 0;
	operation->roomType = roomType;

	if (nick)
		operation->num = (strcmp(nick, "*") == 0);
	else
		operation->num = 0;

	chatGetChannelKeysA(connection->chat, connection->room[roomType], nick,
		num, keys, piGetChannelKeysCallbackA, operation, 0);
	return 1;
}

PEERBool piNewGetGlobalKeysOperation(PEER peer, const char *target, int num,
	const char **keys, PEERCBType callback, void *param, int opID)
{
	piConnection *connection = (piConnection *)peer;
	piOperation *operation;

	if (!target || !target[0])
		return 0;
	if (num <= 0)
		return 0;

	operation = piAddOperation(peer, 10, 0, callback, param, opID);
	if (!operation)
		return 0;

	operation->num = (target[0] == '#');
	chatGetGlobalKeysA(connection->chat, target, num, keys,
		piGetGlobalKeysCallbackA, operation, 0);
	return 1;
}

PEERBool piNewCreateStagingRoomOperation(PEER peer, const char *name,
	const char *password, int maxPlayers, unsigned int socket,
	unsigned short port, PEERCBType callback, void *callbackParam, int opID)
{
	piConnection *connection = (piConnection *)peer;
	piOperation *operation;
	char channelCallbacks[0x30];
	char room[257];
	int createdSocket = 0;

	if (!name)
		name = "";
	if (!callback)
		return 0;

	connection->maxPlayers = maxPlayers;
	if (socket == (unsigned int)-1)
	{
		in_addr address;
		int privatePort;

		address.s_addr = 0;
		privatePort = port ? port : 6500;
		if (qr2_create_socket(&socket, inet_ntoa(address), &privatePort) != 0)
			return 0;

		port = (unsigned short)privatePort;
		createdSocket = 1;
	}

	piMangleStagingRoom(room, connection->title, connection->publicIP,
		connection->privateIP, port);
	operation = piAddOperation(peer, 1, 0, callback, callbackParam, opID);
	if (!operation)
		return 0;

	operation->socketClose = createdSocket;
	operation->name = goastrdup(name);
	if (!operation->name)
	{
		piRemoveOperation(peer, operation);
		return 0;
	}

	operation->socket = socket;
	operation->port = port;
	operation->roomType = 2;
	if (password[0])
		operation->password = goastrdup(password);

	piSetChannelCallbacks(peer, channelCallbacks);
	bfmeSetNameAT((BfmeTableAT *)peer, 2, room);
	chatEnterChannelA(connection->chat, room, 0, channelCallbacks,
		piCreateStagingRoomEnterChannelCallbackA, operation, 0);

	if (password[0])
		connection->passwordedRoom = 1;
	return 1;
}

PEERBool piNewJoinRoomOperation(PEER peer, int roomType,
	const char *channel, const char *password, PEERCBType callback,
	void *callbackParam, int opID)
{
	piConnection *connection = (piConnection *)peer;
	piOperation *operation;
	char channelCallbacks[0x30];

	if (!channel || !channel[0])
		return 0;
	if (!password)
		password = "";
	if (strlen(channel) >= 257)
		return 0;

	operation = piAddOperation(peer, 2, 0, callback, callbackParam, opID);
	if (!operation)
		return 0;
	operation->roomType = roomType;

	piSetChannelCallbacks(peer, channelCallbacks);
	bfmeSetNameAT((BfmeTableAT *)peer, roomType, channel);
	chatEnterChannelA(connection->chat, channel, password, channelCallbacks,
		piJoinRoomEnterChannelCallbackA, operation, 0);
	return 1;
}

static int piEnterResultToJoinResult(int result)
{
	switch (result)
	{
	case 0:
		return 0;
	case 1:
		return 1;
	case 2:
		return 2;
	case 3:
		return 3;
	case 4:
		return 4;
	case 5:
		return 10;
	default:
		return 10;
	}
}

static void piJoinRoomEnterChannelCallbackA(void *chat, int success,
	int result, const char *channel, void *param)
{
	piOperation *operation = (piOperation *)param;
	PEER peer = operation->peer;
	int joinResult;

	if (operation->cancel)
	{
		piSBFreeHostServer(peer);
		piRemoveOperation(peer, operation);
		return;
	}

	if (success)
	{
		chatEnumUsersA(chat, channel, piJoinRoomEnumUsersCallbackA,
			operation, 0);
		return;
	}

	piLeaveRoom(peer, operation->roomType, 0);
	if (result == 0)
		joinResult = 10;
	else
		joinResult = piEnterResultToJoinResult(result);

	piAddJoinRoomCallback(peer, 0, joinResult, operation->roomType,
		operation->callback, operation->callbackParam, operation->ID);
	piRemoveOperation(peer, operation);
}

void piCreateStagingRoomEnterChannelCallbackA(void *chat, int success,
	int result, const char *channel, void *param)
{
	piOperation *operation = (piOperation *)param;
	PEER peer = operation->peer;
	piConnection *connection = (piConnection *)peer;
	int joinResult;

	if (operation->cancel)
	{
		piRemoveOperation(peer, operation);
		return;
	}

	if (success)
	{
		if (operation->password)
			chatSetChannelPasswordA(connection->chat, channel, 1,
				operation->password);

		chatEnumUsersA(chat, channel, piCreateStagingRoomEnumUsersCallbackA,
			operation, 0);
		return;
	}

	piLeaveRoom(peer, 2, 0);
	if (result == 0)
		joinResult = 10;
	else
		joinResult = piEnterResultToJoinResult(result);

	piAddJoinRoomCallback(peer, 0, joinResult, 2, operation->callback,
		operation->callbackParam, operation->ID);
	piRemoveOperation(peer, operation);
}

} // extern "C"
