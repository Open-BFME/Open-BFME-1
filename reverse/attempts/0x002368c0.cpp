// ?parseIntSetTokens@Rva002368C0@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.96 date=2026-09-16
// cl: /DNDEBUG /MD /EHsc
// stlport
// INI field parser at 0x002368C0 (90 B). The HordeContain FieldParse table at
// 0x010AF710 stores the string RanksToReleaseWhenAttacking next to this body,
// so the field names the function; the class keeps the body address because
// retail's own class name is unproven. Every remaining token on the line is
// read with the plain separator set at INI+0x414, converted by the imported
// atoi, and inserted into the set<int> the store argument points at. STLport
// insert_unique at 0x00235A30 returns its pair through the hidden pointer.
//
// Four bytes still differ, down from fourteen. _ReadWriteBarrier keeps the
// atoi spill at +0x2C where retail put it, instead of letting MSVC sink it
// past the two address calculations. It does not fix the registers those two
// leas pick: retail writes lea eax then lea ecx, and every spelling tried
// writes lea ecx then lea edx. Tried without effect: a bare temporary, a split
// declaration and assignment, a volatile store, a pointer alias, the local
// hoisted out of the loop, a const reference bound to the call result, an
// inline helper taking const int &, a second barrier, _WriteBarrier, the store
// pointer cast at the call site, and a named pair for the insert result.

#define _STLP_NO_EXCEPTIONS 1
#include <set>

extern "C" void _ReadWriteBarrier( void );
#pragma intrinsic(_ReadWriteBarrier)

__declspec(dllimport) int __cdecl bfmeAtoi1027( char *text );

class INI
{
public:
	const char *getNextTokenOrNull( const char *seps );

	char m_unreconstructed[ 0x414 ];
	const char *m_seps;
};

class Rva002368C0
{
public:
	static void parseIntSetTokens( INI *ini, void *instance, void *store, const void *userData );
};

// ?parseIntSetTokens@Rva002368C0@@SAXPAVINI@@PAX1PBX@Z
void Rva002368C0::parseIntSetTokens( INI *ini, void *, void *store, const void * )
{
	_STL::set<int> *values = (_STL::set<int> *)store;
	for( const char *token = ini->getNextTokenOrNull( ini->m_seps ); token;
		token = ini->getNextTokenOrNull( ini->m_seps ) )
	{
		int value = bfmeAtoi1027( (char *)token );
		_ReadWriteBarrier();
		values->insert( value );
	}
}
