// cl: /DNDEBUG /MD
// Upstream: GameSpy Peer SDK peerCallbacks.c, 2007 release.

typedef void *PEER;
typedef int PEERBool;

typedef struct piCallbackData
{
	int type;
	int success;
	void *callback;
	void *callbackParam;
	void *params;
	int ID;
	int inCall;
} piCallbackData;

typedef struct piConnection
{
	char reserved[0x1818];
	void *callbackList;
} piConnection;

int piIsCallbackFinishedCompareCallback(const void *left, const void *right);
int ArraySearch(void *array, const void *key,
	int (*compare)(const void *, const void *), int skip, int startIndex);

PEERBool piIsCallbackFinished(PEER peer, int opID)
{
	piCallbackData data;
	piConnection *connection = (piConnection *)peer;

	data.ID = opID;
	return ArraySearch(connection->callbackList, &data,
		piIsCallbackFinishedCompareCallback, 0, 0) == -1;
}
