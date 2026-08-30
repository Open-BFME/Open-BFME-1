// cl: /DNDEBUG /MD
// Upstream: GameSpy Peer SDK peerOperations.c, 2007 release.

#include <stdlib.h>

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
	char reserved[0x1790];
	piOperation *listingGroupsOperation;
	int nextID;
	void *operationList;
	int operationsStarted;
} piConnection;

void *memset(void *dest, int value, unsigned int count);
void ArrayAppend(void *array, const void *element);
PEERBool piSBStartListingGroups(PEER peer, const char *fields);

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
