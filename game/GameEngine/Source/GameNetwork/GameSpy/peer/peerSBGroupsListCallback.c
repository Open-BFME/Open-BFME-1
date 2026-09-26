// cl: /O2 /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerSB.c, 2007 callback reconstruction.
   The callback body follows the authentic nitrocaster/GameSpy source.  The
   declarations below are TU-local views of the 2004 retail layouts: the
   callback ABI is SBServerListInit's four-argument callback, while the
   listing operation is at piConnection+0x1790 and its callback fields are
   at offsets 0x0c, 0x10, and 0x18. */

typedef enum
{
	PEERFalse,
	PEERTrue
} PEERBool;

typedef void *SBServerListPtr;
typedef void *SBServer;

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

typedef struct piOperation
{
	void *peer;
	int type;
	void *data;
	int ID;
	int callback;
	int callback2;
	void *callbackParam;
} piOperation;

struct piConnection
{
	unsigned char reserved[0x1790];
	piOperation *listingGroupsOperation;
};

typedef void (*peerListGroupRoomsCallback)
(
	PEER peer,
	PEERBool success,
	int groupID,
	SBServer server,
	const char *name,
	int numWaiting,
	int maxWaiting,
	int numGames,
	int numPlaying,
	void *param
);

void piAddListGroupRoomsCallback
(
	PEER peer,
	PEERBool success,
	int groupID,
	SBServer server,
	const char *name,
	int numWaiting,
	int maxWaiting,
	int numGames,
	int numPlaying,
	peerListGroupRoomsCallback callback,
	void *param,
	int opID
);

void piRemoveOperation(PEER peer, piOperation *operation);

// Retail imports WSOCK32!htonl here (the x86 byte swap is also its inverse).
unsigned int __stdcall htonl(unsigned int value);
unsigned int SBServerGetPublicInetAddress(SBServer server);
const char *SBServerGetStringValueA(SBServer server, const char *key, const char *defaultValue);
int SBServerGetIntValueA(SBServer server, const char *key, int defaultValue);

void piSBGroupsListCallback
(
	SBServerListPtr serverlist,
	SBListCallbackReason reason,
	SBServer server,
	void *instance
)
{
	piOperation *operation;
	PEER peer = (PEER)instance;
	piConnection *connection = (piConnection *)peer;

	operation = connection->listingGroupsOperation;

	switch(reason)
	{
	case slc_serveradded:
		{
		int groupID = (int)htonl(SBServerGetPublicInetAddress(server));
		const char *name = SBServerGetStringValueA(server, "hostname", "(No Name)");
		int numWaiting = SBServerGetIntValueA(server, "numwaiting", 0);
		int maxWaiting = SBServerGetIntValueA(server, "maxwaiting", 0);
		int numGames = SBServerGetIntValueA(server, "numservers", 0);
		int numPlaying = SBServerGetIntValueA(server, "numplayers", 0);

		piAddListGroupRoomsCallback(peer, PEERTrue, groupID, server, name,
			numWaiting, maxWaiting, numGames, numPlaying,
			(peerListGroupRoomsCallback)operation->callback,
			operation->callbackParam, operation->ID);
		break;
		}

	case slc_initiallistcomplete:
		piAddListGroupRoomsCallback(peer, PEERTrue, 0, 0, 0, 0, 0, 0, 0,
			(peerListGroupRoomsCallback)operation->callback,
			operation->callbackParam, operation->ID);
		piRemoveOperation(peer, operation);
		break;

	case slc_queryerror:
		piAddListGroupRoomsCallback(peer, PEERFalse, 0, 0, 0, 0, 0, 0, 0,
			(peerListGroupRoomsCallback)operation->callback,
			operation->callbackParam, operation->ID);
		piRemoveOperation(peer, operation);
		break;

	default:
		break;
	}

	(void)serverlist;
}
