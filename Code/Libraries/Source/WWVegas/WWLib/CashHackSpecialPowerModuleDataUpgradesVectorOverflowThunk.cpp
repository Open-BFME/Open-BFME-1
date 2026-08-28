// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CashHackSpecialPower.h
struct CashHackSpecialPowerModuleData
{
	struct Upgrades
	{
	};
};

namespace _STL
{
struct __false_type
{
};

template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
protected:
	void _M_insert_overflow(Type *, const Type &, const __false_type &, unsigned int, bool);
};

class CashHackSpecialPowerModuleDataUpgradesInsertOverflowShim
{
public:
	void insert_overflow(CashHackSpecialPowerModuleData::Upgrades *pos, const CashHackSpecialPowerModuleData::Upgrades &x, const __false_type &tag, unsigned int fill_len, bool at_end);
};

void vector<CashHackSpecialPowerModuleData::Upgrades, allocator<CashHackSpecialPowerModuleData::Upgrades> >::_M_insert_overflow(
	CashHackSpecialPowerModuleData::Upgrades *pos, const CashHackSpecialPowerModuleData::Upgrades &x, const __false_type &tag, unsigned int fill_len, bool at_end)
{
	((CashHackSpecialPowerModuleDataUpgradesInsertOverflowShim *)this)->insert_overflow(pos, x, tag, fill_len, at_end);
}
}
