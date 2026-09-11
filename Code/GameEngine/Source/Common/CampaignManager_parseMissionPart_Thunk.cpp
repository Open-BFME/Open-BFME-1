// cl: /DNDEBUG /MD /EHsc
//
// CampaignManager::parseMissionPart, retail 0x005BCB20, 161 bytes.
// The authoritative CampaignManager source supplies the parser semantics and
// the BFME Mission FieldParse table at 0x0110F778.  The small ABI views keep
// the by-value AsciiString copy visible so VC7.1 reproduces the retail unwind
// state and temporary construction order.

class AsciiString;

extern "C" unsigned int __cdecl strlen(const char *text);
#pragma intrinsic(strlen)

template <typename T>
class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();

	void *m_data;
};

class RetailLayoutString
{
public:
	void set(const char *text, int length);
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}

	void set(const char *text)
	{
		int length = text ? strlen(text) : 0;
		((RetailLayoutString *)this)->set(text, length);
	}
};

struct FieldParse;

class INI
{
public:
	const char *getNextToken(const char *delimiters = 0);
	void initFromINI(void *instance, const FieldParse *table);
};

class Mission {};

class Campaign
{
public:
	Mission *newMission(AsciiString name);
};

class CampaignManager
{
public:
	static void parseMissionPart(INI *ini, void *instance, void *store,
		const void *userData);
};

void CampaignManager::parseMissionPart(INI *ini, void *instance, void *, const void *)
{
	AsciiString name;
	const char *token = ini->getNextToken();
	name.set(token);
	Mission *mission = ((Campaign *)instance)->newMission(name);
	ini->initFromINI(mission, (const FieldParse *)0x0110F778);
}
