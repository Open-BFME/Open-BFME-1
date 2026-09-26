// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include
// Open-BFME5: W3DGameWindow::~W3DGameWindow, retail 0x004655F0,
// zh_sweep packet 004655f0.

typedef int Int;
typedef float Real;
typedef int Color;
typedef bool Bool;
static const Bool FALSE = false;
class Image;
class Display
{
public:
	virtual void unused00(); virtual void unused01();
	virtual void unused02(); virtual void unused03();
	virtual void unused04(); virtual void unused05();
	virtual void unused06(); virtual void unused07();
	virtual void unused08(); virtual void unused09();
	virtual void unused10(); virtual void unused11();
	virtual void unused12(); virtual void unused13();
	virtual void unused14(); virtual void unused15();
	virtual void unused16(); virtual void unused17();
	virtual void unused18(); virtual void unused19();
	virtual void unused20(); virtual void unused21();
	virtual void unused22(); virtual void unused23();
	virtual void unused24(); virtual void unused25();
	virtual void unused26(); virtual void unused27();
	virtual void unused28(); virtual void unused29();
	virtual void unused30(); virtual void unused31();
	virtual void unused32(); virtual void unused33();
	virtual void setClipRegion(void *region);
	virtual void unused35();
	virtual void enableClipping(Bool onoff);
	virtual void unused37(); virtual void unused38();
	virtual void unused39(); virtual void unused40();
	virtual void unused41(); virtual void unused42();
	virtual void unused43(); virtual void beginImageDraw();
	virtual void unused45(); virtual void unused46();
	virtual void unused47(); virtual void unused48();
	virtual void unused49(); virtual void unused50();
	virtual void unused51(); virtual void unused52();
	virtual void drawImageCore(const Image *image, Real startX, Real startY,
										Real endX, Real endY, Color color, Int mode);
	virtual void unused54();
	virtual void endImageDraw(void);

	inline void drawImage(const Image *image, Real startX, Real startY,
									 Real endX, Real endY, Color color = -1,
									 Int mode = 2)
	{
		beginImageDraw();
		drawImageCore(image, startX, startY, endX, endY, color, mode);
		endImageDraw();
	}
};
extern Display *TheDisplay;
//
// The Zero Hour destructor body is empty; everything retail emits is the
// implicit epilogue -- stamp the W3DGameWindow vptr, destroy the one
// non-trivial member, then chain to ~GameWindow. Two facts come out of the
// bytes:
//
//  - the member is at [this+0x268] and its destructor is
//    Render2DSentenceClass::~Render2DSentenceClass (0x00887940), i.e. the
//    m_textRenderer the reference class declares. Retail destroys exactly one
//    member, so nothing else in W3DGameWindow needs destruction.
//  - ~GameWindow is a real call to 0x00013AF7, not inlined, and it runs with
//    the EH state already back at -1.
//
// The reference tree's W3DGameWindow.cpp is not ported, so both classes are
// spelled TU-locally. The split between GameWindow's own size and
// W3DGameWindow's leading members is not recovered here -- only the total
// distance to m_textRenderer is proven -- so it is carried as one opaque run
// rather than invented member names.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2dsentence.h
class Render2DSentenceClass
{
public:
	~Render2DSentenceClass();								///< retail 0x00887940
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
protected:
	// Protected, as retail's mangling records: ??1GameWindow@@MAE@XZ.
	virtual ~GameWindow();									///< ILT 0x00013AF7 -> 0x00479CD0

	friend class W3DGameWindow;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DGameWindow.h
class W3DGameWindow : public GameWindow
{
protected:
	virtual ~W3DGameWindow( void );
	void blitBorderRect( Int x, Int y, Int width, Int height );

	// vptr at +0x00; m_textRenderer lands at +0x268.
	unsigned char m_unreconstructed_04[0x268 - 4];
	Render2DSentenceClass m_textRenderer;					///< +0x268
};


// Retail 0x0078D810 initializes the border images in this window TU.
// The enum order is the vendored Gadget.h order: right pieces precede top
// pieces in the static pointer array, despite the lookup-call order below.
class Image;
template <class T> class StringBase
{
private:
	void *m_data;
	StringBase(const T *text);
	~StringBase();
	friend class AsciiString;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString();
};
class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};
extern ImageCollection *TheMappedImageCollection;

enum BorderPiece
{
	BORDER_CORNER_UL,
	BORDER_CORNER_UR,
	BORDER_CORNER_LL,
	BORDER_CORNER_LR,
	BORDER_VERTICAL_LEFT,
	BORDER_VERTICAL_LEFT_SHORT,
	BORDER_VERTICAL_RIGHT,
	BORDER_VERTICAL_RIGHT_SHORT,
	BORDER_HORIZONTAL_TOP,
	BORDER_HORIZONTAL_TOP_SHORT,
	BORDER_HORIZONTAL_BOTTOM,
	BORDER_HORIZONTAL_BOTTOM_SHORT,
	NUM_BORDER_PIECES
};

enum
{
	BORDER_CORNER_SIZE = 15,
	BORDER_LINE_SIZE = 20
};

static Bool bordersInit = false;
static const Image *borderPieces[NUM_BORDER_PIECES] = { 0 };

// ?initBorders@@YAXXZ
void initBorders(void)
{
	{
		AsciiString name("BorderCornerUL");
		borderPieces[BORDER_CORNER_UL] = TheMappedImageCollection->findImageByName(name);
	}
	{
		AsciiString name("BorderCornerUR");
		borderPieces[BORDER_CORNER_UR] = TheMappedImageCollection->findImageByName(name);
	}
	{
		AsciiString name("BorderCornerLL");
		borderPieces[BORDER_CORNER_LL] = TheMappedImageCollection->findImageByName(name);
	}
	{
		AsciiString name("BorderCornerLR");
		borderPieces[BORDER_CORNER_LR] = TheMappedImageCollection->findImageByName(name);
	}
	{
		AsciiString name("BorderLeft");
		borderPieces[BORDER_VERTICAL_LEFT] = TheMappedImageCollection->findImageByName(name);
	}
	{
		AsciiString name("BorderLeftShort");
		borderPieces[BORDER_VERTICAL_LEFT_SHORT] = TheMappedImageCollection->findImageByName(name);
	}
	{
		AsciiString name("BorderTop");
		borderPieces[BORDER_HORIZONTAL_TOP] = TheMappedImageCollection->findImageByName(name);
	}
	{
		AsciiString name("BorderTopShort");
		borderPieces[BORDER_HORIZONTAL_TOP_SHORT] = TheMappedImageCollection->findImageByName(name);
	}
	{
		AsciiString name("BorderRight");
		borderPieces[BORDER_VERTICAL_RIGHT] = TheMappedImageCollection->findImageByName(name);
	}
	{
		AsciiString name("BorderRightShort");
		borderPieces[BORDER_VERTICAL_RIGHT_SHORT] = TheMappedImageCollection->findImageByName(name);
	}
	{
		AsciiString name("BorderBottom");
		borderPieces[BORDER_HORIZONTAL_BOTTOM] = TheMappedImageCollection->findImageByName(name);
	}
	{
		AsciiString name("BorderBottomShort");
		borderPieces[BORDER_HORIZONTAL_BOTTOM_SHORT] = TheMappedImageCollection->findImageByName(name);
	}
	bordersInit = true;
}

void W3DGameWindow::blitBorderRect( Int x, Int y, Int width, Int height )
{
	Int Offset = 15;
	Int OffsetLower = 5;
	if( bordersInit == FALSE )
		initBorders();

	Int originalX = x;
	Int originalY = y;
	Int maxX = x + width;
	Int maxY = y + height;
	Int x2, y2;
	Int size = 20;
	Int halfSize = size / 2;

	y = originalY - Offset;
	y2 = maxY - OffsetLower;
	x2 = maxX - (OffsetLower + BORDER_LINE_SIZE);

	for( x=(originalX + OffsetLower); x <= x2; x += BORDER_LINE_SIZE )
	{
		TheDisplay->drawImage( borderPieces[ BORDER_HORIZONTAL_TOP ],
															 x, y, x + size, y + size );
		TheDisplay->drawImage( borderPieces[ BORDER_HORIZONTAL_BOTTOM ],
															 x, y2, x + size, y2 + size );
	}

	x2 = maxX - 5;
	if( (x2 - x) >= (BORDER_LINE_SIZE / 2) )
	{
		TheDisplay->drawImage( borderPieces[ BORDER_HORIZONTAL_TOP_SHORT ],
															 x, y, x + halfSize, y + size );
		TheDisplay->drawImage( borderPieces[ BORDER_HORIZONTAL_BOTTOM_SHORT ],
															 x, y2, x + halfSize, y2 + size );
		x += (BORDER_LINE_SIZE / 2);
	}

	if( x < x2 )
	{
		x -= ((BORDER_LINE_SIZE / 2) - (((x2 - x) + 1) & ~1));
		TheDisplay->drawImage( borderPieces[ BORDER_HORIZONTAL_TOP_SHORT ],
															 x, y, x + halfSize, y + size );
		TheDisplay->drawImage( borderPieces[ BORDER_HORIZONTAL_BOTTOM_SHORT ],
															 x, y2, x + halfSize, y2 + size );
	}

	x = originalX - Offset;
	x2 = maxX - OffsetLower;
	y2 = maxY - (OffsetLower + BORDER_LINE_SIZE);

	for( y=(originalY + OffsetLower); y <= y2; y += BORDER_LINE_SIZE )
	{
		TheDisplay->drawImage( borderPieces[ BORDER_VERTICAL_LEFT ],
															 x, y, x + size, y + size );
		TheDisplay->drawImage( borderPieces[ BORDER_VERTICAL_RIGHT ],
															 x2, y, x2 + size, y + size );
	}

	y2 = maxY - OffsetLower;
	if( (y2 - y) >= (BORDER_LINE_SIZE / 2) )
	{
		TheDisplay->drawImage( borderPieces[ BORDER_VERTICAL_LEFT_SHORT ],
															 x, y, x + size, y + halfSize );
		TheDisplay->drawImage( borderPieces[ BORDER_VERTICAL_RIGHT_SHORT ],
															 x2, y, x2 + size, y + halfSize );
		y += (BORDER_LINE_SIZE / 2);
	}

	if( y < y2 )
	{
		y -= ((BORDER_LINE_SIZE / 2) - (((y2 - y) + 1) & ~1));
		TheDisplay->drawImage( borderPieces[ BORDER_VERTICAL_LEFT_SHORT ],
															 x, y, x + size, y + halfSize );
		TheDisplay->drawImage( borderPieces[ BORDER_VERTICAL_RIGHT_SHORT ],
															 x2, y, x2 + size, y + halfSize );
	}

	x = originalX - BORDER_CORNER_SIZE;
	y = originalY - BORDER_CORNER_SIZE;
	TheDisplay->drawImage( borderPieces[ BORDER_CORNER_UL ],
														 x, y, x + size, y + size );
	x = maxX - 5;
	y = originalY - BORDER_CORNER_SIZE;
	TheDisplay->drawImage( borderPieces[ BORDER_CORNER_UR ],
														 x, y, x + size, y + size );
	x = originalX - BORDER_CORNER_SIZE;
	y = maxY - 5;
	TheDisplay->drawImage( borderPieces[ BORDER_CORNER_LL ],
														 x, y, x + size, y + size );
	x = maxX - 5;
	y = maxY - 5;
	TheDisplay->drawImage( borderPieces[ BORDER_CORNER_LR ],
														 x, y, x + size, y + size );
}

// W3DGameWindow::~W3DGameWindow ==============================================
//=============================================================================
// ??1W3DGameWindow@@MAE@XZ
W3DGameWindow::~W3DGameWindow( void )
{

}  // end ~W3DGameWindow
