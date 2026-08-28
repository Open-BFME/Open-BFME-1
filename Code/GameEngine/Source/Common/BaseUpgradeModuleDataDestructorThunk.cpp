// cl: /DNDEBUG /MD /EHsc
// Cloned from the TooltipUpgradeModuleData model: identical body once relocation
// immediates are masked so the same class shape reproduces it.
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

class BaseUpgradeModuleDataPrimaryBase
{
public:
	virtual ~BaseUpgradeModuleDataPrimaryBase() {}

private:
	unsigned int m_04;
};

class __declspec(novtable) BaseUpgradeModuleDataIntermediateBase
	: public BaseUpgradeModuleDataPrimaryBase
{
	UpgradeModuleDataSub m_sub;
};

class __declspec(novtable) BaseUpgradeModuleData
	: public BaseUpgradeModuleDataIntermediateBase
{
public:
	virtual ~BaseUpgradeModuleData();

private:
	AsciiString m_70;
	AsciiString m_74;
};

// ??1BaseUpgradeModuleData@@UAE@XZ
BaseUpgradeModuleData::~BaseUpgradeModuleData()
{
}
