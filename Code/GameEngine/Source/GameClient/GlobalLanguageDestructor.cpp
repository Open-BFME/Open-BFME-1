// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
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

template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	void set(const StringBase<T> &source);

private:
	StringBase() {}
	StringBase(const T *text);
	void releaseBuffer();
	char *m_data;
};

class AsciiString
{
public:
	AsciiString() { m_string.m_data = 0; }
	AsciiString(const char *text) : m_string(text) {}
	~AsciiString() { m_string.releaseBuffer(); }

private:
	StringBase<char> m_string;
};

struct BfmeFontEntry
{
	void *unmodelled;
	AsciiString value;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GlobalLanguage.h
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
	FontDesc m_font00;
	FontDesc m_font01;
	FontDesc m_font02;
	FontDesc m_font03;
	FontDesc m_font04;
	FontDesc m_font05;
	FontDesc m_font06;
	FontDesc m_font07;
	FontDesc m_font08;
	FontDesc m_font09;
	FontDesc m_font10;
	FontDesc m_font11;
	FontDesc m_font12;
	FontDesc m_font13;
	FontDesc m_font14;
	FontDesc m_font15;
	FontDesc m_font16;
	FontDesc m_font17;
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
