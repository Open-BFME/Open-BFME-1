// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: ModelConditionSoundSelectorClientBehaviorModuleData lifecycle.

class ModelConditionSoundSelectorClientBehaviorModuleDataMember
{
public:
	~ModelConditionSoundSelectorClientBehaviorModuleDataMember();

	unsigned int m_00;
	unsigned int m_04;
	unsigned int m_08;
};

class ModelConditionSoundSelectorClientBehaviorModuleDataBase
{
public:
	virtual ~ModelConditionSoundSelectorClientBehaviorModuleDataBase() {}

private:
	unsigned char m_pad[0x4];
};

class ModelConditionSoundSelectorClientBehaviorModuleData : public ModelConditionSoundSelectorClientBehaviorModuleDataBase
{
public:
	ModelConditionSoundSelectorClientBehaviorModuleData();
	virtual ~ModelConditionSoundSelectorClientBehaviorModuleData();

private:
	ModelConditionSoundSelectorClientBehaviorModuleDataMember m_member;
};

// ??0ModelConditionSoundSelectorClientBehaviorModuleData@@QAE@XZ
ModelConditionSoundSelectorClientBehaviorModuleData::ModelConditionSoundSelectorClientBehaviorModuleData()
{
	m_member.m_00 = 0;
	m_member.m_04 = 0;
	m_member.m_08 = 0;
}

class __declspec(novtable) ModelConditionSoundSelectorClientBehaviorModuleData;

// ??1ModelConditionSoundSelectorClientBehaviorModuleData@@UAE@XZ
ModelConditionSoundSelectorClientBehaviorModuleData::~ModelConditionSoundSelectorClientBehaviorModuleData()
{
}
