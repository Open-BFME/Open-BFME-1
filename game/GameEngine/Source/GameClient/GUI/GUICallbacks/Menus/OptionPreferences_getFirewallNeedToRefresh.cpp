// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c- /Igame/Libraries/Source/WWVegas/WWLib
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

// The map lookup is reached through retail's ILT thunk at 0x0000AEAC (the
// ledger's ?j_0000aeac@@YAXXZ, the STLport hashtable find body), so the call
// goes to that thunk rather than to a TU-local member.
extern void j_0000aeac();

#include "ascii_string.h"

struct PreferenceNode
{
	unsigned char m_unreconstructed_00[0x14];
	AsciiString m_value;								///< retail this+0x14
};

class PreferenceMap
{
public:
	PreferenceNode *end(void) const { return m_end; }

private:
	PreferenceNode *m_end;								///< retail this+0x00
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UserPreferences.h
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
		// A member-pointer route keeps the thiscall receiver in ECX and the
		// string reference on the stack, as retail's call does.
		union FindRoute
		{
			void (*raw)();
			PreferenceNode *(PreferenceMap::*member)(const AsciiString &) const;
		} route;
		route.raw = j_0000aeac;
		it = ( ( &m_prefs )->*route.member )( key );
	}

	if (it == m_prefs.end())
		return false;

	bool needToRefresh = false;
	AsciiString val = it->m_value;
	if (val.StringBase<char>::compareNoCase("TRUE") == 0)
	{
		needToRefresh = true;
	}

	return needToRefresh;
}
