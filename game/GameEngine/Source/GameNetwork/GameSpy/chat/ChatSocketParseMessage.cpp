// cl: /DNDEBUG /MD
// GameSpy Chat 1.15.00 chatSocket.c parser cluster.  These bodies stay in one
// TU because VC7.1 gives ciParseMessage and ciParseInput private register ABIs.

#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef int CHATBool;
enum { CHATFalse, CHATTrue };

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
	int connectState;
	char serverAddress[256];
	ciBuffer inputQueue;
	ciBuffer outputQueue;
	CHATBool secure;
	gs_crypt_key inKey;
	gs_crypt_key outKey;
	ciServerMessage lastMessage;
};

#define gsimalloc malloc
#define gsifree free
#define RESET(ptr) { if(ptr) { gsifree(ptr); ptr = NULL; } }

extern "C" CHATBool ciParseParam(const char *pText, ciServerMessage *message);

extern "C" {

static void ciBufferClipFront(ciBuffer *buffer, int len)
{
	buffer->length -= len;
	memmove(buffer->buffer, buffer->buffer + len,
		(unsigned int)buffer->length);
	buffer->buffer[buffer->length] = '\0';
}

static CHATBool ciParseUser(const char *pText, ciServerMessage *message)
{
	char *pTmpNick = NULL, *pTmpUsername = NULL, *pTmpHost = NULL;
	int nNick = 0, nUsername = 0, nHost = 0;
	char *p;

	if(pText == NULL || pText[0] == '\0')
		return CHATFalse;

	p = pTmpNick = (char *)pText;
	while(*p != '\0')
	{
		if(*p != '!')
		{
			++p;
			++nNick;
		}
		else
		{
			pTmpUsername = ++p;
			while(*p != '\0')
			{
				if(*p != '@')
				{
					++p;
					++nUsername;
				}
				else
				{
					pTmpHost = ++p;
					while(*p != '\0')
					{
						++p;
						++nHost;
					}
				}
			}
		}
	}

	if(nNick)
	{
		message->nick = (char *)gsimalloc((unsigned int)nNick + 1);
		if(message->nick)
		{
			memcpy(message->nick, pTmpNick, (unsigned int)nNick);
			message->nick[nNick] = '\0';
		}
	}
	else
		message->nick = NULL;

	if(nUsername)
	{
		message->user = (char *)gsimalloc((unsigned int)nUsername + 1);
		if(message->user)
		{
			memcpy(message->user, pTmpUsername, (unsigned int)nUsername);
			message->user[nUsername] = '\0';
		}
	}
	else
		message->user = NULL;

	if(nHost)
	{
		message->host = (char *)gsimalloc((unsigned int)nHost + 1);
		if(message->host)
		{
			memcpy(message->host, pTmpHost, (unsigned int)nHost);
			message->host[nHost] = '\0';
		}
	}
	else
		message->host = NULL;

	return CHATTrue;
}

static CHATBool ciParseMessage(ciSocket *sock, const char *sText)
{
	int nMessage = 0, nServer = 0, nCommand = 0, nMiddle = 0, nParam = 0;
	char *p, *temp;
	ciServerMessage *message = &sock->lastMessage;

	if(sText == NULL || sText[0] == '\0')
		return CHATFalse;

	nMessage = (int)strlen(sText);
	message->message = (char *)gsimalloc((unsigned int)nMessage + 1);
	if(message->message == NULL)
		return CHATFalse;
	memcpy(message->message, sText, (unsigned int)nMessage);
	message->message[nMessage] = '\0';

	p = (char *)sText;
	while(*p == '\n' || *p == '\r')
		++p;

	if(*p == ':')
	{
		message->server = ++p;
		if(*p != '\0')
		{
			while(*p != ' ' && *p != '\0')
			{
				++nServer;
				++p;
			}
		}
	}

	while(*p == ' ')
		++p;
	if(*p != '\0')
	{
		message->command = p;
		while(*p != ' ' && *p != '\0')
		{
			++nCommand;
			++p;
		}
	}

	while(*p == ' ')
		++p;
	if(*p != ':' && *p != '\0')
	{
		message->middle = p;
		while(*p != ' ' && *p != '\0')
		{
			++nMiddle;
			++p;
		}
	}

	while(*p == ' ')
		++p;
	if(*p != '\0')
	{
		message->param = p;
		while(*p != '\0')
		{
			++nParam;
			++p;
		}
	}

	if(nServer)
	{
		temp = message->server;
		message->server = (char *)gsimalloc((unsigned int)nServer + 1);
		if(message->server)
		{
			memcpy(message->server, temp, (unsigned int)nServer);
			message->server[nServer] = '\0';
		}
		if(!ciParseUser(message->server, message))
		{
			RESET(message->message);
			RESET(message->server);
			return CHATFalse;
		}
	}
	else
	{
		message->server = NULL;
		message->nick = NULL;
		message->user = NULL;
		message->host = NULL;
	}

	if(nMiddle)
	{
		if(!ciParseParam(message->middle, message))
		{
			RESET(message->message);
			RESET(message->server);
			RESET(message->nick);
			RESET(message->user);
			RESET(message->host);
			return CHATFalse;
		}
	}
	else if(nParam)
	{
		if(!ciParseParam(message->param, message))
		{
			RESET(message->message);
			RESET(message->server);
			RESET(message->nick);
			RESET(message->user);
			RESET(message->host);
			return CHATFalse;
		}
	}
	else
	{
		message->params = NULL;
		message->numParams = 0;
	}

	if(nParam)
	{
		temp = message->param;
		message->param = (char *)gsimalloc((unsigned int)nParam + 1);
		if(message->param)
		{
			memcpy(message->param, temp, (unsigned int)nParam);
			message->param[nParam] = '\0';
		}
	}
	else
		message->param = NULL;

	if(nCommand)
	{
		temp = message->command;
		message->command = (char *)gsimalloc((unsigned int)nCommand + 1);
		if(message->command)
		{
			memcpy(message->command, temp, (unsigned int)nCommand);
			message->command[nCommand] = '\0';
		}
	}
	else
		message->command = NULL;

	if(nMiddle)
	{
		temp = message->middle;
		message->middle = (char *)gsimalloc((unsigned int)nMiddle + 1);
		if(message->middle)
		{
			memcpy(message->middle, temp, (unsigned int)nMiddle);
			message->middle[nMiddle] = '\0';
		}
	}
	else
		message->middle = NULL;

	return CHATTrue;
}

static CHATBool ciParseInput(ciSocket *sock)
{
	char *p, *q, *r;
	char temp;
	int i;

	p = sock->inputQueue.buffer;
	if(*p != '\0')
	{
		while(*p == 13 || *p == 10)
			++p;
		if(*p != '\0')
		{
			r = q = p;
			while(*q != 10 && *q != 13 && *q != '\0')
			{
				if(*q != ' ')
					r = q;
				++q;
			}
			if(*q != '\0')
			{
				++r;
				temp = *r;
				*r = '\0';

				RESET(sock->lastMessage.message);
				RESET(sock->lastMessage.server);
				RESET(sock->lastMessage.nick);
				RESET(sock->lastMessage.user);
				RESET(sock->lastMessage.host);
				RESET(sock->lastMessage.command);
				RESET(sock->lastMessage.middle);
				RESET(sock->lastMessage.param);
				for(i = 0; i < sock->lastMessage.numParams; i++)
					RESET(sock->lastMessage.params[i]);
				RESET(sock->lastMessage.params);
				sock->lastMessage.numParams = 0;

				memset(&sock->lastMessage, 0, sizeof(sock->lastMessage));
				if(!ciParseMessage(sock, p))
				{
					memset(&sock->lastMessage, 0, sizeof(sock->lastMessage));
					return CHATFalse;
				}

				*r = temp;
				ciBufferClipFront(&sock->inputQueue,
					(int)(q - sock->inputQueue.buffer));
				return CHATTrue;
			}
		}
	}
	return CHATFalse;
}

ciServerMessage *ciSocketRecv(ciSocket *sock)
{
	if(sock->inputQueue.length == 0)
		return NULL;
	if(!ciParseInput(sock))
		return NULL;
	return &sock->lastMessage;
}

}
