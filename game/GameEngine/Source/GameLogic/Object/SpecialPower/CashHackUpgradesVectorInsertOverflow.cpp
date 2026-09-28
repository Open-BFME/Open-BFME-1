// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <vector>

typedef int Int;
typedef int ScienceType;

class CashHackSpecialPowerModuleData
{
public:
	struct Upgrades
	{
		ScienceType m_science;
		Int m_amountToSteal;
	};
};

void BfmeCashHackUpgradesVectorAnchor(_STL::vector<CashHackSpecialPowerModuleData::Upgrades> &v, const CashHackSpecialPowerModuleData::Upgrades &value)
{
	v.insert(v.begin(), value);
}
