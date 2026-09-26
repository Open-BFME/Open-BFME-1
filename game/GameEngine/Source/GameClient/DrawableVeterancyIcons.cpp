// cl: /DNDEBUG /MD /EHs-c-
// ?rva00420360@Drawable@@QAEX_NH@Z

// Retail 0x00420360, 627 bytes, thiscall, ret 8.
//
// Owner: the only caller is 0x00420670, which the matched Drawable::drawIconUI
// dispatch (0x00420AC0) reaches through ILT 0x00038AAA; it forwards its own
// Drawable `this` through ILT 0x0001FC53 with (Bool, Int). This body hands the
// same `this` to the Drawable member at 0x0041FCE0 (via ILT 0x000239ED), which
// fills a Coord3D with the object position raised by the geometry height plus
// a template offset (default 10.0f). That is the shape of ZH
// Object::getHealthBoxPosition, but the BFME Drawable-level name is not
// proven, so both this body and that callee keep their addresses.
//
// What it draws: Drawable::s_veterancyImage[4] at 0x012F12F4..0x012F1300 is
// filled by the matched Drawable::initStaticImages (0x00415D50,
// DrawableInitStaticImages.cpp) with "Good_Vet", "Good_Vet_Dot", "Evil_Vet"
// and "Evil_Vet_Dot". The Bool picks the Evil pair; the Int (an
// ExperienceLevelSystem value in the caller) is drawn as level/5 Vet icons
// in a row above level%5 Vet_Dot icons, both rows centred on the projected
// health-box position.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned int Color;
typedef float Real;
typedef bool Bool;

struct Coord2D
{
	Real x;
	Real y;
};

struct ICoord2D
{
	Int x;
	Int y;
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Image.h
class Image
{
public:
	unsigned char m_pad000[ 0x24 ];
	ICoord2D m_imageSize;						// +0x24

	Int getImageWidth() const { return m_imageSize.x; }
	Int getImageHeight() const { return m_imageSize.y; }
};

#define DISPLAY_SLOT(n) virtual void slot##n();

class Display
{
public:
	DISPLAY_SLOT(00) DISPLAY_SLOT(01) DISPLAY_SLOT(02) DISPLAY_SLOT(03)
	DISPLAY_SLOT(04) DISPLAY_SLOT(05) DISPLAY_SLOT(06) DISPLAY_SLOT(07)
	DISPLAY_SLOT(08) DISPLAY_SLOT(09) DISPLAY_SLOT(10)
	virtual UnsignedInt getWidth();					// slot 11
	virtual UnsignedInt getHeight();				// slot 12
	DISPLAY_SLOT(13) DISPLAY_SLOT(14) DISPLAY_SLOT(15)
	DISPLAY_SLOT(16) DISPLAY_SLOT(17) DISPLAY_SLOT(18) DISPLAY_SLOT(19)
	DISPLAY_SLOT(20) DISPLAY_SLOT(21) DISPLAY_SLOT(22) DISPLAY_SLOT(23)
	DISPLAY_SLOT(24) DISPLAY_SLOT(25) DISPLAY_SLOT(26) DISPLAY_SLOT(27)
	DISPLAY_SLOT(28) DISPLAY_SLOT(29) DISPLAY_SLOT(30) DISPLAY_SLOT(31)
	DISPLAY_SLOT(32) DISPLAY_SLOT(33) DISPLAY_SLOT(34) DISPLAY_SLOT(35)
	DISPLAY_SLOT(36) DISPLAY_SLOT(37) DISPLAY_SLOT(38) DISPLAY_SLOT(39)
	DISPLAY_SLOT(40) DISPLAY_SLOT(41) DISPLAY_SLOT(42) DISPLAY_SLOT(43)
	DISPLAY_SLOT(44) DISPLAY_SLOT(45) DISPLAY_SLOT(46) DISPLAY_SLOT(47)
	DISPLAY_SLOT(48) DISPLAY_SLOT(49) DISPLAY_SLOT(50) DISPLAY_SLOT(51)
	DISPLAY_SLOT(52)
	// slot 53; retail pushes color 0xFFFFFFFF and mode 2 (ZH DRAW_IMAGE_ALPHA)
	virtual void drawImage( const Image *image, Real startX, Real startY,
		Real endX, Real endY, Color color = 0xFFFFFFFF, Int mode = 2 );
};

#undef DISPLAY_SLOT
#define VIEW_SLOT(n) virtual void slot##n();

class View
{
public:
	VIEW_SLOT(00) VIEW_SLOT(01) VIEW_SLOT(02) VIEW_SLOT(03)
	VIEW_SLOT(04) VIEW_SLOT(05) VIEW_SLOT(06) VIEW_SLOT(07)
	VIEW_SLOT(08) VIEW_SLOT(09) VIEW_SLOT(10) VIEW_SLOT(11)
	VIEW_SLOT(12) VIEW_SLOT(13) VIEW_SLOT(14) VIEW_SLOT(15)
	VIEW_SLOT(16) VIEW_SLOT(17) VIEW_SLOT(18) VIEW_SLOT(19)
	VIEW_SLOT(20) VIEW_SLOT(21) VIEW_SLOT(22) VIEW_SLOT(23)
	VIEW_SLOT(24) VIEW_SLOT(25) VIEW_SLOT(26) VIEW_SLOT(27)
	VIEW_SLOT(28) VIEW_SLOT(29) VIEW_SLOT(30) VIEW_SLOT(31)
	VIEW_SLOT(32) VIEW_SLOT(33) VIEW_SLOT(34) VIEW_SLOT(35)
	VIEW_SLOT(36) VIEW_SLOT(37) VIEW_SLOT(38) VIEW_SLOT(39)
	VIEW_SLOT(40) VIEW_SLOT(41) VIEW_SLOT(42) VIEW_SLOT(43)
	VIEW_SLOT(44) VIEW_SLOT(45) VIEW_SLOT(46) VIEW_SLOT(47)
	VIEW_SLOT(48) VIEW_SLOT(49) VIEW_SLOT(50) VIEW_SLOT(51)
	VIEW_SLOT(52) VIEW_SLOT(53) VIEW_SLOT(54) VIEW_SLOT(55)
	VIEW_SLOT(56) VIEW_SLOT(57) VIEW_SLOT(58) VIEW_SLOT(59)
	VIEW_SLOT(60) VIEW_SLOT(61) VIEW_SLOT(62) VIEW_SLOT(63)
	VIEW_SLOT(64) VIEW_SLOT(65) VIEW_SLOT(66) VIEW_SLOT(67)
	VIEW_SLOT(68) VIEW_SLOT(69) VIEW_SLOT(70) VIEW_SLOT(71)
	virtual Real getZoom();						// slot 72
	VIEW_SLOT(73) VIEW_SLOT(74) VIEW_SLOT(75)
	VIEW_SLOT(76) VIEW_SLOT(77) VIEW_SLOT(78) VIEW_SLOT(79)
	VIEW_SLOT(80) VIEW_SLOT(81) VIEW_SLOT(82) VIEW_SLOT(83)
	VIEW_SLOT(84) VIEW_SLOT(85) VIEW_SLOT(86)
	// slot 87; zero means on screen (ZH WTS_INSIDE_FRUSTUM), so retail
	// returns on any nonzero result
	virtual Int worldToScreenTriReturn( const Coord3D *world, ICoord2D *screen );
};

#undef VIEW_SLOT

extern Display *TheDisplay;
extern View *TheTacticalView;

class Drawable
{
public:
	void rva00420360( Bool evil, Int level );
	// 0x0041FCE0, reached through ILT 0x000239ED: thiscall, one Coord3D&
	// out argument, ret 4. drawIconUI (0x00420860) makes the same call.
	void rva0041FCE0( Coord3D &position );

private:
	// defined in DrawableInitStaticImages.cpp
	static const Image *s_veterancyImage[ 4 ];
};

void Drawable::rva00420360( Bool evil, Int level )
{
	if ( level <= 0 )
		return;

	Real scaleX = TheDisplay->getWidth() / 1024.0f;
	scaleX *= 0.5f;
	Real scaleY = TheDisplay->getHeight() / 768.0f;
	scaleY *= 0.5f;
	Real zoom = 1.0f / TheTacticalView->getZoom();
	scaleX *= zoom;
	scaleY *= zoom;
	Real gapY = scaleY * 2.0f;
	Real gapX = scaleX * 2.0f;

	Coord3D pos;
	rva0041FCE0( pos );
	ICoord2D screen;
	if ( TheTacticalView->worldToScreenTriReturn( &pos, &screen ) != 0 )
		return;

	// Retail keeps this pair as one aggregate beside screen and pos in the
	// frame; two scalar locals move every spill slot. The rows then walk up
	// from it through a reference: with a direct anchor.y the Vet row's
	// pushed copy of y is scheduled three instructions late.
	Coord2D anchor;
	anchor.x = screen.x;
	anchor.y = screen.y - 7.0f;
	Real &y = anchor.y;
	// [0] = Vet, [1] = Vet_Dot
	const Image **images = evil ? &s_veterancyImage[ 2 ] : &s_veterancyImage[ 0 ];

	Int vetCount = level / 5;
	Int dotCount = level % 5;

	Real dotHeight = images[ 1 ]->getImageHeight() * scaleY;
	y -= dotHeight;
	if ( dotCount > 0 )
	{
		Real dotWidth = images[ 1 ]->getImageWidth() * scaleX;
		Real x = anchor.x - ( ( dotCount - 1 ) * gapX + dotCount * dotWidth ) * 0.5f;
		do
		{
			TheDisplay->drawImage( images[ 1 ], x, y, x + dotWidth, dotHeight + y );
			x += dotWidth + gapX;
		} while ( --dotCount > 0 );
	}

	if ( vetCount > 0 )
	{
		Real vetHeight = images[ 0 ]->getImageHeight() * scaleY;
		y -= gapY + vetHeight;
		Real vetWidth = images[ 0 ]->getImageWidth() * scaleX;
		Real x = anchor.x - ( ( vetCount - 1 ) * gapX + vetCount * vetWidth ) * 0.5f;
		do
		{
			TheDisplay->drawImage( images[ 0 ], x, y, x + vetWidth, y + vetHeight );
			x += vetWidth + gapX;
		} while ( --vetCount > 0 );
	}
}
