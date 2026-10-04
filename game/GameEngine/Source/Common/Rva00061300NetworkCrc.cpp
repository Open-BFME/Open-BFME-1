// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /Iinputs/reference/shims/iniexception
// Open-BFME5: register the network CRC debug switch and reject the two
// mutually-exclusive CRC command-line modes.

typedef unsigned int UnsignedInt;

extern UnsignedInt TheCommandLineFlags;
bool g_deepCRC = false;
extern bool g_liteCRC;
#include "Common/INIException.h"

struct Rva00889690Obj
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7C();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual bool registerCommand(const char *text);
};

extern Rva00889690Obj *g_rva00889690;

int Rva00061300NetworkCrc(void)
{
	g_deepCRC = true;
	TheCommandLineFlags |= 0x10000;
	g_rva00889690->registerCommand("debug.add l + NETWORK_CRC");
	if (g_liteCRC)
	{
		throw INIException(3, "Do not specify both -deepCRC and -liteCRC in your commandline arguments.");
	}
	return 1;
}
