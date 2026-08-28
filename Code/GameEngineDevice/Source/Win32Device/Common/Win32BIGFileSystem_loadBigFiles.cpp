// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /Ireference/shims/ini /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// Win32BIGFileSystem::loadBigFilesFromDirectory, retail 0x009CDB90, 459 bytes --
// vtable slot 9 of 0x01143B40, which init reaches through [eax+0x24].
//
// Its own translation unit because it needs exceptions: it opens with the fs:[0]
// prologue where closeArchiveFile next door has no SEH frame at all.
//
// Zero Hour's body reaches 332 bytes of the 459. The missing ~127 are three
// helper calls retail makes between filling the filename list and iterating it,
// which look like vector work: 0x009CD890 (123B) compares a count against
// (end - begin) / 4, which is a resize; 0x009CC4C0 (61B) takes five arguments;
// and 0x009CDB40 (74B) halves a range repeatedly, which is sort machinery.
//
// That hypothesis was right, and the shape is now settled: BFME copies the list
// into a vector, stable_sorts it, and REVERSES it. Not redundant even though the
// set is already ordered -- FilenameList is keyed on rts::less_than_nocase, so
// it is in case-insensitive order, and the vector is then put into descending
// default order instead. For .big files that sequence is load precedence, so it
// is a deliberate change rather than a copy for its own sake.
//
// How each step was established, by length against retail's 459:
//
//   Zero Hour's body, no vector at all      332
//   + resize / copy / sort                  403
//   + range-construct instead               397
//   + assign instead                        387
//   + stable_sort rather than sort          413
//   + reverse after the sort                459   <- exact
//
// The frame (0x20) and all four callee-saved registers now match too, so the
// remaining 386 differing bytes are register assignment: retail holds `this` in
// edi and the zero constant in ebx, this holds them in esi and ebx respectively,
// and everything downstream renames with them. One knock-on worth not
// mistaking for structure: retail stores a literal zero (c6 00 00) where this
// stores a register that holds zero (88 18) -- same operation, different
// encoding, purely because of where the zero lives.
//
// NOT claimed. The length agreeing at every step above is good evidence the
// operations are right, but it is not proof, and the register assignment is
// unresolved.

#include "Common/AsciiString.h"
#include <map>
#include <set>
#include <vector>
#include <algorithm>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ArchiveFile.h
class ArchiveFile
{
public:
	virtual ~ArchiveFile();
};

typedef char Char;
typedef int Int;
typedef int Bool;
#define TRUE 1
#define FALSE 0

namespace rts
{
	template <class T> struct less_than_nocase
	{
		bool operator()( const T &a, const T &b ) const;
	};
}

typedef std::map<AsciiString, ArchiveFile *> ArchiveFileMap;
typedef std::set<AsciiString, rts::less_than_nocase<AsciiString> > FilenameList;

class File;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/Win32Device/Common/Win32BIGFileSystem.h
class Win32BIGFileSystem
{
public:
	virtual ~Win32BIGFileSystem();											// slot 0
	virtual void init( void );												// slot 1
	virtual ArchiveFile *openArchiveFile( const Char *filename );			// slot 2
	virtual void closeArchiveFile( const Char *filename ) = 0;				// slot 3
	virtual void closeAllArchiveFiles( void ) = 0;							// slot 4
	virtual File *openFile( const Char *f, Int a, Int a3, Int a4 ) = 0;		// slot 6
	virtual File *openFile( const Char *f, Int a ) = 0;						// slot 5
	virtual void closeAllFiles( void ) = 0;									// slot 7
	virtual Bool doesFileExist( const Char *filename ) const = 0;			// slot 8
	virtual Bool loadBigFilesFromDirectory( AsciiString dir, AsciiString fileMask,
	                                        Bool overwrite );				// slot 9
	virtual void loadIntoDirectoryTree( const ArchiveFile *archiveFile,
	                                    const AsciiString &archiveFilename,
	                                    Bool overwrite ) = 0;				// slot 10

protected:
	ArchiveFileMap m_archiveFileMap;	// +0x04
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/LocalFileSystem.h
class LocalFileSystem
{
public:
	virtual ~LocalFileSystem();
	virtual void L1() = 0;
	virtual void L2() = 0;
	virtual void L3() = 0;
	virtual void L4() = 0;
	// slot 5 = +0x14
	virtual void getFileListInDirectory( const AsciiString &currentDirectory,
	                                     const AsciiString &originalDirectory,
	                                     const AsciiString &searchName,
	                                     FilenameList &filenameList,
	                                     Bool searchSubdirectories ) const = 0;
};

extern LocalFileSystem *TheLocalFileSystem;

// ?loadBigFilesFromDirectory@Win32BIGFileSystem@@UAEHVAsciiString@@0H@Z present-unmatched
Bool Win32BIGFileSystem::loadBigFilesFromDirectory( AsciiString dir, AsciiString fileMask,
                                                    Bool overwrite )
{
	FilenameList filenameList;
	TheLocalFileSystem->getFileListInDirectory( dir, AsciiString( "" ), fileMask, filenameList, TRUE );

	std::vector<AsciiString> ordered;
	ordered.resize( filenameList.size() );
	std::copy( filenameList.begin(), filenameList.end(), ordered.begin() );
	std::stable_sort( ordered.begin(), ordered.end() );
	std::reverse( ordered.begin(), ordered.end() );

	Bool actuallyAdded = FALSE;
	std::vector<AsciiString>::iterator it = ordered.begin();
	while (it != ordered.end()) {
		ArchiveFile *archiveFile = openArchiveFile( (*it).str() );

		if (archiveFile != NULL) {
			loadIntoDirectoryTree( archiveFile, *it, overwrite );
			m_archiveFileMap[(*it)] = archiveFile;
			actuallyAdded = TRUE;
		}

		it++;
	}

	return actuallyAdded;
}
