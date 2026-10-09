// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#include <list>

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();

private:
	unsigned int m_name;
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data(0) {}
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString() { releaseBuffer(); }

	void clear() { releaseBuffer(); }
	void releaseBuffer();

private:
	void *m_data;
};

class BfmeLiteralString : public BFMERetailAsciiString
{
public:
	BfmeLiteralString(const char *text) : BFMERetailAsciiString(text) {}
};

struct FontDesc
{
	FontDesc();
	BFMERetailAsciiString name;
	int size;
	unsigned char bold;
};

#include "string_base.h"

#include "ascii_string.h"

struct BfmeFontEntry
{
	void *unmodelled;
	AsciiString value;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GlobalLanguage.h
// BFME added m_period/m_comma/m_colon/m_language and five more FontDesc slots over the
// ZH original; field names past the recovered ones are TU-local placeholders, matching
// GlobalLanguageConstructor.cpp's layout for the same class.
class GlobalLanguage : public SubsystemInterface
{
public:
	virtual ~GlobalLanguage();

private:
	BfmeLiteralString m_period;
	BfmeLiteralString m_comma;
	BfmeLiteralString m_colon;
	BFMERetailAsciiString m_unicodeFontName;
	BFMERetailAsciiString m_unicodeFontFileName;
	BFMERetailAsciiString m_language;
	unsigned char m_useHardWrap;
	int m_militaryCaptionSpeed;
	FontDesc m_copyrightFont;
	FontDesc m_messageFont;
	FontDesc m_militaryCaptionTitleFont;
	FontDesc m_militaryCaptionFont;
	FontDesc m_font04;
	FontDesc m_superweaponCountdownNormalFont;
	FontDesc m_superweaponCountdownReadyFont;
	FontDesc m_namedTimerCountdownNormalFont;
	FontDesc m_namedTimerCountdownReadyFont;
	FontDesc m_drawableCaptionFont;
	FontDesc m_defaultWindowFont;
	FontDesc m_defaultDisplayStringFont;
	FontDesc m_tooltipFontName;
	FontDesc m_nativeDebugDisplay;
	FontDesc m_drawGroupInfoFont;
	FontDesc m_creditsTitleFont;
	FontDesc m_creditsPositionFont;
	FontDesc m_creditsNormalFont;
	FontDesc m_font18;
	FontDesc m_font19;
	FontDesc m_font20;
	FontDesc m_font21;
	float m_resolutionFontSizeAdjustment;
	std::list<BfmeFontEntry> m_localFonts;
};

// ??1GlobalLanguage@@UAE@XZ
GlobalLanguage::~GlobalLanguage()
{
}
