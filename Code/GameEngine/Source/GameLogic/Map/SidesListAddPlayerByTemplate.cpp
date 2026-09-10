// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
// Retail ?addPlayerByTemplate@SidesList@@QAEXVAsciiString@@@Z at 0x0019C590.
//
// This TU keeps the BFME record layout local.  The fixed side record is the
// same 0x18-byte item whose initializer is identified by the named
// BfmeThingCMC::bfmeAddCMC caller at 0x0019A780.  The team record uses the
// independently proven 0x1c-byte append body reached through ILT 0x45DC7.

#include "string_base.h"

extern "C" unsigned int __cdecl strlen(const char *text);
#pragma intrinsic(strlen)

typedef unsigned short WideChar;

extern "C" __declspec(dllimport) unsigned int __cdecl bfmeLenVGI(
	const WideChar *text);

extern const char Rva006A16B0Empty[];
extern const char g_Rva0107301CEmptyString[];

class AsciiString
{
public:
	static AsciiString TheEmptyString;

	AsciiString()
	{
		m_text = 0;
	}

	~AsciiString()
	{
		((StringBase<char> *)this)->releaseBuffer();
	}

	void set(const char *text)
	{
		((StringBase<char> *)this)->set(text, text ? strlen(text) : 0);
	}

	void set(const char *text, int length)
	{
		((StringBase<char> *)this)->set(text, length);
	}

	void concat(const char *text)
	{
		((StringBase<char> *)this)->concat(text, text ? strlen(text) : 0);
	}

	void concat(const AsciiString &text)
	{
		int length = text.m_text
			? *(const unsigned short *)(text.m_text + 4)
			: 0;
		const char *data = text.m_text ? text.m_text + 8 : Rva006A16B0Empty;
		((StringBase<char> *)this)->concat(data, length);
	}

	bool isEmpty() const
	{
		return m_text == 0 || *(const unsigned short *)(m_text + 4) == 0;
	}

	const char *str() const
	{
		return m_text ? m_text + 8 : Rva006A16B0Empty;
	}

	bool startsWith(const char *text) const
	{
		return ((const StringBase<char> *)this)->startsWith(
			text, text ? strlen(text) : 0);
	}

	int bfmeCompare1294(const char *text) const;

private:
	char *m_text;
};

class UnicodeString
{
public:
	UnicodeString()
	{
		m_text = 0;
	}

	~UnicodeString()
	{
		((StringBase<WideChar> *)this)->releaseBuffer();
	}

	UnicodeString &operator=(const WideChar *text)
	{
		((StringBase<WideChar> *)this)->set(
			text, text ? (int)bfmeLenVGI(text) : 0);
		return *this;
	}

	void translate(const AsciiString &text);

private:
	WideChar *m_text;
};

enum NameKeyType
{
	NAMEKEY_UNKNOWN
};

class StaticNameKey
{
public:
	NameKeyType key() const;
};

extern const StaticNameKey TheKey_playerName;
extern const StaticNameKey TheKey_playerIsHuman;
extern const StaticNameKey TheKey_playerDisplayName;
extern const StaticNameKey TheKey_playerFaction;
extern const StaticNameKey TheKey_playerEnemies;
extern const StaticNameKey TheKey_playerAllies;
extern const StaticNameKey TheKey_teamName;
extern const StaticNameKey TheKey_teamOwner;
extern const StaticNameKey TheKey_teamIsSingleton;

class Dict
{
public:
	Dict(int numPairsToPreAllocate = 0);
	~Dict()
	{
		releaseData();
	}

	void clear();
	void setAsciiString(NameKeyType key, const AsciiString &value);
	void setBool(NameKeyType key, bool value);
	void setUnicodeString(NameKeyType key, const UnicodeString &value);

private:
	void releaseData();
	void *m_data;
};

struct BfmeItemCMC
{
	void bfmeInitCMC(void *value);
	unsigned char m_padding[0x18];
};

struct Rva0019BE80TeamRec
{
	int append(const Dict *dict);
	unsigned char m_padding[0x1c];
};

typedef char SideRecordSizeCheck[sizeof(BfmeItemCMC) == 0x18 ? 1 : -1];
typedef char TeamRecordSizeCheck[sizeof(Rva0019BE80TeamRec) == 0x1c ? 1 : -1];
typedef char AsciiSizeCheck[sizeof(AsciiString) == 4 ? 1 : -1];
typedef char UnicodeSizeCheck[sizeof(UnicodeString) == 4 ? 1 : -1];

class SidesList
{
public:
	void addPlayerByTemplate(AsciiString playerTemplateName);

private:
	unsigned char m_prefix[0x28];
	int m_numSides;
	BfmeItemCMC m_sides[32];
	int m_numSkirmishSides;
	BfmeItemCMC m_skirmishSides[32];
	Rva0019BE80TeamRec m_teamrec;
};

void SidesList::addPlayerByTemplate(AsciiString playerTemplateName)
{
	AsciiString playerName;
	UnicodeString playerDisplayName;
	bool isHuman = false;

	if (playerTemplateName.isEmpty())
	{
		playerName.set(g_Rva0107301CEmptyString, 0);
		playerDisplayName = L"Neutral";
		isHuman = false;
	}
	else
	{
		playerName.set("Plyr");
		if (playerTemplateName.startsWith("Faction"))
			playerName.concat(playerTemplateName.str() + 7);
		else
			playerName.concat(playerTemplateName);

		playerDisplayName.translate(playerName);
		isHuman = true;
		if (playerName.bfmeCompare1294("PlyrCivilian") == 0)
			isHuman = false;
	}

	Dict d;
	d.clear();
	d.setAsciiString(TheKey_playerName.key(), playerName);
	d.setBool(TheKey_playerIsHuman.key(), isHuman);
	d.setUnicodeString(TheKey_playerDisplayName.key(), playerDisplayName);
	d.setAsciiString(TheKey_playerFaction.key(), playerTemplateName);
	d.setAsciiString(TheKey_playerEnemies.key(), AsciiString::TheEmptyString);
	d.setAsciiString(TheKey_playerAllies.key(), AsciiString::TheEmptyString);

	int side = m_numSides;
	if (side < 32)
	{
		m_numSides = side + 1;
		m_sides[side].bfmeInitCMC(&d);
	}

	AsciiString playerTeamName;
	playerTeamName.set("team");
	playerTeamName.concat(playerName);

	d.clear();
	d.setAsciiString(TheKey_teamName.key(), playerTeamName);
	d.setAsciiString(TheKey_teamOwner.key(), playerName);
	d.setBool(TheKey_teamIsSingleton.key(), true);
	m_teamrec.append(&d);
}
