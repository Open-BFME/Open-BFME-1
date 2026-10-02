// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Lift the UpgradeCenter::findVeterancyUpgrade __emit thunk to clean C++.
//
// Verbatim Zero Hour Upgrade.cpp -- two lines: name the veterancy upgrade, then
// look it up. Keeps /EHsc unlike most conversions in this tree: the AsciiString
// temporary really does need unwind here, and retail carries the matching SEH
// prologue with its state variable moving -1 -> 0 -> -1 around the lookup.
//
// getVetUpgradeName returns AsciiString by value, so MSVC passes the hidden
// result pointer as the first cdecl argument -- that is the `lea ecx,[esp+0x18]`
// pushed after the level, not a second parameter.

class UpgradeTemplate;

enum VeterancyLevel { LEVEL_REGULAR = 0 };

#include "ascii_string.h"

// Zero Hour Upgrade.cpp keeps this helper static. Internal linkage is
// required for retail's return-buffer allocation and inline strlen schedule.
extern "C" unsigned int __cdecl strlen(const char *);
#pragma intrinsic(strlen)
inline AsciiString &AsciiString::operator=(const char *s) {
    StringBase<char>::set(s, s ? strlen(s) : 0);
    return *this;
}
template <typename T> inline void StringBase<T>::concat(const T *s) {
    concat(s, s ? strlen(s) : 0);
}
extern const char *TheVeterancyNames[];
__declspec(noinline) static AsciiString getVetUpgradeName(VeterancyLevel v) {
    AsciiString tmp;
    tmp = "Upgrade_Veterancy_";
    tmp.concat(TheVeterancyNames[v]);
    return tmp;
}


// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
class UpgradeCenter
{
public:
	const UpgradeTemplate *findVeterancyUpgrade(VeterancyLevel level) const;
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;	///< ILT thunk at 0x0002F95A
};

// ?findVeterancyUpgrade@UpgradeCenter@@QBEPBVUpgradeTemplate@@W4VeterancyLevel@@@Z
const UpgradeTemplate *UpgradeCenter::findVeterancyUpgrade(VeterancyLevel level) const
{
	AsciiString tmp = getVetUpgradeName(level);
	return findUpgrade(tmp);
}
