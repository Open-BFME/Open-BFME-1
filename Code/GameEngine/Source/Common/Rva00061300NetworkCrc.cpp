// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Open-BFME5: register the network CRC debug switch and reject the two
// mutually-exclusive CRC command-line modes.

typedef unsigned int UnsignedInt;

extern UnsignedInt TheCommandLineFlags;
extern bool g_bfmeOnAPB;
extern bool g_bfmeDoneAPB;
extern "C" char _bfmeTagAPB;
extern void __declspec(noreturn) __stdcall _CxxThrowException(void *object, void *throwInfo);

class Gen001336E5C
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

extern Gen001336E5C *TheGen001336E5C;

class INIException
{
public:
	INIException(int code, const char *message, ...);
	INIException(const INIException &other);

private:
	int m_code;
	const char *m_message;
};

int Rva00061300NetworkCrc(void)
{
	g_bfmeOnAPB = true;
	TheCommandLineFlags |= 0x10000;
	TheGen001336E5C->registerCommand("debug.add l + NETWORK_CRC");
	if (g_bfmeDoneAPB)
	{
		INIException error(3, "Do not specify both -deepCRC and -liteCRC in your commandline arguments.");
		_CxxThrowException(&error, &_bfmeTagAPB);
	}
	return 1;
}
