// cl: /DNDEBUG /MD /EHa /Oy-

#include <string.h>

typedef void *HANDLE;

extern "C" __declspec(dllimport) HANDLE __stdcall CreateMutexA(
	void *, int, const char *);
extern "C" __declspec(dllimport) void *__stdcall SetUnhandledExceptionFilter(
	void *);
extern "C" __declspec(dllimport) unsigned long __stdcall GetModuleFileNameA(
	void *, char *, unsigned long);
extern "C" __declspec(dllimport) int __stdcall DeleteFileA(const char *);
extern "C" __declspec(dllimport) char *__cdecl strrchr(const char *, int);

class DebugExceptionhandler
{
public:
	static long __stdcall ExceptionFilter(void *);
};

void d_0088e970(void);

class Rva0088CDC0Forwarder
{
public:
	Rva0088CDC0Forwarder *forward();
};

class DebugMember : public Rva0088CDC0Forwarder
{
public:
	DebugMember()
	{
		forward();
	}
	~DebugMember();
};

struct DebugIoBuffer
{
	void *buffer;
	unsigned used;
	unsigned alloc;
	unsigned char lastWasCR;
	unsigned char pad[3];
};

class Debug
{
public:
	virtual ~Debug();

private:
	Debug();

	void *hrTranslators;
	unsigned numHrTranslators;
	void *firstIOFactory;
	void *firstCmdGroup;
	unsigned curStackFrame;
	unsigned frameHash[10007];
	void *nextUnusedFrameHash;
	unsigned numAvailableFrameHash;
	void *bfmeField9C7C;
	void *firstLogGroup;
	DebugIoBuffer ioBuffer[7];
	int curType;
	char curSource[256];
	int disableAssertsEtc;
	void *curFrameEntry;
	void *firstPatternEntry;
	void *lastPatternEntry;
	char curCommandGroup[100];
	unsigned char alwaysFlush;
	unsigned char timeStamp;
	unsigned char bfmeField9E6E;
	DebugMember stackWalk;
	char prefix[16];
	int radix;
	char version[64];
	char internalVersion[64];
	char buildDate[64];
	int width;
	char fillChar;
	char isWindowed;
	char field9F4A;
	char field9F4B;
	char field9F4C;
	HANDLE mutex;
	unsigned threadId;
	char field9F58;
};

Debug::Debug()
	: stackWalk()
{
	curStackFrame = 0;
	hrTranslators = 0;
	numHrTranslators = 0;
	firstIOFactory = 0;
	firstCmdGroup = 0;
	memset(frameHash, 0, sizeof(frameHash));
	nextUnusedFrameHash = 0;
	numAvailableFrameHash = 0;
	firstLogGroup = 0;
	memset(ioBuffer, 0, sizeof(ioBuffer));
	curType = 7;
	curSource[0] = 0;
	disableAssertsEtc = 0;
	curFrameEntry = 0;
	firstPatternEntry = 0;
	lastPatternEntry = 0;
	curCommandGroup[0] = 0;
	alwaysFlush = 0;
	timeStamp = 0;
	bfmeField9E6E = 0;
	radix = 10;
	fillChar = ' ';
	field9F4A = 0;
	field9F4B = 0;
	field9F4C = 0;
	isWindowed = 0;
	bfmeField9C7C = 0;
	field9F58 = 0;
	mutex = CreateMutexA(0, 0, 0);
	SetUnhandledExceptionFilter(DebugExceptionhandler::ExceptionFilter);
	d_0088e970();

	char path[512];
	GetModuleFileNameA(0, path, 0x200);
	char *slash = strrchr(path, '\\');
	const char *deletePath;
	if (slash)
	{
		*(unsigned *)slash = *(unsigned *)0x0113304C;
		*(unsigned *)(slash + 4) = *(unsigned *)0x01133050;
		*(unsigned *)(slash + 8) = *(unsigned *)0x01133054;
		deletePath = path;
	}
	else
	{
		deletePath = (const char *)0x01133040;
	}
	DeleteFileA(deletePath);
}
