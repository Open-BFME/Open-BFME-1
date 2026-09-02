// ?parseHordeContainUnitTypePos@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.75 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc /Oi
// Open-BFME5: the HordeContain INI field parser that reads one horde slot,
// retail 0x0023E280.
//
// The line it accepts is `UnitType <name> Pos: <x> <y>`, and both keywords are
// checked with the /Oi inline strcmp -- `repe cmpsb` over the literal plus its
// terminator, so the lengths 9 and 4 in the bytes are "UnitType" and "Pos".
// Either keyword missing throws the usual variadic INIException with code 3.
//
// The slot itself is twelve bytes: an AsciiString for the unit type and the two
// reals of the position. It is allocated with `new` and the pointer -- not the
// slot -- is what goes into the vector the field-parse row hands over as
// `store`, which is why the push_back argument is the address of the local. That
// vector is retail's shared four-byte-pod instantiation at 0x0023DAA0.
//
// parseCoord2D writes a Coord2D temporary and the two words are copied out of it
// individually; retail never lets the parser write into the slot directly.

typedef int Int;
typedef float Real;

extern "C" int __cdecl strcmp( const char *a, const char *b );

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord2D
{
	Real x;
	Real y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString( const char *s );					///< retail 0x00888BC0
	void set( const char *s );						///< ILT thunk at 0x00028BB9

private:
	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INIException.h
class INIException
{
public:
	INIException( Int code, const char *msg, ... );	///< direct call to 0x00850600
	INIException( const INIException &other );

private:
	Int m_code;
	const char *m_msg;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken( const char *seps );			///< ILT thunk at 0x00850970
	const char *getNextTokenOrNull( const char *seps );		///< ILT thunk at 0x008509C0
	const char *getSepsColon( void ) const { return m_sepsColon; }
	static void parseCoord2D( INI *ini, void *instance, void *store, const void *userData );

	char m_unreconstructed_000[ 0x41c ];
	const char *m_sepsColon;
};

// the shared four-byte-pod vector instantiation, retail push_back at 0x0023DAA0
struct Gen_t_0023daa0_p4pod
{
	int a[ 1 ];
};

namespace _STL
{
template <class Type>
class allocator
{
};

template <class Type, class Alloc = allocator<Type> >
class vector
{
public:
	void push_back( const Type &value );

	Type *m_start;
	Type *m_finish;
	Type *m_endOfStorage;
};
}

class HordeContainUnitSlot
{
public:
	HordeContainUnitSlot( void ) : m_unitType( "" ), m_pos()
	{
	}

	AsciiString m_unitType;								///< retail this+0x00
	Coord2D m_pos;										///< retail this+0x04
};

void parseHordeContainUnitTypePos( INI *ini, void *instance, void *store, const void *userData )
{
	HordeContainUnitSlot *slot = new HordeContainUnitSlot;

	const char *token = ini->getNextTokenOrNull( ini->getSepsColon() );
	if ( token == 0 || strcmp( token, "UnitType" ) != 0 )
		throw INIException( 3, "UnitType expected" );

	slot->m_unitType.set( ini->getNextToken( ini->getSepsColon() ) );

	token = ini->getNextTokenOrNull( ini->getSepsColon() );
	if ( token == 0 || strcmp( token, "Pos" ) != 0 )
		throw INIException( 3, "'Pos' expected" );

	{
		Coord2D pos;
		INI::parseCoord2D( ini, 0, &pos, 0 );
		slot->m_pos = pos;
	}

	( (_STL::vector<Gen_t_0023daa0_p4pod> *)store )->push_back(
		*(const Gen_t_0023daa0_p4pod *)&slot );
}
