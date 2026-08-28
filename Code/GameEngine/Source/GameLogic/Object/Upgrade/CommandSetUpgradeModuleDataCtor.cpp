// cl: /DNDEBUG /MD /EHsc
// ModuleFactory's verified allocator fixes the BFME object at 0x74 bytes.
// EA's class declaration and the clean destructor independently place the
// UpgradeModuleData subobject at +0x08 and its AsciiString at +0x70.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString() : m_data( 0 ) {}
	~AsciiString();
	AsciiString &operator=( const AsciiString &other );

private:
	char *m_data;
};

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/CommandSetUpgrade.h
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
