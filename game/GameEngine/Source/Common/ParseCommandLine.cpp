// The retail command-line parser is a distinct 0x63BA0 body.  Keep its
// narrow ABI/layout view here so the reconstructed body does not inherit the
// later release parser's table and ArchiveFileSystem shape.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /Iinputs/vendor/stlport /Iinputs/reference/shims/stringinline /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/sweep

#include "StringInline.h"

#include "../../Include/Common/ScalarTypes.h"


class GlobalData;								///< retail pointee at 0x012ED5C8
extern GlobalData *TheWritableGlobalData;		///< retail [0x012ED5C8]
extern void __cdecl setPathWithSlash(const char *path);

// TU-local layout view of retail's GlobalData; the real class is not needed here.
struct ParseCommandLineGlobalData
{
	unsigned char m_pad[0xdc0];
	AsciiString m_modDir;
	AsciiString m_modBIG;
};


class ArchiveFile;

// The incremental-link thunk at retail 0x00038B22 is the ledger's 5-byte row
// ?j_00038b22@@YAXXZ (game/gen_small/thunks_027.cpp); its body at 0x0063960 is
// the matched AsciiString-to-pointer map operator[].  The class below is this
// TU's view of ArchiveFileSystem::m_archiveFileMap (+0x04): one-argument
// operator[] over the AsciiString key.  Nothing defines a method spelled
// insert() here -- the old name was an address-derived placeholder -- so the
// call names the thunk the ledger owns.
extern void j_00038b22();

class BfmeSubMap3B3
{
public:
	void *&operator[](void *key)
	{
		union
		{
			void (*raw)(void);
			void *&(BfmeSubMap3B3::*typed)(void *);
		} call;
		call.raw = &j_00038b22;
		return (this->*call.typed)(key);
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
extern Int Rva00060CD0_parse(char *args[], int);
extern Int parseFullVersion(char *args[], int);

// The flags Zero Hour has no handler for (and -scriptDebug2 above) bind
// retail's own bodies: each entry's ILT thunk lands on the body named here
// (T3CommandLineParsers.cpp, Rva00061150Set.cpp). EA's names are unknown.
extern Int Rva00060D00_parse(char *args[], int);
extern int rva00061DE0Set();
extern Int Rva00060970_parse(char *args[], int);
extern Int Rva00060980_parse(char *args[], int);

static CommandLineParam params[] =
{
	{ "-noshellmap", parseNoShellMap },
	{ "-mod", parseMod },
	{ "-noaudio", parseNoAudio },
	{ "-xres", parseXRes },
	{ "-yres", parseYRes },
	{ "-win", parseWin },
	{ "-scriptDebug2", Rva00060CD0_parse },
	{ "-scriptDebugLite", Rva00060D00_parse },
	{ "-fullVersion", parseFullVersion },
	{ "-preferLocalFiles", (CommandLineHandler)rva00061DE0Set },
	{ "-Watchdog", Rva00060970_parse },
	{ "-noWatchdog", Rva00060980_parse }
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

	if (stringNotEmpty(((ParseCommandLineGlobalData *)TheWritableGlobalData)->m_modBIG))
	{
		ArchiveFile *archiveFile =
			TheArchiveFileSystem->openArchiveFile(((ParseCommandLineGlobalData *)TheWritableGlobalData)->m_modBIG.str());
		if (archiveFile != 0)
		{
			loadMod(TheArchiveFileSystem, archiveFile,
				(AsciiString *)((char *)TheWritableGlobalData + 0xdc4));
		}
	}

	if (stringNotEmpty(((ParseCommandLineGlobalData *)TheWritableGlobalData)->m_modDir))
	{
		TheArchiveFileSystem->loadBigFilesFromDirectory(
			((ParseCommandLineGlobalData *)TheWritableGlobalData)->m_modDir, "*.big", true);
		setPathWithSlash(((ParseCommandLineGlobalData *)TheWritableGlobalData)->m_modDir.str());
	}
}
