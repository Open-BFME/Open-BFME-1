// ?pushOne@Rva009A1FF0VecBox@@QAEXABUUpgrades@OCLSpecialPowerModuleData@@@Z
// partial score=0.99 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
class OCLSpecialPowerModuleData
{
public:
	struct Upgrades
	{
		int m_first;
		int m_second;
	};
};
class Rva009A1FF0VecBox
{
public:
	void pushOne(const OCLSpecialPowerModuleData::Upgrades &value);
	_STL::vector<OCLSpecialPowerModuleData::Upgrades> m_vec;
};
void Rva009A1FF0VecBox::pushOne(const OCLSpecialPowerModuleData::Upgrades &value)
{
	m_vec.push_back(value);
}
