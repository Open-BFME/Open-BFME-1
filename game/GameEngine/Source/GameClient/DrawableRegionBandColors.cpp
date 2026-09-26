// cl: /DNDEBUG /MD /EHs-c- /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// Band colour tables for the drawable region bars at retail 0x00411110 and
// 0x00411270.
//
// bfmeRegionRenderB (DrawableRegionRenderA.cpp, retail 0x004129B0) calls
// bfmeColorLookup00411270 through ILT 0x00017256 with its raw fill ratio and a
// four-entry Color array, then paints one bar row per entry. The lookup is a
// five-band threshold table (0.8 / 0.6 / 0.4 / 0.2): the three solid bands
// store the packed colours of the three RGBAColorInt tables below, and the two
// transition bands lerp between neighbouring tables with t = (value - low) * 5.
//
// lerpColor00411110 is the retail body at 0x00411110. It is a TU-local static
// helper: MSVC gives it a custom register convention (from in EDI, to in ESI,
// t on the stack, caller-cleaned), which is why retail's call sites preload
// ESI/EDI with the two table entries. A scan of retail .text finds exactly
// five direct calls to it (0x00411220 x1, 0x00411270 x2, 0x00411400 x2) and no
// ILT thunk, as expected of a static function; 0x00411220 and 0x00411400 are
// sibling band lookups over further tables and belong in this TU.
//
// No owning class or source-level names are proven: the function names keep
// their retail address tokens, and the tables are named by the colour they
// hold and their retail .rdata address (VA 0x010F1270 / 0x010F12C0 /
// 0x010F1310; initialisers read from the image).

#include "basetype.h"

typedef Int Color;

static const RGBAColorInt s_redColors00CF1270[4] =
{
	{ 0xdf, 0x03, 0x20, 0xff }, { 0xff, 0xb7, 0x6c, 0xff },
	{ 0xff, 0x2a, 0x19, 0xff }, { 0xd1, 0x01, 0x0d, 0xff },
};

static const RGBAColorInt s_amberColors00CF12C0[4] =
{
	{ 0xd0, 0x90, 0x00, 0xff }, { 0xff, 0xff, 0xc5, 0xff },
	{ 0xff, 0xb2, 0x00, 0xff }, { 0xbd, 0x6f, 0x00, 0xff },
};

static const RGBAColorInt s_greenColors00CF1310[4] =
{
	{ 0x0b, 0x80, 0x08, 0xff }, { 0xff, 0xff, 0x80, 0xff },
	{ 0x4d, 0xb4, 0x03, 0xff }, { 0x04, 0x5d, 0x03, 0xff },
};

// from * (1 - t) + to * t per channel, packed as A8R8G8B8.  Each channel is
// widened to Real before the blend; retail schedules the second channel's
// sign test ahead of the first product only in that form.
static Color lerpColor00411110( const RGBAColorInt &from, const RGBAColorInt &to, Real t )
{
	Real inv = 1.0f - t;

	Real fromAlpha = from.alpha;
	Real toAlpha = to.alpha;
	UnsignedByte alpha = (UnsignedByte)(Int)( fromAlpha * inv + toAlpha * t );

	Real fromRed = from.red;
	Real toRed = to.red;
	UnsignedByte red = (UnsignedByte)(Int)( fromRed * inv + toRed * t );

	Real fromGreen = from.green;
	Real toGreen = to.green;
	UnsignedByte green = (UnsignedByte)(Int)( fromGreen * inv + toGreen * t );

	Real fromBlue = from.blue;
	Real toBlue = to.blue;
	UnsignedByte blue = (UnsignedByte)(Int)( fromBlue * inv + toBlue * t );

	return (alpha << 24) | (red << 16) | (green << 8) | blue;
}

// ?bfmeColorLookup00411270@@YAXMPAH@Z
void bfmeColorLookup00411270( Real value, Color *colors )
{
	if( value >= 0.8f )
	{
		colors[0] = 0xff0b8008;
		colors[1] = 0xffffff80;
		colors[2] = 0xff4db403;
		colors[3] = 0xff045d03;
	}
	else if( value >= 0.6f )
	{
		value = ( value - 0.6f ) * 5.0f;
		for( Int i = 0; i < 4; ++i )
			colors[i] = lerpColor00411110( s_amberColors00CF12C0[i], s_greenColors00CF1310[i], value );
	}
	else if( value >= 0.4f )
	{
		colors[0] = 0xffd09000;
		colors[1] = 0xffffffc5;
		colors[2] = 0xffffb200;
		colors[3] = 0xffbd6f00;
	}
	else if( value >= 0.2f )
	{
		value = ( value - 0.2f ) * 5.0f;
		for( Int i = 0; i < 4; ++i )
			colors[i] = lerpColor00411110( s_redColors00CF1270[i], s_amberColors00CF12C0[i], value );
	}
	else
	{
		colors[0] = 0xffdf0320;
		colors[1] = 0xffffb76c;
		colors[2] = 0xffff2a19;
		colors[3] = 0xffd1010d;
	}
}
