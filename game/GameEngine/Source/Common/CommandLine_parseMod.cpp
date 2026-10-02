// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// parseMod, retail 0x000624F0, 478 bytes.
// Identity: the retail CommandLineParam table entry { "-mod" (0x01075204),
// ILT 0x00040070 -> 0x000624F0 } and the Zero Hour twin in CommandLine.cpp.
// BFME adds the g_rva00061DE0 store (the search-order Bool documented in
// FileSystem_openFile.cpp, whose writer list names 0x00062512) and calls the
// non-virtual FileSystem::doesFileExist through TheFileSystem (0x0134CB48).
// GlobalData+0xDC0/+0xDC4 are m_modDir/m_modBIG as in ParseCommandLine.cpp.

#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "ascii_string.h"

template <class T> inline void StringBase<T>::concat(T c) { concat(&c, 1); }

typedef int Int;

class GlobalData
{
public:
	AsciiString getPath_UserData(void) const;

	unsigned char m_pad[0xdc0];
	AsciiString m_modDir;
	AsciiString m_modBIG;
};

extern GlobalData *TheWritableGlobalData;
#define TheGlobalData ((const GlobalData *)TheWritableGlobalData)

class FileSystem
{
public:
	bool doesFileExist(const char *filename) const;
};

extern FileSystem *TheFileSystem;

extern char g_rva00061DE0[];

Int parseMod(char *args[], Int num)
{
	g_rva00061DE0[0] = 1;
	if (TheWritableGlobalData && num > 1)
	{
		AsciiString modPath = args[1];
		if (strchr(modPath.str(), ':') || modPath.startsWith("/") || modPath.startsWith("\\"))
		{
			// full path passed in.  Don't append base path.
		}
		else
		{
			modPath.format("%s%s", TheGlobalData->getPath_UserData().str(), args[1]);
		}

		if (!TheFileSystem->doesFileExist(modPath.str()))
		{
			return 2; // no such file/dir.
		}

		// now check for dir-ness
		struct _stat statBuf;
		if (_stat(modPath.str(), &statBuf) != 0)
		{
			return 2; // could not stat the file/dir.
		}

		if (statBuf.st_mode & _S_IFDIR)
		{
			if (!modPath.endsWith("\\") && !modPath.endsWith("/"))
				modPath.concat('\\');
			TheWritableGlobalData->m_modDir = modPath;
		}
		else
		{
			TheWritableGlobalData->m_modBIG = modPath;
		}

		return 2;
	}
	return 1;
}
