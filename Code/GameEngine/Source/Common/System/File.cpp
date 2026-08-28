// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/ini /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// readable body of ?Free_Definitions@DefinitionMgrClass@@: Code/Libraries/Source/WWVegas/WWSaveLoad/definitionmgr.cpp
//
// The File base class. Its three subclasses' vtables all carry
// ?close@File@@UAEXXZ at slot 2, which is what identifies the family, and BFME's
// layout is Zero Hour's 15 File slots with two appended -- so slots 0..14 mean
// exactly what Zero Hour's file.h declares them to mean:
//
//   0x01143A38  MemoryReadFile
//   0x01143AA8  MemoryWriteFile
//   0x01143AF8  File itself
//
// The first two are named by their own constructors. 0x009CB3D0 installs
// 0x01143A38 and then sets the file's name to "<MemoryReadFile>"; 0x009CB4E0
// installs 0x01143AA8 and sets "<MemoryWriteFile>". That is the same kind of
// evidence "<no file>" gives for File -- a literal the object's own constructor
// uses to identify it -- and both classes are BFME-only, appearing nowhere in
// the Zero Hour tree.
//
// There are seven File vtables in all, found by looking for the ones that carry
// File::print (0x009CB6C0) at slot 10, which every subclass here inherits:
//
//   0x01143A38  MemoryReadFile        dtor 0x009CB440
//   0x01143AA8  MemoryWriteFile       dtor 0x009CB650
//   0x01143AF8  File                  dtor 0x009CB950
//   0x01143C10  Win32LocalFile        dtor 0x009D1960   ctor 0x009D1930
//   0x01143C58  RAMFile               dtor 0x009D1C30   ctor 0x009D1980
//   0x01143CA8  StreamingArchiveFile  dtor 0x009D22B0   ctor 0x009D20B0
//   0x01143D38  LocalFile             dtor 0x009D26C0   ctor 0x009D23E0
//
// Measured state of 0x009C9000-0x009CE000, since "the File family" is often
// taken to mean that range: it holds 282 real functions once the 5-byte
// incremental-link thunks are discounted, and 36 of them are claimed. 33 of
// those 36 are this file; the rest are two Win32LocalFileSystem rows,
// ArchiveFileSystem, ArchiveFile and one MASM dump.
//
// The other 246 are not waiting on effort. Running tools/locate.py over
// ArchiveFileSystem.cpp, ArchiveFile.cpp, Win32LocalFileSystem.cpp and
// FileSystem.cpp places nothing at all: 114 definitions come back ambiguous,
// because they are STL instantiations over AsciiString-keyed maps of
// ArchivedFileInfo and DetailedArchivedDirectoryInfo whose bodies are identical
// at six or more addresses, and 245 come back unlocated, because BFME rewrote
// the archive file system and Zero Hour's source no longer assembles to it.
// None of the eighteen largest unclaimed functions references a string, so
// there is nothing to anchor a name to either.
//
// So the range is 13% claimed and the remainder is a rewrite to recover rather
// than a gap to fill. The File subclasses themselves -- the part that had names
// to find -- are done.
//
// So the family runs past 0x009CE000 into 0x009D2xxx. None of the last four set
// an identifying literal the way MemoryReadFile and MemoryWriteFile do, so they
// are named by construction instead:
//
// Win32LocalFileSystem's vtable is 0x01143B98 (its constructor is 0x009CDE10),
// and it is identified by two rows this ledger already carries -- slot 4 is
// ?doesFileExist@Win32LocalFileSystem@@UBE_NPBD@Z and slot 6 is
// ?getFileInfo@Win32LocalFileSystem@@UBE_NABVAsciiString@@PAUFileInfo@@@Z. Its
// slot 3, 0x009CDF50, is openFile: it does push 0x18 / call operator new /
// call 0x009D1930. So 0x009D1930 constructs what a local file system hands
// back, sizeof 0x18, and that constructor installs 0x01143C10 -- Win32LocalFile.
//
// 0x009D1930 chains to 0x009D23E0, which installs 0x01143D38 and stores -1 at
// +0x14. A base of Win32LocalFile holding an invalid-handle sentinel is
// LocalFile, and +0x14 is the OS file handle -- the one File's own +0x10 is not.
//
// The other two are named by the fields their constructors zero, matching Zero
// Hour's declarations exactly: 0x009D1980 calls File::File and zeroes +0x14,
// +0x18 and +0x1c, which is RAMFile's char *m_data / Int m_size / Int m_pos
// (sizeof 0x20); 0x009D20B0 calls that constructor and zeroes +0x20, +0x24 and
// +0x28, which is StreamingArchiveFile's File *m_file / Int m_startingPos /
// Int m_size on top of RAMFile (sizeof 0x2C). That also settles the "Streaming
// from a compressed archive file is not supported" lead: the string belongs to
// StreamingArchiveFile at 0x01143CA8, not to 0x01143C10.
//
// 0x01143AF8 is File's own: MemoryReadFile's constructor calls 0x009CB7A0 first,
// and that is what stores 0x01143AF8 and sets "<no file>", so 0x009CB7A0 is
// File::File and 0x009CB8C0 (which MemoryReadFile's deleting destructor calls)
// is File::~File. Counting slots forward from a vtable overruns into the next
// one -- .rdata packs them adjacently with nothing between -- so all three are
// 17 slots, not the 40 a naive walk reports for the last.
//
// Slots holding the same address in all three are File's own un-overridden
// implementations: slot 2 close (0x009CB880), slot 10 print (0x009CB6C0), and
// slots 15/16 (0x009CB760, 0x009CB790) -- the two BFME added, which Zero Hour
// has no name for.
//
// The class is declared here rather than taken from Zero Hour's Common/file.h
// because BFME's differs in the two ways close() shows: File is not a
// MemoryPoolObject here (m_deleteOnClose closes by deleting through the vtable,
// not through the pool's three-call sequence), and the member layout is proven
// directly -- m_nameStr at +4, m_open at +0xc, m_deleteOnClose at +0xd.
#include "PreRTS.h"
#include "Common/AsciiString.h"

class File
{
public:
	// Access flags. TEXT is the bit print() tests -- retail is
	// test byte ptr [esi+8], 0x20 -- and READ|BINARY is what MemoryReadFile's
	// constructor stores (0x41).
	// The values beyond READ/WRITE/TEXT/BINARY are the ones File::open tests:
	// its two illegal-combination checks are `and 0x102` and `and 0x60`, and its
	// three defaulting steps are `test al,3 / or 1`, `test al,5 / or 0x10` and
	// `test al,0x60 / or 0x40` -- i.e. STREAMING|WRITE, TEXT|BINARY, READ|WRITE,
	// READ|APPEND and TEXT|BINARY against Zero Hour's numbering, unchanged.
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
	// Non-virtual, so it adds no slot. Retail expresses it purely through the
	// two virtuals below, which is what pins their slot numbers independently.
	Bool eof( void );
	virtual ~File();							// slot 0
	virtual Bool open( const char *filename, Int access = 0 );	// slot 1
	virtual void close( void );					// slot 2
	virtual Int read( void *buffer, Int bytes );			// slot 3
	virtual Int write( const void *buffer, Int bytes );		// slot 4
	virtual Int seek( Int bytes, Int mode );				// slot 5
	virtual void nextLine( char *buf, Int bufSize );		// slot 6
	virtual Bool scanInt( Int &newInt );				// slot 7
	virtual Bool scanReal( Real &newReal );				// slot 8
	virtual Bool scanString( AsciiString &newString );		// slot 9
	virtual Bool print( const char *format, ... );			// slot 10
	virtual Int size( void );					// slot 11
	virtual Int position( void );					// slot 12
	virtual char *readEntireAndClose( void );			// slot 13
	virtual File *convertToRAMFile( void );				// slot 14
	// Slots 15 and 16 are BFME additions Zero Hour has no name for. They are a
	// mutex acquire/release pair over m_mutex, read straight out of the imports
	// the two bodies call: 0x009CB760 reaches KERNEL32!CreateMutexA and
	// !WaitForSingleObject, 0x009CB790 reaches !ReleaseMutex.
	virtual void lock( void );					// slot 15
	virtual void unlock( void );					// slot 16

protected:
	// Spelled as a direct set() rather than m_nameStr = name. Going through
	// operator= makes &m_nameStr a parameter of an inlined member call, so it is
	// materialised at the inline site instead of at the call -- which shows up in
	// ~File as lea ecx,[esi+4] before the string push rather than after.
	void setName( const char *name )
	{
		((StringBase<char> *)&m_nameStr)->set( name, name ? (int)strlen( name ) : 0 );
	}

	AsciiString m_nameStr;		// +0x04
	Int m_access;				// +0x08
	Bool m_open;				// +0x0c
	Bool m_deleteOnClose;		// +0x0d
	// Not a file handle: lock() creates it with CreateMutexA and unlock()
	// releases it, so the CloseHandle in ~File is closing a mutex. The OS file
	// handle lives one field further on, in the subclass that owns it.
	HANDLE m_mutex;				// +0x10
};

// ?open@File@@UAE_NPBDH@Z
// File's own slot 1 -- the base implementation subclasses call up into. It
// records the access mode and marks the file open; it never touches a handle,
// which is why every subclass vtable that does not override slot 1 points here.
Bool File::open( const char *filename, Int access )
{
	if( m_open )
	{
		return FALSE;
	}

	// This is exactly what `m_nameStr = filename` expands to, written out. It has
	// to be written out: going through operator= makes &m_nameStr a parameter of
	// an inlined member call, so it is materialised at the inline site -- above
	// the null/strlen diamond -- which occupies ecx, pushes filename into a
	// callee-saved register, and costs a third push/pop pair plus a loop-align
	// nop. Six bytes too many, and none of them where the difference is. Called
	// directly, the receiver sinks to the call and retail's shape falls out:
	// push len, push filename, lea ecx,[edi+4], call.
	((StringBase<char> *)&m_nameStr)->set( filename, filename ? (int)strlen( filename ) : 0 );

	if( (access & ( STREAMING | WRITE )) == ( STREAMING | WRITE ))
	{
		// illegal access
		return FALSE;
	}

	if( (access & ( TEXT | BINARY)) == ( TEXT | BINARY ))
	{
		// illegal access
		return FALSE;
	}

	if ( (access & (READ|WRITE)) == 0 )
	{
		access |= READ;
	}

	if ( !(access & (READ|APPEND)) )
	{
		access |= TRUNCATE;
	}

	if ( (access & (TEXT|BINARY)) == 0 )
	{
		access |= BINARY;
	}

	m_access = access;
	m_open = TRUE;
	return TRUE;
}

// ?size@File@@UAEHXZ
// Slot 11. Measures by seeking, so it works for any subclass that implements
// seek and nothing else -- which is why File, and the four subclasses that do
// not override it, all share this one body.
Int File::size( void )
{
	Int pos = seek( 0, CURRENT );
	Int size = seek( 0, END );

	seek( pos, START );

	return size < 0 ? 0 : size;
}

// ?position@File@@UAEHXZ
// Slot 12.
Int File::position( void )
{
	return seek( 0, CURRENT );
}

// Retail 0x009CB740, 30 bytes. Reads position through vtable slot 12 ([eax+0x30])
// and size through slot 11 ([edx+0x2c]), compares them, and returns the Bool via
// the sub/neg/sbb/inc idiom MSVC uses for `== 0`. position is called FIRST, which
// is the order this expression has to produce.
Bool File::eof( void )
{
	return position() == size();
}

// ?close@File@@UAEXXZ
// Must be called once per successful open(). Zero Hour ends with
// this->deleteInstance(); BFME clears m_deleteOnClose first and then deletes
// through vtable slot 0 -- a plain delete this, not MemoryPoolObject's
// getObjectMemoryPool/dtor/freeBlock sequence.
void File::close( void )
{
	if( m_open )
	{
		setName( "<no file>" );
		m_open = FALSE;
		if ( m_deleteOnClose )
		{
			m_deleteOnClose = FALSE;
			delete this;
		}
	}
}

// ?print@File@@UAA_NPBDZZ
// Slot 10, and the same address in all three vtables, so this is File's own.
// TEXT is 0x20 in m_access, read straight off retail's test byte ptr [esi+8], 0x20.
Bool File::print( const char *format, ... )
{
	char buffer[10*1024];
	Int len;

	if ( ! (m_access & TEXT ) )
	{
		return FALSE;
	}

	va_list args;
	va_start( args, format );
	len = vsprintf( buffer, format, args );
	va_end( args );

	if ( len >= sizeof(buffer) )
	{
		return FALSE;
	}

	return (write ( buffer, len ) == len);
}

//-----------------------------------------------------------------------------
// MemoryReadFile -- a File over a block of memory the caller already has.
// Named by its own constructor at 0x009CB3D0, which installs vtable 0x01143A38
// and then sets the file's name to "<MemoryReadFile>". BFME-only; Zero Hour has
// no such class.
//
// Layout, read off the overrides below: m_data at +0x14, m_size at +0x18 and
// m_pos at +0x1c -- straight after File, whose own last member is the buffer
// pointer at +0x10 that File::File zeroes and File::~File frees.
//-----------------------------------------------------------------------------
// Zero Hour's RAMFile, named at 0x01143C58 in the vtable table above. Its three
// members are Zero Hour's, in Zero Hour's order: m_data at +0x14, m_pos at
// +0x18, m_size at +0x1c, which is what the constructor zeroes.
//
// Two further checks on that vtable, since it carries no identifying literal.
// Slots 10, 15 and 16 are File's own print, lock and unlock, so this is a File
// subclass that does not override them. And the constructor chains to
// File::File at 0x009CB7A0, so it is a File subclass at all.
class RAMFile : public File
{
public:
	RAMFile();

	virtual Bool open( const char *filename, Int access = 0 );
	virtual void close( void );
	virtual Int read( void *buffer, Int bytes );
	virtual Int write( const void *buffer, Int bytes );
	virtual Int seek( Int bytes, Int mode );
	virtual void nextLine( char *buf, Int bufSize );
	virtual Bool scanInt( Int &newInt );
	virtual Bool scanReal( Real &newReal );
	virtual Bool scanString( AsciiString &newString );
	virtual Int size( void );
	virtual Int position( void );
	virtual char *readEntireAndClose( void );
	virtual File *convertToRAMFile( void );

protected:
	char *m_data;			// +0x14
	Int m_pos;				// +0x18
	Int m_size;				// +0x1c
};

// noinline stands in for a translation-unit boundary. Retail builds RAMFile and
// StreamingArchiveFile separately, so StreamingArchiveFile's constructor can
// only call this one; with both in this file MSVC inlines it instead and emits
// six zero stores where retail emits a call and three.
__declspec(noinline) RAMFile::RAMFile()
{
	m_data = NULL;
	m_pos = 0;
	m_size = 0;
}

// StreamingArchiveFile, 0x01143CA8 in the table above. It lives here rather than
// in StreamingArchiveFile.cpp for one reason: it is laid out on BFME's File, and
// that file compiles against Zero Hour's, which is four bytes shorter because it
// has no m_mutex at +0x10. Its constructor came out zeroing +0x1c through +0x28
// where retail zeroes +0x20 through +0x28 -- the whole class shifted down by the
// missing word.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StreamingArchiveFile.h
class StreamingArchiveFile : public RAMFile
{
public:
	StreamingArchiveFile();

	virtual Bool open( const char *filename, Int access = 0 );
	virtual void close( void );
	virtual Int read( void *buffer, Int bytes );
	virtual Int write( const void *buffer, Int bytes );
	virtual Int seek( Int bytes, Int mode );
	virtual void nextLine( char *buf, Int bufSize );
	virtual Bool scanInt( Int &newInt );
	virtual Bool scanReal( Real &newReal );
	virtual Bool scanString( AsciiString &newString );
	virtual Int size( void );
	virtual Int position( void );
	virtual char *readEntireAndClose( void );
	virtual File *convertToRAMFile( void );

protected:
	File *m_file;			// +0x20
	Int m_startingPos;		// +0x24
	Int m_size;				// +0x28
};

StreamingArchiveFile::StreamingArchiveFile()
{
	m_file = NULL;
	m_startingPos = 0;
	m_size = 0;
}

// LocalFile, 0x01143D38. It adds one word to File and initialises it to -1,
// which is INVALID_HANDLE_VALUE -- so this is the class that owns the OS file
// handle, and File's own +0x10 (the mutex) is not it.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/LocalFile.h
class LocalFile : public File
{
public:
	LocalFile();

	virtual Bool open( const char *filename, Int access = 0 );
	virtual void close( void );
	virtual Int read( void *buffer, Int bytes );
	virtual Int write( const void *buffer, Int bytes );
	virtual Int seek( Int bytes, Int mode );
	virtual void nextLine( char *buf, Int bufSize );
	virtual Bool scanInt( Int &newInt );
	virtual Bool scanReal( Real &newReal );
	virtual Bool scanString( AsciiString &newString );
	virtual Int size( void );
	virtual Int position( void );
	virtual char *readEntireAndClose( void );
	virtual File *convertToRAMFile( void );

protected:
	HANDLE m_handle;		// +0x14
};

// noinline for the same translation-unit reason as RAMFile::RAMFile below --
// Win32LocalFile's constructor calls this one rather than inlining it.
__declspec(noinline) LocalFile::LocalFile()
{
	m_handle = INVALID_HANDLE_VALUE;
}

// Win32LocalFile, 0x01143C10. It adds no members of its own -- the constructor
// is a base call and a vptr store, nothing else -- which is what
// Win32LocalFileSystem::openFile allocates 0x18 bytes for.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/Win32Device/Common/Win32LocalFile.h
class Win32LocalFile : public LocalFile
{
public:
	Win32LocalFile();

	virtual Bool open( const char *filename, Int access = 0 );
	virtual void close( void );
	virtual Int read( void *buffer, Int bytes );
	virtual Int write( const void *buffer, Int bytes );
	virtual Int seek( Int bytes, Int mode );
	virtual void nextLine( char *buf, Int bufSize );
	virtual Bool scanInt( Int &newInt );
	virtual Bool scanReal( Real &newReal );
	virtual Bool scanString( AsciiString &newString );
	virtual Int size( void );
	virtual Int position( void );
	virtual char *readEntireAndClose( void );
	virtual File *convertToRAMFile( void );
};

Win32LocalFile::Win32LocalFile()
{
}

class MemoryReadFile : public File
{
public:
	virtual Bool open( const char *filename, Int access = 0 );
	virtual Int read( void *buffer, Int bytes );
	virtual Int write( const void *buffer, Int bytes );
	virtual Int seek( Int bytes, Int mode );
	virtual void nextLine( char *buf, Int bufSize );
	virtual Bool scanInt( Int &newInt );
	virtual Bool scanReal( Real &newReal );
	virtual Bool scanString( AsciiString &newString );
	virtual Int size( void );
	virtual Int position( void );
	virtual char *readEntireAndClose( void );
	virtual File *convertToRAMFile( void );

public:
	MemoryReadFile( char *data, Int size );

private:
	char *m_data;			// +0x14
	Int m_size;				// +0x18
	Int m_pos;				// +0x1c
};

// ??0MemoryReadFile@@QAE@PADH@Z
// Wraps a block the caller already owns: nothing is copied, and the file reports
// itself as READ|BINARY and already open.
MemoryReadFile::MemoryReadFile( char *data, Int size )
{
	m_data = data;
	m_size = size;
	m_pos = 0;
	m_open = TRUE;
	m_access = READ | BINARY;
	setName( "<MemoryReadFile>" );
}

// ?open@MemoryReadFile@@UAE_NPBDH@Z
Bool MemoryReadFile::open( const char * /*filename*/, Int /*access*/ )
{
	return FALSE;
}

// ?read@MemoryReadFile@@UAEHPAXH@Z
// The m_pos update is deliberately OUTSIDE the if(bytes), which is what the
// earlier attempts here got wrong while chasing the edi restore. Retail's
// zero-length branch is `je 0x009CB0D4`, and 0x009CB0D4 IS the
// `add [edx+0x1c], eax` -- so a zero-byte read still runs the (zero) update
// rather than skipping it. Once the update is hoisted out, the register
// restores fall into retail's order on their own: pop esi/edi at the join of
// the buffer test, then the add, then pop ebx.
Int MemoryReadFile::read( void *buffer, Int bytes )
{
	if( bytes < 0 )
	{
		return -1;
	}

	// Unsigned compare: retail is jbe, not jle. The negative case is already
	// gone by here, so the clamp is done in UnsignedInt.
	UnsignedInt remaining = (UnsignedInt)m_size - (UnsignedInt)m_pos;
	if( (UnsignedInt)bytes > remaining )
	{
		bytes = remaining;
	}

	if( bytes )
	{
		if( buffer )
		{
			memcpy( buffer, m_data + m_pos, bytes );
		}
	}
	m_pos += bytes;

	return bytes;
}

// ?write@MemoryReadFile@@UAEHPBXH@Z
// Read-only, so writing always fails.
Int MemoryReadFile::write( const void * /*buffer*/, Int /*bytes*/ )
{
	return -1;
}

// ?seek@MemoryReadFile@@UAEHHH@Z
Int MemoryReadFile::seek( Int bytes, Int mode )
{
	Int pos;

	switch( mode )
	{
		case 0:		// START
			pos = bytes;
			break;
		case 1:		// CURRENT
			pos = m_pos + bytes;
			break;
		case 2:		// END
			pos = m_size + bytes;
			break;
		default:
			return -1;
	}

	if( (UnsignedInt)pos > (UnsignedInt)m_size )
	{
		return -1;
	}

	m_pos = pos;
	return pos;
}

// ?nextLine@MemoryReadFile@@UAEXPADH@Z
void MemoryReadFile::nextLine( char * /*buf*/, Int /*bufSize*/ )
{
}

// ?scanInt@MemoryReadFile@@UAE_NAAH@Z
Bool MemoryReadFile::scanInt( Int & /*newInt*/ )
{
	return FALSE;
}

// ?scanReal@MemoryReadFile@@UAE_NAAM@Z
Bool MemoryReadFile::scanReal( Real & /*newReal*/ )
{
	return FALSE;
}

// ?scanString@MemoryReadFile@@UAE_NAAVAsciiString@@@Z
Bool MemoryReadFile::scanString( AsciiString & /*newString*/ )
{
	return FALSE;
}

// ?size@MemoryReadFile@@UAEHXZ
Int MemoryReadFile::size( void )
{
	return m_size;
}

// ?position@MemoryReadFile@@UAEHXZ
Int MemoryReadFile::position( void )
{
	return m_pos;
}

// ?readEntireAndClose@MemoryReadFile@@UAEPADXZ
// Hands back a copy of the whole block and closes. An empty file still returns
// an allocation rather than NULL, so the caller can always delete[] the result.
char *MemoryReadFile::readEntireAndClose( void )
{
	if( m_size == 0 )
	{
		close();
		return NEW char[1];
	}

	char *buffer = NEW char[m_size];
	memcpy( buffer, m_data, m_size );
	close();
	return buffer;
}

// ?convertToRAMFile@MemoryReadFile@@UAEPAVFile@@XZ
// Already in memory, so it is its own RAM file.
File *MemoryReadFile::convertToRAMFile( void )
{
	return this;
}

//-----------------------------------------------------------------------------
// MemoryWriteFile -- a File that accumulates into a heap buffer it grows itself.
// Named by its constructor at 0x009CB4E0, which installs vtable 0x01143AA8 and
// sets the file's name to "<MemoryWriteFile>". BFME-only, like MemoryReadFile.
//
// Same three members as MemoryReadFile, plus m_capacity at +0x20: the
// buffer is realloc'd to 2*needed + 0x1000 whenever a write would run past it,
// so it grows geometrically with a 4K floor.
//-----------------------------------------------------------------------------
class MemoryWriteFile : public File
{
public:
	virtual Bool open( const char *filename, Int access = 0 );
	virtual Int read( void *buffer, Int bytes );
	virtual Int write( const void *buffer, Int bytes );
	virtual Int seek( Int bytes, Int mode );
	virtual void nextLine( char *buf, Int bufSize );
	virtual Bool scanInt( Int &newInt );
	virtual Bool scanReal( Real &newReal );
	virtual Bool scanString( AsciiString &newString );
	virtual Int size( void );
	virtual Int position( void );
	virtual char *readEntireAndClose( void );
	virtual File *convertToRAMFile( void );

public:
	MemoryWriteFile( const char *name );
	virtual ~MemoryWriteFile();

private:
	char *m_data;			// +0x14
	Int m_size;				// +0x18
	Int m_pos;				// +0x1c
	Int m_capacity;			// +0x20
	AsciiString m_pendingName;	// +0x24 -- the destructor releases it
};

// 71 of 173 bytes. Content matches -- same stores, same fallback, same 0x42 --
// but retail keeps its zero in edx, a caller-saved register it can use freely
// because nothing between the File::File call and the name test is a call. We
// put the zero in ebx, which costs a third callee-saved push, because the
// implicit m_pendingName construction lands before the body assignments in our
// schedule and after them in retail's. Same class of difference as
// friend_parseRankDefinition.
// Starts with no buffer at all; the first write allocates. Reports itself as
// WRITE|BINARY and already open. A null name falls back to the placeholder, the
// same way File's own constructor uses "<no file>".
// The first four go in the initialiser list, not the body. Members are
// initialised in declaration order and before the body runs, so retail zeroing
// m_data..m_capacity BEFORE constructing m_pendingName is only possible if they
// are initialisers -- body assignments would land after every member's
// construction, which is four stores in the wrong place.
// Retail 0x009CB590, 94 bytes. The body is one delete; everything else the 94
// bytes contain is compiler-generated and confirms the layout: the vptr store of
// 0x01143AA8 (MemoryWriteFile's vtable -- its slot 0 is ??_GMemoryWriteFile at
// 0x009CB650), then m_pendingName's releaseBuffer at this+0x24, then ~File.
MemoryWriteFile::~MemoryWriteFile()
{
	delete [] m_data;
}

MemoryWriteFile::MemoryWriteFile( const char *name )
: m_data(NULL), m_size(0), m_pos(0), m_capacity(0)
{
	m_open = TRUE;
	m_access = WRITE | BINARY;

	if( name )
	{
		setName( name );
	}
	else
	{
		setName( "<MemoryWriteFile>" );
	}
}

// ?open@MemoryWriteFile@@UAE_NPBDH@Z
Bool MemoryWriteFile::open( const char * /*filename*/, Int /*access*/ )
{
	return FALSE;
}

// ?read@MemoryWriteFile@@UAEHPAXH@Z
// Write-only, so reading always fails.
Int MemoryWriteFile::read( void * /*buffer*/, Int /*bytes*/ )
{
	return -1;
}

// ?write@MemoryWriteFile@@UAEHPBXH@Z
Int MemoryWriteFile::write( const void *buffer, Int bytes )
{
	if( bytes < 0 )
	{
		return -1;
	}

	if( bytes > 0 && buffer == NULL )
	{
		return -1;
	}

	Int needed = m_pos + bytes;
	if( (UnsignedInt)needed > (UnsignedInt)m_capacity )
	{
		m_capacity = needed * 2 + 0x1000;
		m_data = (char *)realloc( m_data, m_capacity );
	}

	memcpy( m_data + m_pos, buffer, bytes );

	m_pos += bytes;
	if( (UnsignedInt)m_pos > (UnsignedInt)m_size )
	{
		m_size = m_pos;
	}

	return bytes;
}

// ?seek@MemoryWriteFile@@UAEHHH@Z
Int MemoryWriteFile::seek( Int bytes, Int mode )
{
	Int pos;

	switch( mode )
	{
		case 0:		// START
			pos = bytes;
			break;
		case 1:		// CURRENT
			pos = m_pos + bytes;
			break;
		case 2:		// END
			pos = m_size + bytes;
			break;
		default:
			return -1;
	}

	if( (UnsignedInt)pos > (UnsignedInt)m_size )
	{
		return -1;
	}

	m_pos = pos;
	return pos;
}

// ?nextLine@MemoryWriteFile@@UAEXPADH@Z
void MemoryWriteFile::nextLine( char * /*buf*/, Int /*bufSize*/ )
{
}

// ?scanInt@MemoryWriteFile@@UAE_NAAH@Z
Bool MemoryWriteFile::scanInt( Int & /*newInt*/ )
{
	return FALSE;
}

// ?scanReal@MemoryWriteFile@@UAE_NAAM@Z
Bool MemoryWriteFile::scanReal( Real & /*newReal*/ )
{
	return FALSE;
}

// ?scanString@MemoryWriteFile@@UAE_NAAVAsciiString@@@Z
Bool MemoryWriteFile::scanString( AsciiString & /*newString*/ )
{
	return FALSE;
}

// ?size@MemoryWriteFile@@UAEHXZ
Int MemoryWriteFile::size( void )
{
	return m_size;
}

// ?position@MemoryWriteFile@@UAEHXZ
Int MemoryWriteFile::position( void )
{
	return m_pos;
}

// ?readEntireAndClose@MemoryWriteFile@@UAEPADXZ
// Nothing to hand back: this file exists to be written into.
char *MemoryWriteFile::readEntireAndClose( void )
{
	return NULL;
}

// ?convertToRAMFile@MemoryWriteFile@@UAEPAVFile@@XZ
File *MemoryWriteFile::convertToRAMFile( void )
{
	return this;
}

// ??0File@@QAE@XZ
// Zeroes everything and gives the file the placeholder name. m_access starts at
// 0, i.e. NONE.
File::File()
:	m_access(0),
	m_open(FALSE),
	m_deleteOnClose(FALSE),
	m_mutex(NULL)
{
	setName( "<no file>" );
}

// ??1File@@UAE@XZ
// The word at +0x10 is a mutex handle, not a buffer: the call retail makes on
// it is KERNEL32!CloseHandle, read out of the import table at the IAT slot
// 0x01358CCC. That also explains why no esp adjustment follows it -- CloseHandle
// is __stdcall, so the callee cleans -- which is what the "some __stdcall
// deallocator" note here used to say without knowing which.
//
// This sat at 129 of 133 for a while, and the last four bytes were instruction
// order inside the inlined close(): retail pushes the "<no file>" pointer before
// computing &m_nameStr and we computed it first. The note here blamed the
// inlining rather than setName, on the grounds that the identical call in
// File::File matched. It was setName. Writing it as a direct set() instead of
// m_nameStr = name stops the receiver being materialised at the inline site, and
// that fixed this one without disturbing the five other call sites -- 42/42.
//
// Clears m_deleteOnClose before closing, so a File that would normally delete
// itself on close does not re-enter delete while already being destroyed.
File::~File()
{
	m_deleteOnClose = FALSE;
	close();

	if( m_mutex )
	{
		CloseHandle( m_mutex );
	}
}

// ?lock@File@@UAEXXZ
// Slot 15, one of the two BFME added. The mutex is created owned, so the first
// caller acquires it by creating it and every later caller waits.
void File::lock( void )
{
	if( m_mutex == NULL )
	{
		m_mutex = CreateMutex( NULL, TRUE, NULL );
	}
	else
	{
		WaitForSingleObject( m_mutex, INFINITE );
	}
}

// ?unlock@File@@UAEXXZ
// Slot 16. A File that was never locked has no mutex, hence the test.
void File::unlock( void )
{
	if( m_mutex != NULL )
	{
		ReleaseMutex( m_mutex );
	}
}
