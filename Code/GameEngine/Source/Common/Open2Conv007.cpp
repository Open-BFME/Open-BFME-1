// cl: /DNDEBUG /MD /EHsc
//
// Four bodies from the 0x0078xxxx run.  Identity is not recovered for the
// classes; callee names that already have byte-verified ledger rows are
// spelled, because this file's call sites add nothing to those claims.

extern "C" __declspec(dllimport) unsigned int __stdcall bfmeTickDYA( void );
extern "C" __declspec(dllimport) char * __cdecl strchr( const char *text, int c );

// ---------------------------------------------------------------------------
// 0x00782E80 -- start and stop an accumulating stopwatch.
//
//     mov al,[esp+4] / cmp [STATE],al / je end / test al,al / mov [STATE],al
//     je stop / call [tick] / mov [START],eax / ret
//     stop: call [tick] / sub eax,[START] / add [ACCUM],eax
//
// The `test al,al` is emitted BEFORE the state store, so the branch is on the
// argument, not on what was just written; and the whole body hangs off a
// change test, which is what the leading `cmp` against the old state is.

extern unsigned char g_open2Running;
extern unsigned int g_open2Started;
extern unsigned int g_open2Accumulated;

// @?Rva00782E80@@YAXE@Z 0x00782E80
void Rva00782E80( unsigned char running )
{
	if( g_open2Running == running )
		return;

	g_open2Running = running;
	if( running )
		g_open2Started = bfmeTickDYA();
	else
		g_open2Accumulated += bfmeTickDYA() - g_open2Started;
}

// ---------------------------------------------------------------------------
// 0x00783010 -- tear the frame down, but only while the hub exists.

class Open2Hub;

extern Open2Hub *TheOpen2Hub;
extern unsigned int g_open2SyncA;
extern unsigned int g_open2SyncB;
extern int g_open2ResetA;
extern int g_open2ResetB;

class Open2Hub
{
public:
	void finish( void );
};

void bfmeResetGlobals( void );				// retail 0x009336B0

class WW3D
{
public:
	static void Sync( unsigned int frame );		// retail 0x008FD310
};

// @?Rva00783010@@YAXXZ 0x00783010
void Rva00783010( void )
{
	if( TheOpen2Hub )
	{
		TheOpen2Hub->finish();
		bfmeResetGlobals();
		g_open2ResetA = 0;
		g_open2ResetB = 0;
		WW3D::Sync( g_open2SyncA );
		WW3D::Sync( g_open2SyncB );
	}
}

// ---------------------------------------------------------------------------
// 0x00785270 and 0x00785930 -- open a file by name, retrying past each
// backslash, and hand the opened stream to the caller.
//
// 0x00785270 is entered with its argument in EAX and nothing on the stack.
// That is MSVC's private convention for a `static` whose every call site it can
// see, so the two bodies have to live in ONE translation unit; split, the
// caller pushes the argument instead and its last dozen bytes are wrong for a
// reason nothing inside the caller can fix.
//
// `str()` is inlined at both ends: `m_data ? &m_data->m_text[0] : ""`, and the
// payload sits at m_data+8, which fixes the header at four bytes of reference
// count plus two counters.

class File
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual File *slot34();
};

class FileSystem
{
public:
	File *openFile( const char *name, int access );	// retail 0x009C8860
};

extern FileSystem *TheOpen2FileSystem;

template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	void concat( const T *text, int length );	// retail 0x00887D60

	const T *str() const
	{
		return m_data ? &m_data->m_text[ 0 ] : (const T *)"";
	}

private:
	StringBase( const StringBase<T> &src );		// retail 0x00887B60
	~StringBase();					// retail 0x00887940

	struct Header
	{
		int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_text[ 1 ];
	};

	Header *m_data;
};

class AsciiString
{
public:
	AsciiString( const AsciiString &other ) : m_string( other.m_string ) {}
	~AsciiString() {}

	void concat( const char *text, int length ) { m_string.concat( text, length ); }
	const char *str() const { return m_string.str(); }

	StringBase<char> m_string;
};

// @?Open2OpenPastSeparators@@YAPAVFile@@ABVAsciiString@@@Z 0x00785270
static File *Open2OpenPastSeparators( const AsciiString &name )
{
	const char *text = name.str();

	File *file = TheOpen2FileSystem->openFile( text, 1 );
	while( file == 0 )
	{
		text = strchr( text, '\\' );
		if( text == 0 )
			return 0;
		++text;
		file = TheOpen2FileSystem->openFile( text, 1 );
	}
	return file;
}

class Rva00785930
{
public:
	void load( void );
	AsciiString m_name;
	File *m_stream;
};

// @?load@Rva00785930@@QAEXXZ 0x00785930
void Rva00785930::load( void )
{
	AsciiString path = m_name;
	path.concat( ".apt", 4 );

	File *file = Open2OpenPastSeparators( path );
	m_stream = file ? file->slot34() : 0;
}
