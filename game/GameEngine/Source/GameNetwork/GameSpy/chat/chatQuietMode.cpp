// cl: /DNDEBUG /MD
// Upstream: GameSpy Chat SDK chatMain.c, 2007 release.

// The matched providers at 00872930 and 00872680 currently retain these
// C++ ledger spellings. Their cdecl pointer/int ABI matches the Chat callers.
struct BfmeArg929F;
class BfmeRoomXM;
void bfmeGo929F(BfmeArg929F *);
void bfmeWalkXM(BfmeRoomXM *, int, int);

extern "C" {
typedef void *CHAT;

typedef struct ciConnection
{
	int connected;
	char reserved0[0x1C - 4];
	char chatSocket[1];
	char reserved1[0x36C - 0x1D];
	char nick[1];
	char reserved2[0x824 - 0x36D];
	int quiet;
} ciConnection;

void ciSocketSendf(void *socket, const char *format, ...);
int ciAddUNQUIETFilter(CHAT chat, const char *channel);

void ciSetQuietModeEnumJoinedChannelsA(CHAT chat, void *unused, const char *channel)
{
	ciAddUNQUIETFilter(chat, channel);
}

void chatSetQuietMode(CHAT chat, int quiet)
{
	ciConnection *connection = (ciConnection *)chat;

	if (!chat || !connection->connected)
		return;
	if (connection->quiet == quiet)
		return;

	if (quiet)
		ciSocketSendf(&connection->chatSocket, "MODE %s +q", connection->nick);
	else
		ciSocketSendf(&connection->chatSocket, "MODE %s -q", connection->nick);

	connection->quiet = quiet;
	if (!quiet)
	{
		bfmeGo929F((BfmeArg929F *)chat);
		bfmeWalkXM((BfmeRoomXM *)chat,
			(int)&ciSetQuietModeEnumJoinedChannelsA, 0);
	}
}

void chatSendUserMessageA(CHAT chat, const char *user,
	const char *message, int type)
{
	ciConnection *connection = (ciConnection *)chat;

	if (!chat || !connection->connected || !message || !message[0])
		return;

	if (type == 0)
		ciSocketSendf(&connection->chatSocket, "PRIVMSG %s :%s", user, message);
	else if (type == 1)
		ciSocketSendf(&connection->chatSocket,
			"PRIVMSG %s :\001ACTION %s\001", user, message);
	else if (type == 2)
		ciSocketSendf(&connection->chatSocket, "NOTICE %s :%s", user, message);
	else if (type == 3)
		ciSocketSendf(&connection->chatSocket, "UTM %s :%s", user, message);
	else if (type == 4)
		ciSocketSendf(&connection->chatSocket, "ATM %s :%s", user, message);
}

} // extern "C"
