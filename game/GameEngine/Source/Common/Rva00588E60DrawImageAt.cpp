// cl: /DNDEBUG /MD
// Retail 0x00588E60, 120 bytes. Draws the image held at +0x1C through
// ?TheDisplay@@3PAVDisplay@@A as the rectangle [origin, origin+size).
// Owner and image keep address-derived names: no named caller, vtable,
// or source owner identifies the body; the three Display slots keep the
// indices proven by Rva0046F060DrawImageAt.cpp (beginImageDraw/+0xB0,
// drawImageCore/+0xD4, endImageDraw/+0xDC). The static inline draw helper
// carries the three Display calls so retail's global-load placement
// reproduces byte-exact.

typedef float Real;

struct Coord2D
{
	Real x;
	Real y;
};

class Rva00588E60Image;

class Display
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void unused38();
	virtual void unused39();
	virtual void unused40();
	virtual void unused41();
	virtual void unused42();
	virtual void unused43();
	virtual void beginImageDraw();
	virtual void unused45();
	virtual void unused46();
	virtual void unused47();
	virtual void unused48();
	virtual void unused49();
	virtual void unused50();
	virtual void unused51();
	virtual void unused52();
	virtual void drawImageCore( Rva00588E60Image *image, Real left, Real top,
		Real right, Real bottom, int color, int mode );
	virtual void unused54();
	virtual void endImageDraw();
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

static __forceinline void bfmeDrawImage588E60( Display *display, Rva00588E60Image *image,
	Real left, Real top, Real right, Real bottom )
{
	display->beginImageDraw();
	display->drawImageCore( image, left, top, right, bottom, -1, 2 );
	display->endImageDraw();
}

void Rva00588E60Owner::draw( const Coord2D *origin, const Coord2D *size,
	void *unused3, void *unused4 )
{
	Rva00588E60Image *image = m_bfmeImage;

	if( image == 0 )
		return;

	bfmeDrawImage588E60( TheDisplay, image, origin->x, origin->y,
		origin->x + size->x, size->y + origin->y );
}
