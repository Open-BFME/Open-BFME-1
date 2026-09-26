// cl: /DNDEBUG /MD /EHsc
// CreditsManager::load, retail0x0040C310/224B. INI load takes filename,
// loadType, Xfer pointer and parser callback. Retail callback thunk1F2A3
// dispatches to the matched INI::parseCredits body40BFC0.

typedef int Int;
typedef float Real;
typedef unsigned char Bool;

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	struct Data
	{
		Int m_refCount;
		unsigned short m_length;
		unsigned short m_capacity;
		T m_text[1];
	};
	Data *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};

class Xfer;

class INI
{
public:
	INI();
	~INI();
	void load(AsciiString filename, int loadType, Xfer *xfer, void (__cdecl *parser)(INI *));
 static void __cdecl parseCredits(INI *);

private:
	char m_storage[0x848];
};

struct FontDesc
{
	AsciiString name;
	Int size;
	Bool bold;
};

class GameFont
{
public:
	unsigned char m_pad[0x10];
	Int height;
};

class GlobalLanguage
{
public:
	Int adjustFontSize(Int theFontSize);
	unsigned char m_pad[0xF4];
	FontDesc m_creditsNormalFont;
};

class FontLibrary
{
public:
	GameFont *getFont(AsciiString *name, Real pointSize, Bool bold);
};

extern GlobalLanguage *TheGlobalLanguageData;
extern FontLibrary *TheFontLibrary;

class CreditsManager
{
public:
	bool load();

	unsigned char m_pad00[0x14];
	Int m_scrollRate;
	Int m_scrollRatePerFrames;
	unsigned char m_pad1C[0x1C];
	Int m_normalFontHeight;
};

// ?load@CreditsManager@@QAE_NXZ
bool CreditsManager::load()
{
	INI ini;
	ini.load(AsciiString("Data\\INI\\Credits.ini"), 1, 0, &INI::parseCredits);

	if (m_scrollRatePerFrames <= 0)
		m_scrollRatePerFrames = 1;
	if (m_scrollRate <= 0)
		m_scrollRate = 1;

	GameFont *font = TheFontLibrary->getFont(
		&TheGlobalLanguageData->m_creditsNormalFont.name,
		(Real)TheGlobalLanguageData->adjustFontSize(
			TheGlobalLanguageData->m_creditsNormalFont.size),
		TheGlobalLanguageData->m_creditsNormalFont.bold);

	m_normalFontHeight = font->height;
	return true;
}
