// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// The same shape as CashHackSpecialPowerModuleData with two numbers changed: the
// vector sits at +0x254 and its element is four bytes rather than eight, which
// the sar 2 / shl 2 pair gives away where the other had sar 3 / shl 3.
//
// Teardown is STLport's size-dispatched deallocate -- capacity in bytes from
// +0x25C minus +0x254, then operator delete above 128 bytes and the node
// allocator's _M_deallocate at or below. _STLP_USE_STATIC_LIB is what makes that
// dispatch appear inline; without it the allocator entry points are dllimport
// and the whole thing collapses to one indirect call.
//
// The base destructor is called rather than inlined, so it is declared without a
// body and no vptr store appears here.
#include <vector>

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialAbilityUpdate.h
class SpecialAbilityUpdateModuleData
{
public:
	virtual ~SpecialAbilityUpdateModuleData();

private:
	unsigned char m_head[0x250];
};

class __declspec(novtable) GiveUpgradeUpdateModuleData : public SpecialAbilityUpdateModuleData
{
public:
	virtual ~GiveUpgradeUpdateModuleData();

private:
	std::vector<int> m_upgrades;
};

// ??1GiveUpgradeUpdateModuleData@@UAE@XZ
GiveUpgradeUpdateModuleData::~GiveUpgradeUpdateModuleData()
{
}
