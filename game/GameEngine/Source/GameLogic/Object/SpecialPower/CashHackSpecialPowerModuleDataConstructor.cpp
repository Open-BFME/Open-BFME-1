// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// CashHackSpecialPowerModuleData constructor, retail 0x00258D70, 101 bytes.
//
// IDENTITY. The only caller is the matched
// CashHackSpecialPower::friend_newModuleData (0x0011FDF0, call at 0x0011FE26
// through ILT 0x00026FF3), and the vtable this body installs, 0x010B3A08, has
// the matched ??_GCashHackSpecialPowerModuleData (0x00258DF0) in slot 0.
//
// LAYOUT. Matches the matched destructor at 0x00258E20: the BFME SpecialPower
// module-data base spans 0x210 bytes and is constructed out of line through
// ILT 0x00015C44, m_upgrades is an STLport vector of eight-byte records at
// +0x210, and m_defaultAmountToSteal follows at +0x21C. The dead copy loop
// after the three zero stores is STLport's inline clear() (erase(begin(),
// end()) copies [end, end) down to begin), as in the Zero Hour source.
#include <vector>

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class BfmeSpecialPowerModuleDataBase
{
public:
	BfmeSpecialPowerModuleDataBase();
	virtual ~BfmeSpecialPowerModuleDataBase();

private:
	unsigned char m_unmodelled_04[0x210 - 4];
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CashHackSpecialPower.h
class CashHackSpecialPowerModuleData : public BfmeSpecialPowerModuleDataBase
{
public:
	struct Upgrades
	{
		int m_science;
		int m_amountToSteal;
	};

	CashHackSpecialPowerModuleData();
	virtual ~CashHackSpecialPowerModuleData();

	std::vector<Upgrades> m_upgrades;
	int m_defaultAmountToSteal;
};

// ??0CashHackSpecialPowerModuleData@@QAE@XZ
CashHackSpecialPowerModuleData::CashHackSpecialPowerModuleData()
{
	m_upgrades.clear();
	m_defaultAmountToSteal = 0;
}
