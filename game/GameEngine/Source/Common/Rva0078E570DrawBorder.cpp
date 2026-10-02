// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include
// Open-BFME5: W3DGameWindow::~W3DGameWindow, retail 0x004655F0,
// zh_sweep packet 004655f0.

#include "ascii_string.h"
#include "unicode_string.h"

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
class GameFont;
class GameWindow
{
public:
    Int winGetScreenPosition(Int *, Int *);
    Int winGetSize(Int *, Int *);
    unsigned int winGetStyle();
    GameWindow *winGetChild();
    GameFont *winGetFont();
    UnicodeString winGetText();
protected:
	// Protected, as retail's mangling records: ??1GameWindow@@MAE@XZ.
	virtual ~GameWindow();									///< ILT 0x00013AF7 -> 0x00479CD0

	friend class W3DGameWindow;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DGameWindow.h
class W3DGameWindow : public GameWindow
{
    friend class Rva0078E570;
protected:
	virtual ~W3DGameWindow( void );
	void blitBorderRect( Int x, Int y, Int width, Int height );

	// vptr at +0x00; m_textRenderer lands at +0x268.
	unsigned char m_unreconstructed_04[0x268 - 4];
	Render2DSentenceClass m_textRenderer;					///< +0x268
};


// Border image initialization, blitting and the W3DGameWindow destructor
// are provided by the verified W3DDevice/GameClient/GUI/W3DGameWindow.cpp.

// 0x0078E570 is NOT the no-argument ZH W3DGameWindow member. Retail's
// GameWindow::winDrawBorder at 0x00478460 calls slot 0 on GameWindow+4,
// passing the window explicitly. The receiver's constructor at 0x0078D1C0
// installs vtable VA 0x01126DA0; slot 0 -> ILT 0x0002A563 -> this body.
class Rva0078E570 {
public:
    virtual void drawBorder(GameWindow *window);
};

// Reuse the existing address-derived callee's ABI; its semantic name is not
// recovered in the ledger. 0x00478520 tests GameWindow+0x1CC and dispatches
// the pointed-to DisplayString's length query at vslot +0x0C.
class Rva00478520 { public: int call(); };

// The native UnicodeString return-value ABI is required here. Retail calls
// ILT 0x00007E82 -> 0x00479B80, a 30-byte sret getter that reads the string
// at receiver+0x30; GameWindow::winGetText (0x005CB9F0) reads +4 instead, so
// this call is modelled by its own address-derived member on the window.
class Rva00479B80Window { public: UnicodeString rva00479B80(); };
class GameWindowManager;
extern GameWindowManager *TheWindowManager;
class Rva0078E570ManagerSlots {
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot0A();
    virtual void slot0B();
    virtual void slot0C();
    virtual void slot0D();
    virtual void slot0E();
    virtual void slot0F();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot1A();
    virtual void slot1B();
    virtual void slot1C();
    virtual void slot1D();
    virtual void slot1E();
    virtual void slot1F();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot2A();
    virtual void slot2B();
    virtual void slot2C();
    virtual void slot2D();
    virtual void slot2E();
    virtual void slot2F();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot3A();
    virtual void slot3B();
    virtual void slot3C();
    virtual void slot3D();
    virtual void slot3E();
    virtual void slot3F();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void getTextSize(GameFont *, UnicodeString, Int *, Int *, Int);
};

struct Rva0078E570ListData {
    char field00[0xA];
    Bool scrollBar;
    char field0B[0x19];
    GameWindow *slider;
};

void Rva0078E570::drawBorder(GameWindow *window)
{
    Bool found = false;
    Int originalX, originalY;
    Int x, y;
    Int width, height;
    unsigned int i;
    Int bits;
    window->winGetScreenPosition(&originalX, &originalY);
    for (i = 0; i < 32 && found == false; ++i) {
        bits = 1 << i;
        if (window->winGetStyle() & bits) {
            switch (window->winGetStyle() & bits) {
            case 4: // GWS_CHECK_BOX
            case 8: // GWS_HORZ_SLIDER
            case 16: // GWS_VERT_SLIDER
                found = true;
                break;
            case 0x40: { // GWS_ENTRY_FIELD
                window->winGetSize(&width, &height);
                x = originalX;
                y = originalY;
                if (((Rva00478520 *)window)->call()) {
                    Int textWidth = 0;
                    ((Rva0078E570ManagerSlots *)TheWindowManager)->getTextSize(
                        window->winGetFont(), ((Rva00479B80Window *)window)->rva00479B80(), &textWidth, 0, 0);
                    width -= textWidth + 6;
                    x += textWidth + 6;
                }
                ((W3DGameWindow *)this)->blitBorderRect(x, y, width, height);
                found = true;
                break;
            }
            case 0x20: { // GWS_SCROLL_LISTBOX
                Rva0078E570ListData *list = *(Rva0078E570ListData **)((char *)window + 0x2C);
                Int sliderAdjustment = 0;
                Int labelAdjustment = 0;
                if (list->scrollBar) {
                    GameWindow *child = list->slider->winGetChild();
                    struct { Int x, y; } size;
                    child->winGetSize(&size.x, &size.y);
                    sliderAdjustment = size.y;
                }
                if (((Rva00478520 *)window)->call())
                    labelAdjustment = 4;
                window->winGetSize(&width, &height);
                ((W3DGameWindow *)this)->blitBorderRect(originalX - 3,
                    originalY - (3 + labelAdjustment), width + 3 - sliderAdjustment,
                    height + 6);
                found = true;
                break;
            }
            case 1:
            case 2:
            case 0x80:
            case 0x100:
            case 0x200:
            case 0x2000:
                window->winGetSize(&width, &height);
                ((W3DGameWindow *)this)->blitBorderRect(originalX, originalY, width, height);
                found = true;
                break;
            }
        }
    }
}
