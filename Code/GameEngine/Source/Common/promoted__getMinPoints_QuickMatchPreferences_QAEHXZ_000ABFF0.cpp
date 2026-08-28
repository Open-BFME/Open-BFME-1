// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// readable body of ?getMinPoints@QuickMatchPreferences@@QAEHXZ: Code/GameEngine/Source/Common/UserPreferences.cpp
// Lift the QuickMatchPreferences::getMinPoints naked dump to clean C++.
//
// The preferences object is a string->string map, so every getter is the same
// three steps: build the key, look it up, atoi the mapped string. The key lives
// in its own scope so it is destroyed after the lookup and before the end()
// comparison, which is the order retail uses.
//
// Retail pins the layout: the map is at this+0x04 and its first word is the end
// sentinel, the mapped AsciiString is at node+0x14, and str() inlines to
// "m_data ? m_data+8 : empty".
//
// /EHs-c- because the build default only clears the /EHc half, and the key's
// destructor would otherwise pull in an SEH prologue retail does not have.

extern "C" __declspec(dllimport) int __cdecl atoi(const char *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiStringData
{
public:
	unsigned char m_unreconstructed_00[8];
	char m_chars[1];									///< retail this+0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/QuickmatchPreferences.h
class QuickMatchPreferences
{
public:
	int getMinPoints(void);

private:
	unsigned char m_unreconstructed_00[4];
	PreferenceMap m_prefs;								///< retail this+0x04
};

// ?getMinPoints@QuickMatchPreferences@@QAEHXZ
int QuickMatchPreferences::getMinPoints(void)
{
	PreferenceNode *it;
	{
		AsciiString key("MinPoints");
		it = m_prefs.find(key);
	}

	if (it == m_prefs.end())
		return 0;

	return atoi(it->m_value.str());
}
