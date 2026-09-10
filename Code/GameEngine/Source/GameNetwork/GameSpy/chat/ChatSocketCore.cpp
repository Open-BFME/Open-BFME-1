// cl: /DNDEBUG /MD
// The control flow follows GameSpy Chat 1.15.00 carrier commit
// d1deb2d1a951cf77933dda040b8d311cc09815a7; BFME's 2004 ABI maps gsifree to CRT free.

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int CHATBool;
enum { CHATFalse, CHATTrue };

enum ciConnectState
{
	ciNotConnected,
	ciConnected,
	ciDisconnected
};

enum CILoginType
{
	CINoLogin,
	CIUniqueNickLogin,
	CIProfileLogin,
	CIPreAuthLogin
};

struct ciBuffer
{
	char *buffer;
	int length;
	int size;
};

struct gs_crypt_key
{
	unsigned char state[256];
	unsigned char x;
	unsigned char y;
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

struct ciSocket
{
	unsigned int sock;
	ciConnectState connectState;
	char serverAddress[256];
	ciBuffer inputQueue;
	ciBuffer outputQueue;
	CHATBool secure;
	gs_crypt_key inKey;
	gs_crypt_key outKey;
	ciServerMessage lastMessage;
};

struct ciHostEntry
{
	char *name;
	char **aliases;
	short addressType;
	short addressLength;
	char **addressList;
};

struct ciInternetAddress
{
	unsigned long address;
};

struct ciSocketAddress
{
	short family;
	unsigned short port;
	ciInternetAddress internetAddress;
	char zero[8];
};

extern "C" {
int __stdcall shutdown(unsigned int socket, int how);
int __stdcall closesocket(unsigned int socket);
int __stdcall send(unsigned int socket, const char *buffer, int length, int flags);
int __stdcall recv(unsigned int socket, char *buffer, int length, int flags);
int __stdcall WSAGetLastError(void);
unsigned long __stdcall inet_addr(const char *address);
ciHostEntry *__stdcall gethostbyname(const char *name);
unsigned short __stdcall htons(unsigned short value);
unsigned long __stdcall htonl(unsigned long value);
unsigned int __stdcall socket(int addressFamily, int type, int protocol);
int __stdcall setsockopt(unsigned int socket, int level, int option, const char *value, int valueLength);
int __stdcall bind(unsigned int socket, const ciSocketAddress *address, int addressLength);
int __stdcall connect(unsigned int socket, const ciSocketAddress *address, int addressLength);
void GSISocketSelect(unsigned int socket, int *readFlag, int *writeFlag, int *exceptFlag);
void gs_crypt(unsigned char *buffer, int length, gs_crypt_key *key);
extern unsigned int gsiSocketInterface;

static CHATBool ciBufferInit(ciBuffer *buffer)
{
	buffer->length = 0;
	buffer->size = 8192;
	buffer->buffer = (char *)malloc(8192 + 1);
	if (buffer->buffer == NULL)
		return CHATFalse;
	buffer->buffer[0] = '\0';
	return CHATTrue;
}

static void ciBufferFree(ciBuffer *buffer)
{
	free(buffer->buffer);
}

static CHATBool ciBufferPreAppend(ciBuffer *buffer, int length)
{
	int total = buffer->length + length;
	if (total <= buffer->size)
		return CHATTrue;
	total += 8192;
	total -= total % 8192;
	char *replacement = (char *)realloc(buffer->buffer, (unsigned int)total + 1);
	if (replacement == NULL)
		return CHATFalse;
	buffer->buffer = replacement;
	buffer->size = total;
	return CHATTrue;
}

static void ciBufferClipFront(ciBuffer *buffer, int length)
{
	buffer->length -= length;
	memmove(buffer->buffer, buffer->buffer + length, (unsigned int)buffer->length);
	buffer->buffer[buffer->length] = '\0';
}

CHATBool ciSocketInit(ciSocket *socket, const char *nick)
{
	// The retail caller passes its selected nickname; this SDK ignores it.
	(void)nick;
	memset(socket, 0, sizeof(*socket));
	socket->sock = ~0U;
	if (ciBufferInit(&socket->inputQueue)) {
		if (ciBufferInit(&socket->outputQueue))
			return CHATTrue;
		ciBufferFree(&socket->inputQueue);
	}
	return CHATFalse;
}

CHATBool ciSocketConnect(ciSocket *socket, const char *serverAddress, int port)
{
	unsigned long ip;
	ciHostEntry *host;
	ciSocketAddress localAddress;
	ciSocketAddress address;
	int keepalive;

	strncpy(socket->serverAddress, serverAddress, 255);
	socket->serverAddress[254] = '\0';

	ip = inet_addr(serverAddress);
	if(ip == ~0UL) {
		host = gethostbyname(serverAddress);
		if(host == NULL)
			return CHATFalse;
		ip = *(unsigned long *)host->addressList[0];
	}

	memset(&address, 0, sizeof(address));
	address.family = 2;
	address.internetAddress.address = ip;
	address.port = htons((unsigned short)port);

	memset(&localAddress, 0, sizeof(localAddress));
	localAddress.family = 2;
	localAddress.internetAddress.address = htonl(gsiSocketInterface);
	localAddress.port = 0;

	socket->sock = ::socket(2, 1, 0);
	if(socket->sock == ~0U)
		return CHATFalse;

	keepalive = 1;
	setsockopt(socket->sock, 0xffff, 8, (const char *)&keepalive, sizeof(keepalive));

	if(bind(socket->sock, &localAddress, sizeof(localAddress)) == -1) {
		closesocket(socket->sock);
		return CHATFalse;
	}
	if(connect(socket->sock, &address, sizeof(address)) == -1) {
		closesocket(socket->sock);
		return CHATFalse;
	}

	socket->connectState = ciConnected;
	return CHATTrue;
}

static void ciSocketSelect(unsigned int socket, CHATBool *readFlag, CHATBool *writeFlag, CHATBool *exceptFlag)
{
	int readable = 0;
	int writable = 0;
	int exceptional = 0;
	GSISocketSelect(socket, &readable, &writable, &exceptional);
	if (readFlag)
		*readFlag = readable;
	if (writeFlag)
		*writeFlag = writable;
	if (exceptFlag)
		*exceptFlag = exceptional;
}

static void ciSocketThinkSend(ciSocket *socket)
{
	while (socket->outputQueue.length > 0) {
		CHATBool writeFlag;
		ciSocketSelect(socket->sock, NULL, &writeFlag, NULL);
		if (!writeFlag)
			return;

		int length = socket->outputQueue.length < 1024 ? socket->outputQueue.length : 1024;
		int result = send(socket->sock, socket->outputQueue.buffer, length, 0);
		if (result == 0 || result == -1)
			return;
		ciBufferClipFront(&socket->outputQueue, result);
	}
}

static void ciSocketThinkRecv(ciSocket *socket)
{
	for (;;) {
		CHATBool readFlag;
		ciSocketSelect(socket->sock, &readFlag, NULL, NULL);
		if (!readFlag)
			return;
		if (!ciBufferPreAppend(&socket->inputQueue, 4096))
			return;

		char *position = socket->inputQueue.buffer + socket->inputQueue.length;
		int result = recv(socket->sock, position, 4096, 0);
		if (result <= 0) {
			WSAGetLastError();
			socket->connectState = ciDisconnected;
			return;
		}
		if (socket->secure)
			gs_crypt((unsigned char *)position, result, &socket->inKey);
		socket->inputQueue.length += result;
		socket->inputQueue.buffer[socket->inputQueue.length] = '\0';
	}
}

void ciSocketDisconnect(ciSocket *socket)
{
	if (socket->sock != ~0U) {
		shutdown(socket->sock, 2);
		closesocket(socket->sock);
	}

	socket->connectState = ciDisconnected;
	ciBufferFree(&socket->inputQueue);
	ciBufferFree(&socket->outputQueue);

	free(socket->lastMessage.message);
	free(socket->lastMessage.server);
	free(socket->lastMessage.nick);
	free(socket->lastMessage.user);
	free(socket->lastMessage.host);
	free(socket->lastMessage.command);
	free(socket->lastMessage.middle);
	free(socket->lastMessage.param);
	for (int i = 0; i < socket->lastMessage.numParams; ++i)
		free(socket->lastMessage.params[i]);
	free(socket->lastMessage.params);
}

void ciSocketThink(ciSocket *socket)
{
	if (socket->connectState == ciDisconnected)
		return;
	ciSocketThinkSend(socket);
	ciSocketThinkRecv(socket);
}

CHATBool ciSocketSend(ciSocket *socket, const char *buffer)
{
	if (socket->connectState == ciDisconnected)
		return CHATTrue;

	int length = (int)strlen(buffer);
	if (!ciBufferPreAppend(&socket->outputQueue, length + 2))
		return CHATFalse;

	char *position = socket->outputQueue.buffer + socket->outputQueue.length;
	memcpy(position, buffer, (unsigned int)length);
	socket->outputQueue.length += length;
	socket->outputQueue.buffer[socket->outputQueue.length++] = '\r';
	socket->outputQueue.buffer[socket->outputQueue.length++] = '\n';
	if (socket->secure)
		gs_crypt((unsigned char *)position, length + 2, &socket->outKey);
	return CHATTrue;
}

CHATBool ciSocketSendf(ciSocket *socket, const char *format, ...)
{
	static char buffer[4096];
	if (socket->connectState == ciDisconnected)
		return CHATTrue;

	va_list arguments;
	va_start(arguments, format);
	int count = vsprintf(buffer, format, arguments);
	if (count != -1)
		buffer[count] = '\0';
	else
		buffer[sizeof(buffer) - 1] = '\0';
	return ciSocketSend(socket, buffer);
}

}
