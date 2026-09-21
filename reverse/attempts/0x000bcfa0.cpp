// ?parseUpgradeKeyVector@Rva000BCFA0@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.67 date=2026-09-20
// cl: /DNDEBUG /MD /EHs-c- /D_STLP_NO_EXCEPTIONS
// stlport
// INI field-parser callback at retail RVA 0x000BCFA0 (154 B): resolves each
// token through NameKeyGenerator::nameToKey and UpgradeCenter::findUpgradeByKey,
// appending matches to the vector the store argument points at.  The vector's
// element type is the shared 4-byte POD family (Gen_t_000bc840_m4pod) so
// growth reuses the already-pinned _M_insert_overflow at retail 0x000BBFC0.
// Guards TheUpgradeCenter by raising the BFME ERROR_BUG code (0xdead0001,
// Common/Errors.h) through the pinned _CxxThrowException helper directly,
// the same manual-throw shape AudioEventInfoParseVolumeSliderMultiplier.cpp
// uses, so no automatic-EH frame is reserved (retail reuses the incoming
// store argument's stack slot for the thrown object).
// Address-derived parser name; owning class/method identity not otherwise
// provable from callers/vtables.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef unsigned short NameKeyType;

class INI
{
public:
	const char *getNextTokenOrNull( const char *seps = 0 );
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};
extern NameKeyGenerator *TheNameKeyGenerator;

class UpgradeCenter
{
public:
	const void *findUpgradeByKey( NameKeyType key ) const;
};
extern UpgradeCenter *TheUpgradeCenter;

extern void __declspec(noreturn) __stdcall _CxxThrowException( void *object, void *throwInfo );

struct Gen_t_000bc840_m4pod { int a[1]; };
bool operator==(const Gen_t_000bc840_m4pod&, const Gen_t_000bc840_m4pod&);
bool operator<(const Gen_t_000bc840_m4pod&, const Gen_t_000bc840_m4pod&);

class Rva000BCFA0
{
public:
	static void parseUpgradeKeyVector( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseUpgradeKeyVector@Rva000BCFA0@@SAXPAVINI@@PAX1PBX@Z
void Rva000BCFA0::parseUpgradeKeyVector( INI *ini, void *, void *store, const void * )
{
	if ( TheUpgradeCenter == 0 )
	{
		int errorCode = (int)0xdead0001;
		_CxxThrowException( &errorCode, (void *)0x011E0004 );
	}

	_STL::vector<Gen_t_000bc840_m4pod> *upgrades = (_STL::vector<Gen_t_000bc840_m4pod> *)store;

	for ( const char *token = ini->getNextTokenOrNull(); token != 0; token = ini->getNextTokenOrNull() )
	{
		const void *upgrade = TheUpgradeCenter->findUpgradeByKey( TheNameKeyGenerator->nameToKey( token ) );
		if ( upgrade != 0 )
			upgrades->push_back( *(const Gen_t_000bc840_m4pod *)&upgrade );
	}
}
