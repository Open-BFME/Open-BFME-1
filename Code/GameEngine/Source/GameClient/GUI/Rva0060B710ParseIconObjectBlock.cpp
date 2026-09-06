// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME7: ParseIconObjectBlock (retail 0x0060B710 209 B; the name is the
// exception text's own): with no INI it throws INIException(3
// "ParseIconObjectBlock::Invalid data passed in."); otherwise a 0x1C-byte icon
// object is allocated (inline constructor: zeros a 1.0f scale and three flag
// bytes) named from the next token when there is one filled through
// INI::initFromINI with the table at VA 0x01115CC0 and pushed onto the
// vector of icon objects at owner+0xC (STLport exceptions off inline
// push_back).  Field names are address-derived.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef int Int;
typedef float Real;

struct FieldParse;

class AsciiString
{
public:
	AsciiString() : m_data( 0 ) {}
	AsciiString &operator=( const char *text );

private:
	void *m_data;
};

class INIException
{
public:
	INIException( Int code, const char *msg, ... );
	INIException( const INIException &other );

private:
	Int m_code;
	const char *m_msg;
};

class INI
{
public:
	const char *getNextToken( const char *seps );
	void initFromINI( void *what, const FieldParse *parseTable );
};

struct Rva0060B710IconObject
{
	Rva0060B710IconObject()
		: m_00( 0 ), m_04( 0 ), m_0C( 0 ), m_scale( 1.0f ), m_flag14( false ), m_flag15( false ), m_flag16( false ), m_18( 0 )
	{
	}

	Int m_00;
	Int m_04;
	AsciiString m_name;
	Int m_0C;
	Real m_scale;
	bool m_flag14;
	bool m_flag15;
	bool m_flag16;
	Int m_18;
};

extern const FieldParse Rva0060B710FieldParseTable[];

struct Rva0060B710Owner
{
	char m_unreconstructed[ 0x0C ];
	_STL::vector<Rva0060B710IconObject *> m_icons;
};

// ?ParseIconObjectBlock@@YAXPAVINI@@PAX@Z
void ParseIconObjectBlock( INI *ini, void *owner )
{
	if( !ini )
		throw INIException( 3, "ParseIconObjectBlock::Invalid data passed in." );
	Rva0060B710IconObject *icon = new Rva0060B710IconObject;
	if( icon )
	{
		const char *name = ini->getNextToken( 0 );
		if( name )
			icon->m_name = name;
		ini->initFromINI( icon, Rva0060B710FieldParseTable );
		((Rva0060B710Owner *)owner)->m_icons.push_back( icon );
	}
}
