// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: WeaponStore constructor
// SubsystemInterface base, vtbl, zero three dwords at +8/+0xC/+0x10.
// Volatile stores keep vtbl before field zeros.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual void subsystemInterfaceAnchor();

private:
	unsigned int m_pad;
};

extern "C" char WeaponStore_vtbl;

class __declspec(novtable) WeaponStore : public SubsystemInterface
{
public:
	WeaponStore();

private:
	unsigned int m_a;
	unsigned int m_b;
	unsigned int m_c;
};

// ??0WeaponStore@@QAE@XZ
WeaponStore::WeaponStore()
{
	*reinterpret_cast<char *volatile *>(this) = &WeaponStore_vtbl;
	*reinterpret_cast<unsigned int volatile *>(&m_a) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_b) = 0;
	*reinterpret_cast<unsigned int volatile *>(&m_c) = 0;
}
