// cl: /DNDEBUG /MD /EHsc
//
// Retail's ModelConditionSoundSelectorClientBehaviorModuleData vtable at
// 0x011157C0 names this scalar deleting destructor in slot zero. Its call
// target is the independently matched destructor body at 0x00607710.

class ModelConditionSoundSelectorClientBehaviorModuleDataMember
{
public:
	~ModelConditionSoundSelectorClientBehaviorModuleDataMember();
};

class ModelConditionSoundSelectorClientBehaviorModuleDataBase
{
public:
	virtual ~ModelConditionSoundSelectorClientBehaviorModuleDataBase() {}
private:
	unsigned char m_pad[0x4];
};

class ModelConditionSoundSelectorClientBehaviorModuleData
	: public ModelConditionSoundSelectorClientBehaviorModuleDataBase
{
public:
	virtual ~ModelConditionSoundSelectorClientBehaviorModuleData();
private:
	ModelConditionSoundSelectorClientBehaviorModuleDataMember m_member;
};

ModelConditionSoundSelectorClientBehaviorModuleData::~ModelConditionSoundSelectorClientBehaviorModuleData()
{
}
