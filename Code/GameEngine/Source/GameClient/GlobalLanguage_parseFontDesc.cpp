// cl: /DNDEBUG /MD /EHsc
// readable body of ?parseFontDesc@GlobalLanguage@@: Code/GameEngine/Source/GameClient/GlobalLanguage.cpp
// Open-BFME: GlobalLanguage::parseFontDesc, retail 0x00439150, 136 bytes. The
// body carried no ledger row; its name sat on a 5-byte thunk.
//
// The reference's three lines. The first is what fills the frame: the quoted
// string comes back by value, is assigned into the descriptor through
// StringBase<char>::set, and is released again -- the /EHsc frame is there for
// that temporary. The other two are plain scans, and the descriptor's layout
// falls out of where they land: the name at +0, the size at +4 and the bold
// flag as the byte at +8.

typedef int Int;
typedef bool Bool;

template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	void set(const StringBase<T> &src);			// retail 0x00887C90

private:
	void releaseBuffer();					// retail 0x00887940

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString() { m_string.releaseBuffer(); }

	const AsciiString &operator=(const AsciiString &src) { m_string.set(src.m_string); return *this; }

	StringBase<char> m_string;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/FontDesc.h
struct FontDesc
{
	AsciiString name;					// +0x00
	Int size;						// +0x04
	Bool bold;						// +0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	AsciiString getNextQuotedAsciiString();			// retail 0x00851540
	const char *getNextToken(const char *seps = 0);		// retail 0x00850970

	static Int scanInt(const char *token);			// retail 0x00852620
	static Bool scanBool(const char *token);		// retail 0x00852550
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GlobalLanguage.h
class GlobalLanguage
{
public:
	static void parseFontDesc(INI *ini, void *instance, void *store, const void *userData);
};

void GlobalLanguage::parseFontDesc(INI *ini, void *instance, void *store, const void *userData)
{
	FontDesc *fontDesc = (FontDesc *)store;
	fontDesc->name = ini->getNextQuotedAsciiString();
	fontDesc->size = ini->scanInt(ini->getNextToken());
	fontDesc->bold = ini->scanBool(ini->getNextToken());
}
