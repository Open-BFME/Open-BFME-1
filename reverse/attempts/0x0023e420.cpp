// ?parseHordeContainSplitResult@@YAXPAVINI@@PAX1PBX@Z
// partial score=0.9 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc /Oi
// Open-BFME5: the HordeContain INI field parser for a split-result entry,
// retail 0x0023E420.
//
// The line is `SplitResult <name> UnitType <name> [RankNumber <n>]`, and each
// keyword is checked with the /Oi inline strcmp -- `repe cmpsb` over the literal
// plus its terminator, so the counts 12, 9 and 11 in the bytes are the three
// keyword lengths. The first two keywords are required and each missing one
// throws the variadic INIException with code 3; retail's two messages name
// 'Target' and 'Result' rather than the keywords they guard, which is EA's
// wording, not a misreading of the bytes.
//
// The rank is optional: a third token that is not `RankNumber` leaves the field
// zero and still stores the entry, so the else arm is a store of zero and not an
// early return -- both arms fall into the same push_back.
//
// The entry is twelve bytes and is allocated with `new`; only the two strings
// are constructed (the two zero stores), the rank is written on every path. The
// pointer -- not the entry -- is what goes into the vector that the field-parse
// row hands over as `store`, retail's shared four-byte-pod push_back at
// 0x0023DA60, so the argument is the address of the local.

typedef int Int;

extern "C" int __cdecl strcmp( const char *a, const char *b );
extern "C" __declspec(dllimport) int __cdecl atoi( const char * );

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString( void ) { m_data = 0; }
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

	char m_unreconstructed_000[ 0x41c ];
	const char *m_sepsColon;
};

// the shared four-byte-pod vector instantiation, retail push_back at 0x0023DA60
class HordeContainSplitEntry;

struct Gen_t_0023da60_p4pod
{
	HordeContainSplitEntry *m_entry;
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

class HordeContainSplitEntry
{
public:
	AsciiString m_splitResult;							///< retail this+0x00
	AsciiString m_unitType;								///< retail this+0x04
	Int m_rankNumber;									///< retail this+0x08
};

void parseHordeContainSplitResult( INI *ini, void *instance, void *store, const void *userData )
{
	HordeContainSplitEntry *entry = new HordeContainSplitEntry;

	Gen_t_0023da60_p4pod slot;
	slot.m_entry = entry;

	const char *token = ini->getNextTokenOrNull( ini->getSepsColon() );
	if ( token == 0 || strcmp( token, "SplitResult" ) != 0 )
		throw INIException( 3, "'Target' expected" );

	entry->m_splitResult.set( ini->getNextToken( ini->getSepsColon() ) );

	token = ini->getNextTokenOrNull( ini->getSepsColon() );
	if ( token == 0 || strcmp( token, "UnitType" ) != 0 )
		throw INIException( 3, "'Result' expected" );

	entry->m_unitType.set( ini->getNextToken( ini->getSepsColon() ) );

	token = ini->getNextTokenOrNull( ini->getSepsColon() );
	if ( token != 0 && strcmp( token, "RankNumber" ) == 0 )
		entry->m_rankNumber = atoi( ini->getNextToken( ini->getSepsColon() ) );
	else
		entry->m_rankNumber = 0;

	( (_STL::vector<Gen_t_0023da60_p4pod> *)store )->push_back( slot );
}
