// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: AttributeModifierAuraUpdateModuleData dtor.
// Four staggered members @+0x08/+0x0c/+0x24/+0x28.

class AttributeModifierAuraUpdateModuleDataMemberA
{
public:
	~AttributeModifierAuraUpdateModuleDataMemberA();
private:
	unsigned char m_pad[4];
};

class AttributeModifierAuraUpdateModuleDataMemberB
{
public:
	~AttributeModifierAuraUpdateModuleDataMemberB();
private:
	unsigned char m_pad[4];
};

class AttributeModifierAuraUpdateModuleDataMemberC
{
public:
	~AttributeModifierAuraUpdateModuleDataMemberC();
private:
	unsigned char m_pad[4];
};

class AttributeModifierAuraUpdateModuleDataMemberD
{
public:
	~AttributeModifierAuraUpdateModuleDataMemberD();
private:
	unsigned char m_pad[4];
};

class AttributeModifierAuraUpdateModuleDataBase
{
public:
	virtual ~AttributeModifierAuraUpdateModuleDataBase() {}
private:
	unsigned char m_pad[4];
};

class __declspec(novtable) AttributeModifierAuraUpdateModuleData
	: public AttributeModifierAuraUpdateModuleDataBase
{
public:
	virtual ~AttributeModifierAuraUpdateModuleData();
private:
	AttributeModifierAuraUpdateModuleDataMemberA m_a;
	AttributeModifierAuraUpdateModuleDataMemberB m_b;
	unsigned char m_gap[0x14];
	AttributeModifierAuraUpdateModuleDataMemberC m_c;
	AttributeModifierAuraUpdateModuleDataMemberD m_d;
};

// ??1AttributeModifierAuraUpdateModuleData@@UAE@XZ
AttributeModifierAuraUpdateModuleData::~AttributeModifierAuraUpdateModuleData()
{
}
