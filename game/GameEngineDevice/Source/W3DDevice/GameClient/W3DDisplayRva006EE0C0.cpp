// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// W3DDisplay::rva006EE0C0 (retail 0x006EE0C0, 641 bytes, ret 4).
//
// Identity: W3DDisplay's primary vtable 0x0111EDD0 (installed by the matched
// W3DDisplay constructor/destructor) holds this body in slot 89, so it is a
// virtual W3DDisplay member taking one int; its meaning is not proven, so the
// name keeps the address. The body skips an iconic window, takes the
// W3DRadarResetLock/bfmeUnlock1179 pair around the frame, and either draws the
// window manager alone (mode 3) or the display's image, debug frame text and
// the subtitle broadcast before the transition handler and End_Render.
//
// Layout views are TU-local: only the witnessed slots and offsets are modelled.
// The frame-text DisplayString pointer (0x012F806C) and the clear colour
// (0x012F81AC, guard 0x012F81BC) are referenced by this body alone.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef unsigned char Bool;

#include "ascii_string.h"

extern "C" __declspec(dllimport) int __stdcall IsIconic(void *window);

extern void *ApplicationHWnd;

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() {}
	UnicodeString(const unsigned short *text) : StringBase<unsigned short>(text) {}
	UnicodeString(const UnicodeString &that) : StringBase<unsigned short>(that) {}
	~UnicodeString() {}
	void __cdecl format(UnicodeString fmt, ...);
};

class Vector3
{
public:
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	float X, Y, Z;
};

class WW3D
{
public:
	static bool Begin_Render(bool clear, bool clearz, const Vector3 &color, float dest_alpha = 0.0f, void (*network_callback)(void) = 0);
	static bool End_Render(bool flip_frame = true);
};

void W3DRadarResetLock(void);
char bfmeUnlock1179(void);

// ?Rva006EE0C0RenderLock absent-from-retail
struct Rva006EE0C0RenderLock
{
	Rva006EE0C0RenderLock() { W3DRadarResetLock(); }
	~Rva006EE0C0RenderLock() { bfmeUnlock1179(); }
};

class GameFont;
class Image;

class FontLibrary
{
public:
	GameFont *getFont(AsciiString *name, Real pointSize, Bool bold);
};

extern FontLibrary *TheFontLibrary;
// Retail 0x004772D0 is ?getFont@FontLibraryBFMERetail@@QAEPAVGameFont@@PAVAsciiString@@ME@Z
// (FontLibraryBFMERetail_getFont.cpp); call it by that defined name.
class FontLibraryBFMERetail
{
public:
	GameFont *getFont(AsciiString *name, float pointSize, unsigned char style);
};

#define RVA006EE0C0_SLOT(n) virtual void slot##n(void);

class DisplayString
{
public:
	RVA006EE0C0_SLOT(00)
	virtual void setText(UnicodeString text);
	RVA006EE0C0_SLOT(02) RVA006EE0C0_SLOT(03) RVA006EE0C0_SLOT(04) RVA006EE0C0_SLOT(05)
	virtual void setFont(GameFont *font);
	RVA006EE0C0_SLOT(07) RVA006EE0C0_SLOT(08) RVA006EE0C0_SLOT(09)
	virtual void slot10(Int a, Int b);
	RVA006EE0C0_SLOT(11) RVA006EE0C0_SLOT(12)
	virtual void draw(Int x, Int y);
};

class DisplayStringManager
{
public:
	RVA006EE0C0_SLOT(00) RVA006EE0C0_SLOT(01) RVA006EE0C0_SLOT(02) RVA006EE0C0_SLOT(03)
	RVA006EE0C0_SLOT(04) RVA006EE0C0_SLOT(05) RVA006EE0C0_SLOT(06) RVA006EE0C0_SLOT(07)
	RVA006EE0C0_SLOT(08)
	virtual DisplayString *newDisplayString(void);
};

extern DisplayStringManager *TheDisplayStringManager;

class WindowManager
{
public:
	RVA006EE0C0_SLOT(00) RVA006EE0C0_SLOT(01) RVA006EE0C0_SLOT(02) RVA006EE0C0_SLOT(03)
	RVA006EE0C0_SLOT(04) RVA006EE0C0_SLOT(05) RVA006EE0C0_SLOT(06)
	virtual void slot07(void);
};

extern WindowManager *g_rva012F19E8WindowManager;

class GameWindowTransitionsHandler
{
public:
	RVA006EE0C0_SLOT(00) RVA006EE0C0_SLOT(01) RVA006EE0C0_SLOT(02) RVA006EE0C0_SLOT(03)
	RVA006EE0C0_SLOT(04) RVA006EE0C0_SLOT(05) RVA006EE0C0_SLOT(06)
	virtual void slot07(void);
};

extern GameWindowTransitionsHandler *TheTransitionHandler;

class Rva0081D520Owner
{
public:
	void broadcast(Int value, Real x0, Real y0, Real x1, Real y1);
};

struct Rva006EE0C0Sub
{
	unsigned char m_unmodelled00[0x18];
	Rva0081D520Owner *m_handler;
};

class Rva006EE0C0Source
{
public:
	RVA006EE0C0_SLOT(00) RVA006EE0C0_SLOT(01) RVA006EE0C0_SLOT(02) RVA006EE0C0_SLOT(03)
	RVA006EE0C0_SLOT(04) RVA006EE0C0_SLOT(05) RVA006EE0C0_SLOT(06) RVA006EE0C0_SLOT(07)
	virtual Int query08(void);
	RVA006EE0C0_SLOT(09) RVA006EE0C0_SLOT(10) RVA006EE0C0_SLOT(11) RVA006EE0C0_SLOT(12)
	RVA006EE0C0_SLOT(13) RVA006EE0C0_SLOT(14)
	virtual Image *query15(void);

	unsigned char m_unmodelled04[0x4];
	Rva006EE0C0Sub *m_sub;
};

// The three helper calls go through retail ILTs whose bodies carry these
// ledger names (0x0040F080, 0x0040EE90, 0x0040E1F0).
class BfmeThing923E
{
public:
	void bfmeGo923E(int i, void *b);
};

class Rva0040EE90Owner
{
public:
	void update();
};

class Gen_0040e1f0
{
public:
	void m();
};

// Frame-text toggle read only by this body (byte at 0x012F8068).
Bool g_012F8068 = 0;

class W3DDisplay
{
public:
	RVA006EE0C0_SLOT(00) RVA006EE0C0_SLOT(01) RVA006EE0C0_SLOT(02) RVA006EE0C0_SLOT(03)
	RVA006EE0C0_SLOT(04) RVA006EE0C0_SLOT(05) RVA006EE0C0_SLOT(06) RVA006EE0C0_SLOT(07)
	RVA006EE0C0_SLOT(08) RVA006EE0C0_SLOT(09) RVA006EE0C0_SLOT(10)
	virtual UnsignedInt getWidth(void);
	virtual UnsignedInt getHeight(void);
	RVA006EE0C0_SLOT(13) RVA006EE0C0_SLOT(14) RVA006EE0C0_SLOT(15)
	RVA006EE0C0_SLOT(16) RVA006EE0C0_SLOT(17) RVA006EE0C0_SLOT(18) RVA006EE0C0_SLOT(19)
	RVA006EE0C0_SLOT(20) RVA006EE0C0_SLOT(21) RVA006EE0C0_SLOT(22) RVA006EE0C0_SLOT(23)
	RVA006EE0C0_SLOT(24) RVA006EE0C0_SLOT(25) RVA006EE0C0_SLOT(26) RVA006EE0C0_SLOT(27)
	RVA006EE0C0_SLOT(28) RVA006EE0C0_SLOT(29) RVA006EE0C0_SLOT(30) RVA006EE0C0_SLOT(31)
	RVA006EE0C0_SLOT(32) RVA006EE0C0_SLOT(33) RVA006EE0C0_SLOT(34) RVA006EE0C0_SLOT(35)
	RVA006EE0C0_SLOT(36) RVA006EE0C0_SLOT(37) RVA006EE0C0_SLOT(38) RVA006EE0C0_SLOT(39)
	RVA006EE0C0_SLOT(40) RVA006EE0C0_SLOT(41) RVA006EE0C0_SLOT(42) RVA006EE0C0_SLOT(43)
	RVA006EE0C0_SLOT(44) RVA006EE0C0_SLOT(45) RVA006EE0C0_SLOT(46) RVA006EE0C0_SLOT(47)
	RVA006EE0C0_SLOT(48) RVA006EE0C0_SLOT(49) RVA006EE0C0_SLOT(50) RVA006EE0C0_SLOT(51)
	RVA006EE0C0_SLOT(52) RVA006EE0C0_SLOT(53) RVA006EE0C0_SLOT(54) RVA006EE0C0_SLOT(55)
	virtual void drawImage(Image *image, Real startX, Real startY, Real endX, Real endY, Int color);
	RVA006EE0C0_SLOT(57) RVA006EE0C0_SLOT(58) RVA006EE0C0_SLOT(59)
	RVA006EE0C0_SLOT(60) RVA006EE0C0_SLOT(61) RVA006EE0C0_SLOT(62) RVA006EE0C0_SLOT(63)
	RVA006EE0C0_SLOT(64) RVA006EE0C0_SLOT(65) RVA006EE0C0_SLOT(66) RVA006EE0C0_SLOT(67)
	RVA006EE0C0_SLOT(68) RVA006EE0C0_SLOT(69) RVA006EE0C0_SLOT(70) RVA006EE0C0_SLOT(71)
	RVA006EE0C0_SLOT(72) RVA006EE0C0_SLOT(73) RVA006EE0C0_SLOT(74) RVA006EE0C0_SLOT(75)
	RVA006EE0C0_SLOT(76) RVA006EE0C0_SLOT(77) RVA006EE0C0_SLOT(78) RVA006EE0C0_SLOT(79)
	RVA006EE0C0_SLOT(80) RVA006EE0C0_SLOT(81) RVA006EE0C0_SLOT(82) RVA006EE0C0_SLOT(83)
	RVA006EE0C0_SLOT(84) RVA006EE0C0_SLOT(85) RVA006EE0C0_SLOT(86) RVA006EE0C0_SLOT(87)
	RVA006EE0C0_SLOT(88)
	virtual void rva006EE0C0(Int mode);

private:
	unsigned char m_unmodelled04[0x34 - 0x04];
	Rva006EE0C0Source *m_source;			// +0x34
	unsigned char m_unmodelled38[0xf8 - 0x38];
	Real m_imageStartX;					// +0xF8
	Real m_imageStartY;					// +0xFC
	Real m_imageEndX;					// +0x100
	Real m_imageEndY;					// +0x104
};

#undef RVA006EE0C0_SLOT

// ?rva006EE0C0@W3DDisplay@@UAEXH@Z
void W3DDisplay::rva006EE0C0(Int mode)
{
	static Vector3 clearColor(0.0f, 0.0f, 0.0f);
	static DisplayString *frameText = 0;

	if (ApplicationHWnd && IsIconic(ApplicationHWnd))
		return;

	Rva006EE0C0RenderLock lock;

	if (mode == 3)
	{
		if ((unsigned char)WW3D::Begin_Render(true, false, clearColor) == 1)
		{
			g_rva012F19E8WindowManager->slot07();
			WW3D::End_Render(true);
		}
		return;
	}

	if ((unsigned char)WW3D::Begin_Render(true, false, clearColor) != 1)
		return;

	reinterpret_cast<BfmeThing923E *>(this)->bfmeGo923E(0, (void *)1);
	reinterpret_cast<BfmeThing923E *>(this)->bfmeGo923E(1, (void *)1);
	drawImage(m_source->query15(), m_imageStartX, m_imageStartY, m_imageEndX, m_imageEndY, -1);
	reinterpret_cast<BfmeThing923E *>(this)->bfmeGo923E(2, (void *)1);
	reinterpret_cast<Rva0040EE90Owner *>(this)->update();
	reinterpret_cast<Gen_0040e1f0 *>(this)->m();

	Rva0081D520Owner *handler = m_source->m_sub->m_handler;

	if (g_012F8068)
	{
		if (frameText == 0)
		{
			frameText = TheDisplayStringManager->newDisplayString();
			{
				AsciiString fontName("FixedSys");
				frameText->setFont(reinterpret_cast<FontLibraryBFMERetail *>(TheFontLibrary)->getFont(&fontName, 12.0f, 0));
			}
			frameText->slot10(-1, 0);
		}

		UnicodeString text;
		text.format(UnicodeString(L"Frame %d"), m_source->query08());
		frameText->setText(text);
		frameText->draw(40, 40);
	}

	if (handler)
		handler->broadcast(m_source->query08(), 0.0f, 0.0f, (Real)getWidth(), (Real)getHeight());

	TheTransitionHandler->slot07();
	WW3D::End_Render(true);
}
