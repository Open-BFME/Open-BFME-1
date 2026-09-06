// cl: /DNDEBUG /MD

typedef void *CHAT;

struct ciConnection
{
	int connected;
	int connecting;
};

extern "C" void __cdecl ciNickError(CHAT chat, int type, const char *nick,
	int numSuggestedNicks, char **suggestedNicks);
struct ciServerMessage;

extern "C" void ciErrNoUniqueNickHandler(CHAT chat, const ciServerMessage *message)
{
	ciConnection *connection = (ciConnection *)chat;

	if (connection->connecting)
		ciNickError(chat, 3, "", 0, 0);
}
