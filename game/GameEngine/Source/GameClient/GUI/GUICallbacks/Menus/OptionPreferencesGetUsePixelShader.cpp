// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /Igame/Libraries/Source/WWVegas/WWLib
// OptionPreferences::getUsePixelShader at retail 0x00090E10.

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);

class AsciiStringData
{
public:
	unsigned char m_unreconstructed_00[8];
	char m_chars[1];
};

#include "ascii_string.h"

struct PreferenceNode
{
	unsigned char m_unreconstructed_00[0x14];
	AsciiString m_value;
};

// Retail lookup ILT 0x0000AEAC reaches the ledger tree body at 0x00080600.
extern void j_0000aeac();

class PreferenceMap
{
public:
	__forceinline PreferenceNode *find(const AsciiString &key) const
	{
		typedef PreferenceNode *(PreferenceMap::*Find)(const AsciiString &) const;
		union { void (*fn)(); Find call; } lookup = { j_0000aeac };
		return (this->*lookup.call)(key);
	}
	PreferenceNode *end(void) const { return m_end; }

private:
	PreferenceNode *m_end;
};

class GlobalData
{
public:
	unsigned char m_unreconstructed_00[0x28];
	unsigned char m_usePixelShader;
};

extern GlobalData *TheWritableGlobalData;

class OptionPreferences
{
public:
	bool getUsePixelShader(void);

private:
	unsigned char m_unreconstructed_00[4];
	PreferenceMap m_prefs;
};

bool OptionPreferences::getUsePixelShader(void)
{
	PreferenceNode *it;
	{
		AsciiString key("UsePixelShader");
		it = m_prefs.find(key);
	}

	if (it == m_prefs.end())
		return TheWritableGlobalData->m_usePixelShader == 0;

	if (_strcmpi(it->m_value.str(), "yes") != 0)
		return false;
	return true;
}
