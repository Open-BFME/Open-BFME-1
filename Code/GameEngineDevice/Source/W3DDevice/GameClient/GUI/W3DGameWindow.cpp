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

// W3DGameWindow::~W3DGameWindow ==============================================
//=============================================================================
// ??1W3DGameWindow@@MAE@XZ
W3DGameWindow::~W3DGameWindow( void )
{

}  // end ~W3DGameWindow
