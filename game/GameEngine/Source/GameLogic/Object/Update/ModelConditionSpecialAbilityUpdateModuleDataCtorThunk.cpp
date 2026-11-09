// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: ModelConditionSpecialAbilityUpdateModuleData ctor - base 0x254.

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
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
	unsigned int m_whichSpecialPower;
	unsigned char m_generateTerror;
	unsigned char m_generateUncontrollableFear;
	unsigned char m_pad25a[2];
	float m_emotionPulseRadius;
};

// ??0ModelConditionSpecialAbilityUpdateModuleData@@QAE@XZ
ModelConditionSpecialAbilityUpdateModuleData::ModelConditionSpecialAbilityUpdateModuleData()
	: SpecialPowerModuleData()
{
	m_generateTerror = 0;
	m_generateUncontrollableFear = 0;
	m_whichSpecialPower = 1;
	m_emotionPulseRadius = 50.0f;
}
