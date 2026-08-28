// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
//
// Win32BIGFile::openFile(const Char *, Int, Int, Int) -- the four-argument form
// the two-argument one in Win32BIGFileOpen.cpp forwards to with two zeros.
//
// The extra pair is an offset bias and a length override: the entry is read from
// m_offset + offset for `size` bytes, and a zero size means "the whole entry".
// The two-argument form therefore reads the entry exactly as Zero Hour's single
// openFile does, which is why the forward can pass zeros.
//
// Three things here are not in Zero Hour's body:
//   - it calls its own tenth slot first, so every open rewrites the archive's
//     name and path (see Win32BIGFileSetName.cpp);
//   - it brackets the read with File::lock and File::unlock, vtable slots 15 and
//     16 -- the BFME-only mutex pair that the File vtable reconstruction turned
//     up, and this is the call site that confirms them;
//   - the read failure path unlocks before closing rather than after, which is
//     why the unlock appears twice instead of once above the branch.
//
// It is a separate translation unit from the two-argument forward because it
// needs the delegating AsciiString -- it builds two temporaries from the
// filename, one per callee -- and the forward matched against a bare skeleton
// that has no AsciiString at all. Everything below is slot-pinned scaffolding;
// only the offsets and slots retail's instruction stream proves are real.
#include "string_base.h"

typedef char Char;
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

private:
	char *m_data;
};

class File
{
public:
	enum { READ = 0x01, WRITE = 0x02, TEXT = 0x20, BINARY = 0x40, STREAMING = 0x100 };

	virtual ~File();							// slot 0
	virtual Bool open( const Char *filename, Int access );			// slot 1
	virtual void close( void );						// slot 2
	virtual Int read( void *buffer, Int bytes );				// slot 3
	virtual Int write( const void *buffer, Int bytes );			// slot 4
	virtual Int seek( Int bytes, Int mode );				// slot 5
	virtual void nextLine( char *buf, Int bufSize );			// slot 6
	virtual Bool scanInt( Int &newInt );					// slot 7
	virtual Bool scanReal( float &newReal );				// slot 8
	virtual Bool scanString( AsciiString &newString );			// slot 9
	virtual Bool print( const char *format, ... );				// slot 10
	virtual Int size( void );						// slot 11
	virtual Int position( void );						// slot 12
	virtual char *readEntireAndClose( void );				// slot 13
	virtual File *convertToRAMFile( void );					// slot 14
	virtual void lock( void );						// slot 15
	virtual void unlock( void );						// slot 16

	void deleteOnClose( void ) { m_deleteOnClose = true; }

protected:
	char m_head[0x09];			// m_nameStr +0x04, m_access +0x08
	Bool m_deleteOnClose;			// +0x0d
	char m_tail[0x06];			// +0x0e padding, then m_mutex at +0x10
};

// Slot 17 is a BFME virtual with no name yet; it only has to sit here so
// openFromArchive and copyDataToFile land on 0x48 and 0x4c.
class RAMFile : public File
{
public:
	RAMFile();

	virtual void reserved17( void );					// slot 17
	virtual Bool openFromArchive( File *archiveFile, const AsciiString &filename, Int offset, Int size );	// slot 18
	virtual Bool copyDataToFile( File *localFile );				// slot 19

protected:
	char m_ramFileFields[0x0c];		// +0x14 through +0x1f, sizeof 0x20
};

// sizeof 0x2c -- retail's operator new argument on the streaming branch.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StreamingArchiveFile.h
class StreamingArchiveFile : public RAMFile
{
public:
	StreamingArchiveFile();

protected:
	char m_streamingFields[0x0c];		// +0x20 through +0x2b
};

// Only slot 2 is proven here: retail's call is call dword ptr [edx+8].
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/LocalFileSystem.h
class LocalFileSystem
{
public:
	virtual ~LocalFileSystem();						// slot 0
	virtual void init( void );						// slot 1
	virtual File *openFile( const Char *filename, Int access );		// slot 2
};

extern LocalFileSystem *TheLocalFileSystem;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ArchiveFileSystem.h
struct ArchivedFileInfo
{
	AsciiString m_filename;			// +0x00
	char *m_archiveFilename;		// +0x04
	unsigned int m_offset;			// +0x08
	unsigned int m_size;			// +0x0c
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ArchiveFile.h
class ArchiveFile
{
public:
	virtual ~ArchiveFile();							// slot 0
	virtual Bool getFileInfo( const AsciiString &filename, void *fileInfo ) const;	// slot 1
	// Reversed on purpose: MSVC lays overloads of one name into the vtable back
	// to front, so declaring the four-argument form first is what puts it at
	// slot 3 and the forward at slot 2.
	virtual File *openFile( const Char *filename, Int access, Int offset, Int size );	// slot 3
	virtual File *openFile( const Char *filename, Int access );		// slot 2
	virtual void closeAllFiles( void );					// slot 4
	virtual AsciiString *getName( void );					// slot 5
	virtual AsciiString *getPath( void );					// slot 6
	virtual void setSearchPriority( Int new_priority );			// slot 7
	virtual void close( void );						// slot 8
	virtual void setNameAndPath( const AsciiString &filename );		// slot 9

protected:
	const ArchivedFileInfo *getArchivedFileInfo( const AsciiString &filename ) const;

	File *m_file;				// +0x04
	char m_opaque[0x1c];			// the archived-directory tree, +0x08 through +0x23
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/Win32Device/Common/Win32BIGFile.h
class Win32BIGFile : public ArchiveFile
{
public:
	virtual File *openFile( const Char *filename, Int access, Int offset, Int size );
};

// ?openFile@Win32BIGFile@@UAEPAVFile@@PBDHHH@Z
File *Win32BIGFile::openFile( const Char *filename, Int access, Int offset, Int size )
{
	setNameAndPath( AsciiString( filename ) );

	const ArchivedFileInfo *fileInfo = getArchivedFileInfo( AsciiString( filename ) );

	if( fileInfo == 0 )
	{
		return 0;
	}

	RAMFile *ramFile;

	if( access & File::STREAMING )
	{
		ramFile = new StreamingArchiveFile;
	}
	else
	{
		ramFile = new RAMFile;
	}

	ramFile->deleteOnClose();

	m_file->lock();

	Int length = size;
	if( length == 0 )
	{
		length = fileInfo->m_size;
	}

	if( ramFile->openFromArchive( m_file, fileInfo->m_filename, fileInfo->m_offset + offset, length ) == false )
	{
		m_file->unlock();
		ramFile->close();
		return 0;
	}

	m_file->unlock();

	if( (access & File::WRITE) == 0 )
	{
		return ramFile;
	}

	// Whoever asked for write access gets a copy on the local disk instead.
	File *localFile = TheLocalFileSystem->openFile( filename, access );
	if( localFile != 0 )
	{
		ramFile->copyDataToFile( localFile );
	}

	ramFile->close();

	return localFile;
}
