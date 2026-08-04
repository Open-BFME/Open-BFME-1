// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
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

class AsciiStringData
{
public:
	unsigned char m_unreconstructed_00[8];
	char m_chars[1];									///< retail this+0x08
};

class AsciiString
{
public:
	AsciiString(const char *);
	~AsciiString();

	const char *str(void) const { return m_data ? m_data->m_chars : ""; }

private:
	AsciiStringData *m_data;
};

struct PreferenceNode
{
	unsigned char m_unreconstructed_00[0x14];
	AsciiString m_value;								///< retail this+0x14
};

class PreferenceMap
{
public:
	PreferenceNode *find(const AsciiString &) const;
	PreferenceNode *end(void) const { return m_end; }

private:
	PreferenceNode *m_end;								///< retail this+0x00
};

class GlobalData
{
public:
	unsigned char m_unreconstructed_00[0xB8C];
	int m_maxParticleCount;								///< retail this+0xB8C
};

extern GlobalData *TheWritableGlobalData;				///< retail [0x012ED5C8]

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
