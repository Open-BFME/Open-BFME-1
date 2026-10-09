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

// Retail's callback search passes this local comparator at RVA 0x0085E1F0.
// Its +0x14 ID loads distinguish the callback record contract; the unrelated
// GP transfer comparator has its own retail body at RVA 0x008F3D20.
static int piIsCallbackFinishedCompareCallback(const void *left, const void *right)
{
	const piCallbackData *leftData = (const piCallbackData *)left;
	const piCallbackData *rightData = (const piCallbackData *)right;
	return leftData->ID - rightData->ID;
}
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
