// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
// Retail 0x00572A60: reverse a numbered key and localize its separators.

struct StringHeader
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	char data[ 1 ];
};

template <typename T>
class StringBase
{
public:
	StringBase() : m_data( 0 ) {}
	StringBase( const StringBase<T> &other );
	~StringBase() { releaseBuffer(); }

	void set( const StringBase<T> &other );
	void set( const T *text, int length );
	void set( T value )
	{
		set( &value, 1 );
	}
	void concat( const T *text, int length );

	StringHeader *m_data;

private:
	void releaseBuffer();
};

extern const char Rva006A16B0Empty[];

class AsciiStringAI : public StringBase<char>
{
public:
	AsciiStringAI() : StringBase<char>() {}
	AsciiStringAI( const AsciiStringAI &other ) : StringBase<char>( other ) {}
	~AsciiStringAI() {}

	void set( const AsciiStringAI &other )
	{
		StringBase<char>::set( other );
	}

	void set( const char *text, int length )
	{
		StringBase<char>::set( text, length );
	}

	void set( char value )
	{
		StringBase<char>::set( value );
	}

	void concat( const char *text, int length )
	{
		StringBase<char>::concat( text, length );
	}

	void concat( const AsciiStringAI &other )
	{
		StringBase<char>::concat( other.str(), other.getLength() );
	}

	int getLength() const
	{
		return m_data ? m_data->length : 0;
	}

	char getCharAt( int index ) const
	{
		return m_data ? m_data->data[ index ] : 0;
	}

	const char *str() const
	{
		return m_data ? m_data->data : Rva006A16B0Empty;
	}
};

// View of the language object this TU reads the digit separator from.  The
// global itself is retail's TheGlobalLanguageData, a GlobalLanguage*
// (0x012F1484); that class is declared by
// Common/System/game_engine_subsystems.h, so this is only the layout of the
// one member read here, reached through a cast.
class GlobalLanguageAI
{
private:
	char m_subsystem[ 8 ];

public:
	AsciiStringAI m_period;
	AsciiStringAI m_comma;
};

class GlobalLanguage;
extern GlobalLanguage *TheGlobalLanguageData;

class BfmeTableAI
{
public:
	AsciiStringAI bfmeLookupAI( AsciiStringAI key );
};

// ?bfmeLookupAI@BfmeTableAI@@QAE?AVAsciiStringAI@@V2@@Z
AsciiStringAI BfmeTableAI::bfmeLookupAI( AsciiStringAI key )
{
	AsciiStringAI result;
	AsciiStringAI digit;
	char value;
	bool numeric = true;

	for( int index = 0; index < key.getLength(); ++index )
	{
		value = key.getCharAt( key.getLength() - index - 1 );
		if( value < '0' || value > '9' )
			numeric = false;

		digit.set( value );
		if( index % 3 == 0 && index != 0 && numeric )
		digit.concat( reinterpret_cast<GlobalLanguageAI *>( TheGlobalLanguageData )->m_comma );
		digit.concat( result.str(), result.getLength() );
		result.set( digit );
	}

	return result;
}
