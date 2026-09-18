// ?d_00290520@@YAXXZ
// partial score=0.99 date=2026-09-15
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <vector>

template <typename T>
class StringBase
{
	friend class AsciiString;

public:
	void set(const StringBase<T> &source);

private:
	StringBase(const T *text);
	void releaseBuffer();
	void *m_data;
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString(const char *text);
	~BFMERetailAsciiString() { releaseBuffer(); }
	void releaseBuffer();

private:
	void *m_data;
};

class UnicodeString
{
public:
	void set(const UnicodeString &source);

private:
	void *m_data;
};

class AsciiString : private BFMERetailAsciiString
{
public:
	AsciiString(const char *text) : BFMERetailAsciiString(text) {}
	~AsciiString()
	{
		releaseBuffer();
	}
};

class BfmeEmotionName : private BFMERetailAsciiString
{
public:
	BfmeEmotionName(const char *text) : BFMERetailAsciiString(text) {}
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

class EmotionTrackerUpdateEntry
{
public:
	~EmotionTrackerUpdateEntry();

private:
	BFMERetailAsciiString m_first;
	unsigned char m_pad04[0x3c - 0x04];
	BFMERetailAsciiString m_second;
	unsigned char m_pad40[0xf4 - 0x40];
	BFMERetailAsciiString m_third;
};

class EmotionTrackerUpdateModuleData
{
public:
	unsigned char m_unknown00[0x30];
	std::vector<EmotionTrackerUpdateEntry *> m_entries;
};

// ?Rva00290520@@YAXPAVINI@@PAX1PBX@Z
void Rva00290520(INI *ini, void *, void *store, const void *)
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

	EmotionNugget *nugget;
	{
		BFMERetailAsciiString name(token);
		nugget = TheEmotionSystem->findNugget(
			*(const BfmeEmotionName *)&name);
	}

	if (nugget == 0)
		throw INIException(3, (const char *)0x010BE2E0);

	EmotionTrackerUpdateEntry *entry =
		(EmotionTrackerUpdateEntry *)new EmotionNugget;
	((BfmeThingVKC *)entry)->bfmeCopyVKC(*(const BfmeThingVKC *)nugget);
	{
		BFMERetailAsciiString name(token);
		((UnicodeString *)entry)->set(*(const UnicodeString *)&name);
	}

	if (hasAdditionalData)
		((BfmeThingDCE *)entry)->bfmeGoDCE((BfmeOtherDCE *)ini);

	((EmotionTrackerUpdateModuleData *)store)->m_entries.push_back(entry);
}
