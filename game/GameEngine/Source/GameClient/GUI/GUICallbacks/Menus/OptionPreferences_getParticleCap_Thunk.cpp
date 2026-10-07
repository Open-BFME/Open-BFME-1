// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /Igame/Libraries/Source/WWVegas/WWLib
// Lift the OptionPreferences::getParticleCap naked dump to clean C++.
//
// Preferences getter whose default is computed rather than read: a missing key
// derives the slider position from the particle cap at GlobalData+0xB8C. Unlike
// the texture-reduction sibling that path returns early, since the computed
// value skips the 0..100 clamp entirely.
// The key lives in its own scope so it dies after the lookup and before the
// end() comparison, which is the order retail uses.
//
// Retail pins the layout: the map is at this+0x04 and its first word is the end
// sentinel, the mapped AsciiString is at node+0x14, and str() inlines to
// "m_data ? m_data+8 : empty".
//
// /EHs-c- because the build default only clears the /EHc half, and the key's
// destructor would otherwise pull in an SEH prologue retail does not have.

extern "C" __declspec(dllimport) int __cdecl atoi(const char *);

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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	unsigned char m_unreconstructed_00[0xB8C];
	int m_maxParticleCount;								///< retail this+0xB8C
};

extern GlobalData *TheWritableGlobalData;				///< retail [0x012ED5C8]

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
class OptionPreferences
{
public:
	int getParticleCap(void);

private:
	unsigned char m_unreconstructed_00[4];
	PreferenceMap m_prefs;								///< retail this+0x04
};

// ?getParticleCap@OptionPreferences@@QAEHXZ
int OptionPreferences::getParticleCap(void)
{
	PreferenceNode *it;
	{
		AsciiString key("MaxParticleCount");
		it = m_prefs.find(key);
	}

	if (it == m_prefs.end())
	{
		// The stored cap spans 100..2999, so subtracting the floor and scaling
		// by 1/29 maps it back onto the 0..100 slider.
		return (int)((TheWritableGlobalData->m_maxParticleCount - 100) * 0.03448275849223137f);
	}

	int value = atoi(it->m_value.str());

	if (value < 0)
		return 0;

	if (value > 100)
		return 100;

	return value;
}
