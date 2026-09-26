// cl: /DNDEBUG /MD /EHsc /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib
//
// BFME splits the slash-qualified team name before the pair-keyed prototype
// lookup.  The split prefix follows the independently matched one-name
// TeamFactory lookup at 0x000F2320; the remaining lookup and inactive-team
// fallback use the witnessed TeamPrototype offsets and routed callees.

#include "ascii_string.h"

static __forceinline void releaseAsciiBuffer( void *self )
{
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

	~BfmeWordEL()
	{
		releaseAsciiBuffer( this );
	}

private:
	void *m_data;
};

class Rva000F8290String
{
public:
	Rva000F8290String() : m_data( 0 ) {}

	~Rva000F8290String()
	{
		releaseAsciiBuffer( this );
	}

	__forceinline Rva000F8290String &operator=( const BfmeWordEL &other )
	{
		reinterpret_cast<AsciiString *>( this )->set(
			*reinterpret_cast<const AsciiString *>( &other ) );
		return *this;
	}

private:
	void *m_data;
};

struct BfmePairEL
	{
	BfmeWordEL first;
	BfmeWordEL second;
	};

BfmePairEL __cdecl Rva00194810( const BfmeWordEL &name );

static __forceinline void assignPair( Rva000F8290String &localName,
	Rva000F8290String &ownerName, const BfmePairEL &split )
	{
	localName = split.first;
	ownerName = split.second;
	}

class Team;

class TeamPrototype
{
public:
	__forceinline Team *getFirstItemIn_TeamInstanceList() const
	{
		return m_firstTeam;
	}

	__forceinline bool getIsSingleton() const
	{
		return (*(const unsigned char *)&m_flags & 1) != 0;
	}

private:
	unsigned char m_prefix[0x18];
	unsigned int m_flags;
	unsigned char m_body[0x274 - 0x1c];
	Team *m_firstTeam;
};

class TeamFactory
{
public:
	TeamPrototype *findTeamPrototype( const AsciiString &name,
		const AsciiString &ownerName );
	Team *createInactiveTeam( const AsciiString &name,
		const AsciiString &ownerName );
	Team *findTeam( const AsciiString &name );
};

// ?findTeam@TeamFactory@@QAEPAVTeam@@ABVAsciiString@@@Z
Team *TeamFactory::findTeam( const AsciiString &name )
{
	Rva000F8290String localName;
	Rva000F8290String ownerName;
	assignPair( localName, ownerName, Rva00194810(
		*reinterpret_cast<const BfmeWordEL *>( &name ) ) );

	TeamPrototype *tp = findTeamPrototype(
		*reinterpret_cast<const AsciiString *>( &localName ),
		*reinterpret_cast<const AsciiString *>( &ownerName ) );
	Team *team;
	Team *t;
	if ( tp )
	{
		t = tp->getFirstItemIn_TeamInstanceList();
		if ( t == 0 && !tp->getIsSingleton() )
			t = createInactiveTeam(
				*reinterpret_cast<const AsciiString *>( &localName ),
				*reinterpret_cast<const AsciiString *>( &ownerName ) );
		team = t;
	}
	else
		team = 0;
	return team;
}
