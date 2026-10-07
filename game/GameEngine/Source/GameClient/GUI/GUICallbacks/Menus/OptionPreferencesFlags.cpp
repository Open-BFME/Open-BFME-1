// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /Igame/Libraries/Source/WWVegas/WWLib
// BFME OptionPreferences boolean getters. Shared preference-map layout for
// UseSystemMapDir, HasSeenLogoMovies and HasGotOnline. The original preference
// implementation lives in Common/UserPreferences.cpp.
//
// The preferences object is a string->string map, so every getter is the same
// three steps: build the key, look it up, compare the mapped string. The key lives
// in its own scope so it is destroyed after the lookup and before the end()
// comparison, which is the order retail uses.
//
// Retail pins the layout: the map is at this+0x04 and its first word is the end
// sentinel, the mapped AsciiString is at node+0x14, and str() inlines to
// "m_data ? m_data+8 : empty".
//
// /EHs-c- because the build default only clears the /EHc half, and the key's
// destructor would otherwise pull in an SEH prologue retail does not have.

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);

#include "ascii_string.h"

struct PreferenceNode
{
	unsigned char m_unreconstructed_00[0x14];
	AsciiString m_value;								///< retail this+0x14
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
	PreferenceNode *m_end;								///< retail this+0x00
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
class OptionPreferences
{
public:
	bool usesSystemMapDir(void);
	bool hasSeenLogoMovies(void);
	bool hasGotOnline(void);

private:
	unsigned char m_unreconstructed_00[4];
	PreferenceMap m_prefs;								///< retail this+0x04
};

// ?usesSystemMapDir@OptionPreferences@@QAE_NXZ
bool OptionPreferences::usesSystemMapDir(void)
{
	PreferenceNode *it;
	{
		AsciiString key("UseSystemMapDir");
		it = m_prefs.find(key);
	}

	if (it == m_prefs.end())
		return true;

	if (_strcmpi(it->m_value.str(), "yes") == 0)
	{
		return true;
	}
	return false;
}

// ?hasSeenLogoMovies@OptionPreferences@@QAE_NXZ
bool OptionPreferences::hasSeenLogoMovies(void)
{
	PreferenceNode *it;
	{
		AsciiString key("HasSeenLogoMovies");
		it = m_prefs.find(key);
	}

	if (it == m_prefs.end())
		return false;

	if (_strcmpi(it->m_value.str(), "yes") == 0)
		return true;
	return false;
}

bool OptionPreferences::hasGotOnline(void)
{
	PreferenceNode *it;
	{
		AsciiString key("HasGotOnline");
		it = m_prefs.find(key);
	}

	if (it == m_prefs.end())
		return false;

	if (_strcmpi(it->m_value.str(), "yes") == 0)
		return true;
	return false;
}
