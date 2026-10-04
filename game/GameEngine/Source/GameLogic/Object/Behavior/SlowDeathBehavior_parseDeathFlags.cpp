// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

typedef bool Bool;

class INI;

#include "string_base.h"

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

template <int WORDS>
class DeathModelFlags
{
public:
	void initialize( int init, int bit1, int bit2, int bit3, int bit4, int bit5 );
	void parse( INI *ini, AsciiString *description );
	void invert( DeathModelFlags *result ) const;

	unsigned int m_words[WORDS];
};

class DeathStatusFlags
{
public:
	void initialize( int init, int bit1, int bit2, int bit3, int bit4, int bit5 );
	void parse( AsciiString description );
	void operator&=( const DeathStatusFlags &other )
	{
		m_words[0] &= other.m_words[0];
		m_words[1] &= other.m_words[1];
		m_words[2] &= other.m_words[2];
	}

	unsigned int m_words[3];
};

// Retail reaches these bodies through incremental-link thunks; call the thunks
// directly so no linker alias pragma is needed.
extern void j_00033433();	// DeathModelFlags<9>::parse
extern void j_0001b04f();	// DeathStatusFlags::parse
extern void j_00034ce8();	// DeathStatusFlags::initialize
extern void j_0000db0c();	// DeathModelFlags<9>::initialize
extern void j_000252b6();	// DeathModelFlags<9>::invert

struct SlowDeathBehaviorModuleDataFields
{
	unsigned char m_beforeDeathFlags[0x128];
	DeathModelFlags<10> m_modelDeathFlags;
	DeathStatusFlags m_statusDeathFlags;
};

static DeathModelFlags<10> s_modelMask;
static DeathModelFlags<10> s_inverseModelMask;
static DeathStatusFlags s_statusMask;
static unsigned int s_initialization;

void parseDeathFlags( INI *ini, void *instance, void *, void * )
{
	unsigned int initialization = s_initialization;
	typedef void (DeathModelFlags<10>::*ModelInit)( int, int, int, int, int, int );
	typedef void (DeathModelFlags<10>::*ModelInvert)( DeathModelFlags<10> * ) const;
	if ( !( initialization & 1 ) )
	{
		union { void (*fn)(); ModelInit call; } modelInit = { j_0000db0c };
		initialization |= 1;
		s_initialization = initialization;
		( s_modelMask.*modelInit.call )( 0, 0x8b, 0x8c, 0x8d, 0x8e, 0xa7 );
	}
	if ( !( initialization & 2 ) )
	{
		union { void (*fn)(); ModelInvert call; } modelInvert = { j_000252b6 };
		initialization |= 2;
		s_initialization = initialization;
		( s_modelMask.*modelInvert.call )( &s_inverseModelMask );
	}

	SlowDeathBehaviorModuleDataFields *self =
		(SlowDeathBehaviorModuleDataFields *)instance;
	DeathModelFlags<10> *modelFlags = &self->m_modelDeathFlags;
	AsciiString description;
	{
		typedef void (DeathModelFlags<10>::*ModelParse)( INI *, AsciiString * );
		union { void (*fn)(); ModelParse call; } modelParse = { j_00033433 };
		( modelFlags->*modelParse.call )( ini, &description );
	}
	for ( int i = 0; i < 10; ++i )
		modelFlags->m_words[i] &= s_modelMask.m_words[i];
	{
		typedef void (DeathStatusFlags::*StatusParse)( AsciiString );
		union { void (*fn)(); StatusParse call; } statusParse = { j_0001b04f };
		( self->m_statusDeathFlags.*statusParse.call )( description );
	}
	if ( !( s_initialization & 4 ) )
	{
		typedef void (DeathStatusFlags::*StatusInit)( int, int, int, int, int, int );
		union { void (*fn)(); StatusInit call; } statusInit = { j_00034ce8 };
		s_initialization |= 4;
		( s_statusMask.*statusInit.call )( 0, 0x1e, 0x1f, 0x20, 0x21, 0x22 );
	}
	self->m_statusDeathFlags &= s_statusMask;
}
