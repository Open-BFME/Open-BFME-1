// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
//
// Win32BIGFile::getFileInfo.
//
// Zero Hour's version stops after copying the archive entry's stored size into
// the FileInfo. BFME's keeps going: it seeks the .big to the entry's offset,
// reads a six byte header, and if the first two bytes are the 0x15FB
// compression magic it decodes the next four -- big endian -- as the
// decompressed length and reports that instead. So a compressed entry's
// getFileInfo answers with the size the caller will actually get from
// openFile, not the size on disk.
//
// It lives in its own translation unit for the same reason the destructor and
// the two name accessors do: retail reaches WWLib's StringBase<char> through
// out-of-line calls (the const char * constructor at 0x00888BC0 for the
// temporary, releaseBuffer at 0x00887940 to destroy it) where Zero Hour's
// Common/AsciiString.h inlines both. Everything else here is a slot-pinned
// skeleton -- the classes exist only to place fields and virtuals where retail's
// instruction stream proves they are.
#include "string_base.h"

typedef int Int;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString( const char *s )
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase( s );
	}

	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

	// StringBase's Header is { int ref_count; short length; short capacity; }
	// ahead of the characters, which is the +8 retail adds after the null test.
	const char *str( void ) const { return m_data ? m_data + 8 : ""; }

private:
	char *m_data;
};

// Six bytes off the front of an archived entry. Splitting the size into its own
// four byte array is what makes retail's two loads: MSVC pairs adjacent byte
// reads into one access and widens it as far as the array allows, so size[0]
// and size[1] arrive in a dword and size[2] and size[3] -- with only two bytes
// of the array left -- in a word. A flat six byte buffer gets neither, because
// then the pair straddles no array boundary the compiler will widen to.
struct CompressionHeader
{
	unsigned char magic[2];
	unsigned char size[4];
};

struct FileInfo
{
	unsigned int sizeHigh;			// +0x00
	unsigned int sizeLow;			// +0x04
	unsigned int timestampHigh;		// +0x08
	unsigned int timestampLow;		// +0x0c
};

class File
{
public:
	enum seekMode { START = 0, CURRENT = 1, END = 2 };

	virtual ~File();							// slot 0
	virtual Bool open( const char *filename, Int access );			// slot 1
	virtual void close( void );						// slot 2
	virtual Int read( void *buffer, Int bytes );				// slot 3
	virtual Int write( const void *buffer, Int bytes );			// slot 4
	virtual Int seek( Int bytes, seekMode mode );				// slot 5

	const AsciiString &getName( void ) const { return m_nameStr; }

protected:
	AsciiString m_nameStr;			// +0x04
};

// Only slot 6 matters -- retail's call is call dword ptr [edx+0x18]. The five
// ahead of it are the destructor plus SubsystemInterface's init/reset/update
// and LocalFileSystem's own openFile.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/LocalFileSystem.h
class LocalFileSystem
{
public:
	virtual ~LocalFileSystem();						// slot 0
	virtual void init( void );						// slot 1
	virtual void reset( void );						// slot 2
	virtual void update( void );						// slot 3
	virtual File *openFile( const char *filename, Int access );		// slot 4
	virtual Bool doesFileExist( const char *filename ) const;		// slot 5
	virtual Bool getFileInfo( const AsciiString &filename, FileInfo *fileInfo ) const;	// slot 6
};

extern LocalFileSystem *TheLocalFileSystem;

// The two AsciiStrings ahead of m_offset are the entry's own name and the name
// of the archive holding it; neither is touched here.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ArchiveFileSystem.h
struct ArchivedFileInfo
{
	char *m_filename;			// +0x00
	char *m_archiveFilename;		// +0x04
	unsigned int m_offset;			// +0x08
	unsigned int m_size;			// +0x0c
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ArchiveFile.h
class ArchiveFile
{
public:
	virtual ~ArchiveFile();

protected:
	const ArchivedFileInfo *getArchivedFileInfo( const AsciiString &filename ) const;

	File *m_file;				// +0x04
	char m_opaque[0x1c];			// the archived-directory tree, +0x08 through +0x23
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/Win32Device/Common/Win32BIGFile.h
class Win32BIGFile : public ArchiveFile
{
public:
	virtual ~Win32BIGFile();						// slot 0
	virtual Bool getFileInfo( const AsciiString &filename, FileInfo *fileInfo ) const;	// slot 1
};

// ?getFileInfo@Win32BIGFile@@UBE_NABVAsciiString@@PAUFileInfo@@@Z
Bool Win32BIGFile::getFileInfo( const AsciiString &filename, FileInfo *fileInfo ) const
{
	const ArchivedFileInfo *tempFileInfo = getArchivedFileInfo( filename );

	if( tempFileInfo == 0 )
	{
		return false;
	}

	TheLocalFileSystem->getFileInfo( AsciiString( m_file->getName().str() ), fileInfo );

	// The size cannot exceed a .big's own, so the high word is always zero.
	fileInfo->sizeHigh = 0;
	fileInfo->sizeLow = tempFileInfo->m_size;

	m_file->seek( tempFileInfo->m_offset, File::START );

	CompressionHeader header;
	if( m_file->read( &header, sizeof( header ) ) == sizeof( header ) )
	{
		if( ((header.magic[0] << 8) | header.magic[1]) == 0x15FB )
		{
			// Written as a loop, not four unrolled ors: MSVC unrolls it two
			// iterations at a time and that is what pairs the byte loads. Any
			// hand-unrolled spelling of the same value -- including the one that
			// parenthesises the halves exactly the way the target computes them --
			// schedules the third byte's load early and loses the pairing.
			Int size = 0;
			for( Int i = 0; i < 4; i++ )
			{
				size = (size << 8) | header.size[i];
			}
			if( size > 0 )
			{
				fileInfo->sizeLow = size;
			}
		}
	}

	return true;
}
