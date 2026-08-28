// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: six small INI parse callbacks, 16 to 62 bytes, each named by the
// keyword its FieldParse row carries.  All six have the callback signature
// `void (INI *, void *instance, void *store, const void *userData)` -- __cdecl,
// four argument slots, `ret` with no operand -- and every callee they reach is
// already a ledger row, so this file mints no pin.
//
//   0x0087DAE0  GeometryRotationAnchorOffset  table 0x00C91550
//       mov ecx,[esp+0xC] ; add ecx,8 ; mov [esp+0xC],ecx ; jmp parseCoord2D
//     A tail call that patches its own `store` argument in place: the field is
//     eight bytes into whatever `store` names, and parseCoord2D does the rest.
//
//   0x0037A960  OnlyIfEnemyThreatAbove        table 0x00CEA728
//   0x0037A920  OnlyIfEnemyThreatBelow        table 0x00CEA738
//       INI::parseUnsignedInt into a local, then two dwords written to `store`:
//       {-1, value} for Above and {1, -value} for Below.  One comparison record
//       with a direction and a threshold, and Below stores the NEGATED
//       threshold rather than a second opcode.
//
//   0x00427670  Type                          table 0x00CF336C
//       *(Int *)store = INI::scanLookupList( ini->getNextToken(), <list> ).
//       The list address is a DIR32 the gate takes from the target.
//
//   0x001B41E0  CanMoveBackwards              table 0x00C9DB70
//       atoi the token; take it when it is 1..4, otherwise fall back to
//       INI::scanBool.  A field that accepts either a small enum or yes/no.
//
//   0x001D5F40  ExtraFriction                 table 0x00C9F370
//       *(Real *)store = <global> * INI::scanReal( ini->getNextToken() ).
//
//   0x001ECDC0  PreferredAgainst              table 0x00CA17D8
//   0x001ECE00  OnlyAgainst                   table 0x00CA17E8
//       INI::scanIndexList picks a row, then BitFlags<116>::parseFromINI is
//       handed `instance + index * 24 + <base>` -- so the owner holds two
//       parallel arrays of 24-byte rows, one at 0x28 and one at 0x88, indexed by
//       the same name list.  The two bodies differ in that base and nothing
//       else.
//
// THE MULTIPLY NEEDS A NAMED LOCAL.  Written as one expression the tail is
// `fmulp` and the body is 33 bytes; retail keeps both operands on the x87 stack
// (`fld <global>` / `fmul st(1)` / `fstp [eax]` / `fstp st(0)`) and runs 37,
// which is what MSVC emits when the scanReal result is stored in a local first.
//
// IDENTITY IS NOT RECOVERED beyond the keywords: nothing here names the structs
// the arguments point at, so their fields carry the keyword or the offset.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

struct LookupListRec;

extern "C" __declspec(dllimport) int __cdecl atoi( const char * );

extern const LookupListRec TheRva00427670TypeNames[];
extern Real TheRva001D5F40Scale;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	const char *getNextToken( const char *seps = 0 );
	static Real scanReal( const char *token );
	static Bool scanBool( const char *token );
	static Int scanLookupList( const char *token, const LookupListRec *list );
	static Int scanIndexList( const char *token, const char *const *list );
	static void parseCoord2D( INI *, void *, void *, const void * );
	static void parseUnsignedInt( INI *, void *, void *, const void * );
};

void parseGeometryRotationAnchorOffset( INI *ini, void *instance, void *store, const void *userData )
{
	INI::parseCoord2D( ini, instance, (char *)store + 8, userData );
}

struct ThreatCondition
{
	Int m_compare;
	Int m_threat;
};

void parseOnlyIfEnemyThreatAbove( INI *ini, void *, void *store, const void * )
{
	UnsignedInt value;
	INI::parseUnsignedInt( ini, 0, &value, 0 );
	( (ThreatCondition *)store )->m_compare = -1;
	( (ThreatCondition *)store )->m_threat = value;
}

void parseOnlyIfEnemyThreatBelow( INI *ini, void *, void *store, const void * )
{
	UnsignedInt value;
	INI::parseUnsignedInt( ini, 0, &value, 0 );
	( (ThreatCondition *)store )->m_compare = 1;
	( (ThreatCondition *)store )->m_threat = -(Int)value;
}

void parseRva00427670Type( INI *ini, void *, void *store, const void * )
{
	*(Int *)store = INI::scanLookupList( ini->getNextToken( 0 ), TheRva00427670TypeNames );
}

void parseCanMoveBackwards( INI *ini, void *, void *store, const void * )
{
	const char *token = ini->getNextToken( 0 );
	Int value = atoi( token );
	if ( value >= 1 && value <= 4 )
		*(Int *)store = value;
	else
		*(Int *)store = INI::scanBool( token );
}

void parseExtraFriction( INI *ini, void *, void *store, const void * )
{
	Real value = INI::scanReal( ini->getNextToken( 0 ) );
	*(Real *)store = TheRva001D5F40Scale * value;
}

extern const char *const TheRva001ECDC0Names[];

template< int N > class BitFlags
{
public:
	static void parseFromINI( INI *, void *, void *, const void * );
};

void parsePreferredAgainst( INI *ini, void *instance, void *, const void * )
{
	Int index = INI::scanIndexList( ini->getNextToken( 0 ), TheRva001ECDC0Names );
	BitFlags< 116 >::parseFromINI( ini, instance,
		(char *)instance + index * 24 + 0x28, 0 );
}

void parseOnlyAgainst( INI *ini, void *instance, void *, const void * )
{
	Int index = INI::scanIndexList( ini->getNextToken( 0 ), TheRva001ECDC0Names );
	BitFlags< 116 >::parseFromINI( ini, instance,
		(char *)instance + index * 24 + 0x88, 0 );
}
