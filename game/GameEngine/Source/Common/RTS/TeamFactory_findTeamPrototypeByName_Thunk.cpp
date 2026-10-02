// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// ScriptConditions::evaluateHasUnits names this lookup through ILT 0x0002AB9E.
// The matched two-argument overload receives the split owner and local name.

#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"

static __forceinline void releaseAsciiBuffer( void *self )
{
// BfmeWordEL is the same one-pointer string view as AsciiString.  Its
// constructor and cleanup use the real string operations without pretending
// that the local view is an AsciiString base class.
reinterpret_cast<AsciiString *>( self )->~AsciiString();
}

class BfmeWordEL
{
public:
	BfmeWordEL( const BfmeWordEL &other )
	{
		reinterpret_cast<AsciiString *>( this )->AsciiString::AsciiString(
			*reinterpret_cast<const AsciiString *>( &other ) );
	}
	~BfmeWordEL() { releaseAsciiBuffer( this ); }

private:
	void *m_data;
};

struct BfmePairEL
{
	BfmeWordEL first;
	BfmeWordEL second;
};

BfmePairEL __cdecl Rva00194810( const BfmeWordEL &name );

static __forceinline void assignPair(AsciiString &localName,
	AsciiString &ownerName, const BfmePairEL &split)
{
	localName = *reinterpret_cast<const AsciiString *>( &split.first );
	ownerName = *reinterpret_cast<const AsciiString *>( &split.second );
}

class TeamPrototype;

class TeamFactory
{
public:
	TeamPrototype *findTeamPrototype( const AsciiString &name );
	TeamPrototype *findTeamPrototype( const AsciiString &name,
		const AsciiString &owner );
};

// ?findTeamPrototype@TeamFactory@@QAEPAVTeamPrototype@@ABVAsciiString@@@Z
TeamPrototype *TeamFactory::findTeamPrototype( const AsciiString &name )
{
	AsciiString localName;
	AsciiString ownerName;
	assignPair(localName, ownerName, Rva00194810(
		*reinterpret_cast<const BfmeWordEL *>( &name ) ));
	return findTeamPrototype( localName, ownerName );
}
