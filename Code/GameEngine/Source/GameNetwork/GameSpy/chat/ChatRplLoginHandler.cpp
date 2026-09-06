// cl: /DNDEBUG /MD -Ireference/shims/gamespy
// GameSpy Chat SDK ciRplLoginHandler.

#include <stdlib.h>

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
	char **params;
	int numParams;
};

struct ciConnection
{
	char pad00[0x10];
	void *fillInUserCallback;
	char pad14[0x08];
	char chatSocket[4];
	char pad20[0x8ac - 0x20];
	int userID;
	int profileID;
};

extern "C" void ciSocketSend(void *chatSocket, const char *buffer);
extern "C" void ciSendNickAndUser(void *chat);

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
