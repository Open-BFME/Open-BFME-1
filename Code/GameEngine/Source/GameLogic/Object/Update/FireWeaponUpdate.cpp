// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: FireWeaponUpdateModuleData default ctor.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FireWeaponUpdate.h
class FireWeaponUpdateModuleData
{
public:
	FireWeaponUpdateModuleData();
	virtual ~FireWeaponUpdateModuleData();

private:
	unsigned int m_gap4;
	unsigned int m_08;
	unsigned char m_0c;
	unsigned char m_0d;
	unsigned char m_0e;
};

// ??0FireWeaponUpdateModuleData@@QAE@XZ
FireWeaponUpdateModuleData::FireWeaponUpdateModuleData()
{
	m_08 = 0;
	m_0c = 0;
	m_0d = 0;
	m_0e = 0;
}