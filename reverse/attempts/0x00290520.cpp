// ?d_00290520@@YAXXZ
// partial score=0.99 date=2026-09-15
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <vector>

template <typename T>
class StringBase
{
	friend class AsciiString;
	friend class BfmeEmotionName;

public:
	void set(const StringBase<T> &source);

private:
	StringBase(const T *text);
	void releaseBuffer();
	void *m_data;
};

class AsciiString
{
public:
	AsciiString(const char *text)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(text);
	}
	~AsciiString()
	{
		((StringBase<char> *)this)->StringBase<char>::releaseBuffer();
	}

private:
	void *m_data;
};

class BfmeEmotionName : private StringBase<char>
{
public:
	BfmeEmotionName(const char *text) : StringBase<char>(text) {}
	~BfmeEmotionName()
	{
		((StringBase<char> *)this)->StringBase<char>::releaseBuffer();
	}
};

class INI
{
public:
	const char *getNextToken(const char *separators = 0);
};

class INIException
{
public:
	INIException(int, const char *, ...);
	INIException(const INIException &);

	char *m_failureMessage;
};

class EmotionNugget
{
public:
	EmotionNugget();

private:
	AsciiString m_name;
	int m_04;
	unsigned char m_08;
	unsigned char m_09;
	unsigned char m_pad0A[2];
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_20;
	int m_24;
	int m_28;
	unsigned char m_2C;
	unsigned char m_2D;
	unsigned char m_pad2E[2];
	int m_30;
	int m_34;
	int m_38;
	AsciiString m_3C;
	int m_40;
	unsigned char m_44;
	unsigned char m_pad45[3];
	int m_48;
	int m_4C;
	int m_50;
	unsigned int m_54[20];
	unsigned int m_A4[20];
	AsciiString m_F4;
};

class EmotionSystem
{
public:
	EmotionNugget *findNugget(const BfmeEmotionName &name);
};

extern EmotionSystem *TheEmotionSystem;
extern void *(__cdecl *g_lookup)(void *, void *);

class BfmeThingVKC
{
public:
	void bfmeCopyVKC(const BfmeThingVKC &source);
};

class BfmeOtherDCE;

class BfmeThingDCE
{
public:
	void bfmeGoDCE(BfmeOtherDCE *other);
};

typedef BfmeThingVKC EmotionTrackerUpdateEntry;

class EmotionTrackerUpdateModuleData
{
public:
	unsigned char m_unknown00[0x30];
	std::vector<EmotionTrackerUpdateEntry *> m_entries;
};

// ?Rva00290520@@YAXPAVINI@@PAX1PBX@Z
void Rva00290520(INI *ini, void *, void *, const void *userData)
{
	const char *token = ini->getNextToken();
	bool hasAdditionalData = false;

	if (token != 0)
	{
		if (!g_lookup((void *)token, (void *)0x010BE338))
		{
			hasAdditionalData = true;
			token = ini->getNextToken();
		}
	}

	if (token == 0)
		throw INIException(3, (const char *)0x010BE2F8);

	EmotionNugget *nugget = 0;
	{
		BfmeEmotionName name(token);
		nugget = TheEmotionSystem->findNugget(name);
	}

	if (nugget == 0)
		throw INIException(3, (const char *)0x010BE2E0);

	EmotionTrackerUpdateEntry *entry =
		(EmotionTrackerUpdateEntry *)new EmotionNugget;
	entry->bfmeCopyVKC(*(const BfmeThingVKC *)nugget);
	{
		BfmeEmotionName name(token);
		((StringBase<char> *)entry)->set(*(const StringBase<char> *)&name);
	}

	if (hasAdditionalData)
		((BfmeThingDCE *)entry)->bfmeGoDCE((BfmeOtherDCE *)ini);

	((EmotionTrackerUpdateModuleData *)userData)->m_entries.push_back(entry);
}
