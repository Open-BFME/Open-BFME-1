// ?bfmeRegionRenderC@@YAXPAXHH@Z
// Retail 0x00412C10..0x00412DEE; Drawable::bfmeRegionDispatch routes through ILT00005A51.
// Existing raw-argument ABI; native volatile view preserves the one offset-x load.
// cl: /DNDEBUG /MD /EHs-c-

typedef unsigned int UnsignedInt;
typedef int Int;
typedef float Real;
typedef unsigned int Color;

struct Rva00412C10Region
{
	Int left;
	Int top;
	Int right;
};

struct Rva00412C10Offset
{
	Int x;
	Int y;
};

#define BFME_REGION_DISPLAY_SLOT(n) virtual void slot##n();

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
extern void j_0003b390();
typedef void (__cdecl *Rva00411400ColorCall)( Int value, Color *colors );

void bfmeRegionRenderC( void *rawRegion, Int rawOffset, const Int rawValue )
{
	const Rva00412C10Offset *offset = (const Rva00412C10Offset *)(UnsignedInt)rawOffset;
	Rva00412C10Region *region = (Rva00412C10Region *)(UnsignedInt)rawRegion;
	const Int regionLeft = region->left;
	Color colors[3];
	Real regionWidth = (Real)(region->right - regionLeft);
	((Rva00411400ColorCall)j_0003b390)( rawValue, colors );

	UnsignedInt state = *(UnsignedInt *)0x012F13D8;
	if( (state & 1) == 0 )
	{
		state |= 1;
		*(UnsignedInt *)0x012F13D8 = state;
		*(UnsignedInt *)0x012F13D4 = 0x7F000000;
	}
	if( (state & 2) == 0 )
	{
		state |= 2;
		*(UnsignedInt *)0x012F13D8 = state;
		*(UnsignedInt *)0x012F13D0 = 0xFFBA9252;
	}
	if( (state & 4) == 0 )
	{
		state |= 4;
		*(UnsignedInt *)0x012F13D8 = state;
		*(UnsignedInt *)0x012F13CC = 0xFF000000;
	}

	TheDisplay->drawOpenRect(
		(Real)(regionLeft + *(const volatile Int *)&offset->x - 3),
		(Real)(region->top + offset->y - 3),
		regionWidth + *(const Real *)0x010828C4,
		9.0f, 1.0f, *(UnsignedInt *)0x012F13D4 );

	TheDisplay->drawOpenRect(
		(Real)(region->left + offset->x - 2),
		(Real)(region->top + offset->y - 2),
		regionWidth + *(const Real *)0x01075340,
		7.0f, 1.0f, *(UnsignedInt *)0x012F13D0 );

	TheDisplay->drawFillRect(
		(Real)(region->left + offset->x - 1),
		(Real)(region->top + offset->y - 1),
		regionWidth + *(const Real *)0x01088830,
		5.0f, *(UnsignedInt *)0x012F13CC );

	const Real &rawValueReal = *(const Real *)&rawValue;
	regionWidth = *(volatile Real *)&regionWidth * rawValueReal;
	for( Int i = 0; i < 3; ++i )
	{
		TheDisplay->drawFillRect(
			(Real)(region->left + offset->x),
			(Real)(region->top + offset->y + i),
			regionWidth, 1.0f, colors[i] );
	}
}
