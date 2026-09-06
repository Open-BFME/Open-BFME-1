// cl: /DNDEBUG /MD

typedef void *CHAT;

struct ciServerMessage
{
	char reserved0[8];
	char *nick;
	char reserved0c[0x20 - 0x0c];
	char **params;
	int numParams;
};

extern "C" void __cdecl ciUserEnumChannels(CHAT chat, const char *user,
	void (*callback)(CHAT, const char *, const char *, void *), void *param);
extern "C" void ciQuitEnumChannelsCallback(CHAT chat, const char *user,
	const char *channel, void *reason);

extern "C" void ciQuitHandler(CHAT chat, const ciServerMessage *message)
{
	if (message->numParams != 1)
		return;

	ciUserEnumChannels(chat, message->nick, ciQuitEnumChannelsCallback,
		message->params[0]);
}
