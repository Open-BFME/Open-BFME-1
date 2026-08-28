// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: WeaponSetSpecialAbilityUpdateModuleData ctor twin of FellBeastSwoop.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerModuleData
{
public:
	SpecialPowerModuleData();
	virtual ~SpecialPowerModuleData();

private:
	unsigned char m_base[0x250];
};

class WeaponSetSpecialAbilityUpdateModuleData : public SpecialPowerModuleData
{
public:
	WeaponSetSpecialAbilityUpdateModuleData();
	virtual ~WeaponSetSpecialAbilityUpdateModuleData();

private:
	unsigned int m_field254;
	unsigned int m_field258;
};

// ??0WeaponSetSpecialAbilityUpdateModuleData@@QAE@XZ
WeaponSetSpecialAbilityUpdateModuleData::WeaponSetSpecialAbilityUpdateModuleData()
	: SpecialPowerModuleData()
{
	m_field254 = 0;
	m_field258 = 0;
}
