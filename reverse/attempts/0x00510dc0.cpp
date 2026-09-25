// ?Rva00510DC0@@YAXPAVUnicodeString@@PAVAsciiString@@HEI@Z
// partial score=0.958115 date=2026-09-25
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Address-derived view of the BFME DisplayString slots used by this routine.
#include "../../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"
#include "../../../../Libraries/Source/WWVegas/WWLib/unicode_string.h"

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
	virtual Rva00510DC0DisplayView *newDisplayString();
};

class Rva00510DC0Dimensions
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24(); virtual float *slot28();
};

class FontLibraryBFMERetail
{
public:
	GameFont *getFont(AsciiString *face, float size, unsigned char style);
};

class BfmeLevelAN
{
public:
	char *bfmeBuildAN(unsigned int level, int p2, int p3, int p4, int p5,
		int p6, int p7, int p8);
};

extern void bfmeGo995B(void);
extern "C" __declspec(dllimport) int __cdecl _snprintf(
	char *, unsigned int, const char *, ...);

extern Rva00510DC0DisplayView *Rva00510DC0Display;
extern Rva00510DC0DisplayManager *Rva00510DC0DisplayManagerGlobal;
extern Rva00510DC0Dimensions *Rva00510DC0DimensionsGlobal;
extern FontLibraryBFMERetail *Rva00510DC0FontLibraryGlobal;
extern int Rva00510DC0DisplayWidth;
extern int Rva00510DC0DisplayHeight;
extern unsigned int Rva00510DC0ActionLevel;

void Rva00510DC0(UnicodeString *text, AsciiString *face, int size,
	unsigned char style, unsigned int color)
{
	Rva00510DC0DisplayView *display = Rva00510DC0Display;
	if (display != 0)
		bfmeGo995B();

	float *dimensions = Rva00510DC0DimensionsGlobal->slot28();
	float minScale = (dimensions[0] < dimensions[1]) ? dimensions[0] : dimensions[1];
	GameFont *font = Rva00510DC0FontLibraryGlobal->getFont(
		face, size * minScale, style);
	if (font == 0)
		return;

	display = Rva00510DC0DisplayManagerGlobal->newDisplayString();
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
	((BfmeLevelAN *)Rva00510DC0DimensionsGlobal)->bfmeBuildAN(
		Rva00510DC0ActionLevel, (int)"ShowToolTip", 2,
		(int)xText, (int)yText, 0, 0, 0);
}
