// ?loadBigFilesFromDirectory@Win32BIGFileSystem@@UAE_NVAsciiString@@0_N@Z
// partial score=0.94 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /Ireference/shims/ini /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
//
// Win32BIGFileSystem::loadBigFilesFromDirectory, retail 0x009CDB90, 459 bytes --
// vtable slot 9 of 0x01143B40, which init reaches through [eax+0x24].
//
// Its own translation unit because it needs exceptions: it opens with the fs:[0]
// prologue where closeArchiveFile next door has no SEH frame at all.
//
// Zero Hour's body reaches 332 bytes of the 459. The missing code includes
// the vector work retail makes between filling the filename list and
// iterating it: 0x009CD890 (123B) is the by-value resize helper,
// 0x009CC4C0 (61B) copies the set into the vector, and 0x009CDB40 (74B) is
// the Q3 sort driver. The retail loop also replaces an existing map entry's
// archive before assigning the newly opened archive.
//
// BFME copies the list into a vector and sends the range to the recovered Q3
// sort driver. FilenameList is keyed on rts::less_than_nocase, so this is not
// equivalent to simply iterating the set: the vector uses the game's sort
// family and comparator ABI.
//
// How each step was established, by length against retail's 459:
//
//   Zero Hour's body, no vector at all      332
//   + resize / copy / Q3 sort               421
//   + map find/delete before assignment     459   <- current target shape
//
// The frame and operation graph are now the useful comparison points; register
// assignment and local temporary ordering still need compiler validation.
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
typedef bool Bool;
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

// Retail's four-byte string sort family is already recovered under the
// address-derived Q3SortElem4 spelling.  This TU-local view is only an ABI
// bridge: the storage remains the real vector<AsciiString> below.
struct Q3SortElem4
{
	Q3SortElem4() : m_string() {}
	Q3SortElem4( const Q3SortElem4 &other ) : m_string( other.m_string ) {}
	~Q3SortElem4() {}
	AsciiString m_string;
};

namespace _STL
{
	template <>
	class vector<Q3SortElem4, allocator<Q3SortElem4> >
	{
	public:
		void resize(unsigned int count, Q3SortElem4 value);
	};
}

struct Q3SortCompare
{
};

void Rva009CDB40(Q3SortElem4 *first, Q3SortElem4 *last, Q3SortCompare comp);

// ?loadBigFilesFromDirectory@Win32BIGFileSystem@@UAEHVAsciiString@@0H@Z present-unmatched
Bool Win32BIGFileSystem::loadBigFilesFromDirectory( AsciiString dir, AsciiString fileMask,
                                                    Bool overwrite )
{
	FilenameList filenameList;
	TheLocalFileSystem->getFileListInDirectory( dir, AsciiString( "" ), fileMask, filenameList, TRUE );

	std::vector<AsciiString> ordered;
	reinterpret_cast<_STL::vector<Q3SortElem4, _STL::allocator<Q3SortElem4> > *>
		(&ordered)->resize( filenameList.size(), Q3SortElem4() );
	std::copy( filenameList.begin(), filenameList.end(), ordered.begin() );
	Rva009CDB40( reinterpret_cast<Q3SortElem4 *>( ordered.begin() ),
		reinterpret_cast<Q3SortElem4 *>( ordered.end() ), Q3SortCompare() );

	bool actuallyAdded = false;
	std::vector<AsciiString>::iterator it = ordered.begin();
	while (it != ordered.end()) {
		ArchiveFile *archiveFile = openArchiveFile( (*it).str() );

		if (archiveFile != NULL) {
			loadIntoDirectoryTree( archiveFile, *it, overwrite );
			ArchiveFileMap::iterator existing = m_archiveFileMap.find( *it );
			if ( existing != m_archiveFileMap.end() ) {
				delete existing->second;
			}
			m_archiveFileMap[(*it)] = archiveFile;
			actuallyAdded = true;
		}

		it++;
	}

	return actuallyAdded;
}
