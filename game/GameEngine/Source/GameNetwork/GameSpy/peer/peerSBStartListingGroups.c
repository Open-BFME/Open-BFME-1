// cl: /O2 /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerSB.c */

#include <string.h>

typedef struct PEERConnection
{
	unsigned char pad_0000[0x0BA0];
	int sbInitialized;
	unsigned char gameList[0x05CC];
	unsigned char groupList[0x05CC];
	unsigned char gameEngine[1];
} PEERConnection;

typedef PEERConnection *PEER;
typedef int PEERBool;

void SBServerListDisconnect(void *serverList);
void SBServerListClear(void *serverList);
void SBEngineHaltUpdates(void *queryEngine);
int SBServerListConnectAndQuery(
	void *serverList, const char *fields, const char *filter,
	int queryType, int disconnectOnComplete);
void piClearCallbacks(PEER peer, int type);

PEERBool piSBStartListingGroups(PEER peer, const char *fields)
{
	char fullFields[257];
	size_t len;

	if (!peer->sbInitialized)
		return 0;

	SBServerListDisconnect(&peer->groupList);
	SBServerListClear(&peer->groupList);

	strcpy(fullFields,
		"\\hostname\\numwaiting\\maxwaiting\\numservers\\numplayers");
	len = strlen(fullFields);
	strncpy(fullFields + len, fields, 256 - len);
	fullFields[255] = '\0';

	if (SBServerListConnectAndQuery(
			&peer->groupList, fullFields, "", 32, 0) != 0) {
		/* The retail SDK build stops the game-list side on this failure. */
		if (peer->sbInitialized) {
			SBServerListDisconnect(&peer->gameList);
			SBEngineHaltUpdates(&peer->gameEngine);
			piClearCallbacks(peer, 3);
		}
		return 0;
	}

	return 1;
}
