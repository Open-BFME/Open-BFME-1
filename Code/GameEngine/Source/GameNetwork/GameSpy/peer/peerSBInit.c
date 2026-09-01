// cl: /O2 /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerSB.c */

#include <string.h>

typedef struct PEERConnection
{
	unsigned char pad_0000[0x0060];
	char title[0x0AF0];
	void *hostServer;
	unsigned char pad_0B54[4];
	char sbName[0x20];
	char sbSecretKey[0x20];
	int sbGameVersion;
	int sbMaxUpdates;
	int sbInitialized;
	unsigned char gameList[0x05CC];
	unsigned char groupList[0x05CC];
	unsigned char gameEngine[0x019C];
	unsigned char autoMatchList[0x05CC];
	unsigned char autoMatchEngine[1];
} PEERConnection;

typedef PEERConnection *PEER;

extern int piSBQueryVersion;

void piSBGamesListCallback(void);
void piSBGamesEngineCallback(void);
void piSBGroupsListCallback(void);
void piSBAutoMatchListCallback(void);
void piSBAutoMatchEngineCallback(void);

void SBServerListInit(
	void *serverList, const char *title, const char *gameName,
	const char *secretKey, int gameVersion,
	void (*callback)(void), void *instance);
void SBQueryEngineInit(
	void *queryEngine, int maxUpdates, int queryVersion,
	void (*callback)(void), void *instance);

int piSBInit(PEER peer)
{
	char autoMatchTitle[32];

	memset(&peer->gameList, 0, sizeof(peer->gameList));
	SBServerListInit(&peer->gameList, peer->title, peer->sbName,
		peer->sbSecretKey, peer->sbGameVersion,
		piSBGamesListCallback, peer);
	SBQueryEngineInit(&peer->gameEngine, peer->sbMaxUpdates,
		piSBQueryVersion, piSBGamesEngineCallback, peer);

	memset(&peer->groupList, 0, sizeof(peer->groupList));
	SBServerListInit(&peer->groupList, peer->title, peer->sbName,
		peer->sbSecretKey, peer->sbGameVersion,
		piSBGroupsListCallback, peer);

	strncpy(autoMatchTitle, peer->title, sizeof(autoMatchTitle));
	autoMatchTitle[sizeof(autoMatchTitle) - 1] = '\0';
	strncat(autoMatchTitle, "am", sizeof(autoMatchTitle) - strlen(autoMatchTitle));
	autoMatchTitle[sizeof(autoMatchTitle) - 1] = '\0';

	memset(&peer->autoMatchList, 0, sizeof(peer->autoMatchList));
	SBServerListInit(&peer->autoMatchList, autoMatchTitle, peer->sbName,
		peer->sbSecretKey, peer->sbGameVersion,
		piSBAutoMatchListCallback, peer);
	SBQueryEngineInit(&peer->autoMatchEngine, peer->sbMaxUpdates,
		piSBQueryVersion, piSBAutoMatchEngineCallback, peer);

	peer->hostServer = 0;
	peer->sbInitialized = 1;
	return 1;
}
