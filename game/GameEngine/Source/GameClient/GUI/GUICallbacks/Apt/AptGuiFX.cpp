// ShowToolTip helper; Mouse::drawTooltip reaches this body through ILT 0x00033280.
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/stringinline
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

class DisplayStringManager
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
	virtual Rva00510DC0DisplayView *newDisplayString();
};

// The pinned global is g_theWindowManager; its 0x004675F0 builder is a member
// of the level-path builder class.  BfmeLevelAN is this TU's view of the
// pointee, as in BfmeConv924.cpp.
class WindowManager
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24(); virtual float *slot28();
};

class BfmeLevelAN
{
public:
	char *bfmeBuildAN(unsigned int level, int p2, int p3, int p4, int p5, int p6,
		int p7, int p8);
};

// Retail global 0x012F1B38 is defined as `FontLibrary *TheFontLibrary`
// (?TheFontLibrary@@3PAVFontLibrary@@A); this TU's view of the pointee needs
// the class spelled FontLibrary (a class, not a struct) for that mangling.
class FontLibrary
{
public:
	GameFont *getFont(AsciiString *face, float size, unsigned char style);
};


extern void bfmeGo995B(void);
extern "C" __declspec(dllimport) int __cdecl _snprintf(
	char *, unsigned int, const char *, ...);

extern Rva00510DC0DisplayView *Rva00510DC0Display;
extern DisplayStringManager *TheDisplayStringManager;
extern WindowManager *g_theWindowManager;
extern FontLibrary *TheFontLibrary;
extern int Rva00510DC0DisplayWidth;
extern int Rva00510DC0DisplayHeight;
extern int g_bfmeVal995B;

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
void Rva00510DC0(UnicodeString *text, AsciiString *face, int size,
	unsigned char style, unsigned int color)
{
	Rva00510DC0DisplayView *display = Rva00510DC0Display;
	if (display != 0)
		bfmeGo995B();

	float *dimensions = g_theWindowManager->slot28();
	float minScale = (dimensions[0] < dimensions[1]) ? dimensions[0] : dimensions[1];
	float scaledSize = size * minScale;
	_ReadWriteBarrier();
	GameFont *font = TheFontLibrary->getFont(
		face, scaledSize, style);
	if (font == 0)
		return;

	display = TheDisplayStringManager->newDisplayString();
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
	char *xTextArg = xText;
	char *yTextArg = yText;
	_ReadWriteBarrier();
	((BfmeLevelAN *)g_theWindowManager)->bfmeBuildAN((unsigned int)g_bfmeVal995B,
		(int)"ShowToolTip", 2, (int)xTextArg, (int)yTextArg, 0, 0, 0);
}
