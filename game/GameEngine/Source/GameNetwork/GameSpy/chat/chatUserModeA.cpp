// cl: /DNDEBUG /MD -Iinputs/reference/shims/gamespy

typedef void *CHAT;

typedef struct ciConnection
{
	int connected;
	unsigned char reserved[0x1c - 4];
	unsigned char chatSocket[1];
} ciConnection;

extern "C" void ciSocketSendf(void *socket, const char *format, ...);

extern "C" void chatSetUserModeA(CHAT chat, const char *channel,
	const char *user, int mode)
{
	ciConnection *connection = (ciConnection *)chat;

	if (!chat || !connection->connected)
		return;

	ciSocketSendf(&connection->chatSocket, "MODE %s %co %s", channel,
		((mode & 2) ? -2 : 0) + 0x2d, user);
	ciSocketSendf(&connection->chatSocket, "MODE %s %cv %s", channel,
		((mode & 1) ? -2 : 0) + 0x2d, user);
}

extern "C" int ciGetUserMode(CHAT, const char *, const char *);
extern "C" int ciGetNextID(CHAT);
extern "C" int ciAddCallback_(CHAT, int, void *, void *, void *, int, const char *, unsigned);
extern "C" void bfmeCiThinkFromEsi(int);
extern "C" void msleep(unsigned);
extern "C" int ciCheckFiltersForID(CHAT, int);
extern "C" int ciCheckCallbacksForID(CHAT, int);
// Complete 42-byte retail helper: five cdecl stack arguments, returns the
// ID produced by ciAddFilter; no semantic name is asserted for this body.
extern "C" int Rva0086C6E0(CHAT, const char *, const char *, void *, void *);

static __forceinline void Rva008615F0Wait(CHAT chat, int id)
{
 do {
  bfmeCiThinkFromEsi(id);
  msleep(10);
 } while (ciCheckFiltersForID(chat, id) || ciCheckCallbacksForID(chat, id));
}

// Separate body at 0x008615F0, bracketed by int3 padding; ret at 0x008616F0.
extern "C" void Rva008615F0(CHAT chat, const char *channel, const char *user,
 void *callback, void *param, int blocking)
{
 ciConnection *connection = (ciConnection *)chat;
 if (!chat || !connection->connected) return;
 int mode = ciGetUserMode(chat, channel, user);
 int id;
 if (mode != -1) {
  struct { int success; const char *channel; const char *user; int mode; } args;
  args.success = 1;
  args.channel = channel;
  args.user = user;
  args.mode = mode;
  id = ciGetNextID(chat);
  ciAddCallback_(chat, 23, callback, &args, param, id, 0, sizeof(args));
  if (blocking) Rva008615F0Wait(chat, id);
 }
 ciSocketSendf(&connection->chatSocket, "WHO %s", user);
 id = Rva0086C6E0(chat, user, channel, callback, param);
 if (blocking) Rva008615F0Wait(chat, id);
}
