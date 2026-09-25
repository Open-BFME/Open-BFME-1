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

// 0x0086B990: userModeChanged (54 bytes; RET+0x35, then INT3).
extern "C" void piSetPlayerModeFlags(PEER, const char *, int, int);
extern "C" void piUserModeChangedA(void *chat, const char *channel,
 const char *nick, int mode, void *param)
{
 PEER peer = (PEER)param;
 int roomType;
 if (piRoomToType(peer, channel, &roomType))
  piSetPlayerModeFlags(peer, nick, roomType, mode);
}

// 0x0086B9D0: channelModeChanged (49 bytes; RET+0x30, then INT3).
struct CHATChannelMode;
extern "C" void piAddRoomModeChangedCallback(PEER, int, CHATChannelMode *);
extern "C" void piChannelModeChangedA(void *chat, const char *channel,
 CHATChannelMode *mode, void *param)
{
 PEER peer = (PEER)param;
 int roomType;
 if (piRoomToType(peer, channel, &roomType))
  piAddRoomModeChangedCallback(peer, roomType, mode);
}
