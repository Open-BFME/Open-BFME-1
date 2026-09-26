// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/asciistring_downloadmanager /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// FontLibraryBFMERetail::rva00476C50, retail 0x00476C50, 361 bytes.
//
// Identity: the matched FontLibraryBFMERetail::getFont at 0x004772D0
// (FontLibraryBFMERetail_getFont.cpp) tail-returns this body through ILT
// 0x0000EBA6, which targets/game/reverse/symbols.csv pins under this name.  The body
// installs the GameFont vtable 0x010F7628 and walks the font list at this+8.
// That proves the owner and signature, not the method name, so the name keeps
// its address token.
//
// The size is snapped to the weight grid (floor(weight * size + k) / weight),
// the name, size and style go through the substitution table at 0x00476B00,
// and the font list is searched for an exact match.  Failing that a new
// GameFont is built, loaded through vtable slot +0x24 and linked at the head.
//
// Shape: the search compares the adjusted style parameter itself; the new
// font takes a copy made after the search.  That copy is what lets VC7.1 load
// the style once into BL ahead of the empty-list test and keep the weight in
// EBP for both the loop and the new font.

#include "PreRTS.h"
#include "Common/AsciiString.h"

typedef int Int;
typedef float Real;

extern "C" __declspec(dllimport) double BfmeFloorER(double value);
extern const Real g_bfmeK1253;

class GameFont
{
public:
	GameFont() {}
	void deleteInstance() { delete this; }

	GameFont *next;
	AsciiString nameString;
	Real pointSize;
	unsigned char m_padding10[4];
	void *fontData;
	unsigned char bold;
	unsigned char m_padding19[3];
	Int m_extra_setting;

protected:
	virtual ~GameFont();
};

struct BfmeFontRecord;

class BfmeFontLibraryBaseView
{
public:
	virtual ~BfmeFontLibraryBaseView();
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;

	AsciiString m_name;
};

// The substitution lookup at 0x00476B00 (FontLibraryBFMEAdjustFont.cpp).  Its
// owner is still address-named; this body calls it on its own this pointer.
class Rva00476B00FontLibrary
{
public:
	void adjustFont(AsciiString *name, Real *size, unsigned char *style);
};

class FontLibraryBFMERetail : public BfmeFontLibraryBaseView
{
public:
	GameFont *getFont(AsciiString *name, Real size, unsigned char style);

private:
	virtual Bool loadFontData(GameFont *font) = 0;
	virtual void releaseFontData(GameFont *font) = 0;

	BfmeFontRecord *bfmeFindRecord(AsciiString *name, Real size);
	GameFont *rva00476C50(AsciiString *name, Real size, unsigned char style,
			Int weight);

	GameFont *m_fontList;
	Int m_count;
};

// ?rva00476C50@FontLibraryBFMERetail@@AAEPAVGameFont@@PAVAsciiString@@MEH@Z
GameFont *FontLibraryBFMERetail::rva00476C50(AsciiString *name, Real size,
		unsigned char style, Int weight)
{
	size = (Real)BfmeFloorER((Real)weight * size + g_bfmeK1253)
		/ (Real)weight;
	AsciiString fontName(*name);

	((Rva00476B00FontLibrary *)this)->adjustFont(&fontName, &size, &style);

	GameFont *font;
	for (font = m_fontList; font != NULL; font = font->next)
	{
		if (font->pointSize == size && font->bold == style &&
				font->m_extra_setting == weight && font->nameString.compare(fontName) == 0)
			return font;
	}

	unsigned char styleValue = style;

	font = new GameFont;
	if (font == NULL)
		return NULL;

	font->nameString = fontName;
	font->pointSize = size;
	font->bold = styleValue;
	font->fontData = NULL;
	font->m_extra_setting = weight;

	if (!loadFontData(font))
	{
		font->deleteInstance();
		return NULL;
	}

	font->next = m_fontList;
	m_fontList = font;
	++m_count;
	return font;
}
