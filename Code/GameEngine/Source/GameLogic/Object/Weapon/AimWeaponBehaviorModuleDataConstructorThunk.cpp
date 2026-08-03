// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: AimWeaponBehaviorModuleData default ctor.

class AimWeaponBehaviorModuleData
{
public:
	AimWeaponBehaviorModuleData();
	virtual ~AimWeaponBehaviorModuleData();

private:
	unsigned int m_gap4;
	float m_08;
	float m_0c;
	unsigned int m_10;
	unsigned int m_14;
};

// ??0AimWeaponBehaviorModuleData@@QAE@XZ
AimWeaponBehaviorModuleData::AimWeaponBehaviorModuleData()
{
	m_08 = -0.05f;
	m_0c = 0.05f;
	m_10 = 0;
	m_14 = 0x7f7fffff;
}