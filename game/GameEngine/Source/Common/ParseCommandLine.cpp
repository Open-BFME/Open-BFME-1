// The retail command-line parser is a distinct 0x63BA0 body.  Keep its
// narrow ABI/layout view here so the reconstructed body does not inherit the
// later release parser's table and ArchiveFileSystem shape.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /Iinputs/vendor/stlport /Iinputs/reference/shims/stringinline /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep

#include "StringInline.h"

typedef int Int;
typedef bool Bool;

struct GlobalData
{
	unsigned char m_pad[0xdc0];
	AsciiString m_modDir;
	AsciiString m_modBIG;
};

extern GlobalData *TheWritableGlobalData;
extern void __cdecl setPathWithSlash(const char *path);

class ArchiveFile;

class BfmeSubMap3B3
{
public:
	void **insert(void *key);
	void *&operator[](void *key)
	{
		return *insert(key);
	}
};

class ArchiveFileSystem
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual ArchiveFile *openArchiveFile(const char *filename);
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual Int loadBigFilesFromDirectory(AsciiString dir, AsciiString fileMask,
		Bool overwrite);
	virtual void loadIntoDirectoryTree(const ArchiveFile *archiveFile,
		const AsciiString &archiveFilename, Bool overwrite);
	BfmeSubMap3B3 m_archiveFileMap;
};

extern ArchiveFileSystem *TheArchiveFileSystem;

typedef Int (__cdecl *CommandLineHandler)(char **args, Int count);

struct CommandLineParam
{
	const char *name;
	CommandLineHandler func;
};

extern Int parseNoShellMap(char *args[], int);
extern Int parseMod(char *args[], Int);
extern Int parseNoAudio(char *args[], int);
extern Int parseXRes(char *args[], int);
extern Int parseYRes(char *args[], int);
extern Int parseWin(char *args[], int);
extern Int parseScriptDebug(char *args[], int);
extern Int parseFullVersion(char *args[], int);

static __declspec(noinline) Int parseScriptDebugLite(char **, Int) { return 1; }
static __declspec(noinline) Int parsePreferLocalFiles(char **, Int) { return 1; }
static __declspec(noinline) Int parseWatchdog(char **, Int) { return 1; }
static __declspec(noinline) Int parseNoWatchdog(char **, Int) { return 1; }

static CommandLineParam params[] =
{
	{ "-noshellmap", parseNoShellMap },
	{ "-mod", parseMod },
	{ "-noaudio", parseNoAudio },
	{ "-xres", parseXRes },
	{ "-yres", parseYRes },
	{ "-win", parseWin },
	{ "-scriptDebug2", parseScriptDebug },
	{ "-scriptDebugLite", parseScriptDebugLite },
	{ "-fullVersion", parseFullVersion },
	{ "-preferLocalFiles", parsePreferLocalFiles },
	{ "-Watchdog", parseWatchdog },
	{ "-noWatchdog", parseNoWatchdog }
};

extern "C" unsigned __cdecl strlen(const char *text);
extern "C" __declspec(dllimport) int __cdecl _strnicmp(const char *left, const char *right,
	unsigned int count);
#pragma intrinsic(strlen)

static Bool stringNotEmpty(const AsciiString &value)
{
	const unsigned char *data = *(const unsigned char * const *)&value;
	return data != 0 && *(const unsigned short *)(data + 4) != 0;
}

static __forceinline void loadMod(ArchiveFileSystem *archiveSystem,
	ArchiveFile *archiveFile, AsciiString *modBig)
{
	archiveSystem->loadIntoDirectoryTree(archiveFile, *modBig, true);
	archiveSystem->m_archiveFileMap[(void *)modBig] = archiveFile;
}

void parseCommandLine(Int argc, char *argv[])
{
	Int arg = 1;
	Int param;
	Bool found;

	while (arg < argc)
	{
		found = false;
		for (param = 0; !found && param < sizeof(params);
			param += sizeof(params[0]))
		{
			Int len = strlen(*(const char **)((const char *)params + param));
			Int len2 = strlen(argv[arg]);
			if (argv[arg][0] == (char)0x96)
				argv[arg][0] = '-';
			if (len2 == len && !_strnicmp(argv[arg],
				*(const char **)((const char *)params + param), len))
			{
				arg += (*(CommandLineHandler *)((char *)params + param + 4))(
					argv + arg, argc - arg);
				found = true;
			}
		}
		if (!found)
			arg++;
	}

	if (stringNotEmpty(TheWritableGlobalData->m_modBIG))
	{
		ArchiveFile *archiveFile =
			TheArchiveFileSystem->openArchiveFile(TheWritableGlobalData->m_modBIG.str());
		if (archiveFile != 0)
		{
			loadMod(TheArchiveFileSystem, archiveFile,
				(AsciiString *)((char *)TheWritableGlobalData + 0xdc4));
		}
	}

	if (stringNotEmpty(TheWritableGlobalData->m_modDir))
	{
		TheArchiveFileSystem->loadBigFilesFromDirectory(
			TheWritableGlobalData->m_modDir, "*.big", true);
		setPathWithSlash(TheWritableGlobalData->m_modDir.str());
	}
}
