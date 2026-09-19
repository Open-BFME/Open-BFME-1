// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: UpgradeSoundSelectorClientBehaviorModuleData dtor. PropagandaTower SEH pattern.

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

class __declspec(novtable) UpgradeSoundSelectorClientBehaviorModuleData : public UpgradeSoundSelectorClientBehaviorModuleDataBase
{
public:
	virtual ~UpgradeSoundSelectorClientBehaviorModuleData();
private:
	UpgradeSoundSelectorClientBehaviorModuleDataMember m_member;
};

// ??1UpgradeSoundSelectorClientBehaviorModuleData@@UAE@XZ
UpgradeSoundSelectorClientBehaviorModuleData::~UpgradeSoundSelectorClientBehaviorModuleData()
{
}
