// cl: /DNDEBUG /MD
// Upstream: GameSpy Peer SDK peerOperations.c, 2007 release.

#include <stdlib.h>
#include <string.h>

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
	char reserved[0x1790 - sizeof(void *)];
	piOperation *listingGroupsOperation;
	int nextID;
	void *operationList;
	int operationsStarted;
	char reserved2[0x1EF0 - 0x17A0];
	piOperation *autoMatchOperation;
} piConnection;

void *memset(void *dest, int value, unsigned int count);
void ArrayAppend(void *array, const void *element);
PEERBool piSBStartListingGroups(PEER peer, const char *fields);
void piGetPlayerInfoCallbackA(void);
void chatGetBasicUserInfoA(void *chat, const char *nick, void *callback,
	void *param, int blocking);
void piChangeNickCallbackA(void);
void chatChangeNickA(void *chat, const char *newNick, void *callback,
	void *param, int blocking);
void piAuthenticateCDKeyCallbackA(void);
void chatAuthenticateCDKeyA(void *chat, const char *cdkey, void *callback,
	void *param, int blocking);
void piSetAutoMatchStatus(PEER peer, int status);
void piSetChannelCallbacks(PEER peer, void *callbacks);
void piStartedEnteringRoom(PEER peer, int roomType, const char *channel);
void piJoinRoomEnterChannelCallbackA(void);
void chatEnterChannelA(void *chat, const char *channel, const char *password,
	void *callbacks, void *callback, void *param, int blocking);

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
		piChangeNickCallbackA, operation, 0);
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
		piAuthenticateCDKeyCallbackA, operation, 0);
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
	piStartedEnteringRoom(peer, roomType, channel);
	chatEnterChannelA(connection->chat, channel, password, channelCallbacks,
		piJoinRoomEnterChannelCallbackA, operation, 0);
	return 1;
}
