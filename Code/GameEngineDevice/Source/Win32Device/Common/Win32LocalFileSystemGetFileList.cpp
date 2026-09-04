// cl: /DNDEBUG /MD /EHsc /Ireference/shims/win32localfilesystem_wide /Ireference/shims/asciistring_thin /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4
#define _INTERNAL
#define DISABLE_ALLOW_DEBUG_UTILS
#define DISABLE_MEMORYPOOL_DEBUG_CUSTOM_NEW

#include <windows.h>
#include "Common/AsciiString.h"
#include "Common/GameMemory.h"
#include "Common/PerfTimer.h"
#include "Win32Device/Common/Win32LocalFileSystem.h"
#include <io.h>

static inline Int bfmeLength( const AsciiString &s )
{
	const char *d = *(const char * const *)&s;
	return d ? *(const unsigned short *)(d + 4) : 0;
}

static inline const char *bfmeStr( const AsciiString &s )
{
	const char *d = *(const char * const *)&s;
	return d ? d + 8 : "";
}

template <class T> class StringBase
{
public:
	void concat( const T *s, int len );
};

static inline void bfmeConcat( AsciiString &s, const AsciiString &v )
{
	((StringBase<char> *)&s)->concat( bfmeStr( v ), bfmeLength( v ) );
}

static inline void bfmeConcat( AsciiString &s, char c )
{
	((StringBase<char> *)&s)->concat( &c, 1 );
}

static inline void bfmeConcat( AsciiString &s, const char *v )
{
	((StringBase<char> *)&s)->concat( v, v ? (int)strlen( v ) : 0 );
}

void Win32LocalFileSystem::getFileListInDirectory(const AsciiString& currentDirectory, const AsciiString& originalDirectory, const AsciiString& searchName, FilenameList & filenameList, Bool searchSubdirectories) const
{
	HANDLE fileHandle = NULL;
	WIN32_FIND_DATA findData;

	char search[_MAX_PATH];
	AsciiString asciisearch;
	asciisearch = originalDirectory;
	bfmeConcat(asciisearch, currentDirectory);
	bfmeConcat(asciisearch, searchName);
	strcpy(search, bfmeStr(asciisearch));

	Bool done = FALSE;

	fileHandle = FindFirstFile(search, &findData);
	done = (fileHandle == INVALID_HANDLE_VALUE);

	while (!done)	{
		if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
				(strcmp(findData.cFileName, ".") && strcmp(findData.cFileName, ".."))) {
			// if we haven't already, add this filename to the list.
				// a stl set should only allow one copy of each filename
				AsciiString newFilename;
				newFilename = originalDirectory;
				bfmeConcat(newFilename, currentDirectory);
				bfmeConcat(newFilename, findData.cFileName);
				if (filenameList.find(newFilename) == filenameList.end()) {
					filenameList.insert(newFilename);
				}
		}

		done = (FindNextFile(fileHandle, &findData) == 0);
	}
	FindClose(fileHandle);

	if (searchSubdirectories) {
		AsciiString subdirsearch;
		subdirsearch = originalDirectory;
		bfmeConcat(subdirsearch, currentDirectory);
		bfmeConcat(subdirsearch, "*.");
		fileHandle = FindFirstFile(bfmeStr(subdirsearch), &findData);
		done = fileHandle == INVALID_HANDLE_VALUE;

		while (!done) {
			if ((findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
					(strcmp(findData.cFileName, ".") && strcmp(findData.cFileName, ".."))) {

					AsciiString tempsearchstr;
					bfmeConcat(tempsearchstr, currentDirectory);
					bfmeConcat(tempsearchstr, findData.cFileName);
					bfmeConcat(tempsearchstr, '\\');
					
					// recursively add files in subdirectories if required.
					getFileListInDirectory(tempsearchstr, originalDirectory, searchName, filenameList, searchSubdirectories);
			}

			done = (FindNextFile(fileHandle, &findData) == 0);
		}

		FindClose(fileHandle);
	}
}
