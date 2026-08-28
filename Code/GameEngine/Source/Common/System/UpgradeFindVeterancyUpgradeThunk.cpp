// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(void);
	AsciiString(const AsciiString &other);
	~AsciiString(void);

private:
	void *m_data;
};

AsciiString getVetUpgradeName(VeterancyLevel level);		///< retail body at 0x0010AD90

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Upgrade.h
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
