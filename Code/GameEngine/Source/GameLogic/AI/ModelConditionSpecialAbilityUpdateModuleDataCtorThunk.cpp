// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: ModelConditionSpecialAbilityUpdateModuleData ctor - base 0x254.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerModuleData
{
public:
	SpecialPowerModuleData();
	virtual ~SpecialPowerModuleData();

private:
	unsigned char m_base[0x250];
};

class ModelConditionSpecialAbilityUpdateModuleData : public SpecialPowerModuleData
{
public:
	ModelConditionSpecialAbilityUpdateModuleData();
	virtual ~ModelConditionSpecialAbilityUpdateModuleData();

private:
	unsigned int m_254;
	unsigned char m_258;
	unsigned char m_259;
	unsigned char m_pad25a[2];
	float m_25c;
};

// ??0ModelConditionSpecialAbilityUpdateModuleData@@QAE@XZ
ModelConditionSpecialAbilityUpdateModuleData::ModelConditionSpecialAbilityUpdateModuleData()
	: SpecialPowerModuleData()
{
	m_258 = 0;
	m_259 = 0;
	m_254 = 1;
	m_25c = 50.0f;
}
