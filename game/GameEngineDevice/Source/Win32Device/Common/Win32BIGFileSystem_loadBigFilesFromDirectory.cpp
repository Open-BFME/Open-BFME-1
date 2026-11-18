// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /Iinputs/reference/shims/ini /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include <map>
#include <set>
#include <vector>
#include <algorithm>

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ArchiveFile.h
class ArchiveFile
{
public:
	virtual ~ArchiveFile();
};

#include "../../../../GameEngine/Include/Common/ScalarTypes.h"


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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/Win32Device/Common/Win32BIGFileSystem.h
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/LocalFileSystem.h
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

// Q3SortElem4 bridges the verified by-value resize ABI to vector<AsciiString>.
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
		void resize(unsigned int count) { resize(count, Q3SortElem4()); }
	};
}

struct Q3SortCompare
{
};

void Rva009CDB40(Q3SortElem4 *first, Q3SortElem4 *last, Q3SortCompare comp);

// ?loadBigFilesFromDirectory@Win32BIGFileSystem@@UAE_NVAsciiString@@0_N@Z
Bool Win32BIGFileSystem::loadBigFilesFromDirectory( AsciiString dir, AsciiString fileMask,
                                                    Bool overwrite )
{
	FilenameList filenameList;
	TheLocalFileSystem->getFileListInDirectory( dir, AsciiString( "" ), fileMask, filenameList, TRUE );

	std::vector<AsciiString> ordered;
	reinterpret_cast<_STL::vector<Q3SortElem4, _STL::allocator<Q3SortElem4> > *>
		(&ordered)->resize( filenameList.size() );
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
