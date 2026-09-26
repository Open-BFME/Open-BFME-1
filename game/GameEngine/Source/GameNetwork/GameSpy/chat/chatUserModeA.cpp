// cl: /DNDEBUG /MD -Iinputs/reference/shims/gamespy

typedef void *CHAT;

typedef struct ciConnection
{
	int connected;
	unsigned char reserved[0x1c - 4];
	unsigned char chatSocket[1];
} ciConnection;

extern "C" void ciSocketSendf(void *socket, const char *format, ...);

extern "C" void chatSetUserModeA(CHAT chat, const char *channel,
	const char *user, int mode)
{
	ciConnection *connection = (ciConnection *)chat;

	if (!chat || !connection->connected)
		return;

	ciSocketSendf(&connection->chatSocket, "MODE %s %co %s", channel,
		((mode & 2) ? -2 : 0) + 0x2d, user);
	ciSocketSendf(&connection->chatSocket, "MODE %s %cv %s", channel,
		((mode & 1) ? -2 : 0) + 0x2d, user);
}
