// cl: /O2 /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerSB.c */

typedef int PEERBool;

typedef struct SBServerRecord
{
	unsigned char pad_0000[0x14];
	unsigned char state;
} SBServerRecord;

typedef SBServerRecord *SBServer;

typedef struct SBServerList
{
	unsigned char pad_0000[0x498];
	unsigned int mypublicip;
} SBServerList;

typedef SBServerList *SBServerListPtr;

typedef enum SBListCallbackReason
{
	slc_serveradded,
	slc_serverupdated,
	slc_serverdeleted,
	slc_initiallistcomplete,
	slc_disconnected,
	slc_queryerror,
	slc_publicipdetermined
} SBListCallbackReason;

typedef struct SBQueryEngine
{
	unsigned char pad_0000[0x10];
	int querylistCount;
	unsigned char pad_0014[0x34];
} SBQueryEngine;

typedef enum SBQueryEngineCallbackReason
{
	qe_updatesuccess,
	qe_updatefailed,
	qe_engineidle
} SBQueryEngineCallbackReason;

typedef struct piOperation
{
	unsigned char pad_0000[0x30];
	unsigned short port;
} piOperation;

typedef struct PEERConnection
{
	unsigned char pad_0000[0x54];
	unsigned int publicIP;
	unsigned int privateIP;
	unsigned char pad_005C[0x384 - 0x5C];
	int enteringRoom[3];
	int inRoom[3];
	unsigned char pad_039C[0x173C - 0x39C];
	SBQueryEngine gameEngine;
	unsigned char pad_1784[0x18D4 - 0x1784];
	int autoMatchStatus;
	unsigned char autoMatchList[0x05CC];
	SBQueryEngine autoMatchEngine;
	int autoMatchBrowsing;
	piOperation *autoMatchOperation;
	int autoMatchReporting;
	char *autoMatchFilter;
	int autoMatchSBFailed;
	int autoMatchQRFailed;
} PEERConnection;

typedef PEERConnection *PEER;

unsigned int SBServerGetPublicInetAddress(SBServer server);
int SBServerHasPrivateAddress(SBServer server);
unsigned int SBServerGetPrivateInetAddress(SBServer server);
unsigned short SBServerGetPrivateQueryPort(SBServer server);
unsigned short SBServerGetPublicQueryPort(SBServer server);
unsigned short SBServerGetPublicQueryPortNBO(SBServer server);
int SBServerHasFullKeys(SBServer server);
int SBServerDirectConnect(SBServer server);
int SBServerGetIntValueA(SBServer server, const char *key, int defaultValue);
void SBGetServerRulesFromMaster(
	void *serverList, unsigned int publicIP, unsigned short publicPort);
void SBQueryEngineUpdateServer(
	SBQueryEngine *engine, SBServer server, int addfront, int querytype);
void SBQueryEngineRemoveServerFromFIFOs(SBQueryEngine *engine, SBServer server);
void SBQueryEngineSetPublicIP(SBQueryEngine *engine, unsigned int publicIP);
int SBServerListCount(void *serverList);
SBServer SBServerListNth(void *serverList, int index);
void SBServerListRemoveAt(void *serverList, int index);
void SBServerAddIntKeyValue(SBServer server, const char *key, int value);
void SBServerListSort(void *serverList, int ascending, const char *sortkey,
	int comparemode);
int piCallAutoMatchRateCallback(PEER peer, SBServer server);
void piStopAutoMatchReporting(PEER peer);
void piLeaveRoom(PEER peer, int roomType, const char *reason);
int piJoinAutoMatchRoom(PEER peer, SBServer server);
void piSetAutoMatchStatus(PEER peer, int status);

static __declspec(noinline) PEERBool piIsLocalServer(PEER peer, SBServer server)
{
	if (SBServerGetPublicInetAddress(server) != peer->publicIP)
		return 0;

	if (SBServerHasPrivateAddress(server))
	{
		if (SBServerGetPrivateInetAddress(server) != peer->privateIP)
			return 0;

		if (SBServerGetPrivateQueryPort(server) != peer->autoMatchOperation->port)
			return 0;
	}
	else if (SBServerGetPublicQueryPort(server) != peer->autoMatchOperation->port)
	{
		return 0;
	}

	return 1;
}

static __declspec(noinline) int piSBAutoMatchGetServerRating(PEER peer, SBServer server)
{
	if (peer->autoMatchReporting && piIsLocalServer(peer, server))
		return 0;

	if (!SBServerHasFullKeys(server))
		return 0;

	if (SBServerGetIntValueA(server, "numplayers", 0) >=
		SBServerGetIntValueA(server, "maxplayers", 0))
		return 0;

	return piCallAutoMatchRateCallback(peer, server);
}

static __declspec(noinline) void piSBAutoMatchCheckUpdatedServer(PEER peer, SBServer server)
{
	int rating;

	if (peer->autoMatchStatus != 2)
		return;
	if (peer->enteringRoom[2])
		return;

	rating = piSBAutoMatchGetServerRating(peer, server);
	if (rating <= 0)
		return;

	piStopAutoMatchReporting(peer);
	piLeaveRoom(peer, 2, "");
	if (!piJoinAutoMatchRoom(peer, server))
		piSetAutoMatchStatus(peer, 0);
}

void piSBAutoMatchListCallback
(
	SBServerListPtr serverlist,
	SBListCallbackReason reason,
	SBServer server,
	void *instance
)
{
	PEER peer = (PEER)instance;

	switch (reason)
	{
	case slc_serveradded:
		if (server->state & (0x02 | 0x08))
			break;

		if (!SBServerDirectConnect(server))
			SBGetServerRulesFromMaster(&peer->autoMatchList,
				SBServerGetPublicInetAddress(server),
				SBServerGetPublicQueryPortNBO(server));
		else
			SBQueryEngineUpdateServer(&peer->autoMatchEngine, server, 0, 1);
		break;

	case slc_serverupdated:
		if (!SBServerHasFullKeys(server))
			SBQueryEngineUpdateServer(&peer->autoMatchEngine, server, 0, 1);
		else if (!SBServerDirectConnect(server))
			piSBAutoMatchCheckUpdatedServer(peer, server);
		break;

	case slc_serverdeleted:
		if ((server->state & (0x04 | 0x08)) != 0)
			SBQueryEngineRemoveServerFromFIFOs(&peer->autoMatchEngine, server);
		break;

	case slc_initiallistcomplete:
		if (!SBServerListCount(&peer->autoMatchList) ||
			peer->autoMatchEngine.querylistCount == 0)
			piSetAutoMatchStatus(peer, 2);
		break;

	case slc_queryerror:
		peer->autoMatchSBFailed = 1;
		if (peer->autoMatchStatus == 1)
			piSetAutoMatchStatus(peer,
				peer->autoMatchQRFailed ? 0 : 2);
		break;

	case slc_publicipdetermined:
		peer->publicIP = serverlist->mypublicip;
		SBQueryEngineSetPublicIP(&peer->gameEngine, serverlist->mypublicip);
		break;

	default:
		break;
	}
}

void piSBAutoMatchEngineCallback
(
	SBQueryEngine *engine,
	SBQueryEngineCallbackReason reason,
	SBServer server,
	void *instance
)
{
	PEER peer = (PEER)instance;
	int i;
	int count;
	int rating;

	switch (reason)
	{
	case qe_updatesuccess:
		piSBAutoMatchCheckUpdatedServer(peer, server);
		break;

	case qe_updatefailed:
		if (!SBServerListCount(&peer->autoMatchList))
			piSetAutoMatchStatus(peer, 2);
		break;

	case qe_engineidle:
		if (peer->autoMatchStatus != 1)
			return;
		if (peer->inRoom[2] || peer->enteringRoom[2])
			return;

		count = SBServerListCount(&peer->autoMatchList);
		for (i = count - 1; i >= 0; i--)
		{
			server = SBServerListNth(&peer->autoMatchList, i);
			rating = piSBAutoMatchGetServerRating(peer, server);
			if (rating <= 0)
			{
				SBServerListRemoveAt(&peer->autoMatchList, i);
				continue;
			}

			SBServerAddIntKeyValue(server, "gsi_am_rating", rating);
		}

		count = SBServerListCount(&peer->autoMatchList);
		if (!count)
		{
			piSetAutoMatchStatus(peer, 2);
			return;
		}

		SBServerListSort(&peer->autoMatchList, 1, "gsi_am_rating", 0);
		if (!piJoinAutoMatchRoom(peer,
			SBServerListNth(&peer->autoMatchList, 0)))
			piSetAutoMatchStatus(peer, 0);
		break;

	default:
		break;
	}

	(void)engine;
}

void piSBAutoMatchCheckUpdatedServerCaller(PEER peer, SBServer server)
{
	piSBAutoMatchCheckUpdatedServer(peer, server);
}
