// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

// One vector member at +0x210 and an out-of-line base destructor.
//
// The teardown is STLport's size-dispatched deallocate: capacity in bytes comes
// from +0x218 minus +0x210, and above 128 bytes it goes to operator delete while
// at or below it goes to the node allocator's _M_deallocate. The sar 3 / shl 3
// pair rounds that byte count to a multiple of the element size, which is how
// the element size is recoverable -- eight bytes, and no per-element loop, so
// the element has no destructor.
//
// The base destructor is CALLED rather than inlined, so it is declared without a
// body here; that is also why no vptr store appears in this function and the
// class is novtable. Where a base destructor is inline and empty the store shows
// up at the end instead.
#include <vector>

struct SpecialPowerEntry
{
	int m_a;
	int m_b;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerModuleData
{
public:
	virtual ~SpecialPowerModuleData();

private:
	unsigned char m_head[0x20C];
};

class __declspec(novtable) CashHackSpecialPowerModuleData : public SpecialPowerModuleData
{
public:
	virtual ~CashHackSpecialPowerModuleData();

private:
	std::vector<SpecialPowerEntry> m_entries;
};

// ??1CashHackSpecialPowerModuleData@@UAE@XZ
CashHackSpecialPowerModuleData::~CashHackSpecialPowerModuleData()
{
}
