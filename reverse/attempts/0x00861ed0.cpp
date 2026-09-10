// _chatConnectDoit
// partial score=0.82 date=2026-09-10
// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Chat SDK -- chatConnectPreAuthA from chatMain.c.
   The parameter-forwarding body is unchanged in the 2007 SDK source covered
   by GameNetwork/GameSpy/PROVENANCE.txt.  This TU also carries the authentic
   static chatConnectDoit helper that the wrapper calls.  Retail identifies
   that helper at 0x00861ED0 with a 995-byte boundary. */

#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef void *CHAT;

typedef enum
{
	CHATFalse,
	CHATTrue
} CHATBool;

typedef enum
{
	CINoLogin,
	CIUniqueNickLogin,
	CIProfileLogin,
	CIPreAuthLogin
} CILoginType;

typedef void (*chatNickErrorCallback)(CHAT chat, int type, const char *nick,
	int numSuggestedNicks, const char **suggestedNicks, void *param);
typedef void (*chatFillInUserCallback)(CHAT chat, unsigned int IP,
	char user[128], void *param);
typedef void (*chatConnectCallback)(CHAT chat, CHATBool success,
	int failureReason, void *param);

typedef struct chatGlobalCallbacks
{
	void *raw;
	void *disconnected;
	void *privateMessage;
	void *invited;
	void *param;
} chatGlobalCallbacks;

typedef struct ciSocket
{
	unsigned char bytes[0x328];
} ciSocket;

typedef struct ciConnection
{
	CHATBool connected;
	CHATBool connecting;
	CHATBool disconnected;
	chatNickErrorCallback nickErrorCallback;
	chatFillInUserCallback fillInUserCallback;
	chatConnectCallback connectCallback;
	void *connectParam;

	ciSocket chatSocket;
	unsigned char pad344[0x36c - 0x344];

	char nick[64];
	char name[128];
	char user[128];

	int namespaceID;
	char email[64];
	char profilenick[32];
	char uniquenick[64];
	char password[32];

	char authtoken[256];
	char partnerchallenge[256];

	unsigned int IP;
	char server[128];
	int port;

	chatGlobalCallbacks globalCallbacks;
	void *channelTable;
	void *enteringChannelList;
	void *filterList;
	void *lastFilter;
	int nextID;
	void *callbackList;
	CHATBool quiet;
	char secretKey[128];
	CILoginType loginType;
	int userID;
	int profileID;
} ciConnection;

#define MAX_NICK 64
#define MAX_NAME 128
#define MAX_USER 128
#define MAX_SERVER 128
#define MAX_SECRETKEY 128
#define MAX_EMAIL 64
#define MAX_PROFILENICK 32
#define MAX_UNIQUENICK 64
#define MAX_PASSWORD 32
#define MAX_AUTHTOKEN 256
#define MAX_PARTNERCHALLENGE 256
#define CI_DEFAULT_SERVER_ADDRESS "peerchat.gamespy.com"
#define CI_DEFUILT_SERVER_PORT 6667
#define ASSERT_NICK() assert(nick != NULL); assert(nick[0] != '\0'); assert(strlen(nick) < MAX_NICK)
#define strzcpy(dest, src, len) { strncpy(dest, src, (len)); (dest)[(len) - 1] = '\0'; }

extern int ciVersionID;
void SocketStartUp(void);
void SocketShutDown(void);
CHATBool ciInitChannels(CHAT chat);
void ciCleanupChannels(CHAT chat);
CHATBool ciInitCallbacks(CHAT chat);
void ciCleanupCallbacks(CHAT chat);
CHATBool ciSocketInit(ciSocket *sock, const char *nick);
CHATBool ciSocketConnect(ciSocket *sock, const char *serverAddress, int port);
void ciSocketDisconnect(ciSocket *sock);
CHATBool ciSocketSend(ciSocket *sock, const char *buffer);
CHATBool ciSocketSendf(ciSocket *sock, const char *format, ...);
void ciSendNickAndUser(CHAT chat);
void ciThink(CHAT chat, int ID);
void chatDisconnect(CHAT chat);
void msleep(unsigned int milliseconds);

static CHAT chatConnectDoit(CILoginType loginType,
	const char *serverAddress,
	int port,
	const char *nick,
	const char *user,
	const char *name,
	int namespaceID,
	const char *email,
	const char *profilenick,
	const char *uniquenick,
	const char *password,
	const char *authtoken,
	const char *partnerchallenge,
	const char *gamename,
	const char *secretKey,
	chatGlobalCallbacks *callbacks,
	chatNickErrorCallback nickErrorCallback,
	chatFillInUserCallback fillInUserCallback,
	chatConnectCallback connectCallback,
	void *param,
	CHATBool blocking)
{
	ciConnection *connection;
	const char *socketNick = "";

	assert(callbacks != NULL);
	assert(connectCallback != NULL);

	if(loginType == CINoLogin)
	{
		ASSERT_NICK();
		if(!nick || !nick[0])
			return NULL;
		socketNick = nick;
	}
	else if(loginType == CIUniqueNickLogin)
	{
		assert(namespaceID > 0);
		if(namespaceID <= 0)
			return NULL;
		assert(uniquenick && uniquenick[0]);
		if(!uniquenick || !uniquenick[0])
			return NULL;
		assert(password && password[0]);
		if(!password || !password[0])
			return NULL;
		socketNick = uniquenick;
	}
	else if(loginType == CIProfileLogin)
	{
		assert(namespaceID >= 0);
		if(namespaceID < 0)
			return NULL;
		assert(email && email[0]);
		if(!email || !email[0])
			return NULL;
		assert(profilenick && profilenick[0]);
		if(!profilenick || !profilenick[0])
			return NULL;
		assert(password && password[0]);
		if(!password || !password[0])
			return NULL;
		socketNick = profilenick;
	}
	else if(loginType == CIPreAuthLogin)
	{
		assert(authtoken && authtoken[0]);
		if(!authtoken || !authtoken[0])
			return NULL;
		assert(partnerchallenge && partnerchallenge[0]);
		if(!partnerchallenge || !partnerchallenge[0])
			return NULL;
		socketNick = "preauth";
	}
	if(loginType != CINoLogin)
	{
		assert(gamename && gamename[0]);
		if(!gamename || !gamename[0])
			return NULL;
		assert(secretKey && secretKey[0]);
		if(!secretKey || !secretKey[0])
			return NULL;
	}

	SocketStartUp();
	connection = (ciConnection *)malloc(sizeof(ciConnection));
	if(connection == NULL)
		return NULL;

	memset(connection, 0, sizeof(ciConnection));
	connection->loginType = loginType;
	if(nick)
		strzcpy(connection->nick, nick, MAX_NICK);
	if(user)
		strzcpy(connection->user, user, MAX_USER);
	if(name)
		strzcpy(connection->name, name, MAX_NAME);
	connection->namespaceID = namespaceID;
	if(email)
		strzcpy(connection->email, email, MAX_EMAIL);
	if(profilenick)
		strzcpy(connection->profilenick, profilenick, MAX_PROFILENICK);
	if(uniquenick)
		strzcpy(connection->uniquenick, uniquenick, MAX_UNIQUENICK);
	if(password)
		strzcpy(connection->password, password, MAX_PASSWORD);
	if(authtoken)
		strzcpy(connection->authtoken, authtoken, MAX_AUTHTOKEN);
	if(partnerchallenge)
		strzcpy(connection->partnerchallenge, partnerchallenge, MAX_PARTNERCHALLENGE);
	strncpy(connection->server, serverAddress, MAX_SERVER);
	connection->port = port;
	connection->server[MAX_SERVER - 1] = '\0';
	connection->globalCallbacks = *callbacks;
	connection->nextID = 1;
	connection->connecting = CHATTrue;
	connection->quiet = CHATFalse;

	if(!ciInitChannels(connection))
	{
		free(connection);
		SocketShutDown();
		return NULL;
	}
	if(!ciInitCallbacks(connection))
	{
		ciCleanupChannels((CHAT)connection);
		free(connection);
		SocketShutDown();
		return NULL;
	}
	if(!ciSocketInit(&connection->chatSocket, socketNick))
	{
		ciCleanupCallbacks((CHAT)connection);
		ciCleanupChannels((CHAT)connection);
		free(connection);
		SocketShutDown();
		return NULL;
	}
	if(!ciSocketConnect(&connection->chatSocket, connection->server, connection->port))
	{
		ciSocketDisconnect(&connection->chatSocket);
		ciCleanupCallbacks((CHAT)connection);
		ciCleanupChannels((CHAT)connection);
		free(connection);
		SocketShutDown();
		return NULL;
	}

	connection->nickErrorCallback = nickErrorCallback;
	connection->fillInUserCallback = fillInUserCallback;
	connection->connectCallback = connectCallback;
	connection->connectParam = param;

	if(gamename && gamename[0] && secretKey && secretKey[0])
	{
		strzcpy(connection->secretKey, secretKey, MAX_SECRETKEY);
		ciSocketSendf(&connection->chatSocket, "CRYPT des %d %s", ciVersionID, gamename);
	}
	else if(connection->fillInUserCallback)
	{
		ciSocketSend(&connection->chatSocket, "USRIP");
	}
	else
	{
		ciSendNickAndUser((CHAT)connection);
	}

	if(blocking)
	{
		do
		{
			ciThink((CHAT)connection, 0);
			msleep(10);
		} while(connection->connecting);

		if(!connection->connected)
		{
			chatDisconnect((CHAT)connection);
			connection = NULL;
		}
	}

	return (CHAT)connection;
}

CHAT chatConnectPreAuthA(const char *serverAddress,
	int port,
	const char *authtoken,
	const char *partnerchallenge,
	const char *name,
	const char *gamename,
	const char *secretKey,
	chatGlobalCallbacks *callbacks,
	chatNickErrorCallback nickErrorCallback,
	chatFillInUserCallback fillInUserCallback,
	chatConnectCallback connectCallback,
	void *param,
	CHATBool blocking)
{
	return chatConnectDoit(CIPreAuthLogin,
		serverAddress,
		port,
		0,
		0,
		name,
		0,
		0,
		0,
		0,
		0,
		authtoken,
		partnerchallenge,
		gamename,
		secretKey,
		callbacks,
		nickErrorCallback,
		fillInUserCallback,
		connectCallback,
		param,
		blocking);
}
