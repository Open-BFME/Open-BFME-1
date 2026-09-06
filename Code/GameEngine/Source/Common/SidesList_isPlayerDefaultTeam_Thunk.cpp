// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringbaseascii /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/buildlistinfo /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib

#include <string.h>

#pragma intrinsic(memcmp)

template <class T>
class StringBase
{
public:
	bool startsWith(const T *text, int length) const;
};

class AsciiString
{
private:
	struct Header
	{
		int references;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

	Header *m_data;
	void releaseBuffer(void);

public:
	~AsciiString(void) { releaseBuffer(); }

	const char *str(void) const
	{
		return m_data ? m_data->data : "";
	}

	bool startsWith(const char *text, int length) const
	{
		return ((const StringBase<char> *)this)->startsWith(text, length);
	}

	int compare(const char *text) const
	{
		int otherLength = text ? (int)strlen(text) : 0;
		int thisLength = m_data ? m_data->length : 0;
		const char *thisData = m_data ? m_data->data : "";
		int count = thisLength < otherLength ? thisLength : otherLength;
		int result = memcmp(thisData, text, count);
		if (result != 0)
			return result;
		return thisLength - otherLength;
	}
};

enum NameKeyType
{
	NameKeyTypeUnknown
};

class StaticNameKey
{
public:
	NameKeyType key(void) const;
};

extern const StaticNameKey TheKey_teamName;
extern const StaticNameKey TheKey_playerName;

class Dict
{
public:
	AsciiString getAsciiString(NameKeyType key, bool *exists) const;
};

class TeamsInfo
{
public:
	Dict *getDict(void) { return &m_dict; }

private:
	Dict m_dict;
};

struct SidesInfo
{
	Dict *getDict(void) { return &m_dict; }

	Dict m_dict;
	char m_padding[23];
};

class SidesList
{
public:
	bool isPlayerDefaultTeam(TeamsInfo *t);

private:
	char m_prefix[40];
	int m_numSides;
	char m_between[4];
	SidesInfo m_sides[1];
};

bool SidesList::isPlayerDefaultTeam(TeamsInfo *t)
{
	AsciiString tname = t->getDict()->getAsciiString(
		TheKey_teamName.key(), 0);
	if (((StringBase<char> *)&tname)->startsWith("team", 4))
	{
		register const char *rest = tname.str() + 4;
		int j;
		for (j = 0; j < m_numSides; j++)
		{
			AsciiString pname = m_sides[j].getDict()->getAsciiString(
				TheKey_playerName.key(), 0);
			if (pname.compare(rest) == 0)
				return true;
		}
	}
	return false;
}
