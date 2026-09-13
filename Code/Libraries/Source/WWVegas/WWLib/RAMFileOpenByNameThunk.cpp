// cl: /DNDEBUG /MD /EHs-c-
// Open-BFME5: RAMFile::open(const Char *, Int), retail 0x009D1A00,
// zh_sweep packet 009d1a00.
//
// The reference body ports unchanged: ask TheFileSystem for the named file,
// bail on NULL, slurp it through the RAMFile::open(File *) overload, then close
// the local file and hand back what the slurp said.
//
// What this address pins is the vtable, and it agrees with what the RAMFile
// constructor at 0x009D1980 already told us. The slurping overload is called
// through [this+0x44], so it is slot 17, so BFME's File has seventeen slots
// before RAMFile adds any -- Zero Hour's File has fifteen. The two extra are
// the lock/unlock pair the ctor row records at slots 15 and 16, which is
// exactly the gap. The close() on the returned file goes through [file+0x08],
// slot 2, which is where File::close sits in both games.
//
// Its own TU because BFME has no RAMFile.cpp yet; File.cpp holds the two
// constructors and nothing that would fix this vtable.

typedef int Int;
typedef bool Bool;
typedef char Char;
typedef float Real;

#define FALSE false
#define NULL 0

class File;
class AsciiString;

class File
{
public:
	virtual ~File();													///< +0x00
	virtual Bool open( const Char *filename, Int access );			///< +0x04
	virtual void close( void );										///< +0x08
	virtual Int read( void *buffer, Int bytes ) = 0;					///< +0x0C
	virtual Int write( const void *buffer, Int bytes ) = 0;			///< +0x10
	virtual Int seek( Int bytes, Int mode ) = 0;					///< +0x14
	virtual void nextLine( Char *buf, Int bufSize ) = 0;			///< +0x18
	virtual Bool scanInt( Int &newInt ) = 0;						///< +0x1C
	virtual Bool scanReal( Real &newReal ) = 0;						///< +0x20
	virtual Bool scanString( AsciiString &newString ) = 0;			///< +0x24
	virtual Bool print( const Char *format, ... );					///< +0x28
	virtual Int size( void );										///< +0x2C
	virtual Int position( void );									///< +0x30
	virtual char *readEntireAndClose( void ) = 0;					///< +0x34
	virtual File *convertToRAMFile( void ) = 0;						///< +0x38
	virtual void lock( void );										///< +0x3C
	virtual void unlock( void );									///< +0x40

private:
	unsigned char m_unreconstructed_04[0x10];
};

class RAMFile : public File
{
public:
	virtual Bool open( const Char *filename, Int access );			///< +0x04, override
	virtual Bool open( File *file );								///< +0x44
};

class FileSystem
{
public:
	File *openFile( const Char *filename, Int access );
};

extern FileSystem *TheFileSystem;

// ?open@RAMFile@@UAE_NPBDH@Z
Bool RAMFile::open( const Char *filename, Int access )
{
	File *file = TheFileSystem->openFile( filename, access );

	if ( file == NULL )
	{
		return FALSE;
	}

	Bool result = open( file );

	file->close();

	return result;
}
