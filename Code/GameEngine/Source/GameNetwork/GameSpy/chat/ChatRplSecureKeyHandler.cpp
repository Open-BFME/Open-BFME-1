// cl: /DNDEBUG /MD -Ireference/shims/gamespy
// GameSpy Chat SDK ciRplSecureKeyHandler.

#include <string.h>

typedef unsigned char byte;

struct gs_crypt_key
{
	byte state[256];
	byte x;
	byte y;
};

struct ciSocket
{
	char pad00[0x120];
	int secure;
	gs_crypt_key inKey;
	gs_crypt_key outKey;
};

struct ciConnection
{
	char pad00[0x10];
	void *fillInUserCallback;
	char pad14[8];
	ciSocket chatSocket;
	char pad344[0x828 - 0x344];
	char secretKey[1];
	char pad829[0x8a8 - 0x829];
	int loginType;
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
	char **params;
	int numParams;
};

extern "C" void gs_xcode_buf(char *buffer, int length, char *key);
extern "C" void gs_prepare_key(const byte *key, int length, gs_crypt_key *out);
extern "C" void ciSocketSend(void *socket, const char *buffer);
extern "C" void ciSendNickAndUser(void *chat);
extern "C" void ciSendLogin(void *chat);

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
