// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// readable body of ?open@StreamingArchiveFile@@: Code/GameEngine/Source/Common/System/StreamingArchiveFile.cpp
//
// Isolated TU for StreamingArchiveFile::open(const char*, Int).
//
// The vendored Zero Hour File/RAMFile/StreamingArchiveFile headers under
// reference/ under-count this class's vtable by two slots: BFME's File class
// appends two virtuals of its own, lock() and unlock(), after Zero Hour's
// convertToRAMFile (see Code/GameEngine/Source/Common/System/File.cpp, slots
// 15 and 16). Every subclass's own new virtuals -- RAMFile's open(File*),
// openFromArchive, copyDataToFile -- sit two slots further out than the
// vendored header predicts as a result. This function calls
// RAMFile::open(File*) virtually (`return (open(file) != NULL);`), and retail
// dispatches it through vtable+0x44, not the +0x40 the vendored layout gives,
// so a local replica carrying the same 17-slot File layout File.cpp already
// proved is required here instead of the shared reference headers.
//
// Only the slot COUNT matters for this function -- it never constructs a
// File/RAMFile/StreamingArchiveFile or calls anything but open() and
// FileSystem::openFile, so the other virtuals are declared (to keep every
// slot index correct and keep the unqualified call `open(file)` from being
// hidden by this class's own open(const char*, Int) overload) but never
// defined.
#include "PreRTS.h"
#include "Common/AsciiString.h"

class File
{
public:
	enum access
	{
		READ		= 0x0001,
		WRITE		= 0x0002,
		APPEND		= 0x0004,
		TRUNCATE	= 0x0010,
		TEXT		= 0x0020,
		BINARY		= 0x0040,
		STREAMING	= 0x0100
	};

	enum seekMode { START, CURRENT, END };

	File();
	Bool eof( void );
	virtual ~File();								// slot 0
	virtual Bool open( const char *filename, Int access = 0 );	// slot 1
	virtual void close( void );					// slot 2
	virtual Int read( void *buffer, Int bytes );	// slot 3
	virtual Int write( const void *buffer, Int bytes );	// slot 4
	virtual Int seek( Int bytes, Int mode );		// slot 5
	virtual void nextLine( char *buf, Int bufSize );	// slot 6
	virtual Bool scanInt( Int &newInt );			// slot 7
	virtual Bool scanReal( Real &newReal );		// slot 8
	virtual Bool scanString( AsciiString &newString );	// slot 9
	virtual Bool print( const char *format, ... );	// slot 10
	virtual Int size( void );						// slot 11
	virtual Int position( void );					// slot 12
	virtual char *readEntireAndClose( void );		// slot 13
	virtual File *convertToRAMFile( void );		// slot 14
	// BFME additions -- see File.cpp for the evidence.
	virtual void lock( void );						// slot 15
	virtual void unlock( void );					// slot 16

protected:
	AsciiString m_nameStr;
	Int m_access;
	Bool m_open;
	Bool m_deleteOnClose;
	HANDLE m_mutex;
};

class RAMFile : public File
{
public:
	virtual Bool open( const char *filename, Int access = 0 );
	virtual void close( void );
	virtual Int read( void *buffer, Int bytes );
	virtual Int write( const void *buffer, Int bytes );
	virtual Int seek( Int bytes, Int mode );
	virtual void nextLine( char *buf, Int bufSize );
	virtual Bool scanInt( Int &newInt );
	virtual Bool scanReal( Real &newReal );
	virtual Bool scanString( AsciiString &newString );
	// New virtuals RAMFile introduces -- these are the ones that land two
	// slots later than the vendored header says, on account of File::lock/unlock.
	virtual Bool open( File *file );				// slot 17
	virtual Bool openFromArchive( File *archiveFile, const AsciiString &filename, Int offset, Int size );	// slot 18
	virtual Bool copyDataToFile( File *localFile );	// slot 19
	virtual char *readEntireAndClose( void );
	virtual File *convertToRAMFile( void );

protected:
	char *m_data;
	Int m_pos;
	Int m_size;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StreamingArchiveFile.h
class StreamingArchiveFile : public RAMFile
{
public:
	virtual Bool open( const char *filename, Int access = 0 );
	virtual Bool open( File *file );

protected:
	File *m_file;
	Int m_startingPos;
	Int m_size;
	Int m_curPos;
};

class FileSystem
{
public:
	File *openFile( const char *filename, Int access = 0 );
};

extern FileSystem *TheFileSystem;

//=================================================================
// StreamingArchiveFile::open
//=================================================================
/**
  *	This function opens a file using the standard C open() call. Access flags
	* are mapped to the appropriate open flags. Returns true if file was opened
	* successfully.
	*/
//=================================================================

// ?open@StreamingArchiveFile@@UAE_NPBDH@Z
Bool StreamingArchiveFile::open( const char *filename, Int access )
{
	File *file = TheFileSystem->openFile( filename, access );

	if ( file == NULL )
	{
		return FALSE;
	}

	return (open( file ) != NULL);
}
