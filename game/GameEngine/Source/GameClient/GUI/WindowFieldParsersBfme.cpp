// cl: /DNDEBUG /MD /EHs-c-
// Window-file field parsers named by the gameWindowFieldList table in .data
// (0x00EB5AE0..): TOOLTIPCALLBACK (retail 0x004869B0), TEXT (0x00485E30)
// and BFME's HEADERTEMPLATE (0x00485CE0).  Same quoted-string skeleton as the
// landed parseDrawCallback (0x00486A60) and the ZH GameWindowManagerScript
// parsers: skip to the opening quote, strtok to the closing one, store the
// text.  The member stores go through AsciiString's inline operator=, which
// is why retail forms the member address before the null test.

typedef int Int;
typedef bool Bool;

extern "C" __declspec(dllimport) char *__cdecl strtok(char *string, const char *separators);
extern "C" unsigned int __cdecl strlen(const char *string);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	void set(const char *string, Int length);

	void set(const char *s)
	{
		set(s, s ? (Int)strlen(s) : 0);
	}

	AsciiString &operator=(const char *s)
	{
		set(s, s ? (Int)strlen(s) : 0);
		return *this;
	}

	const char *str(void) const
	{
		return m_data ? (const char *)((unsigned char *)m_data + 8) : "";
	}

	void *m_data;
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class GameWindow;
class WinInstanceData;
typedef void (__cdecl *GameWinDrawFunc)(GameWindow *, WinInstanceData *);

class GameWindow;
class WinInstanceData;
typedef void (__cdecl *GameWinTooltipFunc)(GameWindow *, WinInstanceData *, unsigned int);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/FunctionLexicon.h
class FunctionLexicon
{
public:
	enum TableIndex
	{
		TABLE_ANY = -1,
		TABLE_GAME_WIN_SYSTEM = 0,
		TABLE_GAME_WIN_INPUT,
		TABLE_GAME_WIN_TOOLTIP
	};

	GameWinTooltipFunc gameWinTooltipFunc(NameKeyType key, TableIndex index = TABLE_GAME_WIN_TOOLTIP)
	{
		return (GameWinTooltipFunc)findFunction(key, index);
	}

protected:
	void *findFunction(NameKeyType key, TableIndex index);
};

extern AsciiString theTooltipString;
extern NameKeyGenerator *TheNameKeyGenerator;
extern FunctionLexicon *TheFunctionLexicon;
extern GameWinTooltipFunc tooltipFunc;

// ?parseTooltipCallback@@YA_NPADPAVWinInstanceData@@0PAX@Z
Bool parseTooltipCallback(char *token, WinInstanceData *instData, char *buffer, void *data)
{
	char *c, *ptr;
	char *stringSeps = "\"";

	ptr = buffer;
	while (*ptr != '"')
		ptr++;
	ptr++;
	c = strtok(ptr, stringSeps);

	theTooltipString.set(c, c ? (Int)strlen(c) : 0);
	NameKeyType key = TheNameKeyGenerator->nameToKey(theTooltipString.str());
	tooltipFunc = TheFunctionLexicon->gameWinTooltipFunc(key);

	return true;
}

// BFME adds the HEADERTEMPLATE field; the name lands in the instance data at
// +0x194.
class UnicodeString
{
public:
	~UnicodeString();

	void *m_data;
};

class GameTextInterface
{
public:
	virtual void unused00() = 0;
	virtual void unused04() = 0;
	virtual void unused08() = 0;
	virtual void unused0c() = 0;
	virtual void unused10() = 0;
	virtual void unused14() = 0;
	virtual void unused18() = 0;
	virtual void unused1c() = 0;
	virtual void unused20() = 0;
	virtual void unused24() = 0;
	virtual UnicodeString fetch(const char *label, Bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

enum
{
	MAX_TEXT_LABEL = 128
};

class WinInstanceData
{
public:
	void setTooltipText(UnicodeString tip);

	unsigned char m_unreconstructed000[0x188];
	AsciiString m_textLabelString;
	unsigned char m_unreconstructed18C[4];
	AsciiString m_tooltipString;
	AsciiString m_headerTemplateName;
};

// ?parseText@@YA_NPADPAVWinInstanceData@@0PAX@Z -- TEXT, retail 0x00485E30
// ?parseText@@YA_NPADPAVWinInstanceData@@0PAX@Z present-unmatched
Bool parseText(char *token, WinInstanceData *instData, char *buffer, void *data)
{
	char *ptr = buffer;
	char *c;
	char *stringSeps = "\n\r\t\"";

	// scan to the first " mark
	while (*ptr != '"')
		ptr++;
	ptr++;  // skip the "
	c = strtok(ptr, stringSeps);  // value
	if (strlen(c) >= MAX_TEXT_LABEL)
		return false;
	instData->m_textLabelString = c;

	return true;
}


// ?parseHeaderTemplate@@YA_NPADPAVWinInstanceData@@0PAX@Z
// ?parseHeaderTemplate@@YA_NPADPAVWinInstanceData@@0PAX@Z present-unmatched
Bool parseHeaderTemplate(char *token, WinInstanceData *instData, char *buffer, void *data)
{
	char *c, *ptr;
	char *stringSeps = "\"";

	ptr = buffer;
	while (*ptr != '"')
		ptr++;
	ptr++;
	c = strtok(ptr, stringSeps);

	instData->m_headerTemplateName = c;

	return true;
}
