// cl: /DNDEBUG /MD -Iinputs/reference/shims/gamespy
/* GameSpy Peer SDK piParseUTM, retail 0x0086B040.

   The two buffers are consecutive in retail: the eight-byte command at
   VA 0x0130E6A0 and the 512-byte parameter string at VA 0x0130E6A8. */

#include <string.h>

typedef enum
{
	PEERFalse,
	PEERTrue
} PEERBool;

#define PI_UTM_COMMAND_LEN 8
#define PI_UTM_PARAMATERS_LEN 512

char piUTMCommand[PI_UTM_COMMAND_LEN];
char piUTMParameters[PI_UTM_PARAMATERS_LEN];

PEERBool piParseUTM(const char *message)
{
	int len;

	if(!message)
		return PEERFalse;

	len = (int)strcspn(message, "/ ");
	if(len >= PI_UTM_COMMAND_LEN)
		return PEERFalse;
	memcpy(piUTMCommand, message, (unsigned int)len);
	piUTMCommand[len] = '\0';

	message += len;
	if(message[0])
	{
		message++;
		if(strlen(message) >= PI_UTM_PARAMATERS_LEN)
			return PEERFalse;
		strcpy(piUTMParameters, message);
	}
	else
	{
		piUTMParameters[0] = '\0';
	}

	return PEERTrue;
}
