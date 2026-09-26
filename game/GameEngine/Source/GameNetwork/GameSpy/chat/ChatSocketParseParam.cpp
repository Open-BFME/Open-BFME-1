// cl: /DNDEBUG /MD
// GameSpy Chat 1.15.00 chatSocket.c: ciAddParam and its real ciParseParam
// caller are kept together because VC7.1 gives the file-static helper a private
// register ABI.  Retail enters ciAddParam with param in EBX and message in EDI.

#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef int CHATBool;
enum { CHATFalse, CHATTrue };

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

#define gsimalloc malloc
#define gsirealloc realloc
#define gsifree free

extern "C" {

static CHATBool ciAddParam(const char *param, ciServerMessage *message)
{
	void *tempPtr;

	tempPtr = gsirealloc(message->params, sizeof(char *) * (message->numParams + 1));
	if (tempPtr == NULL)
		return CHATFalse;
	message->params = (char **)tempPtr;

	tempPtr = gsimalloc(strlen(param) + 1);
	if (tempPtr == NULL)
		return CHATFalse;

	strcpy((char *)tempPtr, param);
	message->params[message->numParams++] = (char *)tempPtr;
	return CHATTrue;
}

CHATBool ciParseParam(const char *pText, ciServerMessage *message)
{
	char *colon;
	char *str;
	char *p;

	assert(pText != NULL);
	assert(message != NULL);

	p = (char *)gsimalloc(strlen(pText) + 1);
	if (p == NULL)
		return CHATFalse;
	strcpy(p, pText);

	if (p[0] == ':') {
		p[0] = '\0';
		colon = &p[1];
	} else {
		colon = strstr(p, " :");
		if (colon != NULL) {
			*colon = '\0';
			colon += 2;
		}
	}

	str = strtok(p, " ");
	while (str != NULL) {
		if (!ciAddParam(str, message)) {
			gsifree(p);
			return CHATFalse;
		}
		str = strtok(NULL, " ");
	}

	if (colon != NULL) {
		if (!ciAddParam(colon, message)) {
			gsifree(p);
			return CHATFalse;
		}
	}

	gsifree(p);
	return CHATTrue;
}

}
