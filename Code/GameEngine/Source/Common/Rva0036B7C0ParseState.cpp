// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX /D_STLP_USE_STATIC_LIB
// stlport

#include <vector>

struct FieldParse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString( const char *text );
	~AsciiString();
	AsciiString &operator=( const AsciiString &other )
	{
		set( other );
		return *this;
	}
	void set( const AsciiString &other );

	const char *str() const
	{
		return m_data ? m_data + 8 : "";
	}

private:
	const char *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken( const char *separators = 0 );
	void initFromINI( void *object, const FieldParse *fields );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	int nameToKey( const char *name );
};

extern NameKeyGenerator *TheNameKeyGenerator;

class Rva00369860State
{
public:
	Rva00369860State();
	static const FieldParse *getFieldParse();

	char m_unreconstructed00[ 0x10 ];
	AsciiString m_name;
	int m_nameKey;
	char m_unreconstructed18[ 0x78 ];
};

class Rva00369860StatePointer
{
public:
	Rva00369860StatePointer( Rva00369860State *state ) : m_state( state ) {}

private:
	Rva00369860State *m_state;
};

class Rva00369860Registry
{
public:
	char m_unreconstructed00[ 8 ];
	std::vector<Rva00369860StatePointer> m_states;
};

extern Rva00369860Registry *TheRva00369860Registry;

void parseRva00369860State( INI *ini )
{
	register Rva00369860State *state = new Rva00369860State;
	const FieldParse *fields = Rva00369860State::getFieldParse();
	const char *name = ini->getNextToken( 0 );

	{
		AsciiString stateName( name );
		state->m_name = stateName;
	}
	{
		AsciiString nameForKey( name );
		state->m_nameKey = TheNameKeyGenerator->nameToKey( nameForKey.str() );
	}

	ini->initFromINI( state, fields );
	TheRva00369860Registry->m_states.push_back( state );
}
