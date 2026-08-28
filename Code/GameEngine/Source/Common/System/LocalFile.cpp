// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: LocalFile, retail vtable 0x01143D38.
//
// File.cpp already pins this class by construction: 0x009D23E0 installs
// 0x01143D38 and stores -1 at +0x14, and a base of Win32LocalFile holding an
// invalid-handle sentinel is LocalFile, so +0x14 is the OS file handle. The
// bodies here confirm it from the other side -- every one of them passes
// [this+0x14] straight to a CRT low-level io import.
//
// The File base is spelled locally rather than included, the same way File.cpp
// spells it: only the layout matters here (m_open at +0xc is what write's
// leading `mov al,[ecx+0xc]` tests), and AsciiString stands in as a raw pointer
// because no body in this file touches the name.
//
// USE_BUFFERED_IO is off in retail: every call site here is a low-level
// _write/_lseek/_read through the IAT, not the stdio pair the Zero Hour source
// takes when that macro is defined.
//
// The vtable itself is the map for the rest of the class. Read out of the image
// at 0x01143D38, seventeen slots, against Zero Hour's file.h declaration order:
//
//   slot  0  0x009D26C0  scalar deleting destructor   (gen_small/dtors_010)
//   slot  1  0x009D2480  open                         landed here
//   slot  2  0x009D2540  close                        5-byte tail jump, see below
//   slot  3  0x009D2550  read                         landed here
//   slot  4  0x009D25A0  write                        landed here
//   slot  5  0x009D25D0  seek                         landed here
//   slot  6  0x009D2610  nextLine                     landed here
//   slot  7  0x009D2850  scanInt                      open, needs AsciiString
//   slot  8  0x009D2970  scanReal                     open, needs AsciiString
//   slot  9  0x009D26E0  scanString                   open, needs AsciiString
//   slot 10  0x009CB6C0  print                        File's, already matched
//   slot 11  0x009CB670  size                         File's, already matched
//   slot 12  0x009CB6B0  position                     File's, already matched
//   slot 13  0x009D2690  readEntireAndClose           landed here
//   slot 14  0x009D2790  convertToRAMFile             open, needs RAMFile
//   slot 15  0x009CB760  lock                         File's
//   slot 16  0x009CB790  unlock                       File's
//
// Slots 10..12 and 15..16 landing on File's own bodies is the independent check
// on the whole table: those five addresses are exactly the ones File.cpp already
// identified as File's un-overridden implementations, so the slot numbering here
// agrees with the numbering derived there from three other vtables.
//
// ~LocalFile is 0x009D2400 and LocalFile::LocalFile 0x009D23E0 (the latter
// already matched in File.cpp), which brackets the class: everything from
// 0x009D23E0 to 0x009D2A00 is one compiland.

// The CRT low-level io family, /MD, so dllimport -- retail reaches all three
// through the IAT (ds:0x135936C, ds:0x1359300, ds:0x1359320) rather than a
// direct call, which is exactly what an import stub gives.
#define NULL 0

extern "C" __declspec(dllimport) int __cdecl _write(int fd, const void *buffer, unsigned int count);
extern "C" __declspec(dllimport) long __cdecl _lseek(int fd, long offset, int origin);
extern "C" __declspec(dllimport) int __cdecl _read(int fd, void *buffer, unsigned int count);
extern "C" __declspec(dllimport) int __cdecl _close(int fd);
extern "C" __declspec(dllimport) int __cdecl _open(const char *filename, int oflag, ...);

// <fcntl.h> / <sys/stat.h>, spelled out so this TU pulls in no CRT headers.
#define _O_APPEND	0x0008
#define _O_CREAT	0x0100
#define _O_TRUNC	0x0200
#define _O_TEXT		0x4000
#define _O_BINARY	0x8000
#define _O_RDONLY	0x0000
#define _O_WRONLY	0x0001
#define _O_RDWR		0x0002
#define _S_IREAD	0x0100
#define _S_IWRITE	0x0080

// For a POD element type with no explicit `operator new[]` declaration visible,
// this MSVC 7.1 build folds `new T[n]` down to the scalar ??2 as a size-cookie-
// avoidance optimization. Retail's readEntireAndClose calls the array form
// (0x00881F70), so the declaration has to be visible here the way <new> makes
// it visible in the real project TUs.
void *operator new[](unsigned int);

class File
{
public:
	enum access
	{
		READ		= 0x0001,
		WRITE		= 0x0002,
		APPEND		= 0x0004,
		// File.cpp's copy of this enum stops at the bits File::open itself
		// tests, so it has no name for 0x8. LocalFile::open supplies it: the
		// bit that turns into _O_CREAT is CREATE, at Zero Hour's value.
		CREATE		= 0x0008,
		TRUNCATE	= 0x0010,
		TEXT		= 0x0020,
		BINARY		= 0x0040,
		STREAMING	= 0x0100,
		READWRITE	= (READ | WRITE)		// retail: and edx,3 / cmp dl,3
	};

	enum seekMode { START, CURRENT, END };

	File();
	bool eof( void );
	virtual ~File();										// slot 0
	virtual bool open( const char *filename, int access = 0 );	// slot 1
	virtual void close( void );								// slot 2
	virtual int read( void *buffer, int bytes );			// slot 3
	virtual int write( const void *buffer, int bytes );		// slot 4
	virtual int seek( int pos, seekMode mode );				// slot 5
	virtual void nextLine( char *buf, int bufSize );		// slot 6
	virtual bool scanInt( int &newInt );					// slot 7
	virtual bool scanReal( float &newReal );				// slot 8
	virtual bool scanString( void *newString );				// slot 9
	virtual bool print( const char *format, ... );			// slot 10
	virtual int size( void );								// slot 11
	virtual int position( void );							// slot 12
	virtual char *readEntireAndClose( void );				// slot 13
	virtual File *convertToRAMFile( void );					// slot 14
	virtual void lock( void );								// slot 15
	virtual void unlock( void );							// slot 16

protected:
	void *m_nameStr;		// +0x04  AsciiString, untouched here
	int m_access;			// +0x08
	bool m_open;			// +0x0c
	bool m_deleteOnClose;	// +0x0d
	void *m_mutex;			// +0x10
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/LocalFile.h
class LocalFile : public File
{
public:
	virtual ~LocalFile();
	virtual bool open( const char *filename, int access );
	virtual void close( void );
	virtual int read( void *buffer, int bytes );
	virtual int write( const void *buffer, int bytes );
	virtual int seek( int pos, seekMode mode );
	virtual void nextLine( char *buf, int bufSize );
	virtual char *readEntireAndClose( void );

protected:
	int m_handle;			// +0x14, -1 when closed
};

// The running count of open local files, retail 0x0134D064. Bumped once per
// successful _open and never read here, so only the increment is visible.
static int s_totalOpen = 0;

// ??1LocalFile@@UAE@XZ
LocalFile::~LocalFile()
{
	if( m_handle != -1 )
	{
		_close( m_handle );
		m_handle = -1;
		--s_totalOpen;
	}

	File::close();

}

// Closes the current file if it is open. Must be called once per successful
// LocalFile::open.
//
// Left unclaimed on purpose. The body is a bare tail jump to File::close, so it
// compiles to the same five bytes an incremental-link thunk does, and the
// address the vtable gives (slot 2, retail 0x009D2540) is already carried by
// ?j_009d2540@@YAXXZ in Code/gen_small/gthunks_086.cpp -- which does jump to
// File::close at 0x009CB880, so the two claims are indistinguishable by bytes.
// Repointing it would orphan that generated definition; the row is worth one
// function and the retraction is a separate commit's work.
// ?close@LocalFile@@UAEXXZ present-unmatched
void LocalFile::close( void )
{
	File::close();
}

// ?read@LocalFile@@UAEHPAXH@Z
int LocalFile::read( void *buffer, int bytes )
{
	if( !m_open )
	{
		return -1;
	}

	if (buffer == NULL)
	{
		_lseek(m_handle, bytes, 1 /* SEEK_CUR */);
		return bytes;
	}

	int ret = _read( m_handle, buffer, bytes );

	return ret;
}

// ?open@LocalFile@@UAE_NPBDH@Z
// Opens a file using the standard C open() call. Access flags are mapped to the
// appropriate open flags. Returns true if the file was opened successfully.
bool LocalFile::open( const char *filename, int access )
{
	if( !File::open( filename, access) )
	{
		return false;
	}

	/* here we translate WSYS file access to the std C equivalent */

	int flags = 0;

	if (m_access & CREATE)
	{
		flags |= _O_CREAT;
	}
	if (m_access & TRUNCATE)
	{
		flags |= _O_TRUNC;
	}
	if (m_access & APPEND)
	{
		flags |= _O_APPEND;
	}
	if (m_access & TEXT)
	{
		flags |= _O_TEXT;
	}
	if (m_access & BINARY)
	{
		flags |= _O_BINARY;
	}

	if((m_access & READWRITE )== READWRITE )
	{
		flags |= _O_RDWR;
	}
	else if(m_access & WRITE)
	{
		flags |= _O_WRONLY;
		flags |= _O_CREAT;
	}
	else
	{
		flags |= _O_RDONLY;
	}

	m_handle = _open( filename, flags , _S_IREAD | _S_IWRITE);

	if( m_handle == -1 )
	{
		goto error;
	}

	++s_totalOpen;
	if ( m_access & APPEND )
	{
		if ( seek ( 0, END ) < 0 )
		{
			goto error;
		}
	}

	return true;

error:

	close();

	return false;
}

// ?write@LocalFile@@UAEHPBXH@Z
int LocalFile::write( const void *buffer, int bytes )
{

	if( !m_open || !buffer )
	{
		return -1;
	}

	int ret = _write( m_handle, buffer, bytes );

	return ret;
}

// ?seek@LocalFile@@UAEHHW4seekMode@File@@@Z
int LocalFile::seek( int pos, seekMode mode )
{
	int lmode;

	switch( mode )
	{
		case START:
			lmode = 0;			// SEEK_SET
			break;
		case CURRENT:
			lmode = 1;			// SEEK_CUR
			break;
		case END:
			lmode = 2;			// SEEK_END
			break;
		default:
			// bad seek mode
			return -1;
	}

	int ret = _lseek( m_handle, pos, lmode );

	return ret;
}

// ?readEntireAndClose@LocalFile@@UAEPADXZ
// Allocate a buffer large enough to hold the entire file, read the entire file
// into the buffer, then close the file. The buffer is owned by the caller, who
// is responsible for freeing it (via delete[]).
//
// NEW here is the plain global array operator new (retail 0x00881F70, a direct
// rel32), not the W3D pool allocator -- so it is spelled `::new`.
char *LocalFile::readEntireAndClose( void )
{
	unsigned int fileSize = size();
	char *buffer = ::new char[fileSize];

	read(buffer, fileSize);

	close();

	return buffer;
}

// ?nextLine@LocalFile@@UAEXPADH@Z
// scans to the first character after a new-line or at EOF
void LocalFile::nextLine( char *buf, int bufSize )
{
	char c = 0;
	int val;
	int i = 0;

	// seek to the next new-line.
	do {
		if ((buf == NULL) || (i >= (bufSize-1))) {
			val = _read(m_handle, &c, 1);
		} else {
			val = _read(m_handle, buf + i, 1);
			c = buf[i];
		}
		++i;
	} while ((val != 0) && (c != '\n'));

	if (buf != NULL) {
		if (i < bufSize) {
			buf[i] = 0;
		} else {
			buf[bufSize] = 0;
		}
	}
}
