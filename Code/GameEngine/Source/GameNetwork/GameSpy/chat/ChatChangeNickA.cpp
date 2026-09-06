// _chatChangeNickA
// cl: /DNDEBUG /MD
// GameSpy Chat SDK chatMain.c body, ported as a C++ ABI slice.

#include <string.h>

typedef void *CHAT;
typedef int CHATBool;

typedef struct ciConnection
{
	int connected;
	char reserved0[0x1C - 4];
	char chatSocket[1];
	char reserved1[0x36C - 0x1D];
	char nick[1];
} ciConnection;

typedef struct ciCallbackChangeNickParams
{
	CHATBool success;
	char *oldNick;
	char *newNick;
} ciCallbackChangeNickParams;

typedef void *(__cdecl *Gen_0093D2D0_Lookup)(void *, void *);
extern Gen_0093D2D0_Lookup g_lookup;

extern "C" int ciGetNextID(CHAT chat);
extern "C" void ciAddCallback_(CHAT chat, int type, void *callback,
	void *callbackParams, void *param, int ID, const char *param2,
	unsigned int callbackParamsSize);
extern "C" int ciAddNICKFilter(CHAT chat, const char *oldNick,
	const char *newNick, void *callback, void *param);
extern "C" void ciSocketSendf(void *socket, const char *format, ...);
extern "C" void bfmeCiThinkFromEsi(int ID);
extern "C" void msleep(unsigned int milliseconds);
extern "C" int ciCheckFiltersForID(CHAT chat, int ID);
extern "C" int ciCheckCallbacksForID(CHAT chat, int ID);

static __forceinline int ciCheckForID(CHAT chat, int ID)
{
	return ciCheckFiltersForID(chat, ID) || ciCheckCallbacksForID(chat, ID);
}

extern "C" void chatChangeNickA(CHAT chat, const char *newNick,
	void *callback, void *param, CHATBool blocking)
{
	ciConnection *connection = (ciConnection *)chat;
	int ID;

	if (!chat || !connection->connected)
		return;

	{
	CHATBool success = 1;
	if (!newNick || !newNick[0] || strlen(newNick) >= 64 ||
		g_lookup((void *)newNick, (void *)connection->nick) == 0)
		success = 0;

	if (!success)
	{
		if (callback)
		{
			ciCallbackChangeNickParams callbackParams;
			callbackParams.success = 0;
			callbackParams.oldNick = connection->nick;
			callbackParams.newNick = (char *)newNick;
			ID = ciGetNextID(chat);
			ciAddCallback_(chat, 26, callback, &callbackParams, param, ID,
				0, sizeof(callbackParams));

			if (blocking)
			{
				do
				{
					bfmeCiThinkFromEsi(ID);
					msleep(10);
				}
				while (ciCheckForID(chat, ID));
			}
		}
		return;
	}

	ciSocketSendf(&connection->chatSocket, "NICK :%s", newNick);
	ID = ciAddNICKFilter(chat, connection->nick, newNick, callback, param);
	if (blocking)
	{
		do
		{
			bfmeCiThinkFromEsi(ID);
			msleep(10);
		}
		while (ciCheckForID(chat, ID));
	}
	}
}
