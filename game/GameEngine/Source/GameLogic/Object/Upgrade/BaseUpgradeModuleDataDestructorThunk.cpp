// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
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

#include "ascii_string.h"

class BaseUpgradeModuleDataPrimaryBase
{
public:
	virtual ~BaseUpgradeModuleDataPrimaryBase() {}

private:
	unsigned int m_04;
};

// TU-local name: this view keeps the primary base vtable the destructor
// needs, so its implicit base destructor COMDAT differs from the ctor TU's.
class __declspec(novtable) BaseUpgradeModuleDataDtorIntermediateBase
	: public BaseUpgradeModuleDataPrimaryBase
{
	UpgradeModuleDataSub m_sub;
};

class __declspec(novtable) BaseUpgradeModuleData
	: public BaseUpgradeModuleDataDtorIntermediateBase
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
