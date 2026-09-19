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

class AsciiString;
class GameFont;

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

class FontLibraryBFMERetail
{
public:
	GameFont *getFont(AsciiString *name, Real size, unsigned char style);

private:
	BfmeFontRecord *bfmeFindRecord(AsciiString *name, Real size);
	GameFont *bfmeBuildFont(AsciiString *name, Real size, unsigned char style,
			Int weight);

	unsigned char m_padding[0x10];
	BfmeFontTable m_tables;
};

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
