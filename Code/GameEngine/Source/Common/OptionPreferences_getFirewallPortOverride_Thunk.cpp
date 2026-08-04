// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Lift the OptionPreferences::getFirewallPortOverride naked dump to clean C++.
//
// Preferences getter whose default is not a constant: a missing key falls back
// to the 16-bit global at GlobalData+0xB1C, so that path returns early rather
// than sharing an epilogue. A present value is returned straight from atoi --
// the unsigned short return needs no narrowing because the value already
// arrives in ax. The key lives in its own scope so it dies after the lookup and
// before the end() comparison, which is the order retail uses.
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
	unsigned char m_unreconstructed_00[0xB1C];
	unsigned short m_firewallPortOverride;				///< retail this+0xB1C
};

extern GlobalData *TheWritableGlobalData;				///< retail [0x012ED5C8]

class OptionPreferences
{
public:
	unsigned short getFirewallPortOverride(void);

private:
	unsigned char m_unreconstructed_00[4];
	PreferenceMap m_prefs;								///< retail this+0x04
};

// ?getFirewallPortOverride@OptionPreferences@@QAEGXZ
unsigned short OptionPreferences::getFirewallPortOverride(void)
{
	PreferenceNode *it;
	{
		AsciiString key("FirewallPortOverride");
		it = m_prefs.find(key);
	}

	if (it == m_prefs.end())
		return TheWritableGlobalData->m_firewallPortOverride;

	return atoi(it->m_value.str());
}
