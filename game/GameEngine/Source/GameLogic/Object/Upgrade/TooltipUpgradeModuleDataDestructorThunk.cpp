// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5: clean C++ lift of the ModuleData destructor.

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

class __declspec(novtable) TooltipUpgradeModuleDataIntermediateBase
	: public TooltipUpgradeModuleDataPrimaryBase
{
	UpgradeModuleDataSub m_sub;
};

class __declspec(novtable) TooltipUpgradeModuleData
	: public TooltipUpgradeModuleDataIntermediateBase
{
public:
	virtual ~TooltipUpgradeModuleData();

private:
	AsciiString m_70;
	AsciiString m_74;
};

// ??1TooltipUpgradeModuleData@@UAE@XZ
TooltipUpgradeModuleData::~TooltipUpgradeModuleData()
{
}
