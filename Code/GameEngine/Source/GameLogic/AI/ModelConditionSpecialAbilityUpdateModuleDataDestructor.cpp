// cl: /O2 /Ob0

class SpecialAbilityUpdateModuleData
{
public:
	virtual ~SpecialAbilityUpdateModuleData();

private:
	unsigned char m_moduleDataStorage[0x250];
};

class __declspec(novtable) ModelConditionSpecialAbilityUpdateModuleData : public SpecialAbilityUpdateModuleData
{
public:
	virtual ~ModelConditionSpecialAbilityUpdateModuleData();
};

ModelConditionSpecialAbilityUpdateModuleData::~ModelConditionSpecialAbilityUpdateModuleData()
{
}
