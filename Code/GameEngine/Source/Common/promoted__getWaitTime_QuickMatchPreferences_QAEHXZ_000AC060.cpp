// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Lift the QuickMatchPreferences::getWaitTime naked dump to clean C++.
//
// One of the preferences getters: build the key, look it up, atoi the mapped
// string. The key lives in its own scope so it is destroyed after the lookup
// and before the end() comparison, which is the order retail uses -- a
// temporary instead makes MSVC hoist a single lea for the map pointer.
//
// Retail pins the layout: the map is at this+0x04 with its end sentinel at
// +0x00, the mapped AsciiString is at node+0x14, and str() inlines to
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

class QuickMatchPreferences
{
public:
	int getWaitTime(void);

private:
	unsigned char m_unreconstructed_00[4];
	PreferenceMap m_prefs;								///< retail this+0x04
};

// ?getWaitTime@QuickMatchPreferences@@QAEHXZ
int QuickMatchPreferences::getWaitTime(void)
{
	PreferenceNode *it;
	{
		AsciiString key("WaitTime");
		it = m_prefs.find(key);
	}

	if (it == m_prefs.end())
		return 0;

	return atoi(it->m_value.str());
}
