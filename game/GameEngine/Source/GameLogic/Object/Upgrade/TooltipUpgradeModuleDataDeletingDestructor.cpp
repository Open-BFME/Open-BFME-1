// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Retail's TooltipUpgradeModuleData vtable at 0x0108F650 names this scalar
// deleting destructor in slot zero. Its call target is the independently
// matched destructor body at 0x0012BBB0.

class UpgradeModuleDataSub
{
public:
	~UpgradeModuleDataSub();
private:
	char m_opaque[0x68];
};

#include "ascii_string.h"

class TooltipUpgradeModuleDataPrimaryBase
{
public:
	virtual ~TooltipUpgradeModuleDataPrimaryBase() {}
private:
	unsigned int m_04;
};

class TooltipUpgradeModuleDataIntermediateBase
	: public TooltipUpgradeModuleDataPrimaryBase
{
	UpgradeModuleDataSub m_sub;
};

class TooltipUpgradeModuleData : public TooltipUpgradeModuleDataIntermediateBase
{
public:
	virtual ~TooltipUpgradeModuleData();
private:
	AsciiString m_70;
	AsciiString m_74;
};

TooltipUpgradeModuleData::~TooltipUpgradeModuleData()
{
}
