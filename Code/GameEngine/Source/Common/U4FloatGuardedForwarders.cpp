// cl: /EHs-c-
//
// Three forwarders that only run when a float comparison fails.
//
//     fld dword ptr [<K>] / mov ecx,[esp+0x10] / fld dword ptr [ecx]
//     fucompp / fnstsw ax / test ah,0x44 / jnp OUT
//     mov [esp+0x10],ecx / jmp <NEXT>
//     OUT: ret
//
// WHAT THE BYTES SHOW.  `fucompp` + `fnstsw` + `test ah,0x44` is MSVC's float
// EQUALITY test: 0x44 masks C3 (equal) and C2 (unordered), so exactly one bit
// survives when the operands are equal OR unordered and none when they simply
// differ.  `jnp` therefore takes the EQUAL branch and `jp` the DIFFERENT one.
// 0x005F5120 jumps on equal to its own `ret`, so its source reads
// `if (x != K) next(...)`; 0x005F8AE0 stacks three of these with the first two
// jumping FORWARD to the call on `jp` and only the last falling through on
// equality, which is the short-circuit `||` of three `!=` tests, one per
// component of a three-float object.
//
// FOUR DWORDS, __cdecl, TAIL-JUMPED, and the fourth is what gets dereferenced:
// the same (INI *, void *instance, void *store, const void *userData) shape
// Code/GameEngine/Source/Common/U4IniParseIntFlagSetters.cpp reads out, and the
// same `mov [esp+0x10],ecx` write-back of a value already in that slot, which
// is the tell that the source forwards a CAST pointer rather than the parameter
// it was handed.
//
// 0x005FF120 (46 bytes) is the same test between TWO POINTED-AT FLOATS rather
// than against a constant, and it CALLS instead of jumping because it has FIVE
// stack dwords and the callee takes four -- the frames do not line up, so the
// four are re-pushed and `add esp,0x10` cleans them.  ITS CALLEE IS THE SAME
// ADDRESS 0x005F5120 JUMPS TO, which is what ties the two shapes together: one
// four-argument __cdecl function reached two ways, and the argument it is given
// in both is the pointer whose float was just tested.
//
// THE CONSTANT IS A DIR32 OPERAND copied from retail; all four of its uses in
// this file are the same address, so it is one symbol.  Nothing here shows its
// value or the object's type -- only that the object holds three floats at
// 0, 4 and 8, because that is what 0x005F8AE0 reads.
//
// IDENTITY IS NOT RECOVERED.  Every name is address-derived; the two callees
// are pinned in reverse/symbols.csv at the addresses their REL32s resolve to.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	void u4Indent( int width );
	void u4Append( const void *value );
	void u4Finish( int radix );
};
struct U4Vec3
{
	float m_x;
	float m_y;
	float m_z;
};
extern const float g_u4Sentinel;

void u4Next005F5120( INI *ini, void *instance, void *store, const void *userData );
void u4Next005F8AE0( INI *ini, void *instance, void *store, const void *userData );

extern const char g_u4Separator[];
void __cdecl u4FormatFloat( INI *ini, double value );
INI *__cdecl u4AppendVector( INI *ini, const void *value );

void u4Next005F5120( INI *ini, void *instance, void *store, const void *userData )
{
	unsigned int depth = (unsigned int)instance;
	if ( depth > 0 )
	{
		do
		{
			ini->u4Indent( 32 );
		}
		while ( --depth );
	}

	ini->u4Append( store );
	ini->u4Append( g_u4Separator );
	u4FormatFloat( ini, *(const float *)userData );
	ini->u4Finish( 10 );
}

void u4Next005F8AE0( INI *ini, void *instance, void *store, const void *userData )
{
	unsigned int depth = (unsigned int)instance;
	if ( depth > 0 )
	{
		do
		{
			ini->u4Indent( 32 );
		}
		while ( --depth );
	}

	ini->u4Append( store );
	ini->u4Append( g_u4Separator );
	INI *result = u4AppendVector( ini, userData );
	result->u4Finish( 10 );
}

void u4Guard005F5120( INI *ini, void *instance, void *store, const void *userData )
{
	const U4Vec3 *v = (const U4Vec3 *)userData;
	if ( v->m_x != g_u4Sentinel )
		u4Next005F5120( ini, instance, store, v );
}

void u4Guard005F8AE0( INI *ini, void *instance, void *store, const void *userData )
{
	const U4Vec3 *v = (const U4Vec3 *)userData;
	if ( v->m_x != g_u4Sentinel || v->m_y != g_u4Sentinel || v->m_z != g_u4Sentinel )
		u4Next005F8AE0( ini, instance, store, v );
}

void u4Guard005FF120( INI *ini, void *instance, void *store, const float *left,
                      const float *right )
{
	if ( *left != *right )
		u4Next005F5120( ini, instance, store, left );
}
