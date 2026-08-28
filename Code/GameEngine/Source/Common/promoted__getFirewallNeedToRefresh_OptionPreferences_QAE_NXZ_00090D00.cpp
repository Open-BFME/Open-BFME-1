// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
// Lift the OptionPreferences::getFirewallNeedToRefresh naked dump to clean C++.
//
// Same preferences-getter opening as the rest of the family -- build the key,
// look it up, compare the mapped string -- but this one does not read the
// mapped AsciiString in place. It copies it into a second local and calls
// AsciiString::compareNoCase on the copy, which is why retail reserves eight
// bytes up front for two string slots rather than the family's usual one.
//
// The result is accumulated into a variable rather than returned from inside
// the if: retail zeroes bl before the compare, sets it to 1 on equality, and
// runs the copy's destructor once before moving bl into al. An if-form with a
// return in each arm would have emitted the destructor twice.
//
// Retail pins the layout: the map is at this+0x04 and its first word is the end
// sentinel, and the mapped AsciiString is at node+0x14.
//
// /EHs-c- because the build default only clears the /EHc half, and the two
// locals' destructors would otherwise pull in an SEH prologue retail lacks.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const char *);
	AsciiString(const AsciiString &);
	~AsciiString();

	int compareNoCase(const char *) const;				///< ILT thunk at 0x000405E8

private:
	void *m_data;
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
class OptionPreferences
{
public:
	bool getFirewallNeedToRefresh(void);

private:
	unsigned char m_unreconstructed_00[4];
	PreferenceMap m_prefs;								///< retail this+0x04
};

// ?getFirewallNeedToRefresh@OptionPreferences@@QAE_NXZ
bool OptionPreferences::getFirewallNeedToRefresh(void)
{
	PreferenceNode *it;
	{
		AsciiString key("FirewallNeedToRefresh");
		it = m_prefs.find(key);
	}

	if (it == m_prefs.end())
		return false;

	bool needToRefresh = false;
	AsciiString val = it->m_value;
	if (val.compareNoCase("TRUE") == 0)
	{
		needToRefresh = true;
	}

	return needToRefresh;
}
