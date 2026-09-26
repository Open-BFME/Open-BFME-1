// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;

class INI;

template <typename T>
class StringBase
{
public:
	StringBase() : m_data( 0 ) {}
	StringBase( const StringBase &other );
	~StringBase() { releaseBuffer(); }

private:
	void releaseBuffer();
	void *m_data;
};

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

#pragma comment(linker, "/alternatename:?parse@?$DeathModelFlags@$09@@QAEXPAVINI@@PAVAsciiString@@@Z=?j_00033433@@YAXXZ")
#pragma comment(linker, "/alternatename:?parse@DeathStatusFlags@@QAEXVAsciiString@@@Z=?j_0001b04f@@YAXXZ")
#pragma comment(linker, "/alternatename:?initialize@DeathStatusFlags@@QAEXHHHHHH@Z=?j_00034ce8@@YAXXZ")
#pragma comment(linker, "/alternatename:?initialize@?$DeathModelFlags@$09@@QAEXHHHHHH@Z=?j_0000db0c@@YAXXZ")
#pragma comment(linker, "/alternatename:?invert@?$DeathModelFlags@$09@@QBEXPAV1@@Z=?j_000252b6@@YAXXZ")

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
	if ( !( initialization & 1 ) )
	{
		initialization |= 1;
		s_initialization = initialization;
		s_modelMask.initialize( 0, 0x8b, 0x8c, 0x8d, 0x8e, 0xa7 );
	}
	if ( !( initialization & 2 ) )
	{
		initialization |= 2;
		s_initialization = initialization;
		s_modelMask.invert( &s_inverseModelMask );
	}

	SlowDeathBehaviorModuleDataFields *self =
		(SlowDeathBehaviorModuleDataFields *)instance;
	DeathModelFlags<10> *modelFlags = &self->m_modelDeathFlags;
	AsciiString description;
	modelFlags->parse( ini, &description );
	for ( int i = 0; i < 10; ++i )
		modelFlags->m_words[i] &= s_modelMask.m_words[i];
	self->m_statusDeathFlags.parse( description );
	if ( !( s_initialization & 4 ) )
	{
		s_initialization |= 4;
		s_statusMask.initialize( 0, 0x1e, 0x1f, 0x20, 0x21, 0x22 );
	}
	self->m_statusDeathFlags &= s_statusMask;
}
