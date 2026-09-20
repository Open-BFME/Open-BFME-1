// ?bfmeColorLookup00411270@@YAXMPAI@Z
// partial score=0.06 date=2026-09-20
// ?bfmeColorLookup00411270@@YAXMPAI@Z
// cl: /DNDEBUG /MD /EHs-c-
//
// Retail 0x00411270 (320 B). Reached only through the ILT thunk
// j_00017256 called by bfmeRegionRenderB (DrawableRegionRenderA.cpp), which
// hands this helper the raw float value and a 4-entry Color output array.
// The retail body is a five-band threshold table: two bands return fixed
// four-color sets, two bands blend between two 16-byte four-channel tables
// through the retail color-blend fragment at 0x00411110 (already matched,
// Code/gen_asm/d_00411110.asm), and the middle band returns a third fixed
// set. 0x00411110 has no independent calling convention: the caller must
// preload ESI/EDI with the two 16-byte table entries and push only the
// blend factor; this is a compiler-outlined shared fragment (confirmed
// blocked independently at 0x00411220/0x00411400/0x00412c10, same file),
// not a callable C++ function signature, so the two call sites are bridged
// with a minimal (non-naked) inline-asm register setup around the retail
// call instruction; everything else here is plain C++.
//
// Address-derived name: no owning class is proven, only the caller site.

typedef int Int32;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef unsigned int Color;

extern void d_00411110(); // ?d_00411110@@YAXXZ retail 0x00411110, matched

// void ?bfmeColorLookup00411270@@YAXMPAI@Z(Real value, Color *colors)
void bfmeColorLookup00411270( Real value, Color *colors )
{
	if( value >= *(const Real *)0x01096EC0 )
	{
		colors[0] = 0xff0b8008;
		colors[1] = 0xffffff80;
		colors[2] = 0xff4db403;
		colors[3] = 0xff045d03;
		return;
	}

	if( value >= *(const Real *)0x01096CF4 )
	{
		Real t = ( value - *(const Real *)0x01096CF4 ) * ( *(const Real *)0x01075344 );
		for( Int32 i = 0; i < 0x40; i += 0x10 )
		{
			const void *a = (const void *)( 0x010F1310 + i );
			const void *b = (const void *)( 0x010F12C0 + i );
			Color result;
			__asm
			{
				push dword ptr t
				mov esi, a
				mov edi, b
				call d_00411110
				add esp, 4
				mov result, eax
			}
			colors[i >> 4] = result;
		}
		return;
	}

	if( value >= *(const Real *)0x01094A60 )
	{
		colors[0] = 0xffd09000;
		colors[1] = 0xffffffc5;
		colors[2] = 0xffffb200;
		colors[3] = 0xffbd6f00;
		return;
	}

	if( value >= *(const Real *)0x01080BBC )
	{
		Real t = ( value - *(const Real *)0x01080BBC ) * ( *(const Real *)0x01075344 );
		for( Int32 i = 0; i < 0x40; i += 0x10 )
		{
			const void *a = (const void *)( 0x010F12C0 + i );
			const void *b = (const void *)( 0x010F1270 + i );
			Color result;
			__asm
			{
				push dword ptr t
				mov esi, a
				mov edi, b
				call d_00411110
				add esp, 4
				mov result, eax
			}
			colors[i >> 4] = result;
		}
		return;
	}

	colors[0] = 0xffdf0320;
	colors[1] = 0xffffb76c;
	colors[2] = 0xffff2a19;
	colors[3] = 0xffd1010d;
}
