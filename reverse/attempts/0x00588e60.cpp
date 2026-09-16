// ?draw@Rva00588E60Owner@@QAEXPBUCoord2D@@0PAX1@Z
// partial score=0.77 date=2026-09-16
// cl: /DNDEBUG /MD
// Retail RVA 0x00588E60. Draws the image held at +0x1C through the global
// pinned as ?TheDisplay@@3PAVDisplay@@A, between the first argument and the
// first argument offset by the second. Nothing names the owner or the image,
// so both are address-derived, and the three Display slots keep their indices
// as names.

struct Coord2D
{
	float x;
	float y;
};

class Rva00588E60Image;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Display.h
class Display
{
public:
#define RVA00588E60_UNUSED_SLOT( N ) virtual void slot##N();
	RVA00588E60_UNUSED_SLOT( 0 )
	RVA00588E60_UNUSED_SLOT( 1 )
	RVA00588E60_UNUSED_SLOT( 2 )
	RVA00588E60_UNUSED_SLOT( 3 )
	RVA00588E60_UNUSED_SLOT( 4 )
	RVA00588E60_UNUSED_SLOT( 5 )
	RVA00588E60_UNUSED_SLOT( 6 )
	RVA00588E60_UNUSED_SLOT( 7 )
	RVA00588E60_UNUSED_SLOT( 8 )
	RVA00588E60_UNUSED_SLOT( 9 )
	RVA00588E60_UNUSED_SLOT( 10 )
	RVA00588E60_UNUSED_SLOT( 11 )
	RVA00588E60_UNUSED_SLOT( 12 )
	RVA00588E60_UNUSED_SLOT( 13 )
	RVA00588E60_UNUSED_SLOT( 14 )
	RVA00588E60_UNUSED_SLOT( 15 )
	RVA00588E60_UNUSED_SLOT( 16 )
	RVA00588E60_UNUSED_SLOT( 17 )
	RVA00588E60_UNUSED_SLOT( 18 )
	RVA00588E60_UNUSED_SLOT( 19 )
	RVA00588E60_UNUSED_SLOT( 20 )
	RVA00588E60_UNUSED_SLOT( 21 )
	RVA00588E60_UNUSED_SLOT( 22 )
	RVA00588E60_UNUSED_SLOT( 23 )
	RVA00588E60_UNUSED_SLOT( 24 )
	RVA00588E60_UNUSED_SLOT( 25 )
	RVA00588E60_UNUSED_SLOT( 26 )
	RVA00588E60_UNUSED_SLOT( 27 )
	RVA00588E60_UNUSED_SLOT( 28 )
	RVA00588E60_UNUSED_SLOT( 29 )
	RVA00588E60_UNUSED_SLOT( 30 )
	RVA00588E60_UNUSED_SLOT( 31 )
	RVA00588E60_UNUSED_SLOT( 32 )
	RVA00588E60_UNUSED_SLOT( 33 )
	RVA00588E60_UNUSED_SLOT( 34 )
	RVA00588E60_UNUSED_SLOT( 35 )
	RVA00588E60_UNUSED_SLOT( 36 )
	RVA00588E60_UNUSED_SLOT( 37 )
	RVA00588E60_UNUSED_SLOT( 38 )
	RVA00588E60_UNUSED_SLOT( 39 )
	RVA00588E60_UNUSED_SLOT( 40 )
	RVA00588E60_UNUSED_SLOT( 41 )
	RVA00588E60_UNUSED_SLOT( 42 )
	RVA00588E60_UNUSED_SLOT( 43 )
	virtual void slot44();
	RVA00588E60_UNUSED_SLOT( 45 )
	RVA00588E60_UNUSED_SLOT( 46 )
	RVA00588E60_UNUSED_SLOT( 47 )
	RVA00588E60_UNUSED_SLOT( 48 )
	RVA00588E60_UNUSED_SLOT( 49 )
	RVA00588E60_UNUSED_SLOT( 50 )
	RVA00588E60_UNUSED_SLOT( 51 )
	RVA00588E60_UNUSED_SLOT( 52 )
	virtual void slot53( Rva00588E60Image *image, float left, float top,
		float right, float bottom, int color, int mode );
	RVA00588E60_UNUSED_SLOT( 54 )
	virtual void slot55();
#undef RVA00588E60_UNUSED_SLOT
};

extern Display *TheDisplay;

class Rva00588E60Owner
{
public:
	void draw( const Coord2D *origin, const Coord2D *size, void *unused3,
		void *unused4 );

	unsigned char m_bfmePad000[ 0x1c ];
	Rva00588E60Image *m_bfmeImage;
};

void Rva00588E60Owner::draw( const Coord2D *origin, const Coord2D *size,
	void *unused3, void *unused4 )
{
	Rva00588E60Image *image = m_bfmeImage;

	if( image == 0 )
		return;

	float bottom = size->y + origin->y;
	float left = origin->x;
	float top = origin->y;
	float right = origin->x + size->x;
	Display *display = TheDisplay;

	display->slot44();
	display->slot53( image, left, top, right, bottom, -1, 2 );
	display->slot55();
}
