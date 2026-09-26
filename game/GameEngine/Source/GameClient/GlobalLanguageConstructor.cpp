// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

namespace _STL
{
class __new_alloc
{
public:
	static void *allocate(unsigned int size);
};
}

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

class HeaderTemplateString
{
	public:
	HeaderTemplateString();
	HeaderTemplateString(const HeaderTemplateString &other);
	~HeaderTemplateString();

private:
	void *m_text;
};

// ?HeaderTemplateGetRegistryLanguage@@YA?AVHeaderTemplateString@@XZ => jmp ?GetRegistryLanguage@@YA?AVAsciiString@@XZ
HeaderTemplateString HeaderTemplateGetRegistryLanguage();

struct BfmeFontListNode
{
	BfmeFontListNode *next;
	BfmeFontListNode *prev;
};

class BfmeFontList
{
public:
	__forceinline BfmeFontList()
	{
		m_node = 0;
		BfmeFontListNode *node = (BfmeFontListNode *)_STL::__new_alloc::allocate(0x10);
		node->next = node;
		node->prev = node;
		m_node = node;
	}
	~BfmeFontList();

private:
	BfmeFontListNode *m_node;
};

class GlobalLanguage : public SubsystemInterface
{
public:
	GlobalLanguage();
	virtual ~GlobalLanguage();

private:
	BfmeLiteralString m_period;
	BfmeLiteralString m_comma;
	BfmeLiteralString m_colon;
	BFMERetailAsciiString m_unicodeFontName;
	BFMERetailAsciiString m_unicodeFontFileName;
	HeaderTemplateString m_language;
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
	BfmeFontList m_localFonts;
};

// ??0GlobalLanguage@@QAE@XZ
GlobalLanguage::GlobalLanguage()
	: SubsystemInterface()
	, m_period(".")
	, m_comma(",")
	, m_colon(":")
	, m_unicodeFontName()
	, m_unicodeFontFileName()
	, m_language(HeaderTemplateGetRegistryLanguage())
	, m_useHardWrap(0)
	, m_militaryCaptionSpeed(0)
	, m_resolutionFontSizeAdjustment(0.7f)
	, m_localFonts()
{
	m_unicodeFontName.clear();
	m_unicodeFontFileName.clear();
	m_unicodeFontName.clear();
}
