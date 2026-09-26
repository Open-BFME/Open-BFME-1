// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: WeaponFireSpecialAbilityUpdateModuleData ctor
// Retail: base call, xor eax, vtbl, then zeros at +0x254/+0x258/+0x25c/+0x260/+0x264.
// All stores volatile so MSVC 7.1 cannot hoist field zeros above the vtbl write.

class WeaponFireSpecialAbilityUpdateModuleDataBase
{
public:
	WeaponFireSpecialAbilityUpdateModuleDataBase();
	virtual void weaponFireModuleDataBaseAnchor();

private:
	unsigned char m_pad[0x250];
};

extern "C" char WeaponFireSpecialAbilityUpdateModuleData_vtbl;

class __declspec(novtable) WeaponFireSpecialAbilityUpdateModuleData
	: public WeaponFireSpecialAbilityUpdateModuleDataBase
{
public:
	WeaponFireSpecialAbilityUpdateModuleData();

private:
	unsigned int m_254;
	unsigned int m_258;
	unsigned char m_25c;
	unsigned char m_pad25d[3];
	unsigned int m_260;
	unsigned char m_264;
};

// ??0WeaponFireSpecialAbilityUpdateModuleData@@QAE@XZ
WeaponFireSpecialAbilityUpdateModuleData::WeaponFireSpecialAbilityUpdateModuleData()
{
	*reinterpret_cast<char *volatile *>(this) =
		&WeaponFireSpecialAbilityUpdateModuleData_vtbl;
	*reinterpret_cast<unsigned int volatile *>(&m_254) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_258) = 0;
	*reinterpret_cast<unsigned char volatile *>(&m_25c) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_260) = 0;
	*reinterpret_cast<unsigned char volatile *>(&m_264) = 0;
}
