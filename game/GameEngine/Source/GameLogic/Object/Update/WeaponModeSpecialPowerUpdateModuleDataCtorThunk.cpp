// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: WeaponModeSpecialPowerUpdateModuleData ctor
// Retail: base, xor eax, vtbl, zeros +0x1d0/+0x1d4, +0x1d8=3, zero +0x1dc twice.
// Volatile stores preserve order under MSVC 7.1.

class WeaponModeSpecialPowerUpdateModuleDataBase
{
public:
	WeaponModeSpecialPowerUpdateModuleDataBase();
	virtual void weaponModeModuleDataBaseAnchor();

private:
	unsigned char m_pad[0x1CC];
};

extern "C" char WeaponModeSpecialPowerUpdateModuleData_vtbl;

class __declspec(novtable) WeaponModeSpecialPowerUpdateModuleData
	: public WeaponModeSpecialPowerUpdateModuleDataBase
{
public:
	WeaponModeSpecialPowerUpdateModuleData();

private:
	unsigned int m_1d0;
	unsigned int m_1d4;
	unsigned int m_1d8;
	unsigned int m_1dc;
};

// ??0WeaponModeSpecialPowerUpdateModuleData@@QAE@XZ
WeaponModeSpecialPowerUpdateModuleData::WeaponModeSpecialPowerUpdateModuleData()
{
	*reinterpret_cast<char *volatile *>(this) =
		&WeaponModeSpecialPowerUpdateModuleData_vtbl;
	*reinterpret_cast<unsigned int volatile *>(&m_1d0) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_1d4) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_1d8) = 3;
	*reinterpret_cast<unsigned int volatile *>(&m_1dc) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_1dc) = 0;
}
