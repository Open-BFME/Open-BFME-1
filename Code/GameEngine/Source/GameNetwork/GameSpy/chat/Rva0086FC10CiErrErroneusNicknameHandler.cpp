// cl: /DNDEBUG /MD

typedef void *CHAT;

struct ciConnection
{
	int connected;
	int connecting;
	char pad08[0x36c - 8];
	char nick[1];
};

extern "C" void __cdecl ciNickError(CHAT chat, int type, const char *nick,
	int numSuggestedNicks, char **suggestedNicks);

extern "C" void ciErrErroneusNicknameHandler(CHAT chat, const void *message)
{
	ciConnection *connection = (ciConnection *)chat;

	if (connection->connecting)
		ciNickError(chat, 1, connection->nick, 0, 0);
}
