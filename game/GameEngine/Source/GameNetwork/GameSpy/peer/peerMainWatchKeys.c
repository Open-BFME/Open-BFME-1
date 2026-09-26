// cl: /DNDEBUG /MD
// Upstream: GameSpy Peer SDK peerMain.c, 2007 release.

typedef void *PEER;
typedef int RoomType;
typedef int PEERBool;

void piSetGlobalWatchKeys(PEER peer, RoomType roomType, int num,
	const char **keys, PEERBool addKeys);
void piSetRoomWatchKeys(PEER peer, RoomType roomType, int num,
	const char **keys, PEERBool addKeys);
const char *piGetGlobalWatchKeyA(PEER peer, const char *nick,
	const char *key);
const char *piGetRoomWatchKeyA(PEER peer, RoomType roomType,
	const char *nick, const char *key);

void peerSetGlobalWatchKeysA(PEER peer, RoomType roomType, int num,
	const char **keys, PEERBool addKeys)
{
	piSetGlobalWatchKeys(peer, roomType, num, keys, addKeys);
}

void peerSetRoomWatchKeysA(PEER peer, RoomType roomType, int num,
	const char **keys, PEERBool addKeys)
{
	piSetRoomWatchKeys(peer, roomType, num, keys, addKeys);
}

const char *peerGetGlobalWatchKeyA(PEER peer, const char *nick,
	const char *key)
{
	return piGetGlobalWatchKeyA(peer, nick, key);
}

const char *peerGetRoomWatchKeyA(PEER peer, RoomType roomType,
	const char *nick, const char *key)
{
	return piGetRoomWatchKeyA(peer, roomType, nick, key);
}
