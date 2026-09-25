// cl: /O2 /Ob2 /DNDEBUG /MD
// Callback identities witnessed by matched piSetChannelCallbacks.
// 0x0086B950: broadcastKeyChanged (59 bytes; RET+0x3A, then INT3).
typedef void *PEER;
extern "C" int piRoomToType(PEER, const char *, int *);
extern "C" void piRoomKeyChanged(PEER, int, const char *, const char *, const char *);

extern "C" void piBroadcastKeyChangedA(void *chat, const char *channel,
 const char *nick, const char *key, const char *value, void *param)
{
 PEER peer = (PEER)param;
 int roomType;
 if (piRoomToType(peer, channel, &roomType))
  piRoomKeyChanged(peer, roomType, nick, key, value);
}
