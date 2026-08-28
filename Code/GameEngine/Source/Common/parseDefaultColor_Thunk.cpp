// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift the retail default-color parser to clean C++.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString() { freeBytes(); }

private:
	void freeBytes();
	void *m_data;
};

class File
{
public:
	virtual ~File() = 0;
	virtual void open() = 0;
	virtual void close() = 0;
	virtual int read(void *, int) = 0;
	virtual int write(const void *, int) = 0;
	virtual int seek(int, int) = 0;
	virtual void nextLine(char *, int) = 0;
	virtual bool scanInt(int &) = 0;
	virtual bool scanReal(float &) = 0;
	virtual bool scanString(AsciiString &) = 0;
};

void readUntilSemicolon(File *, char *, int);
static bool parseColor(int *, char *);
extern "C" int __cdecl strcmp(const char *, const char *);

// ?parseDefaultColor@@YA_NPAHPAVFile@@PAD@Z
// The retail helper is file-local.  Its sibling call graph gives MSVC 7.1 an
// internal register ABI, so the TU-local parseColor and call helper below keep
// that same compiler context while this body remains ordinary C++.
static bool parseDefaultColor(int *color, File *inFile, char *buffer)
{
	AsciiString str;
	inFile->scanString(str);
	readUntilSemicolon(inFile, buffer, 0x800);

	if (!strcmp(buffer, "TRANSPARENT"))
	{
		*color = 0xFFFFFF;
	}
	else
	{
		parseColor(color, buffer);
	}

	return true;
}

extern "C" __declspec(dllimport) int __cdecl atoi(const char *);

__declspec(noinline) static bool parseColor(int *color, char *buffer)
{
	*color = atoi(buffer);
	return true;
}

static int parseDefaultColorValue;
static char parseDefaultColorBuffer[0x800];

bool parseDefaultColorCall(File *inFile)
{
	return parseDefaultColor(&parseDefaultColorValue, inFile, parseDefaultColorBuffer);
}
