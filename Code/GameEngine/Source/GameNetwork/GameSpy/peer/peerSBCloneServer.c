// cl: /O2 /Ob2 /DNDEBUG /MD
/* GameSpy Peer SDK -- peerSB.c */

#include <string.h>

typedef void *HashTable;

typedef struct _SBServer
{
	unsigned int publicip;
	unsigned short publicport;
	unsigned int privateip;
	unsigned short privateport;
	unsigned int icmpip;
	unsigned char state;
	unsigned char flags;
	HashTable keyvals;
	unsigned int updatetime;
	struct _SBServer *next;
} *SBServer;

typedef struct SBKeyValuePair
{
	const char *key;
	const char *value;
} SBKeyValuePair;

SBServer SBAllocServer(void *serverList, unsigned int ip, unsigned short port);
void SBServerAddKeyValue(SBServer server, const char *key, const char *value);
void TableMap(HashTable table, void (*mapFunction)(void *, void *), void *clientData);

static void piSBCloneServerTableMap(void *elem, void *clientData)
{
	SBKeyValuePair *kvPair = (SBKeyValuePair *)elem;
	SBServer clone = (SBServer)clientData;

	SBServerAddKeyValue(clone, kvPair->key, kvPair->value);
}

SBServer piSBCloneServer(SBServer server)
{
	SBServer clone;
	HashTable table;

	clone = SBAllocServer(0, server->publicip, server->publicport);
	table = clone->keyvals;
	memcpy(clone, server, sizeof(struct _SBServer));
	clone->keyvals = table;
	clone->next = 0;
	TableMap(server->keyvals, piSBCloneServerTableMap, clone);

	return clone;
}
