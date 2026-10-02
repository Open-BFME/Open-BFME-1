// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SpawnBehaviorModuleData dtor. dual members @+0x20/+0x58.

class SpawnBehaviorModuleDataMemberA
{
public:
	~SpawnBehaviorModuleDataMemberA();
private:
	unsigned char m_pad[0x38];
};

// The +0x58 member's destructor is the body matched as this name; the
// 0x0001B97D ILT fronts it. Spelled as the defining name so the reference
// links.
class AttributeModifierAuraUpdateModuleDataMemberD
{
public:
	~AttributeModifierAuraUpdateModuleDataMemberD();
private:
	unsigned char m_pad[0x4];
};

class SpawnBehaviorModuleDataBase
{
public:
	virtual ~SpawnBehaviorModuleDataBase() {}
private:
	unsigned char m_pad[0x1c];
};

class __declspec(novtable) SpawnBehaviorModuleData : public SpawnBehaviorModuleDataBase
{
public:
	virtual ~SpawnBehaviorModuleData();
private:
	SpawnBehaviorModuleDataMemberA m_a;
	AttributeModifierAuraUpdateModuleDataMemberD m_b;
};

// ??1SpawnBehaviorModuleData@@UAE@XZ
SpawnBehaviorModuleData::~SpawnBehaviorModuleData()
{
}
