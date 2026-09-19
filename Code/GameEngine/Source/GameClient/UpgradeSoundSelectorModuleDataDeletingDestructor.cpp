// cl: /DNDEBUG /MD /EHsc
//
// Retail's UpgradeSoundSelectorClientBehaviorModuleData vtable at 0x01115A38
// names this scalar deleting destructor in slot zero. Its call target is the
// independently matched destructor body at 0x00608F80.

class UpgradeSoundSelectorClientBehaviorModuleDataMember
{
public:
	~UpgradeSoundSelectorClientBehaviorModuleDataMember();
};

class UpgradeSoundSelectorClientBehaviorModuleDataBase
{
public:
	virtual ~UpgradeSoundSelectorClientBehaviorModuleDataBase() {}
private:
	unsigned char m_pad[0x4];
};

class UpgradeSoundSelectorClientBehaviorModuleData
	: public UpgradeSoundSelectorClientBehaviorModuleDataBase
{
public:
	virtual ~UpgradeSoundSelectorClientBehaviorModuleData();
private:
	UpgradeSoundSelectorClientBehaviorModuleDataMember m_member;
};

UpgradeSoundSelectorClientBehaviorModuleData::~UpgradeSoundSelectorClientBehaviorModuleData()
{
}
