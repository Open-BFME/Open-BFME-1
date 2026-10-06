// cl: -Igame/Libraries/Source/WWVegas/WW3D2 -Igame/Libraries/Source/WWVegas/WWMath -Igame/Libraries/Source/WWVegas/WWLib -Igame/Libraries/Source/WWVegas/WWDebug -Igame/Libraries/Source/WWVegas/WWSaveLoad -Iinputs/reference/shims/sweep

// 17 seven-byte functions with one shape:
//
//     fld dword ptr [<address>] / ret
//
// WHAT THE BYTES SHOW.  A dword is loaded onto the x87 stack from a FIXED
// address and left there, which is the return convention for `float`; `this` is
// never touched and nothing is popped, so these are spelled as free functions.
//
// WHAT IS AT THE ADDRESS DECIDES THE SPELLING.  13 of them point into .rdata at
// a value the source can name -- 0.0f, 1.0f, -1.0f and FLT_MAX -- and reading
// the retail dwords is what identifies them: 00000000, 3f800000, bf800000,
// 7f7fffff.  Written as literals, MSVC 7.1 pools each into a `__real@<hex>`
// constant and emits exactly this load, so the eight bodies returning zero all
// reference one pooled symbol and the build's consistency check confirms they
// all resolve to retail's one address.  No `fldz` or `fld1` shortcut appears
// here: at these settings MSVC loads even 0.0f and 1.0f from the pool, which is
// what retail does too.
//
// Other loads use fixed data objects. Two addresses are in
// .data; two are .rdata IEEE values 7FA00000 (NaN) and 7F800000 (infinity)
// that VC7.1 cannot spell with float literals. The infinity object below
// uses an explicitly typed union and a verified static integer initializer.
// Both NaN and infinity are now defined here; the two mutable zero cells
// below preserve their independent .data addresses.
//
// 0x0113BD7C is not an anonymous global: it is retail's
// RenderObjClass::AT_MIN_LOD (FLT_MAX, defined in rendobj.cpp), and
// 0x0113BD80 is AT_MAX_LOD (-1.0f) beside it, but only 0x0113BD7C was in this
// job's original name list; the -1 getters now use the canonical member too.
//
// IDENTITY IS NOT RECOVERED.  Every other name is derived from an address.

#include "rendobj.h"

// Retail VA 0x0109B46C, binary32 1.5f. Keep its definition separate from
// BfmeConv2211.cpp so VC7.1 preserves that consumer's x87 fadd.
extern const float g_0109B46C = 1.5f;

// The adjacent retail NaN retains its exact payload bits. Like infinity,
// this union float-member read relies on the verified VC7.1 behavior.
union Rva0112E8ACValue
{
    unsigned int bits;
    float value;
};
extern const Rva0112E8ACValue g_Va0112E8AC = { 0x7FA00000u };
// Retail VA 0x0112E8B0 is the IEEE binary32 +infinity bits 0x7F800000.
// VC7.1 cannot spell this float with a literal. Its supported union-punning
// behavior lets consumers load the float view of a statically initialized
// four-byte object; both TUs declare the same object type, with no alias.
union Rva0112E8B0Value
{
    unsigned int bits;
    float value;
};
extern const Rva0112E8B0Value g_Va0112E8B0 = { 0x7F800000u };
// Mutable retail .data cells; each corresponding getter loads one dword.
float g_Va01307200 = 0.0f;
float g_Va01340574 = 0.0f;

float Rva000B4A70GetFloat( void )
{
	return g_Va0112E8AC.value;
}

float Rva0020DB40GetFloat( void )
{
	return 0.0f;
}

float Rva0020DB50GetFloat( void )
{
	return 0.0f;
}

float Rva0020DC40GetFloat( void )
{
	return 0.0f;
}

float Rva00213CB0GetFloat( void )
{
	return 0.0f;
}

float Rva00213CC0GetFloat( void )
{
	return 0.0f;
}

float Rva00213D50GetFloat( void )
{
	return 0.0f;
}

float Rva00219540GetFloat( void )
{
	return 1.0f;
}

float Rva0045BCC0GetFloat( void )
{
	return 0.0f;
}

float Rva0045C070GetFloat( void )
{
	return 1.0f;
}

float Rva00694C80GetFloat( void )
{
	return g_Va0112E8B0.value;
}

float Rva006CF590GetFloat( void )
{
	return RenderObjClass::AT_MIN_LOD;
}

float Rva006CF5A0GetFloat( void )
{
	return RenderObjClass::AT_MAX_LOD;
}

float Rva006DAB40GetFloat( void )
{
	return g_Va01340574;
}

float Rva00750170GetFloat( void )
{
	return 0.0f;
}

float Rva007CC3C0GetFloat( void )
{
	return g_Va01307200;
}

float Rva009558E0GetFloat( void )
{
	return RenderObjClass::AT_MAX_LOD;
}
