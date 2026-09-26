// cl: /O2 /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerSB.c, 2007 game-list callback reconstruction.
   Retail uses the four-argument SBServerList callback ABI and the 2004
   query-engine arity.  These declarations are TU-local views of the retail
   layouts; the body follows the authentic first callback in peerSB.c. */

typedef enum
{
	PEERFalse,
	PEERTrue
} PEERBool;

typedef struct SBServerList SBServerList;
typedef SBServerList *SBServerListPtr;

typedef struct SBServer SBServer;
typedef SBServer *SBServerPtr;

typedef struct SBQueryEngine SBQueryEngine;

typedef enum
{
	slc_serveradded,
	slc_serverupdated,
	slc_serverdeleted,
	slc_initiallistcomplete,
	slc_disconnected,
	slc_queryerror,
	slc_publicipdetermined
} SBListCallbackReason;

typedef struct piConnection piConnection;
typedef piConnection *PEER;

struct SBServerList
{
	unsigned char reserved[0x498];
	unsigned int mypublicip;
};

struct SBServer
{
	unsigned char reserved[0x14];
	unsigned char state;
};

struct SBQueryEngine
{
	unsigned char reserved[0x50];
};

struct piConnection
{
	unsigned char reserved0[0x54];
	unsigned int publicIP;
	unsigned char reserved1[0x16e4];
	SBQueryEngine gameEngine;
	int initialGameList;
};

void piAddListingGamesCallback
(
	PEER peer,
	PEERBool success,
	SBServer *server,
	int message
);

int SBServerHasBasicKeys(SBServer *server);
void SBQueryEngineUpdateServer
(
	SBQueryEngine *engine,
	SBServer *server,
	int addfront,
	int querytype
);
void SBQueryEngineRemoveServerFromFIFOs(SBQueryEngine *engine, SBServer *server);
void SBQueryEngineSetPublicIP(SBQueryEngine *engine, unsigned int mypublicip);

void piSBGamesListCallback
(
	SBServerListPtr serverlist,
	SBListCallbackReason reason,
	SBServer *server,
	void *instance
)
{
	PEER peer = (PEER)instance;
	piConnection *connection = (piConnection *)peer;

	switch(reason)
	{
	case slc_serveradded:
		piAddListingGamesCallback(peer, PEERTrue, server, 0);
		if(!SBServerHasBasicKeys(server))
			SBQueryEngineUpdateServer(&connection->gameEngine, server, 0, 0);
		break;

	case slc_serverupdated:
		piAddListingGamesCallback(peer, PEERTrue, server, 1);
		break;

	case slc_serverdeleted:
		if ((server->state & 0x0c) != 0)
			SBQueryEngineRemoveServerFromFIFOs(&connection->gameEngine, server);
		piAddListingGamesCallback(peer, PEERTrue, server, 2);
		break;

	case slc_initiallistcomplete:
		connection->initialGameList = PEERFalse;
		piAddListingGamesCallback(peer, PEERTrue, (SBServer *)0, 4);
		break;

	case slc_queryerror:
		piAddListingGamesCallback(peer, PEERFalse, (SBServer *)0, 0);
		break;

	case slc_publicipdetermined:
		connection->publicIP = serverlist->mypublicip;
		SBQueryEngineSetPublicIP(&connection->gameEngine, serverlist->mypublicip);
		break;

	default:
		break;
	}

	(void)serverlist;
}
