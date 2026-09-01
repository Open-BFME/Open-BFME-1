// cl: /DNDEBUG /MD -Ireference/shims/gamespy
/* GameSpy Chat SDK -- chatConnectLoginA from chatMain.c.
   The parameter-forwarding body is unchanged in the 2007 SDK source covered
   by GameNetwork/GameSpy/PROVENANCE.txt.  Retail independently fixes the
   login-type choice, the 21-argument chatConnectDoit call, and its target. */

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

typedef void (*chatNickErrorCallback)(void);
typedef void (*chatFillInUserCallback)(void);
typedef void (*chatConnectCallback)(void);

typedef struct chatGlobalCallbacks
{
	void *reserved;
} chatGlobalCallbacks;

CHAT chatConnectDoit(CILoginType loginType,
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
	CHATBool blocking);

CHAT chatConnectLoginA(const char *serverAddress,
	int port,
	int namespaceID,
	const char *email,
	const char *profilenick,
	const char *uniquenick,
	const char *password,
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
	return chatConnectDoit((uniquenick && uniquenick[0]) ?
		CIUniqueNickLogin : CIProfileLogin,
		serverAddress,
		port,
		0,
		0,
		name,
		namespaceID,
		email,
		profilenick,
		uniquenick,
		password,
		0,
		0,
		gamename,
		secretKey,
		callbacks,
		nickErrorCallback,
		fillInUserCallback,
		connectCallback,
		param,
		blocking);
}
