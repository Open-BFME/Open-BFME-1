// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// W3DDisplayStringManager::newDisplayString, retail RVA 0x006F5A90, 269 bytes
// (plain ret). W3DDisplayStringManager's vtable at VA 0x0111FF40 holds its ILT
// 0x00038A32, where tools/ilt_oracle.py CONFIRMS
// ?newDisplayString@W3DDisplayStringManager@@UAEPAVDisplayString@@XZ; it
// follows the matched ??_GW3DDisplayStringManager at 0x006F5A60.
// Zero Hour's body (W3DDisplayStringManager.cpp, whose ZH-header compile keeps a
// present-unmatched copy: ZH's W3DDisplayString is 0x1D8 bytes, BFME's 0x210,
// and BFME's FontLibrary::getFont takes the name by reference and a Real size).

#include "ascii_string.h"

// Retail inlines the emptiness test here: the buffer pointer, then its 16-bit
// length (cmp word ptr [data+4],0); string_base.h declares both out of line.
template <> inline bool StringBase<char>::isEmpty() const
{
	return m_data == 0 || m_data->length == 0;
}
template <> inline bool StringBase<char>::isNotEmpty() const
{
	return !isEmpty();
}

#include "../../../../GameEngine/Include/Common/ScalarTypes/Real.h"
typedef unsigned char Bool;

class GameFont;

class FontLibrary
{
public:
	GameFont *getFont(AsciiString *name, Real pointSize, Bool bold);
};
extern FontLibrary *TheFontLibrary;

struct FontDesc
{
	AsciiString name;		// +0x00
	int size;				// +0x04
	Bool bold;				// +0x08
};

class GlobalLanguage
{
public:
	unsigned char m_unmodelled_000[0xAC];
	FontDesc m_defaultDisplayStringFont;	// +0xAC
};
extern GlobalLanguage *TheGlobalLanguageData;

class DisplayString
{
public:
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14();
	virtual void setFont(GameFont *font);
};

class W3DDisplayString : public DisplayString
{
public:
	W3DDisplayString();
private:
	unsigned char m_unmodelled_004[0x210 - 4];
};

class DisplayStringManager
{
public:
	virtual DisplayString *newDisplayString();
protected:
	void link(DisplayString *string);
};

class W3DDisplayStringManager : public DisplayStringManager
{
public:
	virtual DisplayString *newDisplayString();
};

// ?newDisplayString@W3DDisplayStringManager@@UAEPAVDisplayString@@XZ
DisplayString *W3DDisplayStringManager::newDisplayString()
{
	DisplayString *newString = new W3DDisplayString;

	// sanity
	if (newString == 0)
		return 0;

	// assign a default font
	if (TheGlobalLanguageData && TheGlobalLanguageData->m_defaultDisplayStringFont.name.isNotEmpty())
	{
		newString->setFont(TheFontLibrary->getFont(
			&TheGlobalLanguageData->m_defaultDisplayStringFont.name,
			TheGlobalLanguageData->m_defaultDisplayStringFont.size,
			TheGlobalLanguageData->m_defaultDisplayStringFont.bold));
	}
	else
	{
		AsciiString defaultName("Times New Roman");
		newString->setFont(TheFontLibrary->getFont(&defaultName, 12, false));
	}

	// link string to list
	link(newString);

	// return our new string
	return newString;
}
