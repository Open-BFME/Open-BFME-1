// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// ModuleFactory's verified allocator fixes the BFME object at 0x74 bytes.
// EA's class declaration and the clean destructor independently place the
// UpgradeModuleData subobject at +0x08 and its AsciiString at +0x70.

#include "ascii_string.h"

extern AsciiString TheBfmeCrateNameDefault;

class CommandSetUpgradeModuleDataBase
{
public:
	CommandSetUpgradeModuleDataBase();
	virtual ~CommandSetUpgradeModuleDataBase();

private:
	unsigned char m_data[0x64];
};

class __declspec(novtable) CommandSetUpgradeModuleDataPrimaryBase
{
public:
	virtual void moduleDataAnchor();

private:
	unsigned int m_field04;
};

class __declspec(novtable) CommandSetUpgradeModuleDataIntermediateBase
	: public CommandSetUpgradeModuleDataPrimaryBase
{
protected:
	CommandSetUpgradeModuleDataBase m_upgradeModuleData;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CommandSetUpgrade.h
class CommandSetUpgradeModuleData : public CommandSetUpgradeModuleDataIntermediateBase
{
public:
	CommandSetUpgradeModuleData();
	virtual ~CommandSetUpgradeModuleData();
	virtual void moduleDataAnchor();

private:
	AsciiString m_triggerAlt;
};

// ??0CommandSetUpgradeModuleData@@QAE@XZ
CommandSetUpgradeModuleData::CommandSetUpgradeModuleData()
{
	m_triggerAlt = TheBfmeCrateNameDefault;
}
