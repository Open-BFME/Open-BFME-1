// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Byte-twin of OptionPreferences::usesSystemMapDir at 0x00090780
// (promoted__usesSystemMapDir_OptionPreferences_QAE_NXZ_00090780.cpp):
// identical 95 bytes once relocations (and the key string literal, here
// "UseCameraInReplays" not "UseSystemMapDir") are masked. Same PreferenceMap
// find/end lookup shape; ?useCameraInReplays@OptionPreferences@@QAE_NXZ is
// already claimed at 0x00090900 by an unrelated (naked-lift, different
// shape) body, so this second real accessor is claimed address-derived.
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
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

	if (_strcmpi(it->m_value.str(), "y") == 0)
	{
		return true;
	}
	return false;
}
