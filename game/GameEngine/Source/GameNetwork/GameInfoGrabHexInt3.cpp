// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport

#include <stdlib.h>

// ?grabHexInt3@@YAHPBD@Z
static int __cdecl grabHexInt3(const char *text)
{
	char buffer[6] = "0xfff";
	buffer[2] = text[0];
	buffer[3] = text[1];
	buffer[4] = text[2];
	return strtol(buffer, 0, 16);
}

int __cdecl callGrabHexInt3(const char *text)
{
	return grabHexInt3(text);
}
