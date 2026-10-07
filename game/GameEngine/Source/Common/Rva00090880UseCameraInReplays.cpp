// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /Igame/Libraries/Source/WWVegas/WWLib
// Byte-twin of OptionPreferences::usesSystemMapDir at 0x00090780
// (OptionPreferencesFlags.cpp):
// identical 95 bytes once relocations (and the key string literal, here
// "UseCameraInReplays" not "UseSystemMapDir") are masked. Same PreferenceMap
// find/end lookup shape; ?useCameraInReplays@OptionPreferences@@QAE_NXZ is
// already claimed at 0x00090900 by an unrelated (naked-lift, different
// shape) body, so this second real accessor is claimed address-derived.
//
// /EHs-c- because the build default only clears the /EHc half, and the key's
// destructor would otherwise pull in an SEH prologue retail does not have.

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiStringData
{
public:
	unsigned char m_unreconstructed_00[8];
	char m_chars[1];									///< retail this+0x08
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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
class Rva00090880OptionPreferences
{
public:
	bool useCameraInReplaysAddrDerived(void);

private:
	unsigned char m_unreconstructed_00[4];
	PreferenceMap m_prefs;								///< retail this+0x04
};

bool Rva00090880OptionPreferences::useCameraInReplaysAddrDerived(void)
{
	PreferenceNode *it;
	{
		AsciiString key("UseCameraInReplays");
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
