// cl: /DNDEBUG /MD -Iinputs/reference/shims/gamespy

// The GameSpy Chat SDK bodies that were converted to C++ rather than
// reconstructed inside the SDK's own .c translation units.
//
// Incoming, all (CHAT, const ciServerMessage *) entries in one handler table:
//   ciErrNoUniqueNickHandler       0x0086FC70   ciKillHandler        0x0086D900
//   ciErrUniqueNickExpiredHandler  0x0086FC90   ciQuitHandler        0x0086D820
//   ciErrErroneusNicknameHandler   0x0086FC10   ciRplWelcomeHandler  0x0086F5D0
//   ciRplLoginHandler              0x0086F7C0   ciRplSecureKeyHandler 0x0086F660
// Outgoing, the API entry points that format a line onto the chat socket:
//   chatBanUserSimpleA             0x00860FF0   chatChangeNickA      0x008604C0
//   chatInviteUserA                0x008614E0   ciSendUserA          0x00860280
//   chatSendChannelMessageA        0x008609F0
//
// All thirteen work on the same object: the CHAT handle IS a ciConnection.
// Split one body per file, each file restated it with only the fields its own
// body touched, so it appeared as two ints in one file, as a 0x8b4-byte body in
// another, and five separate files each opened it with `connected` and a
// nameless run of bytes up to the socket at +0x1c. The offsets never disagreed,
// only the amount each file bothered to name, so one declaration below carries
// all of them:
//
//   +0x00 connected     +0x0c nickErrorCallback   +0x1c chatSocket (0x328 B)
//   +0x04 connecting    +0x10 fillInUserCallback  +0x36c nick    +0x774 server
//   +0x08 disconnected  +0x14 connectCallback     +0x3ac name    +0x824 quiet
//                       +0x18 connectParam        +0x42c user    +0x828 secretKey
//                                                 +0x8a8 loginType
//                                                 +0x8ac userID   +0x8b0 profileID
//
// ciServerMessage likewise: the parsed IRC line is eight char pointers, then
// params at +0x20 and numParams at +0x24. The files that only needed params
// spelled the first eight as an opaque 0x20-byte pad.

#include <stdlib.h>
#include <string.h>

typedef void *CHAT;
typedef int CHATBool;
typedef unsigned char byte;

enum
{
	CHATFalse,
	CHATTrue
};

typedef void (__cdecl *ciConnectCallback)(CHAT chat, CHATBool success,
	int failureReason, void *param);

struct gs_crypt_key
{
	byte state[256];
	byte x;
	byte y;
};

struct ciSocket
{
	char pad00[0x120];
	int secure;						// +0x120
	gs_crypt_key inKey;					// +0x124
	gs_crypt_key outKey;					// +0x226
};

struct ciConnection
{
	CHATBool connected;
	CHATBool connecting;
	CHATBool disconnected;
	void *nickErrorCallback;
	void *fillInUserCallback;
	ciConnectCallback connectCallback;
	void *connectParam;
	ciSocket chatSocket;					// +0x1c
	char pad344[0x36c - 0x344];
	char nick[64];						// +0x36c
	char name[1];						// +0x3ac
	char pad3ad[0x42c - 0x3ad];
	char user[1];						// +0x42c
	char pad42d[0x774 - 0x42d];
	char server[1];						// +0x774
	char pad775[0x824 - 0x775];
	int quiet;						// +0x824
	char secretKey[1];					// +0x828
	char pad829[0x8a8 - 0x829];
	int loginType;						// +0x8a8
	int userID;						// +0x8ac
	int profileID;						// +0x8b0
};

struct chatChannelCallbacks
{
	void *channelMessage;
	void *kicked;
	void *userJoined;
	void *userParted;
	void *userChangedNick;
	void *topicChanged;
	void *channelModeChanged;
	void *userModeChanged;
	void *userListUpdated;
	void *newUserList;
	void *broadcastKeyChanged;
	void *param;
};

struct ciCallbackChannelMessageParams
{
	const char *channel;
	char *user;
	const char *message;
	int type;
};

struct ciCallbackChangeNickParams
{
	CHATBool success;
	char *oldNick;
	char *newNick;
};

struct ciServerMessage
{
	char *message;
	char *server;
	char *nick;
	char *user;
	char *host;
	char *command;
	char *middle;
	char *param;
	char **params;						// +0x20
	int numParams;						// +0x24
};

extern "C" void __cdecl ciNickError(CHAT chat, int type, const char *nick,
	int numSuggestedNicks, char **suggestedNicks);
extern "C" void __cdecl ciUserEnumChannels(CHAT chat, const char *user,
	void (*callback)(CHAT, const char *, const char *, void *), void *param);
extern "C" void ciKillEnumChannelsCallback(CHAT chat, const char *user,
	const char *channel, void *param);
extern "C" void ciQuitEnumChannelsCallback(CHAT chat, const char *user,
	const char *channel, void *reason);
extern "C" void ciSocketSend(void *chatSocket, const char *buffer);
extern "C" void ciSendNickAndUser(void *chat);
extern "C" void ciSendLogin(void *chat);
extern "C" void gs_xcode_buf(char *buffer, int length, char *key);
extern "C" void gs_prepare_key(const byte *key, int length, gs_crypt_key *out);
extern "C" void ciSocketSendf(void *socket, const char *format, ...);
extern "C" int ciGetNextID(CHAT chat);
// Both callers discard the result; retail's own signature returns the ID.
extern "C" int ciAddCallback_(CHAT chat, int type, void *callback,
	void *callbackParams, void *param, int ID, const char *channel,
	unsigned int callbackParamsSize);
extern "C" int ciAddNICKFilter(CHAT chat, const char *oldNick,
	const char *newNick, void *callback, void *param);
extern "C" chatChannelCallbacks *ciGetChannelCallbacks(CHAT chat, const char *channel);
extern "C" void bfmeCiThinkFromEsi(int ID);
extern "C" void msleep(unsigned int milliseconds);
extern "C" int ciCheckFiltersForID(CHAT chat, int ID);
extern "C" int ciCheckCallbacksForID(CHAT chat, int ID);

typedef void *(__cdecl *Gen_0093D2D0_Lookup)(void *, void *);
extern Gen_0093D2D0_Lookup g_lookup;

static __forceinline int ciCheckForID(CHAT chat, int ID)
{
	return ciCheckFiltersForID(chat, ID) || ciCheckCallbacksForID(chat, ID);
}

// The three nick failures the server can report while we are still connecting.
// They differ only in the code they hand ciNickError and in whether the nick we
// asked for is worth repeating back.

// _ciErrErroneusNicknameHandler, retail 0x0086FC10
extern "C" void ciErrErroneusNicknameHandler(CHAT chat, const ciServerMessage *message)
{
	ciConnection *connection = (ciConnection *)chat;

	if (connection->connecting)
		ciNickError(chat, 1, connection->nick, 0, 0);
}

// _ciErrUniqueNickExpiredHandler, retail 0x0086FC90
extern "C" void ciErrUniqueNickExpiredHandler(CHAT chat, const ciServerMessage *message)
{
	ciConnection *connection = (ciConnection *)chat;

	if (connection->connecting)
		ciNickError(chat, 2, "", 0, 0);
}

// _ciErrNoUniqueNickHandler, retail 0x0086FC70
extern "C" void ciErrNoUniqueNickHandler(CHAT chat, const ciServerMessage *message)
{
	ciConnection *connection = (ciConnection *)chat;

	if (connection->connecting)
		ciNickError(chat, 3, "", 0, 0);
}

// _ciQuitHandler, retail 0x0086D820
extern "C" void ciQuitHandler(CHAT chat, const ciServerMessage *message)
{
	if (message->numParams != 1)
		return;

	ciUserEnumChannels(chat, message->nick, ciQuitEnumChannelsCallback,
		message->params[0]);
}

// _ciKillHandler, retail 0x0086D900
extern "C" void ciKillHandler(CHAT chat, const ciServerMessage *message)
{
	if (message->numParams != 2)
		return;

	ciUserEnumChannels(chat, message->params[0], ciKillEnumChannelsCallback,
		message->params[1]);
}

// _ciRplWelcomeHandler, retail 0x0086F5D0 -- the server accepted us, so the
// connection is up and the caller's connect callback finally fires.
extern "C" void ciRplWelcomeHandler(CHAT chat, const ciServerMessage *message)
{
	char *nick;
	ciConnection *connection = (ciConnection *)chat;

	if (message->numParams != 2)
		return;

	nick = message->params[0];

	if (strcmp(connection->nick, nick) != 0)
	{
		strncpy(connection->nick, nick, 64);
		connection->nick[63] = '\0';
	}

	connection->connecting = CHATFalse;
	connection->connected = CHATTrue;

	if (connection->connectCallback != 0)
		connection->connectCallback(chat, CHATTrue, 0,
			connection->connectParam);
}

// _ciRplLoginHandler, retail 0x0086F7C0
extern "C" void ciRplLoginHandler(void *chat, const ciServerMessage *message)
{
	ciConnection *connection = (ciConnection *)chat;

	if (message->numParams < 3)
		return;

	connection->userID = atoi(message->params[1]);
	connection->profileID = atoi(message->params[2]);

	if (connection->fillInUserCallback)
	{
		ciSocketSend(&connection->chatSocket, "USRIP");
	}
	else
	{
		ciSendNickAndUser(chat);
	}
}

// _ciRplSecureKeyHandler, retail 0x0086F660 -- both halves of the stream key
// arrive in one message, xcoded with the secret key we were built with.
extern "C" void ciRplSecureKeyHandler(void *chat, const ciServerMessage *message)
{
	char *outKeyRand;
	char *inKeyRand;
	int outKeyLen;
	int inKeyLen;
	ciConnection *connection = (ciConnection *)chat;

	if (message->numParams != 3)
		return;

	outKeyRand = message->params[1];
	inKeyRand = message->params[2];
	outKeyLen = (int)strlen(outKeyRand);
	inKeyLen = (int)strlen(inKeyRand);
	gs_xcode_buf(outKeyRand, outKeyLen, connection->secretKey);
	gs_xcode_buf(inKeyRand, inKeyLen, connection->secretKey);
	gs_prepare_key((const byte *)outKeyRand, outKeyLen, &connection->chatSocket.outKey);
	gs_prepare_key((const byte *)inKeyRand, inKeyLen, &connection->chatSocket.inKey);
	connection->chatSocket.secure = 1;
	if (connection->loginType != 0)
	{
		ciSendLogin(chat);
	}
	else if (connection->fillInUserCallback)
	{
		ciSocketSend(&connection->chatSocket, "USRIP");
	}
	else
	{
		ciSendNickAndUser(chat);
	}
}

// The outgoing half: everything below formats a line onto the chat socket at
// +0x1c, and the two that can fail locally report it through the same callback
// queue the handlers above drain.

// _chatBanUserSimpleA, retail 0x00860FF0
extern "C" void chatBanUserSimpleA(CHAT chat, const char *channel, const char *user)
{
	ciConnection *connection = (ciConnection *)chat;

	if (!chat || !connection->connected)
		return;

	ciSocketSendf(&connection->chatSocket, "MODE %s +b %s", channel, user);
}

// _chatInviteUserA, retail 0x008614E0
extern "C" void chatInviteUserA(CHAT chat, const char *channel, const char *user)
{
	ciConnection *connection = (ciConnection *)chat;

	if (!chat || !connection->connected)
		return;

	ciSocketSendf(&connection->chatSocket, "INVITE %s %s", user, channel);
}

// _ciSendUserA, retail 0x00860280 -- the IRC USER registration line.
extern "C" void ciSendUserA(CHAT chat)
{
	ciConnection *connection = (ciConnection *)chat;

	ciSocketSendf(&connection->chatSocket, "USER %s %s %s :%s",
		connection->user, "127.0.0.1", connection->server, connection->name);
}

// _chatSendChannelMessageA, retail 0x008609F0
extern "C" void chatSendChannelMessageA(CHAT chat, const char *channel,
	const char *message, int type)
{
	ciConnection *connection = (ciConnection *)chat;
	chatChannelCallbacks *callbacks;

	if (!chat || !connection->connected || !message || !message[0])
		return;

	if (type == 0)
		ciSocketSendf(&connection->chatSocket, "PRIVMSG %s :%s", channel, message);
	else if (type == 1)
		ciSocketSendf(&connection->chatSocket,
			"PRIVMSG %s :\001ACTION %s\001", channel, message);
	else if (type == 2)
		ciSocketSendf(&connection->chatSocket, "NOTICE %s :%s", channel, message);
	else if (type == 3)
		ciSocketSendf(&connection->chatSocket, "UTM %s :%s", channel, message);
	else if (type == 4)
		ciSocketSendf(&connection->chatSocket, "ATM %s :%s", channel, message);
	else
		return;

	callbacks = ciGetChannelCallbacks(chat, channel);
	if (callbacks)
	{
		void *callbackParam = callbacks->param;
		void *callback = callbacks->channelMessage;
		ciCallbackChannelMessageParams callbackParams;
		callbackParams.channel = channel;
		callbackParams.user = connection->nick;
		callbackParams.message = message;
		callbackParams.type = type;
		ciAddCallback_(chat, 4, callback, &callbackParams,
			callbackParam, 0, channel, sizeof(callbackParams));
	}
}

// _chatChangeNickA, retail 0x008604C0
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
