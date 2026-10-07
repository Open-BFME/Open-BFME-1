// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /Igame/Libraries/Source/WWVegas/WWLib
// ABI-local reconstruction of OptionPreferences::getCampaignDifficulty.
// The public OptionsMenu declaration uses the game's full headers; this TU
// keeps the retail preference-node and StringBase layout explicit so MSVC 7.1
// emits the out-of-line AsciiString constructor/destructor calls used here.

typedef int Int;

extern "C" __declspec(dllimport) int __cdecl atoi(char *text);

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

class ScriptEngine
{
public:
	unsigned char m_unreconstructed_00[0x17620];
	Int m_globalDifficulty;

	Int getGlobalDifficulty(void) const { return m_globalDifficulty; }
};

extern ScriptEngine *TheScriptEngine;

class OptionPreferences
{
public:
	Int getCampaignDifficulty(void);

private:
	unsigned char m_unreconstructed_00[4];
	PreferenceMap m_prefs;
};

// ?getCampaignDifficulty@OptionPreferences@@QAEHXZ
Int OptionPreferences::getCampaignDifficulty(void)
{
	PreferenceNode *it;
	{
		AsciiString key("CampaignDifficulty");
		it = m_prefs.find(key);
	}

	if (it == m_prefs.end())
		return TheScriptEngine->getGlobalDifficulty();

	Int factor = atoi((char *)it->m_value.str());
	if (factor < 0)
		return 0;
	if (factor > 2)
		return 2;
	return factor;
}
