// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// readable body of ?getPreferredColor@CustomMatchPreferences@@QAEHXZ: Code/GameEngine/Source/Common/UserPreferences.cpp
// Lift the CustomMatchPreferences::getPreferredColor naked dump to clean C++.
//
// Preferences getter bounded by the colour table: a missing key and an
// out-of-range value share the same answer, -1, so both fall through to one
// trailing return. The key lives in its own scope so it dies after the lookup
// and before the end() comparison, which is the order retail uses.
//
// getNumColors is a lazy inline accessor -- retail loads the count at +0x3C and,
// only when it is still zero, seeds it from +0x34 before comparing. That
// conditional store is the accessor, not part of this function's logic.
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/MultiplayerSettings.h
class MultiplayerSettings
{
public:
	int getNumColors(void)
	{
		if (m_numColors == 0)
			m_numColors = m_colorCount;
		return m_numColors;
	}

private:
	unsigned char m_unreconstructed_00[0x34];
	int m_colorCount;									///< retail this+0x34
	unsigned char m_unreconstructed_38[4];
	int m_numColors;									///< retail this+0x3C
};

extern MultiplayerSettings *TheMultiplayerSettings;		///< retail [0x012ED5FC]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/CustomMatchPreferences.h
class CustomMatchPreferences
{
public:
	int getPreferredColor(void);

private:
	unsigned char m_unreconstructed_00[4];
	PreferenceMap m_prefs;								///< retail this+0x04
};

// ?getPreferredColor@CustomMatchPreferences@@QAEHXZ
int CustomMatchPreferences::getPreferredColor(void)
{
	PreferenceNode *it;
	{
		AsciiString key("Color");
		it = m_prefs.find(key);
	}

	if (it != m_prefs.end())
	{
		int value = atoi(it->m_value.str());
		if (value >= -1 && value < TheMultiplayerSettings->getNumColors())
			return value;
	}

	return -1;
}
