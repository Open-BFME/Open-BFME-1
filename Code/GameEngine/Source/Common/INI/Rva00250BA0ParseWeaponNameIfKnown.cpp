// cl: /DNDEBUG /MD /EHsc
// Open-BFME7: INI field parser at 0x00250BA0 (97 B): the token is looked up
// in the weapon store (findWeaponTemplate takes the AsciiString by value so
// the token copies straight into the argument slot; the store global at VA
// 0x012EF738) and only when a template exists the raw token is written into
// the string member at instance+8 through StringBase::set(text length) with
// the inline strlen.  The by-value parameter is spelled as a thin derived
// string class with an inline forwarding constructor: that is what puts the
// saved-esp store before the argument-slot construction as retail has it.
// Address-derived names.

extern "C" unsigned int __cdecl strlen( const char *s );
#pragma intrinsic( strlen )

class AsciiString
{
public:
	AsciiString( const char *text );
	~AsciiString() {}

private:
	void *m_data;
};

class Rva00250BA0Name : public AsciiString
{
public:
	Rva00250BA0Name( const char *text ) : AsciiString( text ) {}
};

class RetailLayoutString
{
public:
	void set( const char *s, int n );
	void set( const char *s ) { set( s, s ? (int)strlen( s ) : 0 ); }
};

class WeaponTemplate;

class WeaponStore
{
public:
	const WeaponTemplate *findWeaponTemplate( Rva00250BA0Name name ) const;
};

extern WeaponStore *TheWeaponStore;

class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
};

struct Rva00250BA0Owner
{
	char m_unreconstructed[ 8 ];
	RetailLayoutString m_weaponName;
};

class Rva00250BA0
{
public:
	static void parseWeaponNameIfKnown( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseWeaponNameIfKnown@Rva00250BA0@@SAXPAVINI@@PAX1PBX@Z
void Rva00250BA0::parseWeaponNameIfKnown( INI *ini, void *instance, void *, const void * )
{
	const char *token = ini->getNextToken();
	if( TheWeaponStore->findWeaponTemplate( token ) )
	{
		RetailLayoutString *name = &((Rva00250BA0Owner *)instance)->m_weaponName;
		int len = token ? (int)strlen( token ) : 0;
		name->set( token, len );
	}
}
