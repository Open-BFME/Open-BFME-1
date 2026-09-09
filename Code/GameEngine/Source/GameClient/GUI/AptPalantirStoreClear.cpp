// cl: /O2 /Oy /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB

template <class Type> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const Type *text );
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
	void format( AsciiString format, ... );
};

class WindowManager
{
public:
	void _bfme_removeNamedAptGadget( const AsciiString &name );
};

extern WindowManager *g_theWindowManager;
extern void bfmeGoDZFc( int value );

static void clearValue( int value )
{
	bfmeGoDZFc( value );
	if ( g_theWindowManager != 0 )
	{
		AsciiString name;
		name.format( AsciiString( "RegionUI/Portrait%d/Portrait" ), value );
		g_theWindowManager->_bfme_removeNamedAptGadget( name );
	}
}

static void forceClearValue( int value )
{
	clearValue( value );
}

void ( *s_forceClearValue )( int ) = forceClearValue;
