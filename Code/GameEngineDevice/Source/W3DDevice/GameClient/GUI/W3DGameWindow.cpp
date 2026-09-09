// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DGameWindow::~W3DGameWindow, retail 0x004655F0,
// zh_sweep packet 004655f0.
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2dsentence.h
class Render2DSentenceClass
{
public:
	~Render2DSentenceClass();								///< retail 0x00887940
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
protected:
	// Protected, as retail's mangling records: ??1GameWindow@@MAE@XZ.
	virtual ~GameWindow();									///< ILT 0x00013AF7 -> 0x00479CD0

	friend class W3DGameWindow;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DGameWindow.h
class W3DGameWindow : public GameWindow
{
protected:
	virtual ~W3DGameWindow( void );

	// vptr at +0x00; m_textRenderer lands at +0x268.
	unsigned char m_unreconstructed_04[0x268 - 4];
	Render2DSentenceClass m_textRenderer;					///< +0x268
};


// Retail 0x0078D810 initializes the border images in this window TU.
// The enum order is the vendored Gadget.h order: right pieces precede top
// pieces in the static pointer array, despite the lookup-call order below.
typedef bool Bool;
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

// W3DGameWindow::~W3DGameWindow ==============================================
//=============================================================================
// ??1W3DGameWindow@@MAE@XZ
W3DGameWindow::~W3DGameWindow( void )
{

}  // end ~W3DGameWindow
