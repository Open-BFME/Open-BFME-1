// cl: /O2 /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerSB.c */

#include <stdio.h>
#include <string.h>

typedef struct PEERConnection
{
	unsigned char pad_0000[0x09A8];
	int groupID;
	unsigned char pad_09AC[0x01F4];
	int sbInitialized;
	unsigned char gameList[0x0B98];
	unsigned char gameEngine[0x0050];
	int initialGameList;
} PEERConnection;

typedef PEERConnection *PEER;
typedef int PEERBool;

extern const char *qr2_registered_key_list[];

void SBServerListDisconnect(void *serverList);
void SBEngineHaltUpdates(void *queryEngine);
void piClearCallbacks(PEER peer, int type);
void SBServerListClear(void *serverList);
void SBQueryEngineAddQueryKey(void *queryEngine, unsigned char key);
int SBServerListConnectAndQuery(
	void *serverList, const char *fields, const char *filter,
	int queryType, int disconnectOnComplete);
void piAddListingGamesCallback(
	PEER peer, int success, void *server, int message);

static __forceinline void piSBStopListingGames(PEER peer)
{
	if (!peer->sbInitialized)
		return;
	SBServerListDisconnect(&peer->gameList);
	SBEngineHaltUpdates(&peer->gameEngine);
	piClearCallbacks(peer, 3);
}

PEERBool piSBStartListingGames(
	PEER peer, const unsigned char *fields, int numFields, const char *filter)
{
	char groupFilter[32];
	char smartSpyFilter[256];
	char fullFields[256];
	int listLen;
	int keyLen;
	int i;

	if (!peer->sbInitialized)
		return 0;

	piSBStopListingGames(peer);
	SBServerListClear(&peer->gameList);

	if (peer->groupID)
		sprintf(groupFilter, "groupid=%d", peer->groupID);
	else
		strcpy(groupFilter, "groupid is null");

	if (filter) {
		sprintf(smartSpyFilter, "(%s) AND (", groupFilter);
		strncat(smartSpyFilter, filter, 255 - strlen(smartSpyFilter));
		smartSpyFilter[254] = '\0';
		strcat(smartSpyFilter, ")");
	} else {
		strcpy(smartSpyFilter, groupFilter);
	}

	*(int *)(&peer->gameEngine[0x3c]) = 0;
	strcpy(fullFields, "\\hostname\\gamemode");
	listLen = (int)strlen(fullFields);
	SBQueryEngineAddQueryKey(&peer->gameEngine, 1);
	SBQueryEngineAddQueryKey(&peer->gameEngine, 11);

	for (i = 0; i < numFields; i++) {
		const char *key = qr2_registered_key_list[fields[i]];
		keyLen = (int)strlen(key);
		if ((listLen + keyLen + 1) >= 256)
			break;
		listLen += sprintf(fullFields + listLen, "\\%s", key);
		SBQueryEngineAddQueryKey(&peer->gameEngine, fields[i]);
	}

	if (SBServerListConnectAndQuery(
			&peer->gameList, fullFields, smartSpyFilter, 4, 0) != 0) {
		piSBStopListingGames(peer);
		return 0;
	}

	peer->initialGameList = 1;
	piAddListingGamesCallback(peer, 1, 0, 3);
	return 1;
}
