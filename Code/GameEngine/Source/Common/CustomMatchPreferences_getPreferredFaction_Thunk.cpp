// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// readable body of ?getPreferredFaction@CustomMatchPreferences@@QAEHXZ: Code/GameEngine/Source/Common/UserPreferences.cpp
// Lift the CustomMatchPreferences::getPreferredFaction naked dump to clean C++.
//
// The preferences-getter opening is the family's; the tail validates the stored
// index against ThePlayerTemplateStore. Retail routes every rejection to one
// `or esi,-1` at the end rather than returning early, so the checks are written
// as a chain that assigns to the index and falls through to a single return.
//
// The template count is not a stored field: retail loads the pointers at
// store+0x08 and store+0x0C, subtracts them, and divides by 292 through the
// usual imul-magic-plus-add-back sequence (0xE070381D with sar 8, which is
// consistent with exactly one divisor). So the store holds PlayerTemplate by
// value in a contiguous range and sizeof(PlayerTemplate) is 292 -- a plain
// pointer subtraction reproduces the whole sequence.
//
// The index -1 is allowed through without a lookup: retail tests it after the
// range check and jumps straight to the return, so "no preference" is a valid
// stored value rather than a rejection.
//
// Retail pins the layout: the map is at this+0x04 and its first word is the end
// sentinel, the mapped AsciiString is at node+0x14, str() inlines to
// "m_data ? m_data+8 : empty", and the playable flag sits at template+0xBD.

typedef int Int;

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

// 292 bytes total; only the playable flag is reconstructed.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerTemplate.h
class PlayerTemplate
{
public:
	unsigned char m_unreconstructed_00[0xBD];
	bool m_isPlayableSide;								///< retail this+0xBD
	unsigned char m_unreconstructed_BE[292 - 0xBE];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/PlayerTemplate.h
class PlayerTemplateStore
{
public:
	const PlayerTemplate *getNthPlayerTemplate(Int index);	///< ILT thunk at 0x00037BD2

	Int getPlayerTemplateCount(void) const { return m_end - m_begin; }

private:
	unsigned char m_unreconstructed_00[8];
	PlayerTemplate *m_begin;							///< retail this+0x08
	PlayerTemplate *m_end;								///< retail this+0x0C
};

extern PlayerTemplateStore *ThePlayerTemplateStore;		///< retail [0x012ED750]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/CustomMatchPreferences.h
class CustomMatchPreferences
{
public:
	Int getPreferredFaction(void);

private:
	unsigned char m_unreconstructed_00[4];
	PreferenceMap m_prefs;								///< retail this+0x04
};

// ?getPreferredFaction@CustomMatchPreferences@@QAEHXZ
Int CustomMatchPreferences::getPreferredFaction(void)
{
	PreferenceNode *it;
	{
		AsciiString key("PlayerTemplate");
		it = m_prefs.find(key);
	}

	if (it == m_prefs.end())
		return -1;

	Int index = atoi(it->m_value.str());

	if (index == -2 || index < -2 || index >= ThePlayerTemplateStore->getPlayerTemplateCount())
	{
		index = -1;
	}
	else if (index >= 0)
	{
		const PlayerTemplate *tmpl = ThePlayerTemplateStore->getNthPlayerTemplate(index);
		if (tmpl == 0 || !tmpl->m_isPlayableSide)
			index = -1;
	}

	return index;
}
