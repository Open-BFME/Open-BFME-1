// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: DualWeaponBehaviorModuleData default ctor.
// Layout: vtable@0, gap@4 (uninit), dword@8, byte@c, dword@10, byte@14, byte@15.

class DualWeaponBehaviorModuleData
{
public:
	DualWeaponBehaviorModuleData();
	virtual ~DualWeaponBehaviorModuleData();

private:
	unsigned int m_gap4;
	unsigned int m_u8;
	unsigned char m_b0c;
	unsigned char m_pad0d;
	unsigned char m_pad0e;
	unsigned char m_pad0f;
	unsigned int m_u10;
	unsigned char m_b14;
	unsigned char m_b15;
};

// ??0DualWeaponBehaviorModuleData@@QAE@XZ
DualWeaponBehaviorModuleData::DualWeaponBehaviorModuleData()
{
	m_u8 = 0;
	m_b0c = 0;
	m_u10 = 0;
	m_b14 = 0;
	m_b15 = 0;
}
