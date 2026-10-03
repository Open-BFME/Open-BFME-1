// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Open-BFME5: ProductionSpeedBonusModuleData dtor. SEH vector<AsciiString>
// @+0x218 then the common SpecialPower module-data base.

#include <vector>

#include "ascii_string.h"

extern template _STL::vector<AsciiString>::~vector();

class SpecialPowerModuleData
{
public:
	virtual ~SpecialPowerModuleData();
private:
	unsigned char m_pad[0x20c];
};

class __declspec(novtable) ProductionSpeedBonusModuleData : public SpecialPowerModuleData
{
public:
	virtual ~ProductionSpeedBonusModuleData();
private:
	unsigned int m_bonusPercent;
	unsigned int m_duration;
	_STL::vector<AsciiString> m_upgradeTypes;
};

// ??1ProductionSpeedBonusModuleData@@UAE@XZ
ProductionSpeedBonusModuleData::~ProductionSpeedBonusModuleData()
{
}
