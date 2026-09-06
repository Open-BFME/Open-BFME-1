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
extern "C" void ciKillEnumChannelsCallback(CHAT chat, const char *user,
	const char *channel, void *param);

extern "C" void ciKillHandler(CHAT chat, const ciServerMessage *message)
{
	if (message->numParams != 2)
		return;

	ciUserEnumChannels(chat, message->params[0], ciKillEnumChannelsCallback,
		message->params[1]);
}
