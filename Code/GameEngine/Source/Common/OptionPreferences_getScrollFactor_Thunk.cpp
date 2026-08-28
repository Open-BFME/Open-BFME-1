// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// readable body of ?getScrollFactor@OptionPreferences@@QAEMXZ: Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Menus/OptionsMenu.cpp
// Lift the OptionPreferences::getScrollFactor naked dump to clean C++.
//
// Float-returning preferences getter: a missing key returns the stored scroll
// factor at GlobalData+0xBC0 directly, while a present one is clamped as an
// integer and only then scaled, which is why retail keeps the value on the
// stack and fild/fmuls it in both clamp arms.
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GlobalData.h
class GlobalData
{
public:
	unsigned char m_unreconstructed_00[0xBC0];
	float m_scrollFactor;								///< retail this+0xBC0
};

extern GlobalData *TheWritableGlobalData;				///< retail [0x012ED5C8]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
class OptionPreferences
{
public:
	float getScrollFactor(void);

private:
	unsigned char m_unreconstructed_00[4];
	PreferenceMap m_prefs;								///< retail this+0x04
};

// ?getScrollFactor@OptionPreferences@@QAEMXZ
float OptionPreferences::getScrollFactor(void)
{
	PreferenceNode *it;
	{
		AsciiString key("ScrollFactor");
		it = m_prefs.find(key);
	}

	if (it == m_prefs.end())
		return TheWritableGlobalData->m_scrollFactor;

	int value = atoi(it->m_value.str());

	// Note the floor is 1, not 0: a negative preference clamps up to the
	// smallest usable scroll rate rather than to none at all.
	if (value < 0)
		value = 1;
	else if (value > 100)
		value = 100;

	return value * 0.019999999552965164f;
}
