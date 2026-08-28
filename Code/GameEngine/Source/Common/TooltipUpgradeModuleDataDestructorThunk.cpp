// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean C++ lift of the ModuleData destructor.

class UpgradeModuleDataSub
{
public:
	~UpgradeModuleDataSub();

private:
	char m_opaque[0x68];
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	~AsciiString();

private:
	char *m_data;
};

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
