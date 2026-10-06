// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

extern "C" __declspec(dllimport) int __cdecl atoi(const char *);

typedef int Int;
typedef bool Bool;

template <typename T> struct StringInlineData
{
	unsigned short m_refCount;
	unsigned short m_reserved;
	unsigned short m_length;
	unsigned short m_pad;
	T m_text[1];
};

#include "../../../Libraries/Source/WWVegas/WWLib/ascii_string.h"


AsciiString AsciiStringToQuotedPrintable(AsciiString original);

struct PreferenceNode
{
	char m_pad[0x14];
	AsciiString m_value;
};

class PreferenceMap
{
public:
	PreferenceNode *find(const AsciiString &) const throw();
	PreferenceNode *end() const
	{
		return m_end;
	}

private:
	PreferenceNode *m_end;
};

class UserPreferences : public PreferenceMap
{
public:
	virtual ~UserPreferences();
};

class QuickMatchPreferences : public UserPreferences
{
public:
	Bool isMapSelected(const AsciiString &mapName);
};

// ?isMapSelected@QuickMatchPreferences@@QAE_NABVAsciiString@@@Z
Bool QuickMatchPreferences::isMapSelected(const AsciiString &mapName)
{
	Int ret;
	PreferenceNode *it = find(AsciiStringToQuotedPrintable(mapName));
	if (it == end())
	{
		return true;
	}

	ret = atoi(it->m_value.str());

	return (ret != 0);
}
