// cl: /DNDEBUG /MD
// Upstream: GameSpy Peer SDK peerMain.c, 2007 release.

#include <string.h>

typedef void *PEER;

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
	char names[3][512];
	int oldFlags[3];
	int groupID;
	char titleRoomChannel[257];
	char reservedTitleRoom[0xAB0 - 0xAAD];
	int stayInTitleRoom;
	void *players;
	int numPlayers[3];
	int alwaysRequestPlayerInfo;
	char reservedStay[0xAF0 - 0xAC8];
	void *queryReporting;
	char reservedReporting[0xB38 - 0xAF4];
	int reportingOptions;
	char reservedReportingOptions[0xB40 - 0xB3C];
	int hosting;
	int playing;
	int maxPlayers;
	int passwordedRoom;
	void *hostServer;
	int ready;
	char reservedReady[0x1784 - 0xB58];
	void *gameListCallback;
	void *gameListParam;
	int initialGameList;
	char reservedGameList[0x1824 - 0x1790];
	int callbackDepth;
	int away;
	char awayReason[128];
	char reserved2[0x18D4 - 0x18AC];
	int autoMatchStatus;
	char reserved3[0x1EF8 - 0x18D8];
	char *autoMatchFilter;
	int autoMatchSBFailed;
	int autoMatchQRFailed;
	int disconnect;
	int shutdown;
} piConnection;

typedef struct piPlayer
{
	char nick[64];
	int inRoom[3];
	int local;
	unsigned int IP;
	int profileID;
	int gotIPAndProfileID;
	int flags[3];
	char reservedFlags[0x74 - 0x68];
	int waitingForPing;
	char reservedWaitingForPing[0x80 - 0x78];
	int pingAverage;
	char reservedPingAverage[0x98 - 0x84];
	int numPings;
	char reservedNumPings[0xA0 - 0x9C];
	int inPingRoom;
	char reservedInPingRoom[0xA8 - 0xA4];
	int mustPing;
	int pingOnce;
} piPlayer;

int piGetNextID(PEER peer);
int piNewChangeNickOperation(PEER peer, const char *newNick,
	void *callback, void *param, int opID);
void piAddChangeNickCallback(PEER peer, int success, const char *oldNick,
	const char *newNick, void *callback, void *param, int opID);
int piNewGetGlobalKeysOperation(PEER peer, const char *target, int num,
	const char **keys, void *callback, void *param, int opID);
int piNewGetRoomKeysOperation(PEER peer, int roomType, const char *nick,
	int num, const char **keys, void *callback, void *param, int opID);
int piNewConnectOperation(PEER peer, int type, const char *nick,
	int namespaceID, const char *email, const char *profilenick,
	const char *uniquenick, const char *password, const char *authtoken,
	const char *partnerchallenge, void *callback, void *param, int opID);
void piAddGetGlobalKeysCallback(PEER peer, int success, const char *nick,
	int num, const char **keys, const char **values, void *callback,
	void *param, int opID);
void piAddGetRoomKeysCallback(PEER peer, int success, int roomType,
	const char *nick, int num, const char **keys, const char **values,
	void *callback, void *param, int opID);
void chatSetGlobalKeysA(void *chat, int num, const char **keys,
	const char **values);
void chatSendUserMessageA(void *chat, const char *nick, const char *message,
	int messageType);
void chatSendChannelMessageA(void *chat, const char *channel,
	const char *message, int messageType);
void chatKickUserA(void *chat, const char *channel, const char *nick,
	const char *reason);
void chatSetQuietMode(void *chat, int quiet);
void chatSetChannelTopicA(void *chat, const char *channel, const char *topic);
void chatSetChannelPasswordA(void *chat, const char *channel, int enable,
	const char *password);
void chatSendRawA(void *chat, const char *command);
piPlayer *piGetPlayer(PEER peer, const char *nick);
typedef void (*piEnumRoomPlayersCallback)(PEER peer, int roomType,
	piPlayer *player, int index, void *param);
void piEnumRoomPlayers(PEER peer, int roomType,
	piEnumRoomPlayersCallback callback, void *param);
typedef void (*peerEnumPlayersCallback)(PEER peer, int success, int roomType,
	int index, const char *nick, int flags, void *param);
int chatGetBasicUserInfoNoWaitA(void *chat, const char *nick,
	const char **user, const char **address);
int piDemangleUser(const char *user, unsigned int *IP, int *profileID);
void piSetPlayerIPAndProfileID(PEER peer, const char *nick, unsigned int IP,
	int profileID);
void piAddGetPlayerIPCallback(PEER peer, int success, const char *nick,
	unsigned int IP, void *callback, void *param, int opID);
int piNewGetIPOperation(PEER peer, const char *nick, void *callback,
	void *param, int opID);
void piAddGetPlayerProfileIDCallback(PEER peer, int success,
	const char *nick, int profileID, void *callback, void *param, int opID);
int piNewGetProfileIDOperation(PEER peer, const char *nick, void *callback,
	void *param, int opID);
void piAddGetPlayerInfoCallback(PEER peer, int success, const char *nick,
	unsigned int IP, int profileID, void *callback, void *param, int opID);
int piNewGetPlayerInfoOperation(PEER peer, const char *nick, void *callback,
	void *param, int opID);
void piMangleGroupRoom(char *room, int groupID);
void piMangleTitleRoom(char *room, const char *title);
int piNewJoinRoomOperation(PEER peer, int roomType, const char *channel,
	const char *password, void *callback, void *param, int opID);
void piAddJoinRoomCallback(PEER peer, int success, int result, int roomType,
	void *callback, void *param, int opID);
void piStopHosting(PEER peer, int stopReporting);
int piNewCreateStagingRoomOperation(PEER peer, const char *name,
	const char *password, int maxPlayers, unsigned int socket,
	unsigned short port, void *callback, void *param, int opID);
void piLeaveRoom(PEER peer, int roomType, const char *reason);
void piStopReporting(PEER peer);
void piSBStopListingGames(PEER peer);
int piSBStartListingGames(PEER peer, const unsigned char *fields,
	int numFields, const char *filter);
void piAddListingGamesCallback(PEER peer, int success, void *server,
	int message);
char *goastrdup(const char *text);
int piNewAutoMatchOperation(PEER peer, unsigned int socket,
	unsigned short port, void *statusCallback, void *rateCallback, void *param,
	int opID);
void piAddAutoMatchStatusCallback(PEER peer);
__declspec(dllimport) void __cdecl free(void *memory);
void piSendChannelUTM(PEER peer, const char *channel, const char *command,
	const char *parameters, int authenticate);
typedef struct in_addr
{
	unsigned int s_addr;
} in_addr;
char *__stdcall inet_ntoa(in_addr address);
__declspec(dllimport) int __cdecl sprintf(char *buffer,
	const char *format, ...);
void peerMessageRoomA(PEER peer, int roomType, const char *message,
	int messageType);
void piSetLocalFlags(PEER peer);
int piStartReporting(PEER peer, unsigned int socket, unsigned short port);
void piSetAutoMatchStatus(PEER peer, int status);
void piSendStateChanged(PEER peer);
void piAddConnectCallback(PEER peer, int success, int failureReason,
	void *callback, void *param, int opID);
void bfmePiDisconnectCleanupFromEsi(void);
void msleep(unsigned int milliseconds);
void bfmePiThinkFromEsi(int opID);
int piIsOperationFinished(PEER peer, int opID);
int PeerOperationsComplete(PEER peer, int opID);
int piIsCallbackFinished(PEER peer, int opID);
void peerShutdown(PEER peer);
__declspec(dllimport) char *__cdecl strncpy(char *destination,
	const char *source, unsigned int count);

void peerChangeNickA(PEER peer, const char *newNick, void *callback,
	void *param, int blocking)
{
	piConnection *connection = (piConnection *)peer;
	int success = 1;
	int opID = piGetNextID(peer);

	if (!piNewChangeNickOperation(peer, newNick, callback, param, opID))
		success = 0;

	if (!success)
		piAddChangeNickCallback(peer, 0, connection->nick, newNick,
			callback, param, opID);

	if (blocking)
	{
		do
		{
			msleep(1);
			bfmePiThinkFromEsi(opID);
		}
		while (!piIsOperationFinished(peer, opID) ||
			!piIsCallbackFinished(peer, opID));

		if (connection->shutdown && connection->callbackDepth == 0)
			peerShutdown(peer);
	}
}

void peerGetPlayerGlobalKeysA(PEER peer, const char *nick, int num,
	const char **keys, void *callback, void *param, int blocking)
{
	piConnection *connection = (piConnection *)peer;
	int success = 1;
	int opID = piGetNextID(peer);

	if (!connection->connected)
		return;
	if (!nick || !nick[0])
		nick = connection->nick;

	if (!piNewGetGlobalKeysOperation(peer, nick, num, keys, callback, param,
			opID))
		success = 0;
	if (!success)
		piAddGetGlobalKeysCallback(peer, 0, nick, 0, 0, 0, callback, param,
			opID);

	if (blocking)
	{
		do
		{
			msleep(1);
			bfmePiThinkFromEsi(opID);
		}
		while (!piIsOperationFinished(peer, opID) ||
			!piIsCallbackFinished(peer, opID));

		if (connection->shutdown && connection->callbackDepth == 0)
			peerShutdown(peer);
	}
}

void peerConnectA(PEER peer, const char *nick, int profileID,
	void *nickErrorCallback, void *connectCallback, void *param, int blocking)
{
	piConnection *connection = (piConnection *)peer;
	int success = 1;
	int opID = piGetNextID(peer);

	if (connection->connected || connection->connecting)
		success = 0;
	if (success && !connection->title[0])
		success = 0;

	if (success)
	{
		connection->chat = 0;
		strncpy(connection->nick, nick, 64);
		connection->nick[63] = '\0';
		connection->connected = 0;
		connection->connecting = 1;
		connection->nickErrorCallback = nickErrorCallback;
		connection->profileID = profileID;
		connection->disconnect = 0;

		if (!piNewConnectOperation(peer, 0, nick, 0, 0, 0, 0, 0, 0, 0,
				connectCallback, param, opID))
		{
			success = 0;
			bfmePiDisconnectCleanupFromEsi();
		}
	}

	if (!success)
		piAddConnectCallback(peer, 0, 0, connectCallback, param, opID);

	if (blocking)
	{
		do
		{
			msleep(1);
			bfmePiThinkFromEsi(opID);
		}
		while (!PeerOperationsComplete(peer, opID) ||
			!piIsCallbackFinished(peer, opID));

		if (connection->shutdown && connection->callbackDepth == 0)
			peerShutdown(peer);
	}
}

void peerDisconnect(PEER peer)
{
	piConnection *connection = (piConnection *)peer;

	if (connection->callbackDepth > 0)
	{
		connection->disconnect = 1;
	}
	else
	{
		connection->stayInTitleRoom = 0;
		bfmePiDisconnectCleanupFromEsi();
		bfmePiThinkFromEsi(-1);
	}

	if (connection->shutdown && connection->callbackDepth == 0)
		peerShutdown(peer);
}

void peerConnectLoginA(PEER peer, int namespaceID, const char *email,
	const char *profilenick, const char *uniquenick, const char *password,
	void *nickErrorCallback, void *connectCallback, void *param, int blocking)
{
	piConnection *connection = (piConnection *)peer;
	int success = 1;
	int opID = piGetNextID(peer);

	if (connection->connected || connection->connecting)
		success = 0;
	if (success && !connection->title[0])
		success = 0;

	if (success)
	{
		connection->chat = 0;
		connection->nick[0] = '\0';
		connection->connected = 0;
		connection->connecting = 1;
		connection->nickErrorCallback = nickErrorCallback;
		connection->profileID = 0;
		connection->disconnect = 0;

		if (!piNewConnectOperation(peer,
				(uniquenick && uniquenick[0]) ? 1 : 2, 0, namespaceID,
				email, profilenick, uniquenick, password, 0, 0,
				connectCallback, param, opID))
		{
			success = 0;
			bfmePiDisconnectCleanupFromEsi();
		}
	}

	if (!success)
		piAddConnectCallback(peer, 0, 0, connectCallback, param, opID);

	if (blocking)
	{
		do
		{
			msleep(1);
			bfmePiThinkFromEsi(opID);
		}
		while (!PeerOperationsComplete(peer, opID) ||
			!piIsCallbackFinished(peer, opID));

		if (connection->shutdown && connection->callbackDepth == 0)
			peerShutdown(peer);
	}
}

void peerGetRoomKeysA(PEER peer, int roomType, const char *nick, int num,
	const char **keys, void *callback, void *param, int blocking)
{
	piConnection *connection = (piConnection *)peer;
	int success = 1;
	int opID = piGetNextID(peer);

	if (!connection->connected)
		return;
	if (!connection->enteringRoom[roomType] && !connection->inRoom[roomType])
		return;

	if (!piNewGetRoomKeysOperation(peer, roomType, nick, num, keys, callback,
			param, opID))
		success = 0;
	if (!success)
		piAddGetRoomKeysCallback(peer, 0, roomType, nick, 0, 0, 0,
			callback, param, opID);

	if (blocking)
	{
		do
		{
			msleep(1);
			bfmePiThinkFromEsi(opID);
		}
		while (!piIsOperationFinished(peer, opID) ||
			!piIsCallbackFinished(peer, opID));

		if (connection->shutdown && connection->callbackDepth == 0)
			peerShutdown(peer);
	}
}

void peerSetGlobalKeysA(PEER peer, int num, const char **keys,
	const char **values)
{
	piConnection *connection = (piConnection *)peer;

	if (!connection->connected)
		return;
	chatSetGlobalKeysA(connection->chat, num, keys, values);
}

const char *peerGetNickA(PEER peer)
{
	piConnection *connection = (piConnection *)peer;

	if (!connection->connected)
		return 0;
	return connection->nick;
}

void peerGetPlayerIPA(PEER peer, const char *nick, void *callback,
	void *param, int blocking)
{
	piConnection *connection = (piConnection *)peer;
	int success = 1;
	piPlayer *player;
	int opID = piGetNextID(peer);

	player = piGetPlayer(peer, nick);
	if (player && !player->gotIPAndProfileID)
	{
		const char *info;
		unsigned int IP;
		int profileID;

		if (chatGetBasicUserInfoNoWaitA(connection->chat, nick, &info, 0) &&
			piDemangleUser(info, &IP, &profileID))
			piSetPlayerIPAndProfileID(peer, nick, IP, profileID);
	}

	if (player && player->gotIPAndProfileID)
	{
		piAddGetPlayerIPCallback(peer, 1, nick, player->IP, callback, param,
			opID);
	}
	else if (!piNewGetIPOperation(peer, nick, callback, param, opID))
	{
		success = 0;
	}

	if (!success)
		piAddGetPlayerIPCallback(peer, 0, nick, 0, callback, param, opID);

	if (blocking)
	{
		do
		{
			msleep(1);
			bfmePiThinkFromEsi(opID);
		}
		while (!piIsOperationFinished(peer, opID) ||
			!piIsCallbackFinished(peer, opID));

		if (connection->shutdown && connection->callbackDepth == 0)
			peerShutdown(peer);
	}
}

void peerGetPlayerProfileIDA(PEER peer, const char *nick, void *callback,
	void *param, int blocking)
{
	piConnection *connection = (piConnection *)peer;
	int success = 1;
	piPlayer *player;
	int opID = piGetNextID(peer);

	player = piGetPlayer(peer, nick);
	if (player && !player->gotIPAndProfileID)
	{
		const char *info;
		unsigned int IP;
		int profileID;

		if (chatGetBasicUserInfoNoWaitA(connection->chat, nick, &info, 0) &&
			piDemangleUser(info, &IP, &profileID))
			piSetPlayerIPAndProfileID(peer, nick, IP, profileID);
	}

	if (player && player->gotIPAndProfileID)
	{
		piAddGetPlayerProfileIDCallback(peer, 1, nick, player->profileID,
			callback, param, opID);
	}
	else if (!piNewGetProfileIDOperation(peer, nick, callback, param, opID))
	{
		success = 0;
	}

	if (!success)
		piAddGetPlayerProfileIDCallback(peer, 0, nick, 0, callback, param,
			opID);

	if (blocking)
	{
		do
		{
			msleep(1);
			bfmePiThinkFromEsi(opID);
		}
		while (!piIsOperationFinished(peer, opID) ||
			!piIsCallbackFinished(peer, opID));

		if (connection->shutdown && connection->callbackDepth == 0)
			peerShutdown(peer);
	}
}

void peerGetPlayerInfoA(PEER peer, const char *nick, void *callback,
	void *param, int blocking)
{
	piConnection *connection = (piConnection *)peer;
	int success = 1;
	piPlayer *player;
	int opID = piGetNextID(peer);

	player = piGetPlayer(peer, nick);
	if (player && !player->gotIPAndProfileID)
	{
		const char *info;
		unsigned int IP;
		int profileID;

		if (chatGetBasicUserInfoNoWaitA(connection->chat, nick, &info, 0) &&
			piDemangleUser(info, &IP, &profileID))
			piSetPlayerIPAndProfileID(peer, nick, IP, profileID);
	}

	if (player && player->gotIPAndProfileID)
	{
		piAddGetPlayerInfoCallback(peer, 1, nick, player->IP,
			player->profileID, callback, param, opID);
	}
	else if (!piNewGetPlayerInfoOperation(peer, nick, callback, param, opID))
	{
		success = 0;
	}

	if (!success)
		piAddGetPlayerInfoCallback(peer, 0, nick, 0, 0, callback, param,
			opID);

	if (blocking)
	{
		do
		{
			msleep(1);
			bfmePiThinkFromEsi(opID);
		}
		while (!piIsOperationFinished(peer, opID) ||
			!piIsCallbackFinished(peer, opID));

		if (connection->shutdown && connection->callbackDepth == 0)
			peerShutdown(peer);
	}
}


void peerJoinGroupRoom(PEER peer, int groupID, void *callback, void *param,
	int blocking)
{
	piConnection *connection = (piConnection *)peer;
	int success = 1;
	int result = 10;
	char room[257];
	int opID = piGetNextID(peer);

	if (!connection->title[0])
	{
		success = 0;
		result = 6;
	}
	if (success && !connection->connected)
	{
		success = 0;
		result = 7;
	}
	if (success && connection->autoMatchStatus &&
		connection->autoMatchStatus != 5)
	{
		success = 0;
		result = 8;
	}
	if (success && !groupID)
		success = 0;
	if (success && (connection->enteringRoom[1] || connection->inRoom[1]))
	{
		success = 0;
		result = 5;
	}

	piMangleGroupRoom(room, groupID);
	connection->groupID = groupID;

	if (success && !piNewJoinRoomOperation(peer, 1, room, 0, callback, param,
			opID))
		success = 0;
	if (!success)
		piAddJoinRoomCallback(peer, 0, result, 1, callback, param, opID);

	if (blocking)
	{
		do
		{
			msleep(1);
			bfmePiThinkFromEsi(opID);
		}
		while (!piIsOperationFinished(peer, opID) ||
			!piIsCallbackFinished(peer, opID));

		if (connection->shutdown && connection->callbackDepth == 0)
			peerShutdown(peer);
	}
}

void peerJoinTitleRoomA(PEER peer, const char *password, void *callback,
	void *param, int blocking)
{
	piConnection *connection = (piConnection *)peer;
	int success = 1;
	int result = 10;
	char room[257];
	int opID = piGetNextID(peer);

	if (!password)
		password = "";
	if (!connection->title[0])
	{
		success = 0;
		result = 6;
	}
	if (success && !connection->connected)
	{
		success = 0;
		result = 7;
	}
	if ((success && connection->enteringRoom[0]) || connection->inRoom[0])
	{
		success = 0;
		result = 5;
	}
	if (success && connection->autoMatchStatus &&
		connection->autoMatchStatus != 5)
	{
		success = 0;
		result = 8;
	}

	if (success)
	{
		if (connection->titleRoomChannel[0])
		{
			const char *source = connection->titleRoomChannel;
			char *destination = room;
			while ((*destination++ = *source++) != '\0')
			{
			}
		}
		else
		{
			piMangleTitleRoom(room, connection->title);
		}
	}

	if (success && !piNewJoinRoomOperation(peer, 0, room, password, callback,
			param, opID))
		success = 0;
	if (!success)
		piAddJoinRoomCallback(peer, 0, result, 0, callback, param, opID);

	if (blocking)
	{
		do
		{
			msleep(1);
			bfmePiThinkFromEsi(opID);
		}
		while (!piIsOperationFinished(peer, opID) ||
			!piIsCallbackFinished(peer, opID));

		if (connection->shutdown && connection->callbackDepth == 0)
			peerShutdown(peer);
	}
}

void peerCreateStagingRoomWithSocketA(PEER peer, const char *name,
	int maxPlayers, const char *password, unsigned int socket,
	unsigned short port, void *callback, void *param, int blocking)
{
	piConnection *connection = (piConnection *)peer;
	int success = 1;
	int result = 10;
	int opID = piGetNextID(peer);

	if (!password)
		password = "";
	if (!connection->title[0])
	{
		success = 0;
		result = 6;
	}
	if (success && !connection->connected)
	{
		success = 0;
		result = 7;
	}
	if (success && (connection->enteringRoom[2] || connection->inRoom[2]))
	{
		success = 0;
		result = 5;
	}
	if (success && connection->autoMatchStatus &&
		connection->autoMatchStatus != 5)
	{
		success = 0;
		result = 8;
	}

	if (success)
		piStopHosting(peer, 1);
	if (success && !piNewCreateStagingRoomOperation(peer, name, password,
			maxPlayers, socket, port, callback, param, opID))
		success = 0;
	if (!success)
		piAddJoinRoomCallback(peer, 0, result, 2, callback, param, opID);

	if (blocking)
	{
		do
		{
			msleep(1);
			bfmePiThinkFromEsi(opID);
		}
		while (!piIsOperationFinished(peer, opID) ||
			!piIsCallbackFinished(peer, opID));

		if (connection->shutdown && connection->callbackDepth == 0)
			peerShutdown(peer);
	}
}

void peerStartAutoMatchWithSocketA(PEER peer, int maxPlayers,
	const char *filter, unsigned int socket, unsigned short port,
	void *statusCallback, void *rateCallback, void *param, int blocking)
{
	piConnection *connection = (piConnection *)peer;
	int opID = piGetNextID(peer);

	if (!filter)
		filter = "";
	if (!connection->title[0])
		goto failed;
	if (!connection->connected)
		goto failed;
	if (connection->autoMatchStatus && connection->autoMatchStatus != 5)
		goto failed;

	if (connection->enteringRoom[2])
		piLeaveRoom(peer, 2, "");
	piStopReporting(peer);
	piSBStopListingGames(peer);

	connection->maxPlayers = maxPlayers;
	connection->autoMatchFilter = goastrdup(filter);
	if (!connection->autoMatchFilter)
		goto failed;

	connection->autoMatchStatus = 0;
	connection->autoMatchSBFailed = 0;
	connection->autoMatchQRFailed = 0;
	if (!piNewAutoMatchOperation(peer, socket, port, statusCallback,
			rateCallback, param, opID))
	{
		free(connection->autoMatchFilter);
		goto failed;
	}

	if (blocking)
	{
		do
		{
			msleep(1);
			bfmePiThinkFromEsi(opID);
		}
		while (!piIsOperationFinished(peer, opID) ||
			!piIsCallbackFinished(peer, opID));

		if (connection->shutdown && connection->callbackDepth == 0)
			peerShutdown(peer);
	}
	return;

failed:
	connection->autoMatchStatus = 0;
	piAddAutoMatchStatusCallback(peer);
}

void peerStartGameA(PEER peer, const char *message, int reportingOptions)
{
	piConnection *connection = (piConnection *)peer;
	char buffer[32];
	in_addr address;

	if (!connection->title[0])
		return;
	if (!connection->connected)
		return;
	if (!connection->inRoom[2])
		return;
	if (!connection->hosting)
		return;
	if (!message)
		message = "";

	piSendChannelUTM(peer, connection->room[2], "GML", message, 0);
	address.s_addr = connection->publicIP;
	sprintf(buffer, "@@@GML %s/OLD", inet_ntoa(address));
	peerMessageRoomA(peer, 2, buffer, 0);

	connection->playing = 1;
	piSetLocalFlags(peer);
	if (connection->autoMatchStatus && connection->autoMatchStatus != 5)
	{
		piSetAutoMatchStatus(peer, 5);
	}
	else if (connection->queryReporting)
	{
		if (reportingOptions & 1)
			piStopReporting(peer);
		else
		{
			connection->reportingOptions = reportingOptions;
			piSendStateChanged(peer);
		}
	}
}

void peerSetReady(PEER peer, int ready)
{
	piConnection *connection = (piConnection *)peer;
	char buffer[32];

	if (!connection->title[0])
		return;
	if (!connection->connected)
		return;
	if (!connection->inRoom[2])
		return;
	if (connection->ready == ready)
		return;

	connection->ready = ready;
	piSetLocalFlags(peer);
	strcpy(buffer, "@@@NFO \\$flags$\\");
	if (ready)
		strcat(buffer, "r");
	strcat(buffer, "X\\");
	peerMessageRoomA(peer, 2, buffer, 0);
}

int peerGetPlayerInfoNoWaitA(PEER peer, const char *nick,
	unsigned int *IP, int *profileID)
{
	piConnection *connection = (piConnection *)peer;
	piPlayer *player = piGetPlayer(peer, nick);

	if (!player || !player->gotIPAndProfileID)
	{
		const char *info;
		unsigned int localIP;
		int localProfileID;

		if (chatGetBasicUserInfoNoWaitA(connection->chat, nick, &info, 0) &&
			piDemangleUser(info, &localIP, &localProfileID))
		{
			if (player)
				piSetPlayerIPAndProfileID(peer, nick, localIP,
					localProfileID);
			if (IP)
				*IP = localIP;
			if (profileID)
				*profileID = localProfileID;
			return 1;
		}
		return 0;
	}

	if (IP)
		*IP = player->IP;
	if (profileID)
		*profileID = player->profileID;
	return 1;
}

void peerMessagePlayerA(PEER peer, const char *nick, const char *message,
	int messageType)
{
	piConnection *connection = (piConnection *)peer;

	if (!connection->connected)
		return;
	if (!message || !message[0])
		return;
	chatSendUserMessageA(connection->chat, nick, message, messageType);
}

void peerKickPlayerA(PEER peer, int roomType, const char *nick,
	const char *reason)
{
	piConnection *connection = (piConnection *)peer;

	if (!connection->connected)
		return;
	chatKickUserA(connection->chat, connection->room[roomType], nick, reason);
}

int peerGetPlayerPingA(PEER peer, const char *nick, int *ping)
{
	piPlayer *player = piGetPlayer(peer, nick);

	if (!player)
		return 0;
	if (player->local)
	{
		*ping = 0;
	}
	else
	{
		if (!player->numPings)
			return 0;
		*ping = player->pingAverage;
	}
	return 1;
}

int peerPingPlayerA(PEER peer, const char *nick)
{
	piPlayer *player = piGetPlayer(peer, nick);

	if (!player)
		return 0;
	if (player->local)
		return 0;
	if (!player->gotIPAndProfileID)
		return 0;
	if (player->waitingForPing)
		return 1;

	player->mustPing = 1;
	if (!player->inPingRoom)
		player->pingOnce = 1;
	return 1;
}

void peerStayInRoom(PEER peer, int roomType)
{
	piConnection *connection = (piConnection *)peer;

	if (roomType != 0)
		return;
	if (!connection->title[0])
		return;
	connection->stayInTitleRoom = 1;
}

void peerSetQuietMode(PEER peer, int quiet)
{
	piConnection *connection = (piConnection *)peer;

	chatSetQuietMode(connection->chat, quiet);
}

void peerSetGroupID(PEER peer, int groupID)
{
	piConnection *connection = (piConnection *)peer;

	if (!connection->title[0])
		return;
	if (!connection->connected)
		return;
	connection->groupID = groupID;
}

int peerGetGroupID(PEER peer)
{
	piConnection *connection = (piConnection *)peer;

	if (!connection->title[0])
		return 0;
	if (!connection->connected)
		return 0;
	return connection->groupID;
}

int peerInRoom(PEER peer, int roomType)
{
	piConnection *connection = (piConnection *)peer;

	return connection->inRoom[roomType];
}

const char *peerGetRoomChannelA(PEER peer, int roomType)
{
	piConnection *connection = (piConnection *)peer;

	if (!connection->inRoom[roomType] && !connection->enteringRoom[roomType])
		return 0;
	return connection->room[roomType];
}

const char *peerGetRoomNameA(PEER peer, int roomType)
{
	piConnection *connection = (piConnection *)peer;

	if (!connection->inRoom[roomType])
		return 0;
	return connection->names[roomType];
}

void peerSetRoomNameA(PEER peer, int roomType, const char *name)
{
	piConnection *connection = (piConnection *)peer;

	if (!name)
		name = "";
	if (!connection->title[0])
		return;
	if (!connection->connected)
		return;
	if (!connection->enteringRoom[roomType] &&
		!connection->inRoom[roomType])
		return;
	if (!connection->hosting)
		return;
	chatSetChannelTopicA(connection->chat, connection->room[roomType], name);
}

void peerSetPasswordA(PEER peer, int roomType, const char *password)
{
	piConnection *connection = (piConnection *)peer;

	if (roomType != 2)
		return;
	if (!password)
		password = "";
	if (!connection->title[0])
		return;
	if (!connection->connected)
		return;
	if (!connection->enteringRoom[roomType] &&
		!connection->inRoom[roomType])
		return;
	if (!connection->hosting)
		return;

	if (password[0])
		chatSetChannelPasswordA(connection->chat,
			connection->room[roomType], 1, password);
	else
		chatSetChannelPasswordA(connection->chat,
			connection->room[roomType], 0, "x");
	connection->passwordedRoom = password[0] != 0;
	piSendStateChanged(peer);
}

void peerSetTitleRoomChannelA(PEER peer, const char *channel)
{
	piConnection *connection = (piConnection *)peer;

	if (!connection->title[0])
		return;
	if (!connection->connected)
		return;
	if (!channel)
		channel = "";
	strncpy(connection->titleRoomChannel, channel, 257);
	connection->titleRoomChannel[256] = '\0';
}

void *peerGetHostServer(PEER peer)
{
	piConnection *connection = (piConnection *)peer;

	return connection->hostServer;
}

void peerSetAwayModeA(PEER peer, const char *reason)
{
	piConnection *connection = (piConnection *)peer;
	char buffer[134];

	if (!reason)
		reason = "";
	connection->away = reason[0] != '\0';
	strncpy(connection->awayReason, reason, 128);
	connection->awayReason[127] = '\0';
	piSetLocalFlags(peer);
	sprintf(buffer, "AWAY :%s", connection->awayReason);
	chatSendRawA(connection->chat, buffer);
}

void peerStartPlaying(PEER peer)
{
	piConnection *connection = (piConnection *)peer;

	if (!connection->title[0])
		return;
	connection->playing = 1;
	piSetLocalFlags(peer);
}

int peerIsPlaying(PEER peer)
{
	piConnection *connection = (piConnection *)peer;

	if (!connection->title[0])
		return 0;
	if (!connection->connected)
		return 0;
	return connection->playing;
}

int peerStartReportingWithSocket(PEER peer, unsigned int socket,
	unsigned short port)
{
	piConnection *connection = (piConnection *)peer;

	if (!connection->title[0])
		return 0;
	if (!piStartReporting(peer, socket, port))
		return 0;
	return 1;
}

int peerStartReporting(PEER peer)
{
	return peerStartReportingWithSocket(peer, (unsigned int)-1, 0);
}

void peerMessageRoomA(PEER peer, int roomType, const char *message,
	int messageType)
{
	piConnection *connection = (piConnection *)peer;

	if (!message || !message[0])
		return;
	if (!connection->inRoom[roomType])
		return;
	chatSendChannelMessageA(connection->chat, connection->room[roomType],
		message, messageType);
}

void peerUTMRoomA(PEER peer, int roomType, const char *command,
	const char *parameters, int authenticate)
{
	piConnection *connection = (piConnection *)peer;

	if (!connection->inRoom[roomType])
		return;
	piSendChannelUTM(peer, connection->room[roomType], command, parameters,
		authenticate);
}

void peerStartAutoMatchA(PEER peer, int maxPlayers, const char *filter,
	void *statusCallback, void *rateCallback, void *param, int blocking)
{
	peerStartAutoMatchWithSocketA(peer, maxPlayers, filter,
		(unsigned int)-1, 0, statusCallback, rateCallback, param, blocking);
}

void peerStartListingGamesA(PEER peer, const unsigned char *fields,
	int numFields, const char *filter, void *callback, void *param)
{
	piConnection *connection = (piConnection *)peer;
	int success;

	if (!connection->title[0])
		return;
	if (filter && !filter[0])
		filter = 0;
	if (!fields || numFields <= 0)
		numFields = 0;

	connection->gameListCallback = callback;
	connection->gameListParam = param;
	success = piSBStartListingGames(peer, fields, numFields, filter);
	if (!success)
		piAddListingGamesCallback(peer, 0, 0, 0);
}

void peerStopListingGames(PEER peer)
{
	piConnection *connection = (piConnection *)peer;

	if (!connection->title[0])
		return;
	piSBStopListingGames(peer);
}

typedef struct piEnumPlayersData
{
	peerEnumPlayersCallback callback;
	void *param;
} piEnumPlayersData;

static void piEnumPlayersEnumRoomPlayersCallback(PEER peer, int roomType,
	piPlayer *player, int index, void *param)
{
	piEnumPlayersData *data = (piEnumPlayersData *)param;
	const char *nick;
	int flags;

	if (player)
	{
		nick = player->nick;
		flags = player->flags[roomType];
	}
	else
	{
		nick = 0;
		flags = 0;
	}
	data->callback(peer, 1, roomType, index, nick, flags, data->param);
}

void peerEnumPlayers(PEER peer, int roomType,
	peerEnumPlayersCallback callback, void *param)
{
	piConnection *connection = (piConnection *)peer;
	piEnumPlayersData data;

	if (!connection->inRoom[roomType])
	{
		callback(peer, 0, roomType, -1, 0, 0, param);
		return;
	}
	data.callback = callback;
	data.param = param;
	piEnumRoomPlayers(peer, roomType,
		piEnumPlayersEnumRoomPlayersCallback, &data);
}




void peerAlwaysGetPlayerInfo(PEER peer, int always)
{
	piConnection *connection = (piConnection *)peer;

	connection->alwaysRequestPlayerInfo = always;
}



int peerGetReadyA(PEER peer, const char *nick, int *ready)
{
	piConnection *connection = (piConnection *)peer;
	piPlayer *player;

	if (!connection->title[0])
		return 0;
	if (!connection->connected)
		return 0;
	if (!connection->inRoom[2])
		return 0;

	player = piGetPlayer(peer, nick);
	if (!player || !player->inRoom[2])
		return 0;
	*ready = (player->flags[2] & 2) != 0;
	return 1;
}

static void piAreAllReadyEnumRoomPlayersCallback(PEER peer, int roomType,
	piPlayer *player, int index, void *param)
{
	if (player && !(player->flags[2] & 2))
		*(int *)param = 0;
}

int peerAreAllReady(PEER peer)
{
	piConnection *connection = (piConnection *)peer;
	int allReady;

	if (!connection->title[0])
		return 0;
	if (!connection->connected)
		return 0;
	if (!connection->inRoom[2])
		return 0;

	allReady = 1;
	piEnumRoomPlayers(peer, 2, piAreAllReadyEnumRoomPlayersCallback,
		&allReady);
	return allReady;
}
