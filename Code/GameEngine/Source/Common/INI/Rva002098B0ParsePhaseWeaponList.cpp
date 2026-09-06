// cl: /DNDEBUG /MD /EHsc
// stlport
// Open-BFME7: INI field parser at 0x002098B0 (167 B).  The first token picks
// a phase through INI::scanIndexList against the INITIAL / MIDPOINT / FINAL /
// HIT_GROUND name table at VA 0x012AE110; every following token is resolved
// through TheWeaponStore (findWeaponTemplate takes the string by value: spelled
// as a thin derived class with an inline forwarding constructor so the
// saved-esp store precedes the argument-slot construction)
// and pushed onto the phase's vector of weapon template pointers (twelve-byte
// vectors from instance+0xB8) and a found template sets bit 2 of the flag
// byte at instance+0x1A4.  STLport exceptions off for the inline push_back.
// Address-derived names.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef int Int;

class AsciiString
{
public:
	AsciiString( const char *text );
	~AsciiString() {}

private:
	void *m_data;
};

class Rva002098B0Name : public AsciiString
{
public:
	Rva002098B0Name( const char *text ) : AsciiString( text ) {}
};

class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
	const char *getNextTokenOrNull( const char *seps = 0 );
	static Int scanIndexList( const char *token, const char *const *nameList );
};

class WeaponTemplate;

class WeaponStore
{
public:
	const WeaponTemplate *findWeaponTemplate( Rva002098B0Name name ) const;
};

extern WeaponStore *TheWeaponStore;
extern const char *const Rva002098B0PhaseNames[];

struct Rva002098B0Owner
{
	char m_unreconstructed00[ 0xB8 ];
	_STL::vector<const WeaponTemplate *> m_phaseWeapons[ 4 ];
	char m_unreconstructedE8[ 0x1A4 - 0xE8 ];
	unsigned char m_flags;
};

class Rva002098B0
{
public:
	static void parsePhaseWeaponList( INI *ini, void *instance, void *store, const void *userData );
};

// ?parsePhaseWeaponList@Rva002098B0@@SAXPAVINI@@PAX1PBX@Z
void Rva002098B0::parsePhaseWeaponList( INI *ini, void *instance, void *, const void * )
{
	Rva002098B0Owner *self = (Rva002098B0Owner *)instance;
	Int phase = INI::scanIndexList( ini->getNextToken(), Rva002098B0PhaseNames );
	const char *token = ini->getNextToken();
	if( token )
	{
		_STL::vector<const WeaponTemplate *> &weapons = self->m_phaseWeapons[ phase ];
		do
		{
			const WeaponTemplate *weapon = TheWeaponStore->findWeaponTemplate( token );
			weapons.push_back( weapon );
			if( weapon )
				self->m_flags |= 4;
			token = ini->getNextTokenOrNull();
		} while( token );
	}
}
