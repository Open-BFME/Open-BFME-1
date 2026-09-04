// cl: /DNDEBUG /MD /EHs-c-
// BFME Drawable caption stage, retail 0x00420150.

typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;
typedef int Int;
typedef unsigned int Color;
typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

struct ICoord2D
{
	Int x;
	Int y;
};

struct Rva0087DC00Vec
{
	Real x;
	Real y;
	Real z;
};

class Rva0087DC00
{
	UnsignedByte m_pad[ 0x18 ];
	Rva0087DC00Vec m_center;

public:
	void get( Rva0087DC00Vec *out );
};

class ThingTemplate
{
public:
	void *m_vtable;
	ThingTemplate *m_nextOverride;
	UnsignedByte m_pad008[ 0x58 ];
	Rva0087DC00 m_geometry;

	ThingTemplate *getFinalOverride();
};

class BFMEObject
{
	UnsignedByte m_pad[ 0x108 ];

public:
	Rva0087DC00 *m_geometry;
};

#define BFME_CAPTION_DISPLAY_SLOT(n) virtual void slot##n();

class DisplayString
{
public:
	BFME_CAPTION_DISPLAY_SLOT(00) BFME_CAPTION_DISPLAY_SLOT(01)
	BFME_CAPTION_DISPLAY_SLOT(02) BFME_CAPTION_DISPLAY_SLOT(03)
	BFME_CAPTION_DISPLAY_SLOT(04) BFME_CAPTION_DISPLAY_SLOT(05)
	BFME_CAPTION_DISPLAY_SLOT(06) BFME_CAPTION_DISPLAY_SLOT(07)
	BFME_CAPTION_DISPLAY_SLOT(08) BFME_CAPTION_DISPLAY_SLOT(09)
	virtual void setColor( Color color, Color dropColor );
	BFME_CAPTION_DISPLAY_SLOT(11) BFME_CAPTION_DISPLAY_SLOT(12)
	BFME_CAPTION_DISPLAY_SLOT(13)
	virtual void draw( Int x, Int y, Int scaleX, Int scaleY );
	virtual void getSize( Int *width, Int *height );
	virtual Int getWidth( Int line );
};

class Display
{
public:
	BFME_CAPTION_DISPLAY_SLOT(00) BFME_CAPTION_DISPLAY_SLOT(01)
	BFME_CAPTION_DISPLAY_SLOT(02) BFME_CAPTION_DISPLAY_SLOT(03)
	BFME_CAPTION_DISPLAY_SLOT(04) BFME_CAPTION_DISPLAY_SLOT(05)
	BFME_CAPTION_DISPLAY_SLOT(06) BFME_CAPTION_DISPLAY_SLOT(07)
	BFME_CAPTION_DISPLAY_SLOT(08) BFME_CAPTION_DISPLAY_SLOT(09)
	BFME_CAPTION_DISPLAY_SLOT(10) BFME_CAPTION_DISPLAY_SLOT(11)
	BFME_CAPTION_DISPLAY_SLOT(12) BFME_CAPTION_DISPLAY_SLOT(13)
	BFME_CAPTION_DISPLAY_SLOT(14) BFME_CAPTION_DISPLAY_SLOT(15)
	BFME_CAPTION_DISPLAY_SLOT(16) BFME_CAPTION_DISPLAY_SLOT(17)
	BFME_CAPTION_DISPLAY_SLOT(18) BFME_CAPTION_DISPLAY_SLOT(19)
	BFME_CAPTION_DISPLAY_SLOT(20) BFME_CAPTION_DISPLAY_SLOT(21)
	BFME_CAPTION_DISPLAY_SLOT(22) BFME_CAPTION_DISPLAY_SLOT(23)
	BFME_CAPTION_DISPLAY_SLOT(24) BFME_CAPTION_DISPLAY_SLOT(25)
	BFME_CAPTION_DISPLAY_SLOT(26) BFME_CAPTION_DISPLAY_SLOT(27)
	BFME_CAPTION_DISPLAY_SLOT(28) BFME_CAPTION_DISPLAY_SLOT(29)
	BFME_CAPTION_DISPLAY_SLOT(30) BFME_CAPTION_DISPLAY_SLOT(31)
	BFME_CAPTION_DISPLAY_SLOT(32) BFME_CAPTION_DISPLAY_SLOT(33)
	BFME_CAPTION_DISPLAY_SLOT(34) BFME_CAPTION_DISPLAY_SLOT(35)
	BFME_CAPTION_DISPLAY_SLOT(36) BFME_CAPTION_DISPLAY_SLOT(37)
	BFME_CAPTION_DISPLAY_SLOT(38) BFME_CAPTION_DISPLAY_SLOT(39)
	BFME_CAPTION_DISPLAY_SLOT(40) BFME_CAPTION_DISPLAY_SLOT(41)
	BFME_CAPTION_DISPLAY_SLOT(42) BFME_CAPTION_DISPLAY_SLOT(43)
	BFME_CAPTION_DISPLAY_SLOT(44) BFME_CAPTION_DISPLAY_SLOT(45)
	BFME_CAPTION_DISPLAY_SLOT(46)
	virtual void drawOpenRect( Real x, Real y, Real width, Real height,
		Real lineWidth, Color color );
	virtual void drawFillRect( Real x, Real y, Real width, Real height,
		Color color );
};

class TacticalView
{
public:
#define BFME_CAPTION_VIEW_SLOT(n) virtual void slot##n();
	BFME_CAPTION_VIEW_SLOT(00) BFME_CAPTION_VIEW_SLOT(01)
	BFME_CAPTION_VIEW_SLOT(02) BFME_CAPTION_VIEW_SLOT(03)
	BFME_CAPTION_VIEW_SLOT(04) BFME_CAPTION_VIEW_SLOT(05)
	BFME_CAPTION_VIEW_SLOT(06) BFME_CAPTION_VIEW_SLOT(07)
	BFME_CAPTION_VIEW_SLOT(08) BFME_CAPTION_VIEW_SLOT(09)
	BFME_CAPTION_VIEW_SLOT(10) BFME_CAPTION_VIEW_SLOT(11)
	BFME_CAPTION_VIEW_SLOT(12) BFME_CAPTION_VIEW_SLOT(13)
	BFME_CAPTION_VIEW_SLOT(14) BFME_CAPTION_VIEW_SLOT(15)
	BFME_CAPTION_VIEW_SLOT(16) BFME_CAPTION_VIEW_SLOT(17)
	BFME_CAPTION_VIEW_SLOT(18) BFME_CAPTION_VIEW_SLOT(19)
	BFME_CAPTION_VIEW_SLOT(20) BFME_CAPTION_VIEW_SLOT(21)
	BFME_CAPTION_VIEW_SLOT(22) BFME_CAPTION_VIEW_SLOT(23)
	BFME_CAPTION_VIEW_SLOT(24) BFME_CAPTION_VIEW_SLOT(25)
	BFME_CAPTION_VIEW_SLOT(26) BFME_CAPTION_VIEW_SLOT(27)
	BFME_CAPTION_VIEW_SLOT(28) BFME_CAPTION_VIEW_SLOT(29)
	BFME_CAPTION_VIEW_SLOT(30) BFME_CAPTION_VIEW_SLOT(31)
	BFME_CAPTION_VIEW_SLOT(32) BFME_CAPTION_VIEW_SLOT(33)
	BFME_CAPTION_VIEW_SLOT(34) BFME_CAPTION_VIEW_SLOT(35)
	BFME_CAPTION_VIEW_SLOT(36) BFME_CAPTION_VIEW_SLOT(37)
	BFME_CAPTION_VIEW_SLOT(38) BFME_CAPTION_VIEW_SLOT(39)
	BFME_CAPTION_VIEW_SLOT(40) BFME_CAPTION_VIEW_SLOT(41)
	BFME_CAPTION_VIEW_SLOT(42) BFME_CAPTION_VIEW_SLOT(43)
	BFME_CAPTION_VIEW_SLOT(44) BFME_CAPTION_VIEW_SLOT(45)
	BFME_CAPTION_VIEW_SLOT(46) BFME_CAPTION_VIEW_SLOT(47)
	BFME_CAPTION_VIEW_SLOT(48) BFME_CAPTION_VIEW_SLOT(49)
	BFME_CAPTION_VIEW_SLOT(50) BFME_CAPTION_VIEW_SLOT(51)
	BFME_CAPTION_VIEW_SLOT(52) BFME_CAPTION_VIEW_SLOT(53)
	BFME_CAPTION_VIEW_SLOT(54) BFME_CAPTION_VIEW_SLOT(55)
	BFME_CAPTION_VIEW_SLOT(56) BFME_CAPTION_VIEW_SLOT(57)
	BFME_CAPTION_VIEW_SLOT(58) BFME_CAPTION_VIEW_SLOT(59)
	BFME_CAPTION_VIEW_SLOT(60) BFME_CAPTION_VIEW_SLOT(61)
	BFME_CAPTION_VIEW_SLOT(62) BFME_CAPTION_VIEW_SLOT(63)
	BFME_CAPTION_VIEW_SLOT(64) BFME_CAPTION_VIEW_SLOT(65)
	BFME_CAPTION_VIEW_SLOT(66) BFME_CAPTION_VIEW_SLOT(67)
	BFME_CAPTION_VIEW_SLOT(68) BFME_CAPTION_VIEW_SLOT(69)
	BFME_CAPTION_VIEW_SLOT(70) BFME_CAPTION_VIEW_SLOT(71)
	BFME_CAPTION_VIEW_SLOT(72) BFME_CAPTION_VIEW_SLOT(73)
	BFME_CAPTION_VIEW_SLOT(74) BFME_CAPTION_VIEW_SLOT(75)
	BFME_CAPTION_VIEW_SLOT(76) BFME_CAPTION_VIEW_SLOT(77)
	BFME_CAPTION_VIEW_SLOT(78) BFME_CAPTION_VIEW_SLOT(79)
	BFME_CAPTION_VIEW_SLOT(80) BFME_CAPTION_VIEW_SLOT(81)
	BFME_CAPTION_VIEW_SLOT(82) BFME_CAPTION_VIEW_SLOT(83)
	BFME_CAPTION_VIEW_SLOT(84) BFME_CAPTION_VIEW_SLOT(85)
	BFME_CAPTION_VIEW_SLOT(86)
#undef BFME_CAPTION_VIEW_SLOT
	virtual Bool worldToScreen( Coord3D *world, ICoord2D *screen );
};

class InGameUI
{
	UnsignedByte m_pad[ 0x7d0 ];

public:
	Color m_drawableCaptionColor;
};

extern Display *TheDisplay;
extern TacticalView *TheTacticalView;
extern InGameUI *TheInGameUI;
extern void j_0003ee55();

class Drawable
{
	UnsignedByte m_pad000[ 4 ];

public:
	ThingTemplate *m_template;

private:
	UnsignedByte m_pad008[ 0xf4 ];
	BFMEObject *m_object;
	UnsignedByte m_pad100[ 0x1d0 ];
	DisplayString *m_captionDisplayString;

public:
private:
	void drawCaption();
};

void Drawable::drawCaption()
{
	if ( m_captionDisplayString == 0 )
		return;

	ICoord2D screen;
	Coord3D center;
	register BFMEObject *object = m_object;
	Rva0087DC00 *geometry;
	if ( object != 0 )
	{
		geometry = object->m_geometry;
	}
	else
	{
		ThingTemplate *drawableTemplate = m_template;
		if ( drawableTemplate != 0 && drawableTemplate->m_nextOverride != 0 )
			drawableTemplate = drawableTemplate->m_nextOverride->getFinalOverride();
		geometry = &drawableTemplate->m_geometry;
	}

	geometry->get( (Rva0087DC00Vec *)&center );
	typedef const Coord3D *(__fastcall *PositionCall)( Drawable * );
	const Coord3D *position = ((PositionCall)j_0003ee55)( this );
	center.x += position->x;
	center.y += position->y;
	center.z += position->z;

	TheTacticalView->worldToScreen( &center, &screen );
	screen.x -= m_captionDisplayString->getWidth( -1 ) / 2;

	Int width, xPos;
	Int height, yPos;
	m_captionDisplayString->getSize( &width, &height );
	xPos = screen.x - 1;
	yPos = screen.y - 1;
	TheDisplay->drawFillRect( xPos, yPos,
		width + 2, height + 2, 0x7d000000 );
	TheDisplay->drawOpenRect( xPos, yPos,
		width + 2, height + 2, 1.0f, 0xff141414 );

	m_captionDisplayString->setColor( TheInGameUI->m_drawableCaptionColor, 0xff000000 );
	m_captionDisplayString->draw( screen.x, screen.y, 1, 1 );
}
