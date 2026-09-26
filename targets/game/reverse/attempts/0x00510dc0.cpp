// ?Rva00510DC0@@YAXPAVUnicodeString@@PAVAsciiString@@HEI@Z
// partial score=0.9738 date=2026-09-25
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline
// Tooltip display builder at 0x00510DC0 (382 B). Its only caller is
// Mouse::drawTooltip (0x005A6090) through ILT 0x00033280, which passes the
// tooltip text, font name, size, bold flag and packed ARGB colour. The body
// frees the previous display string through 0x00510C10, builds a new one
// from the font library, measures it and sends "ShowToolTip" with the
// formatted position through WindowManager::_bfme_callAptFunction.
//
// Display-string slots +0x04/+0x18/+0x1C are named from the Zero Hour
// DisplayString vtable (setText/setFont/getFont); +0x10 of the returned
// font is Zero Hour GameFont::height. Every other slot keeps its offset.
#include "StringInline.h"

typedef unsigned int UnsignedInt;
class GameFont;

class Rva00510DC0DisplayView
{
public:
	virtual void slot00();
	virtual void setText(UnicodeString text);
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void setFont(GameFont *font);
	virtual GameFont *getFont();
	virtual void slot20(int value);
	virtual void slot24(int value);
	virtual void slot28(UnsignedInt color, int value);
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C(int *width, int *height);
};

class Rva00510DC0DisplayManager
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual Rva00510DC0DisplayView *slot24();
};

// The global at 0x012F19E8 is the pinned g_theWindowManager; the level
// builder at 0x004675F0 is its pinned _bfme_callAptFunction.
class WindowManager
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24(); virtual float *slot28();

	void *_bfme_callAptFunction(unsigned int level, const char *functionName,
		int argCount, const char *a0, const char *a1, const char *a2,
		const char *a3, const char *a4);
};

class FontLibraryBFMERetail
{
public:
	GameFont *getFont(AsciiString *face, float size, unsigned char style);
};

extern void bfmeGo995B(void);
extern "C" __declspec(dllimport) int __cdecl _snprintf(
	char *, unsigned int, const char *, ...);

extern Rva00510DC0DisplayView *Rva00510DC0Display;
extern Rva00510DC0DisplayManager *Rva00510DC0DisplayManagerGlobal;
extern WindowManager *g_theWindowManager;
extern FontLibraryBFMERetail *Rva00510DC0FontLibraryGlobal;
extern int Rva00510DC0DisplayWidth;
extern int Rva00510DC0DisplayHeight;
extern int g_bfmeVal995B;

void Rva00510DC0(UnicodeString *text, AsciiString *face, int size,
	unsigned char style, unsigned int color)
{
	Rva00510DC0DisplayView *display = Rva00510DC0Display;
	if (display != 0)
		bfmeGo995B();

	float *dimensions = g_theWindowManager->slot28();
	float minScale = (dimensions[0] < dimensions[1]) ? dimensions[0] : dimensions[1];
	GameFont *font = Rva00510DC0FontLibraryGlobal->getFont(
		face, size * minScale, style);
	if (font == 0)
		return;

	display = Rva00510DC0DisplayManagerGlobal->slot24();
	Rva00510DC0Display = display;
	display->setFont(font);
	Rva00510DC0Display->setText(*text);
	Rva00510DC0Display->slot28(color, 0);
	Rva00510DC0Display->slot24(1);
	Rva00510DC0Display->slot20(0xFF);
	Rva00510DC0Display->slot3C(&Rva00510DC0DisplayWidth, &Rva00510DC0DisplayHeight);
	GameFont *actualFont = Rva00510DC0Display->getFont();
	int height = (*((int *)actualFont + 4) + 1) / 3;
	char xText[16];
	char yText[16];
	_snprintf(xText, 16, "%g",
		((float)(Rva00510DC0DisplayWidth + height) / dimensions[0]) *
		0.5f);
	_snprintf(yText, 16, "%g",
		(float)(Rva00510DC0DisplayHeight + height) / dimensions[1]);
	g_theWindowManager->_bfme_callAptFunction(g_bfmeVal995B,
		"ShowToolTip", 2, xText, yText, 0, 0, 0);
}
