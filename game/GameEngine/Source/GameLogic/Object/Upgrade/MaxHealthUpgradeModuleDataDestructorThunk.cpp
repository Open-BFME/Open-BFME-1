// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: MaxHealthUpgradeModuleData dtor. SEH member@+0x8 pin 0x1B97D.

// The +0x08 member's destructor is the body matched as this name; the
// 0x0001B97D ILT fronts it. Spelled as the defining name so the reference
// links.
class AttributeModifierAuraUpdateModuleDataMemberD
{
public:
	~AttributeModifierAuraUpdateModuleDataMemberD();
};

class MaxHealthUpgradeModuleDataBase
{
public:
	virtual ~MaxHealthUpgradeModuleDataBase() {}
private:
	unsigned char m_pad[0x4];
};

class __declspec(novtable) MaxHealthUpgradeModuleData : public MaxHealthUpgradeModuleDataBase
{
public:
	virtual ~MaxHealthUpgradeModuleData();
private:
	AttributeModifierAuraUpdateModuleDataMemberD m_member;
};

// ??1MaxHealthUpgradeModuleData@@UAE@XZ
MaxHealthUpgradeModuleData::~MaxHealthUpgradeModuleData()
{
}
