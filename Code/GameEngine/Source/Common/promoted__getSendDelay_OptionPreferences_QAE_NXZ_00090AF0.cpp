// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Lift the OptionPreferences::getSendDelay naked dump to clean C++.
//
// Same three steps as the rest of the boolean preferences family: build the
// key, look it up, compare the mapped string. What is new here is the default:
// where the earlier getters returned a literal, these fall back to a field of
// TheWritableGlobalData when the key is absent, so the missing-key branch is a
// global read rather than a constant.
//
// The key lives in its own scope so it is destroyed after the lookup and before
// the end() comparison, which is the order retail uses.
//
// Retail pins the layout: the map is at this+0x04 and its first word is the end
// sentinel, the mapped AsciiString is at node+0x14, str() inlines to
// "m_data ? m_data+8 : empty", and the default reads TheWritableGlobalData+0xB18.
//
// _strcmpi goes through the IAT so the comparison is a call; the neg/sbb/inc tail is MSVC's 8-bit == 0.
//
// /EHs-c- because the build default only clears the /EHc half, and the key's
// destructor would otherwise pull in an SEH prologue retail does not have.

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);

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
	unsigned char m_unreconstructed_00[0xB18];
	bool m_sendDelay;					///< retail this+0xB18
};

extern GlobalData *TheWritableGlobalData;				///< retail [0x012ED5C8]

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
class OptionPreferences
{
public:
	bool getSendDelay(void);

private:
	unsigned char m_unreconstructed_00[4];
	PreferenceMap m_prefs;								///< retail this+0x04
};

// ?getSendDelay@OptionPreferences@@QAE_NXZ
bool OptionPreferences::getSendDelay(void)
{
	PreferenceNode *it;
	{
		AsciiString key("SendDelay");
		it = m_prefs.find(key);
	}

	if (it == m_prefs.end())
		return TheWritableGlobalData->m_sendDelay;

	if (_strcmpi(it->m_value.str(), "yes") == 0)
	{
		return true;
	}
	return false;
}
