// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Open-BFME5: TooltipUpgrade module-data constructor.
//
// The named friend_newModuleData factory at retail 0x0012BC30 allocates 0x78
// bytes and calls this constructor. Its matched destructor at 0x0012BBB0
// independently fixes the UpgradeModuleData subobject at +0x08 and the two
// adjacent string members at +0x70 and +0x74.

class UpgradeModuleDataSub
{
public:
	UpgradeModuleDataSub();
	~UpgradeModuleDataSub();

private:
	unsigned char m_data[ 0x68 ];
};

#include "ascii_string.h"

extern AsciiString TheEmptyString;

class __declspec(novtable) TooltipUpgradeModuleDataPrimaryBase
{
public:
	virtual ~TooltipUpgradeModuleDataPrimaryBase() {}

private:
	unsigned int m_moduleData;
};

class __declspec(novtable) TooltipUpgradeModuleDataIntermediateBase
	: public TooltipUpgradeModuleDataPrimaryBase
{
protected:
	UpgradeModuleDataSub m_upgradeData;
};

class TooltipUpgradeModuleData
	: public TooltipUpgradeModuleDataIntermediateBase
{
public:
	TooltipUpgradeModuleData();
	virtual ~TooltipUpgradeModuleData();

private:
	AsciiString m_tooltipName;
	AsciiString m_disabledTooltipName;
};

// ??0TooltipUpgradeModuleData@@QAE@XZ
TooltipUpgradeModuleData::TooltipUpgradeModuleData()
{
	m_tooltipName.set( TheEmptyString );
	m_disabledTooltipName.set( TheEmptyString );
}
