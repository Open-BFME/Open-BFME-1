// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Lift the HeaderTemplateManager::populateGameFonts __emit thunk to clean C++.
//
// Verbatim Zero Hour HeaderTemplate.cpp: walk the header-template list and give
// each entry the font its name, adjusted point size and bold flag select. The
// DEBUG_ASSERTCRASH between the two compiles away in release.
//
// Retail pins what ZH leaves symbolic: the list header is at this+0x00 with
// nodes linking through +0x00 and holding their element at +0x08, and a
// HeaderTemplate keeps m_font at +0x00, m_fontName at +0x08, m_point at +0x0C
// and m_bold at +0x10. adjustFontSize returns an Int here, which is why the
// point size goes through fild/fstp before being passed as a Real.

typedef int Int;
typedef float Real;
typedef unsigned char Bool;

class GameFont;

// Embedded by value in HeaderTemplate: retail passes its address with
// lea eax,[esi+8], not the stored word, so this cannot be a pointer field.
class AsciiString
{
private:
	void *m_data;
};

class HeaderTemplate
{
public:
	GameFont *m_font;										///< retail this+0x00
	unsigned char m_unreconstructed_04[4];
	AsciiString m_fontName;								///< retail this+0x08
	Int m_point;											///< retail this+0x0C
	Bool m_bold;											///< retail this+0x10
};

struct HeaderTemplateNode
{
	HeaderTemplateNode *m_next;								///< retail this+0x00
	unsigned char m_unreconstructed_04[4];
	HeaderTemplate *m_template;								///< retail this+0x08
};

class GlobalLanguageData
{
public:
	Int adjustFontSize(Int point);							///< ILT thunk at 0x00004E67
};

class FontLibrary
{
public:
	GameFont *getFont(AsciiString *name, Real pointSize, Bool bold);	///< ILT thunk at 0x0000ABC3
};

extern GlobalLanguageData *TheGlobalLanguageData;			///< retail [0x012F1484]
extern FontLibrary *TheFontLibrary;							///< retail [0x012F1B38]

class HeaderTemplateManager
{
	void populateGameFonts(void);

	HeaderTemplateNode *m_headerTemplateList;				///< retail this+0x00
};

// ?populateGameFonts@HeaderTemplateManager@@AAEXXZ
void HeaderTemplateManager::populateGameFonts(void)
{
	HeaderTemplateNode *it = m_headerTemplateList->m_next;
	while (it != m_headerTemplateList)
	{
		HeaderTemplate *hTemplate = it->m_template;
		Real pointSize = (Real)TheGlobalLanguageData->adjustFontSize(hTemplate->m_point);
		GameFont *font = TheFontLibrary->getFont(&hTemplate->m_fontName, pointSize, hTemplate->m_bold);

		hTemplate->m_font = font;

		it = it->m_next;
	}
}
