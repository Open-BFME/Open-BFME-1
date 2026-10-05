// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /Iinputs/reference/shims/iniexception

// ?bfmeSetupAPB@@YAHXZ 0x00061380
// The retail body updates TheCommandLineFlags at 0x012A6FA0, marks the second CRC
// mode at 0x012ED4E6, and rejects the mode pair through the shared INIException
// text at 0x01075230 when g_deepCRC at 0x012ED4E5 is already set.

typedef unsigned int UnsignedInt;

extern UnsignedInt TheCommandLineFlags;
extern bool g_deepCRC;
bool g_liteCRC = false;
#include "Common/INIException.h"

int bfmeSetupAPB(void)
{
	g_liteCRC = true;
	TheCommandLineFlags |= 0x20000;
	if (g_deepCRC)
	{
		throw INIException(3, "Do not specify both -deepCRC and -liteCRC in your commandline arguments.");
	}
	return 1;
}
