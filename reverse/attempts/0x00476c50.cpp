// ?bfmeBuildFont@FontLibraryBFMERetail@@AAEPAVGameFont@@PAVAsciiString@@MEH@Z
// partial score=0.96 date=2026-09-09
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/asciistring_downloadmanager /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport

// Open-BFME5: FontLibraryBFMERetail::getFont, retail 0x004772D0, 60 bytes. The
// body carried only a machine byte-dump row; the symbols.csv pin names it as
// the BFME retail FontLibrary ABI alias.
//
// The name and size go first to the record lookup. A record, if there is one,
// supplies the byte at +8; without one the byte stands at 1. That byte only
// decides between two weights, four and one, which the compiler produces
// without a branch: negate to set carry, subtract with borrow into itself, mask
// to three and add one.
//
// Both helpers are pinned with this body, at the ILTs the two calls use.

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
	unsigned char style;
	unsigned char m_padding19[3];
	Int weight;

protected:
	virtual ~GameFont();
};

struct BfmeFontRecord
{
	unsigned char m_bfmeHead[0x08];
	unsigned char m_bfmeWeighted;				// +0x08
};

typedef _STL::map<Int, UnsignedInt> BfmeFontSizeMap;

struct BfmeFontSizeTable
{
	unsigned char m_padding[0x08];
	BfmeFontRecord *m_defaultRecord;
	BfmeFontSizeMap m_records;
};

typedef _STL::map<AsciiString, BfmeFontSizeTable *> BfmeFontTable;

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

class FontLibraryBFMERetail : public BfmeFontLibraryBaseView
{
public:
	GameFont *getFont(AsciiString *name, Real size, unsigned char style);
	GameFont *firstFont() { return m_fontList; }

private:
	virtual Bool loadFontData(GameFont *font) = 0;
	virtual void releaseFontData(GameFont *font) = 0;

	BfmeFontRecord *bfmeFindRecord(AsciiString *name, Real size);
	GameFont *bfmeBuildFont(AsciiString *name, Real size, unsigned char style,
			Int weight);

	GameFont *m_fontList;
	Int m_count;
	BfmeFontTable m_tables;
};

extern void j_00001ed3();

// ?getFont@FontLibraryBFMERetail@@QAEPAVGameFont@@PAVAsciiString@@ME@Z
GameFont *FontLibraryBFMERetail::getFont(AsciiString *name, Real size,
		unsigned char style)
{
	unsigned char weighted = 1;

	BfmeFontRecord *record = bfmeFindRecord(name, size);

	if (record)
		weighted = record->m_bfmeWeighted;

	return bfmeBuildFont(name, size, style, weighted ? 4 : 1);
}

BfmeFontRecord *FontLibraryBFMERetail::bfmeFindRecord(AsciiString *name,
		Real size)
{
	BfmeFontTable::iterator table;
	table = m_tables.find(*name);
	if (table == m_tables.end())
		return NULL;

	int sizeKey = (int)size;
	BfmeFontSizeTable *sizes = table->second;
	BfmeFontSizeMap::iterator record = sizes->m_records.find(sizeKey);
	if (record == sizes->m_records.end())
		return sizes->m_defaultRecord;
	return (BfmeFontRecord *)record->second;
}

// ?bfmeBuildFont@FontLibraryBFMERetail@@AAEPAVGameFont@@PAVAsciiString@@MEH@Z
GameFont *FontLibraryBFMERetail::bfmeBuildFont(AsciiString *name, Real size,
		unsigned char style, Int weight)
{
	size = (Real)BfmeFloorER((Real)weight * size + g_bfmeK1253)
		/ (Real)weight;
	AsciiString fontName(*name);

	typedef void (FontLibraryBFMERetail::*AdjustFont)(AsciiString *, Real *,
		unsigned char *);
	union
	{
		void (*function)(void);
		AdjustFont member;
	} thunk;
	thunk.function = j_00001ed3;
	(this->*thunk.member)(&fontName, &size, &style);

	GameFont *font;
	for (font = m_fontList; font != NULL; font = font->next)
	{
		if (font->pointSize == size && font->style == style &&
				font->weight == weight && font->nameString.compare(fontName) == 0)
			return font;
	}

	makeFont:
	font = new GameFont;
	if (font == NULL)
		return NULL;

	font->nameString = fontName;
	font->pointSize = size;
	font->style = style;
	font->fontData = NULL;
	font->weight = weight;

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
