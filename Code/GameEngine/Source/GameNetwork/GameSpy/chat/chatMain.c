// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Chat SDK -- the ciSendGetKey body from chatMain.c.
   Reconstructed from the 2007 SDK (nitrocaster/GameSpy,
   src/GameSpy/Chat/chatMain.c), whose function body is unchanged from the
   2004-vintage implementation compiled into lotrbfme.exe.  The surrounding
   declarations are local because the matching 2004 Chat headers are not in
   hand; see ../PROVENANCE.txt for the source and permission record.

   Retail identifies the body independently: its GETKEY format string is
   referenced only at 0x00861860, and the final call targets ciSocketSend at
   0x0085AC90 with &connection->chatSocket (connection + 0x1c). */

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define VALID_NICK_CHARS "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789[]\\`_^{|}-"

typedef void *CHAT;

typedef enum
{
	CHATFalse,
	CHATTrue
} CHATBool;

typedef void (*ciConnectCallback)(CHAT chat, CHATBool success, int failureReason,
		void *param);

typedef struct ciConnection
{
	int connected;
	CHATBool connecting;
	CHATBool disconnected;
	void *nickErrorCallback;
	unsigned char pad10[4];
	ciConnectCallback connectCallback;
	void *connectParam;
	unsigned char chatSocket;
	unsigned char pad1d[0x36c - 0x1d];
	char nick[1];
	unsigned char pad36d[0x3ac - 0x36d];
	char name[1];
	unsigned char pad3ad[0x42c - 0x3ad];
	char user[1];
	unsigned char pad42d[0x4ac - 0x42d];
	int namespaceID;
	unsigned char pad4b0[0x4f0 - 0x4b0];
	char profilernick[1];
	unsigned char pad4f1[0x774 - 0x4f1];
	char server[1];
	unsigned char pad775[0x8a8 - 0x775];
	int loginType;
} ciConnection;

void ciSocketSend(void *chatSocket, const char *buffer);
void ciSocketSendf(void *chatSocket, const char *format, ...);
void ciAddBANFilter(CHAT chat, const char *user, const char *channel);
CHATBool ciCheckFiltersForID(CHAT chat, int ID);
CHATBool ciCheckCallbacksForID(CHAT chat, int ID);
void ciAddCallback_(CHAT chat, int type, void *callback, void *params,
		void *callbackParam, int ID, void *param2, int paramsSize);
#define ciAddCallback(chat, type, callback, params, callbackParam, ID, param2) \
	ciAddCallback_(chat, type, callback, params, callbackParam, ID, param2, \
		sizeof(*(params)))

static CHATBool ciCheckForID(CHAT chat, int ID)
{
	return (CHATBool)(ciCheckFiltersForID(chat, ID) ||
		ciCheckCallbacksForID(chat, ID));
}

CHATBool ciCheckForIDAnchor(CHAT chat, int ID)
{
	return ciCheckForID(chat, ID);
}

char *ciRandomCookie(void)
{
	static char cookie[4];
	static int nextCookie = 0;

	sprintf(cookie, "%03d", nextCookie++);
	nextCookie %= 1000;

	return cookie;
}

static void ciSendGetKey(CHAT chat,
						 const char *target,
						 const char *cookie,
						 int num,
						 const char **keys)
{
	char buffer[512];
	int len;
	int i;
	int j;
	int keyLen;
	ciConnection *connection = (ciConnection *)chat;

	assert(target && target[0]);
	assert(cookie && cookie[0]);
	assert(num >= 1);
	assert(keys);

	sprintf(buffer, "GETKEY %s %s 0 :", target, cookie);
	len = (int)strlen(buffer);

	for(i = 0 ; i < num ; i++)
	{
		if(!keys[i] || !keys[i][0])
			continue;

		keyLen = (int)strlen(keys[i]);
		if((len + keyLen + 1) >= (int)sizeof(buffer))
			return;

		buffer[len++] = '\\';
		memcpy(buffer + len, keys[i], (unsigned int)keyLen);
		for(j = len ; j < (len + keyLen) ; j++)
			if(buffer[j] == '\\')
				buffer[j] = '/';
		len += keyLen;
		buffer[len] = '\0';
	}

	ciSocketSend(&connection->chatSocket, buffer);
}

/* Keep the TU-local SDK helper reachable in this partial reconstruction.  In
   the complete SDK chatGetGlobalKeys calls it; retaining a caller also lets
   VC7.1 reproduce the helper's internal register argument assignment. */
void ciSendGetKeyAnchor(CHAT chat,
						const char *target,
						const char *cookie,
						int num,
						const char **keys)
{
	ciSendGetKey(chat, target, cookie, num, keys);
}

void chatSetChannelKeysA(CHAT chat,
						 const char *channel,
						 const char *user,
						 int num,
						 const char **keys,
						 const char **values)
{
	char buffer[512];
	const char *value;
	int i;
	ciConnection *connection = (ciConnection *)chat;
	if(!connection || *(int *)connection == 0)
		return;

	if(!user || !user[0])
		sprintf(buffer, "SETCHANKEY %s :", channel);
	else
		sprintf(buffer, "SETCKEY %s %s :", channel, user);
	for(i = 0 ; i < num ; i++)
	{
		value = values[i];
		if(!value)
			value = "";
		sprintf(buffer + strlen(buffer), "\\%s\\%s", keys[i], value);
	}

	ciSocketSend(&connection->chatSocket, buffer);
}

static CHATBool ciSendGetChannelKey(CHAT chat,
									const char *channel,
									const char *nick,
									const char *cookie,
									int num,
									const char **keys)
{
	char buffer[512];
	int len;
	int i;
	int j;
	int keyLen;
	CHATBool getBrocastKeys = CHATFalse;
	ciConnection *connection = (ciConnection *)chat;

	assert(channel && channel[0]);
	assert(cookie && cookie[0]);
	assert(!num || keys);

	if(!nick || !nick[0])
		sprintf(buffer, "GETCHANKEY %s %s 0 :", channel, cookie);
	else
		sprintf(buffer, "GETCKEY %s %s %s 0 :", channel, nick, cookie);
	len = (int)strlen(buffer);

	for(i = 0 ; i < num ; i++)
	{
		if(!keys[i] || !keys[i][0])
			continue;

		if(strcmp(keys[i], "b_*") == 0)
		{
			getBrocastKeys = CHATTrue;
			continue;
		}

		keyLen = (int)strlen(keys[i]);
		if((len + keyLen + 1) >= (int)sizeof(buffer))
			continue;

		buffer[len++] = '\\';
		memcpy(buffer + len, keys[i], (unsigned int)keyLen);
		for(j = len ; j < (len + keyLen) ; j++)
			if(buffer[j] == '\\')
				buffer[j] = '/';
		len += keyLen;
		buffer[len] = '\0';
	}

	if(getBrocastKeys)
	{
		if((len + 4) < (int)sizeof(buffer))
		{
			strcpy(buffer + len, "\\b_*");
			len += 4;
		}
	}

	if(!num && (!nick || !nick[0]))
	{
		strcpy(buffer + len, "*");
		len++;
	}

	ciSocketSend(&connection->chatSocket, buffer);

	return getBrocastKeys;
}

CHATBool ciSendGetChannelKeyAnchor(CHAT chat,
									 const char *channel,
									 const char *nick,
									 const char *cookie,
									 int num,
									 const char **keys)
{
	return ciSendGetChannelKey(chat, channel, nick, cookie, num, keys);
}

int ciNickIsValid(const char *nick)
{
	if((NULL == nick) || ('\0' == *nick))
		return CHATFalse;

	if(isdigit(*nick) || (*nick == '-'))
		return CHATFalse;

	while(*nick != '\0')
	{
		if(NULL == strchr(VALID_NICK_CHARS, *nick++))
			return CHATFalse;
	}

	return CHATTrue;
}

void ciNickError(CHAT chat, int type, const char *nick,
		int numSuggestedNicks, char **suggestedNicks)
{
	typedef struct ciCallbackNickErrorParams
	{
		int type;
		char *nick;
		int numSuggestedNicks;
		char **suggestedNicks;
	} ciCallbackNickErrorParams;
	ciConnection *connection = (ciConnection *)chat;

	if(connection->nickErrorCallback)
	{
		ciCallbackNickErrorParams params;

		memset(&params, 0, sizeof(ciCallbackNickErrorParams));
		params.type = type;
		params.nick = (char *)nick;
		params.numSuggestedNicks = numSuggestedNicks;
		params.suggestedNicks = suggestedNicks;
		ciAddCallback(chat, 25, connection->nickErrorCallback, &params,
			connection->connectParam, 0, NULL);
	}
	else
	{
		connection->connecting = CHATFalse;

		if(connection->connectCallback != NULL)
			connection->connectCallback(chat, CHATFalse, 1,
				connection->connectParam);
	}
}

void ciSendNick(CHAT chat)
{
	const char *nick;
	ciConnection *connection = (ciConnection *)chat;

	if(connection->loginType == 0)
	{
		nick = connection->nick;
	}
	else if((connection->loginType == 2) && (connection->namespaceID == 0))
	{
		nick = connection->profilernick;
	}
	else
	{
		nick = "*";
		goto sendNick;
	}

	if(!ciNickIsValid(nick))
	{
		ciNickError(chat, 1, nick, 0, NULL);
		return;
	}

sendNick:
	ciSocketSendf(&connection->chatSocket, "NICK %s", nick);
}

void ciSendNickAndUser(CHAT chat)
{
	ciConnection *connection = (ciConnection *)chat;

	ciSocketSendf(&connection->chatSocket, "USER %s %s %s :%s",
		connection->user,
		"127.0.0.1",
		connection->server,
		connection->name);
	ciSendNick(chat);
}

/* Two one-liners off the same connection.  chatGetNickA returns the empty
   string rather than NULL when there is no connection, and returns a pointer
   INTO the connection rather than a copy -- retail computes connection+0x36C
   and returns it, which is what fixes nick[] as an inline buffer.

   chatSendRawA's guard is the pair, not the single flag every neighbour
   tests: it goes out while still connecting, so the test is connected OR
   connecting.  It tail-jumps into ciSocketSend with the raw buffer left
   where it arrived. */

char *chatGetNickA(CHAT chat)
{
	ciConnection *connection = (ciConnection *)chat;

	if(!connection->connected)
		return "";

	return connection->nick;
}

void chatSendRawA(CHAT chat, const char *raw)
{
	ciConnection *connection = (ciConnection *)chat;

	if(!chat)
		return;

	if(!connection->connected && !connection->connecting)
		return;

	ciSocketSend(&connection->chatSocket, raw);
}

void chatRetryWithNickA(CHAT chat, const char *nick)
{
	int validateNick;
	ciConnection *connection = (ciConnection *)chat;

	if(connection->connected)
		return;

	if(nick == NULL)
	{
		connection->connecting = CHATFalse;

		if(connection->connectCallback != NULL)
			connection->connectCallback(chat, CHATFalse, 1,
				connection->connectParam);

		return;
	}

	strncpy(connection->nick, nick, 64);
	connection->nick[63] = '\0';

	validateNick = ciNickIsValid(nick);
	if(!validateNick)
	{
		ciNickError(chat, 1, nick, 0, NULL);
		return;
	}

	ciSocketSendf(&connection->chatSocket, "NICK :%s", nick);
}

void chatBanUserA(CHAT chat, const char *channel, const char *user)
{
	ciConnection *connection = (ciConnection *)chat;

	if(!connection || !connection->connected)
		return;

	ciSocketSendf(&connection->chatSocket, "WHOIS %s", user);
	ciAddBANFilter(chat, user, channel);
}
