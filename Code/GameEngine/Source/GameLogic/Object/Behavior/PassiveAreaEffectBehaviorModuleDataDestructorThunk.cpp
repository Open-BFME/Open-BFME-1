// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: PassiveAreaEffectBehaviorModuleData dtor.

class PassiveAreaEffectBehaviorModuleDataMemberA
{
public:
	~PassiveAreaEffectBehaviorModuleDataMemberA();
private:
	unsigned char m_pad[0xc];
};

class PassiveAreaEffectBehaviorModuleDataMemberB
{
public:
	~PassiveAreaEffectBehaviorModuleDataMemberB();
private:
	unsigned char m_pad[4];
};

class PassiveAreaEffectBehaviorModuleDataBase
{
public:
	virtual ~PassiveAreaEffectBehaviorModuleDataBase() {}
private:
	unsigned char m_pad[0x10];
};

class __declspec(novtable) PassiveAreaEffectBehaviorModuleData
	: public PassiveAreaEffectBehaviorModuleDataBase
{
public:
	virtual ~PassiveAreaEffectBehaviorModuleData();
private:
	PassiveAreaEffectBehaviorModuleDataMemberA m_a;
	PassiveAreaEffectBehaviorModuleDataMemberB m_b;
};

// ??1PassiveAreaEffectBehaviorModuleData@@UAE@XZ
PassiveAreaEffectBehaviorModuleData::~PassiveAreaEffectBehaviorModuleData()
{
}
