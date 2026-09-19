// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
// Open-BFME: vector<OCLSpecialPowerModuleData::Upgrades>::_M_insert_overflow,
// retail 0x00262FE0, 305 bytes. The body carried no ledger row; its name sat
// on a 5-byte thunk.
//
// The element is eight bytes -- the size arithmetic divides by eight twice --
// and it is plain data: the only calls in the body are the allocation and the
// release, with the element moves done as block copies.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/OCLSpecialPower.h
class OCLSpecialPowerModuleData
{
public:
	struct Upgrades
	{
		Int m_bfmeFirst;
		Int m_bfmeSecond;
	};
};

void BfmeOCLUpgradesVectorAnchor(_STL::vector<OCLSpecialPowerModuleData::Upgrades> &v, const OCLSpecialPowerModuleData::Upgrades &value)
{
	v.insert(v.begin(), value);
}
