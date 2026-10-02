// cl: /DNDEBUG /MD /EHsc
// WeaponBonusUpgrade::upgradeImplementation at retail 0x002DA450: slot 9 of the UpgradeMux table
// 0x010CE5B8, reached only through ILT 0x0000301C. WeaponBonusUpgrade's registered
// constructor 0x002DA320 stores that table. Evidence:
// targets/game/reverse/identity_evidence/upgrademux-slot9-upgradeimplementation.md

struct Rva002DA450Nested
{
	unsigned char m_padding[0x2A0];
	unsigned m_flags;
};

class WeaponBonusUpgrade
{
protected:
	virtual void upgradeImplementation();
};

void WeaponBonusUpgrade::upgradeImplementation()
{
	Rva002DA450Nested *nested = *reinterpret_cast<Rva002DA450Nested **>(
		reinterpret_cast<unsigned char *>(this) - 8);
	nested->m_flags |= 0x20;
}
