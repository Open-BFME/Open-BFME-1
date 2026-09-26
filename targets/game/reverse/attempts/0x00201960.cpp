// ?parseInstantDeathSounds@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.3 date=2026-09-16
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: the InstantDeathBehavior Sound INI field parser, retail
// 0x00201960, 254 bytes.
//
// The FieldParse table at 0x010A4FB8 has four rows. Row 0x010A4FE8 pairs 'Sound'
// with this body, and two of its neighbours are already converted under real
// names in InstantDeathBehaviorParsers.cpp: 'OCL' at 0x006016E0 is
// parseInstantDeathObjectCreationLists and 'Weapon' at 0x00601770 is
// parseInstantDeathWeapons. Those two append to module-data vectors at +0x40
// and +0x4C. This one appends to the vector at +0x58, so the table and the two
// landed siblings name it.
//
// The loop is the siblings' loop. For each token it builds an AsciiString,
// calls slot 0x118 on TheAudioClientUpdate, which returns a four-byte intrusive
// reference through a hidden pointer, destroys the string, and appends the
// reference to the vector. The vector's growth helper is the converted
// _M_insert_overflow at 0x000BD3B0, whose element the ledger calls
// Rva000BD3B0Element, so the reference keeps that name. The reference counts
// through InterlockedIncrement and InterlockedDecrement on the word at
// AudioEventInfo plus 4 and calls vtable slot 0 with 1 when the count reaches
// zero.

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement( long volatile *addend );
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement( long volatile *addend );

inline void *operator new( unsigned int, void *place ) { return place; }
inline void operator delete( void *, void * ) {}

template <typename T> class StringBase
{
	friend class BFMERetailAsciiString;
	StringBase( const T *text );
	void *m_data;
};

// Retail constructs the by-value argument through an inline base forwarder.
class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString( const char *text ) : StringBase<char>( text ) {}
	~BFMERetailAsciiString();
};

class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
	const char *getNextTokenOrNull( const char *seps = 0 );
};

class AudioEventInfo
{
public:
	virtual ~AudioEventInfo();

	long m_refCount;
};

struct Rva000BD3B0Element
{
	Rva000BD3B0Element() : m_held( 0 ) {}
	Rva000BD3B0Element( const Rva000BD3B0Element &other ) : m_held( other.m_held )
	{
		if( m_held )
			InterlockedIncrement( &m_held->m_refCount );
	}
	~Rva000BD3B0Element()
	{
		if( m_held && InterlockedDecrement( &m_held->m_refCount ) <= 0 )
			delete m_held;
	}

	AudioEventInfo *m_held;
};

namespace _STL
{
struct __false_type
{
};

template <class T>
class allocator
{
};

template <class T>
inline void _Construct( T *place, const T &value )
{
	new ( place ) T( value );
}

template <class T, class Alloc>
class vector
{
public:
	void push_back( const T &value )
	{
		if( _M_finish != _M_end_of_storage )
		{
			_Construct( _M_finish, value );
			++_M_finish;
		}
		else
		{
			_M_insert_overflow( _M_finish, value, __false_type(), 1, true );
		}
	}

protected:
	void _M_insert_overflow( T *position, const T &value, const __false_type &,
		unsigned int fillLength, bool atEnd );

	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};
}

class Rva0051D690Audio
{
public:
	#define BFME_AUDIO_SLOT( n ) virtual void bfmeAudioSlot##n() = 0
	BFME_AUDIO_SLOT( 0 ); BFME_AUDIO_SLOT( 1 ); BFME_AUDIO_SLOT( 2 ); BFME_AUDIO_SLOT( 3 );
	BFME_AUDIO_SLOT( 4 ); BFME_AUDIO_SLOT( 5 ); BFME_AUDIO_SLOT( 6 ); BFME_AUDIO_SLOT( 7 );
	BFME_AUDIO_SLOT( 8 ); BFME_AUDIO_SLOT( 9 ); BFME_AUDIO_SLOT( 10 ); BFME_AUDIO_SLOT( 11 );
	BFME_AUDIO_SLOT( 12 ); BFME_AUDIO_SLOT( 13 ); BFME_AUDIO_SLOT( 14 ); BFME_AUDIO_SLOT( 15 );
	BFME_AUDIO_SLOT( 16 ); BFME_AUDIO_SLOT( 17 ); BFME_AUDIO_SLOT( 18 ); BFME_AUDIO_SLOT( 19 );
	BFME_AUDIO_SLOT( 20 ); BFME_AUDIO_SLOT( 21 ); BFME_AUDIO_SLOT( 22 ); BFME_AUDIO_SLOT( 23 );
	BFME_AUDIO_SLOT( 24 ); BFME_AUDIO_SLOT( 25 ); BFME_AUDIO_SLOT( 26 ); BFME_AUDIO_SLOT( 27 );
	BFME_AUDIO_SLOT( 28 ); BFME_AUDIO_SLOT( 29 ); BFME_AUDIO_SLOT( 30 ); BFME_AUDIO_SLOT( 31 );
	BFME_AUDIO_SLOT( 32 ); BFME_AUDIO_SLOT( 33 ); BFME_AUDIO_SLOT( 34 ); BFME_AUDIO_SLOT( 35 );
	BFME_AUDIO_SLOT( 36 ); BFME_AUDIO_SLOT( 37 ); BFME_AUDIO_SLOT( 38 ); BFME_AUDIO_SLOT( 39 );
	BFME_AUDIO_SLOT( 40 ); BFME_AUDIO_SLOT( 41 ); BFME_AUDIO_SLOT( 42 ); BFME_AUDIO_SLOT( 43 );
	BFME_AUDIO_SLOT( 44 ); BFME_AUDIO_SLOT( 45 ); BFME_AUDIO_SLOT( 46 ); BFME_AUDIO_SLOT( 47 );
	BFME_AUDIO_SLOT( 48 ); BFME_AUDIO_SLOT( 49 ); BFME_AUDIO_SLOT( 50 ); BFME_AUDIO_SLOT( 51 );
	BFME_AUDIO_SLOT( 52 ); BFME_AUDIO_SLOT( 53 ); BFME_AUDIO_SLOT( 54 ); BFME_AUDIO_SLOT( 55 );
	BFME_AUDIO_SLOT( 56 ); BFME_AUDIO_SLOT( 57 ); BFME_AUDIO_SLOT( 58 ); BFME_AUDIO_SLOT( 59 );
	BFME_AUDIO_SLOT( 60 ); BFME_AUDIO_SLOT( 61 ); BFME_AUDIO_SLOT( 62 ); BFME_AUDIO_SLOT( 63 );
	BFME_AUDIO_SLOT( 64 ); BFME_AUDIO_SLOT( 65 ); BFME_AUDIO_SLOT( 66 ); BFME_AUDIO_SLOT( 67 );
	BFME_AUDIO_SLOT( 68 ); BFME_AUDIO_SLOT( 69 );
	#undef BFME_AUDIO_SLOT
	virtual Rva000BD3B0Element findAudioEventInfo( const BFMERetailAsciiString &name ) = 0;
};

extern Rva0051D690Audio *TheAudioClientUpdate;

class InstantDeathBehaviorModuleData
{
public:
	unsigned char m_unmodelled[ 0x58 ];
	_STL::vector<Rva000BD3B0Element, _STL::allocator<Rva000BD3B0Element> > m_sounds;
};

void parseInstantDeathSounds( INI *ini, void *instance, void * /*store*/, const void * /*userData*/ )
{
	InstantDeathBehaviorModuleData *self = (InstantDeathBehaviorModuleData *)instance;
	for( const char *token = ini->getNextToken(); token != 0; token = ini->getNextTokenOrNull() )
	{
		Rva000BD3B0Element info = TheAudioClientUpdate->findAudioEventInfo( BFMERetailAsciiString( token ) );
		self->m_sounds.push_back( info );
	}
}

// 259 bytes against retail's 254, with 195 differing.
//
// Two shapes are wrong. Retail allocates one frame dword for the AsciiString
// and parks the returned reference in the dead instance argument slot, while we
// allocate two dwords and never reach that slot. Retail keeps zero out of a
// register and tests with test eax,eax everywhere, while we hold zero in ebx
// and compare against it. The second costs us a fourth callee-saved register
// and rotates the whole body.
//
// These spellings changed neither: a volatile read of TheAudioClientUpdate at
// the use site, dropping the element's default constructor, hoisting the vector
// into a reference before the loop, a const temporary, writing the loop guard
// as a bare pointer test, a named AsciiString local, and casting the instance
// argument at the call site instead of into a local.
