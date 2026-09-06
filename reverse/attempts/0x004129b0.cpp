// ?bfmeRegionRenderB@@YAXPAXHH@Z
// partial score=0.98 date=2026-09-06
// cl: /DNDEBUG /MD /EHs-c-
// Drawable region-rendering callback at retail 0x004129B0.
//
// Drawable::bfmeRegionDispatch calls this callback through the retail ILT.
// This is a local raw-bit view of two four-byte retail argument slots.
// The first carries an offset pointer; the second is interpreted as float.
// The original source-level argument types have not been recovered.

typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;
typedef unsigned int Color;

struct Rva004129B0Region
{
	Int left;
	Int top;
	Int right;
};

struct Rva004129B0Offset
{
	Int x;
	Int y;
};

#define BFME_REGION_DISPLAY_SLOT(n) virtual void slot##n();

// BFME's Display adds three virtuals before the attributes and uses Real
// coordinates for its 2D rectangle calls.  Slots 0xBC and 0xC0 are the
// matched drawOpenRect and drawFillRect entries used by the retail body.
class Display
{
public:
	BFME_REGION_DISPLAY_SLOT(00) BFME_REGION_DISPLAY_SLOT(01)
	BFME_REGION_DISPLAY_SLOT(02) BFME_REGION_DISPLAY_SLOT(03)
	BFME_REGION_DISPLAY_SLOT(04) BFME_REGION_DISPLAY_SLOT(05)
	BFME_REGION_DISPLAY_SLOT(06) BFME_REGION_DISPLAY_SLOT(07)
	BFME_REGION_DISPLAY_SLOT(08) BFME_REGION_DISPLAY_SLOT(09)
	BFME_REGION_DISPLAY_SLOT(10) BFME_REGION_DISPLAY_SLOT(11)
	BFME_REGION_DISPLAY_SLOT(12) BFME_REGION_DISPLAY_SLOT(13)
	BFME_REGION_DISPLAY_SLOT(14) BFME_REGION_DISPLAY_SLOT(15)
	BFME_REGION_DISPLAY_SLOT(16) BFME_REGION_DISPLAY_SLOT(17)
	BFME_REGION_DISPLAY_SLOT(18) BFME_REGION_DISPLAY_SLOT(19)
	BFME_REGION_DISPLAY_SLOT(20) BFME_REGION_DISPLAY_SLOT(21)
	BFME_REGION_DISPLAY_SLOT(22) BFME_REGION_DISPLAY_SLOT(23)
	BFME_REGION_DISPLAY_SLOT(24) BFME_REGION_DISPLAY_SLOT(25)
	BFME_REGION_DISPLAY_SLOT(26) BFME_REGION_DISPLAY_SLOT(27)
	BFME_REGION_DISPLAY_SLOT(28) BFME_REGION_DISPLAY_SLOT(29)
	BFME_REGION_DISPLAY_SLOT(30) BFME_REGION_DISPLAY_SLOT(31)
	BFME_REGION_DISPLAY_SLOT(32) BFME_REGION_DISPLAY_SLOT(33)
	BFME_REGION_DISPLAY_SLOT(34) BFME_REGION_DISPLAY_SLOT(35)
	BFME_REGION_DISPLAY_SLOT(36) BFME_REGION_DISPLAY_SLOT(37)
	BFME_REGION_DISPLAY_SLOT(38) BFME_REGION_DISPLAY_SLOT(39)
	BFME_REGION_DISPLAY_SLOT(40) BFME_REGION_DISPLAY_SLOT(41)
	BFME_REGION_DISPLAY_SLOT(42) BFME_REGION_DISPLAY_SLOT(43)
	BFME_REGION_DISPLAY_SLOT(44) BFME_REGION_DISPLAY_SLOT(45)
	BFME_REGION_DISPLAY_SLOT(46)
	virtual void drawOpenRect( Real x, Real y, Real width, Real height,
		Real lineWidth, Color color );
	virtual void drawFillRect( Real x, Real y, Real width, Real height,
		Color color );
};

#undef BFME_REGION_DISPLAY_SLOT

extern Display *TheDisplay;
extern void j_00017256();

// The retail call is to the existing 5-byte ILT.  Keep its thunk symbol and
// cast only the proven call ABI, so no new shared pin is needed.
typedef void (__cdecl *Rva00411220ColorCall)( Int value, Color *colors );

// ?bfmeRegionRenderB@@YAXPAXHH@Z
void bfmeRegionRenderB( void *rawRegion, Int rawOffset, const Int rawValue )
{
	const Rva004129B0Offset *offset = (const Rva004129B0Offset *)(UnsignedInt)rawOffset;
	Rva004129B0Region *region = (Rva004129B0Region *)(UnsignedInt)rawRegion;
	Int regionLeft = region->left;
	Color colors[4];
	Real regionWidth = (Real)(region->right - regionLeft);
	((Rva00411220ColorCall)j_00017256)( rawValue, colors );

	UnsignedInt state = *(UnsignedInt *)0x012F13C8;
	if( (state & 1) == 0 )
	{
		state |= 1;
		*(UnsignedInt *)0x012F13C8 = state;
		*(UnsignedInt *)0x012F13C4 = 0x7F000000;
	}
	if( (state & 2) == 0 )
	{
		state |= 2;
		*(UnsignedInt *)0x012F13C8 = state;
		*(UnsignedInt *)0x012F13C0 = 0xFFBA9252;
	}
	if( (state & 4) == 0 )
	{
		state |= 4;
		*(UnsignedInt *)0x012F13C8 = state;
		*(UnsignedInt *)0x012F13BC = 0xFF000000;
	}

	// Retail float pool values: 0x010828C4 is 6.0f, 0x01075340 is 4.0f,
	// and 0x01088830 is 2.0f.
	TheDisplay->drawOpenRect(
		(Real)(offset->x + regionLeft - 3),
		(Real)(region->top + offset->y - 3),
		regionWidth + *(const Real *)0x010828C4,
		10.0f, 1.0f, *(UnsignedInt *)0x012F13C4 );

	TheDisplay->drawOpenRect(
		(Real)(region->left + offset->x - 2),
		(Real)(region->top + offset->y - 2),
		regionWidth + *(const Real *)0x01075340,
		8.0f, 1.0f, *(UnsignedInt *)0x012F13C0 );

	TheDisplay->drawFillRect(
		(Real)(region->left + offset->x - 1),
		(Real)(region->top + offset->y - 1),
		regionWidth + *(const Real *)0x01088830,
		6.0f, *(UnsignedInt *)0x012F13BC );

	regionWidth = *(volatile Real *)&regionWidth * *(Real *)&rawValue;
	for( Int i = 0; i < 4; ++i )
	{
		TheDisplay->drawFillRect(
			(Real)(region->left + offset->x),
			(Real)(region->top + offset->y + i),
			regionWidth, 1.0f, colors[i] );
	}
}

